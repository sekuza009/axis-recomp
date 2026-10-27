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

static void lift_473c20(X86 *m);
static void lift_473d30(X86 *m);
static void lift_473e40(X86 *m);
static void lift_473f50(X86 *m);
static void lift_474060(X86 *m);
static void lift_473b10(X86 *m);

/* actor_setActorTypeHeadInfoBy (0x473b10), lifted by tools/lift.py */
static void lift_473b10(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 473b10: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 473b11: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x10u));	/* 473b12: mov ebp, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 473b16: push esi */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 473b17: test ebp, ebp */
	m->ebx = m->ecx;	/* 473b19: mov ebx, ecx */
	if (m->sf == m->of) goto L_473b25;	/* 473b1b: jge 0x473b25 */
	m->esi = M32(m->esp); m->esp += 4;	/* 473b1d: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 473b1e: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 473b1f: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 473b21: pop ebx */
	m->esp += 4 + 8; return;	/* 473b22: ret 8 */
L_473b25:
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 473b25: mov ecx, dword ptr [esp + 0x10] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 473b29: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 473b2c: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 473b2f: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 473b31: lea eax, [eax + eax*2] */
	m->edx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 473b34: lea edx, [ecx + eax*8] */
	m->eax = M32((DWORD)(m->ebx + 0x19e1888u));	/* 473b37: mov eax, dword ptr [ebx + 0x19e1888] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 473b3d: dec eax */
	m->esi = (DWORD)(m->ebx + m->edx*2 + 0x1561b68u);	/* 473b3e: lea esi, [ebx + edx*2 + 0x1561b68] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 473b45: cmp ecx, eax */
	M32((DWORD)(m->esp + 0x14u)) = m->esi;	/* 473b47: mov dword ptr [esp + 0x14], esi */
	if (m->zf || m->sf != m->of) goto L_473b54;	/* 473b4b: jle 0x473b54 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 473b4d: inc ecx */
	M32((DWORD)(m->ebx + 0x19e1888u)) = m->ecx;	/* 473b4e: mov dword ptr [ebx + 0x19e1888], ecx */
L_473b54:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x30cu)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 473b54: cmp dword ptr [esi + 0x30c], ebp */
	if (!m->zf) goto L_473b67;	/* 473b5a: jne 0x473b67 */
	m->esi = M32(m->esp); m->esp += 4;	/* 473b5c: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 473b5d: pop ebp */
	m->eax = 0x1u;	/* 473b5e: mov eax, 1 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 473b63: pop ebx */
	m->esp += 4 + 8; return;	/* 473b64: ret 8 */
