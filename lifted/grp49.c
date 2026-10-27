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

static void lift_457330(X86 *m);

/* actor_setupFromParts (0x457330), lifted by tools/lift.py */
static void lift_457330(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 457330: sub esp, 0x20 */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 457333: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 457337: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 457338: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 457339: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45733a: push edi */
	m->edi = m->ecx;	/* 45733b: mov edi, ecx */
	m->ecx = m->eax;	/* 45733d: mov ecx, eax */
	m->edx = M32((DWORD)(m->esp + 0x40u));	/* 45733f: mov edx, dword ptr [esp + 0x40] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 457343: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 457346: add ecx, eax */
	M32((DWORD)(m->esp + 0x28u)) = m->edi;	/* 457348: mov dword ptr [esp + 0x28], edi */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45734c: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45734f: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 457351: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 457354: add ecx, eax */
	m->ebp = (DWORD)(m->edi + m->ecx*8 + 0x1cd93a8u);	/* 457356: lea ebp, [edi + ecx*8 + 0x1cd93a8] */
	m->ecx = M32((DWORD)(m->edx + 0x0u));	/* 45735d: mov ecx, dword ptr [edx] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 45735f: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 457362: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 457365: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 457367: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 45736a: lea ecx, [ecx + eax*8] */
	m->esi = (DWORD)(m->edi + m->ecx*2 + 0x1561b68u);	/* 45736d: lea esi, [edi + ecx*2 + 0x1561b68] */
	M32((DWORD)(m->esp + 0x2cu)) = m->esi;	/* 457374: mov dword ptr [esp + 0x2c], esi */
	m->ecx = M32((DWORD)(m->esi + 0x30cu));	/* 457378: mov ecx, dword ptr [esi + 0x30c] */
	m->eax = m->ecx;	/* 45737e: mov eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 457380: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 457383: add eax, ecx */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 457385: lea edx, [eax + eax*4] */
	m->eax = (DWORD)(m->ecx + m->edx*4 + 0x0u);	/* 457388: lea eax, [ecx + edx*4] */
	m->ecx = M32((DWORD)(m->esi + 0x310u));	/* 45738b: mov ecx, dword ptr [esi + 0x310] */
	m->edx = (DWORD)(m->edi + m->eax*8 + 0x13c9b30u);	/* 457391: lea edx, [edi + eax*8 + 0x13c9b30] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 457398: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45739b: shl eax, 3 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45739e: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4573a0: lea eax, [eax + eax*4] */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4573a3: shl eax, 1 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4573a5: sub eax, ecx */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 4573a7: lea ecx, [eax + eax*2] */
	m->eax = (DWORD)(m->edi + m->ecx*4 + 0x13eb004u);	/* 4573aa: lea eax, [edi + ecx*4 + 0x13eb004] */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 4573b1: mov dword ptr [esp + 0x10], eax */
	m->eax = M32((DWORD)(m->esi + 0x314u));	/* 4573b5: mov eax, dword ptr [esi + 0x314] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 4573bb: lea ecx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 4573be: lea eax, [eax + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4573c1: shl eax, 8 */
	m->ecx = (DWORD)(m->eax + m->edi*1 + 0x140c8c0u);	/* 4573c4: lea ecx, [eax + edi + 0x140c8c0] */
	m->eax = M32((DWORD)(m->esi + 0x318u));	/* 4573cb: mov eax, dword ptr [esi + 0x318] */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 4573d1: mov dword ptr [esp + 0x20], ecx */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4573d5: lea ecx, [eax + eax*4] */
	{ DWORD a_ = m->ecx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4573d8: shl ecx, 6 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4573db: sub ecx, eax */
	m->eax = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 4573dd: lea eax, [eax + ecx*4] */
	m->ecx = (DWORD)(m->edi + m->eax*4 + 0x1447ec4u);	/* 4573e0: lea ecx, [edi + eax*4 + 0x1447ec4] */
	m->eax = M32((DWORD)(m->esi + 0x31cu));	/* 4573e7: mov eax, dword ptr [esi + 0x31c] */
	M32((DWORD)(m->esp + 0x18u)) = m->ecx;	/* 4573ed: mov dword ptr [esp + 0x18], ecx */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 4573f1: lea ecx, [eax + eax*2] */
	{ DWORD a_ = m->ecx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4573f4: shl ecx, 6 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4573f7: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4573f9: shl ecx, 5 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 4573fc: xor ebx, ebx */
	m->eax = (DWORD)(m->ecx + m->edi*1 + 0x1486470u);	/* 4573fe: lea eax, [ecx + edi + 0x1486470] */
	m->ecx = 0x4u;	/* 457405: mov ecx, 4 */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 45740a: mov dword ptr [esp + 0x24], eax */
	m->eax = (DWORD)(m->ebp + 0x414u);	/* 45740e: lea eax, [ebp + 0x414] */
L_457414:
	M32((DWORD)(m->eax + 0xfffffff0u)) = 0x3f800000u;	/* 457414: mov dword ptr [eax - 0x10], 0x3f800000 */
	M32((DWORD)(m->eax + 0x0u)) = m->ebx;	/* 45741b: mov dword ptr [eax], ebx */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45741d: add eax, 4 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 457420: dec ecx */
	if (!m->zf) goto L_457414;	/* 457421: jne 0x457414 */
	m->eax = 0x3f800000u;	/* 457423: mov eax, 0x3f800000 */
	M32((DWORD)(m->ebp + 0x424u)) = m->ebx;	/* 457428: mov dword ptr [ebp + 0x424], ebx */
	M32((DWORD)(m->ebp + 0x428u)) = m->eax;	/* 45742e: mov dword ptr [ebp + 0x428], eax */
	M32((DWORD)(m->ebp + 0x42cu)) = m->eax;	/* 457434: mov dword ptr [ebp + 0x42c], eax */
	M32((DWORD)(m->ebp + 0x430u)) = m->ebx;	/* 45743a: mov dword ptr [ebp + 0x430], ebx */
	M32((DWORD)(m->ebp + 0x434u)) = m->eax;	/* 457440: mov dword ptr [ebp + 0x434], eax */
	M32((DWORD)(m->ebp + 0x438u)) = m->eax;	/* 457446: mov dword ptr [ebp + 0x438], eax */
	M32((DWORD)(m->ebp + 0x43cu)) = m->eax;	/* 45744c: mov dword ptr [ebp + 0x43c], eax */
	M32((DWORD)(m->ebp + 0x440u)) = m->eax;	/* 457452: mov dword ptr [ebp + 0x440], eax */
	M32((DWORD)(m->ebp + 0x444u)) = m->eax;	/* 457458: mov dword ptr [ebp + 0x444], eax */
	m->eax = (DWORD)(m->esi + 0x320u);	/* 45745e: lea eax, [esi + 0x320] */
	M32((DWORD)(m->ebp + 0x448u)) = m->ebx;	/* 457464: mov dword ptr [ebp + 0x448], ebx */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 45746a: mov dword ptr [esp + 0x14], eax */
	M32((DWORD)(m->esp + 0x1cu)) = 0x6u;	/* 45746e: mov dword ptr [esp + 0x1c], 6 */
L_457476:
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 457476: mov ecx, dword ptr [eax] */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 457478: cmp ecx, ebx */
	if (m->sf != m->of) goto L_4575a7;	/* 45747a: jl 0x4575a7 */
	m->eax = m->ecx;	/* 457480: mov eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 457482: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 457485: sub eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 457487: shl eax, 2 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45748a: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45748c: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45748f: lea eax, [eax + eax*4] */
	{ DWORD a_ = M32((DWORD)(m->edi + m->eax*8 + 0x14d4874u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 457492: cmp dword ptr [edi + eax*8 + 0x14d4874], ebx */
	if (m->sf == m->of) goto L_4575a7;	/* 457499: jge 0x4575a7 */
	m->eax = (DWORD)(m->ecx + 0xffffffe5u);	/* 45749f: lea eax, [ecx - 0x1b] */
	{ DWORD a_ = m->eax, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4574a2: cmp eax, 8 */
	if (!m->cf && !m->zf) goto L_4575a7;	/* 4574a5: ja 0x4575a7 */
	switch (m->eax) { case 0: goto L_4574b2; case 1: goto L_4574d3; case 2: goto L_4574df; case 3: goto L_4574eb; case 4: goto L_4574f7; case 5: goto L_457503; case 6: goto L_457542; case 7: goto L_45757a; case 8: goto L_45758e; default: abort(); }	/* 4574ab: jmp dword ptr [eax*4 + 0x458080] */
L_4574b2:
	m->eax = (DWORD)(m->ebp + 0x404u);	/* 4574b2: lea eax, [ebp + 0x404] */
	m->ecx = 0x4u;	/* 4574b8: mov ecx, 4 */
L_4574bd:
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 4574bd: fld dword ptr [eax] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a94fcu));	/* 4574bf: fadd dword ptr [0x4a94fc] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4574c5: add eax, 4 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4574c8: dec ecx */
	MF((DWORD)(m->eax + 0xfffffffcu)) = (float)ST(0); FPOP();	/* 4574c9: fstp dword ptr [eax - 4] */
	if (!m->zf) goto L_4574bd;	/* 4574cc: jne 0x4574bd */
	goto L_4575a7;	/* 4574ce: jmp 0x4575a7 */
L_4574d3:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x41cu)), b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(m->ebp + 0x41cu)) = r_; }	/* 4574d3: add dword ptr [ebp + 0x41c], 0x64 */
	goto L_4575a7;	/* 4574da: jmp 0x4575a7 */
L_4574df:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x414u)), b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(m->ebp + 0x414u)) = r_; }	/* 4574df: add dword ptr [ebp + 0x414], 0x64 */
	goto L_4575a7;	/* 4574e6: jmp 0x4575a7 */
