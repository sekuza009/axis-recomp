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

static void lift_496c20(X86 *m);
static void lift_496d10(X86 *m);
static void lift_496a30(X86 *m);
static void lift_495140(X86 *m);

/* hud_drawPressFire (0x495140), lifted by tools/lift.py */
static void lift_495140(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495140: sub esp, 0x100 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495146: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49514b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495150: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495155: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x49515fu; native_call(m, 0x44ad30u);	/* 49515a: call 0x44ad30 */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 49515f: lea eax, [esp + 0x10] */
	{ DWORD v_ = 0x4d0414u; m->esp -= 4; M32(m->esp) = v_; }	/* 495163: push 0x4d0414 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 495168: push eax */
	m->esp -= 4; M32(m->esp) = 0x49516eu; native_call(m, 0x49e9ddu);	/* 495169: call 0x49e9dd */
	m->ecx = (DWORD)(m->esp + 0x18u);	/* 49516e: lea ecx, [esp + 0x18] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 495172: push 0x10 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 495174: push ecx */
	{ DWORD v_ = 0x280u; m->esp -= 4; M32(m->esp) = v_; }	/* 495175: push 0x280 */
	{ DWORD v_ = 0x168u; m->esp -= 4; M32(m->esp) = v_; }	/* 49517a: push 0x168 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 49517f: push 0 */
	m->esp -= 4; M32(m->esp) = 0x495186u; native_call(m, 0x44ae10u);	/* 495181: call 0x44ae10 */
	{ DWORD a_ = m->esp, b_ = 0x12cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495186: add esp, 0x12c */
	m->esp += 4 + 0; return;	/* 49518c: ret  */
}

/* hud_drawReadyStart (0x496c20), lifted by tools/lift.py */
static void lift_496c20(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496c20: sub esp, 0x100 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 496c26: push esi */
	m->esi = m->ecx;	/* 496c27: mov esi, ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233cc4cu)));	/* 496c29: fld dword ptr [esi + 0x233cc4c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 496c2f: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 496c35: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 496c37: test ah, 0x41 */
	if (!m->zf) goto L_496cca;	/* 496c3a: jne 0x496cca */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233cc4cu)));	/* 496c40: fld dword ptr [esi + 0x233cc4c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 496c46: fcomp dword ptr [0x4a9424] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496c4c: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496c51: push 0 */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 496c53: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 496c55: test ah, 1 */
	if (!m->zf) goto L_496c89;	/* 496c58: jne 0x496c89 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496c5a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496c5f: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x496c69u; native_call(m, 0x44ad30u);	/* 496c64: call 0x44ad30 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233cc4cu)));	/* 496c69: fld dword ptr [esi + 0x233cc4c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 496c6f: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 496c74: push eax */
	m->eax = (DWORD)(m->esp + 0x18u);	/* 496c75: lea eax, [esp + 0x18] */
	{ DWORD v_ = 0x4d0510u; m->esp -= 4; M32(m->esp) = v_; }	/* 496c79: push 0x4d0510 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 496c7e: push eax */
	m->esp -= 4; M32(m->esp) = 0x496c84u; native_call(m, 0x49e9ddu);	/* 496c7f: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496c84: add esp, 0x1c */
	goto L_496ca7;	/* 496c87: jmp 0x496ca7 */
L_496c89:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496c89: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496c8b: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x496c95u; native_call(m, 0x44ad30u);	/* 496c90: call 0x44ad30 */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 496c95: lea ecx, [esp + 0x14] */
	{ DWORD v_ = 0x4d0508u; m->esp -= 4; M32(m->esp) = v_; }	/* 496c99: push 0x4d0508 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 496c9e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x496ca4u; native_call(m, 0x49e9ddu);	/* 496c9f: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496ca4: add esp, 0x18 */
