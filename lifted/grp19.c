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

static void lift_45ee40(X86 *m);

/* armc_computeTotals (0x45ee40), lifted by tools/lift.py */
static void lift_45ee40(X86 *m)
{
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 45ee40: push -1 */
	m->eax = M32((DWORD)&g_lift_fs0);	/* 45ee42: mov eax, dword ptr fs:[0] */
	{ DWORD v_ = 0x4a89ecu; m->esp -= 4; M32(m->esp) = v_; }	/* 45ee48: push 0x4a89ec */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45ee4d: push eax */
	m->eax = 0x88a0u;	/* 45ee4e: mov eax, 0x88a0 */
	M32((DWORD)&g_lift_fs0) = m->esp;	/* 45ee53: mov dword ptr fs:[0], esp */
	m->esp -= 4; M32(m->esp) = 0x45ee5fu; native_call(m, 0x49fc20u);	/* 45ee5a: call 0x49fc20 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45ee5f: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45ee60: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45ee61: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45ee62: push edi */
	m->edi = m->ecx;	/* 45ee63: mov edi, ecx */
	m->esi = (DWORD)(m->esp + 0x2c0u);	/* 45ee65: lea esi, [esp + 0x2c0] */
	m->ebx = 0x5u;	/* 45ee6c: mov ebx, 5 */
L_45ee71:
	m->ecx = m->esi;	/* 45ee71: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x45ee78u; native_call(m, 0x45fff0u);	/* 45ee73: call 0x45fff0 */
	{ DWORD a_ = m->esi, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 45ee78: add esi, 0x28 */
	{ DWORD a_ = m->ebx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebx = r_; }	/* 45ee7b: dec ebx */
	if (!m->zf) goto L_45ee71;	/* 45ee7c: jne 0x45ee71 */
	m->esi = 0x4a9754u;	/* 45ee7e: mov esi, 0x4a9754 */
	m->ecx = (DWORD)(m->esp + 0x57cu);	/* 45ee83: lea ecx, [esp + 0x57c] */
	M32((DWORD)(m->esp + 0x57cu)) = m->esi;	/* 45ee8a: mov dword ptr [esp + 0x57c], esi */
	m->esp -= 4; M32(m->esp) = 0x45ee96u; native_call(m, 0x46f480u);	/* 45ee91: call 0x46f480 */
	m->ecx = (DWORD)(m->esp + 0xd7cu);	/* 45ee96: lea ecx, [esp + 0xd7c] */
	M32((DWORD)(m->esp + 0x88b8u)) = 0x0u;	/* 45ee9d: mov dword ptr [esp + 0x88b8], 0 */
	M32((DWORD)(m->esp + 0xd7cu)) = m->esi;	/* 45eea8: mov dword ptr [esp + 0xd7c], esi */
	m->esp -= 4; M32(m->esp) = 0x45eeb4u; native_call(m, 0x46f480u);	/* 45eeaf: call 0x46f480 */
	m->ecx = (DWORD)(m->esp + 0x157cu);	/* 45eeb4: lea ecx, [esp + 0x157c] */
	M8((DWORD)(m->esp + 0x88b8u)) = (BYTE)(0x1u);	/* 45eebb: mov byte ptr [esp + 0x88b8], 1 */
	M32((DWORD)(m->esp + 0x157cu)) = m->esi;	/* 45eec3: mov dword ptr [esp + 0x157c], esi */
	m->esp -= 4; M32(m->esp) = 0x45eecfu; native_call(m, 0x46f480u);	/* 45eeca: call 0x46f480 */
	m->ecx = (DWORD)(m->esp + 0x254cu);	/* 45eecf: lea ecx, [esp + 0x254c] */
	M8((DWORD)(m->esp + 0x88b8u)) = (BYTE)(0x2u);	/* 45eed6: mov byte ptr [esp + 0x88b8], 2 */
	M32((DWORD)(m->esp + 0x254cu)) = m->esi;	/* 45eede: mov dword ptr [esp + 0x254c], esi */
	m->esp -= 4; M32(m->esp) = 0x45eeeau; native_call(m, 0x46f480u);	/* 45eee5: call 0x46f480 */
	m->ecx = (DWORD)(m->esp + 0x351cu);	/* 45eeea: lea ecx, [esp + 0x351c] */
	M8((DWORD)(m->esp + 0x88b8u)) = (BYTE)(0x3u);	/* 45eef1: mov byte ptr [esp + 0x88b8], 3 */
	M32((DWORD)(m->esp + 0x351cu)) = m->esi;	/* 45eef9: mov dword ptr [esp + 0x351c], esi */
	m->esp -= 4; M32(m->esp) = 0x45ef05u; native_call(m, 0x46f480u);	/* 45ef00: call 0x46f480 */
	m->ecx = (DWORD)(m->esp + 0x4104u);	/* 45ef05: lea ecx, [esp + 0x4104] */
	M8((DWORD)(m->esp + 0x88b8u)) = (BYTE)(0x4u);	/* 45ef0c: mov byte ptr [esp + 0x88b8], 4 */
	M32((DWORD)(m->esp + 0x4104u)) = m->esi;	/* 45ef14: mov dword ptr [esp + 0x4104], esi */
	m->esp -= 4; M32(m->esp) = 0x45ef20u; native_call(m, 0x46f480u);	/* 45ef1b: call 0x46f480 */
	m->ecx = (DWORD)(m->esp + 0x58a4u);	/* 45ef20: lea ecx, [esp + 0x58a4] */
	M8((DWORD)(m->esp + 0x88b8u)) = (BYTE)(0x5u);	/* 45ef27: mov byte ptr [esp + 0x88b8], 5 */
	M32((DWORD)(m->esp + 0x58a4u)) = m->esi;	/* 45ef2f: mov dword ptr [esp + 0x58a4], esi */
	m->esp -= 4; M32(m->esp) = 0x45ef3bu; native_call(m, 0x46f480u);	/* 45ef36: call 0x46f480 */
	m->ecx = (DWORD)(m->esp + 0x7044u);	/* 45ef3b: lea ecx, [esp + 0x7044] */
	M8((DWORD)(m->esp + 0x88b8u)) = (BYTE)(0x6u);	/* 45ef42: mov byte ptr [esp + 0x88b8], 6 */
	M32((DWORD)(m->esp + 0x7044u)) = m->esi;	/* 45ef4a: mov dword ptr [esp + 0x7044], esi */
	m->esp -= 4; M32(m->esp) = 0x45ef56u; native_call(m, 0x46f480u);	/* 45ef51: call 0x46f480 */
	m->eax = M32((DWORD)(m->esp + 0x88c0u));	/* 45ef56: mov eax, dword ptr [esp + 0x88c0] */
	m->ecx = m->eax;	/* 45ef5d: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45ef5f: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45ef62: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45ef64: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45ef67: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45ef69: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45ef6c: add ecx, eax */
	m->eax = (DWORD)(m->edi + m->ecx*8 + 0x1cd93a8u);	/* 45ef6e: lea eax, [edi + ecx*8 + 0x1cd93a8] */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 45ef75: mov dword ptr [esp + 0x24], eax */
	{ DWORD a_ = M32((DWORD)(m->eax + 0x14cu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45ef79: cmp dword ptr [eax + 0x14c], 1 */
	if (m->zf) goto L_45f036;	/* 45ef80: je 0x45f036 */
	m->ecx = (DWORD)(m->esp + 0x7044u);	/* 45ef86: lea ecx, [esp + 0x7044] */
	M32((DWORD)(m->esp + 0x88b8u)) = 0xeu;	/* 45ef8d: mov dword ptr [esp + 0x88b8], 0xe */
	m->esp -= 4; M32(m->esp) = 0x45ef9du; native_call(m, 0x46f470u);	/* 45ef98: call 0x46f470 */
	m->ecx = (DWORD)(m->esp + 0x58a4u);	/* 45ef9d: lea ecx, [esp + 0x58a4] */
	M8((DWORD)(m->esp + 0x88b8u)) = (BYTE)(0xdu);	/* 45efa4: mov byte ptr [esp + 0x88b8], 0xd */
	m->esp -= 4; M32(m->esp) = 0x45efb1u; native_call(m, 0x46f470u);	/* 45efac: call 0x46f470 */
	m->ecx = (DWORD)(m->esp + 0x4104u);	/* 45efb1: lea ecx, [esp + 0x4104] */
	M8((DWORD)(m->esp + 0x88b8u)) = (BYTE)(0xcu);	/* 45efb8: mov byte ptr [esp + 0x88b8], 0xc */
	m->esp -= 4; M32(m->esp) = 0x45efc5u; native_call(m, 0x46f470u);	/* 45efc0: call 0x46f470 */
	m->ecx = (DWORD)(m->esp + 0x351cu);	/* 45efc5: lea ecx, [esp + 0x351c] */
	M8((DWORD)(m->esp + 0x88b8u)) = (BYTE)(0xbu);	/* 45efcc: mov byte ptr [esp + 0x88b8], 0xb */
	m->esp -= 4; M32(m->esp) = 0x45efd9u; native_call(m, 0x46f470u);	/* 45efd4: call 0x46f470 */
	m->ecx = (DWORD)(m->esp + 0x254cu);	/* 45efd9: lea ecx, [esp + 0x254c] */
	M8((DWORD)(m->esp + 0x88b8u)) = (BYTE)(0xau);	/* 45efe0: mov byte ptr [esp + 0x88b8], 0xa */
	m->esp -= 4; M32(m->esp) = 0x45efedu; native_call(m, 0x46f470u);	/* 45efe8: call 0x46f470 */
	m->ecx = (DWORD)(m->esp + 0x157cu);	/* 45efed: lea ecx, [esp + 0x157c] */
	M8((DWORD)(m->esp + 0x88b8u)) = (BYTE)(0x9u);	/* 45eff4: mov byte ptr [esp + 0x88b8], 9 */
	m->esp -= 4; M32(m->esp) = 0x45f001u; native_call(m, 0x46f470u);	/* 45effc: call 0x46f470 */
	m->ecx = (DWORD)(m->esp + 0xd7cu);	/* 45f001: lea ecx, [esp + 0xd7c] */
	M8((DWORD)(m->esp + 0x88b8u)) = (BYTE)(0x8u);	/* 45f008: mov byte ptr [esp + 0x88b8], 8 */
	m->esp -= 4; M32(m->esp) = 0x45f015u; native_call(m, 0x46f470u);	/* 45f010: call 0x46f470 */
	m->ecx = (DWORD)(m->esp + 0x57cu);	/* 45f015: lea ecx, [esp + 0x57c] */
	M32((DWORD)(m->esp + 0x88b8u)) = 0xffffffffu;	/* 45f01c: mov dword ptr [esp + 0x88b8], 0xffffffff */
	m->esp -= 4; M32(m->esp) = 0x45f02cu; native_call(m, 0x46f470u);	/* 45f027: call 0x46f470 */
	m->eax = 0x1u;	/* 45f02c: mov eax, 1 */
	goto L_45fea8;	/* 45f031: jmp 0x45fea8 */
L_45f036:
	m->ecx = M32((DWORD)(m->eax + 0x10cu));	/* 45f036: mov ecx, dword ptr [eax + 0x10c] */
	m->ebp = 0x3f800000u;	/* 45f03c: mov ebp, 0x3f800000 */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 45f041: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45f044: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45f047: sub eax, ecx */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 45f049: lea edx, [eax + eax*2] */
	m->eax = (DWORD)(m->ecx + m->edx*8 + 0x0u);	/* 45f04c: lea eax, [ecx + edx*8] */
	m->ecx = M32((DWORD)(m->edi + m->eax*2 + 0x1561e74u));	/* 45f04f: mov ecx, dword ptr [edi + eax*2 + 0x1561e74] */
	m->esi = (DWORD)(m->edi + m->eax*2 + 0x1561b68u);	/* 45f056: lea esi, [edi + eax*2 + 0x1561b68] */
	m->eax = m->ecx;	/* 45f05d: mov eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45f05f: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45f062: add eax, ecx */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45f064: lea edx, [eax + eax*4] */
	m->eax = (DWORD)(m->ecx + m->edx*4 + 0x0u);	/* 45f067: lea eax, [ecx + edx*4] */
	m->ecx = M32((DWORD)(m->esi + 0x310u));	/* 45f06a: mov ecx, dword ptr [esi + 0x310] */
	m->edx = (DWORD)(m->edi + m->eax*8 + 0x13c9b30u);	/* 45f070: lea edx, [edi + eax*8 + 0x13c9b30] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 45f077: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45f07a: shl eax, 3 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45f07d: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45f07f: lea eax, [eax + eax*4] */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45f082: shl eax, 1 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45f084: sub eax, ecx */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 45f086: lea ecx, [eax + eax*2] */
	m->eax = (DWORD)(m->edi + m->ecx*4 + 0x13eb004u);	/* 45f089: lea eax, [edi + ecx*4 + 0x13eb004] */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 45f090: mov dword ptr [esp + 0x20], eax */
	m->eax = M32((DWORD)(m->esi + 0x314u));	/* 45f094: mov eax, dword ptr [esi + 0x314] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 45f09a: lea ecx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 45f09d: lea eax, [eax + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45f0a0: shl eax, 8 */
	m->ecx = (DWORD)(m->eax + m->edi*1 + 0x140c8c0u);	/* 45f0a3: lea ecx, [eax + edi + 0x140c8c0] */
	m->eax = M32((DWORD)(m->esi + 0x318u));	/* 45f0aa: mov eax, dword ptr [esi + 0x318] */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 45f0b0: mov dword ptr [esp + 0x10], ecx */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45f0b4: lea ecx, [eax + eax*4] */
	{ DWORD a_ = m->ecx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45f0b7: shl ecx, 6 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45f0ba: sub ecx, eax */
	m->eax = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 45f0bc: lea eax, [eax + ecx*4] */
	m->ebx = (DWORD)(m->edi + m->eax*4 + 0x1447ec4u);	/* 45f0bf: lea ebx, [edi + eax*4 + 0x1447ec4] */
	m->eax = M32((DWORD)(m->esi + 0x31cu));	/* 45f0c6: mov eax, dword ptr [esi + 0x31c] */
	M32((DWORD)(m->esp + 0x18u)) = m->ebx;	/* 45f0cc: mov dword ptr [esp + 0x18], ebx */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 45f0d0: lea ecx, [eax + eax*2] */
	{ DWORD a_ = m->ecx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45f0d3: shl ecx, 6 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45f0d6: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45f0d8: shl ecx, 5 */
	m->eax = (DWORD)(m->ecx + m->edi*1 + 0x1486470u);	/* 45f0db: lea eax, [ecx + edi + 0x1486470] */
	m->ecx = 0x4u;	/* 45f0e2: mov ecx, 4 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 45f0e7: mov dword ptr [esp + 0x1c], eax */
	m->eax = (DWORD)(m->esp + 0x43cu);	/* 45f0eb: lea eax, [esp + 0x43c] */
L_45f0f2:
	M32((DWORD)(m->eax + 0xfffffff0u)) = m->ebp;	/* 45f0f2: mov dword ptr [eax - 0x10], ebp */
	M32((DWORD)(m->eax + 0x0u)) = 0x0u;	/* 45f0f5: mov dword ptr [eax], 0 */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45f0fb: add eax, 4 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 45f0fe: dec ecx */
	if (!m->zf) goto L_45f0f2;	/* 45f0ff: jne 0x45f0f2 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45f101: xor eax, eax */
	M32((DWORD)(m->esp + 0x44cu)) = 0x0u;	/* 45f103: mov dword ptr [esp + 0x44c], 0 */
	M32((DWORD)(m->esp + 0x450u)) = 0x3f800000u;	/* 45f10e: mov dword ptr [esp + 0x450], 0x3f800000 */
	M32((DWORD)(m->esp + 0x454u)) = 0x3f800000u;	/* 45f119: mov dword ptr [esp + 0x454], 0x3f800000 */
	M32((DWORD)(m->esp + 0x458u)) = m->eax;	/* 45f124: mov dword ptr [esp + 0x458], eax */
	M32((DWORD)(m->esp + 0x45cu)) = 0x3f800000u;	/* 45f12b: mov dword ptr [esp + 0x45c], 0x3f800000 */
	M32((DWORD)(m->esp + 0x460u)) = 0x3f800000u;	/* 45f136: mov dword ptr [esp + 0x460], 0x3f800000 */
	M32((DWORD)(m->esp + 0x464u)) = 0x3f800000u;	/* 45f141: mov dword ptr [esp + 0x464], 0x3f800000 */
	M32((DWORD)(m->esp + 0x468u)) = 0x3f800000u;	/* 45f14c: mov dword ptr [esp + 0x468], 0x3f800000 */
	M32((DWORD)(m->esp + 0x46cu)) = 0x3f800000u;	/* 45f157: mov dword ptr [esp + 0x46c], 0x3f800000 */
	M32((DWORD)(m->esp + 0x470u)) = m->eax;	/* 45f162: mov dword ptr [esp + 0x470], eax */
	m->ebp = (DWORD)(m->esi + 0x320u);	/* 45f169: lea ebp, [esi + 0x320] */
	M32((DWORD)(m->esp + 0x14u)) = 0x6u;	/* 45f16f: mov dword ptr [esp + 0x14], 6 */
L_45f177:
	m->ecx = M32((DWORD)(m->ebp + 0x0u));	/* 45f177: mov ecx, dword ptr [ebp] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45f17a: test ecx, ecx */
	if (m->sf != m->of) goto L_45f2c1;	/* 45f17c: jl 0x45f2c1 */
	m->eax = m->ecx;	/* 45f182: mov eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45f184: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45f187: sub eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45f189: shl eax, 2 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45f18c: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45f18e: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45f191: lea eax, [eax + eax*4] */
	{ DWORD a_ = M32((DWORD)(m->edi + m->eax*8 + 0x14d4874u)), b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f194: cmp dword ptr [edi + eax*8 + 0x14d4874], 0 */
	if (m->sf == m->of) goto L_45f2c1;	/* 45f19c: jge 0x45f2c1 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffe5u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45f1a2: add ecx, -0x1b */
	{ DWORD a_ = m->ecx, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f1a5: cmp ecx, 8 */
	if (!m->cf && !m->zf) goto L_45f2c1;	/* 45f1a8: ja 0x45f2c1 */
	switch (m->ecx) { case 0: goto L_45f1b5; case 1: goto L_45f1d7; case 2: goto L_45f1e4; case 3: goto L_45f1f1; case 4: goto L_45f1fe; case 5: goto L_45f20b; case 6: goto L_45f251; case 7: goto L_45f28f; case 8: goto L_45f2a5; default: abort(); }	/* 45f1ae: jmp dword ptr [ecx*4 + 0x45fec4] */
L_45f1b5:
	m->eax = (DWORD)(m->esp + 0x42cu);	/* 45f1b5: lea eax, [esp + 0x42c] */
	m->ecx = 0x4u;	/* 45f1bc: mov ecx, 4 */
L_45f1c1:
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 45f1c1: fld dword ptr [eax] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a94fcu));	/* 45f1c3: fadd dword ptr [0x4a94fc] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45f1c9: add eax, 4 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 45f1cc: dec ecx */
	MF((DWORD)(m->eax + 0xfffffffcu)) = (float)ST(0); FPOP();	/* 45f1cd: fstp dword ptr [eax - 4] */
	if (!m->zf) goto L_45f1c1;	/* 45f1d0: jne 0x45f1c1 */
	goto L_45f2c1;	/* 45f1d2: jmp 0x45f2c1 */
L_45f1d7:
	{ DWORD a_ = M32((DWORD)(m->esp + 0x444u)), b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(m->esp + 0x444u)) = r_; }	/* 45f1d7: add dword ptr [esp + 0x444], 0x64 */
	goto L_45f2c1;	/* 45f1df: jmp 0x45f2c1 */
L_45f1e4:
	{ DWORD a_ = M32((DWORD)(m->esp + 0x43cu)), b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(m->esp + 0x43cu)) = r_; }	/* 45f1e4: add dword ptr [esp + 0x43c], 0x64 */
	goto L_45f2c1;	/* 45f1ec: jmp 0x45f2c1 */
L_45f1f1:
	{ DWORD a_ = M32((DWORD)(m->esp + 0x440u)), b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(m->esp + 0x440u)) = r_; }	/* 45f1f1: add dword ptr [esp + 0x440], 0x64 */
	goto L_45f2c1;	/* 45f1f9: jmp 0x45f2c1 */
L_45f1fe:
	{ DWORD a_ = M32((DWORD)(m->esp + 0x448u)), b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(m->esp + 0x448u)) = r_; }	/* 45f1fe: add dword ptr [esp + 0x448], 0x64 */
	goto L_45f2c1;	/* 45f206: jmp 0x45f2c1 */
L_45f20b:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44cu)));	/* 45f20b: fld dword ptr [esp + 0x44c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9708u));	/* 45f212: fadd dword ptr [0x4a9708] */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x458u)), b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(m->esp + 0x458u)) = r_; }	/* 45f218: add dword ptr [esp + 0x458], 3 */
	MF((DWORD)(m->esp + 0x44cu)) = (float)ST(0); FPOP();	/* 45f220: fstp dword ptr [esp + 0x44c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x450u)));	/* 45f227: fld dword ptr [esp + 0x450] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 45f22e: fsub dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x450u)) = (float)ST(0); FPOP();	/* 45f234: fstp dword ptr [esp + 0x450] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x454u)));	/* 45f23b: fld dword ptr [esp + 0x454] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 45f242: fadd dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x454u)) = (float)ST(0); FPOP();	/* 45f248: fstp dword ptr [esp + 0x454] */
	goto L_45f2c1;	/* 45f24f: jmp 0x45f2c1 */