L_4574eb:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x418u)), b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(m->ebp + 0x418u)) = r_; }	/* 4574eb: add dword ptr [ebp + 0x418], 0x64 */
	goto L_4575a7;	/* 4574f2: jmp 0x4575a7 */
L_4574f7:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x420u)), b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(m->ebp + 0x420u)) = r_; }	/* 4574f7: add dword ptr [ebp + 0x420], 0x64 */
	goto L_4575a7;	/* 4574fe: jmp 0x4575a7 */
L_457503:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x424u)));	/* 457503: fld dword ptr [ebp + 0x424] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9708u));	/* 457509: fadd dword ptr [0x4a9708] */
	MF((DWORD)(m->ebp + 0x424u)) = (float)ST(0); FPOP();	/* 45750f: fstp dword ptr [ebp + 0x424] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x428u)));	/* 457515: fld dword ptr [ebp + 0x428] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 45751b: fsub dword ptr [0x4a942c] */
	MF((DWORD)(m->ebp + 0x428u)) = (float)ST(0); FPOP();	/* 457521: fstp dword ptr [ebp + 0x428] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x42cu)));	/* 457527: fld dword ptr [ebp + 0x42c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 45752d: fadd dword ptr [0x4a9424] */
	MF((DWORD)(m->ebp + 0x42cu)) = (float)ST(0); FPOP();	/* 457533: fstp dword ptr [ebp + 0x42c] */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x430u)), b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(m->ebp + 0x430u)) = r_; }	/* 457539: add dword ptr [ebp + 0x430], 3 */
	goto L_4575a7;	/* 457540: jmp 0x4575a7 */
L_457542:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x434u)));	/* 457542: fld dword ptr [ebp + 0x434] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 457548: fadd dword ptr [0x4a942c] */
	MF((DWORD)(m->ebp + 0x434u)) = (float)ST(0); FPOP();	/* 45754e: fstp dword ptr [ebp + 0x434] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x438u)));	/* 457554: fld dword ptr [ebp + 0x438] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 45755a: fsub dword ptr [0x4a942c] */
	MF((DWORD)(m->ebp + 0x438u)) = (float)ST(0); FPOP();	/* 457560: fstp dword ptr [ebp + 0x438] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x43cu)));	/* 457566: fld dword ptr [ebp + 0x43c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 45756c: fsub dword ptr [0x4a942c] */
	MF((DWORD)(m->ebp + 0x43cu)) = (float)ST(0); FPOP();	/* 457572: fstp dword ptr [ebp + 0x43c] */
	goto L_4575a7;	/* 457578: jmp 0x4575a7 */
L_45757a:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x440u)));	/* 45757a: fld dword ptr [ebp + 0x440] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a94f8u));	/* 457580: fadd dword ptr [0x4a94f8] */
	MF((DWORD)(m->ebp + 0x440u)) = (float)ST(0); FPOP();	/* 457586: fstp dword ptr [ebp + 0x440] */
	goto L_4575a7;	/* 45758c: jmp 0x4575a7 */
L_45758e:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x444u)));	/* 45758e: fld dword ptr [ebp + 0x444] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a94fcu));	/* 457594: fadd dword ptr [0x4a94fc] */
	MF((DWORD)(m->ebp + 0x444u)) = (float)ST(0); FPOP();	/* 45759a: fstp dword ptr [ebp + 0x444] */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x448u)), b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(m->ebp + 0x448u)) = r_; }	/* 4575a0: add dword ptr [ebp + 0x448], 4 */
