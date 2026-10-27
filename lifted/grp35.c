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

static void lift_45e2c0(X86 *m);
static void lift_45e390(X86 *m);
static void lift_45e460(X86 *m);
static void lift_45e530(X86 *m);
static void lift_45e600(X86 *m);
static void lift_45e1f0(X86 *m);

/* FUN_0045e1f0 (0x45e1f0), lifted by tools/lift.py */
static void lift_45e1f0(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 45e1f0: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e1f4: push esi */
	m->edx = m->eax;	/* 45e1f5: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45e1f7: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45e1fa: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45e1fc: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45e1ff: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45e201: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45e204: add edx, eax */
	m->eax = M32((DWORD)(m->ecx + m->edx*8 + 0x1cd94b0u));	/* 45e206: mov eax, dword ptr [ecx + edx*8 + 0x1cd94b0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45e20d: test eax, eax */
	m->esi = (DWORD)(m->ecx + m->edx*8 + 0x1cd93a8u);	/* 45e20f: lea esi, [ecx + edx*8 + 0x1cd93a8] */
	if (m->zf) goto L_45e2b1;	/* 45e216: je 0x45e2b1 */
	m->edx = M32((DWORD)(m->esi + 0x10cu));	/* 45e21c: mov edx, dword ptr [esi + 0x10c] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e222: push edi */
	{ DWORD v_ = 0x7d0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e223: push 0x7d0 */
	m->eax = (DWORD)(m->edx + m->edx*2 + 0x0u);	/* 45e228: lea eax, [edx + edx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45e22b: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45e22e: sub eax, edx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 45e230: lea eax, [eax + eax*2] */
	m->edx = (DWORD)(m->edx + m->eax*8 + 0x0u);	/* 45e233: lea edx, [edx + eax*8] */
	m->edi = M32((DWORD)(m->ecx + m->edx*2 + 0x1561e74u));	/* 45e236: mov edi, dword ptr [ecx + edx*2 + 0x1561e74] */
	m->edx = (DWORD)(m->ecx + m->edx*2 + 0x1561b68u);	/* 45e23d: lea edx, [ecx + edx*2 + 0x1561b68] */
	m->eax = m->edi;	/* 45e244: mov eax, edi */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45e246: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45e249: add eax, edi */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45e24b: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->edi + m->eax*4 + 0x0u);	/* 45e24e: lea eax, [edi + eax*4] */
	m->edi = (DWORD)(m->esi + 0x584u);	/* 45e251: lea edi, [esi + 0x584] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e257: push edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e258: push 0 */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x13c9b30u);	/* 45e25a: lea ecx, [ecx + eax*8 + 0x13c9b30] */
	m->eax = M32((DWORD)(m->esi + 0x484u));	/* 45e261: mov eax, dword ptr [esi + 0x484] */
	m->edi = m->eax;	/* 45e267: mov edi, eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e269: push 0 */
	{ DWORD a_ = m->edi, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 45e26b: shl edi, 7 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e26e: push 0 */
	m->edi = (DWORD)(m->edi + m->ecx*1 + 0x990u);	/* 45e270: lea edi, [edi + ecx + 0x990] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e277: push edi */
	m->edi = M32((DWORD)(m->ecx + m->eax*4 + 0x888u));	/* 45e278: mov edi, dword ptr [ecx + eax*4 + 0x888] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e27f: push edi */
	m->edi = m->eax;	/* 45e280: mov edi, eax */
	{ DWORD a_ = m->edi, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 45e282: shl edi, 4 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 45e285: add edi, eax */
	{ DWORD a_ = m->edi, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 45e287: shl edi, 5 */
	m->edi = (DWORD)(m->edi + m->ecx*1 + 0x448u);	/* 45e28a: lea edi, [edi + ecx + 0x448] */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x40u));	/* 45e291: mov ecx, dword ptr [ecx + eax*4 + 0x40] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e295: push edi */
	m->eax = (DWORD)(m->edx + 0x43534u);	/* 45e296: lea eax, [edx + 0x43534] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e29c: push ecx */
	{ DWORD a_ = m->edx, b_ = 0x338u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45e29d: add edx, 0x338 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45e2a3: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e2a4: push edx */
	m->ecx = (DWORD)(m->esi + 0x554u);	/* 45e2a5: lea ecx, [esi + 0x554] */
	m->esp -= 4; M32(m->esp) = 0x45e2b0u; native_call(m, 0x46f4e0u);	/* 45e2ab: call 0x46f4e0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 45e2b0: pop edi */
L_45e2b1:
	m->esi = M32(m->esp); m->esp += 4;	/* 45e2b1: pop esi */
	m->esp += 4 + 4; return;	/* 45e2b2: ret 4 */
}

/* actor_updateBody (0x45e2c0), lifted by tools/lift.py */
static void lift_45e2c0(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 45e2c0: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e2c4: push esi */
	m->edx = m->eax;	/* 45e2c5: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45e2c7: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45e2ca: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45e2cc: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45e2cf: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45e2d1: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45e2d4: add edx, eax */
	m->eax = M32((DWORD)(m->ecx + m->edx*8 + 0x1cd94b0u));	/* 45e2d6: mov eax, dword ptr [ecx + edx*8 + 0x1cd94b0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45e2dd: test eax, eax */
	m->esi = (DWORD)(m->ecx + m->edx*8 + 0x1cd93a8u);	/* 45e2df: lea esi, [ecx + edx*8 + 0x1cd93a8] */
	if (m->zf) goto L_45e386;	/* 45e2e6: je 0x45e386 */
	m->edx = M32((DWORD)(m->esi + 0x10cu));	/* 45e2ec: mov edx, dword ptr [esi + 0x10c] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e2f2: push edi */
	{ DWORD v_ = 0x7d0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e2f3: push 0x7d0 */
	m->eax = (DWORD)(m->edx + m->edx*2 + 0x0u);	/* 45e2f8: lea eax, [edx + edx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45e2fb: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45e2fe: sub eax, edx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 45e300: lea eax, [eax + eax*2] */
	m->edx = (DWORD)(m->edx + m->eax*8 + 0x0u);	/* 45e303: lea edx, [edx + eax*8] */
	m->edi = (DWORD)(m->ecx + m->edx*2 + 0x1561b68u);	/* 45e306: lea edi, [ecx + edx*2 + 0x1561b68] */
	m->edx = M32((DWORD)(m->ecx + m->edx*2 + 0x1561e78u));	/* 45e30d: mov edx, dword ptr [ecx + edx*2 + 0x1561e78] */
	m->eax = (DWORD)(m->edx + m->edx*2 + 0x0u);	/* 45e314: lea eax, [edx + edx*2] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45e317: shl eax, 3 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45e31a: sub eax, edx */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45e31c: lea eax, [eax + eax*4] */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45e31f: shl eax, 1 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45e321: sub eax, edx */
	m->edx = (DWORD)(m->esi + 0xd84u);	/* 45e323: lea edx, [esi + 0xd84] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e329: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e32a: push 0 */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 45e32c: lea eax, [eax + eax*2] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e32f: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e331: push 0 */
	m->ecx = (DWORD)(m->ecx + m->eax*4 + 0x13eb004u);	/* 45e333: lea ecx, [ecx + eax*4 + 0x13eb004] */
	m->eax = M32((DWORD)(m->esi + 0x484u));	/* 45e33a: mov eax, dword ptr [esi + 0x484] */
	m->edx = m->eax;	/* 45e340: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45e342: shl edx, 7 */
	m->edx = (DWORD)(m->edx + m->ecx*1 + 0x990u);	/* 45e345: lea edx, [edx + ecx + 0x990] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e34c: push edx */
	m->edx = M32((DWORD)(m->ecx + m->eax*4 + 0x888u));	/* 45e34d: mov edx, dword ptr [ecx + eax*4 + 0x888] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e354: push edx */
	m->edx = m->eax;	/* 45e355: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45e357: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45e35a: add edx, eax */
	m->eax = M32((DWORD)(m->ecx + m->eax*4 + 0x40u));	/* 45e35c: mov eax, dword ptr [ecx + eax*4 + 0x40] */
	{ DWORD a_ = m->edx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45e360: shl edx, 5 */
	m->edx = (DWORD)(m->edx + m->ecx*1 + 0x448u);	/* 45e363: lea edx, [edx + ecx + 0x448] */
	m->ecx = (DWORD)(m->edi + 0x43e34u);	/* 45e36a: lea ecx, [edi + 0x43e34] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e370: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45e371: push eax */
	{ DWORD a_ = m->edi, b_ = 0x8284u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 45e372: add edi, 0x8284 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e378: push ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e379: push edi */
	m->ecx = (DWORD)(m->esi + 0xd54u);	/* 45e37a: lea ecx, [esi + 0xd54] */
	m->esp -= 4; M32(m->esp) = 0x45e385u; native_call(m, 0x46f4e0u);	/* 45e380: call 0x46f4e0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 45e385: pop edi */
L_45e386:
	m->esi = M32(m->esp); m->esp += 4;	/* 45e386: pop esi */
	m->esp += 4 + 4; return;	/* 45e387: ret 4 */
}

/* FUN_0045e390 (0x45e390), lifted by tools/lift.py */
static void lift_45e390(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 45e390: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e394: push esi */
	m->edx = m->eax;	/* 45e395: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45e397: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45e39a: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45e39c: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45e39f: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45e3a1: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45e3a4: add edx, eax */
	m->eax = M32((DWORD)(m->ecx + m->edx*8 + 0x1cd94b0u));	/* 45e3a6: mov eax, dword ptr [ecx + edx*8 + 0x1cd94b0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45e3ad: test eax, eax */
	m->esi = (DWORD)(m->ecx + m->edx*8 + 0x1cd93a8u);	/* 45e3af: lea esi, [ecx + edx*8 + 0x1cd93a8] */
	if (m->zf) goto L_45e44d;	/* 45e3b6: je 0x45e44d */
	m->edx = M32((DWORD)(m->esi + 0x10cu));	/* 45e3bc: mov edx, dword ptr [esi + 0x10c] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e3c2: push edi */
	{ DWORD v_ = 0xfa0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e3c3: push 0xfa0 */
	m->eax = (DWORD)(m->edx + m->edx*2 + 0x0u);	/* 45e3c8: lea eax, [edx + edx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45e3cb: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45e3ce: sub eax, edx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 45e3d0: lea eax, [eax + eax*2] */
	m->edx = (DWORD)(m->edx + m->eax*8 + 0x0u);	/* 45e3d3: lea edx, [edx + eax*8] */
	m->eax = M32((DWORD)(m->ecx + m->edx*2 + 0x1561e7cu));	/* 45e3d6: mov eax, dword ptr [ecx + edx*2 + 0x1561e7c] */
	m->edx = (DWORD)(m->ecx + m->edx*2 + 0x1561b68u);	/* 45e3dd: lea edx, [ecx + edx*2 + 0x1561b68] */
	m->edi = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 45e3e4: lea edi, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edi*2 + 0x0u);	/* 45e3e7: lea eax, [eax + edi*2] */
	m->edi = (DWORD)(m->esi + 0x1584u);	/* 45e3ea: lea edi, [esi + 0x1584] */
	{ DWORD a_ = m->eax, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45e3f0: shl eax, 8 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e3f3: push edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e3f4: push 0 */
	m->ecx = (DWORD)(m->eax + m->ecx*1 + 0x140c8c0u);	/* 45e3f6: lea ecx, [eax + ecx + 0x140c8c0] */
	m->eax = M32((DWORD)(m->esi + 0x484u));	/* 45e3fd: mov eax, dword ptr [esi + 0x484] */
	m->edi = m->eax;	/* 45e403: mov edi, eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e405: push 0 */
	{ DWORD a_ = m->edi, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 45e407: shl edi, 7 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e40a: push 0 */
	m->edi = (DWORD)(m->edi + m->ecx*1 + 0x11d0u);	/* 45e40c: lea edi, [edi + ecx + 0x11d0] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e413: push edi */
	m->edi = M32((DWORD)(m->ecx + m->eax*4 + 0x10c8u));	/* 45e414: mov edi, dword ptr [ecx + eax*4 + 0x10c8] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e41b: push edi */
	m->edi = m->eax;	/* 45e41c: mov edi, eax */
	{ DWORD a_ = m->edi, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 45e41e: shl edi, 4 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 45e421: add edi, eax */
	{ DWORD a_ = m->edi, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 45e423: shl edi, 6 */
	m->edi = (DWORD)(m->edi + m->ecx*1 + 0x848u);	/* 45e426: lea edi, [edi + ecx + 0x848] */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x40u));	/* 45e42d: mov ecx, dword ptr [ecx + eax*4 + 0x40] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e431: push edi */
	m->eax = (DWORD)(m->edx + 0x44734u);	/* 45e432: lea eax, [edx + 0x44734] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e438: push ecx */
	{ DWORD a_ = m->edx, b_ = 0x101d0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45e439: add edx, 0x101d0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45e43f: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e440: push edx */
	m->ecx = (DWORD)(m->esi + 0x1554u);	/* 45e441: lea ecx, [esi + 0x1554] */
	m->esp -= 4; M32(m->esp) = 0x45e44cu; native_call(m, 0x46f4e0u);	/* 45e447: call 0x46f4e0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 45e44c: pop edi */
L_45e44d:
	m->esi = M32(m->esp); m->esp += 4;	/* 45e44d: pop esi */
	m->esp += 4 + 4; return;	/* 45e44e: ret 4 */
}

/* FUN_0045e460 (0x45e460), lifted by tools/lift.py */
static void lift_45e460(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 45e460: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e464: push esi */
	m->edx = m->eax;	/* 45e465: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45e467: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45e46a: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45e46c: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45e46f: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45e471: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45e474: add edx, eax */
	m->eax = M32((DWORD)(m->ecx + m->edx*8 + 0x1cd94b0u));	/* 45e476: mov eax, dword ptr [ecx + edx*8 + 0x1cd94b0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45e47d: test eax, eax */
	m->esi = (DWORD)(m->ecx + m->edx*8 + 0x1cd93a8u);	/* 45e47f: lea esi, [ecx + edx*8 + 0x1cd93a8] */
	if (m->zf) goto L_45e51f;	/* 45e486: je 0x45e51f */
	m->edx = M32((DWORD)(m->esi + 0x10cu));	/* 45e48c: mov edx, dword ptr [esi + 0x10c] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e492: push edi */
	{ DWORD v_ = 0xfa0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e493: push 0xfa0 */
	m->eax = (DWORD)(m->edx + m->edx*2 + 0x0u);	/* 45e498: lea eax, [edx + edx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45e49b: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45e49e: sub eax, edx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 45e4a0: lea eax, [eax + eax*2] */
	m->edx = (DWORD)(m->edx + m->eax*8 + 0x0u);	/* 45e4a3: lea edx, [edx + eax*8] */
	m->eax = M32((DWORD)(m->ecx + m->edx*2 + 0x1561e80u));	/* 45e4a6: mov eax, dword ptr [ecx + edx*2 + 0x1561e80] */
	m->edx = (DWORD)(m->ecx + m->edx*2 + 0x1561b68u);	/* 45e4ad: lea edx, [ecx + edx*2 + 0x1561b68] */
	m->edi = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45e4b4: lea edi, [eax + eax*4] */
	{ DWORD a_ = m->edi, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 45e4b7: shl edi, 6 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 45e4ba: sub edi, eax */
	m->eax = (DWORD)(m->eax + m->edi*4 + 0x0u);	/* 45e4bc: lea eax, [eax + edi*4] */
	m->edi = (DWORD)(m->esi + 0x2554u);	/* 45e4bf: lea edi, [esi + 0x2554] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e4c5: push edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e4c6: push 0 */
	m->ecx = (DWORD)(m->ecx + m->eax*4 + 0x1447ec4u);	/* 45e4c8: lea ecx, [ecx + eax*4 + 0x1447ec4] */
	m->eax = M32((DWORD)(m->esi + 0x484u));	/* 45e4cf: mov eax, dword ptr [esi + 0x484] */
	m->edi = m->eax;	/* 45e4d5: mov edi, eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e4d7: push 0 */
	{ DWORD a_ = m->edi, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 45e4d9: shl edi, 7 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e4dc: push 0 */
	m->edi = (DWORD)(m->edi + m->ecx*1 + 0x11d0u);	/* 45e4de: lea edi, [edi + ecx + 0x11d0] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e4e5: push edi */
	m->edi = M32((DWORD)(m->ecx + m->eax*4 + 0x10c8u));	/* 45e4e6: mov edi, dword ptr [ecx + eax*4 + 0x10c8] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e4ed: push edi */
	m->edi = m->eax;	/* 45e4ee: mov edi, eax */
	{ DWORD a_ = m->edi, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 45e4f0: shl edi, 4 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 45e4f3: add edi, eax */
	{ DWORD a_ = m->edi, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 45e4f5: shl edi, 6 */
	m->edi = (DWORD)(m->edi + m->ecx*1 + 0x848u);	/* 45e4f8: lea edi, [edi + ecx + 0x848] */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x40u));	/* 45e4ff: mov ecx, dword ptr [ecx + eax*4 + 0x40] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e503: push edi */
	m->eax = (DWORD)(m->edx + 0x45804u);	/* 45e504: lea eax, [edx + 0x45804] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e50a: push ecx */
	{ DWORD a_ = m->edx, b_ = 0x1fe1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45e50b: add edx, 0x1fe1c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45e511: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e512: push edx */
	m->ecx = (DWORD)(m->esi + 0x2524u);	/* 45e513: lea ecx, [esi + 0x2524] */
	m->esp -= 4; M32(m->esp) = 0x45e51eu; native_call(m, 0x46f4e0u);	/* 45e519: call 0x46f4e0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 45e51e: pop edi */
L_45e51f:
	m->esi = M32(m->esp); m->esp += 4;	/* 45e51f: pop esi */
	m->esp += 4 + 4; return;	/* 45e520: ret 4 */
}

/* FUN_0045e530 (0x45e530), lifted by tools/lift.py */
static void lift_45e530(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 45e530: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e534: push esi */
	m->edx = m->eax;	/* 45e535: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45e537: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45e53a: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45e53c: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45e53f: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45e541: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45e544: add edx, eax */
	m->eax = M32((DWORD)(m->ecx + m->edx*8 + 0x1cd94b0u));	/* 45e546: mov eax, dword ptr [ecx + edx*8 + 0x1cd94b0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45e54d: test eax, eax */
	m->esi = (DWORD)(m->ecx + m->edx*8 + 0x1cd93a8u);	/* 45e54f: lea esi, [ecx + edx*8 + 0x1cd93a8] */
	if (m->zf) goto L_45e5f2;	/* 45e556: je 0x45e5f2 */
	m->edx = M32((DWORD)(m->esi + 0x10cu));	/* 45e55c: mov edx, dword ptr [esi + 0x10c] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e562: push edi */
	{ DWORD v_ = 0xbb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e563: push 0xbb8 */
	m->eax = (DWORD)(m->edx + m->edx*2 + 0x0u);	/* 45e568: lea eax, [edx + edx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45e56b: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45e56e: sub eax, edx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 45e570: lea eax, [eax + eax*2] */
	m->edx = (DWORD)(m->edx + m->eax*8 + 0x0u);	/* 45e573: lea edx, [edx + eax*8] */
	m->eax = M32((DWORD)(m->ecx + m->edx*2 + 0x1561e84u));	/* 45e576: mov eax, dword ptr [ecx + edx*2 + 0x1561e84] */
	m->edi = (DWORD)(m->ecx + m->edx*2 + 0x1561b68u);	/* 45e57d: lea edi, [ecx + edx*2 + 0x1561b68] */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 45e584: lea edx, [eax + eax*2] */
	{ DWORD a_ = m->edx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45e587: shl edx, 6 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45e58a: add edx, eax */
	m->eax = M32((DWORD)(m->esi + 0x484u));	/* 45e58c: mov eax, dword ptr [esi + 0x484] */
	{ DWORD a_ = m->edx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45e592: shl edx, 5 */
	m->edx = (DWORD)(m->edx + m->ecx*1 + 0x1486470u);	/* 45e595: lea edx, [edx + ecx + 0x1486470] */
	m->ecx = (DWORD)(m->esi + 0x3524u);	/* 45e59c: lea ecx, [esi + 0x3524] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e5a2: push ecx */
	m->ecx = m->eax;	/* 45e5a3: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45e5a5: shl ecx, 7 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e5a8: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e5aa: push 0 */
	m->ecx = (DWORD)(m->ecx + m->edx*1 + 0x15f0u);	/* 45e5ac: lea ecx, [ecx + edx + 0x15f0] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e5b3: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e5b5: push ecx */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x14e8u));	/* 45e5b6: mov ecx, dword ptr [edx + eax*4 + 0x14e8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e5bd: push ecx */
	m->ecx = m->eax;	/* 45e5be: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45e5c0: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45e5c3: add ecx, eax */
	m->ecx = (DWORD)(m->ecx + m->ecx*4 + 0x0u);	/* 45e5c5: lea ecx, [ecx + ecx*4] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45e5c8: shl ecx, 4 */
	m->ecx = (DWORD)(m->ecx + m->edx*1 + 0xa48u);	/* 45e5cb: lea ecx, [ecx + edx + 0xa48] */
	m->edx = M32((DWORD)(m->edx + m->eax*4 + 0x40u));	/* 45e5d2: mov edx, dword ptr [edx + eax*4 + 0x40] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e5d6: push ecx */
	m->eax = (DWORD)(m->edi + 0x468d4u);	/* 45e5d7: lea eax, [edi + 0x468d4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e5dd: push edx */
	{ DWORD a_ = m->edi, b_ = 0x2fa68u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 45e5de: add edi, 0x2fa68 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45e5e4: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e5e5: push edi */
	m->ecx = (DWORD)(m->esi + 0x34f4u);	/* 45e5e6: lea ecx, [esi + 0x34f4] */
	m->esp -= 4; M32(m->esp) = 0x45e5f1u; native_call(m, 0x46f4e0u);	/* 45e5ec: call 0x46f4e0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 45e5f1: pop edi */
L_45e5f2:
	m->esi = M32(m->esp); m->esp += 4;	/* 45e5f2: pop esi */
	m->esp += 4 + 4; return;	/* 45e5f3: ret 4 */
}

/* actor_updatePart (0x45e600), lifted by tools/lift.py */
static void lift_45e600(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 45e600: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e604: push ebx */
	m->edx = m->eax;	/* 45e605: mov edx, eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e607: push esi */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45e608: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45e60b: add edx, eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e60d: push edi */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45e60e: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45e611: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45e613: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45e616: add edx, eax */
	m->eax = M32((DWORD)(m->ecx + m->edx*8 + 0x1cd94b0u));	/* 45e618: mov eax, dword ptr [ecx + edx*8 + 0x1cd94b0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45e61f: test eax, eax */
	m->edi = (DWORD)(m->ecx + m->edx*8 + 0x1cd93a8u);	/* 45e621: lea edi, [ecx + edx*8 + 0x1cd93a8] */
	if (m->zf) goto L_45e802;	/* 45e628: je 0x45e802 */
	m->edx = M32((DWORD)(m->edi + 0x10cu));	/* 45e62e: mov edx, dword ptr [edi + 0x10c] */
	m->ebx = M32((DWORD)(m->esp + 0x14u));	/* 45e634: mov ebx, dword ptr [esp + 0x14] */
	m->eax = (DWORD)(m->edx + m->edx*2 + 0x0u);	/* 45e638: lea eax, [edx + edx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45e63b: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45e63e: sub eax, edx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 45e640: lea eax, [eax + eax*2] */
	m->edx = (DWORD)(m->edx + m->eax*8 + 0x0u);	/* 45e643: lea edx, [edx + eax*8] */
	m->eax = (DWORD)(m->ecx + m->edx*2 + 0x1561b68u);	/* 45e646: lea eax, [ecx + edx*2 + 0x1561b68] */
	m->edx = M32((DWORD)(m->eax + m->ebx*4 + 0x320u));	/* 45e64d: mov edx, dword ptr [eax + ebx*4 + 0x320] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45e654: test edx, edx */
	if (m->sf != m->of) goto L_45e673;	/* 45e656: jl 0x45e673 */
	m->eax = m->edx;	/* 45e658: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45e65a: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45e65d: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45e65f: shl eax, 2 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45e662: sub eax, edx */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45e664: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45e667: lea eax, [eax + eax*4] */
	m->esi = (DWORD)(m->ecx + m->eax*8 + 0x14d1ab4u);	/* 45e66a: lea esi, [ecx + eax*8 + 0x14d1ab4] */
	goto L_45e675;	/* 45e671: jmp 0x45e675 */
L_45e673:
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 45e673: xor esi, esi */
L_45e675:
	m->eax = m->ebx;	/* 45e675: mov eax, ebx */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45e677: sub eax, 4 */
	if (m->zf) goto L_45e794;	/* 45e67a: je 0x45e794 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 45e680: dec eax */
	if (m->zf) goto L_45e71d;	/* 45e681: je 0x45e71d */
	{ DWORD a_ = m->ebx, b_ = M32((DWORD)(m->edi + 0x140u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45e687: cmp ebx, dword ptr [edi + 0x140] */
	if (!m->zf) goto L_45e802;	/* 45e68d: jne 0x45e802 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45e693: test esi, esi */
	if (m->zf) goto L_45e702;	/* 45e695: je 0x45e702 */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 45e697: mov eax, dword ptr [esp + 0x18] */
	m->edx = (DWORD)(m->edi + 0x410cu);	/* 45e69b: lea edx, [edi + 0x410c] */
	{ DWORD v_ = 0x1770u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e6a1: push 0x1770 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e6a6: push edx */
	m->edx = m->eax;	/* 45e6a7: mov edx, eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e6a9: push 0 */
	{ DWORD a_ = m->edx, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45e6ab: shl edx, 7 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e6ae: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e6b0: push 0 */
	m->edx = (DWORD)(m->edx + m->esi*1 + 0x1468u);	/* 45e6b2: lea edx, [edx + esi + 0x1468] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e6b9: push edx */
	m->edx = M32((DWORD)(m->esi + m->eax*4 + 0x12dcu));	/* 45e6ba: mov edx, dword ptr [esi + eax*4 + 0x12dc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e6c1: push edx */
	m->edx = m->eax;	/* 45e6c2: mov edx, eax */
	{ long long p_ = (long long)(int)m->edx * (int)0x330u; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edx = r_; }	/* 45e6c4: imul edx, edx, 0x330 */
	m->eax = M32((DWORD)(m->esi + m->eax*4 + 0x40u));	/* 45e6ca: mov eax, dword ptr [esi + eax*4 + 0x40] */
	m->edx = (DWORD)(m->edx + m->esi*1 + 0x94cu);	/* 45e6ce: lea edx, [edx + esi + 0x94c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e6d5: push edx */
	m->edx = (DWORD)(m->ecx + 0x1cbe198u);	/* 45e6d6: lea edx, [ecx + 0x1cbe198] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45e6dc: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x19e188cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45e6dd: add ecx, 0x19e188c */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e6e3: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e6e4: push ecx */
	m->ecx = (DWORD)(m->edi + 0x40dcu);	/* 45e6e5: lea ecx, [edi + 0x40dc] */
	m->esp -= 4; M32(m->esp) = 0x45e6f0u; native_call(m, 0x46f4e0u);	/* 45e6eb: call 0x46f4e0 */
	m->eax = M32((DWORD)(m->esi + 0x2dc0u));	/* 45e6f0: mov eax, dword ptr [esi + 0x2dc0] */
	M32((DWORD)(m->edi + 0x4ccu)) = m->eax;	/* 45e6f6: mov dword ptr [edi + 0x4cc], eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 45e6fc: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45e6fd: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 45e6fe: pop ebx */
	m->esp += 4 + 12; return;	/* 45e6ff: ret 0xc */
L_45e702:
	m->ecx = (DWORD)(m->edi + 0x40dcu);	/* 45e702: lea ecx, [edi + 0x40dc] */
	m->esp -= 4; M32(m->esp) = 0x45e70du; native_call(m, 0x46f4b0u);	/* 45e708: call 0x46f4b0 */
	M32((DWORD)(m->edi + 0x4ccu)) = 0xffffffffu;	/* 45e70d: mov dword ptr [edi + 0x4cc], 0xffffffff */
	m->edi = M32(m->esp); m->esp += 4;	/* 45e717: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45e718: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 45e719: pop ebx */
	m->esp += 4 + 12; return;	/* 45e71a: ret 0xc */
L_45e71d:
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45e71d: test esi, esi */
	if (m->zf) goto L_45e783;	/* 45e71f: je 0x45e783 */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 45e721: mov eax, dword ptr [esp + 0x18] */
	m->edx = (DWORD)(m->edi + 0x704cu);	/* 45e725: lea edx, [edi + 0x704c] */
	{ DWORD v_ = 0x1770u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e72b: push 0x1770 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e730: push edx */
	m->edx = m->eax;	/* 45e731: mov edx, eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e733: push 0 */
	{ DWORD a_ = m->edx, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45e735: shl edx, 7 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e738: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e73a: push 0 */
	m->edx = (DWORD)(m->edx + m->esi*1 + 0x2b24u);	/* 45e73c: lea edx, [edx + esi + 0x2b24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e743: push edx */
	m->edx = M32((DWORD)(m->esi + m->eax*4 + 0x2998u));	/* 45e744: mov edx, dword ptr [esi + eax*4 + 0x2998] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e74b: push edx */
	m->edx = m->eax;	/* 45e74c: mov edx, eax */
	{ long long p_ = (long long)(int)m->edx * (int)0x330u; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edx = r_; }	/* 45e74e: imul edx, edx, 0x330 */
	m->eax = M32((DWORD)(m->esi + m->eax*4 + 0x16fcu));	/* 45e754: mov eax, dword ptr [esi + eax*4 + 0x16fc] */
	m->edx = (DWORD)(m->edx + m->esi*1 + 0x2008u);	/* 45e75b: lea edx, [edx + esi + 0x2008] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e762: push edx */
	m->edx = (DWORD)(m->ecx + 0x1cbe198u);	/* 45e763: lea edx, [ecx + 0x1cbe198] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45e769: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x19e188cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45e76a: add ecx, 0x19e188c */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e770: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e771: push ecx */
	m->ecx = (DWORD)(m->edi + 0x701cu);	/* 45e772: lea ecx, [edi + 0x701c] */
	m->esp -= 4; M32(m->esp) = 0x45e77du; native_call(m, 0x46f4e0u);	/* 45e778: call 0x46f4e0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 45e77d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45e77e: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 45e77f: pop ebx */
	m->esp += 4 + 12; return;	/* 45e780: ret 0xc */
L_45e783:
	m->ecx = (DWORD)(m->edi + 0x701cu);	/* 45e783: lea ecx, [edi + 0x701c] */
	m->esp -= 4; M32(m->esp) = 0x45e78eu; native_call(m, 0x46f4b0u);	/* 45e789: call 0x46f4b0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 45e78e: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45e78f: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 45e790: pop ebx */
	m->esp += 4 + 12; return;	/* 45e791: ret 0xc */
L_45e794:
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45e794: test esi, esi */
	if (m->zf) goto L_45e7f7;	/* 45e796: je 0x45e7f7 */
	m->eax = (DWORD)(m->edi + 0x58acu);	/* 45e798: lea eax, [edi + 0x58ac] */
	{ DWORD v_ = 0x1770u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e79e: push 0x1770 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45e7a3: push eax */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 45e7a4: mov eax, dword ptr [esp + 0x20] */
	m->edx = m->eax;	/* 45e7a8: mov edx, eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e7aa: push 0 */
	{ DWORD a_ = m->edx, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45e7ac: shl edx, 7 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e7af: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45e7b1: push 0 */
	m->edx = (DWORD)(m->edx + m->esi*1 + 0x1468u);	/* 45e7b3: lea edx, [edx + esi + 0x1468] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e7ba: push edx */
	m->edx = M32((DWORD)(m->esi + m->eax*4 + 0x12dcu));	/* 45e7bb: mov edx, dword ptr [esi + eax*4 + 0x12dc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e7c2: push edx */
	m->edx = m->eax;	/* 45e7c3: mov edx, eax */
	{ long long p_ = (long long)(int)m->edx * (int)0x330u; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edx = r_; }	/* 45e7c5: imul edx, edx, 0x330 */
	m->eax = M32((DWORD)(m->esi + m->eax*4 + 0x40u));	/* 45e7cb: mov eax, dword ptr [esi + eax*4 + 0x40] */
	m->edx = (DWORD)(m->edx + m->esi*1 + 0x94cu);	/* 45e7cf: lea edx, [edx + esi + 0x94c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e7d6: push edx */
	m->edx = (DWORD)(m->ecx + 0x1cbe198u);	/* 45e7d7: lea edx, [ecx + 0x1cbe198] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45e7dd: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x19e188cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45e7de: add ecx, 0x19e188c */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e7e4: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e7e5: push ecx */
	m->ecx = (DWORD)(m->edi + 0x587cu);	/* 45e7e6: lea ecx, [edi + 0x587c] */
	m->esp -= 4; M32(m->esp) = 0x45e7f1u; native_call(m, 0x46f4e0u);	/* 45e7ec: call 0x46f4e0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 45e7f1: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45e7f2: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 45e7f3: pop ebx */
	m->esp += 4 + 12; return;	/* 45e7f4: ret 0xc */
L_45e7f7:
	m->ecx = (DWORD)(m->edi + 0x587cu);	/* 45e7f7: lea ecx, [edi + 0x587c] */
	m->esp -= 4; M32(m->esp) = 0x45e802u; native_call(m, 0x46f4b0u);	/* 45e7fd: call 0x46f4b0 */
L_45e802:
	m->edi = M32(m->esp); m->esp += 4;	/* 45e802: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45e803: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 45e804: pop ebx */
	m->esp += 4 + 12; return;	/* 45e805: ret 0xc */
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
