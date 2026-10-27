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

static void lift_40a070(X86 *m);

/* arena_40a070 (0x40a070), lifted by tools/lift.py */
static void lift_40a070(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40a070: sub esp, 0x48 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 40a073: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 40a078: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a07e: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 40a07f: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40a080: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40a081: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a082: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a083: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40a089u; native_call(m, 0x4044a0u);	/* 40a084: call 0x4044a0 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a089: push 2 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 40a08b: mov dword ptr [esp + 0x1c], eax */
	m->esp -= 4; M32(m->esp) = 0x40a094u; native_call(m, 0x41ef90u);	/* 40a08f: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40a094: add esp, 0xc */
	m->esp -= 4; M32(m->esp) = 0x40a09du; native_call(m, M32(0x4a9218u));	/* 40a097: call dword ptr [0x4a9218] */
	m->edi = M32((DWORD)(0x4a9228u));	/* 40a09d: mov edi, dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40a0a3: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a0a8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a0ad: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a0b2: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40a0b9u; native_call(m, m->edi);	/* 40a0b7: call edi */
	m->edx = M32((DWORD)(0x4deb50u));	/* 40a0b9: mov edx, dword ptr [0x4deb50] */
	m->eax = M32((DWORD)(0x4db8d4u));	/* 40a0bf: mov eax, dword ptr [0x4db8d4] */
	m->ecx = M32((DWORD)(0x4db8d0u));	/* 40a0c4: mov ecx, dword ptr [0x4db8d0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a0ca: push edx */
	m->edx = M32((DWORD)(0x4db8ccu));	/* 40a0cb: mov edx, dword ptr [0x4db8cc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a0d1: push eax */
	m->eax = M32((DWORD)(0x4db8c8u));	/* 40a0d2: mov eax, dword ptr [0x4db8c8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a0d7: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a0d8: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a0d9: push eax */
	m->esp -= 4; M32(m->esp) = 0x40a0dfu; native_call(m, 0x427a90u);	/* 40a0da: call 0x427a90 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a0df: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a0e4: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a0e9: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a0ee: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a0f0: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40a0fau; native_call(m, 0x41f0e0u);	/* 40a0f5: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4db8ccu));	/* 40a0fa: mov ecx, dword ptr [0x4db8cc] */
	m->edx = M32((DWORD)(0x4db8d0u));	/* 40a100: mov edx, dword ptr [0x4db8d0] */
	{ DWORD a_ = m->edx, b_ = 0xfffffff0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40a106: add edx, -0x10 */
	m->eax = (DWORD)(m->ecx + 0x28u);	/* 40a109: lea eax, [ecx + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a10c: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a10d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a10e: push eax */
	m->eax = M32((DWORD)(0x4db8c8u));	/* 40a10f: mov eax, dword ptr [0x4db8c8] */
	{ DWORD a_ = m->eax, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40a114: add eax, 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a117: push eax */
	m->esp -= 4; M32(m->esp) = 0x40a11du; native_call(m, 0x427a40u);	/* 40a118: call 0x427a40 */
	m->ecx = M32((DWORD)(0x4dbaa4u));	/* 40a11d: mov ecx, dword ptr [0x4dbaa4] */
	m->edx = M32((DWORD)(0x4dbaa0u));	/* 40a123: mov edx, dword ptr [0x4dbaa0] */
	m->eax = M32((DWORD)(0x4dba9cu));	/* 40a129: mov eax, dword ptr [0x4dba9c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a12e: push ecx */
	m->ecx = M32((DWORD)(0x4dba98u));	/* 40a12f: mov ecx, dword ptr [0x4dba98] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a135: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a136: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a137: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a138: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40a142u; native_call(m, 0x41f0e0u);	/* 40a13d: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x4db8ccu));	/* 40a142: mov edx, dword ptr [0x4db8cc] */
	m->eax = M32((DWORD)(0x4db8c8u));	/* 40a148: mov eax, dword ptr [0x4db8c8] */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40a14d: add esp, 0x4c */
	{ DWORD a_ = m->edx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40a150: add edx, 0x10 */
	{ DWORD a_ = m->eax, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40a153: add eax, 0x50 */
	{ DWORD v_ = 0x7524a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a156: push 0x7524a4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a15b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a15c: push eax */
	m->esp -= 4; M32(m->esp) = 0x40a162u; native_call(m, 0x4028b0u);	/* 40a15d: call 0x4028b0 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40a162: add esp, 0xc */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 40a165: xor ebp, ebp */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 40a167: xor esi, esi */
	m->ebx = 0x752524u;	/* 40a169: mov ebx, 0x752524 */
L_40a16e:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a16e: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x40a179u; native_call(m, M32(0x4a9224u));	/* 40a173: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 40a179: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 40a17e: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40a180: and ecx, 0x800001ff */
	if (!m->sf) goto L_40a190;	/* 40a186: jns 0x40a190 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 40a188: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40a189: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 40a18f: inc ecx */
L_40a190:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 40a190: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 40a191: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a197: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40a198: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 40a19a: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 40a1a0: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 40a1a3: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x40a1acu; native_call(m, 0x4566c0u);	/* 40a1a7: call 0x4566c0 */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x10u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40a1ac: cmp dword ptr [esp + 0x10], ebp */
	if (!m->zf) goto L_40a22f;	/* 40a1b0: jne 0x40a22f */
	m->eax = M32((DWORD)(0x4db8b4u));	/* 40a1b2: mov eax, dword ptr [0x4db8b4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40a1b7: test eax, eax */
	if (!m->zf) goto L_40a22f;	/* 40a1b9: jne 0x40a22f */
	m->eax = M32((DWORD)(0x907b2cu));	/* 40a1bb: mov eax, dword ptr [0x907b2c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40a1c0: test eax, eax */
	if (!m->zf) goto L_40a22f;	/* 40a1c2: jne 0x40a22f */
	m->eax = M32((DWORD)(0x4db714u));	/* 40a1c4: mov eax, dword ptr [0x4db714] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40a1c9: test eax, eax */
	if (!m->zf) goto L_40a22f;	/* 40a1cb: jne 0x40a22f */
	m->eax = M32((DWORD)(0x4db8bcu));	/* 40a1cd: mov eax, dword ptr [0x4db8bc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40a1d2: test eax, eax */
	if (!m->zf) goto L_40a22f;	/* 40a1d4: jne 0x40a22f */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a1d6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a1db: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a1e0: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a1e5: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40a1ecu; native_call(m, m->edi);	/* 40a1ea: call edi */
	m->ecx = M32((DWORD)(0x4db8ccu));	/* 40a1ec: mov ecx, dword ptr [0x4db8cc] */
	m->eax = M32((DWORD)(0x4db8c8u));	/* 40a1f2: mov eax, dword ptr [0x4db8c8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a1f7: push 1 */
	m->edx = (DWORD)(m->ecx + 0x50u);	/* 40a1f9: lea edx, [ecx + 0x50] */
	{ DWORD a_ = m->ecx, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40a1fc: add ecx, 0x30 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a1ff: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xc3u);	/* 40a200: lea edx, [esi + eax + 0xc3] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a207: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x23u);	/* 40a208: lea eax, [esi + eax + 0x23] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a20c: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a20d: push eax */
	m->esp -= 4; M32(m->esp) = 0x40a213u; native_call(m, 0x4282f0u);	/* 40a20e: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x4dbaa4u));	/* 40a213: mov ecx, dword ptr [0x4dbaa4] */
	m->edx = M32((DWORD)(0x4dbaa0u));	/* 40a219: mov edx, dword ptr [0x4dbaa0] */
	m->eax = M32((DWORD)(0x4dba9cu));	/* 40a21f: mov eax, dword ptr [0x4dba9c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a224: push ecx */
	m->ecx = M32((DWORD)(0x4dba98u));	/* 40a225: mov ecx, dword ptr [0x4dba98] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a22b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a22c: push eax */
	goto L_40a286;	/* 40a22d: jmp 0x40a286 */
L_40a22f:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40a22f: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a234: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a239: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a23e: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40a245u; native_call(m, m->edi);	/* 40a243: call edi */
	m->ecx = M32((DWORD)(0x4db8ccu));	/* 40a245: mov ecx, dword ptr [0x4db8cc] */
	m->eax = M32((DWORD)(0x4db8c8u));	/* 40a24b: mov eax, dword ptr [0x4db8c8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a250: push 1 */
	m->edx = (DWORD)(m->ecx + 0x50u);	/* 40a252: lea edx, [ecx + 0x50] */
	{ DWORD a_ = m->ecx, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40a255: add ecx, 0x30 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a258: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xc3u);	/* 40a259: lea edx, [esi + eax + 0xc3] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a260: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x23u);	/* 40a261: lea eax, [esi + eax + 0x23] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a265: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a266: push eax */
	m->esp -= 4; M32(m->esp) = 0x40a26cu; native_call(m, 0x4282f0u);	/* 40a267: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x4db8acu));	/* 40a26c: mov ecx, dword ptr [0x4db8ac] */
	m->edx = M32((DWORD)(0x4db8a8u));	/* 40a272: mov edx, dword ptr [0x4db8a8] */
	m->eax = M32((DWORD)(0x4db8a4u));	/* 40a278: mov eax, dword ptr [0x4db8a4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a27d: push ecx */
	m->ecx = M32((DWORD)(0x4db8a0u));	/* 40a27e: mov ecx, dword ptr [0x4db8a0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a284: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a285: push eax */
L_40a286:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a286: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a287: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40a291u; native_call(m, 0x41f0e0u);	/* 40a28c: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4db8c8u));	/* 40a291: mov eax, dword ptr [0x4db8c8] */
	m->ecx = M32((DWORD)(0x4db8ccu));	/* 40a296: mov ecx, dword ptr [0x4db8cc] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40a29c: add esp, 0x28 */
	{ DWORD a_ = m->ecx, b_ = 0x38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40a29f: add ecx, 0x38 */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xc1u);	/* 40a2a2: lea edx, [esi + eax + 0xc1] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a2a9: push ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a2aa: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x25u);	/* 40a2ab: lea edx, [esi + eax + 0x25] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a2af: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a2b0: push edx */
	m->esp -= 4; M32(m->esp) = 0x40a2b6u; native_call(m, 0x4029d0u);	/* 40a2b1: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40a2b6: add esp, 0x10 */
	{ DWORD a_ = m->ebx, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 40a2b9: add ebx, 0x80 */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 40a2bf: inc ebp */
	{ DWORD a_ = m->esi, b_ = 0xb4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 40a2c0: add esi, 0xb4 */
	{ DWORD a_ = m->ebx, b_ = 0x7526a4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40a2c6: cmp ebx, 0x7526a4 */
	if (m->sf != m->of) goto L_40a16e;	/* 40a2cc: jl 0x40a16e */
	m->eax = M32((DWORD)(0x4dbaa4u));	/* 40a2d2: mov eax, dword ptr [0x4dbaa4] */
	m->ecx = M32((DWORD)(0x4dbaa0u));	/* 40a2d7: mov ecx, dword ptr [0x4dbaa0] */
	m->edx = M32((DWORD)(0x4dba9cu));	/* 40a2dd: mov edx, dword ptr [0x4dba9c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a2e3: push eax */
	m->eax = M32((DWORD)(0x4dba98u));	/* 40a2e4: mov eax, dword ptr [0x4dba98] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a2e9: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a2ea: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a2eb: push eax */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a2ec: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40a2f6u; native_call(m, 0x41f0e0u);	/* 40a2f1: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4db8ccu));	/* 40a2f6: mov ecx, dword ptr [0x4db8cc] */
	m->edx = M32((DWORD)(0x4db8c8u));	/* 40a2fc: mov edx, dword ptr [0x4db8c8] */
	{ DWORD a_ = m->ecx, b_ = 0x5au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40a302: add ecx, 0x5a */
	{ DWORD v_ = 0x7526a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a305: push 0x7526a4 */
	{ DWORD a_ = m->edx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40a30a: add edx, 0x10 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a30d: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a30e: push edx */
	m->esp -= 4; M32(m->esp) = 0x40a314u; native_call(m, 0x402620u);	/* 40a30f: call 0x402620 */
	m->eax = M32((DWORD)(0x4db8ccu));	/* 40a314: mov eax, dword ptr [0x4db8cc] */
	m->ecx = M32((DWORD)(0x4db8c8u));	/* 40a319: mov ecx, dword ptr [0x4db8c8] */
	{ DWORD a_ = m->eax, b_ = 0x5au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40a31f: add eax, 0x5a */
	{ DWORD v_ = 0x752724u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a322: push 0x752724 */
	{ DWORD a_ = m->ecx, b_ = 0x114u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40a327: add ecx, 0x114 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a32d: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a32e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40a334u; native_call(m, 0x402620u);	/* 40a32f: call 0x402620 */
	m->edx = M32((DWORD)(0x4db8ccu));	/* 40a334: mov edx, dword ptr [0x4db8cc] */
	m->eax = M32((DWORD)(0x4db8c8u));	/* 40a33a: mov eax, dword ptr [0x4db8c8] */
	{ DWORD a_ = m->edx, b_ = 0x5au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40a33f: add edx, 0x5a */
	{ DWORD v_ = 0x752ba4u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a342: push 0x752ba4 */
	{ DWORD a_ = m->eax, b_ = 0x164u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40a347: add eax, 0x164 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a34c: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a34d: push eax */
	m->esp -= 4; M32(m->esp) = 0x40a353u; native_call(m, 0x402620u);	/* 40a34e: call 0x402620 */
	m->ecx = M32((DWORD)(0x4db8ccu));	/* 40a353: mov ecx, dword ptr [0x4db8cc] */
	m->edx = M32((DWORD)(0x4db8c8u));	/* 40a359: mov edx, dword ptr [0x4db8c8] */
	{ DWORD a_ = m->ecx, b_ = 0x5au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40a35f: add ecx, 0x5a */
	{ DWORD v_ = 0x7527a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a362: push 0x7527a4 */
	{ DWORD a_ = m->edx, b_ = 0x1b4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40a367: add edx, 0x1b4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a36d: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a36e: push edx */
	m->esp -= 4; M32(m->esp) = 0x40a374u; native_call(m, 0x402620u);	/* 40a36f: call 0x402620 */
	m->eax = M32((DWORD)(0x4db8ccu));	/* 40a374: mov eax, dword ptr [0x4db8cc] */
	m->ecx = M32((DWORD)(0x4db8c8u));	/* 40a379: mov ecx, dword ptr [0x4db8c8] */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40a37f: add esp, 0x44 */
	{ DWORD a_ = m->eax, b_ = 0x5au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40a382: add eax, 0x5a */
	{ DWORD a_ = m->ecx, b_ = 0x1fcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40a385: add ecx, 0x1fc */
	{ DWORD v_ = 0x752824u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a38b: push 0x752824 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a390: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a391: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40a397u; native_call(m, 0x402620u);	/* 40a392: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a397: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a39c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a3a1: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a3a6: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a3a8: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40a3b2u; native_call(m, 0x41f0e0u);	/* 40a3ad: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x4db8ccu));	/* 40a3b2: mov edx, dword ptr [0x4db8cc] */
	m->ecx = M32((DWORD)(0x4db8d0u));	/* 40a3b8: mov ecx, dword ptr [0x4db8d0] */
	{ DWORD a_ = m->ecx, b_ = 0xfffffff0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40a3be: add ecx, -0x10 */
	m->eax = (DWORD)(m->edx + 0x6eu);	/* 40a3c1: lea eax, [edx + 0x6e] */
	m->edx = M32((DWORD)(0x4db8c8u));	/* 40a3c4: mov edx, dword ptr [0x4db8c8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a3ca: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a3cb: push ecx */
	{ DWORD a_ = m->edx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40a3cc: add edx, 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a3cf: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a3d0: push edx */
	m->esp -= 4; M32(m->esp) = 0x40a3d6u; native_call(m, 0x427a40u);	/* 40a3d1: call 0x427a40 */
	m->eax = M32((DWORD)(0x4db8d4u));	/* 40a3d6: mov eax, dword ptr [0x4db8d4] */
	m->ecx = M32((DWORD)(0x4db8d0u));	/* 40a3db: mov ecx, dword ptr [0x4db8d0] */
	m->edx = M32((DWORD)(0x4db8c8u));	/* 40a3e1: mov edx, dword ptr [0x4db8c8] */
	{ DWORD a_ = m->eax, b_ = 0xffffffacu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40a3e7: add eax, -0x54 */
	{ DWORD a_ = m->ecx, b_ = 0xfffffff0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40a3ea: add ecx, -0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a3ed: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a3ee: push ecx */
	{ DWORD a_ = m->edx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40a3ef: add edx, 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a3f2: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a3f3: push edx */
	m->esp -= 4; M32(m->esp) = 0x40a3f9u; native_call(m, 0x427a40u);	/* 40a3f4: call 0x427a40 */
	m->eax = M32((DWORD)(0x4dbac8u));	/* 40a3f9: mov eax, dword ptr [0x4dbac8] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40a3fe: add esp, 0x40 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40a401: test eax, eax */
	if (!m->zf) goto L_40a412;	/* 40a403: jne 0x40a412 */
	m->eax = M32((DWORD)(0x4dbaa8u));	/* 40a405: mov eax, dword ptr [0x4dbaa8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40a40a: test eax, eax */
	if (m->zf) goto L_40a915;	/* 40a40c: je 0x40a915 */
L_40a412:
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 40a412: xor ebp, ebp */
	m->ebx = 0x78u;	/* 40a414: mov ebx, 0x78 */
	goto L_40a421;	/* 40a419: jmp 0x40a421 */
L_40a41b:
	m->edi = M32((DWORD)(0x4a9228u));	/* 40a41b: mov edi, dword ptr [0x4a9228] */
L_40a421:
	{ DWORD a_ = m->ebp, b_ = M32((DWORD)(0x67ef30u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40a421: cmp ebp, dword ptr [0x67ef30] */
	if (m->sf == m->of) goto L_40a7ff;	/* 40a427: jge 0x40a7ff */
	m->eax = M32((DWORD)(0x4dbaa8u));	/* 40a42d: mov eax, dword ptr [0x4dbaa8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40a432: test eax, eax */
	if (m->zf) goto L_40a563;	/* 40a434: je 0x40a563 */
	m->eax = M32((DWORD)(0x680bb0u));	/* 40a43a: mov eax, dword ptr [0x680bb0] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40a43f: add eax, ebp */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 40a441: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 40a444: lea edx, [eax + ecx*4] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edx*2 + 0x908807u))) & 0xff) << 0);	/* 40a447: mov al, byte ptr [edx*2 + 0x908807] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40a44e: test al, al */
	if (m->zf) goto L_40a563;	/* 40a450: je 0x40a563 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a456: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x40a461u; native_call(m, M32(0x4a9224u));	/* 40a45b: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x76d448u));	/* 40a461: mov eax, dword ptr [0x76d448] */
	m->ecx = m->eax;	/* 40a466: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40a468: and ecx, 0x800001ff */
	if (!m->sf) goto L_40a478;	/* 40a46e: jns 0x40a478 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 40a470: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40a471: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 40a477: inc ecx */
L_40a478:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 40a478: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 40a479: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a47f: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40a480: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 40a482: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 40a488: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 40a48b: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x40a494u; native_call(m, 0x4566c0u);	/* 40a48f: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a494: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a499: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a49e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a4a3: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40a4aau; native_call(m, m->edi);	/* 40a4a8: call edi */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a4aa: push 7 */
	m->esp -= 4; M32(m->esp) = 0x40a4b2u; native_call(m, M32(0x4a921cu));	/* 40a4ac: call dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(0x4a920cu));	/* 40a4b2: mov esi, dword ptr [0x4a920c] */
	{ DWORD v_ = 0x3f500000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a4b8: push 0x3f500000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a4bd: push 0 */
	m->esp -= 4; M32(m->esp) = 0x40a4c1u; native_call(m, m->esi);	/* 40a4bf: call esi */
	m->eax = M32((DWORD)(0x4db8ccu));	/* 40a4c1: mov eax, dword ptr [0x4db8cc] */
	m->edx = M32((DWORD)(0x4db8c8u));	/* 40a4c6: mov edx, dword ptr [0x4db8c8] */
	{ DWORD a_ = m->edx, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40a4cc: add edx, 0xc */
	m->ecx = (DWORD)(m->ebx + m->eax*1 + 0xffffffffu);	/* 40a4cf: lea ecx, [ebx + eax - 1] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a4d3: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a4d4: push edx */
	m->esp -= 4; M32(m->esp) = 0x40a4dau; native_call(m, 0x41ef60u);	/* 40a4d5: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40a4da: add esp, 8 */
	{ DWORD v_ = 0x3f500000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a4dd: push 0x3f500000 */
	{ DWORD v_ = 0x3d800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a4e2: push 0x3d800000 */
	m->esp -= 4; M32(m->esp) = 0x40a4e9u; native_call(m, m->esi);	/* 40a4e7: call esi */
	m->eax = M32((DWORD)(0x4db8ccu));	/* 40a4e9: mov eax, dword ptr [0x4db8cc] */
	m->edx = M32((DWORD)(0x4db8c8u));	/* 40a4ee: mov edx, dword ptr [0x4db8c8] */
	{ DWORD a_ = m->edx, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40a4f4: add edx, 0x1c */
	m->ecx = (DWORD)(m->ebx + m->eax*1 + 0xffffffffu);	/* 40a4f7: lea ecx, [ebx + eax - 1] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a4fb: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a4fc: push edx */
	m->esp -= 4; M32(m->esp) = 0x40a502u; native_call(m, 0x41ef60u);	/* 40a4fd: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40a502: add esp, 8 */
	{ DWORD v_ = 0x3f600000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a505: push 0x3f600000 */
	{ DWORD v_ = 0x3d800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a50a: push 0x3d800000 */
	m->esp -= 4; M32(m->esp) = 0x40a511u; native_call(m, m->esi);	/* 40a50f: call esi */
	m->eax = M32((DWORD)(0x4db8ccu));	/* 40a511: mov eax, dword ptr [0x4db8cc] */
	m->edx = M32((DWORD)(0x4db8c8u));	/* 40a516: mov edx, dword ptr [0x4db8c8] */
	{ DWORD a_ = m->edx, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40a51c: add edx, 0x1c */
	m->ecx = (DWORD)(m->ebx + m->eax*1 + 0xfu);	/* 40a51f: lea ecx, [ebx + eax + 0xf] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a523: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a524: push edx */
	m->esp -= 4; M32(m->esp) = 0x40a52au; native_call(m, 0x41ef60u);	/* 40a525: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40a52a: add esp, 8 */
	{ DWORD v_ = 0x3f600000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a52d: push 0x3f600000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a532: push 0 */
	m->esp -= 4; M32(m->esp) = 0x40a536u; native_call(m, m->esi);	/* 40a534: call esi */
	m->eax = M32((DWORD)(0x4db8ccu));	/* 40a536: mov eax, dword ptr [0x4db8cc] */
	m->edx = M32((DWORD)(0x4db8c8u));	/* 40a53b: mov edx, dword ptr [0x4db8c8] */
	{ DWORD a_ = m->edx, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40a541: add edx, 0xc */
	m->ecx = (DWORD)(m->ebx + m->eax*1 + 0xfu);	/* 40a544: lea ecx, [ebx + eax + 0xf] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a548: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a549: push edx */
	m->esp -= 4; M32(m->esp) = 0x40a54fu; native_call(m, 0x41ef60u);	/* 40a54a: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40a54f: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x40a558u; native_call(m, M32(0x4a9220u));	/* 40a552: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a558: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x40a563u; native_call(m, M32(0x4a922cu));	/* 40a55d: call dword ptr [0x4a922c] */
L_40a563:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a563: push 0x3f800000 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40a568: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40a56d: push 0x3f4ccccd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a572: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a574: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40a57eu; native_call(m, 0x41f0e0u);	/* 40a579: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x680bb0u));	/* 40a57e: mov eax, dword ptr [0x680bb0] */
	m->ecx = M32((DWORD)(0x76d41cu));	/* 40a583: mov ecx, dword ptr [0x76d41c] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40a589: add eax, ebp */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40a58b: add esp, 0x14 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40a58e: cmp ecx, eax */
	if (!m->zf) goto L_40a5b3;	/* 40a590: jne 0x40a5b3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a592: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a597: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a59c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a5a1: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a5a6: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40a5b0u; native_call(m, 0x41f0e0u);	/* 40a5ab: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40a5b0: add esp, 0x14 */
L_40a5b3:
	m->ecx = 0xcu;	/* 40a5b3: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40a5b8: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x24u);	/* 40a5ba: lea edi, [esp + 0x24] */
	{ DWORD v_ = 0x20u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a5be: push 0x20 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 40a5c0: rep stosd dword ptr es:[edi], eax */
	m->ecx = M32((DWORD)(0x680bb0u));	/* 40a5c2: mov ecx, dword ptr [0x680bb0] */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 40a5c8: stosw word ptr es:[edi], ax */
	m->eax = (DWORD)(m->ecx + m->ebp*1 + 0x0u);	/* 40a5ca: lea eax, [ecx + ebp] */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 40a5cd: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 40a5d0: lea eax, [eax + edx*4] */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 40a5d3: lea edx, [esp + 0x28] */
	m->ecx = (DWORD)(m->eax*2 + 0x9087c4u);	/* 40a5d7: lea ecx, [eax*2 + 0x9087c4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a5de: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a5df: push edx */
	m->esp -= 4; M32(m->esp) = 0x40a5e5u; native_call(m, 0x49ea80u);	/* 40a5e0: call 0x49ea80 */
	m->ecx = M32((DWORD)(0x4db8ccu));	/* 40a5e5: mov ecx, dword ptr [0x4db8cc] */
	m->eax = (DWORD)(m->esp + 0x30u);	/* 40a5eb: lea eax, [esp + 0x30] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a5ef: push eax */
	m->eax = M32((DWORD)(0x4db8c8u));	/* 40a5f0: mov eax, dword ptr [0x4db8c8] */
	m->edx = (DWORD)(m->ebx + m->ecx*1 + 0x0u);	/* 40a5f5: lea edx, [ebx + ecx] */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40a5f8: add eax, 0x20 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a5fb: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a5fc: push eax */
	m->esp -= 4; M32(m->esp) = 0x40a602u; native_call(m, 0x402620u);	/* 40a5fd: call 0x402620 */
	m->ecx = M32((DWORD)(0x680bb0u));	/* 40a602: mov ecx, dword ptr [0x680bb0] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40a608: add esp, 0x18 */
	m->eax = (DWORD)(m->ecx + m->ebp*1 + 0x0u);	/* 40a60b: lea eax, [ecx + ebp] */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 40a60e: lea edx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 40a611: lea edx, [eax + edx*4] */
	{ DWORD a_ = m->edx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 40a614: shl edx, 1 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edx + 0x9087e4u))) & 0xff) << 0);	/* 40a616: mov al, byte ptr [edx + 0x9087e4] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40a61c: test al, al */
	if (m->zf) goto L_40a645;	/* 40a61e: je 0x40a645 */
	m->eax = M32((DWORD)(0x4db8ccu));	/* 40a620: mov eax, dword ptr [0x4db8cc] */
	m->edx = M32((DWORD)(0x4db8c8u));	/* 40a625: mov edx, dword ptr [0x4db8c8] */
	{ DWORD v_ = 0x75c1a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a62b: push 0x75c1a4 */
	{ DWORD a_ = m->edx, b_ = 0x114u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40a630: add edx, 0x114 */
	m->ecx = (DWORD)(m->ebx + m->eax*1 + 0x0u);	/* 40a636: lea ecx, [ebx + eax] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a639: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a63a: push edx */
	m->esp -= 4; M32(m->esp) = 0x40a640u; native_call(m, 0x402620u);	/* 40a63b: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40a640: add esp, 0xc */
	goto L_40a693;	/* 40a643: jmp 0x40a693 */
L_40a645:
	m->ecx = 0xcu;	/* 40a645: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40a64a: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x24u);	/* 40a64c: lea edi, [esp + 0x24] */
	{ DWORD v_ = 0xdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40a650: push 0xd */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 40a652: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 40a654: stosw word ptr es:[edi], ax */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(m->edx + 0x9087e5u)));	/* 40a656: movsx eax, byte ptr [edx + 0x9087e5] */
	{ DWORD a_ = m->eax, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 40a65d: shl eax, 5 */
	{ DWORD a_ = m->eax, b_ = 0x907b30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40a660: add eax, 0x907b30 */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 40a665: lea ecx, [esp + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a669: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a66a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40a670u; native_call(m, 0x49ea80u);	/* 40a66b: call 0x49ea80 */
	m->eax = M32((DWORD)(0x4db8ccu));	/* 40a670: mov eax, dword ptr [0x4db8cc] */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 40a675: lea edx, [esp + 0x30] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a679: push edx */
	m->edx = M32((DWORD)(0x4db8c8u));	/* 40a67a: mov edx, dword ptr [0x4db8c8] */
	m->ecx = (DWORD)(m->ebx + m->eax*1 + 0x0u);	/* 40a680: lea ecx, [ebx + eax] */
	{ DWORD a_ = m->edx, b_ = 0x114u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40a683: add edx, 0x114 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a689: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a68a: push edx */
	m->esp -= 4; M32(m->esp) = 0x40a690u; native_call(m, 0x402620u);	/* 40a68b: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40a690: add esp, 0x18 */
L_40a693:
	m->eax = M32((DWORD)(0x680bb0u));	/* 40a693: mov eax, dword ptr [0x680bb0] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40a698: add eax, ebp */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 40a69a: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 40a69d: lea edx, [eax + ecx*4] */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(m->edx*2 + 0x9087ecu)));	/* 40a6a0: movsx eax, byte ptr [edx*2 + 0x9087ec] */
	m->edx = M32((DWORD)(0x4db8ccu));	/* 40a6a8: mov edx, dword ptr [0x4db8cc] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 40a6ae: lea eax, [eax + eax*4] */
	m->ecx = (DWORD)(m->eax*4 + 0x4db8d8u);	/* 40a6b1: lea ecx, [eax*4 + 0x4db8d8] */
	m->eax = (DWORD)(m->ebx + m->edx*1 + 0x0u);	/* 40a6b8: lea eax, [ebx + edx] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a6bb: push ecx */
	m->ecx = M32((DWORD)(0x4db8c8u));	/* 40a6bc: mov ecx, dword ptr [0x4db8c8] */
	{ DWORD a_ = m->ecx, b_ = 0x182u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40a6c2: add ecx, 0x182 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a6c8: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a6c9: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40a6cfu; native_call(m, 0x402620u);	/* 40a6ca: call 0x402620 */
	m->ecx = 0xcu;	/* 40a6cf: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40a6d4: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 40a6d6: lea edi, [esp + 0x30] */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 40a6da: lea edx, [esp + 0x30] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 40a6de: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 40a6e0: stosw word ptr es:[edi], ax */
	m->eax = M32((DWORD)(0x680bb0u));	/* 40a6e2: mov eax, dword ptr [0x680bb0] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 40a6e7: push 0xa */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40a6e9: add eax, ebp */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a6eb: push edx */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 40a6ec: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 40a6ef: lea edx, [eax + ecx*4] */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(m->edx*2 + 0x9087e7u)));	/* 40a6f2: movsx eax, byte ptr [edx*2 + 0x9087e7] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a6fa: push eax */
	m->esp -= 4; M32(m->esp) = 0x40a700u; native_call(m, 0x49fb53u);	/* 40a6fb: call 0x49fb53 */
	m->edx = M32((DWORD)(0x680bb0u));	/* 40a700: mov edx, dword ptr [0x680bb0] */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 40a706: lea ecx, [esp + 0x30] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 40a70a: push 0xa */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a70c: push ecx */
	m->eax = (DWORD)(m->edx + m->ebp*1 + 0x0u);	/* 40a70d: lea eax, [edx + ebp] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 40a710: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 40a713: lea edx, [eax + ecx*4] */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(m->edx*2 + 0x9087e6u)));	/* 40a716: movsx eax, byte ptr [edx*2 + 0x9087e6] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a71e: push eax */
	m->esp -= 4; M32(m->esp) = 0x40a724u; native_call(m, 0x49fb53u);	/* 40a71f: call 0x49fb53 */
	m->edi = 0x4ad568u;	/* 40a724: mov edi, 0x4ad568 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40a729: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40a72c: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x48u);	/* 40a72e: lea edx, [esp + 0x48] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 40a732: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 40a734: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 40a736: sub edi, ecx */
	m->esi = m->edi;	/* 40a738: mov esi, edi */
	m->edi = m->edx;	/* 40a73a: mov edi, edx */
	m->edx = m->ecx;	/* 40a73c: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40a73e: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 40a741: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 40a743: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 40a745: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 40a746: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40a749: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 40a74b: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x48u);	/* 40a74d: lea edx, [esp + 0x48] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40a751: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 40a754: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = (DWORD)(m->esp + 0x3cu);	/* 40a756: lea edi, [esp + 0x3c] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40a75a: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 40a75d: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 40a75f: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 40a761: sub edi, ecx */
	m->esi = m->edi;	/* 40a763: mov esi, edi */
	m->edi = m->edx;	/* 40a765: mov edi, edx */
	m->edx = m->ecx;	/* 40a767: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40a769: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 40a76c: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 40a76e: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 40a770: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 40a771: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40a774: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 40a776: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 40a778: lea eax, [esp + 0x48] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40a77c: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a77f: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 40a780: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x4db8ccu));	/* 40a782: mov ecx, dword ptr [0x4db8cc] */
	m->edx = (DWORD)(m->ebx + m->ecx*1 + 0x0u);	/* 40a788: lea edx, [ebx + ecx] */
	m->eax = M32((DWORD)(0x4db8c8u));	/* 40a78b: mov eax, dword ptr [0x4db8c8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a790: push edx */
	{ DWORD a_ = m->eax, b_ = 0x1bcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40a791: add eax, 0x1bc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a796: push eax */
	m->esp -= 4; M32(m->esp) = 0x40a79cu; native_call(m, 0x402620u);	/* 40a797: call 0x402620 */
	m->eax = M32((DWORD)(0x4dbaa8u));	/* 40a79c: mov eax, dword ptr [0x4dbaa8] */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40a7a1: add esp, 0x30 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40a7a4: test eax, eax */
	if (m->zf) goto L_40a7ef;	/* 40a7a6: je 0x40a7ef */
	m->edx = M32((DWORD)(0x680bb0u));	/* 40a7a8: mov edx, dword ptr [0x680bb0] */
	m->ecx = (DWORD)(m->esp + 0x24u);	/* 40a7ae: lea ecx, [esp + 0x24] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 40a7b2: push 0xa */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a7b4: push ecx */
	m->eax = (DWORD)(m->edx + m->ebp*1 + 0x0u);	/* 40a7b5: lea eax, [edx + ebp] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 40a7b8: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 40a7bb: lea edx, [eax + ecx*4] */
	m->eax = M32((DWORD)(m->edx*2 + 0x9087e8u));	/* 40a7be: mov eax, dword ptr [edx*2 + 0x9087e8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a7c5: push eax */
	m->esp -= 4; M32(m->esp) = 0x40a7cbu; native_call(m, 0x49fb53u);	/* 40a7c6: call 0x49fb53 */
	m->edx = M32((DWORD)(0x4db8ccu));	/* 40a7cb: mov edx, dword ptr [0x4db8cc] */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 40a7d1: lea ecx, [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a7d5: push ecx */
	m->ecx = M32((DWORD)(0x4db8c8u));	/* 40a7d6: mov ecx, dword ptr [0x4db8c8] */
	m->eax = (DWORD)(m->ebx + m->edx*1 + 0x0u);	/* 40a7dc: lea eax, [ebx + edx] */
	{ DWORD a_ = m->ecx, b_ = 0x200u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40a7df: add ecx, 0x200 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a7e5: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a7e6: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40a7ecu; native_call(m, 0x402620u);	/* 40a7e7: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40a7ec: add esp, 0x18 */
L_40a7ef:
	{ DWORD a_ = m->ebx, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 40a7ef: add ebx, 0x18 */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 40a7f2: inc ebp */
	{ DWORD a_ = m->ebx, b_ = 0x150u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40a7f3: cmp ebx, 0x150 */
	if (m->sf != m->of) goto L_40a41b;	/* 40a7f9: jl 0x40a41b */
L_40a7ff:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a7ff: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a804: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a809: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a80e: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a813: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40a81du; native_call(m, 0x41f0e0u);	/* 40a818: call 0x41f0e0 */
	m->ecx = 0xcu;	/* 40a81d: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40a822: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x38u);	/* 40a824: lea edi, [esp + 0x38] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 40a828: xor edx, edx */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 40a82a: rep stosd dword ptr es:[edi], eax */
	m->ecx = M32((DWORD)(0x680bb8u));	/* 40a82c: mov ecx, dword ptr [0x680bb8] */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 40a832: mov dword ptr [esp + 0x2c], edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 40a836: stosw word ptr es:[edi], ax */
	m->eax = (DWORD)(m->esp + 0x38u);	/* 40a838: lea eax, [esp + 0x38] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 40a83c: push 0xa */
	M32((DWORD)(m->esp + 0x34u)) = m->edx;	/* 40a83e: mov dword ptr [esp + 0x34], edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a842: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a843: push ecx */
	M16((DWORD)(m->esp + 0x40u)) = (WORD)((m->edx & 0xffff));	/* 40a844: mov word ptr [esp + 0x40], dx */
	m->esp -= 4; M32(m->esp) = 0x40a84eu; native_call(m, 0x49fb53u);	/* 40a849: call 0x49fb53 */
	m->edi = 0x4ad564u;	/* 40a84e: mov edi, 0x4ad564 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40a853: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40a856: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40a858: add esp, 0x20 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 40a85b: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 40a85d: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 40a85f: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 40a861: lea edx, [esp + 0x24] */
	m->esi = m->edi;	/* 40a865: mov esi, edi */
	m->ebx = m->ecx;	/* 40a867: mov ebx, ecx */
	m->edi = m->edx;	/* 40a869: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40a86b: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 40a86e: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 40a870: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 40a872: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 40a873: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40a876: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->eax = M32((DWORD)(0x4dbac8u));	/* 40a878: mov eax, dword ptr [0x4dbac8] */
	m->ecx = m->ebx;	/* 40a87d: mov ecx, ebx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40a87f: and ecx, 3 */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 40a882: push 0xa */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40a884: test eax, eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 40a886: rep movsb byte ptr es:[edi], byte ptr [esi] */
	if (m->zf) goto L_40a898;	/* 40a888: je 0x40a898 */
	m->ecx = M32((DWORD)(0x67ef30u));	/* 40a88a: mov ecx, dword ptr [0x67ef30] */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 40a890: lea eax, [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a894: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a895: push ecx */
	goto L_40a8a3;	/* 40a896: jmp 0x40a8a3 */
L_40a898:
	m->eax = M32((DWORD)(0xa0b368u));	/* 40a898: mov eax, dword ptr [0xa0b368] */
	m->edx = (DWORD)(m->esp + 0x1cu);	/* 40a89d: lea edx, [esp + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a8a1: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a8a2: push eax */
L_40a8a3:
	m->esp -= 4; M32(m->esp) = 0x40a8a8u; native_call(m, 0x49fb53u);	/* 40a8a3: call 0x49fb53 */
	m->edi = (DWORD)(m->esp + 0x24u);	/* 40a8a8: lea edi, [esp + 0x24] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40a8ac: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40a8af: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40a8b1: add esp, 0xc */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 40a8b4: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 40a8b6: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 40a8b8: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 40a8ba: lea edx, [esp + 0x24] */
	m->esi = m->edi;	/* 40a8be: mov esi, edi */
	m->ebx = m->ecx;	/* 40a8c0: mov ebx, ecx */
	m->edi = m->edx;	/* 40a8c2: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40a8c4: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 40a8c7: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 40a8c9: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 40a8cb: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 40a8cc: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40a8cf: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebx;	/* 40a8d1: mov ecx, ebx */
	m->eax = (DWORD)(m->esp + 0x24u);	/* 40a8d3: lea eax, [esp + 0x24] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40a8d7: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a8da: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 40a8db: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x4db8d4u));	/* 40a8dd: mov ecx, dword ptr [0x4db8d4] */
	m->edi = (DWORD)(m->esp + 0x28u);	/* 40a8e3: lea edi, [esp + 0x28] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffb4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40a8e7: add ecx, -0x4c */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40a8ea: xor eax, eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a8ec: push ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40a8ed: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 40a8f0: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 40a8f2: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 40a8f4: dec ecx */
	m->edx = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 40a8f5: lea edx, [ecx + ecx*2] */
	m->eax = (DWORD)(m->ecx + m->edx*4 + 0x0u);	/* 40a8f8: lea eax, [ecx + edx*4] */
	m->ecx = M32((DWORD)(0x4db8d0u));	/* 40a8fb: mov ecx, dword ptr [0x4db8d0] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40a901: sub ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40a903: sub ecx, 0x3c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a906: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40a90cu; native_call(m, 0x4028b0u);	/* 40a907: call 0x4028b0 */
	m->edi = M32((DWORD)(0x4a9228u));	/* 40a90c: mov edi, dword ptr [0x4a9228] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40a912: add esp, 0xc */
L_40a915:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a915: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a91a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a91f: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a924: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a926: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40a930u; native_call(m, 0x41f0e0u);	/* 40a92b: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x4db8d4u));	/* 40a930: mov edx, dword ptr [0x4db8d4] */
	m->ecx = M32((DWORD)(0x4db8d0u));	/* 40a936: mov ecx, dword ptr [0x4db8d0] */
	{ DWORD a_ = m->ecx, b_ = 0xfffffff0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40a93c: add ecx, -0x10 */
	m->eax = (DWORD)(m->edx + 0xffffffceu);	/* 40a93f: lea eax, [edx - 0x32] */
	m->edx = M32((DWORD)(0x4db8c8u));	/* 40a942: mov edx, dword ptr [0x4db8c8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a948: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a949: push ecx */
	{ DWORD a_ = m->edx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40a94a: add edx, 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a94d: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a94e: push edx */
	m->esp -= 4; M32(m->esp) = 0x40a954u; native_call(m, 0x427a40u);	/* 40a94f: call 0x427a40 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40a954: add esp, 0x24 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 40a957: xor esi, esi */
	m->ebx = 0x2u;	/* 40a959: mov ebx, 2 */
	M32((DWORD)(m->esp + 0x14u)) = 0x7528a4u;	/* 40a95e: mov dword ptr [esp + 0x14], 0x7528a4 */
L_40a966:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a966: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x40a971u; native_call(m, M32(0x4a9224u));	/* 40a96b: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 40a971: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 40a976: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40a978: and ecx, 0x800001ff */
	if (!m->sf) goto L_40a988;	/* 40a97e: jns 0x40a988 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 40a980: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40a981: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 40a987: inc ecx */
L_40a988:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 40a988: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 40a989: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a98f: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40a990: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 40a992: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 40a998: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 40a99b: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x40a9a4u; native_call(m, 0x4566c0u);	/* 40a99f: call 0x4566c0 */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 40a9a4: mov eax, dword ptr [esp + 0x10] */
	m->ebp = (DWORD)(m->ebx + 0x1u);	/* 40a9a8: lea ebp, [ebx + 1] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40a9ab: cmp eax, ebp */
	if (!m->zf) goto L_40aaa2;	/* 40a9ad: jne 0x40aaa2 */
	m->eax = M32((DWORD)(0x4db8b4u));	/* 40a9b3: mov eax, dword ptr [0x4db8b4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40a9b8: test eax, eax */
	if (!m->zf) goto L_40aaa2;	/* 40a9ba: jne 0x40aaa2 */
	m->eax = M32((DWORD)(0x907b2cu));	/* 40a9c0: mov eax, dword ptr [0x907b2c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40a9c5: test eax, eax */
	if (!m->zf) goto L_40aaa2;	/* 40a9c7: jne 0x40aaa2 */
	m->eax = M32((DWORD)(0x4dba90u));	/* 40a9cd: mov eax, dword ptr [0x4dba90] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40a9d2: test eax, eax */
	if (!m->zf) goto L_40aa48;	/* 40a9d4: jne 0x40aa48 */
	m->eax = M32((DWORD)(0x4db858u));	/* 40a9d6: mov eax, dword ptr [0x4db858] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40a9db: test eax, eax */
	if (!m->zf) goto L_40aa48;	/* 40a9dd: jne 0x40aa48 */
	{ DWORD a_ = m->ebx, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40a9df: cmp ebx, 2 */
	if (!m->zf) goto L_40aa4d;	/* 40a9e2: jne 0x40aa4d */
	m->eax = M32((DWORD)(0x67ef30u));	/* 40a9e4: mov eax, dword ptr [0x67ef30] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40a9e9: test eax, eax */
	if (m->zf) goto L_40aaa2;	/* 40a9eb: je 0x40aaa2 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a9f1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a9f6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a9fb: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40aa00: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40aa07u; native_call(m, m->edi);	/* 40aa05: call edi */
	m->eax = M32((DWORD)(0x4db8c8u));	/* 40aa07: mov eax, dword ptr [0x4db8c8] */
	m->ecx = M32((DWORD)(0x4db8d4u));	/* 40aa0c: mov ecx, dword ptr [0x4db8d4] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40aa12: push 1 */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x5au);	/* 40aa14: lea eax, [esi + eax + 0x5a] */
	m->edx = (DWORD)(m->ecx + 0xfffffff4u);	/* 40aa18: lea edx, [ecx - 0xc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40aa1b: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40aa1c: add ecx, -0x2c */
	m->edx = (DWORD)(m->eax + 0x78u);	/* 40aa1f: lea edx, [eax + 0x78] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40aa22: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40aa23: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40aa24: push eax */
	m->esp -= 4; M32(m->esp) = 0x40aa2au; native_call(m, 0x4282f0u);	/* 40aa25: call 0x4282f0 */
	m->eax = M32((DWORD)(0x4dbaa4u));	/* 40aa2a: mov eax, dword ptr [0x4dbaa4] */
	m->ecx = M32((DWORD)(0x4dbaa0u));	/* 40aa2f: mov ecx, dword ptr [0x4dbaa0] */
	m->edx = M32((DWORD)(0x4dba9cu));	/* 40aa35: mov edx, dword ptr [0x4dba9c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40aa3b: push eax */
	m->eax = M32((DWORD)(0x4dba98u));	/* 40aa3c: mov eax, dword ptr [0x4dba98] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40aa41: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40aa42: push edx */
	goto L_40aaf5;	/* 40aa43: jmp 0x40aaf5 */
L_40aa48:
	{ DWORD a_ = m->ebx, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40aa48: cmp ebx, 3 */
	if (!m->zf) goto L_40aaa2;	/* 40aa4b: jne 0x40aaa2 */
L_40aa4d:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40aa4d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40aa52: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40aa57: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40aa5c: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40aa63u; native_call(m, m->edi);	/* 40aa61: call edi */
	m->ecx = M32((DWORD)(0x4db8c8u));	/* 40aa63: mov ecx, dword ptr [0x4db8c8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40aa69: push 1 */
	m->eax = (DWORD)(m->esi + m->ecx*1 + 0x5au);	/* 40aa6b: lea eax, [esi + ecx + 0x5a] */
	m->ecx = M32((DWORD)(0x4db8d4u));	/* 40aa6f: mov ecx, dword ptr [0x4db8d4] */
	m->edx = (DWORD)(m->ecx + 0xfffffff4u);	/* 40aa75: lea edx, [ecx - 0xc] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40aa78: add ecx, -0x2c */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40aa7b: push edx */
	m->edx = (DWORD)(m->eax + 0x78u);	/* 40aa7c: lea edx, [eax + 0x78] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40aa7f: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40aa80: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40aa81: push eax */
	m->esp -= 4; M32(m->esp) = 0x40aa87u; native_call(m, 0x4282f0u);	/* 40aa82: call 0x4282f0 */
	m->eax = M32((DWORD)(0x4dbaa4u));	/* 40aa87: mov eax, dword ptr [0x4dbaa4] */
	m->ecx = M32((DWORD)(0x4dbaa0u));	/* 40aa8c: mov ecx, dword ptr [0x4dbaa0] */
	m->edx = M32((DWORD)(0x4dba9cu));	/* 40aa92: mov edx, dword ptr [0x4dba9c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40aa98: push eax */
	m->eax = M32((DWORD)(0x4dba98u));	/* 40aa99: mov eax, dword ptr [0x4dba98] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40aa9e: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40aa9f: push edx */
	goto L_40aaf5;	/* 40aaa0: jmp 0x40aaf5 */
L_40aaa2:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40aaa2: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40aaa7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40aaac: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40aab1: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40aab8u; native_call(m, m->edi);	/* 40aab6: call edi */
	m->ecx = M32((DWORD)(0x4db8c8u));	/* 40aab8: mov ecx, dword ptr [0x4db8c8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40aabe: push 1 */
	m->eax = (DWORD)(m->esi + m->ecx*1 + 0x5au);	/* 40aac0: lea eax, [esi + ecx + 0x5a] */
	m->ecx = M32((DWORD)(0x4db8d4u));	/* 40aac4: mov ecx, dword ptr [0x4db8d4] */
	m->edx = (DWORD)(m->ecx + 0xfffffff4u);	/* 40aaca: lea edx, [ecx - 0xc] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40aacd: add ecx, -0x2c */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40aad0: push edx */
	m->edx = (DWORD)(m->eax + 0x78u);	/* 40aad1: lea edx, [eax + 0x78] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40aad4: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40aad5: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40aad6: push eax */
	m->esp -= 4; M32(m->esp) = 0x40aadcu; native_call(m, 0x4282f0u);	/* 40aad7: call 0x4282f0 */
	m->eax = M32((DWORD)(0x4db8acu));	/* 40aadc: mov eax, dword ptr [0x4db8ac] */
	m->ecx = M32((DWORD)(0x4db8a8u));	/* 40aae1: mov ecx, dword ptr [0x4db8a8] */
	m->edx = M32((DWORD)(0x4db8a4u));	/* 40aae7: mov edx, dword ptr [0x4db8a4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40aaed: push eax */
	m->eax = M32((DWORD)(0x4db8a0u));	/* 40aaee: mov eax, dword ptr [0x4db8a0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40aaf3: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40aaf4: push edx */
L_40aaf5:
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40aaf5: push eax */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40aaf6: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40ab00u; native_call(m, 0x41f0e0u);	/* 40aafb: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4db714u));	/* 40ab00: mov eax, dword ptr [0x4db714] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40ab05: add esp, 0x28 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40ab08: test eax, eax */
	if (!m->zf) goto L_40ab15;	/* 40ab0a: jne 0x40ab15 */
	m->eax = M32((DWORD)(0x4db8bcu));	/* 40ab0c: mov eax, dword ptr [0x4db8bc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40ab11: test eax, eax */
	if (m->zf) goto L_40ab76;	/* 40ab13: je 0x40ab76 */
L_40ab15:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40ab15: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ab1a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ab1f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ab24: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40ab2bu; native_call(m, m->edi);	/* 40ab29: call edi */
	m->ecx = M32((DWORD)(0x4db8c8u));	/* 40ab2b: mov ecx, dword ptr [0x4db8c8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ab31: push 1 */
	m->eax = (DWORD)(m->esi + m->ecx*1 + 0x5au);	/* 40ab33: lea eax, [esi + ecx + 0x5a] */
	m->ecx = M32((DWORD)(0x4db8d4u));	/* 40ab37: mov ecx, dword ptr [0x4db8d4] */
	m->edx = (DWORD)(m->ecx + 0xfffffff4u);	/* 40ab3d: lea edx, [ecx - 0xc] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40ab40: add ecx, -0x2c */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ab43: push edx */
	m->edx = (DWORD)(m->eax + 0x78u);	/* 40ab44: lea edx, [eax + 0x78] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ab47: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ab48: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40ab49: push eax */
	m->esp -= 4; M32(m->esp) = 0x40ab4fu; native_call(m, 0x4282f0u);	/* 40ab4a: call 0x4282f0 */
	m->eax = M32((DWORD)(0x4db8acu));	/* 40ab4f: mov eax, dword ptr [0x4db8ac] */
	m->ecx = M32((DWORD)(0x4db8a8u));	/* 40ab54: mov ecx, dword ptr [0x4db8a8] */
	m->edx = M32((DWORD)(0x4db8a4u));	/* 40ab5a: mov edx, dword ptr [0x4db8a4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40ab60: push eax */
	m->eax = M32((DWORD)(0x4db8a0u));	/* 40ab61: mov eax, dword ptr [0x4db8a0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ab66: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ab67: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40ab68: push eax */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ab69: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40ab73u; native_call(m, 0x41f0e0u);	/* 40ab6e: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40ab73: add esp, 0x28 */
L_40ab76:
	m->ecx = M32((DWORD)(0x4db8c8u));	/* 40ab76: mov ecx, dword ptr [0x4db8c8] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 40ab7c: mov edx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ab80: push edx */
	m->edx = M32((DWORD)(0x4db8d4u));	/* 40ab81: mov edx, dword ptr [0x4db8d4] */
	m->eax = (DWORD)(m->esi + m->ecx*1 + 0x5au);	/* 40ab87: lea eax, [esi + ecx + 0x5a] */
	{ DWORD a_ = m->edx, b_ = 0xffffffdcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40ab8b: add edx, -0x24 */
	m->ecx = (DWORD)(m->eax + 0x78u);	/* 40ab8e: lea ecx, [eax + 0x78] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ab91: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ab92: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40ab93: push eax */
	m->esp -= 4; M32(m->esp) = 0x40ab99u; native_call(m, 0x4029d0u);	/* 40ab94: call 0x4029d0 */
	m->ebx = m->ebp;	/* 40ab99: mov ebx, ebp */
	m->ebp = M32((DWORD)(m->esp + 0x24u));	/* 40ab9b: mov ebp, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40ab9f: add esp, 0x10 */
	{ DWORD a_ = m->ebp, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 40aba2: add ebp, 0x80 */
	m->eax = (DWORD)(m->ebx + 0xfffffffeu);	/* 40aba8: lea eax, [ebx - 2] */
	{ DWORD a_ = m->esi, b_ = 0x96u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 40abab: add esi, 0x96 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40abb1: cmp eax, 3 */
	M32((DWORD)(m->esp + 0x14u)) = m->ebp;	/* 40abb4: mov dword ptr [esp + 0x14], ebp */
	if (m->sf != m->of) goto L_40a966;	/* 40abb8: jl 0x40a966 */
	m->ebx = M32((DWORD)(0x4a9224u));	/* 40abbe: mov ebx, dword ptr [0x4a9224] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40abc4: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x40abcbu; native_call(m, m->ebx);	/* 40abc9: call ebx */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 40abcb: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 40abd0: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40abd2: and ecx, 0x800001ff */
	if (!m->sf) goto L_40abe2;	/* 40abd8: jns 0x40abe2 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 40abda: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40abdb: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 40abe1: inc ecx */
L_40abe2:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 40abe2: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 40abe3: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40abe9: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40abea: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 40abec: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 40abf2: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 40abf5: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x40abfeu; native_call(m, 0x4566c0u);	/* 40abf9: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40abfe: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ac03: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ac08: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ac0d: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40ac14u; native_call(m, m->edi);	/* 40ac12: call edi */
	m->esi = M32((DWORD)(m->esp + 0x10u));	/* 40ac14: mov esi, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->esi, b_ = 0xfu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40ac18: cmp esi, 0xf */
	if (!m->zf) goto L_40b0ec;	/* 40ac1b: jne 0x40b0ec */
	m->eax = M32((DWORD)(0x4db8ccu));	/* 40ac21: mov eax, dword ptr [0x4db8cc] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ac26: push 1 */
	m->ecx = (DWORD)(m->eax + 0xe0u);	/* 40ac28: lea ecx, [eax + 0xe0] */
	{ DWORD a_ = m->eax, b_ = 0xa0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40ac2e: add eax, 0xa0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ac33: push ecx */
	m->ecx = M32((DWORD)(0x4db8c8u));	/* 40ac34: mov ecx, dword ptr [0x4db8c8] */
	m->edx = (DWORD)(m->ecx + 0x23eu);	/* 40ac3a: lea edx, [ecx + 0x23e] */
	{ DWORD a_ = m->ecx, b_ = 0x21eu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40ac40: add ecx, 0x21e */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ac46: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40ac47: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ac48: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40ac4eu; native_call(m, 0x4286b0u);	/* 40ac49: call 0x4286b0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40ac4e: add esp, 0x14 */
L_40ac51:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ac51: push 0 */
L_40ac53:
	m->eax = M32((DWORD)(0x4db8ccu));	/* 40ac53: mov eax, dword ptr [0x4db8cc] */
	m->ecx = (DWORD)(m->eax + 0x130u);	/* 40ac58: lea ecx, [eax + 0x130] */
	{ DWORD a_ = m->eax, b_ = 0xf0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40ac5e: add eax, 0xf0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ac63: push ecx */
	m->ecx = M32((DWORD)(0x4db8c8u));	/* 40ac64: mov ecx, dword ptr [0x4db8c8] */
	m->edx = (DWORD)(m->ecx + 0x23eu);	/* 40ac6a: lea edx, [ecx + 0x23e] */
	{ DWORD a_ = m->ecx, b_ = 0x21eu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40ac70: add ecx, 0x21e */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ac76: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40ac77: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ac78: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40ac7eu; native_call(m, 0x4287a0u);	/* 40ac79: call 0x4287a0 */
	m->eax = M32((DWORD)(0x4dba90u));	/* 40ac7e: mov eax, dword ptr [0x4dba90] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40ac83: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40ac86: test eax, eax */
	if (!m->zf) goto L_40ac9c;	/* 40ac88: jne 0x40ac9c */
	m->eax = M32((DWORD)(0x4db858u));	/* 40ac8a: mov eax, dword ptr [0x4db858] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40ac8f: test eax, eax */
	if (!m->zf) goto L_40ac9c;	/* 40ac91: jne 0x40ac9c */
	m->eax = M32((DWORD)(0x4db8b8u));	/* 40ac93: mov eax, dword ptr [0x4db8b8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40ac98: test eax, eax */
	if (m->zf) goto L_40acfe;	/* 40ac9a: je 0x40acfe */
L_40ac9c:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dba80u)));	/* 40ac9c: fld dword ptr [0x4dba80] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9438u));	/* 40aca2: fmul dword ptr [0x4a9438] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 40aca8: call 0x49ec14 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 40acad: cdq  */
	m->ecx = 0xfu;	/* 40acae: mov ecx, 0xf */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 40acb3: idiv ecx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40acb5: push ecx */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 40acb6: mov dword ptr [esp + 0x18], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x18u)));	/* 40acba: fild dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9434u));	/* 40acbe: fmul dword ptr [0x4a9434] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 40acc4: fstp dword ptr [esp] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40acc7: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40acc9: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40acce: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40acd0: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40acdau; native_call(m, 0x41f0e0u);	/* 40acd5: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4db8d4u));	/* 40acda: mov eax, dword ptr [0x4db8d4] */
	m->edx = M32((DWORD)(0x4db8d0u));	/* 40acdf: mov edx, dword ptr [0x4db8d0] */
	m->ecx = M32((DWORD)(0x4db8c8u));	/* 40ace5: mov ecx, dword ptr [0x4db8c8] */
	{ DWORD v_ = 0x752a24u; m->esp -= 4; M32(m->esp) = v_; }	/* 40aceb: push 0x752a24 */
	{ DWORD a_ = m->eax, b_ = 0xffffffb6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40acf0: add eax, -0x4a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40acf3: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40acf4: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40acf5: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40acfbu; native_call(m, 0x4029d0u);	/* 40acf6: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40acfb: add esp, 0x24 */
L_40acfe:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40acfe: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x40ad09u; native_call(m, M32(0x4a922cu));	/* 40ad03: call dword ptr [0x4a922c] */
	m->eax = M32((DWORD)(0x4db8bcu));	/* 40ad09: mov eax, dword ptr [0x4db8bc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40ad0e: test eax, eax */
	if (m->zf) goto L_40ae68;	/* 40ad10: je 0x40ae68 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ad16: push 0x3f333333 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ad1b: push 0x3f333333 */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40ad20: push 0x3e4ccccd */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40ad25: push 0x3e4ccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ad2a: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40ad34u; native_call(m, 0x41f0e0u);	/* 40ad2f: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4db8ccu));	/* 40ad34: mov eax, dword ptr [0x4db8cc] */
	m->ecx = M32((DWORD)(0x4db8d0u));	/* 40ad39: mov ecx, dword ptr [0x4db8d0] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ad3f: push 1 */
	{ DWORD a_ = m->ecx, b_ = 0xffffff9cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40ad41: add ecx, -0x64 */
	m->edx = (DWORD)(m->eax + 0x116u);	/* 40ad44: lea edx, [eax + 0x116] */
	{ DWORD a_ = m->eax, b_ = 0x96u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40ad4a: add eax, 0x96 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ad4f: push edx */
	m->edx = M32((DWORD)(0x4db8c8u));	/* 40ad50: mov edx, dword ptr [0x4db8c8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ad56: push ecx */
	{ DWORD a_ = m->edx, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40ad57: add edx, 0x64 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40ad5a: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ad5b: push edx */
	m->esp -= 4; M32(m->esp) = 0x40ad61u; native_call(m, 0x427970u);	/* 40ad5c: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ad61: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ad66: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ad6b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ad70: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ad75: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40ad7fu; native_call(m, 0x41f0e0u);	/* 40ad7a: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4db8d0u));	/* 40ad7f: mov eax, dword ptr [0x4db8d0] */
	m->ecx = M32((DWORD)(0x4db8ccu));	/* 40ad84: mov ecx, dword ptr [0x4db8cc] */
	m->edx = M32((DWORD)(0x4db8c8u));	/* 40ad8a: mov edx, dword ptr [0x4db8c8] */
	{ DWORD a_ = m->eax, b_ = 0xffffff9cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40ad90: add eax, -0x64 */
	{ DWORD v_ = 0x74f124u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ad93: push 0x74f124 */
	{ DWORD a_ = m->ecx, b_ = 0xa6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40ad98: add ecx, 0xa6 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40ad9e: push eax */
	{ DWORD a_ = m->edx, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40ad9f: add edx, 0x64 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ada2: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ada3: push edx */
	m->esp -= 4; M32(m->esp) = 0x40ada9u; native_call(m, 0x4029d0u);	/* 40ada4: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40ada9: add esp, 0x4c */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40adac: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40adb1: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40adb3: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40adb5: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40adb7: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40adc1u; native_call(m, 0x41f0e0u);	/* 40adbc: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4db8ccu));	/* 40adc1: mov eax, dword ptr [0x4db8cc] */
	m->edx = M32((DWORD)(0x4db8d0u));	/* 40adc6: mov edx, dword ptr [0x4db8d0] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40adcc: push 1 */
	{ DWORD a_ = m->edx, b_ = 0xffffff38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40adce: add edx, 0xffffff38 */
	m->ecx = (DWORD)(m->eax + 0xe8u);	/* 40add4: lea ecx, [eax + 0xe8] */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40adda: add eax, 0xc8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40addf: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ade0: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40ade1: push eax */
	m->eax = M32((DWORD)(0x4db8c8u));	/* 40ade2: mov eax, dword ptr [0x4db8c8] */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40ade7: add eax, 0xc8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40adec: push eax */
	m->esp -= 4; M32(m->esp) = 0x40adf2u; native_call(m, 0x427970u);	/* 40aded: call 0x427970 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40adf2: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40adf7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40adfc: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ae01: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ae03: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40ae0du; native_call(m, 0x41f0e0u);	/* 40ae08: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4db8ccu));	/* 40ae0d: mov eax, dword ptr [0x4db8cc] */
	m->edx = M32((DWORD)(0x4db8d0u));	/* 40ae12: mov edx, dword ptr [0x4db8d0] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ae18: push 0 */
	{ DWORD a_ = m->edx, b_ = 0xffffff38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40ae1a: add edx, 0xffffff38 */
	m->ecx = (DWORD)(m->eax + 0xe8u);	/* 40ae20: lea ecx, [eax + 0xe8] */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40ae26: add eax, 0xc8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ae2b: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ae2c: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40ae2d: push eax */
	m->eax = M32((DWORD)(0x4db8c8u));	/* 40ae2e: mov eax, dword ptr [0x4db8c8] */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40ae33: add eax, 0xc8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40ae38: push eax */
	m->esp -= 4; M32(m->esp) = 0x40ae3eu; native_call(m, 0x427970u);	/* 40ae39: call 0x427970 */
	m->ecx = M32((DWORD)(0x4db8ccu));	/* 40ae3e: mov ecx, dword ptr [0x4db8cc] */
	m->edx = M32((DWORD)(0x4db8c8u));	/* 40ae44: mov edx, dword ptr [0x4db8c8] */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40ae4a: add esp, 0x50 */
	{ DWORD a_ = m->ecx, b_ = 0xd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40ae4d: add ecx, 0xd0 */
	{ DWORD v_ = 0x4db520u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ae53: push 0x4db520 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ae58: push ecx */
	{ DWORD a_ = m->edx, b_ = 0xd8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40ae59: add edx, 0xd8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ae5f: push edx */
	m->esp -= 4; M32(m->esp) = 0x40ae65u; native_call(m, 0x4028b0u);	/* 40ae60: call 0x4028b0 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40ae65: add esp, 0xc */
L_40ae68:
	m->eax = M32((DWORD)(0x4db714u));	/* 40ae68: mov eax, dword ptr [0x4db714] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40ae6d: test eax, eax */
	if (m->zf) goto L_40af9f;	/* 40ae6f: je 0x40af9f */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ae75: push 0x3f333333 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ae7a: push 0x3f333333 */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40ae7f: push 0x3e4ccccd */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40ae84: push 0x3e4ccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ae89: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40ae93u; native_call(m, 0x41f0e0u);	/* 40ae8e: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4db8ccu));	/* 40ae93: mov eax, dword ptr [0x4db8cc] */
	m->edx = M32((DWORD)(0x4db8d0u));	/* 40ae98: mov edx, dword ptr [0x4db8d0] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ae9e: push 1 */
	{ DWORD a_ = m->edx, b_ = 0xffffff9cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40aea0: add edx, -0x64 */
	m->ecx = (DWORD)(m->eax + 0x116u);	/* 40aea3: lea ecx, [eax + 0x116] */
	{ DWORD a_ = m->eax, b_ = 0x96u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40aea9: add eax, 0x96 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40aeae: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40aeaf: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40aeb0: push eax */
	m->eax = M32((DWORD)(0x4db8c8u));	/* 40aeb1: mov eax, dword ptr [0x4db8c8] */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40aeb6: add eax, 0x64 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40aeb9: push eax */
	m->esp -= 4; M32(m->esp) = 0x40aebfu; native_call(m, 0x427970u);	/* 40aeba: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40aebf: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40aec4: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40aec9: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40aece: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40aed3: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40aeddu; native_call(m, 0x41f0e0u);	/* 40aed8: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4db8d0u));	/* 40aedd: mov ecx, dword ptr [0x4db8d0] */
	m->edx = M32((DWORD)(0x4db8ccu));	/* 40aee3: mov edx, dword ptr [0x4db8cc] */
	m->eax = M32((DWORD)(0x4db8c8u));	/* 40aee9: mov eax, dword ptr [0x4db8c8] */
	{ DWORD a_ = m->ecx, b_ = 0xffffff9cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40aeee: add ecx, -0x64 */
	{ DWORD v_ = 0x74f624u; m->esp -= 4; M32(m->esp) = v_; }	/* 40aef1: push 0x74f624 */
	{ DWORD a_ = m->edx, b_ = 0xa6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40aef6: add edx, 0xa6 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40aefc: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40aefd: add eax, 0x64 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40af00: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40af01: push eax */
	m->esp -= 4; M32(m->esp) = 0x40af07u; native_call(m, 0x4029d0u);	/* 40af02: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40af07: add esp, 0x4c */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40af0a: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40af0f: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40af11: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40af13: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40af15: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40af1fu; native_call(m, 0x41f0e0u);	/* 40af1a: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4db8ccu));	/* 40af1f: mov eax, dword ptr [0x4db8cc] */
	m->edx = M32((DWORD)(0x4db8d0u));	/* 40af24: mov edx, dword ptr [0x4db8d0] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40af2a: push 1 */
	{ DWORD a_ = m->edx, b_ = 0xffffff38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40af2c: add edx, 0xffffff38 */
	m->ecx = (DWORD)(m->eax + 0xe8u);	/* 40af32: lea ecx, [eax + 0xe8] */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40af38: add eax, 0xc8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40af3d: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40af3e: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40af3f: push eax */
	m->eax = M32((DWORD)(0x4db8c8u));	/* 40af40: mov eax, dword ptr [0x4db8c8] */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40af45: add eax, 0xc8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40af4a: push eax */
	m->esp -= 4; M32(m->esp) = 0x40af50u; native_call(m, 0x427970u);	/* 40af4b: call 0x427970 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40af50: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40af55: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40af5a: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40af5f: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40af61: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40af6bu; native_call(m, 0x41f0e0u);	/* 40af66: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4db8ccu));	/* 40af6b: mov eax, dword ptr [0x4db8cc] */
	m->edx = M32((DWORD)(0x4db8d0u));	/* 40af70: mov edx, dword ptr [0x4db8d0] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40af76: push 0 */
	{ DWORD a_ = m->edx, b_ = 0xffffff38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40af78: add edx, 0xffffff38 */
	m->ecx = (DWORD)(m->eax + 0xe8u);	/* 40af7e: lea ecx, [eax + 0xe8] */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40af84: add eax, 0xc8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40af89: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40af8a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40af8b: push eax */
	m->eax = M32((DWORD)(0x4db8c8u));	/* 40af8c: mov eax, dword ptr [0x4db8c8] */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40af91: add eax, 0xc8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40af96: push eax */
	m->esp -= 4; M32(m->esp) = 0x40af9cu; native_call(m, 0x427970u);	/* 40af97: call 0x427970 */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40af9c: add esp, 0x50 */
L_40af9f:
	m->eax = M32((DWORD)(0x4db8b4u));	/* 40af9f: mov eax, dword ptr [0x4db8b4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40afa4: test eax, eax */
	if (m->zf) goto L_40b1a1;	/* 40afa6: je 0x40b1a1 */
	m->ecx = M32((DWORD)(0x4ded6cu));	/* 40afac: mov ecx, dword ptr [0x4ded6c] */
	m->edx = M32((DWORD)(0x4ded68u));	/* 40afb2: mov edx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40afb8: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40afb9: push edx */
	m->esp -= 4; M32(m->esp) = 0x40afbfu; native_call(m, 0x4044e0u);	/* 40afba: call 0x4044e0 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 40afbf: push 0x3f333333 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 40afc4: push 0x3f333333 */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40afc9: push 0x3e4ccccd */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40afce: push 0x3e4ccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40afd3: push 0x9da480 */
	m->esi = m->eax;	/* 40afd8: mov esi, eax */
	m->esp -= 4; M32(m->esp) = 0x40afdfu; native_call(m, 0x41f0e0u);	/* 40afda: call 0x41f0e0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40afdf: push 1 */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 40afe1: push 0x140 */
	{ DWORD v_ = 0x21cu; m->esp -= 4; M32(m->esp) = v_; }	/* 40afe6: push 0x21c */
	{ DWORD v_ = 0xc8u; m->esp -= 4; M32(m->esp) = v_; }	/* 40afeb: push 0xc8 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 40aff0: push 0x64 */
	m->esp -= 4; M32(m->esp) = 0x40aff7u; native_call(m, 0x427970u);	/* 40aff2: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40aff7: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40affc: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40affe: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b003: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b008: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40b012u; native_call(m, 0x41f0e0u);	/* 40b00d: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40b012: add esp, 0x44 */
	{ DWORD v_ = 0x752aa4u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b015: push 0x752aa4 */
	{ DWORD v_ = 0x217u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b01a: push 0x217 */
	{ DWORD v_ = 0xdcu; m->esp -= 4; M32(m->esp) = v_; }	/* 40b01f: push 0xdc */
	{ DWORD v_ = 0x69u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b024: push 0x69 */
	m->esp -= 4; M32(m->esp) = 0x40b02bu; native_call(m, 0x4029d0u);	/* 40b026: call 0x4029d0 */
	{ DWORD v_ = 0x752b24u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b02b: push 0x752b24 */
	{ DWORD v_ = 0x217u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b030: push 0x217 */
	{ DWORD v_ = 0xf4u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b035: push 0xf4 */
	{ DWORD v_ = 0x69u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b03a: push 0x69 */
	m->esp -= 4; M32(m->esp) = 0x40b041u; native_call(m, 0x4029d0u);	/* 40b03c: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40b041: add esp, 0x20 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b044: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x40b04bu; native_call(m, m->ebx);	/* 40b049: call ebx */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 40b04b: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 40b050: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40b052: and ecx, 0x800001ff */
	if (!m->sf) goto L_40b062;	/* 40b058: jns 0x40b062 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 40b05a: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40b05b: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 40b061: inc ecx */
L_40b062:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 40b062: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 40b063: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b069: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40b06a: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 40b06c: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 40b072: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 40b075: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x40b07eu; native_call(m, 0x4566c0u);	/* 40b079: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b07e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b083: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b088: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b08d: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40b094u; native_call(m, m->edi);	/* 40b092: call edi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40b094: test esi, esi */
	if (!m->zf) goto L_40b12c;	/* 40b096: jne 0x40b12c */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b09c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b0a1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b0a6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b0ab: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40b0b2u; native_call(m, m->edi);	/* 40b0b0: call edi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b0b2: push 1 */
	{ DWORD v_ = 0x138u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b0b4: push 0x138 */
	{ DWORD v_ = 0x17cu; m->esp -= 4; M32(m->esp) = v_; }	/* 40b0b9: push 0x17c */
	{ DWORD v_ = 0x118u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b0be: push 0x118 */
	{ DWORD v_ = 0x104u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b0c3: push 0x104 */
	m->esp -= 4; M32(m->esp) = 0x40b0cdu; native_call(m, 0x4282f0u);	/* 40b0c8: call 0x4282f0 */
	m->eax = M32((DWORD)(0x4dbaa4u));	/* 40b0cd: mov eax, dword ptr [0x4dbaa4] */
	m->ecx = M32((DWORD)(0x4dbaa0u));	/* 40b0d2: mov ecx, dword ptr [0x4dbaa0] */
	m->edx = M32((DWORD)(0x4dba9cu));	/* 40b0d8: mov edx, dword ptr [0x4dba9c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40b0de: push eax */
	m->eax = M32((DWORD)(0x4dba98u));	/* 40b0df: mov eax, dword ptr [0x4dba98] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b0e4: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b0e5: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40b0e6: push eax */
	goto L_40b178;	/* 40b0e7: jmp 0x40b178 */
L_40b0ec:
	m->eax = M32((DWORD)(0x4db8ccu));	/* 40b0ec: mov eax, dword ptr [0x4db8cc] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b0f1: push 0 */
	m->ecx = (DWORD)(m->eax + 0xe0u);	/* 40b0f3: lea ecx, [eax + 0xe0] */
	{ DWORD a_ = m->eax, b_ = 0xa0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40b0f9: add eax, 0xa0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b0fe: push ecx */
	m->ecx = M32((DWORD)(0x4db8c8u));	/* 40b0ff: mov ecx, dword ptr [0x4db8c8] */
	m->edx = (DWORD)(m->ecx + 0x23eu);	/* 40b105: lea edx, [ecx + 0x23e] */
	{ DWORD a_ = m->ecx, b_ = 0x21eu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40b10b: add ecx, 0x21e */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b111: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40b112: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b113: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40b119u; native_call(m, 0x4286b0u);	/* 40b114: call 0x4286b0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40b119: add esp, 0x14 */
	{ DWORD a_ = m->esi, b_ = 0x10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40b11c: cmp esi, 0x10 */
	if (!m->zf) goto L_40ac51;	/* 40b11f: jne 0x40ac51 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b125: push 1 */
	goto L_40ac53;	/* 40b127: jmp 0x40ac53 */
L_40b12c:
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b12c: push 0x3f333333 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b131: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b136: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b13b: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40b142u; native_call(m, m->edi);	/* 40b140: call edi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b142: push 1 */
	{ DWORD v_ = 0x138u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b144: push 0x138 */
	{ DWORD v_ = 0x17cu; m->esp -= 4; M32(m->esp) = v_; }	/* 40b149: push 0x17c */
	{ DWORD v_ = 0x118u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b14e: push 0x118 */
	{ DWORD v_ = 0x104u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b153: push 0x104 */
	m->esp -= 4; M32(m->esp) = 0x40b15du; native_call(m, 0x4282f0u);	/* 40b158: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x4db8acu));	/* 40b15d: mov ecx, dword ptr [0x4db8ac] */
	m->edx = M32((DWORD)(0x4db8a8u));	/* 40b163: mov edx, dword ptr [0x4db8a8] */
	m->eax = M32((DWORD)(0x4db8a4u));	/* 40b169: mov eax, dword ptr [0x4db8a4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b16e: push ecx */
	m->ecx = M32((DWORD)(0x4db8a0u));	/* 40b16f: mov ecx, dword ptr [0x4db8a0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b175: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40b176: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b177: push ecx */
L_40b178:
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b178: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40b182u; native_call(m, 0x41f0e0u);	/* 40b17d: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40b182: add esp, 0x28 */
	{ DWORD v_ = 0x751824u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b185: push 0x751824 */
	{ DWORD v_ = 0x17cu; m->esp -= 4; M32(m->esp) = v_; }	/* 40b18a: push 0x17c */
	{ DWORD v_ = 0x120u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b18f: push 0x120 */
	{ DWORD v_ = 0x104u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b194: push 0x104 */
	m->esp -= 4; M32(m->esp) = 0x40b19eu; native_call(m, 0x4029d0u);	/* 40b199: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40b19e: add esp, 0x10 */
L_40b1a1:
	m->eax = M32((DWORD)(0x907b2cu));	/* 40b1a1: mov eax, dword ptr [0x907b2c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40b1a6: test eax, eax */
	if (m->zf) goto L_40b3dd;	/* 40b1a8: je 0x40b3dd */
	m->edx = M32((DWORD)(0x4ded6cu));	/* 40b1ae: mov edx, dword ptr [0x4ded6c] */
	m->eax = M32((DWORD)(0x4ded68u));	/* 40b1b4: mov eax, dword ptr [0x4ded68] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b1b9: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40b1ba: push eax */
	m->esp -= 4; M32(m->esp) = 0x40b1c0u; native_call(m, 0x4045a0u);	/* 40b1bb: call 0x4045a0 */
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40b1c0: push 0x3ecccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40b1c5: push 0x3dcccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40b1ca: push 0x3dcccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40b1cf: push 0x3dcccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b1d4: push 0x9da480 */
	M32((DWORD)(m->esp + 0x2cu)) = m->eax;	/* 40b1d9: mov dword ptr [esp + 0x2c], eax */
	m->esp -= 4; M32(m->esp) = 0x40b1e2u; native_call(m, 0x41f0e0u);	/* 40b1dd: call 0x41f0e0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b1e2: push 1 */
	{ DWORD v_ = 0x1e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b1e4: push 0x1e0 */
	{ DWORD v_ = 0x280u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b1e9: push 0x280 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b1ee: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b1f0: push 0 */
	m->esp -= 4; M32(m->esp) = 0x40b1f7u; native_call(m, 0x427970u);	/* 40b1f2: call 0x427970 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40b1f7: push 0x3f4ccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40b1fc: push 0x3dcccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40b201: push 0x3dcccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40b206: push 0x3dcccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b20b: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40b215u; native_call(m, 0x41f0e0u);	/* 40b210: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40b215: add esp, 0x44 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b218: push 1 */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b21a: push 0x140 */
	{ DWORD v_ = 0x21cu; m->esp -= 4; M32(m->esp) = v_; }	/* 40b21f: push 0x21c */
	{ DWORD v_ = 0xb4u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b224: push 0xb4 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b229: push 0x64 */
	m->esp -= 4; M32(m->esp) = 0x40b230u; native_call(m, 0x427970u);	/* 40b22b: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b230: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b235: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b23a: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b23f: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b241: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40b24bu; native_call(m, 0x41f0e0u);	/* 40b246: call 0x41f0e0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b24b: push 0 */
	{ DWORD v_ = 0x13cu; m->esp -= 4; M32(m->esp) = v_; }	/* 40b24d: push 0x13c */
	{ DWORD v_ = 0x218u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b252: push 0x218 */
	{ DWORD v_ = 0xb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b257: push 0xb8 */
	{ DWORD v_ = 0x68u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b25c: push 0x68 */
	m->esp -= 4; M32(m->esp) = 0x40b263u; native_call(m, 0x427970u);	/* 40b25e: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b263: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b268: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b26d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b272: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b277: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40b281u; native_call(m, 0x41f0e0u);	/* 40b27c: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40b281: add esp, 0x50 */
	{ DWORD v_ = 0x74dfa4u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b284: push 0x74dfa4 */
	{ DWORD v_ = 0x21cu; m->esp -= 4; M32(m->esp) = v_; }	/* 40b289: push 0x21c */
	{ DWORD v_ = 0xc8u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b28e: push 0xc8 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b293: push 0x64 */
	m->esp -= 4; M32(m->esp) = 0x40b29au; native_call(m, 0x4029d0u);	/* 40b295: call 0x4029d0 */
	{ DWORD v_ = 0x74e024u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b29a: push 0x74e024 */
	{ DWORD v_ = 0x21cu; m->esp -= 4; M32(m->esp) = v_; }	/* 40b29f: push 0x21c */
	{ DWORD v_ = 0xdcu; m->esp -= 4; M32(m->esp) = v_; }	/* 40b2a4: push 0xdc */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b2a9: push 0x64 */
	m->esp -= 4; M32(m->esp) = 0x40b2b0u; native_call(m, 0x4029d0u);	/* 40b2ab: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40b2b0: add esp, 0x20 */
	M32((DWORD)(m->esp + 0x14u)) = 0x0u;	/* 40b2b3: mov dword ptr [esp + 0x14], 0 */
	m->esi = 0xb4u;	/* 40b2bb: mov esi, 0xb4 */
	m->ebp = 0x7517a4u;	/* 40b2c0: mov ebp, 0x7517a4 */
L_40b2c5:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b2c5: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x40b2d0u; native_call(m, M32(0x4a9224u));	/* 40b2ca: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 40b2d0: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 40b2d5: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40b2d7: and ecx, 0x800001ff */
	if (!m->sf) goto L_40b2e7;	/* 40b2dd: jns 0x40b2e7 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 40b2df: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40b2e0: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 40b2e6: inc ecx */
L_40b2e7:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 40b2e7: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 40b2e8: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b2ee: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40b2ef: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 40b2f1: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 40b2f7: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 40b2fa: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x40b303u; native_call(m, 0x4566c0u);	/* 40b2fe: call 0x4566c0 */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 40b303: mov eax, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 40b307: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40b30b: cmp ecx, eax */
	if (!m->zf) goto L_40b358;	/* 40b30d: jne 0x40b358 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b30f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b314: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b319: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b31e: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40b325u; native_call(m, m->edi);	/* 40b323: call edi */
	m->ebx = (DWORD)(m->esi + 0x78u);	/* 40b325: lea ebx, [esi + 0x78] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b328: push 1 */
	{ DWORD v_ = 0x124u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b32a: push 0x124 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b32f: push ebx */
	{ DWORD v_ = 0x104u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b330: push 0x104 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40b335: push esi */
	m->esp -= 4; M32(m->esp) = 0x40b33bu; native_call(m, 0x4282f0u);	/* 40b336: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x4dbaa4u));	/* 40b33b: mov ecx, dword ptr [0x4dbaa4] */
	m->edx = M32((DWORD)(0x4dbaa0u));	/* 40b341: mov edx, dword ptr [0x4dbaa0] */
	m->eax = M32((DWORD)(0x4dba9cu));	/* 40b347: mov eax, dword ptr [0x4dba9c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b34c: push ecx */
	m->ecx = M32((DWORD)(0x4dba98u));	/* 40b34d: mov ecx, dword ptr [0x4dba98] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b353: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40b354: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b355: push ecx */
	goto L_40b39f;	/* 40b356: jmp 0x40b39f */
L_40b358:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40b358: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b35d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b362: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b367: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40b36eu; native_call(m, m->edi);	/* 40b36c: call edi */
	m->ebx = (DWORD)(m->esi + 0x78u);	/* 40b36e: lea ebx, [esi + 0x78] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b371: push 1 */
	{ DWORD v_ = 0x124u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b373: push 0x124 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b378: push ebx */
	{ DWORD v_ = 0x104u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b379: push 0x104 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40b37e: push esi */
	m->esp -= 4; M32(m->esp) = 0x40b384u; native_call(m, 0x4282f0u);	/* 40b37f: call 0x4282f0 */
	m->edx = M32((DWORD)(0x4db8acu));	/* 40b384: mov edx, dword ptr [0x4db8ac] */
	m->eax = M32((DWORD)(0x4db8a8u));	/* 40b38a: mov eax, dword ptr [0x4db8a8] */
	m->ecx = M32((DWORD)(0x4db8a4u));	/* 40b38f: mov ecx, dword ptr [0x4db8a4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b395: push edx */
	m->edx = M32((DWORD)(0x4db8a0u));	/* 40b396: mov edx, dword ptr [0x4db8a0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40b39c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b39d: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b39e: push edx */
L_40b39f:
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b39f: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40b3a9u; native_call(m, 0x41f0e0u);	/* 40b3a4: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40b3a9: add esp, 0x28 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 40b3ac: push ebp */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b3ad: push ebx */
	{ DWORD v_ = 0x10cu; m->esp -= 4; M32(m->esp) = v_; }	/* 40b3ae: push 0x10c */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40b3b3: push esi */
	m->esp -= 4; M32(m->esp) = 0x40b3b9u; native_call(m, 0x4029d0u);	/* 40b3b4: call 0x4029d0 */
	m->ebx = M32((DWORD)(m->esp + 0x24u));	/* 40b3b9: mov ebx, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40b3bd: add esp, 0x10 */
	{ DWORD a_ = m->ebp, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 40b3c0: add ebp, 0x80 */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 40b3c6: inc ebx */
	{ DWORD a_ = m->esi, b_ = 0xa0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 40b3c7: add esi, 0xa0 */
	{ DWORD a_ = m->ebp, b_ = 0x7518a4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40b3cd: cmp ebp, 0x7518a4 */
	M32((DWORD)(m->esp + 0x14u)) = m->ebx;	/* 40b3d3: mov dword ptr [esp + 0x14], ebx */
	if (m->sf != m->of) goto L_40b2c5;	/* 40b3d7: jl 0x40b2c5 */
L_40b3dd:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b3dd: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b3e2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b3e7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b3ec: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40b3f3u; native_call(m, m->edi);	/* 40b3f1: call edi */
	m->eax = M32((DWORD)(0x4db8d4u));	/* 40b3f3: mov eax, dword ptr [0x4db8d4] */
	m->ecx = M32((DWORD)(0x4db8d0u));	/* 40b3f8: mov ecx, dword ptr [0x4db8d0] */
	m->edx = M32((DWORD)(0x4db8ccu));	/* 40b3fe: mov edx, dword ptr [0x4db8cc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40b404: push eax */
	m->eax = M32((DWORD)(0x4db8c8u));	/* 40b405: mov eax, dword ptr [0x4db8c8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b40a: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b40b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40b40c: push eax */
	m->esp -= 4; M32(m->esp) = 0x40b412u; native_call(m, 0x428a00u);	/* 40b40d: call 0x428a00 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40b412: add esp, 0x10 */
	m->edi = M32(m->esp); m->esp += 4;	/* 40b415: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 40b416: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 40b417: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 40b418: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40b419: add esp, 0x48 */
	m->esp += 4 + 0; return;	/* 40b41c: ret  */
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
