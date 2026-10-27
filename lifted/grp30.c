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

static void lift_466dc0(X86 *m);

/* shape_getByName (0x466dc0), lifted by tools/lift.py */
static void lift_466dc0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x204u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 466dc0: sub esp, 0x204 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 466dc6: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x4u);	/* 466dc8: lea edx, [esp + 4] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 466dcc: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 466dcd: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 466dce: push esi */
	m->ebp = m->ecx;	/* 466dcf: mov ebp, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 466dd1: push edi */
	m->edi = M32((DWORD)(m->esp + 0x218u));	/* 466dd2: mov edi, dword ptr [esp + 0x218] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 466dd9: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 466ddc: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 466dde: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 466de0: sub edi, ecx */
	m->eax = m->ecx;	/* 466de2: mov eax, ecx */
	m->esi = m->edi;	/* 466de4: mov esi, edi */
	m->edi = m->edx;	/* 466de6: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 466de8: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 466deb: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 466ded: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 466def: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 466df2: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 466df4: lea ecx, [esp + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 466df8: push ecx */
	m->esp -= 4; M32(m->esp) = 0x466dfeu; native_call(m, 0x46cb60u);	/* 466df9: call 0x46cb60 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + 0x18u))) & 0xff) << 0);	/* 466dfe: mov al, byte ptr [esp + 0x18] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 466e02: xor ebx, ebx */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 466e04: add esp, 4 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 466e07: cmp al, bl */
	if (m->zf) goto L_467503;	/* 466e09: je 0x467503 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x2eu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 466e0f: cmp al, 0x2e */
	if (m->zf) goto L_467503;	/* 466e11: je 0x467503 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x114u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 466e17: cmp dword ptr [ebp + 0x114], ebx */
	if (!m->zf) goto L_466e31;	/* 466e1d: jne 0x466e31 */
	{ DWORD v_ = 0x4c4d98u; m->esp -= 4; M32(m->esp) = v_; }	/* 466e1f: push 0x4c4d98 */
	{ DWORD v_ = 0xa0e788u; m->esp -= 4; M32(m->esp) = v_; }	/* 466e24: push 0xa0e788 */
	m->esp -= 4; M32(m->esp) = 0x466e2eu; native_call(m, 0x46c710u);	/* 466e29: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 466e2e: add esp, 8 */
