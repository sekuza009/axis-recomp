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

static void lift_48f970(X86 *m);

/* hud_48f970 (0x48f970), lifted by tools/lift.py */
static void lift_48f970(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48f970: sub esp, 0x30 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48f973: push ebx */
	m->ebx = m->ecx;	/* 48f974: mov ebx, ecx */
	M32((DWORD)(m->esp + 0x10u)) = 0x0u;	/* 48f976: mov dword ptr [esp + 0x10], 0 */
	m->eax = M32((DWORD)(m->ebx + 0x20fcd38u));	/* 48f97e: mov eax, dword ptr [ebx + 0x20fcd38] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48f984: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_48fc1f;	/* 48f986: jle 0x48fc1f */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48f98c: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48f98d: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48f98e: push edi */
	m->esi = (DWORD)(m->ebx + 0x20fae1cu);	/* 48f98f: lea esi, [ebx + 0x20fae1c] */
L_48f995:
	m->edi = M32((DWORD)(m->esi + 0xffffffdcu));	/* 48f995: mov edi, dword ptr [esi - 0x24] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48f998: test edi, edi */
	if (m->sf != m->of) goto L_48fc02;	/* 48f99a: jl 0x48fc02 */
	m->eax = M32((DWORD)(m->esi + 0xfffffffcu));	/* 48f9a0: mov eax, dword ptr [esi - 4] */
	m->ecx = 0x1u;	/* 48f9a3: mov ecx, 1 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48f9a8: cmp eax, ecx */
	if (m->zf) goto L_48fc02;	/* 48f9aa: je 0x48fc02 */
	m->eax = (DWORD)(m->edi + m->edi*8 + 0x0u);	/* 48f9b0: lea eax, [edi + edi*8] */
	m->ebp = (DWORD)(m->esi + 0xffffffe8u);	/* 48f9b3: lea ebp, [esi - 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x20f3970u)));	/* 48f9b6: fld dword ptr [ebx + 0x20f3970] */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48f9bc: shl eax, 4 */
	m->edx = (DWORD)(m->eax + m->ebx*1 + 0x20f3ae0u);	/* 48f9bf: lea edx, [eax + ebx + 0x20f3ae0] */
	m->eax = M32((DWORD)(m->ebx + 0xa08u));	/* 48f9c6: mov eax, dword ptr [ebx + 0xa08] */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 48f9cc: mov dword ptr [esp + 0x14], eax */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 48f9d0: mov dword ptr [esp + 0x18], edx */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 48f9d4: fsub dword ptr [esp + 0x14] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x0u)); FPOP();	/* 48f9d8: fcomp dword ptr [ebp] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48f9db: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48f9dd: test ah, 0x41 */
	if (m->zf) goto L_48fc02;	/* 48f9e0: je 0x48fc02 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x20f3974u)));	/* 48f9e6: fld dword ptr [ebx + 0x20f3974] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 48f9ec: fsub dword ptr [esp + 0x14] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0xffffffecu)); FPOP();	/* 48f9f0: fcomp dword ptr [esi - 0x14] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48f9f3: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48f9f5: test ah, 0x41 */
	if (m->zf) goto L_48fc02;	/* 48f9f8: je 0x48fc02 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x20f3978u)));	/* 48f9fe: fld dword ptr [ebx + 0x20f3978] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 48fa04: fsub dword ptr [esp + 0x14] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0xfffffff0u)); FPOP();	/* 48fa08: fcomp dword ptr [esi - 0x10] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48fa0b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48fa0d: test ah, 0x41 */
	if (m->zf) goto L_48fc02;	/* 48fa10: je 0x48fc02 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 48fa16: fld dword ptr [esp + 0x14] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x20f3970u));	/* 48fa1a: fadd dword ptr [ebx + 0x20f3970] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x0u)); FPOP();	/* 48fa20: fcomp dword ptr [ebp] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48fa23: fnstsw ax */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->eax >> 8) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48fa25: test cl, ah */
	if (!m->zf) goto L_48fc02;	/* 48fa27: jne 0x48fc02 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 48fa2d: fld dword ptr [esp + 0x14] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x20f3974u));	/* 48fa31: fadd dword ptr [ebx + 0x20f3974] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0xffffffecu)); FPOP();	/* 48fa37: fcomp dword ptr [esi - 0x14] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48fa3a: fnstsw ax */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->eax >> 8) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48fa3c: test cl, ah */
	if (!m->zf) goto L_48fc02;	/* 48fa3e: jne 0x48fc02 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 48fa44: fld dword ptr [esp + 0x14] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x20f3978u));	/* 48fa48: fadd dword ptr [ebx + 0x20f3978] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0xfffffff0u)); FPOP();	/* 48fa4e: fcomp dword ptr [esi - 0x10] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48fa51: fnstsw ax */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->eax >> 8) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48fa53: test cl, ah */
	if (!m->zf) goto L_48fc02;	/* 48fa55: jne 0x48fc02 */
	{ DWORD a_ = M32((DWORD)(0x83a9c8u)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48fa5b: cmp dword ptr [0x83a9c8], ecx */
	if (m->zf) goto L_48fb62;	/* 48fa61: je 0x48fb62 */
	{ DWORD a_ = m->edi, b_ = 0x22u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48fa67: cmp edi, 0x22 */
	if (m->zf) goto L_48fb62;	/* 48fa6a: je 0x48fb62 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 48fa70: fld dword ptr [esi] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 48fa72: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48fa78: fnstsw ax */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->eax >> 8) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48fa7a: test cl, ah */
	if (m->zf) goto L_48faa0;	/* 48fa7c: je 0x48faa0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 48fa7e: fld dword ptr [esi] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9744u));	/* 48fa80: fmul dword ptr [0x4a9744] */
	M8((DWORD)(m->esp + 0x10u)) = (BYTE)(0xffu);	/* 48fa86: mov byte ptr [esp + 0x10], 0xff */
	M8((DWORD)(m->esp + 0x11u)) = (BYTE)(0xffu);	/* 48fa8b: mov byte ptr [esp + 0x11], 0xff */
	M8((DWORD)(m->esp + 0x12u)) = (BYTE)(0xffu);	/* 48fa90: mov byte ptr [esp + 0x12], 0xff */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 48fa95: call 0x49ec14 */
	M8((DWORD)(m->esp + 0x13u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 48fa9a: mov byte ptr [esp + 0x13], al */
	goto L_48faaa;	/* 48fa9e: jmp 0x48faaa */
L_48faa0:
	m->ecx = M32((DWORD)(0xa1f23cu));	/* 48faa0: mov ecx, dword ptr [0xa1f23c] */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 48faa6: mov dword ptr [esp + 0x10], ecx */
L_48faaa:
	m->edx = m->edi;	/* 48faaa: mov edx, edi */
	{ DWORD a_ = m->edx, b_ = 0x80000007u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48faac: and edx, 0x80000007 */
	if (!m->sf) goto L_48fab9;	/* 48fab2: jns 0x48fab9 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 48fab4: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffff8u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48fab5: or edx, 0xfffffff8 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 48fab8: inc edx */
L_48fab9:
	{ DWORD a_ = m->edx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 48fab9: shl edx, 5 */
	m->eax = m->edi;	/* 48fabc: mov eax, edi */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 48fabe: mov dword ptr [esp + 0x18], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x18u)));	/* 48fac2: fild dword ptr [esp + 0x18] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48fac6: cdq  */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 48fac7: fmul dword ptr [0x4a957c] */
	{ DWORD a_ = m->edx, b_ = 0x7u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48facd: and edx, 7 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48fad0: push 1 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48fad2: add eax, edx */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 48fad4: push 2 */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48fad6: sar eax, 3 */
	{ DWORD a_ = m->eax, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48fad9: shl eax, 5 */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 48fadc: fstp dword ptr [esp + 0x28] */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 48fae0: mov dword ptr [esp + 0x20], eax */
	m->eax = (DWORD)(m->esp + 0x30u);	/* 48fae4: lea eax, [esp + 0x30] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 48fae8: fild dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48faec: push ebp */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 48faed: lea ecx, [esp + 0x3c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48faf1: push eax */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 48faf2: lea edx, [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 48faf6: fmul dword ptr [0x4a957c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48fafc: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48fafd: push edx */
	m->edx = M32((DWORD)(m->ebx + 0x9ccff8u));	/* 48fafe: mov edx, dword ptr [ebx + 0x9ccff8] */
	m->eax = (DWORD)(m->esp + 0x50u);	/* 48fb04: lea eax, [esp + 0x50] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 48fb08: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 48fb0c: fld dword ptr [esp + 0x38] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4aa274u));	/* 48fb10: fadd dword ptr [0x4aa274] */
	{ DWORD v_ = 0x43160000u; m->esp -= 4; M32(m->esp) = v_; }	/* 48fb16: push 0x43160000 */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 48fb1b: lea ecx, [esp + 0x3c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48fb1f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48fb20: push ecx */
	MF((DWORD)(m->esp + 0x5cu)) = (float)ST(0); FPOP();	/* 48fb21: fstp dword ptr [esp + 0x5c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 48fb25: fld dword ptr [esp + 0x48] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4aa274u));	/* 48fb29: fadd dword ptr [0x4aa274] */
	m->ecx = M32((DWORD)(m->esp + 0x68u));	/* 48fb2f: mov ecx, dword ptr [esp + 0x68] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48fb33: push edx */
	M32((DWORD)(m->esp + 0x58u)) = 0xc3160000u;	/* 48fb34: mov dword ptr [esp + 0x58], 0xc3160000 */
	M32((DWORD)(m->esp + 0x5cu)) = 0xc3160000u;	/* 48fb3c: mov dword ptr [esp + 0x5c], 0xc3160000 */
	MF((DWORD)(m->esp + 0x64u)) = (float)ST(0); FPOP();	/* 48fb44: fstp dword ptr [esp + 0x64] */
	M32((DWORD)(m->esp + 0x50u)) = 0x43160000u;	/* 48fb48: mov dword ptr [esp + 0x50], 0x43160000 */
	M32((DWORD)(m->esp + 0x54u)) = 0x43160000u;	/* 48fb50: mov dword ptr [esp + 0x54], 0x43160000 */
	m->esp -= 4; M32(m->esp) = 0x48fb5du; native_call(m, 0x484ca0u);	/* 48fb58: call 0x484ca0 */
	goto L_48fc02;	/* 48fb5d: jmp 0x48fc02 */
L_48fb62:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 48fb62: fld dword ptr [esi] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 48fb64: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48fb6a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48fb6c: test ah, 1 */
	if (m->zf) goto L_48fb97;	/* 48fb6f: je 0x48fb97 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 48fb71: fld dword ptr [esi] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9744u));	/* 48fb73: fmul dword ptr [0x4a9744] */
	M8((DWORD)(m->esp + 0x10u)) = (BYTE)(0xffu);	/* 48fb79: mov byte ptr [esp + 0x10], 0xff */
	M8((DWORD)(m->esp + 0x11u)) = (BYTE)(0xffu);	/* 48fb7e: mov byte ptr [esp + 0x11], 0xff */
	M8((DWORD)(m->esp + 0x12u)) = (BYTE)(0xffu);	/* 48fb83: mov byte ptr [esp + 0x12], 0xff */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 48fb88: call 0x49ec14 */
	M8((DWORD)(m->esp + 0x13u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 48fb8d: mov byte ptr [esp + 0x13], al */
	m->edi = (DWORD)(m->esp + 0x10u);	/* 48fb91: lea edi, [esp + 0x10] */
	goto L_48fb99;	/* 48fb95: jmp 0x48fb99 */
L_48fb97:
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 48fb97: xor edi, edi */
L_48fb99:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 48fb99: mov eax, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->eax + 0x8cu));	/* 48fb9d: mov ecx, dword ptr [eax + 0x8c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48fba3: test ecx, ecx */
	if (m->zf) goto L_48fc02;	/* 48fba5: je 0x48fc02 */
	m->esp -= 4; M32(m->esp) = 0x48fbadu; native_call(m, M32(0x4a9204u));	/* 48fba7: call dword ptr [0x4a9204] */
	m->ecx = M32((DWORD)(m->esi + 0xfffffff0u));	/* 48fbad: mov ecx, dword ptr [esi - 0x10] */
	m->edx = M32((DWORD)(m->esi + 0xffffffecu));	/* 48fbb0: mov edx, dword ptr [esi - 0x14] */
	m->eax = M32((DWORD)(m->ebp + 0x0u));	/* 48fbb3: mov eax, dword ptr [ebp] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48fbb6: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48fbb7: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48fbb8: push eax */
	m->esp -= 4; M32(m->esp) = 0x48fbbfu; native_call(m, M32(0x4a9214u));	/* 48fbb9: call dword ptr [0x4a9214] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0xfffffff8u)));	/* 48fbbf: fld dword ptr [esi - 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 48fbc2: fmul dword ptr [0x4a93ec] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48fbc8: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 48fbca: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48fbcf: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48fbd1: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 48fbd2: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x48fbdbu; native_call(m, M32(0x4a91f8u));	/* 48fbd5: call dword ptr [0x4a91f8] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 48fbdb: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48fbdf: push 0 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 48fbe1: push -1 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48fbe3: push 1 */
	m->edx = M32((DWORD)(m->ecx + 0x8cu));	/* 48fbe5: mov edx, dword ptr [ecx + 0x8c] */
	m->ecx = M32((DWORD)(m->esp + 0x50u));	/* 48fbeb: mov ecx, dword ptr [esp + 0x50] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48fbef: push edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48fbf0: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48fbf2: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48fbf4: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48fbf6: push edx */
	m->esp -= 4; M32(m->esp) = 0x48fbfcu; native_call(m, 0x4853c0u);	/* 48fbf7: call 0x4853c0 */
	m->esp -= 4; M32(m->esp) = 0x48fc02u; native_call(m, M32(0x4a9258u));	/* 48fbfc: call dword ptr [0x4a9258] */
L_48fc02:
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 48fc02: mov eax, dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(m->ebx + 0x20fcd38u));	/* 48fc06: mov ecx, dword ptr [ebx + 0x20fcd38] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48fc0c: inc eax */
	{ DWORD a_ = m->esi, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 48fc0d: add esi, 0x28 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48fc10: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 48fc12: mov dword ptr [esp + 0x1c], eax */
	if (m->sf != m->of) goto L_48f995;	/* 48fc16: jl 0x48f995 */
	m->edi = M32(m->esp); m->esp += 4;	/* 48fc1c: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48fc1d: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 48fc1e: pop ebp */
L_48fc1f:
	m->ebx = M32(m->esp); m->esp += 4;	/* 48fc1f: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48fc20: add esp, 0x30 */
	m->esp += 4 + 4; return;	/* 48fc23: ret 4 */
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
