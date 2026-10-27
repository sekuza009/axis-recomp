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

static void lift_461410(X86 *m);
static void lift_461450(X86 *m);
static void lift_461490(X86 *m);
static void lift_4614d0(X86 *m);
static void lift_461510(X86 *m);
static void lift_46fed0(X86 *m);
static void lift_474210(X86 *m);
static void lift_4742f0(X86 *m);
static void lift_4613d0(X86 *m);

/* armc_setHeadIndex (0x4613d0), lifted by tools/lift.py */
static void lift_4613d0(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 4613d0: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4613d4: push esi */
	m->esi = M32((DWORD)(m->ecx + 0x15de6c8u));	/* 4613d5: mov esi, dword ptr [ecx + 0x15de6c8] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4613db: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->esi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 4613dc: idiv esi */
	m->eax = m->edx;	/* 4613de: mov eax, edx */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4613e0: add eax, esi */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4613e2: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->esi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 4613e3: idiv esi */
	m->eax = M32((DWORD)(m->ecx + 0x234240du));	/* 4613e5: mov eax, dword ptr [ecx + 0x234240d] */
	m->esi = M32(m->esp); m->esp += 4;	/* 4613eb: pop esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4613ec: test eax, eax */
	M32((DWORD)(m->ecx + 0x234244au)) = m->edx;	/* 4613ee: mov dword ptr [ecx + 0x234244a], edx */
	if (m->sf != m->of) goto L_461403;	/* 4613f4: jl 0x461403 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4613f6: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4613f7: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x1f36c8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4613f8: add ecx, 0x1f36c8 */
	m->esp -= 4; M32(m->esp) = 0x461403u; native_call(m, 0x473b10u);	/* 4613fe: call 0x473b10 */
L_461403:
	m->esp += 4 + 4; return;	/* 461403: ret 4 */
}

/* armc_setChestIndex (0x461410), lifted by tools/lift.py */
static void lift_461410(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 461410: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 461414: push esi */
	m->esi = M32((DWORD)(m->ecx + 0x15fff84u));	/* 461415: mov esi, dword ptr [ecx + 0x15fff84] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 46141b: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->esi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 46141c: idiv esi */
	m->eax = m->edx;	/* 46141e: mov eax, edx */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 461420: add eax, esi */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 461422: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->esi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 461423: idiv esi */
	m->eax = M32((DWORD)(m->ecx + 0x234240du));	/* 461425: mov eax, dword ptr [ecx + 0x234240d] */
	m->esi = M32(m->esp); m->esp += 4;	/* 46142b: pop esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46142c: test eax, eax */
	M32((DWORD)(m->ecx + 0x234244eu)) = m->edx;	/* 46142e: mov dword ptr [ecx + 0x234244e], edx */
	if (m->sf != m->of) goto L_461443;	/* 461434: jl 0x461443 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 461436: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 461437: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x1f36c8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 461438: add ecx, 0x1f36c8 */
	m->esp -= 4; M32(m->esp) = 0x461443u; native_call(m, 0x473c20u);	/* 46143e: call 0x473c20 */
L_461443:
	m->esp += 4 + 4; return;	/* 461443: ret 4 */
}

/* armc_setArmIndex (0x461450), lifted by tools/lift.py */
static void lift_461450(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 461450: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 461454: push esi */
	m->esi = M32((DWORD)(m->ecx + 0x163b588u));	/* 461455: mov esi, dword ptr [ecx + 0x163b588] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 46145b: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->esi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 46145c: idiv esi */
	m->eax = m->edx;	/* 46145e: mov eax, edx */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 461460: add eax, esi */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 461462: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->esi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 461463: idiv esi */
	m->eax = M32((DWORD)(m->ecx + 0x234240du));	/* 461465: mov eax, dword ptr [ecx + 0x234240d] */
	m->esi = M32(m->esp); m->esp += 4;	/* 46146b: pop esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46146c: test eax, eax */
	M32((DWORD)(m->ecx + 0x2342452u)) = m->edx;	/* 46146e: mov dword ptr [ecx + 0x2342452], edx */
	if (m->sf != m->of) goto L_461483;	/* 461474: jl 0x461483 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 461476: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 461477: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x1f36c8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 461478: add ecx, 0x1f36c8 */
	m->esp -= 4; M32(m->esp) = 0x461483u; native_call(m, 0x473d30u);	/* 46147e: call 0x473d30 */
L_461483:
	m->esp += 4 + 4; return;	/* 461483: ret 4 */
}