L_45f251:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x45cu)));	/* 45f251: fld dword ptr [esp + 0x45c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 45f258: fadd dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x45cu)) = (float)ST(0); FPOP();	/* 45f25e: fstp dword ptr [esp + 0x45c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x460u)));	/* 45f265: fld dword ptr [esp + 0x460] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 45f26c: fsub dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x460u)) = (float)ST(0); FPOP();	/* 45f272: fstp dword ptr [esp + 0x460] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x464u)));	/* 45f279: fld dword ptr [esp + 0x464] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 45f280: fsub dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x464u)) = (float)ST(0); FPOP();	/* 45f286: fstp dword ptr [esp + 0x464] */
	goto L_45f2c1;	/* 45f28d: jmp 0x45f2c1 */
L_45f28f:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x468u)));	/* 45f28f: fld dword ptr [esp + 0x468] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a94f8u));	/* 45f296: fadd dword ptr [0x4a94f8] */
	MF((DWORD)(m->esp + 0x468u)) = (float)ST(0); FPOP();	/* 45f29c: fstp dword ptr [esp + 0x468] */
	goto L_45f2c1;	/* 45f2a3: jmp 0x45f2c1 */
L_45f2a5:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x46cu)));	/* 45f2a5: fld dword ptr [esp + 0x46c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a94fcu));	/* 45f2ac: fadd dword ptr [0x4a94fc] */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x470u)), b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(m->esp + 0x470u)) = r_; }	/* 45f2b2: add dword ptr [esp + 0x470], 4 */
	MF((DWORD)(m->esp + 0x46cu)) = (float)ST(0); FPOP();	/* 45f2ba: fstp dword ptr [esp + 0x46c] */
