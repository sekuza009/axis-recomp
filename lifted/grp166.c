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

static void lift_496240(X86 *m);
static void lift_494930(X86 *m);

/* hud_drawRanking (0x494930), lifted by tools/lift.py */
static void lift_494930(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x128u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 494930: sub esp, 0x128 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 494936: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 494937: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 494938: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 494939: push edi */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 49493a: push 0x3e4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49493f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494944: push 0x3f800000 */
	m->ebx = m->ecx;	/* 494949: mov ebx, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49494b: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x494956u; native_call(m, M32(0x4a9228u));	/* 494950: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x80u; m->esp -= 4; M32(m->esp) = v_; }	/* 494956: push 0x80 */
	{ DWORD v_ = 0x210u; m->esp -= 4; M32(m->esp) = v_; }	/* 49495b: push 0x210 */
	{ DWORD v_ = 0x70u; m->esp -= 4; M32(m->esp) = v_; }	/* 494960: push 0x70 */
	{ DWORD v_ = 0x70u; m->esp -= 4; M32(m->esp) = v_; }	/* 494962: push 0x70 */
	m->esp -= 4; M32(m->esp) = 0x494969u; native_call(m, 0x4950a0u);	/* 494964: call 0x4950a0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494969: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49496e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494973: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494978: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x494982u; native_call(m, 0x44ad30u);	/* 49497d: call 0x44ad30 */
	m->eax = M32((DWORD)(m->ebx + 0x22e7180u));	/* 494982: mov eax, dword ptr [ebx + 0x22e7180] */
	m->ecx = (DWORD)(m->esp + 0x58u);	/* 494988: lea ecx, [esp + 0x58] */
	{ DWORD a_ = m->eax, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49498c: shl eax, 6 */
	{ DWORD a_ = m->eax, b_ = 0x4c7030u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49498f: add eax, 0x4c7030 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 494994: push eax */
	{ DWORD v_ = 0x4d0408u; m->esp -= 4; M32(m->esp) = v_; }	/* 494995: push 0x4d0408 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49499a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4949a0u; native_call(m, 0x49e9ddu);	/* 49499b: call 0x49e9dd */
	m->edx = (DWORD)(m->esp + 0x64u);	/* 4949a0: lea edx, [esp + 0x64] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 4949a4: push 0x10 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4949a6: push edx */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 4949a7: push 0x140 */
	{ DWORD v_ = 0x70u; m->esp -= 4; M32(m->esp) = v_; }	/* 4949ac: push 0x70 */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 4949ae: push 0x140 */
	m->esp -= 4; M32(m->esp) = 0x4949b8u; native_call(m, 0x44ae10u);	/* 4949b3: call 0x44ae10 */
	m->eax = M32((DWORD)(m->ebx + 0x22e7184u));	/* 4949b8: mov eax, dword ptr [ebx + 0x22e7184] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4949be: add esp, 0x40 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4949c1: cmp eax, 1 */
	m->esi = 0x8cu;	/* 4949c4: mov esi, 0x8c */
	if (!m->zf) goto L_494ccc;	/* 4949c9: jne 0x494ccc */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4949cf: push 1 */
	m->ecx = m->ebx;	/* 4949d1: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x4949d8u; native_call(m, 0x463780u);	/* 4949d3: call 0x463780 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 4949d8: xor ebp, ebp */
	m->ecx = m->ebx;	/* 4949da: mov ecx, ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4949dc: push ebp */
	m->edi = m->eax;	/* 4949dd: mov edi, eax */
	m->esp -= 4; M32(m->esp) = 0x4949e4u; native_call(m, 0x463780u);	/* 4949df: call 0x463780 */
	m->eax = M32((DWORD)(m->ebx + m->eax*4 + 0x2221fb8u));	/* 4949e4: mov eax, dword ptr [ebx + eax*4 + 0x2221fb8] */
	m->edx = M32((DWORD)(m->ebx + m->edi*4 + 0x2221fb8u));	/* 4949eb: mov edx, dword ptr [ebx + edi*4 + 0x2221fb8] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4949f2: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4949f4: cmp eax, edx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | ((((m->sf != m->of) ? 1u : 0u) & 0xff) << 0);	/* 4949f6: setl cl */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4949f9: xor eax, eax */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 4949fb: mov dword ptr [esp + 0x10], ecx */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 4949ff: mov dword ptr [esp + 0x24], eax */
	goto L_494a0b;	/* 494a03: jmp 0x494a0b */
L_494a05:
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 494a05: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 494a09: xor ebp, ebp */
L_494a0b:
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 494a0b: dec eax */
	if (!m->zf) goto L_494b88;	/* 494a0c: jne 0x494b88 */
	m->eax = m->ecx;	/* 494a12: mov eax, ecx */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 494a14: sub eax, ebp */
	if (m->zf) goto L_494b7e;	/* 494a16: je 0x494b7e */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 494a1c: dec eax */
	if (!m->zf) goto L_494b88;	/* 494a1d: jne 0x494b88 */
	M32((DWORD)(m->esp + 0x10u)) = m->ebp;	/* 494a23: mov dword ptr [esp + 0x10], ebp */
L_494a27:
	M32((DWORD)(m->esp + 0x28u)) = 0x3f800000u;	/* 494a27: mov dword ptr [esp + 0x28], 0x3f800000 */
	M32((DWORD)(m->esp + 0x30u)) = 0x0u;	/* 494a2f: mov dword ptr [esp + 0x30], 0 */
L_494a37:
	m->eax = M32((DWORD)(m->ebx + 0x2342976u));	/* 494a37: mov eax, dword ptr [ebx + 0x2342976] */
	M32((DWORD)(m->esp + 0x1cu)) = m->ebp;	/* 494a3d: mov dword ptr [esp + 0x1c], ebp */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 494a41: cmp eax, ebp */
	if (m->zf || m->sf != m->of) goto L_494cb5;	/* 494a43: jle 0x494cb5 */
	m->edi = (DWORD)(m->ebx + 0x23428f6u);	/* 494a49: lea edi, [ebx + 0x23428f6] */
	M32((DWORD)(m->esp + 0x20u)) = m->edi;	/* 494a4f: mov dword ptr [esp + 0x20], edi */
L_494a53:
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 494a53: mov eax, dword ptr [edi] */
	m->ecx = m->eax;	/* 494a55: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 494a57: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 494a5a: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 494a5c: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 494a5f: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 494a61: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 494a64: add ecx, eax */
	m->edx = M32((DWORD)(m->ebx + m->ecx*8 + 0x1eccb88u));	/* 494a66: mov edx, dword ptr [ebx + ecx*8 + 0x1eccb88] */
	m->ecx = m->ebx;	/* 494a6d: mov ecx, ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 494a6f: push edx */
	m->esp -= 4; M32(m->esp) = 0x494a75u; native_call(m, 0x463740u);	/* 494a70: call 0x463740 */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->esp + 0x10u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 494a75: cmp eax, dword ptr [esp + 0x10] */
	if (!m->zf) goto L_494c8f;	/* 494a79: jne 0x494c8f */
	m->edi = M32((DWORD)(m->edi + 0x0u));	/* 494a7f: mov edi, dword ptr [edi] */
	m->eax = M32((DWORD)(m->ebx + 0x234240du));	/* 494a81: mov eax, dword ptr [ebx + 0x234240d] */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 494a87: cmp edi, eax */
	M32((DWORD)(m->esp + 0x14u)) = m->edi;	/* 494a89: mov dword ptr [esp + 0x14], edi */
	M32((DWORD)(m->esp + 0x34u)) = 0x3f000000u;	/* 494a8d: mov dword ptr [esp + 0x34], 0x3f000000 */
	if (m->zf) goto L_494a9f;	/* 494a95: je 0x494a9f */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e4ccccdu;	/* 494a97: mov dword ptr [esp + 0x34], 0x3e4ccccd */
L_494a9f:
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 494a9f: mov eax, dword ptr [esp + 0x34] */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 494aa3: mov ecx, dword ptr [esp + 0x30] */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 494aa7: mov edx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 494aab: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 494aac: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 494aad: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 494aaf: push edx */
	m->esp -= 4; M32(m->esp) = 0x494ab6u; native_call(m, M32(0x4a9228u));	/* 494ab0: call dword ptr [0x4a9228] */
	m->eax = (DWORD)(m->esi + 0x10u);	/* 494ab6: lea eax, [esi + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 494ab9: push eax */
	{ DWORD v_ = 0x210u; m->esp -= 4; M32(m->esp) = v_; }	/* 494aba: push 0x210 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 494abf: push esi */
	{ DWORD v_ = 0x70u; m->esp -= 4; M32(m->esp) = v_; }	/* 494ac0: push 0x70 */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 494ac2: mov dword ptr [esp + 0x28], eax */
	m->esp -= 4; M32(m->esp) = 0x494acbu; native_call(m, 0x4950a0u);	/* 494ac6: call 0x4950a0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494acb: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494ad0: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494ad5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494ada: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x494ae4u; native_call(m, 0x44ad30u);	/* 494adf: call 0x44ad30 */
	m->eax = m->edi;	/* 494ae4: mov eax, edi */
	m->edx = (DWORD)(m->esp + 0x58u);	/* 494ae6: lea edx, [esp + 0x58] */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 494aea: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 494aed: add eax, edi */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 494aef: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 494af2: add eax, edi */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 494af4: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 494af7: add eax, edi */
	m->ebp = (DWORD)(m->ebx + m->eax*8 + 0x0u);	/* 494af9: lea ebp, [ebx + eax*8] */
	m->ecx = (DWORD)(m->ebp + 0x1eccb08u);	/* 494afc: lea ecx, [ebp + 0x1eccb08] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 494b02: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 494b03: push edx */
	m->esp -= 4; M32(m->esp) = 0x494b09u; native_call(m, 0x49e9ddu);	/* 494b04: call 0x49e9dd */
	m->eax = (DWORD)(m->esp + 0x60u);	/* 494b09: lea eax, [esp + 0x60] */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 494b0d: push 8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 494b0f: push eax */
	m->edi = (DWORD)(m->esp + 0x68u);	/* 494b10: lea edi, [esp + 0x68] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 494b14: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 494b17: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 494b19: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 494b1b: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 494b1d: dec ecx */
	m->edx = 0xf4u;	/* 494b1e: mov edx, 0xf4 */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 494b23: shl ecx, 3 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 494b26: sub edx, ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 494b28: push esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 494b29: push edx */
	m->esp -= 4; M32(m->esp) = 0x494b2fu; native_call(m, 0x44ad60u);	/* 494b2a: call 0x44ad60 */
	{ DWORD a_ = m->esp, b_ = 0x38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 494b2f: add esp, 0x38 */
	m->edi = 0x70u;	/* 494b32: mov edi, 0x70 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494b37: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494b3c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494b41: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494b46: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x494b51u; native_call(m, M32(0x4a9228u));	/* 494b4b: call dword ptr [0x4a9228] */
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x233c9f0u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 494b51: cmp dword ptr [ebx + 0x233c9f0], 1 */
	if (!m->zf) goto L_494b6f;	/* 494b58: jne 0x494b6f */
	m->eax = M32((DWORD)(m->ebp + 0x1eccb4cu));	/* 494b5a: mov eax, dword ptr [ebp + 0x1eccb4c] */
	m->edi = 0x58u;	/* 494b60: mov edi, 0x58 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 494b65: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 494b66: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 494b67: push eax */
	m->ecx = m->ebx;	/* 494b68: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x494b6fu; native_call(m, 0x4922c0u);	/* 494b6a: call 0x4922c0 */
L_494b6f:
	m->eax = M32((DWORD)(m->ebx + 0x8u));	/* 494b6f: mov eax, dword ptr [ebx + 8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 494b72: test eax, eax */
	if (!m->zf) goto L_494ba5;	/* 494b74: jne 0x494ba5 */
	m->ecx = M32((DWORD)(m->ebp + 0x1eccb7cu));	/* 494b76: mov ecx, dword ptr [ebp + 0x1eccb7c] */
	goto L_494ba9;	/* 494b7c: jmp 0x494ba9 */
L_494b7e:
	M32((DWORD)(m->esp + 0x10u)) = 0x1u;	/* 494b7e: mov dword ptr [esp + 0x10], 1 */
	goto L_494b90;	/* 494b86: jmp 0x494b90 */
L_494b88:
	{ DWORD a_ = m->ecx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 494b88: cmp ecx, ebp */
	if (m->zf) goto L_494a27;	/* 494b8a: je 0x494a27 */
L_494b90:
	M32((DWORD)(m->esp + 0x28u)) = 0x0u;	/* 494b90: mov dword ptr [esp + 0x28], 0 */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f800000u;	/* 494b98: mov dword ptr [esp + 0x30], 0x3f800000 */
	goto L_494a37;	/* 494ba0: jmp 0x494a37 */
L_494ba5:
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 494ba5: mov ecx, dword ptr [esp + 0x14] */
L_494ba9:
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 494ba9: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 494bac: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 494baf: sub eax, ecx */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 494bb1: lea edx, [eax + eax*2] */
	m->eax = (DWORD)(m->ecx + m->edx*8 + 0x0u);	/* 494bb4: lea eax, [ecx + edx*8] */
	{ DWORD a_ = M32((DWORD)(m->ebx + m->eax*2 + 0x179d1f6u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 494bb7: cmp dword ptr [ebx + eax*2 + 0x179d1f6], 1 */
	if (!m->zf) goto L_494bce;	/* 494bbf: jne 0x494bce */
	{ DWORD a_ = m->edi, b_ = 0xffffffe8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 494bc1: add edi, -0x18 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 494bc4: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 494bc5: push edi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 494bc6: push ecx */
	m->ecx = m->ebx;	/* 494bc7: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x494bceu; native_call(m, 0x4924d0u);	/* 494bc9: call 0x4924d0 */
L_494bce:
	m->ecx = M32((DWORD)(m->ebp + 0x1eccb58u));	/* 494bce: mov ecx, dword ptr [ebp + 0x1eccb58] */
	m->edx = M32((DWORD)(m->ebp + 0x1eccb54u));	/* 494bd4: mov edx, dword ptr [ebp + 0x1eccb54] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 494bda: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 494bdb: push edx */
	m->eax = (DWORD)(m->esp + 0x40u);	/* 494bdc: lea eax, [esp + 0x40] */
	{ DWORD v_ = 0x4d03f4u; m->esp -= 4; M32(m->esp) = v_; }	/* 494be0: push 0x4d03f4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 494be5: push eax */
	m->esp -= 4; M32(m->esp) = 0x494bebu; native_call(m, 0x49e9ddu);	/* 494be6: call 0x49e9dd */
	m->ecx = (DWORD)(m->esp + 0x48u);	/* 494beb: lea ecx, [esp + 0x48] */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 494bef: push 8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 494bf1: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 494bf2: push esi */
	{ DWORD v_ = 0xfcu; m->esp -= 4; M32(m->esp) = v_; }	/* 494bf3: push 0xfc */
	m->esp -= 4; M32(m->esp) = 0x494bfdu; native_call(m, 0x44ad60u);	/* 494bf8: call 0x44ad60 */
	m->ecx = M32((DWORD)(m->ebp + 0x1eccb6cu));	/* 494bfd: mov ecx, dword ptr [ebp + 0x1eccb6c] */
	m->edi = 0x3cu;	/* 494c03: mov edi, 0x3c */
	m->eax = m->ecx;	/* 494c08: mov eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 494c0a: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->edi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 494c0b: idiv edi */
	m->eax = 0x88888889u;	/* 494c0d: mov eax, 0x88888889 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 494c12: push edx */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 494c13: imul ecx */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 494c15: add edx, ecx */
	m->ecx = (DWORD)(m->esp + 0x5cu);	/* 494c17: lea ecx, [esp + 0x5c] */
	{ DWORD a_ = m->edx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 494c1b: sar edx, 5 */
	m->eax = m->edx;	/* 494c1e: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 494c20: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 494c23: add edx, eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 494c25: push edx */
	{ DWORD v_ = 0x4d03e4u; m->esp -= 4; M32(m->esp) = v_; }	/* 494c26: push 0x4d03e4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 494c2b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x494c31u; native_call(m, 0x49e9ddu);	/* 494c2c: call 0x49e9dd */
	m->edx = (DWORD)(m->esp + 0x68u);	/* 494c31: lea edx, [esp + 0x68] */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 494c35: push 8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 494c37: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 494c38: push esi */
	{ DWORD v_ = 0x1b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 494c39: push 0x1b0 */
	m->esp -= 4; M32(m->esp) = 0x494c43u; native_call(m, 0x44ad60u);	/* 494c3e: call 0x44ad60 */
	m->eax = M32((DWORD)(m->ebp + 0x1eccf4cu));	/* 494c43: mov eax, dword ptr [ebp + 0x1eccf4c] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 494c49: add esp, 0x40 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 494c4c: cmp eax, 1 */
	if (!m->zf) goto L_494c82;	/* 494c4f: jne 0x494c82 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494c51: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494c56: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494c5b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494c60: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x494c6bu; native_call(m, M32(0x4a9228u));	/* 494c65: call dword ptr [0x4a9228] */
	m->eax = M32((DWORD)(m->ebp + 0x1eccb88u));	/* 494c6b: mov eax, dword ptr [ebp + 0x1eccb88] */
	m->ecx = m->ebx;	/* 494c71: mov ecx, ebx */
	{ DWORD a_ = m->eax, b_ = 0x9u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 494c73: add eax, 9 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 494c76: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 494c77: push esi */
	{ DWORD v_ = 0x20cu; m->esp -= 4; M32(m->esp) = v_; }	/* 494c78: push 0x20c */
	m->esp -= 4; M32(m->esp) = 0x494c82u; native_call(m, 0x496820u);	/* 494c7d: call 0x496820 */
L_494c82:
	m->esi = M32((DWORD)(m->esp + 0x18u));	/* 494c82: mov esi, dword ptr [esp + 0x18] */
	m->edi = M32((DWORD)(m->esp + 0x20u));	/* 494c86: mov edi, dword ptr [esp + 0x20] */
	m->ebp = 0x1u;	/* 494c8a: mov ebp, 1 */
L_494c8f:
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 494c8f: mov eax, dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(m->ebx + 0x2342976u));	/* 494c93: mov ecx, dword ptr [ebx + 0x2342976] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 494c99: inc eax */
	{ DWORD a_ = m->edi, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 494c9a: add edi, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 494c9d: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 494c9f: mov dword ptr [esp + 0x1c], eax */
	M32((DWORD)(m->esp + 0x20u)) = m->edi;	/* 494ca3: mov dword ptr [esp + 0x20], edi */
	if (m->sf != m->of) goto L_494a53;	/* 494ca7: jl 0x494a53 */
	{ DWORD a_ = m->ebp, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 494cad: cmp ebp, 1 */
	if (!m->zf) goto L_494cb5;	/* 494cb0: jne 0x494cb5 */
	{ DWORD a_ = m->esi, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 494cb2: add esi, 0xc */
L_494cb5:
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 494cb5: mov eax, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 494cb9: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 494cba: cmp eax, 2 */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 494cbd: mov dword ptr [esp + 0x24], eax */
	if (m->sf != m->of) goto L_494a05;	/* 494cc1: jl 0x494a05 */
	goto L_494ee6;	/* 494cc7: jmp 0x494ee6 */
L_494ccc:
	m->eax = M32((DWORD)(m->ebx + 0x2342976u));	/* 494ccc: mov eax, dword ptr [ebx + 0x2342976] */
	M32((DWORD)(m->esp + 0x1cu)) = 0x0u;	/* 494cd2: mov dword ptr [esp + 0x1c], 0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 494cda: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_494ee6;	/* 494cdc: jle 0x494ee6 */
	m->ecx = (DWORD)(m->ebx + 0x23428f6u);	/* 494ce2: lea ecx, [ebx + 0x23428f6] */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 494ce8: mov dword ptr [esp + 0x10], ecx */
L_494cec:
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 494cec: mov edx, dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->ebx + 0x234240du));	/* 494cf0: mov eax, dword ptr [ebx + 0x234240d] */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 494cf6: push 0x3e4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494cfb: push 0x3f800000 */
	m->edi = M32((DWORD)(m->edx + 0x0u));	/* 494d00: mov edi, dword ptr [edx] */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 494d02: cmp edi, eax */
	M32((DWORD)(m->esp + 0x1cu)) = m->edi;	/* 494d04: mov dword ptr [esp + 0x1c], edi */
	if (!m->zf) goto L_494d10;	/* 494d08: jne 0x494d10 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 494d0a: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 494d0c: push 0 */
	goto L_494d1a;	/* 494d0e: jmp 0x494d1a */
L_494d10:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494d10: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494d15: push 0x3f800000 */
L_494d1a:
	m->esp -= 4; M32(m->esp) = 0x494d20u; native_call(m, M32(0x4a9228u));	/* 494d1a: call dword ptr [0x4a9228] */
	m->eax = (DWORD)(m->esi + 0x10u);	/* 494d20: lea eax, [esi + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 494d23: push eax */
	{ DWORD v_ = 0x210u; m->esp -= 4; M32(m->esp) = v_; }	/* 494d24: push 0x210 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 494d29: push esi */
	{ DWORD v_ = 0x70u; m->esp -= 4; M32(m->esp) = v_; }	/* 494d2a: push 0x70 */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 494d2c: mov dword ptr [esp + 0x28], eax */
	m->esp -= 4; M32(m->esp) = 0x494d35u; native_call(m, 0x4950a0u);	/* 494d30: call 0x4950a0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494d35: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494d3a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494d3f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494d44: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x494d4eu; native_call(m, 0x44ad30u);	/* 494d49: call 0x44ad30 */
	m->eax = m->edi;	/* 494d4e: mov eax, edi */
	m->edx = (DWORD)(m->esp + 0x58u);	/* 494d50: lea edx, [esp + 0x58] */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 494d54: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 494d57: add eax, edi */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 494d59: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 494d5c: add eax, edi */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 494d5e: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 494d61: add eax, edi */
	m->ebp = (DWORD)(m->ebx + m->eax*8 + 0x0u);	/* 494d63: lea ebp, [ebx + eax*8] */
	m->ecx = (DWORD)(m->ebp + 0x1eccb08u);	/* 494d66: lea ecx, [ebp + 0x1eccb08] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 494d6c: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 494d6d: push edx */
	m->esp -= 4; M32(m->esp) = 0x494d73u; native_call(m, 0x49e9ddu);	/* 494d6e: call 0x49e9dd */
	m->eax = (DWORD)(m->esp + 0x60u);	/* 494d73: lea eax, [esp + 0x60] */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 494d77: push 8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 494d79: push eax */
	m->edi = (DWORD)(m->esp + 0x68u);	/* 494d7a: lea edi, [esp + 0x68] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 494d7e: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 494d81: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 494d83: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 494d85: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 494d87: dec ecx */
	m->edx = 0xf4u;	/* 494d88: mov edx, 0xf4 */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 494d8d: shl ecx, 3 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 494d90: sub edx, ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 494d92: push esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 494d93: push edx */
	m->esp -= 4; M32(m->esp) = 0x494d99u; native_call(m, 0x44ad60u);	/* 494d94: call 0x44ad60 */
	{ DWORD a_ = m->esp, b_ = 0x38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 494d99: add esp, 0x38 */
	m->edi = 0x70u;	/* 494d9c: mov edi, 0x70 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494da1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494da6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494dab: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494db0: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x494dbbu; native_call(m, M32(0x4a9228u));	/* 494db5: call dword ptr [0x4a9228] */
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x233c9f0u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 494dbb: cmp dword ptr [ebx + 0x233c9f0], 1 */
	if (!m->zf) goto L_494dd9;	/* 494dc2: jne 0x494dd9 */
	m->eax = M32((DWORD)(m->ebp + 0x1eccb4cu));	/* 494dc4: mov eax, dword ptr [ebp + 0x1eccb4c] */
	m->edi = 0x58u;	/* 494dca: mov edi, 0x58 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 494dcf: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 494dd0: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 494dd1: push eax */
	m->ecx = m->ebx;	/* 494dd2: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x494dd9u; native_call(m, 0x4922c0u);	/* 494dd4: call 0x4922c0 */
L_494dd9:
	m->eax = M32((DWORD)(m->ebx + 0x8u));	/* 494dd9: mov eax, dword ptr [ebx + 8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 494ddc: test eax, eax */
	if (!m->zf) goto L_494de8;	/* 494dde: jne 0x494de8 */
	m->ecx = M32((DWORD)(m->ebp + 0x1eccb7cu));	/* 494de0: mov ecx, dword ptr [ebp + 0x1eccb7c] */
	goto L_494dec;	/* 494de6: jmp 0x494dec */
L_494de8:
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 494de8: mov ecx, dword ptr [esp + 0x14] */
L_494dec:
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 494dec: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 494def: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 494df2: sub eax, ecx */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 494df4: lea edx, [eax + eax*2] */
	m->eax = (DWORD)(m->ecx + m->edx*8 + 0x0u);	/* 494df7: lea eax, [ecx + edx*8] */
	{ DWORD a_ = M32((DWORD)(m->ebx + m->eax*2 + 0x179d1f6u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 494dfa: cmp dword ptr [ebx + eax*2 + 0x179d1f6], 1 */
	if (!m->zf) goto L_494e11;	/* 494e02: jne 0x494e11 */
	{ DWORD a_ = m->edi, b_ = 0xffffffe8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 494e04: add edi, -0x18 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 494e07: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 494e08: push edi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 494e09: push ecx */
	m->ecx = m->ebx;	/* 494e0a: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x494e11u; native_call(m, 0x4924d0u);	/* 494e0c: call 0x4924d0 */
L_494e11:
	m->ecx = M32((DWORD)(m->ebp + 0x1eccb58u));	/* 494e11: mov ecx, dword ptr [ebp + 0x1eccb58] */
	m->edx = M32((DWORD)(m->ebp + 0x1eccb54u));	/* 494e17: mov edx, dword ptr [ebp + 0x1eccb54] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 494e1d: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 494e1e: push edx */
	m->eax = (DWORD)(m->esp + 0x40u);	/* 494e1f: lea eax, [esp + 0x40] */
	{ DWORD v_ = 0x4d03f4u; m->esp -= 4; M32(m->esp) = v_; }	/* 494e23: push 0x4d03f4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 494e28: push eax */
	m->esp -= 4; M32(m->esp) = 0x494e2eu; native_call(m, 0x49e9ddu);	/* 494e29: call 0x49e9dd */
	m->ecx = (DWORD)(m->esp + 0x48u);	/* 494e2e: lea ecx, [esp + 0x48] */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 494e32: push 8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 494e34: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 494e35: push esi */
	{ DWORD v_ = 0xfcu; m->esp -= 4; M32(m->esp) = v_; }	/* 494e36: push 0xfc */
	m->esp -= 4; M32(m->esp) = 0x494e40u; native_call(m, 0x44ad60u);	/* 494e3b: call 0x44ad60 */
	m->ecx = M32((DWORD)(m->ebp + 0x1eccb6cu));	/* 494e40: mov ecx, dword ptr [ebp + 0x1eccb6c] */
	m->edi = 0x3cu;	/* 494e46: mov edi, 0x3c */
	m->eax = m->ecx;	/* 494e4b: mov eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 494e4d: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->edi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 494e4e: idiv edi */
	m->eax = 0x88888889u;	/* 494e50: mov eax, 0x88888889 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 494e55: push edx */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 494e56: imul ecx */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 494e58: add edx, ecx */
	m->ecx = (DWORD)(m->esp + 0x5cu);	/* 494e5a: lea ecx, [esp + 0x5c] */
	{ DWORD a_ = m->edx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 494e5e: sar edx, 5 */
	m->eax = m->edx;	/* 494e61: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 494e63: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 494e66: add edx, eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 494e68: push edx */
	{ DWORD v_ = 0x4d03e4u; m->esp -= 4; M32(m->esp) = v_; }	/* 494e69: push 0x4d03e4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 494e6e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x494e74u; native_call(m, 0x49e9ddu);	/* 494e6f: call 0x49e9dd */
	m->edx = (DWORD)(m->esp + 0x68u);	/* 494e74: lea edx, [esp + 0x68] */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 494e78: push 8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 494e7a: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 494e7b: push esi */
	{ DWORD v_ = 0x1b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 494e7c: push 0x1b0 */
	m->esp -= 4; M32(m->esp) = 0x494e86u; native_call(m, 0x44ad60u);	/* 494e81: call 0x44ad60 */
	m->eax = M32((DWORD)(m->ebp + 0x1eccf48u));	/* 494e86: mov eax, dword ptr [ebp + 0x1eccf48] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 494e8c: add esp, 0x40 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 494e8f: cmp eax, 1 */
	if (!m->zf) goto L_494ebd;	/* 494e92: jne 0x494ebd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494e94: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494e99: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494e9e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494ea3: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x494eaeu; native_call(m, M32(0x4a9228u));	/* 494ea8: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 494eae: push 8 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 494eb0: push esi */
	{ DWORD v_ = 0x20cu; m->esp -= 4; M32(m->esp) = v_; }	/* 494eb1: push 0x20c */
	m->ecx = m->ebx;	/* 494eb6: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x494ebdu; native_call(m, 0x496820u);	/* 494eb8: call 0x496820 */
L_494ebd:
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 494ebd: mov eax, dword ptr [esp + 0x1c] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 494ec1: mov edx, dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->ebx + 0x2342976u));	/* 494ec5: mov ecx, dword ptr [ebx + 0x2342976] */
	m->esi = M32((DWORD)(m->esp + 0x18u));	/* 494ecb: mov esi, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 494ecf: inc eax */
	{ DWORD a_ = m->edx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 494ed0: add edx, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 494ed3: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 494ed5: mov dword ptr [esp + 0x1c], eax */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 494ed9: mov dword ptr [esp + 0x10], edx */
	if (m->sf != m->of) goto L_494cec;	/* 494edd: jl 0x494cec */
	{ DWORD a_ = m->esi, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 494ee3: add esi, 0xc */
L_494ee6:
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 494ee6: xor edi, edi */
	m->ebp = (DWORD)(m->ebx + 0x1eccb08u);	/* 494ee8: lea ebp, [ebx + 0x1eccb08] */
	M32((DWORD)(m->esp + 0x14u)) = m->edi;	/* 494eee: mov dword ptr [esp + 0x14], edi */
L_494ef2:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 494ef2: push edi */
	m->esp -= 4; M32(m->esp) = 0x494ef8u; native_call(m, 0x4a8700u);	/* 494ef3: call 0x4a8700 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 494ef8: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 494efb: cmp eax, 1 */
	if (!m->zf) goto L_49507d;	/* 494efe: jne 0x49507d */
	m->eax = M32((DWORD)(m->ebp + 0x80u));	/* 494f04: mov eax, dword ptr [ebp + 0x80] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 494f0a: test eax, eax */
	if (m->sf == m->of) goto L_49507d;	/* 494f0c: jge 0x49507d */
	{ DWORD a_ = m->edi, b_ = M32((DWORD)(m->ebx + 0x234240du)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 494f12: cmp edi, dword ptr [ebx + 0x234240d] */
	if (!m->zf) goto L_494f21;	/* 494f18: jne 0x494f21 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494f1a: push 0x3f000000 */
	goto L_494f26;	/* 494f1f: jmp 0x494f26 */
L_494f21:
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 494f21: push 0x3e4ccccd */
L_494f26:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 494f26: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494f28: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 494f2d: push 0 */
	m->esp -= 4; M32(m->esp) = 0x494f35u; native_call(m, M32(0x4a9228u));	/* 494f2f: call dword ptr [0x4a9228] */
	m->eax = (DWORD)(m->esi + 0x10u);	/* 494f35: lea eax, [esi + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 494f38: push eax */
	{ DWORD v_ = 0x210u; m->esp -= 4; M32(m->esp) = v_; }	/* 494f39: push 0x210 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 494f3e: push esi */
	{ DWORD v_ = 0x70u; m->esp -= 4; M32(m->esp) = v_; }	/* 494f3f: push 0x70 */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 494f41: mov dword ptr [esp + 0x28], eax */
	m->esp -= 4; M32(m->esp) = 0x494f4au; native_call(m, 0x4950a0u);	/* 494f45: call 0x4950a0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494f4a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494f4f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494f54: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494f59: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x494f63u; native_call(m, 0x44ad30u);	/* 494f5e: call 0x44ad30 */
	m->eax = (DWORD)(m->esp + 0x58u);	/* 494f63: lea eax, [esp + 0x58] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 494f67: push ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 494f68: push eax */
	m->esp -= 4; M32(m->esp) = 0x494f6eu; native_call(m, 0x49e9ddu);	/* 494f69: call 0x49e9dd */
	m->ecx = (DWORD)(m->esp + 0x60u);	/* 494f6e: lea ecx, [esp + 0x60] */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 494f72: push 8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 494f74: push ecx */
	m->edi = (DWORD)(m->esp + 0x68u);	/* 494f75: lea edi, [esp + 0x68] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 494f79: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 494f7c: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 494f7e: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 494f80: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 494f82: dec ecx */
	m->edx = 0xf4u;	/* 494f83: mov edx, 0xf4 */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 494f88: shl ecx, 3 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 494f8b: sub edx, ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 494f8d: push esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 494f8e: push edx */
	m->esp -= 4; M32(m->esp) = 0x494f94u; native_call(m, 0x44ad60u);	/* 494f8f: call 0x44ad60 */
	{ DWORD a_ = m->esp, b_ = 0x38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 494f94: add esp, 0x38 */
	m->edi = 0x70u;	/* 494f97: mov edi, 0x70 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494f9c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494fa1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494fa6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 494fab: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x494fb6u; native_call(m, M32(0x4a9228u));	/* 494fb0: call dword ptr [0x4a9228] */
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x233c9f0u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 494fb6: cmp dword ptr [ebx + 0x233c9f0], 1 */
	if (!m->zf) goto L_494fd1;	/* 494fbd: jne 0x494fd1 */
	m->eax = M32((DWORD)(m->ebp + 0x44u));	/* 494fbf: mov eax, dword ptr [ebp + 0x44] */
	m->edi = 0x58u;	/* 494fc2: mov edi, 0x58 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 494fc7: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 494fc8: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 494fc9: push eax */
	m->ecx = m->ebx;	/* 494fca: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x494fd1u; native_call(m, 0x4922c0u);	/* 494fcc: call 0x4922c0 */
L_494fd1:
	m->eax = M32((DWORD)(m->ebx + 0x8u));	/* 494fd1: mov eax, dword ptr [ebx + 8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 494fd4: test eax, eax */
	if (!m->zf) goto L_494fdd;	/* 494fd6: jne 0x494fdd */
	m->ecx = M32((DWORD)(m->ebp + 0x74u));	/* 494fd8: mov ecx, dword ptr [ebp + 0x74] */
	goto L_494fe1;	/* 494fdb: jmp 0x494fe1 */
L_494fdd:
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 494fdd: mov ecx, dword ptr [esp + 0x14] */
L_494fe1:
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 494fe1: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 494fe4: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 494fe7: sub eax, ecx */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 494fe9: lea edx, [eax + eax*2] */
	m->eax = (DWORD)(m->ecx + m->edx*8 + 0x0u);	/* 494fec: lea eax, [ecx + edx*8] */
	{ DWORD a_ = M32((DWORD)(m->ebx + m->eax*2 + 0x179d1f6u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 494fef: cmp dword ptr [ebx + eax*2 + 0x179d1f6], 1 */
	if (!m->zf) goto L_495006;	/* 494ff7: jne 0x495006 */
	{ DWORD a_ = m->edi, b_ = 0xffffffe8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 494ff9: add edi, -0x18 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 494ffc: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 494ffd: push edi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 494ffe: push ecx */
	m->ecx = m->ebx;	/* 494fff: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x495006u; native_call(m, 0x4924d0u);	/* 495001: call 0x4924d0 */
L_495006:
	m->ecx = M32((DWORD)(m->ebp + 0x50u));	/* 495006: mov ecx, dword ptr [ebp + 0x50] */
	m->edx = M32((DWORD)(m->ebp + 0x4cu));	/* 495009: mov edx, dword ptr [ebp + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49500c: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49500d: push edx */
	m->eax = (DWORD)(m->esp + 0x40u);	/* 49500e: lea eax, [esp + 0x40] */
	{ DWORD v_ = 0x4d03f4u; m->esp -= 4; M32(m->esp) = v_; }	/* 495012: push 0x4d03f4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 495017: push eax */
	m->esp -= 4; M32(m->esp) = 0x49501du; native_call(m, 0x49e9ddu);	/* 495018: call 0x49e9dd */
	m->ecx = (DWORD)(m->esp + 0x48u);	/* 49501d: lea ecx, [esp + 0x48] */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 495021: push 8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 495023: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 495024: push esi */
	{ DWORD v_ = 0xfcu; m->esp -= 4; M32(m->esp) = v_; }	/* 495025: push 0xfc */
	m->esp -= 4; M32(m->esp) = 0x49502fu; native_call(m, 0x44ad60u);	/* 49502a: call 0x44ad60 */
	m->ecx = M32((DWORD)(m->ebp + 0x64u));	/* 49502f: mov ecx, dword ptr [ebp + 0x64] */
	m->edi = 0x3cu;	/* 495032: mov edi, 0x3c */
	m->eax = m->ecx;	/* 495037: mov eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 495039: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->edi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 49503a: idiv edi */
	m->eax = 0x88888889u;	/* 49503c: mov eax, 0x88888889 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 495041: push edx */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 495042: imul ecx */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 495044: add edx, ecx */
	m->ecx = (DWORD)(m->esp + 0x5cu);	/* 495046: lea ecx, [esp + 0x5c] */
	{ DWORD a_ = m->edx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49504a: sar edx, 5 */
	m->eax = m->edx;	/* 49504d: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49504f: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 495052: add edx, eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 495054: push edx */
	{ DWORD v_ = 0x4d03e4u; m->esp -= 4; M32(m->esp) = v_; }	/* 495055: push 0x4d03e4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49505a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x495060u; native_call(m, 0x49e9ddu);	/* 49505b: call 0x49e9dd */
	m->edx = (DWORD)(m->esp + 0x68u);	/* 495060: lea edx, [esp + 0x68] */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 495064: push 8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 495066: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 495067: push esi */
	{ DWORD v_ = 0x1b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495068: push 0x1b0 */
	m->esp -= 4; M32(m->esp) = 0x495072u; native_call(m, 0x44ad60u);	/* 49506d: call 0x44ad60 */
	m->esi = M32((DWORD)(m->esp + 0x58u));	/* 495072: mov esi, dword ptr [esp + 0x58] */
	m->edi = M32((DWORD)(m->esp + 0x54u));	/* 495076: mov edi, dword ptr [esp + 0x54] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49507a: add esp, 0x40 */
L_49507d:
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 49507d: inc edi */
	{ DWORD a_ = m->ebp, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 49507e: add ebp, 0x8888 */
	{ DWORD a_ = m->edi, b_ = 0x10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 495084: cmp edi, 0x10 */
	M32((DWORD)(m->esp + 0x14u)) = m->edi;	/* 495087: mov dword ptr [esp + 0x14], edi */
	if (m->sf != m->of) goto L_494ef2;	/* 49508b: jl 0x494ef2 */
	m->edi = M32(m->esp); m->esp += 4;	/* 495091: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 495092: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 495093: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 495094: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x128u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495095: add esp, 0x128 */
	m->esp += 4 + 0; return;	/* 49509b: ret  */
}

/* hud_496240 (0x496240), lifted by tools/lift.py */
static void lift_496240(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x108u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496240: sub esp, 0x108 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 496246: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 496247: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 496248: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 496249: push edi */
	m->esi = m->ecx;	/* 49624a: mov esi, ecx */
	m->esp -= 4; M32(m->esp) = 0x496251u; native_call(m, 0x4685b0u);	/* 49624c: call 0x4685b0 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 496251: mov dword ptr [esp + 0x10], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 496255: fild dword ptr [esp + 0x10] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9510u));	/* 496259: fdivr dword ptr [0x4a9510] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9514u));	/* 49625f: fdivr dword ptr [0x4a9514] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 496265: call 0x49ec14 */
	m->ebx = m->eax;	/* 49626a: mov ebx, eax */
	m->esp -= 4; M32(m->esp) = 0x496271u; native_call(m, 0x4685c0u);	/* 49626c: call 0x4685c0 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 496271: mov dword ptr [esp + 0x10], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 496275: fild dword ptr [esp + 0x10] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4acu));	/* 496279: fdivr dword ptr [0x4aa4ac] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a944cu));	/* 49627f: fdivr dword ptr [0x4a944c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 496285: call 0x49ec14 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 49628a: mov dword ptr [esp + 0x10], eax */
	m->esp -= 4; M32(m->esp) = 0x496293u; native_call(m, 0x4685c0u);	/* 49628e: call 0x4685c0 */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 496293: mov dword ptr [esp + 0x14], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 496297: fild dword ptr [esp + 0x14] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4acu));	/* 49629b: fdivr dword ptr [0x4aa4ac] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4ecu));	/* 4962a1: fdivr dword ptr [0x4aa4ec] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4962a7: call 0x49ec14 */
	m->ebp = m->eax;	/* 4962ac: mov ebp, eax */
	m->esp -= 4; M32(m->esp) = 0x4962b3u; native_call(m, 0x4685b0u);	/* 4962ae: call 0x4685b0 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4962b3: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4962b4: sub eax, edx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4962b6: push 0x3f000000 */
	m->edi = m->eax;	/* 4962bb: mov edi, eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4962bd: push 0 */
	{ DWORD a_ = m->edi, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 4962bf: sar edi, 1 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4962c1: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4962c3: push 0x3f800000 */
	{ DWORD a_ = m->edi, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4962c8: sub edi, ebx */
	m->esp -= 4; M32(m->esp) = 0x4962d0u; native_call(m, M32(0x4a9228u));	/* 4962ca: call dword ptr [0x4a9228] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 4962d0: mov eax, dword ptr [esp + 0x10] */
	m->ecx = (DWORD)(m->ebx + m->edi*1 + 0xffffffffu);	/* 4962d4: lea ecx, [ebx + edi - 1] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4962d8: add eax, ebp */
	m->edx = (DWORD)(m->ebp + 0x1u);	/* 4962da: lea edx, [ebp + 1] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4962dd: dec eax */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4962de: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4962df: push ecx */
	m->eax = (DWORD)(m->edi + 0x1u);	/* 4962e0: lea eax, [edi + 1] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4962e3: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4962e4: push eax */
	m->esp -= 4; M32(m->esp) = 0x4962eau; native_call(m, 0x46bd60u);	/* 4962e5: call 0x46bd60 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4962ea: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4962ef: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4962f4: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4962f9: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x496303u; native_call(m, 0x44ad30u);	/* 4962fe: call 0x44ad30 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496303: add esp, 0x20 */
	m->ecx = m->esi;	/* 496306: mov ecx, esi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496308: push 0 */
	m->esp -= 4; M32(m->esp) = 0x49630fu; native_call(m, 0x463780u);	/* 49630a: call 0x463780 */
	m->ecx = M32((DWORD)(m->esi + m->eax*4 + 0x2221fb8u));	/* 49630f: mov ecx, dword ptr [esi + eax*4 + 0x2221fb8] */
	m->edx = (DWORD)(m->esp + 0x18u);	/* 496316: lea edx, [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49631a: push ecx */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 49631b: push 0x4b0320 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 496320: push edx */
	m->esp -= 4; M32(m->esp) = 0x496326u; native_call(m, 0x49e9ddu);	/* 496321: call 0x49e9dd */
	m->eax = (DWORD)(m->esp + 0x24u);	/* 496326: lea eax, [esp + 0x24] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 49632a: push 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49632c: push eax */
	{ DWORD v_ = 0x128u; m->esp -= 4; M32(m->esp) = v_; }	/* 49632d: push 0x128 */
	{ DWORD v_ = 0x9u; m->esp -= 4; M32(m->esp) = v_; }	/* 496332: push 9 */
	{ DWORD v_ = 0x128u; m->esp -= 4; M32(m->esp) = v_; }	/* 496334: push 0x128 */
	m->esp -= 4; M32(m->esp) = 0x49633eu; native_call(m, 0x44ae10u);	/* 496339: call 0x44ae10 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49633e: add esp, 0x20 */
	m->edi = (DWORD)(m->ebx + m->edi*1 + 0x1u);	/* 496341: lea edi, [ebx + edi + 1] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496345: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49634a: push 0x3f800000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49634f: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496354: push 0 */
	m->esp -= 4; M32(m->esp) = 0x49635cu; native_call(m, M32(0x4a9228u));	/* 496356: call dword ptr [0x4a9228] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 49635c: mov ecx, dword ptr [esp + 0x10] */
	m->eax = (DWORD)(m->ecx + m->ebp*1 + 0x0u);	/* 496360: lea eax, [ecx + ebp] */
	m->edx = (DWORD)(m->ebx + m->edi*1 + 0x0u);	/* 496363: lea edx, [ebx + edi] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 496366: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 496367: push edx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 496368: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 496369: push edi */
	m->esp -= 4; M32(m->esp) = 0x49636fu; native_call(m, 0x46bd60u);	/* 49636a: call 0x46bd60 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49636f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496374: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496379: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49637e: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x496388u; native_call(m, 0x44ad30u);	/* 496383: call 0x44ad30 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496388: add esp, 0x20 */
	m->ecx = m->esi;	/* 49638b: mov ecx, esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 49638d: push 1 */
	m->esp -= 4; M32(m->esp) = 0x496394u; native_call(m, 0x463780u);	/* 49638f: call 0x463780 */
	m->eax = M32((DWORD)(m->esi + m->eax*4 + 0x2221fb8u));	/* 496394: mov eax, dword ptr [esi + eax*4 + 0x2221fb8] */
	m->ecx = (DWORD)(m->esp + 0x18u);	/* 49639b: lea ecx, [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49639f: push eax */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 4963a0: push 0x4b0320 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4963a5: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4963abu; native_call(m, 0x49e9ddu);	/* 4963a6: call 0x49e9dd */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 4963ab: lea edx, [esp + 0x24] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 4963af: push 0x10 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4963b1: push edx */
	{ DWORD v_ = 0x158u; m->esp -= 4; M32(m->esp) = v_; }	/* 4963b2: push 0x158 */
	{ DWORD v_ = 0x9u; m->esp -= 4; M32(m->esp) = v_; }	/* 4963b7: push 9 */
	{ DWORD v_ = 0x158u; m->esp -= 4; M32(m->esp) = v_; }	/* 4963b9: push 0x158 */
	m->esp -= 4; M32(m->esp) = 0x4963c3u; native_call(m, 0x44ae10u);	/* 4963be: call 0x44ae10 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4963c3: add esp, 0x20 */
	m->esp -= 4; M32(m->esp) = 0x4963cbu; native_call(m, 0x4685c0u);	/* 4963c6: call 0x4685c0 */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 4963cb: mov dword ptr [esp + 0x14], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 4963cf: fild dword ptr [esp + 0x14] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4acu));	/* 4963d3: fdivr dword ptr [0x4aa4ac] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4ecu));	/* 4963d9: fdivr dword ptr [0x4aa4ec] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4963df: call 0x49ec14 */
	m->ebp = m->eax;	/* 4963e4: mov ebp, eax */
	m->esp -= 4; M32(m->esp) = 0x4963ebu; native_call(m, 0x4685b0u);	/* 4963e6: call 0x4685b0 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4963eb: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4963ec: sub eax, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4963ee: push 0x3f800000 */
	m->edi = m->eax;	/* 4963f3: mov edi, eax */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4963f5: push 0x3f800000 */
	{ DWORD a_ = m->edi, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 4963fa: sar edi, 1 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4963fc: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496401: push 0x3f800000 */
	{ DWORD a_ = m->edi, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 496406: sub edi, ebx */
	m->esp -= 4; M32(m->esp) = 0x49640eu; native_call(m, M32(0x4a9228u));	/* 496408: call dword ptr [0x4a9228] */
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 49640e: mov eax, dword ptr [esi + 0x234240d] */
	m->ecx = m->eax;	/* 496414: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 496416: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 496419: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49641b: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49641e: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 496420: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 496423: add ecx, eax */
	m->edx = M32((DWORD)(m->esi + m->ecx*8 + 0x1eccb88u));	/* 496425: mov edx, dword ptr [esi + ecx*8 + 0x1eccb88] */
	m->ecx = m->esi;	/* 49642c: mov ecx, esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49642e: push edx */
	m->esp -= 4; M32(m->esp) = 0x496434u; native_call(m, 0x463740u);	/* 49642f: call 0x463740 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 496434: test eax, eax */
	if (!m->zf) goto L_496446;	/* 496436: jne 0x496446 */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 496438: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ebx, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 49643c: add ebx, edi */
	m->ecx = (DWORD)(m->eax + m->ebp*1 + 0x0u);	/* 49643e: lea ecx, [eax + ebp] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 496441: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 496442: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 496443: push ebp */
	goto L_496486;	/* 496444: jmp 0x496486 */
L_496446:
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 496446: mov eax, dword ptr [esi + 0x234240d] */
	m->ecx = m->esi;	/* 49644c: mov ecx, esi */
	m->edx = m->eax;	/* 49644e: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 496450: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 496453: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 496455: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 496458: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49645a: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49645d: add edx, eax */
	m->eax = M32((DWORD)(m->esi + m->edx*8 + 0x1eccb88u));	/* 49645f: mov eax, dword ptr [esi + edx*8 + 0x1eccb88] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 496466: push eax */
	m->esp -= 4; M32(m->esp) = 0x49646cu; native_call(m, 0x463740u);	/* 496467: call 0x463740 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49646c: cmp eax, 1 */
	if (!m->zf) goto L_49648f;	/* 49646f: jne 0x49648f */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 496471: mov ecx, dword ptr [esp + 0x10] */
	m->edi = (DWORD)(m->edi + m->ebx*1 + 0x1u);	/* 496475: lea edi, [edi + ebx + 1] */
	m->edx = (DWORD)(m->ecx + m->ebp*1 + 0xffffffffu);	/* 496479: lea edx, [ecx + ebp - 1] */
	m->eax = (DWORD)(m->ebx + m->edi*1 + 0xffffffffu);	/* 49647d: lea eax, [ebx + edi - 1] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 496481: push edx */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 496482: inc ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 496483: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 496484: push ebp */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 496485: inc edi */
L_496486:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 496486: push edi */
	m->esp -= 4; M32(m->esp) = 0x49648cu; native_call(m, 0x46bd00u);	/* 496487: call 0x46bd00 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49648c: add esp, 0x10 */
L_49648f:
	m->esp -= 4; M32(m->esp) = 0x496494u; native_call(m, 0x4685b0u);	/* 49648f: call 0x4685b0 */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 496494: mov dword ptr [esp + 0x14], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 496498: fild dword ptr [esp + 0x14] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9510u));	/* 49649c: fdivr dword ptr [0x4a9510] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa27cu));	/* 4964a2: fdivr dword ptr [0x4aa27c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4964a8: call 0x49ec14 */
	m->edi = m->eax;	/* 4964ad: mov edi, eax */
	m->esp -= 4; M32(m->esp) = 0x4964b4u; native_call(m, 0x4685c0u);	/* 4964af: call 0x4685c0 */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 4964b4: mov dword ptr [esp + 0x14], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 4964b8: fild dword ptr [esp + 0x14] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4acu));	/* 4964bc: fdivr dword ptr [0x4aa4ac] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4e8u));	/* 4964c2: fdivr dword ptr [0x4aa4e8] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4964c8: call 0x49ec14 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 4964cd: mov dword ptr [esp + 0x10], eax */
	m->esp -= 4; M32(m->esp) = 0x4964d6u; native_call(m, 0x4685c0u);	/* 4964d1: call 0x4685c0 */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 4964d6: mov dword ptr [esp + 0x14], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 4964da: fild dword ptr [esp + 0x14] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4acu));	/* 4964de: fdivr dword ptr [0x4aa4ac] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa27cu));	/* 4964e4: fdivr dword ptr [0x4aa27c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4964ea: call 0x49ec14 */
	m->ebp = m->eax;	/* 4964ef: mov ebp, eax */
	m->esp -= 4; M32(m->esp) = 0x4964f6u; native_call(m, 0x4685b0u);	/* 4964f1: call 0x4685b0 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4964f6: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4964f7: sub eax, edx */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 4964f9: push 0x3e4ccccd */
	m->ebx = m->eax;	/* 4964fe: mov ebx, eax */
	m->eax = m->edi;	/* 496500: mov eax, edi */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 496502: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 496503: sub eax, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496505: push 0x3f800000 */
	{ DWORD a_ = m->ebx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->ebx = r_; } }	/* 49650a: sar ebx, 1 */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49650c: sar eax, 1 */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 49650e: sub ebx, eax */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496510: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496515: push 0x3f800000 */
	{ DWORD a_ = m->ebx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 49651a: sub ebx, edi */
	m->esp -= 4; M32(m->esp) = 0x496522u; native_call(m, M32(0x4a9228u));	/* 49651c: call dword ptr [0x4a9228] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 496522: mov ecx, dword ptr [esp + 0x10] */
	m->eax = (DWORD)(m->ebx + m->edi*2 + 0x0u);	/* 496526: lea eax, [ebx + edi*2] */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 496529: add edi, eax */
	m->edx = (DWORD)(m->ecx + m->ebp*1 + 0xffffffffu);	/* 49652b: lea edx, [ecx + ebp - 1] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49652f: push edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 496530: push edi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 496531: push ebp */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 496532: push ebx */
	m->esp -= 4; M32(m->esp) = 0x496538u; native_call(m, 0x46bd60u);	/* 496533: call 0x46bd60 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496538: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 49653d: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 49653f: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496541: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x49654bu; native_call(m, 0x44ad30u);	/* 496546: call 0x44ad30 */
	m->ecx = M32((DWORD)(m->esi + 0x234297eu));	/* 49654b: mov ecx, dword ptr [esi + 0x234297e] */
	m->edx = (DWORD)(m->esp + 0x38u);	/* 496551: lea edx, [esp + 0x38] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 496555: push ecx */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 496556: push 0x4b0320 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49655b: push edx */
	m->esp -= 4; M32(m->esp) = 0x496561u; native_call(m, 0x49e9ddu);	/* 49655c: call 0x49e9dd */
	m->eax = (DWORD)(m->esp + 0x44u);	/* 496561: lea eax, [esp + 0x44] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 496565: push 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 496567: push eax */
	{ DWORD v_ = 0x133u; m->esp -= 4; M32(m->esp) = v_; }	/* 496568: push 0x133 */
	{ DWORD v_ = 0x1bu; m->esp -= 4; M32(m->esp) = v_; }	/* 49656d: push 0x1b */
	{ DWORD v_ = 0x119u; m->esp -= 4; M32(m->esp) = v_; }	/* 49656f: push 0x119 */
	m->esp -= 4; M32(m->esp) = 0x496579u; native_call(m, 0x44ae10u);	/* 496574: call 0x44ae10 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496579: add esp, 0x40 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49657c: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496581: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496583: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496588: push 0 */
	m->esp -= 4; M32(m->esp) = 0x49658fu; native_call(m, 0x44ad30u);	/* 49658a: call 0x44ad30 */
	m->ecx = M32((DWORD)(m->esi + 0x2342986u));	/* 49658f: mov ecx, dword ptr [esi + 0x2342986] */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 496595: lea edx, [esp + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 496599: push ecx */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 49659a: push 0x4b0320 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49659f: push edx */
	m->esp -= 4; M32(m->esp) = 0x4965a5u; native_call(m, 0x49e9ddu);	/* 4965a0: call 0x49e9dd */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 4965a5: push 0x10 */
	m->eax = (DWORD)(m->esp + 0x38u);	/* 4965a7: lea eax, [esp + 0x38] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4965ab: push eax */
	{ DWORD v_ = 0x14du; m->esp -= 4; M32(m->esp) = v_; }	/* 4965ac: push 0x14d */
	{ DWORD v_ = 0x1bu; m->esp -= 4; M32(m->esp) = v_; }	/* 4965b1: push 0x1b */
	{ DWORD v_ = 0x133u; m->esp -= 4; M32(m->esp) = v_; }	/* 4965b3: push 0x133 */
	m->esp -= 4; M32(m->esp) = 0x4965bdu; native_call(m, 0x44ae10u);	/* 4965b8: call 0x44ae10 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4965bd: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4965c2: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4965c7: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4965c9: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4965d0u; native_call(m, 0x44ad30u);	/* 4965cb: call 0x44ad30 */
	m->ecx = M32((DWORD)(m->esi + 0x2342982u));	/* 4965d0: mov ecx, dword ptr [esi + 0x2342982] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4965d6: add esp, 0x40 */
	m->edx = (DWORD)(m->esp + 0x18u);	/* 4965d9: lea edx, [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4965dd: push ecx */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 4965de: push 0x4b0320 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4965e3: push edx */
	m->esp -= 4; M32(m->esp) = 0x4965e9u; native_call(m, 0x49e9ddu);	/* 4965e4: call 0x49e9dd */
	m->eax = (DWORD)(m->esp + 0x24u);	/* 4965e9: lea eax, [esp + 0x24] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 4965ed: push 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4965ef: push eax */
	{ DWORD v_ = 0x167u; m->esp -= 4; M32(m->esp) = v_; }	/* 4965f0: push 0x167 */
	{ DWORD v_ = 0x1bu; m->esp -= 4; M32(m->esp) = v_; }	/* 4965f5: push 0x1b */
	{ DWORD v_ = 0x14du; m->esp -= 4; M32(m->esp) = v_; }	/* 4965f7: push 0x14d */
	m->esp -= 4; M32(m->esp) = 0x496601u; native_call(m, 0x44ae10u);	/* 4965fc: call 0x44ae10 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496601: add esp, 0x20 */
	m->edi = M32(m->esp); m->esp += 4;	/* 496604: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 496605: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 496606: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 496607: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x108u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496608: add esp, 0x108 */
	m->esp += 4 + 0; return;	/* 49660e: ret  */
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