/* armc_setLegIndex (0x461490), lifted by tools/lift.py */
static void lift_461490(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 461490: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 461494: push esi */
	m->esi = M32((DWORD)(m->ecx + 0x1679b34u));	/* 461495: mov esi, dword ptr [ecx + 0x1679b34] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 46149b: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->esi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 46149c: idiv esi */
	m->eax = m->edx;	/* 46149e: mov eax, edx */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4614a0: add eax, esi */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4614a2: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->esi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 4614a3: idiv esi */
	m->eax = M32((DWORD)(m->ecx + 0x234240du));	/* 4614a5: mov eax, dword ptr [ecx + 0x234240d] */
	m->esi = M32(m->esp); m->esp += 4;	/* 4614ab: pop esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4614ac: test eax, eax */
	M32((DWORD)(m->ecx + 0x2342456u)) = m->edx;	/* 4614ae: mov dword ptr [ecx + 0x2342456], edx */
	if (m->sf != m->of) goto L_4614c3;	/* 4614b4: jl 0x4614c3 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4614b6: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4614b7: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x1f36c8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4614b8: add ecx, 0x1f36c8 */
	m->esp -= 4; M32(m->esp) = 0x4614c3u; native_call(m, 0x473e40u);	/* 4614be: call 0x473e40 */
L_4614c3:
	m->esp += 4 + 4; return;	/* 4614c3: ret 4 */
}

/* armc_setBoosterIndex (0x4614d0), lifted by tools/lift.py */
static void lift_4614d0(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 4614d0: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4614d4: push esi */
	m->esi = M32((DWORD)(m->ecx + 0x16c5178u));	/* 4614d5: mov esi, dword ptr [ecx + 0x16c5178] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4614db: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->esi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 4614dc: idiv esi */
	m->eax = m->edx;	/* 4614de: mov eax, edx */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4614e0: add eax, esi */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4614e2: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->esi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 4614e3: idiv esi */
	m->eax = M32((DWORD)(m->ecx + 0x234240du));	/* 4614e5: mov eax, dword ptr [ecx + 0x234240d] */
	m->esi = M32(m->esp); m->esp += 4;	/* 4614eb: pop esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4614ec: test eax, eax */
	M32((DWORD)(m->ecx + 0x234245au)) = m->edx;	/* 4614ee: mov dword ptr [ecx + 0x234245a], edx */
	if (m->sf != m->of) goto L_461503;	/* 4614f4: jl 0x461503 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4614f6: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4614f7: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x1f36c8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4614f8: add ecx, 0x1f36c8 */
	m->esp -= 4; M32(m->esp) = 0x461503u; native_call(m, 0x473f50u);	/* 4614fe: call 0x473f50 */
L_461503:
	m->esp += 4 + 4; return;	/* 461503: ret 4 */
}

/* armc_461510 (0x461510), lifted by tools/lift.py */
static void lift_461510(X86 *m)
{
	m->edx = M32((DWORD)(m->esp + 0x8u));	/* 461510: mov edx, dword ptr [esp + 8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 461514: push esi */
	m->esi = M32((DWORD)(m->esp + 0x8u));	/* 461515: mov esi, dword ptr [esp + 8] */
	M32((DWORD)(m->ecx + m->esi*4 + 0x234245eu)) = m->edx;	/* 461519: mov dword ptr [ecx + esi*4 + 0x234245e], edx */
	m->eax = M32((DWORD)(m->ecx + 0x234240du));	/* 461520: mov eax, dword ptr [ecx + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 461526: test eax, eax */
	if (m->sf != m->of) goto L_461538;	/* 461528: jl 0x461538 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46152a: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46152b: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46152c: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x1f36c8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46152d: add ecx, 0x1f36c8 */
	m->esp -= 4; M32(m->esp) = 0x461538u; native_call(m, 0x474060u);	/* 461533: call 0x474060 */
L_461538:
	m->esi = M32(m->esp); m->esp += 4;	/* 461538: pop esi */
	m->esp += 4 + 8; return;	/* 461539: ret 8 */
}