L_45f2c1:
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 45f2c1: mov eax, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ebp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 45f2c5: add ebp, 4 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 45f2c8: dec eax */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 45f2c9: mov dword ptr [esp + 0x14], eax */
	if (!m->zf) goto L_45f177;	/* 45f2cd: jne 0x45f177 */
	m->eax = M32((DWORD)(m->esi + 0x44u));	/* 45f2d3: mov eax, dword ptr [esi + 0x44] */
	m->ebp = M32((DWORD)(m->esp + 0x458u));	/* 45f2d6: mov ebp, dword ptr [esp + 0x458] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 45f2dd: lea ecx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 45f2e0: lea eax, [eax + ecx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->eax*4 + 0x9f9084u)));	/* 45f2e3: fild dword ptr [eax*4 + 0x9f9084] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 45f2ea: fmul dword ptr [0x4a9420] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 45f2f0: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edx + 0xa94u));	/* 45f2f6: fmul dword ptr [edx + 0xa94] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x44cu));	/* 45f2fc: fadd dword ptr [esp + 0x44c] */
	{ long double t = ST(0); FPUSH(t); }	/* 45f303: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 45f305: fmul st(1) */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 45f307: fstp dword ptr [esp + 0x28] */
	m->eax = M32((DWORD)(m->esi + 0x44u));	/* 45f30b: mov eax, dword ptr [esi + 0x44] */
	ST(0) = ST(0); FPOP();	/* 45f30e: fstp st(0) */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 45f310: lea ecx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 45f313: lea eax, [eax + ecx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->eax*4 + 0x9f9084u)));	/* 45f316: fild dword ptr [eax*4 + 0x9f9084] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 45f31d: fmul dword ptr [0x4a9420] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 45f323: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edx + 0xa98u));	/* 45f329: fmul dword ptr [edx + 0xa98] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 45f32f: fstp dword ptr [esp + 0x2c] */
	m->ecx = M32((DWORD)(m->edx + 0xa9cu));	/* 45f333: mov ecx, dword ptr [edx + 0xa9c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x450u)));	/* 45f339: fld dword ptr [esp + 0x450] */
	{ DWORD a_ = m->ecx, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45f340: add ecx, ebp */
	M32((DWORD)(m->esp + 0x30u)) = m->ecx;	/* 45f342: mov dword ptr [esp + 0x30], ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edx + 0xaa0u));	/* 45f346: fmul dword ptr [edx + 0xaa0] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 45f34c: fstp dword ptr [esp + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x454u)));	/* 45f350: fld dword ptr [esp + 0x454] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edx + 0xaa4u));	/* 45f357: fmul dword ptr [edx + 0xaa4] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 45f35d: fstp dword ptr [esp + 0x38] */
	m->eax = M32((DWORD)(m->esi + 0x44u));	/* 45f361: mov eax, dword ptr [esi + 0x44] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 45f364: lea ecx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 45f367: lea eax, [eax + ecx*2] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 45f36a: mov ecx, dword ptr [esp + 0x20] */
	FPUSH((long double)(int)M32((DWORD)(m->eax*4 + 0x9f9088u)));	/* 45f36e: fild dword ptr [eax*4 + 0x9f9088] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 45f375: mov eax, dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 45f379: fmul dword ptr [0x4a9420] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 45f37f: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0xab0u));	/* 45f385: fmul dword ptr [ecx + 0xab0] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 45f38b: mov ecx, dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x468u));	/* 45f38f: fmul dword ptr [esp + 0x468] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 45f396: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x17f8u)));	/* 45f39a: fld dword ptr [eax + 0x17f8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x13d8u));	/* 45f3a0: fadd dword ptr [ebx + 0x13d8] */
	m->eax = M32((DWORD)(m->edi + 0x20f3ab8u));	/* 45f3a6: mov eax, dword ptr [edi + 0x20f3ab8] */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f3ac: cmp eax, 2 */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 45f3af: mov dword ptr [esp + 0x14], eax */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x12e8u));	/* 45f3b3: fadd dword ptr [ecx + 0x12e8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edx + 0xa90u));	/* 45f3b9: fadd dword ptr [edx + 0xa90] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 45f3bf: fstp dword ptr [esp + 0x40] */
	if (m->zf) goto L_45f42a;	/* 45f3c3: je 0x45f42a */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f3c5: cmp eax, 3 */
	if (m->zf) goto L_45f42a;	/* 45f3c8: je 0x45f42a */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f3ca: cmp eax, 4 */
	if (m->zf) goto L_45f42a;	/* 45f3cd: je 0x45f42a */
	{ DWORD a_ = m->eax, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f3cf: cmp eax, 5 */
	if (m->zf) goto L_45f42a;	/* 45f3d2: je 0x45f42a */
	{ DWORD a_ = m->eax, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f3d4: cmp eax, 6 */
	if (m->zf) goto L_45f42a;	/* 45f3d7: je 0x45f42a */
	{ DWORD a_ = m->eax, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f3d9: cmp eax, 7 */
	if (m->zf) goto L_45f42a;	/* 45f3dc: je 0x45f42a */
	{ DWORD a_ = m->eax, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f3de: cmp eax, 8 */
	if (m->zf) goto L_45f42a;	/* 45f3e1: je 0x45f42a */
	{ DWORD a_ = m->eax, b_ = 0x9u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f3e3: cmp eax, 9 */
	if (m->zf) goto L_45f42a;	/* 45f3e6: je 0x45f42a */
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f3e8: cmp eax, 0xa */
	if (m->zf) goto L_45f42a;	/* 45f3eb: je 0x45f42a */
	{ DWORD a_ = m->eax, b_ = 0xbu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f3ed: cmp eax, 0xb */
	if (m->zf) goto L_45f42a;	/* 45f3f0: je 0x45f42a */
	m->edx = (DWORD)(m->esi + 0x320u);	/* 45f3f2: lea edx, [esi + 0x320] */
	m->ebp = 0x6u;	/* 45f3f8: mov ebp, 6 */
L_45f3fd:
	m->ecx = M32((DWORD)(m->edx + 0x0u));	/* 45f3fd: mov ecx, dword ptr [edx] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45f3ff: test ecx, ecx */
	if (m->sf != m->of) goto L_45f424;	/* 45f401: jl 0x45f424 */
	m->eax = m->ecx;	/* 45f403: mov eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45f405: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45f408: sub eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45f40a: shl eax, 2 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 45f40d: fld dword ptr [esp + 0x40] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45f411: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45f413: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45f416: lea eax, [eax + eax*4] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + m->eax*8 + 0x14d486cu));	/* 45f419: fadd dword ptr [edi + eax*8 + 0x14d486c] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 45f420: fstp dword ptr [esp + 0x40] */
L_45f424:
	{ DWORD a_ = m->edx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45f424: add edx, 4 */
	{ DWORD a_ = m->ebp, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebp = r_; }	/* 45f427: dec ebp */
	if (!m->zf) goto L_45f3fd;	/* 45f428: jne 0x45f3fd */
L_45f42a:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 45f42a: fld dword ptr [esp + 0x40] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x3cu)); FPOP();	/* 45f42e: fcomp dword ptr [esp + 0x3c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45f432: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45f434: test ah, 0x41 */
	if (!m->zf) goto L_45f44d;	/* 45f437: jne 0x45f44d */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 45f439: fld dword ptr [esp + 0x40] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 45f43d: fsub dword ptr [esp + 0x3c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 45f441: fdiv dword ptr [esp + 0x3c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a947cu));	/* 45f445: fmul dword ptr [0x4a947c] */
	goto L_45f453;	/* 45f44b: jmp 0x45f453 */
L_45f44d:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93e8u)));	/* 45f44d: fld dword ptr [0x4a93e8] */
L_45f453:
	m->eax = M32((DWORD)(m->esi + 0x44u));	/* 45f453: mov eax, dword ptr [esi + 0x44] */
	m->ebx = M32((DWORD)(m->esp + 0x20u));	/* 45f456: mov ebx, dword ptr [esp + 0x20] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 45f45a: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 45f45d: lea edx, [eax + ecx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->edx*4 + 0x9f9080u)));	/* 45f460: fild dword ptr [edx*4 + 0x9f9080] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 45f467: fmul dword ptr [0x4a9420] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 45f46d: fadd dword ptr [0x4a9424] */
	ST(0) = ST(0) * (long double)(int)M32((DWORD)(m->ebx + 0xab4u));	/* 45f473: fimul dword ptr [ebx + 0xab4] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 45f479: fadd dword ptr [0x4a942c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 45f47f: call 0x49ec14 */
	M32((DWORD)(m->esp + 0x44u)) = m->eax;	/* 45f484: mov dword ptr [esp + 0x44], eax */
	m->eax = M32((DWORD)(m->esi + 0x44u));	/* 45f488: mov eax, dword ptr [esi + 0x44] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 45f48b: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 45f48e: lea edx, [eax + ecx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->edx*4 + 0x9f9080u)));	/* 45f491: fild dword ptr [edx*4 + 0x9f9080] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 45f498: fmul dword ptr [0x4a9420] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 45f49e: fadd dword ptr [0x4a9424] */
	ST(0) = ST(0) * (long double)(int)M32((DWORD)(m->ebx + 0xab8u));	/* 45f4a4: fimul dword ptr [ebx + 0xab8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x46cu));	/* 45f4aa: fmul dword ptr [esp + 0x46c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 45f4b1: fadd dword ptr [0x4a942c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 45f4b7: call 0x49ec14 */
	m->ebx = M32((DWORD)(m->esp + 0x10u));	/* 45f4bc: mov ebx, dword ptr [esp + 0x10] */
	M32((DWORD)(m->esp + 0x48u)) = m->eax;	/* 45f4c0: mov dword ptr [esp + 0x48], eax */
	m->ebp = (DWORD)(m->esp + 0x43cu);	/* 45f4c4: lea ebp, [esp + 0x43c] */
	M32((DWORD)(m->esp + 0x10u)) = 0x4u;	/* 45f4cb: mov dword ptr [esp + 0x10], 4 */
	m->eax = M32((DWORD)(m->ebx + 0x12ecu));	/* 45f4d3: mov eax, dword ptr [ebx + 0x12ec] */
	{ DWORD a_ = m->ebx, b_ = 0x12f0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 45f4d9: add ebx, 0x12f0 */
	M32((DWORD)(m->esp + 0x4cu)) = m->eax;	/* 45f4df: mov dword ptr [esp + 0x4c], eax */
L_45f4e3:
	FPUSH((long double)(int)M32((DWORD)(m->ebx + 0x0u)));	/* 45f4e3: fild dword ptr [ebx] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0xfffffff0u));	/* 45f4e5: fmul dword ptr [ebp - 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 45f4e8: fadd dword ptr [0x4a942c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 45f4ee: call 0x49ec14 */
	m->ecx = M32((DWORD)(m->ebp + 0x0u));	/* 45f4f3: mov ecx, dword ptr [ebp] */
	{ DWORD a_ = m->ebx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 45f4f6: add ebx, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45f4f9: add eax, ecx */
	M32((DWORD)(m->ebp + 0xfffffc14u)) = m->eax;	/* 45f4fb: mov dword ptr [ebp - 0x3ec], eax */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 45f501: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ebp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 45f505: add ebp, 4 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 45f508: dec eax */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 45f509: mov dword ptr [esp + 0x10], eax */
	if (!m->zf) goto L_45f4e3;	/* 45f50d: jne 0x45f4e3 */
	m->eax = M32((DWORD)(m->esi + 0x44u));	/* 45f50f: mov eax, dword ptr [esi + 0x44] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 45f512: fsubr dword ptr [0x4a9424] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 45f518: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 45f51b: lea edx, [eax + ecx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->edx*4 + 0x9f9078u)));	/* 45f51e: fild dword ptr [edx*4 + 0x9f9078] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 45f525: mov edx, dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 45f529: fmul dword ptr [0x4a9420] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 45f52f: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edx + 0x13dcu));	/* 45f535: fmul dword ptr [edx + 0x13dc] */
	ST(0) = ST(0) * ST(1);	/* 45f53b: fmul st(1) */
	MF((DWORD)(m->esp + 0x60u)) = (float)ST(0);	/* 45f53d: fst dword ptr [esp + 0x60] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45f541: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45f547: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45f549: test ah, 1 */
	if (m->zf) goto L_45f556;	/* 45f54c: je 0x45f556 */
	M32((DWORD)(m->esp + 0x60u)) = 0x0u;	/* 45f54e: mov dword ptr [esp + 0x60], 0 */
L_45f556:
	m->ebx = M32((DWORD)(m->edi + 0x20f3accu));	/* 45f556: mov ebx, dword ptr [edi + 0x20f3acc] */
	{ DWORD a_ = m->ebx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f55c: cmp ebx, 1 */
	if (!m->zf) goto L_45f56f;	/* 45f55f: jne 0x45f56f */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x60u)));	/* 45f561: fld dword ptr [esp + 0x60] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9704u));	/* 45f565: fmul dword ptr [0x4a9704] */
	MF((DWORD)(m->esp + 0x60u)) = (float)ST(0); FPOP();	/* 45f56b: fstp dword ptr [esp + 0x60] */
L_45f56f:
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 45f56f: mov ecx, dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x45cu)));	/* 45f573: fld dword ptr [esp + 0x45c] */
	m->eax = M32((DWORD)(m->ecx + 0x1800u));	/* 45f57a: mov eax, dword ptr [ecx + 0x1800] */
	M32((DWORD)(m->esp + 0x68u)) = m->eax;	/* 45f580: mov dword ptr [esp + 0x68], eax */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x1804u));	/* 45f584: fmul dword ptr [ecx + 0x1804] */
	MF((DWORD)(m->esp + 0x6cu)) = (float)ST(0); FPOP();	/* 45f58a: fstp dword ptr [esp + 0x6c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x460u)));	/* 45f58e: fld dword ptr [esp + 0x460] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x1808u));	/* 45f595: fmul dword ptr [ecx + 0x1808] */
	MF((DWORD)(m->esp + 0x70u)) = (float)ST(0); FPOP();	/* 45f59b: fstp dword ptr [esp + 0x70] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x464u)));	/* 45f59f: fld dword ptr [esp + 0x464] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x180cu));	/* 45f5a6: fmul dword ptr [ecx + 0x180c] */
	MF((DWORD)(m->esp + 0x74u)) = (float)ST(0); FPOP();	/* 45f5ac: fstp dword ptr [esp + 0x74] */
	m->eax = M32((DWORD)(m->esi + 0x44u));	/* 45f5b0: mov eax, dword ptr [esi + 0x44] */
	m->ebp = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 45f5b3: lea ebp, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->ebp*2 + 0x0u);	/* 45f5b6: lea eax, [eax + ebp*2] */
	FPUSH((long double)(int)M32((DWORD)(m->eax*4 + 0x9f907cu)));	/* 45f5b9: fild dword ptr [eax*4 + 0x9f907c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 45f5c0: fmul dword ptr [0x4a9420] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edx + 0x13e4u));	/* 45f5c6: fadd dword ptr [edx + 0x13e4] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 45f5cc: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x1810u));	/* 45f5d2: fmul dword ptr [ecx + 0x1810] */
	ST(0) = ST(0) * ST(1);	/* 45f5d8: fmul st(1) */
	MF((DWORD)(m->esp + 0x78u)) = (float)ST(0);	/* 45f5da: fst dword ptr [esp + 0x78] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f4u)); FPOP();	/* 45f5de: fcomp dword ptr [0x4a93f4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45f5e4: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45f5e6: test ah, 1 */
	if (m->zf) goto L_45f5f3;	/* 45f5e9: je 0x45f5f3 */
	M32((DWORD)(m->esp + 0x78u)) = 0x42c80000u;	/* 45f5eb: mov dword ptr [esp + 0x78], 0x42c80000 */