L_466e31:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x120u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 466e31: cmp dword ptr [ebp + 0x120], ebx */
	if (!m->zf) goto L_46704b;	/* 466e37: jne 0x46704b */
	m->edi = (DWORD)(m->esp + 0x14u);	/* 466e3d: lea edi, [esp + 0x14] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 466e41: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 466e44: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 466e46: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 466e48: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 466e4a: sub edi, ecx */
	m->edx = m->ecx;	/* 466e4c: mov edx, ecx */
	m->esi = m->edi;	/* 466e4e: mov esi, edi */
	m->edi = M32((DWORD)(m->ebp + 0x118u));	/* 466e50: mov edi, dword ptr [ebp + 0x118] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 466e56: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 466e59: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 466e5b: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 466e5d: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 466e60: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->eax = M32((DWORD)(m->ebp + 0x118u));	/* 466e62: mov eax, dword ptr [ebp + 0x118] */
	M32((DWORD)(m->eax + 0x40u)) = m->ebx;	/* 466e68: mov dword ptr [eax + 0x40], ebx */
	m->ecx = M32((DWORD)(m->ebp + 0x118u));	/* 466e6b: mov ecx, dword ptr [ebp + 0x118] */
	M32((DWORD)(m->ecx + 0x44u)) = m->ebx;	/* 466e71: mov dword ptr [ecx + 0x44], ebx */
	m->edx = M32((DWORD)(m->ebp + 0x118u));	/* 466e74: mov edx, dword ptr [ebp + 0x118] */
	M32((DWORD)(m->edx + 0x48u)) = m->ebx;	/* 466e7a: mov dword ptr [edx + 0x48], ebx */
	m->eax = M32((DWORD)(m->ebp + 0x110u));	/* 466e7d: mov eax, dword ptr [ebp + 0x110] */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 466e83: cmp eax, 2 */
	if (!m->zf) goto L_466ef9;	/* 466e86: jne 0x466ef9 */
	m->ecx = M32((DWORD)(m->ebp + 0x128u));	/* 466e88: mov ecx, dword ptr [ebp + 0x128] */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 466e8e: cmp ecx, ebx */
	if (m->zf) goto L_466ed9;	/* 466e90: je 0x466ed9 */
	m->eax = M32((DWORD)(m->ebp + 0x12cu));	/* 466e92: mov eax, dword ptr [ebp + 0x12c] */
	m->edx = M32((DWORD)(m->ebp + 0x124u));	/* 466e98: mov edx, dword ptr [ebp + 0x124] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 466e9e: sub edx, eax */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 466ea0: add eax, ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 466ea2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 466ea3: push eax */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 466ea4: lea eax, [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 466ea8: push eax */
	m->esp -= 4; M32(m->esp) = 0x466eaeu; native_call(m, 0x466eaeu + M32(0x466eaau));	/* 0x466d60 unless the patch DLL retargets it */	/* 466ea9: call 0x466d60 */
	m->ecx = M32((DWORD)(m->ebp + 0x11cu));	/* 466eae: mov ecx, dword ptr [ebp + 0x11c] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 466eb4: add esp, 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 466eb7: push eax */
	m->esp -= 4; M32(m->esp) = 0x466ebdu; native_call(m, 0x466ebdu + M32(0x466eb9u));	/* 0x466120 unless the patch DLL retargets it */	/* 466eb8: call 0x466120 */
L_466ebd:
	m->ecx = M32((DWORD)(m->ebp + 0x11cu));	/* 466ebd: mov ecx, dword ptr [ebp + 0x11c] */
	m->eax = M32((DWORD)(m->ebp + 0x12cu));	/* 466ec3: mov eax, dword ptr [ebp + 0x12c] */
	m->edx = M32((DWORD)(m->ecx + 0x4u));	/* 466ec9: mov edx, dword ptr [ecx + 4] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 466ecc: add eax, edx */
	M32((DWORD)(m->ebp + 0x12cu)) = m->eax;	/* 466ece: mov dword ptr [ebp + 0x12c], eax */
	goto L_466fd4;	/* 466ed4: jmp 0x466fd4 */
L_466ed9:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 466ed9: push ebx */
	m->eax = (DWORD)(m->esp + 0x18u);	/* 466eda: lea eax, [esp + 0x18] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 466ede: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 466edf: push eax */
	m->esp -= 4; M32(m->esp) = 0x466ee5u; native_call(m, 0x466ee5u + M32(0x466ee1u));	/* 0x466d60 unless the patch DLL retargets it */	/* 466ee0: call 0x466d60 */
	m->ecx = M32((DWORD)(m->ebp + 0x11cu));	/* 466ee5: mov ecx, dword ptr [ebp + 0x11c] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 466eeb: add esp, 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 466eee: push eax */
	m->esp -= 4; M32(m->esp) = 0x466ef4u; native_call(m, 0x466ef4u + M32(0x466ef0u));	/* 0x466120 unless the patch DLL retargets it */	/* 466eef: call 0x466120 */
	goto L_466fd4;	/* 466ef4: jmp 0x466fd4 */
L_466ef9:
	m->ecx = m->eax;	/* 466ef9: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 466efb: sub ecx, ebx */
	if (m->zf) goto L_466f22;	/* 466efd: je 0x466f22 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 466eff: dec ecx */
	if (m->zf) goto L_466f17;	/* 466f00: je 0x466f17 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 466f02: push eax */
	{ DWORD v_ = 0x4c4d70u; m->esp -= 4; M32(m->esp) = v_; }	/* 466f03: push 0x4c4d70 */
	{ DWORD v_ = 0xa0e788u; m->esp -= 4; M32(m->esp) = v_; }	/* 466f08: push 0xa0e788 */
	m->esp -= 4; M32(m->esp) = 0x466f12u; native_call(m, 0x46c710u);	/* 466f0d: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 466f12: add esp, 0xc */
	goto L_466f48;	/* 466f15: jmp 0x466f48 */
L_466f17:
	m->edx = (DWORD)(m->esp + 0x10u);	/* 466f17: lea edx, [esp + 0x10] */
	m->edi = 0x4c4d6cu;	/* 466f1b: mov edi, 0x4c4d6c */
	goto L_466f2b;	/* 466f20: jmp 0x466f2b */
L_466f22:
	m->edx = (DWORD)(m->esp + 0x10u);	/* 466f22: lea edx, [esp + 0x10] */
	m->edi = 0x4c4d68u;	/* 466f26: mov edi, 0x4c4d68 */
L_466f2b:
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 466f2b: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 466f2e: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 466f30: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 466f32: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 466f34: sub edi, ecx */
	m->eax = m->ecx;	/* 466f36: mov eax, ecx */
	m->esi = m->edi;	/* 466f38: mov esi, edi */
	m->edi = m->edx;	/* 466f3a: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 466f3c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 466f3f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 466f41: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 466f43: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 466f46: rep movsb byte ptr es:[edi], byte ptr [esi] */
L_466f48:
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + 0x10u))) & 0xff) << 0);	/* 466f48: mov cl, byte ptr [ebp + 0x10] */
	m->edx = M32((DWORD)(m->ebp + 0x118u));	/* 466f4b: mov edx, dword ptr [ebp + 0x118] */
	m->eax = (DWORD)(m->ebp + 0x10u);	/* 466f51: lea eax, [ebp + 0x10] */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 466f54: cmp cl, bl */
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 466f56: lea ecx, [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 466f5a: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 466f5b: push edx */
	if (m->zf) goto L_466f76;	/* 466f5c: je 0x466f76 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 466f5e: push eax */
	m->eax = (DWORD)(m->esp + 0x120u);	/* 466f5f: lea eax, [esp + 0x120] */
	{ DWORD v_ = 0x4c4d5cu; m->esp -= 4; M32(m->esp) = v_; }	/* 466f66: push 0x4c4d5c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 466f6b: push eax */
	m->esp -= 4; M32(m->esp) = 0x466f71u; native_call(m, 0x49e9ddu);	/* 466f6c: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 466f71: add esp, 0x14 */
	goto L_466f8b;	/* 466f74: jmp 0x466f8b */
L_466f76:
	m->eax = (DWORD)(m->esp + 0x11cu);	/* 466f76: lea eax, [esp + 0x11c] */
	{ DWORD v_ = 0x4c4d54u; m->esp -= 4; M32(m->esp) = v_; }	/* 466f7d: push 0x4c4d54 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 466f82: push eax */
	m->esp -= 4; M32(m->esp) = 0x466f88u; native_call(m, 0x49e9ddu);	/* 466f83: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 466f88: add esp, 0x10 */
L_466f8b:
	m->ecx = M32((DWORD)(m->ebp + 0x128u));	/* 466f8b: mov ecx, dword ptr [ebp + 0x128] */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 466f91: cmp ecx, ebx */
	if (m->zf) goto L_466fbf;	/* 466f93: je 0x466fbf */
	m->eax = M32((DWORD)(m->ebp + 0x12cu));	/* 466f95: mov eax, dword ptr [ebp + 0x12c] */
	m->edx = M32((DWORD)(m->ebp + 0x124u));	/* 466f9b: mov edx, dword ptr [ebp + 0x124] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 466fa1: sub edx, eax */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 466fa3: add eax, ecx */
	m->ecx = M32((DWORD)(m->ebp + 0x11cu));	/* 466fa5: mov ecx, dword ptr [ebp + 0x11c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 466fab: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 466fac: push eax */
	m->eax = (DWORD)(m->esp + 0x11cu);	/* 466fad: lea eax, [esp + 0x11c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 466fb4: push eax */
	m->esp -= 4; M32(m->esp) = 0x466fbau; native_call(m, 0x464bf0u);	/* 466fb5: call 0x464bf0 */
	goto L_466ebd;	/* 466fba: jmp 0x466ebd */
L_466fbf:
	m->ecx = M32((DWORD)(m->ebp + 0x11cu));	/* 466fbf: mov ecx, dword ptr [ebp + 0x11c] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 466fc5: push ebx */
	m->eax = (DWORD)(m->esp + 0x118u);	/* 466fc6: lea eax, [esp + 0x118] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 466fcd: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 466fce: push eax */
	m->esp -= 4; M32(m->esp) = 0x466fd4u; native_call(m, 0x464bf0u);	/* 466fcf: call 0x464bf0 */
L_466fd4:
	m->ecx = M32((DWORD)(m->ebp + 0x248u));	/* 466fd4: mov ecx, dword ptr [ebp + 0x248] */
	m->edx = M32((DWORD)(m->ebp + 0x244u));	/* 466fda: mov edx, dword ptr [ebp + 0x244] */
	m->eax = M32((DWORD)(m->ebp + 0x240u));	/* 466fe0: mov eax, dword ptr [ebp + 0x240] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 466fe6: push ecx */
	m->ecx = M32((DWORD)(m->ebp + 0x23cu));	/* 466fe7: mov ecx, dword ptr [ebp + 0x23c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 466fed: push edx */
	m->edx = M32((DWORD)(m->ebp + 0x238u));	/* 466fee: mov edx, dword ptr [ebp + 0x238] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 466ff4: push eax */
	m->eax = M32((DWORD)(m->ebp + 0x234u));	/* 466ff5: mov eax, dword ptr [ebp + 0x234] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 466ffb: push ecx */
	m->ecx = M32((DWORD)(m->ebp + 0x230u));	/* 466ffc: mov ecx, dword ptr [ebp + 0x230] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 467002: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 467003: push eax */
	m->edx = (DWORD)(m->ebp + 0x130u);	/* 467004: lea edx, [ebp + 0x130] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46700a: push ecx */
	m->ecx = M32((DWORD)(m->ebp + 0x11cu));	/* 46700b: mov ecx, dword ptr [ebp + 0x11c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 467011: push edx */
	m->esp -= 4; M32(m->esp) = 0x467017u; native_call(m, 0x466430u);	/* 467012: call 0x466430 */
	m->ecx = M32((DWORD)(m->esp + 0x21cu));	/* 467017: mov ecx, dword ptr [esp + 0x21c] */
	m->eax = 0x1u;	/* 46701e: mov eax, 1 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 467023: cmp ecx, eax */
	M32((DWORD)(m->ebp + 0x120u)) = m->eax;	/* 467025: mov dword ptr [ebp + 0x120], eax */
	if (!m->zf) goto L_467038;	/* 46702b: jne 0x467038 */
	m->ecx = M32((DWORD)(m->ebp + 0x11cu));	/* 46702d: mov ecx, dword ptr [ebp + 0x11c] */
	m->esp -= 4; M32(m->esp) = 0x467038u; native_call(m, 0x466650u);	/* 467033: call 0x466650 */
L_467038:
	m->eax = M32((DWORD)(m->ebp + 0x11cu));	/* 467038: mov eax, dword ptr [ebp + 0x11c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 46703e: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46703f: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 467040: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 467041: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x204u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 467042: add esp, 0x204 */
	m->esp += 4 + 8; return;	/* 467048: ret 8 */
L_46704b:
	m->edi = M32((DWORD)(m->ebp + 0x118u));	/* 46704b: mov edi, dword ptr [ebp + 0x118] */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 467051: lea eax, [esp + 0x14] */
	m->esi = m->edi;	/* 467055: mov esi, edi */
L_467057:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 467057: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 467059: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46705b: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_46707b;	/* 46705d: jne 0x46707b */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46705f: cmp cl, bl */
	if (m->zf) goto L_467077;	/* 467061: je 0x467077 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 467063: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 467066: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 467068: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_46707b;	/* 46706b: jne 0x46707b */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46706d: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 467070: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 467073: cmp cl, bl */
	if (!m->zf) goto L_467057;	/* 467075: jne 0x467057 */
L_467077:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 467077: xor eax, eax */
	goto L_467080;	/* 467079: jmp 0x467080 */
L_46707b:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 46707b: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 46707d: sbb eax, -1 */
L_467080:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 467080: cmp eax, ebx */
	if (m->zf) goto L_4670d3;	/* 467082: je 0x4670d3 */
L_467084:
	if (m->sf == m->of) goto L_467093;	/* 467084: jge 0x467093 */
	m->eax = M32((DWORD)(m->edi + 0x44u));	/* 467086: mov eax, dword ptr [edi + 0x44] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 467089: cmp eax, ebx */
	if (m->zf) goto L_467113;	/* 46708b: je 0x467113 */
	goto L_46709e;	/* 467091: jmp 0x46709e */
L_467093:
	m->eax = M32((DWORD)(m->edi + 0x48u));	/* 467093: mov eax, dword ptr [edi + 0x48] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 467096: cmp eax, ebx */
	if (m->zf) goto L_46742e;	/* 467098: je 0x46742e */
L_46709e:
	m->edi = m->eax;	/* 46709e: mov edi, eax */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 4670a0: lea eax, [esp + 0x14] */
	m->esi = m->edi;	/* 4670a4: mov esi, edi */
L_4670a6:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 4670a6: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4670a8: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4670aa: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_4670ca;	/* 4670ac: jne 0x4670ca */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4670ae: cmp cl, bl */
	if (m->zf) goto L_4670c6;	/* 4670b0: je 0x4670c6 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 4670b2: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4670b5: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4670b7: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_4670ca;	/* 4670ba: jne 0x4670ca */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4670bc: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4670bf: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4670c2: cmp cl, bl */
	if (!m->zf) goto L_4670a6;	/* 4670c4: jne 0x4670a6 */
L_4670c6:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4670c6: xor eax, eax */
	goto L_4670cf;	/* 4670c8: jmp 0x4670cf */
L_4670ca:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4670ca: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4670cc: sbb eax, -1 */
L_4670cf:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4670cf: cmp eax, ebx */
	if (!m->zf) goto L_467084;	/* 4670d1: jne 0x467084 */
L_4670d3:
	{ DWORD a_ = M32((DWORD)(m->esp + 0x21cu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4670d3: cmp dword ptr [esp + 0x21c], 1 */
	if (!m->zf) goto L_4670f4;	/* 4670db: jne 0x4670f4 */
	m->eax = M32((DWORD)(m->edi + 0x40u));	/* 4670dd: mov eax, dword ptr [edi + 0x40] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 4670e0: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 4670e3: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->ebp + 0x11cu));	/* 4670e6: mov eax, dword ptr [ebp + 0x11c] */
	m->ecx = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 4670ec: lea ecx, [eax + edx*4] */
	m->esp -= 4; M32(m->esp) = 0x4670f4u; native_call(m, 0x466650u);	/* 4670ef: call 0x466650 */
L_4670f4:
	m->eax = M32((DWORD)(m->edi + 0x40u));	/* 4670f4: mov eax, dword ptr [edi + 0x40] */
	m->edi = M32(m->esp); m->esp += 4;	/* 4670f7: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4670f8: pop esi */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 4670f9: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 4670fc: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->ebp + 0x11cu));	/* 4670ff: mov eax, dword ptr [ebp + 0x11c] */
	m->ebp = M32(m->esp); m->esp += 4;	/* 467105: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 467106: pop ebx */
	m->eax = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 467107: lea eax, [eax + edx*4] */
	{ DWORD a_ = m->esp, b_ = 0x204u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46710a: add esp, 0x204 */
	m->esp += 4 + 8; return;	/* 467110: ret 8 */
L_467113:
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 467113: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = M32((DWORD)(m->ebp + 0x114u));	/* 467119: mov ecx, dword ptr [ebp + 0x114] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46711f: cmp eax, ecx */
	if (m->sf != m->of) goto L_467136;	/* 467121: jl 0x467136 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 467123: push eax */
	{ DWORD v_ = 0x4c4d30u; m->esp -= 4; M32(m->esp) = v_; }	/* 467124: push 0x4c4d30 */
	{ DWORD v_ = 0xa0e788u; m->esp -= 4; M32(m->esp) = v_; }	/* 467129: push 0xa0e788 */
	m->esp -= 4; M32(m->esp) = 0x467133u; native_call(m, 0x46c710u);	/* 46712e: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 467133: add esp, 0xc */
L_467136:
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 467136: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 46713c: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 46713f: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->ebp + 0x118u));	/* 467142: mov eax, dword ptr [ebp + 0x118] */
	m->ecx = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 467148: lea ecx, [eax + edx*4] */
	M32((DWORD)(m->edi + 0x44u)) = m->ecx;	/* 46714b: mov dword ptr [edi + 0x44], ecx */
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 46714e: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = M32((DWORD)(m->ebp + 0x118u));	/* 467154: mov ecx, dword ptr [ebp + 0x118] */
	m->edi = (DWORD)(m->esp + 0x14u);	/* 46715a: lea edi, [esp + 0x14] */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 46715e: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 467161: lea eax, [eax + edx*2] */
	m->edx = (DWORD)(m->ecx + m->eax*4 + 0x0u);	/* 467164: lea edx, [ecx + eax*4] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 467167: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46716a: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 46716c: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 46716e: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 467170: sub edi, ecx */
	m->eax = m->ecx;	/* 467172: mov eax, ecx */
	m->esi = m->edi;	/* 467174: mov esi, edi */
	m->edi = m->edx;	/* 467176: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 467178: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 46717b: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 46717d: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46717f: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 467182: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 467184: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 46718a: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 46718d: lea edx, [eax + ecx*2] */
	m->ecx = M32((DWORD)(m->ebp + 0x118u));	/* 467190: mov ecx, dword ptr [ebp + 0x118] */
	M32((DWORD)(m->ecx + m->edx*4 + 0x40u)) = m->eax;	/* 467196: mov dword ptr [ecx + edx*4 + 0x40], eax */
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 46719a: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = M32((DWORD)(m->ebp + 0x118u));	/* 4671a0: mov ecx, dword ptr [ebp + 0x118] */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 4671a6: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 4671a9: lea eax, [eax + edx*2] */
	M32((DWORD)(m->ecx + m->eax*4 + 0x44u)) = m->ebx;	/* 4671ac: mov dword ptr [ecx + eax*4 + 0x44], ebx */
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 4671b0: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = M32((DWORD)(m->ebp + 0x118u));	/* 4671b6: mov ecx, dword ptr [ebp + 0x118] */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 4671bc: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 4671bf: lea eax, [eax + edx*2] */
	M32((DWORD)(m->ecx + m->eax*4 + 0x48u)) = m->ebx;	/* 4671c2: mov dword ptr [ecx + eax*4 + 0x48], ebx */
	m->eax = M32((DWORD)(m->ebp + 0x110u));	/* 4671c6: mov eax, dword ptr [ebp + 0x110] */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4671cc: cmp eax, 2 */
	if (!m->zf) goto L_467271;	/* 4671cf: jne 0x467271 */
	m->ecx = M32((DWORD)(m->ebp + 0x128u));	/* 4671d5: mov ecx, dword ptr [ebp + 0x128] */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4671db: cmp ecx, ebx */
	if (m->zf) goto L_467242;	/* 4671dd: je 0x467242 */
L_4671df:
	m->eax = M32((DWORD)(m->ebp + 0x12cu));	/* 4671df: mov eax, dword ptr [ebp + 0x12c] */
	m->edx = M32((DWORD)(m->ebp + 0x124u));	/* 4671e5: mov edx, dword ptr [ebp + 0x124] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4671eb: sub edx, eax */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4671ed: add eax, ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4671ef: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4671f0: push eax */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 4671f1: lea eax, [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4671f5: push eax */
	m->esp -= 4; M32(m->esp) = 0x4671fbu; native_call(m, 0x4671fbu + M32(0x4671f7u));	/* 0x466d60 unless the patch DLL retargets it */	/* 4671f6: call 0x466d60 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4671fb: add esp, 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4671fe: push eax */
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 4671ff: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 467205: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 467208: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->ebp + 0x11cu));	/* 46720b: mov eax, dword ptr [ebp + 0x11c] */
	m->ecx = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 467211: lea ecx, [eax + edx*4] */
	m->esp -= 4; M32(m->esp) = 0x467219u; native_call(m, 0x467219u + M32(0x467215u));	/* 0x466120 unless the patch DLL retargets it */	/* 467214: call 0x466120 */
