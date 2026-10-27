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

static void lift_46b1a0(X86 *m);

/* skel_getSkeletonPtrBy (0x46b1a0), lifted by tools/lift.py */
static void lift_46b1a0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x204u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b1a0: sub esp, 0x204 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46b1a6: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x4u);	/* 46b1a8: lea edx, [esp + 4] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46b1ac: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46b1ad: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46b1ae: push esi */
	m->ebp = m->ecx;	/* 46b1af: mov ebp, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46b1b1: push edi */
	m->edi = M32((DWORD)(m->esp + 0x218u));	/* 46b1b2: mov edi, dword ptr [esp + 0x218] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46b1b9: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 46b1bc: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 46b1be: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46b1c0: sub edi, ecx */
	m->eax = m->ecx;	/* 46b1c2: mov eax, ecx */
	m->esi = m->edi;	/* 46b1c4: mov esi, edi */
	m->edi = m->edx;	/* 46b1c6: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46b1c8: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 46b1cb: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 46b1cd: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46b1cf: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 46b1d2: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 46b1d4: lea ecx, [esp + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46b1d8: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46b1deu; native_call(m, 0x46cb60u);	/* 46b1d9: call 0x46cb60 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + 0x18u))) & 0xff) << 0);	/* 46b1de: mov al, byte ptr [esp + 0x18] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 46b1e2: xor ebx, ebx */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b1e4: add esp, 4 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46b1e7: cmp al, bl */
	if (m->zf) goto L_46b7d4;	/* 46b1e9: je 0x46b7d4 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x2eu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46b1ef: cmp al, 0x2e */
	if (m->zf) goto L_46b7d4;	/* 46b1f1: je 0x46b7d4 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x114u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46b1f7: cmp dword ptr [ebp + 0x114], ebx */
	if (!m->zf) goto L_46b211;	/* 46b1fd: jne 0x46b211 */
	{ DWORD v_ = 0x4c5528u; m->esp -= 4; M32(m->esp) = v_; }	/* 46b1ff: push 0x4c5528 */
	{ DWORD v_ = 0xa0eaa0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46b204: push 0xa0eaa0 */
	m->esp -= 4; M32(m->esp) = 0x46b20eu; native_call(m, 0x46c710u);	/* 46b209: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b20e: add esp, 8 */
L_46b211:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x120u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46b211: cmp dword ptr [ebp + 0x120], ebx */
	if (!m->zf) goto L_46b3d1;	/* 46b217: jne 0x46b3d1 */
	m->edi = (DWORD)(m->esp + 0x14u);	/* 46b21d: lea edi, [esp + 0x14] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46b221: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46b224: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 46b226: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 46b228: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46b22a: sub edi, ecx */
	m->edx = m->ecx;	/* 46b22c: mov edx, ecx */
	m->esi = m->edi;	/* 46b22e: mov esi, edi */
	m->edi = M32((DWORD)(m->ebp + 0x118u));	/* 46b230: mov edi, dword ptr [ebp + 0x118] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46b236: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 46b239: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 46b23b: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46b23d: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 46b240: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->eax = M32((DWORD)(m->ebp + 0x118u));	/* 46b242: mov eax, dword ptr [ebp + 0x118] */
	M32((DWORD)(m->eax + 0x40u)) = m->ebx;	/* 46b248: mov dword ptr [eax + 0x40], ebx */
	m->ecx = M32((DWORD)(m->ebp + 0x118u));	/* 46b24b: mov ecx, dword ptr [ebp + 0x118] */
	M32((DWORD)(m->ecx + 0x44u)) = m->ebx;	/* 46b251: mov dword ptr [ecx + 0x44], ebx */
	m->edx = M32((DWORD)(m->ebp + 0x118u));	/* 46b254: mov edx, dword ptr [ebp + 0x118] */
	M32((DWORD)(m->edx + 0x48u)) = m->ebx;	/* 46b25a: mov dword ptr [edx + 0x48], ebx */
	m->eax = M32((DWORD)(m->ebp + 0x110u));	/* 46b25d: mov eax, dword ptr [ebp + 0x110] */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46b263: cmp eax, 2 */
	if (!m->zf) goto L_46b2d9;	/* 46b266: jne 0x46b2d9 */
	m->ecx = M32((DWORD)(m->ebp + 0x128u));	/* 46b268: mov ecx, dword ptr [ebp + 0x128] */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46b26e: cmp ecx, ebx */
	if (m->zf) goto L_46b2b9;	/* 46b270: je 0x46b2b9 */
	m->eax = M32((DWORD)(m->ebp + 0x12cu));	/* 46b272: mov eax, dword ptr [ebp + 0x12c] */
	m->edx = M32((DWORD)(m->ebp + 0x124u));	/* 46b278: mov edx, dword ptr [ebp + 0x124] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46b27e: sub edx, eax */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46b280: add eax, ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46b282: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46b283: push eax */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 46b284: lea eax, [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46b288: push eax */
	m->esp -= 4; M32(m->esp) = 0x46b28eu; native_call(m, 0x46b140u);	/* 46b289: call 0x46b140 */
	m->ecx = M32((DWORD)(m->ebp + 0x11cu));	/* 46b28e: mov ecx, dword ptr [ebp + 0x11c] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b294: add esp, 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46b297: push eax */
	m->esp -= 4; M32(m->esp) = 0x46b29du; native_call(m, 0x46aa10u);	/* 46b298: call 0x46aa10 */
L_46b29d:
	m->ecx = M32((DWORD)(m->ebp + 0x11cu));	/* 46b29d: mov ecx, dword ptr [ebp + 0x11c] */
	m->eax = M32((DWORD)(m->ebp + 0x12cu));	/* 46b2a3: mov eax, dword ptr [ebp + 0x12c] */
	m->edx = M32((DWORD)(m->ecx + 0x4u));	/* 46b2a9: mov edx, dword ptr [ecx + 4] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46b2ac: add eax, edx */
	M32((DWORD)(m->ebp + 0x12cu)) = m->eax;	/* 46b2ae: mov dword ptr [ebp + 0x12c], eax */
	goto L_46b3b4;	/* 46b2b4: jmp 0x46b3b4 */
L_46b2b9:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46b2b9: push ebx */
	m->eax = (DWORD)(m->esp + 0x18u);	/* 46b2ba: lea eax, [esp + 0x18] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46b2be: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46b2bf: push eax */
	m->esp -= 4; M32(m->esp) = 0x46b2c5u; native_call(m, 0x46b140u);	/* 46b2c0: call 0x46b140 */
	m->ecx = M32((DWORD)(m->ebp + 0x11cu));	/* 46b2c5: mov ecx, dword ptr [ebp + 0x11c] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b2cb: add esp, 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46b2ce: push eax */
	m->esp -= 4; M32(m->esp) = 0x46b2d4u; native_call(m, 0x46aa10u);	/* 46b2cf: call 0x46aa10 */
	goto L_46b3b4;	/* 46b2d4: jmp 0x46b3b4 */
L_46b2d9:
	m->ecx = m->eax;	/* 46b2d9: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46b2db: sub ecx, ebx */
	if (m->zf) goto L_46b302;	/* 46b2dd: je 0x46b302 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 46b2df: dec ecx */
	if (m->zf) goto L_46b2f7;	/* 46b2e0: je 0x46b2f7 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46b2e2: push eax */
	{ DWORD v_ = 0x4c54fcu; m->esp -= 4; M32(m->esp) = v_; }	/* 46b2e3: push 0x4c54fc */
	{ DWORD v_ = 0xa0eaa0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46b2e8: push 0xa0eaa0 */
	m->esp -= 4; M32(m->esp) = 0x46b2f2u; native_call(m, 0x46c710u);	/* 46b2ed: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b2f2: add esp, 0xc */
	goto L_46b328;	/* 46b2f5: jmp 0x46b328 */
L_46b2f7:
	m->edx = (DWORD)(m->esp + 0x10u);	/* 46b2f7: lea edx, [esp + 0x10] */
	m->edi = 0x4c54f8u;	/* 46b2fb: mov edi, 0x4c54f8 */
	goto L_46b30b;	/* 46b300: jmp 0x46b30b */
L_46b302:
	m->edx = (DWORD)(m->esp + 0x10u);	/* 46b302: lea edx, [esp + 0x10] */
	m->edi = 0x4c54f4u;	/* 46b306: mov edi, 0x4c54f4 */
L_46b30b:
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46b30b: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46b30e: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 46b310: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 46b312: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46b314: sub edi, ecx */
	m->eax = m->ecx;	/* 46b316: mov eax, ecx */
	m->esi = m->edi;	/* 46b318: mov esi, edi */
	m->edi = m->edx;	/* 46b31a: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46b31c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 46b31f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 46b321: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46b323: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 46b326: rep movsb byte ptr es:[edi], byte ptr [esi] */
L_46b328:
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + 0x10u))) & 0xff) << 0);	/* 46b328: mov cl, byte ptr [ebp + 0x10] */
	m->edx = M32((DWORD)(m->ebp + 0x118u));	/* 46b32b: mov edx, dword ptr [ebp + 0x118] */
	m->eax = (DWORD)(m->ebp + 0x10u);	/* 46b331: lea eax, [ebp + 0x10] */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46b334: cmp cl, bl */
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 46b336: lea ecx, [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46b33a: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46b33b: push edx */
	if (m->zf) goto L_46b356;	/* 46b33c: je 0x46b356 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46b33e: push eax */
	m->eax = (DWORD)(m->esp + 0x120u);	/* 46b33f: lea eax, [esp + 0x120] */
	{ DWORD v_ = 0x4c4d5cu; m->esp -= 4; M32(m->esp) = v_; }	/* 46b346: push 0x4c4d5c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46b34b: push eax */
	m->esp -= 4; M32(m->esp) = 0x46b351u; native_call(m, 0x49e9ddu);	/* 46b34c: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b351: add esp, 0x14 */
	goto L_46b36b;	/* 46b354: jmp 0x46b36b */
L_46b356:
	m->eax = (DWORD)(m->esp + 0x11cu);	/* 46b356: lea eax, [esp + 0x11c] */
	{ DWORD v_ = 0x4c4d54u; m->esp -= 4; M32(m->esp) = v_; }	/* 46b35d: push 0x4c4d54 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46b362: push eax */
	m->esp -= 4; M32(m->esp) = 0x46b368u; native_call(m, 0x49e9ddu);	/* 46b363: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b368: add esp, 0x10 */
L_46b36b:
	m->ecx = M32((DWORD)(m->ebp + 0x128u));	/* 46b36b: mov ecx, dword ptr [ebp + 0x128] */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46b371: cmp ecx, ebx */
	if (m->zf) goto L_46b39f;	/* 46b373: je 0x46b39f */
	m->eax = M32((DWORD)(m->ebp + 0x12cu));	/* 46b375: mov eax, dword ptr [ebp + 0x12c] */
	m->edx = M32((DWORD)(m->ebp + 0x124u));	/* 46b37b: mov edx, dword ptr [ebp + 0x124] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46b381: sub edx, eax */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46b383: add eax, ecx */
	m->ecx = M32((DWORD)(m->ebp + 0x11cu));	/* 46b385: mov ecx, dword ptr [ebp + 0x11c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46b38b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46b38c: push eax */
	m->eax = (DWORD)(m->esp + 0x11cu);	/* 46b38d: lea eax, [esp + 0x11c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46b394: push eax */
	m->esp -= 4; M32(m->esp) = 0x46b39au; native_call(m, 0x4699d0u);	/* 46b395: call 0x4699d0 */
	goto L_46b29d;	/* 46b39a: jmp 0x46b29d */
L_46b39f:
	m->ecx = M32((DWORD)(m->ebp + 0x11cu));	/* 46b39f: mov ecx, dword ptr [ebp + 0x11c] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46b3a5: push ebx */
	m->eax = (DWORD)(m->esp + 0x118u);	/* 46b3a6: lea eax, [esp + 0x118] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46b3ad: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46b3ae: push eax */
	m->esp -= 4; M32(m->esp) = 0x46b3b4u; native_call(m, 0x4699d0u);	/* 46b3af: call 0x4699d0 */
L_46b3b4:
	m->eax = M32((DWORD)(m->ebp + 0x11cu));	/* 46b3b4: mov eax, dword ptr [ebp + 0x11c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 46b3ba: pop edi */
	M32((DWORD)(m->ebp + 0x120u)) = 0x1u;	/* 46b3bb: mov dword ptr [ebp + 0x120], 1 */
	m->esi = M32(m->esp); m->esp += 4;	/* 46b3c5: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 46b3c6: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 46b3c7: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x204u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b3c8: add esp, 0x204 */
	m->esp += 4 + 4; return;	/* 46b3ce: ret 4 */
L_46b3d1:
	m->edi = M32((DWORD)(m->ebp + 0x118u));	/* 46b3d1: mov edi, dword ptr [ebp + 0x118] */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 46b3d7: lea eax, [esp + 0x14] */
	m->esi = m->edi;	/* 46b3db: mov esi, edi */
L_46b3dd:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 46b3dd: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 46b3df: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46b3e1: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_46b401;	/* 46b3e3: jne 0x46b401 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46b3e5: cmp cl, bl */
	if (m->zf) goto L_46b3fd;	/* 46b3e7: je 0x46b3fd */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 46b3e9: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 46b3ec: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46b3ee: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_46b401;	/* 46b3f1: jne 0x46b401 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46b3f3: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46b3f6: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46b3f9: cmp cl, bl */
	if (!m->zf) goto L_46b3dd;	/* 46b3fb: jne 0x46b3dd */
L_46b3fd:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46b3fd: xor eax, eax */
	goto L_46b406;	/* 46b3ff: jmp 0x46b406 */
L_46b401:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 46b401: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 46b403: sbb eax, -1 */
L_46b406:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46b406: cmp eax, ebx */
	if (m->zf) goto L_46b455;	/* 46b408: je 0x46b455 */
L_46b40a:
	if (m->sf == m->of) goto L_46b415;	/* 46b40a: jge 0x46b415 */
	m->eax = M32((DWORD)(m->edi + 0x44u));	/* 46b40c: mov eax, dword ptr [edi + 0x44] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46b40f: cmp eax, ebx */
	if (m->zf) goto L_46b471;	/* 46b411: je 0x46b471 */
	goto L_46b420;	/* 46b413: jmp 0x46b420 */
L_46b415:
	m->eax = M32((DWORD)(m->edi + 0x48u));	/* 46b415: mov eax, dword ptr [edi + 0x48] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46b418: cmp eax, ebx */
	if (m->zf) goto L_46b6ff;	/* 46b41a: je 0x46b6ff */
L_46b420:
	m->edi = m->eax;	/* 46b420: mov edi, eax */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 46b422: lea eax, [esp + 0x14] */
	m->esi = m->edi;	/* 46b426: mov esi, edi */
L_46b428:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 46b428: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 46b42a: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46b42c: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_46b44c;	/* 46b42e: jne 0x46b44c */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46b430: cmp cl, bl */
	if (m->zf) goto L_46b448;	/* 46b432: je 0x46b448 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 46b434: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 46b437: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46b439: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_46b44c;	/* 46b43c: jne 0x46b44c */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46b43e: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46b441: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46b444: cmp cl, bl */
	if (!m->zf) goto L_46b428;	/* 46b446: jne 0x46b428 */
L_46b448:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46b448: xor eax, eax */
	goto L_46b451;	/* 46b44a: jmp 0x46b451 */
L_46b44c:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 46b44c: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 46b44e: sbb eax, -1 */
L_46b451:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46b451: cmp eax, ebx */
	if (!m->zf) goto L_46b40a;	/* 46b453: jne 0x46b40a */
L_46b455:
	m->eax = M32((DWORD)(m->edi + 0x40u));	/* 46b455: mov eax, dword ptr [edi + 0x40] */
	m->ecx = M32((DWORD)(m->ebp + 0x11cu));	/* 46b458: mov ecx, dword ptr [ebp + 0x11c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 46b45e: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46b45f: pop esi */
	m->eax = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 46b460: lea eax, [eax + eax*8] */
	m->ebp = M32(m->esp); m->esp += 4;	/* 46b463: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 46b464: pop ebx */
	m->eax = (DWORD)(m->ecx + m->eax*4 + 0x0u);	/* 46b465: lea eax, [ecx + eax*4] */
	{ DWORD a_ = m->esp, b_ = 0x204u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b468: add esp, 0x204 */
	m->esp += 4 + 4; return;	/* 46b46e: ret 4 */
L_46b471:
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 46b471: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = M32((DWORD)(m->ebp + 0x114u));	/* 46b477: mov ecx, dword ptr [ebp + 0x114] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46b47d: cmp eax, ecx */
	if (m->sf != m->of) goto L_46b494;	/* 46b47f: jl 0x46b494 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46b481: push eax */
	{ DWORD v_ = 0x4c54c8u; m->esp -= 4; M32(m->esp) = v_; }	/* 46b482: push 0x4c54c8 */
	{ DWORD v_ = 0xa0eaa0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46b487: push 0xa0eaa0 */
	m->esp -= 4; M32(m->esp) = 0x46b491u; native_call(m, 0x46c710u);	/* 46b48c: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b491: add esp, 0xc */
L_46b494:
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 46b494: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = M32((DWORD)(m->ebp + 0x118u));	/* 46b49a: mov ecx, dword ptr [ebp + 0x118] */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 46b4a0: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 46b4a3: lea eax, [eax + edx*2] */
	m->edx = (DWORD)(m->ecx + m->eax*4 + 0x0u);	/* 46b4a6: lea edx, [ecx + eax*4] */
	M32((DWORD)(m->edi + 0x44u)) = m->edx;	/* 46b4a9: mov dword ptr [edi + 0x44], edx */
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 46b4ac: mov eax, dword ptr [ebp + 0x120] */
	m->edi = (DWORD)(m->esp + 0x14u);	/* 46b4b2: lea edi, [esp + 0x14] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 46b4b6: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 46b4b9: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->ebp + 0x118u));	/* 46b4bc: mov eax, dword ptr [ebp + 0x118] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46b4c2: or ecx, 0xffffffff */
	m->edx = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 46b4c5: lea edx, [eax + edx*4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46b4c8: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 46b4ca: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 46b4cc: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46b4ce: sub edi, ecx */
	m->eax = m->ecx;	/* 46b4d0: mov eax, ecx */
	m->esi = m->edi;	/* 46b4d2: mov esi, edi */
	m->edi = m->edx;	/* 46b4d4: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46b4d6: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 46b4d9: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 46b4db: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46b4dd: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 46b4e0: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 46b4e2: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 46b4e8: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 46b4eb: lea edx, [eax + ecx*2] */
	m->ecx = M32((DWORD)(m->ebp + 0x118u));	/* 46b4ee: mov ecx, dword ptr [ebp + 0x118] */
	M32((DWORD)(m->ecx + m->edx*4 + 0x40u)) = m->eax;	/* 46b4f4: mov dword ptr [ecx + edx*4 + 0x40], eax */
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 46b4f8: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = M32((DWORD)(m->ebp + 0x118u));	/* 46b4fe: mov ecx, dword ptr [ebp + 0x118] */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 46b504: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 46b507: lea eax, [eax + edx*2] */
	M32((DWORD)(m->ecx + m->eax*4 + 0x44u)) = m->ebx;	/* 46b50a: mov dword ptr [ecx + eax*4 + 0x44], ebx */
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 46b50e: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = M32((DWORD)(m->ebp + 0x118u));	/* 46b514: mov ecx, dword ptr [ebp + 0x118] */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 46b51a: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 46b51d: lea eax, [eax + edx*2] */
	M32((DWORD)(m->ecx + m->eax*4 + 0x48u)) = m->ebx;	/* 46b520: mov dword ptr [ecx + eax*4 + 0x48], ebx */
	m->eax = M32((DWORD)(m->ebp + 0x110u));	/* 46b524: mov eax, dword ptr [ebp + 0x110] */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46b52a: cmp eax, 2 */
	if (!m->zf) goto L_46b5c6;	/* 46b52d: jne 0x46b5c6 */
	m->ecx = M32((DWORD)(m->ebp + 0x128u));	/* 46b533: mov ecx, dword ptr [ebp + 0x128] */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46b539: cmp ecx, ebx */
	if (m->zf) goto L_46b59a;	/* 46b53b: je 0x46b59a */
L_46b53d:
	m->eax = M32((DWORD)(m->ebp + 0x12cu));	/* 46b53d: mov eax, dword ptr [ebp + 0x12c] */
	m->edx = M32((DWORD)(m->ebp + 0x124u));	/* 46b543: mov edx, dword ptr [ebp + 0x124] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46b549: sub edx, eax */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46b54b: add eax, ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46b54d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46b54e: push eax */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 46b54f: lea eax, [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46b553: push eax */
	m->esp -= 4; M32(m->esp) = 0x46b559u; native_call(m, 0x46b140u);	/* 46b554: call 0x46b140 */
	m->edx = M32((DWORD)(m->ebp + 0x11cu));	/* 46b559: mov edx, dword ptr [ebp + 0x11c] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b55f: add esp, 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46b562: push eax */
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 46b563: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 46b569: lea ecx, [eax + eax*8] */
	m->ecx = (DWORD)(m->edx + m->ecx*4 + 0x0u);	/* 46b56c: lea ecx, [edx + ecx*4] */
	m->esp -= 4; M32(m->esp) = 0x46b574u; native_call(m, 0x46aa10u);	/* 46b56f: call 0x46aa10 */
L_46b574:
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 46b574: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = M32((DWORD)(m->ebp + 0x11cu));	/* 46b57a: mov ecx, dword ptr [ebp + 0x11c] */
	m->eax = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 46b580: lea eax, [eax + eax*8] */
	m->edx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 46b583: mov edx, dword ptr [ecx + eax*4 + 4] */
	m->eax = M32((DWORD)(m->ebp + 0x12cu));	/* 46b587: mov eax, dword ptr [ebp + 0x12c] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46b58d: add eax, edx */
	M32((DWORD)(m->ebp + 0x12cu)) = m->eax;	/* 46b58f: mov dword ptr [ebp + 0x12c], eax */
	goto L_46b6d8;	/* 46b595: jmp 0x46b6d8 */
L_46b59a:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46b59a: push ebx */
	m->eax = (DWORD)(m->esp + 0x18u);	/* 46b59b: lea eax, [esp + 0x18] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46b59f: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46b5a0: push eax */
	m->esp -= 4; M32(m->esp) = 0x46b5a6u; native_call(m, 0x46b140u);	/* 46b5a1: call 0x46b140 */
	m->edx = M32((DWORD)(m->ebp + 0x11cu));	/* 46b5a6: mov edx, dword ptr [ebp + 0x11c] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b5ac: add esp, 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46b5af: push eax */
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 46b5b0: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 46b5b6: lea ecx, [eax + eax*8] */
	m->ecx = (DWORD)(m->edx + m->ecx*4 + 0x0u);	/* 46b5b9: lea ecx, [edx + ecx*4] */
	m->esp -= 4; M32(m->esp) = 0x46b5c1u; native_call(m, 0x46aa10u);	/* 46b5bc: call 0x46aa10 */
	goto L_46b6d8;	/* 46b5c1: jmp 0x46b6d8 */
L_46b5c6:
	m->ecx = m->eax;	/* 46b5c6: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46b5c8: sub ecx, ebx */
	if (m->zf) goto L_46b5ef;	/* 46b5ca: je 0x46b5ef */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 46b5cc: dec ecx */
	if (m->zf) goto L_46b5e4;	/* 46b5cd: je 0x46b5e4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46b5cf: push eax */
	{ DWORD v_ = 0x4c54fcu; m->esp -= 4; M32(m->esp) = v_; }	/* 46b5d0: push 0x4c54fc */
	{ DWORD v_ = 0xa0eaa0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46b5d5: push 0xa0eaa0 */
	m->esp -= 4; M32(m->esp) = 0x46b5dfu; native_call(m, 0x46c710u);	/* 46b5da: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b5df: add esp, 0xc */
	goto L_46b615;	/* 46b5e2: jmp 0x46b615 */
L_46b5e4:
	m->edx = (DWORD)(m->esp + 0x10u);	/* 46b5e4: lea edx, [esp + 0x10] */
	m->edi = 0x4c54f8u;	/* 46b5e8: mov edi, 0x4c54f8 */
	goto L_46b5f8;	/* 46b5ed: jmp 0x46b5f8 */
L_46b5ef:
	m->edx = (DWORD)(m->esp + 0x10u);	/* 46b5ef: lea edx, [esp + 0x10] */
	m->edi = 0x4c54f4u;	/* 46b5f3: mov edi, 0x4c54f4 */
L_46b5f8:
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46b5f8: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46b5fb: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 46b5fd: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 46b5ff: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46b601: sub edi, ecx */
	m->eax = m->ecx;	/* 46b603: mov eax, ecx */
	m->esi = m->edi;	/* 46b605: mov esi, edi */
	m->edi = m->edx;	/* 46b607: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46b609: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 46b60c: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 46b60e: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46b610: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 46b613: rep movsb byte ptr es:[edi], byte ptr [esi] */
L_46b615:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + 0x10u))) & 0xff) << 0);	/* 46b615: mov al, byte ptr [ebp + 0x10] */
	m->ecx = (DWORD)(m->ebp + 0x10u);	/* 46b618: lea ecx, [ebp + 0x10] */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 46b61b: lea edx, [esp + 0x10] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46b61f: cmp al, bl */
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 46b621: mov eax, dword ptr [ebp + 0x120] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46b627: push edx */
	if (m->zf) goto L_46b652;	/* 46b628: je 0x46b652 */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 46b62a: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 46b62d: lea eax, [eax + edx*2] */
	m->edx = M32((DWORD)(m->ebp + 0x118u));	/* 46b630: mov edx, dword ptr [ebp + 0x118] */
	m->eax = (DWORD)(m->edx + m->eax*4 + 0x0u);	/* 46b636: lea eax, [edx + eax*4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46b639: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46b63a: push ecx */
	m->ecx = (DWORD)(m->esp + 0x120u);	/* 46b63b: lea ecx, [esp + 0x120] */
	{ DWORD v_ = 0x4c4d5cu; m->esp -= 4; M32(m->esp) = v_; }	/* 46b642: push 0x4c4d5c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46b647: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46b64du; native_call(m, 0x49e9ddu);	/* 46b648: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b64d: add esp, 0x14 */
	goto L_46b677;	/* 46b650: jmp 0x46b677 */
L_46b652:
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 46b652: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 46b655: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->ebp + 0x118u));	/* 46b658: mov eax, dword ptr [ebp + 0x118] */
	m->ecx = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 46b65e: lea ecx, [eax + edx*4] */
	m->edx = (DWORD)(m->esp + 0x118u);	/* 46b661: lea edx, [esp + 0x118] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46b668: push ecx */
	{ DWORD v_ = 0x4c4d54u; m->esp -= 4; M32(m->esp) = v_; }	/* 46b669: push 0x4c4d54 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46b66e: push edx */
	m->esp -= 4; M32(m->esp) = 0x46b674u; native_call(m, 0x49e9ddu);	/* 46b66f: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b674: add esp, 0x10 */
