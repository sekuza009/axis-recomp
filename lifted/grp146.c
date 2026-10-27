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

static void lift_47a2d0(X86 *m);

/* bullet_update (0x47a2d0), lifted by tools/lift.py */
static void lift_47a2d0(X86 *m)
{
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 47a2d0: push ebp */
	m->ebp = m->esp;	/* 47a2d1: mov ebp, esp */
	{ DWORD a_ = m->esp, b_ = 0xfffffff8u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esp = r_; }	/* 47a2d3: and esp, 0xfffffff8 */
	{ DWORD a_ = m->esp, b_ = 0x204u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47a2d6: sub esp, 0x204 */
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 47a2dc: mov eax, dword ptr [ebp + 8] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 47a2df: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 47a2e0: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 47a2e1: push edi */
	m->edi = m->ecx;	/* 47a2e2: mov edi, ecx */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 47a2e4: lea ecx, [eax + eax*4] */
	M32((DWORD)(m->esp + 0x40u)) = m->edi;	/* 47a2e7: mov dword ptr [esp + 0x40], edi */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 47a2eb: shl ecx, 3 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 47a2ee: sub ecx, eax */
	m->edx = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 47a2f0: lea edx, [eax + ecx*4] */
	m->ecx = M32((DWORD)(m->edi + m->edx*8 + 0x202ef3cu));	/* 47a2f3: mov ecx, dword ptr [edi + edx*8 + 0x202ef3c] */
	m->esi = (DWORD)(m->edi + m->edx*8 + 0x202ef34u);	/* 47a2fa: lea esi, [edi + edx*8 + 0x202ef34] */
	m->eax = (DWORD)(m->ecx + m->ecx*8 + 0x0u);	/* 47a301: lea eax, [ecx + ecx*8] */
	m->eax = (DWORD)(m->ecx + m->eax*4 + 0x0u);	/* 47a304: lea eax, [ecx + eax*4] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 47a307: shl eax, 3 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 47a30a: sub eax, ecx */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 47a30c: lea edx, [eax + eax*4] */
	m->eax = M32((DWORD)(m->esi + 0xb8u));	/* 47a30f: mov eax, dword ptr [esi + 0xb8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47a315: test eax, eax */
	m->ebx = (DWORD)(m->edi + m->edx*8 + 0x14d1ab4u);	/* 47a317: lea ebx, [edi + edx*8 + 0x14d1ab4] */
	M32((DWORD)(m->esp + 0x38u)) = m->ebx;	/* 47a31e: mov dword ptr [esp + 0x38], ebx */
	if (m->sf != m->of) goto L_47a5c5;	/* 47a322: jl 0x47a5c5 */
	m->edx = m->eax;	/* 47a328: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 47a32a: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 47a32d: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 47a32f: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 47a332: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 47a334: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 47a337: add edx, eax */
	m->edx = (DWORD)(m->edi + m->edx*8 + 0x0u);	/* 47a339: lea edx, [edi + edx*8] */
	M32((DWORD)(m->esp + 0x58u)) = m->edx;	/* 47a33c: mov dword ptr [esp + 0x58], edx */
	m->edx = M32((DWORD)(m->edx + 0x1cd94b8u));	/* 47a340: mov edx, dword ptr [edx + 0x1cd94b8] */
	{ DWORD a_ = m->edx, b_ = M32((DWORD)(m->edi + 0x202e8d4u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47a346: cmp edx, dword ptr [edi + 0x202e8d4] */
	if (!m->zf) goto L_47a37d;	/* 47a34c: jne 0x47a37d */
	m->edx = M32((DWORD)(m->esp + 0x58u));	/* 47a34e: mov edx, dword ptr [esp + 0x58] */
	{ DWORD a_ = M32((DWORD)(m->edx + 0x1cd94f4u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47a352: cmp dword ptr [edx + 0x1cd94f4], 1 */
	if (!m->zf) goto L_47a37d;	/* 47a359: jne 0x47a37d */
	m->edx = M32((DWORD)(m->ebx + 0x2de0u));	/* 47a35b: mov edx, dword ptr [ebx + 0x2de0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47a361: push ecx */
	m->ecx = M32((DWORD)(m->ebx + 0x2dfcu));	/* 47a362: mov ecx, dword ptr [ebx + 0x2dfc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47a368: push ecx */
	m->ecx = M32((DWORD)(m->ebx + 0x2ddcu));	/* 47a369: mov ecx, dword ptr [ebx + 0x2ddc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47a36f: push edx */
	m->edx = M32((DWORD)(m->esi + 0xcu));	/* 47a370: mov edx, dword ptr [esi + 0xc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47a373: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47a374: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47a375: push edx */
	m->ecx = m->edi;	/* 47a376: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x47a37du; native_call(m, 0x460000u);	/* 47a378: call 0x460000 */
L_47a37d:
	m->eax = M32((DWORD)(m->esi + 0xb8u));	/* 47a37d: mov eax, dword ptr [esi + 0xb8] */
	m->ecx = m->eax;	/* 47a383: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 47a385: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 47a388: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 47a38a: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 47a38d: add ecx, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x84u)));	/* 47a38f: fld dword ptr [esi + 0x84] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 47a395: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 47a398: add ecx, eax */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + m->ecx*8 + 0x1cd9528u));	/* 47a39a: fsub dword ptr [edi + ecx*8 + 0x1cd9528] */
	m->eax = (DWORD)(m->edi + m->ecx*8 + 0x1cd9528u);	/* 47a3a1: lea eax, [edi + ecx*8 + 0x1cd9528] */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47a3a8: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x88u)));	/* 47a3ac: fld dword ptr [esi + 0x88] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 47a3b2: fsub dword ptr [eax + 4] */
	m->edx = M32((DWORD)(m->esp + 0xcu));	/* 47a3b5: mov edx, dword ptr [esp + 0xc] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47a3b9: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8cu)));	/* 47a3bd: fld dword ptr [esi + 0x8c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 47a3c3: fsub dword ptr [eax + 8] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 47a3c6: mov eax, dword ptr [esp + 0x10] */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 47a3ca: mov dword ptr [esp + 0x18], edx */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 47a3ce: mov dword ptr [esp + 0x1c], eax */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 47a3d2: fstp dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 47a3d6: mov ecx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 47a3da: mov dword ptr [esp + 0x20], ecx */
	m->ecx = (DWORD)(m->esp + 0x18u);	/* 47a3de: lea ecx, [esp + 0x18] */
	m->esp -= 4; M32(m->esp) = 0x47a3e7u; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 47a3e2: call 0x467760 */
	m->edx = M32((DWORD)(m->ebx + 0x2dfcu));	/* 47a3e7: mov edx, dword ptr [ebx + 0x2dfc] */
	m->ecx = (DWORD)(m->esi + 0x60u);	/* 47a3ed: lea ecx, [esi + 0x60] */
	ST(0) = ST(0); FPOP();	/* 47a3f0: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x2df0u)));	/* 47a3f2: fld dword ptr [ebx + 0x2df0] */
	{ DWORD a_ = m->edx, b_ = 0x1eu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 47a3f8: add edx, 0x1e */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47a3fb: xor eax, eax */
	M32((DWORD)(m->esp + 0x5cu)) = m->edx;	/* 47a3fd: mov dword ptr [esp + 0x5c], edx */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 47a401: mov edx, dword ptr [ecx] */
	M32((DWORD)(m->esp + 0x64u)) = m->edx;	/* 47a403: mov dword ptr [esp + 0x64], edx */
	M32((DWORD)(m->esp + 0x60u)) = m->eax;	/* 47a407: mov dword ptr [esp + 0x60], eax */
	m->edx = M32((DWORD)(m->ecx + 0x4u));	/* 47a40b: mov edx, dword ptr [ecx + 4] */
	M32((DWORD)(m->esp + 0x7cu)) = m->eax;	/* 47a40e: mov dword ptr [esp + 0x7c], eax */
	MF((DWORD)(m->esp + 0x88u)) = (float)ST(0); FPOP();	/* 47a412: fstp dword ptr [esp + 0x88] */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 47a419: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->esp + 0x68u)) = m->edx;	/* 47a41c: mov dword ptr [esp + 0x68], edx */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 47a420: mov edx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x6cu)) = m->ecx;	/* 47a424: mov dword ptr [esp + 0x6c], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 47a428: mov ecx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x80u)) = m->eax;	/* 47a42c: mov dword ptr [esp + 0x80], eax */
	M32((DWORD)(m->esp + 0x84u)) = m->eax;	/* 47a433: mov dword ptr [esp + 0x84], eax */
	M32((DWORD)(m->esp + 0x8cu)) = m->eax;	/* 47a43a: mov dword ptr [esp + 0x8c], eax */
	M32((DWORD)(m->esp + 0x70u)) = m->edx;	/* 47a441: mov dword ptr [esp + 0x70], edx */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 47a445: mov edx, dword ptr [esp + 0x20] */
	m->eax = (DWORD)(m->esp + 0x5cu);	/* 47a449: lea eax, [esp + 0x5c] */
	M32((DWORD)(m->esp + 0x74u)) = m->ecx;	/* 47a44d: mov dword ptr [esp + 0x74], ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47a451: push eax */
	m->ecx = m->edi;	/* 47a452: mov ecx, edi */
	M32((DWORD)(m->esp + 0x7cu)) = m->edx;	/* 47a454: mov dword ptr [esp + 0x7c], edx */
	m->esp -= 4; M32(m->esp) = 0x47a45du; native_call(m, 0x479950u);	/* 47a458: call 0x479950 */
	m->eax = M32((DWORD)(m->esi + 0xb8u));	/* 47a45d: mov eax, dword ptr [esi + 0xb8] */
	m->edx = M32((DWORD)(m->esi + 0x60u));	/* 47a463: mov edx, dword ptr [esi + 0x60] */
	m->ecx = m->eax;	/* 47a466: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 47a468: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 47a46b: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 47a46d: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 47a470: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 47a472: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 47a475: add ecx, eax */
	m->eax = M32((DWORD)(m->edi + m->ecx*8 + 0x1cd9798u));	/* 47a477: mov eax, dword ptr [edi + ecx*8 + 0x1cd9798] */
	m->ecx = M32((DWORD)(m->esi + 0x68u));	/* 47a47e: mov ecx, dword ptr [esi + 0x68] */
	{ DWORD a_ = m->eax, b_ = 0x2000u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47a481: and eax, 0x2000 */
	M32((DWORD)(m->esp + 0x64u)) = m->edx;	/* 47a486: mov dword ptr [esp + 0x64], edx */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 47a48a: mov edx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x60u)) = m->eax;	/* 47a48e: mov dword ptr [esp + 0x60], eax */
	m->eax = M32((DWORD)(m->esi + 0x64u));	/* 47a492: mov eax, dword ptr [esi + 0x64] */
	M32((DWORD)(m->esp + 0x6cu)) = m->ecx;	/* 47a495: mov dword ptr [esp + 0x6c], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 47a499: mov ecx, dword ptr [esp + 0x20] */
	M32((DWORD)(m->esp + 0x68u)) = m->eax;	/* 47a49d: mov dword ptr [esp + 0x68], eax */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 47a4a1: mov eax, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x5cu)) = 0x8u;	/* 47a4a5: mov dword ptr [esp + 0x5c], 8 */
	M32((DWORD)(m->esp + 0x70u)) = m->edx;	/* 47a4ad: mov dword ptr [esp + 0x70], edx */
	M32((DWORD)(m->esp + 0x74u)) = m->eax;	/* 47a4b1: mov dword ptr [esp + 0x74], eax */
	m->edx = (DWORD)(m->esp + 0x5cu);	/* 47a4b5: lea edx, [esp + 0x5c] */
	M32((DWORD)(m->esp + 0x78u)) = m->ecx;	/* 47a4b9: mov dword ptr [esp + 0x78], ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47a4bd: xor eax, eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47a4bf: push edx */
	m->ecx = m->edi;	/* 47a4c0: mov ecx, edi */
	M32((DWORD)(m->esp + 0x80u)) = m->eax;	/* 47a4c2: mov dword ptr [esp + 0x80], eax */
	M32((DWORD)(m->esp + 0x84u)) = m->eax;	/* 47a4c9: mov dword ptr [esp + 0x84], eax */
	M32((DWORD)(m->esp + 0x88u)) = m->eax;	/* 47a4d0: mov dword ptr [esp + 0x88], eax */
	M32((DWORD)(m->esp + 0x8cu)) = m->eax;	/* 47a4d7: mov dword ptr [esp + 0x8c], eax */
	M32((DWORD)(m->esp + 0x90u)) = m->eax;	/* 47a4de: mov dword ptr [esp + 0x90], eax */
	m->esp -= 4; M32(m->esp) = 0x47a4eau; native_call(m, 0x479950u);	/* 47a4e5: call 0x479950 */
	m->eax = M32((DWORD)(m->ebx + 0x2e04u));	/* 47a4ea: mov eax, dword ptr [ebx + 0x2e04] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47a4f0: test eax, eax */
	if (m->sf != m->of) goto L_47a517;	/* 47a4f2: jl 0x47a517 */
	m->ecx = (DWORD)(m->edi + 0x20f397cu);	/* 47a4f4: lea ecx, [edi + 0x20f397c] */
	{ DWORD v_ = 0x47435000u; m->esp -= 4; M32(m->esp) = v_; }	/* 47a4fa: push 0x47435000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47a4ff: push ecx */
	m->ecx = (DWORD)(m->esi + 0x84u);	/* 47a500: lea ecx, [esi + 0x84] */
	m->edx = (DWORD)(m->edi + 0x20f3970u);	/* 47a506: lea edx, [edi + 0x20f3970] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47a50c: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47a50d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47a50e: push eax */
	m->esp -= 4; M32(m->esp) = 0x47a514u; native_call(m, 0x456ed0u);	/* 47a50f: call 0x456ed0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47a514: add esp, 0x14 */
L_47a517:
	m->eax = M32((DWORD)(m->esi + 0xcu));	/* 47a517: mov eax, dword ptr [esi + 0xc] */
	m->ecx = M32((DWORD)(m->edi + 0x202e8d4u));	/* 47a51a: mov ecx, dword ptr [edi + 0x202e8d4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47a520: cmp eax, ecx */
	if (!m->zf) goto L_47a530;	/* 47a522: jne 0x47a530 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 47a524: push 0x64 */
	{ DWORD v_ = 0xbu; m->esp -= 4; M32(m->esp) = v_; }	/* 47a526: push 0xb */
	m->esp -= 4; M32(m->esp) = 0x47a52du; native_call(m, 0x456e50u);	/* 47a528: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47a52d: add esp, 8 */
L_47a530:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x2e14u)));	/* 47a530: fld dword ptr [ebx + 0x2e14] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47a536: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47a53c: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47a53e: test ah, 0x41 */
	if (!m->zf) goto L_47a5bb;	/* 47a541: jne 0x47a5bb */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x2e14u)));	/* 47a543: fld dword ptr [ebx + 0x2e14] */
	ST(0) = -ST(0);	/* 47a549: fchs  */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47a54b: fld dword ptr [esp + 0x18] */
	ST(0) = ST(0) * ST(1);	/* 47a54f: fmul st(1) */
	m->eax = M32((DWORD)(m->esi + 0xb8u));	/* 47a551: mov eax, dword ptr [esi + 0xb8] */
	m->ecx = m->eax;	/* 47a557: mov ecx, eax */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 47a559: fstp dword ptr [esp + 0x2c] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 47a55d: shl ecx, 4 */
	{ long double t = ST(0); FPUSH(t); }	/* 47a560: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 47a562: fmul dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 47a566: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 47a568: shl ecx, 4 */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 47a56b: fstp dword ptr [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 47a56f: add ecx, eax */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x20u));	/* 47a571: fmul dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 47a575: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 47a579: fmul dword ptr [0x4a9418] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 47a57f: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 47a582: add ecx, eax */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47a584: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 47a588: fld dword ptr [esp + 0x30] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 47a58c: fmul dword ptr [0x4a9418] */
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 47a592: mov eax, dword ptr [esp + 0xc] */
	m->edx = (DWORD)(m->edi + m->ecx*8 + 0x1ce1c04u);	/* 47a596: lea edx, [edi + ecx*8 + 0x1ce1c04] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47a59d: fstp dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 47a5a1: mov ecx, dword ptr [esp + 0x10] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 47a5a5: mov dword ptr [edx], eax */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 47a5a7: fmul dword ptr [0x4a9418] */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 47a5ad: mov dword ptr [edx + 4], ecx */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 47a5b0: fstp dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 47a5b4: mov eax, dword ptr [esp + 0x14] */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 47a5b8: mov dword ptr [edx + 8], eax */
L_47a5bb:
	M32((DWORD)(m->esi + 0xd0u)) = 0x1u;	/* 47a5bb: mov dword ptr [esi + 0xd0], 1 */
L_47a5c5:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x70u)));	/* 47a5c5: fld dword ptr [esi + 0x70] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0x74u)); FPOP();	/* 47a5c8: fcomp dword ptr [esi + 0x74] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47a5cb: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47a5cd: test ah, 0x41 */
	if (!m->zf) goto L_47b8dd;	/* 47a5d0: jne 0x47b8dd */
	m->eax = M32((DWORD)(m->esi + 0xcu));	/* 47a5d6: mov eax, dword ptr [esi + 0xc] */
	m->ecx = m->eax;	/* 47a5d9: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 47a5db: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 47a5de: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 47a5e0: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 47a5e3: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 47a5e5: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 47a5e8: add ecx, eax */
	m->eax = M32((DWORD)(m->edi + 0x202e8d4u));	/* 47a5ea: mov eax, dword ptr [edi + 0x202e8d4] */
	m->edx = M32((DWORD)(m->edi + m->ecx*8 + 0x1cd94b8u));	/* 47a5f0: mov edx, dword ptr [edi + ecx*8 + 0x1cd94b8] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47a5f7: cmp edx, eax */
	if (m->zf) goto L_47afed;	/* 47a5f9: je 0x47afed */
	m->edx = (DWORD)(m->esi + 0x90u);	/* 47a5ff: lea edx, [esi + 0x90] */
	m->ebx = (DWORD)(m->esi + 0x84u);	/* 47a605: lea ebx, [esi + 0x84] */
	m->eax = m->edx;	/* 47a60b: mov eax, edx */
	m->ecx = m->ebx;	/* 47a60d: mov ecx, ebx */
	m->edi = M32((DWORD)(m->eax + 0x0u));	/* 47a60f: mov edi, dword ptr [eax] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edi;	/* 47a611: mov dword ptr [ecx], edi */
	m->edi = M32((DWORD)(m->eax + 0x4u));	/* 47a613: mov edi, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edi;	/* 47a616: mov dword ptr [ecx + 4], edi */
	m->edi = (DWORD)(m->esi + 0x78u);	/* 47a619: lea edi, [esi + 0x78] */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47a61c: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 47a61f: mov dword ptr [ecx + 8], eax */
	m->ecx = (DWORD)(m->esi + 0xacu);	/* 47a622: lea ecx, [esi + 0xac] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 47a628: fld dword ptr [ebx] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 47a62a: fsub dword ptr [edi] */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47a62c: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x4u)));	/* 47a630: fld dword ptr [ebx + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47a633: fsub dword ptr [edi + 4] */
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 47a636: mov eax, dword ptr [esp + 0xc] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47a63a: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x8u)));	/* 47a63e: fld dword ptr [ebx + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47a641: fsub dword ptr [edi + 8] */
	M32((DWORD)(m->ecx + 0x0u)) = m->eax;	/* 47a644: mov dword ptr [ecx], eax */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 47a646: mov eax, dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 47a64a: fstp dword ptr [esp + 0x14] */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 47a64e: mov dword ptr [ecx + 4], eax */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 47a651: mov eax, dword ptr [esp + 0x14] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 47a655: mov dword ptr [ecx + 8], eax */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 47a658: mov ecx, dword ptr [esp + 0x38] */
	m->ecx = M32((DWORD)(m->ecx + 0x2dfcu));	/* 47a65c: mov ecx, dword ptr [ecx + 0x2dfc] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47a662: cmp ecx, 3 */
	if (m->zf) goto L_47acc3;	/* 47a665: je 0x47acc3 */
	{ DWORD a_ = m->ecx, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47a66b: cmp ecx, 7 */
	if (m->zf) goto L_47a719;	/* 47a66e: je 0x47a719 */
	m->ebx = M32((DWORD)(m->esp + 0x40u));	/* 47a674: mov ebx, dword ptr [esp + 0x40] */
	m->eax = M32((DWORD)(m->esi + 0xcu));	/* 47a678: mov eax, dword ptr [esi + 0xc] */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->ebx + 0x202e8d8u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47a67b: cmp eax, dword ptr [ebx + 0x202e8d8] */
	if (!m->zf) goto L_47a69f;	/* 47a681: jne 0x47a69f */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x70u)));	/* 47a683: fld dword ptr [esi + 0x70] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9568u)); FPOP();	/* 47a686: fcomp dword ptr [0x4a9568] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47a68c: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47a68e: test ah, 1 */
	if (m->zf) goto L_47a69f;	/* 47a691: je 0x47a69f */
	M32((DWORD)(m->esp + 0x28u)) = 0x1u;	/* 47a693: mov dword ptr [esp + 0x28], 1 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47a69b: xor eax, eax */
	goto L_47a6a5;	/* 47a69d: jmp 0x47a6a5 */
L_47a69f:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47a69f: xor eax, eax */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 47a6a1: mov dword ptr [esp + 0x28], eax */
L_47a6a5:
	m->ebx = M32((DWORD)(m->esp + 0x38u));	/* 47a6a5: mov ebx, dword ptr [esp + 0x38] */
	{ DWORD a_ = m->ecx, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 47a6a9: add ecx, 0x14 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x2df0u)));	/* 47a6ac: fld dword ptr [ebx + 0x2df0] */
	M32((DWORD)(m->esp + 0x5cu)) = m->ecx;	/* 47a6b2: mov dword ptr [esp + 0x5c], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 47a6b6: mov ecx, dword ptr [esp + 0x28] */
	M32((DWORD)(m->esp + 0x60u)) = m->ecx;	/* 47a6ba: mov dword ptr [esp + 0x60], ecx */
	m->ecx = M32((DWORD)(m->edi + 0x0u));	/* 47a6be: mov ecx, dword ptr [edi] */
	M32((DWORD)(m->esp + 0x64u)) = m->ecx;	/* 47a6c0: mov dword ptr [esp + 0x64], ecx */
	m->ecx = M32((DWORD)(m->edi + 0x4u));	/* 47a6c4: mov ecx, dword ptr [edi + 4] */
	M32((DWORD)(m->esp + 0x68u)) = m->ecx;	/* 47a6c7: mov dword ptr [esp + 0x68], ecx */
	m->ecx = M32((DWORD)(m->edi + 0x8u));	/* 47a6cb: mov ecx, dword ptr [edi + 8] */
	M32((DWORD)(m->esp + 0x6cu)) = m->ecx;	/* 47a6ce: mov dword ptr [esp + 0x6c], ecx */
	m->ecx = M32((DWORD)(m->edx + 0x0u));	/* 47a6d2: mov ecx, dword ptr [edx] */
	MF((DWORD)(m->esp + 0x88u)) = (float)ST(0); FPOP();	/* 47a6d4: fstp dword ptr [esp + 0x88] */
	M32((DWORD)(m->esp + 0x70u)) = m->ecx;	/* 47a6db: mov dword ptr [esp + 0x70], ecx */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 47a6df: mov ecx, dword ptr [edx + 4] */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 47a6e2: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->esp + 0x7cu)) = m->eax;	/* 47a6e5: mov dword ptr [esp + 0x7c], eax */
	M32((DWORD)(m->esp + 0x80u)) = m->eax;	/* 47a6e9: mov dword ptr [esp + 0x80], eax */
	M32((DWORD)(m->esp + 0x84u)) = m->eax;	/* 47a6f0: mov dword ptr [esp + 0x84], eax */
	M32((DWORD)(m->esp + 0x8cu)) = m->eax;	/* 47a6f7: mov dword ptr [esp + 0x8c], eax */
	m->eax = (DWORD)(m->esp + 0x5cu);	/* 47a6fe: lea eax, [esp + 0x5c] */
	M32((DWORD)(m->esp + 0x74u)) = m->ecx;	/* 47a702: mov dword ptr [esp + 0x74], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x40u));	/* 47a706: mov ecx, dword ptr [esp + 0x40] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47a70a: push eax */
	M32((DWORD)(m->esp + 0x7cu)) = m->edx;	/* 47a70b: mov dword ptr [esp + 0x7c], edx */
	m->esp -= 4; M32(m->esp) = 0x47a714u; native_call(m, 0x479950u);	/* 47a70f: call 0x479950 */
	goto L_47afed;	/* 47a714: jmp 0x47afed */