L_467219:
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 467219: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 46721f: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 467222: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->ebp + 0x11cu));	/* 467225: mov eax, dword ptr [ebp + 0x11c] */
	m->ecx = M32((DWORD)(m->eax + m->edx*4 + 0x4u));	/* 46722b: mov ecx, dword ptr [eax + edx*4 + 4] */
	m->eax = M32((DWORD)(m->ebp + 0x12cu));	/* 46722f: mov eax, dword ptr [ebp + 0x12c] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 467235: add eax, ecx */
	M32((DWORD)(m->ebp + 0x12cu)) = m->eax;	/* 467237: mov dword ptr [ebp + 0x12c], eax */
	goto L_467389;	/* 46723d: jmp 0x467389 */
L_467242:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 467242: push ebx */
	m->edx = (DWORD)(m->esp + 0x18u);	/* 467243: lea edx, [esp + 0x18] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 467247: push ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 467248: push edx */
	m->esp -= 4; M32(m->esp) = 0x46724eu; native_call(m, 0x46724eu + M32(0x46724au));	/* 0x466d60 unless the patch DLL retargets it */	/* 467249: call 0x466d60 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46724e: add esp, 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 467251: push eax */
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 467252: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 467258: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 46725b: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->ebp + 0x11cu));	/* 46725e: mov eax, dword ptr [ebp + 0x11c] */
	m->ecx = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 467264: lea ecx, [eax + edx*4] */
	m->esp -= 4; M32(m->esp) = 0x46726cu; native_call(m, 0x46726cu + M32(0x467268u));	/* 0x466120 unless the patch DLL retargets it */	/* 467267: call 0x466120 */
	goto L_467389;	/* 46726c: jmp 0x467389 */
