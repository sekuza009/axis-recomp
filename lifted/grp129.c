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

static void lift_460000(X86 *m);
static void lift_462150(X86 *m);

/* msg_newKing (0x462150), lifted by tools/lift.py */
static void lift_462150(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 462150: sub esp, 0x14 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 462153: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 462154: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 462155: push esi */
	m->esi = m->ecx;	/* 462156: mov esi, ecx */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 462158: xor ebp, ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46215a: push edi */
	M32((DWORD)(m->esi + 0x234297eu)) = m->ebp;	/* 46215b: mov dword ptr [esi + 0x234297e], ebp */
	M32((DWORD)(m->esi + 0x2342982u)) = m->ebp;	/* 462161: mov dword ptr [esi + 0x2342982], ebp */
	M32((DWORD)(m->esi + 0x2342986u)) = m->ebp;	/* 462167: mov dword ptr [esi + 0x2342986], ebp */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 46216d: xor ebx, ebx */
	m->edi = (DWORD)(m->esi + 0x1eccb88u);	/* 46216f: lea edi, [esi + 0x1eccb88] */
L_462175:
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 462175: mov eax, dword ptr [edi] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 462177: cmp eax, ebp */
	if (m->sf != m->of) goto L_4621a6;	/* 462179: jl 0x4621a6 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46217b: push eax */
	m->ecx = m->esi;	/* 46217c: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x462183u; native_call(m, 0x463740u);	/* 46217e: call 0x463740 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 462183: test eax, eax */
	if (!m->zf) goto L_46218f;	/* 462185: jne 0x46218f */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x234297eu)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(m->esi + 0x234297eu)) = r_; }	/* 462187: inc dword ptr [esi + 0x234297e] */
	goto L_4621be;	/* 46218d: jmp 0x4621be */
L_46218f:
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 46218f: mov eax, dword ptr [edi] */
	m->ecx = m->esi;	/* 462191: mov ecx, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 462193: push eax */
	m->esp -= 4; M32(m->esp) = 0x462199u; native_call(m, 0x463740u);	/* 462194: call 0x463740 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 462199: cmp eax, 1 */
	if (!m->zf) goto L_4621be;	/* 46219c: jne 0x4621be */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2342982u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(m->esi + 0x2342982u)) = r_; }	/* 46219e: inc dword ptr [esi + 0x2342982] */
	goto L_4621be;	/* 4621a4: jmp 0x4621be */