L_47a719:
	m->esp -= 4; M32(m->esp) = 0x47a71fu; native_call(m, M32(0x4a9204u));	/* 47a719: call dword ptr [0x4a9204] */
	m->esp -= 4; M32(m->esp) = 0x47a725u; native_call(m, M32(0x4a9218u));	/* 47a71f: call dword ptr [0x4a9218] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8cu)));	/* 47a725: fld dword ptr [esi + 0x8c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47a72b: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47a72d: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 47a72f: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47a734: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47a736: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47a738: push 0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47a73a: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47a73d: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x88u)));	/* 47a740: fld dword ptr [esi + 0x88] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47a746: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47a749: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 47a74c: fld dword ptr [ebx] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47a74e: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47a751: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 47a754: fld dword ptr [esi + 0x80] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47a75a: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47a75d: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x7cu)));	/* 47a760: fld dword ptr [esi + 0x7c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47a763: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47a766: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x0u)));	/* 47a769: fld dword ptr [edi] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47a76b: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47a76e: fstp qword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47a776u; native_call(m, 0x4509d2u);	/* 47a771: call 0x4509d2 */
	m->ecx = (DWORD)(m->esp + 0x1acu);	/* 47a776: lea ecx, [esp + 0x1ac] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47a77d: push ecx */
	{ DWORD v_ = 0xba6u; m->esp -= 4; M32(m->esp) = v_; }	/* 47a77e: push 0xba6 */
	m->esp -= 4; M32(m->esp) = 0x47a789u; native_call(m, M32(0x4a9270u));	/* 47a783: call dword ptr [0x4a9270] */
	m->edx = (DWORD)(m->esp + 0x1acu);	/* 47a789: lea edx, [esp + 0x1ac] */
	m->eax = (DWORD)(m->esp + 0xe4u);	/* 47a790: lea eax, [esp + 0xe4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47a797: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47a798: push eax */
	m->esp -= 4; M32(m->esp) = 0x47a79eu; native_call(m, 0x47d740u);	/* 47a799: call 0x47d740 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47a79e: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x47a7a7u; native_call(m, M32(0x4a9258u));	/* 47a7a1: call dword ptr [0x4a9258] */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 47a7a7: mov ecx, dword ptr [esp + 0x38] */
	M32((DWORD)(m->esp + 0x44u)) = 0x0u;	/* 47a7ab: mov dword ptr [esp + 0x44], 0 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x0u;	/* 47a7b3: mov dword ptr [esp + 0x3c], 0 */
	M32((DWORD)(m->esp + 0x28u)) = 0x0u;	/* 47a7bb: mov dword ptr [esp + 0x28], 0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x2df0u)));	/* 47a7c3: fld dword ptr [ecx + 0x2df0] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47a7c9: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93e8u)));	/* 47a7cd: fld dword ptr [0x4a93e8] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93e8u)));	/* 47a7d3: fld dword ptr [0x4a93e8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 47a7d9: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xf4u));	/* 47a7dd: fmul dword ptr [esp + 0xf4] */
	M32((DWORD)(m->esp + 0x24u)) = 0x0u;	/* 47a7e4: mov dword ptr [esp + 0x24], 0 */
	m->ecx = (DWORD)(m->esi + 0xd4u);	/* 47a7ec: lea ecx, [esi + 0xd4] */
	m->edx = m->ecx;	/* 47a7f2: mov edx, ecx */
	ST(0) = ST(0) + ST(1);	/* 47a7f4: fadd st(1) */
	ST(0) = ST(0) + ST(2);	/* 47a7f6: fadd st(2) */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 47a7f8: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xf8u)));	/* 47a7fc: fld dword ptr [esp + 0xf8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 47a803: fmul dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 47a807: fadd dword ptr [esp + 0x44] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 47a80b: fadd dword ptr [esp + 0x3c] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 47a80f: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xfcu)));	/* 47a813: fld dword ptr [esp + 0xfc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 47a81a: fmul dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 47a81e: fadd dword ptr [esp + 0x28] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47a822: fadd dword ptr [esp + 0x24] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 47a826: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47a82a: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 47a82e: fadd dword ptr [edi] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 47a830: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47a834: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47a838: fadd dword ptr [edi + 4] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 47a83b: mov eax, dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 47a83f: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47a843: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47a847: fadd dword ptr [edi + 8] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 47a84a: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 47a84c: mov eax, dword ptr [esp + 0x30] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 47a850: fstp dword ptr [esp + 0x34] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 47a854: mov dword ptr [edx + 4], eax */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 47a857: mov eax, dword ptr [esp + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47a85b: fld dword ptr [esp + 0x18] */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 47a85f: mov dword ptr [edx + 8], eax */
	m->edx = (DWORD)(m->esi + 0x104u);	/* 47a862: lea edx, [esi + 0x104] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x0u));	/* 47a868: fadd dword ptr [ebx] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 47a86a: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47a86e: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x4u));	/* 47a872: fadd dword ptr [ebx + 4] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 47a875: mov eax, dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 47a879: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47a87d: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x8u));	/* 47a881: fadd dword ptr [ebx + 8] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 47a884: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 47a886: mov eax, dword ptr [esp + 0x30] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 47a88a: fstp dword ptr [esp + 0x34] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 47a88e: mov dword ptr [edx + 4], eax */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 47a891: mov eax, dword ptr [esp + 0x34] */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 47a895: mov dword ptr [edx + 8], eax */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 47a898: mov edx, dword ptr [esp + 0x38] */
	m->eax = (DWORD)(m->esi + 0xe0u);	/* 47a89c: lea eax, [esi + 0xe0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x2df0u)));	/* 47a8a2: fld dword ptr [edx + 0x2df0] */
	ST(0) = -ST(0);	/* 47a8a8: fchs  */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0);	/* 47a8aa: fst dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xf4u));	/* 47a8ae: fmul dword ptr [esp + 0xf4] */
	ST(0) = ST(0) + ST(1);	/* 47a8b5: fadd st(1) */
	ST(0) = ST(0) + ST(2);	/* 47a8b7: fadd st(2) */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 47a8b9: fstp dword ptr [esp + 0x18] */
	ST(0) = ST(0); FPOP();	/* 47a8bd: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xf8u)));	/* 47a8bf: fld dword ptr [esp + 0xf8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 47a8c6: fmul dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 47a8ca: fadd dword ptr [esp + 0x44] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 47a8ce: fadd dword ptr [esp + 0x3c] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 47a8d2: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xfcu)));	/* 47a8d6: fld dword ptr [esp + 0xfc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 47a8dd: fmul dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 47a8e1: fadd dword ptr [esp + 0x28] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47a8e5: fadd dword ptr [esp + 0x24] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 47a8e9: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47a8ed: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 47a8f1: fadd dword ptr [edi] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 47a8f3: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47a8f7: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47a8fb: fadd dword ptr [edi + 4] */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 47a8fe: mov edx, dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 47a902: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47a906: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47a90a: fadd dword ptr [edi + 8] */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 47a90d: mov dword ptr [eax], edx */
	m->edx = M32((DWORD)(m->esp + 0x30u));	/* 47a90f: mov edx, dword ptr [esp + 0x30] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 47a913: fstp dword ptr [esp + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47a917: fld dword ptr [esp + 0x18] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 47a91b: mov dword ptr [eax + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 47a91e: mov edx, dword ptr [esp + 0x34] */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 47a922: mov dword ptr [eax + 8], edx */
	m->eax = (DWORD)(m->esi + 0x110u);	/* 47a925: lea eax, [esi + 0x110] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x0u));	/* 47a92b: fadd dword ptr [ebx] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 47a92d: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47a931: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x4u));	/* 47a935: fadd dword ptr [ebx + 4] */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 47a938: mov edx, dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 47a93c: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47a940: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x8u));	/* 47a944: fadd dword ptr [ebx + 8] */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 47a947: mov dword ptr [eax], edx */
	m->edx = M32((DWORD)(m->esp + 0x30u));	/* 47a949: mov edx, dword ptr [esp + 0x30] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 47a94d: fstp dword ptr [esp + 0x34] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 47a951: mov dword ptr [eax + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 47a954: mov edx, dword ptr [esp + 0x34] */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 47a958: mov dword ptr [eax + 8], edx */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 47a95b: mov eax, dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x2df0u)));	/* 47a95f: fld dword ptr [eax + 0x2df0] */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47a965: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xe4u)));	/* 47a969: fld dword ptr [esp + 0xe4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xcu));	/* 47a970: fmul dword ptr [esp + 0xc] */
	m->edx = M32((DWORD)(m->esp + 0x3cu));	/* 47a974: mov edx, dword ptr [esp + 0x3c] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 47a978: mov eax, dword ptr [esp + 0x24] */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 47a97c: mov dword ptr [esp + 0x28], edx */
	M32((DWORD)(m->esp + 0x44u)) = m->eax;	/* 47a980: mov dword ptr [esp + 0x44], eax */
	ST(0) = ST(0) + ST(1);	/* 47a984: fadd st(1) */
	m->edx = (DWORD)(m->esi + 0xecu);	/* 47a986: lea edx, [esi + 0xec] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 47a98c: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xcu)));	/* 47a990: fld dword ptr [esp + 0xc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xe8u));	/* 47a994: fmul dword ptr [esp + 0xe8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 47a99b: fadd dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 47a99f: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xcu)));	/* 47a9a3: fld dword ptr [esp + 0xc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xecu));	/* 47a9a7: fmul dword ptr [esp + 0xec] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 47a9ae: fadd dword ptr [esp + 0x44] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 47a9b2: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47a9b6: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 47a9ba: fadd dword ptr [edi] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 47a9bc: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47a9c0: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47a9c4: fadd dword ptr [edi + 4] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 47a9c7: mov eax, dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 47a9cb: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47a9cf: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47a9d3: fadd dword ptr [edi + 8] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 47a9d6: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 47a9d8: mov eax, dword ptr [esp + 0x30] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 47a9dc: fstp dword ptr [esp + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47a9e0: fld dword ptr [esp + 0x18] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 47a9e4: mov dword ptr [edx + 4], eax */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 47a9e7: mov eax, dword ptr [esp + 0x34] */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 47a9eb: mov dword ptr [edx + 8], eax */
	m->edx = (DWORD)(m->esi + 0x11cu);	/* 47a9ee: lea edx, [esi + 0x11c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x0u));	/* 47a9f4: fadd dword ptr [ebx] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 47a9f6: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47a9fa: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x4u));	/* 47a9fe: fadd dword ptr [ebx + 4] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 47aa01: mov eax, dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 47aa05: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47aa09: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x8u));	/* 47aa0d: fadd dword ptr [ebx + 8] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 47aa10: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 47aa12: mov eax, dword ptr [esp + 0x30] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 47aa16: fstp dword ptr [esp + 0x34] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 47aa1a: mov dword ptr [edx + 4], eax */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 47aa1d: mov eax, dword ptr [esp + 0x34] */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 47aa21: mov dword ptr [edx + 8], eax */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 47aa24: mov edx, dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x2df0u)));	/* 47aa28: fld dword ptr [edx + 0x2df0] */
	ST(0) = -ST(0);	/* 47aa2e: fchs  */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47aa30: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xe4u)));	/* 47aa34: fld dword ptr [esp + 0xe4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xcu));	/* 47aa3b: fmul dword ptr [esp + 0xc] */
	ST(0) = ST(0) + ST(1);	/* 47aa3f: fadd st(1) */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 47aa41: fstp dword ptr [esp + 0x18] */
	ST(0) = ST(0); FPOP();	/* 47aa45: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xcu)));	/* 47aa47: fld dword ptr [esp + 0xc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xe8u));	/* 47aa4b: fmul dword ptr [esp + 0xe8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 47aa52: fadd dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 47aa56: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xcu)));	/* 47aa5a: fld dword ptr [esp + 0xc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xecu));	/* 47aa5e: fmul dword ptr [esp + 0xec] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 47aa65: fadd dword ptr [esp + 0x44] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 47aa69: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47aa6d: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 47aa71: fadd dword ptr [edi] */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47aa73: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47aa77: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47aa7b: fadd dword ptr [edi + 4] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47aa7e: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47aa82: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47aa86: fadd dword ptr [edi + 8] */
	m->edx = M32((DWORD)(m->esp + 0xcu));	/* 47aa89: mov edx, dword ptr [esp + 0xc] */
	m->eax = (DWORD)(m->esi + 0xf8u);	/* 47aa8d: lea eax, [esi + 0xf8] */
	M32((DWORD)(m->esp + 0x2cu)) = 0x0u;	/* 47aa93: mov dword ptr [esp + 0x2c], 0 */
	M32((DWORD)(m->esp + 0x24u)) = 0x0u;	/* 47aa9b: mov dword ptr [esp + 0x24], 0 */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 47aaa3: mov dword ptr [eax], edx */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 47aaa5: mov edx, dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 47aaa9: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47aaad: fld dword ptr [esp + 0x18] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 47aab1: mov dword ptr [eax + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 47aab4: mov edx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 47aab8: mov dword ptr [esp + 0x28], ecx */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 47aabc: mov dword ptr [eax + 8], edx */
	m->eax = (DWORD)(m->esi + 0x128u);	/* 47aabf: lea eax, [esi + 0x128] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x0u));	/* 47aac5: fadd dword ptr [ebx] */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47aac7: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47aacb: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x4u));	/* 47aacf: fadd dword ptr [ebx + 4] */
	m->edx = M32((DWORD)(m->esp + 0xcu));	/* 47aad2: mov edx, dword ptr [esp + 0xc] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47aad6: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47aada: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x8u));	/* 47aade: fadd dword ptr [ebx + 8] */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 47aae1: mov dword ptr [eax], edx */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 47aae3: mov edx, dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 47aae7: fstp dword ptr [esp + 0x14] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 47aaeb: mov dword ptr [eax + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 47aaee: mov edx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 47aaf2: mov dword ptr [eax + 8], edx */
	m->eax = M32((DWORD)(m->esp + 0x40u));	/* 47aaf5: mov eax, dword ptr [esp + 0x40] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 47aaf9: fld dword ptr [ebx] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 47aafb: fsub dword ptr [edi] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x4u)));	/* 47aafd: fld dword ptr [ebx + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47ab00: fsub dword ptr [edi + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x8u)));	/* 47ab03: fld dword ptr [ebx + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47ab06: fsub dword ptr [edi + 8] */
	{ long double t = ST(0); FPUSH(t); }	/* 47ab09: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 47ab0b: fmul st(1) */
	{ long double t = ST(2); FPUSH(t); }	/* 47ab0d: fld st(2) */
	ST(0) = ST(0) * ST(3);	/* 47ab0f: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47ab11: faddp st(1) */
	{ long double t = ST(3); FPUSH(t); }	/* 47ab13: fld st(3) */
	ST(0) = ST(0) * ST(4);	/* 47ab15: fmul st(4) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47ab17: faddp st(1) */
	{ long double t = ST(0); __asm__("fsqrt" : "+t"(t)); ST(0) = t; }	/* 47ab19: fsqrt  */
	ST(3) = ST(0); FPOP();	/* 47ab1b: fstp st(3) */
	ST(0) = ST(0); FPOP();	/* 47ab1d: fstp st(0) */
	ST(0) = ST(0); FPOP();	/* 47ab1f: fstp st(0) */
	MF((DWORD)(m->esi + 0x494u)) = (float)ST(0);	/* 47ab21: fst dword ptr [esi + 0x494] */
	m->edx = M32((DWORD)(m->eax + 0x9ccfe4u));	/* 47ab27: mov edx, dword ptr [eax + 0x9ccfe4] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((0xffu) & 0xff) << 0);	/* 47ab2d: mov al, 0xff */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa450u));	/* 47ab2f: fmul dword ptr [0x4aa450] */
	M32((DWORD)(m->esp + 0x44u)) = m->edx;	/* 47ab35: mov dword ptr [esp + 0x44], edx */
	M8((DWORD)(m->esp + 0x3cu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 47ab39: mov byte ptr [esp + 0x3c], al */
	M8((DWORD)(m->esp + 0x3du)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 47ab3d: mov byte ptr [esp + 0x3d], al */
	M8((DWORD)(m->esp + 0x3eu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 47ab41: mov byte ptr [esp + 0x3e], al */
	M8((DWORD)(m->esp + 0x3fu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 47ab45: mov byte ptr [esp + 0x3f], al */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47ab49: fstp dword ptr [esp + 0xc] */
L_47ab4d:
	{ DWORD a_ = M8((DWORD)(m->esp + 0x24u)), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47ab4d: test byte ptr [esp + 0x24], 1 */
	if (m->zf) goto L_47ab87;	/* 47ab52: je 0x47ab87 */
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 47ab54: mov eax, dword ptr [esi] */
	{ DWORD a_ = m->eax, b_ = 0x80000003u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47ab56: and eax, 0x80000003 */
	if (!m->sf) goto L_47ab62;	/* 47ab5b: jns 0x47ab62 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 47ab5d: dec eax */
	{ DWORD a_ = m->eax, b_ = 0xfffffffcu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47ab5e: or eax, 0xfffffffc */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 47ab61: inc eax */
L_47ab62:
	{ DWORD a_ = m->eax, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 47ab62: shl eax, 5 */
	M32((DWORD)(m->esp + 0x54u)) = m->eax;	/* 47ab65: mov dword ptr [esp + 0x54], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x54u)));	/* 47ab69: fild dword ptr [esp + 0x54] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 47ab6d: fmul dword ptr [0x4a957c] */
	{ long double t = ST(0); FPUSH(t); }	/* 47ab73: fld st(0) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a958cu));	/* 47ab75: fadd dword ptr [0x4a958c] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47ab7b: fstp dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 47ab7f: fadd dword ptr [0x4a9420] */
	goto L_47abba;	/* 47ab85: jmp 0x47abba */
L_47ab87:
	m->ecx = M32((DWORD)(m->esi + 0x0u));	/* 47ab87: mov ecx, dword ptr [esi] */
	{ DWORD a_ = m->ecx, b_ = 0x80000003u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 47ab89: and ecx, 0x80000003 */
	if (!m->sf) goto L_47ab96;	/* 47ab8f: jns 0x47ab96 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 47ab91: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffffcu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 47ab92: or ecx, 0xfffffffc */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 47ab95: inc ecx */
L_47ab96:
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 47ab96: inc ecx */
	{ DWORD a_ = m->ecx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 47ab97: shl ecx, 5 */
	M32((DWORD)(m->esp + 0x54u)) = m->ecx;	/* 47ab9a: mov dword ptr [esp + 0x54], ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x54u)));	/* 47ab9e: fild dword ptr [esp + 0x54] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 47aba2: fmul dword ptr [0x4a957c] */
	{ long double t = ST(0); FPUSH(t); }	/* 47aba8: fld st(0) */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a958cu));	/* 47abaa: fsub dword ptr [0x4a958c] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47abb0: fstp dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 47abb4: fsub dword ptr [0x4a9420] */
L_47abba:
	m->edx = M32((DWORD)(m->esp + 0x44u));	/* 47abba: mov edx, dword ptr [esp + 0x44] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 47abbe: mov eax, dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 47abc2: fstp dword ptr [esp + 0x30] */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 47abc6: mov ecx, dword ptr [esp + 0x30] */
	M32((DWORD)(m->esp + 0x90u)) = m->edx;	/* 47abca: mov dword ptr [esp + 0x90], edx */
	m->edx = M32((DWORD)(m->esp + 0xcu));	/* 47abd1: mov edx, dword ptr [esp + 0xc] */
	M32((DWORD)(m->esp + 0x94u)) = m->eax;	/* 47abd5: mov dword ptr [esp + 0x94], eax */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 47abdc: mov eax, dword ptr [esp + 0x10] */
	M32((DWORD)(m->esp + 0x9cu)) = m->edx;	/* 47abe0: mov dword ptr [esp + 0x9c], edx */
	m->edx = m->edi;	/* 47abe7: mov edx, edi */
	M32((DWORD)(m->esp + 0x98u)) = m->ecx;	/* 47abe9: mov dword ptr [esp + 0x98], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x3cu));	/* 47abf0: mov ecx, dword ptr [esp + 0x3c] */
	M32((DWORD)(m->esp + 0xa0u)) = m->eax;	/* 47abf4: mov dword ptr [esp + 0xa0], eax */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 47abfb: mov eax, dword ptr [edx] */
	M32((DWORD)(m->esp + 0xa4u)) = m->ecx;	/* 47abfd: mov dword ptr [esp + 0xa4], ecx */
	M32((DWORD)(m->esp + 0xa8u)) = m->eax;	/* 47ac04: mov dword ptr [esp + 0xa8], eax */
	m->eax = m->ebx;	/* 47ac0b: mov eax, ebx */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 47ac0d: mov ecx, dword ptr [edx + 4] */
	M32((DWORD)(m->esp + 0x5cu)) = 0xffffffffu;	/* 47ac10: mov dword ptr [esp + 0x5c], 0xffffffff */
	M32((DWORD)(m->esp + 0xacu)) = m->ecx;	/* 47ac18: mov dword ptr [esp + 0xac], ecx */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47ac1f: mov ecx, dword ptr [eax] */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 47ac21: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->esp + 0xb4u)) = m->ecx;	/* 47ac24: mov dword ptr [esp + 0xb4], ecx */
	M32((DWORD)(m->esp + 0xb0u)) = m->edx;	/* 47ac2b: mov dword ptr [esp + 0xb0], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47ac32: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0xb8u)) = m->edx;	/* 47ac35: mov dword ptr [esp + 0xb8], edx */
	M32((DWORD)(m->esp + 0x8cu)) = 0x1u;	/* 47ac3c: mov dword ptr [esp + 0x8c], 1 */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47ac47: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0xbcu)) = m->eax;	/* 47ac4a: mov dword ptr [esp + 0xbc], eax */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 47ac51: mov eax, dword ptr [esp + 0x28] */
	m->ecx = (DWORD)(m->eax + 0x30u);	/* 47ac55: lea ecx, [eax + 0x30] */
	m->edx = M32((DWORD)(m->eax + 0x30u));	/* 47ac58: mov edx, dword ptr [eax + 0x30] */
	M32((DWORD)(m->esp + 0xc0u)) = m->edx;	/* 47ac5b: mov dword ptr [esp + 0xc0], edx */
	m->edx = M32((DWORD)(m->ecx + 0x4u));	/* 47ac62: mov edx, dword ptr [ecx + 4] */
	M32((DWORD)(m->esp + 0xc4u)) = m->edx;	/* 47ac65: mov dword ptr [esp + 0xc4], edx */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 47ac6c: mov edx, dword ptr [eax] */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 47ac6e: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->esp + 0xccu)) = m->edx;	/* 47ac71: mov dword ptr [esp + 0xcc], edx */
	M32((DWORD)(m->esp + 0xc8u)) = m->ecx;	/* 47ac78: mov dword ptr [esp + 0xc8], ecx */
	m->ecx = M32((DWORD)(m->eax + 0x4u));	/* 47ac7f: mov ecx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0xd0u)) = m->ecx;	/* 47ac82: mov dword ptr [esp + 0xd0], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x40u));	/* 47ac89: mov ecx, dword ptr [esp + 0x40] */
	m->edx = M32((DWORD)(m->eax + 0x8u));	/* 47ac8d: mov edx, dword ptr [eax + 8] */
	m->eax = (DWORD)(m->esp + 0x5cu);	/* 47ac90: lea eax, [esp + 0x5c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47ac94: push eax */
	M32((DWORD)(m->esp + 0xd8u)) = m->edx;	/* 47ac95: mov dword ptr [esp + 0xd8], edx */
	m->esp -= 4; M32(m->esp) = 0x47aca1u; native_call(m, 0x479950u);	/* 47ac9c: call 0x479950 */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 47aca1: mov eax, dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 47aca5: mov edx, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 47aca9: inc eax */
	{ DWORD a_ = m->edx, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 47acaa: add edx, 0xc */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47acad: cmp eax, 4 */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 47acb0: mov dword ptr [esp + 0x24], eax */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 47acb4: mov dword ptr [esp + 0x28], edx */
	if (m->sf != m->of) goto L_47ab4d;	/* 47acb8: jl 0x47ab4d */
	goto L_47afed;	/* 47acbe: jmp 0x47afed */
L_47acc3:
	m->esp -= 4; M32(m->esp) = 0x47acc9u; native_call(m, M32(0x4a9204u));	/* 47acc3: call dword ptr [0x4a9204] */
	m->esp -= 4; M32(m->esp) = 0x47accfu; native_call(m, M32(0x4a9218u));	/* 47acc9: call dword ptr [0x4a9218] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x0u)));	/* 47accf: fld dword ptr [edi] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebx + 0x0u)); FPOP();	/* 47acd1: fcomp dword ptr [ebx] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47acd3: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47acd5: test ah, 0x40 */
	if (m->zf) goto L_47acfc;	/* 47acd8: je 0x47acfc */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 47acda: fld dword ptr [esi + 0x80] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0x8cu)); FPOP();	/* 47ace0: fcomp dword ptr [esi + 0x8c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47ace6: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47ace8: test ah, 0x40 */
	if (m->zf) goto L_47acfc;	/* 47aceb: je 0x47acfc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47aced: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47acef: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47acf1: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47acf3: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 47acf5: push 0x3ff00000 */
	goto L_47ad09;	/* 47acfa: jmp 0x47ad09 */
L_47acfc:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47acfc: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47acfe: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 47ad00: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47ad05: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47ad07: push 0 */
L_47ad09:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8cu)));	/* 47ad09: fld dword ptr [esi + 0x8c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47ad0f: push 0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47ad11: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47ad14: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x88u)));	/* 47ad17: fld dword ptr [esi + 0x88] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47ad1d: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47ad20: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 47ad23: fld dword ptr [ebx] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47ad25: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47ad28: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 47ad2b: fld dword ptr [esi + 0x80] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47ad31: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47ad34: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x7cu)));	/* 47ad37: fld dword ptr [esi + 0x7c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47ad3a: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47ad3d: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x0u)));	/* 47ad40: fld dword ptr [edi] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47ad42: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47ad45: fstp qword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47ad4du; native_call(m, 0x4509d2u);	/* 47ad48: call 0x4509d2 */
	m->ecx = (DWORD)(m->esp + 0x1acu);	/* 47ad4d: lea ecx, [esp + 0x1ac] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ad54: push ecx */
	{ DWORD v_ = 0xba6u; m->esp -= 4; M32(m->esp) = v_; }	/* 47ad55: push 0xba6 */
	m->esp -= 4; M32(m->esp) = 0x47ad60u; native_call(m, M32(0x4a9270u));	/* 47ad5a: call dword ptr [0x4a9270] */
	m->edx = (DWORD)(m->esp + 0x1acu);	/* 47ad60: lea edx, [esp + 0x1ac] */
	m->eax = (DWORD)(m->esp + 0xe4u);	/* 47ad67: lea eax, [esp + 0xe4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ad6e: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47ad6f: push eax */
	m->esp -= 4; M32(m->esp) = 0x47ad75u; native_call(m, 0x47d740u);	/* 47ad70: call 0x47d740 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47ad75: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x47ad7eu; native_call(m, M32(0x4a9258u));	/* 47ad78: call dword ptr [0x4a9258] */
	m->eax = M32((DWORD)(m->esi + 0x4e4u));	/* 47ad7e: mov eax, dword ptr [esi + 0x4e4] */
	m->ecx = 0x14u;	/* 47ad84: mov ecx, 0x14 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 47ad89: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 47ad8a: idiv ecx */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 47ad8c: mov eax, dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x2df0u)));	/* 47ad90: fld dword ptr [eax + 0x2df0] */
	{ long double t = ST(0); FPUSH(t); }	/* 47ad96: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xf4u));	/* 47ad98: fmul dword ptr [esp + 0xf4] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 47ad9f: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xf8u)));	/* 47ada3: fld dword ptr [esp + 0xf8] */
	ST(0) = ST(0) * ST(1);	/* 47adaa: fmul st(1) */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 47adac: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xfcu)));	/* 47adb0: fld dword ptr [esp + 0xfc] */
	ST(0) = ST(0) * ST(1);	/* 47adb7: fmul st(1) */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 47adb9: fstp dword ptr [esp + 0x20] */
	ST(0) = ST(0); FPOP();	/* 47adbd: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47adbf: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 47adc3: fadd dword ptr [edi] */
	m->ecx = (DWORD)(m->edx + m->edx*2 + 0x0u);	/* 47adc5: lea ecx, [edx + edx*2] */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 47adc8: mov dword ptr [esp + 0x24], edx */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 47adcc: shl ecx, 4 */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47adcf: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47add3: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47add7: fadd dword ptr [edi + 4] */
	m->eax = (DWORD)(m->ecx + m->esi*1 + 0x0u);	/* 47adda: lea eax, [ecx + esi] */
	m->ecx = M32((DWORD)(m->esp + 0xcu));	/* 47addd: mov ecx, dword ptr [esp + 0xc] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47ade1: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47ade5: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47ade9: fadd dword ptr [edi + 8] */
	m->edx = (DWORD)(m->eax + 0xd4u);	/* 47adec: lea edx, [eax + 0xd4] */
	M32((DWORD)(m->eax + 0xd4u)) = m->ecx;	/* 47adf2: mov dword ptr [eax + 0xd4], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 47adf8: mov ecx, dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 47adfc: fstp dword ptr [esp + 0x14] */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 47ae00: mov dword ptr [edx + 4], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 47ae03: mov ecx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 47ae07: mov dword ptr [edx + 8], ecx */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 47ae0a: mov edx, dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x2df0u)));	/* 47ae0e: fld dword ptr [edx + 0x2df0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xe4u)));	/* 47ae14: fld dword ptr [esp + 0xe4] */
	ST(0) = ST(0) * ST(1);	/* 47ae1b: fmul st(1) */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 47ae1d: fstp dword ptr [esp + 0x18] */
	{ long double t = ST(0); FPUSH(t); }	/* 47ae21: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xe8u));	/* 47ae23: fmul dword ptr [esp + 0xe8] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 47ae2a: fstp dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xecu));	/* 47ae2e: fmul dword ptr [esp + 0xec] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 47ae35: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47ae39: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 47ae3d: fadd dword ptr [edi] */
	m->ecx = (DWORD)(m->eax + 0xe0u);	/* 47ae3f: lea ecx, [eax + 0xe0] */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47ae45: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47ae49: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47ae4d: fadd dword ptr [edi + 4] */
	m->edx = M32((DWORD)(m->esp + 0xcu));	/* 47ae50: mov edx, dword ptr [esp + 0xc] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47ae54: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47ae58: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47ae5c: fadd dword ptr [edi + 8] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 47ae5f: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 47ae61: mov edx, dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 47ae65: fstp dword ptr [esp + 0x14] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 47ae69: mov dword ptr [ecx + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 47ae6c: mov edx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 47ae70: mov dword ptr [ecx + 8], edx */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 47ae73: mov ecx, dword ptr [esp + 0x38] */
	m->edx = (DWORD)(m->eax + 0xecu);	/* 47ae77: lea edx, [eax + 0xec] */
	{ DWORD a_ = m->eax, b_ = 0xf8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 47ae7d: add eax, 0xf8 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x2df0u)));	/* 47ae82: fld dword ptr [ecx + 0x2df0] */
	ST(0) = -ST(0);	/* 47ae88: fchs  */
	{ long double t = ST(0); FPUSH(t); }	/* 47ae8a: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xf4u));	/* 47ae8c: fmul dword ptr [esp + 0xf4] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 47ae93: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xf8u)));	/* 47ae97: fld dword ptr [esp + 0xf8] */
	ST(0) = ST(0) * ST(1);	/* 47ae9e: fmul st(1) */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 47aea0: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xfcu)));	/* 47aea4: fld dword ptr [esp + 0xfc] */
	ST(0) = ST(0) * ST(1);	/* 47aeab: fmul st(1) */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 47aead: fstp dword ptr [esp + 0x20] */
	ST(0) = ST(0); FPOP();	/* 47aeb1: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47aeb3: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 47aeb7: fadd dword ptr [edi] */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47aeb9: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47aebd: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47aec1: fadd dword ptr [edi + 4] */
	m->ecx = M32((DWORD)(m->esp + 0xcu));	/* 47aec4: mov ecx, dword ptr [esp + 0xc] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47aec8: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47aecc: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47aed0: fadd dword ptr [edi + 8] */
	M32((DWORD)(m->edx + 0x0u)) = m->ecx;	/* 47aed3: mov dword ptr [edx], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 47aed5: mov ecx, dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 47aed9: fstp dword ptr [esp + 0x14] */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 47aedd: mov dword ptr [edx + 4], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 47aee0: mov ecx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 47aee4: mov dword ptr [edx + 8], ecx */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 47aee7: mov edx, dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x2df0u)));	/* 47aeeb: fld dword ptr [edx + 0x2df0] */
	ST(0) = -ST(0);	/* 47aef1: fchs  */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xe4u)));	/* 47aef3: fld dword ptr [esp + 0xe4] */
	ST(0) = ST(0) * ST(1);	/* 47aefa: fmul st(1) */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 47aefc: fstp dword ptr [esp + 0x18] */
	{ long double t = ST(0); FPUSH(t); }	/* 47af00: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xe8u));	/* 47af02: fmul dword ptr [esp + 0xe8] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 47af09: fstp dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xecu));	/* 47af0d: fmul dword ptr [esp + 0xec] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 47af14: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47af18: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 47af1c: fadd dword ptr [edi] */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47af1e: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47af22: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47af26: fadd dword ptr [edi + 4] */
	m->ecx = M32((DWORD)(m->esp + 0xcu));	/* 47af29: mov ecx, dword ptr [esp + 0xc] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47af2d: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47af31: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47af35: fadd dword ptr [edi + 8] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 47af38: mov edx, dword ptr [esp + 0x10] */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 47af3c: mov dword ptr [eax], ecx */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 47af3e: fstp dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 47af42: mov ecx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 47af46: mov dword ptr [eax + 4], edx */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 47af49: mov dword ptr [eax + 8], ecx */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 47af4c: mov eax, dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esi + 0x70u));	/* 47af50: mov edx, dword ptr [esi + 0x70] */
	M32((DWORD)(m->esi + m->eax*4 + 0x494u)) = m->edx;	/* 47af53: mov dword ptr [esi + eax*4 + 0x494], edx */
	m->ecx = M32((DWORD)(m->esi + 0x4e4u));	/* 47af5a: mov ecx, dword ptr [esi + 0x4e4] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 47af60: inc ecx */
	m->eax = m->ecx;	/* 47af61: mov eax, ecx */
	M32((DWORD)(m->esi + 0x4e4u)) = m->ecx;	/* 47af63: mov dword ptr [esi + 0x4e4], ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 47af69: cdq  */
	m->ecx = 0x14u;	/* 47af6a: mov ecx, 0x14 */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 47af6f: idiv ecx */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 47af71: mov dword ptr [esp + 0x24], edx */
	m->edx = (DWORD)(m->edx + m->edx*2 + 0x0u);	/* 47af75: lea edx, [edx + edx*2] */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 47af78: shl edx, 4 */
	m->eax = (DWORD)(m->edx + m->esi*1 + 0x0u);	/* 47af7b: lea eax, [edx + esi] */
	m->edx = m->ebx;	/* 47af7e: mov edx, ebx */
	m->edi = M32((DWORD)(m->edx + 0x0u));	/* 47af80: mov edi, dword ptr [edx] */
	m->ecx = (DWORD)(m->eax + 0xd4u);	/* 47af82: lea ecx, [eax + 0xd4] */
	M32((DWORD)(m->eax + 0xd4u)) = m->edi;	/* 47af88: mov dword ptr [eax + 0xd4], edi */
	m->edi = M32((DWORD)(m->edx + 0x4u));	/* 47af8e: mov edi, dword ptr [edx + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edi;	/* 47af91: mov dword ptr [ecx + 4], edi */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 47af94: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 47af97: mov dword ptr [ecx + 8], edx */
	m->edx = m->ebx;	/* 47af9a: mov edx, ebx */
	m->ecx = (DWORD)(m->eax + 0xe0u);	/* 47af9c: lea ecx, [eax + 0xe0] */
	m->edi = M32((DWORD)(m->edx + 0x0u));	/* 47afa2: mov edi, dword ptr [edx] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edi;	/* 47afa4: mov dword ptr [ecx], edi */
	m->edi = M32((DWORD)(m->edx + 0x4u));	/* 47afa6: mov edi, dword ptr [edx + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edi;	/* 47afa9: mov dword ptr [ecx + 4], edi */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 47afac: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 47afaf: mov dword ptr [ecx + 8], edx */
	m->edx = m->ebx;	/* 47afb2: mov edx, ebx */
	m->ecx = (DWORD)(m->eax + 0xecu);	/* 47afb4: lea ecx, [eax + 0xec] */
	{ DWORD a_ = m->eax, b_ = 0xf8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 47afba: add eax, 0xf8 */
	m->edi = M32((DWORD)(m->edx + 0x0u));	/* 47afbf: mov edi, dword ptr [edx] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edi;	/* 47afc1: mov dword ptr [ecx], edi */
	m->edi = M32((DWORD)(m->edx + 0x4u));	/* 47afc3: mov edi, dword ptr [edx + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edi;	/* 47afc6: mov dword ptr [ecx + 4], edi */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 47afc9: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 47afcc: mov dword ptr [ecx + 8], edx */
	m->ecx = M32((DWORD)(m->ebx + 0x0u));	/* 47afcf: mov ecx, dword ptr [ebx] */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 47afd1: mov dword ptr [eax], ecx */
	m->edx = M32((DWORD)(m->ebx + 0x4u));	/* 47afd3: mov edx, dword ptr [ebx + 4] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 47afd6: mov dword ptr [eax + 4], edx */
	m->ecx = M32((DWORD)(m->ebx + 0x8u));	/* 47afd9: mov ecx, dword ptr [ebx + 8] */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 47afdc: mov dword ptr [eax + 8], ecx */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 47afdf: mov eax, dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esi + 0x70u));	/* 47afe3: mov edx, dword ptr [esi + 0x70] */
	M32((DWORD)(m->esi + m->eax*4 + 0x494u)) = m->edx;	/* 47afe6: mov dword ptr [esi + eax*4 + 0x494], edx */