L_473b67:
	{ DWORD a_ = m->ebp, b_ = M32((DWORD)(m->ebx + 0x13eb000u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 473b67: cmp ebp, dword ptr [ebx + 0x13eb000] */
	if (m->sf != m->of) goto L_473b82;	/* 473b6d: jl 0x473b82 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 473b6f: push ebp */
	{ DWORD v_ = 0x4c75f0u; m->esp -= 4; M32(m->esp) = v_; }	/* 473b70: push 0x4c75f0 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 473b75: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x473b7fu; native_call(m, 0x46c710u);	/* 473b7a: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 473b7f: add esp, 0xc */
L_473b82:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 473b82: push edi */
	m->ecx = (DWORD)(m->esi + 0x338u);	/* 473b83: lea ecx, [esi + 0x338] */
	m->esp -= 4; M32(m->esp) = 0x473b8eu; native_call(m, 0x467520u);	/* 473b89: call 0x467520 */
	m->ecx = (DWORD)(m->esi + 0x43534u);	/* 473b8e: lea ecx, [esi + 0x43534] */
	m->esp -= 4; M32(m->esp) = 0x473b99u; native_call(m, 0x46b7f0u);	/* 473b94: call 0x46b7f0 */
	m->eax = m->ebp;	/* 473b99: mov eax, ebp */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 473b9b: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 473b9e: add eax, ebp */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 473ba0: lea ecx, [eax + eax*4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 473ba3: xor eax, eax */
	m->edx = (DWORD)(m->ebp + m->ecx*4 + 0x0u);	/* 473ba5: lea edx, [ebp + ecx*4] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 473ba9: or ecx, 0xffffffff */
	m->edi = (DWORD)(m->ebx + m->edx*8 + 0x13c9b30u);	/* 473bac: lea edi, [ebx + edx*8 + 0x13c9b30] */
	m->edx = (DWORD)(m->esi + 0x4cu);	/* 473bb3: lea edx, [esi + 0x4c] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 473bb6: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 473bb8: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 473bba: sub edi, ecx */
	m->eax = m->ecx;	/* 473bbc: mov eax, ecx */
	m->esi = m->edi;	/* 473bbe: mov esi, edi */
	m->edi = m->edx;	/* 473bc0: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 473bc2: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 473bc5: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 473bc7: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 473bc9: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 473bcc: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 473bce: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 473bd2: xor esi, esi */
	M32((DWORD)(m->ecx + 0x30cu)) = m->ebp;	/* 473bd4: mov dword ptr [ecx + 0x30c], ebp */
	m->eax = M32((DWORD)(m->ebx + 0x202e8c8u));	/* 473bda: mov eax, dword ptr [ebx + 0x202e8c8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 473be0: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_473c0d;	/* 473be2: jle 0x473c0d */
	m->edi = (DWORD)(m->ebx + 0x1cd94b4u);	/* 473be4: lea edi, [ebx + 0x1cd94b4] */
L_473bea:
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 473bea: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 473bee: mov eax, dword ptr [edi] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 473bf0: cmp eax, edx */
	if (!m->zf) goto L_473bfc;	/* 473bf2: jne 0x473bfc */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 473bf4: push esi */
	m->ecx = m->ebx;	/* 473bf5: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x473bfcu; native_call(m, 0x45e1f0u);	/* 473bf7: call 0x45e1f0 */
L_473bfc:
	m->eax = M32((DWORD)(m->ebx + 0x202e8c8u));	/* 473bfc: mov eax, dword ptr [ebx + 0x202e8c8] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 473c02: inc esi */
	{ DWORD a_ = m->edi, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 473c03: add edi, 0x8888 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 473c09: cmp esi, eax */
	if (m->sf != m->of) goto L_473bea;	/* 473c0b: jl 0x473bea */
L_473c0d:
	m->edi = M32(m->esp); m->esp += 4;	/* 473c0d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 473c0e: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 473c0f: pop ebp */
	m->eax = 0x1u;	/* 473c10: mov eax, 1 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 473c15: pop ebx */
	m->esp += 4 + 8; return;	/* 473c16: ret 8 */
}

/* actor_setActorTypeChestInfoBy (0x473c20), lifted by tools/lift.py */
static void lift_473c20(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 473c20: push ebx */
	m->ebx = M32((DWORD)(m->esp + 0xcu));	/* 473c21: mov ebx, dword ptr [esp + 0xc] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 473c25: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 473c26: push esi */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 473c27: test ebx, ebx */
	m->ebp = m->ecx;	/* 473c29: mov ebp, ecx */
	if (m->sf == m->of) goto L_473c35;	/* 473c2b: jge 0x473c35 */
	m->esi = M32(m->esp); m->esp += 4;	/* 473c2d: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 473c2e: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 473c2f: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 473c31: pop ebx */
	m->esp += 4 + 8; return;	/* 473c32: ret 8 */
L_473c35:
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 473c35: mov ecx, dword ptr [esp + 0x10] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 473c39: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 473c3c: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 473c3f: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 473c41: lea eax, [eax + eax*2] */
	m->edx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 473c44: lea edx, [ecx + eax*8] */
	m->eax = M32((DWORD)(m->ebp + 0x19e1888u));	/* 473c47: mov eax, dword ptr [ebp + 0x19e1888] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 473c4d: dec eax */
	m->esi = (DWORD)(m->ebp + m->edx*2 + 0x1561b68u);	/* 473c4e: lea esi, [ebp + edx*2 + 0x1561b68] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 473c55: cmp ecx, eax */
	M32((DWORD)(m->esp + 0x14u)) = m->esi;	/* 473c57: mov dword ptr [esp + 0x14], esi */
	if (m->zf || m->sf != m->of) goto L_473c64;	/* 473c5b: jle 0x473c64 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 473c5d: inc ecx */
	M32((DWORD)(m->ebp + 0x19e1888u)) = m->ecx;	/* 473c5e: mov dword ptr [ebp + 0x19e1888], ecx */
L_473c64:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x310u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 473c64: cmp dword ptr [esi + 0x310], ebx */
	if (!m->zf) goto L_473c77;	/* 473c6a: jne 0x473c77 */
	m->esi = M32(m->esp); m->esp += 4;	/* 473c6c: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 473c6d: pop ebp */
	m->eax = 0x1u;	/* 473c6e: mov eax, 1 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 473c73: pop ebx */
	m->esp += 4 + 8; return;	/* 473c74: ret 8 */
L_473c77:
	{ DWORD a_ = m->ebx, b_ = M32((DWORD)(m->ebp + 0x140c8bcu)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 473c77: cmp ebx, dword ptr [ebp + 0x140c8bc] */
	if (m->sf != m->of) goto L_473c92;	/* 473c7d: jl 0x473c92 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 473c7f: push ebx */
	{ DWORD v_ = 0x4c7624u; m->esp -= 4; M32(m->esp) = v_; }	/* 473c80: push 0x4c7624 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 473c85: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x473c8fu; native_call(m, 0x46c710u);	/* 473c8a: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 473c8f: add esp, 0xc */
L_473c92:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 473c92: push edi */
	m->ecx = (DWORD)(m->esi + 0x8284u);	/* 473c93: lea ecx, [esi + 0x8284] */
	m->esp -= 4; M32(m->esp) = 0x473c9eu; native_call(m, 0x467520u);	/* 473c99: call 0x467520 */
	m->ecx = (DWORD)(m->esi + 0x43e34u);	/* 473c9e: lea ecx, [esi + 0x43e34] */
	m->esp -= 4; M32(m->esp) = 0x473ca9u; native_call(m, 0x46b7f0u);	/* 473ca4: call 0x46b7f0 */
	m->eax = (DWORD)(m->ebx + m->ebx*2 + 0x0u);	/* 473ca9: lea eax, [ebx + ebx*2] */
	m->edx = (DWORD)(m->esi + 0x8cu);	/* 473cac: lea edx, [esi + 0x8c] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 473cb2: shl eax, 3 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 473cb5: sub eax, ebx */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 473cb7: lea eax, [eax + eax*4] */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 473cba: shl eax, 1 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 473cbc: sub eax, ebx */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 473cbe: lea ecx, [eax + eax*2] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 473cc1: xor eax, eax */
	m->edi = (DWORD)(m->ebp + m->ecx*4 + 0x13eb004u);	/* 473cc3: lea edi, [ebp + ecx*4 + 0x13eb004] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 473cca: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 473ccd: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 473ccf: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 473cd1: sub edi, ecx */
	m->eax = m->ecx;	/* 473cd3: mov eax, ecx */
	m->esi = m->edi;	/* 473cd5: mov esi, edi */
	m->edi = m->edx;	/* 473cd7: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 473cd9: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 473cdc: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 473cde: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 473ce0: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 473ce3: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 473ce5: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 473ce9: xor esi, esi */
	M32((DWORD)(m->ecx + 0x310u)) = m->ebx;	/* 473ceb: mov dword ptr [ecx + 0x310], ebx */
	m->eax = M32((DWORD)(m->ebp + 0x202e8c8u));	/* 473cf1: mov eax, dword ptr [ebp + 0x202e8c8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 473cf7: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_473d24;	/* 473cf9: jle 0x473d24 */
	m->edi = (DWORD)(m->ebp + 0x1cd94b4u);	/* 473cfb: lea edi, [ebp + 0x1cd94b4] */
L_473d01:
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 473d01: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 473d05: mov eax, dword ptr [edi] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 473d07: cmp eax, edx */
	if (!m->zf) goto L_473d13;	/* 473d09: jne 0x473d13 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 473d0b: push esi */
	m->ecx = m->ebp;	/* 473d0c: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x473d13u; native_call(m, 0x45e2c0u);	/* 473d0e: call 0x45e2c0 */
L_473d13:
	m->eax = M32((DWORD)(m->ebp + 0x202e8c8u));	/* 473d13: mov eax, dword ptr [ebp + 0x202e8c8] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 473d19: inc esi */
	{ DWORD a_ = m->edi, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 473d1a: add edi, 0x8888 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 473d20: cmp esi, eax */
	if (m->sf != m->of) goto L_473d01;	/* 473d22: jl 0x473d01 */
L_473d24:
	m->edi = M32(m->esp); m->esp += 4;	/* 473d24: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 473d25: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 473d26: pop ebp */
	m->eax = 0x1u;	/* 473d27: mov eax, 1 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 473d2c: pop ebx */
	m->esp += 4 + 8; return;	/* 473d2d: ret 8 */
}

/* actor_setActorTypeArmInfoBy (0x473d30), lifted by tools/lift.py */
static void lift_473d30(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 473d30: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 473d31: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x10u));	/* 473d32: mov ebp, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 473d36: push esi */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 473d37: test ebp, ebp */
	m->ebx = m->ecx;	/* 473d39: mov ebx, ecx */
	if (m->sf == m->of) goto L_473d45;	/* 473d3b: jge 0x473d45 */
	m->esi = M32(m->esp); m->esp += 4;	/* 473d3d: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 473d3e: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 473d3f: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 473d41: pop ebx */
	m->esp += 4 + 8; return;	/* 473d42: ret 8 */
L_473d45:
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 473d45: mov ecx, dword ptr [esp + 0x10] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 473d49: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 473d4c: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 473d4f: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 473d51: lea eax, [eax + eax*2] */
	m->edx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 473d54: lea edx, [ecx + eax*8] */
	m->eax = M32((DWORD)(m->ebx + 0x19e1888u));	/* 473d57: mov eax, dword ptr [ebx + 0x19e1888] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 473d5d: dec eax */
	m->esi = (DWORD)(m->ebx + m->edx*2 + 0x1561b68u);	/* 473d5e: lea esi, [ebx + edx*2 + 0x1561b68] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 473d65: cmp ecx, eax */
	M32((DWORD)(m->esp + 0x14u)) = m->esi;	/* 473d67: mov dword ptr [esp + 0x14], esi */
	if (m->zf || m->sf != m->of) goto L_473d74;	/* 473d6b: jle 0x473d74 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 473d6d: inc ecx */
	M32((DWORD)(m->ebx + 0x19e1888u)) = m->ecx;	/* 473d6e: mov dword ptr [ebx + 0x19e1888], ecx */
L_473d74:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x314u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 473d74: cmp dword ptr [esi + 0x314], ebp */
	if (!m->zf) goto L_473d87;	/* 473d7a: jne 0x473d87 */
	m->esi = M32(m->esp); m->esp += 4;	/* 473d7c: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 473d7d: pop ebp */
	m->eax = 0x1u;	/* 473d7e: mov eax, 1 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 473d83: pop ebx */
	m->esp += 4 + 8; return;	/* 473d84: ret 8 */
L_473d87:
	{ DWORD a_ = m->ebp, b_ = M32((DWORD)(m->ebx + 0x1447ec0u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 473d87: cmp ebp, dword ptr [ebx + 0x1447ec0] */
	if (m->sf != m->of) goto L_473da2;	/* 473d8d: jl 0x473da2 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 473d8f: push ebp */
	{ DWORD v_ = 0x4c7658u; m->esp -= 4; M32(m->esp) = v_; }	/* 473d90: push 0x4c7658 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 473d95: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x473d9fu; native_call(m, 0x46c710u);	/* 473d9a: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 473d9f: add esp, 0xc */
L_473da2:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 473da2: push edi */
	m->ecx = (DWORD)(m->esi + 0x101d0u);	/* 473da3: lea ecx, [esi + 0x101d0] */
	m->esp -= 4; M32(m->esp) = 0x473daeu; native_call(m, 0x467520u);	/* 473da9: call 0x467520 */
	m->ecx = (DWORD)(m->esi + 0x44734u);	/* 473dae: lea ecx, [esi + 0x44734] */
	m->esp -= 4; M32(m->esp) = 0x473db9u; native_call(m, 0x46b7f0u);	/* 473db4: call 0x46b7f0 */
	m->ecx = (DWORD)(m->ebp + m->ebp*8 + 0x0u);	/* 473db9: lea ecx, [ebp + ebp*8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 473dbd: xor eax, eax */
	m->edx = (DWORD)(m->ebp + m->ecx*2 + 0x0u);	/* 473dbf: lea edx, [ebp + ecx*2] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 473dc3: or ecx, 0xffffffff */
	{ DWORD a_ = m->edx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 473dc6: shl edx, 8 */
	m->edi = (DWORD)(m->edx + m->ebx*1 + 0x140c8c0u);	/* 473dc9: lea edi, [edx + ebx + 0x140c8c0] */
	m->edx = (DWORD)(m->esi + 0xccu);	/* 473dd0: lea edx, [esi + 0xcc] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 473dd6: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 473dd8: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 473dda: sub edi, ecx */
	m->eax = m->ecx;	/* 473ddc: mov eax, ecx */
	m->esi = m->edi;	/* 473dde: mov esi, edi */
	m->edi = m->edx;	/* 473de0: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 473de2: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 473de5: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 473de7: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 473de9: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 473dec: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 473dee: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 473df2: xor esi, esi */
	M32((DWORD)(m->ecx + 0x314u)) = m->ebp;	/* 473df4: mov dword ptr [ecx + 0x314], ebp */
	m->eax = M32((DWORD)(m->ebx + 0x202e8c8u));	/* 473dfa: mov eax, dword ptr [ebx + 0x202e8c8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 473e00: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_473e2d;	/* 473e02: jle 0x473e2d */
	m->edi = (DWORD)(m->ebx + 0x1cd94b4u);	/* 473e04: lea edi, [ebx + 0x1cd94b4] */
L_473e0a:
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 473e0a: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 473e0e: mov eax, dword ptr [edi] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 473e10: cmp eax, edx */
	if (!m->zf) goto L_473e1c;	/* 473e12: jne 0x473e1c */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 473e14: push esi */
	m->ecx = m->ebx;	/* 473e15: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x473e1cu; native_call(m, 0x45e390u);	/* 473e17: call 0x45e390 */
L_473e1c:
	m->eax = M32((DWORD)(m->ebx + 0x202e8c8u));	/* 473e1c: mov eax, dword ptr [ebx + 0x202e8c8] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 473e22: inc esi */
	{ DWORD a_ = m->edi, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 473e23: add edi, 0x8888 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 473e29: cmp esi, eax */
	if (m->sf != m->of) goto L_473e0a;	/* 473e2b: jl 0x473e0a */
L_473e2d:
	m->edi = M32(m->esp); m->esp += 4;	/* 473e2d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 473e2e: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 473e2f: pop ebp */
	m->eax = 0x1u;	/* 473e30: mov eax, 1 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 473e35: pop ebx */
	m->esp += 4 + 8; return;	/* 473e36: ret 8 */
}

/* actor_setActorTypeLegInfoBy (0x473e40), lifted by tools/lift.py */
static void lift_473e40(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 473e40: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 473e41: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x10u));	/* 473e42: mov ebp, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 473e46: push esi */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 473e47: test ebp, ebp */
	m->ebx = m->ecx;	/* 473e49: mov ebx, ecx */
	if (m->sf == m->of) goto L_473e55;	/* 473e4b: jge 0x473e55 */
	m->esi = M32(m->esp); m->esp += 4;	/* 473e4d: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 473e4e: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 473e4f: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 473e51: pop ebx */
	m->esp += 4 + 8; return;	/* 473e52: ret 8 */
L_473e55:
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 473e55: mov ecx, dword ptr [esp + 0x10] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 473e59: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 473e5c: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 473e5f: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 473e61: lea eax, [eax + eax*2] */
	m->edx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 473e64: lea edx, [ecx + eax*8] */
	m->eax = M32((DWORD)(m->ebx + 0x19e1888u));	/* 473e67: mov eax, dword ptr [ebx + 0x19e1888] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 473e6d: dec eax */
	m->esi = (DWORD)(m->ebx + m->edx*2 + 0x1561b68u);	/* 473e6e: lea esi, [ebx + edx*2 + 0x1561b68] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 473e75: cmp ecx, eax */
	M32((DWORD)(m->esp + 0x14u)) = m->esi;	/* 473e77: mov dword ptr [esp + 0x14], esi */
	if (m->zf || m->sf != m->of) goto L_473e84;	/* 473e7b: jle 0x473e84 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 473e7d: inc ecx */
	M32((DWORD)(m->ebx + 0x19e1888u)) = m->ecx;	/* 473e7e: mov dword ptr [ebx + 0x19e1888], ecx */
L_473e84:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x318u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 473e84: cmp dword ptr [esi + 0x318], ebp */
	if (!m->zf) goto L_473e97;	/* 473e8a: jne 0x473e97 */
	m->esi = M32(m->esp); m->esp += 4;	/* 473e8c: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 473e8d: pop ebp */
	m->eax = 0x1u;	/* 473e8e: mov eax, 1 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 473e93: pop ebx */
	m->esp += 4 + 8; return;	/* 473e94: ret 8 */
L_473e97:
	{ DWORD a_ = m->ebp, b_ = M32((DWORD)(m->ebx + 0x148646cu)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 473e97: cmp ebp, dword ptr [ebx + 0x148646c] */
	if (m->sf != m->of) goto L_473eb2;	/* 473e9d: jl 0x473eb2 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 473e9f: push ebp */
	{ DWORD v_ = 0x4c7688u; m->esp -= 4; M32(m->esp) = v_; }	/* 473ea0: push 0x4c7688 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 473ea5: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x473eafu; native_call(m, 0x46c710u);	/* 473eaa: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 473eaf: add esp, 0xc */
L_473eb2:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 473eb2: push edi */
	m->ecx = (DWORD)(m->esi + 0x1fe1cu);	/* 473eb3: lea ecx, [esi + 0x1fe1c] */
	m->esp -= 4; M32(m->esp) = 0x473ebeu; native_call(m, 0x467520u);	/* 473eb9: call 0x467520 */
	m->ecx = (DWORD)(m->esi + 0x45804u);	/* 473ebe: lea ecx, [esi + 0x45804] */
	m->esp -= 4; M32(m->esp) = 0x473ec9u; native_call(m, 0x46b7f0u);	/* 473ec4: call 0x46b7f0 */
	m->ecx = (DWORD)(m->ebp + m->ebp*4 + 0x0u);	/* 473ec9: lea ecx, [ebp + ebp*4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 473ecd: xor eax, eax */
	{ DWORD a_ = m->ecx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 473ecf: shl ecx, 6 */
	{ DWORD a_ = m->ecx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 473ed2: sub ecx, ebp */
	m->edx = (DWORD)(m->ebp + m->ecx*4 + 0x0u);	/* 473ed4: lea edx, [ebp + ecx*4] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 473ed8: or ecx, 0xffffffff */
	m->edi = (DWORD)(m->ebx + m->edx*4 + 0x1447ec4u);	/* 473edb: lea edi, [ebx + edx*4 + 0x1447ec4] */
	m->edx = (DWORD)(m->esi + 0x10cu);	/* 473ee2: lea edx, [esi + 0x10c] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 473ee8: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 473eea: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 473eec: sub edi, ecx */
	m->eax = m->ecx;	/* 473eee: mov eax, ecx */
	m->esi = m->edi;	/* 473ef0: mov esi, edi */
	m->edi = m->edx;	/* 473ef2: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 473ef4: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 473ef7: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 473ef9: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 473efb: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 473efe: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 473f00: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 473f04: xor esi, esi */
	M32((DWORD)(m->ecx + 0x318u)) = m->ebp;	/* 473f06: mov dword ptr [ecx + 0x318], ebp */
	m->eax = M32((DWORD)(m->ebx + 0x202e8c8u));	/* 473f0c: mov eax, dword ptr [ebx + 0x202e8c8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 473f12: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_473f3f;	/* 473f14: jle 0x473f3f */
	m->edi = (DWORD)(m->ebx + 0x1cd94b4u);	/* 473f16: lea edi, [ebx + 0x1cd94b4] */
L_473f1c:
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 473f1c: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 473f20: mov eax, dword ptr [edi] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 473f22: cmp eax, edx */
	if (!m->zf) goto L_473f2e;	/* 473f24: jne 0x473f2e */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 473f26: push esi */
	m->ecx = m->ebx;	/* 473f27: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x473f2eu; native_call(m, 0x45e460u);	/* 473f29: call 0x45e460 */
L_473f2e:
	m->eax = M32((DWORD)(m->ebx + 0x202e8c8u));	/* 473f2e: mov eax, dword ptr [ebx + 0x202e8c8] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 473f34: inc esi */
	{ DWORD a_ = m->edi, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 473f35: add edi, 0x8888 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 473f3b: cmp esi, eax */
	if (m->sf != m->of) goto L_473f1c;	/* 473f3d: jl 0x473f1c */
L_473f3f:
	m->edi = M32(m->esp); m->esp += 4;	/* 473f3f: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 473f40: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 473f41: pop ebp */
	m->eax = 0x1u;	/* 473f42: mov eax, 1 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 473f47: pop ebx */
	m->esp += 4 + 8; return;	/* 473f48: ret 8 */
}

/* actor_setActorTypeBoosterInfoBy (0x473f50), lifted by tools/lift.py */
static void lift_473f50(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 473f50: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 473f51: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x10u));	/* 473f52: mov ebp, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 473f56: push esi */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 473f57: test ebp, ebp */
	m->ebx = m->ecx;	/* 473f59: mov ebx, ecx */
	if (m->sf == m->of) goto L_473f65;	/* 473f5b: jge 0x473f65 */
	m->esi = M32(m->esp); m->esp += 4;	/* 473f5d: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 473f5e: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 473f5f: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 473f61: pop ebx */
	m->esp += 4 + 8; return;	/* 473f62: ret 8 */
L_473f65:
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 473f65: mov ecx, dword ptr [esp + 0x10] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 473f69: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 473f6c: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 473f6f: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 473f71: lea eax, [eax + eax*2] */
	m->edx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 473f74: lea edx, [ecx + eax*8] */
	m->eax = M32((DWORD)(m->ebx + 0x19e1888u));	/* 473f77: mov eax, dword ptr [ebx + 0x19e1888] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 473f7d: dec eax */
	m->esi = (DWORD)(m->ebx + m->edx*2 + 0x1561b68u);	/* 473f7e: lea esi, [ebx + edx*2 + 0x1561b68] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 473f85: cmp ecx, eax */
	M32((DWORD)(m->esp + 0x14u)) = m->esi;	/* 473f87: mov dword ptr [esp + 0x14], esi */
	if (m->zf || m->sf != m->of) goto L_473f94;	/* 473f8b: jle 0x473f94 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 473f8d: inc ecx */
	M32((DWORD)(m->ebx + 0x19e1888u)) = m->ecx;	/* 473f8e: mov dword ptr [ebx + 0x19e1888], ecx */
L_473f94:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x31cu)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 473f94: cmp dword ptr [esi + 0x31c], ebp */
	if (!m->zf) goto L_473fa7;	/* 473f9a: jne 0x473fa7 */
	m->esi = M32(m->esp); m->esp += 4;	/* 473f9c: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 473f9d: pop ebp */
	m->eax = 0x1u;	/* 473f9e: mov eax, 1 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 473fa3: pop ebx */
	m->esp += 4 + 8; return;	/* 473fa4: ret 8 */
L_473fa7:
	{ DWORD a_ = m->ebp, b_ = M32((DWORD)(m->ebx + 0x14d1ab0u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 473fa7: cmp ebp, dword ptr [ebx + 0x14d1ab0] */
	if (m->sf != m->of) goto L_473fc2;	/* 473fad: jl 0x473fc2 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 473faf: push ebp */
	{ DWORD v_ = 0x4c76b8u; m->esp -= 4; M32(m->esp) = v_; }	/* 473fb0: push 0x4c76b8 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 473fb5: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x473fbfu; native_call(m, 0x46c710u);	/* 473fba: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 473fbf: add esp, 0xc */
L_473fc2:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 473fc2: push edi */
	m->ecx = (DWORD)(m->esi + 0x2fa68u);	/* 473fc3: lea ecx, [esi + 0x2fa68] */
	m->esp -= 4; M32(m->esp) = 0x473fceu; native_call(m, 0x467520u);	/* 473fc9: call 0x467520 */
	m->ecx = (DWORD)(m->esi + 0x468d4u);	/* 473fce: lea ecx, [esi + 0x468d4] */
	m->esp -= 4; M32(m->esp) = 0x473fd9u; native_call(m, 0x46b7f0u);	/* 473fd4: call 0x46b7f0 */
	m->ecx = (DWORD)(m->ebp + m->ebp*2 + 0x0u);	/* 473fd9: lea ecx, [ebp + ebp*2] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 473fdd: xor eax, eax */
	{ DWORD a_ = m->ecx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 473fdf: shl ecx, 6 */
	{ DWORD a_ = m->ecx, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 473fe2: add ecx, ebp */
	m->edx = (DWORD)(m->esi + 0x14cu);	/* 473fe4: lea edx, [esi + 0x14c] */
	{ DWORD a_ = m->ecx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 473fea: shl ecx, 5 */
	m->edi = (DWORD)(m->ecx + m->ebx*1 + 0x1486470u);	/* 473fed: lea edi, [ecx + ebx + 0x1486470] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 473ff4: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 473ff7: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 473ff9: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 473ffb: sub edi, ecx */
	m->eax = m->ecx;	/* 473ffd: mov eax, ecx */
	m->esi = m->edi;	/* 473fff: mov esi, edi */
	m->edi = m->edx;	/* 474001: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 474003: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 474006: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 474008: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 47400a: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 47400d: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 47400f: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 474013: xor esi, esi */
	M32((DWORD)(m->ecx + 0x31cu)) = m->ebp;	/* 474015: mov dword ptr [ecx + 0x31c], ebp */
	m->eax = M32((DWORD)(m->ebx + 0x202e8c8u));	/* 47401b: mov eax, dword ptr [ebx + 0x202e8c8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 474021: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_47404e;	/* 474023: jle 0x47404e */
	m->edi = (DWORD)(m->ebx + 0x1cd94b4u);	/* 474025: lea edi, [ebx + 0x1cd94b4] */
L_47402b:
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 47402b: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 47402f: mov eax, dword ptr [edi] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 474031: cmp eax, edx */
	if (!m->zf) goto L_47403d;	/* 474033: jne 0x47403d */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 474035: push esi */
	m->ecx = m->ebx;	/* 474036: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x47403du; native_call(m, 0x45e530u);	/* 474038: call 0x45e530 */
L_47403d:
	m->eax = M32((DWORD)(m->ebx + 0x202e8c8u));	/* 47403d: mov eax, dword ptr [ebx + 0x202e8c8] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 474043: inc esi */
	{ DWORD a_ = m->edi, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 474044: add edi, 0x8888 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47404a: cmp esi, eax */
	if (m->sf != m->of) goto L_47402b;	/* 47404c: jl 0x47402b */
L_47404e:
	m->edi = M32(m->esp); m->esp += 4;	/* 47404e: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 47404f: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 474050: pop ebp */
	m->eax = 0x1u;	/* 474051: mov eax, 1 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 474056: pop ebx */
	m->esp += 4 + 8; return;	/* 474057: ret 8 */
}

/* actor_setActorTypeItemInfoBy (0x474060), lifted by tools/lift.py */
static void lift_474060(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 474060: push ecx */
	m->edx = M32((DWORD)(m->esp + 0x8u));	/* 474061: mov edx, dword ptr [esp + 8] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 474065: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 474066: push ebp */
	m->ebp = m->ecx;	/* 474067: mov ebp, ecx */
	m->eax = (DWORD)(m->edx + m->edx*2 + 0x0u);	/* 474069: lea eax, [edx + edx*2] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 47406c: push esi */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 47406d: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 474070: sub eax, edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 474072: push edi */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 474073: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->edx + m->eax*8 + 0x0u);	/* 474076: lea ecx, [edx + eax*8] */
	m->eax = M32((DWORD)(m->ebp + 0x20f3ab8u));	/* 474079: mov eax, dword ptr [ebp + 0x20f3ab8] */
	{ DWORD a_ = m->eax, b_ = 0xfffffffeu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 47407f: add eax, -2 */
	m->ecx = (DWORD)(m->ebp + m->ecx*2 + 0x1561b68u);	/* 474082: lea ecx, [ebp + ecx*2 + 0x1561b68] */
	{ DWORD a_ = m->eax, b_ = 0x9u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 474089: cmp eax, 9 */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 47408c: mov dword ptr [esp + 0x10], ecx */
	if (!m->cf && !m->zf) goto L_47418d;	/* 474090: ja 0x47418d */
	switch (m->eax) { case 0: goto L_47409d; case 1: goto L_47409d; case 2: goto L_4740af; case 3: goto L_4740af; case 4: goto L_4740c1; case 5: goto L_4740c1; case 6: goto L_4740d3; case 7: goto L_4740d3; case 8: goto L_4740e5; case 9: goto L_4740e5; default: abort(); }	/* 474096: jmp dword ptr [eax*4 + 0x4741e8] */
L_47409d:
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 47409d: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4740a1: test eax, eax */
	if (!m->zf) goto L_474106;	/* 4740a3: jne 0x474106 */
	m->ebx = 0x3u;	/* 4740a5: mov ebx, 3 */
	goto L_474199;	/* 4740aa: jmp 0x474199 */
L_4740af:
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 4740af: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4740b3: test eax, eax */
	if (!m->zf) goto L_474106;	/* 4740b5: jne 0x474106 */
	m->ebx = 0x5u;	/* 4740b7: mov ebx, 5 */
	goto L_474199;	/* 4740bc: jmp 0x474199 */
L_4740c1:
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 4740c1: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4740c5: test eax, eax */
	if (!m->zf) goto L_474106;	/* 4740c7: jne 0x474106 */
	m->ebx = 0x24u;	/* 4740c9: mov ebx, 0x24 */
	goto L_474199;	/* 4740ce: jmp 0x474199 */
L_4740d3:
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 4740d3: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4740d7: test eax, eax */
	if (!m->zf) goto L_474106;	/* 4740d9: jne 0x474106 */
	m->ebx = 0x19u;	/* 4740db: mov ebx, 0x19 */
	goto L_474199;	/* 4740e0: jmp 0x474199 */
L_4740e5:
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 4740e5: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4740e9: test eax, eax */
	if (!m->zf) goto L_4740f7;	/* 4740eb: jne 0x4740f7 */
	m->ebx = 0x16u;	/* 4740ed: mov ebx, 0x16 */
	goto L_474199;	/* 4740f2: jmp 0x474199 */
L_4740f7:
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4740f7: cmp eax, 1 */
	if (!m->zf) goto L_474106;	/* 4740fa: jne 0x474106 */
	m->ebx = 0x17u;	/* 4740fc: mov ebx, 0x17 */
	goto L_474199;	/* 474101: jmp 0x474199 */
L_474106:
	{ DWORD a_ = m->ebx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 474106: or ebx, 0xffffffff */
L_474109:
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 474109: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->eax, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 47410d: shl eax, 6 */
	M8((DWORD)(m->eax + m->ecx*1 + 0x18cu)) = (BYTE)(0x0u);	/* 474110: mov byte ptr [eax + ecx + 0x18c], 0 */
L_474118:
	{ DWORD a_ = m->ebx, b_ = M32((DWORD)(m->ebp + 0x1561b64u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 474118: cmp ebx, dword ptr [ebp + 0x1561b64] */
	if (m->sf != m->of) goto L_47413b;	/* 47411e: jl 0x47413b */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 474120: push ebx */
	{ DWORD v_ = 0x4c76f0u; m->esp -= 4; M32(m->esp) = v_; }	/* 474121: push 0x4c76f0 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 474126: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x474130u; native_call(m, 0x46c710u);	/* 47412b: call 0x46c710 */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 474130: mov edx, dword ptr [esp + 0x24] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 474134: mov ecx, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 474138: add esp, 0xc */
L_47413b:
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 47413b: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 47413f: xor esi, esi */
	M32((DWORD)(m->ecx + m->eax*4 + 0x320u)) = m->ebx;	/* 474141: mov dword ptr [ecx + eax*4 + 0x320], ebx */
	m->eax = M32((DWORD)(m->ebp + 0x202e8c8u));	/* 474148: mov eax, dword ptr [ebp + 0x202e8c8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47414e: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_474185;	/* 474150: jle 0x474185 */
	m->edi = (DWORD)(m->ebp + 0x1cd9844u);	/* 474152: lea edi, [ebp + 0x1cd9844] */
L_474158:
	{ DWORD a_ = M32((DWORD)(m->edi + 0xfffffc70u)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 474158: cmp dword ptr [edi - 0x390], edx */
	if (!m->zf) goto L_474174;	/* 47415e: jne 0x474174 */
	m->ecx = M32((DWORD)(m->edi + 0x0u));	/* 474160: mov ecx, dword ptr [edi] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 474162: mov edx, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 474166: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 474167: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 474168: push esi */
	m->ecx = m->ebp;	/* 474169: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x474170u; native_call(m, 0x45e600u);	/* 47416b: call 0x45e600 */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 474170: mov edx, dword ptr [esp + 0x18] */
L_474174:
	m->eax = M32((DWORD)(m->ebp + 0x202e8c8u));	/* 474174: mov eax, dword ptr [ebp + 0x202e8c8] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 47417a: inc esi */
	{ DWORD a_ = m->edi, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 47417b: add edi, 0x8888 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 474181: cmp esi, eax */
	if (m->sf != m->of) goto L_474158;	/* 474183: jl 0x474158 */
L_474185:
	m->edi = M32(m->esp); m->esp += 4;	/* 474185: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 474186: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 474187: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 474188: pop ebx */
	m->ecx = M32(m->esp); m->esp += 4;	/* 474189: pop ecx */
	m->esp += 4 + 12; return;	/* 47418a: ret 0xc */
L_47418d:
	m->ebx = M32((DWORD)(m->esp + 0x20u));	/* 47418d: mov ebx, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 474191: test ebx, ebx */
	if (m->sf != m->of) goto L_474109;	/* 474193: jl 0x474109 */
L_474199:
	m->eax = (DWORD)(m->ebx + m->ebx*8 + 0x0u);	/* 474199: lea eax, [ebx + ebx*8] */
	m->eax = (DWORD)(m->ebx + m->eax*4 + 0x0u);	/* 47419c: lea eax, [ebx + eax*4] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 47419f: shl eax, 3 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4741a2: sub eax, ebx */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4741a4: lea eax, [eax + eax*4] */
	m->edi = (DWORD)(m->ebp + m->eax*8 + 0x14d1ab4u);	/* 4741a7: lea edi, [ebp + eax*8 + 0x14d1ab4] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 4741ae: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->eax, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4741b2: shl eax, 6 */
	m->esi = (DWORD)(m->eax + m->ecx*1 + 0x18cu);	/* 4741b5: lea esi, [eax + ecx + 0x18c] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4741bc: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4741bf: xor eax, eax */
	M32((DWORD)(m->esp + 0x20u)) = m->esi;	/* 4741c1: mov dword ptr [esp + 0x20], esi */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4741c5: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4741c7: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4741c9: sub edi, ecx */
	m->eax = m->ecx;	/* 4741cb: mov eax, ecx */
	m->esi = m->edi;	/* 4741cd: mov esi, edi */
	m->edi = M32((DWORD)(m->esp + 0x20u));	/* 4741cf: mov edi, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4741d3: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4741d6: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4741d8: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4741da: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4741dd: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 4741df: mov ecx, dword ptr [esp + 0x10] */
	goto L_474118;	/* 4741e3: jmp 0x474118 */
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