L_496ca7:
	m->edx = (DWORD)(m->esp + 0x4u);	/* 496ca7: lea edx, [esp + 4] */
	{ DWORD v_ = 0x20u; m->esp -= 4; M32(m->esp) = v_; }	/* 496cab: push 0x20 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 496cad: push edx */
	{ DWORD v_ = 0x280u; m->esp -= 4; M32(m->esp) = v_; }	/* 496cae: push 0x280 */
	{ DWORD v_ = 0xf0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496cb3: push 0xf0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496cb8: push 0 */
	m->esp -= 4; M32(m->esp) = 0x496cbfu; native_call(m, 0x44ae10u);	/* 496cba: call 0x44ae10 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496cbf: add esp, 0x14 */
	m->esi = M32(m->esp); m->esp += 4;	/* 496cc2: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496cc3: add esp, 0x100 */
	m->esp += 4 + 0; return;	/* 496cc9: ret  */
L_496cca:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496cca: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496ccf: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496cd1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496cd6: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x496ce0u; native_call(m, 0x44ad30u);	/* 496cdb: call 0x44ad30 */
	{ DWORD a_ = m->esi, b_ = 0x2342f06u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 496ce0: add esi, 0x2342f06 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 496ce6: push 0x10 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 496ce8: push esi */
	{ DWORD v_ = 0x280u; m->esp -= 4; M32(m->esp) = v_; }	/* 496ce9: push 0x280 */
	{ DWORD v_ = 0x172u; m->esp -= 4; M32(m->esp) = v_; }	/* 496cee: push 0x172 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496cf3: push 0 */
	m->esp -= 4; M32(m->esp) = 0x496cfau; native_call(m, 0x44ae10u);	/* 496cf5: call 0x44ae10 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496cfa: add esp, 0x24 */
	m->esi = M32(m->esp); m->esp += 4;	/* 496cfd: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496cfe: add esp, 0x100 */
	m->esp += 4 + 0; return;	/* 496d04: ret  */
}

/* hud_drawRecordIndicator (0x496d10), lifted by tools/lift.py */
static void lift_496d10(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x104u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496d10: sub esp, 0x104 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 496d16: push esi */
	m->esi = m->ecx;	/* 496d17: mov esi, ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x2340d29u)));	/* 496d19: fld dword ptr [esi + 0x2340d29] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 496d1f: call 0x49ec14 */
	M32((DWORD)(m->esp + 0x4u)) = m->eax;	/* 496d24: mov dword ptr [esp + 4], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x4u)));	/* 496d28: fild dword ptr [esp + 4] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(m->esi + 0x2340d29u));	/* 496d2c: fsubr dword ptr [esi + 0x2340d29] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a942cu)); FPOP();	/* 496d32: fcomp dword ptr [0x4a942c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 496d38: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 496d3a: test ah, 1 */
	if (m->zf) goto L_496e2a;	/* 496d3d: je 0x496e2a */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 496d43: push edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496d44: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496d49: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496d4e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496d53: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x496d5eu; native_call(m, M32(0x4a9228u));	/* 496d58: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 496d5e: push 4 */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 496d60: push 0x140 */
	{ DWORD v_ = 0x10au; m->esp -= 4; M32(m->esp) = v_; }	/* 496d65: push 0x10a */
	m->ecx = m->esi;	/* 496d6a: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x496d71u; native_call(m, 0x496820u);	/* 496d6c: call 0x496820 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496d71: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496d76: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496d7b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496d80: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x496d8au; native_call(m, 0x44ad30u);	/* 496d85: call 0x44ad30 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x2340d29u)));	/* 496d8a: fld dword ptr [esi + 0x2340d29] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 496d90: call 0x49ec14 */
	m->ecx = m->eax;	/* 496d95: mov ecx, eax */
	m->edi = 0x3cu;	/* 496d97: mov edi, 0x3c */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 496d9c: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->edi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 496d9d: idiv edi */
	m->eax = 0x88888889u;	/* 496d9f: mov eax, 0x88888889 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 496da4: push edx */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 496da5: imul ecx */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 496da7: add edx, ecx */
	m->ecx = (DWORD)(m->esp + 0x20u);	/* 496da9: lea ecx, [esp + 0x20] */
	{ DWORD a_ = m->edx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 496dad: sar edx, 5 */
	m->eax = m->edx;	/* 496db0: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 496db2: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 496db5: add edx, eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 496db7: push edx */
	{ DWORD v_ = 0x4c7cd8u; m->esp -= 4; M32(m->esp) = v_; }	/* 496db8: push 0x4c7cd8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 496dbd: push ecx */
	m->esp -= 4; M32(m->esp) = 0x496dc3u; native_call(m, 0x49e9ddu);	/* 496dbe: call 0x49e9dd */
	m->edx = (DWORD)(m->esp + 0x2cu);	/* 496dc3: lea edx, [esp + 0x2c] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 496dc7: push 0x10 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 496dc9: push edx */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 496dca: push 0x140 */
	{ DWORD v_ = 0x122u; m->esp -= 4; M32(m->esp) = v_; }	/* 496dcf: push 0x122 */
	m->esp -= 4; M32(m->esp) = 0x496dd9u; native_call(m, 0x44ad60u);	/* 496dd4: call 0x44ad60 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496dd9: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496dde: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496de3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496de8: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x496df2u; native_call(m, 0x44ad30u);	/* 496ded: call 0x44ad30 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496df2: add esp, 0x40 */
	{ DWORD a_ = m->esi, b_ = 0x2340d0cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 496df5: add esi, 0x2340d0c */
	m->eax = (DWORD)(m->esp + 0xcu);	/* 496dfb: lea eax, [esp + 0xc] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 496dff: push esi */
	{ DWORD v_ = 0x4d051cu; m->esp -= 4; M32(m->esp) = v_; }	/* 496e00: push 0x4d051c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 496e05: push eax */
	m->esp -= 4; M32(m->esp) = 0x496e0bu; native_call(m, 0x49e9ddu);	/* 496e06: call 0x49e9dd */
	m->ecx = (DWORD)(m->esp + 0x18u);	/* 496e0b: lea ecx, [esp + 0x18] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 496e0f: push 0x10 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 496e11: push ecx */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 496e12: push 0x140 */
	{ DWORD v_ = 0x128u; m->esp -= 4; M32(m->esp) = v_; }	/* 496e17: push 0x128 */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 496e1c: push 0x140 */
	m->esp -= 4; M32(m->esp) = 0x496e26u; native_call(m, 0x44ae10u);	/* 496e21: call 0x44ae10 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496e26: add esp, 0x20 */
	m->edi = M32(m->esp); m->esp += 4;	/* 496e29: pop edi */
L_496e2a:
	m->esi = M32(m->esp); m->esp += 4;	/* 496e2a: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x104u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496e2b: add esp, 0x104 */
	m->esp += 4 + 0; return;	/* 496e31: ret  */
}

/* hud_drawMatchResult (0x496a30), lifted by tools/lift.py */
static void lift_496a30(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496a30: sub esp, 0x100 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 496a36: push esi */
	m->esi = m->ecx;	/* 496a37: mov esi, ecx */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x22e7184u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 496a39: cmp dword ptr [esi + 0x22e7184], 1 */
	if (!m->zf) goto L_496b15;	/* 496a40: jne 0x496b15 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496a46: push 0x3f000000 */
	{ DWORD v_ = 0x3f19999au; m->esp -= 4; M32(m->esp) = v_; }	/* 496a4b: push 0x3f19999a */
	{ DWORD v_ = 0x3f19999au; m->esp -= 4; M32(m->esp) = v_; }	/* 496a50: push 0x3f19999a */
	{ DWORD v_ = 0x3f19999au; m->esp -= 4; M32(m->esp) = v_; }	/* 496a55: push 0x3f19999a */
	m->esp -= 4; M32(m->esp) = 0x496a60u; native_call(m, M32(0x4a9228u));	/* 496a5a: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x192u; m->esp -= 4; M32(m->esp) = v_; }	/* 496a60: push 0x192 */
	{ DWORD v_ = 0x280u; m->esp -= 4; M32(m->esp) = v_; }	/* 496a65: push 0x280 */
	{ DWORD v_ = 0x15eu; m->esp -= 4; M32(m->esp) = v_; }	/* 496a6a: push 0x15e */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496a6f: push 0 */
	m->esp -= 4; M32(m->esp) = 0x496a76u; native_call(m, 0x4950a0u);	/* 496a71: call 0x4950a0 */
	m->eax = M32((DWORD)(m->esi + 0x23423bdu));	/* 496a76: mov eax, dword ptr [esi + 0x23423bd] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496a7c: add esp, 0x10 */
	m->ecx = m->esi;	/* 496a7f: mov ecx, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 496a81: push eax */
	m->esp -= 4; M32(m->esp) = 0x496a87u; native_call(m, 0x463740u);	/* 496a82: call 0x463740 */
	{ DWORD a_ = m->eax, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 496a87: sub eax, 0 */
	if (m->zf) goto L_496acd;	/* 496a8a: je 0x496acd */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 496a8c: dec eax */
	if (m->zf) goto L_496aae;	/* 496a8d: je 0x496aae */
	m->ecx = (DWORD)(m->esp + 0x4u);	/* 496a8f: lea ecx, [esp + 4] */
	{ DWORD v_ = 0x4d04f0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496a93: push 0x4d04f0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 496a98: push ecx */
	m->esp -= 4; M32(m->esp) = 0x496a9eu; native_call(m, 0x49e9ddu);	/* 496a99: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496a9e: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496aa3: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496aa5: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496aaa: push 0 */
	goto L_496aea;	/* 496aac: jmp 0x496aea */
L_496aae:
	m->edx = (DWORD)(m->esp + 0x4u);	/* 496aae: lea edx, [esp + 4] */
	{ DWORD v_ = 0x4d04e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496ab2: push 0x4d04e0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 496ab7: push edx */
	m->esp -= 4; M32(m->esp) = 0x496abdu; native_call(m, 0x49e9ddu);	/* 496ab8: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496abd: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496ac2: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496ac7: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496ac9: push 0 */
	goto L_496aea;	/* 496acb: jmp 0x496aea */
L_496acd:
	m->eax = (DWORD)(m->esp + 0x4u);	/* 496acd: lea eax, [esp + 4] */
	{ DWORD v_ = 0x4d04d0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496ad1: push 0x4d04d0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 496ad6: push eax */
	m->esp -= 4; M32(m->esp) = 0x496adcu; native_call(m, 0x49e9ddu);	/* 496ad7: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496adc: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496ae1: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496ae3: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496ae5: push 0x3f800000 */
L_496aea:
	m->esp -= 4; M32(m->esp) = 0x496aefu; native_call(m, 0x44ad30u);	/* 496aea: call 0x44ad30 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496aef: add esp, 0x18 */
	m->ecx = (DWORD)(m->esp + 0x4u);	/* 496af2: lea ecx, [esp + 4] */
	{ DWORD v_ = 0x20u; m->esp -= 4; M32(m->esp) = v_; }	/* 496af6: push 0x20 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 496af8: push ecx */
	{ DWORD v_ = 0x280u; m->esp -= 4; M32(m->esp) = v_; }	/* 496af9: push 0x280 */
	{ DWORD v_ = 0x168u; m->esp -= 4; M32(m->esp) = v_; }	/* 496afe: push 0x168 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496b03: push 0 */
	m->esp -= 4; M32(m->esp) = 0x496b0au; native_call(m, 0x44ae10u);	/* 496b05: call 0x44ae10 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496b0a: add esp, 0x14 */
	m->esi = M32(m->esp); m->esp += 4;	/* 496b0d: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496b0e: add esp, 0x100 */
	m->esp += 4 + 0; return;	/* 496b14: ret  */
L_496b15:
	m->ecx = m->esi;	/* 496b15: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x496b1cu; native_call(m, 0x4625a0u);	/* 496b17: call 0x4625a0 */
	{ DWORD a_ = M32((DWORD)(m->eax + 0x14cu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 496b1c: cmp dword ptr [eax + 0x14c], 1 */
	if (!m->zf) goto L_496b78;	/* 496b23: jne 0x496b78 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496b25: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496b2a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496b2f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496b34: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x496b3eu; native_call(m, 0x44ad30u);	/* 496b39: call 0x44ad30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496b3e: add esp, 0x10 */
	m->ecx = m->esi;	/* 496b41: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x496b48u; native_call(m, 0x4625a0u);	/* 496b43: call 0x4625a0 */
	{ DWORD a_ = m->eax, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 496b48: add eax, 0x98 */
	m->edx = (DWORD)(m->esp + 0x4u);	/* 496b4d: lea edx, [esp + 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 496b51: push eax */
	{ DWORD v_ = 0x4d04c0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496b52: push 0x4d04c0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 496b57: push edx */
	m->esp -= 4; M32(m->esp) = 0x496b5du; native_call(m, 0x49e9ddu);	/* 496b58: call 0x49e9dd */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 496b5d: lea eax, [esp + 0x10] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 496b61: push 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 496b63: push eax */
	{ DWORD v_ = 0x280u; m->esp -= 4; M32(m->esp) = v_; }	/* 496b64: push 0x280 */
	{ DWORD v_ = 0x192u; m->esp -= 4; M32(m->esp) = v_; }	/* 496b69: push 0x192 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496b6e: push 0 */
	m->esp -= 4; M32(m->esp) = 0x496b75u; native_call(m, 0x44ae10u);	/* 496b70: call 0x44ae10 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496b75: add esp, 0x20 */
L_496b78:
	m->esi = M32(m->esp); m->esp += 4;	/* 496b78: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496b79: add esp, 0x100 */
	m->esp += 4 + 0; return;	/* 496b7f: ret  */
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
