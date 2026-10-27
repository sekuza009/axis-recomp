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

static void lift_41e8b0(X86 *m);
static void lift_41e9d0(X86 *m);
static void lift_41eb00(X86 *m);
static void lift_4036c0(X86 *m);
static void lift_443950(X86 *m);
static void lift_434490(X86 *m);
static void lift_447750(X86 *m);
static void lift_462b50(X86 *m);
static void lift_462c30(X86 *m);
static void lift_462850(X86 *m);
static void lift_453a10(X86 *m);
static void lift_41ec50(X86 *m);

/* game_returnToMenus_41ec50 (0x41ec50), lifted by tools/lift.py */
static void lift_41ec50(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41ec50: push esi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 41ec51: xor esi, esi */
	M32((DWORD)(0x67ef14u)) = m->esi;	/* 41ec53: mov dword ptr [0x67ef14], esi */
	M32((DWORD)(0x5ae9c4u)) = m->esi;	/* 41ec59: mov dword ptr [0x5ae9c4], esi */
	m->esp -= 4; M32(m->esp) = 0x41ec64u; native_call(m, 0x452fe0u);	/* 41ec5f: call 0x452fe0 */
	m->esp -= 4; M32(m->esp) = 0x41ec69u; native_call(m, 0x451e60u);	/* 41ec64: call 0x451e60 */
	M32((DWORD)(0x4dbbf4u)) = m->esi;	/* 41ec69: mov dword ptr [0x4dbbf4], esi */
	m->eax = 0x9f9844u;	/* 41ec6f: mov eax, 0x9f9844 */
L_41ec74:
	M32((DWORD)(m->eax + 0xfffffffcu)) = m->esi;	/* 41ec74: mov dword ptr [eax - 4], esi */
	M32((DWORD)(m->eax + 0x0u)) = m->esi;	/* 41ec77: mov dword ptr [eax], esi */
	{ DWORD a_ = m->eax, b_ = 0x410u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41ec79: add eax, 0x410 */
	{ DWORD a_ = m->eax, b_ = 0x9fd944u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41ec7e: cmp eax, 0x9fd944 */
	if (m->sf != m->of) goto L_41ec74;	/* 41ec83: jl 0x41ec74 */
	m->eax = 0x1f4u;	/* 41ec85: mov eax, 0x1f4 */
	M32((DWORD)(0x76d3e8u)) = m->eax;	/* 41ec8a: mov dword ptr [0x76d3e8], eax */
	M32((DWORD)(0x67ef20u)) = m->eax;	/* 41ec8f: mov dword ptr [0x67ef20], eax */
	m->esp -= 4; M32(m->esp) = 0x41ec99u; native_call(m, 0x4411e0u);	/* 41ec94: call 0x4411e0 */
	m->esp -= 4; M32(m->esp) = 0x41ec9eu; native_call(m, 0x441200u);	/* 41ec99: call 0x441200 */
	m->eax = M32((DWORD)(0x68039cu));	/* 41ec9e: mov eax, dword ptr [0x68039c] */
	M32((DWORD)(0x4df028u)) = 0x0u;	/* 41eca3: mov dword ptr [0x4df028], 0 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41ecad: cmp eax, 1 */
	M32((DWORD)(0x4df024u)) = 0x0u;	/* 41ecb0: mov dword ptr [0x4df024], 0 */
	M32((DWORD)(0x4df02cu)) = 0xc3e10000u;	/* 41ecba: mov dword ptr [0x4df02c], 0xc3e10000 */
	M32((DWORD)(0x680378u)) = 0x0u;	/* 41ecc4: mov dword ptr [0x680378], 0 */
	M32((DWORD)(0x68037cu)) = 0x0u;	/* 41ecce: mov dword ptr [0x68037c], 0 */
	M32((DWORD)(0x680380u)) = 0xc4098000u;	/* 41ecd8: mov dword ptr [0x680380], 0xc4098000 */
	M32((DWORD)(0x680370u)) = m->esi;	/* 41ece2: mov dword ptr [0x680370], esi */
	M32((DWORD)(0x4df8e0u)) = m->esi;	/* 41ece8: mov dword ptr [0x4df8e0], esi */
	M32((DWORD)(0x9dd930u)) = 0x0u;	/* 41ecee: mov dword ptr [0x9dd930], 0 */
	M32((DWORD)(0x9dd934u)) = 0x0u;	/* 41ecf8: mov dword ptr [0x9dd934], 0 */
	M32((DWORD)(0x9dd938u)) = 0xc3e10000u;	/* 41ed02: mov dword ptr [0x9dd938], 0xc3e10000 */
	M32((DWORD)(0x9dd918u)) = 0x0u;	/* 41ed0c: mov dword ptr [0x9dd918], 0 */
	M32((DWORD)(0x9dd91cu)) = 0x0u;	/* 41ed16: mov dword ptr [0x9dd91c], 0 */
	M32((DWORD)(0x9dd920u)) = 0xc4098000u;	/* 41ed20: mov dword ptr [0x9dd920], 0xc4098000 */
	M32((DWORD)(0x4deb48u)) = m->esi;	/* 41ed2a: mov dword ptr [0x4deb48], esi */
	M32((DWORD)(0x9db990u)) = m->esi;	/* 41ed30: mov dword ptr [0x9db990], esi */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 41ed36: mov dword ptr [0x4dda44], 0 */
	M32((DWORD)(0x4dda48u)) = 0x0u;	/* 41ed40: mov dword ptr [0x4dda48], 0 */
	if (!m->zf) goto L_41ed65;	/* 41ed4a: jne 0x41ed65 */
	M32((DWORD)(0x68039cu)) = m->esi;	/* 41ed4c: mov dword ptr [0x68039c], esi */
	m->esp -= 4; M32(m->esp) = 0x41ed57u; native_call(m, 0x431590u);	/* 41ed52: call 0x431590 */
	m->eax = M32((DWORD)(0x4ded18u));	/* 41ed57: mov eax, dword ptr [0x4ded18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41ed5c: push eax */
	m->esp -= 4; M32(m->esp) = 0x41ed62u; native_call(m, 0x401310u);	/* 41ed5d: call 0x401310 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41ed62: add esp, 4 */
L_41ed65:
	m->esi = M32(m->esp); m->esp += 4;	/* 41ed65: pop esi */
	m->esp += 4 + 0; return;	/* 41ed66: ret  */
}

/* game_returnToMenus_41e8b0 (0x41e8b0), lifted by tools/lift.py */
static void lift_41e8b0(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41e8b0: push esi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 41e8b1: xor esi, esi */
	M32((DWORD)(0x67ef14u)) = m->esi;	/* 41e8b3: mov dword ptr [0x67ef14], esi */
	M32((DWORD)(0x5ae9c4u)) = m->esi;	/* 41e8b9: mov dword ptr [0x5ae9c4], esi */
	m->esp -= 4; M32(m->esp) = 0x41e8c4u; native_call(m, 0x452fe0u);	/* 41e8bf: call 0x452fe0 */
	m->esp -= 4; M32(m->esp) = 0x41e8c9u; native_call(m, 0x451e60u);	/* 41e8c4: call 0x451e60 */
	M32((DWORD)(0x4dbbf4u)) = m->esi;	/* 41e8c9: mov dword ptr [0x4dbbf4], esi */
	m->eax = 0x9f9844u;	/* 41e8cf: mov eax, 0x9f9844 */
L_41e8d4:
	M32((DWORD)(m->eax + 0xfffffffcu)) = m->esi;	/* 41e8d4: mov dword ptr [eax - 4], esi */
	M32((DWORD)(m->eax + 0x0u)) = m->esi;	/* 41e8d7: mov dword ptr [eax], esi */
	{ DWORD a_ = m->eax, b_ = 0x410u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41e8d9: add eax, 0x410 */
	{ DWORD a_ = m->eax, b_ = 0x9fd944u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41e8de: cmp eax, 0x9fd944 */
	if (m->sf != m->of) goto L_41e8d4;	/* 41e8e3: jl 0x41e8d4 */
	m->eax = 0x12cu;	/* 41e8e5: mov eax, 0x12c */
	M32((DWORD)(0x76d3e8u)) = m->eax;	/* 41e8ea: mov dword ptr [0x76d3e8], eax */
	M32((DWORD)(0x67ef20u)) = m->eax;	/* 41e8ef: mov dword ptr [0x67ef20], eax */
	m->esp -= 4; M32(m->esp) = 0x41e8f9u; native_call(m, 0x4411e0u);	/* 41e8f4: call 0x4411e0 */
	m->ecx = M32((DWORD)(0x68039cu));	/* 41e8f9: mov ecx, dword ptr [0x68039c] */
	m->eax = 0x1u;	/* 41e8ff: mov eax, 1 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41e904: cmp ecx, eax */
	M32((DWORD)(0x4df028u)) = 0x0u;	/* 41e906: mov dword ptr [0x4df028], 0 */
	M32((DWORD)(0x4df024u)) = 0x0u;	/* 41e910: mov dword ptr [0x4df024], 0 */
	M32((DWORD)(0x4df02cu)) = 0x43fa0000u;	/* 41e91a: mov dword ptr [0x4df02c], 0x43fa0000 */
	M32((DWORD)(0x680378u)) = 0x0u;	/* 41e924: mov dword ptr [0x680378], 0 */
	M32((DWORD)(0x68037cu)) = 0x0u;	/* 41e92e: mov dword ptr [0x68037c], 0 */
	M32((DWORD)(0x680380u)) = 0x43c80000u;	/* 41e938: mov dword ptr [0x680380], 0x43c80000 */
	M32((DWORD)(0x680370u)) = 0x2u;	/* 41e942: mov dword ptr [0x680370], 2 */
	M32((DWORD)(0x4df8e0u)) = m->esi;	/* 41e94c: mov dword ptr [0x4df8e0], esi */
	M32((DWORD)(0x9dd930u)) = 0x0u;	/* 41e952: mov dword ptr [0x9dd930], 0 */
	M32((DWORD)(0x9dd934u)) = 0x0u;	/* 41e95c: mov dword ptr [0x9dd934], 0 */
	M32((DWORD)(0x9dd938u)) = 0x43fa0000u;	/* 41e966: mov dword ptr [0x9dd938], 0x43fa0000 */
	M32((DWORD)(0x9dd918u)) = 0x0u;	/* 41e970: mov dword ptr [0x9dd918], 0 */
	M32((DWORD)(0x9dd91cu)) = 0x0u;	/* 41e97a: mov dword ptr [0x9dd91c], 0 */
	M32((DWORD)(0x9dd920u)) = 0x43c80000u;	/* 41e984: mov dword ptr [0x9dd920], 0x43c80000 */
	M32((DWORD)(0x4deb48u)) = m->eax;	/* 41e98e: mov dword ptr [0x4deb48], eax */
	M32((DWORD)(0x9db990u)) = m->esi;	/* 41e993: mov dword ptr [0x9db990], esi */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 41e999: mov dword ptr [0x4dda44], 0 */
	M32((DWORD)(0x4dda48u)) = 0x0u;	/* 41e9a3: mov dword ptr [0x4dda48], 0 */
	M32((DWORD)(0x4e1868u)) = m->esi;	/* 41e9ad: mov dword ptr [0x4e1868], esi */
	if (!m->zf) goto L_41e9ce;	/* 41e9b3: jne 0x41e9ce */
	M32((DWORD)(0x68039cu)) = m->esi;	/* 41e9b5: mov dword ptr [0x68039c], esi */
	m->esp -= 4; M32(m->esp) = 0x41e9c0u; native_call(m, 0x431590u);	/* 41e9bb: call 0x431590 */
	m->eax = M32((DWORD)(0x4ded18u));	/* 41e9c0: mov eax, dword ptr [0x4ded18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41e9c5: push eax */
	m->esp -= 4; M32(m->esp) = 0x41e9cbu; native_call(m, 0x401310u);	/* 41e9c6: call 0x401310 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41e9cb: add esp, 4 */
L_41e9ce:
	m->esi = M32(m->esp); m->esp += 4;	/* 41e9ce: pop esi */
	m->esp += 4 + 0; return;	/* 41e9cf: ret  */
}

/* game_returnToMenus_41e9d0 (0x41e9d0), lifted by tools/lift.py */
static void lift_41e9d0(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41e9d0: push esi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 41e9d1: xor esi, esi */
	M32((DWORD)(0x67ef14u)) = m->esi;	/* 41e9d3: mov dword ptr [0x67ef14], esi */
	M32((DWORD)(0x5ae9c4u)) = m->esi;	/* 41e9d9: mov dword ptr [0x5ae9c4], esi */
	m->esp -= 4; M32(m->esp) = 0x41e9e4u; native_call(m, 0x452fe0u);	/* 41e9df: call 0x452fe0 */
	m->esp -= 4; M32(m->esp) = 0x41e9e9u; native_call(m, 0x451e60u);	/* 41e9e4: call 0x451e60 */
	M32((DWORD)(0x4dbbf4u)) = m->esi;	/* 41e9e9: mov dword ptr [0x4dbbf4], esi */
	m->eax = 0x9f9844u;	/* 41e9ef: mov eax, 0x9f9844 */
L_41e9f4:
	M32((DWORD)(m->eax + 0xfffffffcu)) = m->esi;	/* 41e9f4: mov dword ptr [eax - 4], esi */
	M32((DWORD)(m->eax + 0x0u)) = m->esi;	/* 41e9f7: mov dword ptr [eax], esi */
	{ DWORD a_ = m->eax, b_ = 0x410u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41e9f9: add eax, 0x410 */
	{ DWORD a_ = m->eax, b_ = 0x9fd944u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41e9fe: cmp eax, 0x9fd944 */
	if (m->sf != m->of) goto L_41e9f4;	/* 41ea03: jl 0x41e9f4 */
	m->eax = 0x12cu;	/* 41ea05: mov eax, 0x12c */
	M32((DWORD)(0x67ef20u)) = 0x190u;	/* 41ea0a: mov dword ptr [0x67ef20], 0x190 */
	M32((DWORD)(0x76d3e8u)) = m->eax;	/* 41ea14: mov dword ptr [0x76d3e8], eax */
	M32((DWORD)(0x67ef0cu)) = m->eax;	/* 41ea19: mov dword ptr [0x67ef0c], eax */
	m->esp -= 4; M32(m->esp) = 0x41ea23u; native_call(m, 0x4411e0u);	/* 41ea1e: call 0x4411e0 */
	m->esp -= 4; M32(m->esp) = 0x41ea28u; native_call(m, 0x441200u);	/* 41ea23: call 0x441200 */
	m->eax = M32((DWORD)(0x68039cu));	/* 41ea28: mov eax, dword ptr [0x68039c] */
	M32((DWORD)(0x4df028u)) = 0x0u;	/* 41ea2d: mov dword ptr [0x4df028], 0 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41ea37: cmp eax, 1 */
	M32((DWORD)(0x4df024u)) = 0x0u;	/* 41ea3a: mov dword ptr [0x4df024], 0 */
	M32((DWORD)(0x4df02cu)) = 0xc3e10000u;	/* 41ea44: mov dword ptr [0x4df02c], 0xc3e10000 */
	M32((DWORD)(0x680378u)) = 0x0u;	/* 41ea4e: mov dword ptr [0x680378], 0 */
	M32((DWORD)(0x68037cu)) = 0x0u;	/* 41ea58: mov dword ptr [0x68037c], 0 */
	M32((DWORD)(0x680380u)) = 0xc4098000u;	/* 41ea62: mov dword ptr [0x680380], 0xc4098000 */
	M32((DWORD)(0x680370u)) = 0x2u;	/* 41ea6c: mov dword ptr [0x680370], 2 */
	M32((DWORD)(0x4df8e0u)) = m->esi;	/* 41ea76: mov dword ptr [0x4df8e0], esi */
	M32((DWORD)(0x9dd930u)) = 0x0u;	/* 41ea7c: mov dword ptr [0x9dd930], 0 */
	M32((DWORD)(0x9dd934u)) = 0x0u;	/* 41ea86: mov dword ptr [0x9dd934], 0 */
	M32((DWORD)(0x9dd938u)) = 0xc3e10000u;	/* 41ea90: mov dword ptr [0x9dd938], 0xc3e10000 */
	M32((DWORD)(0x9dd918u)) = 0x0u;	/* 41ea9a: mov dword ptr [0x9dd918], 0 */
	M32((DWORD)(0x9dd91cu)) = 0x0u;	/* 41eaa4: mov dword ptr [0x9dd91c], 0 */
	M32((DWORD)(0x9dd920u)) = 0xc4098000u;	/* 41eaae: mov dword ptr [0x9dd920], 0xc4098000 */
	M32((DWORD)(0x4deb48u)) = m->esi;	/* 41eab8: mov dword ptr [0x4deb48], esi */
	M32((DWORD)(0x9db990u)) = m->esi;	/* 41eabe: mov dword ptr [0x9db990], esi */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 41eac4: mov dword ptr [0x4dda44], 0 */
	M32((DWORD)(0x4dda48u)) = 0x0u;	/* 41eace: mov dword ptr [0x4dda48], 0 */
	if (!m->zf) goto L_41eaf3;	/* 41ead8: jne 0x41eaf3 */
	M32((DWORD)(0x68039cu)) = m->esi;	/* 41eada: mov dword ptr [0x68039c], esi */
	m->esp -= 4; M32(m->esp) = 0x41eae5u; native_call(m, 0x431590u);	/* 41eae0: call 0x431590 */
	m->eax = M32((DWORD)(0x4ded18u));	/* 41eae5: mov eax, dword ptr [0x4ded18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41eaea: push eax */
	m->esp -= 4; M32(m->esp) = 0x41eaf0u; native_call(m, 0x401310u);	/* 41eaeb: call 0x401310 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41eaf0: add esp, 4 */
L_41eaf3:
	m->esi = M32(m->esp); m->esp += 4;	/* 41eaf3: pop esi */
	m->esp += 4 + 0; return;	/* 41eaf4: ret  */
}

/* game_returnToMenus_41eb00 (0x41eb00), lifted by tools/lift.py */
static void lift_41eb00(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41eb00: push esi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 41eb01: xor esi, esi */
	M32((DWORD)(0x67ef14u)) = m->esi;	/* 41eb03: mov dword ptr [0x67ef14], esi */
	M32((DWORD)(0x5ae9c4u)) = 0x2u;	/* 41eb09: mov dword ptr [0x5ae9c4], 2 */
	m->esp -= 4; M32(m->esp) = 0x41eb18u; native_call(m, 0x452fe0u);	/* 41eb13: call 0x452fe0 */
	M32((DWORD)(0x4dbbf4u)) = m->esi;	/* 41eb18: mov dword ptr [0x4dbbf4], esi */
	m->eax = 0x9f9844u;	/* 41eb1e: mov eax, 0x9f9844 */
L_41eb23:
	M32((DWORD)(m->eax + 0xfffffffcu)) = m->esi;	/* 41eb23: mov dword ptr [eax - 4], esi */
	M32((DWORD)(m->eax + 0x0u)) = m->esi;	/* 41eb26: mov dword ptr [eax], esi */
	{ DWORD a_ = m->eax, b_ = 0x410u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41eb28: add eax, 0x410 */
	{ DWORD a_ = m->eax, b_ = 0x9fd944u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41eb2d: cmp eax, 0x9fd944 */
	if (m->sf != m->of) goto L_41eb23;	/* 41eb32: jl 0x41eb23 */
	m->eax = 0x320u;	/* 41eb34: mov eax, 0x320 */
	M32((DWORD)(0x9dd834u)) = 0x63u;	/* 41eb39: mov dword ptr [0x9dd834], 0x63 */
	M32((DWORD)(0x76d3e8u)) = m->eax;	/* 41eb43: mov dword ptr [0x76d3e8], eax */
	M32((DWORD)(0x67ef20u)) = m->eax;	/* 41eb48: mov dword ptr [0x67ef20], eax */
	M32((DWORD)(0x67ef0cu)) = m->eax;	/* 41eb4d: mov dword ptr [0x67ef0c], eax */
	m->esp -= 4; M32(m->esp) = 0x41eb57u; native_call(m, 0x4411e0u);	/* 41eb52: call 0x4411e0 */
	m->esp -= 4; M32(m->esp) = 0x41eb5cu; native_call(m, 0x441200u);	/* 41eb57: call 0x441200 */
	m->eax = M32((DWORD)(0x68039cu));	/* 41eb5c: mov eax, dword ptr [0x68039c] */
	M32((DWORD)(0x4df028u)) = 0x0u;	/* 41eb61: mov dword ptr [0x4df028], 0 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41eb6b: cmp eax, 1 */
	M32((DWORD)(0x4df024u)) = 0x0u;	/* 41eb6e: mov dword ptr [0x4df024], 0 */
	M32((DWORD)(0x4df02cu)) = 0xc3e10000u;	/* 41eb78: mov dword ptr [0x4df02c], 0xc3e10000 */
	M32((DWORD)(0x680378u)) = 0x0u;	/* 41eb82: mov dword ptr [0x680378], 0 */
	M32((DWORD)(0x68037cu)) = 0x0u;	/* 41eb8c: mov dword ptr [0x68037c], 0 */
	M32((DWORD)(0x680380u)) = 0xc4098000u;	/* 41eb96: mov dword ptr [0x680380], 0xc4098000 */
	M32((DWORD)(0x680370u)) = 0x2u;	/* 41eba0: mov dword ptr [0x680370], 2 */
	M32((DWORD)(0x4df8e0u)) = m->esi;	/* 41ebaa: mov dword ptr [0x4df8e0], esi */
	M32((DWORD)(0x9dd930u)) = 0x0u;	/* 41ebb0: mov dword ptr [0x9dd930], 0 */
	M32((DWORD)(0x9dd934u)) = 0x0u;	/* 41ebba: mov dword ptr [0x9dd934], 0 */
	M32((DWORD)(0x9dd938u)) = 0xc3e10000u;	/* 41ebc4: mov dword ptr [0x9dd938], 0xc3e10000 */
	M32((DWORD)(0x9dd918u)) = 0x0u;	/* 41ebce: mov dword ptr [0x9dd918], 0 */
	M32((DWORD)(0x9dd91cu)) = 0x0u;	/* 41ebd8: mov dword ptr [0x9dd91c], 0 */
	M32((DWORD)(0x9dd920u)) = 0xc4098000u;	/* 41ebe2: mov dword ptr [0x9dd920], 0xc4098000 */
	M32((DWORD)(0x4deb48u)) = m->esi;	/* 41ebec: mov dword ptr [0x4deb48], esi */
	M32((DWORD)(0x9db990u)) = m->esi;	/* 41ebf2: mov dword ptr [0x9db990], esi */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 41ebf8: mov dword ptr [0x4dda44], 0 */
	M32((DWORD)(0x4dda48u)) = 0x0u;	/* 41ec02: mov dword ptr [0x4dda48], 0 */
	if (!m->zf) goto L_41ec27;	/* 41ec0c: jne 0x41ec27 */
	M32((DWORD)(0x68039cu)) = m->esi;	/* 41ec0e: mov dword ptr [0x68039c], esi */
	m->esp -= 4; M32(m->esp) = 0x41ec19u; native_call(m, 0x431590u);	/* 41ec14: call 0x431590 */
	m->eax = M32((DWORD)(0x4ded18u));	/* 41ec19: mov eax, dword ptr [0x4ded18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41ec1e: push eax */
	m->esp -= 4; M32(m->esp) = 0x41ec24u; native_call(m, 0x401310u);	/* 41ec1f: call 0x401310 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41ec24: add esp, 4 */
L_41ec27:
	M32((DWORD)(0x9dced0u)) = m->esi;	/* 41ec27: mov dword ptr [0x9dced0], esi */
	M32((DWORD)(0x4ded54u)) = m->esi;	/* 41ec2d: mov dword ptr [0x4ded54], esi */
	M32((DWORD)(0x9dd1c8u)) = m->esi;	/* 41ec33: mov dword ptr [0x9dd1c8], esi */
	M32((DWORD)(0x9dd350u)) = m->esi;	/* 41ec39: mov dword ptr [0x9dd350], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 41ec3f: pop esi */
	m->esp += 4 + 0; return;	/* 41ec40: ret  */
}

/* room_4036c0 (0x4036c0), lifted by tools/lift.py */
static void lift_4036c0(X86 *m)
{
	m->eax = M32((DWORD)(0x4ded88u));	/* 4036c0: mov eax, dword ptr [0x4ded88] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4036c5: test eax, eax */
	if (m->zf) goto L_403794;	/* 4036c7: je 0x403794 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 4036cd: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 4036d2: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4036d8: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4036d9: push ecx */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 4036da: mov dword ptr [0x4dda44], 0 */
	m->esp -= 4; M32(m->esp) = 0x4036e9u; native_call(m, 0x4033e0u);	/* 4036e4: call 0x4033e0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4036e9: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x19u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4036ec: cmp eax, 0x19 */
	if (!m->cf && !m->zf) goto L_403794;	/* 4036ef: ja 0x403794 */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4036f5: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x403854u))) & 0xff) << 0);	/* 4036f7: mov dl, byte ptr [eax + 0x403854] */
	switch (m->edx) { case 0: goto L_403704; case 1: goto L_403717; case 2: goto L_40372c; case 3: goto L_403747; case 4: goto L_40376b; case 5: goto L_403772; case 6: goto L_403779; case 7: goto L_403780; default: abort(); }	/* 4036fd: jmp dword ptr [edx*4 + 0x403834] */
L_403704:
	m->ecx = M32((DWORD)(0x4d7350u));	/* 403704: mov ecx, dword ptr [0x4d7350] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40370a: add ecx, eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40370c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x403712u; native_call(m, 0x403560u);	/* 40370d: call 0x403560 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 403712: add esp, 4 */
	goto L_403794;	/* 403715: jmp 0x403794 */
L_403717:
	m->edx = M32((DWORD)(0x4d7350u));	/* 403717: mov edx, dword ptr [0x4d7350] */
	m->eax = (DWORD)(m->edx + m->eax*1 + 0xfffffff6u);	/* 40371d: lea eax, [edx + eax - 0xa] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 403721: push eax */
	m->esp -= 4; M32(m->esp) = 0x403727u; native_call(m, 0x403590u);	/* 403722: call 0x403590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 403727: add esp, 4 */
	goto L_403794;	/* 40372a: jmp 0x403794 */
L_40372c:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 40372c: push 2 */
	m->esp -= 4; M32(m->esp) = 0x403733u; native_call(m, 0x41e760u);	/* 40372e: call 0x41e760 */
	m->eax = M32((DWORD)(0x4d7350u));	/* 403733: mov eax, dword ptr [0x4d7350] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 403738: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40373b: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_403794;	/* 40373d: jle 0x403794 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 40373f: dec eax */
	M32((DWORD)(0x4d7350u)) = m->eax;	/* 403740: mov dword ptr [0x4d7350], eax */
	goto L_403794;	/* 403745: jmp 0x403794 */
L_403747:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 403747: push 2 */
	m->esp -= 4; M32(m->esp) = 0x40374eu; native_call(m, 0x41e760u);	/* 403749: call 0x41e760 */
	m->ecx = M32((DWORD)(0x4d7350u));	/* 40374e: mov ecx, dword ptr [0x4d7350] */
	m->eax = M32((DWORD)(0x67ef00u));	/* 403754: mov eax, dword ptr [0x67ef00] */
	{ DWORD a_ = m->ecx, b_ = 0xau & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 403759: add ecx, 0xa */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40375c: add esp, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40375f: cmp ecx, eax */
	if (m->sf == m->of) goto L_403794;	/* 403761: jge 0x403794 */
	{ DWORD a_ = M32((DWORD)(0x4d7350u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(0x4d7350u)) = r_; }	/* 403763: inc dword ptr [0x4d7350] */
	goto L_403794;	/* 403769: jmp 0x403794 */
L_40376b:
	m->esp -= 4; M32(m->esp) = 0x403770u; native_call(m, 0x403530u);	/* 40376b: call 0x403530 */
	goto L_403794;	/* 403770: jmp 0x403794 */
L_403772:
	m->esp -= 4; M32(m->esp) = 0x403777u; native_call(m, 0x4034e0u);	/* 403772: call 0x4034e0 */
	goto L_403794;	/* 403777: jmp 0x403794 */
L_403779:
	m->esp -= 4; M32(m->esp) = 0x40377eu; native_call(m, 0x403640u);	/* 403779: call 0x403640 */
	goto L_403794;	/* 40377e: jmp 0x403794 */
L_403780:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 403780: push 0 */
	m->esp -= 4; M32(m->esp) = 0x403787u; native_call(m, 0x41e760u);	/* 403782: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 403787: add esp, 4 */
	M32((DWORD)(0x4db508u)) = 0x0u;	/* 40378a: mov dword ptr [0x4db508], 0 */
L_403794:
	m->eax = M32((DWORD)(0x4ded94u));	/* 403794: mov eax, dword ptr [0x4ded94] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 403799: test eax, eax */
	if (m->zf) goto L_403832;	/* 40379b: je 0x403832 */
	{ DWORD a_ = M32((DWORD)(0x4dbb3cu)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4037a1: cmp dword ptr [0x4dbb3c], 2 */
	if (!m->zf) goto L_403832;	/* 4037a8: jne 0x403832 */
	m->edx = M32((DWORD)(0x4ded6cu));	/* 4037ae: mov edx, dword ptr [0x4ded6c] */
	m->eax = M32((DWORD)(0x4ded68u));	/* 4037b4: mov eax, dword ptr [0x4ded68] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4037b9: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4037ba: push eax */
	m->esp -= 4; M32(m->esp) = 0x4037c0u; native_call(m, 0x4033e0u);	/* 4037bb: call 0x4033e0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4037c0: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x14u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4037c3: sub eax, 0x14 */
	if (m->zf) goto L_403806;	/* 4037c6: je 0x403806 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4037c8: dec eax */
	if (!m->zf) goto L_403832;	/* 4037c9: jne 0x403832 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dda44u)));	/* 4037cb: fld dword ptr [0x4dda44] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93d0u)); FPOP();	/* 4037d1: fcomp dword ptr [0x4a93d0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4037d7: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4037d9: test ah, 1 */
	if (!m->zf) goto L_403832;	/* 4037dc: jne 0x403832 */
	m->ecx = M32((DWORD)(0x4d7350u));	/* 4037de: mov ecx, dword ptr [0x4d7350] */
	m->eax = M32((DWORD)(0x67ef00u));	/* 4037e4: mov eax, dword ptr [0x67ef00] */
	{ DWORD a_ = m->ecx, b_ = 0xau & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4037e9: add ecx, 0xa */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4037ec: cmp ecx, eax */
	if (m->sf == m->of) goto L_403828;	/* 4037ee: jge 0x403828 */
	m->eax = M32((DWORD)(0x4d7350u));	/* 4037f0: mov eax, dword ptr [0x4d7350] */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 4037f5: mov dword ptr [0x4dda44], 0 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4037ff: inc eax */
	M32((DWORD)(0x4d7350u)) = m->eax;	/* 403800: mov dword ptr [0x4d7350], eax */
	m->esp += 4 + 0; return;	/* 403805: ret  */
L_403806:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dda44u)));	/* 403806: fld dword ptr [0x4dda44] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93d0u)); FPOP();	/* 40380c: fcomp dword ptr [0x4a93d0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 403812: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 403814: test ah, 1 */
	if (!m->zf) goto L_403832;	/* 403817: jne 0x403832 */
	m->eax = M32((DWORD)(0x4d7350u));	/* 403819: mov eax, dword ptr [0x4d7350] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40381e: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_403828;	/* 403820: jle 0x403828 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 403822: dec eax */
	M32((DWORD)(0x4d7350u)) = m->eax;	/* 403823: mov dword ptr [0x4d7350], eax */
L_403828:
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 403828: mov dword ptr [0x4dda44], 0 */
L_403832:
	m->esp += 4 + 0; return;	/* 403832: ret  */
}

/* menuState900_enterSkirmish (0x443950), lifted by tools/lift.py */
static void lift_443950(X86 *m)
{
	m->eax = 0x384u;	/* 443950: mov eax, 0x384 */
	M32((DWORD)(0x4df024u)) = 0x0u;	/* 443955: mov dword ptr [0x4df024], 0 */
	M32((DWORD)(0x4df028u)) = 0x0u;	/* 44395f: mov dword ptr [0x4df028], 0 */
	M32((DWORD)(0x4df02cu)) = 0xc3e10000u;	/* 443969: mov dword ptr [0x4df02c], 0xc3e10000 */
	M32((DWORD)(0x680378u)) = 0x0u;	/* 443973: mov dword ptr [0x680378], 0 */
	M32((DWORD)(0x68037cu)) = 0x0u;	/* 44397d: mov dword ptr [0x68037c], 0 */
	M32((DWORD)(0x680380u)) = 0xc4098000u;	/* 443987: mov dword ptr [0x680380], 0xc4098000 */
	M32((DWORD)(0x9f16a8u)) = 0xau;	/* 443991: mov dword ptr [0x9f16a8], 0xa */
	M32((DWORD)(0x9f16acu)) = 0x14u;	/* 44399b: mov dword ptr [0x9f16ac], 0x14 */
	M32((DWORD)(0x9f16b0u)) = 0x276u;	/* 4439a5: mov dword ptr [0x9f16b0], 0x276 */
	M32((DWORD)(0x9f16b4u)) = 0x1ccu;	/* 4439af: mov dword ptr [0x9f16b4], 0x1cc */
	M32((DWORD)(0x9ef208u)) = 0x0u;	/* 4439b9: mov dword ptr [0x9ef208], 0 */
	M32((DWORD)(0x9ef20cu)) = 0x3f800000u;	/* 4439c3: mov dword ptr [0x9ef20c], 0x3f800000 */
	M32((DWORD)(0x9ef210u)) = 0x3f800000u;	/* 4439cd: mov dword ptr [0x9ef210], 0x3f800000 */
	M32((DWORD)(0x9ef214u)) = 0x3f800000u;	/* 4439d7: mov dword ptr [0x9ef214], 0x3f800000 */
	M32((DWORD)(0x9eeac8u)) = 0x0u;	/* 4439e1: mov dword ptr [0x9eeac8], 0 */
	M32((DWORD)(0x9eeaccu)) = 0x3f19999au;	/* 4439eb: mov dword ptr [0x9eeacc], 0x3f19999a */
	M32((DWORD)(0x9eead0u)) = 0x3f19999au;	/* 4439f5: mov dword ptr [0x9eead0], 0x3f19999a */
	M32((DWORD)(0x9eead4u)) = 0x3f800000u;	/* 4439ff: mov dword ptr [0x9eead4], 0x3f800000 */
	M32((DWORD)(0x4df870u)) = 0x0u;	/* 443a09: mov dword ptr [0x4df870], 0 */
	M32((DWORD)(0x4df874u)) = 0x0u;	/* 443a13: mov dword ptr [0x4df874], 0 */
	M32((DWORD)(0x4df878u)) = 0x42c80000u;	/* 443a1d: mov dword ptr [0x4df878], 0x42c80000 */
	M32((DWORD)(0x76d388u)) = 0x0u;	/* 443a27: mov dword ptr [0x76d388], 0 */
	M32((DWORD)(0x76d38cu)) = 0x0u;	/* 443a31: mov dword ptr [0x76d38c], 0 */
	M32((DWORD)(0x76d390u)) = 0x0u;	/* 443a3b: mov dword ptr [0x76d390], 0 */
	M32((DWORD)(0x9db090u)) = 0x0u;	/* 443a45: mov dword ptr [0x9db090], 0 */
	M32((DWORD)(0x9db094u)) = 0x0u;	/* 443a4f: mov dword ptr [0x9db094], 0 */
	M32((DWORD)(0x9db098u)) = 0xc3e10000u;	/* 443a59: mov dword ptr [0x9db098], 0xc3e10000 */
	M32((DWORD)(0x76d3f8u)) = 0x0u;	/* 443a63: mov dword ptr [0x76d3f8], 0 */
	M32((DWORD)(0x76d3fcu)) = 0x0u;	/* 443a6d: mov dword ptr [0x76d3fc], 0 */
	M32((DWORD)(0x76d400u)) = 0xc4098000u;	/* 443a77: mov dword ptr [0x76d400], 0xc4098000 */
	M32((DWORD)(0x9ef1f0u)) = 0x1u;	/* 443a81: mov dword ptr [0x9ef1f0], 1 */
	M32((DWORD)(0x76d3e8u)) = m->eax;	/* 443a8b: mov dword ptr [0x76d3e8], eax */
	M32((DWORD)(0x67ef0cu)) = m->eax;	/* 443a90: mov dword ptr [0x67ef0c], eax */
	M32((DWORD)(0x67ef20u)) = m->eax;	/* 443a95: mov dword ptr [0x67ef20], eax */
	m->esp -= 4; M32(m->esp) = 0x443a9fu; native_call(m, 0x4437b0u);	/* 443a9a: call 0x4437b0 */
	m->esp -= 4; M32(m->esp) = 0x443aa4u; native_call(m, 0x443840u);	/* 443a9f: call 0x443840 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 443aa4: push 4 */
	M32((DWORD)(0x9eeba8u)) = 0x1u;	/* 443aa6: mov dword ptr [0x9eeba8], 1 */
	M32((DWORD)(0x9ef1f8u)) = 0xau;	/* 443ab0: mov dword ptr [0x9ef1f8], 0xa */
	m->esp -= 4; M32(m->esp) = 0x443abfu; native_call(m, 0x41e760u);	/* 443aba: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443abf: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x443ac7u; native_call(m, 0x4435f0u);	/* 443ac2: call 0x4435f0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 443ac7: xor eax, eax */
	M32((DWORD)(0x9f16bcu)) = m->eax;	/* 443ac9: mov dword ptr [0x9f16bc], eax */
	M32((DWORD)(0x9f1058u)) = m->eax;	/* 443ace: mov dword ptr [0x9f1058], eax */
	M32((DWORD)(0x9f16a4u)) = m->eax;	/* 443ad3: mov dword ptr [0x9f16a4], eax */
	M32((DWORD)(0x680bb4u)) = m->eax;	/* 443ad8: mov dword ptr [0x680bb4], eax */
	M32((DWORD)(0x76d37cu)) = m->eax;	/* 443add: mov dword ptr [0x76d37c], eax */
	m->esp += 4 + 0; return;	/* 443ae2: ret  */
}

/* room_434490 (0x434490), lifted by tools/lift.py */
static void lift_434490(X86 *m)
{
	m->eax = M32((DWORD)(0x68039cu));	/* 434490: mov eax, dword ptr [0x68039c] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 434495: push esi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 434496: xor esi, esi */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 434498: cmp eax, esi */
	if (m->zf) goto L_4344bf;	/* 43449a: je 0x4344bf */
	m->eax = M32((DWORD)(0x9dd888u));	/* 43449c: mov eax, dword ptr [0x9dd888] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4344a1: push eax */
	m->esp -= 4; M32(m->esp) = 0x4344a8u; native_call(m, M32(0x4a9344u));	/* 4344a2: call dword ptr [0x4a9344] */
	m->ecx = M32((DWORD)(0x4ded18u));	/* 4344a8: mov ecx, dword ptr [0x4ded18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4344ae: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4344b5u; native_call(m, M32(0x4a935cu));	/* 4344af: call dword ptr [0x4a935c] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4344b5: push 1 */
	m->esp -= 4; M32(m->esp) = 0x4344bcu; native_call(m, 0x431600u);	/* 4344b7: call 0x431600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4344bc: add esp, 4 */
L_4344bf:
	{ DWORD v_ = 0x9dd1d8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4344bf: push 0x9dd1d8 */
	M32((DWORD)(0x9dd830u)) = m->esi;	/* 4344c4: mov dword ptr [0x9dd830], esi */
	M32((DWORD)(0x9dd38cu)) = m->esi;	/* 4344ca: mov dword ptr [0x9dd38c], esi */
	M32((DWORD)(0x4e1868u)) = m->esi;	/* 4344d0: mov dword ptr [0x4e1868], esi */
	M32((DWORD)(0x68039cu)) = m->esi;	/* 4344d6: mov dword ptr [0x68039c], esi */
	m->esp -= 4; M32(m->esp) = 0x4344e1u; native_call(m, 0x434400u);	/* 4344dc: call 0x434400 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4344e1: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4344e4: cmp eax, 1 */
	if (!m->zf) goto L_4344fe;	/* 4344e7: jne 0x4344fe */
	{ DWORD v_ = 0x15au; m->esp -= 4; M32(m->esp) = v_; }	/* 4344e9: push 0x15a */
	m->esp -= 4; M32(m->esp) = 0x4344f3u; native_call(m, 0x41ee40u);	/* 4344ee: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4344f3: add esp, 4 */
	M32((DWORD)(0x9dd1c8u)) = m->esi;	/* 4344f6: mov dword ptr [0x9dd1c8], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4344fc: pop esi */
	m->esp += 4 + 0; return;	/* 4344fd: ret  */
L_4344fe:
	{ DWORD v_ = 0x9dd1f6u; m->esp -= 4; M32(m->esp) = v_; }	/* 4344fe: push 0x9dd1f6 */
	m->esp -= 4; M32(m->esp) = 0x434508u; native_call(m, 0x434400u);	/* 434503: call 0x434400 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 434508: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43450b: cmp eax, 1 */
	if (!m->zf) goto L_434525;	/* 43450e: jne 0x434525 */
	{ DWORD v_ = 0x15bu; m->esp -= 4; M32(m->esp) = v_; }	/* 434510: push 0x15b */
	m->esp -= 4; M32(m->esp) = 0x43451au; native_call(m, 0x41ee40u);	/* 434515: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43451a: add esp, 4 */
	M32((DWORD)(0x9dd1c8u)) = m->esi;	/* 43451d: mov dword ptr [0x9dd1c8], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 434523: pop esi */
	m->esp += 4 + 0; return;	/* 434524: ret  */
L_434525:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 434525: push edi */
	m->ecx = 0x7u;	/* 434526: mov ecx, 7 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43452b: xor eax, eax */
	m->edi = 0x9dd570u;	/* 43452d: mov edi, 0x9dd570 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 434532: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 434534: stosw word ptr es:[edi], ax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 434536: or ecx, 0xffffffff */
	m->edi = 0x9dd1d8u;	/* 434539: mov edi, 0x9dd1d8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43453e: xor eax, eax */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 434540: xor edx, edx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 434542: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 434544: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 434546: sub edi, ecx */
	M32((DWORD)(0x9dd58eu)) = m->edx;	/* 434548: mov dword ptr [0x9dd58e], edx */
	m->eax = m->ecx;	/* 43454e: mov eax, ecx */
	M32((DWORD)(0x9dd592u)) = m->edx;	/* 434550: mov dword ptr [0x9dd592], edx */
	m->esi = m->edi;	/* 434556: mov esi, edi */
	m->edi = 0x9dd570u;	/* 434558: mov edi, 0x9dd570 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43455d: shr ecx, 2 */
	M32((DWORD)(0x9dd596u)) = m->edx;	/* 434560: mov dword ptr [0x9dd596], edx */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 434566: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 434568: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43456a: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43456c: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43456f: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 434571: or ecx, 0xffffffff */
	m->edi = 0x9dd1f6u;	/* 434574: mov edi, 0x9dd1f6 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 434579: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43457b: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43457d: sub edi, ecx */
	m->edx = m->ecx;	/* 43457f: mov edx, ecx */
	m->esi = m->edi;	/* 434581: mov esi, edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 434583: shr ecx, 2 */
	m->edi = 0x9dd58eu;	/* 434586: mov edi, 0x9dd58e */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43458b: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 43458d: mov ecx, edx */
	m->edx = M32((DWORD)(0xa0b320u));	/* 43458f: mov edx, dword ptr [0xa0b320] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 434595: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 434598: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = 0x7u;	/* 43459a: mov ecx, 7 */
	m->edi = (DWORD)(m->edx + 0x4u);	/* 43459f: lea edi, [edx + 4] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4345a2: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 4345a4: stosw word ptr es:[edi], ax */
	m->ecx = M32((DWORD)(0xa0b320u));	/* 4345a6: mov ecx, dword ptr [0xa0b320] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4345ac: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x22u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4345ae: add ecx, 0x22 */
	m->edi = 0x9dd1d8u;	/* 4345b1: mov edi, 0x9dd1d8 */
	M32((DWORD)(m->ecx + 0x0u)) = m->eax;	/* 4345b6: mov dword ptr [ecx], eax */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 4345b8: mov dword ptr [ecx + 4], eax */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 4345bb: mov dword ptr [ecx + 8], eax */
	m->edx = M32((DWORD)(0xa0b320u));	/* 4345be: mov edx, dword ptr [0xa0b320] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4345c4: or ecx, 0xffffffff */
	{ DWORD a_ = m->edx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4345c7: add edx, 4 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4345ca: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4345cc: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4345ce: sub edi, ecx */
	m->eax = m->ecx;	/* 4345d0: mov eax, ecx */
	m->esi = m->edi;	/* 4345d2: mov esi, edi */
	m->edi = m->edx;	/* 4345d4: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4345d6: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4345d9: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4345db: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4345dd: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4345df: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4345e2: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0xa0b320u));	/* 4345e4: mov ecx, dword ptr [0xa0b320] */
	m->edi = 0x9dd1f6u;	/* 4345ea: mov edi, 0x9dd1f6 */
	m->edx = (DWORD)(m->ecx + 0x22u);	/* 4345ef: lea edx, [ecx + 0x22] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4345f2: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4345f5: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4345f7: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4345f9: sub edi, ecx */
	m->eax = m->ecx;	/* 4345fb: mov eax, ecx */
	m->esi = m->edi;	/* 4345fd: mov esi, edi */
	m->edi = m->edx;	/* 4345ff: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 434601: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 434604: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 434606: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 434608: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43460b: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0xa0b320u));	/* 43460d: mov ecx, dword ptr [0xa0b320] */
	{ DWORD v_ = 0x65u; m->esp -= 4; M32(m->esp) = v_; }	/* 434613: push 0x65 */
	{ DWORD v_ = 0xeu; m->esp -= 4; M32(m->esp) = v_; }	/* 434615: push 0xe */
	M32((DWORD)(m->ecx + 0x0u)) = 0x18u;	/* 434617: mov dword ptr [ecx], 0x18 */
	m->esp -= 4; M32(m->esp) = 0x434622u; native_call(m, 0x4521c0u);	/* 43461d: call 0x4521c0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 434622: add esp, 8 */
	M32((DWORD)(0x9dd838u)) = 0x1u;	/* 434625: mov dword ptr [0x9dd838], 1 */
	m->edi = M32(m->esp); m->esp += 4;	/* 43462f: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 434630: pop esi */
	m->esp += 4 + 0; return;	/* 434631: ret  */
}

/* menuState500_enter (0x447750), lifted by tools/lift.py */
static void lift_447750(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 447750: push esi */
	m->esi = 0x1u;	/* 447751: mov esi, 1 */
	m->eax = 0x1f4u;	/* 447756: mov eax, 0x1f4 */
	M32((DWORD)(0x4df024u)) = 0x0u;	/* 44775b: mov dword ptr [0x4df024], 0 */
	M32((DWORD)(0x4df028u)) = 0x0u;	/* 447765: mov dword ptr [0x4df028], 0 */
	M32((DWORD)(0x4df02cu)) = 0xc3e10000u;	/* 44776f: mov dword ptr [0x4df02c], 0xc3e10000 */
	M32((DWORD)(0x680378u)) = 0x0u;	/* 447779: mov dword ptr [0x680378], 0 */
	M32((DWORD)(0x68037cu)) = 0x0u;	/* 447783: mov dword ptr [0x68037c], 0 */
	M32((DWORD)(0x680380u)) = 0xc4098000u;	/* 44778d: mov dword ptr [0x680380], 0xc4098000 */
	M32((DWORD)(0x9f6308u)) = 0x28u;	/* 447797: mov dword ptr [0x9f6308], 0x28 */
	M32((DWORD)(0x9f630cu)) = 0xau;	/* 4477a1: mov dword ptr [0x9f630c], 0xa */
	M32((DWORD)(0x9f6310u)) = 0x258u;	/* 4477ab: mov dword ptr [0x9f6310], 0x258 */
	M32((DWORD)(0x9f6314u)) = 0x1ccu;	/* 4477b5: mov dword ptr [0x9f6314], 0x1cc */
	M32((DWORD)(0x9f6318u)) = 0x0u;	/* 4477bf: mov dword ptr [0x9f6318], 0 */
	M32((DWORD)(0x9f631cu)) = 0x3f800000u;	/* 4477c9: mov dword ptr [0x9f631c], 0x3f800000 */
	M32((DWORD)(0x9f6320u)) = 0x3f800000u;	/* 4477d3: mov dword ptr [0x9f6320], 0x3f800000 */
	M32((DWORD)(0x9f6324u)) = 0x3f800000u;	/* 4477dd: mov dword ptr [0x9f6324], 0x3f800000 */
	M32((DWORD)(0x9f62e8u)) = 0x0u;	/* 4477e7: mov dword ptr [0x9f62e8], 0 */
	M32((DWORD)(0x9f62ecu)) = 0x3f19999au;	/* 4477f1: mov dword ptr [0x9f62ec], 0x3f19999a */
	M32((DWORD)(0x9f62f0u)) = 0x3f19999au;	/* 4477fb: mov dword ptr [0x9f62f0], 0x3f19999a */
	M32((DWORD)(0x9f62f4u)) = 0x3f800000u;	/* 447805: mov dword ptr [0x9f62f4], 0x3f800000 */
	M32((DWORD)(0x4df870u)) = 0x0u;	/* 44780f: mov dword ptr [0x4df870], 0 */
	M32((DWORD)(0x4df874u)) = 0x0u;	/* 447819: mov dword ptr [0x4df874], 0 */
	M32((DWORD)(0x4df878u)) = 0x42c80000u;	/* 447823: mov dword ptr [0x4df878], 0x42c80000 */
	M32((DWORD)(0x76d388u)) = 0x0u;	/* 44782d: mov dword ptr [0x76d388], 0 */
	M32((DWORD)(0x76d38cu)) = 0x0u;	/* 447837: mov dword ptr [0x76d38c], 0 */
	M32((DWORD)(0x76d390u)) = 0x0u;	/* 447841: mov dword ptr [0x76d390], 0 */
	M32((DWORD)(0x9db090u)) = 0x0u;	/* 44784b: mov dword ptr [0x9db090], 0 */
	M32((DWORD)(0x9db094u)) = 0x0u;	/* 447855: mov dword ptr [0x9db094], 0 */
	M32((DWORD)(0x9db098u)) = 0xc3e10000u;	/* 44785f: mov dword ptr [0x9db098], 0xc3e10000 */
	M32((DWORD)(0x76d3f8u)) = 0x0u;	/* 447869: mov dword ptr [0x76d3f8], 0 */
	M32((DWORD)(0x76d3fcu)) = 0x0u;	/* 447873: mov dword ptr [0x76d3fc], 0 */
	M32((DWORD)(0x76d400u)) = 0xc4098000u;	/* 44787d: mov dword ptr [0x76d400], 0xc4098000 */
	M32((DWORD)(0x9f62f8u)) = m->esi;	/* 447887: mov dword ptr [0x9f62f8], esi */
	M32((DWORD)(0x76d3e8u)) = m->eax;	/* 44788d: mov dword ptr [0x76d3e8], eax */
	M32((DWORD)(0x67ef0cu)) = m->eax;	/* 447892: mov dword ptr [0x67ef0c], eax */
	M32((DWORD)(0x67ef20u)) = m->eax;	/* 447897: mov dword ptr [0x67ef20], eax */
	m->esp -= 4; M32(m->esp) = 0x4478a1u; native_call(m, 0x447660u);	/* 44789c: call 0x447660 */
	m->eax = M32((DWORD)(0x9f181cu));	/* 4478a1: mov eax, dword ptr [0x9f181c] */
	M32((DWORD)(0x9f63b8u)) = m->esi;	/* 4478a6: mov dword ptr [0x9f63b8], esi */
	{ DWORD a_ = m->eax, b_ = 0xfu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4478ac: cmp eax, 0xf */
	M32((DWORD)(0x9f6300u)) = 0x0u;	/* 4478af: mov dword ptr [0x9f6300], 0 */
	M32((DWORD)(0x9f63b4u)) = m->eax;	/* 4478b9: mov dword ptr [0x9f63b4], eax */
	if (m->sf != m->of) goto L_4478ca;	/* 4478be: jl 0x4478ca */
	m->eax = 0xeu;	/* 4478c0: mov eax, 0xe */
	M32((DWORD)(0x9f63b4u)) = m->eax;	/* 4478c5: mov dword ptr [0x9f63b4], eax */
L_4478ca:
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4478ca: push 4 */
	M32((DWORD)(0x9f6328u)) = m->eax;	/* 4478cc: mov dword ptr [0x9f6328], eax */
	M32((DWORD)(0x9f63b0u)) = m->esi;	/* 4478d1: mov dword ptr [0x9f63b0], esi */
	m->esp -= 4; M32(m->esp) = 0x4478dcu; native_call(m, 0x41e760u);	/* 4478d7: call 0x41e760 */
	m->eax = M32((DWORD)(0x9f181cu));	/* 4478dc: mov eax, dword ptr [0x9f181c] */
	m->ecx = M32((DWORD)(0x9f62fcu));	/* 4478e1: mov ecx, dword ptr [0x9f62fc] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4478e7: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4478ea: cmp eax, ecx */
	M32((DWORD)(0x9f62e0u)) = 0x0u;	/* 4478ec: mov dword ptr [0x9f62e0], 0 */
	if (m->zf || m->sf != m->of) goto L_447903;	/* 4478f6: jle 0x447903 */
	M32((DWORD)(0x9f62e0u)) = m->esi;	/* 4478f8: mov dword ptr [0x9f62e0], esi */
	M32((DWORD)(0x9f62fcu)) = m->eax;	/* 4478fe: mov dword ptr [0x9f62fc], eax */
L_447903:
	m->esi = M32(m->esp); m->esp += 4;	/* 447903: pop esi */
	m->esp += 4 + 0; return;	/* 447904: ret  */
}

/* msg_playerConnected (0x462b50), lifted by tools/lift.py */
static void lift_462b50(X86 *m)
{
	m->eax = M32((DWORD)(0x9dae74u));	/* 462b50: mov eax, dword ptr [0x9dae74] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 462b55: dec eax */
	if (m->zf) goto L_462b7f;	/* 462b56: je 0x462b7f */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 462b58: dec eax */
	if (!m->zf) goto L_462bac;	/* 462b59: jne 0x462bac */
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 462b5b: mov eax, dword ptr [esp + 4] */
	m->edx = m->eax;	/* 462b5f: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 462b61: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 462b64: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 462b66: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 462b69: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 462b6b: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 462b6e: add edx, eax */
	m->eax = (DWORD)(m->ecx + m->edx*8 + 0x1eccb08u);	/* 462b70: lea eax, [ecx + edx*8 + 0x1eccb08] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 462b77: push eax */
	{ DWORD v_ = 0x4c4674u; m->esp -= 4; M32(m->esp) = v_; }	/* 462b78: push 0x4c4674 */
	goto L_462ba1;	/* 462b7d: jmp 0x462ba1 */
L_462b7f:
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 462b7f: mov eax, dword ptr [esp + 4] */
	m->edx = m->eax;	/* 462b83: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 462b85: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 462b88: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 462b8a: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 462b8d: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 462b8f: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 462b92: add edx, eax */
	m->eax = (DWORD)(m->ecx + m->edx*8 + 0x1eccb08u);	/* 462b94: lea eax, [ecx + edx*8 + 0x1eccb08] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 462b9b: push eax */
	{ DWORD v_ = 0x4c465cu; m->esp -= 4; M32(m->esp) = v_; }	/* 462b9c: push 0x4c465c */
L_462ba1:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 462ba1: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 462ba3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x462ba9u; native_call(m, 0x4629f0u);	/* 462ba4: call 0x4629f0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 462ba9: add esp, 0x10 */
L_462bac:
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 462bac: push 0x64 */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 462bae: push 0xa */
	m->esp -= 4; M32(m->esp) = 0x462bb5u; native_call(m, 0x456e50u);	/* 462bb0: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 462bb5: add esp, 8 */
	m->esp += 4 + 4; return;	/* 462bb8: ret 4 */
}

/* msg_chatLine (0x462c30), lifted by tools/lift.py */
static void lift_462c30(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 462c30: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 462c31: push edi */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 462c32: mov edi, dword ptr [esp + 0x14] */
	m->esi = m->ecx;	/* 462c36: mov esi, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 462c38: push edi */
	m->esp -= 4; M32(m->esp) = 0x462c3eu; native_call(m, 0x463710u);	/* 462c39: call 0x463710 */
	{ DWORD a_ = m->eax, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 462c3e: sub eax, 0 */
	if (m->zf) goto L_462ca4;	/* 462c41: je 0x462ca4 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 462c43: dec eax */
	if (m->zf) goto L_462c71;	/* 462c44: je 0x462c71 */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 462c46: mov eax, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 462c4a: push eax */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 462c4b: mov eax, dword ptr [esp + 0x10] */
	m->ecx = m->eax;	/* 462c4f: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 462c51: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 462c54: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 462c56: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 462c59: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 462c5b: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 462c5e: add ecx, eax */
	m->edx = (DWORD)(m->esi + m->ecx*8 + 0x1eccb08u);	/* 462c60: lea edx, [esi + ecx*8 + 0x1eccb08] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 462c67: push edx */
	{ DWORD v_ = 0x4c46c0u; m->esp -= 4; M32(m->esp) = v_; }	/* 462c68: push 0x4c46c0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 462c6d: push 1 */
	goto L_462cd5;	/* 462c6f: jmp 0x462cd5 */
L_462c71:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x234243eu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 462c71: cmp dword ptr [esi + 0x234243e], edi */
	if (!m->zf) goto L_462cde;	/* 462c77: jne 0x462cde */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 462c79: mov eax, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 462c7d: push eax */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 462c7e: mov eax, dword ptr [esp + 0x10] */
	m->ecx = m->eax;	/* 462c82: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 462c84: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 462c87: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 462c89: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 462c8c: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 462c8e: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 462c91: add ecx, eax */
	m->edx = (DWORD)(m->esi + m->ecx*8 + 0x1eccb08u);	/* 462c93: lea edx, [esi + ecx*8 + 0x1eccb08] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 462c9a: push edx */
	{ DWORD v_ = 0x4c46c0u; m->esp -= 4; M32(m->esp) = v_; }	/* 462c9b: push 0x4c46c0 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 462ca0: push 2 */
	goto L_462cd5;	/* 462ca2: jmp 0x462cd5 */
L_462ca4:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x234243eu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 462ca4: cmp dword ptr [esi + 0x234243e], edi */
	if (!m->zf) goto L_462cde;	/* 462caa: jne 0x462cde */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 462cac: mov eax, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 462cb0: push eax */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 462cb1: mov eax, dword ptr [esp + 0x10] */
	m->ecx = m->eax;	/* 462cb5: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 462cb7: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 462cba: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 462cbc: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 462cbf: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 462cc1: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 462cc4: add ecx, eax */
	m->edx = (DWORD)(m->esi + m->ecx*8 + 0x1eccb08u);	/* 462cc6: lea edx, [esi + ecx*8 + 0x1eccb08] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 462ccd: push edx */
	{ DWORD v_ = 0x4c46c0u; m->esp -= 4; M32(m->esp) = v_; }	/* 462cce: push 0x4c46c0 */
	{ DWORD v_ = 0x3u; m->esp -= 4; M32(m->esp) = v_; }	/* 462cd3: push 3 */
L_462cd5:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 462cd5: push esi */
	m->esp -= 4; M32(m->esp) = 0x462cdbu; native_call(m, 0x4629f0u);	/* 462cd6: call 0x4629f0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 462cdb: add esp, 0x14 */
L_462cde:
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 462cde: push 0x64 */
	{ DWORD v_ = 0x9u; m->esp -= 4; M32(m->esp) = v_; }	/* 462ce0: push 9 */
	m->esp -= 4; M32(m->esp) = 0x462ce7u; native_call(m, 0x456e50u);	/* 462ce2: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 462ce7: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 462cea: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 462ceb: pop esi */
	m->esp += 4 + 12; return;	/* 462cec: ret 0xc */
}

/* music_playMatch (0x462850), lifted by tools/lift.py */
static void lift_462850(X86 *m)
{
	m->ecx = M32((DWORD)(m->ecx + 0xbe3004u));	/* 462850: mov ecx, dword ptr [ecx + 0xbe3004] */
	m->eax = (DWORD)(m->ecx + 0xffffffffu);	/* 462856: lea eax, [ecx - 1] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 462859: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_46299b;	/* 46285c: ja 0x46299b */
	switch (m->eax) { case 0: goto L_462869; case 1: goto L_4628cf; case 2: goto L_4628f4; case 3: goto L_462949; default: abort(); }	/* 462862: jmp dword ptr [eax*4 + 0x46299c] */
L_462869:
	m->ecx = M32((DWORD)(0xa1efb8u));	/* 462869: mov ecx, dword ptr [0xa1efb8] */
	m->eax = m->ecx;	/* 46286f: mov eax, ecx */
	{ DWORD a_ = m->eax, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 462871: and eax, 0xfff */
	m->eax = M32((DWORD)(m->eax*4 + 0xa106f8u));	/* 462876: mov eax, dword ptr [eax*4 + 0xa106f8] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46287d: and eax, 3 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 462880: inc ecx */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 462881: cmp eax, 3 */
	M32((DWORD)(0xa1efb8u)) = m->ecx;	/* 462884: mov dword ptr [0xa1efb8], ecx */
	if (!m->cf && !m->zf) goto L_46299b;	/* 46288a: ja 0x46299b */
	switch (m->eax) { case 0: goto L_462897; case 1: goto L_4628a5; case 2: goto L_4628b3; case 3: goto L_4628c1; default: abort(); }	/* 462890: jmp dword ptr [eax*4 + 0x4629ac] */
L_462897:
	{ DWORD v_ = 0x4b496cu; m->esp -= 4; M32(m->esp) = v_; }	/* 462897: push 0x4b496c */
	m->esp -= 4; M32(m->esp) = 0x4628a1u; native_call(m, 0x457150u);	/* 46289c: call 0x457150 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4628a1: add esp, 4 */
	m->esp += 4 + 0; return;	/* 4628a4: ret  */
L_4628a5:
	{ DWORD v_ = 0x4b4a6cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4628a5: push 0x4b4a6c */
	m->esp -= 4; M32(m->esp) = 0x4628afu; native_call(m, 0x457150u);	/* 4628aa: call 0x457150 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4628af: add esp, 4 */
	m->esp += 4 + 0; return;	/* 4628b2: ret  */
L_4628b3:
	{ DWORD v_ = 0x4b4b6cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4628b3: push 0x4b4b6c */
	m->esp -= 4; M32(m->esp) = 0x4628bdu; native_call(m, 0x457150u);	/* 4628b8: call 0x457150 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4628bd: add esp, 4 */
	m->esp += 4 + 0; return;	/* 4628c0: ret  */
L_4628c1:
	{ DWORD v_ = 0x4b4c6cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4628c1: push 0x4b4c6c */
	m->esp -= 4; M32(m->esp) = 0x4628cbu; native_call(m, 0x457150u);	/* 4628c6: call 0x457150 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4628cb: add esp, 4 */
	m->esp += 4 + 0; return;	/* 4628ce: ret  */
L_4628cf:
	m->ecx = M32((DWORD)(0xa1efb8u));	/* 4628cf: mov ecx, dword ptr [0xa1efb8] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4628d5: inc ecx */
	M32((DWORD)(0xa1efb8u)) = m->ecx;	/* 4628d6: mov dword ptr [0xa1efb8], ecx */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ ^ b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->ecx = (m->ecx & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 4628dc: xor cl, cl */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4628de: test cl, cl */
	if (!m->zf) goto L_46299b;	/* 4628e0: jne 0x46299b */
	{ DWORD v_ = 0x4b4f6cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4628e6: push 0x4b4f6c */
	m->esp -= 4; M32(m->esp) = 0x4628f0u; native_call(m, 0x457150u);	/* 4628eb: call 0x457150 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4628f0: add esp, 4 */
	m->esp += 4 + 0; return;	/* 4628f3: ret  */
L_4628f4:
	m->eax = M32((DWORD)(0xa1efb8u));	/* 4628f4: mov eax, dword ptr [0xa1efb8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4628f9: xor edx, edx */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4628fb: inc eax */
	m->ecx = 0x3u;	/* 4628fc: mov ecx, 3 */
	M32((DWORD)(0xa1efb8u)) = m->eax;	/* 462901: mov dword ptr [0xa1efb8], eax */
	{ DWORD a_ = m->eax, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 462906: and eax, 0xfff */
	m->eax = M32((DWORD)(m->eax*4 + 0xa106f8u));	/* 46290b: mov eax, dword ptr [eax*4 + 0xa106f8] */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->ecx; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 462912: div ecx */
	{ DWORD a_ = m->edx, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 462914: sub edx, 0 */
	if (m->zf) goto L_46293b;	/* 462917: je 0x46293b */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 462919: dec edx */
	if (m->zf) goto L_46292d;	/* 46291a: je 0x46292d */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 46291c: dec edx */
	if (!m->zf) goto L_46299b;	/* 46291d: jne 0x46299b */
	{ DWORD v_ = 0x4b506cu; m->esp -= 4; M32(m->esp) = v_; }	/* 46291f: push 0x4b506c */
	m->esp -= 4; M32(m->esp) = 0x462929u; native_call(m, 0x457150u);	/* 462924: call 0x457150 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 462929: add esp, 4 */
	m->esp += 4 + 0; return;	/* 46292c: ret  */
L_46292d:
	{ DWORD v_ = 0x4b4e6cu; m->esp -= 4; M32(m->esp) = v_; }	/* 46292d: push 0x4b4e6c */
	m->esp -= 4; M32(m->esp) = 0x462937u; native_call(m, 0x457150u);	/* 462932: call 0x457150 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 462937: add esp, 4 */
	m->esp += 4 + 0; return;	/* 46293a: ret  */
L_46293b:
	{ DWORD v_ = 0x4b4d6cu; m->esp -= 4; M32(m->esp) = v_; }	/* 46293b: push 0x4b4d6c */
	m->esp -= 4; M32(m->esp) = 0x462945u; native_call(m, 0x457150u);	/* 462940: call 0x457150 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 462945: add esp, 4 */
	m->esp += 4 + 0; return;	/* 462948: ret  */
L_462949:
	m->eax = M32((DWORD)(0xa1efb8u));	/* 462949: mov eax, dword ptr [0xa1efb8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 46294e: xor edx, edx */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 462950: inc eax */
	m->ecx = 0x3u;	/* 462951: mov ecx, 3 */
	M32((DWORD)(0xa1efb8u)) = m->eax;	/* 462956: mov dword ptr [0xa1efb8], eax */
	{ DWORD a_ = m->eax, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46295b: and eax, 0xfff */
	m->eax = M32((DWORD)(m->eax*4 + 0xa106f8u));	/* 462960: mov eax, dword ptr [eax*4 + 0xa106f8] */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->ecx; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 462967: div ecx */
	{ DWORD a_ = m->edx, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 462969: sub edx, 0 */
	if (m->zf) goto L_462990;	/* 46296c: je 0x462990 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 46296e: dec edx */
	if (m->zf) goto L_462982;	/* 46296f: je 0x462982 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 462971: dec edx */
	if (!m->zf) goto L_46299b;	/* 462972: jne 0x46299b */
	{ DWORD v_ = 0x4b546cu; m->esp -= 4; M32(m->esp) = v_; }	/* 462974: push 0x4b546c */
	m->esp -= 4; M32(m->esp) = 0x46297eu; native_call(m, 0x457150u);	/* 462979: call 0x457150 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46297e: add esp, 4 */
	m->esp += 4 + 0; return;	/* 462981: ret  */
L_462982:
	{ DWORD v_ = 0x4b536cu; m->esp -= 4; M32(m->esp) = v_; }	/* 462982: push 0x4b536c */
	m->esp -= 4; M32(m->esp) = 0x46298cu; native_call(m, 0x457150u);	/* 462987: call 0x457150 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46298c: add esp, 4 */
	m->esp += 4 + 0; return;	/* 46298f: ret  */
L_462990:
	{ DWORD v_ = 0x4b516cu; m->esp -= 4; M32(m->esp) = v_; }	/* 462990: push 0x4b516c */
	m->esp -= 4; M32(m->esp) = 0x46299au; native_call(m, 0x457150u);	/* 462995: call 0x457150 */
	m->ecx = M32(m->esp); m->esp += 4;	/* 46299a: pop ecx */
L_46299b:
	m->esp += 4 + 0; return;	/* 46299b: ret  */
}

/* dplay_closeSession (0x453a10), lifted by tools/lift.py */
static void lift_453a10(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 453a10: push esi */
	m->esi = M32((DWORD)(m->esp + 0x8u));	/* 453a11: mov esi, dword ptr [esp + 8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 453a15: xor eax, eax */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 453a17: test esi, esi */
	if (m->zf) goto L_453a27;	/* 453a19: je 0x453a27 */
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 453a1b: mov eax, dword ptr [esi] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 453a1d: push esi */
	m->esp -= 4; M32(m->esp) = 0x453a21u; native_call(m, M32((DWORD)(m->eax + 0x10u)));	/* 453a1e: call dword ptr [eax + 0x10] */
	m->ecx = M32((DWORD)(m->esi + 0x0u));	/* 453a21: mov ecx, dword ptr [esi] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 453a23: push esi */
	m->esp -= 4; M32(m->esp) = 0x453a27u; native_call(m, M32((DWORD)(m->ecx + 0x8u)));	/* 453a24: call dword ptr [ecx + 8] */
L_453a27:
	m->esi = M32(m->esp); m->esp += 4;	/* 453a27: pop esi */
	m->esp += 4 + 0; return;	/* 453a28: ret  */
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