L_4621a6:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4621a6: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4621acu; native_call(m, 0x4a8700u);	/* 4621a7: call 0x4a8700 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4621ac: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4621af: cmp eax, 1 */
	if (!m->zf) goto L_4621be;	/* 4621b2: jne 0x4621be */
	{ DWORD a_ = M32((DWORD)(m->edi + 0x0u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4621b4: cmp dword ptr [edi], ebp */
	if (m->sf == m->of) goto L_4621be;	/* 4621b6: jge 0x4621be */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2342986u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(m->esi + 0x2342986u)) = r_; }	/* 4621b8: inc dword ptr [esi + 0x2342986] */
L_4621be:
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 4621be: inc ebx */
	{ DWORD a_ = m->edi, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4621bf: add edi, 0x8888 */
	{ DWORD a_ = m->ebx, b_ = 0x10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4621c5: cmp ebx, 0x10 */
	if (m->sf != m->of) goto L_462175;	/* 4621c8: jl 0x462175 */
	m->eax = (DWORD)(m->esi + 0x23428f6u);	/* 4621ca: lea eax, [esi + 0x23428f6] */
	m->ecx = 0x10u;	/* 4621d0: mov ecx, 0x10 */
L_4621d5:
	M32((DWORD)(m->eax + 0x40u)) = 0xffffffffu;	/* 4621d5: mov dword ptr [eax + 0x40], 0xffffffff */
	M32((DWORD)(m->eax + 0x0u)) = 0xffffffffu;	/* 4621dc: mov dword ptr [eax], 0xffffffff */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4621e2: add eax, 4 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4621e5: dec ecx */
	if (!m->zf) goto L_4621d5;	/* 4621e6: jne 0x4621d5 */
	m->eax = (DWORD)(m->esi + 0x23428f6u);	/* 4621e8: lea eax, [esi + 0x23428f6] */
	M32((DWORD)(m->esi + 0x2342976u)) = m->ebp;	/* 4621ee: mov dword ptr [esi + 0x2342976], ebp */
	M32((DWORD)(m->esp + 0x18u)) = m->ebp;	/* 4621f4: mov dword ptr [esp + 0x18], ebp */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 4621f8: mov dword ptr [esp + 0x1c], eax */
L_4621fc:
	m->edx = (DWORD)(m->esi + 0x2342936u);	/* 4621fc: lea edx, [esi + 0x2342936] */
	{ DWORD a_ = m->edi, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 462202: or edi, 0xffffffff */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 462205: mov dword ptr [esp + 0x10], edx */
	m->edx = 0xfe1334acu;	/* 462209: mov edx, 0xfe1334ac */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46220e: xor ecx, ecx */
	{ DWORD a_ = m->edx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 462210: sub edx, esi */
	M32((DWORD)(m->esp + 0x14u)) = 0x80000000u;	/* 462212: mov dword ptr [esp + 0x14], 0x80000000 */
	m->ebx = 0xffff7778u;	/* 46221a: mov ebx, 0xffff7778 */
	m->eax = (DWORD)(m->esi + 0x1eccb54u);	/* 46221f: lea eax, [esi + 0x1eccb54] */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 462225: mov dword ptr [esp + 0x20], edx */
L_462229:
	m->edx = M32((DWORD)(m->eax + 0x34u));	/* 462229: mov edx, dword ptr [eax + 0x34] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46222c: test edx, edx */
	if (m->sf != m->of) goto L_462269;	/* 46222e: jl 0x462269 */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 462230: mov edx, dword ptr [esp + 0x10] */
	{ DWORD a_ = M32((DWORD)(m->edx + 0x0u)), b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 462234: cmp dword ptr [edx], 0 */
	if (m->sf == m->of) goto L_462269;	/* 462237: jge 0x462269 */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 462239: mov edx, dword ptr [eax] */
	m->ebp = M32((DWORD)(m->esp + 0x14u));	/* 46223b: mov ebp, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->edx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46223f: cmp edx, ebp */
	if (!m->zf && m->sf == m->of) goto L_46225c;	/* 462241: jg 0x46225c */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 462243: test edi, edi */
	if (m->sf != m->of) goto L_462269;	/* 462245: jl 0x462269 */
	{ DWORD a_ = m->edx, b_ = M32((DWORD)(m->ebx + m->esi*1 + 0x1eccb54u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 462247: cmp edx, dword ptr [ebx + esi + 0x1eccb54] */
	if (!m->zf) goto L_462269;	/* 46224e: jne 0x462269 */
	m->ebp = M32((DWORD)(m->eax + 0x4u));	/* 462250: mov ebp, dword ptr [eax + 4] */
	{ DWORD a_ = m->ebp, b_ = M32((DWORD)(m->ebx + m->esi*1 + 0x1eccb58u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 462253: cmp ebp, dword ptr [ebx + esi + 0x1eccb58] */
	if (m->sf == m->of) goto L_462269;	/* 46225a: jge 0x462269 */
L_46225c:
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 46225c: mov dword ptr [esp + 0x14], edx */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 462260: mov edx, dword ptr [esp + 0x20] */
	m->edi = m->ecx;	/* 462264: mov edi, ecx */
	m->ebx = (DWORD)(m->edx + m->eax*1 + 0x0u);	/* 462266: lea ebx, [edx + eax] */
L_462269:
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 462269: mov edx, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 46226d: inc ecx */
	{ DWORD a_ = m->edx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46226e: add edx, 4 */
	{ DWORD a_ = m->eax, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 462271: add eax, 0x8888 */
	{ DWORD a_ = m->ecx, b_ = 0x10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 462276: cmp ecx, 0x10 */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 462279: mov dword ptr [esp + 0x10], edx */
	if (m->sf != m->of) goto L_462229;	/* 46227d: jl 0x462229 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 46227f: xor ebp, ebp */
	{ DWORD a_ = m->edi, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 462281: cmp edi, ebp */
	if (m->sf != m->of) goto L_4622b8;	/* 462283: jl 0x4622b8 */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 462285: mov eax, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 462289: mov ecx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esi + m->edi*4 + 0x2342936u)) = m->eax;	/* 46228d: mov dword ptr [esi + edi*4 + 0x2342936], eax */
	M32((DWORD)(m->ecx + 0x0u)) = m->edi;	/* 462294: mov dword ptr [ecx], edi */
	m->ebx = M32((DWORD)(m->esi + 0x2342976u));	/* 462296: mov ebx, dword ptr [esi + 0x2342976] */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 46229c: inc ebx */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 46229d: inc eax */
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46229e: add ecx, 4 */
	{ DWORD a_ = m->eax, b_ = 0x10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4622a1: cmp eax, 0x10 */
	M32((DWORD)(m->esi + 0x2342976u)) = m->ebx;	/* 4622a4: mov dword ptr [esi + 0x2342976], ebx */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 4622aa: mov dword ptr [esp + 0x18], eax */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 4622ae: mov dword ptr [esp + 0x1c], ecx */
	if (m->sf != m->of) goto L_4621fc;	/* 4622b2: jl 0x4621fc */
L_4622b8:
	m->eax = M32((DWORD)(m->esi + 0x2342976u));	/* 4622b8: mov eax, dword ptr [esi + 0x2342976] */
	M32((DWORD)(m->esp + 0x1cu)) = m->ebp;	/* 4622be: mov dword ptr [esp + 0x1c], ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4622c2: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_462340;	/* 4622c4: jle 0x462340 */
	m->ecx = (DWORD)(m->esi + 0x23428f6u);	/* 4622c6: lea ecx, [esi + 0x23428f6] */
L_4622cc:
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4622cc: test ebp, ebp */
	if (m->zf || m->sf != m->of) goto L_462324;	/* 4622ce: jle 0x462324 */
	m->eax = M32((DWORD)(m->ecx + 0xfffffffcu));	/* 4622d0: mov eax, dword ptr [ecx - 4] */
	m->edx = m->eax;	/* 4622d3: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4622d5: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4622d8: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4622da: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4622dd: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4622df: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4622e2: add edx, eax */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 4622e4: mov eax, dword ptr [ecx] */
	m->edi = (DWORD)(m->esi + m->edx*8 + 0x0u);	/* 4622e6: lea edi, [esi + edx*8] */
	m->edx = m->eax;	/* 4622e9: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4622eb: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4622ee: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4622f0: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4622f3: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4622f5: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4622f8: add edx, eax */
	m->eax = M32((DWORD)(m->esi + m->edx*8 + 0x1eccb54u));	/* 4622fa: mov eax, dword ptr [esi + edx*8 + 0x1eccb54] */
	m->ebx = (DWORD)(m->esi + m->edx*8 + 0x0u);	/* 462301: lea ebx, [esi + edx*8] */
	m->edx = M32((DWORD)(m->edi + 0x1eccb54u));	/* 462304: mov edx, dword ptr [edi + 0x1eccb54] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46230a: cmp eax, edx */
	if (m->sf != m->of) goto L_462320;	/* 46230c: jl 0x462320 */
	if (!m->zf) goto L_462324;	/* 46230e: jne 0x462324 */
	m->eax = M32((DWORD)(m->ebx + 0x1eccb58u));	/* 462310: mov eax, dword ptr [ebx + 0x1eccb58] */
	m->edx = M32((DWORD)(m->edi + 0x1eccb58u));	/* 462316: mov edx, dword ptr [edi + 0x1eccb58] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46231c: cmp eax, edx */
	if (m->zf || m->sf != m->of) goto L_462324;	/* 46231e: jle 0x462324 */
L_462320:
	M32((DWORD)(m->esp + 0x1cu)) = m->ebp;	/* 462320: mov dword ptr [esp + 0x1c], ebp */
L_462324:
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 462324: mov edx, dword ptr [esp + 0x1c] */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 462328: mov eax, dword ptr [ecx] */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 46232a: inc edx */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 46232b: inc ebp */
	M32((DWORD)(m->esi + m->eax*4 + 0x2342936u)) = m->edx;	/* 46232c: mov dword ptr [esi + eax*4 + 0x2342936], edx */
	m->eax = M32((DWORD)(m->esi + 0x2342976u));	/* 462333: mov eax, dword ptr [esi + 0x2342976] */
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 462339: add ecx, 4 */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46233c: cmp ebp, eax */
	if (m->sf != m->of) goto L_4622cc;	/* 46233e: jl 0x4622cc */
L_462340:
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 462340: mov eax, dword ptr [esi + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 462346: test eax, eax */
	if (m->sf != m->of) goto L_462357;	/* 462348: jl 0x462357 */
	m->ecx = M32((DWORD)(m->esi + m->eax*4 + 0x2342936u));	/* 46234a: mov ecx, dword ptr [esi + eax*4 + 0x2342936] */
	M32((DWORD)(m->esi + 0x234297au)) = m->ecx;	/* 462351: mov dword ptr [esi + 0x234297a], ecx */
L_462357:
	m->ecx = M32((DWORD)(m->esi + 0x22e719cu));	/* 462357: mov ecx, dword ptr [esi + 0x22e719c] */
	m->ebp = 0x1u;	/* 46235d: mov ebp, 1 */
	{ DWORD a_ = m->ecx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 462362: cmp ecx, ebp */
	if (!m->zf) goto L_462427;	/* 462364: jne 0x462427 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 46236a: xor edi, edi */
	m->ebx = (DWORD)(m->esi + 0x1eccf48u);	/* 46236c: lea ebx, [esi + 0x1eccf48] */
L_462372:
	m->edx = M32((DWORD)(m->ebx + 0xfffffc40u));	/* 462372: mov edx, dword ptr [ebx - 0x3c0] */
	m->ecx = (DWORD)(m->ebx + 0xfffffbc0u);	/* 462378: lea ecx, [ebx - 0x440] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46237e: test edx, edx */
	if (m->sf != m->of) goto L_462417;	/* 462380: jl 0x462417 */
	{ DWORD a_ = m->edi, b_ = M32((DWORD)(m->esi + 0x23428f6u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 462386: cmp edi, dword ptr [esi + 0x23428f6] */
	if (!m->zf) goto L_4623f4;	/* 46238c: jne 0x4623f4 */
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x0u)), b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46238e: cmp dword ptr [ebx], 0 */
	if (!m->zf) goto L_4623c8;	/* 462391: jne 0x4623c8 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 462393: cmp edi, eax */
	if (!m->zf) goto L_4623b0;	/* 462395: jne 0x4623b0 */
	{ DWORD v_ = 0x4c4644u; m->esp -= 4; M32(m->esp) = v_; }	/* 462397: push 0x4c4644 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46239c: push esi */
	m->esp -= 4; M32(m->esp) = 0x4623a2u; native_call(m, 0x463450u);	/* 46239d: call 0x463450 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 4623a2: push 0x64 */
	{ DWORD v_ = 0x6u; m->esp -= 4; M32(m->esp) = v_; }	/* 4623a4: push 6 */
	m->esp -= 4; M32(m->esp) = 0x4623abu; native_call(m, 0x456e50u);	/* 4623a6: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4623ab: add esp, 0x10 */
	goto L_4623c8;	/* 4623ae: jmp 0x4623c8 */
L_4623b0:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4623b0: push ecx */
	{ DWORD v_ = 0x4c4630u; m->esp -= 4; M32(m->esp) = v_; }	/* 4623b1: push 0x4c4630 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4623b6: push esi */
	m->esp -= 4; M32(m->esp) = 0x4623bcu; native_call(m, 0x463450u);	/* 4623b7: call 0x463450 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 4623bc: push 0x64 */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4623be: push 7 */
	m->esp -= 4; M32(m->esp) = 0x4623c5u; native_call(m, 0x456e50u);	/* 4623c0: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4623c5: add esp, 0x14 */
L_4623c8:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4623c8: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4623ca: push edi */
	m->ecx = (DWORD)(m->esi + 0x1f36c8u);	/* 4623cb: lea ecx, [esi + 0x1f36c8] */
	M32((DWORD)(m->ebx + 0x0u)) = m->ebp;	/* 4623d1: mov dword ptr [ebx], ebp */
	m->esp -= 4; M32(m->esp) = 0x4623d8u; native_call(m, 0x473a80u);	/* 4623d3: call 0x473a80 */
	M32((DWORD)(m->esi + 0x22f0514u)) = m->edi;	/* 4623d8: mov dword ptr [esi + 0x22f0514], edi */
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 4623de: mov eax, dword ptr [esi + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4623e4: cmp eax, edi */
	if (!m->zf) goto L_462417;	/* 4623e6: jne 0x462417 */
	M32((DWORD)(m->esi + 0x234243eu)) = 0x0u;	/* 4623e8: mov dword ptr [esi + 0x234243e], 0 */
	goto L_462417;	/* 4623f2: jmp 0x462417 */
L_4623f4:
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4623f4: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4623f5: push edi */
	m->ecx = (DWORD)(m->esi + 0x1f36c8u);	/* 4623f6: lea ecx, [esi + 0x1f36c8] */
	M32((DWORD)(m->ebx + 0x0u)) = 0x0u;	/* 4623fc: mov dword ptr [ebx], 0 */
	m->esp -= 4; M32(m->esp) = 0x462407u; native_call(m, 0x473a80u);	/* 462402: call 0x473a80 */
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 462407: mov eax, dword ptr [esi + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46240d: cmp eax, edi */
	if (!m->zf) goto L_462417;	/* 46240f: jne 0x462417 */
	M32((DWORD)(m->esi + 0x234243eu)) = m->ebp;	/* 462411: mov dword ptr [esi + 0x234243e], ebp */
L_462417:
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 462417: inc edi */
	{ DWORD a_ = m->ebx, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 462418: add ebx, 0x8888 */
	{ DWORD a_ = m->edi, b_ = 0x10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46241e: cmp edi, 0x10 */
	if (m->sf != m->of) goto L_462372;	/* 462421: jl 0x462372 */
L_462427:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x22e71a0u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 462427: cmp dword ptr [esi + 0x22e71a0], ebp */
	if (!m->zf) goto L_462553;	/* 46242d: jne 0x462553 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 462433: xor edi, edi */
	m->edx = (DWORD)(m->esi + 0x22f0518u);	/* 462435: lea edx, [esi + 0x22f0518] */
	M32((DWORD)(m->esp + 0x14u)) = m->edi;	/* 46243b: mov dword ptr [esp + 0x14], edi */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 46243f: mov dword ptr [esp + 0x10], edx */
L_462443:
	{ DWORD a_ = m->ebp, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 462443: or ebp, 0xffffffff */
	M32((DWORD)(m->esp + 0x1cu)) = 0x800000u;	/* 462446: mov dword ptr [esp + 0x1c], 0x800000 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46244e: xor ecx, ecx */
	m->edx = (DWORD)(m->esi + 0x1eccb6cu);	/* 462450: lea edx, [esi + 0x1eccb6c] */
L_462456:
	{ DWORD a_ = M32((DWORD)(m->edx + 0x1cu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 462456: cmp dword ptr [edx + 0x1c], edi */
	if (!m->zf) goto L_462475;	/* 462459: jne 0x462475 */
	FPUSH((long double)(int)M32((DWORD)(m->edx + 0x0u)));	/* 46245b: fild dword ptr [edx] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edx + 0x4u));	/* 46245d: fadd dword ptr [edx + 4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x1cu));	/* 462460: fcom dword ptr [esp + 0x1c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 462464: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 462466: test ah, 0x41 */
	if (!m->zf) goto L_462473;	/* 462469: jne 0x462473 */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 46246b: fstp dword ptr [esp + 0x1c] */
	m->ebp = m->ecx;	/* 46246f: mov ebp, ecx */
	goto L_462475;	/* 462471: jmp 0x462475 */
L_462473:
	ST(0) = ST(0); FPOP();	/* 462473: fstp st(0) */
L_462475:
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 462475: inc ecx */
	{ DWORD a_ = m->edx, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 462476: add edx, 0x8888 */
	{ DWORD a_ = m->ecx, b_ = 0x10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46247c: cmp ecx, 0x10 */
	if (m->sf != m->of) goto L_462456;	/* 46247f: jl 0x462456 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 462481: test ebp, ebp */
	if (m->sf != m->of) goto L_46250f;	/* 462483: jl 0x46250f */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 462489: xor ebx, ebx */
	m->edi = (DWORD)(m->esi + 0x1eccf4cu);	/* 46248b: lea edi, [esi + 0x1eccf4c] */
L_462491:
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 462491: mov ecx, dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->edi + 0xfffffc3cu));	/* 462495: mov edx, dword ptr [edi - 0x3c4] */
	m->eax = (DWORD)(m->edi + 0xfffffbbcu);	/* 46249b: lea eax, [edi - 0x444] */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4624a1: cmp edx, ecx */
	if (!m->zf) goto L_4624f7;	/* 4624a3: jne 0x4624f7 */
	{ DWORD a_ = m->ebx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4624a5: cmp ebx, ebp */
	if (!m->zf) goto L_4624f1;	/* 4624a7: jne 0x4624f1 */
	{ DWORD a_ = M32((DWORD)(m->edi + 0x0u)), b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4624a9: cmp dword ptr [edi], 0 */
	if (!m->zf) goto L_4624f7;	/* 4624ac: jne 0x4624f7 */
	M32((DWORD)(m->edi + 0x0u)) = 0x1u;	/* 4624ae: mov dword ptr [edi], 1 */
	m->ecx = M32((DWORD)(m->esi + 0x234240du));	/* 4624b4: mov ecx, dword ptr [esi + 0x234240d] */
	{ DWORD a_ = m->ebx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4624ba: cmp ebx, ecx */
	if (!m->zf) goto L_4624d7;	/* 4624bc: jne 0x4624d7 */
	{ DWORD v_ = 0x4c4614u; m->esp -= 4; M32(m->esp) = v_; }	/* 4624be: push 0x4c4614 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4624c3: push esi */
	m->esp -= 4; M32(m->esp) = 0x4624c9u; native_call(m, 0x463450u);	/* 4624c4: call 0x463450 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 4624c9: push 0x64 */
	{ DWORD v_ = 0x6u; m->esp -= 4; M32(m->esp) = v_; }	/* 4624cb: push 6 */
	m->esp -= 4; M32(m->esp) = 0x4624d2u; native_call(m, 0x456e50u);	/* 4624cd: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4624d2: add esp, 0x10 */
	goto L_4624f7;	/* 4624d5: jmp 0x4624f7 */
L_4624d7:
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4624d7: push eax */
	{ DWORD v_ = 0x4c45f8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4624d8: push 0x4c45f8 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4624dd: push esi */
	m->esp -= 4; M32(m->esp) = 0x4624e3u; native_call(m, 0x463450u);	/* 4624de: call 0x463450 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 4624e3: push 0x64 */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4624e5: push 7 */
	m->esp -= 4; M32(m->esp) = 0x4624ecu; native_call(m, 0x456e50u);	/* 4624e7: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4624ec: add esp, 0x14 */
	goto L_4624f7;	/* 4624ef: jmp 0x4624f7 */
L_4624f1:
	M32((DWORD)(m->edi + 0x0u)) = 0x0u;	/* 4624f1: mov dword ptr [edi], 0 */
L_4624f7:
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 4624f7: inc ebx */
	{ DWORD a_ = m->edi, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4624f8: add edi, 0x8888 */
	{ DWORD a_ = m->ebx, b_ = 0x10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4624fe: cmp ebx, 0x10 */
	if (m->sf != m->of) goto L_462491;	/* 462501: jl 0x462491 */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 462503: mov edx, dword ptr [esp + 0x10] */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 462507: mov edi, dword ptr [esp + 0x14] */
	M32((DWORD)(m->edx + 0x0u)) = m->ebp;	/* 46250b: mov dword ptr [edx], ebp */
	goto L_46253a;	/* 46250d: jmp 0x46253a */
L_46250f:
	m->eax = (DWORD)(m->esi + 0x1eccf4cu);	/* 46250f: lea eax, [esi + 0x1eccf4c] */
	m->ecx = 0x10u;	/* 462515: mov ecx, 0x10 */
L_46251a:
	{ DWORD a_ = M32((DWORD)(m->eax + 0xfffffc3cu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46251a: cmp dword ptr [eax - 0x3c4], edi */
	if (!m->zf) goto L_462528;	/* 462520: jne 0x462528 */
	M32((DWORD)(m->eax + 0x0u)) = 0x0u;	/* 462522: mov dword ptr [eax], 0 */
L_462528:
	{ DWORD a_ = m->eax, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 462528: add eax, 0x8888 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 46252d: dec ecx */
	if (!m->zf) goto L_46251a;	/* 46252e: jne 0x46251a */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 462530: mov eax, dword ptr [esp + 0x10] */
	M32((DWORD)(m->eax + 0x0u)) = 0xffffffffu;	/* 462534: mov dword ptr [eax], 0xffffffff */
L_46253a:
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 46253a: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 46253e: inc edi */
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46253f: add ecx, 4 */
	{ DWORD a_ = m->edi, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 462542: cmp edi, 2 */
	M32((DWORD)(m->esp + 0x14u)) = m->edi;	/* 462545: mov dword ptr [esp + 0x14], edi */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 462549: mov dword ptr [esp + 0x10], ecx */
	if (m->sf != m->of) goto L_462443;	/* 46254d: jl 0x462443 */
L_462553:
	m->edi = M32(m->esp); m->esp += 4;	/* 462553: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 462554: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 462555: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 462556: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 462557: add esp, 0x14 */
	m->esp += 4 + 0; return;	/* 46255a: ret  */
}

/* bullet_playImpactSound (0x460000), lifted by tools/lift.py */
static void lift_460000(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 460000: push ecx */
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 460001: mov eax, dword ptr [esp + 0xc] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 460005: push esi */
	m->edx = m->eax;	/* 460006: mov edx, eax */
	M32((DWORD)(m->esp + 0x4u)) = m->ecx;	/* 460008: mov dword ptr [esp + 4], ecx */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 46000c: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46000f: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 460011: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 460014: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 460016: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 460019: add edx, eax */
	m->eax = 0x1u;	/* 46001b: mov eax, 1 */
	m->esi = (DWORD)(m->ecx + m->edx*8 + 0x0u);	/* 460020: lea esi, [ecx + edx*8] */
	m->edx = M32((DWORD)(m->ecx + m->edx*8 + 0x1cd94f4u));	/* 460023: mov edx, dword ptr [ecx + edx*8 + 0x1cd94f4] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46002a: cmp edx, eax */
	if (!m->zf) goto L_460241;	/* 46002c: jne 0x460241 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x1ce1bb4u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 460032: cmp dword ptr [esi + 0x1ce1bb4], eax */
	if (m->zf) goto L_460241;	/* 460038: je 0x460241 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46003e: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46003f: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x14u));	/* 460040: mov ebp, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 460044: push edi */
	m->edx = m->ebp;	/* 460045: mov edx, ebp */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 460047: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46004a: add edx, ebp */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 46004c: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46004f: add edx, ebp */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 460051: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 460054: add edx, ebp */
	m->edi = (DWORD)(m->ecx + m->edx*8 + 0x0u);	/* 460056: lea edi, [ecx + edx*8] */
	m->ecx = M32((DWORD)(m->ecx + m->edx*8 + 0x1cd94b0u));	/* 460059: mov ecx, dword ptr [ecx + edx*8 + 0x1cd94b0] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 460060: cmp ecx, eax */
	if (m->zf) goto L_460069;	/* 460062: je 0x460069 */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 460064: or eax, 0xffffffff */
	goto L_46006f;	/* 460067: jmp 0x46006f */
L_460069:
	m->eax = M32((DWORD)(m->edi + 0x1cd94bcu));	/* 460069: mov eax, dword ptr [edi + 0x1cd94bc] */
L_46006f:
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 46006f: mov ecx, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->ecx, b_ = 0x9u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 460073: cmp ecx, 9 */
	if (!m->cf && !m->zf) goto L_460106;	/* 460076: ja 0x460106 */
	switch (m->ecx) { case 0: goto L_460083; case 1: goto L_460083; case 2: goto L_46009d; case 3: goto L_46009d; case 4: goto L_46009d; case 5: goto L_4600b7; case 6: goto L_4600b7; case 7: goto L_46009d; case 8: goto L_4600d1; case 9: goto L_4600d1; default: abort(); }	/* 46007c: jmp dword ptr [ecx*4 + 0x460248] */
L_460083:
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 460083: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 460086: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->edx*4 + 0x9f9068u));	/* 460089: mov eax, dword ptr [edx*4 + 0x9f9068] */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 460090: add eax, 0x64 */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 460093: mov dword ptr [esp + 0x28], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 460097: fild dword ptr [esp + 0x28] */
	goto L_4600e9;	/* 46009b: jmp 0x4600e9 */
L_46009d:
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 46009d: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 4600a0: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->edx*4 + 0x9f906cu));	/* 4600a3: mov eax, dword ptr [edx*4 + 0x9f906c] */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4600aa: add eax, 0x64 */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 4600ad: mov dword ptr [esp + 0x28], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 4600b1: fild dword ptr [esp + 0x28] */
	goto L_4600e9;	/* 4600b5: jmp 0x4600e9 */
L_4600b7:
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 4600b7: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 4600ba: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->edx*4 + 0x9f9070u));	/* 4600bd: mov eax, dword ptr [edx*4 + 0x9f9070] */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4600c4: add eax, 0x64 */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 4600c7: mov dword ptr [esp + 0x28], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 4600cb: fild dword ptr [esp + 0x28] */
	goto L_4600e9;	/* 4600cf: jmp 0x4600e9 */
L_4600d1:
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 4600d1: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 4600d4: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->edx*4 + 0x9f9074u));	/* 4600d7: mov eax, dword ptr [edx*4 + 0x9f9074] */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4600de: add eax, 0x64 */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 4600e1: mov dword ptr [esp + 0x28], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 4600e5: fild dword ptr [esp + 0x28] */
L_4600e9:
	ST(0) = ST(0) * (long double)(int)M32((DWORD)(m->esp + 0x24u));	/* 4600e9: fimul dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 4600ed: fmul dword ptr [0x4a9420] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4600f3: fadd dword ptr [0x4a942c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4600f9: call 0x49ec14 */
	m->ebx = m->eax;	/* 4600fe: mov ebx, eax */
	M32((DWORD)(m->esp + 0x24u)) = m->ebx;	/* 460100: mov dword ptr [esp + 0x24], ebx */
	goto L_46010a;	/* 460104: jmp 0x46010a */
L_460106:
	m->ebx = M32((DWORD)(m->esp + 0x24u));	/* 460106: mov ebx, dword ptr [esp + 0x24] */
L_46010a:
	m->eax = M32((DWORD)(m->edi + 0x1cd9798u));	/* 46010a: mov eax, dword ptr [edi + 0x1cd9798] */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 460110: test ah, 1 */
	if (m->zf) goto L_46011b;	/* 460113: je 0x46011b */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 460115: add ebx, ebx */
	M32((DWORD)(m->esp + 0x24u)) = m->ebx;	/* 460117: mov dword ptr [esp + 0x24], ebx */
L_46011b:
	m->eax = M32((DWORD)(m->esi + 0x1cd9798u));	/* 46011b: mov eax, dword ptr [esi + 0x1cd9798] */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x8u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 460121: test ah, 8 */
	if (m->zf) goto L_460133;	/* 460124: je 0x460133 */
	m->eax = m->ebx;	/* 460126: mov eax, ebx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 460128: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 460129: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 46012b: sar eax, 1 */
	m->ebx = m->eax;	/* 46012d: mov ebx, eax */
	M32((DWORD)(m->esp + 0x24u)) = m->ebx;	/* 46012f: mov dword ptr [esp + 0x24], ebx */
L_460133:
	m->ecx = M32((DWORD)(m->esi + 0x1cd94c0u));	/* 460133: mov ecx, dword ptr [esi + 0x1cd94c0] */
	m->eax = M32((DWORD)(m->edi + 0x1cd94c0u));	/* 460139: mov eax, dword ptr [edi + 0x1cd94c0] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46013f: cmp ecx, eax */
	if (!m->zf) goto L_46014d;	/* 460141: jne 0x46014d */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x1cu)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 460143: cmp dword ptr [esp + 0x1c], ebp */
	if (!m->zf) goto L_460216;	/* 460147: jne 0x460216 */
L_46014d:
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 46014d: mov eax, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 460151: xor ebp, ebp */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 460153: sub eax, ebp */
	if (m->zf) goto L_4601b6;	/* 460155: je 0x4601b6 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 460157: dec eax */
	if (!m->zf) goto L_4601d2;	/* 460158: jne 0x4601d2 */
	m->edi = M32((DWORD)(m->esi + 0x1cd94d4u));	/* 46015a: mov edi, dword ptr [esi + 0x1cd94d4] */
	{ DWORD a_ = m->edi, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 460160: cmp edi, ebx */
	M32((DWORD)(m->esp + 0x28u)) = m->edi;	/* 460162: mov dword ptr [esp + 0x28], edi */
	if (m->sf != m->of) goto L_46018d;	/* 460166: jl 0x46018d */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x24u)));	/* 460168: fild dword ptr [esp + 0x24] */
	{ DWORD a_ = m->edi, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46016c: sub edi, ebx */
	M32((DWORD)(m->esi + 0x1cd94d4u)) = m->edi;	/* 46016e: mov dword ptr [esi + 0x1cd94d4], edi */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9758u));	/* 460174: fmul dword ptr [0x4a9758] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 46017a: fadd dword ptr [0x4a942c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 460180: call 0x49ec14 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x1cd94d0u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(m->esi + 0x1cd94d0u)) = r_; }	/* 460185: sub dword ptr [esi + 0x1cd94d0], eax */
	goto L_4601d2;	/* 46018b: jmp 0x4601d2 */
L_46018d:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 46018d: fild dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9758u));	/* 460191: fmul dword ptr [0x4a9758] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 460197: fadd dword ptr [0x4a942c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 46019d: call 0x49ec14 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4601a2: sub edi, eax */
	m->eax = M32((DWORD)(m->esi + 0x1cd94d0u));	/* 4601a4: mov eax, dword ptr [esi + 0x1cd94d0] */
	{ DWORD a_ = m->edi, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4601aa: sub edi, ebx */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4601ac: add eax, edi */
	M32((DWORD)(m->esi + 0x1cd94d0u)) = m->eax;	/* 4601ae: mov dword ptr [esi + 0x1cd94d0], eax */
	goto L_4601cc;	/* 4601b4: jmp 0x4601cc */
L_4601b6:
	m->eax = M32((DWORD)(m->esi + 0x1cd94d4u));	/* 4601b6: mov eax, dword ptr [esi + 0x1cd94d4] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4601bc: sub eax, ebx */
	M32((DWORD)(m->esi + 0x1cd94d4u)) = m->eax;	/* 4601be: mov dword ptr [esi + 0x1cd94d4], eax */
	if (!m->sf) goto L_4601d2;	/* 4601c4: jns 0x4601d2 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x1cd94d0u)), b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(m->esi + 0x1cd94d0u)) = r_; }	/* 4601c6: add dword ptr [esi + 0x1cd94d0], eax */
L_4601cc:
	M32((DWORD)(m->esi + 0x1cd94d4u)) = m->ebp;	/* 4601cc: mov dword ptr [esi + 0x1cd94d4], ebp */
L_4601d2:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x1cd94d0u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4601d2: cmp dword ptr [esi + 0x1cd94d0], ebp */
	if (m->sf == m->of) goto L_4601e0;	/* 4601d8: jge 0x4601e0 */
	M32((DWORD)(m->esi + 0x1cd94d0u)) = m->ebp;	/* 4601da: mov dword ptr [esi + 0x1cd94d0], ebp */
L_4601e0:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x1cd94d4u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4601e0: cmp dword ptr [esi + 0x1cd94d4], ebp */
	if (m->sf == m->of) goto L_4601ee;	/* 4601e6: jge 0x4601ee */
	M32((DWORD)(m->esi + 0x1cd94d4u)) = m->ebp;	/* 4601e8: mov dword ptr [esi + 0x1cd94d4], ebp */
L_4601ee:
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 4601ee: mov edx, dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4601f2: mov eax, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 4601f6: mov ecx, dword ptr [esp + 0x2c] */
	M32((DWORD)(m->esi + 0x1cd9864u)) = m->edx;	/* 4601fa: mov dword ptr [esi + 0x1cd9864], edx */
	M32((DWORD)(m->esi + 0x1cd9868u)) = m->eax;	/* 460200: mov dword ptr [esi + 0x1cd9868], eax */
	M32((DWORD)(m->esi + 0x1cd986cu)) = m->ecx;	/* 460206: mov dword ptr [esi + 0x1cd986c], ecx */
	M32((DWORD)(m->esi + 0x1ce1bf8u)) = 0x1u;	/* 46020c: mov dword ptr [esi + 0x1ce1bf8], 1 */
L_460216:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 460216: mov eax, dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 46021a: mov edx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esi + 0x1ce1bfcu)) = 0x3f000000u;	/* 46021e: mov dword ptr [esi + 0x1ce1bfc], 0x3f000000 */
	m->edi = M32(m->esp); m->esp += 4;	/* 460228: pop edi */
	m->ecx = M32((DWORD)(m->eax + 0x202e8d4u));	/* 460229: mov ecx, dword ptr [eax + 0x202e8d4] */
	m->ebp = M32(m->esp); m->esp += 4;	/* 46022f: pop ebp */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 460230: cmp edx, ecx */
	m->ebx = M32(m->esp); m->esp += 4;	/* 460232: pop ebx */
	if (!m->zf) goto L_460241;	/* 460233: jne 0x460241 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 460235: push 0x64 */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 460237: push 0xc */
	m->esp -= 4; M32(m->esp) = 0x46023eu; native_call(m, 0x456e50u);	/* 460239: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46023e: add esp, 8 */
L_460241:
	m->esi = M32(m->esp); m->esp += 4;	/* 460241: pop esi */
	m->ecx = M32(m->esp); m->esp += 4;	/* 460242: pop ecx */
	m->esp += 4 + 24; return;	/* 460243: ret 0x18 */
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
