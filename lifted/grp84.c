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

static void lift_41a280(X86 *m);

/* armc_41a280 (0x41a280), lifted by tools/lift.py */
static void lift_41a280(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x7cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41a280: sub esp, 0x7c */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 41a283: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 41a288: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a28e: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 41a28f: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41a290: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 41a291: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a292: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a293: push ecx */
	M32((DWORD)(m->esp + 0x1cu)) = 0x0u;	/* 41a294: mov dword ptr [esp + 0x1c], 0 */
	M32((DWORD)(m->esp + 0x18u)) = 0x0u;	/* 41a29c: mov dword ptr [esp + 0x18], 0 */
	m->esp -= 4; M32(m->esp) = 0x41a2a9u; native_call(m, 0x40e4d0u);	/* 41a2a4: call 0x40e4d0 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a2a9: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a2ae: push 0x3f000000 */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 41a2b3: push 0x3e4ccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 41a2b8: push 0x3dcccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a2bd: push 0x9da480 */
	M32((DWORD)(m->esp + 0x38u)) = m->eax;	/* 41a2c2: mov dword ptr [esp + 0x38], eax */
	m->esp -= 4; M32(m->esp) = 0x41a2cbu; native_call(m, 0x41f0e0u);	/* 41a2c6: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4dcc94u));	/* 41a2cb: mov eax, dword ptr [0x4dcc94] */
	m->ecx = M32((DWORD)(0x4dcc98u));	/* 41a2d0: mov ecx, dword ptr [0x4dcc98] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a2d6: push 1 */
	m->edx = (DWORD)(m->eax + 0xd0u);	/* 41a2d8: lea edx, [eax + 0xd0] */
	{ DWORD a_ = m->eax, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41a2de: add eax, 0x30 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a2e1: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a2e2: push ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffff38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41a2e3: add ecx, 0xffffff38 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a2e9: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a2ea: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41a2f0u; native_call(m, 0x427970u);	/* 41a2eb: call 0x427970 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a2f0: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a2f5: push 0x3f000000 */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 41a2fa: push 0x3e4ccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 41a2ff: push 0x3dcccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a304: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x41a30eu; native_call(m, 0x41f0e0u);	/* 41a309: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4dcc94u));	/* 41a30e: mov eax, dword ptr [0x4dcc94] */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41a313: add esp, 0x44 */
	m->ecx = (DWORD)(m->eax + 0x180u);	/* 41a316: lea ecx, [eax + 0x180] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a31c: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a31e: push ecx */
	m->ecx = M32((DWORD)(0x4dcc98u));	/* 41a31f: mov ecx, dword ptr [0x4dcc98] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a325: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xe0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41a326: add eax, 0xe0 */
	{ DWORD a_ = m->ecx, b_ = 0xffffff38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41a32b: add ecx, 0xffffff38 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a331: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a332: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41a338u; native_call(m, 0x427970u);	/* 41a333: call 0x427970 */
	m->edx = M32((DWORD)(0x4dbc64u));	/* 41a338: mov edx, dword ptr [0x4dbc64] */
	m->eax = M32((DWORD)(0x4dbc60u));	/* 41a33e: mov eax, dword ptr [0x4dbc60] */
	m->ecx = M32((DWORD)(0x4dbc5cu));	/* 41a343: mov ecx, dword ptr [0x4dbc5c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a349: push edx */
	m->edx = M32((DWORD)(0x4dbc58u));	/* 41a34a: mov edx, dword ptr [0x4dbc58] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a350: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a351: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a352: push edx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a353: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41a35du; native_call(m, 0x41f0e0u);	/* 41a358: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4dcc98u));	/* 41a35d: mov eax, dword ptr [0x4dcc98] */
	m->ecx = M32((DWORD)(0x4dcc94u));	/* 41a362: mov ecx, dword ptr [0x4dcc94] */
	{ DWORD v_ = 0x75d3a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a368: push 0x75d3a4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a36d: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x34u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41a36e: add ecx, 0x34 */
	{ DWORD a_ = m->eax, b_ = 0xffffff38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41a371: add eax, 0xffffff38 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a376: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a377: push eax */
	m->esp -= 4; M32(m->esp) = 0x41a37du; native_call(m, 0x402740u);	/* 41a378: call 0x402740 */
	m->eax = M32((DWORD)(0x4dcc98u));	/* 41a37d: mov eax, dword ptr [0x4dcc98] */
	m->edx = M32((DWORD)(0x4dcc94u));	/* 41a382: mov edx, dword ptr [0x4dcc94] */
	{ DWORD v_ = 0x75d424u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a388: push 0x75d424 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a38d: push eax */
	{ DWORD a_ = m->edx, b_ = 0xe4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 41a38e: add edx, 0xe4 */
	{ DWORD a_ = m->eax, b_ = 0xffffff38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41a394: add eax, 0xffffff38 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a399: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a39a: push eax */
	m->esp -= 4; M32(m->esp) = 0x41a3a0u; native_call(m, 0x402740u);	/* 41a39b: call 0x402740 */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41a3a0: add esp, 0x48 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 41a3a3: xor ebx, ebx */
L_41a3a5:
	m->ecx = 0xcu;	/* 41a3a5: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41a3aa: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x24u);	/* 41a3ac: lea edi, [esp + 0x24] */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 41a3b0: lea edx, [esp + 0x24] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 41a3b4: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 41a3b6: stosw word ptr es:[edi], ax */
	m->ecx = 0xcu;	/* 41a3b8: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41a3bd: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x58u);	/* 41a3bf: lea edi, [esp + 0x58] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 41a3c3: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 41a3c5: stosw word ptr es:[edi], ax */
	m->eax = m->ebx;	/* 41a3c7: mov eax, ebx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a3c9: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41a3cc: shl eax, 7 */
	m->edi = (DWORD)(m->eax + 0x75d4a4u);	/* 41a3cf: lea edi, [eax + 0x75d4a4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41a3d5: xor eax, eax */
	M32((DWORD)(m->esp + 0x20u)) = m->edi;	/* 41a3d7: mov dword ptr [esp + 0x20], edi */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41a3db: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41a3dd: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41a3df: sub edi, ecx */
	m->eax = m->ecx;	/* 41a3e1: mov eax, ecx */
	m->esi = m->edi;	/* 41a3e3: mov esi, edi */
	m->edi = m->edx;	/* 41a3e5: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 41a3e7: lea edx, [esp + 0x24] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41a3eb: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41a3ee: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 41a3f0: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41a3f2: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a3f4: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41a3f7: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b037cu;	/* 41a3f9: mov edi, 0x4b037c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a3fe: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41a401: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41a403: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41a405: sub edi, ecx */
	m->esi = m->edi;	/* 41a407: mov esi, edi */
	m->ebp = m->ecx;	/* 41a409: mov ebp, ecx */
	m->edi = m->edx;	/* 41a40b: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a40d: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41a410: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebp;	/* 41a412: mov ecx, ebp */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41a414: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41a415: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41a418: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebp;	/* 41a41a: mov ecx, ebp */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a41c: and ecx, 3 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41a41f: test ebx, ebx */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41a421: rep movsb byte ptr es:[edi], byte ptr [esi] */
	if (!m->zf) goto L_41a470;	/* 41a423: jne 0x41a470 */
	m->eax = M32((DWORD)(0x4dc4b0u));	/* 41a425: mov eax, dword ptr [0x4dc4b0] */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41a42a: lea eax, [eax + eax*2] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax*8 + 0x4dc4b8u)));	/* 41a42d: fld dword ptr [eax*8 + 0x4dc4b8] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 41a434: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41a439: test eax, eax */
	if (m->sf != m->of) goto L_41a44b;	/* 41a43b: jl 0x41a44b */
	{ DWORD a_ = m->eax, b_ = 0xb4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41a43d: cmp eax, 0xb4 */
	if (m->sf == m->of) goto L_41a44b;	/* 41a442: jge 0x41a44b */
	{ DWORD a_ = m->eax, b_ = 0xb4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41a444: add eax, 0xb4 */
	goto L_41a450;	/* 41a449: jmp 0x41a450 */
L_41a44b:
	{ DWORD a_ = m->eax, b_ = 0xb4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41a44b: sub eax, 0xb4 */
L_41a450:
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 41a450: mov dword ptr [esp + 0x18], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x18u)));	/* 41a454: fild dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9490u));	/* 41a458: fmul dword ptr [0x4a9490] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 41a45e: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a463: push eax */
	m->ecx = (DWORD)(m->esp + 0x5cu);	/* 41a464: lea ecx, [esp + 0x5c] */
	{ DWORD v_ = 0x4b0378u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a468: push 0x4b0378 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a46d: push ecx */
	goto L_41a4da;	/* 41a46e: jmp 0x41a4da */
L_41a470:
	{ DWORD a_ = m->ebx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41a470: cmp ebx, 1 */
	if (!m->zf) goto L_41a4a6;	/* 41a473: jne 0x41a4a6 */
	m->eax = M32((DWORD)(0x4dc4b0u));	/* 41a475: mov eax, dword ptr [0x4dc4b0] */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41a47a: lea edx, [eax + eax*2] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx*8 + 0x4dc4bcu)));	/* 41a47d: fld dword ptr [edx*8 + 0x4dc4bc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 41a484: fmul dword ptr [0x4a93f4] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 41a48a: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41a48f: cmp eax, 0x64 */
	if (m->sf != m->of) goto L_41a499;	/* 41a492: jl 0x41a499 */
	m->eax = 0x63u;	/* 41a494: mov eax, 0x63 */
L_41a499:
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a499: push eax */
	m->eax = (DWORD)(m->esp + 0x5cu);	/* 41a49a: lea eax, [esp + 0x5c] */
	{ DWORD v_ = 0x4b0378u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a49e: push 0x4b0378 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a4a3: push eax */
	goto L_41a4da;	/* 41a4a4: jmp 0x41a4da */
L_41a4a6:
	{ DWORD a_ = m->ebx, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41a4a6: cmp ebx, 2 */
	if (!m->zf) goto L_41a4e2;	/* 41a4a9: jne 0x41a4e2 */
	m->eax = M32((DWORD)(0x4dc4b0u));	/* 41a4ab: mov eax, dword ptr [0x4dc4b0] */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41a4b0: lea ecx, [eax + eax*2] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx*8 + 0x4dc4c0u)));	/* 41a4b3: fld dword ptr [ecx*8 + 0x4dc4c0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 41a4ba: fmul dword ptr [0x4a93f4] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 41a4c0: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41a4c5: cmp eax, 0x64 */
	if (m->sf != m->of) goto L_41a4cf;	/* 41a4c8: jl 0x41a4cf */
	m->eax = 0x63u;	/* 41a4ca: mov eax, 0x63 */
L_41a4cf:
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a4cf: push eax */
	m->edx = (DWORD)(m->esp + 0x5cu);	/* 41a4d0: lea edx, [esp + 0x5c] */
	{ DWORD v_ = 0x4b0378u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a4d4: push 0x4b0378 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a4d9: push edx */
L_41a4da:
	m->esp -= 4; M32(m->esp) = 0x41a4dfu; native_call(m, 0x49e9ddu);	/* 41a4da: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41a4df: add esp, 0xc */
L_41a4e2:
	m->edi = (DWORD)(m->esp + 0x58u);	/* 41a4e2: lea edi, [esp + 0x58] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a4e6: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41a4e9: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 41a4eb: lea edx, [esp + 0x24] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41a4ef: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41a4f1: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41a4f3: sub edi, ecx */
	m->esi = m->edi;	/* 41a4f5: mov esi, edi */
	m->ebp = m->ecx;	/* 41a4f7: mov ebp, ecx */
	m->edi = m->edx;	/* 41a4f9: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a4fb: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41a4fe: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebp;	/* 41a500: mov ecx, ebp */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41a502: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41a503: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41a506: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebp;	/* 41a508: mov ecx, ebp */
	m->ebp = (DWORD)(m->ebx + m->ebx*2 + 0x0u);	/* 41a50a: lea ebp, [ebx + ebx*2] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a50d: and ecx, 3 */
	m->eax = (DWORD)(m->esp + 0x24u);	/* 41a510: lea eax, [esp + 0x24] */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41a514: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x4dcc94u));	/* 41a516: mov ecx, dword ptr [0x4dcc94] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a51c: push eax */
	m->eax = M32((DWORD)(0x4dcc98u));	/* 41a51d: mov eax, dword ptr [0x4dcc98] */
	{ DWORD a_ = m->ebp, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ebp = r_; } }	/* 41a522: shl ebp, 4 */
	{ DWORD a_ = m->eax, b_ = 0xffffff40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41a525: add eax, 0xffffff40 */
	m->edx = (DWORD)(m->ecx + m->ebp*1 + 0x46u);	/* 41a52a: lea edx, [ecx + ebp + 0x46] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a52e: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a52f: push eax */
	m->esp -= 4; M32(m->esp) = 0x41a535u; native_call(m, 0x402620u);	/* 41a530: call 0x402620 */
	m->ecx = 0xcu;	/* 41a535: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41a53a: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 41a53c: lea edi, [esp + 0x30] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41a540: add esp, 0xc */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 41a543: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 41a545: stosw word ptr es:[edi], ax */
	m->ecx = 0xcu;	/* 41a547: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41a54c: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x58u);	/* 41a54e: lea edi, [esp + 0x58] */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 41a552: lea edx, [esp + 0x24] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 41a556: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 41a558: stosw word ptr es:[edi], ax */
	m->edi = M32((DWORD)(m->esp + 0x20u));	/* 41a55a: mov edi, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a55e: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41a561: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41a563: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41a565: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41a567: sub edi, ecx */
	m->eax = m->ecx;	/* 41a569: mov eax, ecx */
	m->esi = m->edi;	/* 41a56b: mov esi, edi */
	m->edi = m->edx;	/* 41a56d: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 41a56f: lea edx, [esp + 0x24] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41a573: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41a576: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 41a578: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41a57a: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a57c: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41a57f: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b037cu;	/* 41a581: mov edi, 0x4b037c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a586: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41a589: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41a58b: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41a58d: sub edi, ecx */
	m->esi = m->edi;	/* 41a58f: mov esi, edi */
	m->edi = m->edx;	/* 41a591: mov edi, edx */
	m->edx = m->ecx;	/* 41a593: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a595: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41a598: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 41a59a: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41a59c: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41a59d: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41a5a0: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 41a5a2: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a5a4: and ecx, 3 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41a5a7: test ebx, ebx */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41a5a9: rep movsb byte ptr es:[edi], byte ptr [esi] */
	if (!m->zf) goto L_41a5fb;	/* 41a5ab: jne 0x41a5fb */
	m->eax = M32((DWORD)(0x4dc4b0u));	/* 41a5ad: mov eax, dword ptr [0x4dc4b0] */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41a5b2: lea eax, [eax + eax*2] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax*8 + 0x4dc4c4u)));	/* 41a5b5: fld dword ptr [eax*8 + 0x4dc4c4] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 41a5bc: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41a5c1: test eax, eax */
	if (m->sf != m->of) goto L_41a5d3;	/* 41a5c3: jl 0x41a5d3 */
	{ DWORD a_ = m->eax, b_ = 0xb4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41a5c5: cmp eax, 0xb4 */
	if (m->sf == m->of) goto L_41a5d3;	/* 41a5ca: jge 0x41a5d3 */
	{ DWORD a_ = m->eax, b_ = 0xb4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41a5cc: add eax, 0xb4 */
	goto L_41a5d8;	/* 41a5d1: jmp 0x41a5d8 */
L_41a5d3:
	{ DWORD a_ = m->eax, b_ = 0xb4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41a5d3: sub eax, 0xb4 */
L_41a5d8:
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 41a5d8: mov dword ptr [esp + 0x18], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x18u)));	/* 41a5dc: fild dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9490u));	/* 41a5e0: fmul dword ptr [0x4a9490] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 41a5e6: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a5eb: push eax */
	m->ecx = (DWORD)(m->esp + 0x5cu);	/* 41a5ec: lea ecx, [esp + 0x5c] */
	{ DWORD v_ = 0x4b0378u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a5f0: push 0x4b0378 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a5f5: push ecx */
	goto L_41a67d;	/* 41a5f6: jmp 0x41a67d */
L_41a5fb:
	{ DWORD a_ = m->ebx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41a5fb: cmp ebx, 1 */
	if (!m->zf) goto L_41a63d;	/* 41a5fe: jne 0x41a63d */
	m->eax = M32((DWORD)(0x4dc4b0u));	/* 41a600: mov eax, dword ptr [0x4dc4b0] */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41a605: lea edx, [eax + eax*2] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx*8 + 0x4dc4c8u)));	/* 41a608: fld dword ptr [edx*8 + 0x4dc4c8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 41a60f: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 41a615: fmul dword ptr [0x4a93f4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 41a61b: fmul dword ptr [0x4a942c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 41a621: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41a626: cmp eax, 0x64 */
	if (m->sf != m->of) goto L_41a630;	/* 41a629: jl 0x41a630 */
	m->eax = 0x63u;	/* 41a62b: mov eax, 0x63 */