L_45f5f3:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x78u)));	/* 45f5f3: fld dword ptr [esp + 0x78] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edx + 0x13e0u));	/* 45f5f7: fmul dword ptr [edx + 0x13e0] */
	m->ebp = 0x1u;	/* 45f5fd: mov ebp, 1 */
	{ DWORD a_ = m->ebx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f602: cmp ebx, ebp */
	MF((DWORD)(m->esp + 0x64u)) = (float)ST(0); FPOP();	/* 45f604: fstp dword ptr [esp + 0x64] */
	if (!m->zf) goto L_45f618;	/* 45f608: jne 0x45f618 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x64u)));	/* 45f60a: fld dword ptr [esp + 0x64] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9704u));	/* 45f60e: fmul dword ptr [0x4a9704] */
	MF((DWORD)(m->esp + 0x64u)) = (float)ST(0); FPOP();	/* 45f614: fstp dword ptr [esp + 0x64] */
L_45f618:
	m->eax = M32((DWORD)(m->esi + 0x44u));	/* 45f618: mov eax, dword ptr [esi + 0x44] */
	m->ebx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 45f61b: lea ebx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->ebx*2 + 0x0u);	/* 45f61e: lea eax, [eax + ebx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->eax*4 + 0x9f907cu)));	/* 45f621: fild dword ptr [eax*4 + 0x9f907c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 45f628: fmul dword ptr [0x4a9420] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edx + 0x13e8u));	/* 45f62e: fadd dword ptr [edx + 0x13e8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 45f634: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x1814u));	/* 45f63a: fmul dword ptr [ecx + 0x1814] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x78u));	/* 45f640: fdiv dword ptr [esp + 0x78] */
	ST(0) = ST(0) * ST(1);	/* 45f644: fmul st(1) */
	MF((DWORD)(m->esp + 0x7cu)) = (float)ST(0);	/* 45f646: fst dword ptr [esp + 0x7c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45f64a: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45f650: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45f652: test ah, 1 */
	if (m->zf) goto L_45f65f;	/* 45f655: je 0x45f65f */
	M32((DWORD)(m->esp + 0x7cu)) = 0x0u;	/* 45f657: mov dword ptr [esp + 0x7c], 0 */