L_46b677:
	m->ecx = M32((DWORD)(m->ebp + 0x128u));	/* 46b677: mov ecx, dword ptr [ebp + 0x128] */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46b67d: cmp ecx, ebx */
	if (m->zf) goto L_46b6b7;	/* 46b67f: je 0x46b6b7 */
	m->eax = M32((DWORD)(m->ebp + 0x12cu));	/* 46b681: mov eax, dword ptr [ebp + 0x12c] */
	m->edx = M32((DWORD)(m->ebp + 0x124u));	/* 46b687: mov edx, dword ptr [ebp + 0x124] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46b68d: sub edx, eax */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46b68f: add eax, ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46b691: push edx */
	m->edx = M32((DWORD)(m->ebp + 0x11cu));	/* 46b692: mov edx, dword ptr [ebp + 0x11c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46b698: push eax */
	m->eax = (DWORD)(m->esp + 0x11cu);	/* 46b699: lea eax, [esp + 0x11c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46b6a0: push eax */
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 46b6a1: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 46b6a7: lea ecx, [eax + eax*8] */
	m->ecx = (DWORD)(m->edx + m->ecx*4 + 0x0u);	/* 46b6aa: lea ecx, [edx + ecx*4] */
	m->esp -= 4; M32(m->esp) = 0x46b6b2u; native_call(m, 0x4699d0u);	/* 46b6ad: call 0x4699d0 */
	goto L_46b574;	/* 46b6b2: jmp 0x46b574 */
