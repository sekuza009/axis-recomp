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

static void lift_4557e0(X86 *m);
static void lift_455080(X86 *m);
static void lift_466a60(X86 *m);
static void lift_46aeb0(X86 *m);
static void lift_46ce80(X86 *m);

/* image_copyTo (0x46ce80), lifted by tools/lift.py */
static void lift_46ce80(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0xc14u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46ce80: sub esp, 0xc14 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46ce86: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46ce87: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46ce88: push esi */
	m->esi = M32((DWORD)(m->esp + 0xc34u));	/* 46ce89: mov esi, dword ptr [esp + 0xc34] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46ce90: xor eax, eax */
	m->edx = m->ecx;	/* 46ce92: mov edx, ecx */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46ce94: cmp esi, eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46ce96: push edi */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 46ce97: mov dword ptr [esp + 0x20], edx */
	if (m->sf == m->of) goto L_46cec1;	/* 46ce9b: jge 0x46cec1 */
	m->edi = M32((DWORD)(m->esp + 0xc40u));	/* 46ce9d: mov edi, dword ptr [esp + 0xc40] */
	M32((DWORD)(m->esp + 0xc38u)) = m->eax;	/* 46cea4: mov dword ptr [esp + 0xc38], eax */
	{ DWORD a_ = m->edi, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46ceab: sub edi, esi */
	M32((DWORD)(m->esp + 0xc40u)) = m->edi;	/* 46cead: mov dword ptr [esp + 0xc40], edi */
	m->edi = M32((DWORD)(m->esp + 0xc48u));	/* 46ceb4: mov edi, dword ptr [esp + 0xc48] */
	{ DWORD a_ = m->edi, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46cebb: add edi, esi */
	m->esi = m->eax;	/* 46cebd: mov esi, eax */
	goto L_46cec8;	/* 46cebf: jmp 0x46cec8 */
L_46cec1:
	m->edi = M32((DWORD)(m->esp + 0xc48u));	/* 46cec1: mov edi, dword ptr [esp + 0xc48] */
L_46cec8:
	m->ecx = M32((DWORD)(m->esp + 0xc3cu));	/* 46cec8: mov ecx, dword ptr [esp + 0xc3c] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46cecf: cmp ecx, eax */
	if (m->sf == m->of) goto L_46cef0;	/* 46ced1: jge 0x46cef0 */
	m->ebp = M32((DWORD)(m->esp + 0xc44u));	/* 46ced3: mov ebp, dword ptr [esp + 0xc44] */
	m->ebx = M32((DWORD)(m->esp + 0xc4cu));	/* 46ceda: mov ebx, dword ptr [esp + 0xc4c] */
	{ DWORD a_ = m->ebp, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 46cee1: sub ebp, ecx */
	{ DWORD a_ = m->ebx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 46cee3: add ebx, ecx */
	M32((DWORD)(m->esp + 0xc3cu)) = m->eax;	/* 46cee5: mov dword ptr [esp + 0xc3c], eax */
	m->ecx = m->eax;	/* 46ceec: mov ecx, eax */
	goto L_46cefe;	/* 46ceee: jmp 0x46cefe */
L_46cef0:
	m->ebx = M32((DWORD)(m->esp + 0xc4cu));	/* 46cef0: mov ebx, dword ptr [esp + 0xc4c] */
	m->ebp = M32((DWORD)(m->esp + 0xc44u));	/* 46cef7: mov ebp, dword ptr [esp + 0xc44] */
L_46cefe:
	m->eax = M32((DWORD)(m->edx + 0x3eu));	/* 46cefe: mov eax, dword ptr [edx + 0x3e] */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46cf01: cmp esi, eax */
	if (m->sf == m->of) goto L_46d250;	/* 46cf03: jge 0x46d250 */
	m->edx = M32((DWORD)(m->edx + 0x42u));	/* 46cf09: mov edx, dword ptr [edx + 0x42] */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46cf0c: cmp ecx, edx */
	if (m->sf == m->of) goto L_46d250;	/* 46cf0e: jge 0x46d250 */
	{ DWORD a_ = m->esi, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46cf14: add esi, edi */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46cf16: cmp esi, eax */
	if (m->zf || m->sf != m->of) goto L_46cf23;	/* 46cf18: jle 0x46cf23 */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->esp + 0xc38u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46cf1a: sub eax, dword ptr [esp + 0xc38] */
	m->edi = m->eax;	/* 46cf21: mov edi, eax */
L_46cf23:
	m->eax = (DWORD)(m->ecx + m->ebx*1 + 0x0u);	/* 46cf23: lea eax, [ecx + ebx] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46cf26: cmp eax, edx */
	if (m->zf || m->sf != m->of) goto L_46cf2e;	/* 46cf28: jle 0x46cf2e */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46cf2a: sub edx, ecx */
	m->ebx = m->edx;	/* 46cf2c: mov ebx, edx */
L_46cf2e:
	m->edx = M32((DWORD)(m->esp + 0xc40u));	/* 46cf2e: mov edx, dword ptr [esp + 0xc40] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46cf35: test edx, edx */
	if (m->sf == m->of) goto L_46cf5d;	/* 46cf37: jge 0x46cf5d */
	m->esi = M32((DWORD)(m->esp + 0xc38u));	/* 46cf39: mov esi, dword ptr [esp + 0xc38] */
	M32((DWORD)(m->esp + 0xc40u)) = 0x0u;	/* 46cf40: mov dword ptr [esp + 0xc40], 0 */
	{ DWORD a_ = m->esi, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46cf4b: sub esi, edx */
	{ DWORD a_ = m->edi, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46cf4d: add edi, edx */
	m->edx = M32((DWORD)(m->esp + 0xc40u));	/* 46cf4f: mov edx, dword ptr [esp + 0xc40] */
	M32((DWORD)(m->esp + 0xc38u)) = m->esi;	/* 46cf56: mov dword ptr [esp + 0xc38], esi */
L_46cf5d:
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46cf5d: test ebp, ebp */
	if (m->sf == m->of) goto L_46cf6e;	/* 46cf5f: jge 0x46cf6e */
	{ DWORD a_ = m->ecx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46cf61: sub ecx, ebp */
	{ DWORD a_ = m->ebx, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 46cf63: add ebx, ebp */
	M32((DWORD)(m->esp + 0xc3cu)) = m->ecx;	/* 46cf65: mov dword ptr [esp + 0xc3c], ecx */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 46cf6c: xor ebp, ebp */
L_46cf6e:
	m->esi = M32((DWORD)(m->esp + 0xc2cu));	/* 46cf6e: mov esi, dword ptr [esp + 0xc2c] */
	{ DWORD a_ = m->edx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46cf75: cmp edx, esi */
	if (m->sf == m->of) goto L_46d250;	/* 46cf77: jge 0x46d250 */
	m->eax = M32((DWORD)(m->esp + 0xc30u));	/* 46cf7d: mov eax, dword ptr [esp + 0xc30] */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46cf84: cmp ebp, eax */
	if (m->sf == m->of) goto L_46d250;	/* 46cf86: jge 0x46d250 */
	{ DWORD a_ = m->edx, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46cf8c: add edx, edi */
	{ DWORD a_ = m->edx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46cf8e: cmp edx, esi */
	if (m->zf || m->sf != m->of) goto L_46cf9d;	/* 46cf90: jle 0x46cf9d */
	m->edx = M32((DWORD)(m->esp + 0xc40u));	/* 46cf92: mov edx, dword ptr [esp + 0xc40] */
	m->edi = m->esi;	/* 46cf99: mov edi, esi */
	{ DWORD a_ = m->edi, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46cf9b: sub edi, edx */
L_46cf9d:
	m->edx = (DWORD)(m->ebx + m->ebp*1 + 0x0u);	/* 46cf9d: lea edx, [ebx + ebp] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46cfa0: cmp edx, eax */
	if (m->zf || m->sf != m->of) goto L_46cfa8;	/* 46cfa2: jle 0x46cfa8 */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46cfa4: sub eax, ebp */
	m->ebx = m->eax;	/* 46cfa6: mov ebx, eax */
L_46cfa8:
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46cfa8: test edi, edi */
	if (m->zf || m->sf != m->of) goto L_46d250;	/* 46cfaa: jle 0x46d250 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46cfb0: test ebx, ebx */
	if (m->zf || m->sf != m->of) goto L_46d250;	/* 46cfb2: jle 0x46d250 */
	{ DWORD a_ = m->edi, b_ = 0x400u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46cfb8: cmp edi, 0x400 */
	if (m->zf || m->sf != m->of) goto L_46cfd9;	/* 46cfbe: jle 0x46cfd9 */
	{ DWORD v_ = 0x4c5984u; m->esp -= 4; M32(m->esp) = v_; }	/* 46cfc0: push 0x4c5984 */
	{ DWORD v_ = 0xa1f0f0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46cfc5: push 0xa1f0f0 */
	m->esp -= 4; M32(m->esp) = 0x46cfcfu; native_call(m, 0x46c710u);	/* 46cfca: call 0x46c710 */
	m->ecx = M32((DWORD)(m->esp + 0xc44u));	/* 46cfcf: mov ecx, dword ptr [esp + 0xc44] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46cfd6: add esp, 8 */
L_46cfd9:
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 46cfd9: mov edx, dword ptr [esp + 0x20] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46cfdd: push 0 */
	m->eax = M32((DWORD)(m->edx + 0x42u));	/* 46cfdf: mov eax, dword ptr [edx + 0x42] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46cfe2: sub eax, ecx */
	m->ecx = M32((DWORD)(m->esp + 0xc3cu));	/* 46cfe4: mov ecx, dword ptr [esp + 0xc3c] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46cfeb: sub eax, ebx */
	{ long long p_ = (long long)(int)m->eax * (int)M32((DWORD)(m->edx + 0x3eu)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 46cfed: imul eax, dword ptr [edx + 0x3e] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46cff1: add eax, ecx */
	m->ecx = M32((DWORD)(m->edx + 0x12u));	/* 46cff3: mov ecx, dword ptr [edx + 0x12] */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 46cff6: lea eax, [eax + eax*2] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46cff9: add eax, ecx */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 46cffb: mov ecx, dword ptr [edx + 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46cffe: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46cfff: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46d005u; native_call(m, 0x49e91eu);	/* 46d000: call 0x49e91e */
	m->eax = M32((DWORD)(m->esp + 0xc5cu));	/* 46d005: mov eax, dword ptr [esp + 0xc5c] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46d00c: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46d00f: test eax, eax */
	if (!m->zf) goto L_46d143;	/* 46d011: jne 0x46d143 */
	m->ecx = (DWORD)(m->ebx + 0xffffffffu);	/* 46d017: lea ecx, [ebx - 1] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46d01a: test ecx, ecx */
	if (m->sf != m->of) goto L_46d250;	/* 46d01c: jl 0x46d250 */
	m->edx = (DWORD)(m->ecx + m->ebp*1 + 0x0u);	/* 46d022: lea edx, [ecx + ebp] */
	m->eax = m->esi;	/* 46d025: mov eax, esi */
	{ long long p_ = (long long)(int)m->edx * (int)m->esi; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edx = r_; }	/* 46d027: imul edx, esi */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 46d02a: neg eax */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 46d02c: shl eax, 2 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 46d02f: mov dword ptr [esp + 0x1c], eax */
	m->eax = M32((DWORD)(m->esp + 0xc40u));	/* 46d033: mov eax, dword ptr [esp + 0xc40] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46d03a: add eax, edx */
	m->edx = M32((DWORD)(m->esp + 0xc28u));	/* 46d03c: mov edx, dword ptr [esp + 0xc28] */
	m->ebx = (DWORD)(m->esi*4 + 0x0u);	/* 46d043: lea ebx, [esi*4] */
	{ DWORD a_ = m->ebx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 46d04a: sub ebx, esi */
	m->esi = (DWORD)(m->edx + m->eax*2 + 0x0u);	/* 46d04c: lea esi, [edx + eax*2] */
	{ DWORD a_ = m->ebx, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->ebx = r_; }	/* 46d04f: neg ebx */
	m->esi = (DWORD)(m->eax + m->esi*1 + 0x2u);	/* 46d051: lea esi, [eax + esi + 2] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 46d055: inc ecx */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 46d056: mov dword ptr [esp + 0x10], esi */
	m->esi = (DWORD)(m->edx + m->eax*4 + 0x2u);	/* 46d05a: lea esi, [edx + eax*4 + 2] */
	M32((DWORD)(m->esp + 0x18u)) = m->esi;	/* 46d05e: mov dword ptr [esp + 0x18], esi */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 46d062: mov dword ptr [esp + 0x14], ecx */
L_46d066:
	m->ebp = M32((DWORD)(m->esp + 0x20u));	/* 46d066: mov ebp, dword ptr [esp + 0x20] */
	m->eax = (DWORD)(m->edi + m->edi*2 + 0x0u);	/* 46d06a: lea eax, [edi + edi*2] */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 46d06d: lea edx, [esp + 0x24] */
	m->ecx = M32((DWORD)(m->ebp + 0x4u));	/* 46d071: mov ecx, dword ptr [ebp + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46d074: push ecx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 46d075: push 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46d077: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46d078: push edx */
	m->esp -= 4; M32(m->esp) = 0x46d07eu; native_call(m, 0x49e836u);	/* 46d079: call 0x49e836 */
	m->eax = M32((DWORD)(m->esp + 0xc44u));	/* 46d07e: mov eax, dword ptr [esp + 0xc44] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46d085: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46d088: sub eax, 3 */
	if (m->zf) goto L_46d0d0;	/* 46d08b: je 0x46d0d0 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 46d08d: dec eax */
	if (m->zf) goto L_46d0a4;	/* 46d08e: je 0x46d0a4 */
	{ DWORD v_ = 0x4c5964u; m->esp -= 4; M32(m->esp) = v_; }	/* 46d090: push 0x4c5964 */
	{ DWORD v_ = 0xa1f0f0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46d095: push 0xa1f0f0 */
	m->esp -= 4; M32(m->esp) = 0x46d09fu; native_call(m, 0x46c710u);	/* 46d09a: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46d09f: add esp, 8 */
	goto L_46d0f8;	/* 46d0a2: jmp 0x46d0f8 */
L_46d0a4:
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46d0a4: test edi, edi */
	if (m->zf || m->sf != m->of) goto L_46d0f8;	/* 46d0a6: jle 0x46d0f8 */
	m->eax = m->esi;	/* 46d0a8: mov eax, esi */
	m->ecx = (DWORD)(m->esp + 0x25u);	/* 46d0aa: lea ecx, [esp + 0x25] */
	m->esi = m->edi;	/* 46d0ae: mov esi, edi */
L_46d0b0:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x1u))) & 0xff) << 0);	/* 46d0b0: mov dl, byte ptr [ecx + 1] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46d0b3: add ecx, 3 */
	M8((DWORD)(m->eax + 0xfffffffeu)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 46d0b6: mov byte ptr [eax - 2], dl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0xfffffffdu))) & 0xff) << 0);	/* 46d0b9: mov dl, byte ptr [ecx - 3] */
	M8((DWORD)(m->eax + 0xffffffffu)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 46d0bc: mov byte ptr [eax - 1], dl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0xfffffffcu))) & 0xff) << 0);	/* 46d0bf: mov dl, byte ptr [ecx - 4] */
	M8((DWORD)(m->eax + 0x0u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 46d0c2: mov byte ptr [eax], dl */
	M8((DWORD)(m->eax + 0x1u)) = (BYTE)(0xffu);	/* 46d0c4: mov byte ptr [eax + 1], 0xff */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46d0c8: add eax, 4 */
	{ DWORD a_ = m->esi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->esi = r_; }	/* 46d0cb: dec esi */
	if (!m->zf) goto L_46d0b0;	/* 46d0cc: jne 0x46d0b0 */
	goto L_46d0f8;	/* 46d0ce: jmp 0x46d0f8 */
L_46d0d0:
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46d0d0: test edi, edi */
	if (m->zf || m->sf != m->of) goto L_46d0f8;	/* 46d0d2: jle 0x46d0f8 */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 46d0d4: mov ecx, dword ptr [esp + 0x10] */
	m->eax = (DWORD)(m->esp + 0x25u);	/* 46d0d8: lea eax, [esp + 0x25] */
	m->esi = m->edi;	/* 46d0dc: mov esi, edi */
L_46d0de:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 46d0de: mov dl, byte ptr [eax + 1] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46d0e1: add eax, 3 */
	M8((DWORD)(m->ecx + 0xfffffffeu)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 46d0e4: mov byte ptr [ecx - 2], dl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0xfffffffdu))) & 0xff) << 0);	/* 46d0e7: mov dl, byte ptr [eax - 3] */
	M8((DWORD)(m->ecx + 0xffffffffu)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 46d0ea: mov byte ptr [ecx - 1], dl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0xfffffffcu))) & 0xff) << 0);	/* 46d0ed: mov dl, byte ptr [eax - 4] */
	M8((DWORD)(m->ecx + 0x0u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 46d0f0: mov byte ptr [ecx], dl */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46d0f2: add ecx, 3 */
	{ DWORD a_ = m->esi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->esi = r_; }	/* 46d0f5: dec esi */
	if (!m->zf) goto L_46d0de;	/* 46d0f6: jne 0x46d0de */
L_46d0f8:
	m->eax = M32((DWORD)(m->ebp + 0x3eu));	/* 46d0f8: mov eax, dword ptr [ebp + 0x3e] */
	m->ecx = M32((DWORD)(m->ebp + 0x4u));	/* 46d0fb: mov ecx, dword ptr [ebp + 4] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46d0fe: sub eax, edi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 46d100: push 1 */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 46d102: lea eax, [eax + eax*2] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46d105: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46d106: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46d10cu; native_call(m, 0x49e91eu);	/* 46d107: call 0x49e91e */
	m->esi = M32((DWORD)(m->esp + 0x24u));	/* 46d10c: mov esi, dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 46d110: mov edx, dword ptr [esp + 0x28] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 46d114: mov ecx, dword ptr [esp + 0x1c] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 46d118: mov eax, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46d11c: add esp, 0xc */
	{ DWORD a_ = m->esi, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46d11f: add esi, edx */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46d121: add ecx, ebx */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 46d123: dec eax */
	M32((DWORD)(m->esp + 0x18u)) = m->esi;	/* 46d124: mov dword ptr [esp + 0x18], esi */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 46d128: mov dword ptr [esp + 0x10], ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 46d12c: mov dword ptr [esp + 0x14], eax */
	if (!m->zf) goto L_46d066;	/* 46d130: jne 0x46d066 */
	m->edi = M32(m->esp); m->esp += 4;	/* 46d136: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46d137: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 46d138: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 46d139: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0xc14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46d13a: add esp, 0xc14 */
	m->esp += 4 + 44; return;	/* 46d140: ret 0x2c */
L_46d143:
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46d143: test ebx, ebx */
	if (m->zf || m->sf != m->of) goto L_46d250;	/* 46d145: jle 0x46d250 */
	m->edx = (DWORD)(m->esi + m->esi*2 + 0x0u);	/* 46d14b: lea edx, [esi + esi*2] */
	m->eax = (DWORD)(m->esi*4 + 0x0u);	/* 46d14e: lea eax, [esi*4] */
	{ long long p_ = (long long)(int)m->esi * (int)m->ebp; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->esi = r_; }	/* 46d155: imul esi, ebp */
	m->ecx = M32((DWORD)(m->esp + 0xc40u));	/* 46d158: mov ecx, dword ptr [esp + 0xc40] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 46d15f: mov dword ptr [esp + 0x1c], eax */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 46d163: mov dword ptr [esp + 0x18], edx */
	m->eax = (DWORD)(m->esi + m->ecx*1 + 0x0u);	/* 46d167: lea eax, [esi + ecx] */
	m->ecx = M32((DWORD)(m->esp + 0xc28u));	/* 46d16a: mov ecx, dword ptr [esp + 0xc28] */
	m->edx = (DWORD)(m->ecx + m->eax*2 + 0x0u);	/* 46d171: lea edx, [ecx + eax*2] */
	m->esi = (DWORD)(m->eax + m->edx*1 + 0x2u);	/* 46d174: lea esi, [eax + edx + 2] */
	m->eax = (DWORD)(m->ecx + m->eax*4 + 0x2u);	/* 46d178: lea eax, [ecx + eax*4 + 2] */
	M32((DWORD)(m->esp + 0x14u)) = m->esi;	/* 46d17c: mov dword ptr [esp + 0x14], esi */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 46d180: mov dword ptr [esp + 0x10], eax */
L_46d184:
	m->ebp = M32((DWORD)(m->esp + 0x20u));	/* 46d184: mov ebp, dword ptr [esp + 0x20] */
	m->eax = (DWORD)(m->edi + m->edi*2 + 0x0u);	/* 46d188: lea eax, [edi + edi*2] */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 46d18b: lea edx, [esp + 0x24] */
	m->ecx = M32((DWORD)(m->ebp + 0x4u));	/* 46d18f: mov ecx, dword ptr [ebp + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46d192: push ecx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 46d193: push 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46d195: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46d196: push edx */
	m->esp -= 4; M32(m->esp) = 0x46d19cu; native_call(m, 0x49e836u);	/* 46d197: call 0x49e836 */
	m->eax = M32((DWORD)(m->esp + 0xc44u));	/* 46d19c: mov eax, dword ptr [esp + 0xc44] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46d1a3: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46d1a6: sub eax, 3 */
	if (m->zf) goto L_46d1f0;	/* 46d1a9: je 0x46d1f0 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 46d1ab: dec eax */
	if (m->zf) goto L_46d1c2;	/* 46d1ac: je 0x46d1c2 */
	{ DWORD v_ = 0x4c5964u; m->esp -= 4; M32(m->esp) = v_; }	/* 46d1ae: push 0x4c5964 */
	{ DWORD v_ = 0xa1f0f0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46d1b3: push 0xa1f0f0 */
	m->esp -= 4; M32(m->esp) = 0x46d1bdu; native_call(m, 0x46c710u);	/* 46d1b8: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46d1bd: add esp, 8 */
	goto L_46d216;	/* 46d1c0: jmp 0x46d216 */
L_46d1c2:
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46d1c2: test edi, edi */
	if (m->zf || m->sf != m->of) goto L_46d216;	/* 46d1c4: jle 0x46d216 */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 46d1c6: mov eax, dword ptr [esp + 0x10] */
	m->ecx = (DWORD)(m->esp + 0x25u);	/* 46d1ca: lea ecx, [esp + 0x25] */
	m->esi = m->edi;	/* 46d1ce: mov esi, edi */
L_46d1d0:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x1u))) & 0xff) << 0);	/* 46d1d0: mov dl, byte ptr [ecx + 1] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46d1d3: add ecx, 3 */
	M8((DWORD)(m->eax + 0xfffffffeu)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 46d1d6: mov byte ptr [eax - 2], dl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0xfffffffdu))) & 0xff) << 0);	/* 46d1d9: mov dl, byte ptr [ecx - 3] */
	M8((DWORD)(m->eax + 0xffffffffu)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 46d1dc: mov byte ptr [eax - 1], dl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0xfffffffcu))) & 0xff) << 0);	/* 46d1df: mov dl, byte ptr [ecx - 4] */
	M8((DWORD)(m->eax + 0x0u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 46d1e2: mov byte ptr [eax], dl */
	M8((DWORD)(m->eax + 0x1u)) = (BYTE)(0xffu);	/* 46d1e4: mov byte ptr [eax + 1], 0xff */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46d1e8: add eax, 4 */
	{ DWORD a_ = m->esi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->esi = r_; }	/* 46d1eb: dec esi */
	if (!m->zf) goto L_46d1d0;	/* 46d1ec: jne 0x46d1d0 */
	goto L_46d216;	/* 46d1ee: jmp 0x46d216 */
L_46d1f0:
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46d1f0: test edi, edi */
	if (m->zf || m->sf != m->of) goto L_46d216;	/* 46d1f2: jle 0x46d216 */
	m->ecx = m->esi;	/* 46d1f4: mov ecx, esi */
	m->eax = (DWORD)(m->esp + 0x25u);	/* 46d1f6: lea eax, [esp + 0x25] */
	m->esi = m->edi;	/* 46d1fa: mov esi, edi */
L_46d1fc:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 46d1fc: mov dl, byte ptr [eax + 1] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46d1ff: add eax, 3 */
	M8((DWORD)(m->ecx + 0xfffffffeu)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 46d202: mov byte ptr [ecx - 2], dl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0xfffffffdu))) & 0xff) << 0);	/* 46d205: mov dl, byte ptr [eax - 3] */
	M8((DWORD)(m->ecx + 0xffffffffu)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 46d208: mov byte ptr [ecx - 1], dl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0xfffffffcu))) & 0xff) << 0);	/* 46d20b: mov dl, byte ptr [eax - 4] */
	M8((DWORD)(m->ecx + 0x0u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 46d20e: mov byte ptr [ecx], dl */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46d210: add ecx, 3 */
	{ DWORD a_ = m->esi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->esi = r_; }	/* 46d213: dec esi */
	if (!m->zf) goto L_46d1fc;	/* 46d214: jne 0x46d1fc */
L_46d216:
	m->eax = M32((DWORD)(m->ebp + 0x3eu));	/* 46d216: mov eax, dword ptr [ebp + 0x3e] */
	m->ecx = M32((DWORD)(m->ebp + 0x4u));	/* 46d219: mov ecx, dword ptr [ebp + 4] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46d21c: sub eax, edi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 46d21e: push 1 */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 46d220: lea eax, [eax + eax*2] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46d223: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46d224: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46d22au; native_call(m, 0x49e91eu);	/* 46d225: call 0x49e91e */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 46d22a: mov edx, dword ptr [esp + 0x28] */
	m->esi = M32((DWORD)(m->esp + 0x1cu));	/* 46d22e: mov esi, dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 46d232: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->esi, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46d236: add esi, edx */
	M32((DWORD)(m->esp + 0x1cu)) = m->esi;	/* 46d238: mov dword ptr [esp + 0x1c], esi */
	m->esi = M32((DWORD)(m->esp + 0x20u));	/* 46d23c: mov esi, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46d240: add esp, 0xc */
	{ DWORD a_ = m->esi, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46d243: add esi, ecx */
	{ DWORD a_ = m->ebx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebx = r_; }	/* 46d245: dec ebx */
	M32((DWORD)(m->esp + 0x14u)) = m->esi;	/* 46d246: mov dword ptr [esp + 0x14], esi */
	if (!m->zf) goto L_46d184;	/* 46d24a: jne 0x46d184 */
L_46d250:
	m->edi = M32(m->esp); m->esp += 4;	/* 46d250: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46d251: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 46d252: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 46d253: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0xc14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46d254: add esp, 0xc14 */
	m->esp += 4 + 44; return;	/* 46d25a: ret 0x2c */
}

/* tex_textureFileExist (0x4557e0), lifted by tools/lift.py */
static void lift_4557e0(X86 *m)
{
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 4557e0: push -1 */
	{ DWORD v_ = 0x4a881bu; m->esp -= 4; M32(m->esp) = v_; }	/* 4557e2: push 0x4a881b */
	m->eax = M32((DWORD)&g_lift_fs0);	/* 4557e7: mov eax, dword ptr fs:[0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4557ed: push eax */
	M32((DWORD)&g_lift_fs0) = m->esp;	/* 4557ee: mov dword ptr fs:[0], esp */
	{ DWORD a_ = m->esp, b_ = 0x24cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4557f5: sub esp, 0x24c */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4557fb: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4557fc: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4557fd: push edi */
	m->ebp = m->ecx;	/* 4557fe: mov ebp, ecx */
	M32((DWORD)(m->esp + 0x10u)) = 0x4a96f8u;	/* 455800: mov dword ptr [esp + 0x10], 0x4a96f8 */
	M32((DWORD)(m->esp + 0x14u)) = 0x0u;	/* 455808: mov dword ptr [esp + 0x14], 0 */
	m->edi = M32((DWORD)(m->esp + 0x268u));	/* 455810: mov edi, dword ptr [esp + 0x268] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 455817: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45581a: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x158u);	/* 45581c: lea edx, [esp + 0x158] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 455823: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 455825: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 455827: sub edi, ecx */
	{ DWORD v_ = 0x4b12f4u; m->esp -= 4; M32(m->esp) = v_; }	/* 455829: push 0x4b12f4 */
	m->eax = m->ecx;	/* 45582e: mov eax, ecx */
	m->esi = m->edi;	/* 455830: mov esi, edi */
	m->edi = m->edx;	/* 455832: mov edi, edx */
	M32((DWORD)(m->esp + 0x264u)) = 0x0u;	/* 455834: mov dword ptr [esp + 0x264], 0 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45583f: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 455842: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 455844: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 455846: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 455849: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->esp + 0x15cu);	/* 45584b: lea ecx, [esp + 0x15c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455852: push ecx */
	m->esp -= 4; M32(m->esp) = 0x455858u; native_call(m, 0x49ec3bu);	/* 455853: call 0x49ec3b */
	m->ecx = M32((DWORD)(m->ebp + 0xc0114u));	/* 455858: mov ecx, dword ptr [ebp + 0xc0114] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45585e: add esp, 8 */
	m->eax = m->ecx;	/* 455861: mov eax, ecx */
	{ DWORD a_ = m->eax, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 455863: sub eax, 0 */
	if (m->zf) goto L_4559ee;	/* 455866: je 0x4559ee */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 45586c: dec eax */
	if (m->zf) goto L_455966;	/* 45586d: je 0x455966 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 455873: dec eax */
	if (m->zf) goto L_45588e;	/* 455874: je 0x45588e */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455876: push ecx */
	{ DWORD v_ = 0x4b400cu; m->esp -= 4; M32(m->esp) = v_; }	/* 455877: push 0x4b400c */
	{ DWORD v_ = 0xa0dff8u; m->esp -= 4; M32(m->esp) = v_; }	/* 45587c: push 0xa0dff8 */
	m->esp -= 4; M32(m->esp) = 0x455886u; native_call(m, 0x46c710u);	/* 455881: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455886: add esp, 0xc */
	goto L_455a43;	/* 455889: jmp 0x455a43 */
L_45588e:
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + 0x8u))) & 0xff) << 0);	/* 45588e: mov cl, byte ptr [ebp + 8] */
	m->eax = (DWORD)(m->ebp + 0x8u);	/* 455891: lea eax, [ebp + 8] */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 455894: test cl, cl */
	if (m->zf) goto L_4558b5;	/* 455896: je 0x4558b5 */
	m->edx = (DWORD)(m->esp + 0x158u);	/* 455898: lea edx, [esp + 0x158] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45589f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4558a0: push eax */
	m->eax = (DWORD)(m->esp + 0x60u);	/* 4558a1: lea eax, [esp + 0x60] */
	{ DWORD v_ = 0x4b4000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4558a5: push 0x4b4000 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4558aa: push eax */
	m->esp -= 4; M32(m->esp) = 0x4558b0u; native_call(m, 0x49e9ddu);	/* 4558ab: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4558b0: add esp, 0x10 */
	goto L_4558cf;	/* 4558b3: jmp 0x4558cf */
L_4558b5:
	m->ecx = (DWORD)(m->esp + 0x158u);	/* 4558b5: lea ecx, [esp + 0x158] */
	m->edx = (DWORD)(m->esp + 0x58u);	/* 4558bc: lea edx, [esp + 0x58] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4558c0: push ecx */
	{ DWORD v_ = 0x4b3ff8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4558c1: push 0x4b3ff8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4558c6: push edx */
	m->esp -= 4; M32(m->esp) = 0x4558ccu; native_call(m, 0x49e9ddu);	/* 4558c7: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4558cc: add esp, 0xc */
L_4558cf:
	m->eax = (DWORD)(m->esp + 0x58u);	/* 4558cf: lea eax, [esp + 0x58] */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 4558d3: push 0x4ad170 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4558d8: push eax */
	m->esp -= 4; M32(m->esp) = 0x4558deu; native_call(m, 0x49e9cau);	/* 4558d9: call 0x49e9ca */
	m->esi = m->eax;	/* 4558de: mov esi, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4558e0: add esp, 8 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4558e3: test esi, esi */
	if (m->zf) goto L_455a43;	/* 4558e5: je 0x455a43 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4558eb: push 0 */
	{ DWORD v_ = 0x6u; m->esp -= 4; M32(m->esp) = v_; }	/* 4558ed: push 6 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4558ef: push esi */
	m->esp -= 4; M32(m->esp) = 0x4558f5u; native_call(m, 0x49e91eu);	/* 4558f0: call 0x49e91e */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4558f5: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4558f6: push 1 */
	m->ecx = (DWORD)(m->esp + 0x20u);	/* 4558f8: lea ecx, [esp + 0x20] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4558fc: push 2 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4558fe: push ecx */
	m->esp -= 4; M32(m->esp) = 0x455904u; native_call(m, 0x49e836u);	/* 4558ff: call 0x49e836 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 455904: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 455905: push 1 */
	m->edx = (DWORD)(m->esp + 0x32u);	/* 455907: lea edx, [esp + 0x32] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 45590b: push 2 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45590d: push edx */
	m->esp -= 4; M32(m->esp) = 0x455913u; native_call(m, 0x49e836u);	/* 45590e: call 0x49e836 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 455913: push esi */
	m->esp -= 4; M32(m->esp) = 0x455919u; native_call(m, 0x49e7e0u);	/* 455914: call 0x49e7e0 */
	m->eax = (DWORD)(int)(short)(M16((DWORD)(m->esp + 0x3cu)));	/* 455919: movsx eax, word ptr [esp + 0x3c] */
	m->ecx = M32((DWORD)(m->ebp + 0xc0118u));	/* 45591e: mov ecx, dword ptr [ebp + 0xc0118] */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455924: add esp, 0x30 */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 455927: shl eax, 3 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45592a: cmp eax, ecx */
	if (!m->zf) goto L_455a43;	/* 45592c: jne 0x455a43 */
	m->ecx = (DWORD)(int)(short)(M16((DWORD)(m->esp + 0xeu)));	/* 455932: movsx ecx, word ptr [esp + 0xe] */
	m->eax = M32((DWORD)(m->ebp + 0xc011cu));	/* 455937: mov eax, dword ptr [ebp + 0xc011c] */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45593d: shl ecx, 3 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455940: cmp ecx, eax */
L_455942:
	if (!m->zf) goto L_455a43;	/* 455942: jne 0x455a43 */
L_455948:
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 455948: lea ecx, [esp + 0x10] */
	M32((DWORD)(m->esp + 0x260u)) = 0xffffffffu;	/* 45594c: mov dword ptr [esp + 0x260], 0xffffffff */
	m->esp -= 4; M32(m->esp) = 0x45595cu; native_call(m, 0x46ce60u);	/* 455957: call 0x46ce60 */
	m->eax = 0x1u;	/* 45595c: mov eax, 1 */
	goto L_455a59;	/* 455961: jmp 0x455a59 */
L_455966:
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + 0x8u))) & 0xff) << 0);	/* 455966: mov cl, byte ptr [ebp + 8] */
	m->eax = (DWORD)(m->ebp + 0x8u);	/* 455969: lea eax, [ebp + 8] */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45596c: test cl, cl */
	if (m->zf) goto L_45598d;	/* 45596e: je 0x45598d */
	m->edx = (DWORD)(m->esp + 0x158u);	/* 455970: lea edx, [esp + 0x158] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 455977: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455978: push eax */
	m->eax = (DWORD)(m->esp + 0x60u);	/* 455979: lea eax, [esp + 0x60] */
	{ DWORD v_ = 0x4b3fecu; m->esp -= 4; M32(m->esp) = v_; }	/* 45597d: push 0x4b3fec */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455982: push eax */
	m->esp -= 4; M32(m->esp) = 0x455988u; native_call(m, 0x49e9ddu);	/* 455983: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455988: add esp, 0x10 */
	goto L_4559a7;	/* 45598b: jmp 0x4559a7 */