L_45f65f:
	m->eax = M32((DWORD)(m->esi + 0x44u));	/* 45f65f: mov eax, dword ptr [esi + 0x44] */
	m->ebx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 45f662: lea ebx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->ebx*2 + 0x0u);	/* 45f665: lea eax, [eax + ebx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->eax*4 + 0x9f907cu)));	/* 45f668: fild dword ptr [eax*4 + 0x9f907c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 45f66f: fmul dword ptr [0x4a9420] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edx + 0x13ecu));	/* 45f675: fadd dword ptr [edx + 0x13ec] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 45f67b: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x1818u));	/* 45f681: fmul dword ptr [ecx + 0x1818] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x78u));	/* 45f687: fdiv dword ptr [esp + 0x78] */
	ST(0) = ST(0) * ST(1);	/* 45f68b: fmul st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9474u));	/* 45f68d: fmul dword ptr [0x4a9474] */
	MF((DWORD)(m->esp + 0x80u)) = (float)ST(0);	/* 45f693: fst dword ptr [esp + 0x80] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45f69a: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45f6a0: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45f6a2: test ah, 0x41 */
	if (!m->zf) goto L_45f6b2;	/* 45f6a5: jne 0x45f6b2 */
	M32((DWORD)(m->esp + 0x80u)) = 0x0u;	/* 45f6a7: mov dword ptr [esp + 0x80], 0 */
L_45f6b2:
	m->esi = M32((DWORD)(m->esi + 0x44u));	/* 45f6b2: mov esi, dword ptr [esi + 0x44] */
	m->eax = (DWORD)(m->esi + m->esi*8 + 0x0u);	/* 45f6b5: lea eax, [esi + esi*8] */
	m->eax = (DWORD)(m->esi + m->eax*2 + 0x0u);	/* 45f6b8: lea eax, [esi + eax*2] */
	FPUSH((long double)(int)M32((DWORD)(m->eax*4 + 0x9f907cu)));	/* 45f6bb: fild dword ptr [eax*4 + 0x9f907c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 45f6c2: fmul dword ptr [0x4a9420] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edx + 0x13f0u));	/* 45f6c8: fadd dword ptr [edx + 0x13f0] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 45f6ce: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x181cu));	/* 45f6d4: fmul dword ptr [ecx + 0x181c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x78u));	/* 45f6da: fdiv dword ptr [esp + 0x78] */
	ST(0) = ST(0) * ST(1);	/* 45f6de: fmul st(1) */
	MF((DWORD)(m->esp + 0x84u)) = (float)ST(0); FPOP();	/* 45f6e0: fstp dword ptr [esp + 0x84] */
	ST(0) = ST(0); FPOP();	/* 45f6e7: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x84u)));	/* 45f6e9: fld dword ptr [esp + 0x84] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45f6f0: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45f6f6: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45f6f8: test ah, 1 */
	if (m->zf) goto L_45f708;	/* 45f6fb: je 0x45f708 */
	M32((DWORD)(m->esp + 0x84u)) = 0x0u;	/* 45f6fd: mov dword ptr [esp + 0x84], 0 */
L_45f708:
	m->ecx = M32((DWORD)(m->esp + 0x78u));	/* 45f708: mov ecx, dword ptr [esp + 0x78] */
	m->eax = M32((DWORD)(m->edi + 0x20f3ad4u));	/* 45f70c: mov eax, dword ptr [edi + 0x20f3ad4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x84u)));	/* 45f712: fld dword ptr [esp + 0x84] */
	m->esi = M32((DWORD)(m->esp + 0x24u));	/* 45f719: mov esi, dword ptr [esp + 0x24] */
	M32((DWORD)(m->esp + 0x90u)) = m->ecx;	/* 45f71d: mov dword ptr [esp + 0x90], ecx */
	ST(0) = -ST(0);	/* 45f724: fchs  */
	MF((DWORD)(m->esp + 0x88u)) = (float)ST(0); FPOP();	/* 45f726: fstp dword ptr [esp + 0x88] */
	m->edx = 0x64u;	/* 45f72d: mov edx, 0x64 */
	m->ecx = 0xau;	/* 45f732: mov ecx, 0xa */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f737: cmp eax, ebp */
	M32((DWORD)(m->esp + 0x8cu)) = m->edx;	/* 45f739: mov dword ptr [esp + 0x8c], edx */
	M32((DWORD)(m->esp + 0x94u)) = 0x44610000u;	/* 45f740: mov dword ptr [esp + 0x94], 0x44610000 */
	M32((DWORD)(m->esp + 0x98u)) = 0x40400000u;	/* 45f74b: mov dword ptr [esp + 0x98], 0x40400000 */
	M32((DWORD)(m->esp + 0x9cu)) = m->ecx;	/* 45f756: mov dword ptr [esp + 0x9c], ecx */
	M32((DWORD)(m->esp + 0xa0u)) = 0x0u;	/* 45f75d: mov dword ptr [esp + 0xa0], 0 */
	M32((DWORD)(m->esp + 0xa4u)) = 0x447a0000u;	/* 45f768: mov dword ptr [esp + 0xa4], 0x447a0000 */
	M32((DWORD)(m->esp + 0xa8u)) = 0x43fa0000u;	/* 45f773: mov dword ptr [esp + 0xa8], 0x43fa0000 */
	M32((DWORD)(m->esp + 0xacu)) = 0x40000000u;	/* 45f77e: mov dword ptr [esp + 0xac], 0x40000000 */
	M32((DWORD)(m->esp + 0xb0u)) = 0x3f800000u;	/* 45f789: mov dword ptr [esp + 0xb0], 0x3f800000 */
	M32((DWORD)(m->esp + 0xb4u)) = 0x457a0000u;	/* 45f794: mov dword ptr [esp + 0xb4], 0x457a0000 */
	M32((DWORD)(m->esp + 0xb8u)) = 0x40a00000u;	/* 45f79f: mov dword ptr [esp + 0xb8], 0x40a00000 */
	M32((DWORD)(m->esp + 0xbcu)) = 0x3f800000u;	/* 45f7aa: mov dword ptr [esp + 0xbc], 0x3f800000 */
	if (!m->zf) goto L_45f815;	/* 45f7b5: jne 0x45f815 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x4d8u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f7b7: cmp dword ptr [esi + 0x4d8], ebp */
	if (!m->zf) goto L_45f7d7;	/* 45f7bd: jne 0x45f7d7 */
	M32((DWORD)(m->esp + 0x41cu)) = 0x447a0000u;	/* 45f7bf: mov dword ptr [esp + 0x41c], 0x447a0000 */
	M32((DWORD)(m->esp + 0x424u)) = 0x447a0000u;	/* 45f7ca: mov dword ptr [esp + 0x424], 0x447a0000 */
	goto L_45f815;	/* 45f7d5: jmp 0x45f815 */
L_45f7d7:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x41cu)));	/* 45f7d7: fld dword ptr [esp + 0x41c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a940cu)); FPOP();	/* 45f7de: fcomp dword ptr [0x4a940c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45f7e4: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45f7e6: test ah, 0x41 */
	if (!m->zf) goto L_45f7f6;	/* 45f7e9: jne 0x45f7f6 */
	M32((DWORD)(m->esp + 0x41cu)) = 0x0u;	/* 45f7eb: mov dword ptr [esp + 0x41c], 0 */
L_45f7f6:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x424u)));	/* 45f7f6: fld dword ptr [esp + 0x424] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a940cu)); FPOP();	/* 45f7fd: fcomp dword ptr [0x4a940c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45f803: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45f805: test ah, 0x41 */
	if (!m->zf) goto L_45f815;	/* 45f808: jne 0x45f815 */
	M32((DWORD)(m->esp + 0x424u)) = 0x0u;	/* 45f80a: mov dword ptr [esp + 0x424], 0 */
L_45f815:
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 45f815: mov eax, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->eax, b_ = 0xfffffffeu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45f819: add eax, -2 */
	{ DWORD a_ = m->eax, b_ = 0x9u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f81c: cmp eax, 9 */
	if (!m->cf && !m->zf) goto L_45f8b2;	/* 45f81f: ja 0x45f8b2 */
	switch (m->eax) { case 0: goto L_45f82c; case 1: goto L_45f82c; case 2: goto L_45f846; case 3: goto L_45f846; case 4: goto L_45f865; case 5: goto L_45f865; case 6: goto L_45f885; case 7: goto L_45f885; case 8: goto L_45f8a5; case 9: goto L_45f8a5; default: abort(); }	/* 45f825: jmp dword ptr [eax*4 + 0x45fee8] */
L_45f82c:
	M32((DWORD)(m->esp + 0x44u)) = m->ecx;	/* 45f82c: mov dword ptr [esp + 0x44], ecx */
	M32((DWORD)(m->esp + 0x48u)) = m->ecx;	/* 45f830: mov dword ptr [esp + 0x48], ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45f834: xor eax, eax */
L_45f836:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45f836: test eax, eax */
	if (!m->zf) goto L_45f83e;	/* 45f838: jne 0x45f83e */
	M32((DWORD)(m->esp + 0x50u)) = m->edx;	/* 45f83a: mov dword ptr [esp + 0x50], edx */
L_45f83e:
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 45f83e: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f83f: cmp eax, 4 */
	if (m->sf != m->of) goto L_45f836;	/* 45f842: jl 0x45f836 */
	goto L_45f8b2;	/* 45f844: jmp 0x45f8b2 */
L_45f846:
	m->eax = 0x96u;	/* 45f846: mov eax, 0x96 */
	M32((DWORD)(m->esp + 0x44u)) = m->eax;	/* 45f84b: mov dword ptr [esp + 0x44], eax */
	M32((DWORD)(m->esp + 0x48u)) = m->eax;	/* 45f84f: mov dword ptr [esp + 0x48], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45f853: xor eax, eax */
L_45f855:
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f855: cmp eax, ebp */
	if (!m->zf) goto L_45f85d;	/* 45f857: jne 0x45f85d */
	M32((DWORD)(m->esp + 0x54u)) = m->edx;	/* 45f859: mov dword ptr [esp + 0x54], edx */
L_45f85d:
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 45f85d: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f85e: cmp eax, 4 */
	if (m->sf != m->of) goto L_45f855;	/* 45f861: jl 0x45f855 */
	goto L_45f8b2;	/* 45f863: jmp 0x45f8b2 */
L_45f865:
	m->eax = 0x96u;	/* 45f865: mov eax, 0x96 */
	M32((DWORD)(m->esp + 0x44u)) = m->eax;	/* 45f86a: mov dword ptr [esp + 0x44], eax */
	M32((DWORD)(m->esp + 0x48u)) = m->eax;	/* 45f86e: mov dword ptr [esp + 0x48], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45f872: xor eax, eax */
L_45f874:
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f874: cmp eax, 2 */
	if (!m->zf) goto L_45f87d;	/* 45f877: jne 0x45f87d */
	M32((DWORD)(m->esp + 0x58u)) = m->edx;	/* 45f879: mov dword ptr [esp + 0x58], edx */
L_45f87d:
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 45f87d: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f87e: cmp eax, 4 */
	if (m->sf != m->of) goto L_45f874;	/* 45f881: jl 0x45f874 */
	goto L_45f8b2;	/* 45f883: jmp 0x45f8b2 */
L_45f885:
	m->eax = 0x96u;	/* 45f885: mov eax, 0x96 */
	M32((DWORD)(m->esp + 0x44u)) = m->eax;	/* 45f88a: mov dword ptr [esp + 0x44], eax */
	M32((DWORD)(m->esp + 0x48u)) = m->eax;	/* 45f88e: mov dword ptr [esp + 0x48], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45f892: xor eax, eax */
L_45f894:
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f894: cmp eax, 3 */
	if (!m->zf) goto L_45f89d;	/* 45f897: jne 0x45f89d */
	M32((DWORD)(m->esp + 0x5cu)) = m->edx;	/* 45f899: mov dword ptr [esp + 0x5c], edx */
L_45f89d:
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 45f89d: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f89e: cmp eax, 4 */
	if (m->sf != m->of) goto L_45f894;	/* 45f8a1: jl 0x45f894 */
	goto L_45f8b2;	/* 45f8a3: jmp 0x45f8b2 */
L_45f8a5:
	m->eax = 0x96u;	/* 45f8a5: mov eax, 0x96 */
	M32((DWORD)(m->esp + 0x44u)) = m->eax;	/* 45f8aa: mov dword ptr [esp + 0x44], eax */
	M32((DWORD)(m->esp + 0x48u)) = m->eax;	/* 45f8ae: mov dword ptr [esp + 0x48], eax */
L_45f8b2:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 45f8b2: fld dword ptr [esi] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 45f8b4: fsub dword ptr [esp + 0x28] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 45f8b8: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45f8be: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45f8c0: test ah, 1 */
	if (m->zf) goto L_45f8c7;	/* 45f8c3: je 0x45f8c7 */
	ST(0) = -ST(0);	/* 45f8c5: fchs  */
L_45f8c7:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93ecu)); FPOP();	/* 45f8c7: fcomp dword ptr [0x4a93ec] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45f8cd: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45f8cf: test ah, 0x41 */
	if (m->zf) goto L_45fe00;	/* 45f8d2: je 0x45fe00 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 45f8d8: fld dword ptr [esi + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x2cu));	/* 45f8db: fsub dword ptr [esp + 0x2c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 45f8df: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45f8e5: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45f8e7: test ah, 1 */
	if (m->zf) goto L_45f8ee;	/* 45f8ea: je 0x45f8ee */
	ST(0) = -ST(0);	/* 45f8ec: fchs  */