L_47afed:
	m->ecx = M32((DWORD)(m->esi + 0x6cu));	/* 47afed: mov ecx, dword ptr [esi + 0x6c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47aff0: test ecx, ecx */
	if (m->zf) goto L_47b6bf;	/* 47aff2: je 0x47b6bf */
	m->eax = M32((DWORD)(m->ecx + 0x8cu));	/* 47aff8: mov eax, dword ptr [ecx + 0x8c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47affe: test eax, eax */
	if (m->zf) goto L_47b214;	/* 47b000: je 0x47b214 */
	m->eax = M32((DWORD)(m->eax + 0x0u));	/* 47b006: mov eax, dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x4cu)));	/* 47b008: fld dword ptr [ecx + 0x4c] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 47b00b: lea edx, [eax + eax*4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x50u)));	/* 47b00e: fld dword ptr [ecx + 0x50] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x54u)));	/* 47b011: fld dword ptr [ecx + 0x54] */
	m->edx = (DWORD)(m->edx + m->edx*8 + 0x0u);	/* 47b014: lea edx, [edx + edx*8] */
	{ DWORD a_ = m->edx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 47b017: shl edx, 2 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 47b01a: sub edx, eax */
	m->eax = M32((DWORD)(m->esp + 0x40u));	/* 47b01c: mov eax, dword ptr [esp + 0x40] */
	{ long double t = ST(0); FPUSH(t); }	/* 47b020: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + m->edx*4 + 0x131b058u));	/* 47b022: fmul dword ptr [eax + edx*4 + 0x131b058] */
	m->eax = (DWORD)(m->eax + m->edx*4 + 0x131ae44u);	/* 47b029: lea eax, [eax + edx*4 + 0x131ae44] */
	{ long double t = ST(2); FPUSH(t); }	/* 47b030: fld st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x204u));	/* 47b032: fmul dword ptr [eax + 0x204] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b038: faddp st(1) */
	{ long double t = ST(3); FPUSH(t); }	/* 47b03a: fld st(3) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x1f4u));	/* 47b03c: fmul dword ptr [eax + 0x1f4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b042: faddp st(1) */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 47b044: fstp dword ptr [esp + 0x18] */
	{ long double t = ST(2); FPUSH(t); }	/* 47b048: fld st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x1f8u));	/* 47b04a: fmul dword ptr [eax + 0x1f8] */
	{ long double t = ST(1); FPUSH(t); }	/* 47b050: fld st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x218u));	/* 47b052: fmul dword ptr [eax + 0x218] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b058: faddp st(1) */
	{ long double t = ST(2); FPUSH(t); }	/* 47b05a: fld st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x208u));	/* 47b05c: fmul dword ptr [eax + 0x208] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b062: faddp st(1) */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 47b064: fstp dword ptr [esp + 0x1c] */
	{ long double t = ST(0); ST(0) = ST(2); ST(2) = t; }	/* 47b068: fxch st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x1fcu));	/* 47b06a: fmul dword ptr [eax + 0x1fc] */
	{ long double t = ST(0); ST(0) = ST(2); ST(2) = t; }	/* 47b070: fxch st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x21cu));	/* 47b072: fmul dword ptr [eax + 0x21c] */
	ST(2) = ST(2) + ST(0); FPOP();	/* 47b078: faddp st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x20cu));	/* 47b07a: fmul dword ptr [eax + 0x20c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b080: faddp st(1) */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 47b082: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x204u)));	/* 47b086: fld dword ptr [eax + 0x204] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x8u));	/* 47b08c: fmul dword ptr [ecx + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x214u)));	/* 47b08f: fld dword ptr [eax + 0x214] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0xcu));	/* 47b095: fmul dword ptr [ecx + 0xc] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b098: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x1f4u)));	/* 47b09a: fld dword ptr [eax + 0x1f4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x4u));	/* 47b0a0: fmul dword ptr [ecx + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b0a3: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x224u));	/* 47b0a5: fadd dword ptr [eax + 0x224] */
	MF((DWORD)(m->esp + 0x124u)) = (float)ST(0); FPOP();	/* 47b0ab: fstp dword ptr [esp + 0x124] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x208u)));	/* 47b0b2: fld dword ptr [eax + 0x208] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x8u));	/* 47b0b8: fmul dword ptr [ecx + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x1f8u)));	/* 47b0bb: fld dword ptr [eax + 0x1f8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x4u));	/* 47b0c1: fmul dword ptr [ecx + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b0c4: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x218u)));	/* 47b0c6: fld dword ptr [eax + 0x218] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0xcu));	/* 47b0cc: fmul dword ptr [ecx + 0xc] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b0cf: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x228u));	/* 47b0d1: fadd dword ptr [eax + 0x228] */
	MF((DWORD)(m->esp + 0x128u)) = (float)ST(0); FPOP();	/* 47b0d7: fstp dword ptr [esp + 0x128] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x20cu)));	/* 47b0de: fld dword ptr [eax + 0x20c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x8u));	/* 47b0e4: fmul dword ptr [ecx + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x1fcu)));	/* 47b0e7: fld dword ptr [eax + 0x1fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x4u));	/* 47b0ed: fmul dword ptr [ecx + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b0f0: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x21cu)));	/* 47b0f2: fld dword ptr [eax + 0x21c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0xcu));	/* 47b0f8: fmul dword ptr [ecx + 0xc] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b0fb: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x22cu));	/* 47b0fd: fadd dword ptr [eax + 0x22c] */
	MF((DWORD)(m->esp + 0x12cu)) = (float)ST(0); FPOP();	/* 47b103: fstp dword ptr [esp + 0x12c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x204u)));	/* 47b10a: fld dword ptr [eax + 0x204] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x14u));	/* 47b110: fmul dword ptr [ecx + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x214u)));	/* 47b113: fld dword ptr [eax + 0x214] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x18u));	/* 47b119: fmul dword ptr [ecx + 0x18] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b11c: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x1f4u)));	/* 47b11e: fld dword ptr [eax + 0x1f4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x10u));	/* 47b124: fmul dword ptr [ecx + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b127: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x224u));	/* 47b129: fadd dword ptr [eax + 0x224] */
	MF((DWORD)(m->esp + 0x130u)) = (float)ST(0); FPOP();	/* 47b12f: fstp dword ptr [esp + 0x130] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x1f8u)));	/* 47b136: fld dword ptr [eax + 0x1f8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x10u));	/* 47b13c: fmul dword ptr [ecx + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x208u)));	/* 47b13f: fld dword ptr [eax + 0x208] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x14u));	/* 47b145: fmul dword ptr [ecx + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b148: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x218u)));	/* 47b14a: fld dword ptr [eax + 0x218] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x18u));	/* 47b150: fmul dword ptr [ecx + 0x18] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b153: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x228u));	/* 47b155: fadd dword ptr [eax + 0x228] */
	MF((DWORD)(m->esp + 0x134u)) = (float)ST(0); FPOP();	/* 47b15b: fstp dword ptr [esp + 0x134] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x1fcu)));	/* 47b162: fld dword ptr [eax + 0x1fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x10u));	/* 47b168: fmul dword ptr [ecx + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x20cu)));	/* 47b16b: fld dword ptr [eax + 0x20c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x14u));	/* 47b171: fmul dword ptr [ecx + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b174: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x21cu)));	/* 47b176: fld dword ptr [eax + 0x21c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x18u));	/* 47b17c: fmul dword ptr [ecx + 0x18] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b17f: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x22cu));	/* 47b181: fadd dword ptr [eax + 0x22c] */
	MF((DWORD)(m->esp + 0x138u)) = (float)ST(0); FPOP();	/* 47b187: fstp dword ptr [esp + 0x138] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x214u)));	/* 47b18e: fld dword ptr [eax + 0x214] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x24u));	/* 47b194: fmul dword ptr [ecx + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x204u)));	/* 47b197: fld dword ptr [eax + 0x204] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x20u));	/* 47b19d: fmul dword ptr [ecx + 0x20] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b1a0: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x1f4u)));	/* 47b1a2: fld dword ptr [eax + 0x1f4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x1cu));	/* 47b1a8: fmul dword ptr [ecx + 0x1c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b1ab: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x224u));	/* 47b1ad: fadd dword ptr [eax + 0x224] */
	MF((DWORD)(m->esp + 0x13cu)) = (float)ST(0); FPOP();	/* 47b1b3: fstp dword ptr [esp + 0x13c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x218u)));	/* 47b1ba: fld dword ptr [eax + 0x218] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x24u));	/* 47b1c0: fmul dword ptr [ecx + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x1f8u)));	/* 47b1c3: fld dword ptr [eax + 0x1f8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x1cu));	/* 47b1c9: fmul dword ptr [ecx + 0x1c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b1cc: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x208u)));	/* 47b1ce: fld dword ptr [eax + 0x208] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x20u));	/* 47b1d4: fmul dword ptr [ecx + 0x20] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b1d7: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x228u));	/* 47b1d9: fadd dword ptr [eax + 0x228] */
	MF((DWORD)(m->esp + 0x140u)) = (float)ST(0); FPOP();	/* 47b1df: fstp dword ptr [esp + 0x140] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x21cu)));	/* 47b1e6: fld dword ptr [eax + 0x21c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x24u));	/* 47b1ec: fmul dword ptr [ecx + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x1fcu)));	/* 47b1ef: fld dword ptr [eax + 0x1fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x1cu));	/* 47b1f5: fmul dword ptr [ecx + 0x1c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b1f8: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x20cu)));	/* 47b1fa: fld dword ptr [eax + 0x20c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x20u));	/* 47b200: fmul dword ptr [ecx + 0x20] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b203: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x22cu));	/* 47b205: fadd dword ptr [eax + 0x22c] */
	MF((DWORD)(m->esp + 0x144u)) = (float)ST(0); FPOP();	/* 47b20b: fstp dword ptr [esp + 0x144] */
	goto L_47b289;	/* 47b212: jmp 0x47b289 */
