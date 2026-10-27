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

static void lift_425460(X86 *m);

/* setup_425460 (0x425460), lifted by tools/lift.py */
static void lift_425460(X86 *m)
{
	m->eax = M32((DWORD)(0x4ded6cu));	/* 425460: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 425465: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42546b: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42546c: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42546d: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42546e: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42546f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425470: push ecx */
	m->esp -= 4; M32(m->esp) = 0x425476u; native_call(m, 0x4206b0u);	/* 425471: call 0x4206b0 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 425476: push 2 */
	m->ebp = m->eax;	/* 425478: mov ebp, eax */
	m->esp -= 4; M32(m->esp) = 0x42547fu; native_call(m, 0x41ef90u);	/* 42547a: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42547f: add esp, 0xc */
	m->esp -= 4; M32(m->esp) = 0x425488u; native_call(m, M32(0x4a9218u));	/* 425482: call dword ptr [0x4a9218] */
	m->esi = M32((DWORD)(0x4a9228u));	/* 425488: mov esi, dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42548e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425493: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425498: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42549d: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4254a4u; native_call(m, m->esi);	/* 4254a2: call esi */
	m->edx = M32((DWORD)(0x4deb50u));	/* 4254a4: mov edx, dword ptr [0x4deb50] */
	m->eax = M32((DWORD)(0x4ddddcu));	/* 4254aa: mov eax, dword ptr [0x4ddddc] */
	m->ecx = M32((DWORD)(0x4dddd8u));	/* 4254af: mov ecx, dword ptr [0x4dddd8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4254b5: push edx */
	m->edx = M32((DWORD)(0x4dddd4u));	/* 4254b6: mov edx, dword ptr [0x4dddd4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4254bc: push eax */
	m->eax = M32((DWORD)(0x4dddd0u));	/* 4254bd: mov eax, dword ptr [0x4dddd0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4254c2: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4254c3: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4254c4: push eax */
	m->esp -= 4; M32(m->esp) = 0x4254cau; native_call(m, 0x427a90u);	/* 4254c5: call 0x427a90 */
	m->ecx = M32((DWORD)(0x4de054u));	/* 4254ca: mov ecx, dword ptr [0x4de054] */
	m->edx = M32((DWORD)(0x4de050u));	/* 4254d0: mov edx, dword ptr [0x4de050] */
	m->eax = M32((DWORD)(0x4de04cu));	/* 4254d6: mov eax, dword ptr [0x4de04c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4254db: push ecx */
	m->ecx = M32((DWORD)(0x4de048u));	/* 4254dc: mov ecx, dword ptr [0x4de048] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4254e2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4254e3: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4254e4: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4254e5: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4254efu; native_call(m, 0x41f0e0u);	/* 4254ea: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x4dddd4u));	/* 4254ef: mov edx, dword ptr [0x4dddd4] */
	m->eax = M32((DWORD)(0x4dddd0u));	/* 4254f5: mov eax, dword ptr [0x4dddd0] */
	{ DWORD a_ = m->edx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4254fa: add edx, 0x10 */
	{ DWORD v_ = 0x7538a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4254fd: push 0x7538a4 */
	{ DWORD a_ = m->eax, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 425502: add eax, 0x50 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425505: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425506: push eax */
	m->esp -= 4; M32(m->esp) = 0x42550cu; native_call(m, 0x4028b0u);	/* 425507: call 0x4028b0 */
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42550c: add esp, 0x34 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 42550f: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x42551au; native_call(m, M32(0x4a9224u));	/* 425514: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 42551a: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 42551f: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 425521: and ecx, 0x800001ff */
	if (!m->sf) goto L_425531;	/* 425527: jns 0x425531 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 425529: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42552a: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 425530: inc ecx */
L_425531:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 425531: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 425532: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425538: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 425539: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 42553b: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 425541: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 425544: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x42554du; native_call(m, 0x4566c0u);	/* 425548: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42554d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425552: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425557: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42555c: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x425563u; native_call(m, m->esi);	/* 425561: call esi */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 425563: xor edi, edi */
	m->esi = 0x753924u;	/* 425565: mov esi, 0x753924 */
L_42556a:
	m->eax = M32((DWORD)(0x4dddd4u));	/* 42556a: mov eax, dword ptr [0x4dddd4] */
	m->edx = M32((DWORD)(0x4dddd0u));	/* 42556f: mov edx, dword ptr [0x4dddd0] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 425575: push esi */
	{ DWORD a_ = m->edx, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 425576: add edx, 0x50 */
	m->ecx = (DWORD)(m->edi + m->eax*1 + 0x44u);	/* 425579: lea ecx, [edi + eax + 0x44] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42557d: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42557e: push edx */
	m->esp -= 4; M32(m->esp) = 0x425584u; native_call(m, 0x402620u);	/* 42557f: call 0x402620 */
	{ DWORD a_ = m->esi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 425584: add esi, 0x80 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42558a: add esp, 0xc */
	{ DWORD a_ = m->edi, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42558d: add edi, 0x28 */
	{ DWORD a_ = m->esi, b_ = 0x753ca4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 425590: cmp esi, 0x753ca4 */
	if (m->sf != m->of) goto L_42556a;	/* 425596: jl 0x42556a */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425598: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42559d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4255a2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4255a7: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4255ac: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4255b6u; native_call(m, 0x41f0e0u);	/* 4255b1: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4ddba0u));	/* 4255b6: mov eax, dword ptr [0x4ddba0] */
	m->edx = M32((DWORD)(0x4dddd4u));	/* 4255bb: mov edx, dword ptr [0x4dddd4] */
	{ DWORD a_ = m->edx, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4255c1: add edx, 0x44 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b04ccu));	/* 4255c4: mov ecx, dword ptr [eax*4 + 0x4b04cc] */
	m->eax = M32((DWORD)(0x4dddd0u));	/* 4255cb: mov eax, dword ptr [0x4dddd0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4255d0: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xe6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4255d1: add eax, 0xe6 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4255d6: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4255d7: push eax */
	m->esp -= 4; M32(m->esp) = 0x4255ddu; native_call(m, 0x402620u);	/* 4255d8: call 0x402620 */
	m->eax = M32((DWORD)(0x4ddba4u));	/* 4255dd: mov eax, dword ptr [0x4ddba4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4255e2: lea eax, [eax + eax*4] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4255e5: lea ecx, [eax + eax*4] */
	m->eax = M32((DWORD)(0x4dddd4u));	/* 4255e8: mov eax, dword ptr [0x4dddd4] */
	{ DWORD a_ = m->eax, b_ = 0x6cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4255ed: add eax, 0x6c */
	m->edx = (DWORD)(m->ecx*2 + 0x4ddbbcu);	/* 4255f0: lea edx, [ecx*2 + 0x4ddbbc] */
	m->ecx = M32((DWORD)(0x4dddd0u));	/* 4255f7: mov ecx, dword ptr [0x4dddd0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4255fd: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xe6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4255fe: add ecx, 0xe6 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425604: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425605: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42560bu; native_call(m, 0x402620u);	/* 425606: call 0x402620 */
	m->eax = M32((DWORD)(0x4ddba8u));	/* 42560b: mov eax, dword ptr [0x4ddba8] */
	m->ecx = M32((DWORD)(0x4dddd4u));	/* 425610: mov ecx, dword ptr [0x4dddd4] */
	{ DWORD a_ = m->ecx, b_ = 0x94u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 425616: add ecx, 0x94 */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 42561c: lea eax, [eax + eax*4] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 42561f: lea edx, [eax + eax*4] */
	m->eax = (DWORD)(m->edx*2 + 0x4dda64u);	/* 425622: lea eax, [edx*2 + 0x4dda64] */
	m->edx = M32((DWORD)(0x4dddd0u));	/* 425629: mov edx, dword ptr [0x4dddd0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42562f: push eax */
	{ DWORD a_ = m->edx, b_ = 0xe6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 425630: add edx, 0xe6 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425636: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425637: push edx */
	m->esp -= 4; M32(m->esp) = 0x42563du; native_call(m, 0x402620u);	/* 425638: call 0x402620 */
	m->eax = M32((DWORD)(0x4ddbacu));	/* 42563d: mov eax, dword ptr [0x4ddbac] */
	m->edx = M32((DWORD)(0x4dddd4u));	/* 425642: mov edx, dword ptr [0x4dddd4] */
	{ DWORD a_ = m->edx, b_ = 0xbcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 425648: add edx, 0xbc */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 42564e: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 425651: lea eax, [eax + eax*4] */
	m->ecx = (DWORD)(m->eax*2 + 0x4ddc84u);	/* 425654: lea ecx, [eax*2 + 0x4ddc84] */
	m->eax = M32((DWORD)(0x4dddd0u));	/* 42565b: mov eax, dword ptr [0x4dddd0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425660: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xe6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 425661: add eax, 0xe6 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425666: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425667: push eax */
	m->esp -= 4; M32(m->esp) = 0x42566du; native_call(m, 0x402620u);	/* 425668: call 0x402620 */
	m->eax = M32((DWORD)(0x4ddbb0u));	/* 42566d: mov eax, dword ptr [0x4ddbb0] */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 425672: add esp, 0x44 */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 425675: lea eax, [eax + eax*4] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 425678: lea ecx, [eax + eax*4] */
	m->eax = M32((DWORD)(0x4dddd4u));	/* 42567b: mov eax, dword ptr [0x4dddd4] */
	{ DWORD a_ = m->eax, b_ = 0xe4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 425680: add eax, 0xe4 */
	m->edx = (DWORD)(m->ecx*2 + 0x4de058u);	/* 425685: lea edx, [ecx*2 + 0x4de058] */
	m->ecx = M32((DWORD)(0x4dddd0u));	/* 42568c: mov ecx, dword ptr [0x4dddd0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425692: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xe6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 425693: add ecx, 0xe6 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425699: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42569a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4256a0u; native_call(m, 0x402620u);	/* 42569b: call 0x402620 */
	m->eax = M32((DWORD)(0x4ddbb4u));	/* 4256a0: mov eax, dword ptr [0x4ddbb4] */
	m->ecx = M32((DWORD)(0x4dddd4u));	/* 4256a5: mov ecx, dword ptr [0x4dddd4] */
	{ DWORD a_ = m->ecx, b_ = 0x10cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4256ab: add ecx, 0x10c */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4256b1: lea eax, [eax + eax*4] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4256b4: lea edx, [eax + eax*4] */
	m->eax = (DWORD)(m->edx*2 + 0x4ddc20u);	/* 4256b7: lea eax, [edx*2 + 0x4ddc20] */
	m->edx = M32((DWORD)(0x4dddd0u));	/* 4256be: mov edx, dword ptr [0x4dddd0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4256c4: push eax */
	{ DWORD a_ = m->edx, b_ = 0xe6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4256c5: add edx, 0xe6 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4256cb: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4256cc: push edx */
	m->esp -= 4; M32(m->esp) = 0x4256d2u; native_call(m, 0x402620u);	/* 4256cd: call 0x402620 */
	m->eax = M32((DWORD)(0x4ddbb8u));	/* 4256d2: mov eax, dword ptr [0x4ddbb8] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4256d7: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4256da: lea eax, [eax + eax*4] */
	m->ecx = (DWORD)(m->eax*2 + 0x4ddaf0u);	/* 4256dd: lea ecx, [eax*2 + 0x4ddaf0] */
	m->edx = M32((DWORD)(0x4dddd4u));	/* 4256e4: mov edx, dword ptr [0x4dddd4] */
	m->eax = M32((DWORD)(0x4dddd0u));	/* 4256ea: mov eax, dword ptr [0x4dddd0] */
	{ DWORD a_ = m->edx, b_ = 0x134u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4256ef: add edx, 0x134 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4256f5: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xe6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4256f6: add eax, 0xe6 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4256fb: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4256fc: push eax */
	m->esp -= 4; M32(m->esp) = 0x425702u; native_call(m, 0x402620u);	/* 4256fd: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 425702: add esp, 0x24 */
	{ DWORD a_ = m->ebp, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 425705: cmp ebp, 6 */
	if (!m->cf && !m->zf) goto L_425b21;	/* 425708: ja 0x425b21 */
	switch (m->ebp) { case 0: goto L_425715; case 1: goto L_425793; case 2: goto L_425827; case 3: goto L_4258c2; case 4: goto L_42594f; case 5: goto L_4259e8; case 6: goto L_425a83; default: abort(); }	/* 42570e: jmp dword ptr [ebp*4 + 0x425cb4] */
L_425715:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425715: push 0x3f800000 */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 42571a: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 42571f: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 425724: push 0x3c23d70a */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 425729: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x425733u; native_call(m, 0x41f0e0u);	/* 42572e: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4ddba0u));	/* 425733: mov ecx, dword ptr [0x4ddba0] */
	m->eax = M32((DWORD)(0x4dddd4u));	/* 425739: mov eax, dword ptr [0x4dddd4] */
	{ DWORD a_ = m->eax, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42573e: add eax, 0x44 */
	m->edx = M32((DWORD)(m->ecx*4 + 0x4b04ccu));	/* 425741: mov edx, dword ptr [ecx*4 + 0x4b04cc] */
	m->ecx = M32((DWORD)(0x4dddd0u));	/* 425748: mov ecx, dword ptr [0x4dddd0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42574e: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xe6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 42574f: add ecx, 0xe6 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425755: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425756: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42575cu; native_call(m, 0x402620u);	/* 425757: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42575c: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 425761: push 0 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 425763: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425768: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 42576d: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x425777u; native_call(m, 0x41f0e0u);	/* 425772: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x4ddba0u));	/* 425777: mov edx, dword ptr [0x4ddba0] */
	m->ecx = M32((DWORD)(0x4dddd4u));	/* 42577d: mov ecx, dword ptr [0x4dddd4] */
	{ DWORD a_ = m->ecx, b_ = 0x43u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 425783: add ecx, 0x43 */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b04ccu));	/* 425786: mov eax, dword ptr [edx*4 + 0x4b04cc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42578d: push eax */
	goto L_425b0b;	/* 42578e: jmp 0x425b0b */
L_425793:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425793: push 0x3f800000 */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 425798: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 42579d: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 4257a2: push 0x3c23d70a */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4257a7: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4257b1u; native_call(m, 0x41f0e0u);	/* 4257ac: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4ddba4u));	/* 4257b1: mov eax, dword ptr [0x4ddba4] */
	m->edx = M32((DWORD)(0x4dddd4u));	/* 4257b6: mov edx, dword ptr [0x4dddd4] */
	{ DWORD a_ = m->edx, b_ = 0x6cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4257bc: add edx, 0x6c */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4257bf: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4257c2: lea eax, [eax + eax*4] */
	m->ecx = (DWORD)(m->eax*2 + 0x4ddbbcu);	/* 4257c5: lea ecx, [eax*2 + 0x4ddbbc] */
	m->eax = M32((DWORD)(0x4dddd0u));	/* 4257cc: mov eax, dword ptr [0x4dddd0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4257d1: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xe6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4257d2: add eax, 0xe6 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4257d7: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4257d8: push eax */
	m->esp -= 4; M32(m->esp) = 0x4257deu; native_call(m, 0x402620u);	/* 4257d9: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4257de: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4257e3: push 0 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 4257e5: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4257ea: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4257ef: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4257f9u; native_call(m, 0x41f0e0u);	/* 4257f4: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4ddba4u));	/* 4257f9: mov eax, dword ptr [0x4ddba4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4257fe: lea eax, [eax + eax*4] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 425801: lea ecx, [eax + eax*4] */
	m->eax = M32((DWORD)(0x4dddd4u));	/* 425804: mov eax, dword ptr [0x4dddd4] */
	{ DWORD a_ = m->eax, b_ = 0x6bu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 425809: add eax, 0x6b */
	m->edx = (DWORD)(m->ecx*2 + 0x4ddbbcu);	/* 42580c: lea edx, [ecx*2 + 0x4ddbbc] */
	m->ecx = M32((DWORD)(0x4dddd0u));	/* 425813: mov ecx, dword ptr [0x4dddd0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425819: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xe5u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 42581a: add ecx, 0xe5 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425820: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425821: push ecx */
	goto L_425b19;	/* 425822: jmp 0x425b19 */
L_425827:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425827: push 0x3f800000 */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 42582c: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 425831: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 425836: push 0x3c23d70a */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 42583b: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x425845u; native_call(m, 0x41f0e0u);	/* 425840: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4ddba8u));	/* 425845: mov eax, dword ptr [0x4ddba8] */
	m->ecx = M32((DWORD)(0x4dddd4u));	/* 42584a: mov ecx, dword ptr [0x4dddd4] */
	{ DWORD a_ = m->ecx, b_ = 0x94u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 425850: add ecx, 0x94 */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 425856: lea eax, [eax + eax*4] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 425859: lea edx, [eax + eax*4] */
	m->eax = (DWORD)(m->edx*2 + 0x4dda64u);	/* 42585c: lea eax, [edx*2 + 0x4dda64] */
	m->edx = M32((DWORD)(0x4dddd0u));	/* 425863: mov edx, dword ptr [0x4dddd0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425869: push eax */
	{ DWORD a_ = m->edx, b_ = 0xe6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 42586a: add edx, 0xe6 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425870: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425871: push edx */
	m->esp -= 4; M32(m->esp) = 0x425877u; native_call(m, 0x402620u);	/* 425872: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425877: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42587c: push 0 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 42587e: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425883: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 425888: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x425892u; native_call(m, 0x41f0e0u);	/* 42588d: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4ddba8u));	/* 425892: mov eax, dword ptr [0x4ddba8] */
	m->edx = M32((DWORD)(0x4dddd4u));	/* 425897: mov edx, dword ptr [0x4dddd4] */
	{ DWORD a_ = m->edx, b_ = 0x93u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 42589d: add edx, 0x93 */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4258a3: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4258a6: lea eax, [eax + eax*4] */
	m->ecx = (DWORD)(m->eax*2 + 0x4dda64u);	/* 4258a9: lea ecx, [eax*2 + 0x4dda64] */
	m->eax = M32((DWORD)(0x4dddd0u));	/* 4258b0: mov eax, dword ptr [0x4dddd0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4258b5: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xe5u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4258b6: add eax, 0xe5 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4258bb: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4258bc: push eax */
	goto L_425b19;	/* 4258bd: jmp 0x425b19 */
L_4258c2:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4258c2: push 0x3f800000 */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 4258c7: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 4258cc: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 4258d1: push 0x3c23d70a */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4258d6: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4258e0u; native_call(m, 0x41f0e0u);	/* 4258db: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4ddbacu));	/* 4258e0: mov eax, dword ptr [0x4ddbac] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4258e5: lea eax, [eax + eax*4] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4258e8: lea ecx, [eax + eax*4] */
	m->eax = M32((DWORD)(0x4dddd4u));	/* 4258eb: mov eax, dword ptr [0x4dddd4] */
	{ DWORD a_ = m->eax, b_ = 0xbcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4258f0: add eax, 0xbc */
	m->edx = (DWORD)(m->ecx*2 + 0x4ddc84u);	/* 4258f5: lea edx, [ecx*2 + 0x4ddc84] */
	m->ecx = M32((DWORD)(0x4dddd0u));	/* 4258fc: mov ecx, dword ptr [0x4dddd0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425902: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xe6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 425903: add ecx, 0xe6 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425909: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42590a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x425910u; native_call(m, 0x402620u);	/* 42590b: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425910: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 425915: push 0 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 425917: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42591c: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 425921: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x42592bu; native_call(m, 0x41f0e0u);	/* 425926: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4ddbacu));	/* 42592b: mov eax, dword ptr [0x4ddbac] */
	m->ecx = M32((DWORD)(0x4dddd4u));	/* 425930: mov ecx, dword ptr [0x4dddd4] */
	{ DWORD a_ = m->ecx, b_ = 0xbbu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 425936: add ecx, 0xbb */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 42593c: lea eax, [eax + eax*4] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 42593f: lea edx, [eax + eax*4] */
	m->eax = (DWORD)(m->edx*2 + 0x4ddc84u);	/* 425942: lea eax, [edx*2 + 0x4ddc84] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425949: push eax */
	goto L_425b0b;	/* 42594a: jmp 0x425b0b */
L_42594f:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42594f: push 0x3f800000 */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 425954: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 425959: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 42595e: push 0x3c23d70a */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 425963: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x42596du; native_call(m, 0x41f0e0u);	/* 425968: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4ddbb0u));	/* 42596d: mov eax, dword ptr [0x4ddbb0] */
	m->edx = M32((DWORD)(0x4dddd4u));	/* 425972: mov edx, dword ptr [0x4dddd4] */
	{ DWORD a_ = m->edx, b_ = 0xe4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 425978: add edx, 0xe4 */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 42597e: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 425981: lea eax, [eax + eax*4] */
	m->ecx = (DWORD)(m->eax*2 + 0x4de058u);	/* 425984: lea ecx, [eax*2 + 0x4de058] */
	m->eax = M32((DWORD)(0x4dddd0u));	/* 42598b: mov eax, dword ptr [0x4dddd0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425990: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xe6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 425991: add eax, 0xe6 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425996: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425997: push eax */
	m->esp -= 4; M32(m->esp) = 0x42599du; native_call(m, 0x402620u);	/* 425998: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42599d: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4259a2: push 0 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 4259a4: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4259a9: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4259ae: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4259b8u; native_call(m, 0x41f0e0u);	/* 4259b3: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4ddbb0u));	/* 4259b8: mov eax, dword ptr [0x4ddbb0] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4259bd: lea eax, [eax + eax*4] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4259c0: lea ecx, [eax + eax*4] */
	m->eax = M32((DWORD)(0x4dddd4u));	/* 4259c3: mov eax, dword ptr [0x4dddd4] */
	{ DWORD a_ = m->eax, b_ = 0xe3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4259c8: add eax, 0xe3 */
	m->edx = (DWORD)(m->ecx*2 + 0x4de058u);	/* 4259cd: lea edx, [ecx*2 + 0x4de058] */
	m->ecx = M32((DWORD)(0x4dddd0u));	/* 4259d4: mov ecx, dword ptr [0x4dddd0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4259da: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xe5u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4259db: add ecx, 0xe5 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4259e1: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4259e2: push ecx */
	goto L_425b19;	/* 4259e3: jmp 0x425b19 */
L_4259e8:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4259e8: push 0x3f800000 */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 4259ed: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 4259f2: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 4259f7: push 0x3c23d70a */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4259fc: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x425a06u; native_call(m, 0x41f0e0u);	/* 425a01: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4ddbb4u));	/* 425a06: mov eax, dword ptr [0x4ddbb4] */
	m->ecx = M32((DWORD)(0x4dddd4u));	/* 425a0b: mov ecx, dword ptr [0x4dddd4] */
	{ DWORD a_ = m->ecx, b_ = 0x10cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 425a11: add ecx, 0x10c */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 425a17: lea eax, [eax + eax*4] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 425a1a: lea edx, [eax + eax*4] */
	m->eax = (DWORD)(m->edx*2 + 0x4ddc20u);	/* 425a1d: lea eax, [edx*2 + 0x4ddc20] */
	m->edx = M32((DWORD)(0x4dddd0u));	/* 425a24: mov edx, dword ptr [0x4dddd0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425a2a: push eax */
	{ DWORD a_ = m->edx, b_ = 0xe6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 425a2b: add edx, 0xe6 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425a31: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425a32: push edx */
	m->esp -= 4; M32(m->esp) = 0x425a38u; native_call(m, 0x402620u);	/* 425a33: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425a38: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 425a3d: push 0 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 425a3f: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425a44: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 425a49: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x425a53u; native_call(m, 0x41f0e0u);	/* 425a4e: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4ddbb4u));	/* 425a53: mov eax, dword ptr [0x4ddbb4] */
	m->edx = M32((DWORD)(0x4dddd4u));	/* 425a58: mov edx, dword ptr [0x4dddd4] */
	{ DWORD a_ = m->edx, b_ = 0x10bu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 425a5e: add edx, 0x10b */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 425a64: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 425a67: lea eax, [eax + eax*4] */
	m->ecx = (DWORD)(m->eax*2 + 0x4ddc20u);	/* 425a6a: lea ecx, [eax*2 + 0x4ddc20] */
	m->eax = M32((DWORD)(0x4dddd0u));	/* 425a71: mov eax, dword ptr [0x4dddd0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425a76: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xe5u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 425a77: add eax, 0xe5 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425a7c: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425a7d: push eax */
	goto L_425b19;	/* 425a7e: jmp 0x425b19 */
L_425a83:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425a83: push 0x3f800000 */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 425a88: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 425a8d: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 425a92: push 0x3c23d70a */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 425a97: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x425aa1u; native_call(m, 0x41f0e0u);	/* 425a9c: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4ddbb8u));	/* 425aa1: mov eax, dword ptr [0x4ddbb8] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 425aa6: lea eax, [eax + eax*4] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 425aa9: lea ecx, [eax + eax*4] */
	m->eax = M32((DWORD)(0x4dddd4u));	/* 425aac: mov eax, dword ptr [0x4dddd4] */
	{ DWORD a_ = m->eax, b_ = 0x134u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 425ab1: add eax, 0x134 */
	m->edx = (DWORD)(m->ecx*2 + 0x4ddaf0u);	/* 425ab6: lea edx, [ecx*2 + 0x4ddaf0] */
	m->ecx = M32((DWORD)(0x4dddd0u));	/* 425abd: mov ecx, dword ptr [0x4dddd0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425ac3: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xe6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 425ac4: add ecx, 0xe6 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425aca: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425acb: push ecx */
	m->esp -= 4; M32(m->esp) = 0x425ad1u; native_call(m, 0x402620u);	/* 425acc: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425ad1: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 425ad6: push 0 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 425ad8: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425add: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 425ae2: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x425aecu; native_call(m, 0x41f0e0u);	/* 425ae7: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4ddbb8u));	/* 425aec: mov eax, dword ptr [0x4ddbb8] */
	m->ecx = M32((DWORD)(0x4dddd4u));	/* 425af1: mov ecx, dword ptr [0x4dddd4] */
	{ DWORD a_ = m->ecx, b_ = 0x133u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 425af7: add ecx, 0x133 */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 425afd: lea eax, [eax + eax*4] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 425b00: lea edx, [eax + eax*4] */
	m->eax = (DWORD)(m->edx*2 + 0x4ddaf0u);	/* 425b03: lea eax, [edx*2 + 0x4ddaf0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425b0a: push eax */
L_425b0b:
	m->edx = M32((DWORD)(0x4dddd0u));	/* 425b0b: mov edx, dword ptr [0x4dddd0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425b11: push ecx */
	{ DWORD a_ = m->edx, b_ = 0xe5u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 425b12: add edx, 0xe5 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425b18: push edx */
L_425b19:
	m->esp -= 4; M32(m->esp) = 0x425b1eu; native_call(m, 0x402620u);	/* 425b19: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 425b1e: add esp, 0x40 */
L_425b21:
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 425b21: xor ebx, ebx */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 425b23: xor esi, esi */
	m->edi = 0x753ca4u;	/* 425b25: mov edi, 0x753ca4 */
L_425b2a:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 425b2a: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x425b35u; native_call(m, M32(0x4a9224u));	/* 425b2f: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 425b35: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 425b3a: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 425b3c: and ecx, 0x800001ff */
	if (!m->sf) goto L_425b4c;	/* 425b42: jns 0x425b4c */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 425b44: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 425b45: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 425b4b: inc ecx */
L_425b4c:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 425b4c: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 425b4d: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425b53: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 425b54: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 425b56: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 425b5c: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 425b5f: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x425b68u; native_call(m, 0x4566c0u);	/* 425b63: call 0x4566c0 */
	m->eax = (DWORD)(m->ebx + 0x7u);	/* 425b68: lea eax, [ebx + 7] */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 425b6b: cmp ebp, eax */
	if (!m->zf) goto L_425bcc;	/* 425b6d: jne 0x425bcc */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425b6f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425b74: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425b79: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425b7e: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x425b89u; native_call(m, M32(0x4a9228u));	/* 425b83: call dword ptr [0x4a9228] */
	m->ecx = M32((DWORD)(0x4ddddcu));	/* 425b89: mov ecx, dword ptr [0x4ddddc] */
	m->eax = M32((DWORD)(0x4dddd0u));	/* 425b8f: mov eax, dword ptr [0x4dddd0] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 425b94: push 1 */
	m->edx = (DWORD)(m->ecx + 0xffffffe0u);	/* 425b96: lea edx, [ecx - 0x20] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffc0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 425b99: add ecx, -0x40 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425b9c: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xdcu);	/* 425b9d: lea edx, [esi + eax + 0xdc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425ba4: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x64u);	/* 425ba5: lea eax, [esi + eax + 0x64] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425ba9: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425baa: push eax */
	m->esp -= 4; M32(m->esp) = 0x425bb0u; native_call(m, 0x4282f0u);	/* 425bab: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x4de054u));	/* 425bb0: mov ecx, dword ptr [0x4de054] */
	m->edx = M32((DWORD)(0x4de050u));	/* 425bb6: mov edx, dword ptr [0x4de050] */
	m->eax = M32((DWORD)(0x4de04cu));	/* 425bbc: mov eax, dword ptr [0x4de04c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425bc1: push ecx */
	m->ecx = M32((DWORD)(0x4de048u));	/* 425bc2: mov ecx, dword ptr [0x4de048] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425bc8: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425bc9: push eax */
	goto L_425c27;	/* 425bca: jmp 0x425c27 */
L_425bcc:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 425bcc: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425bd1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425bd6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425bdb: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x425be6u; native_call(m, M32(0x4a9228u));	/* 425be0: call dword ptr [0x4a9228] */
	m->ecx = M32((DWORD)(0x4ddddcu));	/* 425be6: mov ecx, dword ptr [0x4ddddc] */
	m->eax = M32((DWORD)(0x4dddd0u));	/* 425bec: mov eax, dword ptr [0x4dddd0] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 425bf1: push 1 */
	m->edx = (DWORD)(m->ecx + 0xffffffe0u);	/* 425bf3: lea edx, [ecx - 0x20] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffc0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 425bf6: add ecx, -0x40 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425bf9: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xdcu);	/* 425bfa: lea edx, [esi + eax + 0xdc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425c01: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x64u);	/* 425c02: lea eax, [esi + eax + 0x64] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425c06: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425c07: push eax */
	m->esp -= 4; M32(m->esp) = 0x425c0du; native_call(m, 0x4282f0u);	/* 425c08: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x4ddaecu));	/* 425c0d: mov ecx, dword ptr [0x4ddaec] */
	m->edx = M32((DWORD)(0x4ddae8u));	/* 425c13: mov edx, dword ptr [0x4ddae8] */
	m->eax = M32((DWORD)(0x4ddae4u));	/* 425c19: mov eax, dword ptr [0x4ddae4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425c1e: push ecx */
	m->ecx = M32((DWORD)(0x4ddae0u));	/* 425c1f: mov ecx, dword ptr [0x4ddae0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425c25: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425c26: push eax */
L_425c27:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425c27: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 425c28: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x425c32u; native_call(m, 0x41f0e0u);	/* 425c2d: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4dddd0u));	/* 425c32: mov eax, dword ptr [0x4dddd0] */
	m->ecx = M32((DWORD)(0x4ddddcu));	/* 425c37: mov ecx, dword ptr [0x4ddddc] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 425c3d: add esp, 0x28 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 425c40: add ecx, -0x38 */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xdcu);	/* 425c43: lea edx, [esi + eax + 0xdc] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 425c4a: push edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425c4b: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x64u);	/* 425c4c: lea edx, [esi + eax + 0x64] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425c50: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425c51: push edx */
	m->esp -= 4; M32(m->esp) = 0x425c57u; native_call(m, 0x4029d0u);	/* 425c52: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 425c57: add esp, 0x10 */
	{ DWORD a_ = m->edi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 425c5a: add edi, 0x80 */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 425c60: inc ebx */
	{ DWORD a_ = m->esi, b_ = 0x8cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 425c61: add esi, 0x8c */
	{ DWORD a_ = m->edi, b_ = 0x753da4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 425c67: cmp edi, 0x753da4 */
	if (m->sf != m->of) goto L_425b2a;	/* 425c6d: jl 0x425b2a */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425c73: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425c78: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425c7d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425c82: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x425c8du; native_call(m, M32(0x4a9228u));	/* 425c87: call dword ptr [0x4a9228] */
	m->eax = M32((DWORD)(0x4ddddcu));	/* 425c8d: mov eax, dword ptr [0x4ddddc] */
	m->ecx = M32((DWORD)(0x4dddd8u));	/* 425c92: mov ecx, dword ptr [0x4dddd8] */
	m->edx = M32((DWORD)(0x4dddd4u));	/* 425c98: mov edx, dword ptr [0x4dddd4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425c9e: push eax */
	m->eax = M32((DWORD)(0x4dddd0u));	/* 425c9f: mov eax, dword ptr [0x4dddd0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425ca4: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425ca5: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425ca6: push eax */
	m->esp -= 4; M32(m->esp) = 0x425cacu; native_call(m, 0x428a00u);	/* 425ca7: call 0x428a00 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 425cac: add esp, 0x10 */
	m->edi = M32(m->esp); m->esp += 4;	/* 425caf: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 425cb0: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 425cb1: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 425cb2: pop ebx */
	m->esp += 4 + 0; return;	/* 425cb3: ret  */
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