L_467271:
	m->ecx = m->eax;	/* 467271: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 467273: sub ecx, ebx */
	if (m->zf) goto L_46729a;	/* 467275: je 0x46729a */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 467277: dec ecx */
	if (m->zf) goto L_46728f;	/* 467278: je 0x46728f */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46727a: push eax */
	{ DWORD v_ = 0x4c4d70u; m->esp -= 4; M32(m->esp) = v_; }	/* 46727b: push 0x4c4d70 */
	{ DWORD v_ = 0xa0e788u; m->esp -= 4; M32(m->esp) = v_; }	/* 467280: push 0xa0e788 */
	m->esp -= 4; M32(m->esp) = 0x46728au; native_call(m, 0x46c710u);	/* 467285: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46728a: add esp, 0xc */
	goto L_4672c0;	/* 46728d: jmp 0x4672c0 */
L_46728f:
	m->edx = (DWORD)(m->esp + 0x10u);	/* 46728f: lea edx, [esp + 0x10] */
	m->edi = 0x4c4d6cu;	/* 467293: mov edi, 0x4c4d6c */
	goto L_4672a3;	/* 467298: jmp 0x4672a3 */
L_46729a:
	m->edx = (DWORD)(m->esp + 0x10u);	/* 46729a: lea edx, [esp + 0x10] */
	m->edi = 0x4c4d68u;	/* 46729e: mov edi, 0x4c4d68 */
