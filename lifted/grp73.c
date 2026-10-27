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

static void lift_43a420(X86 *m);

/* room_43a420 (0x43a420), lifted by tools/lift.py */
static void lift_43a420(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a420: sub esp, 0x20 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 43a423: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 43a428: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a42e: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a42f: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43a435u; native_call(m, 0x4322c0u);	/* 43a430: call 0x4322c0 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a435: push 2 */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 43a437: mov dword ptr [esp + 0x14], eax */
	m->esp -= 4; M32(m->esp) = 0x43a440u; native_call(m, 0x41ef90u);	/* 43a43b: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a440: add esp, 0xc */
	m->esp -= 4; M32(m->esp) = 0x43a449u; native_call(m, M32(0x4a9218u));	/* 43a443: call dword ptr [0x4a9218] */
	{ DWORD a_ = M32((DWORD)(0x9dd6d4u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43a449: cmp dword ptr [0x9dd6d4], 1 */
	if (!m->zf) goto L_43a4dd;	/* 43a450: jne 0x43a4dd */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a456: push 0x3f333333 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a45b: push 0x3f333333 */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43a460: push 0x3e4ccccd */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43a465: push 0x3e4ccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a46a: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43a474u; native_call(m, 0x41f0e0u);	/* 43a46f: call 0x41f0e0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a474: push 1 */
	{ DWORD v_ = 0x118u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a476: push 0x118 */
	{ DWORD v_ = 0x230u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a47b: push 0x230 */
	{ DWORD v_ = 0xc8u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a480: push 0xc8 */
	{ DWORD v_ = 0x50u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a485: push 0x50 */
	m->esp -= 4; M32(m->esp) = 0x43a48cu; native_call(m, 0x427970u);	/* 43a487: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a48c: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a491: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a493: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a498: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a49d: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43a4a7u; native_call(m, 0x41f0e0u);	/* 43a4a2: call 0x41f0e0 */
	{ DWORD v_ = 0x75b1a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a4a7: push 0x75b1a4 */
	{ DWORD v_ = 0x230u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a4ac: push 0x230 */
	{ DWORD v_ = 0xdcu; m->esp -= 4; M32(m->esp) = v_; }	/* 43a4b1: push 0xdc */
	{ DWORD v_ = 0x50u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a4b6: push 0x50 */
	m->esp -= 4; M32(m->esp) = 0x43a4bdu; native_call(m, 0x4029d0u);	/* 43a4b8: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a4bd: add esp, 0x4c */
	{ DWORD v_ = 0x74f724u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a4c0: push 0x74f724 */
	{ DWORD v_ = 0x230u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a4c5: push 0x230 */
	{ DWORD v_ = 0xf0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a4ca: push 0xf0 */
	{ DWORD v_ = 0x50u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a4cf: push 0x50 */
	m->esp -= 4; M32(m->esp) = 0x43a4d6u; native_call(m, 0x4029d0u);	/* 43a4d1: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a4d6: add esp, 0x10 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a4d9: add esp, 0x20 */
	m->esp += 4 + 0; return;	/* 43a4dc: ret  */
L_43a4dd:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a4dd: push ebx */
	m->ebx = M32((DWORD)(0x4a9228u));	/* 43a4de: mov ebx, dword ptr [0x4a9228] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43a4e4: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43a4e5: push edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a4e6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a4eb: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a4f0: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a4f5: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43a4fcu; native_call(m, m->ebx);	/* 43a4fa: call ebx */
	m->edx = M32((DWORD)(0x4deb50u));	/* 43a4fc: mov edx, dword ptr [0x4deb50] */
	m->eax = M32((DWORD)(0x9dd374u));	/* 43a502: mov eax, dword ptr [0x9dd374] */
	m->ecx = M32((DWORD)(0x9dd370u));	/* 43a507: mov ecx, dword ptr [0x9dd370] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a50d: push edx */
	m->edx = M32((DWORD)(0x9dd36cu));	/* 43a50e: mov edx, dword ptr [0x9dd36c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a514: push eax */
	m->eax = M32((DWORD)(0x9dd368u));	/* 43a515: mov eax, dword ptr [0x9dd368] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a51a: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a51b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a51c: push eax */
	m->esp -= 4; M32(m->esp) = 0x43a522u; native_call(m, 0x427a90u);	/* 43a51d: call 0x427a90 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a522: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a527: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a52c: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a531: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a533: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43a53du; native_call(m, 0x41f0e0u);	/* 43a538: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dd36cu));	/* 43a53d: mov ecx, dword ptr [0x9dd36c] */
	m->edx = M32((DWORD)(0x9dd370u));	/* 43a543: mov edx, dword ptr [0x9dd370] */
	{ DWORD a_ = m->edx, b_ = 0xfffffff0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43a549: add edx, -0x10 */
	m->eax = (DWORD)(m->ecx + 0x28u);	/* 43a54c: lea eax, [ecx + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a54f: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a550: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a551: push eax */
	m->eax = M32((DWORD)(0x9dd368u));	/* 43a552: mov eax, dword ptr [0x9dd368] */
	{ DWORD a_ = m->eax, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43a557: add eax, 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a55a: push eax */
	m->esp -= 4; M32(m->esp) = 0x43a560u; native_call(m, 0x427a40u);	/* 43a55b: call 0x427a40 */
	m->ecx = M32((DWORD)(0x9dceccu));	/* 43a560: mov ecx, dword ptr [0x9dcecc] */
	m->edx = M32((DWORD)(0x9dcec8u));	/* 43a566: mov edx, dword ptr [0x9dcec8] */
	m->eax = M32((DWORD)(0x9dcec4u));	/* 43a56c: mov eax, dword ptr [0x9dcec4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a571: push ecx */
	m->ecx = M32((DWORD)(0x9dcec0u));	/* 43a572: mov ecx, dword ptr [0x9dcec0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a578: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a579: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a57a: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a57b: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43a585u; native_call(m, 0x41f0e0u);	/* 43a580: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x9dd36cu));	/* 43a585: mov edx, dword ptr [0x9dd36c] */
	m->eax = M32((DWORD)(0x9dd368u));	/* 43a58b: mov eax, dword ptr [0x9dd368] */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a590: add esp, 0x4c */
	{ DWORD a_ = m->edx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43a593: add edx, 0x10 */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43a596: add eax, 0x20 */
	{ DWORD v_ = 0x7592a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a599: push 0x7592a4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a59e: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a59f: push eax */
	m->esp -= 4; M32(m->esp) = 0x43a5a5u; native_call(m, 0x4028b0u);	/* 43a5a0: call 0x4028b0 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a5a5: add esp, 0xc */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 43a5a8: xor edi, edi */
	m->esi = 0x759324u;	/* 43a5aa: mov esi, 0x759324 */
L_43a5af:
	m->ecx = M32((DWORD)(0x9dd36cu));	/* 43a5af: mov ecx, dword ptr [0x9dd36c] */
	m->eax = M32((DWORD)(0x9dd368u));	/* 43a5b5: mov eax, dword ptr [0x9dd368] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43a5ba: push esi */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43a5bb: add eax, 0x20 */
	m->edx = (DWORD)(m->edi + m->ecx*1 + 0x34u);	/* 43a5be: lea edx, [edi + ecx + 0x34] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a5c2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a5c3: push eax */
	m->esp -= 4; M32(m->esp) = 0x43a5c9u; native_call(m, 0x402620u);	/* 43a5c4: call 0x402620 */
	{ DWORD a_ = m->esi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 43a5c9: add esi, 0x80 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a5cf: add esp, 0xc */
	{ DWORD a_ = m->edi, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43a5d2: add edi, 0x1c */
	{ DWORD a_ = m->esi, b_ = 0x7595a4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43a5d5: cmp esi, 0x7595a4 */
	if (m->sf != m->of) goto L_43a5af;	/* 43a5db: jl 0x43a5af */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 43a5dd: xor edi, edi */
	m->esi = 0x7595a4u;	/* 43a5df: mov esi, 0x7595a4 */
L_43a5e4:
	m->ecx = M32((DWORD)(0x9dd36cu));	/* 43a5e4: mov ecx, dword ptr [0x9dd36c] */
	m->eax = M32((DWORD)(0x9dd368u));	/* 43a5ea: mov eax, dword ptr [0x9dd368] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43a5ef: push esi */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43a5f0: add eax, 0x20 */
	m->edx = (DWORD)(m->edi + m->ecx*1 + 0xbeu);	/* 43a5f3: lea edx, [edi + ecx + 0xbe] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a5fa: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a5fb: push eax */
	m->esp -= 4; M32(m->esp) = 0x43a601u; native_call(m, 0x402620u);	/* 43a5fc: call 0x402620 */
	{ DWORD a_ = m->esi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 43a601: add esi, 0x80 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a607: add esp, 0xc */
	{ DWORD a_ = m->edi, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43a60a: add edi, 0x18 */
	{ DWORD a_ = m->esi, b_ = 0x759924u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43a60d: cmp esi, 0x759924 */
	if (m->sf != m->of) goto L_43a5e4;	/* 43a613: jl 0x43a5e4 */
	m->ecx = M32((DWORD)(0x9dd36cu));	/* 43a615: mov ecx, dword ptr [0x9dd36c] */
	m->edx = M32((DWORD)(0x9dd368u));	/* 43a61b: mov edx, dword ptr [0x9dd368] */
	{ DWORD a_ = m->ecx, b_ = 0x38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43a621: add ecx, 0x38 */
	{ DWORD v_ = 0x9dd1d8u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a624: push 0x9dd1d8 */
	{ DWORD a_ = m->edx, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43a629: add edx, 0x98 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a62f: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a630: push edx */
	m->esp -= 4; M32(m->esp) = 0x43a636u; native_call(m, 0x402620u);	/* 43a631: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a636: add esp, 0xc */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 43a639: xor esi, esi */
L_43a63b:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a63b: push 0x3f800000 */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43a640: push 0x3dcccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43a645: push 0x3dcccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43a64a: push 0x3dcccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a64f: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43a659u; native_call(m, 0x41f0e0u);	/* 43a654: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd36cu));	/* 43a659: mov eax, dword ptr [0x9dd36c] */
	m->edx = M32((DWORD)(0x9dd370u));	/* 43a65e: mov edx, dword ptr [0x9dd370] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a664: push 1 */
	{ DWORD a_ = m->edx, b_ = 0xffffffe0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43a666: add edx, -0x20 */
	m->ecx = (DWORD)(m->esi + m->eax*1 + 0x64u);	/* 43a669: lea ecx, [esi + eax + 0x64] */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x4eu);	/* 43a66d: lea eax, [esi + eax + 0x4e] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a671: push ecx */
	m->ecx = M32((DWORD)(0x9dd368u));	/* 43a672: mov ecx, dword ptr [0x9dd368] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a678: push edx */
	{ DWORD a_ = m->ecx, b_ = 0x8eu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43a679: add ecx, 0x8e */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a67f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a680: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43a686u; native_call(m, 0x427970u);	/* 43a681: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a686: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a68b: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a68d: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a692: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a694: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43a69eu; native_call(m, 0x41f0e0u);	/* 43a699: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd36cu));	/* 43a69e: mov eax, dword ptr [0x9dd36c] */
	m->ecx = M32((DWORD)(0x9dd370u));	/* 43a6a3: mov ecx, dword ptr [0x9dd370] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a6a9: push 0 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffe0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43a6ab: add ecx, -0x20 */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x64u);	/* 43a6ae: lea edx, [esi + eax + 0x64] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a6b2: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x4eu);	/* 43a6b3: lea edx, [esi + eax + 0x4e] */
	m->eax = M32((DWORD)(0x9dd368u));	/* 43a6b7: mov eax, dword ptr [0x9dd368] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a6bc: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x8eu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43a6bd: add eax, 0x8e */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a6c2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a6c3: push eax */
	m->esp -= 4; M32(m->esp) = 0x43a6c9u; native_call(m, 0x427970u);	/* 43a6c4: call 0x427970 */
	{ DWORD a_ = m->esi, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 43a6c9: add esi, 0x1c */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a6cc: add esp, 0x50 */
	{ DWORD a_ = m->esi, b_ = 0x70u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43a6cf: cmp esi, 0x70 */
	if (m->sf != m->of) goto L_43a63b;	/* 43a6d2: jl 0x43a63b */
	m->eax = M32((DWORD)(0x9dd69cu));	/* 43a6d8: mov eax, dword ptr [0x9dd69c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43a6dd: test eax, eax */
	if (!m->zf) goto L_43a745;	/* 43a6df: jne 0x43a745 */
	m->edi = 0x9dd6d8u;	/* 43a6e1: mov edi, 0x9dd6d8 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43a6e6: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43a6e9: xor eax, eax */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43a6eb: xor edx, edx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43a6ed: repne scasb al, byte ptr es:[edi] */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 43a6ef: mov dword ptr [esp + 0x18], edx */
	M32((DWORD)(m->esp + 0x1cu)) = m->edx;	/* 43a6f3: mov dword ptr [esp + 0x1c], edx */
	m->ecx = ~m->ecx;	/* 43a6f7: not ecx */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 43a6f9: mov dword ptr [esp + 0x20], edx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43a6fd: dec ecx */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 43a6fe: mov dword ptr [esp + 0x24], edx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43a702: test ecx, ecx */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 43a704: mov dword ptr [esp + 0x28], edx */
	if (m->zf || m->sf != m->of) goto L_43a721;	/* 43a708: jle 0x43a721 */
	m->edx = m->ecx;	/* 43a70a: mov edx, ecx */
	m->eax = 0x2a2a2a2au;	/* 43a70c: mov eax, 0x2a2a2a2a */
	m->edi = (DWORD)(m->esp + 0x18u);	/* 43a711: lea edi, [esp + 0x18] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43a715: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 43a718: rep stosd dword ptr es:[edi], eax */
	m->ecx = m->edx;	/* 43a71a: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43a71c: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1; m->ecx--; }	/* 43a71f: rep stosb byte ptr es:[edi], al */
L_43a721:
	m->ecx = M32((DWORD)(0x9dd36cu));	/* 43a721: mov ecx, dword ptr [0x9dd36c] */
	m->edx = M32((DWORD)(0x9dd368u));	/* 43a727: mov edx, dword ptr [0x9dd368] */
	m->eax = (DWORD)(m->esp + 0x18u);	/* 43a72d: lea eax, [esp + 0x18] */
	{ DWORD a_ = m->ecx, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43a731: add ecx, 0x50 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a734: push eax */
	{ DWORD a_ = m->edx, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43a735: add edx, 0x98 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a73b: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a73c: push edx */
	m->esp -= 4; M32(m->esp) = 0x43a742u; native_call(m, 0x402620u);	/* 43a73d: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a742: add esp, 0xc */
L_43a745:
	m->eax = M32((DWORD)(0x9dd37cu));	/* 43a745: mov eax, dword ptr [0x9dd37c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43a74a: test eax, eax */
	if (!m->zf) goto L_43a7b0;	/* 43a74c: jne 0x43a7b0 */
	m->edi = 0x9dd1f6u;	/* 43a74e: mov edi, 0x9dd1f6 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43a753: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43a756: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43a758: repne scasb al, byte ptr es:[edi] */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 43a75a: mov dword ptr [esp + 0x18], eax */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 43a75e: mov dword ptr [esp + 0x1c], eax */
	m->ecx = ~m->ecx;	/* 43a762: not ecx */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 43a764: mov dword ptr [esp + 0x20], eax */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43a768: dec ecx */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 43a769: mov dword ptr [esp + 0x24], eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43a76d: test ecx, ecx */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 43a76f: mov dword ptr [esp + 0x28], eax */
	if (m->zf || m->sf != m->of) goto L_43a78c;	/* 43a773: jle 0x43a78c */
	m->edx = m->ecx;	/* 43a775: mov edx, ecx */
	m->eax = 0x2a2a2a2au;	/* 43a777: mov eax, 0x2a2a2a2a */
	m->edi = (DWORD)(m->esp + 0x18u);	/* 43a77c: lea edi, [esp + 0x18] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43a780: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 43a783: rep stosd dword ptr es:[edi], eax */
	m->ecx = m->edx;	/* 43a785: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43a787: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1; m->ecx--; }	/* 43a78a: rep stosb byte ptr es:[edi], al */
L_43a78c:
	m->ecx = M32((DWORD)(0x9dd36cu));	/* 43a78c: mov ecx, dword ptr [0x9dd36c] */
	m->edx = M32((DWORD)(0x9dd368u));	/* 43a792: mov edx, dword ptr [0x9dd368] */
	m->eax = (DWORD)(m->esp + 0x18u);	/* 43a798: lea eax, [esp + 0x18] */
	{ DWORD a_ = m->ecx, b_ = 0x6cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43a79c: add ecx, 0x6c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a79f: push eax */
	{ DWORD a_ = m->edx, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43a7a0: add edx, 0x98 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a7a6: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a7a7: push edx */
	m->esp -= 4; M32(m->esp) = 0x43a7adu; native_call(m, 0x402620u);	/* 43a7a8: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a7ad: add esp, 0xc */
L_43a7b0:
	m->eax = M32((DWORD)(0x9dd378u));	/* 43a7b0: mov eax, dword ptr [0x9dd378] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43a7b5: test eax, eax */
	if (!m->zf) goto L_43a81e;	/* 43a7b7: jne 0x43a81e */
	m->edi = 0x9dd202u;	/* 43a7b9: mov edi, 0x9dd202 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43a7be: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43a7c1: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43a7c3: repne scasb al, byte ptr es:[edi] */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 43a7c5: mov dword ptr [esp + 0x18], eax */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 43a7c9: mov dword ptr [esp + 0x1c], eax */
	m->ecx = ~m->ecx;	/* 43a7cd: not ecx */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 43a7cf: mov dword ptr [esp + 0x20], eax */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43a7d3: dec ecx */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 43a7d4: mov dword ptr [esp + 0x24], eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43a7d8: test ecx, ecx */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 43a7da: mov dword ptr [esp + 0x28], eax */
	if (m->zf || m->sf != m->of) goto L_43a7f7;	/* 43a7de: jle 0x43a7f7 */
	m->edx = m->ecx;	/* 43a7e0: mov edx, ecx */
	m->eax = 0x2a2a2a2au;	/* 43a7e2: mov eax, 0x2a2a2a2a */
	m->edi = (DWORD)(m->esp + 0x18u);	/* 43a7e7: lea edi, [esp + 0x18] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43a7eb: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 43a7ee: rep stosd dword ptr es:[edi], eax */
	m->ecx = m->edx;	/* 43a7f0: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43a7f2: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1; m->ecx--; }	/* 43a7f5: rep stosb byte ptr es:[edi], al */
L_43a7f7:
	m->ecx = M32((DWORD)(0x9dd36cu));	/* 43a7f7: mov ecx, dword ptr [0x9dd36c] */
	m->edx = M32((DWORD)(0x9dd368u));	/* 43a7fd: mov edx, dword ptr [0x9dd368] */
	m->eax = (DWORD)(m->esp + 0x18u);	/* 43a803: lea eax, [esp + 0x18] */
	{ DWORD a_ = m->ecx, b_ = 0x88u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43a807: add ecx, 0x88 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a80d: push eax */
	{ DWORD a_ = m->edx, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43a80e: add edx, 0x98 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a814: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a815: push edx */
	m->esp -= 4; M32(m->esp) = 0x43a81bu; native_call(m, 0x402620u);	/* 43a816: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a81b: add esp, 0xc */
L_43a81e:
	m->eax = M32((DWORD)(0x9dd304u));	/* 43a81e: mov eax, dword ptr [0x9dd304] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43a823: test eax, eax */
	if (!m->zf) goto L_43a84c;	/* 43a825: jne 0x43a84c */
	m->eax = M32((DWORD)(0x9dd36cu));	/* 43a827: mov eax, dword ptr [0x9dd36c] */
	m->ecx = M32((DWORD)(0x9dd368u));	/* 43a82c: mov ecx, dword ptr [0x9dd368] */
	{ DWORD a_ = m->eax, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43a832: add eax, 0xa4 */
	{ DWORD v_ = 0x9dd20eu; m->esp -= 4; M32(m->esp) = v_; }	/* 43a837: push 0x9dd20e */
	{ DWORD a_ = m->ecx, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43a83c: add ecx, 0x98 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a842: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a843: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43a849u; native_call(m, 0x402620u);	/* 43a844: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a849: add esp, 0xc */
L_43a84c:
	m->eax = M32((DWORD)(0x9dd5d8u));	/* 43a84c: mov eax, dword ptr [0x9dd5d8] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 43a851: push ebp */
	m->edx = (DWORD)(m->esp + 0x1cu);	/* 43a852: lea edx, [esp + 0x1c] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 43a856: push 0xa */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a858: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a859: push eax */
	m->esp -= 4; M32(m->esp) = 0x43a85fu; native_call(m, 0x49fb53u);	/* 43a85a: call 0x49fb53 */
	m->edx = M32((DWORD)(0x9dd36cu));	/* 43a85f: mov edx, dword ptr [0x9dd36c] */
	m->eax = M32((DWORD)(0x9dd368u));	/* 43a865: mov eax, dword ptr [0x9dd368] */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 43a86a: lea ecx, [esp + 0x28] */
	{ DWORD a_ = m->edx, b_ = 0xbeu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43a86e: add edx, 0xbe */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a874: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43a875: add eax, 0x98 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a87a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a87b: push eax */
	m->esp -= 4; M32(m->esp) = 0x43a881u; native_call(m, 0x402620u);	/* 43a87c: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a881: add esp, 0x18 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a884: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x43a88fu; native_call(m, M32(0x4a9224u));	/* 43a889: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x76d448u));	/* 43a88f: mov eax, dword ptr [0x76d448] */
	m->ecx = m->eax;	/* 43a894: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43a896: and ecx, 0x800001ff */
	if (!m->sf) goto L_43a8a6;	/* 43a89c: jns 0x43a8a6 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43a89e: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43a89f: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 43a8a5: inc ecx */
L_43a8a6:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 43a8a6: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43a8a7: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a8ad: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43a8ae: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 43a8b0: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 43a8b6: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 43a8b9: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x43a8c2u; native_call(m, 0x4566c0u);	/* 43a8bd: call 0x4566c0 */
	m->eax = M32((DWORD)(0x9dd5d8u));	/* 43a8c2: mov eax, dword ptr [0x9dd5d8] */
	m->esi = 0xau;	/* 43a8c7: mov esi, 0xa */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a8cc: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a8d1: push 0x3f800000 */
	m->ecx = (DWORD)(m->eax + 0xffffffffu);	/* 43a8d6: lea ecx, [eax - 1] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a8d9: push 0x3f800000 */
	m->eax = m->ecx;	/* 43a8de: mov eax, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a8e0: push 0x3f800000 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 43a8e5: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->esi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 43a8e6: idiv esi */
	m->eax = 0x66666667u;	/* 43a8e8: mov eax, 0x66666667 */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 43a8ed: mov dword ptr [esp + 0x24], edx */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 43a8f1: imul ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x24u)));	/* 43a8f3: fild dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9590u));	/* 43a8f7: fmul dword ptr [0x4a9590] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 43a8fd: fstp dword ptr [esp + 0x20] */
	{ DWORD a_ = m->edx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 43a901: sar edx, 2 */
	m->ecx = m->edx;	/* 43a904: mov ecx, edx */
	{ DWORD a_ = m->ecx, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43a906: shr ecx, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43a909: add edx, ecx */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 43a90b: mov dword ptr [esp + 0x24], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x24u)));	/* 43a90f: fild dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a958cu));	/* 43a913: fmul dword ptr [0x4a958c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9588u));	/* 43a919: fadd dword ptr [0x4a9588] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 43a91f: fstp dword ptr [esp + 0x24] */
	m->esp -= 4; M32(m->esp) = 0x43a925u; native_call(m, m->ebx);	/* 43a923: call ebx */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a925: push 7 */
	m->esp -= 4; M32(m->esp) = 0x43a92du; native_call(m, M32(0x4a921cu));	/* 43a927: call dword ptr [0x4a921c] */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 43a92d: mov edi, dword ptr [esp + 0x14] */
	m->ebx = M32((DWORD)(m->esp + 0x10u));	/* 43a931: mov ebx, dword ptr [esp + 0x10] */
	m->esi = M32((DWORD)(0x4a920cu));	/* 43a935: mov esi, dword ptr [0x4a920c] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43a93b: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a93c: push ebx */
	m->esp -= 4; M32(m->esp) = 0x43a93fu; native_call(m, m->esi);	/* 43a93d: call esi */
	m->edx = M32((DWORD)(0x9dd36cu));	/* 43a93f: mov edx, dword ptr [0x9dd36c] */
	m->eax = M32((DWORD)(0x9dd368u));	/* 43a945: mov eax, dword ptr [0x9dd368] */
	{ DWORD a_ = m->edx, b_ = 0xbeu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43a94a: add edx, 0xbe */
	{ DWORD a_ = m->eax, b_ = 0xc0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43a950: add eax, 0xc0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a955: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a956: push eax */
	m->esp -= 4; M32(m->esp) = 0x43a95cu; native_call(m, 0x41ef60u);	/* 43a957: call 0x41ef60 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 43a95c: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9590u));	/* 43a960: fadd dword ptr [0x4a9590] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a966: add esp, 8 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43a969: push edi */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 43a96a: fstp dword ptr [esp + 0x14] */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 43a96e: mov edi, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43a972: push edi */
	m->esp -= 4; M32(m->esp) = 0x43a975u; native_call(m, m->esi);	/* 43a973: call esi */
	m->ecx = M32((DWORD)(0x9dd36cu));	/* 43a975: mov ecx, dword ptr [0x9dd36c] */
	m->edx = M32((DWORD)(0x9dd368u));	/* 43a97b: mov edx, dword ptr [0x9dd368] */
	{ DWORD a_ = m->ecx, b_ = 0xbeu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43a981: add ecx, 0xbe */
	{ DWORD a_ = m->edx, b_ = 0xd8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43a987: add edx, 0xd8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a98d: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a98e: push edx */
	m->esp -= 4; M32(m->esp) = 0x43a994u; native_call(m, 0x41ef60u);	/* 43a98f: call 0x41ef60 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 43a994: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a958cu));	/* 43a998: fadd dword ptr [0x4a958c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a99e: add esp, 8 */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 43a9a1: fstp dword ptr [esp + 0x14] */
	m->ebp = M32((DWORD)(m->esp + 0x14u));	/* 43a9a5: mov ebp, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 43a9a9: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43a9aa: push edi */
	m->esp -= 4; M32(m->esp) = 0x43a9adu; native_call(m, m->esi);	/* 43a9ab: call esi */
	m->eax = M32((DWORD)(0x9dd36cu));	/* 43a9ad: mov eax, dword ptr [0x9dd36c] */
	m->ecx = M32((DWORD)(0x9dd368u));	/* 43a9b2: mov ecx, dword ptr [0x9dd368] */
	{ DWORD a_ = m->eax, b_ = 0xceu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43a9b8: add eax, 0xce */
	{ DWORD a_ = m->ecx, b_ = 0xd8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43a9bd: add ecx, 0xd8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a9c3: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a9c4: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43a9cau; native_call(m, 0x41ef60u);	/* 43a9c5: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a9ca: add esp, 8 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 43a9cd: push ebp */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a9ce: push ebx */
	m->esp -= 4; M32(m->esp) = 0x43a9d1u; native_call(m, m->esi);	/* 43a9cf: call esi */
	m->edx = M32((DWORD)(0x9dd36cu));	/* 43a9d1: mov edx, dword ptr [0x9dd36c] */
	m->eax = M32((DWORD)(0x9dd368u));	/* 43a9d7: mov eax, dword ptr [0x9dd368] */
	{ DWORD a_ = m->edx, b_ = 0xceu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43a9dc: add edx, 0xce */
	{ DWORD a_ = m->eax, b_ = 0xc0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43a9e2: add eax, 0xc0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a9e7: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a9e8: push eax */
	m->esp -= 4; M32(m->esp) = 0x43a9eeu; native_call(m, 0x41ef60u);	/* 43a9e9: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a9ee: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x43a9f7u; native_call(m, M32(0x4a9220u));	/* 43a9f1: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a9f7: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x43aa02u; native_call(m, M32(0x4a922cu));	/* 43a9fc: call dword ptr [0x4a922c] */
	{ DWORD v_ = 0x3e99999au; m->esp -= 4; M32(m->esp) = v_; }	/* 43aa02: push 0x3e99999a */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43aa07: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43aa09: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43aa0e: push 0x3f800000 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43aa13: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43aa1du; native_call(m, 0x41f0e0u);	/* 43aa18: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd36cu));	/* 43aa1d: mov eax, dword ptr [0x9dd36c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43aa22: push 0 */
	m->ecx = (DWORD)(m->eax + 0xceu);	/* 43aa24: lea ecx, [eax + 0xce] */
	{ DWORD a_ = m->eax, b_ = 0xbeu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43aa2a: add eax, 0xbe */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43aa2f: push ecx */
	m->ecx = M32((DWORD)(0x9dd368u));	/* 43aa30: mov ecx, dword ptr [0x9dd368] */
	m->edx = (DWORD)(m->ecx + 0xd8u);	/* 43aa36: lea edx, [ecx + 0xd8] */
	{ DWORD a_ = m->ecx, b_ = 0xc1u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43aa3c: add ecx, 0xc1 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43aa42: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43aa43: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43aa44: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43aa4au; native_call(m, 0x427970u);	/* 43aa45: call 0x427970 */
	m->eax = M32((DWORD)(0x9dd248u));	/* 43aa4a: mov eax, dword ptr [0x9dd248] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43aa4f: add esp, 0x28 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43aa52: test eax, eax */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43aa54: pop ebp */
	if (!m->zf) goto L_43aa7e;	/* 43aa55: jne 0x43aa7e */
	m->eax = M32((DWORD)(0x9dd36cu));	/* 43aa57: mov eax, dword ptr [0x9dd36c] */
	m->ecx = M32((DWORD)(0x9dd368u));	/* 43aa5c: mov ecx, dword ptr [0x9dd368] */
	{ DWORD a_ = m->eax, b_ = 0xd6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43aa62: add eax, 0xd6 */
	{ DWORD v_ = 0x759924u; m->esp -= 4; M32(m->esp) = v_; }	/* 43aa67: push 0x759924 */
	{ DWORD a_ = m->ecx, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43aa6c: add ecx, 0x98 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43aa72: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43aa73: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43aa79u; native_call(m, 0x402620u);	/* 43aa74: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43aa79: add esp, 0xc */
	goto L_43aab2;	/* 43aa7c: jmp 0x43aab2 */
L_43aa7e:
	m->edx = (DWORD)(m->esp + 0x18u);	/* 43aa7e: lea edx, [esp + 0x18] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 43aa82: push 0xa */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43aa84: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43aa85: push eax */
	m->esp -= 4; M32(m->esp) = 0x43aa8bu; native_call(m, 0x49fb53u);	/* 43aa86: call 0x49fb53 */
	m->ecx = M32((DWORD)(0x9dd36cu));	/* 43aa8b: mov ecx, dword ptr [0x9dd36c] */
	m->edx = M32((DWORD)(0x9dd368u));	/* 43aa91: mov edx, dword ptr [0x9dd368] */
	m->eax = (DWORD)(m->esp + 0x24u);	/* 43aa97: lea eax, [esp + 0x24] */
	{ DWORD a_ = m->ecx, b_ = 0xd6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43aa9b: add ecx, 0xd6 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43aaa1: push eax */
	{ DWORD a_ = m->edx, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43aaa2: add edx, 0x98 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43aaa8: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43aaa9: push edx */
	m->esp -= 4; M32(m->esp) = 0x43aaafu; native_call(m, 0x402620u);	/* 43aaaa: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43aaaf: add esp, 0x18 */
L_43aab2:
	FPUSH(x87_ldm((const float *)(DWORD)(0x9dd5e4u)));	/* 43aab2: fld dword ptr [0x9dd5e4] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43aab8: sub esp, 8 */
	m->eax = (DWORD)(m->esp + 0x20u);	/* 43aabb: lea eax, [esp + 0x20] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 43aabf: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b0268u; m->esp -= 4; M32(m->esp) = v_; }	/* 43aac2: push 0x4b0268 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43aac7: push eax */
	m->esp -= 4; M32(m->esp) = 0x43aacdu; native_call(m, 0x49e9ddu);	/* 43aac8: call 0x49e9dd */
	m->edx = M32((DWORD)(0x9dd36cu));	/* 43aacd: mov edx, dword ptr [0x9dd36c] */
	m->eax = M32((DWORD)(0x9dd368u));	/* 43aad3: mov eax, dword ptr [0x9dd368] */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 43aad8: lea ecx, [esp + 0x28] */
	{ DWORD a_ = m->edx, b_ = 0xeeu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43aadc: add edx, 0xee */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43aae2: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43aae3: add eax, 0x98 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43aae8: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43aae9: push eax */
	m->esp -= 4; M32(m->esp) = 0x43aaefu; native_call(m, 0x402620u);	/* 43aaea: call 0x402620 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x9dd5f4u)));	/* 43aaef: fld dword ptr [0x9dd5f4] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43aaf5: add esp, 0x14 */
	m->ecx = (DWORD)(m->esp + 0x20u);	/* 43aaf8: lea ecx, [esp + 0x20] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 43aafc: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b0268u; m->esp -= 4; M32(m->esp) = v_; }	/* 43aaff: push 0x4b0268 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ab04: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43ab0au; native_call(m, 0x49e9ddu);	/* 43ab05: call 0x49e9dd */
	m->eax = M32((DWORD)(0x9dd36cu));	/* 43ab0a: mov eax, dword ptr [0x9dd36c] */
	m->ecx = M32((DWORD)(0x9dd368u));	/* 43ab0f: mov ecx, dword ptr [0x9dd368] */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 43ab15: lea edx, [esp + 0x28] */
	{ DWORD a_ = m->eax, b_ = 0x106u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43ab19: add eax, 0x106 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ab1e: push edx */
	{ DWORD a_ = m->ecx, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43ab1f: add ecx, 0x98 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ab25: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ab26: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43ab2cu; native_call(m, 0x402620u);	/* 43ab27: call 0x402620 */
	m->eax = M32((DWORD)(0x9dd5ecu));	/* 43ab2c: mov eax, dword ptr [0x9dd5ec] */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 43ab31: lea edx, [esp + 0x34] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 43ab35: push 0xa */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ab37: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ab38: push eax */
	m->esp -= 4; M32(m->esp) = 0x43ab3eu; native_call(m, 0x49fb53u);	/* 43ab39: call 0x49fb53 */
	m->edx = M32((DWORD)(0x9dd36cu));	/* 43ab3e: mov edx, dword ptr [0x9dd36c] */
	m->eax = M32((DWORD)(0x9dd368u));	/* 43ab44: mov eax, dword ptr [0x9dd368] */
	m->ecx = (DWORD)(m->esp + 0x40u);	/* 43ab49: lea ecx, [esp + 0x40] */
	{ DWORD a_ = m->edx, b_ = 0x11eu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43ab4d: add edx, 0x11e */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ab53: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43ab54: add eax, 0x98 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ab59: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ab5a: push eax */
	m->esp -= 4; M32(m->esp) = 0x43ab60u; native_call(m, 0x402620u);	/* 43ab5b: call 0x402620 */
	m->edx = M32((DWORD)(0x9dd5f0u));	/* 43ab60: mov edx, dword ptr [0x9dd5f0] */
	m->ecx = (DWORD)(m->esp + 0x4cu);	/* 43ab66: lea ecx, [esp + 0x4c] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 43ab6a: push 0xa */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ab6c: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ab6d: push edx */
	m->esp -= 4; M32(m->esp) = 0x43ab73u; native_call(m, 0x49fb53u);	/* 43ab6e: call 0x49fb53 */
	m->ecx = M32((DWORD)(0x9dd36cu));	/* 43ab73: mov ecx, dword ptr [0x9dd36c] */
	m->edx = M32((DWORD)(0x9dd368u));	/* 43ab79: mov edx, dword ptr [0x9dd368] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43ab7f: add esp, 0x40 */
	m->eax = (DWORD)(m->esp + 0x18u);	/* 43ab82: lea eax, [esp + 0x18] */
	{ DWORD a_ = m->ecx, b_ = 0x136u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43ab86: add ecx, 0x136 */
	{ DWORD a_ = m->edx, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43ab8c: add edx, 0x98 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ab92: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ab93: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ab94: push edx */
	m->esp -= 4; M32(m->esp) = 0x43ab9au; native_call(m, 0x402620u);	/* 43ab95: call 0x402620 */
	m->ecx = M32((DWORD)(0x9dd5dcu));	/* 43ab9a: mov ecx, dword ptr [0x9dd5dc] */
	m->eax = (DWORD)(m->esp + 0x24u);	/* 43aba0: lea eax, [esp + 0x24] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 43aba4: push 0xa */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43aba6: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43aba7: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43abadu; native_call(m, 0x49fb53u);	/* 43aba8: call 0x49fb53 */
	m->eax = M32((DWORD)(0x9dd36cu));	/* 43abad: mov eax, dword ptr [0x9dd36c] */
	m->ecx = M32((DWORD)(0x9dd368u));	/* 43abb2: mov ecx, dword ptr [0x9dd368] */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 43abb8: lea edx, [esp + 0x30] */
	{ DWORD a_ = m->eax, b_ = 0x14eu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43abbc: add eax, 0x14e */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43abc1: push edx */
	{ DWORD a_ = m->ecx, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43abc2: add ecx, 0x98 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43abc8: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43abc9: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43abcfu; native_call(m, 0x402620u);	/* 43abca: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43abcf: add esp, 0x24 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 43abd2: xor ebx, ebx */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 43abd4: xor esi, esi */
	m->edi = 0x7517a4u;	/* 43abd6: mov edi, 0x7517a4 */
L_43abdb:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43abdb: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x43abe6u; native_call(m, M32(0x4a9224u));	/* 43abe0: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 43abe6: mov eax, dword ptr [0x9db0a4] */
	m->edx = m->eax;	/* 43abeb: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43abed: and edx, 0x800001ff */
	if (!m->sf) goto L_43abfd;	/* 43abf3: jns 0x43abfd */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 43abf5: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43abf6: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 43abfc: inc edx */
L_43abfd:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43abfd: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 43abfe: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 43ac04: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43ac05: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43ac0b: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 43ac0d: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 43ac10: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x43ac19u; native_call(m, 0x4566c0u);	/* 43ac14: call 0x4566c0 */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 43ac19: mov eax, dword ptr [esp + 0x14] */
	m->edx = (DWORD)(m->ebx + 0x4u);	/* 43ac1d: lea edx, [ebx + 4] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43ac20: cmp eax, edx */
	if (!m->zf) goto L_43ac8a;	/* 43ac22: jne 0x43ac8a */
	m->eax = M32((DWORD)(0x68039cu));	/* 43ac24: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43ac29: test eax, eax */
	if (!m->zf) goto L_43ac8a;	/* 43ac2b: jne 0x43ac8a */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ac2d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ac32: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ac37: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ac3c: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43ac47u; native_call(m, M32(0x4a9228u));	/* 43ac41: call dword ptr [0x4a9228] */
	m->ecx = M32((DWORD)(0x9dd374u));	/* 43ac47: mov ecx, dword ptr [0x9dd374] */
	m->eax = M32((DWORD)(0x9dd368u));	/* 43ac4d: mov eax, dword ptr [0x9dd368] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ac52: push 1 */
	m->edx = (DWORD)(m->ecx + 0xfffffff0u);	/* 43ac54: lea edx, [ecx - 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43ac57: add ecx, -0x30 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ac5a: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xf5u);	/* 43ac5b: lea edx, [esi + eax + 0xf5] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ac62: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x7du);	/* 43ac63: lea eax, [esi + eax + 0x7d] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ac67: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ac68: push eax */
	m->esp -= 4; M32(m->esp) = 0x43ac6eu; native_call(m, 0x4282f0u);	/* 43ac69: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x9dceccu));	/* 43ac6e: mov ecx, dword ptr [0x9dcecc] */
	m->edx = M32((DWORD)(0x9dcec8u));	/* 43ac74: mov edx, dword ptr [0x9dcec8] */
	m->eax = M32((DWORD)(0x9dcec4u));	/* 43ac7a: mov eax, dword ptr [0x9dcec4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ac7f: push ecx */
	m->ecx = M32((DWORD)(0x9dcec0u));	/* 43ac80: mov ecx, dword ptr [0x9dcec0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ac86: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ac87: push eax */
	goto L_43ace5;	/* 43ac88: jmp 0x43ace5 */
L_43ac8a:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43ac8a: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ac8f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ac94: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ac99: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43aca4u; native_call(m, M32(0x4a9228u));	/* 43ac9e: call dword ptr [0x4a9228] */
	m->ecx = M32((DWORD)(0x9dd374u));	/* 43aca4: mov ecx, dword ptr [0x9dd374] */
	m->eax = M32((DWORD)(0x9dd368u));	/* 43acaa: mov eax, dword ptr [0x9dd368] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43acaf: push 1 */
	m->edx = (DWORD)(m->ecx + 0xfffffff0u);	/* 43acb1: lea edx, [ecx - 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43acb4: add ecx, -0x30 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43acb7: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xf5u);	/* 43acb8: lea edx, [esi + eax + 0xf5] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43acbf: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x7du);	/* 43acc0: lea eax, [esi + eax + 0x7d] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43acc4: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43acc5: push eax */
	m->esp -= 4; M32(m->esp) = 0x43accbu; native_call(m, 0x4282f0u);	/* 43acc6: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x9dd344u));	/* 43accb: mov ecx, dword ptr [0x9dd344] */
	m->edx = M32((DWORD)(0x9dd340u));	/* 43acd1: mov edx, dword ptr [0x9dd340] */
	m->eax = M32((DWORD)(0x9dd33cu));	/* 43acd7: mov eax, dword ptr [0x9dd33c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43acdc: push ecx */
	m->ecx = M32((DWORD)(0x9dd338u));	/* 43acdd: mov ecx, dword ptr [0x9dd338] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ace3: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ace4: push eax */
L_43ace5:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ace5: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ace6: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43acf0u; native_call(m, 0x41f0e0u);	/* 43aceb: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd368u));	/* 43acf0: mov eax, dword ptr [0x9dd368] */
	m->ecx = M32((DWORD)(0x9dd374u));	/* 43acf5: mov ecx, dword ptr [0x9dd374] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43acfb: add esp, 0x28 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43acfe: add ecx, -0x28 */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xf5u);	/* 43ad01: lea edx, [esi + eax + 0xf5] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43ad08: push edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ad09: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x7du);	/* 43ad0a: lea edx, [esi + eax + 0x7d] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ad0e: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ad0f: push edx */
	m->esp -= 4; M32(m->esp) = 0x43ad15u; native_call(m, 0x4029d0u);	/* 43ad10: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43ad15: add esp, 0x10 */
	{ DWORD a_ = m->edi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43ad18: add edi, 0x80 */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 43ad1e: inc ebx */
	{ DWORD a_ = m->esi, b_ = 0xa0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 43ad1f: add esi, 0xa0 */
	{ DWORD a_ = m->edi, b_ = 0x7518a4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43ad25: cmp edi, 0x7518a4 */
	if (m->sf != m->of) goto L_43abdb;	/* 43ad2b: jl 0x43abdb */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ad31: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ad36: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ad3b: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ad40: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ad42: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43ad4cu; native_call(m, 0x41f0e0u);	/* 43ad47: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd374u));	/* 43ad4c: mov eax, dword ptr [0x9dd374] */
	m->ecx = M32((DWORD)(0x9dd370u));	/* 43ad51: mov ecx, dword ptr [0x9dd370] */
	m->edx = M32((DWORD)(0x9dd368u));	/* 43ad57: mov edx, dword ptr [0x9dd368] */
	{ DWORD a_ = m->eax, b_ = 0xffffffc0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43ad5d: add eax, -0x40 */
	{ DWORD a_ = m->ecx, b_ = 0xfffffff0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43ad60: add ecx, -0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ad63: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ad64: push ecx */
	{ DWORD a_ = m->edx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43ad65: add edx, 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ad68: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ad69: push edx */
	m->esp -= 4; M32(m->esp) = 0x43ad6fu; native_call(m, 0x427a40u);	/* 43ad6a: call 0x427a40 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43ad6f: add esp, 0x24 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ad72: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ad77: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ad7c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ad81: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43ad8cu; native_call(m, M32(0x4a9228u));	/* 43ad86: call dword ptr [0x4a9228] */
	m->eax = M32((DWORD)(0x9dd374u));	/* 43ad8c: mov eax, dword ptr [0x9dd374] */
	m->ecx = M32((DWORD)(0x9dd370u));	/* 43ad91: mov ecx, dword ptr [0x9dd370] */
	m->edx = M32((DWORD)(0x9dd36cu));	/* 43ad97: mov edx, dword ptr [0x9dd36c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ad9d: push eax */
	m->eax = M32((DWORD)(0x9dd368u));	/* 43ad9e: mov eax, dword ptr [0x9dd368] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ada3: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ada4: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ada5: push eax */
	m->esp -= 4; M32(m->esp) = 0x43adabu; native_call(m, 0x428a00u);	/* 43ada6: call 0x428a00 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43adab: add esp, 0x10 */
	m->edi = M32(m->esp); m->esp += 4;	/* 43adae: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43adaf: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43adb0: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43adb1: add esp, 0x20 */
	m->esp += 4 + 0; return;	/* 43adb4: ret  */
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