L_47b214:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x54u)));	/* 47b214: fld dword ptr [ecx + 0x54] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x50u)));	/* 47b217: fld dword ptr [ecx + 0x50] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x4cu)));	/* 47b21a: fld dword ptr [ecx + 0x4c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 47b21d: fstp dword ptr [esp + 0x18] */
	m->edx = (DWORD)(m->ecx + 0x4u);	/* 47b221: lea edx, [ecx + 4] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 47b224: fstp dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 47b228: fstp dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 47b22c: mov eax, dword ptr [edx] */
	M32((DWORD)(m->esp + 0x124u)) = m->eax;	/* 47b22e: mov dword ptr [esp + 0x124], eax */
	m->eax = M32((DWORD)(m->edx + 0x4u));	/* 47b235: mov eax, dword ptr [edx + 4] */
	M32((DWORD)(m->esp + 0x128u)) = m->eax;	/* 47b238: mov dword ptr [esp + 0x128], eax */
	m->eax = (DWORD)(m->ecx + 0x10u);	/* 47b23f: lea eax, [ecx + 0x10] */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 47b242: mov edx, dword ptr [edx + 8] */
	{ DWORD a_ = m->ecx, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 47b245: add ecx, 0x1c */
	M32((DWORD)(m->esp + 0x12cu)) = m->edx;	/* 47b248: mov dword ptr [esp + 0x12c], edx */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 47b24f: mov edx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x130u)) = m->edx;	/* 47b251: mov dword ptr [esp + 0x130], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47b258: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x134u)) = m->edx;	/* 47b25b: mov dword ptr [esp + 0x134], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47b262: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x138u)) = m->eax;	/* 47b265: mov dword ptr [esp + 0x138], eax */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 47b26c: mov edx, dword ptr [ecx] */
	M32((DWORD)(m->esp + 0x13cu)) = m->edx;	/* 47b26e: mov dword ptr [esp + 0x13c], edx */
	m->eax = M32((DWORD)(m->ecx + 0x4u));	/* 47b275: mov eax, dword ptr [ecx + 4] */
	M32((DWORD)(m->esp + 0x140u)) = m->eax;	/* 47b278: mov dword ptr [esp + 0x140], eax */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 47b27f: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->esp + 0x144u)) = m->ecx;	/* 47b282: mov dword ptr [esp + 0x144], ecx */
L_47b289:
	m->edi = M32((DWORD)(m->esp + 0x38u));	/* 47b289: mov edi, dword ptr [esp + 0x38] */
	m->ebx = (DWORD)(m->esi + 0x60u);	/* 47b28d: lea ebx, [esi + 0x60] */
	m->ecx = m->ebx;	/* 47b290: mov ecx, ebx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47b292: xor eax, eax */
	m->edx = M32((DWORD)(m->edi + 0x2dfcu));	/* 47b294: mov edx, dword ptr [edi + 0x2dfc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x2df0u)));	/* 47b29a: fld dword ptr [edi + 0x2df0] */
	{ DWORD a_ = m->edx, b_ = 0x1eu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 47b2a0: add edx, 0x1e */
	M32((DWORD)(m->esp + 0x60u)) = m->eax;	/* 47b2a3: mov dword ptr [esp + 0x60], eax */
	M32((DWORD)(m->esp + 0x5cu)) = m->edx;	/* 47b2a7: mov dword ptr [esp + 0x5c], edx */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 47b2ab: mov edx, dword ptr [ecx] */
	M32((DWORD)(m->esp + 0x64u)) = m->edx;	/* 47b2ad: mov dword ptr [esp + 0x64], edx */
	M32((DWORD)(m->esp + 0x7cu)) = m->eax;	/* 47b2b1: mov dword ptr [esp + 0x7c], eax */
	m->edx = M32((DWORD)(m->ecx + 0x4u));	/* 47b2b5: mov edx, dword ptr [ecx + 4] */
	M32((DWORD)(m->esp + 0x80u)) = m->eax;	/* 47b2b8: mov dword ptr [esp + 0x80], eax */
	MF((DWORD)(m->esp + 0x88u)) = (float)ST(0); FPOP();	/* 47b2bf: fstp dword ptr [esp + 0x88] */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 47b2c6: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->esp + 0x68u)) = m->edx;	/* 47b2c9: mov dword ptr [esp + 0x68], edx */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 47b2cd: mov edx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x6cu)) = m->ecx;	/* 47b2d1: mov dword ptr [esp + 0x6c], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 47b2d5: mov ecx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x84u)) = m->eax;	/* 47b2d9: mov dword ptr [esp + 0x84], eax */
	M32((DWORD)(m->esp + 0x8cu)) = m->eax;	/* 47b2e0: mov dword ptr [esp + 0x8c], eax */
	M32((DWORD)(m->esp + 0x70u)) = m->edx;	/* 47b2e7: mov dword ptr [esp + 0x70], edx */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 47b2eb: mov edx, dword ptr [esp + 0x20] */
	m->eax = (DWORD)(m->esp + 0x5cu);	/* 47b2ef: lea eax, [esp + 0x5c] */
	M32((DWORD)(m->esp + 0x74u)) = m->ecx;	/* 47b2f3: mov dword ptr [esp + 0x74], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x40u));	/* 47b2f7: mov ecx, dword ptr [esp + 0x40] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47b2fb: push eax */
	M32((DWORD)(m->esp + 0x7cu)) = m->edx;	/* 47b2fc: mov dword ptr [esp + 0x7c], edx */
	m->esp -= 4; M32(m->esp) = 0x47b305u; native_call(m, 0x479950u);	/* 47b300: call 0x479950 */
	m->ecx = M32((DWORD)(m->esi + 0x6cu));	/* 47b305: mov ecx, dword ptr [esi + 0x6c] */
	{ DWORD a_ = M8((DWORD)(m->ecx + 0x0u)), b_ = 0x10u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47b308: test byte ptr [ecx], 0x10 */
	if (!m->zf) goto L_47b688;	/* 47b30b: jne 0x47b688 */
	{ DWORD a_ = M32((DWORD)(0x83a9c8u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47b311: cmp dword ptr [0x83a9c8], 1 */
	if (!m->zf) goto L_47b688;	/* 47b318: jne 0x47b688 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x124u)));	/* 47b31e: fld dword ptr [esp + 0x124] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x0u));	/* 47b325: fsub dword ptr [ebx] */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47b327: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x128u)));	/* 47b32b: fld dword ptr [esp + 0x128] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x4u));	/* 47b332: fsub dword ptr [ebx + 4] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47b335: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x12cu)));	/* 47b339: fld dword ptr [esp + 0x12c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x8u));	/* 47b340: fsub dword ptr [ebx + 8] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 47b343: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 47b347: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x20u));	/* 47b34b: fmul dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 47b34f: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 47b353: fmul dword ptr [esp + 0x1c] */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47b357: fsubp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47b359: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 47b35d: fmul dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47b361: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xcu));	/* 47b365: fmul dword ptr [esp + 0xc] */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47b369: fsubp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47b36b: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xcu));	/* 47b36f: fmul dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47b373: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 47b377: fmul dword ptr [esp + 0x10] */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47b37b: fsubp st(1) */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 47b37d: fstp dword ptr [esp + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 47b381: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 47b385: fmul dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 47b389: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 47b38d: fmul dword ptr [esp + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b391: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xcu)));	/* 47b393: fld dword ptr [esp + 0xc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xcu));	/* 47b397: fmul dword ptr [esp + 0xc] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b39b: faddp st(1) */
	{ long double t = ST(0); __asm__("fsqrt" : "+t"(t)); ST(0) = t; }	/* 47b39d: fsqrt  */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 47b39f: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 47b3a3: fld dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 47b3a7: fmul dword ptr [esp + 0x34] */
	{ long double t = ST(1); FPUSH(t); }	/* 47b3ab: fld st(1) */
	ST(0) = ST(0) * ST(2);	/* 47b3ad: fmul st(2) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b3af: faddp st(1) */
	{ long double t = ST(2); FPUSH(t); }	/* 47b3b1: fld st(2) */
	ST(0) = ST(0) * ST(3);	/* 47b3b3: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b3b5: faddp st(1) */
	{ long double t = ST(0); __asm__("fsqrt" : "+t"(t)); ST(0) = t; }	/* 47b3b7: fsqrt  */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 47b3b9: fld dword ptr [esp + 0x24] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47b3bd: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47b3c3: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47b3c5: test ah, 0x40 */
	if (m->zf) goto L_47b3d2;	/* 47b3c8: je 0x47b3d2 */
	M32((DWORD)(m->esp + 0x24u)) = 0x3f800000u;	/* 47b3ca: mov dword ptr [esp + 0x24], 0x3f800000 */
L_47b3d2:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 47b3d2: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47b3d8: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47b3da: test ah, 0x40 */
	if (m->zf) goto L_47b3e7;	/* 47b3dd: je 0x47b3e7 */
	ST(0) = ST(0); FPOP();	/* 47b3df: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 47b3e1: fld dword ptr [0x4a9424] */
L_47b3e7:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x130u)));	/* 47b3e7: fld dword ptr [esp + 0x130] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x0u));	/* 47b3ee: fsub dword ptr [ebx] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x134u)));	/* 47b3f0: fld dword ptr [esp + 0x134] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x4u));	/* 47b3f7: fsub dword ptr [ebx + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x138u)));	/* 47b3fa: fld dword ptr [esp + 0x138] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x8u));	/* 47b401: fsub dword ptr [ebx + 8] */
	{ long double t = ST(0); FPUSH(t); }	/* 47b404: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 47b406: fmul dword ptr [esp + 0x14] */
	{ long double t = ST(2); FPUSH(t); }	/* 47b40a: fld st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 47b40c: fmul dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 47b410: mov edx, dword ptr [esp + 0x24] */
	M32((DWORD)(m->esp + 0x170u)) = 0x0u;	/* 47b414: mov dword ptr [esp + 0x170], 0 */
	M32((DWORD)(m->esp + 0x16cu)) = m->edx;	/* 47b41f: mov dword ptr [esp + 0x16c], edx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 47b426: xor edx, edx */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b428: faddp st(1) */
	{ long double t = ST(3); FPUSH(t); }	/* 47b42a: fld st(3) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xcu));	/* 47b42c: fmul dword ptr [esp + 0xc] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b430: faddp st(1) */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47b432: fdiv dword ptr [esp + 0x24] */
	MF((DWORD)(m->esp + 0x174u)) = (float)ST(0); FPOP();	/* 47b436: fstp dword ptr [esp + 0x174] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 47b43d: fmul dword ptr [esp + 0x34] */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 47b441: fxch st(1) */
	ST(0) = ST(0) * ST(4);	/* 47b443: fmul st(4) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b445: faddp st(1) */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 47b447: fxch st(1) */
	ST(0) = ST(0) * ST(4);	/* 47b449: fmul st(4) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b44b: faddp st(1) */
	ST(0) = ST(0) / ST(1);	/* 47b44d: fdiv st(1) */
	MF((DWORD)(m->esp + 0x178u)) = (float)ST(0); FPOP();	/* 47b44f: fstp dword ptr [esp + 0x178] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x13cu)));	/* 47b456: fld dword ptr [esp + 0x13c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x0u));	/* 47b45d: fsub dword ptr [ebx] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x140u)));	/* 47b45f: fld dword ptr [esp + 0x140] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x4u));	/* 47b466: fsub dword ptr [ebx + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x144u)));	/* 47b469: fld dword ptr [esp + 0x144] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x8u));	/* 47b470: fsub dword ptr [ebx + 8] */
	{ long double t = ST(0); FPUSH(t); }	/* 47b473: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 47b475: fmul dword ptr [esp + 0x14] */
	{ long double t = ST(2); FPUSH(t); }	/* 47b479: fld st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 47b47b: fmul dword ptr [esp + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b47f: faddp st(1) */
	{ long double t = ST(3); FPUSH(t); }	/* 47b481: fld st(3) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xcu));	/* 47b483: fmul dword ptr [esp + 0xc] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b487: faddp st(1) */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47b489: fdiv dword ptr [esp + 0x24] */
	MF((DWORD)(m->esp + 0x17cu)) = (float)ST(0); FPOP();	/* 47b48d: fstp dword ptr [esp + 0x17c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 47b494: fmul dword ptr [esp + 0x34] */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 47b498: fxch st(1) */
	ST(0) = ST(0) * ST(4);	/* 47b49a: fmul st(4) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b49c: faddp st(1) */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 47b49e: fxch st(1) */
	ST(0) = ST(0) * ST(4);	/* 47b4a0: fmul st(4) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47b4a2: faddp st(1) */
	ST(0) = ST(0) / ST(1);	/* 47b4a4: fdiv st(1) */
	MF((DWORD)(m->esp + 0x180u)) = (float)ST(0); FPOP();	/* 47b4a6: fstp dword ptr [esp + 0x180] */
	m->eax = M32((DWORD)(m->ecx + 0x8cu));	/* 47b4ad: mov eax, dword ptr [ecx + 0x8c] */
	ST(0) = ST(0); FPOP();	/* 47b4b3: fstp st(0) */
	ST(0) = ST(0); FPOP();	/* 47b4b5: fstp st(0) */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47b4b7: cmp eax, edx */
	ST(0) = ST(0); FPOP();	/* 47b4b9: fstp st(0) */
	if (m->zf) goto L_47b607;	/* 47b4bb: je 0x47b607 */
	m->eax = M32((DWORD)(m->eax + 0x0u));	/* 47b4c1: mov eax, dword ptr [eax] */
	m->ebx = M32((DWORD)(m->ecx + 0x90u));	/* 47b4c3: mov ebx, dword ptr [ecx + 0x90] */
	{ DWORD a_ = m->ebx, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ebx = r_; } }	/* 47b4c9: shl ebx, 7 */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 47b4cc: lea edx, [eax + eax*4] */
	m->edx = (DWORD)(m->edx + m->edx*8 + 0x0u);	/* 47b4cf: lea edx, [edx + edx*8] */
	{ DWORD a_ = m->edx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 47b4d2: shl edx, 2 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 47b4d5: sub edx, eax */
	m->eax = M32((DWORD)(m->esp + 0x40u));	/* 47b4d7: mov eax, dword ptr [esp + 0x40] */
	m->edx = M32((DWORD)(m->eax + m->edx*4 + 0x131b0c0u));	/* 47b4db: mov edx, dword ptr [eax + edx*4 + 0x131b0c0] */
	m->eax = M32((DWORD)(m->edx + 0x14u));	/* 47b4e2: mov eax, dword ptr [edx + 0x14] */
	m->edx = M32((DWORD)(m->ecx + 0x94u));	/* 47b4e5: mov edx, dword ptr [ecx + 0x94] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 47b4eb: add eax, ebx */
	m->edx = (DWORD)(m->edx + m->edx*2 + 0x0u);	/* 47b4ed: lea edx, [edx + edx*2] */
	m->ebx = M32((DWORD)(m->eax + 0x50u));	/* 47b4f0: mov ebx, dword ptr [eax + 0x50] */
	m->edx = (DWORD)(m->ebx + m->edx*4 + 0x0u);	/* 47b4f3: lea edx, [ebx + edx*4] */
	m->ebx = M32((DWORD)(m->edx + 0x0u));	/* 47b4f6: mov ebx, dword ptr [edx] */
	M32((DWORD)(m->esp + 0x1ecu)) = m->ebx;	/* 47b4f8: mov dword ptr [esp + 0x1ec], ebx */
	m->ebx = M32((DWORD)(m->edx + 0x4u));	/* 47b4ff: mov ebx, dword ptr [edx + 4] */
	M32((DWORD)(m->esp + 0x1f0u)) = m->ebx;	/* 47b502: mov dword ptr [esp + 0x1f0], ebx */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 47b509: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->esp + 0x1f4u)) = m->edx;	/* 47b50c: mov dword ptr [esp + 0x1f4], edx */
	m->edx = M32((DWORD)(m->ecx + 0x98u));	/* 47b513: mov edx, dword ptr [ecx + 0x98] */
	m->ebx = M32((DWORD)(m->eax + 0x50u));	/* 47b519: mov ebx, dword ptr [eax + 0x50] */
	m->edx = (DWORD)(m->edx + m->edx*2 + 0x0u);	/* 47b51c: lea edx, [edx + edx*2] */
	m->edx = (DWORD)(m->ebx + m->edx*4 + 0x0u);	/* 47b51f: lea edx, [ebx + edx*4] */
	m->ebx = M32((DWORD)(m->edx + 0x0u));	/* 47b522: mov ebx, dword ptr [edx] */
	M32((DWORD)(m->esp + 0x1f8u)) = m->ebx;	/* 47b524: mov dword ptr [esp + 0x1f8], ebx */
	m->ebx = M32((DWORD)(m->edx + 0x4u));	/* 47b52b: mov ebx, dword ptr [edx + 4] */
	M32((DWORD)(m->esp + 0x1fcu)) = m->ebx;	/* 47b52e: mov dword ptr [esp + 0x1fc], ebx */
	m->ebx = (DWORD)(m->esi + 0x60u);	/* 47b535: lea ebx, [esi + 0x60] */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 47b538: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->esp + 0x200u)) = m->edx;	/* 47b53b: mov dword ptr [esp + 0x200], edx */
	m->edx = M32((DWORD)(m->ecx + 0x9cu));	/* 47b542: mov edx, dword ptr [ecx + 0x9c] */
	m->eax = M32((DWORD)(m->eax + 0x50u));	/* 47b548: mov eax, dword ptr [eax + 0x50] */
	m->edx = (DWORD)(m->edx + m->edx*2 + 0x0u);	/* 47b54b: lea edx, [edx + edx*2] */
	m->edx = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 47b54e: lea edx, [eax + edx*4] */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 47b551: mov eax, dword ptr [edx] */
	M32((DWORD)(m->esp + 0x204u)) = m->eax;	/* 47b553: mov dword ptr [esp + 0x204], eax */
	m->eax = M32((DWORD)(m->edx + 0x4u));	/* 47b55a: mov eax, dword ptr [edx + 4] */
	M32((DWORD)(m->esp + 0x208u)) = m->eax;	/* 47b55d: mov dword ptr [esp + 0x208], eax */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 47b564: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->esp + 0x20cu)) = m->edx;	/* 47b567: mov dword ptr [esp + 0x20c], edx */
	m->eax = M32((DWORD)(m->ecx + 0x8cu));	/* 47b56e: mov eax, dword ptr [ecx + 0x8c] */
	m->edx = M32((DWORD)(m->esp + 0x40u));	/* 47b574: mov edx, dword ptr [esp + 0x40] */
	m->eax = M32((DWORD)(m->eax + 0x0u));	/* 47b578: mov eax, dword ptr [eax] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 47b57a: lea ecx, [eax + eax*4] */
	m->ecx = (DWORD)(m->ecx + m->ecx*8 + 0x0u);	/* 47b57d: lea ecx, [ecx + ecx*8] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 47b580: shl ecx, 2 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 47b583: sub ecx, eax */
	m->eax = (DWORD)(m->edx + m->ecx*4 + 0x131af38u);	/* 47b585: lea eax, [edx + ecx*4 + 0x131af38] */
	m->ecx = M32((DWORD)(m->edi + 0x2dfcu));	/* 47b58c: mov ecx, dword ptr [edi + 0x2dfc] */
	{ DWORD a_ = m->ecx, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 47b592: add ecx, 0x28 */
	m->edx = m->ebx;	/* 47b595: mov edx, ebx */
	M32((DWORD)(m->esp + 0x5cu)) = m->ecx;	/* 47b597: mov dword ptr [esp + 0x5c], ecx */
	M32((DWORD)(m->esp + 0x7cu)) = m->eax;	/* 47b59b: mov dword ptr [esp + 0x7c], eax */
	m->ecx = M32((DWORD)(m->edx + 0x0u));	/* 47b59f: mov ecx, dword ptr [edx] */
	m->eax = (DWORD)(m->esp + 0x16cu);	/* 47b5a1: lea eax, [esp + 0x16c] */
	M32((DWORD)(m->esp + 0x64u)) = m->ecx;	/* 47b5a8: mov dword ptr [esp + 0x64], ecx */
	M32((DWORD)(m->esp + 0x60u)) = 0x0u;	/* 47b5ac: mov dword ptr [esp + 0x60], 0 */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 47b5b4: mov ecx, dword ptr [edx + 4] */
	M32((DWORD)(m->esp + 0x84u)) = m->eax;	/* 47b5b7: mov dword ptr [esp + 0x84], eax */
	M32((DWORD)(m->esp + 0x68u)) = m->ecx;	/* 47b5be: mov dword ptr [esp + 0x68], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 47b5c2: mov ecx, dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 47b5c6: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->esp + 0x70u)) = m->ecx;	/* 47b5c9: mov dword ptr [esp + 0x70], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 47b5cd: mov ecx, dword ptr [esp + 0x20] */
	M32((DWORD)(m->esp + 0x6cu)) = m->edx;	/* 47b5d1: mov dword ptr [esp + 0x6c], edx */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 47b5d5: mov edx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x78u)) = m->ecx;	/* 47b5d9: mov dword ptr [esp + 0x78], ecx */
	M32((DWORD)(m->esp + 0x74u)) = m->edx;	/* 47b5dd: mov dword ptr [esp + 0x74], edx */
	m->edx = (DWORD)(m->esp + 0x1ecu);	/* 47b5e1: lea edx, [esp + 0x1ec] */
	M32((DWORD)(m->esp + 0x80u)) = m->edx;	/* 47b5e8: mov dword ptr [esp + 0x80], edx */
	M32((DWORD)(m->esp + 0x88u)) = 0x0u;	/* 47b5ef: mov dword ptr [esp + 0x88], 0 */
	M32((DWORD)(m->esp + 0x8cu)) = 0x0u;	/* 47b5fa: mov dword ptr [esp + 0x8c], 0 */
	goto L_47b67a;	/* 47b605: jmp 0x47b67a */