L_4672a3:
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4672a3: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4672a6: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4672a8: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4672aa: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4672ac: sub edi, ecx */
	m->eax = m->ecx;	/* 4672ae: mov eax, ecx */
	m->esi = m->edi;	/* 4672b0: mov esi, edi */
	m->edi = m->edx;	/* 4672b2: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4672b4: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4672b7: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4672b9: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4672bb: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4672be: rep movsb byte ptr es:[edi], byte ptr [esi] */
L_4672c0:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + 0x10u))) & 0xff) << 0);	/* 4672c0: mov al, byte ptr [ebp + 0x10] */
	m->ecx = (DWORD)(m->ebp + 0x10u);	/* 4672c3: lea ecx, [ebp + 0x10] */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 4672c6: lea edx, [esp + 0x10] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4672ca: cmp al, bl */
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 4672cc: mov eax, dword ptr [ebp + 0x120] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4672d2: push edx */
	if (m->zf) goto L_4672fd;	/* 4672d3: je 0x4672fd */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 4672d5: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 4672d8: lea eax, [eax + edx*2] */
	m->edx = M32((DWORD)(m->ebp + 0x118u));	/* 4672db: mov edx, dword ptr [ebp + 0x118] */
	m->eax = (DWORD)(m->edx + m->eax*4 + 0x0u);	/* 4672e1: lea eax, [edx + eax*4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4672e4: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4672e5: push ecx */
	m->ecx = (DWORD)(m->esp + 0x120u);	/* 4672e6: lea ecx, [esp + 0x120] */
	{ DWORD v_ = 0x4c4d5cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4672ed: push 0x4c4d5c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4672f2: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4672f8u; native_call(m, 0x49e9ddu);	/* 4672f3: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4672f8: add esp, 0x14 */
	goto L_467322;	/* 4672fb: jmp 0x467322 */
L_4672fd:
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 4672fd: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 467300: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->ebp + 0x118u));	/* 467303: mov eax, dword ptr [ebp + 0x118] */
	m->ecx = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 467309: lea ecx, [eax + edx*4] */
	m->edx = (DWORD)(m->esp + 0x118u);	/* 46730c: lea edx, [esp + 0x118] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 467313: push ecx */
	{ DWORD v_ = 0x4c4d54u; m->esp -= 4; M32(m->esp) = v_; }	/* 467314: push 0x4c4d54 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 467319: push edx */
	m->esp -= 4; M32(m->esp) = 0x46731fu; native_call(m, 0x49e9ddu);	/* 46731a: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46731f: add esp, 0x10 */