L_45598d:
	m->ecx = (DWORD)(m->esp + 0x158u);	/* 45598d: lea ecx, [esp + 0x158] */
	m->edx = (DWORD)(m->esp + 0x58u);	/* 455994: lea edx, [esp + 0x58] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455998: push ecx */
	{ DWORD v_ = 0x4b3fe4u; m->esp -= 4; M32(m->esp) = v_; }	/* 455999: push 0x4b3fe4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45599e: push edx */
	m->esp -= 4; M32(m->esp) = 0x4559a4u; native_call(m, 0x49e9ddu);	/* 45599f: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4559a4: add esp, 0xc */
L_4559a7:
	m->eax = (DWORD)(m->esp + 0x58u);	/* 4559a7: lea eax, [esp + 0x58] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4559ab: push eax */
	m->esp -= 4; M32(m->esp) = 0x4559b1u; native_call(m, 0x46ca70u);	/* 4559ac: call 0x46ca70 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4559b1: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4559b4: test eax, eax */
	if (m->zf) goto L_455a43;	/* 4559b6: je 0x455a43 */
	m->ecx = (DWORD)(m->esp + 0x58u);	/* 4559bc: lea ecx, [esp + 0x58] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4559c0: push ecx */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 4559c1: lea ecx, [esp + 0x14] */
	m->esp -= 4; M32(m->esp) = 0x4559cau; native_call(m, 0x46cd00u);	/* 4559c5: call 0x46cd00 */
	m->esi = M32((DWORD)(m->esp + 0x4eu));	/* 4559ca: mov esi, dword ptr [esp + 0x4e] */
	m->edi = M32((DWORD)(m->esp + 0x52u));	/* 4559ce: mov edi, dword ptr [esp + 0x52] */
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 4559d2: lea ecx, [esp + 0x10] */
	m->esp -= 4; M32(m->esp) = 0x4559dbu; native_call(m, 0x46ce50u);	/* 4559d6: call 0x46ce50 */
	{ DWORD a_ = m->esi, b_ = M32((DWORD)(m->ebp + 0xc0118u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4559db: cmp esi, dword ptr [ebp + 0xc0118] */
	if (!m->zf) goto L_455a43;	/* 4559e1: jne 0x455a43 */
	{ DWORD a_ = m->edi, b_ = M32((DWORD)(m->ebp + 0xc011cu)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4559e3: cmp edi, dword ptr [ebp + 0xc011c] */
	goto L_455942;	/* 4559e9: jmp 0x455942 */
L_4559ee:
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + 0x8u))) & 0xff) << 0);	/* 4559ee: mov cl, byte ptr [ebp + 8] */
	m->eax = (DWORD)(m->ebp + 0x8u);	/* 4559f1: lea eax, [ebp + 8] */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4559f4: test cl, cl */
	if (m->zf) goto L_455a15;	/* 4559f6: je 0x455a15 */
	m->edx = (DWORD)(m->esp + 0x158u);	/* 4559f8: lea edx, [esp + 0x158] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4559ff: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455a00: push eax */
	m->eax = (DWORD)(m->esp + 0x60u);	/* 455a01: lea eax, [esp + 0x60] */
	{ DWORD v_ = 0x4b3fdcu; m->esp -= 4; M32(m->esp) = v_; }	/* 455a05: push 0x4b3fdc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455a0a: push eax */
	m->esp -= 4; M32(m->esp) = 0x455a10u; native_call(m, 0x49e9ddu);	/* 455a0b: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455a10: add esp, 0x10 */
	goto L_455a2f;	/* 455a13: jmp 0x455a2f */
