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

static void lift_44e3e0(X86 *m);
static void lift_44de00(X86 *m);
static void lift_41dab0(X86 *m);
static void lift_44e180(X86 *m);

/* profile_44e180 (0x44e180), lifted by tools/lift.py */
static void lift_44e180(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e180: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e181: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 44e182: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44e183: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44e184: push edi */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e185: push 2 */
	m->esp -= 4; M32(m->esp) = 0x44e18cu; native_call(m, 0x41ef90u);	/* 44e187: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44e18c: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x44e195u; native_call(m, M32(0x4a9218u));	/* 44e18f: call dword ptr [0x4a9218] */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 44e195: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 44e19a: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e1a0: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e1a1: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44e1a7u; native_call(m, 0x44b320u);	/* 44e1a2: call 0x44b320 */
	m->edi = M32((DWORD)(0x4a9228u));	/* 44e1a7: mov edi, dword ptr [0x4a9228] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44e1ad: add esp, 8 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 44e1b0: mov dword ptr [esp + 0x10], eax */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e1b4: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e1b9: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e1be: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e1c3: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44e1cau; native_call(m, m->edi);	/* 44e1c8: call edi */
	m->edx = M32((DWORD)(0x4deb50u));	/* 44e1ca: mov edx, dword ptr [0x4deb50] */
	m->eax = M32((DWORD)(0x9f8f28u));	/* 44e1d0: mov eax, dword ptr [0x9f8f28] */
	m->ecx = M32((DWORD)(0x9f8f2cu));	/* 44e1d5: mov ecx, dword ptr [0x9f8f2c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e1db: push edx */
	m->edx = M32((DWORD)(0x9f8f0cu));	/* 44e1dc: mov edx, dword ptr [0x9f8f0c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e1e2: push eax */
	m->eax = M32((DWORD)(0x9f8f1cu));	/* 44e1e3: mov eax, dword ptr [0x9f8f1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e1e8: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e1e9: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e1ea: push eax */
	m->esp -= 4; M32(m->esp) = 0x44e1f0u; native_call(m, 0x427b60u);	/* 44e1eb: call 0x427b60 */
	m->ecx = M32((DWORD)(0x9f8ebcu));	/* 44e1f0: mov ecx, dword ptr [0x9f8ebc] */
	m->edx = M32((DWORD)(0x9f8eb8u));	/* 44e1f6: mov edx, dword ptr [0x9f8eb8] */
	m->eax = M32((DWORD)(0x9f8eb4u));	/* 44e1fc: mov eax, dword ptr [0x9f8eb4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e201: push ecx */
	m->ecx = M32((DWORD)(0x9f8eb0u));	/* 44e202: mov ecx, dword ptr [0x9f8eb0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e208: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e209: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e20a: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e20b: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x44e215u; native_call(m, 0x41f0e0u);	/* 44e210: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9f8f0cu));	/* 44e215: mov eax, dword ptr [0x9f8f0c] */
	m->edx = M32((DWORD)(0x9f8f2cu));	/* 44e21a: mov edx, dword ptr [0x9f8f2c] */
	m->ecx = M32((DWORD)(0x9f8f1cu));	/* 44e220: mov ecx, dword ptr [0x9f8f1c] */
	{ DWORD v_ = 0x751da4u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e226: push 0x751da4 */
	{ DWORD a_ = m->eax, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44e22b: add eax, 0x10 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e22e: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e22f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e230: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44e236u; native_call(m, 0x4029d0u);	/* 44e231: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44e236: add esp, 0x38 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 44e239: xor ebp, ebp */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 44e23b: xor esi, esi */
	m->ebx = 0x7517a4u;	/* 44e23d: mov ebx, 0x7517a4 */
L_44e242:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e242: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x44e24du; native_call(m, M32(0x4a9224u));	/* 44e247: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 44e24d: mov eax, dword ptr [0x9db0a4] */
	m->edx = m->eax;	/* 44e252: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44e254: and edx, 0x800001ff */
	if (!m->sf) goto L_44e264;	/* 44e25a: jns 0x44e264 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 44e25c: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44e25d: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 44e263: inc edx */
L_44e264:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e264: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 44e265: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 44e26b: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44e26c: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44e272: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 44e274: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 44e277: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x44e280u; native_call(m, 0x4566c0u);	/* 44e27b: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e280: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e285: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e28a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e28f: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44e296u; native_call(m, m->edi);	/* 44e294: call edi */
	{ DWORD a_ = m->ebp, b_ = M32((DWORD)(m->esp + 0x10u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44e296: cmp ebp, dword ptr [esp + 0x10] */
	if (!m->zf) goto L_44e2f5;	/* 44e29a: jne 0x44e2f5 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e29c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e2a1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e2a6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e2ab: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44e2b2u; native_call(m, m->edi);	/* 44e2b0: call edi */
	m->ecx = M32((DWORD)(0x9f8f0cu));	/* 44e2b2: mov ecx, dword ptr [0x9f8f0c] */
	m->eax = M32((DWORD)(0x9f8f1cu));	/* 44e2b8: mov eax, dword ptr [0x9f8f1c] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e2bd: push 1 */
	m->edx = (DWORD)(m->ecx + 0x5cu);	/* 44e2bf: lea edx, [ecx + 0x5c] */
	{ DWORD a_ = m->ecx, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44e2c2: add ecx, 0x3c */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e2c5: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xceu);	/* 44e2c6: lea edx, [esi + eax + 0xce] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e2cd: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x6eu);	/* 44e2ce: lea eax, [esi + eax + 0x6e] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e2d2: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e2d3: push eax */
	m->esp -= 4; M32(m->esp) = 0x44e2d9u; native_call(m, 0x4282f0u);	/* 44e2d4: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x9f8ebcu));	/* 44e2d9: mov ecx, dword ptr [0x9f8ebc] */
	m->edx = M32((DWORD)(0x9f8eb8u));	/* 44e2df: mov edx, dword ptr [0x9f8eb8] */
	m->eax = M32((DWORD)(0x9f8eb4u));	/* 44e2e5: mov eax, dword ptr [0x9f8eb4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e2ea: push ecx */
	m->ecx = M32((DWORD)(0x9f8eb0u));	/* 44e2eb: mov ecx, dword ptr [0x9f8eb0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e2f1: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e2f2: push eax */
	goto L_44e34c;	/* 44e2f3: jmp 0x44e34c */
L_44e2f5:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44e2f5: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e2fa: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e2ff: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e304: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44e30bu; native_call(m, m->edi);	/* 44e309: call edi */
	m->ecx = M32((DWORD)(0x9f8f0cu));	/* 44e30b: mov ecx, dword ptr [0x9f8f0c] */
	m->eax = M32((DWORD)(0x9f8f1cu));	/* 44e311: mov eax, dword ptr [0x9f8f1c] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e316: push 1 */
	m->edx = (DWORD)(m->ecx + 0x5cu);	/* 44e318: lea edx, [ecx + 0x5c] */
	{ DWORD a_ = m->ecx, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44e31b: add ecx, 0x3c */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e31e: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xceu);	/* 44e31f: lea edx, [esi + eax + 0xce] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e326: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x6eu);	/* 44e327: lea eax, [esi + eax + 0x6e] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e32b: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e32c: push eax */
	m->esp -= 4; M32(m->esp) = 0x44e332u; native_call(m, 0x4282f0u);	/* 44e32d: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x9f8d64u));	/* 44e332: mov ecx, dword ptr [0x9f8d64] */
	m->edx = M32((DWORD)(0x9f8d60u));	/* 44e338: mov edx, dword ptr [0x9f8d60] */
	m->eax = M32((DWORD)(0x9f8d5cu));	/* 44e33e: mov eax, dword ptr [0x9f8d5c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e343: push ecx */
	m->ecx = M32((DWORD)(0x9f8d58u));	/* 44e344: mov ecx, dword ptr [0x9f8d58] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e34a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e34b: push eax */
L_44e34c:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e34c: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e34d: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x44e357u; native_call(m, 0x41f0e0u);	/* 44e352: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9f8f1cu));	/* 44e357: mov eax, dword ptr [0x9f8f1c] */
	m->ecx = M32((DWORD)(0x9f8f0cu));	/* 44e35c: mov ecx, dword ptr [0x9f8f0c] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44e362: add esp, 0x28 */
	{ DWORD a_ = m->ecx, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44e365: add ecx, 0x44 */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xceu);	/* 44e368: lea edx, [esi + eax + 0xce] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e36f: push ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e370: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x6eu);	/* 44e371: lea edx, [esi + eax + 0x6e] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e375: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e376: push edx */
	m->esp -= 4; M32(m->esp) = 0x44e37cu; native_call(m, 0x4029d0u);	/* 44e377: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44e37c: add esp, 0x10 */
	{ DWORD a_ = m->ebx, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 44e37f: add ebx, 0x80 */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 44e385: inc ebp */
	{ DWORD a_ = m->esi, b_ = 0x78u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 44e386: add esi, 0x78 */
	{ DWORD a_ = m->ebx, b_ = 0x7518a4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44e389: cmp ebx, 0x7518a4 */
	if (m->sf != m->of) goto L_44e242;	/* 44e38f: jl 0x44e242 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e395: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e39a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e39f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e3a4: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44e3abu; native_call(m, m->edi);	/* 44e3a9: call edi */
	m->eax = M32((DWORD)(0x9f8f28u));	/* 44e3ab: mov eax, dword ptr [0x9f8f28] */
	m->ecx = M32((DWORD)(0x9f8f2cu));	/* 44e3b0: mov ecx, dword ptr [0x9f8f2c] */
	m->edx = M32((DWORD)(0x9f8f0cu));	/* 44e3b6: mov edx, dword ptr [0x9f8f0c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e3bc: push eax */
	m->eax = M32((DWORD)(0x9f8f1cu));	/* 44e3bd: mov eax, dword ptr [0x9f8f1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e3c2: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e3c3: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e3c4: push eax */
	m->esp -= 4; M32(m->esp) = 0x44e3cau; native_call(m, 0x428b50u);	/* 44e3c5: call 0x428b50 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44e3ca: add esp, 0x10 */
	m->edi = M32(m->esp); m->esp += 4;	/* 44e3cd: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44e3ce: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 44e3cf: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 44e3d0: pop ebx */
	m->ecx = M32(m->esp); m->esp += 4;	/* 44e3d1: pop ecx */
	m->esp += 4 + 0; return;	/* 44e3d2: ret  */
}

/* profile_44e3e0 (0x44e3e0), lifted by tools/lift.py */
static void lift_44e3e0(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e3e0: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e3e1: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 44e3e2: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44e3e3: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44e3e4: push edi */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e3e5: push 2 */
	m->esp -= 4; M32(m->esp) = 0x44e3ecu; native_call(m, 0x41ef90u);	/* 44e3e7: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44e3ec: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x44e3f5u; native_call(m, M32(0x4a9218u));	/* 44e3ef: call dword ptr [0x4a9218] */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 44e3f5: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 44e3fa: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e400: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e401: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44e407u; native_call(m, 0x44b360u);	/* 44e402: call 0x44b360 */
	m->edi = M32((DWORD)(0x4a9228u));	/* 44e407: mov edi, dword ptr [0x4a9228] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44e40d: add esp, 8 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 44e410: mov dword ptr [esp + 0x10], eax */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e414: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e419: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e41e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e423: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44e42au; native_call(m, m->edi);	/* 44e428: call edi */
	m->edx = M32((DWORD)(0x4deb50u));	/* 44e42a: mov edx, dword ptr [0x4deb50] */
	m->eax = M32((DWORD)(0x9f93c0u));	/* 44e430: mov eax, dword ptr [0x9f93c0] */
	m->ecx = M32((DWORD)(0x9f93bcu));	/* 44e435: mov ecx, dword ptr [0x9f93bc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e43b: push edx */
	m->edx = M32((DWORD)(0x9f683cu));	/* 44e43c: mov edx, dword ptr [0x9f683c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e442: push eax */
	m->eax = M32((DWORD)(0x9f6834u));	/* 44e443: mov eax, dword ptr [0x9f6834] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e448: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e449: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e44a: push eax */
	m->esp -= 4; M32(m->esp) = 0x44e450u; native_call(m, 0x427b60u);	/* 44e44b: call 0x427b60 */
	m->ecx = M32((DWORD)(0x9f8ebcu));	/* 44e450: mov ecx, dword ptr [0x9f8ebc] */
	m->edx = M32((DWORD)(0x9f8eb8u));	/* 44e456: mov edx, dword ptr [0x9f8eb8] */
	m->eax = M32((DWORD)(0x9f8eb4u));	/* 44e45c: mov eax, dword ptr [0x9f8eb4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e461: push ecx */
	m->ecx = M32((DWORD)(0x9f8eb0u));	/* 44e462: mov ecx, dword ptr [0x9f8eb0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e468: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e469: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e46a: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e46b: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x44e475u; native_call(m, 0x41f0e0u);	/* 44e470: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9f683cu));	/* 44e475: mov eax, dword ptr [0x9f683c] */
	m->edx = M32((DWORD)(0x9f93bcu));	/* 44e47a: mov edx, dword ptr [0x9f93bc] */
	m->ecx = M32((DWORD)(0x9f6834u));	/* 44e480: mov ecx, dword ptr [0x9f6834] */
	{ DWORD v_ = 0x751e24u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e486: push 0x751e24 */
	{ DWORD a_ = m->eax, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44e48b: add eax, 0x10 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e48e: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e48f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e490: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44e496u; native_call(m, 0x4029d0u);	/* 44e491: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44e496: add esp, 0x38 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 44e499: xor ebp, ebp */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 44e49b: xor esi, esi */
	m->ebx = 0x7517a4u;	/* 44e49d: mov ebx, 0x7517a4 */
L_44e4a2:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e4a2: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x44e4adu; native_call(m, M32(0x4a9224u));	/* 44e4a7: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 44e4ad: mov eax, dword ptr [0x9db0a4] */
	m->edx = m->eax;	/* 44e4b2: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44e4b4: and edx, 0x800001ff */
	if (!m->sf) goto L_44e4c4;	/* 44e4ba: jns 0x44e4c4 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 44e4bc: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44e4bd: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 44e4c3: inc edx */
L_44e4c4:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e4c4: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 44e4c5: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 44e4cb: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44e4cc: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44e4d2: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 44e4d4: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 44e4d7: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x44e4e0u; native_call(m, 0x4566c0u);	/* 44e4db: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e4e0: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e4e5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e4ea: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e4ef: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44e4f6u; native_call(m, m->edi);	/* 44e4f4: call edi */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x10u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44e4f6: cmp dword ptr [esp + 0x10], ebp */
	if (!m->zf) goto L_44e555;	/* 44e4fa: jne 0x44e555 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e4fc: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e501: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e506: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e50b: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44e512u; native_call(m, m->edi);	/* 44e510: call edi */
	m->ecx = M32((DWORD)(0x9f683cu));	/* 44e512: mov ecx, dword ptr [0x9f683c] */
	m->eax = M32((DWORD)(0x9f6834u));	/* 44e518: mov eax, dword ptr [0x9f6834] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e51d: push 1 */
	m->edx = (DWORD)(m->ecx + 0x5cu);	/* 44e51f: lea edx, [ecx + 0x5c] */
	{ DWORD a_ = m->ecx, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44e522: add ecx, 0x3c */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e525: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xceu);	/* 44e526: lea edx, [esi + eax + 0xce] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e52d: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x6eu);	/* 44e52e: lea eax, [esi + eax + 0x6e] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e532: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e533: push eax */
	m->esp -= 4; M32(m->esp) = 0x44e539u; native_call(m, 0x4282f0u);	/* 44e534: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x9f8ebcu));	/* 44e539: mov ecx, dword ptr [0x9f8ebc] */
	m->edx = M32((DWORD)(0x9f8eb8u));	/* 44e53f: mov edx, dword ptr [0x9f8eb8] */
	m->eax = M32((DWORD)(0x9f8eb4u));	/* 44e545: mov eax, dword ptr [0x9f8eb4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e54a: push ecx */
	m->ecx = M32((DWORD)(0x9f8eb0u));	/* 44e54b: mov ecx, dword ptr [0x9f8eb0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e551: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e552: push eax */
	goto L_44e5ac;	/* 44e553: jmp 0x44e5ac */
L_44e555:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44e555: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e55a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e55f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e564: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44e56bu; native_call(m, m->edi);	/* 44e569: call edi */
	m->ecx = M32((DWORD)(0x9f683cu));	/* 44e56b: mov ecx, dword ptr [0x9f683c] */
	m->eax = M32((DWORD)(0x9f6834u));	/* 44e571: mov eax, dword ptr [0x9f6834] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e576: push 1 */
	m->edx = (DWORD)(m->ecx + 0x5cu);	/* 44e578: lea edx, [ecx + 0x5c] */
	{ DWORD a_ = m->ecx, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44e57b: add ecx, 0x3c */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e57e: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xceu);	/* 44e57f: lea edx, [esi + eax + 0xce] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e586: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x6eu);	/* 44e587: lea eax, [esi + eax + 0x6e] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e58b: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e58c: push eax */
	m->esp -= 4; M32(m->esp) = 0x44e592u; native_call(m, 0x4282f0u);	/* 44e58d: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x9f8d64u));	/* 44e592: mov ecx, dword ptr [0x9f8d64] */
	m->edx = M32((DWORD)(0x9f8d60u));	/* 44e598: mov edx, dword ptr [0x9f8d60] */
	m->eax = M32((DWORD)(0x9f8d5cu));	/* 44e59e: mov eax, dword ptr [0x9f8d5c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e5a3: push ecx */
	m->ecx = M32((DWORD)(0x9f8d58u));	/* 44e5a4: mov ecx, dword ptr [0x9f8d58] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e5aa: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e5ab: push eax */
L_44e5ac:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e5ac: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e5ad: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x44e5b7u; native_call(m, 0x41f0e0u);	/* 44e5b2: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9f6834u));	/* 44e5b7: mov eax, dword ptr [0x9f6834] */
	m->ecx = M32((DWORD)(0x9f683cu));	/* 44e5bc: mov ecx, dword ptr [0x9f683c] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44e5c2: add esp, 0x28 */
	{ DWORD a_ = m->ecx, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44e5c5: add ecx, 0x44 */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xceu);	/* 44e5c8: lea edx, [esi + eax + 0xce] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e5cf: push ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e5d0: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x6eu);	/* 44e5d1: lea edx, [esi + eax + 0x6e] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e5d5: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e5d6: push edx */
	m->esp -= 4; M32(m->esp) = 0x44e5dcu; native_call(m, 0x4029d0u);	/* 44e5d7: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44e5dc: add esp, 0x10 */
	{ DWORD a_ = m->ebx, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 44e5df: add ebx, 0x80 */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 44e5e5: inc ebp */
	{ DWORD a_ = m->esi, b_ = 0x78u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 44e5e6: add esi, 0x78 */
	{ DWORD a_ = m->ebx, b_ = 0x7518a4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44e5e9: cmp ebx, 0x7518a4 */
	if (m->sf != m->of) goto L_44e4a2;	/* 44e5ef: jl 0x44e4a2 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e5f5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e5fa: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e5ff: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e604: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44e60bu; native_call(m, m->edi);	/* 44e609: call edi */
	m->eax = M32((DWORD)(0x9f93c0u));	/* 44e60b: mov eax, dword ptr [0x9f93c0] */
	m->ecx = M32((DWORD)(0x9f93bcu));	/* 44e610: mov ecx, dword ptr [0x9f93bc] */
	m->edx = M32((DWORD)(0x9f683cu));	/* 44e616: mov edx, dword ptr [0x9f683c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e61c: push eax */
	m->eax = M32((DWORD)(0x9f6834u));	/* 44e61d: mov eax, dword ptr [0x9f6834] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e622: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e623: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e624: push eax */
	m->esp -= 4; M32(m->esp) = 0x44e62au; native_call(m, 0x428b50u);	/* 44e625: call 0x428b50 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44e62a: add esp, 0x10 */
	m->edi = M32(m->esp); m->esp += 4;	/* 44e62d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44e62e: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 44e62f: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 44e630: pop ebx */
	m->ecx = M32(m->esp); m->esp += 4;	/* 44e631: pop ecx */
	m->esp += 4 + 0; return;	/* 44e632: ret  */
}

/* profile_44de00 (0x44de00), lifted by tools/lift.py */
static void lift_44de00(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44de00: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44de01: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 44de02: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44de03: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44de04: push edi */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 44de05: push 2 */
	m->esp -= 4; M32(m->esp) = 0x44de0cu; native_call(m, 0x41ef90u);	/* 44de07: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44de0c: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x44de15u; native_call(m, M32(0x4a9218u));	/* 44de0f: call dword ptr [0x4a9218] */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 44de15: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 44de1a: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44de20: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44de21: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44de27u; native_call(m, 0x44b2a0u);	/* 44de22: call 0x44b2a0 */
	m->ebp = M32((DWORD)(0x4a9228u));	/* 44de27: mov ebp, dword ptr [0x4a9228] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44de2d: add esp, 8 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 44de30: mov dword ptr [esp + 0x10], eax */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44de34: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44de39: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44de3e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44de43: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44de4au; native_call(m, m->ebp);	/* 44de48: call ebp */
	m->edx = M32((DWORD)(0x4deb50u));	/* 44de4a: mov edx, dword ptr [0x4deb50] */
	m->eax = M32((DWORD)(0x9f8f24u));	/* 44de50: mov eax, dword ptr [0x9f8f24] */
	m->ecx = M32((DWORD)(0x9f8f20u));	/* 44de55: mov ecx, dword ptr [0x9f8f20] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44de5b: push edx */
	m->edx = M32((DWORD)(0x9f8ea8u));	/* 44de5c: mov edx, dword ptr [0x9f8ea8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44de62: push eax */
	m->eax = M32((DWORD)(0x9f8eacu));	/* 44de63: mov eax, dword ptr [0x9f8eac] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44de68: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44de69: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44de6a: push eax */
	m->esp -= 4; M32(m->esp) = 0x44de70u; native_call(m, 0x427b60u);	/* 44de6b: call 0x427b60 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44de70: push 0x3f800000 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44de75: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44de7a: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44de7f: push 0x3f4ccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 44de84: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x44de8eu; native_call(m, 0x41f0e0u);	/* 44de89: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9f8ebcu));	/* 44de8e: mov ecx, dword ptr [0x9f8ebc] */
	m->edx = M32((DWORD)(0x9f8eb8u));	/* 44de94: mov edx, dword ptr [0x9f8eb8] */
	m->eax = M32((DWORD)(0x9f8eb4u));	/* 44de9a: mov eax, dword ptr [0x9f8eb4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44de9f: push ecx */
	m->ecx = M32((DWORD)(0x9f8eb0u));	/* 44dea0: mov ecx, dword ptr [0x9f8eb0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44dea6: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44dea7: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44dea8: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dea9: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x44deb3u; native_call(m, 0x41f0e0u);	/* 44deae: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x9f8ea8u));	/* 44deb3: mov edx, dword ptr [0x9f8ea8] */
	m->eax = M32((DWORD)(0x9f8eacu));	/* 44deb9: mov eax, dword ptr [0x9f8eac] */
	{ DWORD a_ = m->edx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44debe: add edx, 0x10 */
	{ DWORD v_ = 0x751ca4u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dec1: push 0x751ca4 */
	{ DWORD a_ = m->eax, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44dec6: add eax, 0x14 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44dec9: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44deca: push eax */
	m->esp -= 4; M32(m->esp) = 0x44ded0u; native_call(m, 0x4028b0u);	/* 44decb: call 0x4028b0 */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44ded0: add esp, 0x48 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44ded3: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x44dedeu; native_call(m, M32(0x4a9224u));	/* 44ded8: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 44dede: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 44dee3: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44dee5: and ecx, 0x800001ff */
	if (!m->sf) goto L_44def5;	/* 44deeb: jns 0x44def5 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 44deed: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44deee: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 44def4: inc ecx */
L_44def5:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 44def5: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44def6: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44defc: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44defd: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 44deff: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 44df05: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 44df08: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x44df11u; native_call(m, 0x4566c0u);	/* 44df0c: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44df11: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44df16: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44df1b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44df20: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44df27u; native_call(m, m->ebp);	/* 44df25: call ebp */
	m->eax = M32((DWORD)(0x9f8ea8u));	/* 44df27: mov eax, dword ptr [0x9f8ea8] */
	m->edx = M32((DWORD)(0x9f8f20u));	/* 44df2c: mov edx, dword ptr [0x9f8f20] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44df32: push 1 */
	{ DWORD a_ = m->edx, b_ = 0xffffffecu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44df34: add edx, -0x14 */
	m->ecx = (DWORD)(m->eax + 0x50u);	/* 44df37: lea ecx, [eax + 0x50] */
	{ DWORD a_ = m->eax, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44df3a: add eax, 0x30 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44df3d: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44df3e: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44df3f: push eax */
	m->eax = M32((DWORD)(0x9f8eacu));	/* 44df40: mov eax, dword ptr [0x9f8eac] */
	{ DWORD a_ = m->eax, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44df45: add eax, 0x14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44df48: push eax */
	m->esp -= 4; M32(m->esp) = 0x44df4eu; native_call(m, 0x4283e0u);	/* 44df49: call 0x4283e0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44df4e: add esp, 0x14 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 44df51: xor ebx, ebx */
L_44df53:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44df53: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x44df5eu; native_call(m, M32(0x4a9224u));	/* 44df58: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 44df5e: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 44df63: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44df65: and ecx, 0x800001ff */
	if (!m->sf) goto L_44df75;	/* 44df6b: jns 0x44df75 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 44df6d: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44df6e: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 44df74: inc ecx */
L_44df75:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 44df75: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44df76: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44df7c: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44df7d: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 44df7f: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 44df85: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 44df88: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x44df91u; native_call(m, 0x4566c0u);	/* 44df8c: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44df91: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44df96: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44df9b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dfa0: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44dfa7u; native_call(m, m->ebp);	/* 44dfa5: call ebp */
	{ DWORD a_ = m->ebx, b_ = M32((DWORD)(m->esp + 0x10u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44dfa7: cmp ebx, dword ptr [esp + 0x10] */
	if (!m->zf) goto L_44e012;	/* 44dfab: jne 0x44e012 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dfad: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dfb2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dfb7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dfbc: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44dfc3u; native_call(m, m->ebp);	/* 44dfc1: call ebp */
	m->ecx = M32((DWORD)(0x9f8ea8u));	/* 44dfc3: mov ecx, dword ptr [0x9f8ea8] */
	m->eax = M32((DWORD)(0x9f8eacu));	/* 44dfc9: mov eax, dword ptr [0x9f8eac] */
	m->esi = (DWORD)(m->ebx + m->ebx*2 + 0x0u);	/* 44dfce: lea esi, [ebx + ebx*2] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dfd1: push 1 */
	m->edx = (DWORD)(m->ecx + 0x7au);	/* 44dfd3: lea edx, [ecx + 0x7a] */
	{ DWORD a_ = m->ecx, b_ = 0x5au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44dfd6: add ecx, 0x5a */
	m->esi = (DWORD)(m->esi + m->esi*4 + 0x0u);	/* 44dfd9: lea esi, [esi + esi*4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44dfdc: push edx */
	{ DWORD a_ = m->esi, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 44dfdd: shl esi, 3 */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x100u);	/* 44dfe0: lea edx, [esi + eax + 0x100] */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0xa0u);	/* 44dfe7: lea eax, [esi + eax + 0xa0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44dfee: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44dfef: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44dff0: push eax */
	m->esp -= 4; M32(m->esp) = 0x44dff6u; native_call(m, 0x4282f0u);	/* 44dff1: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x9f8ebcu));	/* 44dff6: mov ecx, dword ptr [0x9f8ebc] */
	m->edx = M32((DWORD)(0x9f8eb8u));	/* 44dffc: mov edx, dword ptr [0x9f8eb8] */
	m->eax = M32((DWORD)(0x9f8eb4u));	/* 44e002: mov eax, dword ptr [0x9f8eb4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e007: push ecx */
	m->ecx = M32((DWORD)(0x9f8eb0u));	/* 44e008: mov ecx, dword ptr [0x9f8eb0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e00e: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e00f: push eax */
	goto L_44e075;	/* 44e010: jmp 0x44e075 */
L_44e012:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44e012: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e017: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e01c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e021: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44e028u; native_call(m, m->ebp);	/* 44e026: call ebp */
	m->ecx = M32((DWORD)(0x9f8ea8u));	/* 44e028: mov ecx, dword ptr [0x9f8ea8] */
	m->eax = M32((DWORD)(0x9f8eacu));	/* 44e02e: mov eax, dword ptr [0x9f8eac] */
	m->esi = (DWORD)(m->ebx + m->ebx*2 + 0x0u);	/* 44e033: lea esi, [ebx + ebx*2] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e036: push 1 */
	m->edx = (DWORD)(m->ecx + 0x7au);	/* 44e038: lea edx, [ecx + 0x7a] */
	{ DWORD a_ = m->ecx, b_ = 0x5au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44e03b: add ecx, 0x5a */
	m->esi = (DWORD)(m->esi + m->esi*4 + 0x0u);	/* 44e03e: lea esi, [esi + esi*4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e041: push edx */
	{ DWORD a_ = m->esi, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 44e042: shl esi, 3 */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x100u);	/* 44e045: lea edx, [esi + eax + 0x100] */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0xa0u);	/* 44e04c: lea eax, [esi + eax + 0xa0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e053: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e054: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e055: push eax */
	m->esp -= 4; M32(m->esp) = 0x44e05bu; native_call(m, 0x4282f0u);	/* 44e056: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x9f8d64u));	/* 44e05b: mov ecx, dword ptr [0x9f8d64] */
	m->edx = M32((DWORD)(0x9f8d60u));	/* 44e061: mov edx, dword ptr [0x9f8d60] */
	m->eax = M32((DWORD)(0x9f8d5cu));	/* 44e067: mov eax, dword ptr [0x9f8d5c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e06c: push ecx */
	m->ecx = M32((DWORD)(0x9f8d58u));	/* 44e06d: mov ecx, dword ptr [0x9f8d58] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e073: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e074: push eax */
L_44e075:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e075: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e076: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x44e080u; native_call(m, 0x41f0e0u);	/* 44e07b: call 0x41f0e0 */
	m->edi = 0x9dc92cu;	/* 44e080: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44e085: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44e088: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44e08a: add esp, 0x28 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44e08d: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44e08f: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 44e091: dec ecx */
	if (!m->zf) goto L_44e0fd;	/* 44e092: jne 0x44e0fd */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44e094: test ebx, ebx */
	if (!m->zf) goto L_44e0fd;	/* 44e096: jne 0x44e0fd */
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44e098: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e09d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e0a2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e0a7: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44e0aeu; native_call(m, m->ebp);	/* 44e0ac: call ebp */
	m->eax = M32((DWORD)(0x9f8ea8u));	/* 44e0ae: mov eax, dword ptr [0x9f8ea8] */
	m->ecx = M32((DWORD)(0x9f8eacu));	/* 44e0b3: mov ecx, dword ptr [0x9f8eac] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e0b9: push 1 */
	m->edx = (DWORD)(m->eax + 0x7au);	/* 44e0bb: lea edx, [eax + 0x7a] */
	{ DWORD a_ = m->eax, b_ = 0x5au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44e0be: add eax, 0x5a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e0c1: push edx */
	m->edx = (DWORD)(m->ecx + 0x100u);	/* 44e0c2: lea edx, [ecx + 0x100] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e0c8: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xa0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44e0c9: add ecx, 0xa0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e0cf: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e0d0: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44e0d6u; native_call(m, 0x4282f0u);	/* 44e0d1: call 0x4282f0 */
	m->eax = M32((DWORD)(0x9f8d64u));	/* 44e0d6: mov eax, dword ptr [0x9f8d64] */
	m->ecx = M32((DWORD)(0x9f8d60u));	/* 44e0db: mov ecx, dword ptr [0x9f8d60] */
	m->edx = M32((DWORD)(0x9f8d5cu));	/* 44e0e1: mov edx, dword ptr [0x9f8d5c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e0e7: push eax */
	m->eax = M32((DWORD)(0x9f8d58u));	/* 44e0e8: mov eax, dword ptr [0x9f8d58] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e0ed: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e0ee: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e0ef: push eax */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e0f0: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x44e0fau; native_call(m, 0x41f0e0u);	/* 44e0f5: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44e0fa: add esp, 0x28 */
L_44e0fd:
	m->eax = M32((DWORD)(0x9f8eacu));	/* 44e0fd: mov eax, dword ptr [0x9f8eac] */
	m->ecx = m->ebx;	/* 44e102: mov ecx, ebx */
	{ DWORD a_ = m->ecx, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44e104: shl ecx, 7 */
	{ DWORD a_ = m->ecx, b_ = 0x7517a4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44e107: add ecx, 0x7517a4 */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x100u);	/* 44e10d: lea edx, [esi + eax + 0x100] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e114: push ecx */
	m->ecx = M32((DWORD)(0x9f8ea8u));	/* 44e115: mov ecx, dword ptr [0x9f8ea8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e11b: push edx */
	{ DWORD a_ = m->ecx, b_ = 0x62u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44e11c: add ecx, 0x62 */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xa0u);	/* 44e11f: lea edx, [esi + eax + 0xa0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e126: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e127: push edx */
	m->esp -= 4; M32(m->esp) = 0x44e12du; native_call(m, 0x4029d0u);	/* 44e128: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44e12d: add esp, 0x10 */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 44e130: inc ebx */
	{ DWORD a_ = m->ebx, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44e131: cmp ebx, 2 */
	if (m->sf != m->of) goto L_44df53;	/* 44e134: jl 0x44df53 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e13a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e13f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e144: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e149: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44e150u; native_call(m, m->ebp);	/* 44e14e: call ebp */
	m->eax = M32((DWORD)(0x9f8f24u));	/* 44e150: mov eax, dword ptr [0x9f8f24] */
	m->ecx = M32((DWORD)(0x9f8f20u));	/* 44e155: mov ecx, dword ptr [0x9f8f20] */
	m->edx = M32((DWORD)(0x9f8ea8u));	/* 44e15b: mov edx, dword ptr [0x9f8ea8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e161: push eax */
	m->eax = M32((DWORD)(0x9f8eacu));	/* 44e162: mov eax, dword ptr [0x9f8eac] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e167: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e168: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e169: push eax */
	m->esp -= 4; M32(m->esp) = 0x44e16fu; native_call(m, 0x428b50u);	/* 44e16a: call 0x428b50 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44e16f: add esp, 0x10 */
	m->edi = M32(m->esp); m->esp += 4;	/* 44e172: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44e173: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 44e174: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 44e175: pop ebx */
	m->ecx = M32(m->esp); m->esp += 4;	/* 44e176: pop ecx */
	m->esp += 4 + 0; return;	/* 44e177: ret  */
}

/* armc_41dab0 (0x41dab0), lifted by tools/lift.py */
static void lift_41dab0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41dab0: sub esp, 0x28 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 41dab3: push ebx */
	m->ebx = M32((DWORD)(0x4dcc94u));	/* 41dab4: mov ebx, dword ptr [0x4dcc94] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41daba: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 41dabb: push edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41dabc: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41dac1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41dac6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41dacb: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41dad0: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41dadau; native_call(m, 0x41f0e0u);	/* 41dad5: call 0x41f0e0 */
	m->edi = 0x7573a4u;	/* 41dada: mov edi, 0x7573a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41dadf: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41dae2: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41dae4: add esp, 0x14 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41dae7: repne scasb al, byte ptr es:[edi] */
	m->eax = M32((DWORD)(0x9dae74u));	/* 41dae9: mov eax, dword ptr [0x9dae74] */
	{ DWORD v_ = 0x7573a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 41daee: push 0x7573a4 */
	m->ecx = ~m->ecx;	/* 41daf3: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 41daf5: dec ecx */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41daf6: cmp eax, 1 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 41daf9: push ebx */
	if (!m->zf) goto L_41db0d;	/* 41dafa: jne 0x41db0d */
	m->eax = (DWORD)(m->ecx*8 + 0x0u);	/* 41dafc: lea eax, [ecx*8] */
	m->ecx = 0x27cu;	/* 41db03: mov ecx, 0x27c */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41db08: sub ecx, eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41db0a: push ecx */
	goto L_41db20;	/* 41db0b: jmp 0x41db20 */
L_41db0d:
	m->edx = (DWORD)(m->ecx*8 + 0x0u);	/* 41db0d: lea edx, [ecx*8] */
	m->eax = 0x27cu;	/* 41db14: mov eax, 0x27c */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 41db19: sub edx, ecx */
	{ DWORD a_ = m->edx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 41db1b: shl edx, 1 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41db1d: sub eax, edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41db1f: push eax */
L_41db20:
	m->esp -= 4; M32(m->esp) = 0x41db25u; native_call(m, 0x4028b0u);	/* 41db20: call 0x4028b0 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc14cu)));	/* 41db25: fld dword ptr [0x4dc14c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4dc0ccu));	/* 41db2b: fadd dword ptr [0x4dc0cc] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41db31: xor ecx, ecx */
	m->edi = 0x4ad564u;	/* 41db33: mov edi, 0x4ad564 */
	M32((DWORD)(m->esp + 0x2cu)) = m->ecx;	/* 41db38: mov dword ptr [esp + 0x2c], ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41db3c: xor eax, eax */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4dc04cu));	/* 41db3e: fadd dword ptr [0x4dc04c] */
	M32((DWORD)(m->esp + 0x30u)) = m->ecx;	/* 41db44: mov dword ptr [esp + 0x30], ecx */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41db48: add esp, 0xc */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 41db4b: mov dword ptr [esp + 0x28], ecx */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 41db4f: lea edx, [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4dbfccu));	/* 41db53: fadd dword ptr [0x4dbfcc] */
	M32((DWORD)(m->esp + 0x2cu)) = m->ecx;	/* 41db59: mov dword ptr [esp + 0x2c], ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 41db5d: push ebp */
	M32((DWORD)(m->esp + 0x34u)) = m->ecx;	/* 41db5e: mov dword ptr [esp + 0x34], ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41db62: or ecx, 0xffffffff */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4dbf4cu));	/* 41db65: fadd dword ptr [0x4dbf4c] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41db6b: repne scasb al, byte ptr es:[edi] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4dbeccu));	/* 41db6d: fadd dword ptr [0x4dbecc] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4dcea0u));	/* 41db73: fadd dword ptr [0x4dcea0] */
	m->ecx = ~m->ecx;	/* 41db79: not ecx */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4dc240u));	/* 41db7b: fadd dword ptr [0x4dc240] */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41db81: sub edi, ecx */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41db83: sub esp, 8 */
	m->eax = m->ecx;	/* 41db86: mov eax, ecx */
	m->esi = m->edi;	/* 41db88: mov esi, edi */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4dc2a4u));	/* 41db8a: fadd dword ptr [0x4dc2a4] */
	m->edi = m->edx;	/* 41db90: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41db92: shr ecx, 2 */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4dcf0cu));	/* 41db95: fadd dword ptr [0x4dcf0c] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41db9b: rep movsd dword ptr es:[edi], dword ptr [esi] */
	MF((DWORD)(0x4dc78cu)) = (float)ST(0); FPOP();	/* 41db9d: fstp dword ptr [0x4dc78c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dcb0cu)));	/* 41dba3: fld dword ptr [0x4dcb0c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41dba9: fstp qword ptr [esp] */
	m->ecx = m->eax;	/* 41dbac: mov ecx, eax */
	{ DWORD v_ = 0x4b0354u; m->esp -= 4; M32(m->esp) = v_; }	/* 41dbae: push 0x4b0354 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41dbb3: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41dbb6: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 41dbb8: lea ecx, [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41dbbc: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41dbc2u; native_call(m, 0x49e9ddu);	/* 41dbbd: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x20u);	/* 41dbc2: lea edi, [esp + 0x20] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41dbc6: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41dbc9: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 41dbcb: lea edx, [esp + 0x34] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41dbcf: repne scasb al, byte ptr es:[edi] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc78cu)));	/* 41dbd1: fld dword ptr [0x4dc78c] */
	MDBL((DWORD)(m->esp + 0x8u)) = (double)ST(0); FPOP();	/* 41dbd7: fstp qword ptr [esp + 8] */
	m->ecx = ~m->ecx;	/* 41dbdb: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41dbdd: sub edi, ecx */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41dbdf: add esp, 8 */
	m->esi = m->edi;	/* 41dbe2: mov esi, edi */
	m->ebp = m->ecx;	/* 41dbe4: mov ebp, ecx */
	m->edi = m->edx;	/* 41dbe6: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41dbe8: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41dbeb: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebp;	/* 41dbed: mov ecx, ebp */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41dbef: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41dbf0: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41dbf3: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebp;	/* 41dbf5: mov ecx, ebp */
	{ DWORD v_ = 0x4b0354u; m->esp -= 4; M32(m->esp) = v_; }	/* 41dbf7: push 0x4b0354 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41dbfc: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41dbff: rep movsb byte ptr es:[edi], byte ptr [esi] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 41dc01: mov dword ptr [esp + 0x1c], eax */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 41dc05: lea ecx, [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 41dc09: mov dword ptr [esp + 0x20], eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41dc0d: push ecx */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 41dc0e: mov dword ptr [esp + 0x28], eax */
	M32((DWORD)(m->esp + 0x2cu)) = m->eax;	/* 41dc12: mov dword ptr [esp + 0x2c], eax */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 41dc16: mov dword ptr [esp + 0x30], eax */
	m->esp -= 4; M32(m->esp) = 0x41dc1fu; native_call(m, 0x49e9ddu);	/* 41dc1a: call 0x49e9dd */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc78cu)));	/* 41dc1f: fld dword ptr [0x4dc78c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4dcb0cu)); FPOP();	/* 41dc25: fcomp dword ptr [0x4dcb0c] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41dc2b: add esp, 0x10 */
	m->ebp = M32(m->esp); m->esp += 4;	/* 41dc2e: pop ebp */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41dc2f: fnstsw ax */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41dc31: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41dc36: push 0 */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41dc38: test ah, 0x41 */
	if (!m->zf) goto L_41dc46;	/* 41dc3b: jne 0x41dc46 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41dc3d: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41dc3f: push 0x3f800000 */
	goto L_41dc4d;	/* 41dc44: jmp 0x41dc4d */
L_41dc46:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41dc46: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41dc4b: push 0 */
L_41dc4d:
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41dc4d: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41dc57u; native_call(m, 0x41f0e0u);	/* 41dc52: call 0x41f0e0 */
	m->edi = (DWORD)(m->esp + 0x20u);	/* 41dc57: lea edi, [esp + 0x20] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41dc5b: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41dc5e: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41dc60: add esp, 0x14 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41dc63: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41dc65: not ecx */
	m->edx = (DWORD)(m->esp + 0xcu);	/* 41dc67: lea edx, [esp + 0xc] */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 41dc6b: dec ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41dc6c: push edx */
	m->edx = m->ecx;	/* 41dc6d: mov edx, ecx */
	m->edi = (DWORD)(m->esp + 0x24u);	/* 41dc6f: lea edi, [esp + 0x24] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41dc73: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41dc76: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41dc78: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 41dc7a: dec ecx */
	m->esi = (DWORD)(m->ebx + 0x10u);	/* 41dc7b: lea esi, [ebx + 0x10] */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 41dc7e: add edx, ecx */
	m->ecx = 0x27eu;	/* 41dc80: mov ecx, 0x27e */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41dc85: push esi */
	m->eax = (DWORD)(m->edx*8 + 0x0u);	/* 41dc86: lea eax, [edx*8] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41dc8d: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41dc8f: shl eax, 1 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41dc91: sub ecx, eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41dc93: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41dc99u; native_call(m, 0x4028b0u);	/* 41dc94: call 0x4028b0 */
	m->edi = (DWORD)(m->esp + 0x2cu);	/* 41dc99: lea edi, [esp + 0x2c] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41dc9d: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41dca0: xor eax, eax */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41dca2: push 0x3f800000 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41dca7: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41dca9: not ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41dcab: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41dcb0: push 0x3f800000 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 41dcb5: dec ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41dcb6: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41dcbb: push 0x76d438 */
	m->edi = m->ecx;	/* 41dcc0: mov edi, ecx */
	m->esp -= 4; M32(m->esp) = 0x41dcc7u; native_call(m, 0x41f0e0u);	/* 41dcc2: call 0x41f0e0 */
	m->eax = (DWORD)(m->edi*8 + 0x0u);	/* 41dcc7: lea eax, [edi*8] */
	m->edx = (DWORD)(m->esp + 0x40u);	/* 41dcce: lea edx, [esp + 0x40] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41dcd2: sub eax, edi */
	m->ecx = 0x27eu;	/* 41dcd4: mov ecx, 0x27e */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41dcd9: shl eax, 1 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41dcdb: push edx */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41dcdc: sub ecx, eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41dcde: push esi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41dcdf: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41dce5u; native_call(m, 0x4028b0u);	/* 41dce0: call 0x4028b0 */
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41dce5: add esp, 0x2c */
	m->edi = M32(m->esp); m->esp += 4;	/* 41dce8: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 41dce9: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 41dcea: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41dceb: add esp, 0x28 */
	m->esp += 4 + 0; return;	/* 41dcee: ret  */
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