L_467322:
	m->ecx = M32((DWORD)(m->ebp + 0x128u));	/* 467322: mov ecx, dword ptr [ebp + 0x128] */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 467328: cmp ecx, ebx */
	if (m->zf) goto L_467365;	/* 46732a: je 0x467365 */
	m->eax = M32((DWORD)(m->ebp + 0x12cu));	/* 46732c: mov eax, dword ptr [ebp + 0x12c] */
	m->edx = M32((DWORD)(m->ebp + 0x124u));	/* 467332: mov edx, dword ptr [ebp + 0x124] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 467338: sub edx, eax */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46733a: add eax, ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46733c: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46733d: push eax */
	m->eax = (DWORD)(m->esp + 0x11cu);	/* 46733e: lea eax, [esp + 0x11c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 467345: push eax */
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 467346: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 46734c: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 46734f: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->ebp + 0x11cu));	/* 467352: mov eax, dword ptr [ebp + 0x11c] */
	m->ecx = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 467358: lea ecx, [eax + edx*4] */
	m->esp -= 4; M32(m->esp) = 0x467360u; native_call(m, 0x464bf0u);	/* 46735b: call 0x464bf0 */
	goto L_467219;	/* 467360: jmp 0x467219 */
L_467365:
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 467365: mov eax, dword ptr [ebp + 0x120] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46736b: push ebx */
	m->edx = (DWORD)(m->esp + 0x118u);	/* 46736c: lea edx, [esp + 0x118] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 467373: push ebx */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 467374: lea ecx, [eax + eax*8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 467377: push edx */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 467378: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->ebp + 0x11cu));	/* 46737b: mov eax, dword ptr [ebp + 0x11c] */
	m->ecx = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 467381: lea ecx, [eax + edx*4] */
	m->esp -= 4; M32(m->esp) = 0x467389u; native_call(m, 0x464bf0u);	/* 467384: call 0x464bf0 */
