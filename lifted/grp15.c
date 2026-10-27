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

static void lift_471040(X86 *m);

/* collision_initVolume (0x471040), lifted by tools/lift.py */
static void lift_471040(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 471040: sub esp, 0x34 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 471043: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 471044: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 471045: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 471046: push edi */
	{ DWORD v_ = 0x4c7490u; m->esp -= 4; M32(m->esp) = v_; }	/* 471047: push 0x4c7490 */
	m->edi = m->ecx;	/* 47104c: mov edi, ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47104e: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 471050: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 471052: push edi */
	M32((DWORD)(m->esp + 0x20u)) = m->edi;	/* 471053: mov dword ptr [esp + 0x20], edi */
	m->esp -= 4; M32(m->esp) = 0x47105cu; native_call(m, 0x470fc0u);	/* 471057: call 0x470fc0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x9ef914u)));	/* 47105c: fld dword ptr [edi + 0x9ef914] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x9ef908u));	/* 471062: fsub dword ptr [edi + 0x9ef908] */
	m->eax = M32((DWORD)(m->esp + 0x6cu));	/* 471068: mov eax, dword ptr [esp + 0x6c] */
	m->ecx = M32((DWORD)(m->esp + 0x68u));	/* 47106c: mov ecx, dword ptr [esp + 0x68] */
	m->edx = M32((DWORD)(m->esp + 0x64u));	/* 471070: mov edx, dword ptr [esp + 0x64] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 471074: add esp, 0x10 */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x50u));	/* 471077: fdiv dword ptr [esp + 0x50] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47107b: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47107c: push ecx */
	m->esi = (DWORD)(m->edi + 0x9ef910u);	/* 47107d: lea esi, [edi + 0x9ef910] */
	m->ebp = (DWORD)(m->edi + 0x9ef904u);	/* 471083: lea ebp, [edi + 0x9ef904] */
	m->ebx = (DWORD)(m->edi + 0xa10u);	/* 471089: lea ebx, [edi + 0xa10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47108f: push edx */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 471090: call 0x49ec14 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 471095: fld dword ptr [esi] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x0u));	/* 471097: fsub dword ptr [ebp] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47109a: push eax */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x5cu));	/* 47109b: fdiv dword ptr [esp + 0x5c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 47109f: call 0x49ec14 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x9ef918u)));	/* 4710a4: fld dword ptr [edi + 0x9ef918] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x9ef90cu));	/* 4710aa: fsub dword ptr [edi + 0x9ef90c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4710b0: push eax */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x5cu));	/* 4710b1: fdiv dword ptr [esp + 0x5c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4710b5: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4710ba: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4710bb: push esi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4710bc: push ebp */
	m->ecx = m->ebx;	/* 4710bd: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x4710c4u; native_call(m, 0x4819b0u);	/* 4710bf: call 0x4819b0 */
	{ DWORD v_ = 0x4c747cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4710c4: push 0x4c747c */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4710c9: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4710cb: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4710cd: push edi */
	m->esp -= 4; M32(m->esp) = 0x4710d3u; native_call(m, 0x470fc0u);	/* 4710ce: call 0x470fc0 */
	m->eax = M32((DWORD)(m->edi + 0x9ef30cu));	/* 4710d3: mov eax, dword ptr [edi + 0x9ef30c] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4710d9: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4710dc: test eax, eax */
	if (m->zf) goto L_47118d;	/* 4710de: je 0x47118d */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 4710e4: fld dword ptr [esi] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 4710e6: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x9ef908u)));	/* 4710ea: fld dword ptr [edi + 0x9ef908] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 4710f0: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x9ef90cu)));	/* 4710f4: fld dword ptr [edi + 0x9ef90c] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 4710fa: fstp dword ptr [esp + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x0u)));	/* 4710fe: fld dword ptr [ebp] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 471101: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x9ef908u)));	/* 471105: fld dword ptr [edi + 0x9ef908] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 47110b: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x9ef918u)));	/* 47110f: fld dword ptr [edi + 0x9ef918] */
	m->eax = m->ebp;	/* 471115: mov eax, ebp */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 471117: push -1 */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 471119: fstp dword ptr [esp + 0x38] */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47111d: mov ecx, dword ptr [eax] */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 47111f: push -1 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 471121: fld dword ptr [esi] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 471123: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 471126: mov dword ptr [esp + 0x1c], ecx */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 47112a: fstp dword ptr [esp + 0x40] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x9ef908u)));	/* 47112e: fld dword ptr [edi + 0x9ef908] */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 471134: mov eax, dword ptr [eax + 8] */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 471137: push -1 */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 471139: mov dword ptr [esp + 0x24], edx */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 47113d: push -1 */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 47113f: fstp dword ptr [esp + 0x4c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x9ef918u)));	/* 471143: fld dword ptr [edi + 0x9ef918] */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 471149: lea ecx, [esp + 0x30] */
	M32((DWORD)(m->esp + 0x2cu)) = m->eax;	/* 47114d: mov dword ptr [esp + 0x2c], eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 471151: push 0 */
	m->edx = (DWORD)(m->esp + 0x40u);	/* 471153: lea edx, [esp + 0x40] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471157: push ecx */
	m->eax = (DWORD)(m->esp + 0x2cu);	/* 471158: lea eax, [esp + 0x2c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47115c: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47115d: push eax */
	MF((DWORD)(m->esp + 0x60u)) = (float)ST(0); FPOP();	/* 47115e: fstp dword ptr [esp + 0x60] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 471162: push 0x10 */
	m->ecx = m->ebx;	/* 471164: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x47116bu; native_call(m, 0x481eb0u);	/* 471166: call 0x481eb0 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 47116b: push -1 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 47116d: push -1 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 47116f: push -1 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 471171: push -1 */
	m->ecx = (DWORD)(m->esp + 0x48u);	/* 471173: lea ecx, [esp + 0x48] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 471177: push 0 */
	m->edx = (DWORD)(m->esp + 0x40u);	/* 471179: lea edx, [esp + 0x40] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47117d: push ecx */
	m->eax = (DWORD)(m->esp + 0x38u);	/* 47117e: lea eax, [esp + 0x38] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 471182: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 471183: push eax */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 471184: push 0x10 */
	m->ecx = m->ebx;	/* 471186: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x47118du; native_call(m, 0x481eb0u);	/* 471188: call 0x481eb0 */
