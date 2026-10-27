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

static void lift_45dc00(X86 *m);
static void lift_45dd80(X86 *m);
static void lift_45ddc0(X86 *m);
static void lift_45de20(X86 *m);
static void lift_45e170(X86 *m);

/* hud_45e170 (0x45e170), lifted by tools/lift.py */
static void lift_45e170(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e170: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e171: push edi */
	m->edi = m->ecx;	/* 45e172: mov edi, ecx */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 45e174: xor esi, esi */
	m->eax = M32((DWORD)(m->edi + 0x202e8c8u));	/* 45e176: mov eax, dword ptr [edi + 0x202e8c8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45e17c: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_45e1b2;	/* 45e17e: jle 0x45e1b2 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e180: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45e181: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x18u));	/* 45e182: mov ebp, dword ptr [esp + 0x18] */
	m->ebx = (DWORD)(m->edi + 0x1cd94b0u);	/* 45e186: lea ebx, [edi + 0x1cd94b0] */
L_45e18c:
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x0u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45e18c: cmp dword ptr [ebx], 1 */
	if (!m->zf) goto L_45e19f;	/* 45e18f: jne 0x45e19f */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 45e191: mov eax, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45e195: push ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45e196: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e197: push esi */
	m->ecx = m->edi;	/* 45e198: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x45e19fu; native_call(m, 0x45d3e0u);	/* 45e19a: call 0x45d3e0 */
L_45e19f:
	m->eax = M32((DWORD)(m->edi + 0x202e8c8u));	/* 45e19f: mov eax, dword ptr [edi + 0x202e8c8] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 45e1a5: inc esi */
	{ DWORD a_ = m->ebx, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 45e1a6: add ebx, 0x8888 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45e1ac: cmp esi, eax */
	if (m->sf != m->of) goto L_45e18c;	/* 45e1ae: jl 0x45e18c */
	m->ebp = M32(m->esp); m->esp += 4;	/* 45e1b0: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 45e1b1: pop ebx */
L_45e1b2:
	m->edi = M32(m->esp); m->esp += 4;	/* 45e1b2: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45e1b3: pop esi */
	m->esp += 4 + 8; return;	/* 45e1b4: ret 8 */
}

/* FUN_0045dc00 (0x45dc00), lifted by tools/lift.py */
static void lift_45dc00(X86 *m)
{
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45dc00: push edi */
	m->edi = M32((DWORD)(m->esp + 0x8u));	/* 45dc01: mov edi, dword ptr [esp + 8] */
	{ DWORD a_ = m->edi, b_ = 0x64u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45dc05: cmp edi, 0x64 */
	if (m->sf != m->of) goto L_45dc11;	/* 45dc08: jl 0x45dc11 */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45dc0a: or eax, 0xffffffff */
	m->edi = M32(m->esp); m->esp += 4;	/* 45dc0d: pop edi */
	m->esp += 4 + 16; return;	/* 45dc0e: ret 0x10 */
L_45dc11:
	m->eax = M32((DWORD)(m->ecx + 0x202e8c8u));	/* 45dc11: mov eax, dword ptr [ecx + 0x202e8c8] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45dc17: cmp eax, edi */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45dc19: push esi */
	if (!m->zf && m->sf == m->of) goto L_45dc51;	/* 45dc1a: jg 0x45dc51 */
	m->edx = m->eax;	/* 45dc1c: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45dc1e: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45dc21: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45dc23: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45dc26: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45dc28: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45dc2b: add edx, eax */
	m->esi = (DWORD)(m->ecx + m->edx*8 + 0x1cd94b0u);	/* 45dc2d: lea esi, [ecx + edx*8 + 0x1cd94b0] */
	m->edx = m->edi;	/* 45dc34: mov edx, edi */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45dc36: sub edx, eax */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 45dc38: inc edx */
L_45dc39:
	M32((DWORD)(m->esi + 0x0u)) = 0x0u;	/* 45dc39: mov dword ptr [esi], 0 */
	{ DWORD a_ = m->esi, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 45dc3f: add esi, 0x8888 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 45dc45: dec edx */
	if (!m->zf) goto L_45dc39;	/* 45dc46: jne 0x45dc39 */
	m->eax = (DWORD)(m->edi + 0x1u);	/* 45dc48: lea eax, [edi + 1] */
	M32((DWORD)(m->ecx + 0x202e8c8u)) = m->eax;	/* 45dc4b: mov dword ptr [ecx + 0x202e8c8], eax */
L_45dc51:
	m->esi = M32((DWORD)(m->ecx + 0x202e8c8u));	/* 45dc51: mov esi, dword ptr [ecx + 0x202e8c8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45dc57: xor eax, eax */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45dc59: test esi, esi */
	if (m->sf != m->of) goto L_45dc7b;	/* 45dc5b: jl 0x45dc7b */
	m->edx = (DWORD)(m->ecx + 0x1cd94b0u);	/* 45dc5d: lea edx, [ecx + 0x1cd94b0] */
L_45dc63:
	{ DWORD a_ = M32((DWORD)(m->edx + 0x0u)), b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45dc63: cmp dword ptr [edx], 0 */
	if (m->zf) goto L_45dc75;	/* 45dc66: je 0x45dc75 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 45dc68: inc eax */
	{ DWORD a_ = m->edx, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45dc69: add edx, 0x8888 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45dc6f: cmp eax, esi */
	if (m->zf || m->sf != m->of) goto L_45dc63;	/* 45dc71: jle 0x45dc63 */
	goto L_45dc7b;	/* 45dc73: jmp 0x45dc7b */
L_45dc75:
	M32((DWORD)(m->ecx + 0x202e8ccu)) = m->eax;	/* 45dc75: mov dword ptr [ecx + 0x202e8cc], eax */
L_45dc7b:
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 45dc7b: mov edx, dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 45dc7f: mov eax, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45dc83: push edx */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 45dc84: mov edx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45dc88: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45dc89: push edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45dc8a: push edi */
	m->esp -= 4; M32(m->esp) = 0x45dc90u; native_call(m, 0x457330u);	/* 45dc8b: call 0x457330 */
	m->esi = M32(m->esp); m->esp += 4;	/* 45dc90: pop esi */
	m->eax = m->edi;	/* 45dc91: mov eax, edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 45dc93: pop edi */
	m->esp += 4 + 16; return;	/* 45dc94: ret 0x10 */
}

/* match_45dd80 (0x45dd80), lifted by tools/lift.py */
static void lift_45dd80(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 45dd80: mov eax, dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x8u));	/* 45dd84: mov edx, dword ptr [esp + 8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45dd88: push esi */
	m->esi = m->ecx;	/* 45dd89: mov esi, ecx */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 45dd8b: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45dd8f: push edi */
	m->edi = M32((DWORD)(m->esp + 0xcu));	/* 45dd90: mov edi, dword ptr [esp + 0xc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45dd94: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45dd95: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45dd96: push edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45dd97: push edi */
	m->ecx = m->esi;	/* 45dd98: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x45dd9fu; lift_45dc00(m);	/* 45dd9a: call 0x45dc00 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45dd9f: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45dda1: push edi */
	m->ecx = m->esi;	/* 45dda2: mov ecx, esi */
	M32((DWORD)(m->esi + 0x202e8d4u)) = m->edi;	/* 45dda4: mov dword ptr [esi + 0x202e8d4], edi */
	m->esp -= 4; M32(m->esp) = 0x45ddafu; native_call(m, 0x45e810u);	/* 45ddaa: call 0x45e810 */
	m->edi = M32(m->esp); m->esp += 4;	/* 45ddaf: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45ddb0: pop esi */
	m->esp += 4 + 16; return;	/* 45ddb1: ret 0x10 */
}

/* armc_45ddc0 (0x45ddc0), lifted by tools/lift.py */
static void lift_45ddc0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45ddc0: sub esp, 0x1c */
	m->edx = M32((DWORD)(0xa0e7a8u));	/* 45ddc3: mov edx, dword ptr [0xa0e7a8] */
	m->eax = M32((DWORD)(m->ecx + 0x202e8d4u));	/* 45ddc9: mov eax, dword ptr [ecx + 0x202e8d4] */
	M32((DWORD)(m->esp + 0x8u)) = m->edx;	/* 45ddcf: mov dword ptr [esp + 8], edx */
	m->edx = M32((DWORD)(0xa0e7acu));	/* 45ddd3: mov edx, dword ptr [0xa0e7ac] */
	M32((DWORD)(m->esp + 0xcu)) = m->edx;	/* 45ddd9: mov dword ptr [esp + 0xc], edx */
	m->edx = M32((DWORD)(0xa0e7b0u));	/* 45dddd: mov edx, dword ptr [0xa0e7b0] */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 45dde3: mov dword ptr [esp + 0x10], edx */
	m->edx = (DWORD)(m->esp + 0x0u);	/* 45dde7: lea edx, [esp] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45ddeb: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45ddec: push eax */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 45dded: push -1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45ddef: push eax */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 45ddf0: mov dword ptr [esp + 0x10], eax */
	M32((DWORD)(m->esp + 0x14u)) = 0x0u;	/* 45ddf4: mov dword ptr [esp + 0x14], 0 */
	M32((DWORD)(m->esp + 0x24u)) = 0x0u;	/* 45ddfc: mov dword ptr [esp + 0x24], 0 */
	M32((DWORD)(m->esp + 0x28u)) = 0x0u;	/* 45de04: mov dword ptr [esp + 0x28], 0 */
	m->esp -= 4; M32(m->esp) = 0x45de11u; lift_45dd80(m);	/* 45de0c: call 0x45dd80 */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45de11: add esp, 0x1c */
	m->esp += 4 + 0; return;	/* 45de14: ret  */
}

/* actor_applySpawnRecord (0x45de20), lifted by tools/lift.py */
static void lift_45de20(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45de20: sub esp, 0x1c */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45de23: push ebx */
	m->ebx = m->ecx;	/* 45de24: mov ebx, ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45de26: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45de27: push edi */
	m->eax = M32((DWORD)(m->ebx + 0x202e8d4u));	/* 45de28: mov eax, dword ptr [ebx + 0x202e8d4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45de2e: test eax, eax */
	if (m->sf == m->of) goto L_45de45;	/* 45de30: jge 0x45de45 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45de32: push eax */
	{ DWORD v_ = 0x4b4538u; m->esp -= 4; M32(m->esp) = v_; }	/* 45de33: push 0x4b4538 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 45de38: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x45de42u; native_call(m, 0x46c710u);	/* 45de3d: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45de42: add esp, 0xc */
L_45de45:
	m->esi = M32((DWORD)(m->esp + 0x30u));	/* 45de45: mov esi, dword ptr [esp + 0x30] */
	m->edi = M32((DWORD)(m->esp + 0x2cu));	/* 45de49: mov edi, dword ptr [esp + 0x2c] */
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 45de4d: mov eax, dword ptr [esi] */
	m->ecx = M32((DWORD)(m->esi + 0x18u));	/* 45de4f: mov ecx, dword ptr [esi + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x10u)));	/* 45de52: fld dword ptr [esi + 0x10] */
	m->edx = (DWORD)(m->esi + 0x4u);	/* 45de55: lea edx, [esi + 4] */
	M32((DWORD)(m->esp + 0xcu)) = m->eax;	/* 45de58: mov dword ptr [esp + 0xc], eax */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 45de5c: mov dword ptr [esp + 0x10], ecx */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 45de60: mov eax, dword ptr [edx] */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 45de62: mov dword ptr [esp + 0x14], eax */
	m->eax = (DWORD)(m->esp + 0xcu);	/* 45de66: lea eax, [esp + 0xc] */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 45de6a: mov ecx, dword ptr [edx + 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45de6d: push eax */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 45de6e: mov dword ptr [esp + 0x1c], ecx */
	m->ecx = M32((DWORD)(m->ebx + 0x202e8d4u));	/* 45de72: mov ecx, dword ptr [ebx + 0x202e8d4] */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 45de78: mov edx, dword ptr [edx + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45de7b: push ecx */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 45de7c: fstp dword ptr [esp + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x14u)));	/* 45de80: fld dword ptr [esi + 0x14] */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 45de83: push -1 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45de85: push edi */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 45de86: fstp dword ptr [esp + 0x34] */
	m->ecx = m->ebx;	/* 45de8a: mov ecx, ebx */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 45de8c: mov dword ptr [esp + 0x2c], edx */
	m->esp -= 4; M32(m->esp) = 0x45de95u; lift_45dc00(m);	/* 45de90: call 0x45dc00 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45de95: test edi, edi */
	if (m->sf != m->of) goto L_45df7e;	/* 45de97: jl 0x45df7e */
	m->edx = m->edi;	/* 45de9d: mov edx, edi */
	m->eax = M32((DWORD)(m->esi + 0x1cu));	/* 45de9f: mov eax, dword ptr [esi + 0x1c] */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45dea2: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45dea5: add edx, edi */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45dea7: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45deaa: add edx, edi */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45deac: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45deaf: add edx, edi */
	m->edi = (DWORD)(m->ebx + m->edx*8 + 0x1cd93a8u);	/* 45deb1: lea edi, [ebx + edx*8 + 0x1cd93a8] */
	M32((DWORD)(m->edi + 0x64u)) = m->eax;	/* 45deb8: mov dword ptr [edi + 0x64], eax */
	m->ecx = M32((DWORD)(m->esi + 0x20u));	/* 45debb: mov ecx, dword ptr [esi + 0x20] */
	M32((DWORD)(m->edi + 0x1cu)) = m->ecx;	/* 45debe: mov dword ptr [edi + 0x1c], ecx */
	m->edx = M32((DWORD)(m->esi + 0x24u));	/* 45dec1: mov edx, dword ptr [esi + 0x24] */
	M32((DWORD)(m->edi + 0x20u)) = m->edx;	/* 45dec4: mov dword ptr [edi + 0x20], edx */
	m->eax = M32((DWORD)(m->esi + 0x20u));	/* 45dec7: mov eax, dword ptr [esi + 0x20] */
	M32((DWORD)(m->edi + 0x128u)) = m->eax;	/* 45deca: mov dword ptr [edi + 0x128], eax */
	m->ecx = M32((DWORD)(m->esi + 0x24u));	/* 45ded0: mov ecx, dword ptr [esi + 0x24] */
	M32((DWORD)(m->edi + 0x12cu)) = m->ecx;	/* 45ded3: mov dword ptr [edi + 0x12c], ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x28u)));	/* 45ded9: fld dword ptr [esi + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9750u));	/* 45dedc: fmul dword ptr [0x4a9750] */
	MF((DWORD)(m->edi + 0x68u)) = (float)ST(0);	/* 45dee2: fst dword ptr [edi + 0x68] */
	MF((DWORD)(m->edi + 0x50u)) = (float)ST(0); FPOP();	/* 45dee5: fstp dword ptr [edi + 0x50] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x2cu)));	/* 45dee8: fld dword ptr [esi + 0x2c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 45deeb: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->edi + 0x6cu)) = (float)ST(0); FPOP();	/* 45def1: fstp dword ptr [edi + 0x6c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x30u)));	/* 45def4: fld dword ptr [esi + 0x30] */
	{ long double t = ST(0); FPUSH(t); }	/* 45def7: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 45def9: fmul st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9708u));	/* 45defb: fmul dword ptr [0x4a9708] */
	MF((DWORD)(m->edi + 0x0u)) = (float)ST(0); FPOP();	/* 45df01: fstp dword ptr [edi] */
	m->edx = M32((DWORD)(m->esi + 0x34u));	/* 45df03: mov edx, dword ptr [esi + 0x34] */
	ST(0) = ST(0); FPOP();	/* 45df06: fstp st(0) */
	M32((DWORD)(m->edi + 0x70u)) = m->edx;	/* 45df08: mov dword ptr [edi + 0x70], edx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x38u)));	/* 45df0b: fld dword ptr [esi + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 45df0e: fmul dword ptr [0x4a9418] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 45df14: call 0x49ec14 */
	M32((DWORD)(m->edi + 0x74u)) = m->eax;	/* 45df19: mov dword ptr [edi + 0x74], eax */
	m->eax = M32((DWORD)(m->esi + 0x3cu));	/* 45df1c: mov eax, dword ptr [esi + 0x3c] */
	M32((DWORD)(m->edi + 0x78u)) = m->eax;	/* 45df1f: mov dword ptr [edi + 0x78], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x40u)));	/* 45df22: fld dword ptr [esi + 0x40] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 45df25: fmul dword ptr [0x4a93f4] */
	MF((DWORD)(m->edi + 0x7cu)) = (float)ST(0); FPOP();	/* 45df2b: fstp dword ptr [edi + 0x7c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x44u)));	/* 45df2e: fld dword ptr [esi + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 45df31: fmul dword ptr [0x4a93f4] */
	MF((DWORD)(m->edi + 0x80u)) = (float)ST(0); FPOP();	/* 45df37: fstp dword ptr [edi + 0x80] */
	m->ecx = M32((DWORD)(m->esi + 0x48u));	/* 45df3d: mov ecx, dword ptr [esi + 0x48] */
	M32((DWORD)(m->edi + 0x84u)) = m->ecx;	/* 45df40: mov dword ptr [edi + 0x84], ecx */
	m->edx = M32((DWORD)(m->esi + 0x4cu));	/* 45df46: mov edx, dword ptr [esi + 0x4c] */
	M32((DWORD)(m->edi + 0x88u)) = m->edx;	/* 45df49: mov dword ptr [edi + 0x88], edx */
	m->eax = M32((DWORD)(m->esi + 0x50u));	/* 45df4f: mov eax, dword ptr [esi + 0x50] */
	M32((DWORD)(m->edi + 0x8cu)) = m->eax;	/* 45df52: mov dword ptr [edi + 0x8c], eax */
	m->ecx = M32((DWORD)(m->esi + 0x54u));	/* 45df58: mov ecx, dword ptr [esi + 0x54] */
	M32((DWORD)(m->edi + 0x90u)) = m->ecx;	/* 45df5b: mov dword ptr [edi + 0x90], ecx */
	m->edx = M32((DWORD)(m->esi + 0x58u));	/* 45df61: mov edx, dword ptr [esi + 0x58] */
	M32((DWORD)(m->edi + 0x94u)) = m->edx;	/* 45df64: mov dword ptr [edi + 0x94], edx */
	M32((DWORD)(m->edi + 0x87f8u)) = 0xffffffffu;	/* 45df6a: mov dword ptr [edi + 0x87f8], 0xffffffff */
	M32((DWORD)(m->edi + 0x87fcu)) = 0xffffffffu;	/* 45df74: mov dword ptr [edi + 0x87fc], 0xffffffff */
L_45df7e:
	m->edi = M32(m->esp); m->esp += 4;	/* 45df7e: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45df7f: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 45df80: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45df81: add esp, 0x1c */
	m->esp += 4 + 8; return;	/* 45df84: ret 8 */
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