L_467389:
	m->ecx = M32((DWORD)(m->ebp + 0x248u));	/* 467389: mov ecx, dword ptr [ebp + 0x248] */
	m->edx = M32((DWORD)(m->ebp + 0x244u));	/* 46738f: mov edx, dword ptr [ebp + 0x244] */
	m->eax = M32((DWORD)(m->ebp + 0x240u));	/* 467395: mov eax, dword ptr [ebp + 0x240] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46739b: push ecx */
	m->ecx = M32((DWORD)(m->ebp + 0x23cu));	/* 46739c: mov ecx, dword ptr [ebp + 0x23c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4673a2: push edx */
	m->edx = M32((DWORD)(m->ebp + 0x238u));	/* 4673a3: mov edx, dword ptr [ebp + 0x238] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4673a9: push eax */
	m->eax = M32((DWORD)(m->ebp + 0x234u));	/* 4673aa: mov eax, dword ptr [ebp + 0x234] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4673b0: push ecx */
	m->ecx = M32((DWORD)(m->ebp + 0x230u));	/* 4673b1: mov ecx, dword ptr [ebp + 0x230] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4673b7: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4673b8: push eax */
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 4673b9: mov eax, dword ptr [ebp + 0x120] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4673bf: push ecx */
	m->edx = (DWORD)(m->ebp + 0x130u);	/* 4673c0: lea edx, [ebp + 0x130] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 4673c6: lea ecx, [eax + eax*8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4673c9: push edx */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 4673ca: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->ebp + 0x11cu));	/* 4673cd: mov eax, dword ptr [ebp + 0x11c] */
	m->ecx = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 4673d3: lea ecx, [eax + edx*4] */
	m->esp -= 4; M32(m->esp) = 0x4673dbu; native_call(m, 0x466430u);	/* 4673d6: call 0x466430 */
	m->edx = M32((DWORD)(m->ebp + 0x120u));	/* 4673db: mov edx, dword ptr [ebp + 0x120] */
	m->ecx = M32((DWORD)(m->esp + 0x21cu));	/* 4673e1: mov ecx, dword ptr [esp + 0x21c] */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 4673e8: inc edx */
	{ DWORD a_ = m->ecx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4673e9: cmp ecx, 1 */
	M32((DWORD)(m->ebp + 0x120u)) = m->edx;	/* 4673ec: mov dword ptr [ebp + 0x120], edx */
	m->eax = m->edx;	/* 4673f2: mov eax, edx */
	if (!m->zf) goto L_46740b;	/* 4673f4: jne 0x46740b */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 4673f6: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 4673f9: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->ebp + 0x11cu));	/* 4673fc: mov eax, dword ptr [ebp + 0x11c] */
	m->ecx = (DWORD)(m->eax + m->edx*4 + 0xffffffb4u);	/* 467402: lea ecx, [eax + edx*4 - 0x4c] */
	m->esp -= 4; M32(m->esp) = 0x46740bu; native_call(m, 0x466650u);	/* 467406: call 0x466650 */