L_455a15:
	m->ecx = (DWORD)(m->esp + 0x158u);	/* 455a15: lea ecx, [esp + 0x158] */
	m->edx = (DWORD)(m->esp + 0x58u);	/* 455a1c: lea edx, [esp + 0x58] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455a20: push ecx */
	{ DWORD v_ = 0x4b3fd8u; m->esp -= 4; M32(m->esp) = v_; }	/* 455a21: push 0x4b3fd8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 455a26: push edx */
	m->esp -= 4; M32(m->esp) = 0x455a2cu; native_call(m, 0x49e9ddu);	/* 455a27: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455a2c: add esp, 0xc */
L_455a2f:
	m->eax = (DWORD)(m->esp + 0x58u);	/* 455a2f: lea eax, [esp + 0x58] */
	m->ecx = m->ebp;	/* 455a33: mov ecx, ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455a35: push eax */
	m->esp -= 4; M32(m->esp) = 0x455a3bu; native_call(m, 0x4554c0u);	/* 455a36: call 0x4554c0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 455a3b: test eax, eax */
	if (m->sf == m->of) goto L_455948;	/* 455a3d: jge 0x455948 */
L_455a43:
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 455a43: lea ecx, [esp + 0x10] */
	M32((DWORD)(m->esp + 0x260u)) = 0xffffffffu;	/* 455a47: mov dword ptr [esp + 0x260], 0xffffffff */
	m->esp -= 4; M32(m->esp) = 0x455a57u; native_call(m, 0x46ce60u);	/* 455a52: call 0x46ce60 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 455a57: xor eax, eax */