L_45f8ee:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93ecu)); FPOP();	/* 45f8ee: fcomp dword ptr [0x4a93ec] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45f8f4: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45f8f6: test ah, 0x41 */
	if (m->zf) goto L_45fe00;	/* 45f8f9: je 0x45fe00 */
	m->ecx = M32((DWORD)(m->esi + 0x8u));	/* 45f8ff: mov ecx, dword ptr [esi + 8] */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 45f902: mov eax, dword ptr [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f906: cmp ecx, eax */
	if (!m->zf) goto L_45fe00;	/* 45f908: jne 0x45fe00 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0xcu)));	/* 45f90e: fld dword ptr [esi + 0xc] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 45f911: fsub dword ptr [esp + 0x34] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 45f915: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45f91b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45f91d: test ah, 1 */
	if (m->zf) goto L_45f924;	/* 45f920: je 0x45f924 */
	ST(0) = -ST(0);	/* 45f922: fchs  */
L_45f924:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93ecu)); FPOP();	/* 45f924: fcomp dword ptr [0x4a93ec] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45f92a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45f92c: test ah, 0x41 */
	if (m->zf) goto L_45fe00;	/* 45f92f: je 0x45fe00 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x10u)));	/* 45f935: fld dword ptr [esi + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x38u));	/* 45f938: fsub dword ptr [esp + 0x38] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 45f93c: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45f942: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45f944: test ah, 1 */
	if (m->zf) goto L_45f94b;	/* 45f947: je 0x45f94b */
	ST(0) = -ST(0);	/* 45f949: fchs  */
L_45f94b:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93ecu)); FPOP();	/* 45f94b: fcomp dword ptr [0x4a93ec] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45f951: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45f953: test ah, 0x41 */
	if (m->zf) goto L_45fe00;	/* 45f956: je 0x45fe00 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x14u)));	/* 45f95c: fld dword ptr [esi + 0x14] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 45f95f: fsub dword ptr [esp + 0x3c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 45f963: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45f969: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45f96b: test ah, 1 */
	if (m->zf) goto L_45f972;	/* 45f96e: je 0x45f972 */
	ST(0) = -ST(0);	/* 45f970: fchs  */
L_45f972:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93ecu)); FPOP();	/* 45f972: fcomp dword ptr [0x4a93ec] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45f978: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45f97a: test ah, 0x41 */
	if (m->zf) goto L_45fe00;	/* 45f97d: je 0x45fe00 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x18u)));	/* 45f983: fld dword ptr [esi + 0x18] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 45f986: fsub dword ptr [esp + 0x40] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 45f98a: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45f990: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45f992: test ah, 1 */
	if (m->zf) goto L_45f999;	/* 45f995: je 0x45f999 */
	ST(0) = -ST(0);	/* 45f997: fchs  */
L_45f999:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93ecu)); FPOP();	/* 45f999: fcomp dword ptr [0x4a93ec] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45f99f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45f9a1: test ah, 0x41 */
	if (m->zf) goto L_45fe00;	/* 45f9a4: je 0x45fe00 */
	m->edx = M32((DWORD)(m->esp + 0x44u));	/* 45f9aa: mov edx, dword ptr [esp + 0x44] */
	m->eax = M32((DWORD)(m->esi + 0x1cu));	/* 45f9ae: mov eax, dword ptr [esi + 0x1c] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f9b1: cmp eax, edx */
	if (!m->zf) goto L_45fe00;	/* 45f9b3: jne 0x45fe00 */
	m->eax = M32((DWORD)(m->esp + 0x48u));	/* 45f9b9: mov eax, dword ptr [esp + 0x48] */
	m->ecx = M32((DWORD)(m->esi + 0x20u));	/* 45f9bd: mov ecx, dword ptr [esi + 0x20] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f9c0: cmp ecx, eax */
	if (!m->zf) goto L_45fe00;	/* 45f9c2: jne 0x45fe00 */
	m->ecx = M32((DWORD)(m->esi + 0x24u));	/* 45f9c8: mov ecx, dword ptr [esi + 0x24] */
	m->eax = M32((DWORD)(m->esp + 0x4cu));	/* 45f9cb: mov eax, dword ptr [esp + 0x4c] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f9cf: cmp ecx, eax */
	if (!m->zf) goto L_45fe00;	/* 45f9d1: jne 0x45fe00 */
	m->edx = M32((DWORD)(m->esp + 0x50u));	/* 45f9d7: mov edx, dword ptr [esp + 0x50] */
	m->eax = M32((DWORD)(m->esi + 0x28u));	/* 45f9db: mov eax, dword ptr [esi + 0x28] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f9de: cmp eax, edx */
	if (!m->zf) goto L_45fe00;	/* 45f9e0: jne 0x45fe00 */
	m->ebp = M32((DWORD)(m->esi + 0x2cu));	/* 45f9e6: mov ebp, dword ptr [esi + 0x2c] */
	m->eax = M32((DWORD)(m->esp + 0x54u));	/* 45f9e9: mov eax, dword ptr [esp + 0x54] */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f9ed: cmp ebp, eax */
	if (!m->zf) goto L_45fe00;	/* 45f9ef: jne 0x45fe00 */
	m->ebx = M32((DWORD)(m->esi + 0x30u));	/* 45f9f5: mov ebx, dword ptr [esi + 0x30] */
	m->eax = M32((DWORD)(m->esp + 0x58u));	/* 45f9f8: mov eax, dword ptr [esp + 0x58] */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45f9fc: cmp ebx, eax */
	if (!m->zf) goto L_45fe00;	/* 45f9fe: jne 0x45fe00 */
	m->edi = M32((DWORD)(m->esi + 0x34u));	/* 45fa04: mov edi, dword ptr [esi + 0x34] */
	m->eax = M32((DWORD)(m->esp + 0x5cu));	/* 45fa07: mov eax, dword ptr [esp + 0x5c] */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45fa0b: cmp edi, eax */
	if (!m->zf) goto L_45fe00;	/* 45fa0d: jne 0x45fe00 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x38u)));	/* 45fa13: fld dword ptr [esi + 0x38] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x60u));	/* 45fa16: fsub dword ptr [esp + 0x60] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 45fa1a: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45fa20: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45fa22: test ah, 1 */
	if (m->zf) goto L_45fa29;	/* 45fa25: je 0x45fa29 */
	ST(0) = -ST(0);	/* 45fa27: fchs  */
L_45fa29:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93ecu)); FPOP();	/* 45fa29: fcomp dword ptr [0x4a93ec] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45fa2f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45fa31: test ah, 0x41 */
	if (m->zf) goto L_45fe00;	/* 45fa34: je 0x45fe00 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x44u)));	/* 45fa3a: fld dword ptr [esi + 0x44] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x6cu));	/* 45fa3d: fsub dword ptr [esp + 0x6c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 45fa41: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45fa47: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45fa49: test ah, 1 */
	if (m->zf) goto L_45fa50;	/* 45fa4c: je 0x45fa50 */
	ST(0) = -ST(0);	/* 45fa4e: fchs  */
L_45fa50:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93ecu)); FPOP();	/* 45fa50: fcomp dword ptr [0x4a93ec] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45fa56: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45fa58: test ah, 0x41 */
	if (m->zf) goto L_45fe00;	/* 45fa5b: je 0x45fe00 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x48u)));	/* 45fa61: fld dword ptr [esi + 0x48] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x70u));	/* 45fa64: fsub dword ptr [esp + 0x70] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 45fa68: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45fa6e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45fa70: test ah, 1 */
	if (m->zf) goto L_45fa77;	/* 45fa73: je 0x45fa77 */
	ST(0) = -ST(0);	/* 45fa75: fchs  */
L_45fa77:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93ecu)); FPOP();	/* 45fa77: fcomp dword ptr [0x4a93ec] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45fa7d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45fa7f: test ah, 0x41 */
	if (m->zf) goto L_45fe00;	/* 45fa82: je 0x45fe00 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4cu)));	/* 45fa88: fld dword ptr [esi + 0x4c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x74u));	/* 45fa8b: fsub dword ptr [esp + 0x74] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 45fa8f: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45fa95: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45fa97: test ah, 1 */
	if (m->zf) goto L_45fa9e;	/* 45fa9a: je 0x45fa9e */
	ST(0) = -ST(0);	/* 45fa9c: fchs  */