L_46b6b7:
	m->edx = M32((DWORD)(m->ebp + 0x11cu));	/* 46b6b7: mov edx, dword ptr [ebp + 0x11c] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46b6bd: push ebx */
	m->eax = (DWORD)(m->esp + 0x118u);	/* 46b6be: lea eax, [esp + 0x118] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46b6c5: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46b6c6: push eax */
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 46b6c7: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 46b6cd: lea ecx, [eax + eax*8] */
	m->ecx = (DWORD)(m->edx + m->ecx*4 + 0x0u);	/* 46b6d0: lea ecx, [edx + ecx*4] */
	m->esp -= 4; M32(m->esp) = 0x46b6d8u; native_call(m, 0x4699d0u);	/* 46b6d3: call 0x4699d0 */
L_46b6d8:
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 46b6d8: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = M32((DWORD)(m->ebp + 0x11cu));	/* 46b6de: mov ecx, dword ptr [ebp + 0x11c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 46b6e4: inc eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 46b6e5: pop edi */
	M32((DWORD)(m->ebp + 0x120u)) = m->eax;	/* 46b6e6: mov dword ptr [ebp + 0x120], eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 46b6ec: pop esi */
	m->eax = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 46b6ed: lea eax, [eax + eax*8] */
	m->ebp = M32(m->esp); m->esp += 4;	/* 46b6f0: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 46b6f1: pop ebx */
	m->eax = (DWORD)(m->ecx + m->eax*4 + 0xffffffdcu);	/* 46b6f2: lea eax, [ecx + eax*4 - 0x24] */
	{ DWORD a_ = m->esp, b_ = 0x204u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b6f6: add esp, 0x204 */
	m->esp += 4 + 4; return;	/* 46b6fc: ret 4 */
L_46b6ff:
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 46b6ff: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = M32((DWORD)(m->ebp + 0x114u));	/* 46b705: mov ecx, dword ptr [ebp + 0x114] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46b70b: cmp eax, ecx */
	if (m->sf != m->of) goto L_46b722;	/* 46b70d: jl 0x46b722 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46b70f: push eax */
	{ DWORD v_ = 0x4c54c8u; m->esp -= 4; M32(m->esp) = v_; }	/* 46b710: push 0x4c54c8 */
	{ DWORD v_ = 0xa0eaa0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46b715: push 0xa0eaa0 */
	m->esp -= 4; M32(m->esp) = 0x46b71fu; native_call(m, 0x46c710u);	/* 46b71a: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b71f: add esp, 0xc */
L_46b722:
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 46b722: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = M32((DWORD)(m->ebp + 0x118u));	/* 46b728: mov ecx, dword ptr [ebp + 0x118] */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 46b72e: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 46b731: lea eax, [eax + edx*2] */
	m->edx = (DWORD)(m->ecx + m->eax*4 + 0x0u);	/* 46b734: lea edx, [ecx + eax*4] */
	M32((DWORD)(m->edi + 0x48u)) = m->edx;	/* 46b737: mov dword ptr [edi + 0x48], edx */
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 46b73a: mov eax, dword ptr [ebp + 0x120] */
	m->edi = (DWORD)(m->esp + 0x14u);	/* 46b740: lea edi, [esp + 0x14] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 46b744: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 46b747: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->ebp + 0x118u));	/* 46b74a: mov eax, dword ptr [ebp + 0x118] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46b750: or ecx, 0xffffffff */
	m->edx = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 46b753: lea edx, [eax + edx*4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46b756: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 46b758: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 46b75a: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46b75c: sub edi, ecx */
	m->eax = m->ecx;	/* 46b75e: mov eax, ecx */
	m->esi = m->edi;	/* 46b760: mov esi, edi */
	m->edi = m->edx;	/* 46b762: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46b764: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 46b767: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 46b769: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46b76b: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 46b76e: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 46b770: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 46b776: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 46b779: lea edx, [eax + ecx*2] */
	m->ecx = M32((DWORD)(m->ebp + 0x118u));	/* 46b77c: mov ecx, dword ptr [ebp + 0x118] */
	M32((DWORD)(m->ecx + m->edx*4 + 0x40u)) = m->eax;	/* 46b782: mov dword ptr [ecx + edx*4 + 0x40], eax */
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 46b786: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = M32((DWORD)(m->ebp + 0x118u));	/* 46b78c: mov ecx, dword ptr [ebp + 0x118] */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 46b792: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 46b795: lea eax, [eax + edx*2] */
	M32((DWORD)(m->ecx + m->eax*4 + 0x44u)) = m->ebx;	/* 46b798: mov dword ptr [ecx + eax*4 + 0x44], ebx */
	m->eax = M32((DWORD)(m->ebp + 0x120u));	/* 46b79c: mov eax, dword ptr [ebp + 0x120] */
	m->ecx = M32((DWORD)(m->ebp + 0x118u));	/* 46b7a2: mov ecx, dword ptr [ebp + 0x118] */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 46b7a8: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 46b7ab: lea eax, [eax + edx*2] */
	M32((DWORD)(m->ecx + m->eax*4 + 0x48u)) = m->ebx;	/* 46b7ae: mov dword ptr [ecx + eax*4 + 0x48], ebx */
	m->eax = M32((DWORD)(m->ebp + 0x110u));	/* 46b7b2: mov eax, dword ptr [ebp + 0x110] */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46b7b8: cmp eax, 2 */
	if (!m->zf) goto L_46b5c6;	/* 46b7bb: jne 0x46b5c6 */
	m->ecx = M32((DWORD)(m->ebp + 0x128u));	/* 46b7c1: mov ecx, dword ptr [ebp + 0x128] */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46b7c7: cmp ecx, ebx */
	if (m->zf) goto L_46b59a;	/* 46b7c9: je 0x46b59a */
	goto L_46b53d;	/* 46b7cf: jmp 0x46b53d */
L_46b7d4:
	m->edi = M32(m->esp); m->esp += 4;	/* 46b7d4: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46b7d5: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 46b7d6: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46b7d7: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 46b7d9: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x204u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b7da: add esp, 0x204 */
	m->esp += 4 + 4; return;	/* 46b7e0: ret 4 */
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