L_4575a7:
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4575a7: mov eax, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 4575ab: mov ecx, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4575af: add eax, 4 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4575b2: dec ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 4575b3: mov dword ptr [esp + 0x14], eax */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 4575b7: mov dword ptr [esp + 0x1c], ecx */
	if (!m->zf) goto L_457476;	/* 4575bb: jne 0x457476 */
	m->eax = M32((DWORD)(m->esi + 0x44u));	/* 4575c1: mov eax, dword ptr [esi + 0x44] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 4575c4: lea ecx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 4575c7: lea eax, [eax + ecx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->eax*4 + 0x9f9084u)));	/* 4575ca: fild dword ptr [eax*4 + 0x9f9084] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 4575d1: fmul dword ptr [0x4a9420] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4575d7: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edx + 0xa94u));	/* 4575dd: fmul dword ptr [edx + 0xa94] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x424u));	/* 4575e3: fadd dword ptr [ebp + 0x424] */
	{ long double t = ST(0); FPUSH(t); }	/* 4575e9: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 4575eb: fmul st(1) */
	MF((DWORD)(m->ebp + 0x0u)) = (float)ST(0); FPOP();	/* 4575ed: fstp dword ptr [ebp] */
	m->eax = M32((DWORD)(m->esi + 0x44u));	/* 4575f0: mov eax, dword ptr [esi + 0x44] */
	ST(0) = ST(0); FPOP();	/* 4575f3: fstp st(0) */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 4575f5: lea ecx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 4575f8: lea eax, [eax + ecx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->eax*4 + 0x9f9084u)));	/* 4575fb: fild dword ptr [eax*4 + 0x9f9084] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 457602: fmul dword ptr [0x4a9420] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 457608: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edx + 0xa98u));	/* 45760e: fmul dword ptr [edx + 0xa98] */
	MF((DWORD)(m->ebp + 0x4u)) = (float)ST(0); FPOP();	/* 457614: fstp dword ptr [ebp + 4] */
	m->ecx = M32((DWORD)(m->edx + 0xa9cu));	/* 457617: mov ecx, dword ptr [edx + 0xa9c] */
	m->eax = M32((DWORD)(m->ebp + 0x430u));	/* 45761d: mov eax, dword ptr [ebp + 0x430] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 457623: add ecx, eax */
	M32((DWORD)(m->ebp + 0x8u)) = m->ecx;	/* 457625: mov dword ptr [ebp + 8], ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0xaa0u)));	/* 457628: fld dword ptr [edx + 0xaa0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x428u));	/* 45762e: fmul dword ptr [ebp + 0x428] */
	MF((DWORD)(m->ebp + 0xcu)) = (float)ST(0); FPOP();	/* 457634: fstp dword ptr [ebp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0xaa4u)));	/* 457637: fld dword ptr [edx + 0xaa4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x42cu));	/* 45763d: fmul dword ptr [ebp + 0x42c] */
	MF((DWORD)(m->ebp + 0x10u)) = (float)ST(0); FPOP();	/* 457643: fstp dword ptr [ebp + 0x10] */
	m->eax = M32((DWORD)(m->esi + 0x44u));	/* 457646: mov eax, dword ptr [esi + 0x44] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 457649: lea ecx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 45764c: lea eax, [eax + ecx*2] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 45764f: mov ecx, dword ptr [esp + 0x10] */
	FPUSH((long double)(int)M32((DWORD)(m->eax*4 + 0x9f9088u)));	/* 457653: fild dword ptr [eax*4 + 0x9f9088] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 45765a: mov eax, dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 45765e: fmul dword ptr [0x4a9420] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 457664: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0xab0u));	/* 45766a: fmul dword ptr [ecx + 0xab0] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 457670: mov ecx, dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x440u));	/* 457674: fmul dword ptr [ebp + 0x440] */
	MF((DWORD)(m->ebp + 0x14u)) = (float)ST(0); FPOP();	/* 45767a: fstp dword ptr [ebp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x17f8u)));	/* 45767d: fld dword ptr [eax + 0x17f8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x13d8u));	/* 457683: fadd dword ptr [ecx + 0x13d8] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 457689: mov eax, dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x12e8u));	/* 45768d: fadd dword ptr [eax + 0x12e8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edx + 0xa90u));	/* 457693: fadd dword ptr [edx + 0xa90] */
	MF((DWORD)(m->ebp + 0x18u)) = (float)ST(0); FPOP();	/* 457699: fstp dword ptr [ebp + 0x18] */
	m->eax = M32((DWORD)(m->edi + 0x20f3ab8u));	/* 45769c: mov eax, dword ptr [edi + 0x20f3ab8] */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4576a2: cmp eax, 2 */
	if (m->zf) goto L_457715;	/* 4576a5: je 0x457715 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4576a7: cmp eax, 3 */
	if (m->zf) goto L_457715;	/* 4576aa: je 0x457715 */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4576ac: cmp eax, 4 */
	if (m->zf) goto L_457715;	/* 4576af: je 0x457715 */
	{ DWORD a_ = m->eax, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4576b1: cmp eax, 5 */
	if (m->zf) goto L_457715;	/* 4576b4: je 0x457715 */
	{ DWORD a_ = m->eax, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4576b6: cmp eax, 6 */
	if (m->zf) goto L_457715;	/* 4576b9: je 0x457715 */
	{ DWORD a_ = m->eax, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4576bb: cmp eax, 7 */
	if (m->zf) goto L_457715;	/* 4576be: je 0x457715 */
	{ DWORD a_ = m->eax, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4576c0: cmp eax, 8 */
	if (m->zf) goto L_457715;	/* 4576c3: je 0x457715 */
	{ DWORD a_ = m->eax, b_ = 0x9u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4576c5: cmp eax, 9 */
	if (m->zf) goto L_457715;	/* 4576c8: je 0x457715 */
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4576ca: cmp eax, 0xa */
	if (m->zf) goto L_457715;	/* 4576cd: je 0x457715 */
	{ DWORD a_ = m->eax, b_ = 0xbu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4576cf: cmp eax, 0xb */
	if (m->zf) goto L_457715;	/* 4576d2: je 0x457715 */
	m->ecx = (DWORD)(m->esi + 0x320u);	/* 4576d4: lea ecx, [esi + 0x320] */
	M32((DWORD)(m->esp + 0x1cu)) = 0x6u;	/* 4576da: mov dword ptr [esp + 0x1c], 6 */
L_4576e2:
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 4576e2: mov edx, dword ptr [ecx] */
	{ DWORD a_ = m->edx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4576e4: cmp edx, ebx */
	if (m->sf != m->of) goto L_457707;	/* 4576e6: jl 0x457707 */
	m->eax = m->edx;	/* 4576e8: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4576ea: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4576ed: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4576ef: shl eax, 2 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4576f2: sub eax, edx */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4576f4: lea eax, [eax + eax*4] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4576f7: lea edx, [eax + eax*4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + m->edx*8 + 0x14d486cu)));	/* 4576fa: fld dword ptr [edi + edx*8 + 0x14d486c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x18u));	/* 457701: fadd dword ptr [ebp + 0x18] */
	MF((DWORD)(m->ebp + 0x18u)) = (float)ST(0); FPOP();	/* 457704: fstp dword ptr [ebp + 0x18] */
L_457707:
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 457707: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45770b: add ecx, 4 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 45770e: dec eax */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 45770f: mov dword ptr [esp + 0x1c], eax */
	if (!m->zf) goto L_4576e2;	/* 457713: jne 0x4576e2 */
L_457715:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x18u)));	/* 457715: fld dword ptr [ebp + 0x18] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x14u)); FPOP();	/* 457718: fcomp dword ptr [ebp + 0x14] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45771b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45771d: test ah, 0x41 */
	if (!m->zf) goto L_457733;	/* 457720: jne 0x457733 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x18u)));	/* 457722: fld dword ptr [ebp + 0x18] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x14u));	/* 457725: fsub dword ptr [ebp + 0x14] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->ebp + 0x14u));	/* 457728: fdiv dword ptr [ebp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a947cu));	/* 45772b: fmul dword ptr [0x4a947c] */
	goto L_457739;	/* 457731: jmp 0x457739 */
L_457733:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93e8u)));	/* 457733: fld dword ptr [0x4a93e8] */
L_457739:
	m->eax = M32((DWORD)(m->esi + 0x44u));	/* 457739: mov eax, dword ptr [esi + 0x44] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 45773c: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 45773f: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 457742: mov eax, dword ptr [esp + 0x10] */
	FPUSH((long double)(int)M32((DWORD)(m->edx*4 + 0x9f9080u)));	/* 457746: fild dword ptr [edx*4 + 0x9f9080] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 45774d: fmul dword ptr [0x4a9420] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 457753: fadd dword ptr [0x4a9424] */
	ST(0) = ST(0) * (long double)(int)M32((DWORD)(m->eax + 0xab4u));	/* 457759: fimul dword ptr [eax + 0xab4] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 45775f: fadd dword ptr [0x4a942c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 457765: call 0x49ec14 */
	M32((DWORD)(m->ebp + 0x1cu)) = m->eax;	/* 45776a: mov dword ptr [ebp + 0x1c], eax */
	m->eax = M32((DWORD)(m->esi + 0x44u));	/* 45776d: mov eax, dword ptr [esi + 0x44] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 457770: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 457773: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 457776: mov eax, dword ptr [esp + 0x10] */
	FPUSH((long double)(int)M32((DWORD)(m->edx*4 + 0x9f9080u)));	/* 45777a: fild dword ptr [edx*4 + 0x9f9080] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 457781: fmul dword ptr [0x4a9420] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 457787: fadd dword ptr [0x4a9424] */
	ST(0) = ST(0) * (long double)(int)M32((DWORD)(m->eax + 0xab8u));	/* 45778d: fimul dword ptr [eax + 0xab8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x444u));	/* 457793: fmul dword ptr [ebp + 0x444] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 457799: fadd dword ptr [0x4a942c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 45779f: call 0x49ec14 */
	M32((DWORD)(m->ebp + 0x20u)) = m->eax;	/* 4577a4: mov dword ptr [ebp + 0x20], eax */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 4577a7: mov eax, dword ptr [esp + 0x20] */
	M32((DWORD)(m->esp + 0x20u)) = 0x4u;	/* 4577ab: mov dword ptr [esp + 0x20], 4 */
	m->ecx = M32((DWORD)(m->eax + 0x12ecu));	/* 4577b3: mov ecx, dword ptr [eax + 0x12ec] */
	{ DWORD a_ = m->eax, b_ = 0x12f0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4577b9: add eax, 0x12f0 */
	M32((DWORD)(m->ebp + 0x24u)) = m->ecx;	/* 4577be: mov dword ptr [ebp + 0x24], ecx */
	m->ecx = (DWORD)(m->ebp + 0x414u);	/* 4577c1: lea ecx, [ebp + 0x414] */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 4577c7: mov dword ptr [esp + 0x14], ecx */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 4577cb: mov dword ptr [esp + 0x10], eax */
L_4577cf:
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 4577cf: mov edx, dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4577d3: mov eax, dword ptr [esp + 0x14] */
	FPUSH((long double)(int)M32((DWORD)(m->edx + 0x0u)));	/* 4577d7: fild dword ptr [edx] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0xfffffff0u));	/* 4577d9: fmul dword ptr [eax - 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4577dc: fadd dword ptr [0x4a942c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4577e2: call 0x49ec14 */
	m->ecx = m->eax;	/* 4577e7: mov ecx, eax */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4577e9: mov eax, dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 4577ed: mov edx, dword ptr [eax] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4577ef: add eax, 4 */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4577f2: add ecx, edx */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 4577f4: mov edx, dword ptr [esp + 0x10] */
	M32((DWORD)(m->eax + 0xfffffc10u)) = m->ecx;	/* 4577f8: mov dword ptr [eax - 0x3f0], ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 4577fe: mov dword ptr [esp + 0x14], eax */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 457802: mov eax, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->edx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 457806: add edx, 4 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 457809: dec eax */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 45780a: mov dword ptr [esp + 0x10], edx */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 45780e: mov dword ptr [esp + 0x20], eax */
	if (!m->zf) goto L_4577cf;	/* 457812: jne 0x4577cf */
	m->eax = M32((DWORD)(m->esi + 0x44u));	/* 457814: mov eax, dword ptr [esi + 0x44] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 457817: mov ecx, dword ptr [esp + 0x18] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 45781b: fsubr dword ptr [0x4a9424] */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 457821: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 457824: lea eax, [eax + edx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->eax*4 + 0x9f9078u)));	/* 457827: fild dword ptr [eax*4 + 0x9f9078] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 45782e: fmul dword ptr [0x4a9420] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 457834: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x13dcu));	/* 45783a: fmul dword ptr [ecx + 0x13dc] */
	ST(0) = ST(0) * ST(1);	/* 457840: fmul st(1) */
	MF((DWORD)(m->ebp + 0x38u)) = (float)ST(0);	/* 457842: fst dword ptr [ebp + 0x38] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 457845: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45784b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45784d: test ah, 1 */
	if (m->zf) goto L_457855;	/* 457850: je 0x457855 */
	M32((DWORD)(m->ebp + 0x38u)) = m->ebx;	/* 457852: mov dword ptr [ebp + 0x38], ebx */
L_457855:
	{ DWORD a_ = M32((DWORD)(m->edi + 0x20f3accu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 457855: cmp dword ptr [edi + 0x20f3acc], 1 */
	if (!m->zf) goto L_45786a;	/* 45785c: jne 0x45786a */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x38u)));	/* 45785e: fld dword ptr [ebp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9704u));	/* 457861: fmul dword ptr [0x4a9704] */
	MF((DWORD)(m->ebp + 0x38u)) = (float)ST(0); FPOP();	/* 457867: fstp dword ptr [ebp + 0x38] */
L_45786a:
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 45786a: mov ecx, dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->ecx + 0x1800u));	/* 45786e: mov edx, dword ptr [ecx + 0x1800] */
	M32((DWORD)(m->ebp + 0x40u)) = m->edx;	/* 457874: mov dword ptr [ebp + 0x40], edx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x1804u)));	/* 457877: fld dword ptr [ecx + 0x1804] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x434u));	/* 45787d: fmul dword ptr [ebp + 0x434] */
	MF((DWORD)(m->ebp + 0x44u)) = (float)ST(0); FPOP();	/* 457883: fstp dword ptr [ebp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x1808u)));	/* 457886: fld dword ptr [ecx + 0x1808] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x438u));	/* 45788c: fmul dword ptr [ebp + 0x438] */
	MF((DWORD)(m->ebp + 0x48u)) = (float)ST(0); FPOP();	/* 457892: fstp dword ptr [ebp + 0x48] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x180cu)));	/* 457895: fld dword ptr [ecx + 0x180c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x43cu));	/* 45789b: fmul dword ptr [ebp + 0x43c] */
	MF((DWORD)(m->ebp + 0x4cu)) = (float)ST(0); FPOP();	/* 4578a1: fstp dword ptr [ebp + 0x4c] */
	m->eax = M32((DWORD)(m->esi + 0x44u));	/* 4578a4: mov eax, dword ptr [esi + 0x44] */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 4578a7: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 4578aa: lea eax, [eax + edx*2] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 4578ad: mov edx, dword ptr [esp + 0x18] */
	FPUSH((long double)(int)M32((DWORD)(m->eax*4 + 0x9f907cu)));	/* 4578b1: fild dword ptr [eax*4 + 0x9f907c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 4578b8: fmul dword ptr [0x4a9420] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edx + 0x13e4u));	/* 4578be: fadd dword ptr [edx + 0x13e4] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4578c4: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x1810u));	/* 4578ca: fmul dword ptr [ecx + 0x1810] */
	ST(0) = ST(0) * ST(1);	/* 4578d0: fmul st(1) */
	MF((DWORD)(m->ebp + 0x50u)) = (float)ST(0);	/* 4578d2: fst dword ptr [ebp + 0x50] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f4u)); FPOP();	/* 4578d5: fcomp dword ptr [0x4a93f4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4578db: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4578dd: test ah, 1 */
	if (m->zf) goto L_4578e9;	/* 4578e0: je 0x4578e9 */
	M32((DWORD)(m->ebp + 0x50u)) = 0x42c80000u;	/* 4578e2: mov dword ptr [ebp + 0x50], 0x42c80000 */