L_45fa9e:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93ecu)); FPOP();	/* 45fa9e: fcomp dword ptr [0x4a93ec] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45faa4: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45faa6: test ah, 0x41 */
	if (m->zf) goto L_45fe00;	/* 45faa9: je 0x45fe00 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x50u)));	/* 45faaf: fld dword ptr [esi + 0x50] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x78u));	/* 45fab2: fsub dword ptr [esp + 0x78] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 45fab6: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45fabc: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45fabe: test ah, 1 */
	if (m->zf) goto L_45fac5;	/* 45fac1: je 0x45fac5 */
	ST(0) = -ST(0);	/* 45fac3: fchs  */
L_45fac5:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93ecu)); FPOP();	/* 45fac5: fcomp dword ptr [0x4a93ec] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45facb: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45facd: test ah, 0x41 */
	if (m->zf) goto L_45fe00;	/* 45fad0: je 0x45fe00 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x3cu)));	/* 45fad6: fld dword ptr [esi + 0x3c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x64u));	/* 45fad9: fsub dword ptr [esp + 0x64] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 45fadd: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45fae3: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45fae5: test ah, 1 */
	if (m->zf) goto L_45faec;	/* 45fae8: je 0x45faec */
	ST(0) = -ST(0);	/* 45faea: fchs  */
L_45faec:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93ecu)); FPOP();	/* 45faec: fcomp dword ptr [0x4a93ec] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45faf2: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45faf4: test ah, 0x41 */
	if (m->zf) goto L_45fe00;	/* 45faf7: je 0x45fe00 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x54u)));	/* 45fafd: fld dword ptr [esi + 0x54] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x7cu));	/* 45fb00: fsub dword ptr [esp + 0x7c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 45fb04: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45fb0a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45fb0c: test ah, 1 */
	if (m->zf) goto L_45fb13;	/* 45fb0f: je 0x45fb13 */
	ST(0) = -ST(0);	/* 45fb11: fchs  */
L_45fb13:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93ecu)); FPOP();	/* 45fb13: fcomp dword ptr [0x4a93ec] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45fb19: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45fb1b: test ah, 0x41 */
	if (m->zf) goto L_45fe00;	/* 45fb1e: je 0x45fe00 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x58u)));	/* 45fb24: fld dword ptr [esi + 0x58] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x80u));	/* 45fb27: fsub dword ptr [esp + 0x80] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 45fb2e: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45fb34: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45fb36: test ah, 1 */
	if (m->zf) goto L_45fb3d;	/* 45fb39: je 0x45fb3d */
	ST(0) = -ST(0);	/* 45fb3b: fchs  */
L_45fb3d:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93ecu)); FPOP();	/* 45fb3d: fcomp dword ptr [0x4a93ec] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45fb43: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45fb45: test ah, 0x41 */
	if (m->zf) goto L_45fe00;	/* 45fb48: je 0x45fe00 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x5cu)));	/* 45fb4e: fld dword ptr [esi + 0x5c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x84u));	/* 45fb51: fsub dword ptr [esp + 0x84] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 45fb58: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45fb5e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45fb60: test ah, 1 */
	if (m->zf) goto L_45fb67;	/* 45fb63: je 0x45fb67 */
	ST(0) = -ST(0);	/* 45fb65: fchs  */
L_45fb67:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93ecu)); FPOP();	/* 45fb67: fcomp dword ptr [0x4a93ec] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45fb6d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45fb6f: test ah, 0x41 */
	if (m->zf) goto L_45fe00;	/* 45fb72: je 0x45fe00 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x60u)));	/* 45fb78: fld dword ptr [esi + 0x60] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x88u));	/* 45fb7b: fsub dword ptr [esp + 0x88] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 45fb82: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45fb88: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45fb8a: test ah, 1 */
	if (m->zf) goto L_45fb91;	/* 45fb8d: je 0x45fb91 */
	ST(0) = -ST(0);	/* 45fb8f: fchs  */
L_45fb91:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93ecu)); FPOP();	/* 45fb91: fcomp dword ptr [0x4a93ec] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45fb97: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45fb99: test ah, 0x41 */
	if (m->zf) goto L_45fe00;	/* 45fb9c: je 0x45fe00 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x68u)));	/* 45fba2: fld dword ptr [esi + 0x68] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x78u));	/* 45fba5: fsub dword ptr [esp + 0x78] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 45fba9: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45fbaf: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45fbb1: test ah, 1 */
	if (m->zf) goto L_45fbb8;	/* 45fbb4: je 0x45fbb8 */
	ST(0) = -ST(0);	/* 45fbb6: fchs  */
L_45fbb8:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93ecu)); FPOP();	/* 45fbb8: fcomp dword ptr [0x4a93ec] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45fbbe: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45fbc0: test ah, 0x41 */
	if (m->zf) goto L_45fe00;	/* 45fbc3: je 0x45fe00 */
	m->ecx = M32((DWORD)(m->esi + 0x448u));	/* 45fbc9: mov ecx, dword ptr [esi + 0x448] */
	m->edx = M32((DWORD)(m->esp + 0x470u));	/* 45fbcf: mov edx, dword ptr [esp + 0x470] */
	m->eax = m->ecx;	/* 45fbd6: mov eax, ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45fbd8: sub eax, edx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 45fbda: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45fbdb: xor eax, edx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45fbdd: sub eax, edx */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 45fbdf: mov dword ptr [esp + 0x18], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x18u)));	/* 45fbe3: fild dword ptr [esp + 0x18] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93ecu)); FPOP();	/* 45fbe7: fcomp dword ptr [0x4a93ec] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45fbed: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45fbef: test ah, 0x41 */
	if (m->zf) goto L_45fe00;	/* 45fbf2: je 0x45fe00 */
	m->eax = M32((DWORD)(m->esi + 0x1cu));	/* 45fbf8: mov eax, dword ptr [esi + 0x1c] */
	m->edx = M32((DWORD)(m->esi + 0x128u));	/* 45fbfb: mov edx, dword ptr [esi + 0x128] */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45fc01: add eax, 0x64 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45fc04: cmp edx, eax */
	if (!m->zf && m->sf == m->of) goto L_45fd78;	/* 45fc06: jg 0x45fd78 */
	m->eax = M32((DWORD)(m->esi + 0x20u));	/* 45fc0c: mov eax, dword ptr [esi + 0x20] */
	m->edx = M32((DWORD)(m->esi + 0x12cu));	/* 45fc0f: mov edx, dword ptr [esi + 0x12c] */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45fc15: add eax, 0x64 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45fc18: cmp edx, eax */
	if (!m->zf && m->sf == m->of) goto L_45fd78;	/* 45fc1a: jg 0x45fd78 */
	m->eax = M32((DWORD)(m->esi + 0x28u));	/* 45fc20: mov eax, dword ptr [esi + 0x28] */
	m->edx = M32((DWORD)(m->esi + 0x130u));	/* 45fc23: mov edx, dword ptr [esi + 0x130] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45fc29: cmp edx, eax */
	if (!m->zf && m->sf == m->of) goto L_45fd78;	/* 45fc2b: jg 0x45fd78 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x134u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45fc31: cmp dword ptr [esi + 0x134], ebp */
	if (!m->zf && m->sf == m->of) goto L_45fd78;	/* 45fc37: jg 0x45fd78 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x138u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45fc3d: cmp dword ptr [esi + 0x138], ebx */
	if (!m->zf && m->sf == m->of) goto L_45fd78;	/* 45fc43: jg 0x45fd78 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x13cu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45fc49: cmp dword ptr [esi + 0x13c], edi */
	if (!m->zf && m->sf == m->of) goto L_45fd78;	/* 45fc4f: jg 0x45fd78 */
	{ DWORD a_ = m->ecx, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45fc55: cmp ecx, 8 */
	if (!m->zf && m->sf == m->of) goto L_45fd78;	/* 45fc58: jg 0x45fd78 */
	m->ecx = M32((DWORD)(m->esi + 0x4d8u));	/* 45fc5e: mov ecx, dword ptr [esi + 0x4d8] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45fc64: test ecx, ecx */
	if (!m->zf) goto L_45fc7f;	/* 45fc66: jne 0x45fc7f */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x3f4u)));	/* 45fc68: fld dword ptr [esi + 0x3f4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a940cu)); FPOP();	/* 45fc6e: fcomp dword ptr [0x4a940c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45fc74: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45fc76: test ah, 0x41 */
	if (m->zf) goto L_45fd78;	/* 45fc79: je 0x45fd78 */
L_45fc7f:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x3f8u)));	/* 45fc7f: fld dword ptr [esi + 0x3f8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a940cu)); FPOP();	/* 45fc85: fcomp dword ptr [0x4a940c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45fc8b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45fc8d: test ah, 0x41 */
	if (m->zf) goto L_45fd78;	/* 45fc90: je 0x45fd78 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45fc96: test ecx, ecx */
	if (!m->zf) goto L_45fcb1;	/* 45fc98: jne 0x45fcb1 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x3fcu)));	/* 45fc9a: fld dword ptr [esi + 0x3fc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a940cu)); FPOP();	/* 45fca0: fcomp dword ptr [0x4a940c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45fca6: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45fca8: test ah, 0x41 */
	if (m->zf) goto L_45fd78;	/* 45fcab: je 0x45fd78 */