L_46740b:
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 46740b: mov eax, dword ptr [ebp + 0x120] */
	m->edi = M32(m->esp); m->esp += 4;	/* 467411: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 467412: pop esi */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 467413: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 467416: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->ebp + 0x11cu));	/* 467419: mov eax, dword ptr [ebp + 0x11c] */
	m->ebp = M32(m->esp); m->esp += 4;	/* 46741f: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 467420: pop ebx */
	m->eax = (DWORD)(m->eax + m->edx*4 + 0xffffffb4u);	/* 467421: lea eax, [eax + edx*4 - 0x4c] */
	{ DWORD a_ = m->esp, b_ = 0x204u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 467425: add esp, 0x204 */
	m->esp += 4 + 8; return;	/* 46742b: ret 8 */
L_46742e:
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 46742e: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = M32((DWORD)(m->ebp + 0x114u));	/* 467434: mov ecx, dword ptr [ebp + 0x114] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46743a: cmp eax, ecx */
	if (m->sf != m->of) goto L_467451;	/* 46743c: jl 0x467451 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46743e: push eax */
	{ DWORD v_ = 0x4c4d30u; m->esp -= 4; M32(m->esp) = v_; }	/* 46743f: push 0x4c4d30 */
	{ DWORD v_ = 0xa0e788u; m->esp -= 4; M32(m->esp) = v_; }	/* 467444: push 0xa0e788 */
	m->esp -= 4; M32(m->esp) = 0x46744eu; native_call(m, 0x46c710u);	/* 467449: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46744e: add esp, 0xc */
L_467451:
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 467451: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 467457: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 46745a: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->ebp + 0x118u));	/* 46745d: mov eax, dword ptr [ebp + 0x118] */
	m->ecx = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 467463: lea ecx, [eax + edx*4] */
	M32((DWORD)(m->edi + 0x48u)) = m->ecx;	/* 467466: mov dword ptr [edi + 0x48], ecx */
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 467469: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = M32((DWORD)(m->ebp + 0x118u));	/* 46746f: mov ecx, dword ptr [ebp + 0x118] */
	m->edi = (DWORD)(m->esp + 0x14u);	/* 467475: lea edi, [esp + 0x14] */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 467479: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 46747c: lea eax, [eax + edx*2] */
	m->edx = (DWORD)(m->ecx + m->eax*4 + 0x0u);	/* 46747f: lea edx, [ecx + eax*4] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 467482: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 467485: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 467487: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 467489: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46748b: sub edi, ecx */
	m->eax = m->ecx;	/* 46748d: mov eax, ecx */
	m->esi = m->edi;	/* 46748f: mov esi, edi */
	m->edi = m->edx;	/* 467491: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 467493: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 467496: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 467498: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46749a: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 46749d: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 46749f: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 4674a5: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 4674a8: lea edx, [eax + ecx*2] */
	m->ecx = M32((DWORD)(m->ebp + 0x118u));	/* 4674ab: mov ecx, dword ptr [ebp + 0x118] */
	M32((DWORD)(m->ecx + m->edx*4 + 0x40u)) = m->eax;	/* 4674b1: mov dword ptr [ecx + edx*4 + 0x40], eax */
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 4674b5: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = M32((DWORD)(m->ebp + 0x118u));	/* 4674bb: mov ecx, dword ptr [ebp + 0x118] */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 4674c1: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 4674c4: lea eax, [eax + edx*2] */
	M32((DWORD)(m->ecx + m->eax*4 + 0x44u)) = m->ebx;	/* 4674c7: mov dword ptr [ecx + eax*4 + 0x44], ebx */
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 4674cb: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = M32((DWORD)(m->ebp + 0x118u));	/* 4674d1: mov ecx, dword ptr [ebp + 0x118] */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 4674d7: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 4674da: lea eax, [eax + edx*2] */
	M32((DWORD)(m->ecx + m->eax*4 + 0x48u)) = m->ebx;	/* 4674dd: mov dword ptr [ecx + eax*4 + 0x48], ebx */
	m->eax = M32((DWORD)(m->ebp + 0x110u));	/* 4674e1: mov eax, dword ptr [ebp + 0x110] */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4674e7: cmp eax, 2 */
	if (!m->zf) goto L_467271;	/* 4674ea: jne 0x467271 */
	m->ecx = M32((DWORD)(m->ebp + 0x128u));	/* 4674f0: mov ecx, dword ptr [ebp + 0x128] */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4674f6: cmp ecx, ebx */
	if (m->zf) goto L_467242;	/* 4674f8: je 0x467242 */
	goto L_4671df;	/* 4674fe: jmp 0x4671df */
L_467503:
	m->edi = M32(m->esp); m->esp += 4;	/* 467503: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 467504: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 467505: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 467506: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 467508: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x204u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 467509: add esp, 0x204 */
	m->esp += 4 + 8; return;	/* 46750f: ret 8 */
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