L_4578e9:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x13e0u)));	/* 4578e9: fld dword ptr [edx + 0x13e0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x50u));	/* 4578ef: fmul dword ptr [ebp + 0x50] */
	MF((DWORD)(m->ebp + 0x3cu)) = (float)ST(0);	/* 4578f2: fst dword ptr [ebp + 0x3c] */
	{ DWORD a_ = M32((DWORD)(m->edi + 0x20f3accu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4578f5: cmp dword ptr [edi + 0x20f3acc], 1 */
	if (!m->zf) goto L_457909;	/* 4578fc: jne 0x457909 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9704u));	/* 4578fe: fmul dword ptr [0x4a9704] */
	MF((DWORD)(m->ebp + 0x3cu)) = (float)ST(0); FPOP();	/* 457904: fstp dword ptr [ebp + 0x3c] */
	goto L_45790b;	/* 457907: jmp 0x45790b */
L_457909:
	ST(0) = ST(0); FPOP();	/* 457909: fstp st(0) */
L_45790b:
	m->eax = M32((DWORD)(m->esi + 0x44u));	/* 45790b: mov eax, dword ptr [esi + 0x44] */
	m->edi = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 45790e: lea edi, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edi*2 + 0x0u);	/* 457911: lea eax, [eax + edi*2] */
	FPUSH((long double)(int)M32((DWORD)(m->eax*4 + 0x9f907cu)));	/* 457914: fild dword ptr [eax*4 + 0x9f907c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 45791b: fmul dword ptr [0x4a9420] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edx + 0x13e8u));	/* 457921: fadd dword ptr [edx + 0x13e8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 457927: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x1814u));	/* 45792d: fmul dword ptr [ecx + 0x1814] */
	MF((DWORD)(m->ebp + 0x54u)) = (float)ST(0);	/* 457933: fst dword ptr [ebp + 0x54] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->ebp + 0x50u));	/* 457936: fdiv dword ptr [ebp + 0x50] */
	ST(0) = ST(0) * ST(1);	/* 457939: fmul st(1) */
	MF((DWORD)(m->ebp + 0x54u)) = (float)ST(0);	/* 45793b: fst dword ptr [ebp + 0x54] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45793e: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 457944: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 457946: test ah, 1 */
	if (m->zf) goto L_45794e;	/* 457949: je 0x45794e */
	M32((DWORD)(m->ebp + 0x54u)) = m->ebx;	/* 45794b: mov dword ptr [ebp + 0x54], ebx */
L_45794e:
	m->eax = M32((DWORD)(m->esi + 0x44u));	/* 45794e: mov eax, dword ptr [esi + 0x44] */
	m->edi = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 457951: lea edi, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edi*2 + 0x0u);	/* 457954: lea eax, [eax + edi*2] */
	FPUSH((long double)(int)M32((DWORD)(m->eax*4 + 0x9f907cu)));	/* 457957: fild dword ptr [eax*4 + 0x9f907c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 45795e: fmul dword ptr [0x4a9420] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edx + 0x13ecu));	/* 457964: fadd dword ptr [edx + 0x13ec] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 45796a: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x1818u));	/* 457970: fmul dword ptr [ecx + 0x1818] */
	MF((DWORD)(m->ebp + 0x58u)) = (float)ST(0);	/* 457976: fst dword ptr [ebp + 0x58] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->ebp + 0x50u));	/* 457979: fdiv dword ptr [ebp + 0x50] */
	ST(0) = ST(0) * ST(1);	/* 45797c: fmul st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9474u));	/* 45797e: fmul dword ptr [0x4a9474] */
	MF((DWORD)(m->ebp + 0x58u)) = (float)ST(0);	/* 457984: fst dword ptr [ebp + 0x58] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 457987: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45798d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45798f: test ah, 0x41 */
	if (!m->zf) goto L_457997;	/* 457992: jne 0x457997 */
	M32((DWORD)(m->ebp + 0x58u)) = m->ebx;	/* 457994: mov dword ptr [ebp + 0x58], ebx */
L_457997:
	m->eax = M32((DWORD)(m->esi + 0x44u));	/* 457997: mov eax, dword ptr [esi + 0x44] */
	m->edi = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 45799a: lea edi, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edi*2 + 0x0u);	/* 45799d: lea eax, [eax + edi*2] */
	FPUSH((long double)(int)M32((DWORD)(m->eax*4 + 0x9f907cu)));	/* 4579a0: fild dword ptr [eax*4 + 0x9f907c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 4579a7: fmul dword ptr [0x4a9420] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edx + 0x13f0u));	/* 4579ad: fadd dword ptr [edx + 0x13f0] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4579b3: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x181cu));	/* 4579b9: fmul dword ptr [ecx + 0x181c] */
	MF((DWORD)(m->ebp + 0x5cu)) = (float)ST(0);	/* 4579bf: fst dword ptr [ebp + 0x5c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->ebp + 0x50u));	/* 4579c2: fdiv dword ptr [ebp + 0x50] */
	ST(1) = ST(1) * ST(0); FPOP();	/* 4579c5: fmulp st(1) */
	MF((DWORD)(m->ebp + 0x5cu)) = (float)ST(0);	/* 4579c7: fst dword ptr [ebp + 0x5c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 4579ca: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4579d0: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4579d2: test ah, 1 */
	if (m->zf) goto L_4579da;	/* 4579d5: je 0x4579da */
	M32((DWORD)(m->ebp + 0x5cu)) = m->ebx;	/* 4579d7: mov dword ptr [ebp + 0x5c], ebx */
L_4579da:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x5cu)));	/* 4579da: fld dword ptr [ebp + 0x5c] */
	ST(0) = -ST(0);	/* 4579dd: fchs  */
	MF((DWORD)(m->ebp + 0x60u)) = (float)ST(0); FPOP();	/* 4579df: fstp dword ptr [ebp + 0x60] */
	M32((DWORD)(m->ebp + 0x64u)) = 0x64u;	/* 4579e2: mov dword ptr [ebp + 0x64], 0x64 */
	m->ecx = M32((DWORD)(m->ebp + 0x50u));	/* 4579e9: mov ecx, dword ptr [ebp + 0x50] */
	M32((DWORD)(m->ebp + 0x68u)) = m->ecx;	/* 4579ec: mov dword ptr [ebp + 0x68], ecx */
	M32((DWORD)(m->ebp + 0x6cu)) = 0x44610000u;	/* 4579ef: mov dword ptr [ebp + 0x6c], 0x44610000 */
	M32((DWORD)(m->ebp + 0x70u)) = 0x40400000u;	/* 4579f6: mov dword ptr [ebp + 0x70], 0x40400000 */
	M32((DWORD)(m->ebp + 0x74u)) = 0xau;	/* 4579fd: mov dword ptr [ebp + 0x74], 0xa */
	M32((DWORD)(m->ebp + 0x78u)) = m->ebx;	/* 457a04: mov dword ptr [ebp + 0x78], ebx */
	M32((DWORD)(m->ebp + 0x7cu)) = 0x447a0000u;	/* 457a07: mov dword ptr [ebp + 0x7c], 0x447a0000 */
	M32((DWORD)(m->ebp + 0x80u)) = 0x43fa0000u;	/* 457a0e: mov dword ptr [ebp + 0x80], 0x43fa0000 */
	m->eax = 0x3f800000u;	/* 457a18: mov eax, 0x3f800000 */
	M32((DWORD)(m->ebp + 0x84u)) = 0x40000000u;	/* 457a1d: mov dword ptr [ebp + 0x84], 0x40000000 */
	M32((DWORD)(m->ebp + 0x88u)) = m->eax;	/* 457a27: mov dword ptr [ebp + 0x88], eax */
	M32((DWORD)(m->ebp + 0x8cu)) = 0x457a0000u;	/* 457a2d: mov dword ptr [ebp + 0x8c], 0x457a0000 */
	M32((DWORD)(m->ebp + 0x90u)) = 0x40a00000u;	/* 457a37: mov dword ptr [ebp + 0x90], 0x40a00000 */
	M32((DWORD)(m->ebp + 0x94u)) = m->eax;	/* 457a41: mov dword ptr [ebp + 0x94], eax */
	m->edx = 0x1u;	/* 457a47: mov edx, 1 */
	m->edi = (DWORD)(m->esi + 0x4u);	/* 457a4c: lea edi, [esi + 4] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 457a4f: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 457a52: xor eax, eax */
	M32((DWORD)(m->ebp + 0xd8u)) = m->edx;	/* 457a54: mov dword ptr [ebp + 0xd8], edx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 457a5a: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 457a5c: not ecx */
	m->esi = (DWORD)(m->ebp + 0x98u);	/* 457a5e: lea esi, [ebp + 0x98] */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 457a64: sub edi, ecx */
	m->eax = m->ecx;	/* 457a66: mov eax, ecx */
	M32((DWORD)(m->esp + 0x24u)) = m->esi;	/* 457a68: mov dword ptr [esp + 0x24], esi */
	m->esi = m->edi;	/* 457a6c: mov esi, edi */
	m->edi = M32((DWORD)(m->esp + 0x24u));	/* 457a6e: mov edi, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 457a72: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 457a75: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 457a77: mov ecx, eax */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 457a79: mov eax, dword ptr [esp + 0x38] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 457a7d: and ecx, 3 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 457a80: cmp eax, ebx */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 457a82: rep movsb byte ptr es:[edi], byte ptr [esi] */
	if (m->sf != m->of) goto L_457a92;	/* 457a84: jl 0x457a92 */
	m->esi = M32((DWORD)(m->esp + 0x28u));	/* 457a86: mov esi, dword ptr [esp + 0x28] */
	M32((DWORD)(m->ebp + 0x104u)) = m->eax;	/* 457a8a: mov dword ptr [ebp + 0x104], eax */
	goto L_457aaf;	/* 457a90: jmp 0x457aaf */