L_47b607:
	m->ecx = M32((DWORD)(m->edi + 0x2dfcu));	/* 47b607: mov ecx, dword ptr [edi + 0x2dfc] */
	m->eax = m->ebx;	/* 47b60d: mov eax, ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x2df0u)));	/* 47b60f: fld dword ptr [edi + 0x2df0] */
	{ DWORD a_ = m->ecx, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 47b615: add ecx, 0x28 */
	M32((DWORD)(m->esp + 0x60u)) = m->edx;	/* 47b618: mov dword ptr [esp + 0x60], edx */
	M32((DWORD)(m->esp + 0x5cu)) = m->ecx;	/* 47b61c: mov dword ptr [esp + 0x5c], ecx */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47b620: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x64u)) = m->ecx;	/* 47b622: mov dword ptr [esp + 0x64], ecx */
	M32((DWORD)(m->esp + 0x7cu)) = m->edx;	/* 47b626: mov dword ptr [esp + 0x7c], edx */
	m->ecx = M32((DWORD)(m->eax + 0x4u));	/* 47b62a: mov ecx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x8cu)) = m->edx;	/* 47b62d: mov dword ptr [esp + 0x8c], edx */
	M32((DWORD)(m->esp + 0x68u)) = m->ecx;	/* 47b634: mov dword ptr [esp + 0x68], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 47b638: mov ecx, dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47b63c: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x70u)) = m->ecx;	/* 47b63f: mov dword ptr [esp + 0x70], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 47b643: mov ecx, dword ptr [esp + 0x20] */
	M32((DWORD)(m->esp + 0x6cu)) = m->eax;	/* 47b647: mov dword ptr [esp + 0x6c], eax */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 47b64b: mov eax, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x78u)) = m->ecx;	/* 47b64f: mov dword ptr [esp + 0x78], ecx */
	MF((DWORD)(m->esp + 0x88u)) = (float)ST(0); FPOP();	/* 47b653: fstp dword ptr [esp + 0x88] */
	M32((DWORD)(m->esp + 0x74u)) = m->eax;	/* 47b65a: mov dword ptr [esp + 0x74], eax */
	m->eax = (DWORD)(m->esp + 0x124u);	/* 47b65e: lea eax, [esp + 0x124] */
	m->ecx = (DWORD)(m->esp + 0x16cu);	/* 47b665: lea ecx, [esp + 0x16c] */
	M32((DWORD)(m->esp + 0x80u)) = m->eax;	/* 47b66c: mov dword ptr [esp + 0x80], eax */
	M32((DWORD)(m->esp + 0x84u)) = m->ecx;	/* 47b673: mov dword ptr [esp + 0x84], ecx */
L_47b67a:
	m->ecx = M32((DWORD)(m->esp + 0x40u));	/* 47b67a: mov ecx, dword ptr [esp + 0x40] */
	m->edx = (DWORD)(m->esp + 0x5cu);	/* 47b67e: lea edx, [esp + 0x5c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47b682: push edx */
	m->esp -= 4; M32(m->esp) = 0x47b688u; native_call(m, 0x479950u);	/* 47b683: call 0x479950 */
L_47b688:
	m->eax = M32((DWORD)(m->edi + 0x2e04u));	/* 47b688: mov eax, dword ptr [edi + 0x2e04] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47b68e: test eax, eax */
	if (m->sf != m->of) goto L_47b6b3;	/* 47b690: jl 0x47b6b3 */
	m->ecx = M32((DWORD)(m->esp + 0x40u));	/* 47b692: mov ecx, dword ptr [esp + 0x40] */
	{ DWORD v_ = 0x47435000u; m->esp -= 4; M32(m->esp) = v_; }	/* 47b696: push 0x47435000 */
	m->edx = (DWORD)(m->ecx + 0x20f397cu);	/* 47b69b: lea edx, [ecx + 0x20f397c] */
	{ DWORD a_ = m->ecx, b_ = 0x20f3970u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 47b6a1: add ecx, 0x20f3970 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47b6a7: push edx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 47b6a8: push ebx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47b6a9: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47b6aa: push eax */
	m->esp -= 4; M32(m->esp) = 0x47b6b0u; native_call(m, 0x456ed0u);	/* 47b6ab: call 0x456ed0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47b6b0: add esp, 0x14 */
L_47b6b3:
	M32((DWORD)(m->esi + 0xd0u)) = 0x1u;	/* 47b6b3: mov dword ptr [esi + 0xd0], 1 */
	goto L_47b6c3;	/* 47b6bd: jmp 0x47b6c3 */
L_47b6bf:
	m->edi = M32((DWORD)(m->esp + 0x38u));	/* 47b6bf: mov edi, dword ptr [esp + 0x38] */
L_47b6c3:
	{ DWORD a_ = M32((DWORD)(m->esi + 0xd0u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47b6c3: cmp dword ptr [esi + 0xd0], 1 */
	if (!m->zf) goto L_47b8c7;	/* 47b6ca: jne 0x47b8c7 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x2df4u)));	/* 47b6d0: fld dword ptr [edi + 0x2df4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47b6d6: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47b6dc: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47b6de: test ah, 0x41 */
	if (!m->zf) goto L_47b8c7;	/* 47b6e1: jne 0x47b8c7 */
	m->ebx = M32((DWORD)(m->esp + 0x40u));	/* 47b6e7: mov ebx, dword ptr [esp + 0x40] */
	M32((DWORD)(m->esp + 0x3cu)) = 0x0u;	/* 47b6eb: mov dword ptr [esp + 0x3c], 0 */
	m->eax = M32((DWORD)(m->ebx + 0x202e8c8u));	/* 47b6f3: mov eax, dword ptr [ebx + 0x202e8c8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47b6f9: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_47b8c7;	/* 47b6fb: jle 0x47b8c7 */
	{ DWORD a_ = m->ebx, b_ = 0x1cd9530u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 47b701: add ebx, 0x1cd9530 */
L_47b707:
	{ DWORD a_ = M32((DWORD)(m->ebx + 0xffffffc4u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47b707: cmp dword ptr [ebx - 0x3c], 1 */
	if (!m->zf) goto L_47b8a6;	/* 47b70b: jne 0x47b8a6 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0xffffff98u)));	/* 47b711: fld dword ptr [ebx - 0x68] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9534u)); FPOP();	/* 47b714: fcomp dword ptr [0x4a9534] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47b71a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47b71c: test ah, 0x41 */
	if (!m->zf) goto L_47b8a6;	/* 47b71f: jne 0x47b8a6 */
	m->ecx = M32((DWORD)(m->esp + 0x40u));	/* 47b725: mov ecx, dword ptr [esp + 0x40] */
	m->eax = M32((DWORD)(m->ebx + 0xffffff88u));	/* 47b729: mov eax, dword ptr [ebx - 0x78] */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->ecx + 0x202e8d4u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47b72c: cmp eax, dword ptr [ecx + 0x202e8d4] */
	if (!m->zf) goto L_47b8a6;	/* 47b732: jne 0x47b8a6 */
	m->edx = M32((DWORD)(m->esp + 0x3cu));	/* 47b738: mov edx, dword ptr [esp + 0x3c] */
	m->eax = M32((DWORD)(m->esi + 0xb8u));	/* 47b73c: mov eax, dword ptr [esi + 0xb8] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47b742: cmp eax, edx */
	if (m->zf) goto L_47b8a6;	/* 47b744: je 0x47b8a6 */
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x86c4u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47b74a: cmp dword ptr [ebx + 0x86c4], 1 */
	if (m->zf) goto L_47b8a6;	/* 47b751: je 0x47b8a6 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0xfffffff8u)));	/* 47b757: fld dword ptr [ebx - 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x84u));	/* 47b75a: fsub dword ptr [esi + 0x84] */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47b760: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0xfffffffcu)));	/* 47b764: fld dword ptr [ebx - 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x88u));	/* 47b767: fsub dword ptr [esi + 0x88] */
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 47b76d: mov eax, dword ptr [esp + 0xc] */
	M32((DWORD)(m->esp + 0x48u)) = m->eax;	/* 47b771: mov dword ptr [esp + 0x48], eax */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47b775: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 47b779: fld dword ptr [ebx] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x8cu));	/* 47b77b: fsub dword ptr [esi + 0x8c] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 47b781: mov ecx, dword ptr [esp + 0x10] */
	M32((DWORD)(m->esp + 0x4cu)) = m->ecx;	/* 47b785: mov dword ptr [esp + 0x4c], ecx */
	m->ecx = (DWORD)(m->esp + 0x48u);	/* 47b789: lea ecx, [esp + 0x48] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 47b78d: fstp dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 47b791: mov edx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->esp + 0x50u)) = m->edx;	/* 47b795: mov dword ptr [esp + 0x50], edx */
	m->esp -= 4; M32(m->esp) = 0x47b79eu; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 47b799: call 0x467760 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->edi + 0x2df4u));	/* 47b79e: fcom dword ptr [edi + 0x2df4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47b7a4: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47b7a6: test ah, 1 */
	if (m->zf) goto L_47b8a4;	/* 47b7a9: je 0x47b8a4 */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->edi + 0x2df4u));	/* 47b7af: fdiv dword ptr [edi + 0x2df4] */
	m->eax = M32((DWORD)(m->esi + 0x8u));	/* 47b7b5: mov eax, dword ptr [esi + 8] */
	m->ecx = M32((DWORD)(m->edi + 0x2dfcu));	/* 47b7b8: mov ecx, dword ptr [edi + 0x2dfc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47b7be: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47b7bf: push ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 47b7c0: fmul dword ptr [0x4a942c] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 47b7c6: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 47b7cc: fstp dword ptr [esp + 0x30] */
	FPUSH((long double)(int)M32((DWORD)(m->edi + 0x2de0u)));	/* 47b7d0: fild dword ptr [edi + 0x2de0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 47b7d6: fmul dword ptr [esp + 0x30] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 47b7da: call 0x49ec14 */
	m->edx = M32((DWORD)(m->edi + 0x2ddcu));	/* 47b7df: mov edx, dword ptr [edi + 0x2ddc] */
	m->ecx = M32((DWORD)(m->esi + 0xcu));	/* 47b7e5: mov ecx, dword ptr [esi + 0xc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47b7e8: push eax */
	m->eax = M32((DWORD)(m->esp + 0x48u));	/* 47b7e9: mov eax, dword ptr [esp + 0x48] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47b7ed: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47b7ee: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47b7ef: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x58u));	/* 47b7f0: mov ecx, dword ptr [esp + 0x58] */
	m->esp -= 4; M32(m->esp) = 0x47b7f9u; native_call(m, 0x460000u);	/* 47b7f4: call 0x460000 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x2e14u)));	/* 47b7f9: fld dword ptr [edi + 0x2e14] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47b7ff: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47b805: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47b807: test ah, 0x41 */
	if (!m->zf) goto L_47b8a6;	/* 47b80a: jne 0x47b8a6 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x2e14u)));	/* 47b810: fld dword ptr [edi + 0x2e14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 47b816: fld dword ptr [esp + 0x48] */
	ST(0) = ST(0) * ST(1);	/* 47b81a: fmul st(1) */
	m->edx = (DWORD)(m->ebx + 0x86d4u);	/* 47b81c: lea edx, [ebx + 0x86d4] */
	MF((DWORD)(m->esp + 0x184u)) = (float)ST(0); FPOP();	/* 47b822: fstp dword ptr [esp + 0x184] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 47b829: fld dword ptr [esp + 0x4c] */
	ST(0) = ST(0) * ST(1);	/* 47b82d: fmul st(1) */
	MF((DWORD)(m->esp + 0x188u)) = (float)ST(0); FPOP();	/* 47b82f: fstp dword ptr [esp + 0x188] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x50u));	/* 47b836: fmul dword ptr [esp + 0x50] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x184u)));	/* 47b83a: fld dword ptr [esp + 0x184] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 47b841: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x190u)) = (float)ST(0); FPOP();	/* 47b847: fstp dword ptr [esp + 0x190] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x188u)));	/* 47b84e: fld dword ptr [esp + 0x188] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 47b855: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x194u)) = (float)ST(0); FPOP();	/* 47b85b: fstp dword ptr [esp + 0x194] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 47b862: fmul dword ptr [0x4a9418] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 47b868: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x190u));	/* 47b86c: fmul dword ptr [esp + 0x190] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 47b873: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x194u)));	/* 47b877: fld dword ptr [esp + 0x194] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 47b87e: fmul dword ptr [esp + 0x28] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 47b882: mov eax, dword ptr [esp + 0x2c] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 47b886: mov dword ptr [edx], eax */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 47b888: fstp dword ptr [esp + 0x30] */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 47b88c: mov ecx, dword ptr [esp + 0x30] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 47b890: fmul dword ptr [esp + 0x28] */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 47b894: mov dword ptr [edx + 4], ecx */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 47b897: fstp dword ptr [esp + 0x34] */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 47b89b: mov eax, dword ptr [esp + 0x34] */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 47b89f: mov dword ptr [edx + 8], eax */
	goto L_47b8a6;	/* 47b8a2: jmp 0x47b8a6 */
L_47b8a4:
	ST(0) = ST(0); FPOP();	/* 47b8a4: fstp st(0) */
L_47b8a6:
	m->ecx = M32((DWORD)(m->esp + 0x40u));	/* 47b8a6: mov ecx, dword ptr [esp + 0x40] */
	m->eax = M32((DWORD)(m->esp + 0x3cu));	/* 47b8aa: mov eax, dword ptr [esp + 0x3c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 47b8ae: inc eax */
	{ DWORD a_ = m->ebx, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 47b8af: add ebx, 0x8888 */
	m->edx = M32((DWORD)(m->ecx + 0x202e8c8u));	/* 47b8b5: mov edx, dword ptr [ecx + 0x202e8c8] */
	M32((DWORD)(m->esp + 0x3cu)) = m->eax;	/* 47b8bb: mov dword ptr [esp + 0x3c], eax */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47b8bf: cmp eax, edx */
	if (m->sf != m->of) goto L_47b707;	/* 47b8c1: jl 0x47b707 */
L_47b8c7:
	m->edx = M32((DWORD)(m->ebp + 0x8u));	/* 47b8c7: mov edx, dword ptr [ebp + 8] */
	m->ecx = M32((DWORD)(m->esp + 0x40u));	/* 47b8ca: mov ecx, dword ptr [esp + 0x40] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47b8ce: push edx */
	m->esp -= 4; M32(m->esp) = 0x47b8d4u; native_call(m, 0x47cf10u);	/* 47b8cf: call 0x47cf10 */
	m->edi = M32(m->esp); m->esp += 4;	/* 47b8d4: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 47b8d5: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 47b8d6: pop ebx */
	m->esp = m->ebp;	/* 47b8d7: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 47b8d9: pop ebp */
	m->esp += 4 + 8; return;	/* 47b8da: ret 8 */
L_47b8dd:
	m->ebx = (DWORD)(m->esi + 0x84u);	/* 47b8dd: lea ebx, [esi + 0x84] */
	m->edi = (DWORD)(m->esi + 0x78u);	/* 47b8e3: lea edi, [esi + 0x78] */
	m->eax = m->ebx;	/* 47b8e6: mov eax, ebx */
	m->ecx = m->edi;	/* 47b8e8: mov ecx, edi */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 47b8ea: mov edx, dword ptr [eax] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 47b8ec: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47b8ee: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 47b8f1: mov dword ptr [ecx + 4], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47b8f4: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 47b8f7: mov dword ptr [ecx + 8], eax */
	m->eax = M32((DWORD)(m->esi + 0xcu));	/* 47b8fa: mov eax, dword ptr [esi + 0xc] */
	m->edx = m->eax;	/* 47b8fd: mov edx, eax */
	m->ecx = M32((DWORD)(m->esp + 0x40u));	/* 47b8ff: mov ecx, dword ptr [esp + 0x40] */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 47b903: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 47b906: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 47b908: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 47b90b: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 47b90d: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 47b910: add edx, eax */
	m->eax = M32((DWORD)(m->ecx + m->edx*8 + 0x1cd94b8u));	/* 47b912: mov eax, dword ptr [ecx + edx*8 + 0x1cd94b8] */
	m->edx = M32((DWORD)(m->ecx + 0x202e8d4u));	/* 47b919: mov edx, dword ptr [ecx + 0x202e8d4] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47b91f: cmp eax, edx */
	if (!m->zf) goto L_47bff4;	/* 47b921: jne 0x47bff4 */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 47b927: mov edx, dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x2e0cu)));	/* 47b92b: fld dword ptr [edx + 0x2e0c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47b931: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47b937: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47b939: test ah, 0x41 */
	if (!m->zf) goto L_47bc7b;	/* 47b93c: jne 0x47bc7b */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x2de8u)));	/* 47b942: fld dword ptr [edx + 0x2de8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47b948: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47b94e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47b950: test ah, 0x41 */
	if (!m->zf) goto L_47bc7b;	/* 47b953: jne 0x47bc7b */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0xc0u)));	/* 47b959: fld dword ptr [esi + 0xc0] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0xcu));	/* 47b95f: fsub dword ptr [ebp + 0xc] */
	MF((DWORD)(m->esi + 0xc0u)) = (float)ST(0);	/* 47b962: fst dword ptr [esi + 0xc0] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47b968: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47b96e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47b970: test ah, 0x41 */
	if (m->zf) goto L_47bc7b;	/* 47b973: je 0x47bc7b */
	{ DWORD a_ = M32((DWORD)(m->edx + 0x2dfcu)), b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47b979: cmp dword ptr [edx + 0x2dfc], 3 */
	if (m->zf) goto L_47b998;	/* 47b980: je 0x47b998 */
	m->eax = M32((DWORD)(m->edx + 0x2de8u));	/* 47b982: mov eax, dword ptr [edx + 0x2de8] */
	m->edx = M32((DWORD)(m->edx + 0x2e0cu));	/* 47b988: mov edx, dword ptr [edx + 0x2e0c] */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 47b98e: mov dword ptr [esp + 0x28], eax */
	M32((DWORD)(m->esp + 0x44u)) = m->edx;	/* 47b992: mov dword ptr [esp + 0x44], edx */
	goto L_47b9e0;	/* 47b996: jmp 0x47b9e0 */
L_47b998:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x70u)));	/* 47b998: fld dword ptr [esi + 0x70] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a947cu));	/* 47b99b: fmul dword ptr [0x4a947c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 47b9a1: fsub dword ptr [0x4a9424] */
	{ long double t = ST(0); FPUSH(t); }	/* 47b9a7: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 47b9a9: fmul st(1) */
	ST(0) = ST(0) * ST(1);	/* 47b9ab: fmul st(1) */
	ST(0) = ST(0) * ST(1);	/* 47b9ad: fmul st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 47b9af: fadd dword ptr [0x4a93ec] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edx + 0x2de8u));	/* 47b9b5: fmul dword ptr [edx + 0x2de8] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 47b9bb: fstp dword ptr [esp + 0x28] */
	ST(0) = ST(0); FPOP();	/* 47b9bf: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x70u)));	/* 47b9c1: fld dword ptr [esi + 0x70] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 47b9c4: fadd dword ptr [0x4a9424] */
	{ long double t = ST(0); FPUSH(t); }	/* 47b9ca: fld st(0) */
	{ long double t = ST(0); FPUSH(t); }	/* 47b9cc: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 47b9ce: fmul st(1) */
	ST(0) = ST(0) * ST(2);	/* 47b9d0: fmul st(2) */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(m->edx + 0x2e0cu));	/* 47b9d2: fdivr dword ptr [edx + 0x2e0c] */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 47b9d8: fstp dword ptr [esp + 0x44] */
	ST(0) = ST(0); FPOP();	/* 47b9dc: fstp st(0) */
	ST(0) = ST(0); FPOP();	/* 47b9de: fstp st(0) */
L_47b9e0:
	m->eax = M32((DWORD)(m->esi + 0xbcu));	/* 47b9e0: mov eax, dword ptr [esi + 0xbc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47b9e6: test eax, eax */
	if (m->sf != m->of) goto L_47ba39;	/* 47b9e8: jl 0x47ba39 */
	m->edx = m->eax;	/* 47b9ea: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 47b9ec: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 47b9ef: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 47b9f1: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 47b9f4: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 47b9f6: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 47b9f9: add edx, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + m->edx*8 + 0x1cd9528u)));	/* 47b9fb: fld dword ptr [ecx + edx*8 + 0x1cd9528] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 47ba02: fsub dword ptr [edi] */
	m->eax = (DWORD)(m->ecx + m->edx*8 + 0x1cd9528u);	/* 47ba04: lea eax, [ecx + edx*8 + 0x1cd9528] */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47ba0b: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 47ba0f: fld dword ptr [eax + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47ba12: fsub dword ptr [edi + 4] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47ba15: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 47ba19: fld dword ptr [eax + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47ba1c: fsub dword ptr [edi + 8] */
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 47ba1f: mov eax, dword ptr [esp + 0xc] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 47ba23: mov ecx, dword ptr [esp + 0x10] */
	M32((DWORD)(m->esp + 0x48u)) = m->eax;	/* 47ba27: mov dword ptr [esp + 0x48], eax */
	M32((DWORD)(m->esp + 0x4cu)) = m->ecx;	/* 47ba2b: mov dword ptr [esp + 0x4c], ecx */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 47ba2f: fstp dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 47ba33: mov edx, dword ptr [esp + 0x14] */
	goto L_47ba73;	/* 47ba37: jmp 0x47ba73 */
L_47ba39:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0xc4u)));	/* 47ba39: fld dword ptr [esi + 0xc4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 47ba3f: fsub dword ptr [edi] */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47ba41: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0xc8u)));	/* 47ba45: fld dword ptr [esi + 0xc8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47ba4b: fsub dword ptr [edi + 4] */
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 47ba4e: mov eax, dword ptr [esp + 0xc] */
	M32((DWORD)(m->esp + 0x48u)) = m->eax;	/* 47ba52: mov dword ptr [esp + 0x48], eax */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47ba56: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0xccu)));	/* 47ba5a: fld dword ptr [esi + 0xcc] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47ba60: fsub dword ptr [edi + 8] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 47ba63: mov ecx, dword ptr [esp + 0x10] */
	M32((DWORD)(m->esp + 0x4cu)) = m->ecx;	/* 47ba67: mov dword ptr [esp + 0x4c], ecx */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 47ba6b: fstp dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 47ba6f: mov edx, dword ptr [esp + 0x14] */