L_45fcb1:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x400u)));	/* 45fcb1: fld dword ptr [esi + 0x400] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a940cu)); FPOP();	/* 45fcb7: fcomp dword ptr [0x4a940c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45fcbd: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45fcbf: test ah, 0x41 */
	if (m->zf) goto L_45fd78;	/* 45fcc2: je 0x45fd78 */
	m->ecx = (DWORD)(m->esp + 0x7044u);	/* 45fcc8: lea ecx, [esp + 0x7044] */
	M32((DWORD)(m->esp + 0x88b8u)) = 0x23u;	/* 45fccf: mov dword ptr [esp + 0x88b8], 0x23 */
	m->esp -= 4; M32(m->esp) = 0x45fcdfu; native_call(m, 0x46f470u);	/* 45fcda: call 0x46f470 */
	m->ecx = (DWORD)(m->esp + 0x58a4u);	/* 45fcdf: lea ecx, [esp + 0x58a4] */
	M8((DWORD)(m->esp + 0x88b8u)) = (BYTE)(0x22u);	/* 45fce6: mov byte ptr [esp + 0x88b8], 0x22 */
	m->esp -= 4; M32(m->esp) = 0x45fcf3u; native_call(m, 0x46f470u);	/* 45fcee: call 0x46f470 */
	m->ecx = (DWORD)(m->esp + 0x4104u);	/* 45fcf3: lea ecx, [esp + 0x4104] */
	M8((DWORD)(m->esp + 0x88b8u)) = (BYTE)(0x21u);	/* 45fcfa: mov byte ptr [esp + 0x88b8], 0x21 */
	m->esp -= 4; M32(m->esp) = 0x45fd07u; native_call(m, 0x46f470u);	/* 45fd02: call 0x46f470 */
	m->ecx = (DWORD)(m->esp + 0x351cu);	/* 45fd07: lea ecx, [esp + 0x351c] */
	M8((DWORD)(m->esp + 0x88b8u)) = (BYTE)(0x20u);	/* 45fd0e: mov byte ptr [esp + 0x88b8], 0x20 */
	m->esp -= 4; M32(m->esp) = 0x45fd1bu; native_call(m, 0x46f470u);	/* 45fd16: call 0x46f470 */
	m->ecx = (DWORD)(m->esp + 0x254cu);	/* 45fd1b: lea ecx, [esp + 0x254c] */
	M8((DWORD)(m->esp + 0x88b8u)) = (BYTE)(0x1fu);	/* 45fd22: mov byte ptr [esp + 0x88b8], 0x1f */
	m->esp -= 4; M32(m->esp) = 0x45fd2fu; native_call(m, 0x46f470u);	/* 45fd2a: call 0x46f470 */
	m->ecx = (DWORD)(m->esp + 0x157cu);	/* 45fd2f: lea ecx, [esp + 0x157c] */
	M8((DWORD)(m->esp + 0x88b8u)) = (BYTE)(0x1eu);	/* 45fd36: mov byte ptr [esp + 0x88b8], 0x1e */
	m->esp -= 4; M32(m->esp) = 0x45fd43u; native_call(m, 0x46f470u);	/* 45fd3e: call 0x46f470 */
	m->ecx = (DWORD)(m->esp + 0xd7cu);	/* 45fd43: lea ecx, [esp + 0xd7c] */
	M8((DWORD)(m->esp + 0x88b8u)) = (BYTE)(0x1du);	/* 45fd4a: mov byte ptr [esp + 0x88b8], 0x1d */
	m->esp -= 4; M32(m->esp) = 0x45fd57u; native_call(m, 0x46f470u);	/* 45fd52: call 0x46f470 */
	m->ecx = (DWORD)(m->esp + 0x57cu);	/* 45fd57: lea ecx, [esp + 0x57c] */
	M32((DWORD)(m->esp + 0x88b8u)) = 0xffffffffu;	/* 45fd5e: mov dword ptr [esp + 0x88b8], 0xffffffff */
	m->esp -= 4; M32(m->esp) = 0x45fd6eu; native_call(m, 0x46f470u);	/* 45fd69: call 0x46f470 */
	m->eax = 0x1u;	/* 45fd6e: mov eax, 1 */
	goto L_45fea8;	/* 45fd73: jmp 0x45fea8 */
L_45fd78:
	m->ecx = (DWORD)(m->esp + 0x7044u);	/* 45fd78: lea ecx, [esp + 0x7044] */
	M32((DWORD)(m->esp + 0x88b8u)) = 0x1cu;	/* 45fd7f: mov dword ptr [esp + 0x88b8], 0x1c */
	m->esp -= 4; M32(m->esp) = 0x45fd8fu; native_call(m, 0x46f470u);	/* 45fd8a: call 0x46f470 */
	m->ecx = (DWORD)(m->esp + 0x58a4u);	/* 45fd8f: lea ecx, [esp + 0x58a4] */
	M8((DWORD)(m->esp + 0x88b8u)) = (BYTE)(0x1bu);	/* 45fd96: mov byte ptr [esp + 0x88b8], 0x1b */
	m->esp -= 4; M32(m->esp) = 0x45fda3u; native_call(m, 0x46f470u);	/* 45fd9e: call 0x46f470 */
	m->ecx = (DWORD)(m->esp + 0x4104u);	/* 45fda3: lea ecx, [esp + 0x4104] */
	M8((DWORD)(m->esp + 0x88b8u)) = (BYTE)(0x1au);	/* 45fdaa: mov byte ptr [esp + 0x88b8], 0x1a */
	m->esp -= 4; M32(m->esp) = 0x45fdb7u; native_call(m, 0x46f470u);	/* 45fdb2: call 0x46f470 */
	m->ecx = (DWORD)(m->esp + 0x351cu);	/* 45fdb7: lea ecx, [esp + 0x351c] */
	M8((DWORD)(m->esp + 0x88b8u)) = (BYTE)(0x19u);	/* 45fdbe: mov byte ptr [esp + 0x88b8], 0x19 */
	m->esp -= 4; M32(m->esp) = 0x45fdcbu; native_call(m, 0x46f470u);	/* 45fdc6: call 0x46f470 */
	m->ecx = (DWORD)(m->esp + 0x254cu);	/* 45fdcb: lea ecx, [esp + 0x254c] */
	M8((DWORD)(m->esp + 0x88b8u)) = (BYTE)(0x18u);	/* 45fdd2: mov byte ptr [esp + 0x88b8], 0x18 */
	m->esp -= 4; M32(m->esp) = 0x45fddfu; native_call(m, 0x46f470u);	/* 45fdda: call 0x46f470 */
	m->ecx = (DWORD)(m->esp + 0x157cu);	/* 45fddf: lea ecx, [esp + 0x157c] */
	M8((DWORD)(m->esp + 0x88b8u)) = (BYTE)(0x17u);	/* 45fde6: mov byte ptr [esp + 0x88b8], 0x17 */
	m->esp -= 4; M32(m->esp) = 0x45fdf3u; native_call(m, 0x46f470u);	/* 45fdee: call 0x46f470 */
	M8((DWORD)(m->esp + 0x88b8u)) = (BYTE)(0x16u);	/* 45fdf3: mov byte ptr [esp + 0x88b8], 0x16 */
	goto L_45fe83;	/* 45fdfb: jmp 0x45fe83 */
L_45fe00:
	m->ecx = (DWORD)(m->esp + 0x7044u);	/* 45fe00: lea ecx, [esp + 0x7044] */
	M32((DWORD)(m->esp + 0x88b8u)) = 0x15u;	/* 45fe07: mov dword ptr [esp + 0x88b8], 0x15 */
	m->esp -= 4; M32(m->esp) = 0x45fe17u; native_call(m, 0x46f470u);	/* 45fe12: call 0x46f470 */
	m->ecx = (DWORD)(m->esp + 0x58a4u);	/* 45fe17: lea ecx, [esp + 0x58a4] */
	M8((DWORD)(m->esp + 0x88b8u)) = (BYTE)(0x14u);	/* 45fe1e: mov byte ptr [esp + 0x88b8], 0x14 */
	m->esp -= 4; M32(m->esp) = 0x45fe2bu; native_call(m, 0x46f470u);	/* 45fe26: call 0x46f470 */
	m->ecx = (DWORD)(m->esp + 0x4104u);	/* 45fe2b: lea ecx, [esp + 0x4104] */
	M8((DWORD)(m->esp + 0x88b8u)) = (BYTE)(0x13u);	/* 45fe32: mov byte ptr [esp + 0x88b8], 0x13 */
	m->esp -= 4; M32(m->esp) = 0x45fe3fu; native_call(m, 0x46f470u);	/* 45fe3a: call 0x46f470 */
	m->ecx = (DWORD)(m->esp + 0x351cu);	/* 45fe3f: lea ecx, [esp + 0x351c] */
	M8((DWORD)(m->esp + 0x88b8u)) = (BYTE)(0x12u);	/* 45fe46: mov byte ptr [esp + 0x88b8], 0x12 */
	m->esp -= 4; M32(m->esp) = 0x45fe53u; native_call(m, 0x46f470u);	/* 45fe4e: call 0x46f470 */
	m->ecx = (DWORD)(m->esp + 0x254cu);	/* 45fe53: lea ecx, [esp + 0x254c] */
	M8((DWORD)(m->esp + 0x88b8u)) = (BYTE)(0x11u);	/* 45fe5a: mov byte ptr [esp + 0x88b8], 0x11 */
	m->esp -= 4; M32(m->esp) = 0x45fe67u; native_call(m, 0x46f470u);	/* 45fe62: call 0x46f470 */
	m->ecx = (DWORD)(m->esp + 0x157cu);	/* 45fe67: lea ecx, [esp + 0x157c] */
	M8((DWORD)(m->esp + 0x88b8u)) = (BYTE)(0x10u);	/* 45fe6e: mov byte ptr [esp + 0x88b8], 0x10 */
	m->esp -= 4; M32(m->esp) = 0x45fe7bu; native_call(m, 0x46f470u);	/* 45fe76: call 0x46f470 */
	M8((DWORD)(m->esp + 0x88b8u)) = (BYTE)(0xfu);	/* 45fe7b: mov byte ptr [esp + 0x88b8], 0xf */
L_45fe83:
	m->ecx = (DWORD)(m->esp + 0xd7cu);	/* 45fe83: lea ecx, [esp + 0xd7c] */
	m->esp -= 4; M32(m->esp) = 0x45fe8fu; native_call(m, 0x46f470u);	/* 45fe8a: call 0x46f470 */
	m->ecx = (DWORD)(m->esp + 0x57cu);	/* 45fe8f: lea ecx, [esp + 0x57c] */
	M32((DWORD)(m->esp + 0x88b8u)) = 0xffffffffu;	/* 45fe96: mov dword ptr [esp + 0x88b8], 0xffffffff */
	m->esp -= 4; M32(m->esp) = 0x45fea6u; native_call(m, 0x46f470u);	/* 45fea1: call 0x46f470 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45fea6: xor eax, eax */
L_45fea8:
	m->ecx = M32((DWORD)(m->esp + 0x88b0u));	/* 45fea8: mov ecx, dword ptr [esp + 0x88b0] */
	m->edi = M32(m->esp); m->esp += 4;	/* 45feaf: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45feb0: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 45feb1: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 45feb2: pop ebx */
	M32((DWORD)&g_lift_fs0) = m->ecx;	/* 45feb3: mov dword ptr fs:[0], ecx */
	{ DWORD a_ = m->esp, b_ = 0x88acu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45feba: add esp, 0x88ac */
	m->esp += 4 + 4; return;	/* 45fec0: ret 4 */
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