L_457a92:
	m->esi = M32((DWORD)(m->esp + 0x28u));	/* 457a92: mov esi, dword ptr [esp + 0x28] */
	m->ecx = M32((DWORD)(m->esi + 0x202e8d0u));	/* 457a96: mov ecx, dword ptr [esi + 0x202e8d0] */
	M32((DWORD)(m->ebp + 0x104u)) = m->ecx;	/* 457a9c: mov dword ptr [ebp + 0x104], ecx */
	m->eax = M32((DWORD)(m->esi + 0x202e8d0u));	/* 457aa2: mov eax, dword ptr [esi + 0x202e8d0] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 457aa8: inc eax */
	M32((DWORD)(m->esi + 0x202e8d0u)) = m->eax;	/* 457aa9: mov dword ptr [esi + 0x202e8d0], eax */
L_457aaf:
	m->edi = M32((DWORD)(m->esp + 0x40u));	/* 457aaf: mov edi, dword ptr [esp + 0x40] */
	m->eax = M32((DWORD)(m->esp + 0x3cu));	/* 457ab3: mov eax, dword ptr [esp + 0x3c] */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 457ab7: mov ecx, dword ptr [esp + 0x2c] */
	M32((DWORD)(m->ebp + 0x108u)) = m->edx;	/* 457abb: mov dword ptr [ebp + 0x108], edx */
	m->edx = M32((DWORD)(m->edi + 0x0u));	/* 457ac1: mov edx, dword ptr [edi] */
	M32((DWORD)(m->ebp + 0x10cu)) = m->edx;	/* 457ac3: mov dword ptr [ebp + 0x10c], edx */
	M32((DWORD)(m->ebp + 0x110u)) = m->eax;	/* 457ac9: mov dword ptr [ebp + 0x110], eax */
	m->eax = M32((DWORD)(m->ecx + 0x44u));	/* 457acf: mov eax, dword ptr [ecx + 0x44] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 457ad2: cmp eax, ebx */
	M32((DWORD)(m->ebp + 0x114u)) = m->eax;	/* 457ad4: mov dword ptr [ebp + 0x114], eax */
	if (m->sf != m->of) goto L_457ae1;	/* 457ada: jl 0x457ae1 */
	{ DWORD a_ = m->eax, b_ = 0x9u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 457adc: cmp eax, 9 */
	if (m->sf != m->of) goto L_457ae7;	/* 457adf: jl 0x457ae7 */
L_457ae1:
	M32((DWORD)(m->ebp + 0x114u)) = m->ebx;	/* 457ae1: mov dword ptr [ebp + 0x114], ebx */
L_457ae7:
	m->ecx = M32((DWORD)(m->ecx + 0x48u));	/* 457ae7: mov ecx, dword ptr [ecx + 0x48] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 457aea: push ebx */
	M32((DWORD)(m->ebp + 0x118u)) = m->ecx;	/* 457aeb: mov dword ptr [ebp + 0x118], ecx */
	m->edx = M32((DWORD)(m->edi + 0x4u));	/* 457af1: mov edx, dword ptr [edi + 4] */
	M32((DWORD)(m->ebp + 0x11cu)) = m->edx;	/* 457af4: mov dword ptr [ebp + 0x11c], edx */
	M32((DWORD)(m->ebp + 0x120u)) = m->ebx;	/* 457afa: mov dword ptr [ebp + 0x120], ebx */
	M32((DWORD)(m->ebp + 0x124u)) = 0x3f800000u;	/* 457b00: mov dword ptr [ebp + 0x124], 0x3f800000 */
	m->eax = M32((DWORD)(m->ebp + 0x1cu));	/* 457b0a: mov eax, dword ptr [ebp + 0x1c] */
	M32((DWORD)(m->ebp + 0x128u)) = m->eax;	/* 457b0d: mov dword ptr [ebp + 0x128], eax */
	m->ecx = M32((DWORD)(m->ebp + 0x20u));	/* 457b13: mov ecx, dword ptr [ebp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 457b16: mov eax, dword ptr [esp + 0x38] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 457b1a: xor edx, edx */
	M32((DWORD)(m->ebp + 0x12cu)) = m->ecx;	/* 457b1c: mov dword ptr [ebp + 0x12c], ecx */
	M32((DWORD)(m->ebp + 0x130u)) = m->edx;	/* 457b22: mov dword ptr [ebp + 0x130], edx */
	M32((DWORD)(m->ebp + 0x134u)) = m->edx;	/* 457b28: mov dword ptr [ebp + 0x134], edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 457b2e: push eax */
	M32((DWORD)(m->ebp + 0x138u)) = m->edx;	/* 457b2f: mov dword ptr [ebp + 0x138], edx */
	m->ecx = m->esi;	/* 457b35: mov ecx, esi */
	M32((DWORD)(m->ebp + 0x13cu)) = m->edx;	/* 457b37: mov dword ptr [ebp + 0x13c], edx */
	M32((DWORD)(m->ebp + 0x140u)) = 0xffffffffu;	/* 457b3d: mov dword ptr [ebp + 0x140], 0xffffffff */
	M32((DWORD)(m->ebp + 0x144u)) = m->ebx;	/* 457b47: mov dword ptr [ebp + 0x144], ebx */
	m->esp -= 4; M32(m->esp) = 0x457b52u; native_call(m, 0x45e810u);	/* 457b4d: call 0x45e810 */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 457b52: mov ecx, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 457b56: push ecx */
	m->ecx = m->esi;	/* 457b57: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x457b5eu; native_call(m, 0x45ebc0u);	/* 457b59: call 0x45ebc0 */
	m->eax = (DWORD)(m->ebp + 0x154u);	/* 457b5e: lea eax, [ebp + 0x154] */
	{ DWORD a_ = m->edi, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 457b64: add edi, 8 */
	M32((DWORD)(m->ebp + 0x14cu)) = 0x1u;	/* 457b67: mov dword ptr [ebp + 0x14c], 1 */
	M32((DWORD)(m->ebp + 0x150u)) = m->ebx;	/* 457b71: mov dword ptr [ebp + 0x150], ebx */
	m->ecx = M32((DWORD)(m->edi + 0x0u));	/* 457b77: mov ecx, dword ptr [edi] */
	m->edx = m->eax;	/* 457b79: mov edx, eax */
	M32((DWORD)(m->edx + 0x0u)) = m->ecx;	/* 457b7b: mov dword ptr [edx], ecx */
	m->ecx = M32((DWORD)(m->edi + 0x4u));	/* 457b7d: mov ecx, dword ptr [edi + 4] */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 457b80: mov dword ptr [edx + 4], ecx */
	m->ecx = M32((DWORD)(m->edi + 0x8u));	/* 457b83: mov ecx, dword ptr [edi + 8] */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 457b86: mov dword ptr [edx + 8], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x40u));	/* 457b89: mov ecx, dword ptr [esp + 0x40] */
	m->edx = M32((DWORD)(m->ecx + 0x14u));	/* 457b8d: mov edx, dword ptr [ecx + 0x14] */
	M32((DWORD)(m->ebp + 0x160u)) = m->edx;	/* 457b90: mov dword ptr [ebp + 0x160], edx */
	m->ecx = M32((DWORD)(m->ecx + 0x18u));	/* 457b96: mov ecx, dword ptr [ecx + 0x18] */
	M32((DWORD)(m->ebp + 0x164u)) = m->ecx;	/* 457b99: mov dword ptr [ebp + 0x164], ecx */
	m->ecx = m->eax;	/* 457b9f: mov ecx, eax */
	m->edx = (DWORD)(m->ebp + 0x180u);	/* 457ba1: lea edx, [ebp + 0x180] */
	M32((DWORD)(m->ebp + 0x168u)) = m->ebx;	/* 457ba7: mov dword ptr [ebp + 0x168], ebx */
	m->edi = M32((DWORD)(m->ecx + 0x0u));	/* 457bad: mov edi, dword ptr [ecx] */
	M32((DWORD)(m->ebp + 0x16cu)) = m->ebx;	/* 457baf: mov dword ptr [ebp + 0x16c], ebx */
	M32((DWORD)(m->edx + 0x0u)) = m->edi;	/* 457bb5: mov dword ptr [edx], edi */
	M32((DWORD)(m->ebp + 0x170u)) = m->ebx;	/* 457bb7: mov dword ptr [ebp + 0x170], ebx */
	m->edi = M32((DWORD)(m->ecx + 0x4u));	/* 457bbd: mov edi, dword ptr [ecx + 4] */
	M32((DWORD)(m->ebp + 0x174u)) = m->ebx;	/* 457bc0: mov dword ptr [ebp + 0x174], ebx */
	M32((DWORD)(m->edx + 0x4u)) = m->edi;	/* 457bc6: mov dword ptr [edx + 4], edi */
	M32((DWORD)(m->ebp + 0x178u)) = m->ebx;	/* 457bc9: mov dword ptr [ebp + 0x178], ebx */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 457bcf: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->ebp + 0x17cu)) = m->ebx;	/* 457bd2: mov dword ptr [ebp + 0x17c], ebx */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 457bd8: mov dword ptr [edx + 8], ecx */
	m->ecx = M32((DWORD)(m->ebp + 0x164u));	/* 457bdb: mov ecx, dword ptr [ebp + 0x164] */
	m->edx = M32((DWORD)(m->ebp + 0x160u));	/* 457be1: mov edx, dword ptr [ebp + 0x160] */
	M32((DWORD)(m->ebp + 0x190u)) = m->ecx;	/* 457be7: mov dword ptr [ebp + 0x190], ecx */
	m->ecx = m->eax;	/* 457bed: mov ecx, eax */
	M32((DWORD)(m->ebp + 0x18cu)) = m->edx;	/* 457bef: mov dword ptr [ebp + 0x18c], edx */
	m->edx = (DWORD)(m->ebp + 0x1acu);	/* 457bf5: lea edx, [ebp + 0x1ac] */
	M32((DWORD)(m->ebp + 0x194u)) = m->ebx;	/* 457bfb: mov dword ptr [ebp + 0x194], ebx */
	m->edi = M32((DWORD)(m->ecx + 0x0u));	/* 457c01: mov edi, dword ptr [ecx] */
	M32((DWORD)(m->ebp + 0x198u)) = m->ebx;	/* 457c03: mov dword ptr [ebp + 0x198], ebx */
	M32((DWORD)(m->edx + 0x0u)) = m->edi;	/* 457c09: mov dword ptr [edx], edi */
	M32((DWORD)(m->ebp + 0x19cu)) = m->ebx;	/* 457c0b: mov dword ptr [ebp + 0x19c], ebx */
	m->edi = M32((DWORD)(m->ecx + 0x4u));	/* 457c11: mov edi, dword ptr [ecx + 4] */
	M32((DWORD)(m->ebp + 0x1a0u)) = m->ebx;	/* 457c14: mov dword ptr [ebp + 0x1a0], ebx */
	M32((DWORD)(m->edx + 0x4u)) = m->edi;	/* 457c1a: mov dword ptr [edx + 4], edi */
	M32((DWORD)(m->ebp + 0x1a4u)) = m->ebx;	/* 457c1d: mov dword ptr [ebp + 0x1a4], ebx */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 457c23: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->ebp + 0x1a8u)) = m->ebx;	/* 457c26: mov dword ptr [ebp + 0x1a8], ebx */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 457c2c: mov dword ptr [edx + 8], ecx */
	m->edx = M32((DWORD)(m->ebp + 0x160u));	/* 457c2f: mov edx, dword ptr [ebp + 0x160] */
	m->ecx = M32((DWORD)(m->ebp + 0x164u));	/* 457c35: mov ecx, dword ptr [ebp + 0x164] */
	M32((DWORD)(m->ebp + 0x1b8u)) = m->edx;	/* 457c3b: mov dword ptr [ebp + 0x1b8], edx */
	M32((DWORD)(m->ebp + 0x1bcu)) = m->ecx;	/* 457c41: mov dword ptr [ebp + 0x1bc], ecx */
	M32((DWORD)(m->ebp + 0x1c0u)) = m->ebx;	/* 457c47: mov dword ptr [ebp + 0x1c0], ebx */
	M32((DWORD)(m->ebp + 0x1c4u)) = m->ebx;	/* 457c4d: mov dword ptr [ebp + 0x1c4], ebx */
	M32((DWORD)(m->ebp + 0x1c8u)) = m->ebx;	/* 457c53: mov dword ptr [ebp + 0x1c8], ebx */
	m->ecx = m->eax;	/* 457c59: mov ecx, eax */
	m->edx = (DWORD)(m->ebp + 0x1d4u);	/* 457c5b: lea edx, [ebp + 0x1d4] */
	M32((DWORD)(m->ebp + 0x1ccu)) = m->ebx;	/* 457c61: mov dword ptr [ebp + 0x1cc], ebx */
	M32((DWORD)(m->ebp + 0x1d0u)) = m->ebx;	/* 457c67: mov dword ptr [ebp + 0x1d0], ebx */
	m->edi = M32((DWORD)(m->ecx + 0x0u));	/* 457c6d: mov edi, dword ptr [ecx] */
	M32((DWORD)(m->ebp + 0x1e8u)) = m->ebx;	/* 457c6f: mov dword ptr [ebp + 0x1e8], ebx */
	M32((DWORD)(m->edx + 0x0u)) = m->edi;	/* 457c75: mov dword ptr [edx], edi */
	M32((DWORD)(m->ebp + 0x1ecu)) = m->ebx;	/* 457c77: mov dword ptr [ebp + 0x1ec], ebx */
	m->edi = M32((DWORD)(m->ecx + 0x4u));	/* 457c7d: mov edi, dword ptr [ecx + 4] */
	M32((DWORD)(m->ebp + 0x1f0u)) = m->ebx;	/* 457c80: mov dword ptr [ebp + 0x1f0], ebx */
	M32((DWORD)(m->edx + 0x4u)) = m->edi;	/* 457c86: mov dword ptr [edx + 4], edi */
	m->edi = 0x5u;	/* 457c89: mov edi, 5 */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 457c8e: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 457c91: mov dword ptr [edx + 8], ecx */
	m->edx = M32((DWORD)(m->ebp + 0x160u));	/* 457c94: mov edx, dword ptr [ebp + 0x160] */
	m->ecx = M32((DWORD)(m->ebp + 0x164u));	/* 457c9a: mov ecx, dword ptr [ebp + 0x164] */
	M32((DWORD)(m->ebp + 0x1e0u)) = m->edx;	/* 457ca0: mov dword ptr [ebp + 0x1e0], edx */
	M32((DWORD)(m->ebp + 0x1e4u)) = m->ecx;	/* 457ca6: mov dword ptr [ebp + 0x1e4], ecx */
	M32((DWORD)(m->ebp + 0x1f4u)) = m->ebx;	/* 457cac: mov dword ptr [ebp + 0x1f4], ebx */
	m->edx = (DWORD)(m->ebp + 0x360u);	/* 457cb2: lea edx, [ebp + 0x360] */
	m->ecx = (DWORD)(m->ebp + 0x1fcu);	/* 457cb8: lea ecx, [ebp + 0x1fc] */