L_47ba73:
	m->ecx = (DWORD)(m->esp + 0x48u);	/* 47ba73: lea ecx, [esp + 0x48] */
	M32((DWORD)(m->esp + 0x50u)) = m->edx;	/* 47ba77: mov dword ptr [esp + 0x50], edx */
	m->esp -= 4; M32(m->esp) = 0x47ba80u; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 47ba7b: call 0x467760 */
	ST(0) = ST(0); FPOP();	/* 47ba80: fstp st(0) */
	m->ecx = (DWORD)(m->esi + 0xa0u);	/* 47ba82: lea ecx, [esi + 0xa0] */
	m->esp -= 4; M32(m->esp) = 0x47ba8du; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 47ba88: call 0x467760 */
	ST(0) = ST(0); FPOP();	/* 47ba8d: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x50u)));	/* 47ba8f: fld dword ptr [esp + 0x50] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xa8u));	/* 47ba93: fmul dword ptr [esi + 0xa8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 47ba99: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xa4u));	/* 47ba9d: fmul dword ptr [esi + 0xa4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47baa3: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 47baa5: fld dword ptr [esp + 0x48] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xa0u));	/* 47baa9: fmul dword ptr [esi + 0xa0] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47baaf: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 47bab1: fld dword ptr [esp + 0x44] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 47bab5: call 0x49ec14 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax*4 + 0xa17f38u)));	/* 47baba: fld dword ptr [eax*4 + 0xa17f38] */
	FCOM(ST(0), ST(1)); FPOP(); FPOP();	/* 47bac1: fcompp  */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47bac3: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47bac5: test ah, 0x41 */
	if (!m->zf) goto L_47bc2b;	/* 47bac8: jne 0x47bc2b */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x50u)));	/* 47bace: fld dword ptr [esp + 0x50] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xa4u));	/* 47bad2: fmul dword ptr [esi + 0xa4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 47bad8: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xa8u));	/* 47badc: fmul dword ptr [esi + 0xa8] */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47bae2: fsubp st(1) */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47bae4: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 47bae8: fld dword ptr [esp + 0x48] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xa8u));	/* 47baec: fmul dword ptr [esi + 0xa8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x50u)));	/* 47baf2: fld dword ptr [esp + 0x50] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xa0u));	/* 47baf6: fmul dword ptr [esi + 0xa0] */
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 47bafc: mov eax, dword ptr [esp + 0xc] */
	M32((DWORD)(m->esp + 0x148u)) = m->eax;	/* 47bb00: mov dword ptr [esp + 0x148], eax */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47bb07: fsubp st(1) */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47bb09: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 47bb0d: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xa0u));	/* 47bb11: fmul dword ptr [esi + 0xa0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 47bb17: fld dword ptr [esp + 0x48] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xa4u));	/* 47bb1b: fmul dword ptr [esi + 0xa4] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 47bb21: mov ecx, dword ptr [esp + 0x10] */
	M32((DWORD)(m->esp + 0x14cu)) = m->ecx;	/* 47bb25: mov dword ptr [esp + 0x14c], ecx */
	m->ecx = (DWORD)(m->esp + 0x148u);	/* 47bb2c: lea ecx, [esp + 0x148] */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47bb33: fsubp st(1) */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 47bb35: fstp dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 47bb39: mov edx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->esp + 0x150u)) = m->edx;	/* 47bb3d: mov dword ptr [esp + 0x150], edx */
	m->esp -= 4; M32(m->esp) = 0x47bb49u; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 47bb44: call 0x467760 */
	ST(0) = ST(0); FPOP();	/* 47bb49: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 47bb4b: fld dword ptr [esp + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa44cu));	/* 47bb4f: fmul dword ptr [0x4aa44c] */
	m->eax = (DWORD)(m->esp + 0x19cu);	/* 47bb55: lea eax, [esp + 0x19c] */
	m->ecx = (DWORD)(m->esp + 0x1acu);	/* 47bb5c: lea ecx, [esp + 0x1ac] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47bb63: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47bb64: push ecx */
	MF((DWORD)(m->esp + 0x1a4u)) = (float)ST(0); FPOP();	/* 47bb65: fstp dword ptr [esp + 0x1a4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x150u)));	/* 47bb6c: fld dword ptr [esp + 0x150] */
	MF((DWORD)(m->esp + 0x1a8u)) = (float)ST(0); FPOP();	/* 47bb73: fstp dword ptr [esp + 0x1a8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x154u)));	/* 47bb7a: fld dword ptr [esp + 0x154] */
	MF((DWORD)(m->esp + 0x1acu)) = (float)ST(0); FPOP();	/* 47bb81: fstp dword ptr [esp + 0x1ac] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x158u)));	/* 47bb88: fld dword ptr [esp + 0x158] */
	MF((DWORD)(m->esp + 0x1b0u)) = (float)ST(0); FPOP();	/* 47bb8f: fstp dword ptr [esp + 0x1b0] */
	m->esp -= 4; M32(m->esp) = 0x47bb9bu; native_call(m, 0x47d9a0u);	/* 47bb96: call 0x47d9a0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1d4u)));	/* 47bb9b: fld dword ptr [esp + 0x1d4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xa8u));	/* 47bba2: fmul dword ptr [esi + 0xa8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1c4u)));	/* 47bba8: fld dword ptr [esp + 0x1c4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xa4u));	/* 47bbaf: fmul dword ptr [esi + 0xa4] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47bbb5: add esp, 8 */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47bbb8: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1acu)));	/* 47bbba: fld dword ptr [esp + 0x1ac] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xa0u));	/* 47bbc1: fmul dword ptr [esi + 0xa0] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47bbc7: faddp st(1) */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 47bbc9: fstp dword ptr [esp + 0x48] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1b0u)));	/* 47bbcd: fld dword ptr [esp + 0x1b0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xa0u));	/* 47bbd4: fmul dword ptr [esi + 0xa0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1d0u)));	/* 47bbda: fld dword ptr [esp + 0x1d0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xa8u));	/* 47bbe1: fmul dword ptr [esi + 0xa8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47bbe7: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1c0u)));	/* 47bbe9: fld dword ptr [esp + 0x1c0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xa4u));	/* 47bbf0: fmul dword ptr [esi + 0xa4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47bbf6: faddp st(1) */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 47bbf8: fstp dword ptr [esp + 0x4c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1b4u)));	/* 47bbfc: fld dword ptr [esp + 0x1b4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xa0u));	/* 47bc03: fmul dword ptr [esi + 0xa0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1d4u)));	/* 47bc09: fld dword ptr [esp + 0x1d4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xa8u));	/* 47bc10: fmul dword ptr [esi + 0xa8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47bc16: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1c4u)));	/* 47bc18: fld dword ptr [esp + 0x1c4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xa4u));	/* 47bc1f: fmul dword ptr [esi + 0xa4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47bc25: faddp st(1) */
	MF((DWORD)(m->esp + 0x50u)) = (float)ST(0); FPOP();	/* 47bc27: fstp dword ptr [esp + 0x50] */
L_47bc2b:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 47bc2b: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x48u));	/* 47bc2f: fmul dword ptr [esp + 0x48] */
	M32((DWORD)(m->esi + 0xc0u)) = 0x3d888889u;	/* 47bc33: mov dword ptr [esi + 0xc0], 0x3d888889 */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47bc3d: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 47bc41: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 47bc45: fmul dword ptr [esp + 0x28] */
	m->edx = M32((DWORD)(m->esp + 0xcu));	/* 47bc49: mov edx, dword ptr [esp + 0xc] */
	M32((DWORD)(m->esi + 0xa0u)) = m->edx;	/* 47bc4d: mov dword ptr [esi + 0xa0], edx */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 47bc53: mov edx, dword ptr [esp + 0x38] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47bc57: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x50u)));	/* 47bc5b: fld dword ptr [esp + 0x50] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 47bc5f: fmul dword ptr [esp + 0x28] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 47bc63: mov eax, dword ptr [esp + 0x10] */
	M32((DWORD)(m->esi + 0xa4u)) = m->eax;	/* 47bc67: mov dword ptr [esi + 0xa4], eax */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 47bc6d: fstp dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 47bc71: mov ecx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->esi + 0xa8u)) = m->ecx;	/* 47bc75: mov dword ptr [esi + 0xa8], ecx */
L_47bc7b:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x2de8u)));	/* 47bc7b: fld dword ptr [edx + 0x2de8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47bc81: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47bc87: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47bc89: test ah, 0x41 */
	if (!m->zf) goto L_47bd47;	/* 47bc8c: jne 0x47bd47 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0xcu)));	/* 47bc92: fld dword ptr [ebp + 0xc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xa0u));	/* 47bc95: fmul dword ptr [esi + 0xa0] */
	m->ecx = (DWORD)(m->esi + 0xacu);	/* 47bc9b: lea ecx, [esi + 0xac] */
	m->edx = m->ecx;	/* 47bca1: mov edx, ecx */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47bca3: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0xcu)));	/* 47bca7: fld dword ptr [ebp + 0xc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xa4u));	/* 47bcaa: fmul dword ptr [esi + 0xa4] */
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 47bcb0: mov eax, dword ptr [esp + 0xc] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47bcb4: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0xcu)));	/* 47bcb8: fld dword ptr [ebp + 0xc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xa8u));	/* 47bcbb: fmul dword ptr [esi + 0xa8] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 47bcc1: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 47bcc3: mov eax, dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 47bcc7: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0xcu)));	/* 47bccb: fld dword ptr [ebp + 0xc] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x70u));	/* 47bcce: fadd dword ptr [esi + 0x70] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 47bcd1: mov dword ptr [edx + 4], eax */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 47bcd4: mov eax, dword ptr [esp + 0x14] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0x74u)); FPOP();	/* 47bcd8: fcomp dword ptr [esi + 0x74] */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 47bcdb: mov dword ptr [edx + 8], eax */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47bcde: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47bce0: test ah, 0x41 */
	if (!m->zf) goto L_47bd13;	/* 47bce3: jne 0x47bd13 */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 47bce5: mov edx, dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x2e0cu)));	/* 47bce9: fld dword ptr [edx + 0x2e0c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47bcef: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47bcf5: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47bcf7: test ah, 0x41 */
	if (m->zf) goto L_47bd13;	/* 47bcfa: je 0x47bd13 */
	m->eax = (DWORD)(m->esi + 0x60u);	/* 47bcfc: lea eax, [esi + 0x60] */
	m->ecx = m->ebx;	/* 47bcff: mov ecx, ebx */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 47bd01: mov edx, dword ptr [eax] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 47bd03: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47bd05: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 47bd08: mov dword ptr [ecx + 4], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47bd0b: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 47bd0e: mov dword ptr [ecx + 8], eax */
	goto L_47bd79;	/* 47bd11: jmp 0x47bd79 */
L_47bd13:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x0u)));	/* 47bd13: fld dword ptr [ecx] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 47bd15: fadd dword ptr [edi] */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47bd17: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x4u)));	/* 47bd1b: fld dword ptr [edi + 4] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x4u));	/* 47bd1e: fadd dword ptr [ecx + 4] */
	m->edx = M32((DWORD)(m->esp + 0xcu));	/* 47bd21: mov edx, dword ptr [esp + 0xc] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47bd25: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x8u)));	/* 47bd29: fld dword ptr [edi + 8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x8u));	/* 47bd2c: fadd dword ptr [ecx + 8] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 47bd2f: mov eax, dword ptr [esp + 0x10] */
	m->ecx = m->ebx;	/* 47bd33: mov ecx, ebx */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 47bd35: mov dword ptr [ecx], edx */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 47bd37: fstp dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 47bd3b: mov edx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 47bd3f: mov dword ptr [ecx + 4], eax */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 47bd42: mov dword ptr [ecx + 8], edx */
	goto L_47bd79;	/* 47bd45: jmp 0x47bd79 */
L_47bd47:
	m->eax = (DWORD)(m->esi + 0xa0u);	/* 47bd47: lea eax, [esi + 0xa0] */
	m->ecx = (DWORD)(m->esi + 0xacu);	/* 47bd4d: lea ecx, [esi + 0xac] */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 47bd53: mov edx, dword ptr [eax] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 47bd55: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47bd57: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 47bd5a: mov dword ptr [ecx + 4], edx */
	m->edx = m->ebx;	/* 47bd5d: mov edx, ebx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47bd5f: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 47bd62: mov dword ptr [ecx + 8], eax */
	m->ecx = (DWORD)(m->esi + 0x60u);	/* 47bd65: lea ecx, [esi + 0x60] */
	m->eax = M32((DWORD)(m->esi + 0x60u));	/* 47bd68: mov eax, dword ptr [esi + 0x60] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 47bd6b: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->ecx + 0x4u));	/* 47bd6d: mov eax, dword ptr [ecx + 4] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 47bd70: mov dword ptr [edx + 4], eax */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 47bd73: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 47bd76: mov dword ptr [edx + 8], ecx */
L_47bd79:
	m->ecx = M32((DWORD)(m->esi + 0xb4u));	/* 47bd79: mov ecx, dword ptr [esi + 0xb4] */
	m->edx = M32((DWORD)(m->esi + 0xacu));	/* 47bd7f: mov edx, dword ptr [esi + 0xac] */
	m->eax = M32((DWORD)(m->esi + 0xb0u));	/* 47bd85: mov eax, dword ptr [esi + 0xb0] */
	M32((DWORD)(m->esp + 0x15cu)) = m->ecx;	/* 47bd8b: mov dword ptr [esp + 0x15c], ecx */
	m->ecx = (DWORD)(m->esp + 0x154u);	/* 47bd92: lea ecx, [esp + 0x154] */
	M32((DWORD)(m->esp + 0x154u)) = m->edx;	/* 47bd99: mov dword ptr [esp + 0x154], edx */
	M32((DWORD)(m->esp + 0x158u)) = m->eax;	/* 47bda0: mov dword ptr [esp + 0x158], eax */
	m->esp -= 4; M32(m->esp) = 0x47bdacu; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 47bda7: call 0x467760 */
	m->edx = M32((DWORD)(m->esp + 0x40u));	/* 47bdac: mov edx, dword ptr [esp + 0x40] */
	M32((DWORD)(m->esp + 0x28u)) = 0x7f7fffffu;	/* 47bdb0: mov dword ptr [esp + 0x28], 0x7f7fffff */
	ST(0) = ST(0); FPOP();	/* 47bdb8: fstp st(0) */
	m->eax = M32((DWORD)(m->edx + 0x202e8c8u));	/* 47bdba: mov eax, dword ptr [edx + 0x202e8c8] */
	M32((DWORD)(m->esp + 0x3cu)) = 0x0u;	/* 47bdc0: mov dword ptr [esp + 0x3c], 0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47bdc8: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_47bed3;	/* 47bdca: jle 0x47bed3 */
	m->eax = m->edx;	/* 47bdd0: mov eax, edx */
	{ DWORD a_ = m->eax, b_ = 0x1cd9528u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 47bdd2: add eax, 0x1cd9528 */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 47bdd7: mov dword ptr [esp + 0x24], eax */
L_47bddb:
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 47bddb: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD a_ = M32((DWORD)(m->ecx + 0xffffffccu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47bddf: cmp dword ptr [ecx - 0x34], 1 */
	if (!m->zf) goto L_47beac;	/* 47bde3: jne 0x47beac */
	m->edx = m->ecx;	/* 47bde9: mov edx, ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0xffffffa0u)));	/* 47bdeb: fld dword ptr [edx - 0x60] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9534u)); FPOP();	/* 47bdee: fcomp dword ptr [0x4a9534] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47bdf4: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47bdf6: test ah, 0x41 */
	if (!m->zf) goto L_47beac;	/* 47bdf9: jne 0x47beac */
	m->eax = M32((DWORD)(m->esp + 0x3cu));	/* 47bdff: mov eax, dword ptr [esp + 0x3c] */
	m->ecx = M32((DWORD)(m->esi + 0xcu));	/* 47be03: mov ecx, dword ptr [esi + 0xc] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47be06: cmp eax, ecx */
	if (m->zf) goto L_47beac;	/* 47be08: je 0x47beac */
	m->ecx = m->edx;	/* 47be0e: mov ecx, edx */
	m->eax = M32((DWORD)(m->ecx + 0x86ccu));	/* 47be10: mov eax, dword ptr [ecx + 0x86cc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47be16: test eax, eax */
	if (!m->zf) goto L_47beac;	/* 47be18: jne 0x47beac */
	m->edx = (DWORD)(m->esp + 0x58u);	/* 47be1e: lea edx, [esp + 0x58] */
	m->eax = (DWORD)(m->esp + 0x160u);	/* 47be22: lea eax, [esp + 0x160] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47be29: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47be2a: push eax */
	m->eax = m->ecx;	/* 47be2b: mov eax, ecx */
	m->ecx = M32((DWORD)(m->esp + 0x40u));	/* 47be2d: mov ecx, dword ptr [esp + 0x40] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47be31: push ecx */
	m->edx = (DWORD)(m->esp + 0x160u);	/* 47be32: lea edx, [esp + 0x160] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x268u)));	/* 47be39: fld dword ptr [eax + 0x268] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x2df0u));	/* 47be3f: fadd dword ptr [ecx + 0x2df0] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47be45: fstp dword ptr [esp] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47be48: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47be49: push edx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 47be4a: push ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 47be4b: push edi */
	m->esp -= 4; M32(m->esp) = 0x47be51u; native_call(m, 0x47d9d0u);	/* 47be4c: call 0x47d9d0 */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47be51: add esp, 0x1c */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47be54: cmp eax, 1 */
	if (!m->zf) goto L_47beac;	/* 47be57: jne 0x47beac */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x58u)));	/* 47be59: fld dword ptr [esp + 0x58] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x28u)); FPOP();	/* 47be5d: fcomp dword ptr [esp + 0x28] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47be61: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47be63: test ah, 1 */
	if (m->zf) goto L_47beac;	/* 47be66: je 0x47beac */
	m->eax = M32((DWORD)(m->esp + 0x3cu));	/* 47be68: mov eax, dword ptr [esp + 0x3c] */
	m->ecx = M32((DWORD)(m->esp + 0x164u));	/* 47be6c: mov ecx, dword ptr [esp + 0x164] */
	M32((DWORD)(m->esi + 0xb8u)) = m->eax;	/* 47be73: mov dword ptr [esi + 0xb8], eax */
	m->eax = M32((DWORD)(m->esp + 0x160u));	/* 47be79: mov eax, dword ptr [esp + 0x160] */
	m->edx = m->ebx;	/* 47be80: mov edx, ebx */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 47be82: mov dword ptr [edx], eax */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 47be84: mov dword ptr [edx + 4], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x168u));	/* 47be87: mov ecx, dword ptr [esp + 0x168] */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 47be8e: mov dword ptr [edx + 8], ecx */
	m->edx = (DWORD)(m->esi + 0x60u);	/* 47be91: lea edx, [esi + 0x60] */
	M32((DWORD)(m->esi + 0x60u)) = m->eax;	/* 47be94: mov dword ptr [esi + 0x60], eax */
	m->eax = M32((DWORD)(m->esp + 0x164u));	/* 47be97: mov eax, dword ptr [esp + 0x164] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 47be9e: mov dword ptr [edx + 4], eax */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 47bea1: mov dword ptr [edx + 8], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x58u));	/* 47bea4: mov ecx, dword ptr [esp + 0x58] */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 47bea8: mov dword ptr [esp + 0x28], ecx */
L_47beac:
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 47beac: mov edx, dword ptr [esp + 0x24] */
	m->eax = M32((DWORD)(m->esp + 0x3cu));	/* 47beb0: mov eax, dword ptr [esp + 0x3c] */
	{ DWORD a_ = m->edx, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 47beb4: add edx, 0x8888 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 47beba: inc eax */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 47bebb: mov dword ptr [esp + 0x24], edx */
	m->edx = M32((DWORD)(m->esp + 0x40u));	/* 47bebf: mov edx, dword ptr [esp + 0x40] */
	M32((DWORD)(m->esp + 0x3cu)) = m->eax;	/* 47bec3: mov dword ptr [esp + 0x3c], eax */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->edx + 0x202e8c8u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47bec7: cmp eax, dword ptr [edx + 0x202e8c8] */
	if (m->sf != m->of) goto L_47bddb;	/* 47becd: jl 0x47bddb */
L_47bed3:
	m->ecx = M32((DWORD)(m->esi + 0xb8u));	/* 47bed3: mov ecx, dword ptr [esi + 0xb8] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47bed9: test ecx, ecx */
	if (m->sf != m->of) goto L_47beea;	/* 47bedb: jl 0x47beea */
	m->eax = M32((DWORD)(m->esi + 0x70u));	/* 47bedd: mov eax, dword ptr [esi + 0x70] */
	M32((DWORD)(m->esi + 0x6cu)) = 0x0u;	/* 47bee0: mov dword ptr [esi + 0x6c], 0 */
	M32((DWORD)(m->esi + 0x74u)) = m->eax;	/* 47bee7: mov dword ptr [esi + 0x74], eax */
L_47beea:
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 47beea: mov edx, dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x2e0cu)));	/* 47beee: fld dword ptr [edx + 0x2e0c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47bef4: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47befa: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47befc: test ah, 0x41 */
	if (!m->zf) goto L_47bfe5;	/* 47beff: jne 0x47bfe5 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47bf05: test ecx, ecx */
	if (m->sf == m->of) goto L_47bfe5;	/* 47bf07: jge 0x47bfe5 */
	m->ecx = M32((DWORD)(m->esp + 0x40u));	/* 47bf0d: mov ecx, dword ptr [esp + 0x40] */
	m->eax = (DWORD)(m->esp + 0xd8u);	/* 47bf11: lea eax, [esp + 0xd8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47bf18: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 47bf19: push ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 47bf1a: push edi */
	m->esp -= 4; M32(m->esp) = 0x47bf20u; native_call(m, 0x471740u);	/* 47bf1b: call 0x471740 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47bf20: test eax, eax */
	M32((DWORD)(m->esi + 0x6cu)) = m->eax;	/* 47bf22: mov dword ptr [esi + 0x6c], eax */
	if (m->zf) goto L_47bfe5;	/* 47bf25: je 0x47bfe5 */
	m->edx = M32((DWORD)(m->esp + 0xd8u));	/* 47bf2b: mov edx, dword ptr [esp + 0xd8] */
	m->eax = M32((DWORD)(m->esp + 0xdcu));	/* 47bf32: mov eax, dword ptr [esp + 0xdc] */
	m->ecx = (DWORD)(m->esi + 0x60u);	/* 47bf39: lea ecx, [esi + 0x60] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xd8u)));	/* 47bf3c: fld dword ptr [esp + 0xd8] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 47bf43: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->esp + 0xe0u));	/* 47bf45: mov edx, dword ptr [esp + 0xe0] */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 47bf4c: mov dword ptr [ecx + 4], eax */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 47bf4f: mov dword ptr [ecx + 8], edx */
	m->edx = M32((DWORD)(m->esi + 0xa0u));	/* 47bf52: mov edx, dword ptr [esi + 0xa0] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 47bf58: fsub dword ptr [edi] */
	m->ecx = M32((DWORD)(m->esi + 0xa4u));	/* 47bf5a: mov ecx, dword ptr [esi + 0xa4] */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 47bf60: mov dword ptr [esp + 0x28], edx */
	m->eax = M32((DWORD)(m->esi + 0xa8u));	/* 47bf64: mov eax, dword ptr [esi + 0xa8] */
	M32((DWORD)(m->esp + 0x44u)) = m->ecx;	/* 47bf6a: mov dword ptr [esp + 0x44], ecx */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 47bf6e: mov dword ptr [esp + 0x24], eax */
	MF((DWORD)(m->esp + 0xd8u)) = (float)ST(0); FPOP();	/* 47bf72: fstp dword ptr [esp + 0xd8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xdcu)));	/* 47bf79: fld dword ptr [esp + 0xdc] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47bf80: fsub dword ptr [edi + 4] */
	MF((DWORD)(m->esp + 0xdcu)) = (float)ST(0);	/* 47bf83: fst dword ptr [esp + 0xdc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xe0u)));	/* 47bf8a: fld dword ptr [esp + 0xe0] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47bf91: fsub dword ptr [edi + 8] */
	MF((DWORD)(m->esp + 0xe0u)) = (float)ST(0);	/* 47bf94: fst dword ptr [esp + 0xe0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xd8u)));	/* 47bf9b: fld dword ptr [esp + 0xd8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xd8u));	/* 47bfa2: fmul dword ptr [esp + 0xd8] */
	{ long double t = ST(1); FPUSH(t); }	/* 47bfa9: fld st(1) */
	ST(0) = ST(0) * ST(2);	/* 47bfab: fmul st(2) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47bfad: faddp st(1) */
	{ long double t = ST(2); FPUSH(t); }	/* 47bfaf: fld st(2) */
	ST(0) = ST(0) * ST(3);	/* 47bfb1: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47bfb3: faddp st(1) */
	{ long double t = ST(0); __asm__("fsqrt" : "+t"(t)); ST(0) = t; }	/* 47bfb5: fsqrt  */
	ST(2) = ST(0); FPOP();	/* 47bfb7: fstp st(2) */
	ST(0) = ST(0); FPOP();	/* 47bfb9: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 47bfbb: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 47bfbf: fmul dword ptr [esp + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 47bfc3: fld dword ptr [esp + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 47bfc7: fmul dword ptr [esp + 0x44] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47bfcb: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 47bfcd: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47bfd1: fmul dword ptr [esp + 0x24] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47bfd5: faddp st(1) */
	{ long double t = ST(0); __asm__("fsqrt" : "+t"(t)); ST(0) = t; }	/* 47bfd7: fsqrt  */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 47bfd9: fxch st(1) */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 47bfdb: fxch st(1) */
	ST(1) = ST(1) / ST(0); FPOP();	/* 47bfdd: fdivp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x70u));	/* 47bfdf: fadd dword ptr [esi + 0x70] */
	MF((DWORD)(m->esi + 0x74u)) = (float)ST(0); FPOP();	/* 47bfe2: fstp dword ptr [esi + 0x74] */
L_47bfe5:
	M32((DWORD)(m->esi + 0x9cu)) = 0x1u;	/* 47bfe5: mov dword ptr [esi + 0x9c], 1 */
	goto L_47c092;	/* 47bfef: jmp 0x47c092 */
