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

static void lift_467b90(X86 *m);

/* sound_loadWav (0x467b90), lifted by tools/lift.py */
static void lift_467b90(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x6cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 467b90: sub esp, 0x6c */
	m->eax = M32((DWORD)(m->esp + 0x70u));	/* 467b93: mov eax, dword ptr [esp + 0x70] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 467b97: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 467b98: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 467b99: push edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 467b9a: push 0 */
	{ DWORD v_ = 0x80u; m->esp -= 4; M32(m->esp) = v_; }	/* 467b9c: push 0x80 */
	{ DWORD v_ = 0x3u; m->esp -= 4; M32(m->esp) = v_; }	/* 467ba1: push 3 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 467ba3: push 0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 467ba5: push 1 */
	{ DWORD v_ = 0x80000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 467ba7: push 0x80000000 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 467bac: push eax */
	m->esp -= 4; M32(m->esp) = 0x467bb3u; native_call(m, M32(0x4a91b4u));	/* 467bad: call dword ptr [0x4a91b4] */
	m->esi = m->eax;	/* 467bb3: mov esi, eax */
	{ DWORD a_ = m->esi, b_ = 0xffffffffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 467bb5: cmp esi, -1 */
	if (!m->zf) goto L_467bc3;	/* 467bb8: jne 0x467bc3 */
	m->edi = M32(m->esp); m->esp += 4;	/* 467bba: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 467bbb: pop esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 467bbc: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 467bbe: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x6cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 467bbf: add esp, 0x6c */
	m->esp += 4 + 0; return;	/* 467bc2: ret  */
L_467bc3:
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 467bc3: push ebp */
	m->ebp = M32((DWORD)(0x4a9068u));	/* 467bc4: mov ebp, dword ptr [0x4a9068] */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 467bca: lea ecx, [esp + 0x14] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 467bce: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 467bd0: push ecx */
	m->edx = (DWORD)(m->esp + 0x58u);	/* 467bd1: lea edx, [esp + 0x58] */
	{ DWORD v_ = 0x2cu; m->esp -= 4; M32(m->esp) = v_; }	/* 467bd5: push 0x2c */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 467bd7: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 467bd8: push esi */
	m->esp -= 4; M32(m->esp) = 0x467bdbu; native_call(m, m->ebp);	/* 467bd9: call ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 467bdb: xor eax, eax */
	m->ecx = (m->ecx & 0xffff0000u) | ((M16((DWORD)(m->esp + 0x66u))) & 0xffff);	/* 467bdd: mov cx, word ptr [esp + 0x66] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 467be2: mov dword ptr [esp + 0x1c], eax */
	M16((DWORD)(m->esp + 0x1eu)) = (WORD)((m->ecx & 0xffff));	/* 467be6: mov word ptr [esp + 0x1e], cx */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 467beb: mov dword ptr [esp + 0x20], eax */
	m->ecx = M32((DWORD)(m->esp + 0x68u));	/* 467bef: mov ecx, dword ptr [esp + 0x68] */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 467bf3: mov dword ptr [esp + 0x24], eax */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 467bf7: mov dword ptr [esp + 0x20], ecx */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 467bfb: mov dword ptr [esp + 0x28], eax */
	m->eax = M32((DWORD)(m->esp + 0x70u));	/* 467bff: mov eax, dword ptr [esp + 0x70] */
	M16((DWORD)(m->esp + 0x28u)) = (WORD)((m->eax & 0xffff));	/* 467c03: mov word ptr [esp + 0x28], ax */
	{ DWORD a_ = m->eax, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 467c08: and eax, 0xffff */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 467c0d: imul eax, ecx */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 467c10: mov dword ptr [esp + 0x24], eax */
	m->edx = (m->edx & 0xffff0000u) | ((M16((DWORD)(m->esp + 0x72u))) & 0xffff);	/* 467c14: mov dx, word ptr [esp + 0x72] */
	m->ecx = 0x9u;	/* 467c19: mov ecx, 9 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 467c1e: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x2cu);	/* 467c20: lea edi, [esp + 0x2c] */
	M16((DWORD)(m->esp + 0x1cu)) = (WORD)(0x1u);	/* 467c24: mov word ptr [esp + 0x1c], 1 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 467c2b: rep stosd dword ptr es:[edi], eax */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 467c2d: lea eax, [esp + 0x1c] */
	M16((DWORD)(m->esp + 0x2au)) = (WORD)((m->edx & 0xffff));	/* 467c31: mov word ptr [esp + 0x2a], dx */
	M32((DWORD)(m->esp + 0x3cu)) = m->eax;	/* 467c36: mov dword ptr [esp + 0x3c], eax */
	m->eax = M32((DWORD)(m->esp + 0x78u));	/* 467c3a: mov eax, dword ptr [esp + 0x78] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 467c3e: push eax */
	M32((DWORD)(m->esp + 0x30u)) = 0x24u;	/* 467c3f: mov dword ptr [esp + 0x30], 0x24 */
	M32((DWORD)(m->esp + 0x34u)) = 0xe2u;	/* 467c47: mov dword ptr [esp + 0x34], 0xe2 */
	M32((DWORD)(m->esp + 0x38u)) = m->eax;	/* 467c4f: mov dword ptr [esp + 0x38], eax */
	M32((DWORD)(m->esp + 0x84u)) = m->eax;	/* 467c53: mov dword ptr [esp + 0x84], eax */
	m->esp -= 4; M32(m->esp) = 0x467c5fu; native_call(m, 0x49f1aau);	/* 467c5a: call 0x49f1aa */
	m->edi = m->eax;	/* 467c5f: mov edi, eax */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 467c61: push 0x64 */
	M32((DWORD)(m->esp + 0x20u)) = m->edi;	/* 467c63: mov dword ptr [esp + 0x20], edi */
	m->esp -= 4; M32(m->esp) = 0x467c6cu; native_call(m, 0x49f1aau);	/* 467c67: call 0x49f1aa */
	m->edx = M32((DWORD)(m->esp + 0x88u));	/* 467c6c: mov edx, dword ptr [esp + 0x88] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 467c73: add esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 467c76: lea ecx, [esp + 0x14] */
	m->ebx = m->eax;	/* 467c7a: mov ebx, eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 467c7c: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 467c7e: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 467c7f: push edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 467c80: push edi */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 467c81: push esi */
	m->esp -= 4; M32(m->esp) = 0x467c84u; native_call(m, m->ebp);	/* 467c82: call ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 467c84: push esi */
	m->esp -= 4; M32(m->esp) = 0x467c8bu; native_call(m, M32(0x4a91b0u));	/* 467c85: call dword ptr [0x4a91b0] */
	m->eax = M32((DWORD)(0xa0e804u));	/* 467c8b: mov eax, dword ptr [0xa0e804] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 467c90: push 0 */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 467c92: lea edx, [esp + 0x30] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 467c96: push ebx */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 467c97: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 467c99: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 467c9a: push eax */
	m->esp -= 4; M32(m->esp) = 0x467c9eu; native_call(m, M32((DWORD)(m->ecx + 0xcu)));	/* 467c9b: call dword ptr [ecx + 0xc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 467c9e: test eax, eax */
	m->ebp = M32(m->esp); m->esp += 4;	/* 467ca0: pop ebp */
	if (m->zf) goto L_467cc0;	/* 467ca1: je 0x467cc0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 467ca3: push 0 */
	{ DWORD v_ = 0x4c4de0u; m->esp -= 4; M32(m->esp) = v_; }	/* 467ca5: push 0x4c4de0 */
	{ DWORD v_ = 0x4c4dc4u; m->esp -= 4; M32(m->esp) = v_; }	/* 467caa: push 0x4c4dc4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 467caf: push 0 */
	m->esp -= 4; M32(m->esp) = 0x467cb7u; native_call(m, M32(0x4a9324u));	/* 467cb1: call dword ptr [0x4a9324] */
	m->edi = M32(m->esp); m->esp += 4;	/* 467cb7: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 467cb8: pop esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 467cb9: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 467cbb: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x6cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 467cbc: add esp, 0x6c */
	m->esp += 4 + 0; return;	/* 467cbf: ret  */
L_467cc0:
	m->eax = M32((DWORD)(m->ebx + 0x0u));	/* 467cc0: mov eax, dword ptr [ebx] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 467cc2: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 467cc4: push 0 */
	m->edx = (DWORD)(m->esp + 0x84u);	/* 467cc6: lea edx, [esp + 0x84] */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 467ccd: mov ecx, dword ptr [eax] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 467ccf: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 467cd1: push edx */
	m->edx = (DWORD)(m->esp + 0x1cu);	/* 467cd2: lea edx, [esp + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 467cd6: push edx */
	m->edx = M32((DWORD)(m->esp + 0x90u));	/* 467cd7: mov edx, dword ptr [esp + 0x90] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 467cde: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 467cdf: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 467ce1: push eax */
	m->esp -= 4; M32(m->esp) = 0x467ce5u; native_call(m, M32((DWORD)(m->ecx + 0x2cu)));	/* 467ce2: call dword ptr [ecx + 0x2c] */
	m->ecx = M32((DWORD)(m->esp + 0x7cu));	/* 467ce5: mov ecx, dword ptr [esp + 0x7c] */
	m->esi = m->edi;	/* 467ce9: mov esi, edi */
	m->edi = M32((DWORD)(m->esp + 0xcu));	/* 467ceb: mov edi, dword ptr [esp + 0xc] */
	m->eax = m->ecx;	/* 467cef: mov eax, ecx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 467cf1: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 467cf4: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 467cf6: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 467cf8: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 467cfb: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edx = M32((DWORD)(m->esp + 0x7cu));	/* 467cfd: mov edx, dword ptr [esp + 0x7c] */
	m->eax = M32((DWORD)(m->ebx + 0x0u));	/* 467d01: mov eax, dword ptr [ebx] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 467d03: xor esi, esi */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 467d05: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 467d07: push esi */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 467d08: push esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 467d09: push edx */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 467d0a: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 467d0e: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 467d0f: push eax */
	m->esp -= 4; M32(m->esp) = 0x467d13u; native_call(m, M32((DWORD)(m->ecx + 0x4cu)));	/* 467d10: call dword ptr [ecx + 0x4c] */
	M32((DWORD)(m->ebx + 0x20u)) = m->esi;	/* 467d13: mov dword ptr [ebx + 0x20], esi */
	m->eax = (DWORD)(m->ebx + 0x44u);	/* 467d16: lea eax, [ebx + 0x44] */
	m->ecx = 0x8u;	/* 467d19: mov ecx, 8 */
L_467d1e:
	M32((DWORD)(m->eax + 0xffffffe0u)) = m->esi;	/* 467d1e: mov dword ptr [eax - 0x20], esi */
	M32((DWORD)(m->eax + 0x0u)) = m->esi;	/* 467d21: mov dword ptr [eax], esi */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 467d23: add eax, 4 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 467d26: dec ecx */
	if (!m->zf) goto L_467d1e;	/* 467d27: jne 0x467d1e */
	m->esi = m->ebx;	/* 467d29: mov esi, ebx */
	m->edi = 0x8u;	/* 467d2b: mov edi, 8 */
L_467d30:
	m->eax = M32((DWORD)(0xa0e804u));	/* 467d30: mov eax, dword ptr [0xa0e804] */
	m->edx = M32((DWORD)(m->ebx + 0x0u));	/* 467d35: mov edx, dword ptr [ebx] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 467d37: push esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 467d38: push edx */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 467d39: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 467d3b: push eax */
	m->esp -= 4; M32(m->esp) = 0x467d3fu; native_call(m, M32((DWORD)(m->ecx + 0x14u)));	/* 467d3c: call dword ptr [ecx + 0x14] */
	{ DWORD a_ = m->esi, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 467d3f: add esi, 4 */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 467d42: dec edi */
	if (!m->zf) goto L_467d30;	/* 467d43: jne 0x467d30 */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 467d45: mov eax, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 467d49: push eax */
	m->esp -= 4; M32(m->esp) = 0x467d4fu; native_call(m, 0x49ef24u);	/* 467d4a: call 0x49ef24 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 467d4f: add esp, 4 */
	m->eax = m->ebx;	/* 467d52: mov eax, ebx */
	m->edi = M32(m->esp); m->esp += 4;	/* 467d54: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 467d55: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 467d56: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x6cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 467d57: add esp, 0x6c */
	m->esp += 4 + 0; return;	/* 467d5a: ret  */
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