L_457cbe:
	M32((DWORD)(m->ecx + 0xfffffffcu)) = m->ebx;	/* 457cbe: mov dword ptr [ecx - 4], ebx */
	M32((DWORD)(m->ecx + 0x0u)) = m->ebx;	/* 457cc1: mov dword ptr [ecx], ebx */
	M32((DWORD)(m->edx + 0x0u)) = 0xffffffffu;	/* 457cc3: mov dword ptr [edx], 0xffffffff */
	{ DWORD a_ = m->edx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 457cc9: add edx, 4 */
	{ DWORD a_ = m->ecx, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 457ccc: add ecx, 0x20 */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 457ccf: dec edi */
	if (!m->zf) goto L_457cbe;	/* 457cd0: jne 0x457cbe */
	M32((DWORD)(m->ebp + 0x374u)) = m->ebx;	/* 457cd2: mov dword ptr [ebp + 0x374], ebx */
	m->ecx = M32((DWORD)(0xa0e7e8u));	/* 457cd8: mov ecx, dword ptr [0xa0e7e8] */
	m->edx = (DWORD)(m->ebp + 0x378u);	/* 457cde: lea edx, [ebp + 0x378] */
	M32((DWORD)(m->ebp + 0x378u)) = m->ecx;	/* 457ce4: mov dword ptr [ebp + 0x378], ecx */
	m->ecx = M32((DWORD)(0xa0e7ecu));	/* 457cea: mov ecx, dword ptr [0xa0e7ec] */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 457cf0: mov dword ptr [edx + 4], ecx */
	m->ecx = M32((DWORD)(0xa0e7f0u));	/* 457cf3: mov ecx, dword ptr [0xa0e7f0] */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 457cf9: mov dword ptr [edx + 8], ecx */
	m->ecx = M32((DWORD)(0xa0e7e8u));	/* 457cfc: mov ecx, dword ptr [0xa0e7e8] */
	m->edx = (DWORD)(m->ebp + 0x384u);	/* 457d02: lea edx, [ebp + 0x384] */
	M32((DWORD)(m->ebp + 0x384u)) = m->ecx;	/* 457d08: mov dword ptr [ebp + 0x384], ecx */
	m->ecx = M32((DWORD)(0xa0e7ecu));	/* 457d0e: mov ecx, dword ptr [0xa0e7ec] */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 457d14: mov dword ptr [edx + 4], ecx */
	m->ecx = M32((DWORD)(0xa0e7f0u));	/* 457d17: mov ecx, dword ptr [0xa0e7f0] */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 457d1d: mov dword ptr [edx + 8], ecx */
	M32((DWORD)(m->ebp + 0x3e8u)) = 0x43fa0000u;	/* 457d20: mov dword ptr [ebp + 0x3e8], 0x43fa0000 */
	M32((DWORD)(m->ebp + 0x3ecu)) = m->ebx;	/* 457d2a: mov dword ptr [ebp + 0x3ec], ebx */
	M32((DWORD)(m->ebp + 0x3f0u)) = m->ebx;	/* 457d30: mov dword ptr [ebp + 0x3f0], ebx */
	m->edx = M32((DWORD)(m->ebp + 0x104u));	/* 457d36: mov edx, dword ptr [ebp + 0x104] */
	{ DWORD a_ = m->edx, b_ = 0x80000001u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 457d3c: and edx, 0x80000001 */
	if (!m->sf) goto L_457d49;	/* 457d42: jns 0x457d49 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 457d44: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffffeu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 457d45: or edx, 0xfffffffe */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 457d48: inc edx */
L_457d49:
	{ DWORD a_ = m->edx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 457d49: cmp edx, 1 */
	if (!m->zf) goto L_457d58;	/* 457d4c: jne 0x457d58 */
	M32((DWORD)(m->ebp + 0x3f0u)) = 0x4000u;	/* 457d4e: mov dword ptr [ebp + 0x3f0], 0x4000 */
L_457d58:
	M32((DWORD)(m->ebp + 0x3f4u)) = m->ebx;	/* 457d58: mov dword ptr [ebp + 0x3f4], ebx */
	M32((DWORD)(m->ebp + 0x3f8u)) = m->ebx;	/* 457d5e: mov dword ptr [ebp + 0x3f8], ebx */
	M32((DWORD)(m->ebp + 0x3fcu)) = m->ebx;	/* 457d64: mov dword ptr [ebp + 0x3fc], ebx */
	M32((DWORD)(m->ebp + 0x400u)) = m->ebx;	/* 457d6a: mov dword ptr [ebp + 0x400], ebx */
	M32((DWORD)(m->ebp + 0x44cu)) = m->ebx;	/* 457d70: mov dword ptr [ebp + 0x44c], ebx */
	M32((DWORD)(m->ebp + 0x450u)) = m->ebx;	/* 457d76: mov dword ptr [ebp + 0x450], ebx */
	M32((DWORD)(m->ebp + 0x454u)) = m->ebx;	/* 457d7c: mov dword ptr [ebp + 0x454], ebx */
	M32((DWORD)(m->ebp + 0x458u)) = m->ebx;	/* 457d82: mov dword ptr [ebp + 0x458], ebx */
	M32((DWORD)(m->ebp + 0x45cu)) = m->ebx;	/* 457d88: mov dword ptr [ebp + 0x45c], ebx */
	M32((DWORD)(m->ebp + 0x460u)) = m->ebx;	/* 457d8e: mov dword ptr [ebp + 0x460], ebx */
	M32((DWORD)(m->ebp + 0x464u)) = m->ebx;	/* 457d94: mov dword ptr [ebp + 0x464], ebx */
	M32((DWORD)(m->ebp + 0x468u)) = m->ebx;	/* 457d9a: mov dword ptr [ebp + 0x468], ebx */
	M32((DWORD)(m->ebp + 0x46cu)) = m->ebx;	/* 457da0: mov dword ptr [ebp + 0x46c], ebx */
	M32((DWORD)(m->ebp + 0x470u)) = m->ebx;	/* 457da6: mov dword ptr [ebp + 0x470], ebx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 457dac: or ecx, 0xffffffff */
	M32((DWORD)(m->ebp + 0x474u)) = m->ebx;	/* 457daf: mov dword ptr [ebp + 0x474], ebx */
	m->edi = M32((DWORD)(m->esp + 0x34u));	/* 457db5: mov edi, dword ptr [esp + 0x34] */
	M32((DWORD)(m->ebp + 0x478u)) = m->ecx;	/* 457db9: mov dword ptr [ebp + 0x478], ecx */
	M32((DWORD)(m->ebp + 0x47cu)) = m->ebx;	/* 457dbf: mov dword ptr [ebp + 0x47c], ebx */
	M32((DWORD)(m->ebp + 0x480u)) = m->ebx;	/* 457dc5: mov dword ptr [ebp + 0x480], ebx */
	M32((DWORD)(m->ebp + 0x484u)) = m->ebx;	/* 457dcb: mov dword ptr [ebp + 0x484], ebx */
	M32((DWORD)(m->ebp + 0x488u)) = m->ebx;	/* 457dd1: mov dword ptr [ebp + 0x488], ebx */
	m->edx = 0x3f800000u;	/* 457dd7: mov edx, 0x3f800000 */
	M32((DWORD)(m->ebp + 0x48cu)) = m->ebx;	/* 457ddc: mov dword ptr [ebp + 0x48c], ebx */
	M32((DWORD)(m->ebp + 0x490u)) = m->edx;	/* 457de2: mov dword ptr [ebp + 0x490], edx */
	M32((DWORD)(m->ebp + 0x494u)) = m->ebx;	/* 457de8: mov dword ptr [ebp + 0x494], ebx */
	M32((DWORD)(m->ebp + 0x498u)) = m->ebx;	/* 457dee: mov dword ptr [ebp + 0x498], ebx */
	{ DWORD a_ = m->edi, b_ = M32((DWORD)(m->esi + 0x202e8d8u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 457df4: cmp edi, dword ptr [esi + 0x202e8d8] */
	if (!m->zf) goto L_457e04;	/* 457dfa: jne 0x457e04 */
	M32((DWORD)(m->ebp + 0x49cu)) = m->ebx;	/* 457dfc: mov dword ptr [ebp + 0x49c], ebx */
	goto L_457e0e;	/* 457e02: jmp 0x457e0e */
L_457e04:
	M32((DWORD)(m->ebp + 0x49cu)) = 0x1u;	/* 457e04: mov dword ptr [ebp + 0x49c], 1 */
L_457e0e:
	M32((DWORD)(m->ebp + 0x4a0u)) = m->ebx;	/* 457e0e: mov dword ptr [ebp + 0x4a0], ebx */
	M32((DWORD)(m->ebp + 0x4a4u)) = m->ebx;	/* 457e14: mov dword ptr [ebp + 0x4a4], ebx */
	M32((DWORD)(m->ebp + 0x4a8u)) = m->ebx;	/* 457e1a: mov dword ptr [ebp + 0x4a8], ebx */
	M32((DWORD)(m->ebp + 0x4acu)) = m->edx;	/* 457e20: mov dword ptr [ebp + 0x4ac], edx */
	M32((DWORD)(m->ebp + 0x4b0u)) = m->edx;	/* 457e26: mov dword ptr [ebp + 0x4b0], edx */
	M32((DWORD)(m->ebp + 0x4b4u)) = m->ebx;	/* 457e2c: mov dword ptr [ebp + 0x4b4], ebx */
	M32((DWORD)(m->ebp + 0x4b8u)) = m->ebx;	/* 457e32: mov dword ptr [ebp + 0x4b8], ebx */
	M32((DWORD)(m->ebp + 0x4bcu)) = m->ecx;	/* 457e38: mov dword ptr [ebp + 0x4bc], ecx */
	M32((DWORD)(m->ebp + 0x4c0u)) = m->ecx;	/* 457e3e: mov dword ptr [ebp + 0x4c0], ecx */
	M32((DWORD)(m->ebp + 0x4c4u)) = m->ecx;	/* 457e44: mov dword ptr [ebp + 0x4c4], ecx */
	M32((DWORD)(m->ebp + 0x4d0u)) = m->ecx;	/* 457e4a: mov dword ptr [ebp + 0x4d0], ecx */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 457e50: mov edx, dword ptr [eax] */
	m->ecx = (DWORD)(m->ebp + 0x4e0u);	/* 457e52: lea ecx, [ebp + 0x4e0] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 457e58: push edi */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 457e59: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 457e5b: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 457e5e: mov dword ptr [ecx + 4], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 457e61: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 457e64: mov dword ptr [ecx + 8], eax */
	M32((DWORD)(m->ebp + 0x4ecu)) = m->ebx;	/* 457e67: mov dword ptr [ebp + 0x4ec], ebx */
	M8((DWORD)(m->ebp + 0x4f4u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 457e6d: mov byte ptr [ebp + 0x4f4], bl */
	M32((DWORD)(m->ebp + 0x534u)) = 0xc61c4000u;	/* 457e73: mov dword ptr [ebp + 0x534], 0xc61c4000 */
	M32((DWORD)(m->ebp + 0x538u)) = 0xffffffffu;	/* 457e7d: mov dword ptr [ebp + 0x538], 0xffffffff */
	M32((DWORD)(m->ebp + 0x53cu)) = m->ebx;	/* 457e87: mov dword ptr [ebp + 0x53c], ebx */
	M32((DWORD)(m->ebp + 0x540u)) = m->ebx;	/* 457e8d: mov dword ptr [ebp + 0x540], ebx */
	M32((DWORD)(m->ebp + 0x544u)) = m->ebx;	/* 457e93: mov dword ptr [ebp + 0x544], ebx */
	M32((DWORD)(m->ebp + 0x548u)) = 0x3f800000u;	/* 457e99: mov dword ptr [ebp + 0x548], 0x3f800000 */
	m->ecx = m->esi;	/* 457ea3: mov ecx, esi */
	M32((DWORD)(m->ebp + 0x54cu)) = m->ebx;	/* 457ea5: mov dword ptr [ebp + 0x54c], ebx */
	m->esp -= 4; M32(m->esp) = 0x457eb0u; native_call(m, 0x45e1f0u);	/* 457eab: call 0x45e1f0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 457eb0: push edi */
	m->ecx = m->esi;	/* 457eb1: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x457eb8u; native_call(m, 0x45e2c0u);	/* 457eb3: call 0x45e2c0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 457eb8: push edi */
	m->ecx = m->esi;	/* 457eb9: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x457ec0u; native_call(m, 0x45e390u);	/* 457ebb: call 0x45e390 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 457ec0: push edi */
	m->ecx = m->esi;	/* 457ec1: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x457ec8u; native_call(m, 0x45e460u);	/* 457ec3: call 0x45e460 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 457ec8: push edi */
	m->ecx = m->esi;	/* 457ec9: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x457ed0u; native_call(m, 0x45e530u);	/* 457ecb: call 0x45e530 */
	M32((DWORD)(m->esp + 0x34u)) = 0x5u;	/* 457ed0: mov dword ptr [esp + 0x34], 5 */
L_457ed8:
	m->ecx = M32((DWORD)(m->ebp + 0x49cu));	/* 457ed8: mov ecx, dword ptr [ebp + 0x49c] */
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 457ede: mov edx, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 457ee2: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 457ee3: push edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 457ee4: push edi */
	m->ecx = m->esi;	/* 457ee5: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x457eecu; native_call(m, 0x45e600u);	/* 457ee7: call 0x45e600 */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 457eec: mov eax, dword ptr [esp + 0x34] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 457ef0: dec eax */
	M32((DWORD)(m->esp + 0x34u)) = m->eax;	/* 457ef1: mov dword ptr [esp + 0x34], eax */
	if (!m->sf) goto L_457ed8;	/* 457ef5: jns 0x457ed8 */
	M32((DWORD)(m->ebp + 0x87bcu)) = m->ebx;	/* 457ef7: mov dword ptr [ebp + 0x87bc], ebx */
	M32((DWORD)(m->ebp + 0x87c0u)) = m->ebx;	/* 457efd: mov dword ptr [ebp + 0x87c0], ebx */
	M32((DWORD)(m->ebp + 0x87c4u)) = m->ebx;	/* 457f03: mov dword ptr [ebp + 0x87c4], ebx */
	M32((DWORD)(m->ebp + 0x87c8u)) = m->ebx;	/* 457f09: mov dword ptr [ebp + 0x87c8], ebx */
	M32((DWORD)(m->ebp + 0x87ccu)) = m->ebx;	/* 457f0f: mov dword ptr [ebp + 0x87cc], ebx */
	M32((DWORD)(m->ebp + 0x87d0u)) = m->ebx;	/* 457f15: mov dword ptr [ebp + 0x87d0], ebx */
	M32((DWORD)(m->ebp + 0x87d4u)) = m->ebx;	/* 457f1b: mov dword ptr [ebp + 0x87d4], ebx */
	M32((DWORD)(m->ebp + 0x87d8u)) = m->ebx;	/* 457f21: mov dword ptr [ebp + 0x87d8], ebx */
	M32((DWORD)(m->ebp + 0x87dcu)) = m->ebx;	/* 457f27: mov dword ptr [ebp + 0x87dc], ebx */
	M32((DWORD)(m->ebp + 0x87e0u)) = m->ebx;	/* 457f2d: mov dword ptr [ebp + 0x87e0], ebx */
	M32((DWORD)(m->ebp + 0x87e8u)) = m->ebx;	/* 457f33: mov dword ptr [ebp + 0x87e8], ebx */
	M32((DWORD)(m->ebp + 0x87ecu)) = m->ebx;	/* 457f39: mov dword ptr [ebp + 0x87ec], ebx */
	M32((DWORD)(m->ebp + 0x87f0u)) = m->ebx;	/* 457f3f: mov dword ptr [ebp + 0x87f0], ebx */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 457f45: or eax, 0xffffffff */
	M32((DWORD)(m->ebp + 0x87f4u)) = m->ebx;	/* 457f48: mov dword ptr [ebp + 0x87f4], ebx */
	M32((DWORD)(m->ebp + 0x87f8u)) = m->eax;	/* 457f4e: mov dword ptr [ebp + 0x87f8], eax */
	M32((DWORD)(m->ebp + 0x87fcu)) = m->eax;	/* 457f54: mov dword ptr [ebp + 0x87fc], eax */
	M32((DWORD)(m->ebp + 0x8800u)) = m->ebx;	/* 457f5a: mov dword ptr [ebp + 0x8800], ebx */
	M32((DWORD)(m->ebp + 0x8804u)) = m->ebx;	/* 457f60: mov dword ptr [ebp + 0x8804], ebx */
	M32((DWORD)(m->ebp + 0x8808u)) = m->eax;	/* 457f66: mov dword ptr [ebp + 0x8808], eax */
	M32((DWORD)(m->ebp + 0x880cu)) = m->ebx;	/* 457f6c: mov dword ptr [ebp + 0x880c], ebx */
	M32((DWORD)(m->ebp + 0x8810u)) = m->eax;	/* 457f72: mov dword ptr [ebp + 0x8810], eax */
	M32((DWORD)(m->ebp + 0x8814u)) = m->eax;	/* 457f78: mov dword ptr [ebp + 0x8814], eax */
	M32((DWORD)(m->ebp + 0x8818u)) = m->eax;	/* 457f7e: mov dword ptr [ebp + 0x8818], eax */
	M32((DWORD)(m->ebp + 0x881cu)) = m->eax;	/* 457f84: mov dword ptr [ebp + 0x881c], eax */
	M32((DWORD)(m->ebp + 0x8820u)) = m->eax;	/* 457f8a: mov dword ptr [ebp + 0x8820], eax */
	M32((DWORD)(m->ebp + 0x8824u)) = m->ebx;	/* 457f90: mov dword ptr [ebp + 0x8824], ebx */
	M32((DWORD)(m->ebp + 0x8828u)) = m->ebx;	/* 457f96: mov dword ptr [ebp + 0x8828], ebx */
	M32((DWORD)(m->ebp + 0x882cu)) = m->ebx;	/* 457f9c: mov dword ptr [ebp + 0x882c], ebx */
	M32((DWORD)(m->ebp + 0x8830u)) = m->ebx;	/* 457fa2: mov dword ptr [ebp + 0x8830], ebx */
	M32((DWORD)(m->ebp + 0x8834u)) = m->ebx;	/* 457fa8: mov dword ptr [ebp + 0x8834], ebx */
	m->edx = M32((DWORD)(0xa0e7e8u));	/* 457fae: mov edx, dword ptr [0xa0e7e8] */
	m->ecx = (DWORD)(m->ebp + 0x8838u);	/* 457fb4: lea ecx, [ebp + 0x8838] */
	M32((DWORD)(m->ebp + 0x8838u)) = m->edx;	/* 457fba: mov dword ptr [ebp + 0x8838], edx */
	m->edx = M32((DWORD)(0xa0e7ecu));	/* 457fc0: mov edx, dword ptr [0xa0e7ec] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 457fc6: mov dword ptr [ecx + 4], edx */
	m->edx = M32((DWORD)(0xa0e7f0u));	/* 457fc9: mov edx, dword ptr [0xa0e7f0] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 457fcf: mov dword ptr [ecx + 8], edx */
	M32((DWORD)(m->ebp + 0x8844u)) = m->ebx;	/* 457fd2: mov dword ptr [ebp + 0x8844], ebx */
	M32((DWORD)(m->ebp + 0x8848u)) = 0x44bb8000u;	/* 457fd8: mov dword ptr [ebp + 0x8848], 0x44bb8000 */
	M32((DWORD)(m->ebp + 0x884cu)) = m->ebx;	/* 457fe2: mov dword ptr [ebp + 0x884c], ebx */
	M32((DWORD)(m->ebp + 0x8850u)) = m->ebx;	/* 457fe8: mov dword ptr [ebp + 0x8850], ebx */
	M32((DWORD)(m->ebp + 0x8854u)) = m->ebx;	/* 457fee: mov dword ptr [ebp + 0x8854], ebx */
	m->edx = M32((DWORD)(0xa0e7e8u));	/* 457ff4: mov edx, dword ptr [0xa0e7e8] */
	m->ecx = (DWORD)(m->ebp + 0x885cu);	/* 457ffa: lea ecx, [ebp + 0x885c] */
	M32((DWORD)(m->ebp + 0x885cu)) = m->edx;	/* 458000: mov dword ptr [ebp + 0x885c], edx */
	m->edx = M32((DWORD)(0xa0e7ecu));	/* 458006: mov edx, dword ptr [0xa0e7ec] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 45800c: mov dword ptr [ecx + 4], edx */
	m->edx = M32((DWORD)(0xa0e7f0u));	/* 45800f: mov edx, dword ptr [0xa0e7f0] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 458015: mov dword ptr [ecx + 8], edx */
	M32((DWORD)(m->ebp + 0x8858u)) = m->ebx;	/* 458018: mov dword ptr [ebp + 0x8858], ebx */
	M32((DWORD)(m->ebp + 0x8868u)) = m->ebx;	/* 45801e: mov dword ptr [ebp + 0x8868], ebx */
	M32((DWORD)(m->ebp + 0x886cu)) = 0x3f800000u;	/* 458024: mov dword ptr [ebp + 0x886c], 0x3f800000 */
	M32((DWORD)(m->ebp + 0x8870u)) = m->eax;	/* 45802e: mov dword ptr [ebp + 0x8870], eax */
	m->ecx = M32((DWORD)(0xa0e7e8u));	/* 458034: mov ecx, dword ptr [0xa0e7e8] */
	m->eax = (DWORD)(m->ebp + 0x8874u);	/* 45803a: lea eax, [ebp + 0x8874] */
	M32((DWORD)(m->ebp + 0x8874u)) = m->ecx;	/* 458040: mov dword ptr [ebp + 0x8874], ecx */
	m->edx = M32((DWORD)(0xa0e7ecu));	/* 458046: mov edx, dword ptr [0xa0e7ec] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 45804c: mov dword ptr [eax + 4], edx */
	m->ecx = M32((DWORD)(0xa0e7f0u));	/* 45804f: mov ecx, dword ptr [0xa0e7f0] */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 458055: mov dword ptr [eax + 8], ecx */
	M32((DWORD)(m->ebp + 0x8880u)) = m->ebx;	/* 458058: mov dword ptr [ebp + 0x8880], ebx */
	M32((DWORD)(m->ebp + 0x8884u)) = m->ebx;	/* 45805e: mov dword ptr [ebp + 0x8884], ebx */
	M32((DWORD)(m->esi + m->edi*4 + 0x202ea80u)) = m->ebx;	/* 458064: mov dword ptr [esi + edi*4 + 0x202ea80], ebx */
	M32((DWORD)(m->esi + 0x202e8ecu)) = 0x1u;	/* 45806b: mov dword ptr [esi + 0x202e8ec], 1 */
	m->edi = M32(m->esp); m->esp += 4;	/* 458075: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 458076: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 458077: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 458078: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 458079: add esp, 0x20 */
	m->esp += 4 + 16; return;	/* 45807c: ret 0x10 */
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