L_455a59:
	m->ecx = M32((DWORD)(m->esp + 0x258u));	/* 455a59: mov ecx, dword ptr [esp + 0x258] */
	m->edi = M32(m->esp); m->esp += 4;	/* 455a60: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 455a61: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 455a62: pop ebp */
	M32((DWORD)&g_lift_fs0) = m->ecx;	/* 455a63: mov dword ptr fs:[0], ecx */
	{ DWORD a_ = m->esp, b_ = 0x258u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455a6a: add esp, 0x258 */
	m->esp += 4 + 4; return;	/* 455a70: ret 4 */
}

/* tex_initBy (0x455080), lifted by tools/lift.py */
static void lift_455080(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x200u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455080: sub esp, 0x200 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 455086: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 455087: push ebp */
	m->ebp = m->ecx;	/* 455088: mov ebp, ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45508a: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45508b: push edi */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x4u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45508c: cmp dword ptr [ebp + 4], 1 */
	if (!m->zf) goto L_4550a4;	/* 455090: jne 0x4550a4 */
	{ DWORD v_ = 0x4b3f5cu; m->esp -= 4; M32(m->esp) = v_; }	/* 455092: push 0x4b3f5c */
	{ DWORD v_ = 0xa0dff8u; m->esp -= 4; M32(m->esp) = v_; }	/* 455097: push 0xa0dff8 */
	m->esp -= 4; M32(m->esp) = 0x4550a1u; native_call(m, 0x46c710u);	/* 45509c: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4550a1: add esp, 8 */
L_4550a4:
	m->edi = M32((DWORD)(m->esp + 0x214u));	/* 4550a4: mov edi, dword ptr [esp + 0x214] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4550ab: test edi, edi */
	if (m->zf) goto L_455109;	/* 4550ad: je 0x455109 */
	m->esi = 0x4b1304u;	/* 4550af: mov esi, 0x4b1304 */
	m->eax = m->edi;	/* 4550b4: mov eax, edi */
L_4550b6:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 4550b6: mov dl, byte ptr [eax] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 4550b8: mov bl, byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4550ba: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4550bc: cmp dl, bl */
	if (!m->zf) goto L_4550de;	/* 4550be: jne 0x4550de */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4550c0: test cl, cl */
	if (m->zf) goto L_4550da;	/* 4550c2: je 0x4550da */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 4550c4: mov dl, byte ptr [eax + 1] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 4550c7: mov bl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4550ca: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4550cc: cmp dl, bl */
	if (!m->zf) goto L_4550de;	/* 4550ce: jne 0x4550de */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4550d0: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4550d3: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4550d6: test cl, cl */
	if (!m->zf) goto L_4550b6;	/* 4550d8: jne 0x4550b6 */
L_4550da:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4550da: xor eax, eax */
	goto L_4550e3;	/* 4550dc: jmp 0x4550e3 */
L_4550de:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4550de: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4550e0: sbb eax, -1 */
L_4550e3:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4550e3: test eax, eax */
	if (m->zf) goto L_455109;	/* 4550e5: je 0x455109 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4550e7: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4550ea: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4550ec: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4550ee: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4550f0: sub edi, ecx */
	m->ebx = (DWORD)(m->ebp + 0x8u);	/* 4550f2: lea ebx, [ebp + 8] */
	m->eax = m->ecx;	/* 4550f5: mov eax, ecx */
	m->esi = m->edi;	/* 4550f7: mov esi, edi */
	m->edi = m->ebx;	/* 4550f9: mov edi, ebx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4550fb: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4550fe: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 455100: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 455102: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 455105: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_45510f;	/* 455107: jmp 0x45510f */
L_455109:
	m->ebx = (DWORD)(m->ebp + 0x8u);	/* 455109: lea ebx, [ebp + 8] */
	M8((DWORD)(m->ebx + 0x0u)) = (BYTE)(0x0u);	/* 45510c: mov byte ptr [ebx], 0 */
L_45510f:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45510f: push ebx */
	m->esp -= 4; M32(m->esp) = 0x455115u; native_call(m, 0x46cb60u);	/* 455110: call 0x46cb60 */
	m->esi = M32((DWORD)(m->esp + 0x22cu));	/* 455115: mov esi, dword ptr [esp + 0x22c] */
	m->ecx = M32((DWORD)(m->esp + 0x220u));	/* 45511c: mov ecx, dword ptr [esp + 0x220] */
	m->edx = M32((DWORD)(m->esp + 0x224u));	/* 455123: mov edx, dword ptr [esp + 0x224] */
	m->eax = M32((DWORD)(m->esp + 0x228u));	/* 45512a: mov eax, dword ptr [esp + 0x228] */
	M32((DWORD)(m->ebp + 0xc0124u)) = m->esi;	/* 455131: mov dword ptr [ebp + 0xc0124], esi */
	m->esi = M32((DWORD)(m->esp + 0x230u));	/* 455137: mov esi, dword ptr [esp + 0x230] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 45513e: xor edi, edi */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455140: add esp, 4 */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455143: cmp ecx, edi */
	M32((DWORD)(m->ebp + 0xc0114u)) = m->ecx;	/* 455145: mov dword ptr [ebp + 0xc0114], ecx */
	M32((DWORD)(m->ebp + 0xc0118u)) = m->edx;	/* 45514b: mov dword ptr [ebp + 0xc0118], edx */
	M32((DWORD)(m->ebp + 0xc011cu)) = m->eax;	/* 455151: mov dword ptr [ebp + 0xc011c], eax */
	M32((DWORD)(m->ebp + 0xc0120u)) = m->esi;	/* 455157: mov dword ptr [ebp + 0xc0120], esi */
	if (!m->zf) goto L_45539f;	/* 45515d: jne 0x45539f */
	{ DWORD a_ = m->edx, b_ = 0x40u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455163: cmp edx, 0x40 */
	if (!m->zf) goto L_45519b;	/* 455166: jne 0x45519b */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455168: cmp eax, edx */
	if (!m->zf) goto L_4552ac;	/* 45516a: jne 0x4552ac */
	m->edi = 0x4b3f54u;	/* 455170: mov edi, 0x4b3f54 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 455175: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 455178: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 45517a: lea edx, [esp + 0x10] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 45517e: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 455180: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 455182: sub edi, ecx */
	m->eax = m->ecx;	/* 455184: mov eax, ecx */
	m->esi = m->edi;	/* 455186: mov esi, edi */
	m->edi = m->edx;	/* 455188: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45518a: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 45518d: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 45518f: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 455191: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 455194: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_4552c0;	/* 455196: jmp 0x4552c0 */
L_45519b:
	{ DWORD a_ = m->edx, b_ = 0x80u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45519b: cmp edx, 0x80 */
	if (!m->zf) goto L_4551d3;	/* 4551a1: jne 0x4551d3 */
	{ DWORD a_ = m->eax, b_ = 0x40u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4551a3: cmp eax, 0x40 */
	if (!m->zf) goto L_455213;	/* 4551a6: jne 0x455213 */
	m->edi = 0x4b3f4cu;	/* 4551a8: mov edi, 0x4b3f4c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4551ad: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4551b0: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 4551b2: lea edx, [esp + 0x10] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4551b6: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4551b8: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4551ba: sub edi, ecx */
	m->eax = m->ecx;	/* 4551bc: mov eax, ecx */
	m->esi = m->edi;	/* 4551be: mov esi, edi */
	m->edi = m->edx;	/* 4551c0: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4551c2: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4551c5: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4551c7: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4551c9: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4551cc: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_4552c0;	/* 4551ce: jmp 0x4552c0 */
L_4551d3:
	{ DWORD a_ = m->edx, b_ = 0x100u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4551d3: cmp edx, 0x100 */
	if (!m->zf) goto L_45520b;	/* 4551d9: jne 0x45520b */
	{ DWORD a_ = m->eax, b_ = 0x40u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4551db: cmp eax, 0x40 */
	if (!m->zf) goto L_45524e;	/* 4551de: jne 0x45524e */
	m->edi = 0x4b3f44u;	/* 4551e0: mov edi, 0x4b3f44 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4551e5: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4551e8: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 4551ea: lea edx, [esp + 0x10] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4551ee: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4551f0: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4551f2: sub edi, ecx */
	m->eax = m->ecx;	/* 4551f4: mov eax, ecx */
	m->esi = m->edi;	/* 4551f6: mov esi, edi */
	m->edi = m->edx;	/* 4551f8: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4551fa: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4551fd: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4551ff: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 455201: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 455204: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_4552c0;	/* 455206: jmp 0x4552c0 */
L_45520b:
	{ DWORD a_ = m->edx, b_ = 0x80u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45520b: cmp edx, 0x80 */
	if (!m->zf) goto L_455246;	/* 455211: jne 0x455246 */
L_455213:
	{ DWORD a_ = m->eax, b_ = 0x80u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455213: cmp eax, 0x80 */
	if (!m->zf) goto L_4552ac;	/* 455218: jne 0x4552ac */
	m->edi = 0x4b3f3cu;	/* 45521e: mov edi, 0x4b3f3c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 455223: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 455226: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 455228: lea edx, [esp + 0x10] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 45522c: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 45522e: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 455230: sub edi, ecx */
	m->eax = m->ecx;	/* 455232: mov eax, ecx */
	m->esi = m->edi;	/* 455234: mov esi, edi */
	m->edi = m->edx;	/* 455236: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 455238: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 45523b: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 45523d: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 45523f: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 455242: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_4552c0;	/* 455244: jmp 0x4552c0 */
L_455246:
	{ DWORD a_ = m->edx, b_ = 0x100u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455246: cmp edx, 0x100 */
	if (!m->zf) goto L_4552ac;	/* 45524c: jne 0x4552ac */
L_45524e:
	{ DWORD a_ = m->eax, b_ = 0x80u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45524e: cmp eax, 0x80 */
	if (!m->zf) goto L_45527d;	/* 455253: jne 0x45527d */
	m->edi = 0x4b3f34u;	/* 455255: mov edi, 0x4b3f34 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 45525a: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45525d: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 45525f: lea edx, [esp + 0x10] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 455263: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 455265: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 455267: sub edi, ecx */
	m->eax = m->ecx;	/* 455269: mov eax, ecx */
	m->esi = m->edi;	/* 45526b: mov esi, edi */
	m->edi = m->edx;	/* 45526d: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45526f: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 455272: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 455274: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 455276: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 455279: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_4552c0;	/* 45527b: jmp 0x4552c0 */
L_45527d:
	{ DWORD a_ = m->eax, b_ = 0x100u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45527d: cmp eax, 0x100 */
	if (!m->zf) goto L_4552ac;	/* 455282: jne 0x4552ac */
	m->edi = 0x4b3f2cu;	/* 455284: mov edi, 0x4b3f2c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 455289: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45528c: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 45528e: lea edx, [esp + 0x10] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 455292: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 455294: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 455296: sub edi, ecx */
	m->eax = m->ecx;	/* 455298: mov eax, ecx */
	m->esi = m->edi;	/* 45529a: mov esi, edi */
	m->edi = m->edx;	/* 45529c: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45529e: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4552a1: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4552a3: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4552a5: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4552a8: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_4552c0;	/* 4552aa: jmp 0x4552c0 */
L_4552ac:
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4552ac: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4552ad: push edx */
	m->ecx = (DWORD)(m->esp + 0x18u);	/* 4552ae: lea ecx, [esp + 0x18] */
	{ DWORD v_ = 0x4b3f20u; m->esp -= 4; M32(m->esp) = v_; }	/* 4552b2: push 0x4b3f20 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4552b7: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4552bdu; native_call(m, 0x49e9ddu);	/* 4552b8: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4552bd: add esp, 0x10 */
L_4552c0:
	{ DWORD a_ = M8((DWORD)(m->ebx + 0x0u)), b_ = 0x0u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4552c0: cmp byte ptr [ebx], 0 */
	if (m->zf) goto L_4552e2;	/* 4552c3: je 0x4552e2 */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 4552c5: lea edx, [esp + 0x10] */
	m->eax = (DWORD)(m->esp + 0x110u);	/* 4552c9: lea eax, [esp + 0x110] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4552d0: push edx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4552d1: push ebx */
	{ DWORD v_ = 0x4b3f10u; m->esp -= 4; M32(m->esp) = v_; }	/* 4552d2: push 0x4b3f10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4552d7: push eax */
	m->esp -= 4; M32(m->esp) = 0x4552ddu; native_call(m, 0x49e9ddu);	/* 4552d8: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4552dd: add esp, 0x10 */
	goto L_4552fc;	/* 4552e0: jmp 0x4552fc */
L_4552e2:
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 4552e2: lea ecx, [esp + 0x10] */
	m->edx = (DWORD)(m->esp + 0x110u);	/* 4552e6: lea edx, [esp + 0x110] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4552ed: push ecx */
	{ DWORD v_ = 0x4b3f04u; m->esp -= 4; M32(m->esp) = v_; }	/* 4552ee: push 0x4b3f04 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4552f3: push edx */
	m->esp -= 4; M32(m->esp) = 0x4552f9u; native_call(m, 0x49e9ddu);	/* 4552f4: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4552f9: add esp, 0xc */
L_4552fc:
	m->eax = (DWORD)(m->esp + 0x110u);	/* 4552fc: lea eax, [esp + 0x110] */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 455303: push 0x4ad170 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455308: push eax */
	m->esp -= 4; M32(m->esp) = 0x45530eu; native_call(m, 0x49e9cau);	/* 455309: call 0x49e9ca */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 45530e: xor edi, edi */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455310: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455313: cmp eax, edi */
	M32((DWORD)(m->ebp + 0x110u)) = m->eax;	/* 455315: mov dword ptr [ebp + 0x110], eax */
	if (!m->zf) goto L_455337;	/* 45531b: jne 0x455337 */
	m->ecx = (DWORD)(m->esp + 0x110u);	/* 45531d: lea ecx, [esp + 0x110] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455324: push ecx */
	{ DWORD v_ = 0x4b3ee4u; m->esp -= 4; M32(m->esp) = v_; }	/* 455325: push 0x4b3ee4 */
	{ DWORD v_ = 0xa0dff8u; m->esp -= 4; M32(m->esp) = v_; }	/* 45532a: push 0xa0dff8 */
	m->esp -= 4; M32(m->esp) = 0x455334u; native_call(m, 0x46c710u);	/* 45532f: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455334: add esp, 0xc */
L_455337:
	m->edx = M32((DWORD)(m->ebp + 0x110u));	/* 455337: mov edx, dword ptr [ebp + 0x110] */
	m->esi = (DWORD)(m->ebp + 0x108u);	/* 45533d: lea esi, [ebp + 0x108] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 455343: push edx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 455344: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 455346: push 4 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 455348: push esi */
	m->esp -= 4; M32(m->esp) = 0x45534eu; native_call(m, 0x49e836u);	/* 455349: call 0x49e836 */
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 45534e: mov eax, dword ptr [esi] */
	m->ecx = m->eax;	/* 455350: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 455352: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 455355: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 455357: shl ecx, 2 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45535a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x455360u; native_call(m, 0x49f1aau);	/* 45535b: call 0x49f1aa */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455360: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455363: cmp eax, edi */
	M32((DWORD)(m->ebp + 0x10cu)) = m->eax;	/* 455365: mov dword ptr [ebp + 0x10c], eax */
	if (!m->zf) goto L_455382;	/* 45536b: jne 0x455382 */
	m->edx = M32((DWORD)(m->esi + 0x0u));	/* 45536d: mov edx, dword ptr [esi] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45536f: push edx */
	{ DWORD v_ = 0x4b3eb4u; m->esp -= 4; M32(m->esp) = v_; }	/* 455370: push 0x4b3eb4 */
	{ DWORD v_ = 0xa0dff8u; m->esp -= 4; M32(m->esp) = v_; }	/* 455375: push 0xa0dff8 */
	m->esp -= 4; M32(m->esp) = 0x45537fu; native_call(m, 0x46c710u);	/* 45537a: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45537f: add esp, 0xc */
L_455382:
	m->eax = M32((DWORD)(m->ebp + 0x110u));	/* 455382: mov eax, dword ptr [ebp + 0x110] */
	m->ecx = M32((DWORD)(m->esi + 0x0u));	/* 455388: mov ecx, dword ptr [esi] */
	m->edx = M32((DWORD)(m->ebp + 0x10cu));	/* 45538a: mov edx, dword ptr [ebp + 0x10c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455390: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455391: push ecx */
	{ DWORD v_ = 0x44u; m->esp -= 4; M32(m->esp) = v_; }	/* 455392: push 0x44 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 455394: push edx */
	m->esp -= 4; M32(m->esp) = 0x45539au; native_call(m, 0x49e836u);	/* 455395: call 0x49e836 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45539a: add esp, 0x10 */
	goto L_4553b1;	/* 45539d: jmp 0x4553b1 */
L_45539f:
	M32((DWORD)(m->ebp + 0x108u)) = m->edi;	/* 45539f: mov dword ptr [ebp + 0x108], edi */
	M32((DWORD)(m->ebp + 0x10cu)) = m->edi;	/* 4553a5: mov dword ptr [ebp + 0x10c], edi */
	M32((DWORD)(m->ebp + 0x110u)) = m->edi;	/* 4553ab: mov dword ptr [ebp + 0x110], edi */
L_4553b1:
	m->eax = M32((DWORD)(m->esp + 0x218u));	/* 4553b1: mov eax, dword ptr [esp + 0x218] */
	M32((DWORD)(m->ebp + 0xcd128u)) = m->edi;	/* 4553b8: mov dword ptr [ebp + 0xcd128], edi */
	{ DWORD a_ = m->eax, b_ = 0x200u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4553be: cmp eax, 0x200 */
	M32((DWORD)(m->ebp + 0xcd130u)) = m->eax;	/* 4553c3: mov dword ptr [ebp + 0xcd130], eax */
	if (m->zf || m->sf != m->of) goto L_4553d5;	/* 4553c9: jle 0x4553d5 */
	M32((DWORD)(m->ebp + 0xcd130u)) = 0x200u;	/* 4553cb: mov dword ptr [ebp + 0xcd130], 0x200 */
L_4553d5:
	m->eax = M32((DWORD)(m->ebp + 0xcd130u));	/* 4553d5: mov eax, dword ptr [ebp + 0xcd130] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4553db: lea eax, [eax + eax*4] */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4553de: shl eax, 2 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4553e1: push eax */
	m->esp -= 4; M32(m->esp) = 0x4553e7u; native_call(m, 0x49f1aau);	/* 4553e2: call 0x49f1aa */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4553e7: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4553ea: cmp eax, edi */
	M32((DWORD)(m->ebp + 0xcd12cu)) = m->eax;	/* 4553ec: mov dword ptr [ebp + 0xcd12c], eax */
	if (!m->zf) goto L_45540d;	/* 4553f2: jne 0x45540d */
	m->ecx = M32((DWORD)(m->ebp + 0xcd130u));	/* 4553f4: mov ecx, dword ptr [ebp + 0xcd130] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4553fa: push ecx */
	{ DWORD v_ = 0x4b3e84u; m->esp -= 4; M32(m->esp) = v_; }	/* 4553fb: push 0x4b3e84 */
	{ DWORD v_ = 0xa0dff8u; m->esp -= 4; M32(m->esp) = v_; }	/* 455400: push 0xa0dff8 */
	m->esp -= 4; M32(m->esp) = 0x45540au; native_call(m, 0x46c710u);	/* 455405: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45540a: add esp, 0xc */
L_45540d:
	m->eax = M32((DWORD)(m->ebp + 0xcd130u));	/* 45540d: mov eax, dword ptr [ebp + 0xcd130] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 455413: xor esi, esi */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455415: cmp eax, esi */
	if (m->zf || m->sf != m->of) goto L_455489;	/* 455417: jle 0x455489 */
L_455419:
	m->edx = M32((DWORD)(m->ebp + 0xcd12cu));	/* 455419: mov edx, dword ptr [ebp + 0xcd12c] */
	M32((DWORD)(m->esi + m->edx*1 + 0x0u)) = m->edi;	/* 45541f: mov dword ptr [esi + edx], edi */
	m->eax = M32((DWORD)(m->ebp + 0xcd12cu));	/* 455422: mov eax, dword ptr [ebp + 0xcd12c] */
	M32((DWORD)(m->esi + m->eax*1 + 0x4u)) = 0xffffffffu;	/* 455428: mov dword ptr [esi + eax + 4], 0xffffffff */
	m->ecx = M32((DWORD)(m->ebp + 0xcd12cu));	/* 455430: mov ecx, dword ptr [ebp + 0xcd12c] */
	m->edx = (DWORD)(m->esi + m->ecx*1 + 0x8u);	/* 455436: lea edx, [esi + ecx + 8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45543a: push edx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45543b: push 1 */
	m->esp -= 4; M32(m->esp) = 0x455443u; native_call(m, M32(0x4a925cu));	/* 45543d: call dword ptr [0x4a925c] */
	m->ecx = M32((DWORD)(m->ebp + 0xcd130u));	/* 455443: mov ecx, dword ptr [ebp + 0xcd130] */
	m->ebx = M32((DWORD)(m->ebp + 0xcd12cu));	/* 455449: mov ebx, dword ptr [ebp + 0xcd12c] */
	{ DWORD a_ = m->esi, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 45544f: add esi, 0x14 */
	m->eax = (DWORD)(m->ecx + m->edi*1 + 0xffffffffu);	/* 455452: lea eax, [ecx + edi - 1] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 455456: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 455457: idiv ecx */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 455459: inc edi */
	m->eax = (DWORD)(m->edx + m->edx*4 + 0x0u);	/* 45545a: lea eax, [edx + edx*4] */
	m->ecx = (DWORD)(m->ebx + m->eax*4 + 0x0u);	/* 45545d: lea ecx, [ebx + eax*4] */
	m->eax = m->edi;	/* 455460: mov eax, edi */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 455462: cdq  */
	M32((DWORD)(m->esi + m->ebx*1 + 0xfffffff8u)) = m->ecx;	/* 455463: mov dword ptr [esi + ebx - 8], ecx */
	m->ecx = M32((DWORD)(m->ebp + 0xcd12cu));	/* 455467: mov ecx, dword ptr [ebp + 0xcd12c] */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)M32((DWORD)(m->ebp + 0xcd130u)); m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 45546d: idiv dword ptr [ebp + 0xcd130] */
	m->edx = (DWORD)(m->edx + m->edx*4 + 0x0u);	/* 455473: lea edx, [edx + edx*4] */
	m->eax = (DWORD)(m->ecx + m->edx*4 + 0x0u);	/* 455476: lea eax, [ecx + edx*4] */
	M32((DWORD)(m->esi + m->ecx*1 + 0xfffffffcu)) = m->eax;	/* 455479: mov dword ptr [esi + ecx - 4], eax */
	m->eax = M32((DWORD)(m->ebp + 0xcd130u));	/* 45547d: mov eax, dword ptr [ebp + 0xcd130] */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455483: cmp edi, eax */
	if (m->sf != m->of) goto L_455419;	/* 455485: jl 0x455419 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 455487: xor esi, esi */
L_455489:
	m->ecx = M32((DWORD)(m->ebp + 0xcd12cu));	/* 455489: mov ecx, dword ptr [ebp + 0xcd12c] */
	M32((DWORD)(m->ebp + 0xcd138u)) = m->esi;	/* 45548f: mov dword ptr [ebp + 0xcd138], esi */
	M32((DWORD)(m->ebp + 0xcd13cu)) = m->esi;	/* 455495: mov dword ptr [ebp + 0xcd13c], esi */
	M32((DWORD)(m->ebp + 0xcd140u)) = m->esi;	/* 45549b: mov dword ptr [ebp + 0xcd140], esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 4554a1: pop edi */
	M32((DWORD)(m->ebp + 0xcd134u)) = m->ecx;	/* 4554a2: mov dword ptr [ebp + 0xcd134], ecx */
	M32((DWORD)(m->ebp + 0x4u)) = 0x1u;	/* 4554a8: mov dword ptr [ebp + 4], 1 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4554af: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4554b0: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4554b1: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x200u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4554b2: add esp, 0x200 */
	m->esp += 4 + 28; return;	/* 4554b8: ret 0x1c */
}

/* shape_initBy (0x466a60), lifted by tools/lift.py */
static void lift_466a60(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 466a60: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 466a61: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 466a62: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 466a63: push edi */
	m->ebp = m->ecx;	/* 466a64: mov ebp, ecx */
	m->esp -= 4; M32(m->esp) = 0x466a6bu; native_call(m, 0x466a30u);	/* 466a66: call 0x466a30 */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 466a6b: mov edi, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 466a6f: xor ebx, ebx */
	{ DWORD a_ = m->edi, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 466a71: cmp edi, ebx */
	if (m->zf) goto L_466acd;	/* 466a73: je 0x466acd */
	m->esi = 0x4b1304u;	/* 466a75: mov esi, 0x4b1304 */
	m->eax = m->edi;	/* 466a7a: mov eax, edi */
L_466a7c:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 466a7c: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 466a7e: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 466a80: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_466aa0;	/* 466a82: jne 0x466aa0 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 466a84: test cl, cl */
	if (m->zf) goto L_466a9c;	/* 466a86: je 0x466a9c */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 466a88: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 466a8b: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 466a8d: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_466aa0;	/* 466a90: jne 0x466aa0 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 466a92: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 466a95: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 466a98: test cl, cl */
	if (!m->zf) goto L_466a7c;	/* 466a9a: jne 0x466a7c */
L_466a9c:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 466a9c: xor eax, eax */
	goto L_466aa5;	/* 466a9e: jmp 0x466aa5 */
L_466aa0:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 466aa0: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 466aa2: sbb eax, -1 */
L_466aa5:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 466aa5: cmp eax, ebx */
	if (m->zf) goto L_466acd;	/* 466aa7: je 0x466acd */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 466aa9: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 466aac: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 466aae: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 466ab0: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 466ab2: sub edi, ecx */
	m->edx = (DWORD)(m->ebp + 0x10u);	/* 466ab4: lea edx, [ebp + 0x10] */
	m->eax = m->ecx;	/* 466ab7: mov eax, ecx */
	m->esi = m->edi;	/* 466ab9: mov esi, edi */
	m->edi = m->edx;	/* 466abb: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 466abd: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 466ac0: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 466ac2: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 466ac4: and ecx, 3 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 466ac7: xor ebx, ebx */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 466ac9: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_466ad3;	/* 466acb: jmp 0x466ad3 */
L_466acd:
	m->edx = (DWORD)(m->ebp + 0x10u);	/* 466acd: lea edx, [ebp + 0x10] */
	M8((DWORD)(m->edx + 0x0u)) = (BYTE)(0x0u);	/* 466ad0: mov byte ptr [edx], 0 */
L_466ad3:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 466ad3: push edx */
	m->esp -= 4; M32(m->esp) = 0x466ad9u; native_call(m, 0x46cb60u);	/* 466ad4: call 0x46cb60 */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 466ad9: mov eax, dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 466add: mov ecx, dword ptr [esp + 0x20] */
	m->esi = M32((DWORD)(m->esp + 0x28u));	/* 466ae1: mov esi, dword ptr [esp + 0x28] */
	M32((DWORD)(m->ebp + 0x110u)) = m->ecx;	/* 466ae5: mov dword ptr [ebp + 0x110], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 466aeb: mov ecx, dword ptr [esp + 0x24] */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 466aef: lea edx, [eax + eax*8] */
	M32((DWORD)(m->ebp + 0x114u)) = m->eax;	/* 466af2: mov dword ptr [ebp + 0x114], eax */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 466af8: add esp, 4 */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 466afb: lea eax, [eax + edx*2] */
	{ DWORD a_ = m->esi, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 466afe: cmp esi, ebx */
	M32((DWORD)(m->ebp + 0x124u)) = m->ecx;	/* 466b00: mov dword ptr [ebp + 0x124], ecx */
	m->eax = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 466b06: lea eax, [ecx + eax*8] */
	M32((DWORD)(m->ebp + 0x4u)) = m->eax;	/* 466b09: mov dword ptr [ebp + 4], eax */
	if (!m->zf) goto L_466b3d;	/* 466b0c: jne 0x466b3d */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 466b0e: push eax */
	m->esp -= 4; M32(m->esp) = 0x466b14u; native_call(m, 0x49f1aau);	/* 466b0f: call 0x49f1aa */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 466b14: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 466b17: cmp eax, ebx */
	M32((DWORD)(m->ebp + 0x8u)) = m->eax;	/* 466b19: mov dword ptr [ebp + 8], eax */
	if (!m->zf) goto L_466b34;	/* 466b1c: jne 0x466b34 */
	m->ecx = M32((DWORD)(m->ebp + 0x4u));	/* 466b1e: mov ecx, dword ptr [ebp + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 466b21: push ecx */
	{ DWORD v_ = 0x4c4cecu; m->esp -= 4; M32(m->esp) = v_; }	/* 466b22: push 0x4c4cec */
	{ DWORD v_ = 0xa0e788u; m->esp -= 4; M32(m->esp) = v_; }	/* 466b27: push 0xa0e788 */
	m->esp -= 4; M32(m->esp) = 0x466b31u; native_call(m, 0x46c710u);	/* 466b2c: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 466b31: add esp, 0xc */
L_466b34:
	M32((DWORD)(m->ebp + 0xcu)) = 0x1u;	/* 466b34: mov dword ptr [ebp + 0xc], 1 */
	goto L_466b5c;	/* 466b3b: jmp 0x466b5c */
L_466b3d:
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 466b3d: mov ecx, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 466b41: cmp ecx, eax */
	if (m->sf == m->of) goto L_466b59;	/* 466b43: jge 0x466b59 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 466b45: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 466b46: push eax */
	{ DWORD v_ = 0x4c4cbcu; m->esp -= 4; M32(m->esp) = v_; }	/* 466b47: push 0x4c4cbc */
	{ DWORD v_ = 0xa0e788u; m->esp -= 4; M32(m->esp) = v_; }	/* 466b4c: push 0xa0e788 */
	m->esp -= 4; M32(m->esp) = 0x466b56u; native_call(m, 0x46c710u);	/* 466b51: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 466b56: add esp, 0x10 */
L_466b59:
	M32((DWORD)(m->ebp + 0x8u)) = m->esi;	/* 466b59: mov dword ptr [ebp + 8], esi */
L_466b5c:
	m->eax = M32((DWORD)(m->ebp + 0x114u));	/* 466b5c: mov eax, dword ptr [ebp + 0x114] */
	m->ecx = M32((DWORD)(m->ebp + 0x8u));	/* 466b62: mov ecx, dword ptr [ebp + 8] */
	M32((DWORD)(m->ebp + 0x118u)) = m->ecx;	/* 466b65: mov dword ptr [ebp + 0x118], ecx */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 466b6b: lea edx, [eax + eax*8] */
	m->esi = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 466b6e: lea esi, [eax + edx*2] */
	{ DWORD a_ = m->esi, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 466b71: shl esi, 2 */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 466b74: add ecx, esi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 466b76: add esi, esi */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 466b78: cmp eax, ebx */
	M32((DWORD)(m->ebp + 0x11cu)) = m->ecx;	/* 466b7a: mov dword ptr [ebp + 0x11c], ecx */
	if (m->zf || m->sf != m->of) goto L_466bae;	/* 466b80: jle 0x466bae */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 466b82: xor edi, edi */
L_466b84:
	m->ecx = M32((DWORD)(m->ebp + 0x11cu));	/* 466b84: mov ecx, dword ptr [ebp + 0x11c] */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 466b8a: add ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x466b91u; native_call(m, 0x464bb0u);	/* 466b8c: call 0x464bb0 */
	m->ecx = M32((DWORD)(m->ebp + 0x11cu));	/* 466b91: mov ecx, dword ptr [ebp + 0x11c] */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 466b97: add ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x466b9eu; native_call(m, 0x464bc0u);	/* 466b99: call 0x464bc0 */
	m->eax = M32((DWORD)(m->ebp + 0x114u));	/* 466b9e: mov eax, dword ptr [ebp + 0x114] */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 466ba4: inc ebx */
	{ DWORD a_ = m->edi, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 466ba5: add edi, 0x4c */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 466ba8: cmp ebx, eax */
	if (m->sf != m->of) goto L_466b84;	/* 466baa: jl 0x466b84 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 466bac: xor ebx, ebx */
L_466bae:
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 466bae: mov eax, dword ptr [ebp + 8] */
	m->edi = M32(m->esp); m->esp += 4;	/* 466bb1: pop edi */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 466bb2: add eax, esi */
	M8((DWORD)(m->ebp + 0x130u)) = (BYTE)(0x0u);	/* 466bb4: mov byte ptr [ebp + 0x130], 0 */
	M32((DWORD)(m->ebp + 0x128u)) = m->eax;	/* 466bbb: mov dword ptr [ebp + 0x128], eax */
	M32((DWORD)(m->ebp + 0x230u)) = m->ebx;	/* 466bc1: mov dword ptr [ebp + 0x230], ebx */
	M32((DWORD)(m->ebp + 0x234u)) = m->ebx;	/* 466bc7: mov dword ptr [ebp + 0x234], ebx */
	M32((DWORD)(m->ebp + 0x238u)) = m->ebx;	/* 466bcd: mov dword ptr [ebp + 0x238], ebx */
	M32((DWORD)(m->ebp + 0x23cu)) = m->ebx;	/* 466bd3: mov dword ptr [ebp + 0x23c], ebx */
	M32((DWORD)(m->ebp + 0x240u)) = m->ebx;	/* 466bd9: mov dword ptr [ebp + 0x240], ebx */
	M32((DWORD)(m->ebp + 0x244u)) = m->ebx;	/* 466bdf: mov dword ptr [ebp + 0x244], ebx */
	M32((DWORD)(m->ebp + 0x248u)) = m->ebx;	/* 466be5: mov dword ptr [ebp + 0x248], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 466beb: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 466bec: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 466bed: pop ebx */
	m->esp += 4 + 24; return;	/* 466bee: ret 0x18 */
}

/* skel_loadFrom_46aeb0 (0x46aeb0), lifted by tools/lift.py */
static void lift_46aeb0(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46aeb0: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46aeb1: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46aeb2: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46aeb3: push edi */
	m->ebx = m->ecx;	/* 46aeb4: mov ebx, ecx */
	m->esp -= 4; M32(m->esp) = 0x46aebbu; native_call(m, 0x46ae80u);	/* 46aeb6: call 0x46ae80 */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 46aebb: mov edi, dword ptr [esp + 0x14] */
	m->edx = (DWORD)(m->ebx + 0x10u);	/* 46aebf: lea edx, [ebx + 0x10] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46aec2: test edi, edi */
	if (!m->zf) goto L_46aecb;	/* 46aec4: jne 0x46aecb */
	m->edi = 0x4b1304u;	/* 46aec6: mov edi, 0x4b1304 */
L_46aecb:
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46aecb: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46aece: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 46aed0: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 46aed2: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46aed4: sub edi, ecx */
	m->eax = m->ecx;	/* 46aed6: mov eax, ecx */
	m->esi = m->edi;	/* 46aed8: mov esi, edi */
	m->edi = m->edx;	/* 46aeda: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46aedc: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 46aedf: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 46aee1: mov ecx, eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 46aee3: mov eax, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46aee7: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 46aeea: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 46aeec: mov ecx, dword ptr [esp + 0x1c] */
	m->esi = M32((DWORD)(m->esp + 0x24u));	/* 46aef0: mov esi, dword ptr [esp + 0x24] */
	m->edx = (DWORD)(m->eax*8 + 0x0u);	/* 46aef4: lea edx, [eax*8] */
	M32((DWORD)(m->ebx + 0x110u)) = m->ecx;	/* 46aefb: mov dword ptr [ebx + 0x110], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 46af01: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46af05: sub edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 46af07: shl edx, 4 */
	M32((DWORD)(m->ebx + 0x114u)) = m->eax;	/* 46af0a: mov dword ptr [ebx + 0x114], eax */
	M32((DWORD)(m->ebx + 0x124u)) = m->ecx;	/* 46af10: mov dword ptr [ebx + 0x124], ecx */
	m->eax = (DWORD)(m->edx + m->ecx*1 + 0x0u);	/* 46af16: lea eax, [edx + ecx] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46af19: test esi, esi */
	M32((DWORD)(m->ebx + 0x4u)) = m->eax;	/* 46af1b: mov dword ptr [ebx + 4], eax */
	if (!m->zf) goto L_46af4f;	/* 46af1e: jne 0x46af4f */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46af20: push eax */
	m->esp -= 4; M32(m->esp) = 0x46af26u; native_call(m, 0x49f1aau);	/* 46af21: call 0x49f1aa */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46af26: add esp, 4 */
	M32((DWORD)(m->ebx + 0x8u)) = m->eax;	/* 46af29: mov dword ptr [ebx + 8], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46af2c: test eax, eax */
	if (!m->zf) goto L_46af46;	/* 46af2e: jne 0x46af46 */
	m->eax = M32((DWORD)(m->ebx + 0x4u));	/* 46af30: mov eax, dword ptr [ebx + 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46af33: push eax */
	{ DWORD v_ = 0x4c4becu; m->esp -= 4; M32(m->esp) = v_; }	/* 46af34: push 0x4c4bec */
	{ DWORD v_ = 0xa0eaa0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46af39: push 0xa0eaa0 */
	m->esp -= 4; M32(m->esp) = 0x46af43u; native_call(m, 0x46c710u);	/* 46af3e: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46af43: add esp, 0xc */
L_46af46:
	M32((DWORD)(m->ebx + 0xcu)) = 0x1u;	/* 46af46: mov dword ptr [ebx + 0xc], 1 */
	goto L_46af6e;	/* 46af4d: jmp 0x46af6e */
L_46af4f:
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 46af4f: mov ecx, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46af53: cmp ecx, eax */
	if (m->sf == m->of) goto L_46af6b;	/* 46af55: jge 0x46af6b */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46af57: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46af58: push eax */
	{ DWORD v_ = 0x4c4b08u; m->esp -= 4; M32(m->esp) = v_; }	/* 46af59: push 0x4c4b08 */
	{ DWORD v_ = 0xa0eaa0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46af5e: push 0xa0eaa0 */
	m->esp -= 4; M32(m->esp) = 0x46af68u; native_call(m, 0x46c710u);	/* 46af63: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46af68: add esp, 0x10 */
L_46af6b:
	M32((DWORD)(m->ebx + 0x8u)) = m->esi;	/* 46af6b: mov dword ptr [ebx + 8], esi */
L_46af6e:
	m->eax = M32((DWORD)(m->ebx + 0x114u));	/* 46af6e: mov eax, dword ptr [ebx + 0x114] */
	m->edx = M32((DWORD)(m->ebx + 0x8u));	/* 46af74: mov edx, dword ptr [ebx + 8] */
	M32((DWORD)(m->ebx + 0x118u)) = m->edx;	/* 46af77: mov dword ptr [ebx + 0x118], edx */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 46af7d: xor edi, edi */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 46af7f: lea ecx, [eax + eax*8] */
	m->ecx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 46af82: lea ecx, [eax + ecx*2] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46af85: shl ecx, 2 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46af88: add edx, ecx */
	M32((DWORD)(m->ebx + 0x11cu)) = m->edx;	/* 46af8a: mov dword ptr [ebx + 0x11c], edx */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 46af90: lea edx, [eax + eax*8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46af93: test eax, eax */
	m->ebp = (DWORD)(m->ecx + m->edx*4 + 0x0u);	/* 46af95: lea ebp, [ecx + edx*4] */
	if (m->zf || m->sf != m->of) goto L_46afc8;	/* 46af98: jle 0x46afc8 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 46af9a: xor esi, esi */
L_46af9c:
	m->edx = M32((DWORD)(m->ebx + 0x11cu));	/* 46af9c: mov edx, dword ptr [ebx + 0x11c] */
	m->ecx = m->esi;	/* 46afa2: mov ecx, esi */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46afa4: add ecx, edx */
	m->esp -= 4; M32(m->esp) = 0x46afabu; native_call(m, 0x469980u);	/* 46afa6: call 0x469980 */
	m->eax = M32((DWORD)(m->ebx + 0x11cu));	/* 46afab: mov eax, dword ptr [ebx + 0x11c] */
	m->ecx = m->esi;	/* 46afb1: mov ecx, esi */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46afb3: add ecx, eax */
	m->esp -= 4; M32(m->esp) = 0x46afbau; native_call(m, 0x4699a0u);	/* 46afb5: call 0x4699a0 */
	m->eax = M32((DWORD)(m->ebx + 0x114u));	/* 46afba: mov eax, dword ptr [ebx + 0x114] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 46afc0: inc edi */
	{ DWORD a_ = m->esi, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46afc1: add esi, 0x24 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46afc4: cmp edi, eax */
	if (m->sf != m->of) goto L_46af9c;	/* 46afc6: jl 0x46af9c */
L_46afc8:
	m->eax = M32((DWORD)(m->ebx + 0x8u));	/* 46afc8: mov eax, dword ptr [ebx + 8] */
	m->edi = M32(m->esp); m->esp += 4;	/* 46afcb: pop edi */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 46afcc: add ebp, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 46afce: pop esi */
	M32((DWORD)(m->ebx + 0x128u)) = m->ebp;	/* 46afcf: mov dword ptr [ebx + 0x128], ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 46afd5: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 46afd6: pop ebx */
	m->esp += 4 + 24; return;	/* 46afd7: ret 0x18 */
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