L_47bff4:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x9cu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47bff4: cmp dword ptr [esi + 0x9c], 1 */
	if (!m->zf) goto L_47c056;	/* 47bffb: jne 0x47c056 */
	m->eax = (DWORD)(m->esi + 0x90u);	/* 47bffd: lea eax, [esi + 0x90] */
	m->ecx = m->ebx;	/* 47c003: mov ecx, ebx */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 47c005: mov edx, dword ptr [eax] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 47c007: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47c009: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 47c00c: mov dword ptr [ecx + 4], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47c00f: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 47c012: mov dword ptr [ecx + 8], eax */
	m->ecx = (DWORD)(m->esi + 0xacu);	/* 47c015: lea ecx, [esi + 0xac] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 47c01b: fld dword ptr [ebx] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 47c01d: fsub dword ptr [edi] */
	m->edx = m->ecx;	/* 47c01f: mov edx, ecx */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47c021: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x4u)));	/* 47c025: fld dword ptr [ebx + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47c028: fsub dword ptr [edi + 4] */
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 47c02b: mov eax, dword ptr [esp + 0xc] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47c02f: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x8u)));	/* 47c033: fld dword ptr [ebx + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47c036: fsub dword ptr [edi + 8] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 47c039: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 47c03b: mov eax, dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 47c03f: fstp dword ptr [esp + 0x14] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 47c043: mov dword ptr [edx + 4], eax */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 47c046: mov eax, dword ptr [esp + 0x14] */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 47c04a: mov dword ptr [edx + 8], eax */
	m->esp -= 4; M32(m->esp) = 0x47c052u; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 47c04d: call 0x467760 */
	ST(0) = ST(0); FPOP();	/* 47c052: fstp st(0) */
	goto L_47c092;	/* 47c054: jmp 0x47c092 */
L_47c056:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0xacu)));	/* 47c056: fld dword ptr [esi + 0xac] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 47c05c: fadd dword ptr [edi] */
	m->ecx = m->ebx;	/* 47c05e: mov ecx, ebx */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47c060: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0xb0u)));	/* 47c064: fld dword ptr [esi + 0xb0] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47c06a: fadd dword ptr [edi + 4] */
	m->edx = M32((DWORD)(m->esp + 0xcu));	/* 47c06d: mov edx, dword ptr [esp + 0xc] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47c071: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0xb4u)));	/* 47c075: fld dword ptr [esi + 0xb4] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47c07b: fadd dword ptr [edi + 8] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 47c07e: mov eax, dword ptr [esp + 0x10] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 47c082: mov dword ptr [ecx], edx */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 47c084: fstp dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 47c088: mov edx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 47c08c: mov dword ptr [ecx + 4], eax */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 47c08f: mov dword ptr [ecx + 8], edx */
