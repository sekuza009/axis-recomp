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

static void lift_40b750(X86 *m);

/* arena_createDraw (0x40b750), lifted by tools/lift.py */
static void lift_40b750(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40b750: sub esp, 0x10 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 40b753: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 40b758: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b75e: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 40b75f: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40b760: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40b761: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40b762: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b763: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40b769u; native_call(m, 0x404520u);	/* 40b764: call 0x404520 */
	m->ebx = m->eax;	/* 40b769: mov ebx, eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b76b: push 2 */
	M32((DWORD)(m->esp + 0x1cu)) = m->ebx;	/* 40b76d: mov dword ptr [esp + 0x1c], ebx */
	m->esp -= 4; M32(m->esp) = 0x40b776u; native_call(m, 0x41ef90u);	/* 40b771: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40b776: add esp, 0xc */
	m->esp -= 4; M32(m->esp) = 0x40b77fu; native_call(m, M32(0x4a9218u));	/* 40b779: call dword ptr [0x4a9218] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b77f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b784: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b789: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b78e: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40b799u; native_call(m, M32(0x4a9228u));	/* 40b793: call dword ptr [0x4a9228] */
	m->edx = M32((DWORD)(0x4deb50u));	/* 40b799: mov edx, dword ptr [0x4deb50] */
	m->eax = M32((DWORD)(0x4dbb0cu));	/* 40b79f: mov eax, dword ptr [0x4dbb0c] */
	m->ecx = M32((DWORD)(0x4dbb08u));	/* 40b7a4: mov ecx, dword ptr [0x4dbb08] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b7aa: push edx */
	m->edx = M32((DWORD)(0x4dbb04u));	/* 40b7ab: mov edx, dword ptr [0x4dbb04] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40b7b1: push eax */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 40b7b2: mov eax, dword ptr [0x4dbb00] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b7b7: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b7b8: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40b7b9: push eax */
	m->esp -= 4; M32(m->esp) = 0x40b7bfu; native_call(m, 0x427a90u);	/* 40b7ba: call 0x427a90 */
	m->ecx = M32((DWORD)(0x4dbaa4u));	/* 40b7bf: mov ecx, dword ptr [0x4dbaa4] */
	m->edx = M32((DWORD)(0x4dbaa0u));	/* 40b7c5: mov edx, dword ptr [0x4dbaa0] */
	m->eax = M32((DWORD)(0x4dba9cu));	/* 40b7cb: mov eax, dword ptr [0x4dba9c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b7d0: push ecx */
	m->ecx = M32((DWORD)(0x4dba98u));	/* 40b7d1: mov ecx, dword ptr [0x4dba98] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b7d7: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40b7d8: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b7d9: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b7da: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40b7e4u; native_call(m, 0x41f0e0u);	/* 40b7df: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x4dbb04u));	/* 40b7e4: mov edx, dword ptr [0x4dbb04] */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 40b7ea: mov eax, dword ptr [0x4dbb00] */
	{ DWORD a_ = m->edx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40b7ef: add edx, 0x10 */
	{ DWORD v_ = 0x752c24u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b7f2: push 0x752c24 */
	{ DWORD a_ = m->eax, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40b7f7: add eax, 0x50 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b7fa: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40b7fb: push eax */
	m->esp -= 4; M32(m->esp) = 0x40b801u; native_call(m, 0x4028b0u);	/* 40b7fc: call 0x4028b0 */
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40b801: add esp, 0x34 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 40b804: xor edi, edi */
	m->esi = 0x752ca4u;	/* 40b806: mov esi, 0x752ca4 */
L_40b80b:
	m->ecx = M32((DWORD)(0x4dbaa4u));	/* 40b80b: mov ecx, dword ptr [0x4dbaa4] */
	m->edx = M32((DWORD)(0x4dbaa0u));	/* 40b811: mov edx, dword ptr [0x4dbaa0] */
	m->eax = M32((DWORD)(0x4dba9cu));	/* 40b817: mov eax, dword ptr [0x4dba9c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b81c: push ecx */
	m->ecx = M32((DWORD)(0x4dba98u));	/* 40b81d: mov ecx, dword ptr [0x4dba98] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b823: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40b824: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b825: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b826: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40b830u; native_call(m, 0x41f0e0u);	/* 40b82b: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40b830: add esp, 0x14 */
	{ DWORD a_ = m->esi, b_ = 0x753024u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40b833: cmp esi, 0x753024 */
	if (m->zf || m->sf != m->of) goto L_40b85c;	/* 40b839: jle 0x40b85c */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b83b: push 0x3f800000 */
	{ DWORD v_ = 0x3f19999au; m->esp -= 4; M32(m->esp) = v_; }	/* 40b840: push 0x3f19999a */
	{ DWORD v_ = 0x3f19999au; m->esp -= 4; M32(m->esp) = v_; }	/* 40b845: push 0x3f19999a */
	{ DWORD v_ = 0x3f19999au; m->esp -= 4; M32(m->esp) = v_; }	/* 40b84a: push 0x3f19999a */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b84f: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40b859u; native_call(m, 0x41f0e0u);	/* 40b854: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40b859: add esp, 0x14 */
L_40b85c:
	m->edx = M32((DWORD)(0x4dbb04u));	/* 40b85c: mov edx, dword ptr [0x4dbb04] */
	m->ecx = M32((DWORD)(0x4dbb00u));	/* 40b862: mov ecx, dword ptr [0x4dbb00] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40b868: push esi */
	{ DWORD a_ = m->ecx, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40b869: add ecx, 0x40 */
	m->eax = (DWORD)(m->edi + m->edx*1 + 0x32u);	/* 40b86c: lea eax, [edi + edx + 0x32] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40b870: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b871: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40b877u; native_call(m, 0x402620u);	/* 40b872: call 0x402620 */
	{ DWORD a_ = m->esi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 40b877: add esi, 0x80 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40b87d: add esp, 0xc */
	{ DWORD a_ = m->edi, b_ = 0x22u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 40b880: add edi, 0x22 */
	{ DWORD a_ = m->esi, b_ = 0x7530a4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40b883: cmp esi, 0x7530a4 */
	if (m->sf != m->of) goto L_40b80b;	/* 40b889: jl 0x40b80b */
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40b88b: push 0x3ecccccd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b890: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b892: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b894: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b896: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40b8a0u; native_call(m, 0x41f0e0u);	/* 40b89b: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4dbb04u));	/* 40b8a0: mov ecx, dword ptr [0x4dbb04] */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 40b8a6: mov eax, dword ptr [0x4dbb00] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b8ab: push 1 */
	m->edx = (DWORD)(m->ecx + 0x45u);	/* 40b8ad: lea edx, [ecx + 0x45] */
	{ DWORD a_ = m->ecx, b_ = 0x2fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40b8b0: add ecx, 0x2f */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b8b3: push edx */
	m->edx = (DWORD)(m->eax + 0x1a7u);	/* 40b8b4: lea edx, [eax + 0x1a7] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b8ba: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40b8bb: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b8c0: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40b8c1: push eax */
	m->esp -= 4; M32(m->esp) = 0x40b8c7u; native_call(m, 0x427970u);	/* 40b8c2: call 0x427970 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b8c7: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b8cc: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b8d1: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b8d6: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b8d8: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40b8e2u; native_call(m, 0x41f0e0u);	/* 40b8dd: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4dbb04u));	/* 40b8e2: mov ecx, dword ptr [0x4dbb04] */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 40b8e8: mov eax, dword ptr [0x4dbb00] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b8ed: push 0 */
	m->edx = (DWORD)(m->ecx + 0x45u);	/* 40b8ef: lea edx, [ecx + 0x45] */
	{ DWORD a_ = m->ecx, b_ = 0x2fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40b8f2: add ecx, 0x2f */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b8f5: push edx */
	m->edx = (DWORD)(m->eax + 0x1a7u);	/* 40b8f6: lea edx, [eax + 0x1a7] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b8fc: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40b8fd: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b902: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40b903: push eax */
	m->esp -= 4; M32(m->esp) = 0x40b909u; native_call(m, 0x427970u);	/* 40b904: call 0x427970 */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40b909: add esp, 0x50 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b90c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b911: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b916: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b91b: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b920: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40b92au; native_call(m, 0x41f0e0u);	/* 40b925: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4dbab0u));	/* 40b92a: mov eax, dword ptr [0x4dbab0] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40b92f: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40b932: test eax, eax */
	if (!m->zf) goto L_40b959;	/* 40b934: jne 0x40b959 */
	m->eax = M32((DWORD)(0x4dbb04u));	/* 40b936: mov eax, dword ptr [0x4dbb04] */
	m->ecx = M32((DWORD)(0x4dbb00u));	/* 40b93b: mov ecx, dword ptr [0x4dbb00] */
	{ DWORD a_ = m->eax, b_ = 0x32u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40b941: add eax, 0x32 */
	{ DWORD v_ = 0x4db528u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b944: push 0x4db528 */
	{ DWORD a_ = m->ecx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40b949: add ecx, 0xa4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40b94f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b950: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40b956u; native_call(m, 0x402620u);	/* 40b951: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40b956: add esp, 0xc */
L_40b959:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40b959: push 0x3ecccccd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b95e: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b960: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b962: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b964: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40b96eu; native_call(m, 0x41f0e0u);	/* 40b969: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4dbb04u));	/* 40b96e: mov ecx, dword ptr [0x4dbb04] */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 40b974: mov eax, dword ptr [0x4dbb00] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b979: push 1 */
	m->edx = (DWORD)(m->ecx + 0x67u);	/* 40b97b: lea edx, [ecx + 0x67] */
	{ DWORD a_ = m->ecx, b_ = 0x51u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40b97e: add ecx, 0x51 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b981: push edx */
	m->edx = (DWORD)(m->eax + 0xefu);	/* 40b982: lea edx, [eax + 0xef] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b988: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40b989: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b98e: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40b98f: push eax */
	m->esp -= 4; M32(m->esp) = 0x40b995u; native_call(m, 0x427970u);	/* 40b990: call 0x427970 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b995: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b99a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b99f: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b9a4: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b9a6: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40b9b0u; native_call(m, 0x41f0e0u);	/* 40b9ab: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4dbb04u));	/* 40b9b0: mov ecx, dword ptr [0x4dbb04] */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 40b9b6: mov eax, dword ptr [0x4dbb00] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b9bb: push 0 */
	m->edx = (DWORD)(m->ecx + 0x67u);	/* 40b9bd: lea edx, [ecx + 0x67] */
	{ DWORD a_ = m->ecx, b_ = 0x51u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40b9c0: add ecx, 0x51 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b9c3: push edx */
	m->edx = (DWORD)(m->eax + 0xefu);	/* 40b9c4: lea edx, [eax + 0xef] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b9ca: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40b9cb: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b9d0: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40b9d1: push eax */
	m->esp -= 4; M32(m->esp) = 0x40b9d7u; native_call(m, 0x427970u);	/* 40b9d2: call 0x427970 */
	m->eax = M32((DWORD)(0x4dbaccu));	/* 40b9d7: mov eax, dword ptr [0x4dbacc] */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40b9dc: add esp, 0x50 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40b9df: test eax, eax */
	if (!m->zf) goto L_40ba3e;	/* 40b9e1: jne 0x40ba3e */
	m->edi = 0x4db54eu;	/* 40b9e3: mov edi, 0x4db54e */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40b9e8: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40b9eb: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 40b9ed: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 40b9ef: not ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 40b9f1: mov dword ptr [esp + 0x14], eax */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 40b9f5: dec ecx */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 40b9f6: mov dword ptr [esp + 0x18], eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40b9fa: test ecx, ecx */
	M16((DWORD)(m->esp + 0x1cu)) = (WORD)((m->eax & 0xffff));	/* 40b9fc: mov word ptr [esp + 0x1c], ax */
	if (m->zf || m->sf != m->of) goto L_40ba1a;	/* 40ba01: jle 0x40ba1a */
	m->edx = m->ecx;	/* 40ba03: mov edx, ecx */
	m->eax = 0x2a2a2a2au;	/* 40ba05: mov eax, 0x2a2a2a2a */
	m->edi = (DWORD)(m->esp + 0x14u);	/* 40ba0a: lea edi, [esp + 0x14] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 40ba0e: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 40ba11: rep stosd dword ptr es:[edi], eax */
	m->ecx = m->edx;	/* 40ba13: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40ba15: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1; m->ecx--; }	/* 40ba18: rep stosb byte ptr es:[edi], al */
L_40ba1a:
	m->ecx = M32((DWORD)(0x4dbb04u));	/* 40ba1a: mov ecx, dword ptr [0x4dbb04] */
	m->edx = M32((DWORD)(0x4dbb00u));	/* 40ba20: mov edx, dword ptr [0x4dbb00] */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 40ba26: lea eax, [esp + 0x14] */
	{ DWORD a_ = m->ecx, b_ = 0x54u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40ba2a: add ecx, 0x54 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40ba2d: push eax */
	{ DWORD a_ = m->edx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40ba2e: add edx, 0xa4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ba34: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ba35: push edx */
	m->esp -= 4; M32(m->esp) = 0x40ba3bu; native_call(m, 0x402620u);	/* 40ba36: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40ba3b: add esp, 0xc */
L_40ba3e:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40ba3e: push 0x3ecccccd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ba43: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ba45: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ba47: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ba49: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40ba53u; native_call(m, 0x41f0e0u);	/* 40ba4e: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4dbb04u));	/* 40ba53: mov ecx, dword ptr [0x4dbb04] */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 40ba59: mov eax, dword ptr [0x4dbb00] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ba5e: push 1 */
	m->edx = (DWORD)(m->ecx + 0x91u);	/* 40ba60: lea edx, [ecx + 0x91] */
	{ DWORD a_ = m->ecx, b_ = 0x6du & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40ba66: add ecx, 0x6d */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ba69: push edx */
	m->edx = (DWORD)(m->eax + 0x18fu);	/* 40ba6a: lea edx, [eax + 0x18f] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ba70: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40ba71: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ba76: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40ba77: push eax */
	m->esp -= 4; M32(m->esp) = 0x40ba7du; native_call(m, 0x427970u);	/* 40ba78: call 0x427970 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ba7d: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ba82: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ba87: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ba8c: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ba8e: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40ba98u; native_call(m, 0x41f0e0u);	/* 40ba93: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4dbb04u));	/* 40ba98: mov ecx, dword ptr [0x4dbb04] */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 40ba9e: mov eax, dword ptr [0x4dbb00] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40baa3: push 0 */
	m->edx = (DWORD)(m->ecx + 0x91u);	/* 40baa5: lea edx, [ecx + 0x91] */
	{ DWORD a_ = m->ecx, b_ = 0x6du & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40baab: add ecx, 0x6d */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40baae: push edx */
	m->edx = (DWORD)(m->eax + 0x18fu);	/* 40baaf: lea edx, [eax + 0x18f] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bab5: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40bab6: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40babb: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40babc: push eax */
	m->esp -= 4; M32(m->esp) = 0x40bac2u; native_call(m, 0x427970u);	/* 40babd: call 0x427970 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4db54au))) & 0xff) << 0);	/* 40bac2: mov al, byte ptr [0x4db54a] */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40bac7: add esp, 0x50 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40baca: test al, al */
	if (m->zf) goto L_40badd;	/* 40bacc: je 0x40badd */
	m->eax = M32((DWORD)(0x4dbb04u));	/* 40bace: mov eax, dword ptr [0x4dbb04] */
	{ DWORD v_ = 0x4ad56cu; m->esp -= 4; M32(m->esp) = v_; }	/* 40bad3: push 0x4ad56c */
	{ DWORD a_ = m->eax, b_ = 0x76u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40bad8: add eax, 0x76 */
	goto L_40baf9;	/* 40badb: jmp 0x40baf9 */
L_40badd:
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x4db548u)));	/* 40badd: movsx eax, byte ptr [0x4db548] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 40bae4: lea edx, [eax + eax*4] */
	m->eax = M32((DWORD)(0x4dbb04u));	/* 40bae7: mov eax, dword ptr [0x4dbb04] */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 40baec: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = 0x5ae9d0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40baef: add edx, 0x5ae9d0 */
	{ DWORD a_ = m->eax, b_ = 0x6fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40baf5: add eax, 0x6f */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40baf8: push edx */
L_40baf9:
	m->ecx = M32((DWORD)(0x4dbb00u));	/* 40baf9: mov ecx, dword ptr [0x4dbb00] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40baff: push eax */
	{ DWORD a_ = m->ecx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40bb00: add ecx, 0xa4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bb06: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40bb0cu; native_call(m, 0x402620u);	/* 40bb07: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40bb0c: add esp, 0xc */
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40bb0f: push 0x3ecccccd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bb14: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bb16: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bb18: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bb1a: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40bb24u; native_call(m, 0x41f0e0u);	/* 40bb1f: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4dbb04u));	/* 40bb24: mov ecx, dword ptr [0x4dbb04] */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 40bb2a: mov eax, dword ptr [0x4dbb00] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bb2f: push 1 */
	m->edx = (DWORD)(m->ecx + 0xabu);	/* 40bb31: lea edx, [ecx + 0xab] */
	{ DWORD a_ = m->ecx, b_ = 0x95u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40bb37: add ecx, 0x95 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bb3d: push edx */
	m->edx = (DWORD)(m->eax + 0xefu);	/* 40bb3e: lea edx, [eax + 0xef] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bb44: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40bb45: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bb4a: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40bb4b: push eax */
	m->esp -= 4; M32(m->esp) = 0x40bb51u; native_call(m, 0x427970u);	/* 40bb4c: call 0x427970 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bb51: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bb56: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bb5b: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bb60: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bb62: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40bb6cu; native_call(m, 0x41f0e0u);	/* 40bb67: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4dbb04u));	/* 40bb6c: mov ecx, dword ptr [0x4dbb04] */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 40bb72: mov eax, dword ptr [0x4dbb00] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bb77: push 0 */
	m->edx = (DWORD)(m->ecx + 0xabu);	/* 40bb79: lea edx, [ecx + 0xab] */
	{ DWORD a_ = m->ecx, b_ = 0x95u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40bb7f: add ecx, 0x95 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bb85: push edx */
	m->edx = (DWORD)(m->eax + 0xefu);	/* 40bb86: lea edx, [eax + 0xef] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bb8c: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40bb8d: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bb92: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40bb93: push eax */
	m->esp -= 4; M32(m->esp) = 0x40bb99u; native_call(m, 0x427970u);	/* 40bb94: call 0x427970 */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(0x4db549u)));	/* 40bb99: movsx ecx, byte ptr [0x4db549] */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40bba0: add esp, 0x50 */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 40bba3: lea eax, [esp + 0x14] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 40bba7: push 0xa */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40bba9: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bbaa: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40bbb0u; native_call(m, 0x49fb53u);	/* 40bbab: call 0x49fb53 */
	m->eax = M32((DWORD)(0x4dbb04u));	/* 40bbb0: mov eax, dword ptr [0x4dbb04] */
	m->ecx = M32((DWORD)(0x4dbb00u));	/* 40bbb5: mov ecx, dword ptr [0x4dbb00] */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 40bbbb: lea edx, [esp + 0x20] */
	{ DWORD a_ = m->eax, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40bbbf: add eax, 0x98 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bbc4: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40bbc5: add ecx, 0xa4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40bbcb: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bbcc: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40bbd2u; native_call(m, 0x402620u);	/* 40bbcd: call 0x402620 */
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40bbd2: push 0x3ecccccd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bbd7: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bbd9: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bbdb: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bbdd: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40bbe7u; native_call(m, 0x41f0e0u);	/* 40bbe2: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4dbb04u));	/* 40bbe7: mov ecx, dword ptr [0x4dbb04] */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 40bbed: mov eax, dword ptr [0x4dbb00] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bbf2: push 1 */
	m->edx = (DWORD)(m->ecx + 0xcdu);	/* 40bbf4: lea edx, [ecx + 0xcd] */
	{ DWORD a_ = m->ecx, b_ = 0xb7u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40bbfa: add ecx, 0xb7 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bc00: push edx */
	m->edx = (DWORD)(m->eax + 0xefu);	/* 40bc01: lea edx, [eax + 0xef] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bc07: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40bc08: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bc0d: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40bc0e: push eax */
	m->esp -= 4; M32(m->esp) = 0x40bc14u; native_call(m, 0x427970u);	/* 40bc0f: call 0x427970 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40bc14: add esp, 0x40 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bc17: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bc1c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bc21: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bc26: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bc28: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40bc32u; native_call(m, 0x41f0e0u);	/* 40bc2d: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4dbb04u));	/* 40bc32: mov ecx, dword ptr [0x4dbb04] */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 40bc38: mov eax, dword ptr [0x4dbb00] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bc3d: push 0 */
	m->edx = (DWORD)(m->ecx + 0xcdu);	/* 40bc3f: lea edx, [ecx + 0xcd] */
	{ DWORD a_ = m->ecx, b_ = 0xb7u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40bc45: add ecx, 0xb7 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bc4b: push edx */
	m->edx = (DWORD)(m->eax + 0xefu);	/* 40bc4c: lea edx, [eax + 0xef] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bc52: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40bc53: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bc58: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40bc59: push eax */
	m->esp -= 4; M32(m->esp) = 0x40bc5fu; native_call(m, 0x427970u);	/* 40bc5a: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bc5f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bc64: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bc69: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bc6e: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bc73: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40bc7du; native_call(m, 0x41f0e0u);	/* 40bc78: call 0x41f0e0 */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x4db54au)));	/* 40bc7d: movsx eax, byte ptr [0x4db54a] */
	m->edx = M32((DWORD)(0x4dbb04u));	/* 40bc84: mov edx, dword ptr [0x4dbb04] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 40bc8a: lea eax, [eax + eax*4] */
	{ DWORD a_ = m->edx, b_ = 0xbau & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40bc8d: add edx, 0xba */
	m->ecx = (DWORD)(m->eax*4 + 0x4dbba4u);	/* 40bc93: lea ecx, [eax*4 + 0x4dbba4] */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 40bc9a: mov eax, dword ptr [0x4dbb00] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bc9f: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40bca0: add eax, 0xa4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bca5: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40bca6: push eax */
	m->esp -= 4; M32(m->esp) = 0x40bcacu; native_call(m, 0x402620u);	/* 40bca7: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40bcac: add esp, 0x48 */
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40bcaf: push 0x3ecccccd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bcb4: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bcb6: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bcb8: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bcba: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40bcc4u; native_call(m, 0x41f0e0u);	/* 40bcbf: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4dbb04u));	/* 40bcc4: mov ecx, dword ptr [0x4dbb04] */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 40bcca: mov eax, dword ptr [0x4dbb00] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bccf: push 1 */
	m->edx = (DWORD)(m->ecx + 0xefu);	/* 40bcd1: lea edx, [ecx + 0xef] */
	{ DWORD a_ = m->ecx, b_ = 0xd9u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40bcd7: add ecx, 0xd9 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bcdd: push edx */
	m->edx = (DWORD)(m->eax + 0x18fu);	/* 40bcde: lea edx, [eax + 0x18f] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bce4: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40bce5: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bcea: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40bceb: push eax */
	m->esp -= 4; M32(m->esp) = 0x40bcf1u; native_call(m, 0x427970u);	/* 40bcec: call 0x427970 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bcf1: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bcf6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bcfb: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bd00: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bd02: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40bd0cu; native_call(m, 0x41f0e0u);	/* 40bd07: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4dbb04u));	/* 40bd0c: mov ecx, dword ptr [0x4dbb04] */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 40bd12: mov eax, dword ptr [0x4dbb00] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bd17: push 0 */
	m->edx = (DWORD)(m->ecx + 0xefu);	/* 40bd19: lea edx, [ecx + 0xef] */
	{ DWORD a_ = m->ecx, b_ = 0xd9u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40bd1f: add ecx, 0xd9 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bd25: push edx */
	m->edx = (DWORD)(m->eax + 0x18fu);	/* 40bd26: lea edx, [eax + 0x18f] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bd2c: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40bd2d: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bd32: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40bd33: push eax */
	m->esp -= 4; M32(m->esp) = 0x40bd39u; native_call(m, 0x427970u);	/* 40bd34: call 0x427970 */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40bd39: add esp, 0x50 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bd3c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bd41: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bd46: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bd4b: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bd50: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40bd5au; native_call(m, 0x41f0e0u);	/* 40bd55: call 0x41f0e0 */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x4db54bu)));	/* 40bd5a: movsx eax, byte ptr [0x4db54b] */
	m->ecx = M32((DWORD)(0x4dbb04u));	/* 40bd61: mov ecx, dword ptr [0x4dbb04] */
	{ DWORD a_ = m->eax, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 40bd67: shl eax, 7 */
	{ DWORD a_ = m->eax, b_ = 0x75c9a4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40bd6a: add eax, 0x75c9a4 */
	{ DWORD a_ = m->ecx, b_ = 0xdcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40bd6f: add ecx, 0xdc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40bd75: push eax */
	m->edx = M32((DWORD)(0x4dbb00u));	/* 40bd76: mov edx, dword ptr [0x4dbb00] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bd7c: push ecx */
	{ DWORD a_ = m->edx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40bd7d: add edx, 0xa4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bd83: push edx */
	m->esp -= 4; M32(m->esp) = 0x40bd89u; native_call(m, 0x402620u);	/* 40bd84: call 0x402620 */
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40bd89: push 0x3ecccccd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bd8e: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bd90: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bd92: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bd94: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40bd9eu; native_call(m, 0x41f0e0u);	/* 40bd99: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4dbb04u));	/* 40bd9e: mov ecx, dword ptr [0x4dbb04] */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 40bda4: mov eax, dword ptr [0x4dbb00] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bda9: push 1 */
	m->edx = (DWORD)(m->ecx + 0x111u);	/* 40bdab: lea edx, [ecx + 0x111] */
	{ DWORD a_ = m->ecx, b_ = 0xfbu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40bdb1: add ecx, 0xfb */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bdb7: push edx */
	m->edx = (DWORD)(m->eax + 0xefu);	/* 40bdb8: lea edx, [eax + 0xef] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bdbe: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40bdbf: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bdc4: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40bdc5: push eax */
	m->esp -= 4; M32(m->esp) = 0x40bdcbu; native_call(m, 0x427970u);	/* 40bdc6: call 0x427970 */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40bdcb: add esp, 0x48 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bdce: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bdd3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bdd8: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bddd: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bddf: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40bde9u; native_call(m, 0x41f0e0u);	/* 40bde4: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4dbb04u));	/* 40bde9: mov ecx, dword ptr [0x4dbb04] */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 40bdef: mov eax, dword ptr [0x4dbb00] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bdf4: push 0 */
	m->edx = (DWORD)(m->ecx + 0x111u);	/* 40bdf6: lea edx, [ecx + 0x111] */
	{ DWORD a_ = m->ecx, b_ = 0xfbu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40bdfc: add ecx, 0xfb */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40be02: push edx */
	m->edx = (DWORD)(m->eax + 0xefu);	/* 40be03: lea edx, [eax + 0xef] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40be09: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40be0a: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40be0f: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40be10: push eax */
	m->esp -= 4; M32(m->esp) = 0x40be16u; native_call(m, 0x427970u);	/* 40be11: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40be16: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40be1b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40be20: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40be25: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40be2a: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40be34u; native_call(m, 0x41f0e0u);	/* 40be2f: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4db850u));	/* 40be34: mov eax, dword ptr [0x4db850] */
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40be39: add esp, 0x3c */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40be3c: test eax, eax */
	if (!m->zf) goto L_40be7e;	/* 40be3e: jne 0x40be7e */
	m->ecx = M32((DWORD)(0x4db54cu));	/* 40be40: mov ecx, dword ptr [0x4db54c] */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 40be46: lea eax, [esp + 0x14] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 40be4a: push 0xa */
	{ DWORD a_ = m->ecx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40be4c: and ecx, 0xff */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40be52: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40be53: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40be59u; native_call(m, 0x49fb53u);	/* 40be54: call 0x49fb53 */
	m->eax = M32((DWORD)(0x4dbb04u));	/* 40be59: mov eax, dword ptr [0x4dbb04] */
	m->ecx = M32((DWORD)(0x4dbb00u));	/* 40be5e: mov ecx, dword ptr [0x4dbb00] */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 40be64: lea edx, [esp + 0x20] */
	{ DWORD a_ = m->eax, b_ = 0xfeu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40be68: add eax, 0xfe */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40be6d: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40be6e: add ecx, 0xa4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40be74: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40be75: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40be7bu; native_call(m, 0x402620u);	/* 40be76: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40be7b: add esp, 0x18 */
L_40be7e:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40be7e: push 0x3ecccccd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40be83: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40be85: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40be87: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40be89: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40be93u; native_call(m, 0x41f0e0u);	/* 40be8e: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4dbb04u));	/* 40be93: mov ecx, dword ptr [0x4dbb04] */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 40be99: mov eax, dword ptr [0x4dbb00] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40be9e: push 1 */
	m->edx = (DWORD)(m->ecx + 0x133u);	/* 40bea0: lea edx, [ecx + 0x133] */
	{ DWORD a_ = m->ecx, b_ = 0x11du & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40bea6: add ecx, 0x11d */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40beac: push edx */
	m->edx = (DWORD)(m->eax + 0xefu);	/* 40bead: lea edx, [eax + 0xef] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40beb3: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40beb4: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40beb9: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40beba: push eax */
	m->esp -= 4; M32(m->esp) = 0x40bec0u; native_call(m, 0x427970u);	/* 40bebb: call 0x427970 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bec0: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bec5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40beca: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40becf: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bed1: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40bedbu; native_call(m, 0x41f0e0u);	/* 40bed6: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4dbb04u));	/* 40bedb: mov ecx, dword ptr [0x4dbb04] */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 40bee1: mov eax, dword ptr [0x4dbb00] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bee6: push 0 */
	m->edx = (DWORD)(m->ecx + 0x133u);	/* 40bee8: lea edx, [ecx + 0x133] */
	{ DWORD a_ = m->ecx, b_ = 0x11du & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40beee: add ecx, 0x11d */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bef4: push edx */
	m->edx = (DWORD)(m->eax + 0xefu);	/* 40bef5: lea edx, [eax + 0xef] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40befb: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40befc: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bf01: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40bf02: push eax */
	m->esp -= 4; M32(m->esp) = 0x40bf08u; native_call(m, 0x427970u);	/* 40bf03: call 0x427970 */
	m->eax = M32((DWORD)(0x4db518u));	/* 40bf08: mov eax, dword ptr [0x4db518] */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40bf0d: add esp, 0x50 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40bf10: test eax, eax */
	if (!m->zf) goto L_40bf4e;	/* 40bf12: jne 0x40bf4e */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40bf14: xor ecx, ecx */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 40bf16: lea eax, [esp + 0x14] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x4db54du))) & 0xff) << 0);	/* 40bf1a: mov cl, byte ptr [0x4db54d] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 40bf20: push 0xa */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40bf22: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bf23: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40bf29u; native_call(m, 0x49fb53u);	/* 40bf24: call 0x49fb53 */
	m->eax = M32((DWORD)(0x4dbb04u));	/* 40bf29: mov eax, dword ptr [0x4dbb04] */
	m->ecx = M32((DWORD)(0x4dbb00u));	/* 40bf2e: mov ecx, dword ptr [0x4dbb00] */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 40bf34: lea edx, [esp + 0x20] */
	{ DWORD a_ = m->eax, b_ = 0x120u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40bf38: add eax, 0x120 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bf3d: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40bf3e: add ecx, 0xa4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40bf44: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bf45: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40bf4bu; native_call(m, 0x402620u);	/* 40bf46: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40bf4b: add esp, 0x18 */
L_40bf4e:
	m->eax = M32((DWORD)(0x68039cu));	/* 40bf4e: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40bf53: test eax, eax */
	if (!m->zf) goto L_40c453;	/* 40bf55: jne 0x40c453 */
	m->eax = M32((DWORD)(0x4db55cu));	/* 40bf5b: mov eax, dword ptr [0x4db55c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40bf60: test eax, eax */
	if (!m->zf) goto L_40c453;	/* 40bf62: jne 0x40c453 */
	m->eax = M32((DWORD)(0x907b2cu));	/* 40bf68: mov eax, dword ptr [0x907b2c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40bf6d: test eax, eax */
	if (!m->zf) goto L_40c453;	/* 40bf6f: jne 0x40c453 */
	m->eax = M32((DWORD)(0x4db508u));	/* 40bf75: mov eax, dword ptr [0x4db508] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40bf7a: test eax, eax */
	if (!m->zf) goto L_40c453;	/* 40bf7c: jne 0x40c453 */
	{ DWORD a_ = m->ebx, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40bf82: cmp ebx, 7 */
	if (!m->cf && !m->zf) goto L_40c453;	/* 40bf85: ja 0x40c453 */
	switch (m->ebx) { case 0: goto L_40bf92; case 1: goto L_40bffd; case 2: goto L_40c0a1; case 3: goto L_40c14d; case 4: goto L_40c1d3; case 5: goto L_40c274; case 6: goto L_40c31e; case 7: goto L_40c3bb; default: abort(); }	/* 40bf8b: jmp dword ptr [ebx*4 + 0x40ce50] */
L_40bf92:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bf92: push 0x3f800000 */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 40bf97: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 40bf9c: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 40bfa1: push 0x3c23d70a */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bfa6: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40bfb0u; native_call(m, 0x41f0e0u);	/* 40bfab: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x4dbb04u));	/* 40bfb0: mov edx, dword ptr [0x4dbb04] */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 40bfb6: mov eax, dword ptr [0x4dbb00] */
	{ DWORD a_ = m->edx, b_ = 0x32u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40bfbb: add edx, 0x32 */
	{ DWORD v_ = 0x4db528u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bfbe: push 0x4db528 */
	{ DWORD a_ = m->eax, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40bfc3: add eax, 0xa4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40bfc8: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40bfc9: push eax */
	m->esp -= 4; M32(m->esp) = 0x40bfcfu; native_call(m, 0x402620u);	/* 40bfca: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bfcf: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bfd4: push 0 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40bfd6: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bfdb: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bfe0: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40bfeau; native_call(m, 0x41f0e0u);	/* 40bfe5: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4dbb04u));	/* 40bfea: mov ecx, dword ptr [0x4dbb04] */
	{ DWORD v_ = 0x4db528u; m->esp -= 4; M32(m->esp) = v_; }	/* 40bff0: push 0x4db528 */
	{ DWORD a_ = m->ecx, b_ = 0x31u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40bff5: add ecx, 0x31 */
	goto L_40c132;	/* 40bff8: jmp 0x40c132 */
L_40bffd:
	m->edi = 0x4db54eu;	/* 40bffd: mov edi, 0x4db54e */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40c002: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40c005: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 40c007: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 40c009: not ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 40c00b: mov dword ptr [esp + 0x14], eax */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 40c00f: dec ecx */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 40c010: mov dword ptr [esp + 0x18], eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40c014: test ecx, ecx */
	M16((DWORD)(m->esp + 0x1cu)) = (WORD)((m->eax & 0xffff));	/* 40c016: mov word ptr [esp + 0x1c], ax */
	if (m->zf || m->sf != m->of) goto L_40c034;	/* 40c01b: jle 0x40c034 */
	m->edx = m->ecx;	/* 40c01d: mov edx, ecx */
	m->eax = 0x2a2a2a2au;	/* 40c01f: mov eax, 0x2a2a2a2a */
	m->edi = (DWORD)(m->esp + 0x14u);	/* 40c024: lea edi, [esp + 0x14] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 40c028: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 40c02b: rep stosd dword ptr es:[edi], eax */
	m->ecx = m->edx;	/* 40c02d: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40c02f: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1; m->ecx--; }	/* 40c032: rep stosb byte ptr es:[edi], al */
L_40c034:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c034: push 0x3f800000 */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 40c039: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 40c03e: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 40c043: push 0x3c23d70a */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c048: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40c052u; native_call(m, 0x41f0e0u);	/* 40c04d: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4dbb04u));	/* 40c052: mov ecx, dword ptr [0x4dbb04] */
	m->edx = M32((DWORD)(0x4dbb00u));	/* 40c058: mov edx, dword ptr [0x4dbb00] */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 40c05e: lea eax, [esp + 0x28] */
	{ DWORD a_ = m->ecx, b_ = 0x54u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40c062: add ecx, 0x54 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c065: push eax */
	{ DWORD a_ = m->edx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40c066: add edx, 0xa4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c06c: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c06d: push edx */
	m->esp -= 4; M32(m->esp) = 0x40c073u; native_call(m, 0x402620u);	/* 40c06e: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c073: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c078: push 0 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40c07a: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c07f: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c084: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40c08eu; native_call(m, 0x41f0e0u);	/* 40c089: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4dbb04u));	/* 40c08e: mov ecx, dword ptr [0x4dbb04] */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 40c094: lea eax, [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c098: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x53u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40c099: add ecx, 0x53 */
	goto L_40c132;	/* 40c09c: jmp 0x40c132 */
L_40c0a1:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4db54au))) & 0xff) << 0);	/* 40c0a1: mov al, byte ptr [0x4db54a] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40c0a6: test al, al */
	if (!m->zf) goto L_40c453;	/* 40c0a8: jne 0x40c453 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c0ae: push 0x3f800000 */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 40c0b3: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 40c0b8: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 40c0bd: push 0x3c23d70a */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c0c2: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40c0ccu; native_call(m, 0x41f0e0u);	/* 40c0c7: call 0x41f0e0 */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x4db548u)));	/* 40c0cc: movsx eax, byte ptr [0x4db548] */
	m->ecx = M32((DWORD)(0x4dbb04u));	/* 40c0d3: mov ecx, dword ptr [0x4dbb04] */
	m->edx = M32((DWORD)(0x4dbb00u));	/* 40c0d9: mov edx, dword ptr [0x4dbb00] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 40c0df: lea eax, [eax + eax*4] */
	{ DWORD a_ = m->ecx, b_ = 0x6fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40c0e2: add ecx, 0x6f */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 40c0e5: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = 0x5ae9d0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40c0e8: add eax, 0x5ae9d0 */
	{ DWORD a_ = m->edx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40c0ed: add edx, 0xa4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c0f3: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c0f4: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c0f5: push edx */
	m->esp -= 4; M32(m->esp) = 0x40c0fbu; native_call(m, 0x402620u);	/* 40c0f6: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c0fb: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c100: push 0 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40c102: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c107: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c10c: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40c116u; native_call(m, 0x41f0e0u);	/* 40c111: call 0x41f0e0 */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x4db548u)));	/* 40c116: movsx eax, byte ptr [0x4db548] */
	m->ecx = M32((DWORD)(0x4dbb04u));	/* 40c11d: mov ecx, dword ptr [0x4dbb04] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 40c123: lea eax, [eax + eax*4] */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 40c126: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = 0x5ae9d0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40c129: add eax, 0x5ae9d0 */
	{ DWORD a_ = m->ecx, b_ = 0x6eu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40c12e: add ecx, 0x6e */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c131: push eax */
L_40c132:
	m->edx = M32((DWORD)(0x4dbb00u));	/* 40c132: mov edx, dword ptr [0x4dbb00] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c138: push ecx */
	{ DWORD a_ = m->edx, b_ = 0xa3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40c139: add edx, 0xa3 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c13f: push edx */
	m->esp -= 4; M32(m->esp) = 0x40c145u; native_call(m, 0x402620u);	/* 40c140: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40c145: add esp, 0x40 */
	goto L_40c453;	/* 40c148: jmp 0x40c453 */
L_40c14d:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c14d: push 0x3f800000 */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 40c152: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 40c157: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 40c15c: push 0x3c23d70a */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c161: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40c16bu; native_call(m, 0x41f0e0u);	/* 40c166: call 0x41f0e0 */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(0x4db549u)));	/* 40c16b: movsx ecx, byte ptr [0x4db549] */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 40c172: lea eax, [esp + 0x28] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 40c176: push 0xa */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c178: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c179: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40c17fu; native_call(m, 0x49fb53u);	/* 40c17a: call 0x49fb53 */
	m->eax = M32((DWORD)(0x4dbb04u));	/* 40c17f: mov eax, dword ptr [0x4dbb04] */
	m->ecx = M32((DWORD)(0x4dbb00u));	/* 40c184: mov ecx, dword ptr [0x4dbb00] */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 40c18a: lea edx, [esp + 0x34] */
	{ DWORD a_ = m->eax, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40c18e: add eax, 0x98 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c193: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40c194: add ecx, 0xa4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c19a: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c19b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40c1a1u; native_call(m, 0x402620u);	/* 40c19c: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c1a1: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c1a6: push 0 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40c1a8: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c1ad: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c1b2: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40c1bcu; native_call(m, 0x41f0e0u);	/* 40c1b7: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4dbb04u));	/* 40c1bc: mov eax, dword ptr [0x4dbb04] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40c1c1: add esp, 0x40 */
	m->edx = (DWORD)(m->esp + 0x14u);	/* 40c1c4: lea edx, [esp + 0x14] */
	{ DWORD a_ = m->eax, b_ = 0x97u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40c1c8: add eax, 0x97 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c1cd: push edx */
	goto L_40c43d;	/* 40c1ce: jmp 0x40c43d */
L_40c1d3:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c1d3: push 0x3f800000 */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 40c1d8: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 40c1dd: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 40c1e2: push 0x3c23d70a */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c1e7: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40c1f1u; native_call(m, 0x41f0e0u);	/* 40c1ec: call 0x41f0e0 */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x4db54au)));	/* 40c1f1: movsx eax, byte ptr [0x4db54a] */
	m->ecx = M32((DWORD)(0x4dbb04u));	/* 40c1f8: mov ecx, dword ptr [0x4dbb04] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 40c1fe: lea edx, [eax + eax*4] */
	{ DWORD a_ = m->ecx, b_ = 0xbau & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40c201: add ecx, 0xba */
	m->eax = (DWORD)(m->edx*4 + 0x4dbba4u);	/* 40c207: lea eax, [edx*4 + 0x4dbba4] */
	m->edx = M32((DWORD)(0x4dbb00u));	/* 40c20e: mov edx, dword ptr [0x4dbb00] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c214: push eax */
	{ DWORD a_ = m->edx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40c215: add edx, 0xa4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c21b: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c21c: push edx */
	m->esp -= 4; M32(m->esp) = 0x40c222u; native_call(m, 0x402620u);	/* 40c21d: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c222: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c227: push 0 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40c229: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c22e: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c233: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40c23du; native_call(m, 0x41f0e0u);	/* 40c238: call 0x41f0e0 */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x4db54au)));	/* 40c23d: movsx eax, byte ptr [0x4db54a] */
	m->edx = M32((DWORD)(0x4dbb04u));	/* 40c244: mov edx, dword ptr [0x4dbb04] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 40c24a: lea eax, [eax + eax*4] */
	{ DWORD a_ = m->edx, b_ = 0xb9u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40c24d: add edx, 0xb9 */
	m->ecx = (DWORD)(m->eax*4 + 0x4dbba4u);	/* 40c253: lea ecx, [eax*4 + 0x4dbba4] */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 40c25a: mov eax, dword ptr [0x4dbb00] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c25f: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xa3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40c260: add eax, 0xa3 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c265: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c266: push eax */
	m->esp -= 4; M32(m->esp) = 0x40c26cu; native_call(m, 0x402620u);	/* 40c267: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40c26c: add esp, 0x40 */
	goto L_40c453;	/* 40c26f: jmp 0x40c453 */
L_40c274:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4db54au))) & 0xff) << 0);	/* 40c274: mov al, byte ptr [0x4db54a] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40c279: test al, al */
	if (!m->zf) goto L_40c453;	/* 40c27b: jne 0x40c453 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c281: push 0x3f800000 */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 40c286: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 40c28b: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 40c290: push 0x3c23d70a */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c295: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40c29fu; native_call(m, 0x41f0e0u);	/* 40c29a: call 0x41f0e0 */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(0x4db54bu)));	/* 40c29f: movsx ecx, byte ptr [0x4db54b] */
	m->edx = M32((DWORD)(0x4dbb04u));	/* 40c2a6: mov edx, dword ptr [0x4dbb04] */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 40c2ac: mov eax, dword ptr [0x4dbb00] */
	{ DWORD a_ = m->ecx, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 40c2b1: shl ecx, 7 */
	{ DWORD a_ = m->ecx, b_ = 0x75c9a4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40c2b4: add ecx, 0x75c9a4 */
	{ DWORD a_ = m->edx, b_ = 0xdcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40c2ba: add edx, 0xdc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c2c0: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40c2c1: add eax, 0xa4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c2c6: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c2c7: push eax */
	m->esp -= 4; M32(m->esp) = 0x40c2cdu; native_call(m, 0x402620u);	/* 40c2c8: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c2cd: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c2d2: push 0 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40c2d4: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c2d9: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c2de: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40c2e8u; native_call(m, 0x41f0e0u);	/* 40c2e3: call 0x41f0e0 */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(0x4db54bu)));	/* 40c2e8: movsx ecx, byte ptr [0x4db54b] */
	m->edx = M32((DWORD)(0x4dbb04u));	/* 40c2ef: mov edx, dword ptr [0x4dbb04] */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 40c2f5: mov eax, dword ptr [0x4dbb00] */
	{ DWORD a_ = m->ecx, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 40c2fa: shl ecx, 7 */
	{ DWORD a_ = m->ecx, b_ = 0x75c9a4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40c2fd: add ecx, 0x75c9a4 */
	{ DWORD a_ = m->edx, b_ = 0xdbu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40c303: add edx, 0xdb */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c309: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xa3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40c30a: add eax, 0xa3 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c30f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c310: push eax */
	m->esp -= 4; M32(m->esp) = 0x40c316u; native_call(m, 0x402620u);	/* 40c311: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40c316: add esp, 0x40 */
	goto L_40c453;	/* 40c319: jmp 0x40c453 */
L_40c31e:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c31e: push 0x3f800000 */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 40c323: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 40c328: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 40c32d: push 0x3c23d70a */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c332: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40c33cu; native_call(m, 0x41f0e0u);	/* 40c337: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x4db54cu));	/* 40c33c: mov edx, dword ptr [0x4db54c] */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 40c342: lea ecx, [esp + 0x28] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 40c346: push 0xa */
	{ DWORD a_ = m->edx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 40c348: and edx, 0xff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c34e: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c34f: push edx */
	m->esp -= 4; M32(m->esp) = 0x40c355u; native_call(m, 0x49fb53u);	/* 40c350: call 0x49fb53 */
	m->ecx = M32((DWORD)(0x4dbb04u));	/* 40c355: mov ecx, dword ptr [0x4dbb04] */
	m->edx = M32((DWORD)(0x4dbb00u));	/* 40c35b: mov edx, dword ptr [0x4dbb00] */
	m->eax = (DWORD)(m->esp + 0x34u);	/* 40c361: lea eax, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0xfeu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40c365: add ecx, 0xfe */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c36b: push eax */
	{ DWORD a_ = m->edx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40c36c: add edx, 0xa4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c372: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c373: push edx */
	m->esp -= 4; M32(m->esp) = 0x40c379u; native_call(m, 0x402620u);	/* 40c374: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c379: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c37e: push 0 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40c380: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c385: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c38a: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40c394u; native_call(m, 0x41f0e0u);	/* 40c38f: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4dbb04u));	/* 40c394: mov ecx, dword ptr [0x4dbb04] */
	m->edx = M32((DWORD)(0x4dbb00u));	/* 40c39a: mov edx, dword ptr [0x4dbb00] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40c3a0: add esp, 0x40 */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 40c3a3: lea eax, [esp + 0x14] */
	{ DWORD a_ = m->ecx, b_ = 0xfdu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40c3a7: add ecx, 0xfd */
	{ DWORD a_ = m->edx, b_ = 0xa3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40c3ad: add edx, 0xa3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c3b3: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c3b4: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c3b5: push edx */
	goto L_40c44b;	/* 40c3b6: jmp 0x40c44b */
L_40c3bb:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c3bb: push 0x3f800000 */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 40c3c0: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 40c3c5: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 40c3ca: push 0x3c23d70a */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c3cf: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40c3d9u; native_call(m, 0x41f0e0u);	/* 40c3d4: call 0x41f0e0 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40c3d9: xor ecx, ecx */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 40c3db: lea eax, [esp + 0x28] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x4db54du))) & 0xff) << 0);	/* 40c3df: mov cl, byte ptr [0x4db54d] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 40c3e5: push 0xa */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c3e7: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c3e8: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40c3eeu; native_call(m, 0x49fb53u);	/* 40c3e9: call 0x49fb53 */
	m->eax = M32((DWORD)(0x4dbb04u));	/* 40c3ee: mov eax, dword ptr [0x4dbb04] */
	m->ecx = M32((DWORD)(0x4dbb00u));	/* 40c3f3: mov ecx, dword ptr [0x4dbb00] */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 40c3f9: lea edx, [esp + 0x34] */
	{ DWORD a_ = m->eax, b_ = 0x120u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40c3fd: add eax, 0x120 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c402: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40c403: add ecx, 0xa4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c409: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c40a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40c410u; native_call(m, 0x402620u);	/* 40c40b: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c410: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c415: push 0 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40c417: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c41c: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c421: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40c42bu; native_call(m, 0x41f0e0u);	/* 40c426: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4dbb04u));	/* 40c42b: mov eax, dword ptr [0x4dbb04] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40c430: add esp, 0x40 */
	m->edx = (DWORD)(m->esp + 0x14u);	/* 40c433: lea edx, [esp + 0x14] */
	{ DWORD a_ = m->eax, b_ = 0x11fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40c437: add eax, 0x11f */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c43c: push edx */
L_40c43d:
	m->ecx = M32((DWORD)(0x4dbb00u));	/* 40c43d: mov ecx, dword ptr [0x4dbb00] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c443: push eax */
	{ DWORD a_ = m->ecx, b_ = 0xa3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40c444: add ecx, 0xa3 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c44a: push ecx */
L_40c44b:
	m->esp -= 4; M32(m->esp) = 0x40c450u; native_call(m, 0x402620u);	/* 40c44b: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40c450: add esp, 0xc */
L_40c453:
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 40c453: xor edi, edi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 40c455: xor esi, esi */
	m->ebx = 0x7530a4u;	/* 40c457: mov ebx, 0x7530a4 */
L_40c45c:
	m->ebp = M32((DWORD)(0x4a9224u));	/* 40c45c: mov ebp, dword ptr [0x4a9224] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c462: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x40c469u; native_call(m, m->ebp);	/* 40c467: call ebp */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 40c469: mov eax, dword ptr [0x9db0a4] */
	m->edx = m->eax;	/* 40c46e: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 40c470: and edx, 0x800001ff */
	if (!m->sf) goto L_40c480;	/* 40c476: jns 0x40c480 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 40c478: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 40c479: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 40c47f: inc edx */
L_40c480:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c480: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 40c481: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 40c487: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 40c488: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40c48e: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 40c490: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 40c493: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x40c49cu; native_call(m, 0x4566c0u);	/* 40c497: call 0x4566c0 */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 40c49c: mov eax, dword ptr [esp + 0x10] */
	m->edx = (DWORD)(m->edi + 0x8u);	/* 40c4a0: lea edx, [edi + 8] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40c4a3: cmp eax, edx */
	if (!m->zf) goto L_40c52c;	/* 40c4a5: jne 0x40c52c */
	m->eax = M32((DWORD)(0x68039cu));	/* 40c4ab: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40c4b0: test eax, eax */
	if (!m->zf) goto L_40c52c;	/* 40c4b2: jne 0x40c52c */
	m->eax = M32((DWORD)(0x4db55cu));	/* 40c4b4: mov eax, dword ptr [0x4db55c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40c4b9: test eax, eax */
	if (!m->zf) goto L_40c52c;	/* 40c4bb: jne 0x40c52c */
	m->eax = M32((DWORD)(0x907b2cu));	/* 40c4bd: mov eax, dword ptr [0x907b2c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40c4c2: test eax, eax */
	if (!m->zf) goto L_40c52c;	/* 40c4c4: jne 0x40c52c */
	m->eax = M32((DWORD)(0x4db508u));	/* 40c4c6: mov eax, dword ptr [0x4db508] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40c4cb: test eax, eax */
	if (!m->zf) goto L_40c52c;	/* 40c4cd: jne 0x40c52c */
	{ DWORD v_ = 0x3f666666u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c4cf: push 0x3f666666 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c4d4: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c4d9: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c4de: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40c4e9u; native_call(m, M32(0x4a9228u));	/* 40c4e3: call dword ptr [0x4a9228] */
	m->ecx = M32((DWORD)(0x4dbb0cu));	/* 40c4e9: mov ecx, dword ptr [0x4dbb0c] */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 40c4ef: mov eax, dword ptr [0x4dbb00] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c4f4: push 1 */
	m->edx = (DWORD)(m->ecx + 0xffffffc6u);	/* 40c4f6: lea edx, [ecx - 0x3a] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffa6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40c4f9: add ecx, -0x5a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c4fc: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x104u);	/* 40c4fd: lea edx, [esi + eax + 0x104] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c504: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x3cu);	/* 40c505: lea eax, [esi + eax + 0x3c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c509: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c50a: push eax */
	m->esp -= 4; M32(m->esp) = 0x40c510u; native_call(m, 0x4282f0u);	/* 40c50b: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x4dbaa4u));	/* 40c510: mov ecx, dword ptr [0x4dbaa4] */
	m->edx = M32((DWORD)(0x4dbaa0u));	/* 40c516: mov edx, dword ptr [0x4dbaa0] */
	m->eax = M32((DWORD)(0x4dba9cu));	/* 40c51c: mov eax, dword ptr [0x4dba9c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c521: push ecx */
	m->ecx = M32((DWORD)(0x4dba98u));	/* 40c522: mov ecx, dword ptr [0x4dba98] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c528: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c529: push eax */
	goto L_40c587;	/* 40c52a: jmp 0x40c587 */
L_40c52c:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40c52c: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c531: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c536: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c53b: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40c546u; native_call(m, M32(0x4a9228u));	/* 40c540: call dword ptr [0x4a9228] */
	m->ecx = M32((DWORD)(0x4dbb0cu));	/* 40c546: mov ecx, dword ptr [0x4dbb0c] */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 40c54c: mov eax, dword ptr [0x4dbb00] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c551: push 1 */
	m->edx = (DWORD)(m->ecx + 0xffffffc6u);	/* 40c553: lea edx, [ecx - 0x3a] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffa6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40c556: add ecx, -0x5a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c559: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x104u);	/* 40c55a: lea edx, [esi + eax + 0x104] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c561: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x3cu);	/* 40c562: lea eax, [esi + eax + 0x3c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c566: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c567: push eax */
	m->esp -= 4; M32(m->esp) = 0x40c56du; native_call(m, 0x4282f0u);	/* 40c568: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x4db8acu));	/* 40c56d: mov ecx, dword ptr [0x4db8ac] */
	m->edx = M32((DWORD)(0x4db8a8u));	/* 40c573: mov edx, dword ptr [0x4db8a8] */
	m->eax = M32((DWORD)(0x4db8a4u));	/* 40c579: mov eax, dword ptr [0x4db8a4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c57e: push ecx */
	m->ecx = M32((DWORD)(0x4db8a0u));	/* 40c57f: mov ecx, dword ptr [0x4db8a0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c585: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c586: push eax */
L_40c587:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c587: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c588: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40c592u; native_call(m, 0x41f0e0u);	/* 40c58d: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 40c592: mov eax, dword ptr [0x4dbb00] */
	m->ecx = M32((DWORD)(0x4dbb0cu));	/* 40c597: mov ecx, dword ptr [0x4dbb0c] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40c59d: add esp, 0x28 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffaeu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40c5a0: add ecx, -0x52 */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x104u);	/* 40c5a3: lea edx, [esi + eax + 0x104] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c5aa: push ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c5ab: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x3cu);	/* 40c5ac: lea edx, [esi + eax + 0x3c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c5b0: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c5b1: push edx */
	m->esp -= 4; M32(m->esp) = 0x40c5b7u; native_call(m, 0x4029d0u);	/* 40c5b2: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40c5b7: add esp, 0x10 */
	{ DWORD a_ = m->ebx, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 40c5ba: add ebx, 0x80 */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 40c5c0: inc edi */
	{ DWORD a_ = m->esi, b_ = 0xfau & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 40c5c1: add esi, 0xfa */
	{ DWORD a_ = m->ebx, b_ = 0x7531a4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40c5c7: cmp ebx, 0x7531a4 */
	if (m->sf != m->of) goto L_40c45c;	/* 40c5cd: jl 0x40c45c */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 40c5d3: xor edi, edi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 40c5d5: xor esi, esi */
	m->ebx = 0x7531a4u;	/* 40c5d7: mov ebx, 0x7531a4 */
L_40c5dc:
	{ DWORD a_ = m->ebx, b_ = 0x7531a4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40c5dc: cmp ebx, 0x7531a4 */
	if (m->zf) goto L_40c740;	/* 40c5e2: je 0x40c740 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c5e8: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x40c5efu; native_call(m, m->ebp);	/* 40c5ed: call ebp */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 40c5ef: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 40c5f4: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40c5f6: and ecx, 0x800001ff */
	if (!m->sf) goto L_40c606;	/* 40c5fc: jns 0x40c606 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 40c5fe: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40c5ff: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 40c605: inc ecx */
L_40c606:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 40c606: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 40c607: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c60d: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40c60e: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 40c610: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 40c616: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 40c619: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x40c622u; native_call(m, 0x4566c0u);	/* 40c61d: call 0x4566c0 */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 40c622: mov ecx, dword ptr [esp + 0x10] */
	m->eax = (DWORD)(m->edi + 0xau);	/* 40c626: lea eax, [edi + 0xa] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40c629: cmp ecx, eax */
	if (!m->zf) goto L_40c6b2;	/* 40c62b: jne 0x40c6b2 */
	m->eax = M32((DWORD)(0x68039cu));	/* 40c631: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40c636: test eax, eax */
	if (!m->zf) goto L_40c6b2;	/* 40c638: jne 0x40c6b2 */
	m->eax = M32((DWORD)(0x4db55cu));	/* 40c63a: mov eax, dword ptr [0x4db55c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40c63f: test eax, eax */
	if (!m->zf) goto L_40c6b2;	/* 40c641: jne 0x40c6b2 */
	m->eax = M32((DWORD)(0x907b2cu));	/* 40c643: mov eax, dword ptr [0x907b2c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40c648: test eax, eax */
	if (!m->zf) goto L_40c6b2;	/* 40c64a: jne 0x40c6b2 */
	m->eax = M32((DWORD)(0x4db508u));	/* 40c64c: mov eax, dword ptr [0x4db508] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40c651: test eax, eax */
	if (!m->zf) goto L_40c6b2;	/* 40c653: jne 0x40c6b2 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c655: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c65a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c65f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c664: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40c66fu; native_call(m, M32(0x4a9228u));	/* 40c669: call dword ptr [0x4a9228] */
	m->ecx = M32((DWORD)(0x4dbb0cu));	/* 40c66f: mov ecx, dword ptr [0x4dbb0c] */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 40c675: mov eax, dword ptr [0x4dbb00] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c67a: push 1 */
	m->edx = (DWORD)(m->ecx + 0xffffffeeu);	/* 40c67c: lea edx, [ecx - 0x12] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffceu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40c67f: add ecx, -0x32 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c682: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x104u);	/* 40c683: lea edx, [esi + eax + 0x104] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c68a: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x3cu);	/* 40c68b: lea eax, [esi + eax + 0x3c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c68f: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c690: push eax */
	m->esp -= 4; M32(m->esp) = 0x40c696u; native_call(m, 0x4282f0u);	/* 40c691: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x4dbaa4u));	/* 40c696: mov ecx, dword ptr [0x4dbaa4] */
	m->edx = M32((DWORD)(0x4dbaa0u));	/* 40c69c: mov edx, dword ptr [0x4dbaa0] */
	m->eax = M32((DWORD)(0x4dba9cu));	/* 40c6a2: mov eax, dword ptr [0x4dba9c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c6a7: push ecx */
	m->ecx = M32((DWORD)(0x4dba98u));	/* 40c6a8: mov ecx, dword ptr [0x4dba98] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c6ae: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c6af: push eax */
	goto L_40c70d;	/* 40c6b0: jmp 0x40c70d */
L_40c6b2:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40c6b2: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c6b7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c6bc: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c6c1: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40c6ccu; native_call(m, M32(0x4a9228u));	/* 40c6c6: call dword ptr [0x4a9228] */
	m->ecx = M32((DWORD)(0x4dbb0cu));	/* 40c6cc: mov ecx, dword ptr [0x4dbb0c] */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 40c6d2: mov eax, dword ptr [0x4dbb00] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c6d7: push 1 */
	m->edx = (DWORD)(m->ecx + 0xffffffeeu);	/* 40c6d9: lea edx, [ecx - 0x12] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffceu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40c6dc: add ecx, -0x32 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c6df: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x104u);	/* 40c6e0: lea edx, [esi + eax + 0x104] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c6e7: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x3cu);	/* 40c6e8: lea eax, [esi + eax + 0x3c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c6ec: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c6ed: push eax */
	m->esp -= 4; M32(m->esp) = 0x40c6f3u; native_call(m, 0x4282f0u);	/* 40c6ee: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x4db8acu));	/* 40c6f3: mov ecx, dword ptr [0x4db8ac] */
	m->edx = M32((DWORD)(0x4db8a8u));	/* 40c6f9: mov edx, dword ptr [0x4db8a8] */
	m->eax = M32((DWORD)(0x4db8a4u));	/* 40c6ff: mov eax, dword ptr [0x4db8a4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c704: push ecx */
	m->ecx = M32((DWORD)(0x4db8a0u));	/* 40c705: mov ecx, dword ptr [0x4db8a0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c70b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c70c: push eax */
L_40c70d:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c70d: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c70e: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40c718u; native_call(m, 0x41f0e0u);	/* 40c713: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 40c718: mov eax, dword ptr [0x4dbb00] */
	m->ecx = M32((DWORD)(0x4dbb0cu));	/* 40c71d: mov ecx, dword ptr [0x4dbb0c] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40c723: add esp, 0x28 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40c726: add ecx, -0x2a */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x104u);	/* 40c729: lea edx, [esi + eax + 0x104] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c730: push ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c731: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x3cu);	/* 40c732: lea edx, [esi + eax + 0x3c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c736: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c737: push edx */
	m->esp -= 4; M32(m->esp) = 0x40c73du; native_call(m, 0x4029d0u);	/* 40c738: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40c73d: add esp, 0x10 */
L_40c740:
	{ DWORD a_ = m->ebx, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 40c740: add ebx, 0x80 */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 40c746: inc edi */
	{ DWORD a_ = m->esi, b_ = 0xfau & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 40c747: add esi, 0xfa */
	{ DWORD a_ = m->ebx, b_ = 0x7532a4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40c74d: cmp ebx, 0x7532a4 */
	if (m->sf != m->of) goto L_40c5dc;	/* 40c753: jl 0x40c5dc */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x4db548u)));	/* 40c759: movsx eax, byte ptr [0x4db548] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c760: push eax */
	m->esp -= 4; M32(m->esp) = 0x40c766u; native_call(m, 0x40b550u);	/* 40c761: call 0x40b550 */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 40c766: mov eax, dword ptr [0x9db0a4] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40c76b: add esp, 4 */
	m->ecx = m->eax;	/* 40c76e: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40c770: and ecx, 0x800001ff */
	if (!m->sf) goto L_40c780;	/* 40c776: jns 0x40c780 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 40c778: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40c779: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 40c77f: inc ecx */
L_40c780:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 40c780: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 40c781: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c787: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40c788: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 40c78a: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 40c790: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 40c793: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x40c79cu; native_call(m, 0x4566c0u);	/* 40c797: call 0x4566c0 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c79c: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x40c7a3u; native_call(m, m->ebp);	/* 40c7a1: call ebp */
	m->edi = M32((DWORD)(0x4a9228u));	/* 40c7a3: mov edi, dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c7a9: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c7ae: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c7b3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c7b8: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40c7bfu; native_call(m, m->edi);	/* 40c7bd: call edi */
	m->esi = M32((DWORD)(m->esp + 0x10u));	/* 40c7bf: mov esi, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->esi, b_ = 0xdu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40c7c3: cmp esi, 0xd */
	if (!m->zf) goto L_40c901;	/* 40c7c6: jne 0x40c901 */
	m->eax = M32((DWORD)(0x68039cu));	/* 40c7cc: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40c7d1: test eax, eax */
	if (!m->zf) goto L_40c901;	/* 40c7d3: jne 0x40c901 */
	m->eax = M32((DWORD)(0x4db55cu));	/* 40c7d9: mov eax, dword ptr [0x4db55c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40c7de: test eax, eax */
	if (!m->zf) goto L_40c901;	/* 40c7e0: jne 0x40c901 */
	m->eax = M32((DWORD)(0x907b2cu));	/* 40c7e6: mov eax, dword ptr [0x907b2c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40c7eb: test eax, eax */
	if (!m->zf) goto L_40c901;	/* 40c7ed: jne 0x40c901 */
	m->eax = M32((DWORD)(0x4db508u));	/* 40c7f3: mov eax, dword ptr [0x4db508] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40c7f8: test eax, eax */
	if (!m->zf) goto L_40c901;	/* 40c7fa: jne 0x40c901 */
	m->eax = M32((DWORD)(0x4dbb04u));	/* 40c800: mov eax, dword ptr [0x4dbb04] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c805: push 1 */
	m->ecx = (DWORD)(m->eax + 0xefu);	/* 40c807: lea ecx, [eax + 0xef] */
	{ DWORD a_ = m->eax, b_ = 0xd7u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40c80d: add eax, 0xd7 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c812: push ecx */
	m->ecx = M32((DWORD)(0x4dbb08u));	/* 40c813: mov ecx, dword ptr [0x4dbb08] */
	m->edx = (DWORD)(m->ecx + 0xffffffa4u);	/* 40c819: lea edx, [ecx - 0x5c] */
	{ DWORD a_ = m->ecx, b_ = 0xffffff74u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40c81c: add ecx, 0xffffff74 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c822: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c823: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c824: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40c82au; native_call(m, 0x4284d0u);	/* 40c825: call 0x4284d0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40c82a: add esp, 0x14 */
L_40c82d:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c82d: push 0 */
L_40c82f:
	m->eax = M32((DWORD)(0x4dbb04u));	/* 40c82f: mov eax, dword ptr [0x4dbb04] */
	m->ecx = (DWORD)(m->eax + 0xefu);	/* 40c834: lea ecx, [eax + 0xef] */
	{ DWORD a_ = m->eax, b_ = 0xd7u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40c83a: add eax, 0xd7 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c83f: push ecx */
	m->ecx = M32((DWORD)(0x4dbb08u));	/* 40c840: mov ecx, dword ptr [0x4dbb08] */
	m->edx = (DWORD)(m->ecx + 0xffffffe0u);	/* 40c846: lea edx, [ecx - 0x20] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffb0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40c849: add ecx, -0x50 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c84c: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c84d: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c84e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40c854u; native_call(m, 0x4285c0u);	/* 40c84f: call 0x4285c0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40c854: add esp, 0x14 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c857: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x40c85eu; native_call(m, m->ebp);	/* 40c85c: call ebp */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 40c85e: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 40c863: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40c865: and ecx, 0x800001ff */
	if (!m->sf) goto L_40c875;	/* 40c86b: jns 0x40c875 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 40c86d: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40c86e: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 40c874: inc ecx */
L_40c875:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 40c875: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 40c876: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c87c: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40c87d: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 40c87f: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 40c885: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 40c888: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x40c891u; native_call(m, 0x4566c0u);	/* 40c88c: call 0x4566c0 */
	{ DWORD a_ = M8((DWORD)(0x4db54au)), b_ = 0x1u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40c891: cmp byte ptr [0x4db54a], 1 */
	if (!m->zf) goto L_40c965;	/* 40c898: jne 0x40c965 */
	m->eax = M32((DWORD)(0x68039cu));	/* 40c89e: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40c8a3: test eax, eax */
	if (!m->zf) goto L_40c965;	/* 40c8a5: jne 0x40c965 */
	m->eax = M32((DWORD)(0x4db55cu));	/* 40c8ab: mov eax, dword ptr [0x4db55c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40c8b0: test eax, eax */
	if (!m->zf) goto L_40c965;	/* 40c8b2: jne 0x40c965 */
	m->eax = M32((DWORD)(0x907b2cu));	/* 40c8b8: mov eax, dword ptr [0x907b2c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40c8bd: test eax, eax */
	if (!m->zf) goto L_40c965;	/* 40c8bf: jne 0x40c965 */
	m->eax = M32((DWORD)(0x4db508u));	/* 40c8c5: mov eax, dword ptr [0x4db508] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40c8ca: test eax, eax */
	if (!m->zf) goto L_40c965;	/* 40c8cc: jne 0x40c965 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c8d2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c8d7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c8dc: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c8e1: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40c8e8u; native_call(m, m->edi);	/* 40c8e6: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c8e8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c8ed: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c8f2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c8f7: push 0x3f800000 */
	goto L_40c995;	/* 40c8fc: jmp 0x40c995 */
L_40c901:
	m->eax = M32((DWORD)(0x4dbb04u));	/* 40c901: mov eax, dword ptr [0x4dbb04] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c906: push 0 */
	m->ecx = (DWORD)(m->eax + 0xefu);	/* 40c908: lea ecx, [eax + 0xef] */
	{ DWORD a_ = m->eax, b_ = 0xd7u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40c90e: add eax, 0xd7 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c913: push ecx */
	m->ecx = M32((DWORD)(0x4dbb08u));	/* 40c914: mov ecx, dword ptr [0x4dbb08] */
	m->edx = (DWORD)(m->ecx + 0xffffffa4u);	/* 40c91a: lea edx, [ecx - 0x5c] */
	{ DWORD a_ = m->ecx, b_ = 0xffffff74u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40c91d: add ecx, 0xffffff74 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c923: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c924: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c925: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40c92bu; native_call(m, 0x4284d0u);	/* 40c926: call 0x4284d0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40c92b: add esp, 0x14 */
	{ DWORD a_ = m->esi, b_ = 0xeu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40c92e: cmp esi, 0xe */
	if (!m->zf) goto L_40c82d;	/* 40c931: jne 0x40c82d */
	m->eax = M32((DWORD)(0x68039cu));	/* 40c937: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40c93c: test eax, eax */
	if (!m->zf) goto L_40c82d;	/* 40c93e: jne 0x40c82d */
	m->eax = M32((DWORD)(0x4db55cu));	/* 40c944: mov eax, dword ptr [0x4db55c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40c949: test eax, eax */
	if (!m->zf) goto L_40c82d;	/* 40c94b: jne 0x40c82d */
	m->eax = M32((DWORD)(0x907b2cu));	/* 40c951: mov eax, dword ptr [0x907b2c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40c956: test eax, eax */
	if (!m->zf) goto L_40c82d;	/* 40c958: jne 0x40c82d */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c95e: push 1 */
	goto L_40c82f;	/* 40c960: jmp 0x40c82f */
L_40c965:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40c965: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c96a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c96f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c974: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40c97bu; native_call(m, m->edi);	/* 40c979: call edi */
	m->eax = M32((DWORD)(0x4db8acu));	/* 40c97b: mov eax, dword ptr [0x4db8ac] */
	m->ecx = M32((DWORD)(0x4db8a8u));	/* 40c980: mov ecx, dword ptr [0x4db8a8] */
	m->edx = M32((DWORD)(0x4db8a4u));	/* 40c986: mov edx, dword ptr [0x4db8a4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c98c: push eax */
	m->eax = M32((DWORD)(0x4db8a0u));	/* 40c98d: mov eax, dword ptr [0x4db8a0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c992: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c993: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c994: push eax */
L_40c995:
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c995: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40c99fu; native_call(m, 0x41f0e0u);	/* 40c99a: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4dbb04u));	/* 40c99f: mov eax, dword ptr [0x4dbb04] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40c9a4: add esp, 0x14 */
	m->ecx = (DWORD)(m->eax + 0x111u);	/* 40c9a7: lea ecx, [eax + 0x111] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c9ad: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c9af: push ecx */
	m->ecx = M32((DWORD)(0x4dbb08u));	/* 40c9b0: mov ecx, dword ptr [0x4dbb08] */
	{ DWORD a_ = m->eax, b_ = 0xf5u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40c9b6: add eax, 0xf5 */
	m->edx = (DWORD)(m->ecx + 0xffffffeau);	/* 40c9bb: lea edx, [ecx - 0x16] */
	{ DWORD a_ = m->ecx, b_ = 0xffffff6au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40c9be: add ecx, 0xffffff6a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c9c4: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c9c5: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c9c6: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40c9ccu; native_call(m, 0x4282f0u);	/* 40c9c7: call 0x4282f0 */
	m->eax = M32((DWORD)(0x4dbb08u));	/* 40c9cc: mov eax, dword ptr [0x4dbb08] */
	m->edx = M32((DWORD)(0x4dbb04u));	/* 40c9d1: mov edx, dword ptr [0x4dbb04] */
	{ DWORD v_ = 0x75d8a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 40c9d7: push 0x75d8a4 */
	{ DWORD a_ = m->edx, b_ = 0xfbu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40c9dc: add edx, 0xfb */
	m->ecx = (DWORD)(m->eax + 0xffffffeau);	/* 40c9e2: lea ecx, [eax - 0x16] */
	{ DWORD a_ = m->eax, b_ = 0xffffff6au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40c9e5: add eax, 0xffffff6a */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c9ea: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40c9eb: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40c9ec: push eax */
	m->esp -= 4; M32(m->esp) = 0x40c9f2u; native_call(m, 0x4029d0u);	/* 40c9ed: call 0x4029d0 */
	m->eax = M32((DWORD)(0x4db55cu));	/* 40c9f2: mov eax, dword ptr [0x4db55c] */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40c9f7: add esp, 0x24 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40c9fa: test eax, eax */
	if (m->zf) goto L_40cbda;	/* 40c9fc: je 0x40cbda */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ca02: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ca07: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ca0c: push 0 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ca0e: push 0x3f333333 */
	m->esp -= 4; M32(m->esp) = 0x40ca15u; native_call(m, m->edi);	/* 40ca13: call edi */
	m->eax = M32((DWORD)(0x4deb50u));	/* 40ca15: mov eax, dword ptr [0x4deb50] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40ca1a: push eax */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ca1b: push 0x140 */
	{ DWORD v_ = 0x21cu; m->esp -= 4; M32(m->esp) = v_; }	/* 40ca20: push 0x21c */
	{ DWORD v_ = 0xb4u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ca25: push 0xb4 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ca2a: push 0x64 */
	m->esp -= 4; M32(m->esp) = 0x40ca31u; native_call(m, 0x427b60u);	/* 40ca2c: call 0x427b60 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ca31: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ca36: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ca3b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ca40: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ca45: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40ca4fu; native_call(m, 0x41f0e0u);	/* 40ca4a: call 0x41f0e0 */
	{ DWORD v_ = 0x753224u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ca4f: push 0x753224 */
	{ DWORD v_ = 0x21cu; m->esp -= 4; M32(m->esp) = v_; }	/* 40ca54: push 0x21c */
	{ DWORD v_ = 0xc8u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ca59: push 0xc8 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ca5e: push 0x64 */
	m->esp -= 4; M32(m->esp) = 0x40ca65u; native_call(m, 0x4029d0u);	/* 40ca60: call 0x4029d0 */
	{ DWORD v_ = 0x7532a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ca65: push 0x7532a4 */
	{ DWORD v_ = 0x21cu; m->esp -= 4; M32(m->esp) = v_; }	/* 40ca6a: push 0x21c */
	{ DWORD v_ = 0xdcu; m->esp -= 4; M32(m->esp) = v_; }	/* 40ca6f: push 0xdc */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ca74: push 0x64 */
	m->esp -= 4; M32(m->esp) = 0x40ca7bu; native_call(m, 0x4029d0u);	/* 40ca76: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40ca7b: add esp, 0x48 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 40ca7e: xor ebp, ebp */
	m->esi = 0xb4u;	/* 40ca80: mov esi, 0xb4 */
	m->ebx = 0x7517a4u;	/* 40ca85: mov ebx, 0x7517a4 */
L_40ca8a:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ca8a: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x40ca95u; native_call(m, M32(0x4a9224u));	/* 40ca8f: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 40ca95: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 40ca9a: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40ca9c: and ecx, 0x800001ff */
	if (!m->sf) goto L_40caac;	/* 40caa2: jns 0x40caac */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 40caa4: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40caa5: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 40caab: inc ecx */
L_40caac:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 40caac: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 40caad: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40cab3: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40cab4: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 40cab6: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 40cabc: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 40cabf: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x40cac8u; native_call(m, 0x4566c0u);	/* 40cac3: call 0x4566c0 */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 40cac8: mov ecx, dword ptr [esp + 0x10] */
	m->eax = (DWORD)(m->ebp + 0xfu);	/* 40cacc: lea eax, [ebp + 0xf] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40cacf: cmp ecx, eax */
	if (!m->zf) goto L_40cb20;	/* 40cad1: jne 0x40cb20 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cad3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cad8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cadd: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cae2: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40caedu; native_call(m, M32(0x4a9228u));	/* 40cae7: call dword ptr [0x4a9228] */
	m->edi = (DWORD)(m->esi + 0x78u);	/* 40caed: lea edi, [esi + 0x78] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40caf0: push 1 */
	{ DWORD v_ = 0x124u; m->esp -= 4; M32(m->esp) = v_; }	/* 40caf2: push 0x124 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40caf7: push edi */
	{ DWORD v_ = 0x104u; m->esp -= 4; M32(m->esp) = v_; }	/* 40caf8: push 0x104 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40cafd: push esi */
	m->esp -= 4; M32(m->esp) = 0x40cb03u; native_call(m, 0x4282f0u);	/* 40cafe: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x4dbaa4u));	/* 40cb03: mov ecx, dword ptr [0x4dbaa4] */
	m->edx = M32((DWORD)(0x4dbaa0u));	/* 40cb09: mov edx, dword ptr [0x4dbaa0] */
	m->eax = M32((DWORD)(0x4dba9cu));	/* 40cb0f: mov eax, dword ptr [0x4dba9c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40cb14: push ecx */
	m->ecx = M32((DWORD)(0x4dba98u));	/* 40cb15: mov ecx, dword ptr [0x4dba98] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40cb1b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40cb1c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40cb1d: push ecx */
	goto L_40cb6b;	/* 40cb1e: jmp 0x40cb6b */
L_40cb20:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40cb20: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cb25: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cb2a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cb2f: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40cb3au; native_call(m, M32(0x4a9228u));	/* 40cb34: call dword ptr [0x4a9228] */
	m->edi = (DWORD)(m->esi + 0x78u);	/* 40cb3a: lea edi, [esi + 0x78] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cb3d: push 1 */
	{ DWORD v_ = 0x124u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cb3f: push 0x124 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40cb44: push edi */
	{ DWORD v_ = 0x104u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cb45: push 0x104 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40cb4a: push esi */
	m->esp -= 4; M32(m->esp) = 0x40cb50u; native_call(m, 0x4282f0u);	/* 40cb4b: call 0x4282f0 */
	m->edx = M32((DWORD)(0x4db8acu));	/* 40cb50: mov edx, dword ptr [0x4db8ac] */
	m->eax = M32((DWORD)(0x4db8a8u));	/* 40cb56: mov eax, dword ptr [0x4db8a8] */
	m->ecx = M32((DWORD)(0x4db8a4u));	/* 40cb5b: mov ecx, dword ptr [0x4db8a4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40cb61: push edx */
	m->edx = M32((DWORD)(0x4db8a0u));	/* 40cb62: mov edx, dword ptr [0x4db8a0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40cb68: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40cb69: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40cb6a: push edx */
L_40cb6b:
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cb6b: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40cb75u; native_call(m, 0x41f0e0u);	/* 40cb70: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40cb75: add esp, 0x28 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 40cb78: push ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40cb79: push edi */
	{ DWORD v_ = 0x10cu; m->esp -= 4; M32(m->esp) = v_; }	/* 40cb7a: push 0x10c */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40cb7f: push esi */
	m->esp -= 4; M32(m->esp) = 0x40cb85u; native_call(m, 0x4029d0u);	/* 40cb80: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40cb85: add esp, 0x10 */
	{ DWORD a_ = m->ebx, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 40cb88: add ebx, 0x80 */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 40cb8e: inc ebp */
	{ DWORD a_ = m->esi, b_ = 0xa0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 40cb8f: add esi, 0xa0 */
	{ DWORD a_ = m->ebx, b_ = 0x7518a4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40cb95: cmp ebx, 0x7518a4 */
	if (m->sf != m->of) goto L_40ca8a;	/* 40cb9b: jl 0x40ca8a */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cba1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cba6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cbab: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cbb0: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40cbbbu; native_call(m, M32(0x4a9228u));	/* 40cbb5: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cbbb: push 0x140 */
	{ DWORD v_ = 0x21cu; m->esp -= 4; M32(m->esp) = v_; }	/* 40cbc0: push 0x21c */
	{ DWORD v_ = 0xb4u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cbc5: push 0xb4 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cbca: push 0x64 */
	m->esp -= 4; M32(m->esp) = 0x40cbd1u; native_call(m, 0x428b50u);	/* 40cbcc: call 0x428b50 */
	m->edi = M32((DWORD)(0x4a9228u));	/* 40cbd1: mov edi, dword ptr [0x4a9228] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40cbd7: add esp, 0x10 */
L_40cbda:
	m->eax = M32((DWORD)(0x907b2cu));	/* 40cbda: mov eax, dword ptr [0x907b2c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40cbdf: test eax, eax */
	if (m->zf) goto L_40ce0f;	/* 40cbe1: je 0x40ce0f */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 40cbe7: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 40cbec: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40cbf2: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40cbf3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40cbf9u; native_call(m, 0x4045a0u);	/* 40cbf4: call 0x4045a0 */
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40cbf9: push 0x3ecccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40cbfe: push 0x3dcccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40cc03: push 0x3dcccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40cc08: push 0x3dcccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cc0d: push 0x9da480 */
	M32((DWORD)(m->esp + 0x2cu)) = m->eax;	/* 40cc12: mov dword ptr [esp + 0x2c], eax */
	m->esp -= 4; M32(m->esp) = 0x40cc1bu; native_call(m, 0x41f0e0u);	/* 40cc16: call 0x41f0e0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cc1b: push 1 */
	{ DWORD v_ = 0x1e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cc1d: push 0x1e0 */
	{ DWORD v_ = 0x280u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cc22: push 0x280 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cc27: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cc29: push 0 */
	m->esp -= 4; M32(m->esp) = 0x40cc30u; native_call(m, 0x427970u);	/* 40cc2b: call 0x427970 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40cc30: push 0x3f4ccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40cc35: push 0x3dcccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40cc3a: push 0x3dcccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40cc3f: push 0x3dcccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cc44: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40cc4eu; native_call(m, 0x41f0e0u);	/* 40cc49: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40cc4e: add esp, 0x44 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cc51: push 1 */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cc53: push 0x140 */
	{ DWORD v_ = 0x21cu; m->esp -= 4; M32(m->esp) = v_; }	/* 40cc58: push 0x21c */
	{ DWORD v_ = 0xb4u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cc5d: push 0xb4 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cc62: push 0x64 */
	m->esp -= 4; M32(m->esp) = 0x40cc69u; native_call(m, 0x427970u);	/* 40cc64: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cc69: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cc6e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cc73: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cc78: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cc7a: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40cc84u; native_call(m, 0x41f0e0u);	/* 40cc7f: call 0x41f0e0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cc84: push 0 */
	{ DWORD v_ = 0x13cu; m->esp -= 4; M32(m->esp) = v_; }	/* 40cc86: push 0x13c */
	{ DWORD v_ = 0x218u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cc8b: push 0x218 */
	{ DWORD v_ = 0xb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cc90: push 0xb8 */
	{ DWORD v_ = 0x68u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cc95: push 0x68 */
	m->esp -= 4; M32(m->esp) = 0x40cc9cu; native_call(m, 0x427970u);	/* 40cc97: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cc9c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cca1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cca6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ccab: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ccb0: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40ccbau; native_call(m, 0x41f0e0u);	/* 40ccb5: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40ccba: add esp, 0x50 */
	{ DWORD v_ = 0x74dfa4u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ccbd: push 0x74dfa4 */
	{ DWORD v_ = 0x21cu; m->esp -= 4; M32(m->esp) = v_; }	/* 40ccc2: push 0x21c */
	{ DWORD v_ = 0xc8u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ccc7: push 0xc8 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cccc: push 0x64 */
	m->esp -= 4; M32(m->esp) = 0x40ccd3u; native_call(m, 0x4029d0u);	/* 40ccce: call 0x4029d0 */
	{ DWORD v_ = 0x74e024u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ccd3: push 0x74e024 */
	{ DWORD v_ = 0x21cu; m->esp -= 4; M32(m->esp) = v_; }	/* 40ccd8: push 0x21c */
	{ DWORD v_ = 0xdcu; m->esp -= 4; M32(m->esp) = v_; }	/* 40ccdd: push 0xdc */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cce2: push 0x64 */
	m->esp -= 4; M32(m->esp) = 0x40cce9u; native_call(m, 0x4029d0u);	/* 40cce4: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40cce9: add esp, 0x20 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 40ccec: xor ebp, ebp */
	m->esi = 0xb4u;	/* 40ccee: mov esi, 0xb4 */
	m->ebx = 0x7517a4u;	/* 40ccf3: mov ebx, 0x7517a4 */
L_40ccf8:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ccf8: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x40cd03u; native_call(m, M32(0x4a9224u));	/* 40ccfd: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 40cd03: mov eax, dword ptr [0x9db0a4] */
	m->edx = m->eax;	/* 40cd08: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 40cd0a: and edx, 0x800001ff */
	if (!m->sf) goto L_40cd1a;	/* 40cd10: jns 0x40cd1a */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 40cd12: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 40cd13: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 40cd19: inc edx */
L_40cd1a:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40cd1a: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 40cd1b: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 40cd21: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 40cd22: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40cd28: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 40cd2a: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 40cd2d: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x40cd36u; native_call(m, 0x4566c0u);	/* 40cd31: call 0x4566c0 */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x10u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40cd36: cmp dword ptr [esp + 0x10], ebp */
	if (!m->zf) goto L_40cd89;	/* 40cd3a: jne 0x40cd89 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cd3c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cd41: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cd46: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cd4b: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40cd56u; native_call(m, M32(0x4a9228u));	/* 40cd50: call dword ptr [0x4a9228] */
	m->edi = (DWORD)(m->esi + 0x78u);	/* 40cd56: lea edi, [esi + 0x78] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cd59: push 1 */
	{ DWORD v_ = 0x124u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cd5b: push 0x124 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40cd60: push edi */
	{ DWORD v_ = 0x104u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cd61: push 0x104 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40cd66: push esi */
	m->esp -= 4; M32(m->esp) = 0x40cd6cu; native_call(m, 0x4282f0u);	/* 40cd67: call 0x4282f0 */
	m->edx = M32((DWORD)(0x4dbaa4u));	/* 40cd6c: mov edx, dword ptr [0x4dbaa4] */
	m->eax = M32((DWORD)(0x4dbaa0u));	/* 40cd72: mov eax, dword ptr [0x4dbaa0] */
	m->ecx = M32((DWORD)(0x4dba9cu));	/* 40cd77: mov ecx, dword ptr [0x4dba9c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40cd7d: push edx */
	m->edx = M32((DWORD)(0x4dba98u));	/* 40cd7e: mov edx, dword ptr [0x4dba98] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40cd84: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40cd85: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40cd86: push edx */
	goto L_40cdd3;	/* 40cd87: jmp 0x40cdd3 */
L_40cd89:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40cd89: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cd8e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cd93: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cd98: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40cda3u; native_call(m, M32(0x4a9228u));	/* 40cd9d: call dword ptr [0x4a9228] */
	m->edi = (DWORD)(m->esi + 0x78u);	/* 40cda3: lea edi, [esi + 0x78] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cda6: push 1 */
	{ DWORD v_ = 0x124u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cda8: push 0x124 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40cdad: push edi */
	{ DWORD v_ = 0x104u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cdae: push 0x104 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40cdb3: push esi */
	m->esp -= 4; M32(m->esp) = 0x40cdb9u; native_call(m, 0x4282f0u);	/* 40cdb4: call 0x4282f0 */
	m->eax = M32((DWORD)(0x4db8acu));	/* 40cdb9: mov eax, dword ptr [0x4db8ac] */
	m->ecx = M32((DWORD)(0x4db8a8u));	/* 40cdbe: mov ecx, dword ptr [0x4db8a8] */
	m->edx = M32((DWORD)(0x4db8a4u));	/* 40cdc4: mov edx, dword ptr [0x4db8a4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40cdca: push eax */
	m->eax = M32((DWORD)(0x4db8a0u));	/* 40cdcb: mov eax, dword ptr [0x4db8a0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40cdd0: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40cdd1: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40cdd2: push eax */
L_40cdd3:
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cdd3: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40cdddu; native_call(m, 0x41f0e0u);	/* 40cdd8: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40cddd: add esp, 0x28 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 40cde0: push ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40cde1: push edi */
	{ DWORD v_ = 0x10cu; m->esp -= 4; M32(m->esp) = v_; }	/* 40cde2: push 0x10c */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40cde7: push esi */
	m->esp -= 4; M32(m->esp) = 0x40cdedu; native_call(m, 0x4029d0u);	/* 40cde8: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40cded: add esp, 0x10 */
	{ DWORD a_ = m->ebx, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 40cdf0: add ebx, 0x80 */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 40cdf6: inc ebp */
	{ DWORD a_ = m->esi, b_ = 0xa0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 40cdf7: add esi, 0xa0 */
	{ DWORD a_ = m->ebx, b_ = 0x7518a4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40cdfd: cmp ebx, 0x7518a4 */
	if (m->sf != m->of) goto L_40ccf8;	/* 40ce03: jl 0x40ccf8 */
	m->edi = M32((DWORD)(0x4a9228u));	/* 40ce09: mov edi, dword ptr [0x4a9228] */
L_40ce0f:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ce0f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ce14: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ce19: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ce1e: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40ce25u; native_call(m, m->edi);	/* 40ce23: call edi */
	m->ecx = M32((DWORD)(0x4dbb0cu));	/* 40ce25: mov ecx, dword ptr [0x4dbb0c] */
	m->edx = M32((DWORD)(0x4dbb08u));	/* 40ce2b: mov edx, dword ptr [0x4dbb08] */
	m->eax = M32((DWORD)(0x4dbb04u));	/* 40ce31: mov eax, dword ptr [0x4dbb04] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ce36: push ecx */
	m->ecx = M32((DWORD)(0x4dbb00u));	/* 40ce37: mov ecx, dword ptr [0x4dbb00] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ce3d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40ce3e: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ce3f: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40ce45u; native_call(m, 0x428a00u);	/* 40ce40: call 0x428a00 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40ce45: add esp, 0x10 */
	m->edi = M32(m->esp); m->esp += 4;	/* 40ce48: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 40ce49: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 40ce4a: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 40ce4b: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40ce4c: add esp, 0x10 */
	m->esp += 4 + 0; return;	/* 40ce4f: ret  */
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