L_47118d:
	m->eax = M32((DWORD)(m->edi + 0xdc0a74u));	/* 47118d: mov eax, dword ptr [edi + 0xdc0a74] */
	M32((DWORD)(m->esp + 0x54u)) = 0x0u;	/* 471193: mov dword ptr [esp + 0x54], 0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47119b: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_471387;	/* 47119d: jle 0x471387 */
	m->esi = (DWORD)(m->edi + 0xdc0260u);	/* 4711a3: lea esi, [edi + 0xdc0260] */
L_4711a9:
	m->eax = M32((DWORD)(m->esi + 0xffffffe4u));	/* 4711a9: mov eax, dword ptr [esi - 0x1c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4711ac: test eax, eax */
	if (!m->zf) goto L_47128d;	/* 4711ae: jne 0x47128d */
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 4711b4: mov eax, dword ptr [esi] */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 4711b6: xor ebp, ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4711b8: test eax, eax */
	M32((DWORD)(m->esp + 0x5cu)) = m->ebp;	/* 4711ba: mov dword ptr [esp + 0x5c], ebp */
	if (m->zf || m->sf != m->of) goto L_47136a;	/* 4711be: jle 0x47136a */
L_4711c4:
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4711c4: push ebp */
	{ DWORD v_ = 0x4c7458u; m->esp -= 4; M32(m->esp) = v_; }	/* 4711c5: push 0x4c7458 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4711ca: push ebp */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4711cb: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4711cd: push edi */
	m->esp -= 4; M32(m->esp) = 0x4711d3u; native_call(m, 0x470fc0u);	/* 4711ce: call 0x470fc0 */
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 4711d3: mov eax, dword ptr [esi + 4] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4711d6: add esp, 0x14 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 4711d9: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4711db: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_471275;	/* 4711dd: jle 0x471275 */
L_4711e3:
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4711e3: inc eax */
	m->edx = M32((DWORD)(m->esi + 0x24u));	/* 4711e4: mov edx, dword ptr [esi + 0x24] */
	M32((DWORD)(m->esp + 0x58u)) = m->eax;	/* 4711e7: mov dword ptr [esp + 0x58], eax */
	{ long long p_ = (long long)(int)m->eax * (int)m->ebp; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 4711eb: imul eax, ebp */
	m->ecx = (DWORD)(m->eax + m->edi*1 + 0x0u);	/* 4711ee: lea ecx, [eax + edi] */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 4711f1: push -1 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 4711f3: push -1 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 4711f5: push -1 */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x3u);	/* 4711f7: lea eax, [ecx + ecx*2 + 3] */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 4711fb: push -1 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4711fd: push 0 */
	m->ecx = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 4711ff: lea ecx, [ecx + ecx*2] */
	m->eax = (DWORD)(m->edx + m->eax*4 + 0x0u);	/* 471202: lea eax, [edx + eax*4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 471205: push eax */
	m->eax = (DWORD)(m->ebp + 0x1u);	/* 471206: lea eax, [ebp + 1] */
	{ long long p_ = (long long)(int)m->eax * (int)M32((DWORD)(m->esp + 0x70u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 471209: imul eax, dword ptr [esp + 0x70] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 47120e: add eax, edi */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 471210: lea eax, [eax + eax*2] */
	m->eax = (DWORD)(m->edx + m->eax*4 + 0x0u);	/* 471213: lea eax, [edx + eax*4] */
	m->edx = (DWORD)(m->edx + m->ecx*4 + 0x0u);	/* 471216: lea edx, [edx + ecx*4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 471219: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47121a: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47121b: push 0 */
	m->ecx = m->ebx;	/* 47121d: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x471224u; native_call(m, 0x481eb0u);	/* 47121f: call 0x481eb0 */
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 471224: mov eax, dword ptr [esi + 4] */
	m->ecx = M32((DWORD)(m->esp + 0x5cu));	/* 471227: mov ecx, dword ptr [esp + 0x5c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 47122b: inc eax */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 47122c: inc ecx */
	{ long long p_ = (long long)(int)m->ecx * (int)m->eax; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ecx = r_; }	/* 47122d: imul ecx, eax */
	m->edx = M32((DWORD)(m->esi + 0x24u));	/* 471230: mov edx, dword ptr [esi + 0x24] */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 471233: add ecx, edi */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 471235: push -1 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 471237: push -1 */
	m->ebp = (DWORD)(m->ecx + m->ecx*2 + 0x3u);	/* 471239: lea ebp, [ecx + ecx*2 + 3] */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 47123d: push -1 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 47123f: push -1 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 471241: push 0 */
	m->ebp = (DWORD)(m->edx + m->ebp*4 + 0x0u);	/* 471243: lea ebp, [edx + ebp*4] */
	m->ecx = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 471246: lea ecx, [ecx + ecx*2] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 471249: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x74u));	/* 47124a: mov ebp, dword ptr [esp + 0x74] */
	{ long long p_ = (long long)(int)m->eax * (int)m->ebp; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 47124e: imul eax, ebp */
	m->ecx = (DWORD)(m->edx + m->ecx*4 + 0x0u);	/* 471251: lea ecx, [edx + ecx*4] */
	m->eax = (DWORD)(m->eax + m->edi*1 + 0x1u);	/* 471254: lea eax, [eax + edi + 1] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471258: push ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 471259: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->edx + m->eax*4 + 0x0u);	/* 47125c: lea ecx, [edx + eax*4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47125f: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 471260: push 0 */
	m->ecx = m->ebx;	/* 471262: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x471269u; native_call(m, 0x481eb0u);	/* 471264: call 0x481eb0 */
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 471269: mov eax, dword ptr [esi + 4] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 47126c: inc edi */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47126d: cmp edi, eax */
	if (m->sf != m->of) goto L_4711e3;	/* 47126f: jl 0x4711e3 */
L_471275:
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 471275: mov eax, dword ptr [esi] */
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 471277: mov edi, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 47127b: inc ebp */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47127c: cmp ebp, eax */
	M32((DWORD)(m->esp + 0x5cu)) = m->ebp;	/* 47127e: mov dword ptr [esp + 0x5c], ebp */
	if (m->sf != m->of) goto L_4711c4;	/* 471282: jl 0x4711c4 */
	goto L_47136a;	/* 471288: jmp 0x47136a */
L_47128d:
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47128d: cmp eax, 1 */
	if (!m->zf) goto L_47136a;	/* 471290: jne 0x47136a */
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 471296: mov eax, dword ptr [esi] */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 471298: xor ebp, ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47129a: test eax, eax */
	M32((DWORD)(m->esp + 0x5cu)) = m->ebp;	/* 47129c: mov dword ptr [esp + 0x5c], ebp */
	if (m->zf || m->sf != m->of) goto L_47136a;	/* 4712a0: jle 0x47136a */
L_4712a6:
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4712a6: push ebp */
	{ DWORD v_ = 0x4c7430u; m->esp -= 4; M32(m->esp) = v_; }	/* 4712a7: push 0x4c7430 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4712ac: push ebp */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4712ad: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4712af: push edi */
	m->esp -= 4; M32(m->esp) = 0x4712b5u; native_call(m, 0x470fc0u);	/* 4712b0: call 0x470fc0 */
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 4712b5: mov eax, dword ptr [esi + 4] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4712b8: add esp, 0x14 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 4712bb: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4712bd: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_471357;	/* 4712bf: jle 0x471357 */
L_4712c5:
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4712c5: inc eax */
	m->edx = M32((DWORD)(m->esi + 0x24u));	/* 4712c6: mov edx, dword ptr [esi + 0x24] */
	M32((DWORD)(m->esp + 0x58u)) = m->eax;	/* 4712c9: mov dword ptr [esp + 0x58], eax */
	{ long long p_ = (long long)(int)m->eax * (int)m->ebp; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 4712cd: imul eax, ebp */
	m->ecx = (DWORD)(m->eax + m->edi*1 + 0x0u);	/* 4712d0: lea ecx, [eax + edi] */
	m->eax = (DWORD)(m->ebp + 0x1u);	/* 4712d3: lea eax, [ebp + 1] */
	{ long long p_ = (long long)(int)m->eax * (int)M32((DWORD)(m->esp + 0x58u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 4712d6: imul eax, dword ptr [esp + 0x58] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4712db: add eax, edi */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 4712dd: push -1 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 4712df: push -1 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 4712e1: push -1 */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 4712e3: lea eax, [eax + eax*2] */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 4712e6: push -1 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4712e8: push 0 */
	m->eax = (DWORD)(m->edx + m->eax*4 + 0x0u);	/* 4712ea: lea eax, [edx + eax*4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4712ed: push eax */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x3u);	/* 4712ee: lea eax, [ecx + ecx*2 + 3] */
	m->ecx = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 4712f2: lea ecx, [ecx + ecx*2] */
	m->eax = (DWORD)(m->edx + m->eax*4 + 0x0u);	/* 4712f5: lea eax, [edx + eax*4] */
	m->edx = (DWORD)(m->edx + m->ecx*4 + 0x0u);	/* 4712f8: lea edx, [edx + ecx*4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4712fb: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4712fc: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4712fd: push 0 */
	m->ecx = m->ebx;	/* 4712ff: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x471306u; native_call(m, 0x481eb0u);	/* 471301: call 0x481eb0 */
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 471306: mov eax, dword ptr [esi + 4] */
	m->ecx = M32((DWORD)(m->esp + 0x5cu));	/* 471309: mov ecx, dword ptr [esp + 0x5c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 47130d: inc eax */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 47130e: inc ecx */
	{ long long p_ = (long long)(int)m->ecx * (int)m->eax; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ecx = r_; }	/* 47130f: imul ecx, eax */
	m->edx = M32((DWORD)(m->esi + 0x24u));	/* 471312: mov edx, dword ptr [esi + 0x24] */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 471315: add ecx, edi */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 471317: push -1 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 471319: push -1 */
	m->ebp = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 47131b: lea ebp, [ecx + ecx*2] */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 47131e: push -1 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 471320: push -1 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 471322: push 0 */
	m->ebp = (DWORD)(m->edx + m->ebp*4 + 0x0u);	/* 471324: lea ebp, [edx + ebp*4] */
	m->ecx = (DWORD)(m->ecx + m->ecx*2 + 0x3u);	/* 471327: lea ecx, [ecx + ecx*2 + 3] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 47132b: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x74u));	/* 47132c: mov ebp, dword ptr [esp + 0x74] */
	{ long long p_ = (long long)(int)m->eax * (int)m->ebp; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 471330: imul eax, ebp */
	m->ecx = (DWORD)(m->edx + m->ecx*4 + 0x0u);	/* 471333: lea ecx, [edx + ecx*4] */
	m->eax = (DWORD)(m->eax + m->edi*1 + 0x1u);	/* 471336: lea eax, [eax + edi + 1] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47133a: push ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 47133b: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->edx + m->eax*4 + 0x0u);	/* 47133e: lea ecx, [edx + eax*4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471341: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 471342: push 0 */
	m->ecx = m->ebx;	/* 471344: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x47134bu; native_call(m, 0x481eb0u);	/* 471346: call 0x481eb0 */
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 47134b: mov eax, dword ptr [esi + 4] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 47134e: inc edi */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47134f: cmp edi, eax */
	if (m->sf != m->of) goto L_4712c5;	/* 471351: jl 0x4712c5 */
L_471357:
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 471357: mov eax, dword ptr [esi] */
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 471359: mov edi, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 47135d: inc ebp */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47135e: cmp ebp, eax */
	M32((DWORD)(m->esp + 0x5cu)) = m->ebp;	/* 471360: mov dword ptr [esp + 0x5c], ebp */
	if (m->sf != m->of) goto L_4712a6;	/* 471364: jl 0x4712a6 */
L_47136a:
	m->eax = M32((DWORD)(m->esp + 0x54u));	/* 47136a: mov eax, dword ptr [esp + 0x54] */
	m->ecx = M32((DWORD)(m->edi + 0xdc0a74u));	/* 47136e: mov ecx, dword ptr [edi + 0xdc0a74] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 471374: inc eax */
	{ DWORD a_ = m->esi, b_ = 0x20cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 471375: add esi, 0x20c */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47137b: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x54u)) = m->eax;	/* 47137d: mov dword ptr [esp + 0x54], eax */
	if (m->sf != m->of) goto L_4711a9;	/* 471381: jl 0x4711a9 */
L_471387:
	m->eax = M32((DWORD)(m->edi + 0x13c9b24u));	/* 471387: mov eax, dword ptr [edi + 0x13c9b24] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 47138d: xor esi, esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47138f: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_4713f5;	/* 471391: jle 0x4713f5 */
	m->ebp = (DWORD)(m->edi + 0x131ae50u);	/* 471393: lea ebp, [edi + 0x131ae50] */
L_471399:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0xfffffff8u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 471399: cmp dword ptr [ebp - 8], 1 */
	if (!m->zf) goto L_4713e4;	/* 47139d: jne 0x4713e4 */
	{ DWORD a_ = M8((DWORD)(m->ebp + 0x0u)), b_ = 0x4u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47139f: test byte ptr [ebp], 4 */
	if (!m->zf) goto L_4713e4;	/* 4713a3: jne 0x4713e4 */
	m->edx = m->esi;	/* 4713a5: mov edx, esi */
	{ DWORD a_ = m->edx, b_ = 0x80000001u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4713a7: and edx, 0x80000001 */
	if (!m->sf) goto L_4713b4;	/* 4713ad: jns 0x4713b4 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 4713af: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffffeu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4713b0: or edx, 0xfffffffe */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 4713b3: inc edx */
L_4713b4:
	if (!m->zf) goto L_4713c8;	/* 4713b4: jne 0x4713c8 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4713b6: push esi */
	{ DWORD v_ = 0x4c7418u; m->esp -= 4; M32(m->esp) = v_; }	/* 4713b7: push 0x4c7418 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4713bc: push esi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4713bd: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4713bf: push edi */
	m->esp -= 4; M32(m->esp) = 0x4713c5u; native_call(m, 0x470fc0u);	/* 4713c0: call 0x470fc0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4713c5: add esp, 0x14 */
L_4713c8:
	m->ecx = M32((DWORD)(m->ebp + 0x270u));	/* 4713c8: mov ecx, dword ptr [ebp + 0x270] */
	m->eax = (DWORD)(m->ebp + 0xe8u);	/* 4713ce: lea eax, [ebp + 0xe8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4713d4: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4713d5: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4713d6: push esi */
	m->ecx = m->ebx;	/* 4713d7: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x4713deu; native_call(m, 0x4823c0u);	/* 4713d9: call 0x4823c0 */
	M32((DWORD)(m->ebp + 0x280u)) = m->eax;	/* 4713de: mov dword ptr [ebp + 0x280], eax */
L_4713e4:
	m->eax = M32((DWORD)(m->edi + 0x13c9b24u));	/* 4713e4: mov eax, dword ptr [edi + 0x13c9b24] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 4713ea: inc esi */
	{ DWORD a_ = m->ebp, b_ = 0x2ccu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 4713eb: add ebp, 0x2cc */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4713f1: cmp esi, eax */
	if (m->sf != m->of) goto L_471399;	/* 4713f3: jl 0x471399 */
L_4713f5:
	m->edi = M32(m->esp); m->esp += 4;	/* 4713f5: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4713f6: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4713f7: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4713f8: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4713f9: add esp, 0x34 */
	m->esp += 4 + 24; return;	/* 4713fc: ret 0x18 */
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
