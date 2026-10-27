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

static void lift_4050a0(X86 *m);
static void lift_44f6c0(X86 *m);
static void lift_405140(X86 *m);
static void lift_41dcf0(X86 *m);
static void lift_42e730(X86 *m);
static void lift_42e240(X86 *m);
static void lift_42da70(X86 *m);
static void lift_48dbf0(X86 *m);
static void lift_421680(X86 *m);
static void lift_42d730(X86 *m);

/* cfg_loadAxisCfg (0x42d730), lifted by tools/lift.py */
static void lift_42d730(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x184u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42d730: sub esp, 0x184 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42d736: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42d739: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x0u);	/* 42d73b: lea edx, [esp] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d73f: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d740: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d741: push edi */
	m->edi = 0x9dae7cu;	/* 42d742: mov edi, 0x9dae7c */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42d747: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42d749: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42d74b: sub edi, ecx */
	{ DWORD v_ = 0x4b21a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d74d: push 0x4b21a4 */
	m->eax = m->ecx;	/* 42d752: mov eax, ecx */
	m->esi = m->edi;	/* 42d754: mov esi, edi */
	m->edi = m->edx;	/* 42d756: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 42d758: lea edx, [esp + 0x10] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42d75c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42d75f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 42d761: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42d763: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42d765: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 42d768: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2198u;	/* 42d76a: mov edi, 0x4b2198 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42d76f: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42d772: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42d774: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42d776: sub edi, ecx */
	m->esi = m->edi;	/* 42d778: mov esi, edi */
	m->ebx = m->ecx;	/* 42d77a: mov ebx, ecx */
	m->edi = m->edx;	/* 42d77c: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42d77e: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42d781: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 42d783: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 42d785: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42d786: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42d789: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebx;	/* 42d78b: mov ecx, ebx */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42d78d: lea eax, [esp + 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42d791: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42d794: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 42d795: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x42d79cu; native_call(m, 0x49e9cau);	/* 42d797: call 0x49e9ca */
	m->esi = m->eax;	/* 42d79c: mov esi, eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d79e: push esi */
	{ DWORD v_ = 0x4b0f50u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d79f: push 0x4b0f50 */
	m->esp -= 4; M32(m->esp) = 0x42d7a9u; native_call(m, 0x49f167u);	/* 42d7a4: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d7a9: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d7aa: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d7b4u; native_call(m, 0x49f167u);	/* 42d7af: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d7b4: push esi */
	m->esp -= 4; M32(m->esp) = 0x42d7bau; native_call(m, 0x42c650u);	/* 42d7b5: call 0x42c650 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d7ba: push esi */
	m->esp -= 4; M32(m->esp) = 0x42d7c0u; native_call(m, 0x42c6f0u);	/* 42d7bb: call 0x42c6f0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d7c0: push esi */
	m->esp -= 4; M32(m->esp) = 0x42d7c6u; native_call(m, 0x42c910u);	/* 42d7c1: call 0x42c910 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d7c6: push esi */
	m->esp -= 4; M32(m->esp) = 0x42d7ccu; native_call(m, 0x42c9f0u);	/* 42d7c7: call 0x42c9f0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d7cc: push esi */
	m->esp -= 4; M32(m->esp) = 0x42d7d2u; native_call(m, 0x42cba0u);	/* 42d7cd: call 0x42cba0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d7d2: push esi */
	m->esp -= 4; M32(m->esp) = 0x42d7d8u; native_call(m, 0x49e7e0u);	/* 42d7d3: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42d7d8: add esp, 0x30 */
	m->edi = M32(m->esp); m->esp += 4;	/* 42d7db: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 42d7dc: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 42d7dd: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x184u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42d7de: add esp, 0x184 */
	m->esp += 4 + 0; return;	/* 42d7e4: ret  */
}

/* FUN_004050a0 (0x4050a0), lifted by tools/lift.py */
static void lift_4050a0(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4050a0: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4050a1: push edi */
	m->edi = 0x4db560u;	/* 4050a2: mov edi, 0x4db560 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4050a7: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4050aa: xor eax, eax */
	m->edx = M32((DWORD)(0x4db584u));	/* 4050ac: mov edx, dword ptr [0x4db584] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4050b2: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4050b4: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4050b6: sub edi, ecx */
	m->eax = m->ecx;	/* 4050b8: mov eax, ecx */
	m->esi = m->edi;	/* 4050ba: mov esi, edi */
	m->edi = 0x4dedb0u;	/* 4050bc: mov edi, 0x4dedb0 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4050c1: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4050c4: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4050c6: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4050c8: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4050cb: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x4db580u));	/* 4050cd: mov ecx, dword ptr [0x4db580] */
	M32((DWORD)(0x4dedd4u)) = m->edx;	/* 4050d3: mov dword ptr [0x4dedd4], edx */
	M32((DWORD)(0x4dedd0u)) = m->ecx;	/* 4050d9: mov dword ptr [0x4dedd0], ecx */
	m->esp -= 4; M32(m->esp) = 0x4050e4u; lift_42d730(m);	/* 4050df: call 0x42d730 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4050e4: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4050e5: pop esi */
	m->esp += 4 + 0; return;	/* 4050e6: ret  */
}

/* profile_44f6c0 (0x44f6c0), lifted by tools/lift.py */
static void lift_44f6c0(X86 *m)
{
	m->eax = M32((DWORD)(0x9f6840u));	/* 44f6c0: mov eax, dword ptr [0x9f6840] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44f6c5: test eax, eax */
	if (m->zf) goto L_44f733;	/* 44f6c7: je 0x44f733 */
	m->eax = M32((DWORD)(0x76d410u));	/* 44f6c9: mov eax, dword ptr [0x76d410] */
	M32((DWORD)(0x9da49cu)) = 0x0u;	/* 44f6ce: mov dword ptr [0x9da49c], 0 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44f6d8: cmp eax, 1 */
	if (!m->zf) goto L_44f6e7;	/* 44f6db: jne 0x44f6e7 */
	M32((DWORD)(0x9da49cu)) = 0x65u;	/* 44f6dd: mov dword ptr [0x9da49c], 0x65 */
L_44f6e7:
	m->esp -= 4; M32(m->esp) = 0x44f6ecu; native_call(m, 0x446a10u);	/* 44f6e7: call 0x446a10 */
	m->eax = 0x12cu;	/* 44f6ec: mov eax, 0x12c */
	{ DWORD v_ = 0x20u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f6f1: push 0x20 */
	M32((DWORD)(0x76d3e8u)) = m->eax;	/* 44f6f3: mov dword ptr [0x76d3e8], eax */
	M32((DWORD)(0x67ef20u)) = m->eax;	/* 44f6f8: mov dword ptr [0x67ef20], eax */
	m->eax = M32((DWORD)(0x9f8c58u));	/* 44f6fd: mov eax, dword ptr [0x9f8c58] */
	M32((DWORD)(0x680370u)) = 0x2u;	/* 44f702: mov dword ptr [0x680370], 2 */
	M32((DWORD)(0x4df8e0u)) = 0x0u;	/* 44f70c: mov dword ptr [0x4df8e0], 0 */
	m->eax = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44f716: lea eax, [eax + eax*8] */
	m->ecx = (DWORD)(m->eax*8 + 0x9f684cu);	/* 44f719: lea ecx, [eax*8 + 0x9f684c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f720: push ecx */
	{ DWORD v_ = 0x4dedb0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f721: push 0x4dedb0 */
	m->esp -= 4; M32(m->esp) = 0x44f72bu; native_call(m, 0x49ea80u);	/* 44f726: call 0x49ea80 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44f72b: add esp, 0xc */
	lift_42d730(m); return;	/* 44f72e: jmp 0x42d730 */
L_44f733:
	m->esp += 4 + 0; return;	/* 44f733: ret  */
}

/* lobby_405140 (0x405140), lifted by tools/lift.py */
static void lift_405140(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 405140: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 405141: push edi */
	m->edi = 0x4db54eu;	/* 405142: mov edi, 0x4db54e */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 405147: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40514a: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 40514c: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 40514e: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 405150: dec ecx */
	m->edi = 0x4db528u;	/* 405151: mov edi, 0x4db528 */
	m->edx = (m->edx & ~(0xffu << 0)) | ((((!m->zf) ? 1u : 0u) & 0xff) << 0);	/* 405156: setne dl */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 405159: or ecx, 0xffffffff */
	M8((DWORD)(0x4db556u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 40515c: mov byte ptr [0x4db556], dl */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 405162: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 405164: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 405166: sub edi, ecx */
	m->eax = m->ecx;	/* 405168: mov eax, ecx */
	m->esi = m->edi;	/* 40516a: mov esi, edi */
	m->edi = 0x4ded20u;	/* 40516c: mov edi, 0x4ded20 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 405171: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 405174: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 405176: mov ecx, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4db549u))) & 0xff) << 0);	/* 405178: mov al, byte ptr [0x4db549] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40517d: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 405180: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x4db548u))) & 0xff) << 0);	/* 405182: mov cl, byte ptr [0x4db548] */
	M8((DWORD)(0x4ded41u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 405188: mov byte ptr [0x4ded41], al */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4db54bu))) & 0xff) << 0);	/* 40518d: mov al, byte ptr [0x4db54b] */
	M8((DWORD)(0x4ded40u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 405192: mov byte ptr [0x4ded40], cl */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x4db54au))) & 0xff) << 0);	/* 405198: mov cl, byte ptr [0x4db54a] */
	M8((DWORD)(0x4ded43u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 40519e: mov byte ptr [0x4ded43], al */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4db54du))) & 0xff) << 0);	/* 4051a3: mov al, byte ptr [0x4db54d] */
	M8((DWORD)(0x4ded42u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 4051a8: mov byte ptr [0x4ded42], cl */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x4db54cu))) & 0xff) << 0);	/* 4051ae: mov cl, byte ptr [0x4db54c] */
	M8((DWORD)(0x4ded45u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 4051b4: mov byte ptr [0x4ded45], al */
	M8((DWORD)(0x4ded44u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 4051b9: mov byte ptr [0x4ded44], cl */
	m->edi = 0x4db54eu;	/* 4051bf: mov edi, 0x4db54e */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4051c4: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4051c7: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4051c9: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4051cb: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4051cd: sub edi, ecx */
	m->eax = m->ecx;	/* 4051cf: mov eax, ecx */
	m->esi = m->edi;	/* 4051d1: mov esi, edi */
	m->edi = 0x4ded46u;	/* 4051d3: mov edi, 0x4ded46 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4051d8: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4051db: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4051dd: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4051df: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4051e2: rep movsb byte ptr es:[edi], byte ptr [esi] */
	M8((DWORD)(0x4ded4eu)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 4051e4: mov byte ptr [0x4ded4e], dl */
	m->esp -= 4; M32(m->esp) = 0x4051efu; lift_42d730(m);	/* 4051ea: call 0x42d730 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4051ef: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4051f0: pop esi */
	m->esp += 4 + 0; return;	/* 4051f1: ret  */
}

/* armc_41dcf0 (0x41dcf0), lifted by tools/lift.py */
static void lift_41dcf0(X86 *m)
{
	m->eax = M32((DWORD)(0x4dcb1cu));	/* 41dcf0: mov eax, dword ptr [0x4dcb1c] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 41dcf5: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 41dcf6: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41dcf7: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 41dcf8: push edi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 41dcf9: xor esi, esi */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41dcfb: xor ecx, ecx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 41dcfd: xor edx, edx */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 41dcff: xor edi, edi */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 41dd01: xor ebx, ebx */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 41dd03: xor ebp, ebp */
	{ DWORD a_ = m->eax, b_ = 0x1bu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41dd05: cmp eax, 0x1b */
	M32((DWORD)(0x4dcb10u)) = m->esi;	/* 41dd08: mov dword ptr [0x4dcb10], esi */
	M32((DWORD)(0x4dcea8u)) = m->ecx;	/* 41dd0e: mov dword ptr [0x4dcea8], ecx */
	M32((DWORD)(0x4dcc5cu)) = m->edx;	/* 41dd14: mov dword ptr [0x4dcc5c], edx */
	M32((DWORD)(0x4dbc54u)) = m->edi;	/* 41dd1a: mov dword ptr [0x4dbc54], edi */
	M32((DWORD)(0x4dbe44u)) = m->ebx;	/* 41dd20: mov dword ptr [0x4dbe44], ebx */
	M32((DWORD)(0x4dc794u)) = m->ebp;	/* 41dd26: mov dword ptr [0x4dc794], ebp */
	M32((DWORD)(0x4dbd78u)) = m->ebp;	/* 41dd2c: mov dword ptr [0x4dbd78], ebp */
	M32((DWORD)(0x4dc774u)) = m->ebp;	/* 41dd32: mov dword ptr [0x4dc774], ebp */
	M32((DWORD)(0x4dcf30u)) = m->ebp;	/* 41dd38: mov dword ptr [0x4dcf30], ebp */
	M32((DWORD)(0x4dbc70u)) = m->ebp;	/* 41dd3e: mov dword ptr [0x4dbc70], ebp */
	M32((DWORD)(0x4dc248u)) = m->ebp;	/* 41dd44: mov dword ptr [0x4dc248], ebp */
	M32((DWORD)(0x4dcc6cu)) = m->ebp;	/* 41dd4a: mov dword ptr [0x4dcc6c], ebp */
	M32((DWORD)(0x4dc548u)) = m->ebp;	/* 41dd50: mov dword ptr [0x4dc548], ebp */
	M32((DWORD)(0x4dcb34u)) = m->ebp;	/* 41dd56: mov dword ptr [0x4dcb34], ebp */
	M32((DWORD)(0x4dbc78u)) = m->ebp;	/* 41dd5c: mov dword ptr [0x4dbc78], ebp */
	M32((DWORD)(0x4dc898u)) = m->ebp;	/* 41dd62: mov dword ptr [0x4dc898], ebp */
	M32((DWORD)(0x4dceb4u)) = m->ebp;	/* 41dd68: mov dword ptr [0x4dceb4], ebp */
	M32((DWORD)(0x4dc88cu)) = m->ebp;	/* 41dd6e: mov dword ptr [0x4dc88c], ebp */
	M32((DWORD)(0x4dcca0u)) = m->ebp;	/* 41dd74: mov dword ptr [0x4dcca0], ebp */
	M32((DWORD)(0x4dc894u)) = m->ebp;	/* 41dd7a: mov dword ptr [0x4dc894], ebp */
	M32((DWORD)(0x4dceb0u)) = m->ebp;	/* 41dd80: mov dword ptr [0x4dceb0], ebp */
	M32((DWORD)(0x4dcc68u)) = m->ebp;	/* 41dd86: mov dword ptr [0x4dcc68], ebp */
	M32((DWORD)(0x4dbc74u)) = m->ebp;	/* 41dd8c: mov dword ptr [0x4dbc74], ebp */
	if (m->sf != m->of) goto L_41de13;	/* 41dd92: jl 0x41de13 */
	{ DWORD a_ = m->eax, b_ = 0xffffffe5u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41dd94: add eax, -0x1b */
	{ DWORD a_ = m->eax, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41dd97: cmp eax, 8 */
	if (!m->cf && !m->zf) goto L_41de13;	/* 41dd9a: ja 0x41de13 */
	switch (m->eax) { case 0: goto L_41dda3; case 1: goto L_41ddb0; case 2: goto L_41ddbd; case 3: goto L_41ddca; case 4: goto L_41ddd7; case 5: goto L_41dde4; case 6: goto L_41ddf1; case 7: goto L_41ddfd; case 8: goto L_41de09; default: abort(); }	/* 41dd9c: jmp dword ptr [eax*4 + 0x41df64] */
L_41dda3:
	m->esi = 0x1u;	/* 41dda3: mov esi, 1 */
	M32((DWORD)(0x4dcb10u)) = m->esi;	/* 41dda8: mov dword ptr [0x4dcb10], esi */
	goto L_41de13;	/* 41ddae: jmp 0x41de13 */
L_41ddb0:
	m->ecx = 0x1u;	/* 41ddb0: mov ecx, 1 */
	M32((DWORD)(0x4dcea8u)) = m->ecx;	/* 41ddb5: mov dword ptr [0x4dcea8], ecx */
	goto L_41de13;	/* 41ddbb: jmp 0x41de13 */
L_41ddbd:
	m->edx = 0x1u;	/* 41ddbd: mov edx, 1 */
	M32((DWORD)(0x4dcc5cu)) = m->edx;	/* 41ddc2: mov dword ptr [0x4dcc5c], edx */
	goto L_41de13;	/* 41ddc8: jmp 0x41de13 */
L_41ddca:
	m->edi = 0x1u;	/* 41ddca: mov edi, 1 */
	M32((DWORD)(0x4dbc54u)) = m->edi;	/* 41ddcf: mov dword ptr [0x4dbc54], edi */
	goto L_41de13;	/* 41ddd5: jmp 0x41de13 */
L_41ddd7:
	m->ebx = 0x1u;	/* 41ddd7: mov ebx, 1 */
	M32((DWORD)(0x4dbe44u)) = m->ebx;	/* 41dddc: mov dword ptr [0x4dbe44], ebx */
	goto L_41de13;	/* 41dde2: jmp 0x41de13 */
L_41dde4:
	m->ebp = 0x1u;	/* 41dde4: mov ebp, 1 */
	M32((DWORD)(0x4dc794u)) = m->ebp;	/* 41dde9: mov dword ptr [0x4dc794], ebp */
	goto L_41de13;	/* 41ddef: jmp 0x41de13 */
L_41ddf1:
	M32((DWORD)(0x4dbd78u)) = 0x1u;	/* 41ddf1: mov dword ptr [0x4dbd78], 1 */
	goto L_41de13;	/* 41ddfb: jmp 0x41de13 */
L_41ddfd:
	M32((DWORD)(0x4dc774u)) = 0x1u;	/* 41ddfd: mov dword ptr [0x4dc774], 1 */
	goto L_41de13;	/* 41de07: jmp 0x41de13 */
L_41de09:
	M32((DWORD)(0x4dcf30u)) = 0x1u;	/* 41de09: mov dword ptr [0x4dcf30], 1 */
L_41de13:
	m->eax = M32((DWORD)(0x4dcb18u));	/* 41de13: mov eax, dword ptr [0x4dcb18] */
	{ DWORD a_ = m->eax, b_ = 0x1bu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41de18: cmp eax, 0x1b */
	if (m->sf != m->of) goto L_41de9b;	/* 41de1b: jl 0x41de9b */
	{ DWORD a_ = m->eax, b_ = 0xffffffe5u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41de1d: add eax, -0x1b */
	{ DWORD a_ = m->eax, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41de20: cmp eax, 8 */
	if (!m->cf && !m->zf) goto L_41de9b;	/* 41de23: ja 0x41de9b */
	switch (m->eax) { case 0: goto L_41de2c; case 1: goto L_41de38; case 2: goto L_41de45; case 3: goto L_41de52; case 4: goto L_41de5f; case 5: goto L_41de6c; case 6: goto L_41de79; case 7: goto L_41de85; case 8: goto L_41de91; default: abort(); }	/* 41de25: jmp dword ptr [eax*4 + 0x41df88] */
L_41de2c:
	m->eax = 0x1u;	/* 41de2c: mov eax, 1 */
	M32((DWORD)(0x4dcb10u)) = m->eax;	/* 41de31: mov dword ptr [0x4dcb10], eax */
	goto L_41dea5;	/* 41de36: jmp 0x41dea5 */
L_41de38:
	m->ecx = 0x1u;	/* 41de38: mov ecx, 1 */
	M32((DWORD)(0x4dcea8u)) = m->ecx;	/* 41de3d: mov dword ptr [0x4dcea8], ecx */
	goto L_41de9b;	/* 41de43: jmp 0x41de9b */
L_41de45:
	m->edx = 0x1u;	/* 41de45: mov edx, 1 */
	M32((DWORD)(0x4dcc5cu)) = m->edx;	/* 41de4a: mov dword ptr [0x4dcc5c], edx */
	goto L_41de9b;	/* 41de50: jmp 0x41de9b */
L_41de52:
	m->edi = 0x1u;	/* 41de52: mov edi, 1 */
	M32((DWORD)(0x4dbc54u)) = m->edi;	/* 41de57: mov dword ptr [0x4dbc54], edi */
	goto L_41de9b;	/* 41de5d: jmp 0x41de9b */
L_41de5f:
	m->ebx = 0x1u;	/* 41de5f: mov ebx, 1 */
	M32((DWORD)(0x4dbe44u)) = m->ebx;	/* 41de64: mov dword ptr [0x4dbe44], ebx */
	goto L_41de9b;	/* 41de6a: jmp 0x41de9b */
L_41de6c:
	m->ebp = 0x1u;	/* 41de6c: mov ebp, 1 */
	M32((DWORD)(0x4dc794u)) = m->ebp;	/* 41de71: mov dword ptr [0x4dc794], ebp */
	goto L_41de9b;	/* 41de77: jmp 0x41de9b */
L_41de79:
	M32((DWORD)(0x4dbd78u)) = 0x1u;	/* 41de79: mov dword ptr [0x4dbd78], 1 */
	goto L_41de9b;	/* 41de83: jmp 0x41de9b */
L_41de85:
	M32((DWORD)(0x4dc774u)) = 0x1u;	/* 41de85: mov dword ptr [0x4dc774], 1 */
	goto L_41de9b;	/* 41de8f: jmp 0x41de9b */
L_41de91:
	M32((DWORD)(0x4dcf30u)) = 0x1u;	/* 41de91: mov dword ptr [0x4dcf30], 1 */
L_41de9b:
	{ DWORD a_ = m->esi, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41de9b: cmp esi, 1 */
	m->eax = 0x1u;	/* 41de9e: mov eax, 1 */
	if (!m->zf) goto L_41deaf;	/* 41dea3: jne 0x41deaf */
L_41dea5:
	M32((DWORD)(0x4dbc70u)) = 0x3e99999au;	/* 41dea5: mov dword ptr [0x4dbc70], 0x3e99999a */
L_41deaf:
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41deaf: cmp ecx, eax */
	if (!m->zf) goto L_41debd;	/* 41deb1: jne 0x41debd */
	M32((DWORD)(0x4dc248u)) = 0x42c80000u;	/* 41deb3: mov dword ptr [0x4dc248], 0x42c80000 */
L_41debd:
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41debd: cmp edx, eax */
	if (!m->zf) goto L_41decb;	/* 41debf: jne 0x41decb */
	M32((DWORD)(0x4dcc6cu)) = 0x42c80000u;	/* 41dec1: mov dword ptr [0x4dcc6c], 0x42c80000 */
L_41decb:
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41decb: cmp edi, eax */
	if (!m->zf) goto L_41ded9;	/* 41decd: jne 0x41ded9 */
	M32((DWORD)(0x4dc548u)) = 0x42c80000u;	/* 41decf: mov dword ptr [0x4dc548], 0x42c80000 */
L_41ded9:
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41ded9: cmp ebx, eax */
	if (!m->zf) goto L_41dee7;	/* 41dedb: jne 0x41dee7 */
	M32((DWORD)(0x4dcb34u)) = 0x42480000u;	/* 41dedd: mov dword ptr [0x4dcb34], 0x42480000 */
L_41dee7:
	m->edi = M32(m->esp); m->esp += 4;	/* 41dee7: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 41dee8: pop esi */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41dee9: cmp ebp, eax */
	m->ebp = M32(m->esp); m->esp += 4;	/* 41deeb: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 41deec: pop ebx */
	if (!m->zf) goto L_41df17;	/* 41deed: jne 0x41df17 */
	M32((DWORD)(0x4dbc78u)) = 0x42c80000u;	/* 41deef: mov dword ptr [0x4dbc78], 0x42c80000 */
	M32((DWORD)(0x4dc898u)) = 0x3f000000u;	/* 41def9: mov dword ptr [0x4dc898], 0x3f000000 */
	M32((DWORD)(0x4dceb4u)) = 0x40400000u;	/* 41df03: mov dword ptr [0x4dceb4], 0x40400000 */
	M32((DWORD)(0x4dc88cu)) = 0x3f800000u;	/* 41df0d: mov dword ptr [0x4dc88c], 0x3f800000 */
L_41df17:
	{ DWORD a_ = M32((DWORD)(0x4dbd78u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41df17: cmp dword ptr [0x4dbd78], eax */
	if (!m->zf) goto L_41df33;	/* 41df1d: jne 0x41df33 */
	M32((DWORD)(0x4dcca0u)) = 0x3f000000u;	/* 41df1f: mov dword ptr [0x4dcca0], 0x3f000000 */
	M32((DWORD)(0x4dc894u)) = 0xbdcccccdu;	/* 41df29: mov dword ptr [0x4dc894], 0xbdcccccd */
L_41df33:
	{ DWORD a_ = M32((DWORD)(0x4dc774u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41df33: cmp dword ptr [0x4dc774], eax */
	if (!m->zf) goto L_41df45;	/* 41df39: jne 0x41df45 */
	M32((DWORD)(0x4dceb0u)) = 0x3e4ccccdu;	/* 41df3b: mov dword ptr [0x4dceb0], 0x3e4ccccd */
L_41df45:
	{ DWORD a_ = M32((DWORD)(0x4dcf30u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41df45: cmp dword ptr [0x4dcf30], eax */
	if (!m->zf) goto L_41df61;	/* 41df4b: jne 0x41df61 */
	M32((DWORD)(0x4dcc68u)) = 0x3e99999au;	/* 41df4d: mov dword ptr [0x4dcc68], 0x3e99999a */
	M32((DWORD)(0x4dbc74u)) = 0x3f800000u;	/* 41df57: mov dword ptr [0x4dbc74], 0x3f800000 */
L_41df61:
	m->esp += 4 + 0; return;	/* 41df61: ret  */
}

/* cfg_parseKeyNames (0x42e730), lifted by tools/lift.py */
static void lift_42e730(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x10cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42e730: sub esp, 0x10c */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42e736: push ebp */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 42e737: xor ebp, ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42e739: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42e73a: push edi */
	M32((DWORD)(m->esp + 0xcu)) = m->ebp;	/* 42e73b: mov dword ptr [esp + 0xc], ebp */
L_42e73f:
	m->eax = M32((DWORD)(m->esp + 0x11cu));	/* 42e73f: mov eax, dword ptr [esp + 0x11c] */
	m->ecx = (DWORD)(m->esp + 0x94u);	/* 42e746: lea ecx, [esp + 0x94] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42e74d: push eax */
	{ DWORD v_ = 0x50u; m->esp -= 4; M32(m->esp) = v_; }	/* 42e74e: push 0x50 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42e750: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42e756u; native_call(m, 0x49ecd7u);	/* 42e751: call 0x49ecd7 */
	m->edi = (DWORD)(m->esp + 0xa0u);	/* 42e756: lea edi, [esp + 0xa0] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e75d: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42e760: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0xa0u);	/* 42e762: lea edx, [esp + 0xa0] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42e769: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42e76b: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 42e76d: dec ecx */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42e76e: push 0x4ad5dc */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42e773: push edx */
	M8((DWORD)(m->esp + m->ecx*1 + 0xa7u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 42e774: mov byte ptr [esp + ecx + 0xa7], al */
	m->esp -= 4; M32(m->esp) = 0x42e780u; native_call(m, 0x49ec3bu);	/* 42e77b: call 0x49ec3b */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42e780: push 0x4ad5dc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42e785: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42e78cu; native_call(m, 0x49ec3bu);	/* 42e787: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42e78c: add esp, 0x1c */
	m->ecx = 0x21u;	/* 42e78f: mov ecx, 0x21 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42e794: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x10u);	/* 42e796: lea edi, [esp + 0x10] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 42e79a: rep stosd dword ptr es:[edi], eax */
L_42e79c:
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42e79c: push 0x4ad5dc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42e7a1: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42e7a8u; native_call(m, 0x49ec3bu);	/* 42e7a3: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42e7a8: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42e7ab: test eax, eax */
	if (m->zf) goto L_42e7dc;	/* 42e7ad: je 0x42e7dc */
	m->edi = m->eax;	/* 42e7af: mov edi, eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e7b1: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42e7b4: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 42e7b6: lea edx, [esp + 0x10] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42e7ba: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42e7bc: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42e7be: sub edi, ecx */
	m->esi = m->edi;	/* 42e7c0: mov esi, edi */
	m->edi = m->edx;	/* 42e7c2: mov edi, edx */
	m->edx = m->ecx;	/* 42e7c4: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e7c6: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42e7c9: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 42e7cb: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 42e7cd: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42e7ce: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42e7d1: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 42e7d3: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e7d5: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 42e7d8: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_42e79c;	/* 42e7da: jmp 0x42e79c */
L_42e7dc:
	{ DWORD a_ = m->ebp, b_ = 0x40u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42e7dc: cmp ebp, 0x40 */
	if (!m->zf) goto L_42e835;	/* 42e7df: jne 0x42e835 */
	m->esi = 0x4b21bcu;	/* 42e7e1: mov esi, 0x4b21bc */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42e7e6: lea eax, [esp + 0x10] */
L_42e7ea:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42e7ea: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e7ec: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e7ee: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42e81e;	/* 42e7f0: jne 0x42e81e */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e7f2: test cl, cl */
	if (m->zf) goto L_42e80a;	/* 42e7f4: je 0x42e80a */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42e7f6: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e7f9: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e7fb: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42e81e;	/* 42e7fe: jne 0x42e81e */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42e800: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42e803: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e806: test cl, cl */
	if (!m->zf) goto L_42e7ea;	/* 42e808: jne 0x42e7ea */
L_42e80a:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42e80a: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e80c: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42e80e: test eax, eax */
	m->ecx = (m->ecx & ~(0xffu << 0)) | ((((m->zf) ? 1u : 0u) & 0xff) << 0);	/* 42e810: sete cl */
	M32((DWORD)(0x4df000u)) = m->ecx;	/* 42e813: mov dword ptr [0x4df000], ecx */
	goto L_42eb64;	/* 42e819: jmp 0x42eb64 */
L_42e81e:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e81e: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e820: sbb eax, -1 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e823: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42e825: test eax, eax */
	m->ecx = (m->ecx & ~(0xffu << 0)) | ((((m->zf) ? 1u : 0u) & 0xff) << 0);	/* 42e827: sete cl */
	M32((DWORD)(0x4df000u)) = m->ecx;	/* 42e82a: mov dword ptr [0x4df000], ecx */
	goto L_42eb64;	/* 42e830: jmp 0x42eb64 */
L_42e835:
	{ DWORD a_ = m->ebp, b_ = 0x41u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42e835: cmp ebp, 0x41 */
	if (!m->zf) goto L_42e88e;	/* 42e838: jne 0x42e88e */
	m->esi = 0x4b21bcu;	/* 42e83a: mov esi, 0x4b21bc */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42e83f: lea eax, [esp + 0x10] */
L_42e843:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42e843: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e845: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e847: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42e877;	/* 42e849: jne 0x42e877 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e84b: test cl, cl */
	if (m->zf) goto L_42e863;	/* 42e84d: je 0x42e863 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42e84f: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e852: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e854: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42e877;	/* 42e857: jne 0x42e877 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42e859: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42e85c: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e85f: test cl, cl */
	if (!m->zf) goto L_42e843;	/* 42e861: jne 0x42e843 */
L_42e863:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42e863: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e865: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42e867: test eax, eax */
	m->ecx = (m->ecx & ~(0xffu << 0)) | ((((m->zf) ? 1u : 0u) & 0xff) << 0);	/* 42e869: sete cl */
	M32((DWORD)(0x4df004u)) = m->ecx;	/* 42e86c: mov dword ptr [0x4df004], ecx */
	goto L_42eb64;	/* 42e872: jmp 0x42eb64 */
L_42e877:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e877: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e879: sbb eax, -1 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e87c: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42e87e: test eax, eax */
	m->ecx = (m->ecx & ~(0xffu << 0)) | ((((m->zf) ? 1u : 0u) & 0xff) << 0);	/* 42e880: sete cl */
	M32((DWORD)(0x4df004u)) = m->ecx;	/* 42e883: mov dword ptr [0x4df004], ecx */
	goto L_42eb64;	/* 42e889: jmp 0x42eb64 */
L_42e88e:
	{ DWORD a_ = m->ebp, b_ = 0x42u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42e88e: cmp ebp, 0x42 */
	if (!m->zf) goto L_42e8aa;	/* 42e891: jne 0x42e8aa */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 42e893: lea edx, [esp + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42e897: push edx */
	m->esp -= 4; M32(m->esp) = 0x42e89du; native_call(m, 0x49ec09u);	/* 42e898: call 0x49ec09 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42e89d: add esp, 4 */
	M32((DWORD)(0x4df008u)) = m->eax;	/* 42e8a0: mov dword ptr [0x4df008], eax */
	goto L_42eb68;	/* 42e8a5: jmp 0x42eb68 */
L_42e8aa:
	{ DWORD a_ = m->ebp, b_ = 0x43u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42e8aa: cmp ebp, 0x43 */
	if (!m->zf) goto L_42e8c6;	/* 42e8ad: jne 0x42e8c6 */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42e8af: lea eax, [esp + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42e8b3: push eax */
	m->esp -= 4; M32(m->esp) = 0x42e8b9u; native_call(m, 0x49ec09u);	/* 42e8b4: call 0x49ec09 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42e8b9: add esp, 4 */
	M32((DWORD)(0x4df00cu)) = m->eax;	/* 42e8bc: mov dword ptr [0x4df00c], eax */
	goto L_42eb68;	/* 42e8c1: jmp 0x42eb68 */
L_42e8c6:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42e8c6: xor eax, eax */
	m->ebp = 0x4b0750u;	/* 42e8c8: mov ebp, 0x4b0750 */
L_42e8cd:
	m->edi = M32((DWORD)(m->ebp + 0x0u));	/* 42e8cd: mov edi, dword ptr [ebp] */
	m->esi = (DWORD)(m->esp + 0x10u);	/* 42e8d0: lea esi, [esp + 0x10] */
L_42e8d4:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 42e8d4: mov dl, byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e8d6: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->edi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e8d8: cmp dl, byte ptr [edi] */
	if (!m->zf) goto L_42e8f8;	/* 42e8da: jne 0x42e8f8 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e8dc: test cl, cl */
	if (m->zf) goto L_42e8f4;	/* 42e8de: je 0x42e8f4 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 42e8e0: mov dl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e8e3: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->edi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e8e5: cmp dl, byte ptr [edi + 1] */
	if (!m->zf) goto L_42e8f8;	/* 42e8e8: jne 0x42e8f8 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42e8ea: add esi, 2 */
	{ DWORD a_ = m->edi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42e8ed: add edi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e8f0: test cl, cl */
	if (!m->zf) goto L_42e8d4;	/* 42e8f2: jne 0x42e8d4 */
L_42e8f4:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e8f4: xor ecx, ecx */
	goto L_42e8fd;	/* 42e8f6: jmp 0x42e8fd */
L_42e8f8:
	{ DWORD a_ = m->ecx, b_ = m->ecx, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 42e8f8: sbb ecx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 42e8fa: sbb ecx, -1 */
L_42e8fd:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42e8fd: test ecx, ecx */
	if (!m->zf) goto L_42eb54;	/* 42e8ff: jne 0x42eb54 */
	m->ecx = M32((DWORD)(m->esp + 0xcu));	/* 42e905: mov ecx, dword ptr [esp + 0xc] */
	{ DWORD a_ = m->ecx, b_ = 0x3fu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42e909: cmp ecx, 0x3f */
	if (!m->cf && !m->zf) goto L_42eb54;	/* 42e90c: ja 0x42eb54 */
	switch (m->ecx) { case 0: goto L_42e919; case 1: goto L_42e923; case 2: goto L_42e92d; case 3: goto L_42e937; case 4: goto L_42e941; case 5: goto L_42e94b; case 6: goto L_42e955; case 7: goto L_42e95f; case 8: goto L_42e969; case 9: goto L_42e973; case 10: goto L_42e97d; case 11: goto L_42e987; case 12: goto L_42e991; case 13: goto L_42e99b; case 14: goto L_42e9a5; case 15: goto L_42e9af; case 16: goto L_42e9b9; case 17: goto L_42e9c3; case 18: goto L_42e9cd; case 19: goto L_42e9d7; case 20: goto L_42e9e1; case 21: goto L_42e9eb; case 22: goto L_42e9f5; case 23: goto L_42e9ff; case 24: goto L_42ea09; case 25: goto L_42ea13; case 26: goto L_42ea1d; case 27: goto L_42ea27; case 28: goto L_42ea31; case 29: goto L_42ea3b; case 30: goto L_42ea45; case 31: goto L_42ea4f; case 32: goto L_42ea59; case 33: goto L_42ea63; case 34: goto L_42ea6d; case 35: goto L_42ea77; case 36: goto L_42ea81; case 37: goto L_42ea8b; case 38: goto L_42ea95; case 39: goto L_42ea9f; case 40: goto L_42eaa9; case 41: goto L_42eab3; case 42: goto L_42eabd; case 43: goto L_42eac7; case 44: goto L_42ead1; case 45: goto L_42ead8; case 46: goto L_42eadf; case 47: goto L_42eae6; case 48: goto L_42eaed; case 49: goto L_42eaf4; case 50: goto L_42eafb; case 51: goto L_42eb02; case 52: goto L_42eb09; case 53: goto L_42eb10; case 54: goto L_42eb17; case 55: goto L_42eb1e; case 56: goto L_42eb25; case 57: goto L_42eb2c; case 58: goto L_42eb33; case 59: goto L_42eb3a; case 60: goto L_42eb41; case 61: goto L_42eb48; case 62: goto L_42eb4f; case 63: goto L_42eb4f; default: abort(); }	/* 42e912: jmp dword ptr [ecx*4 + 0x42eb9c] */
L_42e919:
	M32((DWORD)(0x4def00u)) = m->eax;	/* 42e919: mov dword ptr [0x4def00], eax */
	goto L_42eb54;	/* 42e91e: jmp 0x42eb54 */
L_42e923:
	M32((DWORD)(0x4def04u)) = m->eax;	/* 42e923: mov dword ptr [0x4def04], eax */
	goto L_42eb54;	/* 42e928: jmp 0x42eb54 */
L_42e92d:
	M32((DWORD)(0x4def08u)) = m->eax;	/* 42e92d: mov dword ptr [0x4def08], eax */
	goto L_42eb54;	/* 42e932: jmp 0x42eb54 */
L_42e937:
	M32((DWORD)(0x4def0cu)) = m->eax;	/* 42e937: mov dword ptr [0x4def0c], eax */
	goto L_42eb54;	/* 42e93c: jmp 0x42eb54 */
L_42e941:
	M32((DWORD)(0x4def10u)) = m->eax;	/* 42e941: mov dword ptr [0x4def10], eax */
	goto L_42eb54;	/* 42e946: jmp 0x42eb54 */
L_42e94b:
	M32((DWORD)(0x4def14u)) = m->eax;	/* 42e94b: mov dword ptr [0x4def14], eax */
	goto L_42eb54;	/* 42e950: jmp 0x42eb54 */
L_42e955:
	M32((DWORD)(0x4def18u)) = m->eax;	/* 42e955: mov dword ptr [0x4def18], eax */
	goto L_42eb54;	/* 42e95a: jmp 0x42eb54 */
L_42e95f:
	M32((DWORD)(0x4def1cu)) = m->eax;	/* 42e95f: mov dword ptr [0x4def1c], eax */
	goto L_42eb54;	/* 42e964: jmp 0x42eb54 */
L_42e969:
	M32((DWORD)(0x4def20u)) = m->eax;	/* 42e969: mov dword ptr [0x4def20], eax */
	goto L_42eb54;	/* 42e96e: jmp 0x42eb54 */
L_42e973:
	M32((DWORD)(0x4def24u)) = m->eax;	/* 42e973: mov dword ptr [0x4def24], eax */
	goto L_42eb54;	/* 42e978: jmp 0x42eb54 */
L_42e97d:
	M32((DWORD)(0x4def28u)) = m->eax;	/* 42e97d: mov dword ptr [0x4def28], eax */
	goto L_42eb54;	/* 42e982: jmp 0x42eb54 */
L_42e987:
	M32((DWORD)(0x4def2cu)) = m->eax;	/* 42e987: mov dword ptr [0x4def2c], eax */
	goto L_42eb54;	/* 42e98c: jmp 0x42eb54 */
L_42e991:
	M32((DWORD)(0x4def30u)) = m->eax;	/* 42e991: mov dword ptr [0x4def30], eax */
	goto L_42eb54;	/* 42e996: jmp 0x42eb54 */
L_42e99b:
	M32((DWORD)(0x4def34u)) = m->eax;	/* 42e99b: mov dword ptr [0x4def34], eax */
	goto L_42eb54;	/* 42e9a0: jmp 0x42eb54 */
L_42e9a5:
	M32((DWORD)(0x4def38u)) = m->eax;	/* 42e9a5: mov dword ptr [0x4def38], eax */
	goto L_42eb54;	/* 42e9aa: jmp 0x42eb54 */
L_42e9af:
	M32((DWORD)(0x4def3cu)) = m->eax;	/* 42e9af: mov dword ptr [0x4def3c], eax */
	goto L_42eb54;	/* 42e9b4: jmp 0x42eb54 */
L_42e9b9:
	M32((DWORD)(0x4def40u)) = m->eax;	/* 42e9b9: mov dword ptr [0x4def40], eax */
	goto L_42eb54;	/* 42e9be: jmp 0x42eb54 */
L_42e9c3:
	M32((DWORD)(0x4def44u)) = m->eax;	/* 42e9c3: mov dword ptr [0x4def44], eax */
	goto L_42eb54;	/* 42e9c8: jmp 0x42eb54 */
L_42e9cd:
	M32((DWORD)(0x4def48u)) = m->eax;	/* 42e9cd: mov dword ptr [0x4def48], eax */
	goto L_42eb54;	/* 42e9d2: jmp 0x42eb54 */
L_42e9d7:
	M32((DWORD)(0x4def4cu)) = m->eax;	/* 42e9d7: mov dword ptr [0x4def4c], eax */
	goto L_42eb54;	/* 42e9dc: jmp 0x42eb54 */
L_42e9e1:
	M32((DWORD)(0x4def50u)) = m->eax;	/* 42e9e1: mov dword ptr [0x4def50], eax */
	goto L_42eb54;	/* 42e9e6: jmp 0x42eb54 */
L_42e9eb:
	M32((DWORD)(0x4def54u)) = m->eax;	/* 42e9eb: mov dword ptr [0x4def54], eax */
	goto L_42eb54;	/* 42e9f0: jmp 0x42eb54 */
L_42e9f5:
	M32((DWORD)(0x4def58u)) = m->eax;	/* 42e9f5: mov dword ptr [0x4def58], eax */
	goto L_42eb54;	/* 42e9fa: jmp 0x42eb54 */
L_42e9ff:
	M32((DWORD)(0x4def5cu)) = m->eax;	/* 42e9ff: mov dword ptr [0x4def5c], eax */
	goto L_42eb54;	/* 42ea04: jmp 0x42eb54 */
L_42ea09:
	M32((DWORD)(0x4def60u)) = m->eax;	/* 42ea09: mov dword ptr [0x4def60], eax */
	goto L_42eb54;	/* 42ea0e: jmp 0x42eb54 */
L_42ea13:
	M32((DWORD)(0x4def64u)) = m->eax;	/* 42ea13: mov dword ptr [0x4def64], eax */
	goto L_42eb54;	/* 42ea18: jmp 0x42eb54 */
L_42ea1d:
	M32((DWORD)(0x4def78u)) = m->eax;	/* 42ea1d: mov dword ptr [0x4def78], eax */
	goto L_42eb54;	/* 42ea22: jmp 0x42eb54 */
L_42ea27:
	M32((DWORD)(0x4def7cu)) = m->eax;	/* 42ea27: mov dword ptr [0x4def7c], eax */
	goto L_42eb54;	/* 42ea2c: jmp 0x42eb54 */
L_42ea31:
	M32((DWORD)(0x4def80u)) = m->eax;	/* 42ea31: mov dword ptr [0x4def80], eax */
	goto L_42eb54;	/* 42ea36: jmp 0x42eb54 */
L_42ea3b:
	M32((DWORD)(0x4def84u)) = m->eax;	/* 42ea3b: mov dword ptr [0x4def84], eax */
	goto L_42eb54;	/* 42ea40: jmp 0x42eb54 */
L_42ea45:
	M32((DWORD)(0x4def88u)) = m->eax;	/* 42ea45: mov dword ptr [0x4def88], eax */
	goto L_42eb54;	/* 42ea4a: jmp 0x42eb54 */
L_42ea4f:
	M32((DWORD)(0x4def8cu)) = m->eax;	/* 42ea4f: mov dword ptr [0x4def8c], eax */
	goto L_42eb54;	/* 42ea54: jmp 0x42eb54 */
L_42ea59:
	M32((DWORD)(0x4def90u)) = m->eax;	/* 42ea59: mov dword ptr [0x4def90], eax */
	goto L_42eb54;	/* 42ea5e: jmp 0x42eb54 */
L_42ea63:
	M32((DWORD)(0x4def94u)) = m->eax;	/* 42ea63: mov dword ptr [0x4def94], eax */
	goto L_42eb54;	/* 42ea68: jmp 0x42eb54 */
L_42ea6d:
	M32((DWORD)(0x4def68u)) = m->eax;	/* 42ea6d: mov dword ptr [0x4def68], eax */
	goto L_42eb54;	/* 42ea72: jmp 0x42eb54 */
L_42ea77:
	M32((DWORD)(0x4def6cu)) = m->eax;	/* 42ea77: mov dword ptr [0x4def6c], eax */
	goto L_42eb54;	/* 42ea7c: jmp 0x42eb54 */
L_42ea81:
	M32((DWORD)(0x4def70u)) = m->eax;	/* 42ea81: mov dword ptr [0x4def70], eax */
	goto L_42eb54;	/* 42ea86: jmp 0x42eb54 */
L_42ea8b:
	M32((DWORD)(0x4def74u)) = m->eax;	/* 42ea8b: mov dword ptr [0x4def74], eax */
	goto L_42eb54;	/* 42ea90: jmp 0x42eb54 */
L_42ea95:
	M32((DWORD)(0x4def98u)) = m->eax;	/* 42ea95: mov dword ptr [0x4def98], eax */
	goto L_42eb54;	/* 42ea9a: jmp 0x42eb54 */
L_42ea9f:
	M32((DWORD)(0x4def9cu)) = m->eax;	/* 42ea9f: mov dword ptr [0x4def9c], eax */
	goto L_42eb54;	/* 42eaa4: jmp 0x42eb54 */
L_42eaa9:
	M32((DWORD)(0x4defa0u)) = m->eax;	/* 42eaa9: mov dword ptr [0x4defa0], eax */
	goto L_42eb54;	/* 42eaae: jmp 0x42eb54 */
L_42eab3:
	M32((DWORD)(0x4defa4u)) = m->eax;	/* 42eab3: mov dword ptr [0x4defa4], eax */
	goto L_42eb54;	/* 42eab8: jmp 0x42eb54 */
L_42eabd:
	M32((DWORD)(0x4defa8u)) = m->eax;	/* 42eabd: mov dword ptr [0x4defa8], eax */
	goto L_42eb54;	/* 42eac2: jmp 0x42eb54 */
L_42eac7:
	M32((DWORD)(0x4defacu)) = m->eax;	/* 42eac7: mov dword ptr [0x4defac], eax */
	goto L_42eb54;	/* 42eacc: jmp 0x42eb54 */
L_42ead1:
	M32((DWORD)(0x4defb0u)) = m->eax;	/* 42ead1: mov dword ptr [0x4defb0], eax */
	goto L_42eb54;	/* 42ead6: jmp 0x42eb54 */
L_42ead8:
	M32((DWORD)(0x4defb4u)) = m->eax;	/* 42ead8: mov dword ptr [0x4defb4], eax */
	goto L_42eb54;	/* 42eadd: jmp 0x42eb54 */
L_42eadf:
	M32((DWORD)(0x4defb8u)) = m->eax;	/* 42eadf: mov dword ptr [0x4defb8], eax */
	goto L_42eb54;	/* 42eae4: jmp 0x42eb54 */
L_42eae6:
	M32((DWORD)(0x4defbcu)) = m->eax;	/* 42eae6: mov dword ptr [0x4defbc], eax */
	goto L_42eb54;	/* 42eaeb: jmp 0x42eb54 */
L_42eaed:
	M32((DWORD)(0x4defc0u)) = m->eax;	/* 42eaed: mov dword ptr [0x4defc0], eax */
	goto L_42eb54;	/* 42eaf2: jmp 0x42eb54 */
L_42eaf4:
	M32((DWORD)(0x4defc4u)) = m->eax;	/* 42eaf4: mov dword ptr [0x4defc4], eax */
	goto L_42eb54;	/* 42eaf9: jmp 0x42eb54 */
L_42eafb:
	M32((DWORD)(0x4defc8u)) = m->eax;	/* 42eafb: mov dword ptr [0x4defc8], eax */
	goto L_42eb54;	/* 42eb00: jmp 0x42eb54 */
L_42eb02:
	M32((DWORD)(0x4defccu)) = m->eax;	/* 42eb02: mov dword ptr [0x4defcc], eax */
	goto L_42eb54;	/* 42eb07: jmp 0x42eb54 */
L_42eb09:
	M32((DWORD)(0x4defd0u)) = m->eax;	/* 42eb09: mov dword ptr [0x4defd0], eax */
	goto L_42eb54;	/* 42eb0e: jmp 0x42eb54 */
L_42eb10:
	M32((DWORD)(0x4defd4u)) = m->eax;	/* 42eb10: mov dword ptr [0x4defd4], eax */
	goto L_42eb54;	/* 42eb15: jmp 0x42eb54 */
L_42eb17:
	M32((DWORD)(0x4defd8u)) = m->eax;	/* 42eb17: mov dword ptr [0x4defd8], eax */
	goto L_42eb54;	/* 42eb1c: jmp 0x42eb54 */
L_42eb1e:
	M32((DWORD)(0x4defdcu)) = m->eax;	/* 42eb1e: mov dword ptr [0x4defdc], eax */
	goto L_42eb54;	/* 42eb23: jmp 0x42eb54 */
L_42eb25:
	M32((DWORD)(0x4defe0u)) = m->eax;	/* 42eb25: mov dword ptr [0x4defe0], eax */
	goto L_42eb54;	/* 42eb2a: jmp 0x42eb54 */
L_42eb2c:
	M32((DWORD)(0x4defe4u)) = m->eax;	/* 42eb2c: mov dword ptr [0x4defe4], eax */
	goto L_42eb54;	/* 42eb31: jmp 0x42eb54 */
L_42eb33:
	M32((DWORD)(0x4defe8u)) = m->eax;	/* 42eb33: mov dword ptr [0x4defe8], eax */
	goto L_42eb54;	/* 42eb38: jmp 0x42eb54 */
L_42eb3a:
	M32((DWORD)(0x4defecu)) = m->eax;	/* 42eb3a: mov dword ptr [0x4defec], eax */
	goto L_42eb54;	/* 42eb3f: jmp 0x42eb54 */
L_42eb41:
	M32((DWORD)(0x4deff0u)) = m->eax;	/* 42eb41: mov dword ptr [0x4deff0], eax */
	goto L_42eb54;	/* 42eb46: jmp 0x42eb54 */
L_42eb48:
	M32((DWORD)(0x4deff4u)) = m->eax;	/* 42eb48: mov dword ptr [0x4deff4], eax */
	goto L_42eb54;	/* 42eb4d: jmp 0x42eb54 */
L_42eb4f:
	M32((DWORD)(0x4deff8u)) = m->eax;	/* 42eb4f: mov dword ptr [0x4deff8], eax */
L_42eb54:
	{ DWORD a_ = m->ebp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 42eb54: add ebp, 4 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 42eb57: inc eax */
	{ DWORD a_ = m->ebp, b_ = 0x4b0b50u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42eb58: cmp ebp, 0x4b0b50 */
	if (m->sf != m->of) goto L_42e8cd;	/* 42eb5e: jl 0x42e8cd */
L_42eb64:
	m->ebp = M32((DWORD)(m->esp + 0xcu));	/* 42eb64: mov ebp, dword ptr [esp + 0xc] */
L_42eb68:
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 42eb68: inc ebp */
	{ DWORD a_ = m->ebp, b_ = 0x44u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42eb69: cmp ebp, 0x44 */
	M32((DWORD)(m->esp + 0xcu)) = m->ebp;	/* 42eb6c: mov dword ptr [esp + 0xc], ebp */
	if (m->sf != m->of) goto L_42e73f;	/* 42eb70: jl 0x42e73f */
	m->eax = M32((DWORD)(m->esp + 0x11cu));	/* 42eb76: mov eax, dword ptr [esp + 0x11c] */
	m->ecx = (DWORD)(m->esp + 0x94u);	/* 42eb7d: lea ecx, [esp + 0x94] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42eb84: push eax */
	{ DWORD v_ = 0x50u; m->esp -= 4; M32(m->esp) = v_; }	/* 42eb85: push 0x50 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42eb87: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42eb8du; native_call(m, 0x49ecd7u);	/* 42eb88: call 0x49ecd7 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42eb8d: add esp, 0xc */
	m->edi = M32(m->esp); m->esp += 4;	/* 42eb90: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 42eb91: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 42eb92: pop ebp */
	{ DWORD a_ = m->esp, b_ = 0x10cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42eb93: add esp, 0x10c */
	m->esp += 4 + 0; return;	/* 42eb99: ret  */
}

/* cfg_videoModeNames (0x42e240), lifted by tools/lift.py */
static void lift_42e240(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x10cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42e240: sub esp, 0x10c */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42e246: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42e247: push edi */
	M32((DWORD)(m->esp + 0x8u)) = 0x0u;	/* 42e248: mov dword ptr [esp + 8], 0 */
L_42e250:
	m->eax = M32((DWORD)(m->esp + 0x118u));	/* 42e250: mov eax, dword ptr [esp + 0x118] */
	m->ecx = (DWORD)(m->esp + 0x90u);	/* 42e257: lea ecx, [esp + 0x90] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42e25e: push eax */
	{ DWORD v_ = 0x50u; m->esp -= 4; M32(m->esp) = v_; }	/* 42e25f: push 0x50 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42e261: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42e267u; native_call(m, 0x49ecd7u);	/* 42e262: call 0x49ecd7 */
	m->edi = (DWORD)(m->esp + 0x9cu);	/* 42e267: lea edi, [esp + 0x9c] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e26e: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42e271: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x9cu);	/* 42e273: lea edx, [esp + 0x9c] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42e27a: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42e27c: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 42e27e: dec ecx */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42e27f: push 0x4ad5dc */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42e284: push edx */
	M8((DWORD)(m->esp + m->ecx*1 + 0xa3u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 42e285: mov byte ptr [esp + ecx + 0xa3], al */
	m->esp -= 4; M32(m->esp) = 0x42e291u; native_call(m, 0x49ec3bu);	/* 42e28c: call 0x49ec3b */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42e291: push 0x4ad5dc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42e296: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42e29du; native_call(m, 0x49ec3bu);	/* 42e298: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42e29d: add esp, 0x1c */
	m->ecx = 0x21u;	/* 42e2a0: mov ecx, 0x21 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42e2a5: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0xcu);	/* 42e2a7: lea edi, [esp + 0xc] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 42e2ab: rep stosd dword ptr es:[edi], eax */
L_42e2ad:
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42e2ad: push 0x4ad5dc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42e2b2: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42e2b9u; native_call(m, 0x49ec3bu);	/* 42e2b4: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42e2b9: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42e2bc: test eax, eax */
	if (m->zf) goto L_42e2ed;	/* 42e2be: je 0x42e2ed */
	m->edi = m->eax;	/* 42e2c0: mov edi, eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e2c2: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42e2c5: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0xcu);	/* 42e2c7: lea edx, [esp + 0xc] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42e2cb: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42e2cd: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42e2cf: sub edi, ecx */
	m->esi = m->edi;	/* 42e2d1: mov esi, edi */
	m->edi = m->edx;	/* 42e2d3: mov edi, edx */
	m->edx = m->ecx;	/* 42e2d5: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e2d7: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42e2da: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 42e2dc: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 42e2de: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42e2df: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42e2e2: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 42e2e4: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e2e6: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 42e2e9: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_42e2ad;	/* 42e2eb: jmp 0x42e2ad */
L_42e2ed:
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 42e2ed: mov eax, dword ptr [esp + 8] */
	{ DWORD a_ = m->eax, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42e2f1: cmp eax, 6 */
	if (!m->cf && !m->zf) goto L_42e6d2;	/* 42e2f4: ja 0x42e6d2 */
	switch (m->eax) { case 0: goto L_42e301; case 1: goto L_42e4f5; case 2: goto L_42e549; case 3: goto L_42e59d; case 4: goto L_42e5f1; case 5: goto L_42e645; case 6: goto L_42e693; default: abort(); }	/* 42e2fa: jmp dword ptr [eax*4 + 0x42e708] */
L_42e301:
	m->esi = 0x4ac858u;	/* 42e301: mov esi, 0x4ac858 */
	m->eax = (DWORD)(m->esp + 0xcu);	/* 42e306: lea eax, [esp + 0xc] */
L_42e30a:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42e30a: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e30c: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e30e: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42e32e;	/* 42e310: jne 0x42e32e */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e312: test cl, cl */
	if (m->zf) goto L_42e32a;	/* 42e314: je 0x42e32a */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42e316: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e319: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e31b: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42e32e;	/* 42e31e: jne 0x42e32e */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42e320: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42e323: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e326: test cl, cl */
	if (!m->zf) goto L_42e30a;	/* 42e328: jne 0x42e30a */
L_42e32a:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42e32a: xor eax, eax */
	goto L_42e333;	/* 42e32c: jmp 0x42e333 */
L_42e32e:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e32e: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e330: sbb eax, -1 */
L_42e333:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42e333: test eax, eax */
	if (!m->zf) goto L_42e346;	/* 42e335: jne 0x42e346 */
	M32((DWORD)(0x83a9c0u)) = 0x1u;	/* 42e337: mov dword ptr [0x83a9c0], 1 */
	goto L_42e6d2;	/* 42e341: jmp 0x42e6d2 */
L_42e346:
	m->esi = 0x4ac87cu;	/* 42e346: mov esi, 0x4ac87c */
	m->eax = (DWORD)(m->esp + 0xcu);	/* 42e34b: lea eax, [esp + 0xc] */
L_42e34f:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42e34f: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e351: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e353: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42e373;	/* 42e355: jne 0x42e373 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e357: test cl, cl */
	if (m->zf) goto L_42e36f;	/* 42e359: je 0x42e36f */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42e35b: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e35e: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e360: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42e373;	/* 42e363: jne 0x42e373 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42e365: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42e368: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e36b: test cl, cl */
	if (!m->zf) goto L_42e34f;	/* 42e36d: jne 0x42e34f */
L_42e36f:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42e36f: xor eax, eax */
	goto L_42e378;	/* 42e371: jmp 0x42e378 */
L_42e373:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e373: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e375: sbb eax, -1 */
L_42e378:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42e378: test eax, eax */
	if (!m->zf) goto L_42e38b;	/* 42e37a: jne 0x42e38b */
	M32((DWORD)(0x83a9c0u)) = 0x2u;	/* 42e37c: mov dword ptr [0x83a9c0], 2 */
	goto L_42e6d2;	/* 42e386: jmp 0x42e6d2 */
L_42e38b:
	m->esi = 0x4ac8a0u;	/* 42e38b: mov esi, 0x4ac8a0 */
	m->eax = (DWORD)(m->esp + 0xcu);	/* 42e390: lea eax, [esp + 0xc] */
L_42e394:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42e394: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e396: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e398: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42e3b8;	/* 42e39a: jne 0x42e3b8 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e39c: test cl, cl */
	if (m->zf) goto L_42e3b4;	/* 42e39e: je 0x42e3b4 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42e3a0: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e3a3: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e3a5: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42e3b8;	/* 42e3a8: jne 0x42e3b8 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42e3aa: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42e3ad: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e3b0: test cl, cl */
	if (!m->zf) goto L_42e394;	/* 42e3b2: jne 0x42e394 */
L_42e3b4:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42e3b4: xor eax, eax */
	goto L_42e3bd;	/* 42e3b6: jmp 0x42e3bd */
L_42e3b8:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e3b8: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e3ba: sbb eax, -1 */
L_42e3bd:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42e3bd: test eax, eax */
	if (!m->zf) goto L_42e3d0;	/* 42e3bf: jne 0x42e3d0 */
	M32((DWORD)(0x83a9c0u)) = 0x3u;	/* 42e3c1: mov dword ptr [0x83a9c0], 3 */
	goto L_42e6d2;	/* 42e3cb: jmp 0x42e6d2 */
L_42e3d0:
	m->esi = 0x4ac8c4u;	/* 42e3d0: mov esi, 0x4ac8c4 */
	m->eax = (DWORD)(m->esp + 0xcu);	/* 42e3d5: lea eax, [esp + 0xc] */
L_42e3d9:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42e3d9: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e3db: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e3dd: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42e3fd;	/* 42e3df: jne 0x42e3fd */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e3e1: test cl, cl */
	if (m->zf) goto L_42e3f9;	/* 42e3e3: je 0x42e3f9 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42e3e5: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e3e8: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e3ea: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42e3fd;	/* 42e3ed: jne 0x42e3fd */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42e3ef: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42e3f2: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e3f5: test cl, cl */
	if (!m->zf) goto L_42e3d9;	/* 42e3f7: jne 0x42e3d9 */
L_42e3f9:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42e3f9: xor eax, eax */
	goto L_42e402;	/* 42e3fb: jmp 0x42e402 */
L_42e3fd:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e3fd: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e3ff: sbb eax, -1 */
L_42e402:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42e402: test eax, eax */
	if (!m->zf) goto L_42e415;	/* 42e404: jne 0x42e415 */
	M32((DWORD)(0x83a9c0u)) = 0x4u;	/* 42e406: mov dword ptr [0x83a9c0], 4 */
	goto L_42e6d2;	/* 42e410: jmp 0x42e6d2 */
L_42e415:
	m->esi = 0x4ac8e8u;	/* 42e415: mov esi, 0x4ac8e8 */
	m->eax = (DWORD)(m->esp + 0xcu);	/* 42e41a: lea eax, [esp + 0xc] */
L_42e41e:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42e41e: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e420: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e422: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42e442;	/* 42e424: jne 0x42e442 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e426: test cl, cl */
	if (m->zf) goto L_42e43e;	/* 42e428: je 0x42e43e */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42e42a: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e42d: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e42f: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42e442;	/* 42e432: jne 0x42e442 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42e434: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42e437: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e43a: test cl, cl */
	if (!m->zf) goto L_42e41e;	/* 42e43c: jne 0x42e41e */
L_42e43e:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42e43e: xor eax, eax */
	goto L_42e447;	/* 42e440: jmp 0x42e447 */
L_42e442:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e442: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e444: sbb eax, -1 */
L_42e447:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42e447: test eax, eax */
	if (!m->zf) goto L_42e45a;	/* 42e449: jne 0x42e45a */
	M32((DWORD)(0x83a9c0u)) = 0x5u;	/* 42e44b: mov dword ptr [0x83a9c0], 5 */
	goto L_42e6d2;	/* 42e455: jmp 0x42e6d2 */
L_42e45a:
	m->esi = 0x4ac90cu;	/* 42e45a: mov esi, 0x4ac90c */
	m->eax = (DWORD)(m->esp + 0xcu);	/* 42e45f: lea eax, [esp + 0xc] */
L_42e463:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42e463: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e465: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e467: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42e487;	/* 42e469: jne 0x42e487 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e46b: test cl, cl */
	if (m->zf) goto L_42e483;	/* 42e46d: je 0x42e483 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42e46f: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e472: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e474: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42e487;	/* 42e477: jne 0x42e487 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42e479: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42e47c: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e47f: test cl, cl */
	if (!m->zf) goto L_42e463;	/* 42e481: jne 0x42e463 */
L_42e483:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42e483: xor eax, eax */
	goto L_42e48c;	/* 42e485: jmp 0x42e48c */
L_42e487:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e487: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e489: sbb eax, -1 */
L_42e48c:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42e48c: test eax, eax */
	if (!m->zf) goto L_42e49f;	/* 42e48e: jne 0x42e49f */
	M32((DWORD)(0x83a9c0u)) = 0x6u;	/* 42e490: mov dword ptr [0x83a9c0], 6 */
	goto L_42e6d2;	/* 42e49a: jmp 0x42e6d2 */
L_42e49f:
	m->esi = 0x4ac92cu;	/* 42e49f: mov esi, 0x4ac92c */
	m->eax = (DWORD)(m->esp + 0xcu);	/* 42e4a4: lea eax, [esp + 0xc] */
L_42e4a8:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42e4a8: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e4aa: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e4ac: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42e4dd;	/* 42e4ae: jne 0x42e4dd */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e4b0: test cl, cl */
	if (m->zf) goto L_42e4c8;	/* 42e4b2: je 0x42e4c8 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42e4b4: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e4b7: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e4b9: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42e4dd;	/* 42e4bc: jne 0x42e4dd */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42e4be: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42e4c1: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e4c4: test cl, cl */
	if (!m->zf) goto L_42e4a8;	/* 42e4c6: jne 0x42e4a8 */
L_42e4c8:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42e4c8: xor eax, eax */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 42e4ca: neg eax */
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e4cc: sbb eax, eax */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0xf9u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 42e4ce: and al, 0xf9 */
	{ DWORD a_ = m->eax, b_ = 0x7u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42e4d0: add eax, 7 */
	M32((DWORD)(0x83a9c0u)) = m->eax;	/* 42e4d3: mov dword ptr [0x83a9c0], eax */
	goto L_42e6d2;	/* 42e4d8: jmp 0x42e6d2 */
L_42e4dd:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e4dd: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e4df: sbb eax, -1 */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 42e4e2: neg eax */
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e4e4: sbb eax, eax */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0xf9u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 42e4e6: and al, 0xf9 */
	{ DWORD a_ = m->eax, b_ = 0x7u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42e4e8: add eax, 7 */
	M32((DWORD)(0x83a9c0u)) = m->eax;	/* 42e4eb: mov dword ptr [0x83a9c0], eax */
	goto L_42e6d2;	/* 42e4f0: jmp 0x42e6d2 */
L_42e4f5:
	m->esi = 0x4b22d4u;	/* 42e4f5: mov esi, 0x4b22d4 */
	m->eax = (DWORD)(m->esp + 0xcu);	/* 42e4fa: lea eax, [esp + 0xc] */
L_42e4fe:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42e4fe: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e500: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e502: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42e532;	/* 42e504: jne 0x42e532 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e506: test cl, cl */
	if (m->zf) goto L_42e51e;	/* 42e508: je 0x42e51e */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42e50a: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e50d: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e50f: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42e532;	/* 42e512: jne 0x42e532 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42e514: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42e517: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e51a: test cl, cl */
	if (!m->zf) goto L_42e4fe;	/* 42e51c: jne 0x42e4fe */
L_42e51e:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42e51e: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e520: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42e522: test eax, eax */
	m->ecx = (m->ecx & ~(0xffu << 0)) | ((((m->zf) ? 1u : 0u) & 0xff) << 0);	/* 42e524: sete cl */
	M32((DWORD)(0x83a9c4u)) = m->ecx;	/* 42e527: mov dword ptr [0x83a9c4], ecx */
	goto L_42e6d2;	/* 42e52d: jmp 0x42e6d2 */
L_42e532:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e532: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e534: sbb eax, -1 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e537: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42e539: test eax, eax */
	m->ecx = (m->ecx & ~(0xffu << 0)) | ((((m->zf) ? 1u : 0u) & 0xff) << 0);	/* 42e53b: sete cl */
	M32((DWORD)(0x83a9c4u)) = m->ecx;	/* 42e53e: mov dword ptr [0x83a9c4], ecx */
	goto L_42e6d2;	/* 42e544: jmp 0x42e6d2 */
L_42e549:
	m->esi = 0x4b22ccu;	/* 42e549: mov esi, 0x4b22cc */
	m->eax = (DWORD)(m->esp + 0xcu);	/* 42e54e: lea eax, [esp + 0xc] */
L_42e552:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42e552: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e554: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e556: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42e586;	/* 42e558: jne 0x42e586 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e55a: test cl, cl */
	if (m->zf) goto L_42e572;	/* 42e55c: je 0x42e572 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42e55e: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e561: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e563: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42e586;	/* 42e566: jne 0x42e586 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42e568: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42e56b: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e56e: test cl, cl */
	if (!m->zf) goto L_42e552;	/* 42e570: jne 0x42e552 */
L_42e572:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42e572: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e574: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42e576: test eax, eax */
	m->ecx = (m->ecx & ~(0xffu << 0)) | ((((m->zf) ? 1u : 0u) & 0xff) << 0);	/* 42e578: sete cl */
	M32((DWORD)(0x83a9c8u)) = m->ecx;	/* 42e57b: mov dword ptr [0x83a9c8], ecx */
	goto L_42e6d2;	/* 42e581: jmp 0x42e6d2 */
L_42e586:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e586: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e588: sbb eax, -1 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e58b: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42e58d: test eax, eax */
	m->ecx = (m->ecx & ~(0xffu << 0)) | ((((m->zf) ? 1u : 0u) & 0xff) << 0);	/* 42e58f: sete cl */
	M32((DWORD)(0x83a9c8u)) = m->ecx;	/* 42e592: mov dword ptr [0x83a9c8], ecx */
	goto L_42e6d2;	/* 42e598: jmp 0x42e6d2 */
L_42e59d:
	m->esi = 0x4b21bcu;	/* 42e59d: mov esi, 0x4b21bc */
	m->eax = (DWORD)(m->esp + 0xcu);	/* 42e5a2: lea eax, [esp + 0xc] */
L_42e5a6:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42e5a6: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e5a8: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e5aa: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42e5da;	/* 42e5ac: jne 0x42e5da */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e5ae: test cl, cl */
	if (m->zf) goto L_42e5c6;	/* 42e5b0: je 0x42e5c6 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42e5b2: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e5b5: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e5b7: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42e5da;	/* 42e5ba: jne 0x42e5da */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42e5bc: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42e5bf: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e5c2: test cl, cl */
	if (!m->zf) goto L_42e5a6;	/* 42e5c4: jne 0x42e5a6 */
L_42e5c6:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42e5c6: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e5c8: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42e5ca: test eax, eax */
	m->ecx = (m->ecx & ~(0xffu << 0)) | ((((m->zf) ? 1u : 0u) & 0xff) << 0);	/* 42e5cc: sete cl */
	M32((DWORD)(0x83a9ccu)) = m->ecx;	/* 42e5cf: mov dword ptr [0x83a9cc], ecx */
	goto L_42e6d2;	/* 42e5d5: jmp 0x42e6d2 */
L_42e5da:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e5da: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e5dc: sbb eax, -1 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e5df: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42e5e1: test eax, eax */
	m->ecx = (m->ecx & ~(0xffu << 0)) | ((((m->zf) ? 1u : 0u) & 0xff) << 0);	/* 42e5e3: sete cl */
	M32((DWORD)(0x83a9ccu)) = m->ecx;	/* 42e5e6: mov dword ptr [0x83a9cc], ecx */
	goto L_42e6d2;	/* 42e5ec: jmp 0x42e6d2 */
L_42e5f1:
	m->esi = 0x4b21bcu;	/* 42e5f1: mov esi, 0x4b21bc */
	m->eax = (DWORD)(m->esp + 0xcu);	/* 42e5f6: lea eax, [esp + 0xc] */
L_42e5fa:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42e5fa: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e5fc: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e5fe: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42e62e;	/* 42e600: jne 0x42e62e */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e602: test cl, cl */
	if (m->zf) goto L_42e61a;	/* 42e604: je 0x42e61a */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42e606: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e609: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e60b: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42e62e;	/* 42e60e: jne 0x42e62e */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42e610: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42e613: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e616: test cl, cl */
	if (!m->zf) goto L_42e5fa;	/* 42e618: jne 0x42e5fa */
L_42e61a:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42e61a: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e61c: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42e61e: test eax, eax */
	m->ecx = (m->ecx & ~(0xffu << 0)) | ((((m->zf) ? 1u : 0u) & 0xff) << 0);	/* 42e620: sete cl */
	M32((DWORD)(0x83a9d0u)) = m->ecx;	/* 42e623: mov dword ptr [0x83a9d0], ecx */
	goto L_42e6d2;	/* 42e629: jmp 0x42e6d2 */
L_42e62e:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e62e: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e630: sbb eax, -1 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e633: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42e635: test eax, eax */
	m->ecx = (m->ecx & ~(0xffu << 0)) | ((((m->zf) ? 1u : 0u) & 0xff) << 0);	/* 42e637: sete cl */
	M32((DWORD)(0x83a9d0u)) = m->ecx;	/* 42e63a: mov dword ptr [0x83a9d0], ecx */
	goto L_42e6d2;	/* 42e640: jmp 0x42e6d2 */
L_42e645:
	m->esi = 0x4b21bcu;	/* 42e645: mov esi, 0x4b21bc */
	m->eax = (DWORD)(m->esp + 0xcu);	/* 42e64a: lea eax, [esp + 0xc] */
L_42e64e:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42e64e: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e650: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e652: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42e67f;	/* 42e654: jne 0x42e67f */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e656: test cl, cl */
	if (m->zf) goto L_42e66e;	/* 42e658: je 0x42e66e */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42e65a: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e65d: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e65f: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42e67f;	/* 42e662: jne 0x42e67f */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42e664: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42e667: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e66a: test cl, cl */
	if (!m->zf) goto L_42e64e;	/* 42e66c: jne 0x42e64e */
L_42e66e:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42e66e: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e670: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42e672: test eax, eax */
	m->ecx = (m->ecx & ~(0xffu << 0)) | ((((m->zf) ? 1u : 0u) & 0xff) << 0);	/* 42e674: sete cl */
	M32((DWORD)(0x83a9d4u)) = m->ecx;	/* 42e677: mov dword ptr [0x83a9d4], ecx */
	goto L_42e6d2;	/* 42e67d: jmp 0x42e6d2 */
L_42e67f:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e67f: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e681: sbb eax, -1 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e684: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42e686: test eax, eax */
	m->ecx = (m->ecx & ~(0xffu << 0)) | ((((m->zf) ? 1u : 0u) & 0xff) << 0);	/* 42e688: sete cl */
	M32((DWORD)(0x83a9d4u)) = m->ecx;	/* 42e68b: mov dword ptr [0x83a9d4], ecx */
	goto L_42e6d2;	/* 42e691: jmp 0x42e6d2 */
L_42e693:
	m->esi = 0x4b21bcu;	/* 42e693: mov esi, 0x4b21bc */
	m->eax = (DWORD)(m->esp + 0xcu);	/* 42e698: lea eax, [esp + 0xc] */
L_42e69c:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42e69c: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e69e: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e6a0: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42e6c0;	/* 42e6a2: jne 0x42e6c0 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e6a4: test cl, cl */
	if (m->zf) goto L_42e6bc;	/* 42e6a6: je 0x42e6bc */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42e6a8: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e6ab: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e6ad: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42e6c0;	/* 42e6b0: jne 0x42e6c0 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42e6b2: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42e6b5: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e6b8: test cl, cl */
	if (!m->zf) goto L_42e69c;	/* 42e6ba: jne 0x42e69c */
L_42e6bc:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42e6bc: xor eax, eax */
	goto L_42e6c5;	/* 42e6be: jmp 0x42e6c5 */
L_42e6c0:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e6c0: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e6c2: sbb eax, -1 */
L_42e6c5:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e6c5: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42e6c7: test eax, eax */
	m->ecx = (m->ecx & ~(0xffu << 0)) | ((((m->zf) ? 1u : 0u) & 0xff) << 0);	/* 42e6c9: sete cl */
	M32((DWORD)(0x83a9d8u)) = m->ecx;	/* 42e6cc: mov dword ptr [0x83a9d8], ecx */
L_42e6d2:
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 42e6d2: mov eax, dword ptr [esp + 8] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 42e6d6: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42e6d7: cmp eax, 7 */
	M32((DWORD)(m->esp + 0x8u)) = m->eax;	/* 42e6da: mov dword ptr [esp + 8], eax */
	if (m->sf != m->of) goto L_42e250;	/* 42e6de: jl 0x42e250 */
	m->edx = M32((DWORD)(m->esp + 0x118u));	/* 42e6e4: mov edx, dword ptr [esp + 0x118] */
	m->eax = (DWORD)(m->esp + 0x90u);	/* 42e6eb: lea eax, [esp + 0x90] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42e6f2: push edx */
	{ DWORD v_ = 0x50u; m->esp -= 4; M32(m->esp) = v_; }	/* 42e6f3: push 0x50 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42e6f5: push eax */
	m->esp -= 4; M32(m->esp) = 0x42e6fbu; native_call(m, 0x49ecd7u);	/* 42e6f6: call 0x49ecd7 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42e6fb: add esp, 0xc */
	m->edi = M32(m->esp); m->esp += 4;	/* 42e6fe: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 42e6ff: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x10cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42e700: add esp, 0x10c */
	m->esp += 4 + 0; return;	/* 42e706: ret  */
}

/* cfg_gameTypeNames (0x42da70), lifted by tools/lift.py */
static void lift_42da70(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x108u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42da70: sub esp, 0x108 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42da76: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42da77: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42da78: push esi */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 42da79: xor ebx, ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42da7b: push edi */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 42da7c: xor ebp, ebp */
L_42da7e:
	m->eax = M32((DWORD)(m->esp + 0x11cu));	/* 42da7e: mov eax, dword ptr [esp + 0x11c] */
	m->ecx = (DWORD)(m->esp + 0x94u);	/* 42da85: lea ecx, [esp + 0x94] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42da8c: push eax */
	{ DWORD v_ = 0x50u; m->esp -= 4; M32(m->esp) = v_; }	/* 42da8d: push 0x50 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42da8f: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42da95u; native_call(m, 0x49ecd7u);	/* 42da90: call 0x49ecd7 */
	m->edi = (DWORD)(m->esp + 0xa0u);	/* 42da95: lea edi, [esp + 0xa0] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42da9c: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42da9f: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0xa0u);	/* 42daa1: lea edx, [esp + 0xa0] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42daa8: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42daaa: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 42daac: dec ecx */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42daad: push 0x4ad5dc */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42dab2: push edx */
	M8((DWORD)(m->esp + m->ecx*1 + 0xa7u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 42dab3: mov byte ptr [esp + ecx + 0xa7], bl */
	m->esp -= 4; M32(m->esp) = 0x42dabfu; native_call(m, 0x49ec3bu);	/* 42daba: call 0x49ec3b */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42dabf: push 0x4ad5dc */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42dac4: push ebx */
	m->esp -= 4; M32(m->esp) = 0x42dacau; native_call(m, 0x49ec3bu);	/* 42dac5: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42daca: add esp, 0x1c */
	m->ecx = 0x21u;	/* 42dacd: mov ecx, 0x21 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42dad2: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x10u);	/* 42dad4: lea edi, [esp + 0x10] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 42dad8: rep stosd dword ptr es:[edi], eax */
L_42dada:
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42dada: push 0x4ad5dc */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42dadf: push ebx */
	m->esp -= 4; M32(m->esp) = 0x42dae5u; native_call(m, 0x49ec3bu);	/* 42dae0: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42dae5: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42dae8: cmp eax, ebx */
	if (m->zf) goto L_42db50;	/* 42daea: je 0x42db50 */
	m->edi = m->eax;	/* 42daec: mov edi, eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42daee: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42daf1: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 42daf3: lea edx, [esp + 0x10] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42daf7: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42daf9: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42dafb: sub edi, ecx */
	m->esi = m->edi;	/* 42dafd: mov esi, edi */
	m->edi = m->edx;	/* 42daff: mov edi, edx */
	m->edx = m->ecx;	/* 42db01: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42db03: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42db06: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 42db08: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 42db0a: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42db0b: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42db0e: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 42db10: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42db12: and ecx, 3 */
	{ DWORD a_ = m->ebp, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42db15: cmp ebp, ebx */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 42db17: rep movsb byte ptr es:[edi], byte ptr [esi] */
	if (m->zf) goto L_42db20;	/* 42db19: je 0x42db20 */
	{ DWORD a_ = m->ebp, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42db1b: cmp ebp, 4 */
	if (!m->zf) goto L_42dada;	/* 42db1e: jne 0x42dada */
L_42db20:
	m->edi = 0x4b035cu;	/* 42db20: mov edi, 0x4b035c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42db25: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42db28: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 42db2a: lea edx, [esp + 0x10] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42db2e: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42db30: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42db32: sub edi, ecx */
	m->esi = m->edi;	/* 42db34: mov esi, edi */
	m->edi = m->edx;	/* 42db36: mov edi, edx */
	m->edx = m->ecx;	/* 42db38: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42db3a: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42db3d: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 42db3f: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 42db41: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42db42: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42db45: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 42db47: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42db49: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 42db4c: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_42dada;	/* 42db4e: jmp 0x42dada */
L_42db50:
	{ DWORD a_ = m->ebp, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42db50: cmp ebp, 6 */
	if (!m->cf && !m->zf) goto L_42e02a;	/* 42db53: ja 0x42e02a */
	switch (m->ebp) { case 0: goto L_42db60; case 1: goto L_42db96; case 2: goto L_42dbbf; case 3: goto L_42dbe9; case 4: goto L_42dc37; case 5: goto L_42dfee; case 6: goto L_42e00d; default: abort(); }	/* 42db59: jmp dword ptr [ebp*4 + 0x42e05c] */
L_42db60:
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42db60: lea eax, [esp + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42db64: push eax */
	m->esp -= 4; M32(m->esp) = 0x42db6au; native_call(m, 0x44ac70u);	/* 42db65: call 0x44ac70 */
	m->edi = (DWORD)(m->esp + 0x14u);	/* 42db6a: lea edi, [esp + 0x14] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42db6e: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42db71: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42db73: add esp, 4 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42db76: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42db78: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42db7a: sub edi, ecx */
	m->edx = m->ecx;	/* 42db7c: mov edx, ecx */
	m->esi = m->edi;	/* 42db7e: mov esi, edi */
	m->edi = 0x4ded20u;	/* 42db80: mov edi, 0x4ded20 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42db85: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42db88: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 42db8a: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42db8c: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 42db8f: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_42e02a;	/* 42db91: jmp 0x42e02a */
L_42db96:
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42db96: lea eax, [esp + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42db9a: push eax */
	m->esp -= 4; M32(m->esp) = 0x42dba0u; native_call(m, 0x49ec09u);	/* 42db9b: call 0x49ec09 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42dba0: add esp, 4 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dba3: cmp al, bl */
	M8((DWORD)(0x4ded40u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 42dba5: mov byte ptr [0x4ded40], al */
	if (m->sf != m->of) goto L_42dbb4;	/* 42dbaa: jl 0x42dbb4 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x15u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dbac: cmp al, 0x15 */
	if (m->zf || m->sf != m->of) goto L_42e02a;	/* 42dbae: jle 0x42e02a */
L_42dbb4:
	M8((DWORD)(0x4ded40u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 42dbb4: mov byte ptr [0x4ded40], bl */
	goto L_42e02a;	/* 42dbba: jmp 0x42e02a */
L_42dbbf:
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 42dbbf: lea ecx, [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42dbc3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42dbc9u; native_call(m, 0x49ec09u);	/* 42dbc4: call 0x49ec09 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42dbc9: add esp, 4 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dbcc: cmp al, bl */
	M8((DWORD)(0x4ded41u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 42dbce: mov byte ptr [0x4ded41], al */
	if (m->sf != m->of) goto L_42dbdd;	/* 42dbd3: jl 0x42dbdd */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x10u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dbd5: cmp al, 0x10 */
	if (m->zf || m->sf != m->of) goto L_42e02a;	/* 42dbd7: jle 0x42e02a */
L_42dbdd:
	M8((DWORD)(0x4ded41u)) = (BYTE)(0x8u);	/* 42dbdd: mov byte ptr [0x4ded41], 8 */
	goto L_42e02a;	/* 42dbe4: jmp 0x42e02a */
L_42dbe9:
	m->esi = 0x4b21bcu;	/* 42dbe9: mov esi, 0x4b21bc */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42dbee: lea eax, [esp + 0x10] */
L_42dbf2:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42dbf2: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42dbf4: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dbf6: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42dc23;	/* 42dbf8: jne 0x42dc23 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dbfa: cmp cl, bl */
	if (m->zf) goto L_42dc12;	/* 42dbfc: je 0x42dc12 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42dbfe: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42dc01: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dc03: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42dc23;	/* 42dc06: jne 0x42dc23 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42dc08: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42dc0b: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dc0e: cmp cl, bl */
	if (!m->zf) goto L_42dbf2;	/* 42dc10: jne 0x42dbf2 */
L_42dc12:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42dc12: xor eax, eax */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42dc14: cmp eax, ebx */
	m->eax = (m->eax & ~(0xffu << 0)) | ((((m->zf) ? 1u : 0u) & 0xff) << 0);	/* 42dc16: sete al */
	M8((DWORD)(0x4ded42u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 42dc19: mov byte ptr [0x4ded42], al */
	goto L_42e02a;	/* 42dc1e: jmp 0x42e02a */
L_42dc23:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42dc23: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42dc25: sbb eax, -1 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42dc28: cmp eax, ebx */
	m->eax = (m->eax & ~(0xffu << 0)) | ((((m->zf) ? 1u : 0u) & 0xff) << 0);	/* 42dc2a: sete al */
	M8((DWORD)(0x4ded42u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 42dc2d: mov byte ptr [0x4ded42], al */
	goto L_42e02a;	/* 42dc32: jmp 0x42e02a */
L_42dc37:
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 42dc37: lea ecx, [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42dc3b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42dc41u; native_call(m, 0x44ac70u);	/* 42dc3c: call 0x44ac70 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42dc41: add esp, 4 */
	m->esi = 0x4b22b8u;	/* 42dc44: mov esi, 0x4b22b8 */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42dc49: lea eax, [esp + 0x10] */
L_42dc4d:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42dc4d: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42dc4f: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dc51: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42dc71;	/* 42dc53: jne 0x42dc71 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dc55: cmp cl, bl */
	if (m->zf) goto L_42dc6d;	/* 42dc57: je 0x42dc6d */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42dc59: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42dc5c: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dc5e: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42dc71;	/* 42dc61: jne 0x42dc71 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42dc63: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42dc66: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dc69: cmp cl, bl */
	if (!m->zf) goto L_42dc4d;	/* 42dc6b: jne 0x42dc4d */
L_42dc6d:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42dc6d: xor eax, eax */
	goto L_42dc76;	/* 42dc6f: jmp 0x42dc76 */
L_42dc71:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42dc71: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42dc73: sbb eax, -1 */
L_42dc76:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42dc76: cmp eax, ebx */
	if (!m->zf) goto L_42dc86;	/* 42dc78: jne 0x42dc86 */
	M8((DWORD)(0x4ded43u)) = (BYTE)(0x1u);	/* 42dc7a: mov byte ptr [0x4ded43], 1 */
	goto L_42e02a;	/* 42dc81: jmp 0x42e02a */
L_42dc86:
	m->esi = 0x4b22a8u;	/* 42dc86: mov esi, 0x4b22a8 */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42dc8b: lea eax, [esp + 0x10] */
L_42dc8f:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42dc8f: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42dc91: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dc93: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42dcb3;	/* 42dc95: jne 0x42dcb3 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dc97: cmp cl, bl */
	if (m->zf) goto L_42dcaf;	/* 42dc99: je 0x42dcaf */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42dc9b: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42dc9e: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dca0: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42dcb3;	/* 42dca3: jne 0x42dcb3 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42dca5: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42dca8: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dcab: cmp cl, bl */
	if (!m->zf) goto L_42dc8f;	/* 42dcad: jne 0x42dc8f */
L_42dcaf:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42dcaf: xor eax, eax */
	goto L_42dcb8;	/* 42dcb1: jmp 0x42dcb8 */
L_42dcb3:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42dcb3: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42dcb5: sbb eax, -1 */
L_42dcb8:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42dcb8: cmp eax, ebx */
	if (!m->zf) goto L_42dcc8;	/* 42dcba: jne 0x42dcc8 */
	M8((DWORD)(0x4ded43u)) = (BYTE)(0x2u);	/* 42dcbc: mov byte ptr [0x4ded43], 2 */
	goto L_42e02a;	/* 42dcc3: jmp 0x42e02a */
L_42dcc8:
	m->esi = 0x4b2294u;	/* 42dcc8: mov esi, 0x4b2294 */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42dccd: lea eax, [esp + 0x10] */
L_42dcd1:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42dcd1: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42dcd3: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dcd5: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42dcf5;	/* 42dcd7: jne 0x42dcf5 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dcd9: cmp cl, bl */
	if (m->zf) goto L_42dcf1;	/* 42dcdb: je 0x42dcf1 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42dcdd: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42dce0: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dce2: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42dcf5;	/* 42dce5: jne 0x42dcf5 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42dce7: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42dcea: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dced: cmp cl, bl */
	if (!m->zf) goto L_42dcd1;	/* 42dcef: jne 0x42dcd1 */
L_42dcf1:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42dcf1: xor eax, eax */
	goto L_42dcfa;	/* 42dcf3: jmp 0x42dcfa */
L_42dcf5:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42dcf5: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42dcf7: sbb eax, -1 */
L_42dcfa:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42dcfa: cmp eax, ebx */
	if (!m->zf) goto L_42dd0a;	/* 42dcfc: jne 0x42dd0a */
	M8((DWORD)(0x4ded43u)) = (BYTE)(0x3u);	/* 42dcfe: mov byte ptr [0x4ded43], 3 */
	goto L_42e02a;	/* 42dd05: jmp 0x42e02a */
L_42dd0a:
	m->esi = 0x4b2284u;	/* 42dd0a: mov esi, 0x4b2284 */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42dd0f: lea eax, [esp + 0x10] */
L_42dd13:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42dd13: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42dd15: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dd17: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42dd37;	/* 42dd19: jne 0x42dd37 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dd1b: cmp cl, bl */
	if (m->zf) goto L_42dd33;	/* 42dd1d: je 0x42dd33 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42dd1f: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42dd22: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dd24: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42dd37;	/* 42dd27: jne 0x42dd37 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42dd29: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42dd2c: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dd2f: cmp cl, bl */
	if (!m->zf) goto L_42dd13;	/* 42dd31: jne 0x42dd13 */
L_42dd33:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42dd33: xor eax, eax */
	goto L_42dd3c;	/* 42dd35: jmp 0x42dd3c */
L_42dd37:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42dd37: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42dd39: sbb eax, -1 */
L_42dd3c:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42dd3c: cmp eax, ebx */
	if (!m->zf) goto L_42dd4c;	/* 42dd3e: jne 0x42dd4c */
	M8((DWORD)(0x4ded43u)) = (BYTE)(0x4u);	/* 42dd40: mov byte ptr [0x4ded43], 4 */
	goto L_42e02a;	/* 42dd47: jmp 0x42e02a */
L_42dd4c:
	m->esi = 0x4b2270u;	/* 42dd4c: mov esi, 0x4b2270 */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42dd51: lea eax, [esp + 0x10] */
L_42dd55:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42dd55: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42dd57: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dd59: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42dd79;	/* 42dd5b: jne 0x42dd79 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dd5d: cmp cl, bl */
	if (m->zf) goto L_42dd75;	/* 42dd5f: je 0x42dd75 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42dd61: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42dd64: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dd66: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42dd79;	/* 42dd69: jne 0x42dd79 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42dd6b: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42dd6e: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dd71: cmp cl, bl */
	if (!m->zf) goto L_42dd55;	/* 42dd73: jne 0x42dd55 */
L_42dd75:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42dd75: xor eax, eax */
	goto L_42dd7e;	/* 42dd77: jmp 0x42dd7e */
L_42dd79:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42dd79: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42dd7b: sbb eax, -1 */
L_42dd7e:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42dd7e: cmp eax, ebx */
	if (!m->zf) goto L_42dd8e;	/* 42dd80: jne 0x42dd8e */
	M8((DWORD)(0x4ded43u)) = (BYTE)(0x5u);	/* 42dd82: mov byte ptr [0x4ded43], 5 */
	goto L_42e02a;	/* 42dd89: jmp 0x42e02a */
L_42dd8e:
	m->esi = 0x4b2260u;	/* 42dd8e: mov esi, 0x4b2260 */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42dd93: lea eax, [esp + 0x10] */
L_42dd97:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42dd97: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42dd99: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dd9b: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42ddbb;	/* 42dd9d: jne 0x42ddbb */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dd9f: cmp cl, bl */
	if (m->zf) goto L_42ddb7;	/* 42dda1: je 0x42ddb7 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42dda3: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42dda6: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dda8: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42ddbb;	/* 42ddab: jne 0x42ddbb */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42ddad: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42ddb0: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42ddb3: cmp cl, bl */
	if (!m->zf) goto L_42dd97;	/* 42ddb5: jne 0x42dd97 */
L_42ddb7:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42ddb7: xor eax, eax */
	goto L_42ddc0;	/* 42ddb9: jmp 0x42ddc0 */
L_42ddbb:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42ddbb: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42ddbd: sbb eax, -1 */
L_42ddc0:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42ddc0: cmp eax, ebx */
	if (!m->zf) goto L_42ddd0;	/* 42ddc2: jne 0x42ddd0 */
	M8((DWORD)(0x4ded43u)) = (BYTE)(0x6u);	/* 42ddc4: mov byte ptr [0x4ded43], 6 */
	goto L_42e02a;	/* 42ddcb: jmp 0x42e02a */
L_42ddd0:
	m->esi = 0x4b2248u;	/* 42ddd0: mov esi, 0x4b2248 */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42ddd5: lea eax, [esp + 0x10] */
L_42ddd9:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42ddd9: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42dddb: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dddd: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42ddfd;	/* 42dddf: jne 0x42ddfd */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dde1: cmp cl, bl */
	if (m->zf) goto L_42ddf9;	/* 42dde3: je 0x42ddf9 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42dde5: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42dde8: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42ddea: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42ddfd;	/* 42dded: jne 0x42ddfd */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42ddef: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42ddf2: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42ddf5: cmp cl, bl */
	if (!m->zf) goto L_42ddd9;	/* 42ddf7: jne 0x42ddd9 */
L_42ddf9:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42ddf9: xor eax, eax */
	goto L_42de02;	/* 42ddfb: jmp 0x42de02 */
L_42ddfd:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42ddfd: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42ddff: sbb eax, -1 */
L_42de02:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42de02: cmp eax, ebx */
	if (!m->zf) goto L_42de12;	/* 42de04: jne 0x42de12 */
	M8((DWORD)(0x4ded43u)) = (BYTE)(0x7u);	/* 42de06: mov byte ptr [0x4ded43], 7 */
	goto L_42e02a;	/* 42de0d: jmp 0x42e02a */
L_42de12:
	m->esi = 0x4b2238u;	/* 42de12: mov esi, 0x4b2238 */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42de17: lea eax, [esp + 0x10] */
L_42de1b:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42de1b: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42de1d: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42de1f: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42de3f;	/* 42de21: jne 0x42de3f */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42de23: cmp cl, bl */
	if (m->zf) goto L_42de3b;	/* 42de25: je 0x42de3b */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42de27: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42de2a: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42de2c: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42de3f;	/* 42de2f: jne 0x42de3f */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42de31: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42de34: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42de37: cmp cl, bl */
	if (!m->zf) goto L_42de1b;	/* 42de39: jne 0x42de1b */
L_42de3b:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42de3b: xor eax, eax */
	goto L_42de44;	/* 42de3d: jmp 0x42de44 */
L_42de3f:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42de3f: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42de41: sbb eax, -1 */
L_42de44:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42de44: cmp eax, ebx */
	if (!m->zf) goto L_42de54;	/* 42de46: jne 0x42de54 */
	M8((DWORD)(0x4ded43u)) = (BYTE)(0x8u);	/* 42de48: mov byte ptr [0x4ded43], 8 */
	goto L_42e02a;	/* 42de4f: jmp 0x42e02a */
L_42de54:
	m->esi = 0x4b2224u;	/* 42de54: mov esi, 0x4b2224 */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42de59: lea eax, [esp + 0x10] */
L_42de5d:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42de5d: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42de5f: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42de61: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42de81;	/* 42de63: jne 0x42de81 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42de65: cmp cl, bl */
	if (m->zf) goto L_42de7d;	/* 42de67: je 0x42de7d */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42de69: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42de6c: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42de6e: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42de81;	/* 42de71: jne 0x42de81 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42de73: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42de76: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42de79: cmp cl, bl */
	if (!m->zf) goto L_42de5d;	/* 42de7b: jne 0x42de5d */
L_42de7d:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42de7d: xor eax, eax */
	goto L_42de86;	/* 42de7f: jmp 0x42de86 */
L_42de81:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42de81: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42de83: sbb eax, -1 */
L_42de86:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42de86: cmp eax, ebx */
	if (!m->zf) goto L_42de96;	/* 42de88: jne 0x42de96 */
	M8((DWORD)(0x4ded43u)) = (BYTE)(0x9u);	/* 42de8a: mov byte ptr [0x4ded43], 9 */
	goto L_42e02a;	/* 42de91: jmp 0x42e02a */
L_42de96:
	m->esi = 0x4b2214u;	/* 42de96: mov esi, 0x4b2214 */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42de9b: lea eax, [esp + 0x10] */
L_42de9f:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42de9f: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42dea1: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dea3: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42dec3;	/* 42dea5: jne 0x42dec3 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dea7: cmp cl, bl */
	if (m->zf) goto L_42debf;	/* 42dea9: je 0x42debf */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42deab: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42deae: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42deb0: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42dec3;	/* 42deb3: jne 0x42dec3 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42deb5: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42deb8: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42debb: cmp cl, bl */
	if (!m->zf) goto L_42de9f;	/* 42debd: jne 0x42de9f */
L_42debf:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42debf: xor eax, eax */
	goto L_42dec8;	/* 42dec1: jmp 0x42dec8 */
L_42dec3:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42dec3: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42dec5: sbb eax, -1 */
L_42dec8:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42dec8: cmp eax, ebx */
	if (!m->zf) goto L_42ded8;	/* 42deca: jne 0x42ded8 */
	M8((DWORD)(0x4ded43u)) = (BYTE)(0xau);	/* 42decc: mov byte ptr [0x4ded43], 0xa */
	goto L_42e02a;	/* 42ded3: jmp 0x42e02a */
L_42ded8:
	m->esi = 0x4b21fcu;	/* 42ded8: mov esi, 0x4b21fc */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42dedd: lea eax, [esp + 0x10] */
L_42dee1:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42dee1: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42dee3: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dee5: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42df05;	/* 42dee7: jne 0x42df05 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dee9: cmp cl, bl */
	if (m->zf) goto L_42df01;	/* 42deeb: je 0x42df01 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42deed: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42def0: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42def2: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42df05;	/* 42def5: jne 0x42df05 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42def7: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42defa: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42defd: cmp cl, bl */
	if (!m->zf) goto L_42dee1;	/* 42deff: jne 0x42dee1 */
L_42df01:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42df01: xor eax, eax */
	goto L_42df0a;	/* 42df03: jmp 0x42df0a */
L_42df05:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42df05: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42df07: sbb eax, -1 */
L_42df0a:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42df0a: cmp eax, ebx */
	if (!m->zf) goto L_42df1a;	/* 42df0c: jne 0x42df1a */
	M8((DWORD)(0x4ded43u)) = (BYTE)(0xbu);	/* 42df0e: mov byte ptr [0x4ded43], 0xb */
	goto L_42e02a;	/* 42df15: jmp 0x42e02a */
L_42df1a:
	m->esi = 0x4b21e8u;	/* 42df1a: mov esi, 0x4b21e8 */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42df1f: lea eax, [esp + 0x10] */
L_42df23:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42df23: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42df25: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42df27: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42df47;	/* 42df29: jne 0x42df47 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42df2b: cmp cl, bl */
	if (m->zf) goto L_42df43;	/* 42df2d: je 0x42df43 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42df2f: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42df32: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42df34: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42df47;	/* 42df37: jne 0x42df47 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42df39: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42df3c: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42df3f: cmp cl, bl */
	if (!m->zf) goto L_42df23;	/* 42df41: jne 0x42df23 */
L_42df43:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42df43: xor eax, eax */
	goto L_42df4c;	/* 42df45: jmp 0x42df4c */
L_42df47:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42df47: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42df49: sbb eax, -1 */
L_42df4c:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42df4c: cmp eax, ebx */
	if (!m->zf) goto L_42df5c;	/* 42df4e: jne 0x42df5c */
	M8((DWORD)(0x4ded43u)) = (BYTE)(0xcu);	/* 42df50: mov byte ptr [0x4ded43], 0xc */
	goto L_42e02a;	/* 42df57: jmp 0x42e02a */
L_42df5c:
	m->esi = 0x4b21d8u;	/* 42df5c: mov esi, 0x4b21d8 */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42df61: lea eax, [esp + 0x10] */
L_42df65:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42df65: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42df67: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42df69: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42df89;	/* 42df6b: jne 0x42df89 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42df6d: cmp cl, bl */
	if (m->zf) goto L_42df85;	/* 42df6f: je 0x42df85 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42df71: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42df74: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42df76: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42df89;	/* 42df79: jne 0x42df89 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42df7b: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42df7e: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42df81: cmp cl, bl */
	if (!m->zf) goto L_42df65;	/* 42df83: jne 0x42df65 */
L_42df85:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42df85: xor eax, eax */
	goto L_42df8e;	/* 42df87: jmp 0x42df8e */
L_42df89:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42df89: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42df8b: sbb eax, -1 */
L_42df8e:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42df8e: cmp eax, ebx */
	if (!m->zf) goto L_42df9e;	/* 42df90: jne 0x42df9e */
	M8((DWORD)(0x4ded43u)) = (BYTE)(0xdu);	/* 42df92: mov byte ptr [0x4ded43], 0xd */
	goto L_42e02a;	/* 42df99: jmp 0x42e02a */
L_42df9e:
	m->esi = 0x4b21c0u;	/* 42df9e: mov esi, 0x4b21c0 */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42dfa3: lea eax, [esp + 0x10] */
L_42dfa7:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42dfa7: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42dfa9: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dfab: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42dfd9;	/* 42dfad: jne 0x42dfd9 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dfaf: cmp cl, bl */
	if (m->zf) goto L_42dfc7;	/* 42dfb1: je 0x42dfc7 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42dfb3: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42dfb6: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dfb8: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42dfd9;	/* 42dfbb: jne 0x42dfd9 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42dfbd: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42dfc0: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dfc3: cmp cl, bl */
	if (!m->zf) goto L_42dfa7;	/* 42dfc5: jne 0x42dfa7 */
L_42dfc7:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42dfc7: xor eax, eax */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42dfc9: cmp eax, ebx */
	m->eax = (m->eax & ~(0xffu << 0)) | ((((!m->zf) ? 1u : 0u) & 0xff) << 0);	/* 42dfcb: setne al */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 42dfce: dec eax */
	{ DWORD a_ = m->eax, b_ = 0xeu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42dfcf: and eax, 0xe */
	M8((DWORD)(0x4ded43u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 42dfd2: mov byte ptr [0x4ded43], al */
	goto L_42e02a;	/* 42dfd7: jmp 0x42e02a */
L_42dfd9:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42dfd9: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42dfdb: sbb eax, -1 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42dfde: cmp eax, ebx */
	m->eax = (m->eax & ~(0xffu << 0)) | ((((!m->zf) ? 1u : 0u) & 0xff) << 0);	/* 42dfe0: setne al */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 42dfe3: dec eax */
	{ DWORD a_ = m->eax, b_ = 0xeu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42dfe4: and eax, 0xe */
	M8((DWORD)(0x4ded43u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 42dfe7: mov byte ptr [0x4ded43], al */
	goto L_42e02a;	/* 42dfec: jmp 0x42e02a */
L_42dfee:
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 42dfee: lea ecx, [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42dff2: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42dff8u; native_call(m, 0x49ec09u);	/* 42dff3: call 0x49ec09 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42dff8: add esp, 4 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0xfau & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42dffb: cmp al, 0xfa */
	M8((DWORD)(0x4ded44u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 42dffd: mov byte ptr [0x4ded44], al */
	if (m->cf || m->zf) goto L_42e02a;	/* 42e002: jbe 0x42e02a */
	M8((DWORD)(0x4ded44u)) = (BYTE)(0x1eu);	/* 42e004: mov byte ptr [0x4ded44], 0x1e */
	goto L_42e02a;	/* 42e00b: jmp 0x42e02a */
L_42e00d:
	m->edx = (DWORD)(m->esp + 0x10u);	/* 42e00d: lea edx, [esp + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42e011: push edx */
	m->esp -= 4; M32(m->esp) = 0x42e017u; native_call(m, 0x49ec09u);	/* 42e012: call 0x49ec09 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42e017: add esp, 4 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0xfau & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e01a: cmp al, 0xfa */
	M8((DWORD)(0x4ded45u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 42e01c: mov byte ptr [0x4ded45], al */
	if (m->cf || m->zf) goto L_42e02a;	/* 42e021: jbe 0x42e02a */
	M8((DWORD)(0x4ded45u)) = (BYTE)(0x1eu);	/* 42e023: mov byte ptr [0x4ded45], 0x1e */
L_42e02a:
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 42e02a: inc ebp */
	{ DWORD a_ = m->ebp, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42e02b: cmp ebp, 7 */
	if (m->sf != m->of) goto L_42da7e;	/* 42e02e: jl 0x42da7e */
	m->eax = M32((DWORD)(m->esp + 0x11cu));	/* 42e034: mov eax, dword ptr [esp + 0x11c] */
	m->ecx = (DWORD)(m->esp + 0x94u);	/* 42e03b: lea ecx, [esp + 0x94] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42e042: push eax */
	{ DWORD v_ = 0x50u; m->esp -= 4; M32(m->esp) = v_; }	/* 42e043: push 0x50 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42e045: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42e04bu; native_call(m, 0x49ecd7u);	/* 42e046: call 0x49ecd7 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42e04b: add esp, 0xc */
	m->edi = M32(m->esp); m->esp += 4;	/* 42e04e: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 42e04f: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 42e050: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 42e051: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x108u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42e052: add esp, 0x108 */
	m->esp += 4 + 0; return;	/* 42e058: ret  */
}

/* net_sendGamePacket (0x48dbf0), lifted by tools/lift.py */
static void lift_48dbf0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48dbf0: sub esp, 0x44 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48dbf3: push ebx */
	m->ebx = M32((DWORD)(m->esp + 0x4cu));	/* 48dbf4: mov ebx, dword ptr [esp + 0x4c] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48dbf8: push ebp */
	m->eax = m->ebx;	/* 48dbf9: mov eax, ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48dbfb: push esi */
	m->esi = m->ecx;	/* 48dbfc: mov esi, ecx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48dbfe: shl eax, 4 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 48dc01: xor ebp, ebp */
	m->ecx = M32((DWORD)(m->eax + m->esi*1 + 0x2343006u));	/* 48dc03: mov ecx, dword ptr [eax + esi + 0x2343006] */
	m->eax = (DWORD)(m->eax + m->esi*1 + 0x2343006u);	/* 48dc0a: lea eax, [eax + esi + 0x2343006] */
	{ DWORD a_ = m->ecx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48dc11: cmp ecx, ebp */
	M32((DWORD)(m->esp + 0xcu)) = m->eax;	/* 48dc13: mov dword ptr [esp + 0xc], eax */
	if (m->zf) goto L_48e0d3;	/* 48dc17: je 0x48e0d3 */
	m->eax = M32((DWORD)(m->esi + 0x1f1ca8u));	/* 48dc1d: mov eax, dword ptr [esi + 0x1f1ca8] */
	M8((DWORD)(m->esp + 0x11u)) = (BYTE)(0x1u);	/* 48dc23: mov byte ptr [esp + 0x11], 1 */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48dc28: cmp eax, ebp */
	M8((DWORD)(m->esp + 0x12u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 48dc2a: mov byte ptr [esp + 0x12], bl */
	if (m->zf || m->sf != m->of) goto L_48dc86;	/* 48dc2e: jle 0x48dc86 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x234239du)));	/* 48dc30: fld dword ptr [esi + 0x234239d] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 48dc36: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48dc3c: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48dc3e: test ah, 0x41 */
	if (m->zf) goto L_48dc86;	/* 48dc41: je 0x48dc86 */
	m->ecx = M32((DWORD)(m->esi + 0x1f1cacu));	/* 48dc43: mov ecx, dword ptr [esi + 0x1f1cac] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48dc49: shl ecx, 4 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + m->esi*1 + 0x1f1668u))) & 0xff) << 0);	/* 48dc4c: mov dl, byte ptr [ecx + esi + 0x1f1668] */
	m->eax = (DWORD)(m->ecx + m->esi*1 + 0x0u);	/* 48dc53: lea eax, [ecx + esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1f1cb4u))) & 0xff) << 0);	/* 48dc56: mov cl, byte ptr [esi + 0x1f1cb4] */
	M8((DWORD)(m->esp + 0x13u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 48dc5c: mov byte ptr [esp + 0x13], dl */
	M8((DWORD)(m->esp + 0x14u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 48dc60: mov byte ptr [esp + 0x14], cl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1f166cu))) & 0xff) << 0);	/* 48dc64: mov dl, byte ptr [eax + 0x1f166c] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1f1cb8u))) & 0xff) << 0);	/* 48dc6a: mov al, byte ptr [esi + 0x1f1cb8] */
	m->ecx = (m->ecx & 0xffff0000u) | ((M16((DWORD)(m->esi + 0xbe3000u))) & 0xffff);	/* 48dc70: mov cx, word ptr [esi + 0xbe3000] */
	M8((DWORD)(m->esp + 0x15u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 48dc77: mov byte ptr [esp + 0x15], dl */
	M8((DWORD)(m->esp + 0x16u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 48dc7b: mov byte ptr [esp + 0x16], al */
	M16((DWORD)(m->esp + 0x17u)) = (WORD)((m->ecx & 0xffff));	/* 48dc7f: mov word ptr [esp + 0x17], cx */
	goto L_48dca1;	/* 48dc84: jmp 0x48dca1 */
L_48dc86:
	M8((DWORD)(m->esp + 0x13u)) = (BYTE)(0xffu);	/* 48dc86: mov byte ptr [esp + 0x13], 0xff */
	M8((DWORD)(m->esp + 0x14u)) = (BYTE)(0xffu);	/* 48dc8b: mov byte ptr [esp + 0x14], 0xff */
	M8((DWORD)(m->esp + 0x15u)) = (BYTE)(0xffu);	/* 48dc90: mov byte ptr [esp + 0x15], 0xff */
	M8((DWORD)(m->esp + 0x16u)) = (BYTE)(0xffu);	/* 48dc95: mov byte ptr [esp + 0x16], 0xff */
	M16((DWORD)(m->esp + 0x17u)) = (WORD)(0xffffu);	/* 48dc9a: mov word ptr [esp + 0x17], 0xffff */
L_48dca1:
	m->edx = M32((DWORD)(m->esi + 0x22f0408u));	/* 48dca1: mov edx, dword ptr [esi + 0x22f0408] */
	m->ecx = M32((DWORD)(m->esi + 0x23423c9u));	/* 48dca7: mov ecx, dword ptr [esi + 0x23423c9] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48dcad: push edi */
	M32((DWORD)(m->esp + 0x1du)) = m->edx;	/* 48dcae: mov dword ptr [esp + 0x1d], edx */
	m->eax = m->ecx;	/* 48dcb2: mov eax, ecx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48dcb4: xor edx, edx */
	m->edi = 0x5u;	/* 48dcb6: mov edi, 5 */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->edi; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 48dcbb: div edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x22f040cu)));	/* 48dcbd: fld dword ptr [esi + 0x22f040c] */
	MF((DWORD)(m->esp + 0x21u)) = (float)ST(0); FPOP();	/* 48dcc3: fstp dword ptr [esp + 0x21] */
	M8((DWORD)(m->esp + 0x3fu)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 48dcc7: mov byte ptr [esp + 0x3f], dl */
	m->eax = M32((DWORD)(m->esp + 0x3fu));	/* 48dccb: mov eax, dword ptr [esp + 0x3f] */
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48dccf: and eax, 0xff */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48dcd4: inc ecx */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48dcd5: cmp eax, 4 */
	M32((DWORD)(m->esi + 0x23423c9u)) = m->ecx;	/* 48dcd8: mov dword ptr [esi + 0x23423c9], ecx */
	if (!m->cf && !m->zf) goto L_48defa;	/* 48dcde: ja 0x48defa */
	switch (m->eax) { case 0: goto L_48dceb; case 1: goto L_48dd51; case 2: goto L_48ddc6; case 3: goto L_48de2f; case 4: goto L_48de94; default: abort(); }	/* 48dce4: jmp dword ptr [eax*4 + 0x48e0dc] */
L_48dceb:
	m->ecx = M32((DWORD)(0xa1efb8u));	/* 48dceb: mov ecx, dword ptr [0xa1efb8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48dcf1: xor edx, edx */
	m->eax = m->ecx;	/* 48dcf3: mov eax, ecx */
	m->edi = 0x186a0u;	/* 48dcf5: mov edi, 0x186a0 */
	{ DWORD a_ = m->eax, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48dcfa: and eax, 0xfff */
	m->eax = M32((DWORD)(m->eax*4 + 0xa106f8u));	/* 48dcff: mov eax, dword ptr [eax*4 + 0xa106f8] */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->edi; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 48dd06: div edi */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48dd08: inc ecx */
	M32((DWORD)(0xa1efb8u)) = m->ecx;	/* 48dd09: mov dword ptr [0xa1efb8], ecx */
	m->edi = M32((DWORD)(m->esi + 0x23423e5u));	/* 48dd0f: mov edi, dword ptr [esi + 0x23423e5] */
	m->ecx = m->edx;	/* 48dd15: mov ecx, edx */
	M16((DWORD)(m->esp + 0x40u)) = (WORD)((m->edx & 0xffff));	/* 48dd17: mov word ptr [esp + 0x40], dx */
	{ DWORD a_ = m->ecx, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48dd1c: and ecx, 0xffff */
	m->eax = m->ecx;	/* 48dd22: mov eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48dd24: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->edi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48dd25: idiv edi */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48dd27: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)M32((DWORD)(m->esi + 0x15de6c8u)); m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48dd28: idiv dword ptr [esi + 0x15de6c8] */
	m->eax = m->edx;	/* 48dd2e: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48dd30: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48dd33: add eax, edx */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 48dd35: lea eax, [eax + eax*4] */
	m->edx = (DWORD)(m->edx + m->eax*4 + 0x0u);	/* 48dd38: lea edx, [edx + eax*4] */
	m->eax = m->ecx;	/* 48dd3b: mov eax, ecx */
	m->ecx = m->edx;	/* 48dd3d: mov ecx, edx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48dd3f: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->edi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48dd40: idiv edi */
	m->edx = (DWORD)(m->edx + m->ecx*2 + 0x0u);	/* 48dd42: lea edx, [edx + ecx*2] */
	m->eax = M32((DWORD)(m->esi + m->edx*4 + 0x15bd1f8u));	/* 48dd45: mov eax, dword ptr [esi + edx*4 + 0x15bd1f8] */
	goto L_48def6;	/* 48dd4c: jmp 0x48def6 */
L_48dd51:
	m->ecx = M32((DWORD)(0xa1efb8u));	/* 48dd51: mov ecx, dword ptr [0xa1efb8] */
	m->edi = 0x186a0u;	/* 48dd57: mov edi, 0x186a0 */
	m->edx = m->ecx;	/* 48dd5c: mov edx, ecx */
	{ DWORD a_ = m->edx, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48dd5e: and edx, 0xfff */
	m->eax = M32((DWORD)(m->edx*4 + 0xa106f8u));	/* 48dd64: mov eax, dword ptr [edx*4 + 0xa106f8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48dd6b: xor edx, edx */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->edi; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 48dd6d: div edi */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48dd6f: inc ecx */
	M32((DWORD)(0xa1efb8u)) = m->ecx;	/* 48dd70: mov dword ptr [0xa1efb8], ecx */
	m->edi = M32((DWORD)(m->esi + 0x23423e9u));	/* 48dd76: mov edi, dword ptr [esi + 0x23423e9] */
	m->ecx = m->edx;	/* 48dd7c: mov ecx, edx */
	M16((DWORD)(m->esp + 0x40u)) = (WORD)((m->edx & 0xffff));	/* 48dd7e: mov word ptr [esp + 0x40], dx */
	{ DWORD a_ = m->ecx, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48dd83: and ecx, 0xffff */
	m->eax = m->ecx;	/* 48dd89: mov eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48dd8b: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->edi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48dd8c: idiv edi */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48dd8e: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)M32((DWORD)(m->esi + 0x15fff84u)); m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48dd8f: idiv dword ptr [esi + 0x15fff84] */
	m->eax = (DWORD)(m->edx + m->edx*2 + 0x0u);	/* 48dd95: lea eax, [edx + edx*2] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48dd98: shl eax, 3 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48dd9b: sub eax, edx */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 48dd9d: lea eax, [eax + eax*4] */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48dda0: shl eax, 1 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48dda2: sub eax, edx */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 48dda4: lea edx, [eax + eax*2] */
	m->eax = m->ecx;	/* 48dda7: mov eax, ecx */
	M32((DWORD)(m->esp + 0x58u)) = m->edx;	/* 48dda9: mov dword ptr [esp + 0x58], edx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48ddad: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->edi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48ddae: idiv edi */
	m->eax = M32((DWORD)(m->esp + 0x58u));	/* 48ddb0: mov eax, dword ptr [esp + 0x58] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48ddb4: add eax, edx */
	m->ecx = M32((DWORD)(m->esi + m->eax*4 + 0x15de6ccu));	/* 48ddb6: mov ecx, dword ptr [esi + eax*4 + 0x15de6cc] */
	M32((DWORD)(m->esp + 0x42u)) = m->ecx;	/* 48ddbd: mov dword ptr [esp + 0x42], ecx */
	goto L_48defa;	/* 48ddc1: jmp 0x48defa */
L_48ddc6:
	m->ecx = M32((DWORD)(0xa1efb8u));	/* 48ddc6: mov ecx, dword ptr [0xa1efb8] */
	m->edi = 0x186a0u;	/* 48ddcc: mov edi, 0x186a0 */
	m->edx = m->ecx;	/* 48ddd1: mov edx, ecx */
	{ DWORD a_ = m->edx, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48ddd3: and edx, 0xfff */
	m->eax = M32((DWORD)(m->edx*4 + 0xa106f8u));	/* 48ddd9: mov eax, dword ptr [edx*4 + 0xa106f8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48dde0: xor edx, edx */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->edi; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 48dde2: div edi */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48dde4: inc ecx */
	M32((DWORD)(0xa1efb8u)) = m->ecx;	/* 48dde5: mov dword ptr [0xa1efb8], ecx */
	m->edi = M32((DWORD)(m->esi + 0x23423edu));	/* 48ddeb: mov edi, dword ptr [esi + 0x23423ed] */
	m->ecx = m->edx;	/* 48ddf1: mov ecx, edx */
	M16((DWORD)(m->esp + 0x40u)) = (WORD)((m->edx & 0xffff));	/* 48ddf3: mov word ptr [esp + 0x40], dx */
	{ DWORD a_ = m->ecx, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48ddf8: and ecx, 0xffff */
	m->eax = m->ecx;	/* 48ddfe: mov eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48de00: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->edi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48de01: idiv edi */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48de03: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)M32((DWORD)(m->esi + 0x163b588u)); m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48de04: idiv dword ptr [esi + 0x163b588] */
	m->eax = m->ecx;	/* 48de0a: mov eax, ecx */
	{ long long p_ = (long long)(int)m->edx * (int)0x4c0u; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edx = r_; }	/* 48de0c: imul edx, edx, 0x4c0 */
	M32((DWORD)(m->esp + 0x58u)) = m->edx;	/* 48de12: mov dword ptr [esp + 0x58], edx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48de16: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->edi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48de17: idiv edi */
	m->eax = M32((DWORD)(m->esp + 0x58u));	/* 48de19: mov eax, dword ptr [esp + 0x58] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48de1d: add eax, edx */
	m->ecx = M32((DWORD)(m->esi + m->eax*4 + 0x15fff88u));	/* 48de1f: mov ecx, dword ptr [esi + eax*4 + 0x15fff88] */
	M32((DWORD)(m->esp + 0x42u)) = m->ecx;	/* 48de26: mov dword ptr [esp + 0x42], ecx */
	goto L_48defa;	/* 48de2a: jmp 0x48defa */
L_48de2f:
	m->ecx = M32((DWORD)(0xa1efb8u));	/* 48de2f: mov ecx, dword ptr [0xa1efb8] */
	m->edi = 0x186a0u;	/* 48de35: mov edi, 0x186a0 */
	m->edx = m->ecx;	/* 48de3a: mov edx, ecx */
	{ DWORD a_ = m->edx, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48de3c: and edx, 0xfff */
	m->eax = M32((DWORD)(m->edx*4 + 0xa106f8u));	/* 48de42: mov eax, dword ptr [edx*4 + 0xa106f8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48de49: xor edx, edx */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->edi; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 48de4b: div edi */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48de4d: inc ecx */
	M32((DWORD)(0xa1efb8u)) = m->ecx;	/* 48de4e: mov dword ptr [0xa1efb8], ecx */
	m->edi = M32((DWORD)(m->esi + 0x23423f1u));	/* 48de54: mov edi, dword ptr [esi + 0x23423f1] */
	m->ecx = m->edx;	/* 48de5a: mov ecx, edx */
	M16((DWORD)(m->esp + 0x40u)) = (WORD)((m->edx & 0xffff));	/* 48de5c: mov word ptr [esp + 0x40], dx */
	{ DWORD a_ = m->ecx, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48de61: and ecx, 0xffff */
	m->eax = m->ecx;	/* 48de67: mov eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48de69: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->edi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48de6a: idiv edi */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48de6c: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)M32((DWORD)(m->esi + 0x1679b34u)); m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48de6d: idiv dword ptr [esi + 0x1679b34] */
	m->eax = (DWORD)(m->edx + m->edx*4 + 0x0u);	/* 48de73: lea eax, [edx + edx*4] */
	{ DWORD a_ = m->eax, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48de76: shl eax, 6 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48de79: sub eax, edx */
	m->edx = (DWORD)(m->edx + m->eax*4 + 0x0u);	/* 48de7b: lea edx, [edx + eax*4] */
	m->eax = m->ecx;	/* 48de7e: mov eax, ecx */
	m->ecx = m->edx;	/* 48de80: mov ecx, edx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48de82: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->edi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48de83: idiv edi */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48de85: add ecx, edx */
	m->edx = M32((DWORD)(m->esi + m->ecx*4 + 0x163b58cu));	/* 48de87: mov edx, dword ptr [esi + ecx*4 + 0x163b58c] */
	M32((DWORD)(m->esp + 0x42u)) = m->edx;	/* 48de8e: mov dword ptr [esp + 0x42], edx */
	goto L_48defa;	/* 48de92: jmp 0x48defa */
L_48de94:
	m->ecx = M32((DWORD)(0xa1efb8u));	/* 48de94: mov ecx, dword ptr [0xa1efb8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48de9a: xor edx, edx */
	m->eax = m->ecx;	/* 48de9c: mov eax, ecx */
	m->edi = 0x186a0u;	/* 48de9e: mov edi, 0x186a0 */
	{ DWORD a_ = m->eax, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48dea3: and eax, 0xfff */
	m->eax = M32((DWORD)(m->eax*4 + 0xa106f8u));	/* 48dea8: mov eax, dword ptr [eax*4 + 0xa106f8] */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->edi; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 48deaf: div edi */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48deb1: inc ecx */
	M32((DWORD)(0xa1efb8u)) = m->ecx;	/* 48deb2: mov dword ptr [0xa1efb8], ecx */
	m->edi = M32((DWORD)(m->esi + 0x23423f5u));	/* 48deb8: mov edi, dword ptr [esi + 0x23423f5] */
	m->ecx = m->edx;	/* 48debe: mov ecx, edx */
	M16((DWORD)(m->esp + 0x40u)) = (WORD)((m->edx & 0xffff));	/* 48dec0: mov word ptr [esp + 0x40], dx */
	{ DWORD a_ = m->ecx, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48dec5: and ecx, 0xffff */
	m->eax = m->ecx;	/* 48decb: mov eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48decd: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->edi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48dece: idiv edi */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48ded0: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)M32((DWORD)(m->esi + 0x16c5178u)); m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48ded1: idiv dword ptr [esi + 0x16c5178] */
	m->eax = (DWORD)(m->edx + m->edx*2 + 0x0u);	/* 48ded7: lea eax, [edx + edx*2] */
	{ DWORD a_ = m->eax, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48deda: shl eax, 6 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48dedd: add eax, edx */
	M32((DWORD)(m->esp + 0x58u)) = m->eax;	/* 48dedf: mov dword ptr [esp + 0x58], eax */
	m->eax = m->ecx;	/* 48dee3: mov eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48dee5: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->edi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48dee6: idiv edi */
	m->ecx = M32((DWORD)(m->esp + 0x58u));	/* 48dee8: mov ecx, dword ptr [esp + 0x58] */
	m->edx = (DWORD)(m->edx + m->ecx*8 + 0x0u);	/* 48deec: lea edx, [edx + ecx*8] */
	m->eax = M32((DWORD)(m->esi + m->edx*4 + 0x1679b38u));	/* 48deef: mov eax, dword ptr [esi + edx*4 + 0x1679b38] */
L_48def6:
	M32((DWORD)(m->esp + 0x42u)) = m->eax;	/* 48def6: mov dword ptr [esp + 0x42], eax */
L_48defa:
	m->edi = M32((DWORD)(0xa1efb8u));	/* 48defa: mov edi, dword ptr [0xa1efb8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48df00: xor edx, edx */
	m->ecx = m->edi;	/* 48df02: mov ecx, edi */
	{ DWORD a_ = m->ecx, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48df04: and ecx, 0xfff */
	m->eax = M32((DWORD)(m->ecx*4 + 0xa106f8u));	/* 48df0a: mov eax, dword ptr [ecx*4 + 0xa106f8] */
	m->ecx = 0x186a0u;	/* 48df11: mov ecx, 0x186a0 */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->ecx; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 48df16: div ecx */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 48df18: inc edi */
	M32((DWORD)(0xa1efb8u)) = m->edi;	/* 48df19: mov dword ptr [0xa1efb8], edi */
	m->edi = M32((DWORD)(m->esi + 0x23423f9u));	/* 48df1f: mov edi, dword ptr [esi + 0x23423f9] */
	m->ecx = m->edx;	/* 48df25: mov ecx, edx */
	M16((DWORD)(m->esp + 0x46u)) = (WORD)((m->ecx & 0xffff));	/* 48df27: mov word ptr [esp + 0x46], cx */
	{ DWORD a_ = m->ecx, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48df2c: and ecx, 0xffff */
	m->eax = m->ecx;	/* 48df32: mov eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48df34: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->edi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48df35: idiv edi */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48df37: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)M32((DWORD)(m->esi + 0x175522cu)); m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48df38: idiv dword ptr [esi + 0x175522c] */
	m->eax = (DWORD)(m->edx + m->edx*8 + 0x0u);	/* 48df3e: lea eax, [edx + edx*8] */
	m->eax = (DWORD)(m->edx + m->eax*4 + 0x0u);	/* 48df41: lea eax, [edx + eax*4] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48df44: shl eax, 3 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48df47: sub eax, edx */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 48df49: lea edx, [eax + eax*4] */
	m->eax = m->ecx;	/* 48df4c: mov eax, ecx */
	m->ecx = m->edx;	/* 48df4e: mov ecx, edx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48df50: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->edi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48df51: idiv edi */
	m->edx = (DWORD)(m->edx + m->ecx*2 + 0x0u);	/* 48df53: lea edx, [edx + ecx*2] */
	m->ecx = m->ebx;	/* 48df56: mov ecx, ebx */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48df58: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48df5b: add ecx, ebx */
	m->eax = M32((DWORD)(m->esi + m->edx*4 + 0x16c517cu));	/* 48df5d: mov eax, dword ptr [esi + edx*4 + 0x16c517c] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48df64: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48df67: add ecx, ebx */
	M32((DWORD)(m->esp + 0x48u)) = m->eax;	/* 48df69: mov dword ptr [esp + 0x48], eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48df6d: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48df70: add ecx, ebx */
	M32((DWORD)(m->esp + 0x2du)) = m->ebp;	/* 48df72: mov dword ptr [esp + 0x2d], ebp */
	M32((DWORD)(m->esp + 0x31u)) = m->ebp;	/* 48df76: mov dword ptr [esp + 0x31], ebp */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 48df7a: xor edi, edi */
	m->edx = M32((DWORD)(m->esi + m->ecx*8 + 0x1eccb6cu));	/* 48df7c: mov edx, dword ptr [esi + ecx*8 + 0x1eccb6c] */
	m->eax = M32((DWORD)(m->esi + m->ecx*8 + 0x1eccb70u));	/* 48df83: mov eax, dword ptr [esi + ecx*8 + 0x1eccb70] */
	m->ebx = (DWORD)(m->esi + m->ecx*8 + 0x0u);	/* 48df8a: lea ebx, [esi + ecx*8] */
	M32((DWORD)(m->esp + 0x25u)) = m->edx;	/* 48df8d: mov dword ptr [esp + 0x25], edx */
	M32((DWORD)(m->esp + 0x29u)) = m->eax;	/* 48df91: mov dword ptr [esp + 0x29], eax */
	m->ebp = (DWORD)(m->esi + 0x2343012u);	/* 48df95: lea ebp, [esi + 0x2343012] */
L_48df9b:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48df9b: push edi */
	m->esp -= 4; M32(m->esp) = 0x48dfa1u; native_call(m, 0x4a8700u);	/* 48df9c: call 0x4a8700 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48dfa1: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48dfa4: cmp eax, 1 */
	if (!m->zf) goto L_48dfe9;	/* 48dfa7: jne 0x48dfe9 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0xfffffffcu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48dfa9: cmp dword ptr [ebp - 4], 1 */
	if (!m->zf) goto L_48dfc9;	/* 48dfad: jne 0x48dfc9 */
	m->eax = M32((DWORD)(m->esp + 0x2du));	/* 48dfaf: mov eax, dword ptr [esp + 0x2d] */
	m->edx = 0x1u;	/* 48dfb3: mov edx, 1 */
	m->ecx = m->edi;	/* 48dfb8: mov ecx, edi */
	M32((DWORD)(m->ebp + 0xfffffffcu)) = 0x0u;	/* 48dfba: mov dword ptr [ebp - 4], 0 */
	{ DWORD a_ = m->edx, c_ = (((m->ecx >> 0) & 0xff)) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 48dfc1: shl edx, cl */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48dfc3: or eax, edx */
	M32((DWORD)(m->esp + 0x2du)) = m->eax;	/* 48dfc5: mov dword ptr [esp + 0x2d], eax */
L_48dfc9:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x0u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48dfc9: cmp dword ptr [ebp], 1 */
	if (!m->zf) goto L_48dfe9;	/* 48dfcd: jne 0x48dfe9 */
	m->eax = 0x1u;	/* 48dfcf: mov eax, 1 */
	m->ecx = m->edi;	/* 48dfd4: mov ecx, edi */
	{ DWORD a_ = m->eax, c_ = (((m->ecx >> 0) & 0xff)) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48dfd6: shl eax, cl */
	m->ecx = M32((DWORD)(m->esp + 0x31u));	/* 48dfd8: mov ecx, dword ptr [esp + 0x31] */
	M32((DWORD)(m->ebp + 0x0u)) = 0x0u;	/* 48dfdc: mov dword ptr [ebp], 0 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48dfe3: or ecx, eax */
	M32((DWORD)(m->esp + 0x31u)) = m->ecx;	/* 48dfe5: mov dword ptr [esp + 0x31], ecx */
L_48dfe9:
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 48dfe9: inc edi */
	{ DWORD a_ = m->ebp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 48dfea: add ebp, 0x10 */
	{ DWORD a_ = m->edi, b_ = 0x10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48dfed: cmp edi, 0x10 */
	if (m->sf != m->of) goto L_48df9b;	/* 48dff0: jl 0x48df9b */
	m->ecx = (m->ecx & 0xffff0000u) | ((M16((DWORD)(m->ebx + 0x1eccb54u))) & 0xffff);	/* 48dff2: mov cx, word ptr [ebx + 0x1eccb54] */
	m->eax = (m->eax & 0xffff0000u) | ((M16((DWORD)(m->esi + 0x2221fb8u))) & 0xffff);	/* 48dff9: mov ax, word ptr [esi + 0x2221fb8] */
	m->edx = (m->edx & 0xffff0000u) | ((M16((DWORD)(m->ebx + 0x1eccb58u))) & 0xffff);	/* 48e000: mov dx, word ptr [ebx + 0x1eccb58] */
	M16((DWORD)(m->esp + 0x35u)) = (WORD)((m->ecx & 0xffff));	/* 48e007: mov word ptr [esp + 0x35], cx */
	m->ecx = (m->ecx & 0xffff0000u) | ((M16((DWORD)(m->esi + 0x2221fbcu))) & 0xffff);	/* 48e00c: mov cx, word ptr [esi + 0x2221fbc] */
	M16((DWORD)(m->esp + 0x39u)) = (WORD)((m->eax & 0xffff));	/* 48e013: mov word ptr [esp + 0x39], ax */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 48e018: mov eax, dword ptr [esp + 0x10] */
	M16((DWORD)(m->esp + 0x3bu)) = (WORD)((m->ecx & 0xffff));	/* 48e01c: mov word ptr [esp + 0x3b], cx */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 48e021: lea ecx, [esp + 0x14] */
	M16((DWORD)(m->esp + 0x37u)) = (WORD)((m->edx & 0xffff));	/* 48e025: mov word ptr [esp + 0x37], dx */
	m->edx = (m->edx & 0xffff0000u) | ((M16((DWORD)(m->esi + 0x22f0404u))) & 0xffff);	/* 48e02a: mov dx, word ptr [esi + 0x22f0404] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e031: push ecx */
	M32((DWORD)(m->esi + 0x22f0404u)) = 0xffffffffu;	/* 48e032: mov dword ptr [esi + 0x22f0404], 0xffffffff */
	{ DWORD v_ = 0x40u; m->esp -= 4; M32(m->esp) = v_; }	/* 48e03c: push 0x40 */
	M16((DWORD)(m->esp + 0x45u)) = (WORD)((m->edx & 0xffff));	/* 48e03e: mov word ptr [esp + 0x45], dx */
	M32((DWORD)(m->eax + 0x0u)) = 0x0u;	/* 48e043: mov dword ptr [eax], 0 */
	m->esp -= 4; M32(m->esp) = 0x48e04eu; native_call(m, 0x4a8360u);	/* 48e049: call 0x4a8360 */
	m->ecx = M32((DWORD)(m->esi + 0x2340c78u));	/* 48e04e: mov ecx, dword ptr [esi + 0x2340c78] */
	m->eax = M32((DWORD)(m->esi + 0x2340d1du));	/* 48e054: mov eax, dword ptr [esi + 0x2340d1d] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48e05a: add esp, 8 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48e05d: inc ecx */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e05e: cmp eax, 1 */
	M32((DWORD)(m->esi + 0x2340c78u)) = m->ecx;	/* 48e061: mov dword ptr [esi + 0x2340c78], ecx */
	m->edi = M32(m->esp); m->esp += 4;	/* 48e067: pop edi */
	if (!m->zf) goto L_48e0d3;	/* 48e068: jne 0x48e0d3 */
	m->edx = M32((DWORD)(m->esi + 0x2340d08u));	/* 48e06a: mov edx, dword ptr [esi + 0x2340d08] */
	m->eax = (DWORD)(m->esi + 0x2340d29u);	/* 48e070: lea eax, [esi + 0x2340d29] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e076: push edx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48e077: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48e079: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48e07b: push eax */
	M32((DWORD)(m->esp + 0x64u)) = 0x40u;	/* 48e07c: mov dword ptr [esp + 0x64], 0x40 */
	m->esp -= 4; M32(m->esp) = 0x48e089u; native_call(m, 0x46cc30u);	/* 48e084: call 0x46cc30 */
	m->ecx = M32((DWORD)(m->esi + 0x2340d08u));	/* 48e089: mov ecx, dword ptr [esi + 0x2340d08] */
	m->edx = (DWORD)(m->esi + 0x234240du);	/* 48e08f: lea edx, [esi + 0x234240d] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e095: push ecx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48e096: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48e098: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e09a: push edx */
	m->esp -= 4; M32(m->esp) = 0x48e0a0u; native_call(m, 0x46cc30u);	/* 48e09b: call 0x46cc30 */
	m->eax = M32((DWORD)(m->esi + 0x2340d08u));	/* 48e0a0: mov eax, dword ptr [esi + 0x2340d08] */
	m->ecx = (DWORD)(m->esp + 0x74u);	/* 48e0a6: lea ecx, [esp + 0x74] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48e0aa: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48e0ab: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48e0ad: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e0af: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48e0b5u; native_call(m, 0x46cc30u);	/* 48e0b0: call 0x46cc30 */
	m->edx = M32((DWORD)(m->esi + 0x2340d08u));	/* 48e0b5: mov edx, dword ptr [esi + 0x2340d08] */
	m->eax = M32((DWORD)(m->esp + 0x84u));	/* 48e0bb: mov eax, dword ptr [esp + 0x84] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e0c2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48e0c3: push eax */
	m->ecx = (DWORD)(m->esp + 0x48u);	/* 48e0c4: lea ecx, [esp + 0x48] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48e0c8: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e0ca: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48e0d0u; native_call(m, 0x46cc30u);	/* 48e0cb: call 0x46cc30 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48e0d0: add esp, 0x40 */
L_48e0d3:
	m->esi = M32(m->esp); m->esp += 4;	/* 48e0d3: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 48e0d4: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48e0d5: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48e0d6: add esp, 0x44 */
	m->esp += 4 + 4; return;	/* 48e0d9: ret 4 */
}

/* setup_drawKeyBindingRows (0x421680), lifted by tools/lift.py */
static void lift_421680(X86 *m)
{
	m->eax = M32((DWORD)(0x9da440u));	/* 421680: mov eax, dword ptr [0x9da440] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 421685: push esi */
	m->esi = M32((DWORD)(m->esp + 0x8u));	/* 421686: mov esi, dword ptr [esp + 8] */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42168a: cmp esi, eax */
	if (m->zf) goto L_42203f;	/* 42168c: je 0x42203f */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 421692: push esi */
	m->esp -= 4; M32(m->esp) = 0x421698u; native_call(m, 0x420e50u);	/* 421693: call 0x420e50 */
	m->eax = M32((DWORD)(0x4ddce8u));	/* 421698: mov eax, dword ptr [0x4ddce8] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42169d: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4216a0: sub eax, 0 */
	if (m->zf) goto L_421d32;	/* 4216a3: je 0x421d32 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4216a9: dec eax */
	if (m->zf) goto L_4219ce;	/* 4216aa: je 0x4219ce */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4216b0: dec eax */
	if (!m->zf) goto L_42203a;	/* 4216b1: jne 0x42203a */
	m->eax = M32((DWORD)(0x4de040u));	/* 4216b7: mov eax, dword ptr [0x4de040] */
	{ DWORD a_ = m->eax, b_ = 0x9u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4216bc: cmp eax, 9 */
	if (!m->cf && !m->zf) goto L_42203a;	/* 4216bf: ja 0x42203a */
	switch (m->eax) { case 0: goto L_4216cc; case 1: goto L_421719; case 2: goto L_421766; case 3: goto L_4217b3; case 4: goto L_421800; case 5: goto L_42184d; case 6: goto L_42189a; case 7: goto L_4218e7; case 8: goto L_421934; case 9: goto L_421981; default: abort(); }	/* 4216c5: jmp dword ptr [eax*4 + 0x422044] */
L_4216cc:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 4216cc: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de16cu));	/* 4216d1: mov ecx, dword ptr [0x4de16c] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4216d7: cmp ecx, eax */
	if (m->zf) goto L_4216ed;	/* 4216d9: je 0x4216ed */
	M32((DWORD)(0x4de168u)) = m->esi;	/* 4216db: mov dword ptr [0x4de168], esi */
	M32((DWORD)(0x4de16cu)) = m->eax;	/* 4216e1: mov dword ptr [0x4de16c], eax */
	m->esp -= 4; M32(m->esp) = 0x4216ebu; native_call(m, 0x421350u);	/* 4216e6: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4216eb: pop esi */
	m->esp += 4 + 0; return;	/* 4216ec: ret  */
L_4216ed:
	m->ecx = M32((DWORD)(0x4de168u));	/* 4216ed: mov ecx, dword ptr [0x4de168] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4216f3: cmp ecx, eax */
	if (!m->zf) goto L_421704;	/* 4216f5: jne 0x421704 */
	M32((DWORD)(0x4de168u)) = m->esi;	/* 4216f7: mov dword ptr [0x4de168], esi */
	m->esp -= 4; M32(m->esp) = 0x421702u; native_call(m, 0x421350u);	/* 4216fd: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421702: pop esi */
	m->esp += 4 + 0; return;	/* 421703: ret  */
L_421704:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421704: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 421706: je 0x42203a */
	M32((DWORD)(0x4de16cu)) = m->esi;	/* 42170c: mov dword ptr [0x4de16c], esi */
	m->esp -= 4; M32(m->esp) = 0x421717u; native_call(m, 0x421350u);	/* 421712: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421717: pop esi */
	m->esp += 4 + 0; return;	/* 421718: ret  */
L_421719:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 421719: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de174u));	/* 42171e: mov ecx, dword ptr [0x4de174] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421724: cmp ecx, eax */
	if (m->zf) goto L_42173a;	/* 421726: je 0x42173a */
	M32((DWORD)(0x4de170u)) = m->esi;	/* 421728: mov dword ptr [0x4de170], esi */
	M32((DWORD)(0x4de174u)) = m->eax;	/* 42172e: mov dword ptr [0x4de174], eax */
	m->esp -= 4; M32(m->esp) = 0x421738u; native_call(m, 0x421350u);	/* 421733: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421738: pop esi */
	m->esp += 4 + 0; return;	/* 421739: ret  */
L_42173a:
	m->ecx = M32((DWORD)(0x4de170u));	/* 42173a: mov ecx, dword ptr [0x4de170] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421740: cmp ecx, eax */
	if (!m->zf) goto L_421751;	/* 421742: jne 0x421751 */
	M32((DWORD)(0x4de170u)) = m->esi;	/* 421744: mov dword ptr [0x4de170], esi */
	m->esp -= 4; M32(m->esp) = 0x42174fu; native_call(m, 0x421350u);	/* 42174a: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 42174f: pop esi */
	m->esp += 4 + 0; return;	/* 421750: ret  */
L_421751:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421751: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 421753: je 0x42203a */
	M32((DWORD)(0x4de174u)) = m->esi;	/* 421759: mov dword ptr [0x4de174], esi */
	m->esp -= 4; M32(m->esp) = 0x421764u; native_call(m, 0x421350u);	/* 42175f: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421764: pop esi */
	m->esp += 4 + 0; return;	/* 421765: ret  */
L_421766:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 421766: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de17cu));	/* 42176b: mov ecx, dword ptr [0x4de17c] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421771: cmp ecx, eax */
	if (m->zf) goto L_421787;	/* 421773: je 0x421787 */
	M32((DWORD)(0x4de178u)) = m->esi;	/* 421775: mov dword ptr [0x4de178], esi */
	M32((DWORD)(0x4de17cu)) = m->eax;	/* 42177b: mov dword ptr [0x4de17c], eax */
	m->esp -= 4; M32(m->esp) = 0x421785u; native_call(m, 0x421350u);	/* 421780: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421785: pop esi */
	m->esp += 4 + 0; return;	/* 421786: ret  */
L_421787:
	m->ecx = M32((DWORD)(0x4de178u));	/* 421787: mov ecx, dword ptr [0x4de178] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42178d: cmp ecx, eax */
	if (!m->zf) goto L_42179e;	/* 42178f: jne 0x42179e */
	M32((DWORD)(0x4de178u)) = m->esi;	/* 421791: mov dword ptr [0x4de178], esi */
	m->esp -= 4; M32(m->esp) = 0x42179cu; native_call(m, 0x421350u);	/* 421797: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 42179c: pop esi */
	m->esp += 4 + 0; return;	/* 42179d: ret  */
L_42179e:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42179e: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 4217a0: je 0x42203a */
	M32((DWORD)(0x4de17cu)) = m->esi;	/* 4217a6: mov dword ptr [0x4de17c], esi */
	m->esp -= 4; M32(m->esp) = 0x4217b1u; native_call(m, 0x421350u);	/* 4217ac: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4217b1: pop esi */
	m->esp += 4 + 0; return;	/* 4217b2: ret  */
L_4217b3:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 4217b3: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de184u));	/* 4217b8: mov ecx, dword ptr [0x4de184] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4217be: cmp ecx, eax */
	if (m->zf) goto L_4217d4;	/* 4217c0: je 0x4217d4 */
	M32((DWORD)(0x4de180u)) = m->esi;	/* 4217c2: mov dword ptr [0x4de180], esi */
	M32((DWORD)(0x4de184u)) = m->eax;	/* 4217c8: mov dword ptr [0x4de184], eax */
	m->esp -= 4; M32(m->esp) = 0x4217d2u; native_call(m, 0x421350u);	/* 4217cd: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4217d2: pop esi */
	m->esp += 4 + 0; return;	/* 4217d3: ret  */
L_4217d4:
	m->ecx = M32((DWORD)(0x4de180u));	/* 4217d4: mov ecx, dword ptr [0x4de180] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4217da: cmp ecx, eax */
	if (!m->zf) goto L_4217eb;	/* 4217dc: jne 0x4217eb */
	M32((DWORD)(0x4de180u)) = m->esi;	/* 4217de: mov dword ptr [0x4de180], esi */
	m->esp -= 4; M32(m->esp) = 0x4217e9u; native_call(m, 0x421350u);	/* 4217e4: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4217e9: pop esi */
	m->esp += 4 + 0; return;	/* 4217ea: ret  */
L_4217eb:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4217eb: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 4217ed: je 0x42203a */
	M32((DWORD)(0x4de184u)) = m->esi;	/* 4217f3: mov dword ptr [0x4de184], esi */
	m->esp -= 4; M32(m->esp) = 0x4217feu; native_call(m, 0x421350u);	/* 4217f9: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4217fe: pop esi */
	m->esp += 4 + 0; return;	/* 4217ff: ret  */
L_421800:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 421800: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de18cu));	/* 421805: mov ecx, dword ptr [0x4de18c] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42180b: cmp ecx, eax */
	if (m->zf) goto L_421821;	/* 42180d: je 0x421821 */
	M32((DWORD)(0x4de188u)) = m->esi;	/* 42180f: mov dword ptr [0x4de188], esi */
	M32((DWORD)(0x4de18cu)) = m->eax;	/* 421815: mov dword ptr [0x4de18c], eax */
	m->esp -= 4; M32(m->esp) = 0x42181fu; native_call(m, 0x421350u);	/* 42181a: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 42181f: pop esi */
	m->esp += 4 + 0; return;	/* 421820: ret  */
L_421821:
	m->ecx = M32((DWORD)(0x4de188u));	/* 421821: mov ecx, dword ptr [0x4de188] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421827: cmp ecx, eax */
	if (!m->zf) goto L_421838;	/* 421829: jne 0x421838 */
	M32((DWORD)(0x4de188u)) = m->esi;	/* 42182b: mov dword ptr [0x4de188], esi */
	m->esp -= 4; M32(m->esp) = 0x421836u; native_call(m, 0x421350u);	/* 421831: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421836: pop esi */
	m->esp += 4 + 0; return;	/* 421837: ret  */
L_421838:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421838: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 42183a: je 0x42203a */
	M32((DWORD)(0x4de18cu)) = m->esi;	/* 421840: mov dword ptr [0x4de18c], esi */
	m->esp -= 4; M32(m->esp) = 0x42184bu; native_call(m, 0x421350u);	/* 421846: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 42184b: pop esi */
	m->esp += 4 + 0; return;	/* 42184c: ret  */
L_42184d:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 42184d: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de194u));	/* 421852: mov ecx, dword ptr [0x4de194] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421858: cmp ecx, eax */
	if (m->zf) goto L_42186e;	/* 42185a: je 0x42186e */
	M32((DWORD)(0x4de190u)) = m->esi;	/* 42185c: mov dword ptr [0x4de190], esi */
	M32((DWORD)(0x4de194u)) = m->eax;	/* 421862: mov dword ptr [0x4de194], eax */
	m->esp -= 4; M32(m->esp) = 0x42186cu; native_call(m, 0x421350u);	/* 421867: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 42186c: pop esi */
	m->esp += 4 + 0; return;	/* 42186d: ret  */
L_42186e:
	m->ecx = M32((DWORD)(0x4de190u));	/* 42186e: mov ecx, dword ptr [0x4de190] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421874: cmp ecx, eax */
	if (!m->zf) goto L_421885;	/* 421876: jne 0x421885 */
	M32((DWORD)(0x4de190u)) = m->esi;	/* 421878: mov dword ptr [0x4de190], esi */
	m->esp -= 4; M32(m->esp) = 0x421883u; native_call(m, 0x421350u);	/* 42187e: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421883: pop esi */
	m->esp += 4 + 0; return;	/* 421884: ret  */
L_421885:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421885: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 421887: je 0x42203a */
	M32((DWORD)(0x4de194u)) = m->esi;	/* 42188d: mov dword ptr [0x4de194], esi */
	m->esp -= 4; M32(m->esp) = 0x421898u; native_call(m, 0x421350u);	/* 421893: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421898: pop esi */
	m->esp += 4 + 0; return;	/* 421899: ret  */
L_42189a:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 42189a: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de1a4u));	/* 42189f: mov ecx, dword ptr [0x4de1a4] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4218a5: cmp ecx, eax */
	if (m->zf) goto L_4218bb;	/* 4218a7: je 0x4218bb */
	M32((DWORD)(0x4de1a0u)) = m->esi;	/* 4218a9: mov dword ptr [0x4de1a0], esi */
	M32((DWORD)(0x4de1a4u)) = m->eax;	/* 4218af: mov dword ptr [0x4de1a4], eax */
	m->esp -= 4; M32(m->esp) = 0x4218b9u; native_call(m, 0x421350u);	/* 4218b4: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4218b9: pop esi */
	m->esp += 4 + 0; return;	/* 4218ba: ret  */
L_4218bb:
	m->ecx = M32((DWORD)(0x4de1a0u));	/* 4218bb: mov ecx, dword ptr [0x4de1a0] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4218c1: cmp ecx, eax */
	if (!m->zf) goto L_4218d2;	/* 4218c3: jne 0x4218d2 */
	M32((DWORD)(0x4de1a0u)) = m->esi;	/* 4218c5: mov dword ptr [0x4de1a0], esi */
	m->esp -= 4; M32(m->esp) = 0x4218d0u; native_call(m, 0x421350u);	/* 4218cb: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4218d0: pop esi */
	m->esp += 4 + 0; return;	/* 4218d1: ret  */
L_4218d2:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4218d2: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 4218d4: je 0x42203a */
	M32((DWORD)(0x4de1a4u)) = m->esi;	/* 4218da: mov dword ptr [0x4de1a4], esi */
	m->esp -= 4; M32(m->esp) = 0x4218e5u; native_call(m, 0x421350u);	/* 4218e0: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4218e5: pop esi */
	m->esp += 4 + 0; return;	/* 4218e6: ret  */
L_4218e7:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 4218e7: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de1acu));	/* 4218ec: mov ecx, dword ptr [0x4de1ac] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4218f2: cmp ecx, eax */
	if (m->zf) goto L_421908;	/* 4218f4: je 0x421908 */
	M32((DWORD)(0x4de1a8u)) = m->esi;	/* 4218f6: mov dword ptr [0x4de1a8], esi */
	M32((DWORD)(0x4de1acu)) = m->eax;	/* 4218fc: mov dword ptr [0x4de1ac], eax */
	m->esp -= 4; M32(m->esp) = 0x421906u; native_call(m, 0x421350u);	/* 421901: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421906: pop esi */
	m->esp += 4 + 0; return;	/* 421907: ret  */
L_421908:
	m->ecx = M32((DWORD)(0x4de1a8u));	/* 421908: mov ecx, dword ptr [0x4de1a8] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42190e: cmp ecx, eax */
	if (!m->zf) goto L_42191f;	/* 421910: jne 0x42191f */
	M32((DWORD)(0x4de1a8u)) = m->esi;	/* 421912: mov dword ptr [0x4de1a8], esi */
	m->esp -= 4; M32(m->esp) = 0x42191du; native_call(m, 0x421350u);	/* 421918: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 42191d: pop esi */
	m->esp += 4 + 0; return;	/* 42191e: ret  */
L_42191f:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42191f: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 421921: je 0x42203a */
	M32((DWORD)(0x4de1acu)) = m->esi;	/* 421927: mov dword ptr [0x4de1ac], esi */
	m->esp -= 4; M32(m->esp) = 0x421932u; native_call(m, 0x421350u);	/* 42192d: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421932: pop esi */
	m->esp += 4 + 0; return;	/* 421933: ret  */
L_421934:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 421934: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de1b4u));	/* 421939: mov ecx, dword ptr [0x4de1b4] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42193f: cmp ecx, eax */
	if (m->zf) goto L_421955;	/* 421941: je 0x421955 */
	M32((DWORD)(0x4de1b0u)) = m->esi;	/* 421943: mov dword ptr [0x4de1b0], esi */
	M32((DWORD)(0x4de1b4u)) = m->eax;	/* 421949: mov dword ptr [0x4de1b4], eax */
	m->esp -= 4; M32(m->esp) = 0x421953u; native_call(m, 0x421350u);	/* 42194e: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421953: pop esi */
	m->esp += 4 + 0; return;	/* 421954: ret  */
L_421955:
	m->ecx = M32((DWORD)(0x4de1b0u));	/* 421955: mov ecx, dword ptr [0x4de1b0] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42195b: cmp ecx, eax */
	if (!m->zf) goto L_42196c;	/* 42195d: jne 0x42196c */
	M32((DWORD)(0x4de1b0u)) = m->esi;	/* 42195f: mov dword ptr [0x4de1b0], esi */
	m->esp -= 4; M32(m->esp) = 0x42196au; native_call(m, 0x421350u);	/* 421965: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 42196a: pop esi */
	m->esp += 4 + 0; return;	/* 42196b: ret  */
L_42196c:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42196c: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 42196e: je 0x42203a */
	M32((DWORD)(0x4de1b4u)) = m->esi;	/* 421974: mov dword ptr [0x4de1b4], esi */
	m->esp -= 4; M32(m->esp) = 0x42197fu; native_call(m, 0x421350u);	/* 42197a: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 42197f: pop esi */
	m->esp += 4 + 0; return;	/* 421980: ret  */
L_421981:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 421981: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de1bcu));	/* 421986: mov ecx, dword ptr [0x4de1bc] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42198c: cmp ecx, eax */
	if (m->zf) goto L_4219a2;	/* 42198e: je 0x4219a2 */
	M32((DWORD)(0x4de1b8u)) = m->esi;	/* 421990: mov dword ptr [0x4de1b8], esi */
	M32((DWORD)(0x4de1bcu)) = m->eax;	/* 421996: mov dword ptr [0x4de1bc], eax */
	m->esp -= 4; M32(m->esp) = 0x4219a0u; native_call(m, 0x421350u);	/* 42199b: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4219a0: pop esi */
	m->esp += 4 + 0; return;	/* 4219a1: ret  */
L_4219a2:
	m->ecx = M32((DWORD)(0x4de1b8u));	/* 4219a2: mov ecx, dword ptr [0x4de1b8] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4219a8: cmp ecx, eax */
	if (!m->zf) goto L_4219b9;	/* 4219aa: jne 0x4219b9 */
	M32((DWORD)(0x4de1b8u)) = m->esi;	/* 4219ac: mov dword ptr [0x4de1b8], esi */
	m->esp -= 4; M32(m->esp) = 0x4219b7u; native_call(m, 0x421350u);	/* 4219b2: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4219b7: pop esi */
	m->esp += 4 + 0; return;	/* 4219b8: ret  */
L_4219b9:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4219b9: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 4219bb: je 0x42203a */
	M32((DWORD)(0x4de1bcu)) = m->esi;	/* 4219c1: mov dword ptr [0x4de1bc], esi */
	m->esp -= 4; M32(m->esp) = 0x4219ccu; native_call(m, 0x421350u);	/* 4219c7: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4219cc: pop esi */
	m->esp += 4 + 0; return;	/* 4219cd: ret  */
L_4219ce:
	m->eax = M32((DWORD)(0x4de040u));	/* 4219ce: mov eax, dword ptr [0x4de040] */
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4219d3: cmp eax, 0xa */
	if (!m->cf && !m->zf) goto L_42203a;	/* 4219d6: ja 0x42203a */
	switch (m->eax) { case 0: goto L_4219e3; case 1: goto L_421a30; case 2: goto L_421a7d; case 3: goto L_421aca; case 4: goto L_421b17; case 5: goto L_421b64; case 6: goto L_421bb1; case 7: goto L_421bfe; case 8: goto L_421c4b; case 9: goto L_421c98; case 10: goto L_421ce5; default: abort(); }	/* 4219dc: jmp dword ptr [eax*4 + 0x42206c] */
L_4219e3:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 4219e3: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de114u));	/* 4219e8: mov ecx, dword ptr [0x4de114] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4219ee: cmp ecx, eax */
	if (m->zf) goto L_421a04;	/* 4219f0: je 0x421a04 */
	M32((DWORD)(0x4de110u)) = m->esi;	/* 4219f2: mov dword ptr [0x4de110], esi */
	M32((DWORD)(0x4de114u)) = m->eax;	/* 4219f8: mov dword ptr [0x4de114], eax */
	m->esp -= 4; M32(m->esp) = 0x421a02u; native_call(m, 0x421350u);	/* 4219fd: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421a02: pop esi */
	m->esp += 4 + 0; return;	/* 421a03: ret  */
L_421a04:
	m->ecx = M32((DWORD)(0x4de110u));	/* 421a04: mov ecx, dword ptr [0x4de110] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421a0a: cmp ecx, eax */
	if (!m->zf) goto L_421a1b;	/* 421a0c: jne 0x421a1b */
	M32((DWORD)(0x4de110u)) = m->esi;	/* 421a0e: mov dword ptr [0x4de110], esi */
	m->esp -= 4; M32(m->esp) = 0x421a19u; native_call(m, 0x421350u);	/* 421a14: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421a19: pop esi */
	m->esp += 4 + 0; return;	/* 421a1a: ret  */
L_421a1b:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421a1b: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 421a1d: je 0x42203a */
	M32((DWORD)(0x4de114u)) = m->esi;	/* 421a23: mov dword ptr [0x4de114], esi */
	m->esp -= 4; M32(m->esp) = 0x421a2eu; native_call(m, 0x421350u);	/* 421a29: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421a2e: pop esi */
	m->esp += 4 + 0; return;	/* 421a2f: ret  */
L_421a30:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 421a30: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de11cu));	/* 421a35: mov ecx, dword ptr [0x4de11c] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421a3b: cmp ecx, eax */
	if (m->zf) goto L_421a51;	/* 421a3d: je 0x421a51 */
	M32((DWORD)(0x4de118u)) = m->esi;	/* 421a3f: mov dword ptr [0x4de118], esi */
	M32((DWORD)(0x4de11cu)) = m->eax;	/* 421a45: mov dword ptr [0x4de11c], eax */
	m->esp -= 4; M32(m->esp) = 0x421a4fu; native_call(m, 0x421350u);	/* 421a4a: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421a4f: pop esi */
	m->esp += 4 + 0; return;	/* 421a50: ret  */
L_421a51:
	m->ecx = M32((DWORD)(0x4de118u));	/* 421a51: mov ecx, dword ptr [0x4de118] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421a57: cmp ecx, eax */
	if (!m->zf) goto L_421a68;	/* 421a59: jne 0x421a68 */
	M32((DWORD)(0x4de118u)) = m->esi;	/* 421a5b: mov dword ptr [0x4de118], esi */
	m->esp -= 4; M32(m->esp) = 0x421a66u; native_call(m, 0x421350u);	/* 421a61: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421a66: pop esi */
	m->esp += 4 + 0; return;	/* 421a67: ret  */
L_421a68:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421a68: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 421a6a: je 0x42203a */
	M32((DWORD)(0x4de11cu)) = m->esi;	/* 421a70: mov dword ptr [0x4de11c], esi */
	m->esp -= 4; M32(m->esp) = 0x421a7bu; native_call(m, 0x421350u);	/* 421a76: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421a7b: pop esi */
	m->esp += 4 + 0; return;	/* 421a7c: ret  */
L_421a7d:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 421a7d: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de124u));	/* 421a82: mov ecx, dword ptr [0x4de124] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421a88: cmp ecx, eax */
	if (m->zf) goto L_421a9e;	/* 421a8a: je 0x421a9e */
	M32((DWORD)(0x4de120u)) = m->esi;	/* 421a8c: mov dword ptr [0x4de120], esi */
	M32((DWORD)(0x4de124u)) = m->eax;	/* 421a92: mov dword ptr [0x4de124], eax */
	m->esp -= 4; M32(m->esp) = 0x421a9cu; native_call(m, 0x421350u);	/* 421a97: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421a9c: pop esi */
	m->esp += 4 + 0; return;	/* 421a9d: ret  */
L_421a9e:
	m->ecx = M32((DWORD)(0x4de120u));	/* 421a9e: mov ecx, dword ptr [0x4de120] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421aa4: cmp ecx, eax */
	if (!m->zf) goto L_421ab5;	/* 421aa6: jne 0x421ab5 */
	M32((DWORD)(0x4de120u)) = m->esi;	/* 421aa8: mov dword ptr [0x4de120], esi */
	m->esp -= 4; M32(m->esp) = 0x421ab3u; native_call(m, 0x421350u);	/* 421aae: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421ab3: pop esi */
	m->esp += 4 + 0; return;	/* 421ab4: ret  */
L_421ab5:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421ab5: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 421ab7: je 0x42203a */
	M32((DWORD)(0x4de124u)) = m->esi;	/* 421abd: mov dword ptr [0x4de124], esi */
	m->esp -= 4; M32(m->esp) = 0x421ac8u; native_call(m, 0x421350u);	/* 421ac3: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421ac8: pop esi */
	m->esp += 4 + 0; return;	/* 421ac9: ret  */
L_421aca:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 421aca: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de13cu));	/* 421acf: mov ecx, dword ptr [0x4de13c] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421ad5: cmp ecx, eax */
	if (m->zf) goto L_421aeb;	/* 421ad7: je 0x421aeb */
	M32((DWORD)(0x4de138u)) = m->esi;	/* 421ad9: mov dword ptr [0x4de138], esi */
	M32((DWORD)(0x4de13cu)) = m->eax;	/* 421adf: mov dword ptr [0x4de13c], eax */
	m->esp -= 4; M32(m->esp) = 0x421ae9u; native_call(m, 0x421350u);	/* 421ae4: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421ae9: pop esi */
	m->esp += 4 + 0; return;	/* 421aea: ret  */
L_421aeb:
	m->ecx = M32((DWORD)(0x4de138u));	/* 421aeb: mov ecx, dword ptr [0x4de138] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421af1: cmp ecx, eax */
	if (!m->zf) goto L_421b02;	/* 421af3: jne 0x421b02 */
	M32((DWORD)(0x4de138u)) = m->esi;	/* 421af5: mov dword ptr [0x4de138], esi */
	m->esp -= 4; M32(m->esp) = 0x421b00u; native_call(m, 0x421350u);	/* 421afb: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421b00: pop esi */
	m->esp += 4 + 0; return;	/* 421b01: ret  */
L_421b02:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421b02: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 421b04: je 0x42203a */
	M32((DWORD)(0x4de13cu)) = m->esi;	/* 421b0a: mov dword ptr [0x4de13c], esi */
	m->esp -= 4; M32(m->esp) = 0x421b15u; native_call(m, 0x421350u);	/* 421b10: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421b15: pop esi */
	m->esp += 4 + 0; return;	/* 421b16: ret  */
L_421b17:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 421b17: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de144u));	/* 421b1c: mov ecx, dword ptr [0x4de144] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421b22: cmp ecx, eax */
	if (m->zf) goto L_421b38;	/* 421b24: je 0x421b38 */
	M32((DWORD)(0x4de140u)) = m->esi;	/* 421b26: mov dword ptr [0x4de140], esi */
	M32((DWORD)(0x4de144u)) = m->eax;	/* 421b2c: mov dword ptr [0x4de144], eax */
	m->esp -= 4; M32(m->esp) = 0x421b36u; native_call(m, 0x421350u);	/* 421b31: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421b36: pop esi */
	m->esp += 4 + 0; return;	/* 421b37: ret  */
L_421b38:
	m->ecx = M32((DWORD)(0x4de140u));	/* 421b38: mov ecx, dword ptr [0x4de140] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421b3e: cmp ecx, eax */
	if (!m->zf) goto L_421b4f;	/* 421b40: jne 0x421b4f */
	M32((DWORD)(0x4de140u)) = m->esi;	/* 421b42: mov dword ptr [0x4de140], esi */
	m->esp -= 4; M32(m->esp) = 0x421b4du; native_call(m, 0x421350u);	/* 421b48: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421b4d: pop esi */
	m->esp += 4 + 0; return;	/* 421b4e: ret  */
L_421b4f:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421b4f: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 421b51: je 0x42203a */
	M32((DWORD)(0x4de144u)) = m->esi;	/* 421b57: mov dword ptr [0x4de144], esi */
	m->esp -= 4; M32(m->esp) = 0x421b62u; native_call(m, 0x421350u);	/* 421b5d: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421b62: pop esi */
	m->esp += 4 + 0; return;	/* 421b63: ret  */
L_421b64:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 421b64: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de14cu));	/* 421b69: mov ecx, dword ptr [0x4de14c] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421b6f: cmp ecx, eax */
	if (m->zf) goto L_421b85;	/* 421b71: je 0x421b85 */
	M32((DWORD)(0x4de148u)) = m->esi;	/* 421b73: mov dword ptr [0x4de148], esi */
	M32((DWORD)(0x4de14cu)) = m->eax;	/* 421b79: mov dword ptr [0x4de14c], eax */
	m->esp -= 4; M32(m->esp) = 0x421b83u; native_call(m, 0x421350u);	/* 421b7e: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421b83: pop esi */
	m->esp += 4 + 0; return;	/* 421b84: ret  */
L_421b85:
	m->ecx = M32((DWORD)(0x4de148u));	/* 421b85: mov ecx, dword ptr [0x4de148] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421b8b: cmp ecx, eax */
	if (!m->zf) goto L_421b9c;	/* 421b8d: jne 0x421b9c */
	M32((DWORD)(0x4de148u)) = m->esi;	/* 421b8f: mov dword ptr [0x4de148], esi */
	m->esp -= 4; M32(m->esp) = 0x421b9au; native_call(m, 0x421350u);	/* 421b95: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421b9a: pop esi */
	m->esp += 4 + 0; return;	/* 421b9b: ret  */
L_421b9c:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421b9c: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 421b9e: je 0x42203a */
	M32((DWORD)(0x4de14cu)) = m->esi;	/* 421ba4: mov dword ptr [0x4de14c], esi */
	m->esp -= 4; M32(m->esp) = 0x421bafu; native_call(m, 0x421350u);	/* 421baa: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421baf: pop esi */
	m->esp += 4 + 0; return;	/* 421bb0: ret  */
L_421bb1:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 421bb1: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de154u));	/* 421bb6: mov ecx, dword ptr [0x4de154] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421bbc: cmp ecx, eax */
	if (m->zf) goto L_421bd2;	/* 421bbe: je 0x421bd2 */
	M32((DWORD)(0x4de150u)) = m->esi;	/* 421bc0: mov dword ptr [0x4de150], esi */
	M32((DWORD)(0x4de154u)) = m->eax;	/* 421bc6: mov dword ptr [0x4de154], eax */
	m->esp -= 4; M32(m->esp) = 0x421bd0u; native_call(m, 0x421350u);	/* 421bcb: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421bd0: pop esi */
	m->esp += 4 + 0; return;	/* 421bd1: ret  */
L_421bd2:
	m->ecx = M32((DWORD)(0x4de150u));	/* 421bd2: mov ecx, dword ptr [0x4de150] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421bd8: cmp ecx, eax */
	if (!m->zf) goto L_421be9;	/* 421bda: jne 0x421be9 */
	M32((DWORD)(0x4de150u)) = m->esi;	/* 421bdc: mov dword ptr [0x4de150], esi */
	m->esp -= 4; M32(m->esp) = 0x421be7u; native_call(m, 0x421350u);	/* 421be2: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421be7: pop esi */
	m->esp += 4 + 0; return;	/* 421be8: ret  */
L_421be9:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421be9: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 421beb: je 0x42203a */
	M32((DWORD)(0x4de154u)) = m->esi;	/* 421bf1: mov dword ptr [0x4de154], esi */
	m->esp -= 4; M32(m->esp) = 0x421bfcu; native_call(m, 0x421350u);	/* 421bf7: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421bfc: pop esi */
	m->esp += 4 + 0; return;	/* 421bfd: ret  */
L_421bfe:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 421bfe: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de12cu));	/* 421c03: mov ecx, dword ptr [0x4de12c] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421c09: cmp ecx, eax */
	if (m->zf) goto L_421c1f;	/* 421c0b: je 0x421c1f */
	M32((DWORD)(0x4de128u)) = m->esi;	/* 421c0d: mov dword ptr [0x4de128], esi */
	M32((DWORD)(0x4de12cu)) = m->eax;	/* 421c13: mov dword ptr [0x4de12c], eax */
	m->esp -= 4; M32(m->esp) = 0x421c1du; native_call(m, 0x421350u);	/* 421c18: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421c1d: pop esi */
	m->esp += 4 + 0; return;	/* 421c1e: ret  */
L_421c1f:
	m->ecx = M32((DWORD)(0x4de128u));	/* 421c1f: mov ecx, dword ptr [0x4de128] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421c25: cmp ecx, eax */
	if (!m->zf) goto L_421c36;	/* 421c27: jne 0x421c36 */
	M32((DWORD)(0x4de128u)) = m->esi;	/* 421c29: mov dword ptr [0x4de128], esi */
	m->esp -= 4; M32(m->esp) = 0x421c34u; native_call(m, 0x421350u);	/* 421c2f: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421c34: pop esi */
	m->esp += 4 + 0; return;	/* 421c35: ret  */
L_421c36:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421c36: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 421c38: je 0x42203a */
	M32((DWORD)(0x4de12cu)) = m->esi;	/* 421c3e: mov dword ptr [0x4de12c], esi */
	m->esp -= 4; M32(m->esp) = 0x421c49u; native_call(m, 0x421350u);	/* 421c44: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421c49: pop esi */
	m->esp += 4 + 0; return;	/* 421c4a: ret  */
L_421c4b:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 421c4b: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de134u));	/* 421c50: mov ecx, dword ptr [0x4de134] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421c56: cmp ecx, eax */
	if (m->zf) goto L_421c6c;	/* 421c58: je 0x421c6c */
	M32((DWORD)(0x4de130u)) = m->esi;	/* 421c5a: mov dword ptr [0x4de130], esi */
	M32((DWORD)(0x4de134u)) = m->eax;	/* 421c60: mov dword ptr [0x4de134], eax */
	m->esp -= 4; M32(m->esp) = 0x421c6au; native_call(m, 0x421350u);	/* 421c65: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421c6a: pop esi */
	m->esp += 4 + 0; return;	/* 421c6b: ret  */
L_421c6c:
	m->ecx = M32((DWORD)(0x4de130u));	/* 421c6c: mov ecx, dword ptr [0x4de130] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421c72: cmp ecx, eax */
	if (!m->zf) goto L_421c83;	/* 421c74: jne 0x421c83 */
	M32((DWORD)(0x4de130u)) = m->esi;	/* 421c76: mov dword ptr [0x4de130], esi */
	m->esp -= 4; M32(m->esp) = 0x421c81u; native_call(m, 0x421350u);	/* 421c7c: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421c81: pop esi */
	m->esp += 4 + 0; return;	/* 421c82: ret  */
L_421c83:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421c83: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 421c85: je 0x42203a */
	M32((DWORD)(0x4de134u)) = m->esi;	/* 421c8b: mov dword ptr [0x4de134], esi */
	m->esp -= 4; M32(m->esp) = 0x421c96u; native_call(m, 0x421350u);	/* 421c91: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421c96: pop esi */
	m->esp += 4 + 0; return;	/* 421c97: ret  */
L_421c98:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 421c98: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de15cu));	/* 421c9d: mov ecx, dword ptr [0x4de15c] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421ca3: cmp ecx, eax */
	if (m->zf) goto L_421cb9;	/* 421ca5: je 0x421cb9 */
	M32((DWORD)(0x4de158u)) = m->esi;	/* 421ca7: mov dword ptr [0x4de158], esi */
	M32((DWORD)(0x4de15cu)) = m->eax;	/* 421cad: mov dword ptr [0x4de15c], eax */
	m->esp -= 4; M32(m->esp) = 0x421cb7u; native_call(m, 0x421350u);	/* 421cb2: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421cb7: pop esi */
	m->esp += 4 + 0; return;	/* 421cb8: ret  */
L_421cb9:
	m->ecx = M32((DWORD)(0x4de158u));	/* 421cb9: mov ecx, dword ptr [0x4de158] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421cbf: cmp ecx, eax */
	if (!m->zf) goto L_421cd0;	/* 421cc1: jne 0x421cd0 */
	M32((DWORD)(0x4de158u)) = m->esi;	/* 421cc3: mov dword ptr [0x4de158], esi */
	m->esp -= 4; M32(m->esp) = 0x421cceu; native_call(m, 0x421350u);	/* 421cc9: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421cce: pop esi */
	m->esp += 4 + 0; return;	/* 421ccf: ret  */
L_421cd0:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421cd0: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 421cd2: je 0x42203a */
	M32((DWORD)(0x4de15cu)) = m->esi;	/* 421cd8: mov dword ptr [0x4de15c], esi */
	m->esp -= 4; M32(m->esp) = 0x421ce3u; native_call(m, 0x421350u);	/* 421cde: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421ce3: pop esi */
	m->esp += 4 + 0; return;	/* 421ce4: ret  */
L_421ce5:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 421ce5: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de164u));	/* 421cea: mov ecx, dword ptr [0x4de164] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421cf0: cmp ecx, eax */
	if (m->zf) goto L_421d06;	/* 421cf2: je 0x421d06 */
	M32((DWORD)(0x4de160u)) = m->esi;	/* 421cf4: mov dword ptr [0x4de160], esi */
	M32((DWORD)(0x4de164u)) = m->eax;	/* 421cfa: mov dword ptr [0x4de164], eax */
	m->esp -= 4; M32(m->esp) = 0x421d04u; native_call(m, 0x421350u);	/* 421cff: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421d04: pop esi */
	m->esp += 4 + 0; return;	/* 421d05: ret  */
L_421d06:
	m->ecx = M32((DWORD)(0x4de160u));	/* 421d06: mov ecx, dword ptr [0x4de160] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421d0c: cmp ecx, eax */
	if (!m->zf) goto L_421d1d;	/* 421d0e: jne 0x421d1d */
	M32((DWORD)(0x4de160u)) = m->esi;	/* 421d10: mov dword ptr [0x4de160], esi */
	m->esp -= 4; M32(m->esp) = 0x421d1bu; native_call(m, 0x421350u);	/* 421d16: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421d1b: pop esi */
	m->esp += 4 + 0; return;	/* 421d1c: ret  */
L_421d1d:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421d1d: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 421d1f: je 0x42203a */
	M32((DWORD)(0x4de164u)) = m->esi;	/* 421d25: mov dword ptr [0x4de164], esi */
	m->esp -= 4; M32(m->esp) = 0x421d30u; native_call(m, 0x421350u);	/* 421d2b: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421d30: pop esi */
	m->esp += 4 + 0; return;	/* 421d31: ret  */
L_421d32:
	m->eax = M32((DWORD)(0x4de040u));	/* 421d32: mov eax, dword ptr [0x4de040] */
	{ DWORD a_ = m->eax, b_ = 0x9u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421d37: cmp eax, 9 */
	if (!m->cf && !m->zf) goto L_42203a;	/* 421d3a: ja 0x42203a */
	switch (m->eax) { case 0: goto L_421d47; case 1: goto L_421d94; case 2: goto L_421de1; case 3: goto L_421e2e; case 4: goto L_421e7b; case 5: goto L_421ec8; case 6: goto L_421f15; case 7: goto L_421f62; case 8: goto L_421faf; case 9: goto L_421ff8; default: abort(); }	/* 421d40: jmp dword ptr [eax*4 + 0x422098] */
L_421d47:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 421d47: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de0c4u));	/* 421d4c: mov ecx, dword ptr [0x4de0c4] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421d52: cmp ecx, eax */
	if (m->zf) goto L_421d68;	/* 421d54: je 0x421d68 */
	M32((DWORD)(0x4de0c0u)) = m->esi;	/* 421d56: mov dword ptr [0x4de0c0], esi */
	M32((DWORD)(0x4de0c4u)) = m->eax;	/* 421d5c: mov dword ptr [0x4de0c4], eax */
	m->esp -= 4; M32(m->esp) = 0x421d66u; native_call(m, 0x421350u);	/* 421d61: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421d66: pop esi */
	m->esp += 4 + 0; return;	/* 421d67: ret  */
L_421d68:
	m->ecx = M32((DWORD)(0x4de0c0u));	/* 421d68: mov ecx, dword ptr [0x4de0c0] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421d6e: cmp ecx, eax */
	if (!m->zf) goto L_421d7f;	/* 421d70: jne 0x421d7f */
	M32((DWORD)(0x4de0c0u)) = m->esi;	/* 421d72: mov dword ptr [0x4de0c0], esi */
	m->esp -= 4; M32(m->esp) = 0x421d7du; native_call(m, 0x421350u);	/* 421d78: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421d7d: pop esi */
	m->esp += 4 + 0; return;	/* 421d7e: ret  */
L_421d7f:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421d7f: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 421d81: je 0x42203a */
	M32((DWORD)(0x4de0c4u)) = m->esi;	/* 421d87: mov dword ptr [0x4de0c4], esi */
	m->esp -= 4; M32(m->esp) = 0x421d92u; native_call(m, 0x421350u);	/* 421d8d: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421d92: pop esi */
	m->esp += 4 + 0; return;	/* 421d93: ret  */
L_421d94:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 421d94: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de0ccu));	/* 421d99: mov ecx, dword ptr [0x4de0cc] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421d9f: cmp ecx, eax */
	if (m->zf) goto L_421db5;	/* 421da1: je 0x421db5 */
	M32((DWORD)(0x4de0c8u)) = m->esi;	/* 421da3: mov dword ptr [0x4de0c8], esi */
	M32((DWORD)(0x4de0ccu)) = m->eax;	/* 421da9: mov dword ptr [0x4de0cc], eax */
	m->esp -= 4; M32(m->esp) = 0x421db3u; native_call(m, 0x421350u);	/* 421dae: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421db3: pop esi */
	m->esp += 4 + 0; return;	/* 421db4: ret  */
L_421db5:
	m->ecx = M32((DWORD)(0x4de0c8u));	/* 421db5: mov ecx, dword ptr [0x4de0c8] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421dbb: cmp ecx, eax */
	if (!m->zf) goto L_421dcc;	/* 421dbd: jne 0x421dcc */
	M32((DWORD)(0x4de0c8u)) = m->esi;	/* 421dbf: mov dword ptr [0x4de0c8], esi */
	m->esp -= 4; M32(m->esp) = 0x421dcau; native_call(m, 0x421350u);	/* 421dc5: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421dca: pop esi */
	m->esp += 4 + 0; return;	/* 421dcb: ret  */
L_421dcc:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421dcc: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 421dce: je 0x42203a */
	M32((DWORD)(0x4de0ccu)) = m->esi;	/* 421dd4: mov dword ptr [0x4de0cc], esi */
	m->esp -= 4; M32(m->esp) = 0x421ddfu; native_call(m, 0x421350u);	/* 421dda: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421ddf: pop esi */
	m->esp += 4 + 0; return;	/* 421de0: ret  */
L_421de1:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 421de1: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de0d4u));	/* 421de6: mov ecx, dword ptr [0x4de0d4] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421dec: cmp ecx, eax */
	if (m->zf) goto L_421e02;	/* 421dee: je 0x421e02 */
	M32((DWORD)(0x4de0d0u)) = m->esi;	/* 421df0: mov dword ptr [0x4de0d0], esi */
	M32((DWORD)(0x4de0d4u)) = m->eax;	/* 421df6: mov dword ptr [0x4de0d4], eax */
	m->esp -= 4; M32(m->esp) = 0x421e00u; native_call(m, 0x421350u);	/* 421dfb: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421e00: pop esi */
	m->esp += 4 + 0; return;	/* 421e01: ret  */
L_421e02:
	m->ecx = M32((DWORD)(0x4de0d0u));	/* 421e02: mov ecx, dword ptr [0x4de0d0] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421e08: cmp ecx, eax */
	if (!m->zf) goto L_421e19;	/* 421e0a: jne 0x421e19 */
	M32((DWORD)(0x4de0d0u)) = m->esi;	/* 421e0c: mov dword ptr [0x4de0d0], esi */
	m->esp -= 4; M32(m->esp) = 0x421e17u; native_call(m, 0x421350u);	/* 421e12: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421e17: pop esi */
	m->esp += 4 + 0; return;	/* 421e18: ret  */
L_421e19:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421e19: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 421e1b: je 0x42203a */
	M32((DWORD)(0x4de0d4u)) = m->esi;	/* 421e21: mov dword ptr [0x4de0d4], esi */
	m->esp -= 4; M32(m->esp) = 0x421e2cu; native_call(m, 0x421350u);	/* 421e27: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421e2c: pop esi */
	m->esp += 4 + 0; return;	/* 421e2d: ret  */
L_421e2e:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 421e2e: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de0dcu));	/* 421e33: mov ecx, dword ptr [0x4de0dc] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421e39: cmp ecx, eax */
	if (m->zf) goto L_421e4f;	/* 421e3b: je 0x421e4f */
	M32((DWORD)(0x4de0d8u)) = m->esi;	/* 421e3d: mov dword ptr [0x4de0d8], esi */
	M32((DWORD)(0x4de0dcu)) = m->eax;	/* 421e43: mov dword ptr [0x4de0dc], eax */
	m->esp -= 4; M32(m->esp) = 0x421e4du; native_call(m, 0x421350u);	/* 421e48: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421e4d: pop esi */
	m->esp += 4 + 0; return;	/* 421e4e: ret  */
L_421e4f:
	m->ecx = M32((DWORD)(0x4de0d8u));	/* 421e4f: mov ecx, dword ptr [0x4de0d8] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421e55: cmp ecx, eax */
	if (!m->zf) goto L_421e66;	/* 421e57: jne 0x421e66 */
	M32((DWORD)(0x4de0d8u)) = m->esi;	/* 421e59: mov dword ptr [0x4de0d8], esi */
	m->esp -= 4; M32(m->esp) = 0x421e64u; native_call(m, 0x421350u);	/* 421e5f: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421e64: pop esi */
	m->esp += 4 + 0; return;	/* 421e65: ret  */
L_421e66:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421e66: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 421e68: je 0x42203a */
	M32((DWORD)(0x4de0dcu)) = m->esi;	/* 421e6e: mov dword ptr [0x4de0dc], esi */
	m->esp -= 4; M32(m->esp) = 0x421e79u; native_call(m, 0x421350u);	/* 421e74: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421e79: pop esi */
	m->esp += 4 + 0; return;	/* 421e7a: ret  */
L_421e7b:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 421e7b: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de0e4u));	/* 421e80: mov ecx, dword ptr [0x4de0e4] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421e86: cmp ecx, eax */
	if (m->zf) goto L_421e9c;	/* 421e88: je 0x421e9c */
	M32((DWORD)(0x4de0e0u)) = m->esi;	/* 421e8a: mov dword ptr [0x4de0e0], esi */
	M32((DWORD)(0x4de0e4u)) = m->eax;	/* 421e90: mov dword ptr [0x4de0e4], eax */
	m->esp -= 4; M32(m->esp) = 0x421e9au; native_call(m, 0x421350u);	/* 421e95: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421e9a: pop esi */
	m->esp += 4 + 0; return;	/* 421e9b: ret  */
L_421e9c:
	m->ecx = M32((DWORD)(0x4de0e0u));	/* 421e9c: mov ecx, dword ptr [0x4de0e0] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421ea2: cmp ecx, eax */
	if (!m->zf) goto L_421eb3;	/* 421ea4: jne 0x421eb3 */
	M32((DWORD)(0x4de0e0u)) = m->esi;	/* 421ea6: mov dword ptr [0x4de0e0], esi */
	m->esp -= 4; M32(m->esp) = 0x421eb1u; native_call(m, 0x421350u);	/* 421eac: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421eb1: pop esi */
	m->esp += 4 + 0; return;	/* 421eb2: ret  */
L_421eb3:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421eb3: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 421eb5: je 0x42203a */
	M32((DWORD)(0x4de0e4u)) = m->esi;	/* 421ebb: mov dword ptr [0x4de0e4], esi */
	m->esp -= 4; M32(m->esp) = 0x421ec6u; native_call(m, 0x421350u);	/* 421ec1: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421ec6: pop esi */
	m->esp += 4 + 0; return;	/* 421ec7: ret  */
L_421ec8:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 421ec8: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de0ecu));	/* 421ecd: mov ecx, dword ptr [0x4de0ec] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421ed3: cmp ecx, eax */
	if (m->zf) goto L_421ee9;	/* 421ed5: je 0x421ee9 */
	M32((DWORD)(0x4de0e8u)) = m->esi;	/* 421ed7: mov dword ptr [0x4de0e8], esi */
	M32((DWORD)(0x4de0ecu)) = m->eax;	/* 421edd: mov dword ptr [0x4de0ec], eax */
	m->esp -= 4; M32(m->esp) = 0x421ee7u; native_call(m, 0x421350u);	/* 421ee2: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421ee7: pop esi */
	m->esp += 4 + 0; return;	/* 421ee8: ret  */
L_421ee9:
	m->ecx = M32((DWORD)(0x4de0e8u));	/* 421ee9: mov ecx, dword ptr [0x4de0e8] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421eef: cmp ecx, eax */
	if (!m->zf) goto L_421f00;	/* 421ef1: jne 0x421f00 */
	M32((DWORD)(0x4de0e8u)) = m->esi;	/* 421ef3: mov dword ptr [0x4de0e8], esi */
	m->esp -= 4; M32(m->esp) = 0x421efeu; native_call(m, 0x421350u);	/* 421ef9: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421efe: pop esi */
	m->esp += 4 + 0; return;	/* 421eff: ret  */
L_421f00:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421f00: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 421f02: je 0x42203a */
	M32((DWORD)(0x4de0ecu)) = m->esi;	/* 421f08: mov dword ptr [0x4de0ec], esi */
	m->esp -= 4; M32(m->esp) = 0x421f13u; native_call(m, 0x421350u);	/* 421f0e: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421f13: pop esi */
	m->esp += 4 + 0; return;	/* 421f14: ret  */
L_421f15:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 421f15: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de0f4u));	/* 421f1a: mov ecx, dword ptr [0x4de0f4] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421f20: cmp ecx, eax */
	if (m->zf) goto L_421f36;	/* 421f22: je 0x421f36 */
	M32((DWORD)(0x4de0f0u)) = m->esi;	/* 421f24: mov dword ptr [0x4de0f0], esi */
	M32((DWORD)(0x4de0f4u)) = m->eax;	/* 421f2a: mov dword ptr [0x4de0f4], eax */
	m->esp -= 4; M32(m->esp) = 0x421f34u; native_call(m, 0x421350u);	/* 421f2f: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421f34: pop esi */
	m->esp += 4 + 0; return;	/* 421f35: ret  */
L_421f36:
	m->ecx = M32((DWORD)(0x4de0f0u));	/* 421f36: mov ecx, dword ptr [0x4de0f0] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421f3c: cmp ecx, eax */
	if (!m->zf) goto L_421f4d;	/* 421f3e: jne 0x421f4d */
	M32((DWORD)(0x4de0f0u)) = m->esi;	/* 421f40: mov dword ptr [0x4de0f0], esi */
	m->esp -= 4; M32(m->esp) = 0x421f4bu; native_call(m, 0x421350u);	/* 421f46: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421f4b: pop esi */
	m->esp += 4 + 0; return;	/* 421f4c: ret  */
L_421f4d:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421f4d: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 421f4f: je 0x42203a */
	M32((DWORD)(0x4de0f4u)) = m->esi;	/* 421f55: mov dword ptr [0x4de0f4], esi */
	m->esp -= 4; M32(m->esp) = 0x421f60u; native_call(m, 0x421350u);	/* 421f5b: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421f60: pop esi */
	m->esp += 4 + 0; return;	/* 421f61: ret  */
L_421f62:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 421f62: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de0fcu));	/* 421f67: mov ecx, dword ptr [0x4de0fc] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421f6d: cmp ecx, eax */
	if (m->zf) goto L_421f83;	/* 421f6f: je 0x421f83 */
	M32((DWORD)(0x4de0f8u)) = m->esi;	/* 421f71: mov dword ptr [0x4de0f8], esi */
	M32((DWORD)(0x4de0fcu)) = m->eax;	/* 421f77: mov dword ptr [0x4de0fc], eax */
	m->esp -= 4; M32(m->esp) = 0x421f81u; native_call(m, 0x421350u);	/* 421f7c: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421f81: pop esi */
	m->esp += 4 + 0; return;	/* 421f82: ret  */
L_421f83:
	m->ecx = M32((DWORD)(0x4de0f8u));	/* 421f83: mov ecx, dword ptr [0x4de0f8] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421f89: cmp ecx, eax */
	if (!m->zf) goto L_421f9a;	/* 421f8b: jne 0x421f9a */
	M32((DWORD)(0x4de0f8u)) = m->esi;	/* 421f8d: mov dword ptr [0x4de0f8], esi */
	m->esp -= 4; M32(m->esp) = 0x421f98u; native_call(m, 0x421350u);	/* 421f93: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421f98: pop esi */
	m->esp += 4 + 0; return;	/* 421f99: ret  */
L_421f9a:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421f9a: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 421f9c: je 0x42203a */
	M32((DWORD)(0x4de0fcu)) = m->esi;	/* 421fa2: mov dword ptr [0x4de0fc], esi */
	m->esp -= 4; M32(m->esp) = 0x421fadu; native_call(m, 0x421350u);	/* 421fa8: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421fad: pop esi */
	m->esp += 4 + 0; return;	/* 421fae: ret  */
L_421faf:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 421faf: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de104u));	/* 421fb4: mov ecx, dword ptr [0x4de104] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421fba: cmp ecx, eax */
	if (m->zf) goto L_421fd0;	/* 421fbc: je 0x421fd0 */
	M32((DWORD)(0x4de100u)) = m->esi;	/* 421fbe: mov dword ptr [0x4de100], esi */
	M32((DWORD)(0x4de104u)) = m->eax;	/* 421fc4: mov dword ptr [0x4de104], eax */
	m->esp -= 4; M32(m->esp) = 0x421fceu; native_call(m, 0x421350u);	/* 421fc9: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421fce: pop esi */
	m->esp += 4 + 0; return;	/* 421fcf: ret  */
L_421fd0:
	m->ecx = M32((DWORD)(0x4de100u));	/* 421fd0: mov ecx, dword ptr [0x4de100] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421fd6: cmp ecx, eax */
	if (!m->zf) goto L_421fe7;	/* 421fd8: jne 0x421fe7 */
	M32((DWORD)(0x4de100u)) = m->esi;	/* 421fda: mov dword ptr [0x4de100], esi */
	m->esp -= 4; M32(m->esp) = 0x421fe5u; native_call(m, 0x421350u);	/* 421fe0: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421fe5: pop esi */
	m->esp += 4 + 0; return;	/* 421fe6: ret  */
L_421fe7:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 421fe7: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 421fe9: je 0x42203a */
	M32((DWORD)(0x4de104u)) = m->esi;	/* 421feb: mov dword ptr [0x4de104], esi */
	m->esp -= 4; M32(m->esp) = 0x421ff6u; native_call(m, 0x421350u);	/* 421ff1: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 421ff6: pop esi */
	m->esp += 4 + 0; return;	/* 421ff7: ret  */
L_421ff8:
	m->eax = M32((DWORD)(0x4df8e4u));	/* 421ff8: mov eax, dword ptr [0x4df8e4] */
	m->ecx = M32((DWORD)(0x4de10cu));	/* 421ffd: mov ecx, dword ptr [0x4de10c] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422003: cmp ecx, eax */
	if (m->zf) goto L_422019;	/* 422005: je 0x422019 */
	M32((DWORD)(0x4de108u)) = m->esi;	/* 422007: mov dword ptr [0x4de108], esi */
	M32((DWORD)(0x4de10cu)) = m->eax;	/* 42200d: mov dword ptr [0x4de10c], eax */
	m->esp -= 4; M32(m->esp) = 0x422017u; native_call(m, 0x421350u);	/* 422012: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 422017: pop esi */
	m->esp += 4 + 0; return;	/* 422018: ret  */
L_422019:
	m->ecx = M32((DWORD)(0x4de108u));	/* 422019: mov ecx, dword ptr [0x4de108] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42201f: cmp ecx, eax */
	if (!m->zf) goto L_422030;	/* 422021: jne 0x422030 */
	M32((DWORD)(0x4de108u)) = m->esi;	/* 422023: mov dword ptr [0x4de108], esi */
	m->esp -= 4; M32(m->esp) = 0x42202eu; native_call(m, 0x421350u);	/* 422029: call 0x421350 */
	m->esi = M32(m->esp); m->esp += 4;	/* 42202e: pop esi */
	m->esp += 4 + 0; return;	/* 42202f: ret  */
L_422030:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422030: cmp ecx, esi */
	if (m->zf) goto L_42203a;	/* 422032: je 0x42203a */
	M32((DWORD)(0x4de10cu)) = m->esi;	/* 422034: mov dword ptr [0x4de10c], esi */
L_42203a:
	m->esp -= 4; M32(m->esp) = 0x42203fu; native_call(m, 0x421350u);	/* 42203a: call 0x421350 */
L_42203f:
	m->esi = M32(m->esp); m->esp += 4;	/* 42203f: pop esi */
	m->esp += 4 + 0; return;	/* 422040: ret  */
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
