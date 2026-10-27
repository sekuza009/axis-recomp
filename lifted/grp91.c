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

static void lift_461540(X86 *m);

/* armc_461540 (0x461540), lifted by tools/lift.py */
static void lift_461540(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 461540: sub esp, 0x18 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 461543: push esi */
	m->esi = m->ecx;	/* 461544: mov esi, ecx */
	m->ecx = M32((DWORD)(m->esi + 0x234240du));	/* 461546: mov ecx, dword ptr [esi + 0x234240d] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46154c: test ecx, ecx */
	if (m->sf != m->of) goto L_4616d6;	/* 46154e: jl 0x4616d6 */
	m->eax = m->ecx;	/* 461554: mov eax, ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 461556: push ebx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 461557: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46155a: add eax, ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46155c: push ebp */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 46155d: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 461560: add eax, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 461562: push edi */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 461563: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 461566: add eax, ecx */
	m->ebx = M32((DWORD)(m->esp + 0x2cu));	/* 461568: mov ebx, dword ptr [esp + 0x2c] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46156c: test ebx, ebx */
	m->eax = (DWORD)(m->esi + m->eax*8 + 0x0u);	/* 46156e: lea eax, [esi + eax*8] */
	m->edx = (DWORD)(m->eax + 0x1eccbf0u);	/* 461571: lea edx, [eax + 0x1eccbf0] */
	m->ebp = M32((DWORD)(m->eax + 0x1eccbf0u));	/* 461577: mov ebp, dword ptr [eax + 0x1eccbf0] */
	m->edi = M32((DWORD)(m->edx + 0x4u));	/* 46157d: mov edi, dword ptr [edx + 4] */
	M32((DWORD)(m->esp + 0x20u)) = m->edi;	/* 461580: mov dword ptr [esp + 0x20], edi */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 461584: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 461587: mov dword ptr [esp + 0x24], edx */
	m->edx = M32((DWORD)(m->eax + 0x1eccbfcu));	/* 46158b: mov edx, dword ptr [eax + 0x1eccbfc] */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 461591: mov dword ptr [esp + 0x10], edx */
	m->edx = M32((DWORD)(m->eax + 0x1eccc00u));	/* 461595: mov edx, dword ptr [eax + 0x1eccc00] */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 46159b: mov dword ptr [esp + 0x14], edx */
	m->edx = M32((DWORD)(m->eax + 0x1eccbb4u));	/* 46159f: mov edx, dword ptr [eax + 0x1eccbb4] */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 4615a5: mov dword ptr [esp + 0x18], edx */
	if (m->sf == m->of) goto L_4615b7;	/* 4615a9: jge 0x4615b7 */
	m->edx = M32((DWORD)(m->eax + 0x1eccbb0u));	/* 4615ab: mov edx, dword ptr [eax + 0x1eccbb0] */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 4615b1: mov dword ptr [esp + 0x2c], edx */
	goto L_4615bb;	/* 4615b5: jmp 0x4615bb */
L_4615b7:
	M32((DWORD)(m->esp + 0x2cu)) = m->ebx;	/* 4615b7: mov dword ptr [esp + 0x2c], ebx */
L_4615bb:
	{ DWORD a_ = m->ecx, b_ = M32((DWORD)(m->esi + 0x2221fa0u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4615bb: cmp ecx, dword ptr [esi + 0x2221fa0] */
	if (!m->zf) goto L_4615cf;	/* 4615c1: jne 0x4615cf */
	M32((DWORD)(m->eax + 0x1eccf0cu)) = 0x0u;	/* 4615c3: mov dword ptr [eax + 0x1eccf0c], 0 */
	goto L_4615d9;	/* 4615cd: jmp 0x4615d9 */
L_4615cf:
	M32((DWORD)(m->eax + 0x1eccf0cu)) = 0x1u;	/* 4615cf: mov dword ptr [eax + 0x1eccf0c], 1 */
L_4615d9:
	m->edi = (DWORD)(m->esi + 0x1f36c8u);	/* 4615d9: lea edi, [esi + 0x1f36c8] */
	m->ecx = m->edi;	/* 4615df: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x4615e6u; native_call(m, 0x45ddc0u);	/* 4615e1: call 0x45ddc0 */
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 4615e6: mov eax, dword ptr [esi + 0x234240d] */
	m->ecx = m->eax;	/* 4615ec: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4615ee: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4615f1: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4615f3: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4615f6: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4615f8: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4615fb: add ecx, eax */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 4615fd: mov eax, dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 461601: fld dword ptr [esp + 0x10] */
	m->edx = (DWORD)(m->esi + m->ecx*8 + 0x1eccbf0u);	/* 461605: lea edx, [esi + ecx*8 + 0x1eccbf0] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 46160c: mov ecx, dword ptr [esp + 0x24] */
	M32((DWORD)(m->edx + 0x0u)) = m->ebp;	/* 461610: mov dword ptr [edx], ebp */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 461612: mov dword ptr [edx + 4], eax */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 461615: mov dword ptr [edx + 8], ecx */
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 461618: mov eax, dword ptr [esi + 0x234240d] */
	m->edx = m->eax;	/* 46161e: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 461620: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 461623: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 461625: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 461628: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 46162a: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46162d: add edx, eax */
	MF((DWORD)(m->esi + m->edx*8 + 0x1eccbfcu)) = (float)ST(0); FPOP();	/* 46162f: fstp dword ptr [esi + edx*8 + 0x1eccbfc] */
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 461636: mov eax, dword ptr [esi + 0x234240d] */
	m->ecx = m->eax;	/* 46163c: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46163e: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 461641: add ecx, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 461643: fld dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 461647: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46164a: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46164c: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46164f: add ecx, eax */
	{ DWORD a_ = m->ebx, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 461651: cmp ebx, 3 */
	MF((DWORD)(m->esi + m->ecx*8 + 0x1eccc00u)) = (float)ST(0); FPOP();	/* 461654: fstp dword ptr [esi + ecx*8 + 0x1eccc00] */
	if (m->zf || m->sf != m->of) goto L_461698;	/* 46165b: jle 0x461698 */
	m->ebx = M32((DWORD)(m->esp + 0x18u));	/* 46165d: mov ebx, dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esi + 0x234240du));	/* 461661: mov edx, dword ptr [esi + 0x234240d] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 461667: push ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 461668: push edx */
	m->ecx = m->edi;	/* 461669: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x461670u; native_call(m, 0x45e810u);	/* 46166b: call 0x45e810 */
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 461670: mov eax, dword ptr [esi + 0x234240d] */
	m->ecx = m->eax;	/* 461676: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 461678: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46167b: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46167d: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 461680: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 461682: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 461685: add ecx, eax */
	m->edx = M32((DWORD)(m->esi + m->ecx*8 + 0x1eccf0cu));	/* 461687: mov edx, dword ptr [esi + ecx*8 + 0x1eccf0c] */
	m->ecx = m->edi;	/* 46168e: mov ecx, edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 461690: push edx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 461691: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 461692: push eax */
	m->esp -= 4; M32(m->esp) = 0x461698u; native_call(m, 0x45e600u);	/* 461693: call 0x45e600 */
L_461698:
	m->ebx = M32((DWORD)(m->esp + 0x2cu));	/* 461698: mov ebx, dword ptr [esp + 0x2c] */
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 46169c: mov eax, dword ptr [esi + 0x234240d] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4616a2: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4616a3: push eax */
	m->ecx = m->edi;	/* 4616a4: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x4616abu; native_call(m, 0x45e810u);	/* 4616a6: call 0x45e810 */
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 4616ab: mov eax, dword ptr [esi + 0x234240d] */
	m->ecx = m->eax;	/* 4616b1: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4616b3: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4616b6: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4616b8: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4616bb: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4616bd: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4616c0: add ecx, eax */
	m->edx = M32((DWORD)(m->esi + m->ecx*8 + 0x1eccf0cu));	/* 4616c2: mov edx, dword ptr [esi + ecx*8 + 0x1eccf0c] */
	m->ecx = m->edi;	/* 4616c9: mov ecx, edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4616cb: push edx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4616cc: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4616cd: push eax */
	m->esp -= 4; M32(m->esp) = 0x4616d3u; native_call(m, 0x45e600u);	/* 4616ce: call 0x45e600 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4616d3: pop edi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4616d4: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4616d5: pop ebx */
L_4616d6:
	m->esi = M32(m->esp); m->esp += 4;	/* 4616d6: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4616d7: add esp, 0x18 */
	m->esp += 4 + 4; return;	/* 4616da: ret 4 */
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