L_41a630:
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a630: push eax */
	m->eax = (DWORD)(m->esp + 0x5cu);	/* 41a631: lea eax, [esp + 0x5c] */
	{ DWORD v_ = 0x4b0378u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a635: push 0x4b0378 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a63a: push eax */
	goto L_41a67d;	/* 41a63b: jmp 0x41a67d */
L_41a63d:
	{ DWORD a_ = m->ebx, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41a63d: cmp ebx, 2 */
	if (!m->zf) goto L_41a685;	/* 41a640: jne 0x41a685 */
	m->eax = M32((DWORD)(0x4dc4b0u));	/* 41a642: mov eax, dword ptr [0x4dc4b0] */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41a647: lea ecx, [eax + eax*2] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx*8 + 0x4dc4ccu)));	/* 41a64a: fld dword ptr [ecx*8 + 0x4dc4cc] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 41a651: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 41a657: fmul dword ptr [0x4a93f4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 41a65d: fmul dword ptr [0x4a942c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 41a663: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41a668: cmp eax, 0x64 */
	if (m->sf != m->of) goto L_41a672;	/* 41a66b: jl 0x41a672 */
	m->eax = 0x63u;	/* 41a66d: mov eax, 0x63 */
L_41a672:
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a672: push eax */
	m->edx = (DWORD)(m->esp + 0x5cu);	/* 41a673: lea edx, [esp + 0x5c] */
	{ DWORD v_ = 0x4b0378u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a677: push 0x4b0378 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a67c: push edx */
L_41a67d:
	m->esp -= 4; M32(m->esp) = 0x41a682u; native_call(m, 0x49e9ddu);	/* 41a67d: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41a682: add esp, 0xc */
L_41a685:
	m->edi = (DWORD)(m->esp + 0x58u);	/* 41a685: lea edi, [esp + 0x58] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a689: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41a68c: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 41a68e: lea edx, [esp + 0x24] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41a692: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41a694: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41a696: sub edi, ecx */
	m->esi = m->edi;	/* 41a698: mov esi, edi */
	m->edi = m->edx;	/* 41a69a: mov edi, edx */
	m->edx = m->ecx;	/* 41a69c: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a69e: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41a6a1: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 41a6a3: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41a6a5: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41a6a6: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41a6a9: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 41a6ab: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x24u);	/* 41a6ad: lea eax, [esp + 0x24] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a6b1: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a6b4: push eax */
	m->eax = M32((DWORD)(0x4dcc98u));	/* 41a6b5: mov eax, dword ptr [0x4dcc98] */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41a6ba: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x4dcc94u));	/* 41a6bc: mov ecx, dword ptr [0x4dcc94] */
	{ DWORD a_ = m->eax, b_ = 0xffffff40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41a6c2: add eax, 0xffffff40 */
	m->edx = (DWORD)(m->ecx + m->ebp*1 + 0xf6u);	/* 41a6c7: lea edx, [ecx + ebp + 0xf6] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a6ce: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a6cf: push eax */
	m->esp -= 4; M32(m->esp) = 0x41a6d5u; native_call(m, 0x402620u);	/* 41a6d0: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41a6d5: add esp, 0xc */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 41a6d8: inc ebx */
	{ DWORD a_ = m->ebx, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41a6d9: cmp ebx, 3 */
	if (m->sf != m->of) goto L_41a3a5;	/* 41a6dc: jl 0x41a3a5 */
	m->ebx = M32((DWORD)(0x4a9224u));	/* 41a6e2: mov ebx, dword ptr [0x4a9224] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a6e8: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x41a6efu; native_call(m, m->ebx);	/* 41a6ed: call ebx */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 41a6ef: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 41a6f4: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a6f6: and ecx, 0x800001ff */
	if (!m->sf) goto L_41a706;	/* 41a6fc: jns 0x41a706 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 41a6fe: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a6ff: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 41a705: inc ecx */
L_41a706:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 41a706: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 41a707: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a70d: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41a70e: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 41a710: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41a716: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 41a719: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x41a722u; native_call(m, 0x4566c0u);	/* 41a71d: call 0x4566c0 */
	m->ebp = M32((DWORD)(0x4a9228u));	/* 41a722: mov ebp, dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a728: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a72d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a732: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a737: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41a73eu; native_call(m, m->ebp);	/* 41a73c: call ebp */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 41a73e: xor edi, edi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 41a740: xor esi, esi */
L_41a742:
	{ DWORD a_ = M32((DWORD)(0x4dc4b0u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41a742: cmp dword ptr [0x4dc4b0], edi */
	if (!m->zf) goto L_41a751;	/* 41a748: jne 0x41a751 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 41a74a: push 0x3f4ccccd */
	goto L_41a756;	/* 41a74f: jmp 0x41a756 */
L_41a751:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 41a751: push 0x3ecccccd */
L_41a756:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a756: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a75b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a760: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41a767u; native_call(m, m->ebp);	/* 41a765: call ebp */
	m->eax = M32((DWORD)(0x4dcc94u));	/* 41a767: mov eax, dword ptr [0x4dcc94] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a76c: push 1 */
	m->ecx = (DWORD)(m->esi + m->eax*1 + 0x6cu);	/* 41a76e: lea ecx, [esi + eax + 0x6c] */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x40u);	/* 41a772: lea eax, [esi + eax + 0x40] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a776: push ecx */
	m->ecx = M32((DWORD)(0x4dcc90u));	/* 41a777: mov ecx, dword ptr [0x4dcc90] */
	m->edx = (DWORD)(m->ecx + 0xb0u);	/* 41a77d: lea edx, [ecx + 0xb0] */
	{ DWORD a_ = m->ecx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41a783: add ecx, 0x10 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a786: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a787: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a788: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41a78eu; native_call(m, 0x4283e0u);	/* 41a789: call 0x4283e0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41a78e: add esp, 0x14 */
	{ DWORD a_ = m->esi, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 41a791: add esi, 0x30 */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 41a794: inc edi */
	{ DWORD a_ = m->esi, b_ = 0x120u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41a795: cmp esi, 0x120 */
	if (m->sf != m->of) goto L_41a742;	/* 41a79b: jl 0x41a742 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 41a79d: xor esi, esi */
L_41a79f:
	{ DWORD a_ = M32((DWORD)(0x4dc4b0u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41a79f: cmp dword ptr [0x4dc4b0], esi */
	if (!m->zf) goto L_41a7c4;	/* 41a7a5: jne 0x41a7c4 */
	m->ecx = M32((DWORD)(0x4dbc64u));	/* 41a7a7: mov ecx, dword ptr [0x4dbc64] */
	m->edx = M32((DWORD)(0x4dbc60u));	/* 41a7ad: mov edx, dword ptr [0x4dbc60] */
	m->eax = M32((DWORD)(0x4dbc5cu));	/* 41a7b3: mov eax, dword ptr [0x4dbc5c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a7b8: push ecx */
	m->ecx = M32((DWORD)(0x4dbc58u));	/* 41a7b9: mov ecx, dword ptr [0x4dbc58] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a7bf: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a7c0: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a7c1: push ecx */
	goto L_41a7df;	/* 41a7c2: jmp 0x41a7df */
L_41a7c4:
	m->edx = M32((DWORD)(0x4dc1dcu));	/* 41a7c4: mov edx, dword ptr [0x4dc1dc] */
	m->eax = M32((DWORD)(0x4dc1d8u));	/* 41a7ca: mov eax, dword ptr [0x4dc1d8] */
	m->ecx = M32((DWORD)(0x4dc1d4u));	/* 41a7cf: mov ecx, dword ptr [0x4dc1d4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a7d5: push edx */
	m->edx = M32((DWORD)(0x4dc1d0u));	/* 41a7d6: mov edx, dword ptr [0x4dc1d0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a7dc: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a7dd: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a7de: push edx */
L_41a7df:
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a7df: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41a7e9u; native_call(m, 0x41f0e0u);	/* 41a7e4: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41a7e9: add esp, 0x14 */
	{ DWORD a_ = m->esi, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41a7ec: cmp esi, 5 */
	if (!m->zf) goto L_41a81d;	/* 41a7ef: jne 0x41a81d */
	m->eax = M32((DWORD)(0x4dcc90u));	/* 41a7f1: mov eax, dword ptr [0x4dcc90] */
	m->edx = M32((DWORD)(0x4dcc94u));	/* 41a7f6: mov edx, dword ptr [0x4dcc94] */
	{ DWORD v_ = 0x756d24u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a7fc: push 0x756d24 */
	{ DWORD a_ = m->edx, b_ = 0x13du & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 41a801: add edx, 0x13d */
	m->ecx = (DWORD)(m->eax + 0xb0u);	/* 41a807: lea ecx, [eax + 0xb0] */
	{ DWORD a_ = m->eax, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41a80d: add eax, 0x10 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a810: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a811: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a812: push eax */
	m->esp -= 4; M32(m->esp) = 0x41a818u; native_call(m, 0x4029d0u);	/* 41a813: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41a818: add esp, 0x10 */
	goto L_41a84b;	/* 41a81b: jmp 0x41a84b */
L_41a81d:
	m->edx = M32((DWORD)(0x4dcc94u));	/* 41a81d: mov edx, dword ptr [0x4dcc94] */
	m->eax = m->esi;	/* 41a823: mov eax, esi */
	{ DWORD a_ = m->eax, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41a825: shl eax, 7 */
	m->ecx = (DWORD)(m->esi + m->esi*2 + 0x0u);	/* 41a828: lea ecx, [esi + esi*2] */
	{ DWORD a_ = m->eax, b_ = 0x756aa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41a82b: add eax, 0x756aa4 */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41a830: shl ecx, 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a833: push eax */
	m->eax = (DWORD)(m->ecx + m->edx*1 + 0x44u);	/* 41a834: lea eax, [ecx + edx + 0x44] */
	m->ecx = M32((DWORD)(0x4dcc90u));	/* 41a838: mov ecx, dword ptr [0x4dcc90] */
	{ DWORD a_ = m->ecx, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41a83e: add ecx, 0x18 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a841: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a842: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41a848u; native_call(m, 0x402620u);	/* 41a843: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41a848: add esp, 0xc */
L_41a84b:
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 41a84b: inc esi */
	{ DWORD a_ = m->esi, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41a84c: cmp esi, 6 */
	if (m->sf != m->of) goto L_41a79f;	/* 41a84f: jl 0x41a79f */
	m->eax = M32((DWORD)(0x4dbc68u));	/* 41a855: mov eax, dword ptr [0x4dbc68] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41a85a: test eax, eax */
	if (m->zf) goto L_41a92a;	/* 41a85c: je 0x41a92a */
	m->edx = M32((DWORD)(0x4dbc64u));	/* 41a862: mov edx, dword ptr [0x4dbc64] */
	m->eax = M32((DWORD)(0x4dbc60u));	/* 41a868: mov eax, dword ptr [0x4dbc60] */
	m->ecx = M32((DWORD)(0x4dbc5cu));	/* 41a86d: mov ecx, dword ptr [0x4dbc5c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a873: push edx */
	m->edx = M32((DWORD)(0x4dbc58u));	/* 41a874: mov edx, dword ptr [0x4dbc58] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a87a: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a87b: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a87c: push edx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a87d: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41a887u; native_call(m, 0x41f0e0u);	/* 41a882: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4dcc94u));	/* 41a887: mov eax, dword ptr [0x4dcc94] */
	m->ecx = M32((DWORD)(0x4dcc90u));	/* 41a88c: mov ecx, dword ptr [0x4dcc90] */
	{ DWORD a_ = m->eax, b_ = 0x54u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41a892: add eax, 0x54 */
	{ DWORD v_ = 0x4dceb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a895: push 0x4dceb8 */
	{ DWORD a_ = m->ecx, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41a89a: add ecx, 0x28 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a89d: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a89e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41a8a4u; native_call(m, 0x402620u);	/* 41a89f: call 0x402620 */
	m->edx = M32((DWORD)(0x4dcc94u));	/* 41a8a4: mov edx, dword ptr [0x4dcc94] */
	m->eax = M32((DWORD)(0x4dcc90u));	/* 41a8aa: mov eax, dword ptr [0x4dcc90] */
	{ DWORD a_ = m->edx, b_ = 0x84u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 41a8af: add edx, 0x84 */
	{ DWORD v_ = 0x4dbc08u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a8b5: push 0x4dbc08 */
	{ DWORD a_ = m->eax, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41a8ba: add eax, 0x28 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a8bd: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a8be: push eax */
	m->esp -= 4; M32(m->esp) = 0x41a8c4u; native_call(m, 0x402620u);	/* 41a8bf: call 0x402620 */
	m->ecx = M32((DWORD)(0x4dcc94u));	/* 41a8c4: mov ecx, dword ptr [0x4dcc94] */
	m->edx = M32((DWORD)(0x4dcc90u));	/* 41a8ca: mov edx, dword ptr [0x4dcc90] */
	{ DWORD a_ = m->ecx, b_ = 0xb4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41a8d0: add ecx, 0xb4 */
	{ DWORD v_ = 0x4dc250u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a8d6: push 0x4dc250 */
	{ DWORD a_ = m->edx, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 41a8db: add edx, 0x28 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a8de: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a8df: push edx */
	m->esp -= 4; M32(m->esp) = 0x41a8e5u; native_call(m, 0x402620u);	/* 41a8e0: call 0x402620 */
	m->eax = M32((DWORD)(0x4dcc94u));	/* 41a8e5: mov eax, dword ptr [0x4dcc94] */
	m->ecx = M32((DWORD)(0x4dcc90u));	/* 41a8ea: mov ecx, dword ptr [0x4dcc90] */
	{ DWORD a_ = m->eax, b_ = 0xe4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41a8f0: add eax, 0xe4 */
	{ DWORD v_ = 0x4dc1e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a8f5: push 0x4dc1e8 */
	{ DWORD a_ = m->ecx, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41a8fa: add ecx, 0x28 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a8fd: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a8fe: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41a904u; native_call(m, 0x402620u);	/* 41a8ff: call 0x402620 */
	m->edx = M32((DWORD)(0x4dcc94u));	/* 41a904: mov edx, dword ptr [0x4dcc94] */
	m->eax = M32((DWORD)(0x4dcc90u));	/* 41a90a: mov eax, dword ptr [0x4dcc90] */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41a90f: add esp, 0x44 */
	{ DWORD a_ = m->edx, b_ = 0x114u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 41a912: add edx, 0x114 */
	{ DWORD a_ = m->eax, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41a918: add eax, 0x28 */
	{ DWORD v_ = 0x4dce40u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a91b: push 0x4dce40 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a920: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a921: push eax */
	m->esp -= 4; M32(m->esp) = 0x41a927u; native_call(m, 0x402620u);	/* 41a922: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41a927: add esp, 0xc */
L_41a92a:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a92a: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x41a931u; native_call(m, m->ebx);	/* 41a92f: call ebx */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 41a931: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 41a936: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a938: and ecx, 0x800001ff */
	if (!m->sf) goto L_41a948;	/* 41a93e: jns 0x41a948 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 41a940: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a941: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 41a947: inc ecx */
L_41a948:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 41a948: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 41a949: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a94f: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41a950: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 41a952: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41a958: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 41a95b: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x41a964u; native_call(m, 0x4566c0u);	/* 41a95f: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a964: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a969: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a96e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a973: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41a97au; native_call(m, m->ebp);	/* 41a978: call ebp */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a97a: push 7 */
	m->esp -= 4; M32(m->esp) = 0x41a982u; native_call(m, M32(0x4a921cu));	/* 41a97c: call dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(0x4a920cu));	/* 41a982: mov esi, dword ptr [0x4a920c] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 41a988: xor ebx, ebx */
L_41a98a:
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41a98a: test ebx, ebx */
	if (!m->zf) goto L_41aac2;	/* 41a98c: jne 0x41aac2 */
	{ DWORD v_ = 0x3e000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a992: push 0x3e000000 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a997: push ebx */
	m->esp -= 4; M32(m->esp) = 0x41a99au; native_call(m, m->esi);	/* 41a998: call esi */
	m->eax = M32((DWORD)(0x4dcc94u));	/* 41a99a: mov eax, dword ptr [0x4dcc94] */
	m->ecx = M32((DWORD)(0x4dcc98u));	/* 41a99f: mov ecx, dword ptr [0x4dcc98] */
	{ DWORD a_ = m->eax, b_ = 0x53u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41a9a5: add eax, 0x53 */
	{ DWORD a_ = m->ecx, b_ = 0xffffff44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41a9a8: add ecx, 0xffffff44 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a9ae: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a9af: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41a9b5u; native_call(m, 0x41ef60u);	/* 41a9b0: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41a9b5: add esp, 8 */
	{ DWORD v_ = 0x3e000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a9b8: push 0x3e000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a9bd: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41a9c4u; native_call(m, m->esi);	/* 41a9c2: call esi */
	m->edx = M32((DWORD)(0x4dcc94u));	/* 41a9c4: mov edx, dword ptr [0x4dcc94] */
	m->eax = M32((DWORD)(0x4dcc98u));	/* 41a9ca: mov eax, dword ptr [0x4dcc98] */
	{ DWORD a_ = m->edx, b_ = 0x53u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 41a9cf: add edx, 0x53 */
	{ DWORD a_ = m->eax, b_ = 0xfffffff0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41a9d2: add eax, -0x10 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a9d5: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a9d6: push eax */
	m->esp -= 4; M32(m->esp) = 0x41a9dcu; native_call(m, 0x41ef60u);	/* 41a9d7: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41a9dc: add esp, 8 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a9df: push 0x3e800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a9e4: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41a9ebu; native_call(m, m->esi);	/* 41a9e9: call esi */
	m->ecx = M32((DWORD)(0x4dcc94u));	/* 41a9eb: mov ecx, dword ptr [0x4dcc94] */
	m->edx = M32((DWORD)(0x4dcc98u));	/* 41a9f1: mov edx, dword ptr [0x4dcc98] */
	{ DWORD a_ = m->ecx, b_ = 0x73u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41a9f7: add ecx, 0x73 */
	{ DWORD a_ = m->edx, b_ = 0xfffffff0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 41a9fa: add edx, -0x10 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a9fd: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a9fe: push edx */
	m->esp -= 4; M32(m->esp) = 0x41aa04u; native_call(m, 0x41ef60u);	/* 41a9ff: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41aa04: add esp, 8 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41aa07: push 0x3e800000 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 41aa0c: push ebx */
	m->esp -= 4; M32(m->esp) = 0x41aa0fu; native_call(m, m->esi);	/* 41aa0d: call esi */
	m->eax = M32((DWORD)(0x4dcc94u));	/* 41aa0f: mov eax, dword ptr [0x4dcc94] */
	m->ecx = M32((DWORD)(0x4dcc98u));	/* 41aa14: mov ecx, dword ptr [0x4dcc98] */
	{ DWORD a_ = m->eax, b_ = 0x73u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41aa1a: add eax, 0x73 */
	{ DWORD a_ = m->ecx, b_ = 0xffffff44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41aa1d: add ecx, 0xffffff44 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41aa23: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41aa24: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41aa2au; native_call(m, 0x41ef60u);	/* 41aa25: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41aa2a: add esp, 8 */
	{ DWORD v_ = 0x3e000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41aa2d: push 0x3e000000 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 41aa32: push ebx */
	m->esp -= 4; M32(m->esp) = 0x41aa35u; native_call(m, m->esi);	/* 41aa33: call esi */
	m->edx = M32((DWORD)(0x4dcc94u));	/* 41aa35: mov edx, dword ptr [0x4dcc94] */
	m->eax = M32((DWORD)(0x4dcc98u));	/* 41aa3b: mov eax, dword ptr [0x4dcc98] */
	{ DWORD a_ = m->edx, b_ = 0x103u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 41aa40: add edx, 0x103 */
	{ DWORD a_ = m->eax, b_ = 0xffffff44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41aa46: add eax, 0xffffff44 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41aa4b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41aa4c: push eax */
	m->esp -= 4; M32(m->esp) = 0x41aa52u; native_call(m, 0x41ef60u);	/* 41aa4d: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41aa52: add esp, 8 */
	{ DWORD v_ = 0x3e000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41aa55: push 0x3e000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41aa5a: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41aa61u; native_call(m, m->esi);	/* 41aa5f: call esi */
	m->ecx = M32((DWORD)(0x4dcc94u));	/* 41aa61: mov ecx, dword ptr [0x4dcc94] */
	m->edx = M32((DWORD)(0x4dcc98u));	/* 41aa67: mov edx, dword ptr [0x4dcc98] */
	{ DWORD a_ = m->ecx, b_ = 0x103u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41aa6d: add ecx, 0x103 */
	{ DWORD a_ = m->edx, b_ = 0xfffffff0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 41aa73: add edx, -0x10 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41aa76: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41aa77: push edx */
	m->esp -= 4; M32(m->esp) = 0x41aa7du; native_call(m, 0x41ef60u);	/* 41aa78: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41aa7d: add esp, 8 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41aa80: push 0x3e800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41aa85: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41aa8cu; native_call(m, m->esi);	/* 41aa8a: call esi */
	m->eax = M32((DWORD)(0x4dcc94u));	/* 41aa8c: mov eax, dword ptr [0x4dcc94] */
	m->ecx = M32((DWORD)(0x4dcc98u));	/* 41aa91: mov ecx, dword ptr [0x4dcc98] */
	{ DWORD a_ = m->eax, b_ = 0x123u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41aa97: add eax, 0x123 */
	{ DWORD a_ = m->ecx, b_ = 0xfffffff0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41aa9c: add ecx, -0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41aa9f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41aaa0: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41aaa6u; native_call(m, 0x41ef60u);	/* 41aaa1: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41aaa6: add esp, 8 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41aaa9: push 0x3e800000 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 41aaae: push ebx */
	m->esp -= 4; M32(m->esp) = 0x41aab1u; native_call(m, m->esi);	/* 41aaaf: call esi */
	m->edx = M32((DWORD)(0x4dcc94u));	/* 41aab1: mov edx, dword ptr [0x4dcc94] */
	{ DWORD a_ = m->edx, b_ = 0x123u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 41aab7: add edx, 0x123 */
	goto L_41abfc;	/* 41aabd: jmp 0x41abfc */
L_41aac2:
	{ DWORD v_ = 0x3f600000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41aac2: push 0x3f600000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41aac7: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41aacbu; native_call(m, m->esi);	/* 41aac9: call esi */
	m->ecx = M32((DWORD)(0x4dcc94u));	/* 41aacb: mov ecx, dword ptr [0x4dcc94] */
	m->eax = M32((DWORD)(0x4dcc98u));	/* 41aad1: mov eax, dword ptr [0x4dcc98] */
	m->edi = (DWORD)(m->ebx + m->ebx*2 + 0x0u);	/* 41aad6: lea edi, [ebx + ebx*2] */
	{ DWORD a_ = m->eax, b_ = 0xffffff44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41aad9: add eax, 0xffffff44 */
	{ DWORD a_ = m->edi, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 41aade: shl edi, 4 */
	m->edx = (DWORD)(m->edi + m->ecx*1 + 0x5au);	/* 41aae1: lea edx, [edi + ecx + 0x5a] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41aae5: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41aae6: push eax */
	m->esp -= 4; M32(m->esp) = 0x41aaecu; native_call(m, 0x41ef60u);	/* 41aae7: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41aaec: add esp, 8 */
	{ DWORD v_ = 0x3f600000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41aaef: push 0x3f600000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41aaf4: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41aafbu; native_call(m, m->esi);	/* 41aaf9: call esi */
	m->ecx = M32((DWORD)(0x4dcc94u));	/* 41aafb: mov ecx, dword ptr [0x4dcc94] */
	m->eax = M32((DWORD)(0x4dcc98u));	/* 41ab01: mov eax, dword ptr [0x4dcc98] */
	{ DWORD a_ = m->eax, b_ = 0xfffffff0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41ab06: add eax, -0x10 */
	m->edx = (DWORD)(m->edi + m->ecx*1 + 0x5au);	/* 41ab09: lea edx, [edi + ecx + 0x5a] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41ab0d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41ab0e: push eax */
	m->esp -= 4; M32(m->esp) = 0x41ab14u; native_call(m, 0x41ef60u);	/* 41ab0f: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41ab14: add esp, 8 */
	{ DWORD v_ = 0x3f700000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ab17: push 0x3f700000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ab1c: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41ab23u; native_call(m, m->esi);	/* 41ab21: call esi */
	m->ecx = M32((DWORD)(0x4dcc94u));	/* 41ab23: mov ecx, dword ptr [0x4dcc94] */
	m->eax = M32((DWORD)(0x4dcc98u));	/* 41ab29: mov eax, dword ptr [0x4dcc98] */
	{ DWORD a_ = m->eax, b_ = 0xfffffff0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41ab2e: add eax, -0x10 */
	m->edx = (DWORD)(m->edi + m->ecx*1 + 0x6au);	/* 41ab31: lea edx, [edi + ecx + 0x6a] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41ab35: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41ab36: push eax */
	m->esp -= 4; M32(m->esp) = 0x41ab3cu; native_call(m, 0x41ef60u);	/* 41ab37: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41ab3c: add esp, 8 */
	{ DWORD v_ = 0x3f700000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ab3f: push 0x3f700000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ab44: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41ab48u; native_call(m, m->esi);	/* 41ab46: call esi */
	m->ecx = M32((DWORD)(0x4dcc94u));	/* 41ab48: mov ecx, dword ptr [0x4dcc94] */
	m->eax = M32((DWORD)(0x4dcc98u));	/* 41ab4e: mov eax, dword ptr [0x4dcc98] */
	{ DWORD a_ = m->eax, b_ = 0xffffff44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41ab53: add eax, 0xffffff44 */
	m->edx = (DWORD)(m->edi + m->ecx*1 + 0x6au);	/* 41ab58: lea edx, [edi + ecx + 0x6a] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41ab5c: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41ab5d: push eax */
	m->esp -= 4; M32(m->esp) = 0x41ab63u; native_call(m, 0x41ef60u);	/* 41ab5e: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41ab63: add esp, 8 */
	{ DWORD v_ = 0x3f600000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ab66: push 0x3f600000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ab6b: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41ab6fu; native_call(m, m->esi);	/* 41ab6d: call esi */
	m->ecx = M32((DWORD)(0x4dcc94u));	/* 41ab6f: mov ecx, dword ptr [0x4dcc94] */
	m->eax = M32((DWORD)(0x4dcc98u));	/* 41ab75: mov eax, dword ptr [0x4dcc98] */
	{ DWORD a_ = m->eax, b_ = 0xffffff44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41ab7a: add eax, 0xffffff44 */
	m->edx = (DWORD)(m->edi + m->ecx*1 + 0x10au);	/* 41ab7f: lea edx, [edi + ecx + 0x10a] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41ab86: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41ab87: push eax */
	m->esp -= 4; M32(m->esp) = 0x41ab8du; native_call(m, 0x41ef60u);	/* 41ab88: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41ab8d: add esp, 8 */
	{ DWORD v_ = 0x3f600000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ab90: push 0x3f600000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ab95: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41ab9cu; native_call(m, m->esi);	/* 41ab9a: call esi */
	m->ecx = M32((DWORD)(0x4dcc94u));	/* 41ab9c: mov ecx, dword ptr [0x4dcc94] */
	m->eax = M32((DWORD)(0x4dcc98u));	/* 41aba2: mov eax, dword ptr [0x4dcc98] */
	{ DWORD a_ = m->eax, b_ = 0xfffffff0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41aba7: add eax, -0x10 */
	m->edx = (DWORD)(m->edi + m->ecx*1 + 0x10au);	/* 41abaa: lea edx, [edi + ecx + 0x10a] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41abb1: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41abb2: push eax */
	m->esp -= 4; M32(m->esp) = 0x41abb8u; native_call(m, 0x41ef60u);	/* 41abb3: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41abb8: add esp, 8 */
	{ DWORD v_ = 0x3f700000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41abbb: push 0x3f700000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41abc0: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41abc7u; native_call(m, m->esi);	/* 41abc5: call esi */
	m->ecx = M32((DWORD)(0x4dcc94u));	/* 41abc7: mov ecx, dword ptr [0x4dcc94] */
	m->eax = M32((DWORD)(0x4dcc98u));	/* 41abcd: mov eax, dword ptr [0x4dcc98] */
	{ DWORD a_ = m->eax, b_ = 0xfffffff0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41abd2: add eax, -0x10 */
	m->edx = (DWORD)(m->edi + m->ecx*1 + 0x11au);	/* 41abd5: lea edx, [edi + ecx + 0x11a] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41abdc: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41abdd: push eax */
	m->esp -= 4; M32(m->esp) = 0x41abe3u; native_call(m, 0x41ef60u);	/* 41abde: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41abe3: add esp, 8 */
	{ DWORD v_ = 0x3f700000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41abe6: push 0x3f700000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41abeb: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41abefu; native_call(m, m->esi);	/* 41abed: call esi */
	m->ecx = M32((DWORD)(0x4dcc94u));	/* 41abef: mov ecx, dword ptr [0x4dcc94] */
	m->edx = (DWORD)(m->edi + m->ecx*1 + 0x11au);	/* 41abf5: lea edx, [edi + ecx + 0x11a] */
L_41abfc:
	m->eax = M32((DWORD)(0x4dcc98u));	/* 41abfc: mov eax, dword ptr [0x4dcc98] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41ac01: push edx */
	{ DWORD a_ = m->eax, b_ = 0xffffff44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41ac02: add eax, 0xffffff44 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41ac07: push eax */
	m->esp -= 4; M32(m->esp) = 0x41ac0du; native_call(m, 0x41ef60u);	/* 41ac08: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41ac0d: add esp, 8 */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 41ac10: inc ebx */
	{ DWORD a_ = m->ebx, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41ac11: cmp ebx, 3 */
	if (m->sf != m->of) goto L_41a98a;	/* 41ac14: jl 0x41a98a */
	m->esp -= 4; M32(m->esp) = 0x41ac20u; native_call(m, M32(0x4a9220u));	/* 41ac1a: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ac20: push 7 */
	m->esp -= 4; M32(m->esp) = 0x41ac28u; native_call(m, M32(0x4a921cu));	/* 41ac22: call dword ptr [0x4a921c] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 41ac28: xor ebx, ebx */
	M32((DWORD)(m->esp + 0x18u)) = m->ebx;	/* 41ac2a: mov dword ptr [esp + 0x18], ebx */
L_41ac2e:
	m->eax = m->ebx;	/* 41ac2e: mov eax, ebx */
	{ DWORD a_ = m->eax, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41ac30: sub eax, 0 */
	if (m->zf) goto L_41ae73;	/* 41ac33: je 0x41ae73 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 41ac39: dec eax */
	if (m->zf) goto L_41ac60;	/* 41ac3a: je 0x41ac60 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 41ac3c: dec eax */
	if (!m->zf) goto L_41af1c;	/* 41ac3d: jne 0x41af1c */
	m->eax = M32((DWORD)(0x4dc4b0u));	/* 41ac43: mov eax, dword ptr [0x4dc4b0] */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41ac48: lea eax, [eax + eax*2] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41ac4b: shl eax, 3 */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4c0u));	/* 41ac4e: mov ecx, dword ptr [eax + 0x4dc4c0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4dc4ccu)));	/* 41ac54: fld dword ptr [eax + 0x4dc4cc] */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 41ac5a: mov dword ptr [esp + 0x14], ecx */
	goto L_41ac7b;	/* 41ac5e: jmp 0x41ac7b */
L_41ac60:
	m->eax = M32((DWORD)(0x4dc4b0u));	/* 41ac60: mov eax, dword ptr [0x4dc4b0] */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41ac65: lea eax, [eax + eax*2] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41ac68: shl eax, 3 */
	m->edx = M32((DWORD)(m->eax + 0x4dc4bcu));	/* 41ac6b: mov edx, dword ptr [eax + 0x4dc4bc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4dc4c8u)));	/* 41ac71: fld dword ptr [eax + 0x4dc4c8] */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 41ac77: mov dword ptr [esp + 0x14], edx */
L_41ac7b:
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 41ac7b: fadd dword ptr [0x4a9424] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ac81: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ac86: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ac8b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ac90: push 0x3f800000 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 41ac95: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 41ac9b: fstp dword ptr [esp + 0x20] */
	m->esp -= 4; M32(m->esp) = 0x41aca1u; native_call(m, m->ebp);	/* 41ac9f: call ebp */
L_41aca1:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41aca1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41aca6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41acab: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41acb0: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41acb7u; native_call(m, m->ebp);	/* 41acb5: call ebp */
	{ DWORD v_ = 0x3f700000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41acb7: push 0x3f700000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41acbc: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41acc0u; native_call(m, m->esi);	/* 41acbe: call esi */
	m->edx = M32((DWORD)(0x4dcc94u));	/* 41acc0: mov edx, dword ptr [0x4dcc94] */
	m->ecx = M32((DWORD)(0x4dcc98u));	/* 41acc6: mov ecx, dword ptr [0x4dcc98] */
	m->edi = (DWORD)(m->ebx + m->ebx*2 + 0x0u);	/* 41accc: lea edi, [ebx + ebx*2] */
	{ DWORD a_ = m->ecx, b_ = 0xffffff46u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41accf: add ecx, 0xffffff46 */
	{ DWORD a_ = m->edi, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 41acd5: shl edi, 4 */
	m->eax = (DWORD)(m->edi + m->edx*1 + 0x5au);	/* 41acd8: lea eax, [edi + edx + 0x5a] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41acdc: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41acdd: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41ace3u; native_call(m, 0x41ef60u);	/* 41acde: call 0x41ef60 */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 41ace3: mov edx, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41ace7: add esp, 8 */
	{ DWORD v_ = 0x3f700000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41acea: push 0x3f700000 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41acef: push edx */
	m->esp -= 4; M32(m->esp) = 0x41acf2u; native_call(m, m->esi);	/* 41acf0: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 41acf2: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a948cu));	/* 41acf6: fmul dword ptr [0x4a948c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 41acfc: call 0x49ec14 */
	m->edx = M32((DWORD)(0x4dcc98u));	/* 41ad01: mov edx, dword ptr [0x4dcc98] */
	m->ebx = m->eax;	/* 41ad07: mov ebx, eax */
	m->eax = M32((DWORD)(0x4dcc94u));	/* 41ad09: mov eax, dword ptr [0x4dcc94] */
	{ DWORD a_ = m->edx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 41ad0e: sub edx, ebx */
	{ DWORD a_ = m->edx, b_ = 0xbau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 41ad10: sub edx, 0xba */
	m->ecx = (DWORD)(m->edi + m->eax*1 + 0x5au);	/* 41ad16: lea ecx, [edi + eax + 0x5a] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41ad1a: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41ad1b: push edx */
	m->esp -= 4; M32(m->esp) = 0x41ad21u; native_call(m, 0x41ef60u);	/* 41ad1c: call 0x41ef60 */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 41ad21: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41ad25: add esp, 8 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ad28: push 0x3f800000 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41ad2d: push eax */
	m->esp -= 4; M32(m->esp) = 0x41ad30u; native_call(m, m->esi);	/* 41ad2e: call esi */
	m->ecx = M32((DWORD)(0x4dcc94u));	/* 41ad30: mov ecx, dword ptr [0x4dcc94] */
	m->eax = M32((DWORD)(0x4dcc98u));	/* 41ad36: mov eax, dword ptr [0x4dcc98] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41ad3b: sub eax, ebx */
	m->edx = (DWORD)(m->edi + m->ecx*1 + 0x6au);	/* 41ad3d: lea edx, [edi + ecx + 0x6a] */
	{ DWORD a_ = m->eax, b_ = 0xbau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41ad41: sub eax, 0xba */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41ad46: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41ad47: push eax */
	m->esp -= 4; M32(m->esp) = 0x41ad4du; native_call(m, 0x41ef60u);	/* 41ad48: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41ad4d: add esp, 8 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ad50: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ad55: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41ad59u; native_call(m, m->esi);	/* 41ad57: call esi */
	m->ecx = M32((DWORD)(0x4dcc94u));	/* 41ad59: mov ecx, dword ptr [0x4dcc94] */
	m->eax = M32((DWORD)(0x4dcc98u));	/* 41ad5f: mov eax, dword ptr [0x4dcc98] */
	{ DWORD a_ = m->eax, b_ = 0xffffff46u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41ad64: add eax, 0xffffff46 */
	m->edx = (DWORD)(m->edi + m->ecx*1 + 0x6au);	/* 41ad69: lea edx, [edi + ecx + 0x6a] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41ad6d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41ad6e: push eax */
	m->esp -= 4; M32(m->esp) = 0x41ad74u; native_call(m, 0x41ef60u);	/* 41ad6f: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41ad74: add esp, 8 */
	{ DWORD v_ = 0x3f700000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ad77: push 0x3f700000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ad7c: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41ad80u; native_call(m, m->esi);	/* 41ad7e: call esi */
	m->ecx = M32((DWORD)(0x4dcc94u));	/* 41ad80: mov ecx, dword ptr [0x4dcc94] */
	m->eax = M32((DWORD)(0x4dcc98u));	/* 41ad86: mov eax, dword ptr [0x4dcc98] */
	{ DWORD a_ = m->eax, b_ = 0xffffff46u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41ad8b: add eax, 0xffffff46 */
	m->edx = (DWORD)(m->edi + m->ecx*1 + 0x10au);	/* 41ad90: lea edx, [edi + ecx + 0x10a] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41ad97: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41ad98: push eax */
	m->esp -= 4; M32(m->esp) = 0x41ad9eu; native_call(m, 0x41ef60u);	/* 41ad99: call 0x41ef60 */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 41ad9e: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41ada2: add esp, 8 */
	{ DWORD v_ = 0x3f700000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ada5: push 0x3f700000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41adaa: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41adadu; native_call(m, m->esi);	/* 41adab: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 41adad: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a948cu));	/* 41adb1: fmul dword ptr [0x4a948c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 41adb7: call 0x49ec14 */
	m->edx = M32((DWORD)(0x4dcc94u));	/* 41adbc: mov edx, dword ptr [0x4dcc94] */
	m->ebx = m->eax;	/* 41adc2: mov ebx, eax */
	m->eax = (DWORD)(m->edi + m->edx*1 + 0x10au);	/* 41adc4: lea eax, [edi + edx + 0x10a] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41adcb: push eax */
	m->ecx = M32((DWORD)(0x4dcc98u));	/* 41adcc: mov ecx, dword ptr [0x4dcc98] */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41add2: sub ecx, ebx */
	{ DWORD a_ = m->ecx, b_ = 0xbau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41add4: sub ecx, 0xba */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41adda: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41ade0u; native_call(m, 0x41ef60u);	/* 41addb: call 0x41ef60 */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 41ade0: mov edx, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41ade4: add esp, 8 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ade7: push 0x3f800000 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41adec: push edx */
	m->esp -= 4; M32(m->esp) = 0x41adefu; native_call(m, m->esi);	/* 41aded: call esi */
	m->eax = M32((DWORD)(0x4dcc94u));	/* 41adef: mov eax, dword ptr [0x4dcc94] */
	m->edx = M32((DWORD)(0x4dcc98u));	/* 41adf4: mov edx, dword ptr [0x4dcc98] */
	{ DWORD a_ = m->edx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 41adfa: sub edx, ebx */
	m->ecx = (DWORD)(m->edi + m->eax*1 + 0x11au);	/* 41adfc: lea ecx, [edi + eax + 0x11a] */
	{ DWORD a_ = m->edx, b_ = 0xbau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 41ae03: sub edx, 0xba */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41ae09: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41ae0a: push edx */
	m->esp -= 4; M32(m->esp) = 0x41ae10u; native_call(m, 0x41ef60u);	/* 41ae0b: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41ae10: add esp, 8 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ae13: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ae18: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41ae1cu; native_call(m, m->esi);	/* 41ae1a: call esi */
	m->eax = M32((DWORD)(0x4dcc94u));	/* 41ae1c: mov eax, dword ptr [0x4dcc94] */
	m->edx = M32((DWORD)(0x4dcc98u));	/* 41ae21: mov edx, dword ptr [0x4dcc98] */
	{ DWORD a_ = m->edx, b_ = 0xffffff46u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 41ae27: add edx, 0xffffff46 */
	m->ecx = (DWORD)(m->edi + m->eax*1 + 0x11au);	/* 41ae2d: lea ecx, [edi + eax + 0x11a] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41ae34: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41ae35: push edx */
	m->esp -= 4; M32(m->esp) = 0x41ae3bu; native_call(m, 0x41ef60u);	/* 41ae36: call 0x41ef60 */
	m->ebx = M32((DWORD)(m->esp + 0x20u));	/* 41ae3b: mov ebx, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41ae3f: add esp, 8 */
L_41ae42:
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 41ae42: inc ebx */
	{ DWORD a_ = m->ebx, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41ae43: cmp ebx, 3 */
	M32((DWORD)(m->esp + 0x18u)) = m->ebx;	/* 41ae46: mov dword ptr [esp + 0x18], ebx */
	if (m->sf != m->of) goto L_41ac2e;	/* 41ae4a: jl 0x41ac2e */
	m->esp -= 4; M32(m->esp) = 0x41ae56u; native_call(m, M32(0x4a9220u));	/* 41ae50: call dword ptr [0x4a9220] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 41ae56: xor edi, edi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 41ae58: xor esi, esi */
L_41ae5a:
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 41ae5a: mov ecx, dword ptr [esp + 0x1c] */
	m->eax = (DWORD)(m->edi + 0x3u);	/* 41ae5e: lea eax, [edi + 3] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41ae61: cmp ecx, eax */
	if (!m->zf) goto L_41b0c0;	/* 41ae63: jne 0x41b0c0 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 41ae69: push 0x3f4ccccd */
	goto L_41b0c5;	/* 41ae6e: jmp 0x41b0c5 */
L_41ae73:
	m->eax = M32((DWORD)(0x4dc4b0u));	/* 41ae73: mov eax, dword ptr [0x4dc4b0] */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41ae78: lea eax, [eax + eax*2] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41ae7b: shl eax, 3 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4dc4b8u)));	/* 41ae7e: fld dword ptr [eax + 0x4dc4b8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 41ae84: fcom dword ptr [0x4a93e8] */
	m->eax = M32((DWORD)(m->eax + 0x4dc4c4u));	/* 41ae8a: mov eax, dword ptr [eax + 0x4dc4c4] */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 41ae90: mov dword ptr [esp + 0x10], eax */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41ae94: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41ae96: test ah, 1 */
	if (!m->zf) goto L_41aeb0;	/* 41ae99: jne 0x41aeb0 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a945cu));	/* 41ae9b: fcom dword ptr [0x4a945c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41aea1: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41aea3: test ah, 1 */
	if (m->zf) goto L_41aeb0;	/* 41aea6: je 0x41aeb0 */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a945cu));	/* 41aea8: fadd dword ptr [0x4a945c] */
	goto L_41aeb6;	/* 41aeae: jmp 0x41aeb6 */
L_41aeb0:
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a945cu));	/* 41aeb0: fsub dword ptr [0x4a945c] */
L_41aeb6:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 41aeb6: fld dword ptr [esp + 0x10] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 41aeba: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41aec0: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41aec2: test ah, 1 */
	if (!m->zf) goto L_41aee4;	/* 41aec5: jne 0x41aee4 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 41aec7: fld dword ptr [esp + 0x10] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a945cu)); FPOP();	/* 41aecb: fcomp dword ptr [0x4a945c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41aed1: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41aed3: test ah, 1 */
	if (m->zf) goto L_41aee4;	/* 41aed6: je 0x41aee4 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 41aed8: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a945cu));	/* 41aedc: fadd dword ptr [0x4a945c] */
	goto L_41aeee;	/* 41aee2: jmp 0x41aeee */
L_41aee4:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 41aee4: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a945cu));	/* 41aee8: fsub dword ptr [0x4a945c] */
L_41aeee:
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 41aeee: fxch st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9488u));	/* 41aef0: fmul dword ptr [0x4a9488] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41aef6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41aefb: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41af00: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41af05: push 0x3f800000 */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 41af0a: fstp dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9488u));	/* 41af0e: fmul dword ptr [0x4a9488] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 41af14: fstp dword ptr [esp + 0x20] */
	m->esp -= 4; M32(m->esp) = 0x41af1au; native_call(m, m->ebp);	/* 41af18: call ebp */
	goto L_41af24;	/* 41af1a: jmp 0x41af24 */
L_41af1c:
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41af1c: test ebx, ebx */
	if (!m->zf) goto L_41aca1;	/* 41af1e: jne 0x41aca1 */
L_41af24:
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41af24: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41af29: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41af2e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41af33: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41af3au; native_call(m, m->ebp);	/* 41af38: call ebp */
	{ DWORD v_ = 0x3f500000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41af3a: push 0x3f500000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41af3f: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41af43u; native_call(m, m->esi);	/* 41af41: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 41af43: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9484u));	/* 41af47: fmul dword ptr [0x4a9484] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 41af4d: call 0x49ec14 */
	m->edx = M32((DWORD)(0x4dcc98u));	/* 41af52: mov edx, dword ptr [0x4dcc98] */
	m->ecx = M32((DWORD)(0x4dcc94u));	/* 41af58: mov ecx, dword ptr [0x4dcc94] */
	m->edi = m->eax;	/* 41af5e: mov edi, eax */
	{ DWORD a_ = m->ecx, b_ = 0x5au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41af60: add ecx, 0x5a */
	{ DWORD a_ = m->edx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 41af63: sub edx, edi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41af65: push ecx */
	{ DWORD a_ = m->edx, b_ = 0xbdu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 41af66: sub edx, 0xbd */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41af6c: push edx */
	m->esp -= 4; M32(m->esp) = 0x41af72u; native_call(m, 0x41ef60u);	/* 41af6d: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41af72: add esp, 8 */
	{ DWORD v_ = 0x3f500000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41af75: push 0x3f500000 */
	{ DWORD v_ = 0x3d000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41af7a: push 0x3d000000 */
	m->esp -= 4; M32(m->esp) = 0x41af81u; native_call(m, m->esi);	/* 41af7f: call esi */
	m->ecx = M32((DWORD)(0x4dcc98u));	/* 41af81: mov ecx, dword ptr [0x4dcc98] */
	m->eax = M32((DWORD)(0x4dcc94u));	/* 41af87: mov eax, dword ptr [0x4dcc94] */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41af8c: sub ecx, edi */
	{ DWORD a_ = m->eax, b_ = 0x5au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41af8e: add eax, 0x5a */
	{ DWORD a_ = m->ecx, b_ = 0xb5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41af91: sub ecx, 0xb5 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41af97: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41af98: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41af9eu; native_call(m, 0x41ef60u);	/* 41af99: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41af9e: add esp, 8 */
	{ DWORD v_ = 0x3f600000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41afa1: push 0x3f600000 */
	{ DWORD v_ = 0x3d000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41afa6: push 0x3d000000 */
	m->esp -= 4; M32(m->esp) = 0x41afadu; native_call(m, m->esi);	/* 41afab: call esi */
	m->eax = M32((DWORD)(0x4dcc98u));	/* 41afad: mov eax, dword ptr [0x4dcc98] */
	m->edx = M32((DWORD)(0x4dcc94u));	/* 41afb2: mov edx, dword ptr [0x4dcc94] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41afb8: sub eax, edi */
	{ DWORD a_ = m->edx, b_ = 0x6au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 41afba: add edx, 0x6a */
	{ DWORD a_ = m->eax, b_ = 0xb5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41afbd: sub eax, 0xb5 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41afc2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41afc3: push eax */
	m->esp -= 4; M32(m->esp) = 0x41afc9u; native_call(m, 0x41ef60u);	/* 41afc4: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41afc9: add esp, 8 */
	{ DWORD v_ = 0x3f600000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41afcc: push 0x3f600000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41afd1: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41afd5u; native_call(m, m->esi);	/* 41afd3: call esi */
	m->edx = M32((DWORD)(0x4dcc98u));	/* 41afd5: mov edx, dword ptr [0x4dcc98] */
	m->ecx = M32((DWORD)(0x4dcc94u));	/* 41afdb: mov ecx, dword ptr [0x4dcc94] */
	{ DWORD a_ = m->edx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 41afe1: sub edx, edi */
	{ DWORD a_ = m->ecx, b_ = 0x6au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41afe3: add ecx, 0x6a */
	{ DWORD a_ = m->edx, b_ = 0xbdu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 41afe6: sub edx, 0xbd */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41afec: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41afed: push edx */
	m->esp -= 4; M32(m->esp) = 0x41aff3u; native_call(m, 0x41ef60u);	/* 41afee: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41aff3: add esp, 8 */
	{ DWORD v_ = 0x3f500000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41aff6: push 0x3f500000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41affb: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41afffu; native_call(m, m->esi);	/* 41affd: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 41afff: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9484u));	/* 41b003: fmul dword ptr [0x4a9484] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 41b009: call 0x49ec14 */
	m->ecx = M32((DWORD)(0x4dcc98u));	/* 41b00e: mov ecx, dword ptr [0x4dcc98] */
	m->edi = m->eax;	/* 41b014: mov edi, eax */
	m->eax = M32((DWORD)(0x4dcc94u));	/* 41b016: mov eax, dword ptr [0x4dcc94] */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41b01b: sub ecx, edi */
	{ DWORD a_ = m->eax, b_ = 0x10au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41b01d: add eax, 0x10a */
	{ DWORD a_ = m->ecx, b_ = 0xbdu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41b022: sub ecx, 0xbd */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41b028: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b029: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41b02fu; native_call(m, 0x41ef60u);	/* 41b02a: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41b02f: add esp, 8 */
	{ DWORD v_ = 0x3f500000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b032: push 0x3f500000 */
	{ DWORD v_ = 0x3d000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b037: push 0x3d000000 */
	m->esp -= 4; M32(m->esp) = 0x41b03eu; native_call(m, m->esi);	/* 41b03c: call esi */
	m->edx = M32((DWORD)(0x4dcc94u));	/* 41b03e: mov edx, dword ptr [0x4dcc94] */
	m->eax = M32((DWORD)(0x4dcc98u));	/* 41b044: mov eax, dword ptr [0x4dcc98] */
	{ DWORD a_ = m->edx, b_ = 0x10au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 41b049: add edx, 0x10a */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41b04f: sub eax, edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b051: push edx */
	{ DWORD a_ = m->eax, b_ = 0xb5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41b052: sub eax, 0xb5 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41b057: push eax */
	m->esp -= 4; M32(m->esp) = 0x41b05du; native_call(m, 0x41ef60u);	/* 41b058: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41b05d: add esp, 8 */
	{ DWORD v_ = 0x3f600000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b060: push 0x3f600000 */
	{ DWORD v_ = 0x3d000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b065: push 0x3d000000 */
	m->esp -= 4; M32(m->esp) = 0x41b06cu; native_call(m, m->esi);	/* 41b06a: call esi */
	m->edx = M32((DWORD)(0x4dcc98u));	/* 41b06c: mov edx, dword ptr [0x4dcc98] */
	m->ecx = M32((DWORD)(0x4dcc94u));	/* 41b072: mov ecx, dword ptr [0x4dcc94] */
	{ DWORD a_ = m->edx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 41b078: sub edx, edi */
	{ DWORD a_ = m->ecx, b_ = 0x11au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41b07a: add ecx, 0x11a */
	{ DWORD a_ = m->edx, b_ = 0xb5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 41b080: sub edx, 0xb5 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b086: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b087: push edx */
	m->esp -= 4; M32(m->esp) = 0x41b08du; native_call(m, 0x41ef60u);	/* 41b088: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41b08d: add esp, 8 */
	{ DWORD v_ = 0x3f600000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b090: push 0x3f600000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b095: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41b099u; native_call(m, m->esi);	/* 41b097: call esi */
	m->ecx = M32((DWORD)(0x4dcc98u));	/* 41b099: mov ecx, dword ptr [0x4dcc98] */
	m->eax = M32((DWORD)(0x4dcc94u));	/* 41b09f: mov eax, dword ptr [0x4dcc94] */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41b0a4: sub ecx, edi */
	{ DWORD a_ = m->eax, b_ = 0x11au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41b0a6: add eax, 0x11a */
	{ DWORD a_ = m->ecx, b_ = 0xbdu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41b0ab: sub ecx, 0xbd */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41b0b1: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b0b2: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41b0b8u; native_call(m, 0x41ef60u);	/* 41b0b3: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41b0b8: add esp, 8 */
	goto L_41ae42;	/* 41b0bb: jmp 0x41ae42 */
L_41b0c0:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 41b0c0: push 0x3ecccccd */
L_41b0c5:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b0c5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b0ca: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b0cf: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41b0d6u; native_call(m, m->ebp);	/* 41b0d4: call ebp */
	m->eax = M32((DWORD)(0x4dcc90u));	/* 41b0d6: mov eax, dword ptr [0x4dcc90] */
	m->ecx = M32((DWORD)(0x4dcc9cu));	/* 41b0db: mov ecx, dword ptr [0x4dcc9c] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b0e1: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b0e3: push ecx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x70u);	/* 41b0e4: lea edx, [esi + eax + 0x70] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffe0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41b0e8: add ecx, -0x20 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b0eb: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x10u);	/* 41b0ec: lea eax, [esi + eax + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b0f0: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41b0f1: push eax */
	m->esp -= 4; M32(m->esp) = 0x41b0f7u; native_call(m, 0x4282f0u);	/* 41b0f2: call 0x4282f0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41b0f7: add esp, 0x14 */
	{ DWORD a_ = m->esi, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 41b0fa: add esi, 0x64 */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 41b0fd: inc edi */
	{ DWORD a_ = m->esi, b_ = 0xc8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41b0fe: cmp esi, 0xc8 */
	if (m->sf != m->of) goto L_41ae5a;	/* 41b104: jl 0x41ae5a */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 41b10a: xor ebx, ebx */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 41b10c: xor edi, edi */
	m->esi = 0x7517a4u;	/* 41b10e: mov esi, 0x7517a4 */
L_41b113:
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 41b113: mov eax, dword ptr [esp + 0x1c] */
	m->ecx = (DWORD)(m->ebx + 0x3u);	/* 41b117: lea ecx, [ebx + 3] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41b11a: cmp eax, ecx */
	if (!m->zf) goto L_41b13b;	/* 41b11c: jne 0x41b13b */
	m->edx = M32((DWORD)(0x4dbc64u));	/* 41b11e: mov edx, dword ptr [0x4dbc64] */
	m->eax = M32((DWORD)(0x4dbc60u));	/* 41b124: mov eax, dword ptr [0x4dbc60] */
	m->ecx = M32((DWORD)(0x4dbc5cu));	/* 41b129: mov ecx, dword ptr [0x4dbc5c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b12f: push edx */
	m->edx = M32((DWORD)(0x4dbc58u));	/* 41b130: mov edx, dword ptr [0x4dbc58] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41b136: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b137: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b138: push edx */
	goto L_41b155;	/* 41b139: jmp 0x41b155 */
L_41b13b:
	m->eax = M32((DWORD)(0x4dc1dcu));	/* 41b13b: mov eax, dword ptr [0x4dc1dc] */
	m->ecx = M32((DWORD)(0x4dc1d8u));	/* 41b140: mov ecx, dword ptr [0x4dc1d8] */
	m->edx = M32((DWORD)(0x4dc1d4u));	/* 41b146: mov edx, dword ptr [0x4dc1d4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41b14c: push eax */
	m->eax = M32((DWORD)(0x4dc1d0u));	/* 41b14d: mov eax, dword ptr [0x4dc1d0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b152: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b153: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41b154: push eax */
L_41b155:
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b155: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41b15fu; native_call(m, 0x41f0e0u);	/* 41b15a: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4dcc90u));	/* 41b15f: mov eax, dword ptr [0x4dcc90] */
	m->edx = M32((DWORD)(0x4dcc9cu));	/* 41b164: mov edx, dword ptr [0x4dcc9c] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41b16a: add esp, 0x14 */
	{ DWORD a_ = m->edx, b_ = 0xffffffe8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 41b16d: add edx, -0x18 */
	m->ecx = (DWORD)(m->edi + m->eax*1 + 0x70u);	/* 41b170: lea ecx, [edi + eax + 0x70] */
	m->eax = (DWORD)(m->edi + m->eax*1 + 0x10u);	/* 41b174: lea eax, [edi + eax + 0x10] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41b178: push esi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b179: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b17a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41b17b: push eax */
	m->esp -= 4; M32(m->esp) = 0x41b181u; native_call(m, 0x4029d0u);	/* 41b17c: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41b181: add esp, 0x10 */
	{ DWORD a_ = m->esi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 41b184: add esi, 0x80 */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 41b18a: inc ebx */
	{ DWORD a_ = m->edi, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41b18b: add edi, 0x64 */
	{ DWORD a_ = m->esi, b_ = 0x7518a4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41b18e: cmp esi, 0x7518a4 */
	if (m->sf != m->of) goto L_41b113;	/* 41b194: jl 0x41b113 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b19a: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x41b1a5u; native_call(m, M32(0x4a9224u));	/* 41b19f: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 41b1a5: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 41b1aa: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41b1ac: and ecx, 0x800001ff */
	if (!m->sf) goto L_41b1bc;	/* 41b1b2: jns 0x41b1bc */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 41b1b4: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41b1b5: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 41b1bb: inc ecx */
L_41b1bc:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 41b1bc: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 41b1bd: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b1c3: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41b1c4: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 41b1c6: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41b1cc: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 41b1cf: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x41b1d8u; native_call(m, 0x4566c0u);	/* 41b1d3: call 0x4566c0 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b1d8: push 0x3f333333 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b1dd: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b1e2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b1e7: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41b1eeu; native_call(m, m->ebp);	/* 41b1ec: call ebp */
	m->eax = M32((DWORD)(0x4dcc9cu));	/* 41b1ee: mov eax, dword ptr [0x4dcc9c] */
	m->ecx = M32((DWORD)(0x4dcc98u));	/* 41b1f3: mov ecx, dword ptr [0x4dcc98] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b1f9: push 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41b1fb: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b1fc: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xffffffe0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41b1fd: add eax, -0x20 */
	{ DWORD a_ = m->ecx, b_ = 0xffffff60u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41b200: add ecx, 0xffffff60 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41b206: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b207: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41b20du; native_call(m, 0x4282f0u);	/* 41b208: call 0x4282f0 */
	m->eax = M32((DWORD)(0x4dbc64u));	/* 41b20d: mov eax, dword ptr [0x4dbc64] */
	m->ecx = M32((DWORD)(0x4dbc60u));	/* 41b212: mov ecx, dword ptr [0x4dbc60] */
	m->edx = M32((DWORD)(0x4dbc5cu));	/* 41b218: mov edx, dword ptr [0x4dbc5c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41b21e: push eax */
	m->eax = M32((DWORD)(0x4dbc58u));	/* 41b21f: mov eax, dword ptr [0x4dbc58] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b224: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b225: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41b226: push eax */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b227: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41b231u; native_call(m, 0x41f0e0u);	/* 41b22c: call 0x41f0e0 */
	m->ecx = 0xcu;	/* 41b231: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41b236: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x4cu);	/* 41b238: lea edi, [esp + 0x4c] */
	m->edx = (DWORD)(m->esp + 0x4cu);	/* 41b23c: lea edx, [esp + 0x4c] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 41b240: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 41b242: stosw word ptr es:[edi], ax */
	m->edi = 0x756da4u;	/* 41b244: mov edi, 0x756da4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41b249: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41b24c: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41b24e: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41b250: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41b252: sub edi, ecx */
	m->eax = m->ecx;	/* 41b254: mov eax, ecx */
	m->esi = m->edi;	/* 41b256: mov esi, edi */
	m->edi = m->edx;	/* 41b258: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x4cu);	/* 41b25a: lea edx, [esp + 0x4c] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41b25e: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41b261: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 41b263: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41b265: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41b267: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41b26a: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b035cu;	/* 41b26c: mov edi, 0x4b035c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41b271: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41b274: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41b276: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41b278: sub edi, ecx */
	m->esi = m->edi;	/* 41b27a: mov esi, edi */
	m->ebx = m->ecx;	/* 41b27c: mov ebx, ecx */
	m->edi = m->edx;	/* 41b27e: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41b280: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41b283: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 41b285: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41b287: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41b288: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41b28b: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebx;	/* 41b28d: mov ecx, ebx */
	m->edx = (DWORD)(m->esp + 0x4cu);	/* 41b28f: lea edx, [esp + 0x4c] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41b293: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41b296: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = M32((DWORD)(0x4dceacu));	/* 41b298: mov edi, dword ptr [0x4dceac] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41b29e: or ecx, 0xffffffff */
	{ DWORD a_ = m->edi, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 41b2a1: shl edi, 7 */
	{ DWORD a_ = m->edi, b_ = 0x751924u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41b2a4: add edi, 0x751924 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41b2aa: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41b2ac: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41b2ae: sub edi, ecx */
	m->esi = m->edi;	/* 41b2b0: mov esi, edi */
	m->ebx = m->ecx;	/* 41b2b2: mov ebx, ecx */
	m->edi = m->edx;	/* 41b2b4: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41b2b6: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41b2b9: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 41b2bb: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41b2bd: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41b2be: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41b2c1: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebx;	/* 41b2c3: mov ecx, ebx */
	m->eax = (DWORD)(m->esp + 0x4cu);	/* 41b2c5: lea eax, [esp + 0x4c] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41b2c9: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41b2cc: push eax */
	m->eax = M32((DWORD)(0x4dcc98u));	/* 41b2cd: mov eax, dword ptr [0x4dcc98] */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41b2d2: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x4dcc9cu));	/* 41b2d4: mov ecx, dword ptr [0x4dcc9c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41b2da: push eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffe8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41b2db: add ecx, -0x18 */
	{ DWORD a_ = m->eax, b_ = 0xffffff60u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41b2de: add eax, 0xffffff60 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b2e3: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41b2e4: push eax */
	m->esp -= 4; M32(m->esp) = 0x41b2eau; native_call(m, 0x4029d0u);	/* 41b2e5: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41b2ea: add esp, 0x38 */
	m->edi = M32(m->esp); m->esp += 4;	/* 41b2ed: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 41b2ee: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 41b2ef: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 41b2f0: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x7cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41b2f1: add esp, 0x7c */
	m->esp += 4 + 0; return;	/* 41b2f4: ret  */
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