/* actor_46fed0 (0x46fed0), lifted by tools/lift.py */
static void lift_46fed0(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fed0: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46fed1: push esi */
	m->esi = m->ecx;	/* 46fed2: mov esi, ecx */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 46fed4: xor ebx, ebx */
	m->eax = M32((DWORD)(m->esi + 0x10u));	/* 46fed6: mov eax, dword ptr [esi + 0x10] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46fed9: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_46fefe;	/* 46fedb: jle 0x46fefe */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46fedd: push edi */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 46fede: xor edi, edi */
L_46fee0:
	m->eax = M32((DWORD)(m->esi + 0x14u));	/* 46fee0: mov eax, dword ptr [esi + 0x14] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46fee3: add eax, edi */
	m->eax = M32((DWORD)(m->eax + 0x0u));	/* 46fee5: mov eax, dword ptr [eax] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46fee7: test eax, eax */
	if (m->zf) goto L_46fef2;	/* 46fee9: je 0x46fef2 */
	m->ecx = m->eax;	/* 46feeb: mov ecx, eax */
	m->esp -= 4; M32(m->esp) = 0x46fef2u; native_call(m, 0x466650u);	/* 46feed: call 0x466650 */
L_46fef2:
	m->eax = M32((DWORD)(m->esi + 0x10u));	/* 46fef2: mov eax, dword ptr [esi + 0x10] */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 46fef5: inc ebx */
	{ DWORD a_ = m->edi, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46fef6: add edi, 0x64 */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46fef9: cmp ebx, eax */
	if (m->sf != m->of) goto L_46fee0;	/* 46fefb: jl 0x46fee0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 46fefd: pop edi */
L_46fefe:
	m->esi = M32(m->esp); m->esp += 4;	/* 46fefe: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 46feff: pop ebx */
	m->esp += 4 + 0; return;	/* 46ff00: ret  */
}

/* match_474210 (0x474210), lifted by tools/lift.py */
static void lift_474210(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 474210: mov eax, dword ptr [esp + 8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 474214: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 474215: push edi */
	m->edi = M32((DWORD)(m->esp + 0xcu));	/* 474216: mov edi, dword ptr [esp + 0xc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47421a: push eax */
	m->esi = m->ecx;	/* 47421b: mov esi, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 47421d: push edi */
	m->esp -= 4; M32(m->esp) = 0x474223u; native_call(m, 0x473940u);	/* 47421e: call 0x473940 */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 474223: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 474227: push ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 474228: push edi */
	m->ecx = m->esi;	/* 474229: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x474230u; native_call(m, 0x473a10u);	/* 47422b: call 0x473a10 */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 474230: mov edx, dword ptr [esp + 0x18] */
	m->ecx = m->esi;	/* 474234: mov ecx, esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 474236: push edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 474237: push edi */
	m->esp -= 4; M32(m->esp) = 0x47423du; native_call(m, 0x473a80u);	/* 474238: call 0x473a80 */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 47423d: mov eax, dword ptr [esp + 0x1c] */
	m->ecx = m->esi;	/* 474241: mov ecx, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 474243: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 474244: push edi */
	m->esp -= 4; M32(m->esp) = 0x47424au; native_call(m, 0x473b10u);	/* 474245: call 0x473b10 */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 47424a: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47424e: push ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 47424f: push edi */
	m->ecx = m->esi;	/* 474250: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x474257u; native_call(m, 0x473c20u);	/* 474252: call 0x473c20 */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 474257: mov edx, dword ptr [esp + 0x24] */
	m->ecx = m->esi;	/* 47425b: mov ecx, esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47425d: push edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 47425e: push edi */
	m->esp -= 4; M32(m->esp) = 0x474264u; native_call(m, 0x473d30u);	/* 47425f: call 0x473d30 */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 474264: mov eax, dword ptr [esp + 0x28] */
	m->ecx = m->esi;	/* 474268: mov ecx, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47426a: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 47426b: push edi */
	m->esp -= 4; M32(m->esp) = 0x474271u; native_call(m, 0x473e40u);	/* 47426c: call 0x473e40 */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 474271: mov ecx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 474275: push ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 474276: push edi */
	m->ecx = m->esi;	/* 474277: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x47427eu; native_call(m, 0x473f50u);	/* 474279: call 0x473f50 */
	m->edx = M32((DWORD)(m->esp + 0x30u));	/* 47427e: mov edx, dword ptr [esp + 0x30] */
	m->ecx = m->esi;	/* 474282: mov ecx, esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 474284: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 474285: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 474287: push edi */
	m->esp -= 4; M32(m->esp) = 0x47428du; native_call(m, 0x474060u);	/* 474288: call 0x474060 */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 47428d: mov eax, dword ptr [esp + 0x34] */
	m->ecx = m->esi;	/* 474291: mov ecx, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 474293: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 474294: push 1 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 474296: push edi */
	m->esp -= 4; M32(m->esp) = 0x47429cu; native_call(m, 0x474060u);	/* 474297: call 0x474060 */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 47429c: mov ecx, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4742a0: push ecx */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4742a1: push 2 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4742a3: push edi */
	m->ecx = m->esi;	/* 4742a4: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x4742abu; native_call(m, 0x474060u);	/* 4742a6: call 0x474060 */
	m->edx = M32((DWORD)(m->esp + 0x3cu));	/* 4742ab: mov edx, dword ptr [esp + 0x3c] */
	m->ecx = m->esi;	/* 4742af: mov ecx, esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4742b1: push edx */
	{ DWORD v_ = 0x3u; m->esp -= 4; M32(m->esp) = v_; }	/* 4742b2: push 3 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4742b4: push edi */
	m->esp -= 4; M32(m->esp) = 0x4742bau; native_call(m, 0x474060u);	/* 4742b5: call 0x474060 */
	m->eax = M32((DWORD)(m->esp + 0x40u));	/* 4742ba: mov eax, dword ptr [esp + 0x40] */
	m->ecx = m->esi;	/* 4742be: mov ecx, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4742c0: push eax */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4742c1: push 4 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4742c3: push edi */
	m->esp -= 4; M32(m->esp) = 0x4742c9u; native_call(m, 0x474060u);	/* 4742c4: call 0x474060 */
	m->ecx = M32((DWORD)(m->esp + 0x44u));	/* 4742c9: mov ecx, dword ptr [esp + 0x44] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4742cd: push ecx */
	{ DWORD v_ = 0x5u; m->esp -= 4; M32(m->esp) = v_; }	/* 4742ce: push 5 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4742d0: push edi */
	m->ecx = m->esi;	/* 4742d1: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x4742d8u; native_call(m, 0x474060u);	/* 4742d3: call 0x474060 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4742d8: push edi */
	m->ecx = m->esi;	/* 4742d9: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x4742e0u; native_call(m, 0x474390u);	/* 4742db: call 0x474390 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4742e0: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4742e1: pop esi */
	m->esp += 4 + 60; return;	/* 4742e2: ret 0x3c */
}

/* load_4742f0 (0x4742f0), lifted by tools/lift.py */
static void lift_4742f0(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4742f0: push ebx */
	m->ebx = M32((DWORD)(m->esp + 0xcu));	/* 4742f1: mov ebx, dword ptr [esp + 0xc] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4742f5: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4742f6: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4742f7: push edi */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 4742f8: mov edi, dword ptr [esp + 0x14] */
	m->eax = (DWORD)(m->ebx + 0x8u);	/* 4742fc: lea eax, [ebx + 8] */
	m->esi = m->ecx;	/* 4742ff: mov esi, ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 474301: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 474302: push edi */
	m->esp -= 4; M32(m->esp) = 0x474308u; native_call(m, 0x473940u);	/* 474303: call 0x473940 */
	m->ecx = M32((DWORD)(m->ebx + 0x4u));	/* 474308: mov ecx, dword ptr [ebx + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47430b: push ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 47430c: push edi */
	m->ecx = m->esi;	/* 47430d: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x474314u; native_call(m, 0x473a10u);	/* 47430f: call 0x473a10 */
	m->edx = M32((DWORD)(m->ebx + 0x28u));	/* 474314: mov edx, dword ptr [ebx + 0x28] */
	m->ecx = m->esi;	/* 474317: mov ecx, esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 474319: push edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 47431a: push edi */
	m->esp -= 4; M32(m->esp) = 0x474320u; native_call(m, 0x473a80u);	/* 47431b: call 0x473a80 */
	m->eax = M32((DWORD)(m->ebx + 0x2cu));	/* 474320: mov eax, dword ptr [ebx + 0x2c] */
	m->ecx = m->esi;	/* 474323: mov ecx, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 474325: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 474326: push edi */
	m->esp -= 4; M32(m->esp) = 0x47432cu; native_call(m, 0x473b10u);	/* 474327: call 0x473b10 */
	m->ecx = M32((DWORD)(m->ebx + 0x30u));	/* 47432c: mov ecx, dword ptr [ebx + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47432f: push ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 474330: push edi */
	m->ecx = m->esi;	/* 474331: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x474338u; native_call(m, 0x473c20u);	/* 474333: call 0x473c20 */
	m->edx = M32((DWORD)(m->ebx + 0x34u));	/* 474338: mov edx, dword ptr [ebx + 0x34] */
	m->ecx = m->esi;	/* 47433b: mov ecx, esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47433d: push edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 47433e: push edi */
	m->esp -= 4; M32(m->esp) = 0x474344u; native_call(m, 0x473d30u);	/* 47433f: call 0x473d30 */
	m->eax = M32((DWORD)(m->ebx + 0x38u));	/* 474344: mov eax, dword ptr [ebx + 0x38] */
	m->ecx = m->esi;	/* 474347: mov ecx, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 474349: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 47434a: push edi */
	m->esp -= 4; M32(m->esp) = 0x474350u; native_call(m, 0x473e40u);	/* 47434b: call 0x473e40 */
	m->ecx = M32((DWORD)(m->ebx + 0x3cu));	/* 474350: mov ecx, dword ptr [ebx + 0x3c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 474353: push ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 474354: push edi */
	m->ecx = m->esi;	/* 474355: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x47435cu; native_call(m, 0x473f50u);	/* 474357: call 0x473f50 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 47435c: xor ebp, ebp */
	{ DWORD a_ = m->ebx, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 47435e: add ebx, 0x40 */
L_474361:
	m->edx = M32((DWORD)(m->ebx + 0x0u));	/* 474361: mov edx, dword ptr [ebx] */
	m->ecx = m->esi;	/* 474363: mov ecx, esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 474365: push edx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 474366: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 474367: push edi */
	m->esp -= 4; M32(m->esp) = 0x47436du; native_call(m, 0x474060u);	/* 474368: call 0x474060 */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 47436d: inc ebp */
	{ DWORD a_ = m->ebx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 47436e: add ebx, 4 */
	{ DWORD a_ = m->ebp, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 474371: cmp ebp, 6 */
	if (m->sf != m->of) goto L_474361;	/* 474374: jl 0x474361 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 474376: push edi */
	m->ecx = m->esi;	/* 474377: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x47437eu; native_call(m, 0x474390u);	/* 474379: call 0x474390 */
	m->edi = M32(m->esp); m->esp += 4;	/* 47437e: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 47437f: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 474380: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 474381: pop ebx */
	m->esp += 4 + 8; return;	/* 474382: ret 8 */
}

/* hud_4955a0 (0x4955a0), lifted by tools/lift.py */
/* (hud_4955a0 was here, cut at 0x4955c0 by functions.csv; lifted whole in lifted/grp153.c, batch 198) */

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
