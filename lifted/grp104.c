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

static void lift_467d70(X86 *m);
static void lift_467db0(X86 *m);
static void lift_467dd0(X86 *m);
static void lift_457310(X86 *m);
static void lift_4572b0(X86 *m);
static void lift_457150(X86 *m);
static void lift_467a50(X86 *m);

/* sound_init (0x467a50), lifted by tools/lift.py */
static void lift_467a50(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x38u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 467a50: sub esp, 0x38 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 467a53: push 0 */
	{ DWORD v_ = 0xa0e804u; m->esp -= 4; M32(m->esp) = v_; }	/* 467a55: push 0xa0e804 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 467a5a: push 0 */
	m->esp -= 4; M32(m->esp) = 0x467a61u; native_call(m, 0x4a82e6u);	/* 467a5c: call 0x4a82e6 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 467a61: test eax, eax */
	if (m->zf) goto L_467a6b;	/* 467a63: je 0x467a6b */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 467a65: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 467a67: add esp, 0x38 */
	m->esp += 4 + 0; return;	/* 467a6a: ret  */
L_467a6b:
	m->eax = M32((DWORD)(0xa0e804u));	/* 467a6b: mov eax, dword ptr [0xa0e804] */
	m->edx = M32((DWORD)(m->esp + 0x3cu));	/* 467a70: mov edx, dword ptr [esp + 0x3c] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 467a74: push 2 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 467a76: push edx */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 467a77: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 467a79: push eax */
	m->esp -= 4; M32(m->esp) = 0x467a7du; native_call(m, M32((DWORD)(m->ecx + 0x18u)));	/* 467a7a: call dword ptr [ecx + 0x18] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 467a7d: test eax, eax */
	if (m->zf) goto L_467a87;	/* 467a7f: je 0x467a87 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 467a81: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 467a83: add esp, 0x38 */
	m->esp += 4 + 0; return;	/* 467a86: ret  */
L_467a87:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 467a87: push edi */
	m->ecx = 0x9u;	/* 467a88: mov ecx, 9 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 467a8d: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x18u);	/* 467a8f: lea edi, [esp + 0x18] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 467a93: rep stosd dword ptr es:[edi], eax */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 467a95: mov dword ptr [esp + 0x20], eax */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 467a99: mov dword ptr [esp + 0x28], eax */
	M32((DWORD)(m->esp + 0x4u)) = m->eax;	/* 467a9d: mov dword ptr [esp + 4], eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 467aa1: push 0 */
	M32((DWORD)(m->esp + 0xcu)) = m->eax;	/* 467aa3: mov dword ptr [esp + 0xc], eax */
	m->edx = (DWORD)(m->esp + 0x1cu);	/* 467aa7: lea edx, [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 467aab: mov dword ptr [esp + 0x10], eax */
	M32((DWORD)(m->esp + 0x1cu)) = 0x24u;	/* 467aaf: mov dword ptr [esp + 0x1c], 0x24 */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 467ab7: mov dword ptr [esp + 0x14], eax */
	M32((DWORD)(m->esp + 0x20u)) = 0x1u;	/* 467abb: mov dword ptr [esp + 0x20], 1 */
	M16((DWORD)(m->esp + 0x18u)) = (WORD)((m->eax & 0xffff));	/* 467ac3: mov word ptr [esp + 0x18], ax */
	m->eax = M32((DWORD)(0xa0e804u));	/* 467ac8: mov eax, dword ptr [0xa0e804] */
	M16((DWORD)(m->esp + 0x8u)) = (WORD)(0x1u);	/* 467acd: mov word ptr [esp + 8], 1 */
	M16((DWORD)(m->esp + 0xau)) = (WORD)(0x2u);	/* 467ad4: mov word ptr [esp + 0xa], 2 */
	M32((DWORD)(m->esp + 0xcu)) = 0xac44u;	/* 467adb: mov dword ptr [esp + 0xc], 0xac44 */
	M16((DWORD)(m->esp + 0x16u)) = (WORD)(0x10u);	/* 467ae3: mov word ptr [esp + 0x16], 0x10 */
	M16((DWORD)(m->esp + 0x14u)) = (WORD)(0x4u);	/* 467aea: mov word ptr [esp + 0x14], 4 */
	M32((DWORD)(m->esp + 0x10u)) = 0x2b110u;	/* 467af1: mov dword ptr [esp + 0x10], 0x2b110 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 467af9: mov ecx, dword ptr [eax] */
	{ DWORD v_ = 0xa0e808u; m->esp -= 4; M32(m->esp) = v_; }	/* 467afb: push 0xa0e808 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 467b00: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 467b01: push eax */
	m->esp -= 4; M32(m->esp) = 0x467b05u; native_call(m, M32((DWORD)(m->ecx + 0xcu)));	/* 467b02: call dword ptr [ecx + 0xc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 467b05: test eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 467b07: pop edi */
	if (m->zf) goto L_467b10;	/* 467b08: je 0x467b10 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 467b0a: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 467b0c: add esp, 0x38 */
	m->esp += 4 + 0; return;	/* 467b0f: ret  */
L_467b10:
	m->eax = M32((DWORD)(0xa0e808u));	/* 467b10: mov eax, dword ptr [0xa0e808] */
	m->edx = (DWORD)(m->esp + 0x0u);	/* 467b15: lea edx, [esp] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 467b19: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 467b1a: push eax */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 467b1b: mov ecx, dword ptr [eax] */
	m->esp -= 4; M32(m->esp) = 0x467b20u; native_call(m, M32((DWORD)(m->ecx + 0x38u)));	/* 467b1d: call dword ptr [ecx + 0x38] */
	m->eax = M32((DWORD)(0xa0e808u));	/* 467b20: mov eax, dword ptr [0xa0e808] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 467b25: push 1 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 467b27: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 467b29: push 0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 467b2b: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 467b2d: push eax */
	m->esp -= 4; M32(m->esp) = 0x467b31u; native_call(m, M32((DWORD)(m->ecx + 0x30u)));	/* 467b2e: call dword ptr [ecx + 0x30] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 467b31: test eax, eax */
	if (m->zf) goto L_467b50;	/* 467b33: je 0x467b50 */
	m->eax = M32((DWORD)(0xa0e804u));	/* 467b35: mov eax, dword ptr [0xa0e804] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 467b3a: push eax */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 467b3b: mov edx, dword ptr [eax] */
	m->esp -= 4; M32(m->esp) = 0x467b40u; native_call(m, M32((DWORD)(m->edx + 0x8u)));	/* 467b3d: call dword ptr [edx + 8] */
	M32((DWORD)(0xa0e804u)) = 0x0u;	/* 467b40: mov dword ptr [0xa0e804], 0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 467b4a: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 467b4c: add esp, 0x38 */
	m->esp += 4 + 0; return;	/* 467b4f: ret  */
L_467b50:
	M32((DWORD)(0xa0e80cu)) = 0x1u;	/* 467b50: mov dword ptr [0xa0e80c], 1 */
	m->eax = 0x1u;	/* 467b5a: mov eax, 1 */
	{ DWORD a_ = m->esp, b_ = 0x38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 467b5f: add esp, 0x38 */
	m->esp += 4 + 0; return;	/* 467b62: ret  */
}

/* dsbuf_play (0x467d70), lifted by tools/lift.py */
static void lift_467d70(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 467d70: push esi */
	m->esi = M32((DWORD)(m->esp + 0x8u));	/* 467d71: mov esi, dword ptr [esp + 8] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 467d75: test esi, esi */
	if (m->zf) goto L_467da4;	/* 467d77: je 0x467da4 */
	m->eax = M32((DWORD)(m->esi + 0x20u));	/* 467d79: mov eax, dword ptr [esi + 0x20] */
	m->eax = M32((DWORD)(m->esi + m->eax*4 + 0x0u));	/* 467d7c: mov eax, dword ptr [esi + eax*4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 467d7f: test eax, eax */
	if (m->zf) goto L_467d8f;	/* 467d81: je 0x467d8f */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 467d83: mov ecx, dword ptr [eax] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 467d85: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 467d87: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 467d89: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 467d8b: push eax */
	m->esp -= 4; M32(m->esp) = 0x467d8fu; native_call(m, M32((DWORD)(m->ecx + 0x30u)));	/* 467d8c: call dword ptr [ecx + 0x30] */
L_467d8f:
	m->eax = M32((DWORD)(m->esi + 0x20u));	/* 467d8f: mov eax, dword ptr [esi + 0x20] */
	{ DWORD a_ = m->eax, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 467d92: cmp eax, 7 */
	if (m->sf == m->of) goto L_467d9d;	/* 467d95: jge 0x467d9d */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 467d97: inc eax */
	M32((DWORD)(m->esi + 0x20u)) = m->eax;	/* 467d98: mov dword ptr [esi + 0x20], eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 467d9b: pop esi */
	m->esp += 4 + 0; return;	/* 467d9c: ret  */
L_467d9d:
	M32((DWORD)(m->esi + 0x20u)) = 0x0u;	/* 467d9d: mov dword ptr [esi + 0x20], 0 */
L_467da4:
	m->esi = M32(m->esp); m->esp += 4;	/* 467da4: pop esi */
	m->esp += 4 + 0; return;	/* 467da5: ret  */
}

/* dsbuf_setVolume (0x467db0), lifted by tools/lift.py */
static void lift_467db0(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 467db0: mov eax, dword ptr [esp + 4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 467db4: test eax, eax */
	if (m->zf) goto L_467dcd;	/* 467db6: je 0x467dcd */
	m->ecx = M32((DWORD)(m->eax + 0x20u));	/* 467db8: mov ecx, dword ptr [eax + 0x20] */
	m->eax = M32((DWORD)(m->eax + m->ecx*4 + 0x0u));	/* 467dbb: mov eax, dword ptr [eax + ecx*4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 467dbe: test eax, eax */
	if (m->zf) goto L_467dcd;	/* 467dc0: je 0x467dcd */
	m->ecx = M32((DWORD)(m->esp + 0x8u));	/* 467dc2: mov ecx, dword ptr [esp + 8] */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 467dc6: mov edx, dword ptr [eax] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 467dc8: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 467dc9: push eax */
	m->esp -= 4; M32(m->esp) = 0x467dcdu; native_call(m, M32((DWORD)(m->edx + 0x3cu)));	/* 467dca: call dword ptr [edx + 0x3c] */
L_467dcd:
	m->esp += 4 + 0; return;	/* 467dcd: ret  */
}

/* sound_467dd0 (0x467dd0), lifted by tools/lift.py */
static void lift_467dd0(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 467dd0: push esi */
	m->esi = M32((DWORD)(m->esp + 0x8u));	/* 467dd1: mov esi, dword ptr [esp + 8] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 467dd5: test esi, esi */
	if (m->zf) goto L_467e50;	/* 467dd7: je 0x467e50 */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 467dd9: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 467ddd: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x2710u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 467ddf: cmp ecx, 0x2710 */
	m->eax = (m->eax & ~(0xffu << 0)) | ((((!m->zf && m->sf == m->of) ? 1u : 0u) & 0xff) << 0);	/* 467de5: setg al */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 467de8: xor edx, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffd8f0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 467dea: cmp ecx, 0xffffd8f0 */
	m->edx = (m->edx & ~(0xffu << 0)) | ((((m->sf != m->of) ? 1u : 0u) & 0xff) << 0);	/* 467df0: setl dl */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 467df3: or eax, edx */
	if (!m->zf) goto L_467e50;	/* 467df5: jne 0x467e50 */
	m->edx = M32((DWORD)(m->esi + 0x20u));	/* 467df7: mov edx, dword ptr [esi + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 467dfa: mov eax, dword ptr [esp + 0xc] */
	M32((DWORD)(m->esi + m->edx*4 + 0x24u)) = m->eax;	/* 467dfe: mov dword ptr [esi + edx*4 + 0x24], eax */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 467e02: dec eax */
	if (m->zf) goto L_467e11;	/* 467e03: je 0x467e11 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 467e05: dec eax */
	if (!m->zf) goto L_467e18;	/* 467e06: jne 0x467e18 */
	m->eax = M32((DWORD)(m->esi + 0x20u));	/* 467e08: mov eax, dword ptr [esi + 0x20] */
	M32((DWORD)(m->esi + m->eax*4 + 0x44u)) = m->ecx;	/* 467e0b: mov dword ptr [esi + eax*4 + 0x44], ecx */
	goto L_467e18;	/* 467e0f: jmp 0x467e18 */
L_467e11:
	m->edx = M32((DWORD)(m->esi + 0x20u));	/* 467e11: mov edx, dword ptr [esi + 0x20] */
	M32((DWORD)(m->esi + m->edx*4 + 0x44u)) = m->ecx;	/* 467e14: mov dword ptr [esi + edx*4 + 0x44], ecx */
L_467e18:
	m->eax = M32((DWORD)(m->esi + 0x20u));	/* 467e18: mov eax, dword ptr [esi + 0x20] */
	m->ecx = M32((DWORD)(m->esi + m->eax*4 + 0x0u));	/* 467e1b: mov ecx, dword ptr [esi + eax*4] */
	m->eax = M32((DWORD)(m->esi + m->eax*4 + 0x44u));	/* 467e1e: mov eax, dword ptr [esi + eax*4 + 0x44] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 467e22: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 467e23: push ecx */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 467e24: mov edx, dword ptr [ecx] */
	m->esp -= 4; M32(m->esp) = 0x467e29u; native_call(m, M32((DWORD)(m->edx + 0x40u)));	/* 467e26: call dword ptr [edx + 0x40] */
	m->ecx = M32((DWORD)(m->esi + 0x20u));	/* 467e29: mov ecx, dword ptr [esi + 0x20] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 467e2c: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 467e2e: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 467e30: push 0 */
	m->eax = M32((DWORD)(m->esi + m->ecx*4 + 0x0u));	/* 467e32: mov eax, dword ptr [esi + ecx*4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 467e35: push eax */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 467e36: mov edx, dword ptr [eax] */
	m->esp -= 4; M32(m->esp) = 0x467e3bu; native_call(m, M32((DWORD)(m->edx + 0x30u)));	/* 467e38: call dword ptr [edx + 0x30] */
	m->eax = M32((DWORD)(m->esi + 0x20u));	/* 467e3b: mov eax, dword ptr [esi + 0x20] */
	{ DWORD a_ = m->eax, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 467e3e: cmp eax, 7 */
	if (m->sf == m->of) goto L_467e49;	/* 467e41: jge 0x467e49 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 467e43: inc eax */
	M32((DWORD)(m->esi + 0x20u)) = m->eax;	/* 467e44: mov dword ptr [esi + 0x20], eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 467e47: pop esi */
	m->esp += 4 + 0; return;	/* 467e48: ret  */
L_467e49:
	M32((DWORD)(m->esi + 0x20u)) = 0x0u;	/* 467e49: mov dword ptr [esi + 0x20], 0 */
L_467e50:
	m->esi = M32(m->esp); m->esp += 4;	/* 467e50: pop esi */
	m->esp += 4 + 0; return;	/* 467e51: ret  */
}

/* music_shutdown (0x457310), lifted by tools/lift.py */
static void lift_457310(X86 *m)
{
	m->eax = M32((DWORD)(0xa0e670u));	/* 457310: mov eax, dword ptr [0xa0e670] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 457315: test eax, eax */
	if (m->zf) goto L_45732f;	/* 457317: je 0x45732f */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 457319: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45731b: push eax */
	m->esp -= 4; M32(m->esp) = 0x45731fu; native_call(m, M32((DWORD)(m->ecx + 0x8u)));	/* 45731c: call dword ptr [ecx + 8] */
	M32((DWORD)(0xa0e670u)) = 0x0u;	/* 45731f: mov dword ptr [0xa0e670], 0 */
	native_call(m, M32(0x4a93b8u)); return;	/* 457329: jmp dword ptr [0x4a93b8] */
L_45732f:
	m->esp += 4 + 0; return;	/* 45732f: ret  */
}

/* music_4572b0 (0x4572b0), lifted by tools/lift.py */
static void lift_4572b0(X86 *m)
{
	m->eax = M32((DWORD)(0xa0e670u));	/* 4572b0: mov eax, dword ptr [0xa0e670] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4572b5: sub esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4572b8: test eax, eax */
	if (m->zf) goto L_457300;	/* 4572ba: je 0x457300 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 4572bc: mov ecx, dword ptr [eax] */
	m->edx = (DWORD)(m->esp + 0x0u);	/* 4572be: lea edx, [esp] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4572c2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4572c3: push eax */
	m->esp -= 4; M32(m->esp) = 0x4572c7u; native_call(m, M32((DWORD)(m->ecx + 0x20u)));	/* 4572c4: call dword ptr [ecx + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 4572c7: mov eax, dword ptr [esp + 4] */
	m->ecx = M32((DWORD)(0xa0e01cu));	/* 4572cb: mov ecx, dword ptr [0xa0e01c] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4572d1: cmp eax, ecx */
	if (m->sf != m->of) goto L_457300;	/* 4572d3: jl 0x457300 */
	if (!m->zf && m->sf == m->of) goto L_4572e4;	/* 4572d5: jg 0x4572e4 */
	m->ecx = M32((DWORD)(m->esp + 0x0u));	/* 4572d7: mov ecx, dword ptr [esp] */
	m->eax = M32((DWORD)(0xa0e018u));	/* 4572db: mov eax, dword ptr [0xa0e018] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4572e0: cmp ecx, eax */
	if (m->cf) goto L_457300;	/* 4572e2: jb 0x457300 */
L_4572e4:
	m->eax = M32((DWORD)(0xa0e670u));	/* 4572e4: mov eax, dword ptr [0xa0e670] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4572e9: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4572eb: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4572ed: push eax */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 4572ee: mov edx, dword ptr [eax] */
	m->esp -= 4; M32(m->esp) = 0x4572f3u; native_call(m, M32((DWORD)(m->edx + 0x28u)));	/* 4572f0: call dword ptr [edx + 0x28] */
	m->eax = M32((DWORD)(0xa0e670u));	/* 4572f3: mov eax, dword ptr [0xa0e670] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4572f8: push 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4572fa: push eax */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 4572fb: mov ecx, dword ptr [eax] */
	m->esp -= 4; M32(m->esp) = 0x457300u; native_call(m, M32((DWORD)(m->ecx + 0x1cu)));	/* 4572fd: call dword ptr [ecx + 0x1c] */
L_457300:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 457300: add esp, 8 */
	m->esp += 4 + 0; return;	/* 457303: ret  */
}

/* music_play (0x457150), lifted by tools/lift.py */
static void lift_457150(X86 *m)
{
	m->eax = M32((DWORD)(0x4e0c94u));	/* 457150: mov eax, dword ptr [0x4e0c94] */
	{ DWORD a_ = m->esp, b_ = 0x20cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 457155: sub esp, 0x20c */
	{ DWORD a_ = m->eax, b_ = 0x32u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45715b: cmp eax, 0x32 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45715e: push edi */
	if (m->sf == m->of) goto L_457173;	/* 45715f: jge 0x457173 */
	m->esp -= 4; M32(m->esp) = 0x457166u; lift_457310(m);	/* 457161: call 0x457310 */
	m->eax = 0x1u;	/* 457166: mov eax, 1 */
	m->edi = M32(m->esp); m->esp += 4;	/* 45716b: pop edi */
	{ DWORD a_ = m->esp, b_ = 0x20cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45716c: add esp, 0x20c */
	m->esp += 4 + 0; return;	/* 457172: ret  */
L_457173:
	m->eax = M32((DWORD)(0xa0e670u));	/* 457173: mov eax, dword ptr [0xa0e670] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 457178: test eax, eax */
	if (m->zf) goto L_457181;	/* 45717a: je 0x457181 */
	m->esp -= 4; M32(m->esp) = 0x457181u; lift_457310(m);	/* 45717c: call 0x457310 */
L_457181:
	m->edi = M32((DWORD)(m->esp + 0x214u));	/* 457181: mov edi, dword ptr [esp + 0x214] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 457188: push edi */
	m->esp -= 4; M32(m->esp) = 0x45718eu; native_call(m, 0x46ca70u);	/* 457189: call 0x46ca70 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45718e: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 457191: test eax, eax */
	if (!m->zf) goto L_4571b0;	/* 457193: jne 0x4571b0 */
	m->eax = M32((DWORD)(0xa0e670u));	/* 457195: mov eax, dword ptr [0xa0e670] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45719a: test eax, eax */
	if (m->zf) goto L_4571a3;	/* 45719c: je 0x4571a3 */
	m->esp -= 4; M32(m->esp) = 0x4571a3u; lift_457310(m);	/* 45719e: call 0x457310 */
L_4571a3:
	m->eax = 0x1u;	/* 4571a3: mov eax, 1 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4571a8: pop edi */
	{ DWORD a_ = m->esp, b_ = 0x20cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4571a9: add esp, 0x20c */
	m->esp += 4 + 0; return;	/* 4571af: ret  */
L_4571b0:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4571b0: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4571b8u; native_call(m, M32(0x4a93bcu));	/* 4571b2: call dword ptr [0x4a93bc] */
	m->eax = (DWORD)(m->esp + 0x4u);	/* 4571b8: lea eax, [esp + 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4571bc: push eax */
	{ DWORD v_ = 0x4aae90u; m->esp -= 4; M32(m->esp) = v_; }	/* 4571bd: push 0x4aae90 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4571c2: push 1 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4571c4: push 0 */
	{ DWORD v_ = 0x4aaf10u; m->esp -= 4; M32(m->esp) = v_; }	/* 4571c6: push 0x4aaf10 */
	m->esp -= 4; M32(m->esp) = 0x4571d1u; native_call(m, M32(0x4a93b4u));	/* 4571cb: call dword ptr [0x4a93b4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4571d1: test eax, eax */
	if (m->zf) goto L_4571df;	/* 4571d3: je 0x4571df */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4571d5: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 4571d7: pop edi */
	{ DWORD a_ = m->esp, b_ = 0x20cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4571d8: add esp, 0x20c */
	m->esp += 4 + 0; return;	/* 4571de: ret  */
L_4571df:
	m->ecx = (DWORD)(m->esp + 0x8u);	/* 4571df: lea ecx, [esp + 8] */
	{ DWORD v_ = 0x104u; m->esp -= 4; M32(m->esp) = v_; }	/* 4571e3: push 0x104 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4571e8: push ecx */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 4571e9: push -1 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4571eb: push edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4571ec: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4571ee: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4571f6u; native_call(m, M32(0x4a9164u));	/* 4571f0: call dword ptr [0x4a9164] */
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 4571f6: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4571fa: push 0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4571fc: push 1 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4571fe: push 0 */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 457200: mov edx, dword ptr [eax] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 457202: push eax */
	m->esp -= 4; M32(m->esp) = 0x457206u; native_call(m, M32((DWORD)(m->edx + 0x30u)));	/* 457203: call dword ptr [edx + 0x30] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 457206: test eax, eax */
	if (m->zf) goto L_457214;	/* 457208: je 0x457214 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45720a: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 45720c: pop edi */
	{ DWORD a_ = m->esp, b_ = 0x20cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45720d: add esp, 0x20c */
	m->esp += 4 + 0; return;	/* 457213: ret  */
L_457214:
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 457214: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 457218: push 0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45721a: push 1 */
	{ DWORD v_ = 0x4aafc0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45721c: push 0x4aafc0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 457221: mov ecx, dword ptr [eax] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 457223: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 457225: push eax */
	m->esp -= 4; M32(m->esp) = 0x457229u; native_call(m, M32((DWORD)(m->ecx + 0x3cu)));	/* 457226: call dword ptr [ecx + 0x3c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 457229: test eax, eax */
	if (m->zf) goto L_457237;	/* 45722b: je 0x457237 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45722d: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 45722f: pop edi */
	{ DWORD a_ = m->esp, b_ = 0x20cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 457230: add esp, 0x20c */
	m->esp += 4 + 0; return;	/* 457236: ret  */
L_457237:
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 457237: mov eax, dword ptr [esp + 4] */
	m->ecx = (DWORD)(m->esp + 0x8u);	/* 45723b: lea ecx, [esp + 8] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45723f: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 457241: push ecx */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 457242: mov edx, dword ptr [eax] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 457244: push eax */
	m->esp -= 4; M32(m->esp) = 0x457248u; native_call(m, M32((DWORD)(m->edx + 0x40u)));	/* 457245: call dword ptr [edx + 0x40] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 457248: test eax, eax */
	if (m->zf) goto L_457256;	/* 45724a: je 0x457256 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45724c: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 45724e: pop edi */
	{ DWORD a_ = m->esp, b_ = 0x20cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45724f: add esp, 0x20c */
	m->esp += 4 + 0; return;	/* 457255: ret  */
L_457256:
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 457256: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45725a: push esi */
	M32((DWORD)(0xa0e670u)) = m->eax;	/* 45725b: mov dword ptr [0xa0e670], eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 457260: push 1 */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 457262: mov edx, dword ptr [eax] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 457264: push eax */
	m->esp -= 4; M32(m->esp) = 0x457268u; native_call(m, M32((DWORD)(m->edx + 0x1cu)));	/* 457265: call dword ptr [edx + 0x1c] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 457268: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45726b: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 45726d: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 45726f: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 457271: sub edi, ecx */
	{ DWORD v_ = 0xa0e018u; m->esp -= 4; M32(m->esp) = v_; }	/* 457273: push 0xa0e018 */
	m->eax = m->ecx;	/* 457278: mov eax, ecx */
	m->esi = m->edi;	/* 45727a: mov esi, edi */
	m->edi = 0xa0e674u;	/* 45727c: mov edi, 0xa0e674 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 457281: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 457284: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 457286: mov ecx, eax */
	m->eax = M32((DWORD)(0xa0e670u));	/* 457288: mov eax, dword ptr [0xa0e670] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 45728d: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 457290: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 457291: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 457293: mov ecx, dword ptr [eax] */
	m->esp -= 4; M32(m->esp) = 0x457298u; native_call(m, M32((DWORD)(m->ecx + 0x24u)));	/* 457295: call dword ptr [ecx + 0x24] */
	m->esi = M32(m->esp); m->esp += 4;	/* 457298: pop esi */
	m->eax = 0x1u;	/* 457299: mov eax, 1 */
	m->edi = M32(m->esp); m->esp += 4;	/* 45729e: pop edi */
	{ DWORD a_ = m->esp, b_ = 0x20cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45729f: add esp, 0x20c */
	m->esp += 4 + 0; return;	/* 4572a5: ret  */
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