L_47c092:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x9cu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47c092: cmp dword ptr [esi + 0x9c], 1 */
	if (!m->zf) goto L_47ca23;	/* 47c099: jne 0x47ca23 */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 47c09f: mov eax, dword ptr [esp + 0x38] */
	m->ecx = M32((DWORD)(m->eax + 0x2dfcu));	/* 47c0a3: mov ecx, dword ptr [eax + 0x2dfc] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47c0a9: cmp ecx, 3 */
	if (m->zf) goto L_47c701;	/* 47c0ac: je 0x47c701 */
	{ DWORD a_ = m->ecx, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47c0b2: cmp ecx, 7 */
	if (m->zf) goto L_47c155;	/* 47c0b5: je 0x47c155 */
	m->eax = M32((DWORD)(m->esp + 0x40u));	/* 47c0bb: mov eax, dword ptr [esp + 0x40] */
	m->edx = M32((DWORD)(m->esi + 0xcu));	/* 47c0bf: mov edx, dword ptr [esi + 0xc] */
	{ DWORD a_ = m->edx, b_ = M32((DWORD)(m->eax + 0x202e8d8u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47c0c2: cmp edx, dword ptr [eax + 0x202e8d8] */
	if (!m->zf) goto L_47c0e1;	/* 47c0c8: jne 0x47c0e1 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x70u)));	/* 47c0ca: fld dword ptr [esi + 0x70] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9568u)); FPOP();	/* 47c0cd: fcomp dword ptr [0x4a9568] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47c0d3: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47c0d5: test ah, 1 */
	if (m->zf) goto L_47c0e1;	/* 47c0d8: je 0x47c0e1 */
	m->eax = 0x1u;	/* 47c0da: mov eax, 1 */
	goto L_47c0e3;	/* 47c0df: jmp 0x47c0e3 */
L_47c0e1:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47c0e1: xor eax, eax */
L_47c0e3:
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 47c0e3: mov edx, dword ptr [esp + 0x38] */
	{ DWORD a_ = m->ecx, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 47c0e7: add ecx, 0x14 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x2df0u)));	/* 47c0ea: fld dword ptr [edx + 0x2df0] */
	M32((DWORD)(m->esp + 0x60u)) = m->eax;	/* 47c0f0: mov dword ptr [esp + 0x60], eax */
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 47c0f4: mov eax, dword ptr [edi] */
	m->edx = M32((DWORD)(m->edi + 0x8u));	/* 47c0f6: mov edx, dword ptr [edi + 8] */
	M32((DWORD)(m->esp + 0x64u)) = m->eax;	/* 47c0f9: mov dword ptr [esp + 0x64], eax */
	m->eax = M32((DWORD)(m->ebx + 0x0u));	/* 47c0fd: mov eax, dword ptr [ebx] */
	M32((DWORD)(m->esp + 0x5cu)) = m->ecx;	/* 47c0ff: mov dword ptr [esp + 0x5c], ecx */
	m->ecx = M32((DWORD)(m->edi + 0x4u));	/* 47c103: mov ecx, dword ptr [edi + 4] */
	M32((DWORD)(m->esp + 0x70u)) = m->eax;	/* 47c106: mov dword ptr [esp + 0x70], eax */
	MF((DWORD)(m->esp + 0x88u)) = (float)ST(0); FPOP();	/* 47c10a: fstp dword ptr [esp + 0x88] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47c111: xor eax, eax */
	M32((DWORD)(m->esp + 0x68u)) = m->ecx;	/* 47c113: mov dword ptr [esp + 0x68], ecx */
	m->ecx = M32((DWORD)(m->ebx + 0x4u));	/* 47c117: mov ecx, dword ptr [ebx + 4] */
	M32((DWORD)(m->esp + 0x7cu)) = m->eax;	/* 47c11a: mov dword ptr [esp + 0x7c], eax */
	M32((DWORD)(m->esp + 0x80u)) = m->eax;	/* 47c11e: mov dword ptr [esp + 0x80], eax */
	M32((DWORD)(m->esp + 0x84u)) = m->eax;	/* 47c125: mov dword ptr [esp + 0x84], eax */
	M32((DWORD)(m->esp + 0x8cu)) = m->eax;	/* 47c12c: mov dword ptr [esp + 0x8c], eax */
	M32((DWORD)(m->esp + 0x6cu)) = m->edx;	/* 47c133: mov dword ptr [esp + 0x6c], edx */
	m->edx = M32((DWORD)(m->ebx + 0x8u));	/* 47c137: mov edx, dword ptr [ebx + 8] */
	m->eax = (DWORD)(m->esp + 0x5cu);	/* 47c13a: lea eax, [esp + 0x5c] */
	M32((DWORD)(m->esp + 0x74u)) = m->ecx;	/* 47c13e: mov dword ptr [esp + 0x74], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x40u));	/* 47c142: mov ecx, dword ptr [esp + 0x40] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47c146: push eax */
	M32((DWORD)(m->esp + 0x7cu)) = m->edx;	/* 47c147: mov dword ptr [esp + 0x7c], edx */
	m->esp -= 4; M32(m->esp) = 0x47c150u; native_call(m, 0x479950u);	/* 47c14b: call 0x479950 */
	goto L_47ca23;	/* 47c150: jmp 0x47ca23 */
L_47c155:
	m->esp -= 4; M32(m->esp) = 0x47c15bu; native_call(m, M32(0x4a9204u));	/* 47c155: call dword ptr [0x4a9204] */
	m->esp -= 4; M32(m->esp) = 0x47c161u; native_call(m, M32(0x4a9218u));	/* 47c15b: call dword ptr [0x4a9218] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8cu)));	/* 47c161: fld dword ptr [esi + 0x8c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47c167: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47c169: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 47c16b: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47c170: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47c172: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47c174: push 0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47c176: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47c179: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x88u)));	/* 47c17c: fld dword ptr [esi + 0x88] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47c182: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47c185: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 47c188: fld dword ptr [ebx] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47c18a: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47c18d: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 47c190: fld dword ptr [esi + 0x80] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47c196: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47c199: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x7cu)));	/* 47c19c: fld dword ptr [esi + 0x7c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47c19f: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47c1a2: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x0u)));	/* 47c1a5: fld dword ptr [edi] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47c1a7: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47c1aa: fstp qword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47c1b2u; native_call(m, 0x4509d2u);	/* 47c1ad: call 0x4509d2 */
	m->ecx = (DWORD)(m->esp + 0x1acu);	/* 47c1b2: lea ecx, [esp + 0x1ac] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47c1b9: push ecx */
	{ DWORD v_ = 0xba6u; m->esp -= 4; M32(m->esp) = v_; }	/* 47c1ba: push 0xba6 */
	m->esp -= 4; M32(m->esp) = 0x47c1c5u; native_call(m, M32(0x4a9270u));	/* 47c1bf: call dword ptr [0x4a9270] */
	m->edx = (DWORD)(m->esp + 0x1acu);	/* 47c1c5: lea edx, [esp + 0x1ac] */
	m->eax = (DWORD)(m->esp + 0xe4u);	/* 47c1cc: lea eax, [esp + 0xe4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47c1d3: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47c1d4: push eax */
	m->esp -= 4; M32(m->esp) = 0x47c1dau; native_call(m, 0x47d740u);	/* 47c1d5: call 0x47d740 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47c1da: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x47c1e3u; native_call(m, M32(0x4a9258u));	/* 47c1dd: call dword ptr [0x4a9258] */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 47c1e3: mov ecx, dword ptr [esp + 0x38] */
	M32((DWORD)(m->esp + 0x44u)) = 0x0u;	/* 47c1e7: mov dword ptr [esp + 0x44], 0 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x0u;	/* 47c1ef: mov dword ptr [esp + 0x3c], 0 */
	M32((DWORD)(m->esp + 0x28u)) = 0x0u;	/* 47c1f7: mov dword ptr [esp + 0x28], 0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x2df0u)));	/* 47c1ff: fld dword ptr [ecx + 0x2df0] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47c205: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93e8u)));	/* 47c209: fld dword ptr [0x4a93e8] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93e8u)));	/* 47c20f: fld dword ptr [0x4a93e8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 47c215: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xf4u));	/* 47c219: fmul dword ptr [esp + 0xf4] */
	M32((DWORD)(m->esp + 0x24u)) = 0x0u;	/* 47c220: mov dword ptr [esp + 0x24], 0 */
	m->ecx = (DWORD)(m->esi + 0xd4u);	/* 47c228: lea ecx, [esi + 0xd4] */
	m->edx = m->ecx;	/* 47c22e: mov edx, ecx */
	ST(0) = ST(0) + ST(1);	/* 47c230: fadd st(1) */
	ST(0) = ST(0) + ST(2);	/* 47c232: fadd st(2) */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 47c234: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xf8u)));	/* 47c238: fld dword ptr [esp + 0xf8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 47c23f: fmul dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 47c243: fadd dword ptr [esp + 0x44] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 47c247: fadd dword ptr [esp + 0x3c] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 47c24b: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xfcu)));	/* 47c24f: fld dword ptr [esp + 0xfc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 47c256: fmul dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 47c25a: fadd dword ptr [esp + 0x28] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47c25e: fadd dword ptr [esp + 0x24] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 47c262: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47c266: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 47c26a: fadd dword ptr [edi] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 47c26c: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47c270: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47c274: fadd dword ptr [edi + 4] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 47c277: mov eax, dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 47c27b: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47c27f: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47c283: fadd dword ptr [edi + 8] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 47c286: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 47c288: mov eax, dword ptr [esp + 0x30] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 47c28c: fstp dword ptr [esp + 0x34] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 47c290: mov dword ptr [edx + 4], eax */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 47c293: mov eax, dword ptr [esp + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47c297: fld dword ptr [esp + 0x18] */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 47c29b: mov dword ptr [edx + 8], eax */
	m->edx = (DWORD)(m->esi + 0x104u);	/* 47c29e: lea edx, [esi + 0x104] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x0u));	/* 47c2a4: fadd dword ptr [ebx] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 47c2a6: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47c2aa: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x4u));	/* 47c2ae: fadd dword ptr [ebx + 4] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 47c2b1: mov eax, dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 47c2b5: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47c2b9: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x8u));	/* 47c2bd: fadd dword ptr [ebx + 8] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 47c2c0: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 47c2c2: mov eax, dword ptr [esp + 0x30] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 47c2c6: fstp dword ptr [esp + 0x34] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 47c2ca: mov dword ptr [edx + 4], eax */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 47c2cd: mov eax, dword ptr [esp + 0x34] */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 47c2d1: mov dword ptr [edx + 8], eax */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 47c2d4: mov edx, dword ptr [esp + 0x38] */
	m->eax = (DWORD)(m->esi + 0xe0u);	/* 47c2d8: lea eax, [esi + 0xe0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x2df0u)));	/* 47c2de: fld dword ptr [edx + 0x2df0] */
	ST(0) = -ST(0);	/* 47c2e4: fchs  */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0);	/* 47c2e6: fst dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xf4u));	/* 47c2ea: fmul dword ptr [esp + 0xf4] */
	ST(0) = ST(0) + ST(1);	/* 47c2f1: fadd st(1) */
	ST(0) = ST(0) + ST(2);	/* 47c2f3: fadd st(2) */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 47c2f5: fstp dword ptr [esp + 0x18] */
	ST(0) = ST(0); FPOP();	/* 47c2f9: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xf8u)));	/* 47c2fb: fld dword ptr [esp + 0xf8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 47c302: fmul dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 47c306: fadd dword ptr [esp + 0x44] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 47c30a: fadd dword ptr [esp + 0x3c] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 47c30e: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xfcu)));	/* 47c312: fld dword ptr [esp + 0xfc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 47c319: fmul dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 47c31d: fadd dword ptr [esp + 0x28] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47c321: fadd dword ptr [esp + 0x24] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 47c325: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47c329: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 47c32d: fadd dword ptr [edi] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 47c32f: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47c333: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47c337: fadd dword ptr [edi + 4] */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 47c33a: mov edx, dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 47c33e: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47c342: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47c346: fadd dword ptr [edi + 8] */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 47c349: mov dword ptr [eax], edx */
	m->edx = M32((DWORD)(m->esp + 0x30u));	/* 47c34b: mov edx, dword ptr [esp + 0x30] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 47c34f: fstp dword ptr [esp + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47c353: fld dword ptr [esp + 0x18] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 47c357: mov dword ptr [eax + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 47c35a: mov edx, dword ptr [esp + 0x34] */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 47c35e: mov dword ptr [eax + 8], edx */
	m->eax = (DWORD)(m->esi + 0x110u);	/* 47c361: lea eax, [esi + 0x110] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x0u));	/* 47c367: fadd dword ptr [ebx] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 47c369: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47c36d: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x4u));	/* 47c371: fadd dword ptr [ebx + 4] */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 47c374: mov edx, dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 47c378: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47c37c: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x8u));	/* 47c380: fadd dword ptr [ebx + 8] */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 47c383: mov dword ptr [eax], edx */
	m->edx = M32((DWORD)(m->esp + 0x30u));	/* 47c385: mov edx, dword ptr [esp + 0x30] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 47c389: fstp dword ptr [esp + 0x34] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 47c38d: mov dword ptr [eax + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 47c390: mov edx, dword ptr [esp + 0x34] */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 47c394: mov dword ptr [eax + 8], edx */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 47c397: mov eax, dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x2df0u)));	/* 47c39b: fld dword ptr [eax + 0x2df0] */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47c3a1: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xe4u)));	/* 47c3a5: fld dword ptr [esp + 0xe4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xcu));	/* 47c3ac: fmul dword ptr [esp + 0xc] */
	m->edx = M32((DWORD)(m->esp + 0x3cu));	/* 47c3b0: mov edx, dword ptr [esp + 0x3c] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 47c3b4: mov eax, dword ptr [esp + 0x24] */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 47c3b8: mov dword ptr [esp + 0x28], edx */
	M32((DWORD)(m->esp + 0x44u)) = m->eax;	/* 47c3bc: mov dword ptr [esp + 0x44], eax */
	ST(0) = ST(0) + ST(1);	/* 47c3c0: fadd st(1) */
	m->edx = (DWORD)(m->esi + 0xecu);	/* 47c3c2: lea edx, [esi + 0xec] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 47c3c8: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xcu)));	/* 47c3cc: fld dword ptr [esp + 0xc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xe8u));	/* 47c3d0: fmul dword ptr [esp + 0xe8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 47c3d7: fadd dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 47c3db: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xcu)));	/* 47c3df: fld dword ptr [esp + 0xc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xecu));	/* 47c3e3: fmul dword ptr [esp + 0xec] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 47c3ea: fadd dword ptr [esp + 0x44] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 47c3ee: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47c3f2: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 47c3f6: fadd dword ptr [edi] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 47c3f8: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47c3fc: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47c400: fadd dword ptr [edi + 4] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 47c403: mov eax, dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 47c407: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47c40b: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47c40f: fadd dword ptr [edi + 8] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 47c412: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 47c414: mov eax, dword ptr [esp + 0x30] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 47c418: fstp dword ptr [esp + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47c41c: fld dword ptr [esp + 0x18] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 47c420: mov dword ptr [edx + 4], eax */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 47c423: mov eax, dword ptr [esp + 0x34] */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 47c427: mov dword ptr [edx + 8], eax */
	m->edx = (DWORD)(m->esi + 0x11cu);	/* 47c42a: lea edx, [esi + 0x11c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x0u));	/* 47c430: fadd dword ptr [ebx] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 47c432: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47c436: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x4u));	/* 47c43a: fadd dword ptr [ebx + 4] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 47c43d: mov eax, dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 47c441: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47c445: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x8u));	/* 47c449: fadd dword ptr [ebx + 8] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 47c44c: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 47c44e: mov eax, dword ptr [esp + 0x30] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 47c452: fstp dword ptr [esp + 0x34] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 47c456: mov dword ptr [edx + 4], eax */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 47c459: mov eax, dword ptr [esp + 0x34] */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 47c45d: mov dword ptr [edx + 8], eax */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 47c460: mov edx, dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x2df0u)));	/* 47c464: fld dword ptr [edx + 0x2df0] */
	ST(0) = -ST(0);	/* 47c46a: fchs  */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47c46c: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xe4u)));	/* 47c470: fld dword ptr [esp + 0xe4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xcu));	/* 47c477: fmul dword ptr [esp + 0xc] */
	ST(0) = ST(0) + ST(1);	/* 47c47b: fadd st(1) */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 47c47d: fstp dword ptr [esp + 0x18] */
	ST(0) = ST(0); FPOP();	/* 47c481: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xcu)));	/* 47c483: fld dword ptr [esp + 0xc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xe8u));	/* 47c487: fmul dword ptr [esp + 0xe8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 47c48e: fadd dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 47c492: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xcu)));	/* 47c496: fld dword ptr [esp + 0xc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xecu));	/* 47c49a: fmul dword ptr [esp + 0xec] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 47c4a1: fadd dword ptr [esp + 0x44] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 47c4a5: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47c4a9: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 47c4ad: fadd dword ptr [edi] */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47c4af: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47c4b3: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47c4b7: fadd dword ptr [edi + 4] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47c4ba: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47c4be: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47c4c2: fadd dword ptr [edi + 8] */
	m->edx = M32((DWORD)(m->esp + 0xcu));	/* 47c4c5: mov edx, dword ptr [esp + 0xc] */
	m->eax = (DWORD)(m->esi + 0xf8u);	/* 47c4c9: lea eax, [esi + 0xf8] */
	M32((DWORD)(m->esp + 0x2cu)) = 0x0u;	/* 47c4cf: mov dword ptr [esp + 0x2c], 0 */
	M32((DWORD)(m->esp + 0x24u)) = 0x0u;	/* 47c4d7: mov dword ptr [esp + 0x24], 0 */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 47c4df: mov dword ptr [eax], edx */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 47c4e1: mov edx, dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 47c4e5: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47c4e9: fld dword ptr [esp + 0x18] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 47c4ed: mov dword ptr [eax + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 47c4f0: mov edx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 47c4f4: mov dword ptr [esp + 0x28], ecx */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 47c4f8: mov dword ptr [eax + 8], edx */
	m->eax = (DWORD)(m->esi + 0x128u);	/* 47c4fb: lea eax, [esi + 0x128] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x0u));	/* 47c501: fadd dword ptr [ebx] */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47c503: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47c507: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x4u));	/* 47c50b: fadd dword ptr [ebx + 4] */
	m->edx = M32((DWORD)(m->esp + 0xcu));	/* 47c50e: mov edx, dword ptr [esp + 0xc] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47c512: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47c516: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x8u));	/* 47c51a: fadd dword ptr [ebx + 8] */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 47c51d: mov dword ptr [eax], edx */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 47c51f: mov edx, dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 47c523: fstp dword ptr [esp + 0x14] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 47c527: mov dword ptr [eax + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 47c52a: mov edx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 47c52e: mov dword ptr [eax + 8], edx */
	m->eax = M32((DWORD)(m->esp + 0x40u));	/* 47c531: mov eax, dword ptr [esp + 0x40] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 47c535: fld dword ptr [ebx] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 47c537: fsub dword ptr [edi] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x4u)));	/* 47c539: fld dword ptr [ebx + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47c53c: fsub dword ptr [edi + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x8u)));	/* 47c53f: fld dword ptr [ebx + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47c542: fsub dword ptr [edi + 8] */
	{ long double t = ST(2); FPUSH(t); }	/* 47c545: fld st(2) */
	ST(3) = ST(3) * ST(0); FPOP();	/* 47c547: fmulp st(3) */
	{ long double t = ST(0); FPUSH(t); }	/* 47c549: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 47c54b: fmul st(1) */
	ST(3) = ST(3) + ST(0); FPOP();	/* 47c54d: faddp st(3) */
	{ long double t = ST(1); FPUSH(t); }	/* 47c54f: fld st(1) */
	ST(0) = ST(0) * ST(2);	/* 47c551: fmul st(2) */
	ST(3) = ST(3) + ST(0); FPOP();	/* 47c553: faddp st(3) */
	{ long double t = ST(0); ST(0) = ST(2); ST(2) = t; }	/* 47c555: fxch st(2) */
	{ long double t = ST(0); __asm__("fsqrt" : "+t"(t)); ST(0) = t; }	/* 47c557: fsqrt  */
	{ long double t = ST(0); ST(0) = ST(2); ST(2) = t; }	/* 47c559: fxch st(2) */
	ST(0) = ST(0); FPOP();	/* 47c55b: fstp st(0) */
	ST(0) = ST(0); FPOP();	/* 47c55d: fstp st(0) */
	MF((DWORD)(m->esi + 0x494u)) = (float)ST(0);	/* 47c55f: fst dword ptr [esi + 0x494] */
	m->edx = M32((DWORD)(m->eax + 0x9ccfe4u));	/* 47c565: mov edx, dword ptr [eax + 0x9ccfe4] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((0xffu) & 0xff) << 0);	/* 47c56b: mov al, 0xff */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa450u));	/* 47c56d: fmul dword ptr [0x4aa450] */
	M32((DWORD)(m->esp + 0x44u)) = m->edx;	/* 47c573: mov dword ptr [esp + 0x44], edx */
	M8((DWORD)(m->esp + 0x3cu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 47c577: mov byte ptr [esp + 0x3c], al */
	M8((DWORD)(m->esp + 0x3du)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 47c57b: mov byte ptr [esp + 0x3d], al */
	M8((DWORD)(m->esp + 0x3eu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 47c57f: mov byte ptr [esp + 0x3e], al */
	M8((DWORD)(m->esp + 0x3fu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 47c583: mov byte ptr [esp + 0x3f], al */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47c587: fstp dword ptr [esp + 0xc] */
L_47c58b:
	{ DWORD a_ = M8((DWORD)(m->esp + 0x24u)), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47c58b: test byte ptr [esp + 0x24], 1 */
	if (m->zf) goto L_47c5c5;	/* 47c590: je 0x47c5c5 */
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 47c592: mov eax, dword ptr [esi] */
	{ DWORD a_ = m->eax, b_ = 0x80000003u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47c594: and eax, 0x80000003 */
	if (!m->sf) goto L_47c5a0;	/* 47c599: jns 0x47c5a0 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 47c59b: dec eax */
	{ DWORD a_ = m->eax, b_ = 0xfffffffcu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47c59c: or eax, 0xfffffffc */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 47c59f: inc eax */
L_47c5a0:
	{ DWORD a_ = m->eax, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 47c5a0: shl eax, 5 */
	M32((DWORD)(m->esp + 0x54u)) = m->eax;	/* 47c5a3: mov dword ptr [esp + 0x54], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x54u)));	/* 47c5a7: fild dword ptr [esp + 0x54] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 47c5ab: fmul dword ptr [0x4a957c] */
	{ long double t = ST(0); FPUSH(t); }	/* 47c5b1: fld st(0) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a958cu));	/* 47c5b3: fadd dword ptr [0x4a958c] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47c5b9: fstp dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 47c5bd: fadd dword ptr [0x4a9420] */
	goto L_47c5f8;	/* 47c5c3: jmp 0x47c5f8 */
L_47c5c5:
	m->ecx = M32((DWORD)(m->esi + 0x0u));	/* 47c5c5: mov ecx, dword ptr [esi] */
	{ DWORD a_ = m->ecx, b_ = 0x80000003u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 47c5c7: and ecx, 0x80000003 */
	if (!m->sf) goto L_47c5d4;	/* 47c5cd: jns 0x47c5d4 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 47c5cf: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffffcu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 47c5d0: or ecx, 0xfffffffc */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 47c5d3: inc ecx */
L_47c5d4:
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 47c5d4: inc ecx */
	{ DWORD a_ = m->ecx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 47c5d5: shl ecx, 5 */
	M32((DWORD)(m->esp + 0x54u)) = m->ecx;	/* 47c5d8: mov dword ptr [esp + 0x54], ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x54u)));	/* 47c5dc: fild dword ptr [esp + 0x54] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 47c5e0: fmul dword ptr [0x4a957c] */
	{ long double t = ST(0); FPUSH(t); }	/* 47c5e6: fld st(0) */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a958cu));	/* 47c5e8: fsub dword ptr [0x4a958c] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47c5ee: fstp dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 47c5f2: fsub dword ptr [0x4a9420] */
L_47c5f8:
	m->edx = M32((DWORD)(m->esp + 0x44u));	/* 47c5f8: mov edx, dword ptr [esp + 0x44] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 47c5fc: mov eax, dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 47c600: fstp dword ptr [esp + 0x30] */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 47c604: mov ecx, dword ptr [esp + 0x30] */
	M32((DWORD)(m->esp + 0x90u)) = m->edx;	/* 47c608: mov dword ptr [esp + 0x90], edx */
	m->edx = M32((DWORD)(m->esp + 0xcu));	/* 47c60f: mov edx, dword ptr [esp + 0xc] */
	M32((DWORD)(m->esp + 0x94u)) = m->eax;	/* 47c613: mov dword ptr [esp + 0x94], eax */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 47c61a: mov eax, dword ptr [esp + 0x10] */
	M32((DWORD)(m->esp + 0x9cu)) = m->edx;	/* 47c61e: mov dword ptr [esp + 0x9c], edx */
	m->edx = m->edi;	/* 47c625: mov edx, edi */
	M32((DWORD)(m->esp + 0x98u)) = m->ecx;	/* 47c627: mov dword ptr [esp + 0x98], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x3cu));	/* 47c62e: mov ecx, dword ptr [esp + 0x3c] */
	M32((DWORD)(m->esp + 0xa0u)) = m->eax;	/* 47c632: mov dword ptr [esp + 0xa0], eax */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 47c639: mov eax, dword ptr [edx] */
	M32((DWORD)(m->esp + 0xa4u)) = m->ecx;	/* 47c63b: mov dword ptr [esp + 0xa4], ecx */
	M32((DWORD)(m->esp + 0xa8u)) = m->eax;	/* 47c642: mov dword ptr [esp + 0xa8], eax */
	m->eax = m->ebx;	/* 47c649: mov eax, ebx */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 47c64b: mov ecx, dword ptr [edx + 4] */
	M32((DWORD)(m->esp + 0x5cu)) = 0xffffffffu;	/* 47c64e: mov dword ptr [esp + 0x5c], 0xffffffff */
	M32((DWORD)(m->esp + 0xacu)) = m->ecx;	/* 47c656: mov dword ptr [esp + 0xac], ecx */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47c65d: mov ecx, dword ptr [eax] */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 47c65f: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->esp + 0xb4u)) = m->ecx;	/* 47c662: mov dword ptr [esp + 0xb4], ecx */
	M32((DWORD)(m->esp + 0xb0u)) = m->edx;	/* 47c669: mov dword ptr [esp + 0xb0], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47c670: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0xb8u)) = m->edx;	/* 47c673: mov dword ptr [esp + 0xb8], edx */
	M32((DWORD)(m->esp + 0x8cu)) = 0x1u;	/* 47c67a: mov dword ptr [esp + 0x8c], 1 */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47c685: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0xbcu)) = m->eax;	/* 47c688: mov dword ptr [esp + 0xbc], eax */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 47c68f: mov eax, dword ptr [esp + 0x28] */
	m->ecx = (DWORD)(m->eax + 0x30u);	/* 47c693: lea ecx, [eax + 0x30] */
	m->edx = M32((DWORD)(m->eax + 0x30u));	/* 47c696: mov edx, dword ptr [eax + 0x30] */
	M32((DWORD)(m->esp + 0xc0u)) = m->edx;	/* 47c699: mov dword ptr [esp + 0xc0], edx */
	m->edx = M32((DWORD)(m->ecx + 0x4u));	/* 47c6a0: mov edx, dword ptr [ecx + 4] */
	M32((DWORD)(m->esp + 0xc4u)) = m->edx;	/* 47c6a3: mov dword ptr [esp + 0xc4], edx */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 47c6aa: mov edx, dword ptr [eax] */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 47c6ac: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->esp + 0xccu)) = m->edx;	/* 47c6af: mov dword ptr [esp + 0xcc], edx */
	M32((DWORD)(m->esp + 0xc8u)) = m->ecx;	/* 47c6b6: mov dword ptr [esp + 0xc8], ecx */
	m->ecx = M32((DWORD)(m->eax + 0x4u));	/* 47c6bd: mov ecx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0xd0u)) = m->ecx;	/* 47c6c0: mov dword ptr [esp + 0xd0], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x40u));	/* 47c6c7: mov ecx, dword ptr [esp + 0x40] */
	m->edx = M32((DWORD)(m->eax + 0x8u));	/* 47c6cb: mov edx, dword ptr [eax + 8] */
	m->eax = (DWORD)(m->esp + 0x5cu);	/* 47c6ce: lea eax, [esp + 0x5c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47c6d2: push eax */
	M32((DWORD)(m->esp + 0xd8u)) = m->edx;	/* 47c6d3: mov dword ptr [esp + 0xd8], edx */
	m->esp -= 4; M32(m->esp) = 0x47c6dfu; native_call(m, 0x479950u);	/* 47c6da: call 0x479950 */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 47c6df: mov eax, dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 47c6e3: mov edx, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 47c6e7: inc eax */
	{ DWORD a_ = m->edx, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 47c6e8: add edx, 0xc */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47c6eb: cmp eax, 4 */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 47c6ee: mov dword ptr [esp + 0x24], eax */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 47c6f2: mov dword ptr [esp + 0x28], edx */
	if (m->sf != m->of) goto L_47c58b;	/* 47c6f6: jl 0x47c58b */
	goto L_47ca23;	/* 47c6fc: jmp 0x47ca23 */
L_47c701:
	m->esp -= 4; M32(m->esp) = 0x47c707u; native_call(m, M32(0x4a9204u));	/* 47c701: call dword ptr [0x4a9204] */
	m->esp -= 4; M32(m->esp) = 0x47c70du; native_call(m, M32(0x4a9218u));	/* 47c707: call dword ptr [0x4a9218] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x0u)));	/* 47c70d: fld dword ptr [edi] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebx + 0x0u)); FPOP();	/* 47c70f: fcomp dword ptr [ebx] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47c711: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47c713: test ah, 0x40 */
	if (m->zf) goto L_47c73a;	/* 47c716: je 0x47c73a */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 47c718: fld dword ptr [esi + 0x80] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0x8cu)); FPOP();	/* 47c71e: fcomp dword ptr [esi + 0x8c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47c724: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47c726: test ah, 0x40 */
	if (m->zf) goto L_47c73a;	/* 47c729: je 0x47c73a */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47c72b: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47c72d: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47c72f: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47c731: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 47c733: push 0x3ff00000 */
	goto L_47c747;	/* 47c738: jmp 0x47c747 */
L_47c73a:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47c73a: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47c73c: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 47c73e: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47c743: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47c745: push 0 */
L_47c747:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8cu)));	/* 47c747: fld dword ptr [esi + 0x8c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47c74d: push 0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47c74f: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47c752: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x88u)));	/* 47c755: fld dword ptr [esi + 0x88] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47c75b: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47c75e: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 47c761: fld dword ptr [ebx] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47c763: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47c766: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 47c769: fld dword ptr [esi + 0x80] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47c76f: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47c772: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x7cu)));	/* 47c775: fld dword ptr [esi + 0x7c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47c778: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47c77b: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x0u)));	/* 47c77e: fld dword ptr [edi] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47c780: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47c783: fstp qword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47c78bu; native_call(m, 0x4509d2u);	/* 47c786: call 0x4509d2 */
	m->ecx = (DWORD)(m->esp + 0x1acu);	/* 47c78b: lea ecx, [esp + 0x1ac] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47c792: push ecx */
	{ DWORD v_ = 0xba6u; m->esp -= 4; M32(m->esp) = v_; }	/* 47c793: push 0xba6 */
	m->esp -= 4; M32(m->esp) = 0x47c79eu; native_call(m, M32(0x4a9270u));	/* 47c798: call dword ptr [0x4a9270] */
	m->edx = (DWORD)(m->esp + 0x1acu);	/* 47c79e: lea edx, [esp + 0x1ac] */
	m->eax = (DWORD)(m->esp + 0xe4u);	/* 47c7a5: lea eax, [esp + 0xe4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47c7ac: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47c7ad: push eax */
	m->esp -= 4; M32(m->esp) = 0x47c7b3u; native_call(m, 0x47d740u);	/* 47c7ae: call 0x47d740 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47c7b3: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x47c7bcu; native_call(m, M32(0x4a9258u));	/* 47c7b6: call dword ptr [0x4a9258] */
	m->eax = M32((DWORD)(m->esi + 0x4e4u));	/* 47c7bc: mov eax, dword ptr [esi + 0x4e4] */
	m->ecx = 0x14u;	/* 47c7c2: mov ecx, 0x14 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 47c7c7: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 47c7c8: idiv ecx */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 47c7ca: mov eax, dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x2df0u)));	/* 47c7ce: fld dword ptr [eax + 0x2df0] */
	{ long double t = ST(0); FPUSH(t); }	/* 47c7d4: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xf4u));	/* 47c7d6: fmul dword ptr [esp + 0xf4] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 47c7dd: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xf8u)));	/* 47c7e1: fld dword ptr [esp + 0xf8] */
	ST(0) = ST(0) * ST(1);	/* 47c7e8: fmul st(1) */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 47c7ea: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xfcu)));	/* 47c7ee: fld dword ptr [esp + 0xfc] */
	ST(0) = ST(0) * ST(1);	/* 47c7f5: fmul st(1) */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 47c7f7: fstp dword ptr [esp + 0x20] */
	ST(0) = ST(0); FPOP();	/* 47c7fb: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47c7fd: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 47c801: fadd dword ptr [edi] */
	m->ecx = (DWORD)(m->edx + m->edx*2 + 0x0u);	/* 47c803: lea ecx, [edx + edx*2] */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 47c806: mov dword ptr [esp + 0x24], edx */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 47c80a: shl ecx, 4 */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47c80d: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47c811: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47c815: fadd dword ptr [edi + 4] */
	m->eax = (DWORD)(m->ecx + m->esi*1 + 0x0u);	/* 47c818: lea eax, [ecx + esi] */
	m->ecx = M32((DWORD)(m->esp + 0xcu));	/* 47c81b: mov ecx, dword ptr [esp + 0xc] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47c81f: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47c823: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47c827: fadd dword ptr [edi + 8] */
	m->edx = (DWORD)(m->eax + 0xd4u);	/* 47c82a: lea edx, [eax + 0xd4] */
	M32((DWORD)(m->eax + 0xd4u)) = m->ecx;	/* 47c830: mov dword ptr [eax + 0xd4], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 47c836: mov ecx, dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 47c83a: fstp dword ptr [esp + 0x14] */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 47c83e: mov dword ptr [edx + 4], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 47c841: mov ecx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 47c845: mov dword ptr [edx + 8], ecx */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 47c848: mov edx, dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x2df0u)));	/* 47c84c: fld dword ptr [edx + 0x2df0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xe4u)));	/* 47c852: fld dword ptr [esp + 0xe4] */
	ST(0) = ST(0) * ST(1);	/* 47c859: fmul st(1) */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 47c85b: fstp dword ptr [esp + 0x18] */
	{ long double t = ST(0); FPUSH(t); }	/* 47c85f: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xe8u));	/* 47c861: fmul dword ptr [esp + 0xe8] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 47c868: fstp dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xecu));	/* 47c86c: fmul dword ptr [esp + 0xec] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 47c873: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47c877: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 47c87b: fadd dword ptr [edi] */
	m->ecx = (DWORD)(m->eax + 0xe0u);	/* 47c87d: lea ecx, [eax + 0xe0] */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47c883: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47c887: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47c88b: fadd dword ptr [edi + 4] */
	m->edx = M32((DWORD)(m->esp + 0xcu));	/* 47c88e: mov edx, dword ptr [esp + 0xc] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47c892: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47c896: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47c89a: fadd dword ptr [edi + 8] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 47c89d: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 47c89f: mov edx, dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 47c8a3: fstp dword ptr [esp + 0x14] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 47c8a7: mov dword ptr [ecx + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 47c8aa: mov edx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 47c8ae: mov dword ptr [ecx + 8], edx */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 47c8b1: mov ecx, dword ptr [esp + 0x38] */
	m->edx = (DWORD)(m->eax + 0xecu);	/* 47c8b5: lea edx, [eax + 0xec] */
	{ DWORD a_ = m->eax, b_ = 0xf8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 47c8bb: add eax, 0xf8 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x2df0u)));	/* 47c8c0: fld dword ptr [ecx + 0x2df0] */
	ST(0) = -ST(0);	/* 47c8c6: fchs  */
	{ long double t = ST(0); FPUSH(t); }	/* 47c8c8: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xf4u));	/* 47c8ca: fmul dword ptr [esp + 0xf4] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 47c8d1: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xf8u)));	/* 47c8d5: fld dword ptr [esp + 0xf8] */
	ST(0) = ST(0) * ST(1);	/* 47c8dc: fmul st(1) */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 47c8de: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xfcu)));	/* 47c8e2: fld dword ptr [esp + 0xfc] */
	ST(0) = ST(0) * ST(1);	/* 47c8e9: fmul st(1) */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 47c8eb: fstp dword ptr [esp + 0x20] */
	ST(0) = ST(0); FPOP();	/* 47c8ef: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47c8f1: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 47c8f5: fadd dword ptr [edi] */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47c8f7: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47c8fb: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47c8ff: fadd dword ptr [edi + 4] */
	m->ecx = M32((DWORD)(m->esp + 0xcu));	/* 47c902: mov ecx, dword ptr [esp + 0xc] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47c906: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47c90a: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47c90e: fadd dword ptr [edi + 8] */
	M32((DWORD)(m->edx + 0x0u)) = m->ecx;	/* 47c911: mov dword ptr [edx], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 47c913: mov ecx, dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 47c917: fstp dword ptr [esp + 0x14] */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 47c91b: mov dword ptr [edx + 4], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 47c91e: mov ecx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 47c922: mov dword ptr [edx + 8], ecx */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 47c925: mov edx, dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x2df0u)));	/* 47c929: fld dword ptr [edx + 0x2df0] */
	ST(0) = -ST(0);	/* 47c92f: fchs  */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xe4u)));	/* 47c931: fld dword ptr [esp + 0xe4] */
	ST(0) = ST(0) * ST(1);	/* 47c938: fmul st(1) */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 47c93a: fstp dword ptr [esp + 0x18] */
	{ long double t = ST(0); FPUSH(t); }	/* 47c93e: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xe8u));	/* 47c940: fmul dword ptr [esp + 0xe8] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 47c947: fstp dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xecu));	/* 47c94b: fmul dword ptr [esp + 0xec] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47c952: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 47c956: fadd dword ptr [edi] */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 47c958: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47c95c: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47c960: fadd dword ptr [edi + 4] */
	m->ecx = M32((DWORD)(m->esp + 0xcu));	/* 47c963: mov ecx, dword ptr [esp + 0xc] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47c967: fstp dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 47c96b: mov edx, dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47c96f: fadd dword ptr [edi + 8] */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 47c972: mov dword ptr [eax], ecx */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 47c974: fstp dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 47c978: mov ecx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 47c97c: mov dword ptr [eax + 4], edx */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 47c97f: mov dword ptr [eax + 8], ecx */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 47c982: mov eax, dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esi + 0x70u));	/* 47c986: mov edx, dword ptr [esi + 0x70] */
	M32((DWORD)(m->esi + m->eax*4 + 0x494u)) = m->edx;	/* 47c989: mov dword ptr [esi + eax*4 + 0x494], edx */
	m->ecx = M32((DWORD)(m->esi + 0x4e4u));	/* 47c990: mov ecx, dword ptr [esi + 0x4e4] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 47c996: inc ecx */
	m->eax = m->ecx;	/* 47c997: mov eax, ecx */
	M32((DWORD)(m->esi + 0x4e4u)) = m->ecx;	/* 47c999: mov dword ptr [esi + 0x4e4], ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 47c99f: cdq  */
	m->ecx = 0x14u;	/* 47c9a0: mov ecx, 0x14 */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 47c9a5: idiv ecx */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 47c9a7: mov dword ptr [esp + 0x24], edx */
	m->edx = (DWORD)(m->edx + m->edx*2 + 0x0u);	/* 47c9ab: lea edx, [edx + edx*2] */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 47c9ae: shl edx, 4 */
	m->eax = (DWORD)(m->edx + m->esi*1 + 0x0u);	/* 47c9b1: lea eax, [edx + esi] */
	m->edx = m->ebx;	/* 47c9b4: mov edx, ebx */
	m->edi = M32((DWORD)(m->edx + 0x0u));	/* 47c9b6: mov edi, dword ptr [edx] */
	m->ecx = (DWORD)(m->eax + 0xd4u);	/* 47c9b8: lea ecx, [eax + 0xd4] */
	M32((DWORD)(m->eax + 0xd4u)) = m->edi;	/* 47c9be: mov dword ptr [eax + 0xd4], edi */
	m->edi = M32((DWORD)(m->edx + 0x4u));	/* 47c9c4: mov edi, dword ptr [edx + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edi;	/* 47c9c7: mov dword ptr [ecx + 4], edi */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 47c9ca: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 47c9cd: mov dword ptr [ecx + 8], edx */
	m->edx = m->ebx;	/* 47c9d0: mov edx, ebx */
	m->ecx = (DWORD)(m->eax + 0xe0u);	/* 47c9d2: lea ecx, [eax + 0xe0] */
	m->edi = M32((DWORD)(m->edx + 0x0u));	/* 47c9d8: mov edi, dword ptr [edx] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edi;	/* 47c9da: mov dword ptr [ecx], edi */
	m->edi = M32((DWORD)(m->edx + 0x4u));	/* 47c9dc: mov edi, dword ptr [edx + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edi;	/* 47c9df: mov dword ptr [ecx + 4], edi */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 47c9e2: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 47c9e5: mov dword ptr [ecx + 8], edx */
	m->edx = m->ebx;	/* 47c9e8: mov edx, ebx */
	m->ecx = (DWORD)(m->eax + 0xecu);	/* 47c9ea: lea ecx, [eax + 0xec] */
	{ DWORD a_ = m->eax, b_ = 0xf8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 47c9f0: add eax, 0xf8 */
	m->edi = M32((DWORD)(m->edx + 0x0u));	/* 47c9f5: mov edi, dword ptr [edx] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edi;	/* 47c9f7: mov dword ptr [ecx], edi */
	m->edi = M32((DWORD)(m->edx + 0x4u));	/* 47c9f9: mov edi, dword ptr [edx + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edi;	/* 47c9fc: mov dword ptr [ecx + 4], edi */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 47c9ff: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 47ca02: mov dword ptr [ecx + 8], edx */
	m->ecx = M32((DWORD)(m->ebx + 0x0u));	/* 47ca05: mov ecx, dword ptr [ebx] */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 47ca07: mov dword ptr [eax], ecx */
	m->edx = M32((DWORD)(m->ebx + 0x4u));	/* 47ca09: mov edx, dword ptr [ebx + 4] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 47ca0c: mov dword ptr [eax + 4], edx */
	m->ecx = M32((DWORD)(m->ebx + 0x8u));	/* 47ca0f: mov ecx, dword ptr [ebx + 8] */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 47ca12: mov dword ptr [eax + 8], ecx */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 47ca15: mov eax, dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esi + 0x70u));	/* 47ca19: mov edx, dword ptr [esi + 0x70] */
	M32((DWORD)(m->esi + m->eax*4 + 0x494u)) = m->edx;	/* 47ca1c: mov dword ptr [esi + eax*4 + 0x494], edx */
L_47ca23:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0xcu)));	/* 47ca23: fld dword ptr [ebp + 0xc] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x70u));	/* 47ca26: fadd dword ptr [esi + 0x70] */
	MF((DWORD)(m->esi + 0x70u)) = (float)ST(0);	/* 47ca29: fst dword ptr [esi + 0x70] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0x74u)); FPOP();	/* 47ca2c: fcomp dword ptr [esi + 0x74] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47ca2f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47ca31: test ah, 0x41 */
	if (!m->zf) goto L_47ca59;	/* 47ca34: jne 0x47ca59 */
	m->eax = M32((DWORD)(m->esi + 0xcu));	/* 47ca36: mov eax, dword ptr [esi + 0xc] */
	m->edx = M32((DWORD)(m->esp + 0x40u));	/* 47ca39: mov edx, dword ptr [esp + 0x40] */
	m->ecx = m->eax;	/* 47ca3d: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 47ca3f: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 47ca42: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 47ca44: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 47ca47: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 47ca49: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 47ca4c: add ecx, eax */
	M32((DWORD)(m->edx + m->ecx*8 + 0x1cd971cu)) = 0x1u;	/* 47ca4e: mov dword ptr [edx + ecx*8 + 0x1cd971c], 1 */
L_47ca59:
	M32((DWORD)(m->esi + 0x9cu)) = 0x0u;	/* 47ca59: mov dword ptr [esi + 0x9c], 0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 47ca63: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 47ca64: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 47ca65: pop ebx */
	m->esp = m->ebp;	/* 47ca66: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 47ca68: pop ebp */
	m->esp += 4 + 8; return;	/* 47ca69: ret 8 */
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
