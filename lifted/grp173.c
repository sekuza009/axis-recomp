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

static void lift_4580b0(X86 *m);

/* actor_processFrame (0x4580b0), lifted by tools/lift.py */
static void lift_4580b0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x2a0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4580b0: sub esp, 0x2a0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4580b6: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4580b7: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4580b8: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4580b9: push edi */
	m->edi = M32((DWORD)(m->esp + 0x2b4u));	/* 4580ba: mov edi, dword ptr [esp + 0x2b4] */
	m->ebx = m->ecx;	/* 4580c1: mov ebx, ecx */
	m->eax = m->edi;	/* 4580c3: mov eax, edi */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4580c5: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4580c8: add eax, edi */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4580ca: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4580cd: add eax, edi */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4580cf: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4580d2: add eax, edi */
	m->ecx = M32((DWORD)(m->ebx + m->eax*8 + 0x1cd94b4u));	/* 4580d4: mov ecx, dword ptr [ebx + eax*8 + 0x1cd94b4] */
	m->ebp = (DWORD)(m->ebx + m->eax*8 + 0x1cd93a8u);	/* 4580db: lea ebp, [ebx + eax*8 + 0x1cd93a8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x120u)));	/* 4580e2: fld dword ptr [ebp + 0x120] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 4580e8: lea eax, [ecx + ecx*2] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x124u)); FPOP();	/* 4580eb: fcomp dword ptr [ebp + 0x124] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4580f1: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4580f4: sub eax, ecx */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 4580f6: lea edx, [eax + eax*2] */
	m->eax = (DWORD)(m->ecx + m->edx*8 + 0x0u);	/* 4580f9: lea eax, [ecx + edx*8] */
	m->esi = (DWORD)(m->ebx + m->eax*2 + 0x1561b68u);	/* 4580fc: lea esi, [ebx + eax*2 + 0x1561b68] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 458103: fnstsw ax */
	M32((DWORD)(m->esp + 0x50u)) = m->esi;	/* 458105: mov dword ptr [esp + 0x50], esi */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 458109: test ah, 0x41 */
	if (!m->zf) goto L_458139;	/* 45810c: jne 0x458139 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45810e: push edi */
	m->ecx = m->ebx;	/* 45810f: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x458116u; native_call(m, 0x45dca0u);	/* 458111: call 0x45dca0 */
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x202e8d8u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 458116: cmp dword ptr [ebx + 0x202e8d8], edi */
	if (!m->zf) goto L_45d395;	/* 45811c: jne 0x45d395 */
	m->edi = M32(m->esp); m->esp += 4;	/* 458122: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 458123: pop esi */
	M32((DWORD)(m->ebx + 0x202e8d8u)) = 0xffffffffu;	/* 458124: mov dword ptr [ebx + 0x202e8d8], 0xffffffff */
	m->ebp = M32(m->esp); m->esp += 4;	/* 45812e: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 45812f: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x2a0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 458130: add esp, 0x2a0 */
	m->esp += 4 + 8; return;	/* 458136: ret 8 */
L_458139:
	m->ecx = M32((DWORD)(m->ebp + 0x110u));	/* 458139: mov ecx, dword ptr [ebp + 0x110] */
	m->eax = M32((DWORD)(m->ebx + 0x202e8d4u));	/* 45813f: mov eax, dword ptr [ebx + 0x202e8d4] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 458145: cmp ecx, eax */
	if (!m->zf) goto L_458153;	/* 458147: jne 0x458153 */
	m->eax = M32((DWORD)(m->ebp + 0x11cu));	/* 458149: mov eax, dword ptr [ebp + 0x11c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45814f: test eax, eax */
	if (m->zf) goto L_45815b;	/* 458151: je 0x45815b */
L_458153:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 458153: push edi */
	m->ecx = m->ebx;	/* 458154: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x45815bu; native_call(m, 0x45eab0u);	/* 458156: call 0x45eab0 */
L_45815b:
	m->ecx = M32((DWORD)(m->esi + 0x310u));	/* 45815b: mov ecx, dword ptr [esi + 0x310] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 458161: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 458164: shl eax, 3 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 458167: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 458169: lea eax, [eax + eax*4] */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45816c: shl eax, 1 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45816e: sub eax, ecx */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 458170: lea edx, [eax + eax*2] */
	m->eax = (DWORD)(m->ebx + m->edx*4 + 0x13eb004u);	/* 458173: lea eax, [ebx + edx*4 + 0x13eb004] */
	M32((DWORD)(m->esp + 0x4cu)) = m->eax;	/* 45817a: mov dword ptr [esp + 0x4c], eax */
	m->eax = M32((DWORD)(m->esi + 0x314u));	/* 45817e: mov eax, dword ptr [esi + 0x314] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 458184: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 458187: lea edx, [eax + ecx*2] */
	{ DWORD a_ = m->edx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45818a: shl edx, 8 */
	m->eax = (DWORD)(m->edx + m->ebx*1 + 0x140c8c0u);	/* 45818d: lea eax, [edx + ebx + 0x140c8c0] */
	M32((DWORD)(m->esp + 0x7cu)) = m->eax;	/* 458194: mov dword ptr [esp + 0x7c], eax */
	m->eax = M32((DWORD)(m->esi + 0x318u));	/* 458198: mov eax, dword ptr [esi + 0x318] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45819e: lea ecx, [eax + eax*4] */
	{ DWORD a_ = m->ecx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4581a1: shl ecx, 6 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4581a4: sub ecx, eax */
	m->edx = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 4581a6: lea edx, [eax + ecx*4] */
	m->eax = (DWORD)(m->ebx + m->edx*4 + 0x1447ec4u);	/* 4581a9: lea eax, [ebx + edx*4 + 0x1447ec4] */
	M32((DWORD)(m->esp + 0xc0u)) = m->eax;	/* 4581b0: mov dword ptr [esp + 0xc0], eax */
	m->eax = M32((DWORD)(m->esi + 0x31cu));	/* 4581b7: mov eax, dword ptr [esi + 0x31c] */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 4581bd: lea ecx, [eax + eax*2] */
	{ DWORD a_ = m->ecx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4581c0: shl ecx, 6 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4581c3: add ecx, eax */
	m->eax = M32((DWORD)(m->ebp + 0x484u));	/* 4581c5: mov eax, dword ptr [ebp + 0x484] */
	{ DWORD a_ = m->ecx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4581cb: shl ecx, 5 */
	m->edx = (DWORD)(m->ecx + m->ebx*1 + 0x1486470u);	/* 4581ce: lea edx, [ecx + ebx + 0x1486470] */
	m->ecx = M32((DWORD)(m->ebp + 0x488u));	/* 4581d5: mov ecx, dword ptr [ebp + 0x488] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4581db: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x80u)) = m->edx;	/* 4581dd: mov dword ptr [esp + 0x80], edx */
	if (m->zf) goto L_45821a;	/* 4581e4: je 0x45821a */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4581e6: push edi */
	m->ecx = m->ebx;	/* 4581e7: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x4581eeu; native_call(m, 0x45e1f0u);	/* 4581e9: call 0x45e1f0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4581ee: push edi */
	m->ecx = m->ebx;	/* 4581ef: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x4581f6u; native_call(m, 0x45e2c0u);	/* 4581f1: call 0x45e2c0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4581f6: push edi */
	m->ecx = m->ebx;	/* 4581f7: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x4581feu; native_call(m, 0x45e390u);	/* 4581f9: call 0x45e390 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4581fe: push edi */
	m->ecx = m->ebx;	/* 4581ff: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x458206u; native_call(m, 0x45e460u);	/* 458201: call 0x45e460 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 458206: push edi */
	m->ecx = m->ebx;	/* 458207: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x45820eu; native_call(m, 0x45e530u);	/* 458209: call 0x45e530 */
	m->ecx = M32((DWORD)(m->ebp + 0x484u));	/* 45820e: mov ecx, dword ptr [ebp + 0x484] */
	M32((DWORD)(m->ebp + 0x488u)) = m->ecx;	/* 458214: mov dword ptr [ebp + 0x488], ecx */
L_45821a:
	m->edx = M32((DWORD)(m->ebp + 0x140u));	/* 45821a: mov edx, dword ptr [ebp + 0x140] */
	m->ecx = M32((DWORD)(m->esi + m->edx*4 + 0x320u));	/* 458220: mov ecx, dword ptr [esi + edx*4 + 0x320] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 458227: test ecx, ecx */
	if (m->sf != m->of) goto L_458246;	/* 458229: jl 0x458246 */
	m->eax = m->ecx;	/* 45822b: mov eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45822d: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 458230: sub eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 458232: shl eax, 2 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 458235: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 458237: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45823a: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->ebx + m->eax*8 + 0x14d1ab4u);	/* 45823d: lea eax, [ebx + eax*8 + 0x14d1ab4] */
	goto L_458248;	/* 458244: jmp 0x458248 */
L_458246:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 458246: xor eax, eax */
L_458248:
	m->ecx = M32((DWORD)(m->ebp + 0x110u));	/* 458248: mov ecx, dword ptr [ebp + 0x110] */
	m->edx = M32((DWORD)(m->ebx + 0x202e8d4u));	/* 45824e: mov edx, dword ptr [ebx + 0x202e8d4] */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 458254: cmp ecx, edx */
	M32((DWORD)(m->esp + 0x34u)) = m->eax;	/* 458256: mov dword ptr [esp + 0x34], eax */
	if (!m->zf) goto L_4582bc;	/* 45825a: jne 0x4582bc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45825c: test eax, eax */
	if (m->zf) goto L_4582bc;	/* 45825e: je 0x4582bc */
	m->edx = M32((DWORD)(m->eax + 0x2dc0u));	/* 458260: mov edx, dword ptr [eax + 0x2dc0] */
	m->ecx = M32((DWORD)(m->ebp + m->edx*4 + 0x130u));	/* 458266: mov ecx, dword ptr [ebp + edx*4 + 0x130] */
	m->edx = M32((DWORD)(m->eax + 0x2dc4u));	/* 45826d: mov edx, dword ptr [eax + 0x2dc4] */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 458273: cmp ecx, edx */
	if (m->sf == m->of) goto L_4582bc;	/* 458275: jge 0x4582bc */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x490u)));	/* 458277: fld dword ptr [ebp + 0x490] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 45827d: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 458283: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 458285: test ah, 1 */
	if (!m->zf) goto L_4582bc;	/* 458288: jne 0x4582bc */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45828a: push edi */
	m->ecx = m->ebx;	/* 45828b: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x458292u; native_call(m, 0x45e9e0u);	/* 45828d: call 0x45e9e0 */
	m->edx = M32((DWORD)(m->ebp + 0x140u));	/* 458292: mov edx, dword ptr [ebp + 0x140] */
	m->ecx = M32((DWORD)(m->esi + m->edx*4 + 0x320u));	/* 458298: mov ecx, dword ptr [esi + edx*4 + 0x320] */
	m->eax = m->ecx;	/* 45829f: mov eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4582a1: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4582a4: sub eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4582a6: shl eax, 2 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4582a9: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4582ab: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4582ae: lea eax, [eax + eax*4] */
	m->ecx = (DWORD)(m->ebx + m->eax*8 + 0x14d1ab4u);	/* 4582b1: lea ecx, [ebx + eax*8 + 0x14d1ab4] */
	M32((DWORD)(m->esp + 0x34u)) = m->ecx;	/* 4582b8: mov dword ptr [esp + 0x34], ecx */
L_4582bc:
	m->eax = M32((DWORD)(m->ebp + 0x478u));	/* 4582bc: mov eax, dword ptr [ebp + 0x478] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4582c2: test eax, eax */
	if (m->sf != m->of) goto L_4582cf;	/* 4582c4: jl 0x4582cf */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4582c6: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4582c7: push edi */
	m->ecx = m->ebx;	/* 4582c8: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x4582cfu; native_call(m, 0x45e880u);	/* 4582ca: call 0x45e880 */
L_4582cf:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x47cu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4582cf: cmp dword ptr [ebp + 0x47c], 1 */
	if (!m->zf) goto L_4582e0;	/* 4582d6: jne 0x4582e0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4582d8: push edi */
	m->ecx = m->ebx;	/* 4582d9: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x4582e0u; native_call(m, 0x45e910u);	/* 4582db: call 0x45e910 */
L_4582e0:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x480u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4582e0: cmp dword ptr [ebp + 0x480], 1 */
	if (!m->zf) goto L_4582f1;	/* 4582e7: jne 0x4582f1 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4582e9: push edi */
	m->ecx = m->ebx;	/* 4582ea: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x4582f1u; native_call(m, 0x45e9e0u);	/* 4582ec: call 0x45e9e0 */
L_4582f1:
	{ DWORD a_ = m->edi, b_ = M32((DWORD)(m->ebx + 0x202e8d8u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4582f1: cmp edi, dword ptr [ebx + 0x202e8d8] */
	if (!m->zf) goto L_458318;	/* 4582f7: jne 0x458318 */
	m->eax = M32((DWORD)(m->ebp + 0x49cu));	/* 4582f9: mov eax, dword ptr [ebp + 0x49c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4582ff: test eax, eax */
	if (m->zf) goto L_458361;	/* 458301: je 0x458361 */
	M32((DWORD)(m->ebp + 0x49cu)) = 0x0u;	/* 458303: mov dword ptr [ebp + 0x49c], 0 */
	m->edx = M32((DWORD)(m->ebp + 0x140u));	/* 45830d: mov edx, dword ptr [ebp + 0x140] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 458313: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 458315: push edx */
	goto L_458359;	/* 458316: jmp 0x458359 */
L_458318:
	m->eax = M32((DWORD)(m->ebp + 0x484u));	/* 458318: mov eax, dword ptr [ebp + 0x484] */
	m->ecx = M32((DWORD)(m->ebp + 0x49cu));	/* 45831e: mov ecx, dword ptr [ebp + 0x49c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 458324: inc eax */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 458325: cmp ecx, eax */
	if (m->zf) goto L_458361;	/* 458327: je 0x458361 */
	M32((DWORD)(m->ebp + 0x49cu)) = m->eax;	/* 458329: mov dword ptr [ebp + 0x49c], eax */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45832f: push eax */
	m->eax = M32((DWORD)(m->ebp + 0x144u));	/* 458330: mov eax, dword ptr [ebp + 0x144] */
	m->ecx = m->ebx;	/* 458336: mov ecx, ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 458338: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 458339: push edi */
	m->esp -= 4; M32(m->esp) = 0x45833fu; native_call(m, 0x45e600u);	/* 45833a: call 0x45e600 */
	m->ecx = M32((DWORD)(m->ebp + 0x49cu));	/* 45833f: mov ecx, dword ptr [ebp + 0x49c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 458345: push ecx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 458346: push 4 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 458348: push edi */
	m->ecx = m->ebx;	/* 458349: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x458350u; native_call(m, 0x45e600u);	/* 45834b: call 0x45e600 */
	m->edx = M32((DWORD)(m->ebp + 0x49cu));	/* 458350: mov edx, dword ptr [ebp + 0x49c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 458356: push edx */
	{ DWORD v_ = 0x5u; m->esp -= 4; M32(m->esp) = v_; }	/* 458357: push 5 */
L_458359:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 458359: push edi */
	m->ecx = m->ebx;	/* 45835a: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x458361u; native_call(m, 0x45e600u);	/* 45835c: call 0x45e600 */
L_458361:
	m->eax = M32((DWORD)(m->ebp + 0x110u));	/* 458361: mov eax, dword ptr [ebp + 0x110] */
	m->ecx = M32((DWORD)(m->ebx + 0x202e8d4u));	/* 458367: mov ecx, dword ptr [ebx + 0x202e8d4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45836d: cmp eax, ecx */
	if (m->zf) goto L_4583a1;	/* 45836f: je 0x4583a1 */
	m->eax = M32((DWORD)(m->ebp + 0x48cu));	/* 458371: mov eax, dword ptr [ebp + 0x48c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 458377: test eax, eax */
	if (!m->zf) goto L_4583a1;	/* 458379: jne 0x4583a1 */
	m->eax = M32((DWORD)(m->ebp + 0x140u));	/* 45837b: mov eax, dword ptr [ebp + 0x140] */
	m->ecx = M32((DWORD)(m->ebp + 0x498u));	/* 458381: mov ecx, dword ptr [ebp + 0x498] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 458387: cmp ecx, eax */
	if (m->zf) goto L_4583a1;	/* 458389: je 0x4583a1 */
	M32((DWORD)(m->ebp + 0x498u)) = m->eax;	/* 45838b: mov dword ptr [ebp + 0x498], eax */
	m->ecx = M32((DWORD)(m->ebp + 0x49cu));	/* 458391: mov ecx, dword ptr [ebp + 0x49c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 458397: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 458398: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 458399: push edi */
	m->ecx = m->ebx;	/* 45839a: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x4583a1u; native_call(m, 0x45e600u);	/* 45839c: call 0x45e600 */
L_4583a1:
	m->eax = M32((DWORD)(m->ebp + 0x140u));	/* 4583a1: mov eax, dword ptr [ebp + 0x140] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4583a7: cmp eax, 4 */
	if (!m->zf) goto L_4583b8;	/* 4583aa: jne 0x4583b8 */
	m->edx = (DWORD)(m->ebp + 0x587cu);	/* 4583ac: lea edx, [ebp + 0x587c] */
	M32((DWORD)(m->esp + 0x54u)) = m->edx;	/* 4583b2: mov dword ptr [esp + 0x54], edx */
	goto L_4583d3;	/* 4583b6: jmp 0x4583d3 */
L_4583b8:
	{ DWORD a_ = m->eax, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4583b8: cmp eax, 5 */
	if (!m->zf) goto L_4583c9;	/* 4583bb: jne 0x4583c9 */
	m->eax = (DWORD)(m->ebp + 0x701cu);	/* 4583bd: lea eax, [ebp + 0x701c] */
	M32((DWORD)(m->esp + 0x54u)) = m->eax;	/* 4583c3: mov dword ptr [esp + 0x54], eax */
	goto L_4583d3;	/* 4583c7: jmp 0x4583d3 */
L_4583c9:
	m->ecx = (DWORD)(m->ebp + 0x40dcu);	/* 4583c9: lea ecx, [ebp + 0x40dc] */
	M32((DWORD)(m->esp + 0x54u)) = m->ecx;	/* 4583cf: mov dword ptr [esp + 0x54], ecx */
L_4583d3:
	m->eax = M32((DWORD)(m->ebp + 0x14cu));	/* 4583d3: mov eax, dword ptr [ebp + 0x14c] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4583d9: cmp eax, 1 */
	m->eax = (DWORD)(m->ebp + 0x154u);	/* 4583dc: lea eax, [ebp + 0x154] */
	if (!m->zf) goto L_458400;	/* 4583e2: jne 0x458400 */
	m->edx = (DWORD)(m->ebp + 0x180u);	/* 4583e4: lea edx, [ebp + 0x180] */
	m->ecx = M32((DWORD)(m->ebp + 0x180u));	/* 4583ea: mov ecx, dword ptr [ebp + 0x180] */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 4583f0: mov dword ptr [eax], ecx */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 4583f2: mov ecx, dword ptr [edx + 4] */
	M32((DWORD)(m->eax + 0x4u)) = m->ecx;	/* 4583f5: mov dword ptr [eax + 4], ecx */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 4583f8: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 4583fb: mov dword ptr [eax + 8], edx */
	goto L_45841a;	/* 4583fe: jmp 0x45841a */
L_458400:
	m->ecx = (DWORD)(m->ebp + 0x4e0u);	/* 458400: lea ecx, [ebp + 0x4e0] */
	m->edx = M32((DWORD)(m->ebp + 0x4e0u));	/* 458406: mov edx, dword ptr [ebp + 0x4e0] */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 45840c: mov dword ptr [eax], edx */
	m->edx = M32((DWORD)(m->ecx + 0x4u));	/* 45840e: mov edx, dword ptr [ecx + 4] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 458411: mov dword ptr [eax + 4], edx */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 458414: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 458417: mov dword ptr [eax + 8], ecx */
L_45841a:
	m->edx = M32((DWORD)(m->ebp + 0x18cu));	/* 45841a: mov edx, dword ptr [ebp + 0x18c] */
	M32((DWORD)(m->ebp + 0x160u)) = m->edx;	/* 458420: mov dword ptr [ebp + 0x160], edx */
	m->eax = M32((DWORD)(m->ebp + 0x190u));	/* 458426: mov eax, dword ptr [ebp + 0x190] */
	M32((DWORD)(m->ebp + 0x164u)) = m->eax;	/* 45842c: mov dword ptr [ebp + 0x164], eax */
	m->ecx = M32((DWORD)(m->ebp + 0x194u));	/* 458432: mov ecx, dword ptr [ebp + 0x194] */
	M32((DWORD)(m->ebp + 0x168u)) = m->ecx;	/* 458438: mov dword ptr [ebp + 0x168], ecx */
	m->edx = M32((DWORD)(m->ebp + 0x198u));	/* 45843e: mov edx, dword ptr [ebp + 0x198] */
	M32((DWORD)(m->ebp + 0x16cu)) = m->edx;	/* 458444: mov dword ptr [ebp + 0x16c], edx */
	m->eax = M32((DWORD)(m->ebp + 0x19cu));	/* 45844a: mov eax, dword ptr [ebp + 0x19c] */
	M32((DWORD)(m->ebp + 0x170u)) = m->eax;	/* 458450: mov dword ptr [ebp + 0x170], eax */
	m->ecx = M32((DWORD)(m->ebp + 0x1a0u));	/* 458456: mov ecx, dword ptr [ebp + 0x1a0] */
	M32((DWORD)(m->ebp + 0x174u)) = m->ecx;	/* 45845c: mov dword ptr [ebp + 0x174], ecx */
	m->edx = M32((DWORD)(m->ebp + 0x1a4u));	/* 458462: mov edx, dword ptr [ebp + 0x1a4] */
	M32((DWORD)(m->ebp + 0x178u)) = m->edx;	/* 458468: mov dword ptr [ebp + 0x178], edx */
	m->eax = M32((DWORD)(m->ebp + 0x1a8u));	/* 45846e: mov eax, dword ptr [ebp + 0x1a8] */
	M32((DWORD)(m->ebp + 0x17cu)) = m->eax;	/* 458474: mov dword ptr [ebp + 0x17c], eax */
	m->ecx = M32((DWORD)(m->ebp + 0x110u));	/* 45847a: mov ecx, dword ptr [ebp + 0x110] */
	{ DWORD a_ = m->ecx, b_ = M32((DWORD)(m->ebx + 0x202e8d4u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 458480: cmp ecx, dword ptr [ebx + 0x202e8d4] */
	if (!m->zf) goto L_459928;	/* 458486: jne 0x459928 */
	m->eax = M32((DWORD)(m->ebx + 0x20f3ad4u));	/* 45848c: mov eax, dword ptr [ebx + 0x20f3ad4] */
	m->edi = 0x1u;	/* 458492: mov edi, 1 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 458497: cmp eax, edi */
	if (!m->zf) goto L_4584f0;	/* 458499: jne 0x4584f0 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x4d8u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45849b: cmp dword ptr [ebp + 0x4d8], edi */
	if (!m->zf) goto L_4584b6;	/* 4584a1: jne 0x4584b6 */
	m->eax = 0x447a0000u;	/* 4584a3: mov eax, 0x447a0000 */
	M32((DWORD)(m->ebp + 0x3f4u)) = m->eax;	/* 4584a8: mov dword ptr [ebp + 0x3f4], eax */
	M32((DWORD)(m->ebp + 0x3fcu)) = m->eax;	/* 4584ae: mov dword ptr [ebp + 0x3fc], eax */
	goto L_4584f0;	/* 4584b4: jmp 0x4584f0 */
L_4584b6:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x3f4u)));	/* 4584b6: fld dword ptr [ebp + 0x3f4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a940cu)); FPOP();	/* 4584bc: fcomp dword ptr [0x4a940c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4584c2: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4584c4: test ah, 0x41 */
	if (!m->zf) goto L_4584d3;	/* 4584c7: jne 0x4584d3 */
	M32((DWORD)(m->ebp + 0x3f4u)) = 0x0u;	/* 4584c9: mov dword ptr [ebp + 0x3f4], 0 */
L_4584d3:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x3fcu)));	/* 4584d3: fld dword ptr [ebp + 0x3fc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a940cu)); FPOP();	/* 4584d9: fcomp dword ptr [0x4a940c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4584df: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4584e1: test ah, 0x41 */
	if (!m->zf) goto L_4584f0;	/* 4584e4: jne 0x4584f0 */
	M32((DWORD)(m->ebp + 0x3fcu)) = 0x0u;	/* 4584e6: mov dword ptr [ebp + 0x3fc], 0 */
L_4584f0:
	M32((DWORD)(m->ebp + 0x87f4u)) = 0x0u;	/* 4584f0: mov dword ptr [ebp + 0x87f4], 0 */
	m->eax = M32((DWORD)(m->ebp + 0x11cu));	/* 4584fa: mov eax, dword ptr [ebp + 0x11c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 458500: test eax, eax */
	if (m->zf) goto L_45859c;	/* 458502: je 0x45859c */
	FPUSH((long double)(int)M32((DWORD)(m->ebp + 0x1cu)));	/* 458508: fild dword ptr [ebp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94fcu));	/* 45850b: fmul dword ptr [0x4a94fc] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 458511: call 0x49ec14 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x128u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 458516: cmp dword ptr [ebp + 0x128], eax */
	if (m->sf == m->of) goto L_458524;	/* 45851c: jge 0x458524 */
	M32((DWORD)(m->ebp + 0x87f4u)) = m->edi;	/* 45851e: mov dword ptr [ebp + 0x87f4], edi */
L_458524:
	m->ecx = M32((DWORD)(m->esi + 0x320u));	/* 458524: mov ecx, dword ptr [esi + 0x320] */
	m->eax = m->ecx;	/* 45852a: mov eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45852c: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45852f: sub eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 458531: shl eax, 2 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 458534: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 458536: lea eax, [eax + eax*4] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 458539: lea edx, [eax + eax*4] */
	m->ecx = M32((DWORD)(m->ebx + m->edx*8 + 0x14d4874u));	/* 45853c: mov ecx, dword ptr [ebx + edx*8 + 0x14d4874] */
	m->eax = (DWORD)(m->ebx + m->edx*8 + 0x0u);	/* 458543: lea eax, [ebx + edx*8] */
	m->edx = M32((DWORD)(m->ebp + m->ecx*4 + 0x130u));	/* 458546: mov edx, dword ptr [ebp + ecx*4 + 0x130] */
	m->ecx = M32((DWORD)(m->eax + 0x14d4878u));	/* 45854d: mov ecx, dword ptr [eax + 0x14d4878] */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 458553: cmp edx, ecx */
	if (m->sf == m->of) goto L_45859c;	/* 458555: jge 0x45859c */
	m->esi = M32((DWORD)(m->esi + 0x330u));	/* 458557: mov esi, dword ptr [esi + 0x330] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45855d: test esi, esi */
	if (m->sf != m->of) goto L_45859c;	/* 45855f: jl 0x45859c */
	m->eax = m->esi;	/* 458561: mov eax, esi */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 458563: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 458566: sub eax, esi */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 458568: shl eax, 2 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45856b: sub eax, esi */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45856d: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 458570: lea eax, [eax + eax*4] */
	m->ecx = M32((DWORD)(m->ebx + m->eax*8 + 0x14d4874u));	/* 458573: mov ecx, dword ptr [ebx + eax*8 + 0x14d4874] */
	m->eax = (DWORD)(m->ebx + m->eax*8 + 0x0u);	/* 45857a: lea eax, [ebx + eax*8] */
	m->edx = M32((DWORD)(m->ebp + m->ecx*4 + 0x130u));	/* 45857d: mov edx, dword ptr [ebp + ecx*4 + 0x130] */
	m->ecx = M32((DWORD)(m->eax + 0x14d4878u));	/* 458584: mov ecx, dword ptr [eax + 0x14d4878] */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45858a: cmp edx, ecx */
	if (m->sf == m->of) goto L_45859c;	/* 45858c: jge 0x45859c */
	m->eax = M32((DWORD)(m->ebp + 0x87f4u));	/* 45858e: mov eax, dword ptr [ebp + 0x87f4] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x2u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 458594: or al, 2 */
	M32((DWORD)(m->ebp + 0x87f4u)) = m->eax;	/* 458596: mov dword ptr [ebp + 0x87f4], eax */
L_45859c:
	m->esi = M32((DWORD)(m->ebx + 0x20a99b4u));	/* 45859c: mov esi, dword ptr [ebx + 0x20a99b4] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 4585a2: xor edi, edi */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4585a4: xor ecx, ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->edi;	/* 4585a6: mov dword ptr [esp + 0x14], edi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4585aa: test esi, esi */
	if (m->zf || m->sf != m->of) goto L_458697;	/* 4585ac: jle 0x458697 */
	m->edx = (DWORD)(m->ebx + 0x202ef40u);	/* 4585b2: lea edx, [ebx + 0x202ef40] */
L_4585b8:
	m->eax = M32((DWORD)(m->esp + 0x2b4u));	/* 4585b8: mov eax, dword ptr [esp + 0x2b4] */
	{ DWORD a_ = M32((DWORD)(m->edx + 0xb0u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4585bf: cmp dword ptr [edx + 0xb0], eax */
	if (!m->zf) goto L_4585ef;	/* 4585c5: jne 0x4585ef */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 4585c7: mov eax, dword ptr [edx] */
	m->edi = m->eax;	/* 4585c9: mov edi, eax */
	{ DWORD a_ = m->edi, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 4585cb: shl edi, 4 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4585ce: add edi, eax */
	{ DWORD a_ = m->edi, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 4585d0: shl edi, 4 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4585d3: add edi, eax */
	{ DWORD a_ = m->edi, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 4585d5: shl edi, 4 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4585d8: add edi, eax */
	m->eax = M32((DWORD)(m->ebx + m->edi*8 + 0x1cd94b8u));	/* 4585da: mov eax, dword ptr [ebx + edi*8 + 0x1cd94b8] */
	m->edi = M32((DWORD)(m->ebx + 0x202e8d4u));	/* 4585e1: mov edi, dword ptr [ebx + 0x202e8d4] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4585e7: cmp eax, edi */
	if (!m->zf) goto L_4585ff;	/* 4585e9: jne 0x4585ff */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 4585eb: mov edi, dword ptr [esp + 0x14] */
L_4585ef:
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4585ef: inc ecx */
	{ DWORD a_ = m->edx, b_ = 0x4e8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4585f0: add edx, 0x4e8 */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4585f6: cmp ecx, esi */
	if (m->sf != m->of) goto L_4585b8;	/* 4585f8: jl 0x4585b8 */
	goto L_458697;	/* 4585fa: jmp 0x458697 */
L_4585ff:
	m->eax = M32((DWORD)(m->ebp + 0x8880u));	/* 4585ff: mov eax, dword ptr [ebp + 0x8880] */
	m->edi = 0x1u;	/* 458605: mov edi, 1 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45860a: test eax, eax */
	if (!m->zf) goto L_458697;	/* 45860c: jne 0x458697 */
	m->eax = M32((DWORD)(m->ebp + 0x11cu));	/* 458612: mov eax, dword ptr [ebp + 0x11c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 458618: test eax, eax */
	if (m->zf) goto L_458697;	/* 45861a: je 0x458697 */
	m->eax = M32((DWORD)(m->ebp + 0x8820u));	/* 45861c: mov eax, dword ptr [ebp + 0x8820] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 458622: test eax, eax */
	if (m->sf == m->of) goto L_458697;	/* 458624: jge 0x458697 */
	{ long long p_ = (long long)(int)m->ecx * (int)0x4e8u; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ecx = r_; }	/* 458626: imul ecx, ecx, 0x4e8 */
	m->esi = M32((DWORD)(m->ebp + 0x118u));	/* 45862c: mov esi, dword ptr [ebp + 0x118] */
	m->eax = M32((DWORD)(m->ecx + m->ebx*1 + 0x202ef40u));	/* 458632: mov eax, dword ptr [ecx + ebx + 0x202ef40] */
	m->ecx = m->eax;	/* 458639: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45863b: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45863e: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 458640: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 458643: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 458645: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 458648: add ecx, eax */
	m->edx = M32((DWORD)(m->ebx + m->ecx*8 + 0x1cd94c0u));	/* 45864a: mov edx, dword ptr [ebx + ecx*8 + 0x1cd94c0] */
	m->ecx = (DWORD)(m->ebx + m->ecx*8 + 0x0u);	/* 458651: lea ecx, [ebx + ecx*8] */
	{ DWORD a_ = m->edx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 458654: cmp edx, esi */
	if (m->zf) goto L_458697;	/* 458656: je 0x458697 */
	{ DWORD a_ = M32((DWORD)(m->ecx + 0x1cd94f4u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 458658: cmp dword ptr [ecx + 0x1cd94f4], edi */
	if (!m->zf) goto L_458697;	/* 45865e: jne 0x458697 */
	m->edx = M32((DWORD)(m->ecx + 0x1cd9798u));	/* 458660: mov edx, dword ptr [ecx + 0x1cd9798] */
	{ DWORD a_ = ((m->edx >> 8) & 0xff), b_ = 0x2u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 458666: test dh, 2 */
	if (m->zf) goto L_458678;	/* 458669: je 0x458678 */
	m->ecx = M32((DWORD)(m->ecx + 0x1cd93b0u));	/* 45866b: mov ecx, dword ptr [ecx + 0x1cd93b0] */
	m->edx = M32((DWORD)(m->ebp + 0x8u));	/* 458671: mov edx, dword ptr [ebp + 8] */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 458674: cmp ecx, edx */
	if (m->sf == m->of) goto L_458697;	/* 458676: jge 0x458697 */
L_458678:
	m->edx = M32((DWORD)(m->esp + 0x2b4u));	/* 458678: mov edx, dword ptr [esp + 0x2b4] */
	M32((DWORD)(m->ebp + 0x8820u)) = m->eax;	/* 45867f: mov dword ptr [ebp + 0x8820], eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 458685: push edx */
	m->ecx = m->ebx;	/* 458686: mov ecx, ebx */
	M32((DWORD)(m->ebp + 0x8858u)) = 0x41280000u;	/* 458688: mov dword ptr [ebp + 0x8858], 0x41280000 */
	m->esp -= 4; M32(m->esp) = 0x458697u; native_call(m, 0x45edb0u);	/* 458692: call 0x45edb0 */
L_458697:
	m->esi = M32((DWORD)(m->esp + 0x2b4u));	/* 458697: mov esi, dword ptr [esp + 0x2b4] */
	M32((DWORD)(m->ebp + 0x8880u)) = m->edi;	/* 45869e: mov dword ptr [ebp + 0x8880], edi */
	{ DWORD a_ = m->esi, b_ = M32((DWORD)(m->ebx + 0x202e8d4u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4586a4: cmp esi, dword ptr [ebx + 0x202e8d4] */
	if (!m->zf) goto L_4586f3;	/* 4586aa: jne 0x4586f3 */
	{ DWORD a_ = m->edi, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4586ac: cmp edi, 1 */
	if (!m->zf) goto L_4586e9;	/* 4586af: jne 0x4586e9 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x8884u)));	/* 4586b1: fld dword ptr [ebp + 0x8884] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x2b8u));	/* 4586b7: fsub dword ptr [esp + 0x2b8] */
	MF((DWORD)(m->ebp + 0x8884u)) = (float)ST(0);	/* 4586be: fst dword ptr [ebp + 0x8884] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 4586c4: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4586ca: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4586cc: test ah, 1 */
	if (m->zf) goto L_4586f3;	/* 4586cf: je 0x4586f3 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 4586d1: push 0x64 */
	{ DWORD v_ = 0x11u; m->esp -= 4; M32(m->esp) = v_; }	/* 4586d3: push 0x11 */
	m->esp -= 4; M32(m->esp) = 0x4586dau; native_call(m, 0x456e50u);	/* 4586d5: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4586da: add esp, 8 */
	M32((DWORD)(m->ebp + 0x8884u)) = 0x3f000000u;	/* 4586dd: mov dword ptr [ebp + 0x8884], 0x3f000000 */
	goto L_4586f3;	/* 4586e7: jmp 0x4586f3 */
L_4586e9:
	M32((DWORD)(m->ebp + 0x8884u)) = 0x0u;	/* 4586e9: mov dword ptr [ebp + 0x8884], 0 */
L_4586f3:
	m->eax = M32((DWORD)(m->ebp + 0x8820u));	/* 4586f3: mov eax, dword ptr [ebp + 0x8820] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4586f9: test eax, eax */
	if (m->sf != m->of) goto L_458732;	/* 4586fb: jl 0x458732 */
	m->ecx = m->eax;	/* 4586fd: mov ecx, eax */
	m->edi = 0x1u;	/* 4586ff: mov edi, 1 */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 458704: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 458707: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 458709: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45870c: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45870e: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 458711: add ecx, eax */
	{ DWORD a_ = M32((DWORD)(m->ebx + m->ecx*8 + 0x1cd94f4u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 458713: cmp dword ptr [ebx + ecx*8 + 0x1cd94f4], edi */
	if (m->zf) goto L_458737;	/* 45871a: je 0x458737 */
	M32((DWORD)(m->ebp + 0x8820u)) = 0xffffffffu;	/* 45871c: mov dword ptr [ebp + 0x8820], 0xffffffff */
	M32((DWORD)(m->ebp + 0x8858u)) = 0x0u;	/* 458726: mov dword ptr [ebp + 0x8858], 0 */
	goto L_458737;	/* 458730: jmp 0x458737 */
L_458732:
	m->edi = 0x1u;	/* 458732: mov edi, 1 */
L_458737:
	m->eax = M32((DWORD)(m->ebp + 0x11cu));	/* 458737: mov eax, dword ptr [ebp + 0x11c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45873d: test eax, eax */
	if (m->zf) goto L_458ac3;	/* 45873f: je 0x458ac3 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x8824u)));	/* 458745: fld dword ptr [ebp + 0x8824] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x2b8u));	/* 45874b: fsub dword ptr [esp + 0x2b8] */
	MF((DWORD)(m->ebp + 0x8824u)) = (float)ST(0);	/* 458752: fst dword ptr [ebp + 0x8824] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x8854u)));	/* 458758: fld dword ptr [ebp + 0x8854] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45875e: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 458764: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 458766: test ah, 0x41 */
	if (!m->zf) goto L_4587df;	/* 458769: jne 0x4587df */
	m->eax = M32((DWORD)(m->ebp + 0x4c0u));	/* 45876b: mov eax, dword ptr [ebp + 0x4c0] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 458771: cmp eax, esi */
	if (m->zf) goto L_4587df;	/* 458773: je 0x4587df */
	m->edx = m->eax;	/* 458775: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 458777: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45877a: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45877c: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45877f: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 458781: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 458784: add edx, eax */
	m->ecx = (DWORD)(m->ebx + m->edx*8 + 0x0u);	/* 458786: lea ecx, [ebx + edx*8] */
	m->edx = M32((DWORD)(m->ebx + m->edx*8 + 0x1cd94c0u));	/* 458789: mov edx, dword ptr [ebx + edx*8 + 0x1cd94c0] */
	{ DWORD a_ = m->edx, b_ = M32((DWORD)(m->ebp + 0x118u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 458790: cmp edx, dword ptr [ebp + 0x118] */
	if (m->zf) goto L_4587df;	/* 458796: je 0x4587df */
	{ DWORD a_ = M32((DWORD)(m->ecx + 0x1cd94f4u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 458798: cmp dword ptr [ecx + 0x1cd94f4], edi */
	if (!m->zf) goto L_4587df;	/* 45879e: jne 0x4587df */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x8820u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4587a0: cmp dword ptr [ebp + 0x8820], eax */
	if (m->zf) goto L_4587df;	/* 4587a6: je 0x4587df */
	m->edx = M32((DWORD)(m->ecx + 0x1cd9798u));	/* 4587a8: mov edx, dword ptr [ecx + 0x1cd9798] */
	{ DWORD a_ = ((m->edx >> 8) & 0xff), b_ = 0x2u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4587ae: test dh, 2 */
	if (m->zf) goto L_4587c0;	/* 4587b1: je 0x4587c0 */
	m->ecx = M32((DWORD)(m->ecx + 0x1cd93b0u));	/* 4587b3: mov ecx, dword ptr [ecx + 0x1cd93b0] */
	m->edx = M32((DWORD)(m->ebp + 0x8u));	/* 4587b9: mov edx, dword ptr [ebp + 8] */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4587bc: cmp ecx, edx */
	if (m->sf == m->of) goto L_4587df;	/* 4587be: jge 0x4587df */
L_4587c0:
	M32((DWORD)(m->ebp + 0x8820u)) = m->eax;	/* 4587c0: mov dword ptr [ebp + 0x8820], eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4587c6: push esi */
	m->ecx = m->ebx;	/* 4587c7: mov ecx, ebx */
	M32((DWORD)(m->ebp + 0x8858u)) = 0x41280000u;	/* 4587c9: mov dword ptr [ebp + 0x8858], 0x41280000 */
	ST(0) = ST(0); FPOP();	/* 4587d3: fstp st(0) */
	m->esp -= 4; M32(m->esp) = 0x4587dau; native_call(m, 0x45edb0u);	/* 4587d5: call 0x45edb0 */
	goto L_458a49;	/* 4587da: jmp 0x458a49 */
L_4587df:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 4587df: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4587e5: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4587e7: test ah, 0x41 */
	if (m->zf) goto L_458a49;	/* 4587ea: je 0x458a49 */
	{ DWORD a_ = M8((DWORD)(m->ebp + 0x87f4u)), b_ = 0x2u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4587f0: test byte ptr [ebp + 0x87f4], 2 */
	if (!m->zf) goto L_458a49;	/* 4587f7: jne 0x458a49 */
	m->eax = M32((DWORD)(m->ebp + 0x8820u));	/* 4587fd: mov eax, dword ptr [ebp + 0x8820] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 458803: test eax, eax */
	if (m->sf == m->of) goto L_458919;	/* 458805: jge 0x458919 */
	m->eax = M32((DWORD)(m->ebx + 0x202e8c8u));	/* 45880b: mov eax, dword ptr [ebx + 0x202e8c8] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 458811: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 458813: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_4588f7;	/* 458815: jle 0x4588f7 */
	m->esi = (DWORD)(m->ebx + 0x1cd9504u);	/* 45881b: lea esi, [ebx + 0x1cd9504] */
L_458821:
	{ DWORD a_ = m->edi, b_ = M32((DWORD)(m->esp + 0x2b4u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 458821: cmp edi, dword ptr [esp + 0x2b4] */
	if (m->zf) goto L_4588da;	/* 458828: je 0x4588da */
	{ DWORD a_ = M32((DWORD)(m->esi + 0xfffffff0u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45882e: cmp dword ptr [esi - 0x10], 1 */
	if (!m->zf) goto L_4588da;	/* 458832: jne 0x4588da */
	m->edx = M32((DWORD)(m->esi + 0xffffffbcu));	/* 458838: mov edx, dword ptr [esi - 0x44] */
	m->eax = M32((DWORD)(m->ebp + 0x118u));	/* 45883b: mov eax, dword ptr [ebp + 0x118] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 458841: cmp edx, eax */
	if (m->zf) goto L_4588da;	/* 458843: je 0x4588da */
	m->eax = M32((DWORD)(m->esi + 0x294u));	/* 458849: mov eax, dword ptr [esi + 0x294] */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x2u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45884f: test ah, 2 */
	if (m->zf) goto L_458861;	/* 458852: je 0x458861 */
	m->eax = M32((DWORD)(m->esi + 0xfffffeacu));	/* 458854: mov eax, dword ptr [esi - 0x154] */
	m->ecx = M32((DWORD)(m->ebp + 0x8u));	/* 45885a: mov ecx, dword ptr [ebp + 8] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45885d: cmp eax, ecx */
	if (m->sf == m->of) goto L_4588da;	/* 45885f: jge 0x4588da */
L_458861:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0xfffffff8u)));	/* 458861: fld dword ptr [esi - 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x154u));	/* 458864: fsub dword ptr [ebp + 0x154] */
	m->edx = (DWORD)(m->esi + 0xfffffff8u);	/* 45886a: lea edx, [esi - 8] */
	m->ecx = (DWORD)(m->ebp + 0x154u);	/* 45886d: lea ecx, [ebp + 0x154] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 458873: fstp dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0xfffffffcu)));	/* 458877: fld dword ptr [esi - 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ecx + 0x4u));	/* 45887a: fsub dword ptr [ecx + 4] */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 45887d: mov eax, dword ptr [esp + 0x38] */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 458881: mov dword ptr [esp + 0x28], eax */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 458885: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 458889: fld dword ptr [esi] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ecx + 0x8u));	/* 45888b: fsub dword ptr [ecx + 8] */
	m->eax = M32((DWORD)(m->esp + 0x3cu));	/* 45888e: mov eax, dword ptr [esp + 0x3c] */
	M32((DWORD)(m->esp + 0x2cu)) = m->eax;	/* 458892: mov dword ptr [esp + 0x2c], eax */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 458896: fstp dword ptr [esp + 0x40] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 45889a: fld dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x38u));	/* 45889e: fmul dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 4588a2: fld dword ptr [esp + 0x40] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 4588a6: fmul dword ptr [esp + 0x40] */
	m->eax = M32((DWORD)(m->esp + 0x40u));	/* 4588aa: mov eax, dword ptr [esp + 0x40] */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 4588ae: mov dword ptr [esp + 0x30], eax */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4588b2: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 4588b4: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 4588b8: fmul dword ptr [esp + 0x3c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4588bc: faddp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x0u)); FPOP();	/* 4588be: fcomp dword ptr [ebp] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4588c1: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4588c3: test ah, 0x41 */
	if (m->zf) goto L_4588da;	/* 4588c6: je 0x4588da */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 4588c8: lea eax, [esp + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4588cc: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4588cd: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4588ce: push ecx */
	m->ecx = m->ebx;	/* 4588cf: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x4588d6u; native_call(m, 0x471740u);	/* 4588d1: call 0x471740 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4588d6: test eax, eax */
	if (m->zf) goto L_4588f1;	/* 4588d8: je 0x4588f1 */
L_4588da:
	m->eax = M32((DWORD)(m->ebx + 0x202e8c8u));	/* 4588da: mov eax, dword ptr [ebx + 0x202e8c8] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 4588e0: inc edi */
	{ DWORD a_ = m->esi, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4588e1: add esi, 0x8888 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4588e7: cmp edi, eax */
	if (m->sf != m->of) goto L_458821;	/* 4588e9: jl 0x458821 */
	goto L_4588f7;	/* 4588ef: jmp 0x4588f7 */
L_4588f1:
	M32((DWORD)(m->ebp + 0x8820u)) = m->edi;	/* 4588f1: mov dword ptr [ebp + 0x8820], edi */
L_4588f7:
	m->eax = M32((DWORD)(m->ebp + 0x8820u));	/* 4588f7: mov eax, dword ptr [ebp + 0x8820] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4588fd: test eax, eax */
	if (m->sf != m->of) goto L_458a33;	/* 4588ff: jl 0x458a33 */
	m->ecx = M32((DWORD)(m->esp + 0x2b4u));	/* 458905: mov ecx, dword ptr [esp + 0x2b4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45890c: push ecx */
	m->ecx = m->ebx;	/* 45890d: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x458914u; native_call(m, 0x45edb0u);	/* 45890f: call 0x45edb0 */
	goto L_458a33;	/* 458914: jmp 0x458a33 */
L_458919:
	m->ecx = m->eax;	/* 458919: mov ecx, eax */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 45891b: lea edx, [esp + 0x28] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45891f: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 458922: add ecx, eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 458924: push edx */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 458925: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 458928: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45892a: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45892d: add ecx, eax */
	m->eax = (DWORD)(m->ebp + 0x154u);	/* 45892f: lea eax, [ebp + 0x154] */
	m->edx = (DWORD)(m->ebx + m->ecx*8 + 0x1cd94fcu);	/* 458935: lea edx, [ebx + ecx*8 + 0x1cd94fc] */
	m->ecx = m->ebx;	/* 45893c: mov ecx, ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45893e: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45893f: push eax */
	m->esp -= 4; M32(m->esp) = 0x458945u; native_call(m, 0x471740u);	/* 458940: call 0x471740 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 458945: test eax, eax */
	if (!m->zf) goto L_458984;	/* 458947: jne 0x458984 */
	m->eax = M32((DWORD)(m->ebp + 0x8820u));	/* 458949: mov eax, dword ptr [ebp + 0x8820] */
	m->ecx = m->eax;	/* 45894f: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 458951: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 458954: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 458956: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 458959: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45895b: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45895e: add ecx, eax */
	m->eax = (DWORD)(m->ebx + m->ecx*8 + 0x0u);	/* 458960: lea eax, [ebx + ecx*8] */
	m->ecx = M32((DWORD)(m->ebx + m->ecx*8 + 0x1cd9798u));	/* 458963: mov ecx, dword ptr [ebx + ecx*8 + 0x1cd9798] */
	{ DWORD a_ = ((m->ecx >> 8) & 0xff), b_ = 0x2u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45896a: test ch, 2 */
	if (m->zf) goto L_458a33;	/* 45896d: je 0x458a33 */
	m->edx = M32((DWORD)(m->eax + 0x1cd93b0u));	/* 458973: mov edx, dword ptr [eax + 0x1cd93b0] */
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 458979: mov eax, dword ptr [ebp + 8] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45897c: cmp edx, eax */
	if (m->sf != m->of) goto L_458a33;	/* 45897e: jl 0x458a33 */
L_458984:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x8858u)));	/* 458984: fld dword ptr [ebp + 0x8858] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45898a: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 458990: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 458992: test ah, 0x41 */
	if (!m->zf) goto L_458a29;	/* 458995: jne 0x458a29 */
	m->eax = M32((DWORD)(m->ebx + 0x202e8c8u));	/* 45899b: mov eax, dword ptr [ebx + 0x202e8c8] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 4589a1: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4589a3: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_458a33;	/* 4589a5: jle 0x458a33 */
	m->esi = (DWORD)(m->ebx + 0x1cd94c0u);	/* 4589ab: lea esi, [ebx + 0x1cd94c0] */
L_4589b1:
	{ DWORD a_ = m->edi, b_ = M32((DWORD)(m->esp + 0x2b4u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4589b1: cmp edi, dword ptr [esp + 0x2b4] */
	if (m->zf) goto L_4589ff;	/* 4589b8: je 0x4589ff */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x34u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4589ba: cmp dword ptr [esi + 0x34], 1 */
	if (!m->zf) goto L_4589ff;	/* 4589be: jne 0x4589ff */
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 4589c0: mov eax, dword ptr [esi] */
	m->ecx = M32((DWORD)(m->ebp + 0x118u));	/* 4589c2: mov ecx, dword ptr [ebp + 0x118] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4589c8: cmp eax, ecx */
	if (m->zf) goto L_4589ff;	/* 4589ca: je 0x4589ff */
	m->eax = M32((DWORD)(m->esi + 0x2d8u));	/* 4589cc: mov eax, dword ptr [esi + 0x2d8] */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x2u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4589d2: test ah, 2 */
	if (m->zf) goto L_4589e4;	/* 4589d5: je 0x4589e4 */
	m->ecx = M32((DWORD)(m->esi + 0xfffffef0u));	/* 4589d7: mov ecx, dword ptr [esi - 0x110] */
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 4589dd: mov eax, dword ptr [ebp + 8] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4589e0: cmp ecx, eax */
	if (m->sf == m->of) goto L_4589ff;	/* 4589e2: jge 0x4589ff */
L_4589e4:
	m->edx = (DWORD)(m->esp + 0x28u);	/* 4589e4: lea edx, [esp + 0x28] */
	m->eax = (DWORD)(m->esi + 0x3cu);	/* 4589e8: lea eax, [esi + 0x3c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4589eb: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4589ec: push eax */
	m->eax = (DWORD)(m->ebp + 0x154u);	/* 4589ed: lea eax, [ebp + 0x154] */
	m->ecx = m->ebx;	/* 4589f3: mov ecx, ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4589f5: push eax */
	m->esp -= 4; M32(m->esp) = 0x4589fbu; native_call(m, 0x471740u);	/* 4589f6: call 0x471740 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4589fb: test eax, eax */
	if (m->zf) goto L_458a12;	/* 4589fd: je 0x458a12 */
L_4589ff:
	m->eax = M32((DWORD)(m->ebx + 0x202e8c8u));	/* 4589ff: mov eax, dword ptr [ebx + 0x202e8c8] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 458a05: inc edi */
	{ DWORD a_ = m->esi, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 458a06: add esi, 0x8888 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 458a0c: cmp edi, eax */
	if (m->sf != m->of) goto L_4589b1;	/* 458a0e: jl 0x4589b1 */
	goto L_458a33;	/* 458a10: jmp 0x458a33 */
L_458a12:
	m->ecx = M32((DWORD)(m->esp + 0x2b4u));	/* 458a12: mov ecx, dword ptr [esp + 0x2b4] */
	M32((DWORD)(m->ebp + 0x8820u)) = m->edi;	/* 458a19: mov dword ptr [ebp + 0x8820], edi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 458a1f: push ecx */
	m->ecx = m->ebx;	/* 458a20: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x458a27u; native_call(m, 0x45edb0u);	/* 458a22: call 0x45edb0 */
	goto L_458a33;	/* 458a27: jmp 0x458a33 */
L_458a29:
	M32((DWORD)(m->ebp + 0x8820u)) = 0xffffffffu;	/* 458a29: mov dword ptr [ebp + 0x8820], 0xffffffff */
L_458a33:
	m->esi = M32((DWORD)(m->esp + 0x2b4u));	/* 458a33: mov esi, dword ptr [esp + 0x2b4] */
	M32((DWORD)(m->ebp + 0x8824u)) = 0x3f000000u;	/* 458a3a: mov dword ptr [ebp + 0x8824], 0x3f000000 */
	m->edi = 0x1u;	/* 458a44: mov edi, 1 */
L_458a49:
	m->eax = M32((DWORD)(m->ebp + 0x8820u));	/* 458a49: mov eax, dword ptr [ebp + 0x8820] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 458a4f: test eax, eax */
	if (m->sf != m->of) goto L_458ac3;	/* 458a51: jl 0x458ac3 */
	m->eax = M32((DWORD)(m->ebx + 0x20fcd48u));	/* 458a53: mov eax, dword ptr [ebx + 0x20fcd48] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 458a59: test eax, eax */
	if (!m->zf) goto L_458ac3;	/* 458a5b: jne 0x458ac3 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x8828u)));	/* 458a5d: fld dword ptr [ebp + 0x8828] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x2b8u));	/* 458a63: fsub dword ptr [esp + 0x2b8] */
	MF((DWORD)(m->ebp + 0x8828u)) = (float)ST(0);	/* 458a6a: fst dword ptr [ebp + 0x8828] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 458a70: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 458a76: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 458a78: test ah, 0x41 */
	if (m->zf) goto L_458ac3;	/* 458a7b: je 0x458ac3 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x882cu)));	/* 458a7d: fld dword ptr [ebp + 0x882c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 458a83: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 458a89: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 458a8b: test ah, 0x41 */
	if (m->zf) goto L_458aaa;	/* 458a8e: je 0x458aaa */
	m->edx = M32((DWORD)(m->ebp + 0x90u));	/* 458a90: mov edx, dword ptr [ebp + 0x90] */
	M32((DWORD)(m->ebp + 0x8828u)) = m->edx;	/* 458a96: mov dword ptr [ebp + 0x8828], edx */
	m->eax = M32((DWORD)(m->ebp + 0x94u));	/* 458a9c: mov eax, dword ptr [ebp + 0x94] */
	M32((DWORD)(m->ebp + 0x882cu)) = m->eax;	/* 458aa2: mov dword ptr [ebp + 0x882c], eax */
	goto L_458ac3;	/* 458aa8: jmp 0x458ac3 */
L_458aaa:
	M32((DWORD)(m->ebp + 0x46cu)) = m->edi;	/* 458aaa: mov dword ptr [ebp + 0x46c], edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x882cu)));	/* 458ab0: fld dword ptr [ebp + 0x882c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x2b8u));	/* 458ab6: fsub dword ptr [esp + 0x2b8] */
	MF((DWORD)(m->ebp + 0x882cu)) = (float)ST(0); FPOP();	/* 458abd: fstp dword ptr [ebp + 0x882c] */
L_458ac3:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x886cu)));	/* 458ac3: fld dword ptr [ebp + 0x886c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x2b8u));	/* 458ac9: fsub dword ptr [esp + 0x2b8] */
	MF((DWORD)(m->ebp + 0x886cu)) = (float)ST(0); FPOP();	/* 458ad0: fstp dword ptr [ebp + 0x886c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x384u)));	/* 458ad6: fld dword ptr [ebp + 0x384] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x8874u));	/* 458adc: fadd dword ptr [ebp + 0x8874] */
	MF((DWORD)(m->ebp + 0x8874u)) = (float)ST(0); FPOP();	/* 458ae2: fstp dword ptr [ebp + 0x8874] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x388u)));	/* 458ae8: fld dword ptr [ebp + 0x388] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x8878u));	/* 458aee: fadd dword ptr [ebp + 0x8878] */
	MF((DWORD)(m->ebp + 0x8878u)) = (float)ST(0); FPOP();	/* 458af4: fstp dword ptr [ebp + 0x8878] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x38cu)));	/* 458afa: fld dword ptr [ebp + 0x38c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x887cu));	/* 458b00: fadd dword ptr [ebp + 0x887c] */
	MF((DWORD)(m->ebp + 0x887cu)) = (float)ST(0); FPOP();	/* 458b06: fstp dword ptr [ebp + 0x887c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x886cu)));	/* 458b0c: fld dword ptr [ebp + 0x886c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 458b12: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 458b18: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 458b1a: test ah, 0x41 */
	if (m->zf) goto L_458b9b;	/* 458b1d: je 0x458b9b */
	m->ecx = M32((DWORD)(m->ebp + 0x87f8u));	/* 458b1f: mov ecx, dword ptr [ebp + 0x87f8] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 458b25: test ecx, ecx */
	if (m->sf != m->of) goto L_458b6e;	/* 458b27: jl 0x458b6e */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x887cu)));	/* 458b29: fld dword ptr [ebp + 0x887c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x8878u)));	/* 458b2f: fld dword ptr [ebp + 0x8878] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x8874u)));	/* 458b35: fld dword ptr [ebp + 0x8874] */
	{ long double t = ST(0); FPUSH(t); }	/* 458b3b: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 458b3d: fmul st(1) */
	{ long double t = ST(2); FPUSH(t); }	/* 458b3f: fld st(2) */
	ST(0) = ST(0) * ST(3);	/* 458b41: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 458b43: faddp st(1) */
	{ long double t = ST(3); FPUSH(t); }	/* 458b45: fld st(3) */
	ST(0) = ST(0) * ST(4);	/* 458b47: fmul st(4) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 458b49: faddp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9740u)); FPOP();	/* 458b4b: fcomp dword ptr [0x4a9740] */
	ST(0) = ST(0); FPOP();	/* 458b51: fstp st(0) */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 458b53: fnstsw ax */
	ST(0) = ST(0); FPOP();	/* 458b55: fstp st(0) */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 458b57: test ah, 1 */
	ST(0) = ST(0); FPOP();	/* 458b5a: fstp st(0) */
	if (m->zf) goto L_458b6e;	/* 458b5c: je 0x458b6e */
	M32((DWORD)(m->ebp + 0x8870u)) = m->ecx;	/* 458b5e: mov dword ptr [ebp + 0x8870], ecx */
	M32((DWORD)(m->ebp + 0x87f8u)) = 0xffffffffu;	/* 458b64: mov dword ptr [ebp + 0x87f8], 0xffffffff */
L_458b6e:
	M32((DWORD)(m->ebp + 0x886cu)) = 0x3f800000u;	/* 458b6e: mov dword ptr [ebp + 0x886c], 0x3f800000 */
	m->ecx = M32((DWORD)(0xa0e7e8u));	/* 458b78: mov ecx, dword ptr [0xa0e7e8] */
	M32((DWORD)(m->ebp + 0x8874u)) = m->ecx;	/* 458b7e: mov dword ptr [ebp + 0x8874], ecx */
	m->edx = M32((DWORD)(0xa0e7ecu));	/* 458b84: mov edx, dword ptr [0xa0e7ec] */
	M32((DWORD)(m->ebp + 0x8878u)) = m->edx;	/* 458b8a: mov dword ptr [ebp + 0x8878], edx */
	m->eax = M32((DWORD)(0xa0e7f0u));	/* 458b90: mov eax, dword ptr [0xa0e7f0] */
	M32((DWORD)(m->ebp + 0x887cu)) = m->eax;	/* 458b95: mov dword ptr [ebp + 0x887c], eax */
L_458b9b:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x11cu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 458b9b: cmp dword ptr [ebp + 0x11c], edi */
	if (!m->zf) goto L_458bdb;	/* 458ba1: jne 0x458bdb */
	m->eax = M32((DWORD)(m->ebp + 0x87f8u));	/* 458ba3: mov eax, dword ptr [ebp + 0x87f8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 458ba9: test eax, eax */
	if (m->sf == m->of) goto L_458bdb;	/* 458bab: jge 0x458bdb */
	m->eax = M32((DWORD)(m->ebp + 0x8820u));	/* 458bad: mov eax, dword ptr [ebp + 0x8820] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 458bb3: test eax, eax */
	if (m->sf != m->of) goto L_458bc0;	/* 458bb5: jl 0x458bc0 */
	{ DWORD a_ = M8((DWORD)(m->ebp + 0x87f4u)), b_ = 0x3u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 458bb7: test byte ptr [ebp + 0x87f4], 3 */
	if (m->zf) goto L_458bdb;	/* 458bbe: je 0x458bdb */
L_458bc0:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 458bc0: push esi */
	m->ecx = m->ebx;	/* 458bc1: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x458bc8u; native_call(m, 0x460270u);	/* 458bc3: call 0x460270 */
	{ DWORD a_ = M8((DWORD)(m->ebp + 0x87f4u)), b_ = 0x2u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 458bc8: test byte ptr [ebp + 0x87f4], 2 */
	if (m->zf) goto L_458bdb;	/* 458bcf: je 0x458bdb */
	M32((DWORD)(m->ebp + 0x8820u)) = 0xffffffffu;	/* 458bd1: mov dword ptr [ebp + 0x8820], 0xffffffff */
L_458bdb:
	m->eax = M32((DWORD)(m->ebp + 0x8810u));	/* 458bdb: mov eax, dword ptr [ebp + 0x8810] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 458be1: test eax, eax */
	if (m->sf != m->of) goto L_458c09;	/* 458be3: jl 0x458c09 */
	m->ecx = m->eax;	/* 458be5: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 458be7: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 458bea: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 458bec: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 458bef: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 458bf1: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 458bf4: add ecx, eax */
	{ DWORD a_ = M32((DWORD)(m->ebx + m->ecx*8 + 0x1cd94f4u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 458bf6: cmp dword ptr [ebx + ecx*8 + 0x1cd94f4], edi */
	if (m->zf) goto L_458c09;	/* 458bfd: je 0x458c09 */
	M32((DWORD)(m->ebp + 0x8810u)) = 0xffffffffu;	/* 458bff: mov dword ptr [ebp + 0x8810], 0xffffffff */
L_458c09:
	m->eax = M32((DWORD)(m->ebp + 0x881cu));	/* 458c09: mov eax, dword ptr [ebp + 0x881c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 458c0f: test eax, eax */
	if (m->sf != m->of) goto L_458c37;	/* 458c11: jl 0x458c37 */
	m->edx = m->eax;	/* 458c13: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 458c15: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 458c18: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 458c1a: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 458c1d: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 458c1f: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 458c22: add edx, eax */
	{ DWORD a_ = M32((DWORD)(m->ebx + m->edx*8 + 0x1cd94f4u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 458c24: cmp dword ptr [ebx + edx*8 + 0x1cd94f4], edi */
	if (m->zf) goto L_458c37;	/* 458c2b: je 0x458c37 */
	M32((DWORD)(m->ebp + 0x881cu)) = 0xffffffffu;	/* 458c2d: mov dword ptr [ebp + 0x881c], 0xffffffff */
L_458c37:
	m->edx = M32((DWORD)(m->ebp + 0x87f8u));	/* 458c37: mov edx, dword ptr [ebp + 0x87f8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 458c3d: test edx, edx */
	if (m->sf != m->of) goto L_458d2a;	/* 458c3f: jl 0x458d2a */
	m->ecx = M32((DWORD)(m->ebp + 0x87fcu));	/* 458c45: mov ecx, dword ptr [ebp + 0x87fc] */
	m->eax = (DWORD)(m->edx + 0x821b9u);	/* 458c4b: lea eax, [edx + 0x821b9] */
	m->edi = (DWORD)(m->eax*8 + 0x0u);	/* 458c51: lea edi, [eax*8] */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 458c58: sub edi, eax */
	m->eax = (DWORD)(m->ecx + m->ecx*4 + 0x0u);	/* 458c5a: lea eax, [ecx + ecx*4] */
	m->edi = M32((DWORD)(m->ebx + m->edi*4 + 0x0u));	/* 458c5d: mov edi, dword ptr [ebx + edi*4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + m->eax*4 + 0x0u)));	/* 458c60: fld dword ptr [edi + eax*4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x154u));	/* 458c63: fsub dword ptr [ebp + 0x154] */
	m->eax = (DWORD)(m->edi + m->eax*4 + 0x0u);	/* 458c69: lea eax, [edi + eax*4] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 458c6c: fstp dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 458c70: fld dword ptr [eax + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x158u));	/* 458c73: fsub dword ptr [ebp + 0x158] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 458c79: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 458c7d: fld dword ptr [eax + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x15cu));	/* 458c80: fsub dword ptr [ebp + 0x15c] */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 458c86: mov eax, dword ptr [esp + 0x38] */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 458c8a: mov dword ptr [esp + 0x28], eax */
	m->eax = M32((DWORD)(m->esp + 0x3cu));	/* 458c8e: mov eax, dword ptr [esp + 0x3c] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 458c92: fstp dword ptr [esp + 0x40] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 458c96: fld dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x38u));	/* 458c9a: fmul dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 458c9e: fld dword ptr [esp + 0x40] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 458ca2: fmul dword ptr [esp + 0x40] */
	M32((DWORD)(m->esp + 0x2cu)) = m->eax;	/* 458ca6: mov dword ptr [esp + 0x2c], eax */
	m->eax = M32((DWORD)(m->esp + 0x40u));	/* 458caa: mov eax, dword ptr [esp + 0x40] */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 458cae: mov dword ptr [esp + 0x30], eax */
	ST(1) = ST(1) + ST(0); FPOP();	/* 458cb2: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 458cb4: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 458cb8: fmul dword ptr [esp + 0x3c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 458cbc: faddp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a94ecu)); FPOP();	/* 458cbe: fcomp dword ptr [0x4a94ec] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 458cc4: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 458cc6: test ah, 1 */
	if (m->zf) goto L_458d25;	/* 458cc9: je 0x458d25 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 458ccb: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 458ccc: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 458ccd: push esi */
	m->ecx = m->ebx;	/* 458cce: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x458cd5u; native_call(m, 0x483770u);	/* 458cd0: call 0x483770 */
	m->eax = M32((DWORD)(m->ebp + 0x8800u));	/* 458cd5: mov eax, dword ptr [ebp + 0x8800] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 458cdb: test eax, eax */
	if (!m->zf) goto L_458d09;	/* 458cdd: jne 0x458d09 */
	m->eax = M32((DWORD)(m->ebp + 0x87f8u));	/* 458cdf: mov eax, dword ptr [ebp + 0x87f8] */
	m->ecx = M32((DWORD)(m->ebp + 0x87fcu));	/* 458ce5: mov ecx, dword ptr [ebp + 0x87fc] */
	m->edx = (DWORD)(m->eax*8 + 0x0u);	/* 458ceb: lea edx, [eax*8] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 458cf2: sub edx, eax */
	m->eax = M32((DWORD)(m->ebx + m->edx*4 + 0xe3b038u));	/* 458cf4: mov eax, dword ptr [ebx + edx*4 + 0xe3b038] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 458cfb: dec eax */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 458cfc: cmp ecx, eax */
	if (m->sf == m->of) goto L_458d16;	/* 458cfe: jge 0x458d16 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 458d00: inc ecx */
	M32((DWORD)(m->ebp + 0x87fcu)) = m->ecx;	/* 458d01: mov dword ptr [ebp + 0x87fc], ecx */
	goto L_458d25;	/* 458d07: jmp 0x458d25 */
L_458d09:
	m->eax = M32((DWORD)(m->ebp + 0x87fcu));	/* 458d09: mov eax, dword ptr [ebp + 0x87fc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 458d0f: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_458d16;	/* 458d11: jle 0x458d16 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 458d13: dec eax */
	goto L_458d1f;	/* 458d14: jmp 0x458d1f */
L_458d16:
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 458d16: or eax, 0xffffffff */
	M32((DWORD)(m->ebp + 0x87f8u)) = m->eax;	/* 458d19: mov dword ptr [ebp + 0x87f8], eax */
L_458d1f:
	M32((DWORD)(m->ebp + 0x87fcu)) = m->eax;	/* 458d1f: mov dword ptr [ebp + 0x87fc], eax */
L_458d25:
	m->edi = 0x1u;	/* 458d25: mov edi, 1 */
L_458d2a:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x11cu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 458d2a: cmp dword ptr [ebp + 0x11c], edi */
	if (!m->zf) goto L_458d59;	/* 458d30: jne 0x458d59 */
	m->eax = M32((DWORD)(m->ebp + 0x87f8u));	/* 458d32: mov eax, dword ptr [ebp + 0x87f8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 458d38: test eax, eax */
	if (m->sf != m->of) goto L_458d59;	/* 458d3a: jl 0x458d59 */
	m->eax = M32((DWORD)(m->ebp + 0x8820u));	/* 458d3c: mov eax, dword ptr [ebp + 0x8820] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 458d42: test eax, eax */
	if (m->sf != m->of) goto L_458d59;	/* 458d44: jl 0x458d59 */
	{ DWORD a_ = M8((DWORD)(m->ebp + 0x87f4u)), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 458d46: test byte ptr [ebp + 0x87f4], 1 */
	if (!m->zf) goto L_458d59;	/* 458d4d: jne 0x458d59 */
	M32((DWORD)(m->ebp + 0x87f8u)) = 0xffffffffu;	/* 458d4f: mov dword ptr [ebp + 0x87f8], 0xffffffff */
L_458d59:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x8804u)));	/* 458d59: fld dword ptr [ebp + 0x8804] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 458d5f: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 458d65: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 458d67: test ah, 0x41 */
	if (!m->zf) goto L_458d7f;	/* 458d6a: jne 0x458d7f */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x8804u)));	/* 458d6c: fld dword ptr [ebp + 0x8804] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x2b8u));	/* 458d72: fsub dword ptr [esp + 0x2b8] */
	MF((DWORD)(m->ebp + 0x8804u)) = (float)ST(0); FPOP();	/* 458d79: fstp dword ptr [ebp + 0x8804] */
L_458d7f:
	m->eax = M32((DWORD)(m->ebp + 0x8808u));	/* 458d7f: mov eax, dword ptr [ebp + 0x8808] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 458d85: test eax, eax */
	if (m->sf != m->of) goto L_458d9c;	/* 458d87: jl 0x458d9c */
	{ DWORD a_ = M32((DWORD)(m->ebx + m->eax*4 + 0xe3c618u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 458d89: cmp dword ptr [ebx + eax*4 + 0xe3c618], edi */
	if (!m->zf) goto L_458d9c;	/* 458d90: jne 0x458d9c */
	M32((DWORD)(m->ebp + 0x8808u)) = 0xffffffffu;	/* 458d92: mov dword ptr [ebp + 0x8808], 0xffffffff */
L_458d9c:
	m->eax = M32((DWORD)(m->ebp + 0x11cu));	/* 458d9c: mov eax, dword ptr [ebp + 0x11c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 458da2: test eax, eax */
	if (m->zf) goto L_45991a;	/* 458da4: je 0x45991a */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x8804u)));	/* 458daa: fld dword ptr [ebp + 0x8804] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 458db0: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 458db6: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 458db8: test ah, 0x41 */
	if (m->zf) goto L_45991a;	/* 458dbb: je 0x45991a */
	m->eax = M32((DWORD)(m->ebp + 0x8808u));	/* 458dc1: mov eax, dword ptr [ebp + 0x8808] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 458dc7: test eax, eax */
	if (m->sf == m->of) goto L_45991a;	/* 458dc9: jge 0x45991a */
	m->eax = M32((DWORD)(m->ebp + 0x881cu));	/* 458dcf: mov eax, dword ptr [ebp + 0x881c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 458dd5: test eax, eax */
	if (m->sf != m->of) goto L_458e9b;	/* 458dd7: jl 0x458e9b */
	m->ecx = m->eax;	/* 458ddd: mov ecx, eax */
	m->edx = (DWORD)(m->ebp + 0x154u);	/* 458ddf: lea edx, [ebp + 0x154] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 458de5: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 458de8: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 458dea: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 458ded: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 458def: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 458df2: add ecx, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + m->ecx*8 + 0x1cd94fcu)));	/* 458df4: fld dword ptr [ebx + ecx*8 + 0x1cd94fc] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edx + 0x0u));	/* 458dfb: fsub dword ptr [edx] */
	m->ecx = (DWORD)(m->ebx + m->ecx*8 + 0x1cd94fcu);	/* 458dfd: lea ecx, [ebx + ecx*8 + 0x1cd94fc] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 458e04: fstp dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x4u)));	/* 458e08: fld dword ptr [ecx + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edx + 0x4u));	/* 458e0b: fsub dword ptr [edx + 4] */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 458e0e: mov eax, dword ptr [esp + 0x38] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 458e12: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x8u)));	/* 458e16: fld dword ptr [ecx + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edx + 0x8u));	/* 458e19: fsub dword ptr [edx + 8] */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 458e1c: mov dword ptr [esp + 0x28], eax */
	m->eax = M32((DWORD)(m->esp + 0x3cu));	/* 458e20: mov eax, dword ptr [esp + 0x3c] */
	M32((DWORD)(m->esp + 0x2cu)) = m->eax;	/* 458e24: mov dword ptr [esp + 0x2c], eax */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 458e28: fstp dword ptr [esp + 0x40] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 458e2c: fld dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x38u));	/* 458e30: fmul dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 458e34: fld dword ptr [esp + 0x40] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 458e38: fmul dword ptr [esp + 0x40] */
	m->eax = M32((DWORD)(m->esp + 0x40u));	/* 458e3c: mov eax, dword ptr [esp + 0x40] */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 458e40: mov dword ptr [esp + 0x30], eax */
	ST(1) = ST(1) + ST(0); FPOP();	/* 458e44: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 458e46: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 458e4a: fmul dword ptr [esp + 0x3c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 458e4e: faddp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a973cu)); FPOP();	/* 458e50: fcomp dword ptr [0x4a973c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 458e56: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 458e58: test ah, 0x41 */
	if (!m->zf) goto L_458e7c;	/* 458e5b: jne 0x458e7c */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 458e5d: mov eax, dword ptr [ecx] */
	m->edx = (DWORD)(m->ebp + 0x1d4u);	/* 458e5f: lea edx, [ebp + 0x1d4] */
	M32((DWORD)(m->ebp + 0x1d4u)) = m->eax;	/* 458e65: mov dword ptr [ebp + 0x1d4], eax */
	m->eax = M32((DWORD)(m->ecx + 0x4u));	/* 458e6b: mov eax, dword ptr [ecx + 4] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 458e6e: mov dword ptr [edx + 4], eax */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 458e71: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 458e74: mov dword ptr [edx + 8], ecx */
	goto L_45918f;	/* 458e77: jmp 0x45918f */
L_458e7c:
	m->ecx = M32((DWORD)(m->edx + 0x0u));	/* 458e7c: mov ecx, dword ptr [edx] */
	m->eax = (DWORD)(m->ebp + 0x1d4u);	/* 458e7e: lea eax, [ebp + 0x1d4] */
	M32((DWORD)(m->ebp + 0x1d4u)) = m->ecx;	/* 458e84: mov dword ptr [ebp + 0x1d4], ecx */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 458e8a: mov ecx, dword ptr [edx + 4] */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 458e8d: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->eax + 0x4u)) = m->ecx;	/* 458e90: mov dword ptr [eax + 4], ecx */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 458e93: mov dword ptr [eax + 8], edx */
	goto L_45918f;	/* 458e96: jmp 0x45918f */
L_458e9b:
	m->eax = M32((DWORD)(m->ebp + 0x87f8u));	/* 458e9b: mov eax, dword ptr [ebp + 0x87f8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 458ea1: test eax, eax */
	if (m->sf != m->of) goto L_458f51;	/* 458ea3: jl 0x458f51 */
	{ DWORD a_ = m->eax, b_ = 0x821b9u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 458ea9: add eax, 0x821b9 */
	m->edx = (DWORD)(m->ebp + 0x154u);	/* 458eae: lea edx, [ebp + 0x154] */
	m->ecx = (DWORD)(m->eax*8 + 0x0u);	/* 458eb4: lea ecx, [eax*8] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 458ebb: sub ecx, eax */
	m->eax = M32((DWORD)(m->ebp + 0x87fcu));	/* 458ebd: mov eax, dword ptr [ebp + 0x87fc] */
	m->esi = (DWORD)(m->ebx + m->ecx*4 + 0x0u);	/* 458ec3: lea esi, [ebx + ecx*4] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 458ec6: lea ecx, [eax + eax*4] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 458ec9: shl ecx, 2 */
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 458ecc: mov eax, dword ptr [esi] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 458ece: add eax, ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 458ed0: fld dword ptr [eax] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edx + 0x0u));	/* 458ed2: fsub dword ptr [edx] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 458ed4: fstp dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 458ed8: fld dword ptr [eax + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edx + 0x4u));	/* 458edb: fsub dword ptr [edx + 4] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 458ede: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 458ee2: fld dword ptr [eax + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edx + 0x8u));	/* 458ee5: fsub dword ptr [edx + 8] */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 458ee8: mov eax, dword ptr [esp + 0x38] */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 458eec: mov dword ptr [esp + 0x28], eax */
	m->eax = M32((DWORD)(m->esp + 0x3cu));	/* 458ef0: mov eax, dword ptr [esp + 0x3c] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 458ef4: fstp dword ptr [esp + 0x40] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 458ef8: fld dword ptr [esp + 0x40] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 458efc: fmul dword ptr [esp + 0x40] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 458f00: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 458f04: fmul dword ptr [esp + 0x3c] */
	M32((DWORD)(m->esp + 0x2cu)) = m->eax;	/* 458f08: mov dword ptr [esp + 0x2c], eax */
	m->eax = M32((DWORD)(m->esp + 0x40u));	/* 458f0c: mov eax, dword ptr [esp + 0x40] */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 458f10: mov dword ptr [esp + 0x30], eax */
	ST(1) = ST(1) + ST(0); FPOP();	/* 458f14: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 458f16: fld dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x38u));	/* 458f1a: fmul dword ptr [esp + 0x38] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 458f1e: faddp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a94ecu)); FPOP();	/* 458f20: fcomp dword ptr [0x4a94ec] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 458f26: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 458f28: test ah, 0x41 */
	if (!m->zf) goto L_458f31;	/* 458f2b: jne 0x458f31 */
	m->edx = M32((DWORD)(m->esi + 0x0u));	/* 458f2d: mov edx, dword ptr [esi] */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 458f2f: add edx, ecx */
L_458f31:
	m->ecx = M32((DWORD)(m->edx + 0x0u));	/* 458f31: mov ecx, dword ptr [edx] */
	m->eax = (DWORD)(m->ebp + 0x1d4u);	/* 458f33: lea eax, [ebp + 0x1d4] */
	m->edi = 0x1u;	/* 458f39: mov edi, 1 */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 458f3e: mov dword ptr [eax], ecx */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 458f40: mov ecx, dword ptr [edx + 4] */
	M32((DWORD)(m->eax + 0x4u)) = m->ecx;	/* 458f43: mov dword ptr [eax + 4], ecx */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 458f46: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 458f49: mov dword ptr [eax + 8], edx */
	goto L_45918f;	/* 458f4c: jmp 0x45918f */
L_458f51:
	m->ecx = M32((DWORD)(m->ebp + 0x8820u));	/* 458f51: mov ecx, dword ptr [ebp + 0x8820] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 458f57: test ecx, ecx */
	if (m->sf != m->of) goto L_45918f;	/* 458f59: jl 0x45918f */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x8830u)));	/* 458f5f: fld dword ptr [ebp + 0x8830] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x2b8u));	/* 458f65: fsub dword ptr [esp + 0x2b8] */
	MF((DWORD)(m->ebp + 0x8830u)) = (float)ST(0);	/* 458f6c: fst dword ptr [ebp + 0x8830] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 458f72: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 458f78: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 458f7a: test ah, 0x41 */
	if (m->zf) goto L_45910d;	/* 458f7d: je 0x45910d */
	m->eax = m->ecx;	/* 458f83: mov eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 458f85: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 458f88: add eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 458f8a: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 458f8d: add eax, ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x154u)));	/* 458f8f: fld dword ptr [ebp + 0x154] */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 458f95: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 458f98: add eax, ecx */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + m->eax*8 + 0x1cd94fcu));	/* 458f9a: fsub dword ptr [ebx + eax*8 + 0x1cd94fc] */
	m->eax = (DWORD)(m->ebx + m->eax*8 + 0x1cd94fcu);	/* 458fa1: lea eax, [ebx + eax*8 + 0x1cd94fc] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 458fa8: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x158u)));	/* 458fac: fld dword ptr [ebp + 0x158] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 458fb2: fsub dword ptr [eax + 4] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 458fb5: mov ecx, dword ptr [esp + 0x18] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 458fb9: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x15cu)));	/* 458fbd: fld dword ptr [ebp + 0x15c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 458fc3: fsub dword ptr [eax + 8] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 458fc6: mov edx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x70u)) = m->ecx;	/* 458fca: mov dword ptr [esp + 0x70], ecx */
	m->ecx = (DWORD)(m->esp + 0x70u);	/* 458fce: lea ecx, [esp + 0x70] */
	M32((DWORD)(m->esp + 0x74u)) = m->edx;	/* 458fd2: mov dword ptr [esp + 0x74], edx */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 458fd6: fstp dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 458fda: mov eax, dword ptr [esp + 0x20] */
	M32((DWORD)(m->esp + 0x78u)) = m->eax;	/* 458fde: mov dword ptr [esp + 0x78], eax */
	m->esp -= 4; M32(m->esp) = 0x458fe7u; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 458fe2: call 0x467760 */
	ST(0) = ST(0); FPOP();	/* 458fe7: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x70u)));	/* 458fe9: fld dword ptr [esp + 0x70] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x8cu));	/* 458fed: fmul dword ptr [ebp + 0x8c] */
	M32((DWORD)(m->esp + 0x74u)) = 0x0u;	/* 458ff3: mov dword ptr [esp + 0x74], 0 */
	MF((DWORD)(m->esp + 0x70u)) = (float)ST(0); FPOP();	/* 458ffb: fstp dword ptr [esp + 0x70] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x78u)));	/* 458fff: fld dword ptr [esp + 0x78] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x8cu));	/* 459003: fmul dword ptr [ebp + 0x8c] */
	MF((DWORD)(m->esp + 0x78u)) = (float)ST(0);	/* 459009: fst dword ptr [esp + 0x78] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0xa0e7dcu));	/* 45900d: fmul dword ptr [0xa0e7dc] */
	ST(0) = -ST(0);	/* 459013: fchs  */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 459015: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x78u)));	/* 459019: fld dword ptr [esp + 0x78] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0xa0e7d8u));	/* 45901d: fmul dword ptr [0xa0e7d8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x70u)));	/* 459023: fld dword ptr [esp + 0x70] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0xa0e7e0u));	/* 459027: fmul dword ptr [0xa0e7e0] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 45902d: mov ecx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 459031: mov dword ptr [esp + 0x28], ecx */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 459035: lea ecx, [esp + 0x28] */
	ST(1) = ST(1) - ST(0); FPOP();	/* 459039: fsubp st(1) */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 45903b: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x70u)));	/* 45903f: fld dword ptr [esp + 0x70] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0xa0e7dcu));	/* 459043: fmul dword ptr [0xa0e7dc] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 459049: mov edx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 45904d: mov dword ptr [esp + 0x2c], edx */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 459051: fstp dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 459055: mov eax, dword ptr [esp + 0x20] */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 459059: mov dword ptr [esp + 0x30], eax */
	m->esp -= 4; M32(m->esp) = 0x459062u; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 45905d: call 0x467760 */
	ST(0) = ST(0); FPOP();	/* 459062: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x7cu)));	/* 459064: fld dword ptr [ebp + 0x7c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 459067: call 0x49ec14 */
	m->ecx = m->eax;	/* 45906c: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45906e: shl ecx, 1 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 459070: test ecx, ecx */
	if (m->zf || m->sf != m->of) goto L_45909a;	/* 459072: jle 0x45909a */
	m->esi = M32((DWORD)(0xa1efb8u));	/* 459074: mov esi, dword ptr [0xa1efb8] */
	m->edx = m->esi;	/* 45907a: mov edx, esi */
	{ DWORD a_ = m->edx, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 45907c: and edx, 0xfff */
	m->eax = M32((DWORD)(m->edx*4 + 0xa106f8u));	/* 459082: mov eax, dword ptr [edx*4 + 0xa106f8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 459089: xor edx, edx */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->ecx; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 45908b: div ecx */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 45908d: inc esi */
	M32((DWORD)(0xa1efb8u)) = m->esi;	/* 45908e: mov dword ptr [0xa1efb8], esi */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 459094: mov dword ptr [esp + 0x14], edx */
	goto L_4590a2;	/* 459098: jmp 0x4590a2 */
L_45909a:
	M32((DWORD)(m->esp + 0x14u)) = 0x0u;	/* 45909a: mov dword ptr [esp + 0x14], 0 */
L_4590a2:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 4590a2: fild dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->ebp + 0x8820u));	/* 4590a6: mov eax, dword ptr [ebp + 0x8820] */
	m->edx = M32((DWORD)(m->ebp + 0x84u));	/* 4590ac: mov edx, dword ptr [ebp + 0x84] */
	m->ecx = m->eax;	/* 4590b2: mov ecx, eax */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x7cu));	/* 4590b4: fsub dword ptr [ebp + 0x7c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 4590b7: fld dword ptr [esp + 0x28] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4590bb: shl ecx, 4 */
	ST(0) = ST(0) * ST(1);	/* 4590be: fmul st(1) */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4590c0: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4590c2: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4590c5: add ecx, eax */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 4590c7: fstp dword ptr [esp + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 4590cb: fld dword ptr [esp + 0x30] */
	ST(0) = ST(0) * ST(1);	/* 4590cf: fmul st(1) */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4590d1: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4590d4: add ecx, eax */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 4590d6: fstp dword ptr [esp + 0x30] */
	m->eax = (DWORD)(m->ebx + m->ecx*8 + 0x0u);	/* 4590da: lea eax, [ebx + ecx*8] */
	ST(0) = ST(0); FPOP();	/* 4590dd: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 4590df: fld dword ptr [esp + 0x28] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x1cd94fcu));	/* 4590e3: fadd dword ptr [eax + 0x1cd94fc] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x70u));	/* 4590e9: fadd dword ptr [esp + 0x70] */
	MF((DWORD)(m->ebp + 0x1d4u)) = (float)ST(0); FPOP();	/* 4590ed: fstp dword ptr [ebp + 0x1d4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 4590f3: fld dword ptr [esp + 0x30] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x1cd9504u));	/* 4590f7: fadd dword ptr [eax + 0x1cd9504] */
	M32((DWORD)(m->ebp + 0x8830u)) = m->edx;	/* 4590fd: mov dword ptr [ebp + 0x8830], edx */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x78u));	/* 459103: fadd dword ptr [esp + 0x78] */
	MF((DWORD)(m->ebp + 0x1dcu)) = (float)ST(0); FPOP();	/* 459107: fstp dword ptr [ebp + 0x1dc] */
L_45910d:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x8834u)));	/* 45910d: fld dword ptr [ebp + 0x8834] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x2b8u));	/* 459113: fsub dword ptr [esp + 0x2b8] */
	MF((DWORD)(m->ebp + 0x8834u)) = (float)ST(0);	/* 45911a: fst dword ptr [ebp + 0x8834] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 459120: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 459126: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 459128: test ah, 0x41 */
	if (m->zf) goto L_45918f;	/* 45912b: je 0x45918f */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x80u)));	/* 45912d: fld dword ptr [ebp + 0x80] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 459133: call 0x49ec14 */
	m->ecx = m->eax;	/* 459138: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45913a: shl ecx, 1 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45913c: test ecx, ecx */
	if (m->zf || m->sf != m->of) goto L_459165;	/* 45913e: jle 0x459165 */
	m->esi = M32((DWORD)(0xa1efb8u));	/* 459140: mov esi, dword ptr [0xa1efb8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 459146: xor edx, edx */
	m->eax = m->esi;	/* 459148: mov eax, esi */
	{ DWORD a_ = m->eax, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45914a: and eax, 0xfff */
	m->eax = M32((DWORD)(m->eax*4 + 0xa106f8u));	/* 45914f: mov eax, dword ptr [eax*4 + 0xa106f8] */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->ecx; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 459156: div ecx */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 459158: inc esi */
	M32((DWORD)(0xa1efb8u)) = m->esi;	/* 459159: mov dword ptr [0xa1efb8], esi */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 45915f: mov dword ptr [esp + 0x14], edx */
	goto L_45916d;	/* 459163: jmp 0x45916d */
L_459165:
	M32((DWORD)(m->esp + 0x14u)) = 0x0u;	/* 459165: mov dword ptr [esp + 0x14], 0 */
L_45916d:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 45916d: fild dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->ebp + 0x88u));	/* 459171: mov ecx, dword ptr [ebp + 0x88] */
	M32((DWORD)(m->ebp + 0x8834u)) = m->ecx;	/* 459177: mov dword ptr [ebp + 0x8834], ecx */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x158u));	/* 45917d: fadd dword ptr [ebp + 0x158] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x80u));	/* 459183: fsub dword ptr [ebp + 0x80] */
	MF((DWORD)(m->ebp + 0x1d8u)) = (float)ST(0); FPOP();	/* 459189: fstp dword ptr [ebp + 0x1d8] */
L_45918f:
	m->eax = M32((DWORD)(m->ebp + 0x8810u));	/* 45918f: mov eax, dword ptr [ebp + 0x8810] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 459195: test eax, eax */
	if (m->sf != m->of) goto L_459247;	/* 459197: jl 0x459247 */
	m->edx = m->eax;	/* 45919d: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45919f: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4591a2: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4591a4: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4591a7: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4591a9: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4591ac: add edx, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + m->edx*8 + 0x1cd94fcu)));	/* 4591ae: fld dword ptr [ebx + edx*8 + 0x1cd94fc] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x154u));	/* 4591b5: fsub dword ptr [ebp + 0x154] */
	m->eax = (DWORD)(m->ebx + m->edx*8 + 0x1cd94fcu);	/* 4591bb: lea eax, [ebx + edx*8 + 0x1cd94fc] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4591c2: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 4591c6: fld dword ptr [eax + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x158u));	/* 4591c9: fsub dword ptr [ebp + 0x158] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 4591cf: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 4591d3: fld dword ptr [eax + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x15cu));	/* 4591d6: fsub dword ptr [ebp + 0x15c] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4591dc: mov eax, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 4591e0: mov ecx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x70u)) = m->eax;	/* 4591e4: mov dword ptr [esp + 0x70], eax */
	M32((DWORD)(m->esp + 0x74u)) = m->ecx;	/* 4591e8: mov dword ptr [esp + 0x74], ecx */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 4591ec: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 4591f0: fld dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 4591f4: fld dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 4591f8: fld dword ptr [esp + 0x1c] */
	ST(0) = -ST(0);	/* 4591fc: fchs  */
	{ long double t = ST(2); FPUSH(t); }	/* 4591fe: fld st(2) */
	ST(3) = ST(3) * ST(0); FPOP();	/* 459200: fmulp st(3) */
	{ long double t = ST(1); FPUSH(t); }	/* 459202: fld st(1) */
	ST(0) = ST(0) * ST(2);	/* 459204: fmul st(2) */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 459206: mov edx, dword ptr [esp + 0x20] */
	M32((DWORD)(m->esp + 0x78u)) = m->edx;	/* 45920a: mov dword ptr [esp + 0x78], edx */
	ST(3) = ST(3) + ST(0); FPOP();	/* 45920e: faddp st(3) */
	{ long double t = ST(0); ST(0) = ST(2); ST(2) = t; }	/* 459210: fxch st(2) */
	{ long double t = ST(0); __asm__("fsqrt" : "+t"(t)); ST(0) = t; }	/* 459212: fsqrt  */
	{ long double t = ST(0); ST(0) = ST(2); ST(2) = t; }	/* 459214: fxch st(2) */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 459216: fxch st(1) */
	{ long double t = ST(0); ST(0) = ST(2); ST(2) = t; }	/* 459218: fxch st(2) */
	{ long double x_ = ST(0), y_ = ST(1), r_; __asm__("fpatan" : "=t"(r_) : "0"(x_), "u"(y_) : "st(1)"); FPOP(); ST(0) = r_; }	/* 45921a: fpatan  */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 45921c: fxch st(1) */
	ST(0) = ST(0); FPOP();	/* 45921e: fstp st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9738u));	/* 459220: fmul dword ptr [0x4a9738] */
	MF((DWORD)(m->ebp + 0x1e0u)) = (float)ST(0); FPOP();	/* 459226: fstp dword ptr [ebp + 0x1e0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 45922c: fld dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 459230: fld dword ptr [esp + 0x20] */
	{ long double x_ = ST(0), y_ = ST(1), r_; __asm__("fpatan" : "=t"(r_) : "0"(x_), "u"(y_) : "st(1)"); FPOP(); ST(0) = r_; }	/* 459234: fpatan  */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9738u));	/* 459236: fmul dword ptr [0x4a9738] */
	MF((DWORD)(m->ebp + 0x1e4u)) = (float)ST(0); FPOP();	/* 45923c: fstp dword ptr [ebp + 0x1e4] */
	goto L_4595be;	/* 459242: jmp 0x4595be */
L_459247:
	m->eax = M32((DWORD)(m->ebp + 0x8814u));	/* 459247: mov eax, dword ptr [ebp + 0x8814] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45924d: test eax, eax */
	if (m->sf != m->of) goto L_459300;	/* 45924f: jl 0x459300 */
	{ DWORD a_ = m->eax, b_ = 0x821b9u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 459255: add eax, 0x821b9 */
	m->ecx = (DWORD)(m->eax*8 + 0x0u);	/* 45925a: lea ecx, [eax*8] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 459261: sub ecx, eax */
	m->eax = M32((DWORD)(m->ebp + 0x8818u));	/* 459263: mov eax, dword ptr [ebp + 0x8818] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 459269: lea edx, [eax + eax*4] */
	m->eax = M32((DWORD)(m->ebx + m->ecx*4 + 0x0u));	/* 45926c: mov eax, dword ptr [ebx + ecx*4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + m->edx*4 + 0x0u)));	/* 45926f: fld dword ptr [eax + edx*4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x154u));	/* 459272: fsub dword ptr [ebp + 0x154] */
	m->eax = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 459278: lea eax, [eax + edx*4] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 45927b: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 45927f: fld dword ptr [eax + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x158u));	/* 459282: fsub dword ptr [ebp + 0x158] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 459288: mov ecx, dword ptr [esp + 0x18] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 45928c: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 459290: fld dword ptr [eax + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x15cu));	/* 459293: fsub dword ptr [ebp + 0x15c] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 459299: mov edx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x70u)) = m->ecx;	/* 45929d: mov dword ptr [esp + 0x70], ecx */
	M32((DWORD)(m->esp + 0x74u)) = m->edx;	/* 4592a1: mov dword ptr [esp + 0x74], edx */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 4592a5: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 4592a9: fld dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 4592ad: fld dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 4592b1: fld dword ptr [esp + 0x1c] */
	ST(0) = -ST(0);	/* 4592b5: fchs  */
	{ long double t = ST(2); FPUSH(t); }	/* 4592b7: fld st(2) */
	ST(3) = ST(3) * ST(0); FPOP();	/* 4592b9: fmulp st(3) */
	{ long double t = ST(1); FPUSH(t); }	/* 4592bb: fld st(1) */
	ST(0) = ST(0) * ST(2);	/* 4592bd: fmul st(2) */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 4592bf: mov eax, dword ptr [esp + 0x20] */
	M32((DWORD)(m->esp + 0x78u)) = m->eax;	/* 4592c3: mov dword ptr [esp + 0x78], eax */
	ST(3) = ST(3) + ST(0); FPOP();	/* 4592c7: faddp st(3) */
	{ long double t = ST(0); ST(0) = ST(2); ST(2) = t; }	/* 4592c9: fxch st(2) */
	{ long double t = ST(0); __asm__("fsqrt" : "+t"(t)); ST(0) = t; }	/* 4592cb: fsqrt  */
	{ long double t = ST(0); ST(0) = ST(2); ST(2) = t; }	/* 4592cd: fxch st(2) */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 4592cf: fxch st(1) */
	{ long double t = ST(0); ST(0) = ST(2); ST(2) = t; }	/* 4592d1: fxch st(2) */
	{ long double x_ = ST(0), y_ = ST(1), r_; __asm__("fpatan" : "=t"(r_) : "0"(x_), "u"(y_) : "st(1)"); FPOP(); ST(0) = r_; }	/* 4592d3: fpatan  */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 4592d5: fxch st(1) */
	ST(0) = ST(0); FPOP();	/* 4592d7: fstp st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9738u));	/* 4592d9: fmul dword ptr [0x4a9738] */
	MF((DWORD)(m->ebp + 0x1e0u)) = (float)ST(0); FPOP();	/* 4592df: fstp dword ptr [ebp + 0x1e0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 4592e5: fld dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 4592e9: fld dword ptr [esp + 0x20] */
	{ long double x_ = ST(0), y_ = ST(1), r_; __asm__("fpatan" : "=t"(r_) : "0"(x_), "u"(y_) : "st(1)"); FPOP(); ST(0) = r_; }	/* 4592ed: fpatan  */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9738u));	/* 4592ef: fmul dword ptr [0x4a9738] */
	MF((DWORD)(m->ebp + 0x1e4u)) = (float)ST(0); FPOP();	/* 4592f5: fstp dword ptr [ebp + 0x1e4] */
	goto L_4595be;	/* 4592fb: jmp 0x4595be */
L_459300:
	m->eax = M32((DWORD)(m->ebp + 0x881cu));	/* 459300: mov eax, dword ptr [ebp + 0x881c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 459306: test eax, eax */
	if (m->sf != m->of) goto L_4593b8;	/* 459308: jl 0x4593b8 */
	m->ecx = m->eax;	/* 45930e: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 459310: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 459313: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 459315: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 459318: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45931a: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45931d: add ecx, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + m->ecx*8 + 0x1cd94fcu)));	/* 45931f: fld dword ptr [ebx + ecx*8 + 0x1cd94fc] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x154u));	/* 459326: fsub dword ptr [ebp + 0x154] */
	m->eax = (DWORD)(m->ebx + m->ecx*8 + 0x1cd94fcu);	/* 45932c: lea eax, [ebx + ecx*8 + 0x1cd94fc] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 459333: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 459337: fld dword ptr [eax + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x158u));	/* 45933a: fsub dword ptr [ebp + 0x158] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 459340: mov edx, dword ptr [esp + 0x18] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 459344: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 459348: fld dword ptr [eax + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x15cu));	/* 45934b: fsub dword ptr [ebp + 0x15c] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 459351: mov eax, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x70u)) = m->edx;	/* 459355: mov dword ptr [esp + 0x70], edx */
	M32((DWORD)(m->esp + 0x74u)) = m->eax;	/* 459359: mov dword ptr [esp + 0x74], eax */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 45935d: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 459361: fld dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 459365: fld dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 459369: fld dword ptr [esp + 0x1c] */
	ST(0) = -ST(0);	/* 45936d: fchs  */
	{ long double t = ST(2); FPUSH(t); }	/* 45936f: fld st(2) */
	ST(3) = ST(3) * ST(0); FPOP();	/* 459371: fmulp st(3) */
	{ long double t = ST(1); FPUSH(t); }	/* 459373: fld st(1) */
	ST(0) = ST(0) * ST(2);	/* 459375: fmul st(2) */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 459377: mov ecx, dword ptr [esp + 0x20] */
	M32((DWORD)(m->esp + 0x78u)) = m->ecx;	/* 45937b: mov dword ptr [esp + 0x78], ecx */
	ST(3) = ST(3) + ST(0); FPOP();	/* 45937f: faddp st(3) */
	{ long double t = ST(0); ST(0) = ST(2); ST(2) = t; }	/* 459381: fxch st(2) */
	{ long double t = ST(0); __asm__("fsqrt" : "+t"(t)); ST(0) = t; }	/* 459383: fsqrt  */
	{ long double t = ST(0); ST(0) = ST(2); ST(2) = t; }	/* 459385: fxch st(2) */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 459387: fxch st(1) */
	{ long double t = ST(0); ST(0) = ST(2); ST(2) = t; }	/* 459389: fxch st(2) */
	{ long double x_ = ST(0), y_ = ST(1), r_; __asm__("fpatan" : "=t"(r_) : "0"(x_), "u"(y_) : "st(1)"); FPOP(); ST(0) = r_; }	/* 45938b: fpatan  */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 45938d: fxch st(1) */
	ST(0) = ST(0); FPOP();	/* 45938f: fstp st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9738u));	/* 459391: fmul dword ptr [0x4a9738] */
	MF((DWORD)(m->ebp + 0x1e0u)) = (float)ST(0); FPOP();	/* 459397: fstp dword ptr [ebp + 0x1e0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 45939d: fld dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 4593a1: fld dword ptr [esp + 0x20] */
	{ long double x_ = ST(0), y_ = ST(1), r_; __asm__("fpatan" : "=t"(r_) : "0"(x_), "u"(y_) : "st(1)"); FPOP(); ST(0) = r_; }	/* 4593a5: fpatan  */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9738u));	/* 4593a7: fmul dword ptr [0x4a9738] */
	MF((DWORD)(m->ebp + 0x1e4u)) = (float)ST(0); FPOP();	/* 4593ad: fstp dword ptr [ebp + 0x1e4] */
	goto L_4595be;	/* 4593b3: jmp 0x4595be */
L_4593b8:
	m->eax = M32((DWORD)(m->ebp + 0x8820u));	/* 4593b8: mov eax, dword ptr [ebp + 0x8820] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4593be: test eax, eax */
	if (m->sf != m->of) goto L_459470;	/* 4593c0: jl 0x459470 */
	m->edx = m->eax;	/* 4593c6: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4593c8: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4593cb: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4593cd: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4593d0: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4593d2: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4593d5: add edx, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + m->edx*8 + 0x1cd94fcu)));	/* 4593d7: fld dword ptr [ebx + edx*8 + 0x1cd94fc] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x154u));	/* 4593de: fsub dword ptr [ebp + 0x154] */
	m->eax = (DWORD)(m->ebx + m->edx*8 + 0x1cd94fcu);	/* 4593e4: lea eax, [ebx + edx*8 + 0x1cd94fc] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4593eb: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 4593ef: fld dword ptr [eax + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x158u));	/* 4593f2: fsub dword ptr [ebp + 0x158] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 4593f8: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 4593fc: fld dword ptr [eax + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x15cu));	/* 4593ff: fsub dword ptr [ebp + 0x15c] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 459405: mov eax, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 459409: mov ecx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x70u)) = m->eax;	/* 45940d: mov dword ptr [esp + 0x70], eax */
	M32((DWORD)(m->esp + 0x74u)) = m->ecx;	/* 459411: mov dword ptr [esp + 0x74], ecx */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 459415: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 459419: fld dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 45941d: fld dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 459421: fld dword ptr [esp + 0x1c] */
	ST(0) = -ST(0);	/* 459425: fchs  */
	{ long double t = ST(2); FPUSH(t); }	/* 459427: fld st(2) */
	ST(3) = ST(3) * ST(0); FPOP();	/* 459429: fmulp st(3) */
	{ long double t = ST(1); FPUSH(t); }	/* 45942b: fld st(1) */
	ST(0) = ST(0) * ST(2);	/* 45942d: fmul st(2) */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 45942f: mov edx, dword ptr [esp + 0x20] */
	M32((DWORD)(m->esp + 0x78u)) = m->edx;	/* 459433: mov dword ptr [esp + 0x78], edx */
	ST(3) = ST(3) + ST(0); FPOP();	/* 459437: faddp st(3) */
	{ long double t = ST(0); ST(0) = ST(2); ST(2) = t; }	/* 459439: fxch st(2) */
	{ long double t = ST(0); __asm__("fsqrt" : "+t"(t)); ST(0) = t; }	/* 45943b: fsqrt  */
	{ long double t = ST(0); ST(0) = ST(2); ST(2) = t; }	/* 45943d: fxch st(2) */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 45943f: fxch st(1) */
	{ long double t = ST(0); ST(0) = ST(2); ST(2) = t; }	/* 459441: fxch st(2) */
	{ long double x_ = ST(0), y_ = ST(1), r_; __asm__("fpatan" : "=t"(r_) : "0"(x_), "u"(y_) : "st(1)"); FPOP(); ST(0) = r_; }	/* 459443: fpatan  */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 459445: fxch st(1) */
	ST(0) = ST(0); FPOP();	/* 459447: fstp st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9738u));	/* 459449: fmul dword ptr [0x4a9738] */
	MF((DWORD)(m->ebp + 0x1e0u)) = (float)ST(0); FPOP();	/* 45944f: fstp dword ptr [ebp + 0x1e0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 459455: fld dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 459459: fld dword ptr [esp + 0x20] */
	{ long double x_ = ST(0), y_ = ST(1), r_; __asm__("fpatan" : "=t"(r_) : "0"(x_), "u"(y_) : "st(1)"); FPOP(); ST(0) = r_; }	/* 45945d: fpatan  */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9738u));	/* 45945f: fmul dword ptr [0x4a9738] */
	MF((DWORD)(m->ebp + 0x1e4u)) = (float)ST(0); FPOP();	/* 459465: fstp dword ptr [ebp + 0x1e4] */
	goto L_4595be;	/* 45946b: jmp 0x4595be */
L_459470:
	m->eax = M32((DWORD)(m->ebp + 0x87f8u));	/* 459470: mov eax, dword ptr [ebp + 0x87f8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 459476: test eax, eax */
	if (m->sf != m->of) goto L_459529;	/* 459478: jl 0x459529 */
	{ DWORD a_ = m->eax, b_ = 0x821b9u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45947e: add eax, 0x821b9 */
	m->ecx = (DWORD)(m->eax*8 + 0x0u);	/* 459483: lea ecx, [eax*8] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45948a: sub ecx, eax */
	m->eax = M32((DWORD)(m->ebp + 0x87fcu));	/* 45948c: mov eax, dword ptr [ebp + 0x87fc] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 459492: lea edx, [eax + eax*4] */
	m->eax = M32((DWORD)(m->ebx + m->ecx*4 + 0x0u));	/* 459495: mov eax, dword ptr [ebx + ecx*4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + m->edx*4 + 0x0u)));	/* 459498: fld dword ptr [eax + edx*4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x154u));	/* 45949b: fsub dword ptr [ebp + 0x154] */
	m->eax = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 4594a1: lea eax, [eax + edx*4] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4594a4: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 4594a8: fld dword ptr [eax + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x158u));	/* 4594ab: fsub dword ptr [ebp + 0x158] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 4594b1: mov ecx, dword ptr [esp + 0x18] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 4594b5: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 4594b9: fld dword ptr [eax + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x15cu));	/* 4594bc: fsub dword ptr [ebp + 0x15c] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 4594c2: mov edx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x70u)) = m->ecx;	/* 4594c6: mov dword ptr [esp + 0x70], ecx */
	M32((DWORD)(m->esp + 0x74u)) = m->edx;	/* 4594ca: mov dword ptr [esp + 0x74], edx */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 4594ce: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 4594d2: fld dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 4594d6: fld dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 4594da: fld dword ptr [esp + 0x1c] */
	ST(0) = -ST(0);	/* 4594de: fchs  */
	{ long double t = ST(2); FPUSH(t); }	/* 4594e0: fld st(2) */
	ST(3) = ST(3) * ST(0); FPOP();	/* 4594e2: fmulp st(3) */
	{ long double t = ST(1); FPUSH(t); }	/* 4594e4: fld st(1) */
	ST(0) = ST(0) * ST(2);	/* 4594e6: fmul st(2) */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 4594e8: mov eax, dword ptr [esp + 0x20] */
	M32((DWORD)(m->esp + 0x78u)) = m->eax;	/* 4594ec: mov dword ptr [esp + 0x78], eax */
	ST(3) = ST(3) + ST(0); FPOP();	/* 4594f0: faddp st(3) */
	{ long double t = ST(0); ST(0) = ST(2); ST(2) = t; }	/* 4594f2: fxch st(2) */
	{ long double t = ST(0); __asm__("fsqrt" : "+t"(t)); ST(0) = t; }	/* 4594f4: fsqrt  */
	{ long double t = ST(0); ST(0) = ST(2); ST(2) = t; }	/* 4594f6: fxch st(2) */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 4594f8: fxch st(1) */
	{ long double t = ST(0); ST(0) = ST(2); ST(2) = t; }	/* 4594fa: fxch st(2) */
	{ long double x_ = ST(0), y_ = ST(1), r_; __asm__("fpatan" : "=t"(r_) : "0"(x_), "u"(y_) : "st(1)"); FPOP(); ST(0) = r_; }	/* 4594fc: fpatan  */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 4594fe: fxch st(1) */
	ST(0) = ST(0); FPOP();	/* 459500: fstp st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9738u));	/* 459502: fmul dword ptr [0x4a9738] */
	MF((DWORD)(m->ebp + 0x1e0u)) = (float)ST(0); FPOP();	/* 459508: fstp dword ptr [ebp + 0x1e0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 45950e: fld dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 459512: fld dword ptr [esp + 0x20] */
	{ long double x_ = ST(0), y_ = ST(1), r_; __asm__("fpatan" : "=t"(r_) : "0"(x_), "u"(y_) : "st(1)"); FPOP(); ST(0) = r_; }	/* 459516: fpatan  */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9738u));	/* 459518: fmul dword ptr [0x4a9738] */
	MF((DWORD)(m->ebp + 0x1e4u)) = (float)ST(0); FPOP();	/* 45951e: fstp dword ptr [ebp + 0x1e4] */
	goto L_4595be;	/* 459524: jmp 0x4595be */
L_459529:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x8844u)));	/* 459529: fld dword ptr [ebp + 0x8844] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x2b8u));	/* 45952f: fsub dword ptr [esp + 0x2b8] */
	MF((DWORD)(m->ebp + 0x8844u)) = (float)ST(0);	/* 459536: fst dword ptr [ebp + 0x8844] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45953c: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 459542: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 459544: test ah, 0x41 */
	if (m->zf) goto L_4595be;	/* 459547: je 0x4595be */
	m->ecx = M32((DWORD)(0xa1efb8u));	/* 459549: mov ecx, dword ptr [0xa1efb8] */
	m->esi = 0x384u;	/* 45954f: mov esi, 0x384 */
	m->edx = m->ecx;	/* 459554: mov edx, ecx */
	{ DWORD a_ = m->edx, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 459556: and edx, 0xfff */
	m->eax = M32((DWORD)(m->edx*4 + 0xa106f8u));	/* 45955c: mov eax, dword ptr [edx*4 + 0xa106f8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 459563: xor edx, edx */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->esi; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 459565: div esi */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 459567: inc ecx */
	m->esi = 0xe10u;	/* 459568: mov esi, 0xe10 */
	M32((DWORD)(0xa1efb8u)) = m->ecx;	/* 45956d: mov dword ptr [0xa1efb8], ecx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe3eu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 459573: add edx, 0xfffffe3e */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 459579: mov dword ptr [esp + 0x14], edx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 45957d: xor edx, edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 45957f: fild dword ptr [esp + 0x14] */
	MF((DWORD)(m->ebp + 0x1e0u)) = (float)ST(0); FPOP();	/* 459583: fstp dword ptr [ebp + 0x1e0] */
	m->ecx = M32((DWORD)(0xa1efb8u));	/* 459589: mov ecx, dword ptr [0xa1efb8] */
	m->eax = m->ecx;	/* 45958f: mov eax, ecx */
	{ DWORD a_ = m->eax, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 459591: and eax, 0xfff */
	m->eax = M32((DWORD)(m->eax*4 + 0xa106f8u));	/* 459596: mov eax, dword ptr [eax*4 + 0xa106f8] */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->esi; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 45959d: div esi */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 45959f: inc ecx */
	M32((DWORD)(0xa1efb8u)) = m->ecx;	/* 4595a0: mov dword ptr [0xa1efb8], ecx */
	M32((DWORD)(m->ebp + 0x8844u)) = 0x40000000u;	/* 4595a6: mov dword ptr [ebp + 0x8844], 0x40000000 */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 4595b0: mov dword ptr [esp + 0x14], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 4595b4: fild dword ptr [esp + 0x14] */
	MF((DWORD)(m->ebp + 0x1e4u)) = (float)ST(0); FPOP();	/* 4595b8: fstp dword ptr [ebp + 0x1e4] */
L_4595be:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x1d4u)));	/* 4595be: fld dword ptr [ebp + 0x1d4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x154u));	/* 4595c4: fsub dword ptr [ebp + 0x154] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4595ca: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x1d8u)));	/* 4595ce: fld dword ptr [ebp + 0x1d8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x158u));	/* 4595d4: fsub dword ptr [ebp + 0x158] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 4595da: mov ecx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 4595de: mov dword ptr [esp + 0x28], ecx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 4595e2: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x1dcu)));	/* 4595e6: fld dword ptr [ebp + 0x1dc] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x15cu));	/* 4595ec: fsub dword ptr [ebp + 0x15c] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 4595f2: mov edx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 4595f6: mov dword ptr [esp + 0x2c], edx */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 4595fa: fstp dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 4595fe: mov eax, dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x164u)));	/* 459602: fld dword ptr [ebp + 0x164] */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 459608: mov dword ptr [esp + 0x30], eax */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 45960c: call 0x49ec14 */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 459611: neg eax */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 459613: push eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 459614: push 2 */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 459616: lea ecx, [esp + 0x30] */
	m->esp -= 4; M32(m->esp) = 0x45961fu; native_call(m, 0x4677c0u);	/* 45961a: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x160u)));	/* 45961f: fld dword ptr [ebp + 0x160] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 459625: call 0x49ec14 */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 45962a: neg eax */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45962c: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45962d: push edi */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 45962e: lea ecx, [esp + 0x30] */
	m->esp -= 4; M32(m->esp) = 0x459637u; native_call(m, 0x4677c0u);	/* 459632: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 459637: fld dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 45963b: fld dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 45963f: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 459643: fmul dword ptr [esp + 0x28] */
	{ long double t = ST(1); FPUSH(t); }	/* 459647: fld st(1) */
	ST(0) = ST(0) * ST(2);	/* 459649: fmul st(2) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 45964b: faddp st(1) */
	{ long double t = ST(2); FPUSH(t); }	/* 45964d: fld st(2) */
	ST(0) = ST(0) * ST(3);	/* 45964f: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 459651: faddp st(1) */
	{ long double t = ST(0); __asm__("fsqrt" : "+t"(t)); ST(0) = t; }	/* 459653: fsqrt  */
	ST(2) = ST(0); FPOP();	/* 459655: fstp st(2) */
	ST(0) = ST(0); FPOP();	/* 459657: fstp st(0) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9450u)); FPOP();	/* 459659: fcomp dword ptr [0x4a9450] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45965f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 459661: test ah, 0x41 */
	if (!m->zf) goto L_459864;	/* 459664: jne 0x459864 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 45966a: fld dword ptr [esp + 0x28] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45966e: fcomp dword ptr [0x4a93e8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 459674: fld dword ptr [esp + 0x28] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 459678: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45967a: test ah, 1 */
	if (m->zf) goto L_459681;	/* 45967d: je 0x459681 */
	ST(0) = -ST(0);	/* 45967f: fchs  */
L_459681:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 459681: fld dword ptr [esp + 0x30] */
	FCOM(ST(0), ST(1)); FPOP();	/* 459685: fcomp st(1) */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 459687: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 459689: test ah, 0x41 */
	ST(0) = ST(0); FPOP();	/* 45968c: fstp st(0) */
	if (!m->zf) goto L_4596d6;	/* 45968e: jne 0x4596d6 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 459690: fld dword ptr [esp + 0x2c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 459694: fcomp dword ptr [0x4a93e8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 45969a: fld dword ptr [esp + 0x2c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45969e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4596a0: test ah, 1 */
	if (m->zf) goto L_4596a7;	/* 4596a3: je 0x4596a7 */
	ST(0) = -ST(0);	/* 4596a5: fchs  */
L_4596a7:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 4596a7: fld dword ptr [esp + 0x30] */
	FCOM(ST(0), ST(1)); FPOP();	/* 4596ab: fcomp st(1) */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4596ad: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4596af: test ah, 0x41 */
	ST(0) = ST(0); FPOP();	/* 4596b2: fstp st(0) */
	if (!m->zf) goto L_45973d;	/* 4596b4: jne 0x45973d */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 4596ba: fld dword ptr [esp + 0x30] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9450u)); FPOP();	/* 4596be: fcomp dword ptr [0x4a9450] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4596c4: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4596c6: test ah, 0x41 */
	if (!m->zf) goto L_45973d;	/* 4596c9: jne 0x45973d */
	M32((DWORD)(m->ebp + 0x44cu)) = m->edi;	/* 4596cb: mov dword ptr [ebp + 0x44c], edi */
	goto L_459864;	/* 4596d1: jmp 0x459864 */
L_4596d6:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 4596d6: fld dword ptr [esp + 0x28] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 4596da: fcomp dword ptr [0x4a93e8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 4596e0: fld dword ptr [esp + 0x28] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4596e4: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4596e6: test ah, 1 */
	if (m->zf) goto L_4596ed;	/* 4596e9: je 0x4596ed */
	ST(0) = -ST(0);	/* 4596eb: fchs  */
L_4596ed:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 4596ed: fld dword ptr [esp + 0x30] */
	ST(0) = -ST(0);	/* 4596f1: fchs  */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 4596f3: fst dword ptr [esp + 0x14] */
	FCOM(ST(0), ST(1)); FPOP();	/* 4596f7: fcomp st(1) */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4596f9: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4596fb: test ah, 0x41 */
	ST(0) = ST(0); FPOP();	/* 4596fe: fstp st(0) */
	if (!m->zf) goto L_459763;	/* 459700: jne 0x459763 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 459702: fld dword ptr [esp + 0x2c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 459706: fcomp dword ptr [0x4a93e8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 45970c: fld dword ptr [esp + 0x2c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 459710: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 459712: test ah, 1 */
	if (m->zf) goto L_459719;	/* 459715: je 0x459719 */
	ST(0) = -ST(0);	/* 459717: fchs  */
L_459719:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 459719: fld dword ptr [esp + 0x14] */
	FCOM(ST(0), ST(1)); FPOP();	/* 45971d: fcomp st(1) */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45971f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 459721: test ah, 0x41 */
	ST(0) = ST(0); FPOP();	/* 459724: fstp st(0) */
	if (!m->zf) goto L_45973d;	/* 459726: jne 0x45973d */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 459728: fld dword ptr [esp + 0x14] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9450u)); FPOP();	/* 45972c: fcomp dword ptr [0x4a9450] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 459732: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 459734: test ah, 0x41 */
	if (m->zf) goto L_45985e;	/* 459737: je 0x45985e */
L_45973d:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 45973d: fld dword ptr [esp + 0x2c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9450u)); FPOP();	/* 459741: fcomp dword ptr [0x4a9450] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 459747: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 459749: test ah, 0x41 */
	if (!m->zf) goto L_4597d8;	/* 45974c: jne 0x4597d8 */
	M32((DWORD)(m->ebp + 0x470u)) = m->edi;	/* 459752: mov dword ptr [ebp + 0x470], edi */
	M32((DWORD)(m->ebp + 0x44cu)) = m->edi;	/* 459758: mov dword ptr [ebp + 0x44c], edi */
	goto L_459864;	/* 45975e: jmp 0x459864 */
L_459763:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 459763: fld dword ptr [esp + 0x28] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 459767: fcomp dword ptr [0x4a93e8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 45976d: fld dword ptr [esp + 0x2c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 459771: fnstsw ax */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 459773: fcomp dword ptr [0x4a93e8] */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 459779: test ah, 0x41 */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45977c: fnstsw ax */
	if (!m->zf) goto L_4597ed;	/* 45977e: jne 0x4597ed */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 459780: fld dword ptr [esp + 0x2c] */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 459784: test ah, 1 */
	if (m->zf) goto L_45978b;	/* 459787: je 0x45978b */
	ST(0) = -ST(0);	/* 459789: fchs  */
L_45978b:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 45978b: fld dword ptr [esp + 0x28] */
	FCOM(ST(0), ST(1)); FPOP();	/* 45978f: fcomp st(1) */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 459791: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 459793: test ah, 0x41 */
	ST(0) = ST(0); FPOP();	/* 459796: fstp st(0) */
	if (!m->zf) goto L_4597b6;	/* 459798: jne 0x4597b6 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 45979a: fld dword ptr [esp + 0x28] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9450u)); FPOP();	/* 45979e: fcomp dword ptr [0x4a9450] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4597a4: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4597a6: test ah, 0x41 */
	if (!m->zf) goto L_4597b6;	/* 4597a9: jne 0x4597b6 */
	M32((DWORD)(m->ebp + 0x454u)) = m->edi;	/* 4597ab: mov dword ptr [ebp + 0x454], edi */
	goto L_459864;	/* 4597b1: jmp 0x459864 */
L_4597b6:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 4597b6: fld dword ptr [esp + 0x2c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9450u)); FPOP();	/* 4597ba: fcomp dword ptr [0x4a9450] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4597c0: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4597c2: test ah, 0x41 */
	if (!m->zf) goto L_4597d8;	/* 4597c5: jne 0x4597d8 */
	M32((DWORD)(m->ebp + 0x470u)) = m->edi;	/* 4597c7: mov dword ptr [ebp + 0x470], edi */
	M32((DWORD)(m->ebp + 0x44cu)) = m->edi;	/* 4597cd: mov dword ptr [ebp + 0x44c], edi */
	goto L_459864;	/* 4597d3: jmp 0x459864 */
L_4597d8:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 4597d8: fld dword ptr [esp + 0x2c] */
	ST(0) = -ST(0);	/* 4597dc: fchs  */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9450u)); FPOP();	/* 4597de: fcomp dword ptr [0x4a9450] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4597e4: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4597e6: test ah, 0x41 */
	if (!m->zf) goto L_459864;	/* 4597e9: jne 0x459864 */
	goto L_459858;	/* 4597eb: jmp 0x459858 */
L_4597ed:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 4597ed: fld dword ptr [esp + 0x2c] */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4597f1: test ah, 1 */
	if (m->zf) goto L_4597f8;	/* 4597f4: je 0x4597f8 */
	ST(0) = -ST(0);	/* 4597f6: fchs  */
L_4597f8:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 4597f8: fld dword ptr [esp + 0x28] */
	ST(0) = -ST(0);	/* 4597fc: fchs  */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 4597fe: fst dword ptr [esp + 0x14] */
	FCOM(ST(0), ST(1)); FPOP();	/* 459802: fcomp st(1) */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 459804: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 459806: test ah, 0x41 */
	ST(0) = ST(0); FPOP();	/* 459809: fstp st(0) */
	if (!m->zf) goto L_459826;	/* 45980b: jne 0x459826 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 45980d: fld dword ptr [esp + 0x14] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9450u)); FPOP();	/* 459811: fcomp dword ptr [0x4a9450] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 459817: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 459819: test ah, 0x41 */
	if (!m->zf) goto L_459826;	/* 45981c: jne 0x459826 */
	M32((DWORD)(m->ebp + 0x458u)) = m->edi;	/* 45981e: mov dword ptr [ebp + 0x458], edi */
	goto L_459864;	/* 459824: jmp 0x459864 */
L_459826:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 459826: fld dword ptr [esp + 0x2c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9450u)); FPOP();	/* 45982a: fcomp dword ptr [0x4a9450] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 459830: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 459832: test ah, 0x41 */
	if (!m->zf) goto L_459845;	/* 459835: jne 0x459845 */
	M32((DWORD)(m->ebp + 0x470u)) = m->edi;	/* 459837: mov dword ptr [ebp + 0x470], edi */
	M32((DWORD)(m->ebp + 0x44cu)) = m->edi;	/* 45983d: mov dword ptr [ebp + 0x44c], edi */
	goto L_459864;	/* 459843: jmp 0x459864 */
L_459845:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 459845: fld dword ptr [esp + 0x2c] */
	ST(0) = -ST(0);	/* 459849: fchs  */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9450u)); FPOP();	/* 45984b: fcomp dword ptr [0x4a9450] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 459851: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 459853: test ah, 0x41 */
	if (!m->zf) goto L_459864;	/* 459856: jne 0x459864 */
L_459858:
	M32((DWORD)(m->ebp + 0x470u)) = m->edi;	/* 459858: mov dword ptr [ebp + 0x470], edi */
L_45985e:
	M32((DWORD)(m->ebp + 0x450u)) = m->edi;	/* 45985e: mov dword ptr [ebp + 0x450], edi */
L_459864:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2b8u)));	/* 459864: fld dword ptr [esp + 0x2b8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x6cu));	/* 45986b: fmul dword ptr [ebp + 0x6c] */
	m->ecx = M32((DWORD)(m->ebp + 0x1e0u));	/* 45986e: mov ecx, dword ptr [ebp + 0x1e0] */
	m->edx = M32((DWORD)(m->ebp + 0x160u));	/* 459874: mov edx, dword ptr [ebp + 0x160] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45987a: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45987b: push edx */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 45987c: fstp dword ptr [esp + 0x2c] */
	m->esp -= 4; M32(m->esp) = 0x459885u; { long double r_ = native_call_fp(m, 0x46c140u); FPUSH(r_); }	/* 459880: call 0x46c140 */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0);	/* 459885: fst dword ptr [esp + 0x1c] */
	MF((DWORD)(m->ebp + 0x464u)) = (float)ST(0);	/* 459889: fst dword ptr [ebp + 0x464] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x2cu)); FPOP();	/* 45988f: fcomp dword ptr [esp + 0x2c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 459893: add esp, 8 */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 459896: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 459898: test ah, 0x41 */
	if (!m->zf) goto L_4598a9;	/* 45989b: jne 0x4598a9 */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 45989d: mov eax, dword ptr [esp + 0x24] */
	M32((DWORD)(m->ebp + 0x464u)) = m->eax;	/* 4598a1: mov dword ptr [ebp + 0x464], eax */
	goto L_4598c6;	/* 4598a7: jmp 0x4598c6 */
L_4598a9:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 4598a9: fld dword ptr [esp + 0x24] */
	ST(0) = -ST(0);	/* 4598ad: fchs  */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 4598af: fld dword ptr [esp + 0x14] */
	FCOM(ST(0), ST(1)); FPOP();	/* 4598b3: fcomp st(1) */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4598b5: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4598b7: test ah, 1 */
	if (m->zf) goto L_4598c4;	/* 4598ba: je 0x4598c4 */
	MF((DWORD)(m->ebp + 0x464u)) = (float)ST(0); FPOP();	/* 4598bc: fstp dword ptr [ebp + 0x464] */
	goto L_4598c6;	/* 4598c2: jmp 0x4598c6 */
L_4598c4:
	ST(0) = ST(0); FPOP();	/* 4598c4: fstp st(0) */
L_4598c6:
	m->ecx = M32((DWORD)(m->ebp + 0x1e4u));	/* 4598c6: mov ecx, dword ptr [ebp + 0x1e4] */
	m->edx = M32((DWORD)(m->ebp + 0x164u));	/* 4598cc: mov edx, dword ptr [ebp + 0x164] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4598d2: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4598d3: push edx */
	m->esp -= 4; M32(m->esp) = 0x4598d9u; { long double r_ = native_call_fp(m, 0x46c140u); FPUSH(r_); }	/* 4598d4: call 0x46c140 */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0);	/* 4598d9: fst dword ptr [esp + 0x1c] */
	MF((DWORD)(m->ebp + 0x468u)) = (float)ST(0);	/* 4598dd: fst dword ptr [ebp + 0x468] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x2cu)); FPOP();	/* 4598e3: fcomp dword ptr [esp + 0x2c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4598e7: add esp, 8 */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4598ea: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4598ec: test ah, 0x41 */
	if (!m->zf) goto L_4598fd;	/* 4598ef: jne 0x4598fd */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 4598f1: mov eax, dword ptr [esp + 0x24] */
	M32((DWORD)(m->ebp + 0x468u)) = m->eax;	/* 4598f5: mov dword ptr [ebp + 0x468], eax */
	goto L_45991a;	/* 4598fb: jmp 0x45991a */
L_4598fd:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 4598fd: fld dword ptr [esp + 0x24] */
	ST(0) = -ST(0);	/* 459901: fchs  */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 459903: fld dword ptr [esp + 0x14] */
	FCOM(ST(0), ST(1)); FPOP();	/* 459907: fcomp st(1) */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 459909: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45990b: test ah, 1 */
	if (m->zf) goto L_459918;	/* 45990e: je 0x459918 */
	MF((DWORD)(m->ebp + 0x468u)) = (float)ST(0); FPOP();	/* 459910: fstp dword ptr [ebp + 0x468] */
	goto L_45991a;	/* 459916: jmp 0x45991a */
L_459918:
	ST(0) = ST(0); FPOP();	/* 459918: fstp st(0) */
L_45991a:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x11cu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45991a: cmp dword ptr [ebp + 0x11c], edi */
	if (!m->zf) goto L_459928;	/* 459920: jne 0x459928 */
	M32((DWORD)(m->ebp + 0x474u)) = m->edi;	/* 459922: mov dword ptr [ebp + 0x474], edi */
L_459928:
	m->eax = M32((DWORD)(m->ebp + 0x4d0u));	/* 459928: mov eax, dword ptr [ebp + 0x4d0] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45992e: cmp eax, 4 */
	if (!m->cf && !m->zf) goto L_4599ab;	/* 459931: ja 0x4599ab */
	switch (m->eax) { case 0: goto L_45993a; case 1: goto L_45994e; case 2: goto L_459969; case 3: goto L_459975; case 4: goto L_459981; default: abort(); }	/* 459933: jmp dword ptr [eax*4 + 0x45d3a4] */
L_45993a:
	m->ecx = M32((DWORD)(m->ebp + 0x1cu));	/* 45993a: mov ecx, dword ptr [ebp + 0x1c] */
	m->edx = M32((DWORD)(m->ebp + 0x20u));	/* 45993d: mov edx, dword ptr [ebp + 0x20] */
	M32((DWORD)(m->ebp + 0x128u)) = m->ecx;	/* 459940: mov dword ptr [ebp + 0x128], ecx */
	M32((DWORD)(m->ebp + 0x12cu)) = m->edx;	/* 459946: mov dword ptr [ebp + 0x12c], edx */
	goto L_4599ab;	/* 45994c: jmp 0x4599ab */
L_45994e:
	m->eax = (DWORD)(m->ebp + 0x130u);	/* 45994e: lea eax, [ebp + 0x130] */
	m->ecx = 0x4u;	/* 459954: mov ecx, 4 */
L_459959:
	m->edx = M32((DWORD)(m->eax + 0xfffffef8u));	/* 459959: mov edx, dword ptr [eax - 0x108] */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 45995f: mov dword ptr [eax], edx */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 459961: add eax, 4 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 459964: dec ecx */
	if (!m->zf) goto L_459959;	/* 459965: jne 0x459959 */
	goto L_4599ab;	/* 459967: jmp 0x4599ab */
L_459969:
	M32((DWORD)(m->ebp + 0x4d4u)) = 0x1u;	/* 459969: mov dword ptr [ebp + 0x4d4], 1 */
	goto L_4599ab;	/* 459973: jmp 0x4599ab */
L_459975:
	M32((DWORD)(m->ebp + 0x4d4u)) = 0x0u;	/* 459975: mov dword ptr [ebp + 0x4d4], 0 */
	goto L_4599ab;	/* 45997f: jmp 0x4599ab */
L_459981:
	m->edx = M32((DWORD)(m->ebp + 0xe8u));	/* 459981: mov edx, dword ptr [ebp + 0xe8] */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 459987: push -1 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 459989: inc edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45998a: push 0 */
	M32((DWORD)(m->ebp + 0xe8u)) = m->edx;	/* 45998c: mov dword ptr [ebp + 0xe8], edx */
	m->eax = M32((DWORD)(m->ebp + 0x128u));	/* 459992: mov eax, dword ptr [ebp + 0x128] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 459998: push eax */
	m->eax = M32((DWORD)(m->esp + 0x2c0u));	/* 459999: mov eax, dword ptr [esp + 0x2c0] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4599a0: push 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4599a2: push eax */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4599a3: push eax */
	m->ecx = m->ebx;	/* 4599a4: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x4599abu; native_call(m, 0x460000u);	/* 4599a6: call 0x460000 */
L_4599ab:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2b8u)));	/* 4599ab: fld dword ptr [esp + 0x2b8] */
	m->eax = M32((DWORD)(m->ebp + 0x474u));	/* 4599b2: mov eax, dword ptr [ebp + 0x474] */
	M32((DWORD)(m->ebp + 0x4d0u)) = 0xffffffffu;	/* 4599b8: mov dword ptr [ebp + 0x4d0], 0xffffffff */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x38u));	/* 4599c2: fmul dword ptr [ebp + 0x38] */
	m->esi = 0x1u;	/* 4599c5: mov esi, 1 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4599ca: cmp eax, esi */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 4599cc: fstp dword ptr [esp + 0x10] */
	if (!m->zf) goto L_4599dc;	/* 4599d0: jne 0x4599dc */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4599d2: fld dword ptr [esp + 0x10] */
	ST(0) = ST(0) + ST(0);	/* 4599d6: fadd st(0), st(0) */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 4599d8: fstp dword ptr [esp + 0x10] */
L_4599dc:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2b8u)));	/* 4599dc: fld dword ptr [esp + 0x2b8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x3cu));	/* 4599e3: fmul dword ptr [ebp + 0x3c] */
	M32((DWORD)(m->esp + 0xb0u)) = 0x0u;	/* 4599e6: mov dword ptr [esp + 0xb0], 0 */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 4599f1: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x16cu)));	/* 4599f5: fld dword ptr [ebp + 0x16c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x50u));	/* 4599fb: fmul dword ptr [ebp + 0x50] */
	MF((DWORD)(m->esp + 0xa8u)) = (float)ST(0); FPOP();	/* 4599fe: fstp dword ptr [esp + 0xa8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x168u)));	/* 459a05: fld dword ptr [ebp + 0x168] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x50u));	/* 459a0b: fmul dword ptr [ebp + 0x50] */
	MF((DWORD)(m->esp + 0xacu)) = (float)ST(0); FPOP();	/* 459a0e: fstp dword ptr [esp + 0xac] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 459a15: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x170u));	/* 459a1b: fsub dword ptr [ebp + 0x170] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x160u)));	/* 459a21: fld dword ptr [ebp + 0x160] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9734u));	/* 459a27: fadd dword ptr [0x4a9734] */
	ST(1) = ST(1) * ST(0); FPOP();	/* 459a2d: fmulp st(1) */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 459a2f: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 459a34: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 459a35: push esi */
	m->ecx = (DWORD)(m->esp + 0xb0u);	/* 459a36: lea ecx, [esp + 0xb0] */
	m->esp -= 4; M32(m->esp) = 0x459a42u; native_call(m, 0x4677c0u);	/* 459a3d: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x164u)));	/* 459a42: fld dword ptr [ebp + 0x164] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 459a48: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 459a4d: push eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 459a4e: push 2 */
	m->ecx = (DWORD)(m->esp + 0xb0u);	/* 459a50: lea ecx, [esp + 0xb0] */
	m->esp -= 4; M32(m->esp) = 0x459a5cu; native_call(m, 0x4677c0u);	/* 459a57: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x378u)));	/* 459a5c: fld dword ptr [ebp + 0x378] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0xa8u));	/* 459a62: fsub dword ptr [esp + 0xa8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 459a69: fld dword ptr [esp + 0x24] */
	ST(0) = -ST(0);	/* 459a6d: fchs  */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 459a6f: fstp dword ptr [esp + 0x14] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x14u));	/* 459a73: fcom dword ptr [esp + 0x14] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 459a77: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 459a79: test ah, 1 */
	if (m->zf) goto L_459a92;	/* 459a7c: je 0x459a92 */
	ST(0) = ST(0); FPOP();	/* 459a7e: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 459a80: fld dword ptr [esp + 0x24] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x378u));	/* 459a84: fadd dword ptr [ebp + 0x378] */
	MF((DWORD)(m->ebp + 0x378u)) = (float)ST(0); FPOP();	/* 459a8a: fstp dword ptr [ebp + 0x378] */
	goto L_459abc;	/* 459a90: jmp 0x459abc */
L_459a92:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x24u)); FPOP();	/* 459a92: fcomp dword ptr [esp + 0x24] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 459a96: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 459a98: test ah, 0x41 */
	if (!m->zf) goto L_459aaf;	/* 459a9b: jne 0x459aaf */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x378u)));	/* 459a9d: fld dword ptr [ebp + 0x378] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 459aa3: fsub dword ptr [esp + 0x24] */
	MF((DWORD)(m->ebp + 0x378u)) = (float)ST(0); FPOP();	/* 459aa7: fstp dword ptr [ebp + 0x378] */
	goto L_459abc;	/* 459aad: jmp 0x459abc */
L_459aaf:
	m->ecx = M32((DWORD)(m->esp + 0xa8u));	/* 459aaf: mov ecx, dword ptr [esp + 0xa8] */
	M32((DWORD)(m->ebp + 0x378u)) = m->ecx;	/* 459ab6: mov dword ptr [ebp + 0x378], ecx */
L_459abc:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x37cu)));	/* 459abc: fld dword ptr [ebp + 0x37c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0xacu));	/* 459ac2: fsub dword ptr [esp + 0xac] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x14u));	/* 459ac9: fcom dword ptr [esp + 0x14] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 459acd: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 459acf: test ah, 1 */
	if (m->zf) goto L_459ae8;	/* 459ad2: je 0x459ae8 */
	ST(0) = ST(0); FPOP();	/* 459ad4: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 459ad6: fld dword ptr [esp + 0x24] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x37cu));	/* 459ada: fadd dword ptr [ebp + 0x37c] */
	MF((DWORD)(m->ebp + 0x37cu)) = (float)ST(0); FPOP();	/* 459ae0: fstp dword ptr [ebp + 0x37c] */
	goto L_459b12;	/* 459ae6: jmp 0x459b12 */
L_459ae8:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x24u)); FPOP();	/* 459ae8: fcomp dword ptr [esp + 0x24] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 459aec: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 459aee: test ah, 0x41 */
	if (!m->zf) goto L_459b05;	/* 459af1: jne 0x459b05 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x37cu)));	/* 459af3: fld dword ptr [ebp + 0x37c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 459af9: fsub dword ptr [esp + 0x24] */
	MF((DWORD)(m->ebp + 0x37cu)) = (float)ST(0); FPOP();	/* 459afd: fstp dword ptr [ebp + 0x37c] */
	goto L_459b12;	/* 459b03: jmp 0x459b12 */
L_459b05:
	m->edx = M32((DWORD)(m->esp + 0xacu));	/* 459b05: mov edx, dword ptr [esp + 0xac] */
	M32((DWORD)(m->ebp + 0x37cu)) = m->edx;	/* 459b0c: mov dword ptr [ebp + 0x37c], edx */
L_459b12:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x380u)));	/* 459b12: fld dword ptr [ebp + 0x380] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0xb0u));	/* 459b18: fsub dword ptr [esp + 0xb0] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x14u));	/* 459b1f: fcom dword ptr [esp + 0x14] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 459b23: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 459b25: test ah, 1 */
	if (m->zf) goto L_459b3e;	/* 459b28: je 0x459b3e */
	ST(0) = ST(0); FPOP();	/* 459b2a: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 459b2c: fld dword ptr [esp + 0x24] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x380u));	/* 459b30: fadd dword ptr [ebp + 0x380] */
	MF((DWORD)(m->ebp + 0x380u)) = (float)ST(0); FPOP();	/* 459b36: fstp dword ptr [ebp + 0x380] */
	goto L_459b68;	/* 459b3c: jmp 0x459b68 */
L_459b3e:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x24u)); FPOP();	/* 459b3e: fcomp dword ptr [esp + 0x24] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 459b42: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 459b44: test ah, 0x41 */
	if (!m->zf) goto L_459b5b;	/* 459b47: jne 0x459b5b */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x380u)));	/* 459b49: fld dword ptr [ebp + 0x380] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 459b4f: fsub dword ptr [esp + 0x24] */
	MF((DWORD)(m->ebp + 0x380u)) = (float)ST(0); FPOP();	/* 459b53: fstp dword ptr [ebp + 0x380] */
	goto L_459b68;	/* 459b59: jmp 0x459b68 */
L_459b5b:
	m->eax = M32((DWORD)(m->esp + 0xb0u));	/* 459b5b: mov eax, dword ptr [esp + 0xb0] */
	M32((DWORD)(m->ebp + 0x380u)) = m->eax;	/* 459b62: mov dword ptr [ebp + 0x380], eax */
L_459b68:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2b8u)));	/* 459b68: fld dword ptr [esp + 0x2b8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9468u)); FPOP();	/* 459b6f: fcomp dword ptr [0x4a9468] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 459b75: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 459b77: test ah, 1 */
	if (m->zf) goto L_459b89;	/* 459b7a: je 0x459b89 */
	m->ecx = M32((DWORD)(m->esp + 0x2b8u));	/* 459b7c: mov ecx, dword ptr [esp + 0x2b8] */
	M32((DWORD)(m->esp + 0x24u)) = m->ecx;	/* 459b83: mov dword ptr [esp + 0x24], ecx */
	goto L_459b91;	/* 459b87: jmp 0x459b91 */
L_459b89:
	M32((DWORD)(m->esp + 0x24u)) = 0x3d4ccccdu;	/* 459b89: mov dword ptr [esp + 0x24], 0x3d4ccccd */
L_459b91:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 459b91: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x378u));	/* 459b95: fmul dword ptr [ebp + 0x378] */
	m->ecx = (DWORD)(m->ebp + 0x384u);	/* 459b9b: lea ecx, [ebp + 0x384] */
	m->edx = m->ecx;	/* 459ba1: mov edx, ecx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 459ba3: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 459ba7: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x37cu));	/* 459bab: fmul dword ptr [ebp + 0x37c] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 459bb1: mov eax, dword ptr [esp + 0x18] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 459bb5: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 459bb9: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x380u));	/* 459bbd: fmul dword ptr [ebp + 0x380] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 459bc3: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 459bc5: mov eax, dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 459bc9: fstp dword ptr [esp + 0x20] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 459bcd: mov dword ptr [edx + 4], eax */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 459bd0: mov eax, dword ptr [esp + 0x20] */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 459bd4: mov dword ptr [edx + 8], eax */
	m->edx = M32((DWORD)(m->ebp + 0x110u));	/* 459bd7: mov edx, dword ptr [ebp + 0x110] */
	{ DWORD a_ = m->edx, b_ = M32((DWORD)(m->ebx + 0x202e8d4u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 459bdd: cmp edx, dword ptr [ebx + 0x202e8d4] */
	if (!m->zf) goto L_459c6e;	/* 459be3: jne 0x459c6e */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x14cu)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 459be9: cmp dword ptr [ebp + 0x14c], esi */
	if (!m->zf) goto L_459c6e;	/* 459bef: jne 0x459c6e */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x8854u)));	/* 459bf1: fld dword ptr [ebp + 0x8854] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 459bf7: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 459bfd: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 459bff: test ah, 0x41 */
	if (!m->zf) goto L_459c6e;	/* 459c02: jne 0x459c6e */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 459c04: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x885cu));	/* 459c08: fmul dword ptr [ebp + 0x885c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 459c0e: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x8860u));	/* 459c12: fmul dword ptr [ebp + 0x8860] */
	MF((DWORD)(m->esp + 0x5cu)) = (float)ST(0); FPOP();	/* 459c18: fstp dword ptr [esp + 0x5c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 459c1c: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x8864u));	/* 459c20: fmul dword ptr [ebp + 0x8864] */
	MF((DWORD)(m->esp + 0x60u)) = (float)ST(0); FPOP();	/* 459c26: fstp dword ptr [esp + 0x60] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x8854u)));	/* 459c2a: fld dword ptr [ebp + 0x8854] */
	{ long double t = ST(0); FPUSH(t); }	/* 459c30: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 459c32: fmul st(1) */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 459c34: fstp dword ptr [esp + 0x14] */
	ST(0) = ST(0); FPOP();	/* 459c38: fstp st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 459c3a: fmul dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x5cu)));	/* 459c3e: fld dword ptr [esp + 0x5c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 459c42: fmul dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 459c46: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x60u)));	/* 459c4a: fld dword ptr [esp + 0x60] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 459c4e: fmul dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 459c52: fstp dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x0u));	/* 459c56: fadd dword ptr [ecx] */
	MF((DWORD)(m->ecx + 0x0u)) = (float)ST(0); FPOP();	/* 459c58: fstp dword ptr [ecx] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 459c5a: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x4u));	/* 459c5e: fadd dword ptr [ecx + 4] */
	MF((DWORD)(m->ecx + 0x4u)) = (float)ST(0); FPOP();	/* 459c61: fstp dword ptr [ecx + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 459c64: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x8u));	/* 459c68: fadd dword ptr [ecx + 8] */
	MF((DWORD)(m->ecx + 0x8u)) = (float)ST(0); FPOP();	/* 459c6b: fstp dword ptr [ecx + 8] */
L_459c6e:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x4b4u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 459c6e: cmp dword ptr [ebp + 0x4b4], esi */
	if (!m->zf) goto L_459c80;	/* 459c74: jne 0x459c80 */
	M32((DWORD)(m->ebp + 0x474u)) = 0x0u;	/* 459c76: mov dword ptr [ebp + 0x474], 0 */
L_459c80:
	m->eax = M32((DWORD)(m->ebp + 0x110u));	/* 459c80: mov eax, dword ptr [ebp + 0x110] */
	m->edx = M32((DWORD)(m->ebx + 0x202e8d4u));	/* 459c86: mov edx, dword ptr [ebx + 0x202e8d4] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 459c8c: cmp eax, edx */
	if (!m->zf) goto L_45a5d1;	/* 459c8e: jne 0x45a5d1 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x14cu)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 459c94: cmp dword ptr [ebp + 0x14c], esi */
	if (!m->zf) goto L_45a5d1;	/* 459c9a: jne 0x45a5d1 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x154u)));	/* 459ca0: fld dword ptr [ebp + 0x154] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x0u));	/* 459ca6: fadd dword ptr [ecx] */
	m->eax = (DWORD)(m->ebp + 0x180u);	/* 459ca8: lea eax, [ebp + 0x180] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 459cae: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x4u)));	/* 459cb2: fld dword ptr [ecx + 4] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x158u));	/* 459cb5: fadd dword ptr [ebp + 0x158] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 459cbb: mov edx, dword ptr [esp + 0x18] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 459cbf: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x8u)));	/* 459cc3: fld dword ptr [ecx + 8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x15cu));	/* 459cc6: fadd dword ptr [ebp + 0x15c] */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 459ccc: mov dword ptr [eax], edx */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 459cce: mov edx, dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 459cd2: fstp dword ptr [esp + 0x20] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 459cd6: mov dword ptr [eax + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 459cd9: mov edx, dword ptr [esp + 0x20] */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 459cdd: mov dword ptr [eax + 8], edx */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 459ce0: mov eax, dword ptr [ecx] */
	M32((DWORD)(m->esp + 0x90u)) = m->eax;	/* 459ce2: mov dword ptr [esp + 0x90], eax */
	m->edx = M32((DWORD)(m->ecx + 0x4u));	/* 459ce9: mov edx, dword ptr [ecx + 4] */
	M32((DWORD)(m->esp + 0x94u)) = m->edx;	/* 459cec: mov dword ptr [esp + 0x94], edx */
	m->eax = M32((DWORD)(m->ecx + 0x8u));	/* 459cf3: mov eax, dword ptr [ecx + 8] */
	m->ecx = (DWORD)(m->esp + 0x90u);	/* 459cf6: lea ecx, [esp + 0x90] */
	M32((DWORD)(m->esp + 0x98u)) = m->eax;	/* 459cfd: mov dword ptr [esp + 0x98], eax */
	m->esp -= 4; M32(m->esp) = 0x459d09u; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 459d04: call 0x467760 */
	m->eax = M32((DWORD)(m->ebx + 0x202e8c8u));	/* 459d09: mov eax, dword ptr [ebx + 0x202e8c8] */
	M32((DWORD)(m->esp + 0x24u)) = 0x0u;	/* 459d0f: mov dword ptr [esp + 0x24], 0 */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 459d17: fstp dword ptr [esp + 0x48] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 459d1b: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_459fda;	/* 459d1d: jle 0x459fda */
	m->ecx = (DWORD)(m->ebx + 0x1cd9504u);	/* 459d23: lea ecx, [ebx + 0x1cd9504] */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 459d29: mov dword ptr [esp + 0x14], ecx */
L_459d2d:
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 459d2d: mov edx, dword ptr [esp + 0x14] */
	{ DWORD a_ = M32((DWORD)(m->edx + 0xfffffff0u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 459d31: cmp dword ptr [edx - 0x10], 1 */
	if (!m->zf) goto L_459fb5;	/* 459d35: jne 0x459fb5 */
	m->eax = M32((DWORD)(m->esp + 0x2b4u));	/* 459d3b: mov eax, dword ptr [esp + 0x2b4] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 459d42: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 459d46: cmp ecx, eax */
	if (m->zf) goto L_459fb5;	/* 459d48: je 0x459fb5 */
	m->ecx = m->edx;	/* 459d4e: mov ecx, edx */
	m->eax = M32((DWORD)(m->ecx + 0x86f0u));	/* 459d50: mov eax, dword ptr [ecx + 0x86f0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 459d56: test eax, eax */
	if (!m->zf) goto L_459fb5;	/* 459d58: jne 0x459fb5 */
	m->eax = m->edx;	/* 459d5e: mov eax, edx */
	m->edx = (DWORD)(m->esp + 0x1dcu);	/* 459d60: lea edx, [esp + 0x1dc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 459d67: push edx */
	m->ecx = (DWORD)(m->esp + 0xc8u);	/* 459d68: lea ecx, [esp + 0xc8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x28cu)));	/* 459d6f: fld dword ptr [eax + 0x28c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x3e8u));	/* 459d75: fadd dword ptr [ebp + 0x3e8] */
	{ DWORD a_ = m->eax, b_ = 0xfffffff8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 459d7b: add eax, -8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 459d7e: push ecx */
	m->esi = (DWORD)(m->ebp + 0x180u);	/* 459d7f: lea esi, [ebp + 0x180] */
	m->edi = (DWORD)(m->ebp + 0x154u);	/* 459d85: lea edi, [ebp + 0x154] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9730u));	/* 459d8b: fmul dword ptr [0x4a9730] */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 459d91: fstp dword ptr [esp + 0x4c] */
	m->edx = M32((DWORD)(m->esp + 0x4cu));	/* 459d95: mov edx, dword ptr [esp + 0x4c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 459d99: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 459d9a: push eax */
	m->eax = (DWORD)(m->esp + 0xa0u);	/* 459d9b: lea eax, [esp + 0xa0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 459da2: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 459da3: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 459da4: push edi */
	m->esp -= 4; M32(m->esp) = 0x459daau; native_call(m, 0x47d9d0u);	/* 459da5: call 0x47d9d0 */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 459daa: add esp, 0x1c */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 459dad: cmp eax, 1 */
	if (!m->zf) goto L_459fb5;	/* 459db0: jne 0x459fb5 */
	m->edx = M32((DWORD)(m->esp + 0xc4u));	/* 459db6: mov edx, dword ptr [esp + 0xc4] */
	m->eax = M32((DWORD)(m->esp + 0xc8u));	/* 459dbd: mov eax, dword ptr [esp + 0xc8] */
	m->ecx = m->esi;	/* 459dc4: mov ecx, esi */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 459dc6: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->esp + 0xccu));	/* 459dc8: mov edx, dword ptr [esp + 0xcc] */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 459dcf: mov dword ptr [ecx + 4], eax */
	m->eax = (DWORD)(m->ebp + 0x384u);	/* 459dd2: lea eax, [ebp + 0x384] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 459dd8: mov dword ptr [ecx + 8], edx */
	m->ecx = m->eax;	/* 459ddb: mov ecx, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 459ddd: fld dword ptr [esi] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 459ddf: fsub dword ptr [edi] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 459de1: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 459de5: fld dword ptr [esi + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 459de8: fsub dword ptr [edi + 4] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 459deb: mov edx, dword ptr [esp + 0x18] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 459def: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 459df3: fld dword ptr [esi + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 459df6: fsub dword ptr [edi + 8] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 459df9: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 459dfb: mov edx, dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 459dff: fstp dword ptr [esp + 0x20] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 459e03: mov dword ptr [ecx + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 459e06: mov edx, dword ptr [esp + 0x20] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 459e0a: mov dword ptr [ecx + 8], edx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 459e0d: fld dword ptr [eax + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 459e10: fld dword ptr [eax + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 459e13: fld dword ptr [eax] */
	{ long double t = ST(0); FPUSH(t); }	/* 459e15: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 459e17: fmul st(1) */
	{ long double t = ST(2); FPUSH(t); }	/* 459e19: fld st(2) */
	ST(0) = ST(0) * ST(3);	/* 459e1b: fmul st(3) */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 459e1d: mov eax, dword ptr [esp + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 459e21: faddp st(1) */
	{ long double t = ST(3); FPUSH(t); }	/* 459e23: fld st(3) */
	ST(0) = ST(0) * ST(4);	/* 459e25: fmul st(4) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 459e27: faddp st(1) */
	{ long double t = ST(0); __asm__("fsqrt" : "+t"(t)); ST(0) = t; }	/* 459e29: fsqrt  */
	ST(3) = ST(0); FPOP();	/* 459e2b: fstp st(3) */
	ST(0) = ST(0); FPOP();	/* 459e2d: fstp st(0) */
	ST(0) = ST(0); FPOP();	/* 459e2f: fstp st(0) */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(m->esp + 0x48u));	/* 459e31: fsubr dword ptr [esp + 0x48] */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 459e35: fstp dword ptr [esp + 0x48] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xc4u)));	/* 459e39: fld dword ptr [esp + 0xc4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->eax + 0xfffffff8u));	/* 459e40: fsub dword ptr [eax - 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xc8u)));	/* 459e43: fld dword ptr [esp + 0xc8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->eax + 0xfffffffcu));	/* 459e4a: fsub dword ptr [eax - 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xccu)));	/* 459e4d: fld dword ptr [esp + 0xcc] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 459e54: fsub dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x94u)));	/* 459e56: fld dword ptr [esp + 0x94] */
	ST(0) = ST(0) * ST(1);	/* 459e5d: fmul st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x98u)));	/* 459e5f: fld dword ptr [esp + 0x98] */
	ST(0) = ST(0) * ST(3);	/* 459e66: fmul st(3) */
	ST(1) = ST(1) - ST(0); FPOP();	/* 459e68: fsubp st(1) */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 459e6a: fstp dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x98u)));	/* 459e6e: fld dword ptr [esp + 0x98] */
	ST(0) = ST(0) * ST(3);	/* 459e75: fmul st(3) */
	{ long double t = ST(1); FPUSH(t); }	/* 459e77: fld st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x90u));	/* 459e79: fmul dword ptr [esp + 0x90] */
	ST(1) = ST(1) - ST(0); FPOP();	/* 459e80: fsubp st(1) */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 459e82: fstp dword ptr [esp + 0x3c] */
	{ long double t = ST(1); FPUSH(t); }	/* 459e86: fld st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x90u));	/* 459e88: fmul dword ptr [esp + 0x90] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x94u)));	/* 459e8f: fld dword ptr [esp + 0x94] */
	ST(0) = ST(0) * ST(4);	/* 459e96: fmul st(4) */
	ST(1) = ST(1) - ST(0); FPOP();	/* 459e98: fsubp st(1) */
	{ long double t = ST(0); FPUSH(t); }	/* 459e9a: fld st(0) */
	ST(0) = ST(0) * ST(3);	/* 459e9c: fmul st(3) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 459e9e: fld dword ptr [esp + 0x3c] */
	ST(0) = ST(0) * ST(3);	/* 459ea2: fmul st(3) */
	ST(1) = ST(1) - ST(0); FPOP();	/* 459ea4: fsubp st(1) */
	MF((DWORD)(m->esp + 0x64u)) = (float)ST(0); FPOP();	/* 459ea6: fstp dword ptr [esp + 0x64] */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 459eaa: fxch st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x38u));	/* 459eac: fmul dword ptr [esp + 0x38] */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 459eb0: fxch st(1) */
	ST(0) = ST(0) * ST(3);	/* 459eb2: fmul st(3) */
	m->eax = M32((DWORD)(m->esp + 0x64u));	/* 459eb4: mov eax, dword ptr [esp + 0x64] */
	M32((DWORD)(m->esp + 0x84u)) = m->eax;	/* 459eb8: mov dword ptr [esp + 0x84], eax */
	ST(1) = ST(1) - ST(0); FPOP();	/* 459ebf: fsubp st(1) */
	MF((DWORD)(m->esp + 0x68u)) = (float)ST(0); FPOP();	/* 459ec1: fstp dword ptr [esp + 0x68] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 459ec5: fld dword ptr [esp + 0x3c] */
	ST(0) = ST(0) * ST(2);	/* 459ec9: fmul st(2) */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 459ecb: fxch st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x38u));	/* 459ecd: fmul dword ptr [esp + 0x38] */
	m->ecx = M32((DWORD)(m->esp + 0x68u));	/* 459ed1: mov ecx, dword ptr [esp + 0x68] */
	M32((DWORD)(m->esp + 0x88u)) = m->ecx;	/* 459ed5: mov dword ptr [esp + 0x88], ecx */
	m->ecx = (DWORD)(m->esp + 0x84u);	/* 459edc: lea ecx, [esp + 0x84] */
	ST(1) = ST(1) - ST(0); FPOP();	/* 459ee3: fsubp st(1) */
	MF((DWORD)(m->esp + 0x6cu)) = (float)ST(0); FPOP();	/* 459ee5: fstp dword ptr [esp + 0x6c] */
	m->edx = M32((DWORD)(m->esp + 0x6cu));	/* 459ee9: mov edx, dword ptr [esp + 0x6c] */
	ST(0) = ST(0); FPOP();	/* 459eed: fstp st(0) */
	M32((DWORD)(m->esp + 0x8cu)) = m->edx;	/* 459eef: mov dword ptr [esp + 0x8c], edx */
	m->esp -= 4; M32(m->esp) = 0x459efbu; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 459ef6: call 0x467760 */
	ST(0) = ST(0); FPOP();	/* 459efb: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x84u)));	/* 459efd: fld dword ptr [esp + 0x84] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x48u));	/* 459f04: fmul dword ptr [esp + 0x48] */
	m->eax = (DWORD)(m->ebp + 0x384u);	/* 459f08: lea eax, [ebp + 0x384] */
	MF((DWORD)(m->esp + 0x84u)) = (float)ST(0); FPOP();	/* 459f0e: fstp dword ptr [esp + 0x84] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x88u)));	/* 459f15: fld dword ptr [esp + 0x88] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x48u));	/* 459f1c: fmul dword ptr [esp + 0x48] */
	MF((DWORD)(m->esp + 0x88u)) = (float)ST(0); FPOP();	/* 459f20: fstp dword ptr [esp + 0x88] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x8cu)));	/* 459f27: fld dword ptr [esp + 0x8c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x48u));	/* 459f2e: fmul dword ptr [esp + 0x48] */
	MF((DWORD)(m->esp + 0x8cu)) = (float)ST(0); FPOP();	/* 459f32: fstp dword ptr [esp + 0x8c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x84u)));	/* 459f39: fld dword ptr [esp + 0x84] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 459f40: fadd dword ptr [esi] */
	MF((DWORD)(m->esi + 0x0u)) = (float)ST(0); FPOP();	/* 459f42: fstp dword ptr [esi] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x88u)));	/* 459f44: fld dword ptr [esp + 0x88] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 459f4b: fadd dword ptr [esi + 4] */
	MF((DWORD)(m->esi + 0x4u)) = (float)ST(0); FPOP();	/* 459f4e: fstp dword ptr [esi + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x8cu)));	/* 459f51: fld dword ptr [esp + 0x8c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 459f58: fadd dword ptr [esi + 8] */
	MF((DWORD)(m->esi + 0x8u)) = (float)ST(0); FPOP();	/* 459f5b: fstp dword ptr [esi + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 459f5e: fld dword ptr [esi] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 459f60: fsub dword ptr [edi] */
	MF((DWORD)(m->esp + 0x58u)) = (float)ST(0); FPOP();	/* 459f62: fstp dword ptr [esp + 0x58] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 459f66: fld dword ptr [esi + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 459f69: fsub dword ptr [edi + 4] */
	MF((DWORD)(m->esp + 0x5cu)) = (float)ST(0); FPOP();	/* 459f6c: fstp dword ptr [esp + 0x5c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 459f70: fld dword ptr [esi + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 459f73: fsub dword ptr [edi + 8] */
	m->ecx = M32((DWORD)(m->esp + 0x5cu));	/* 459f76: mov ecx, dword ptr [esp + 0x5c] */
	m->esi = m->eax;	/* 459f7a: mov esi, eax */
	m->eax = M32((DWORD)(m->esp + 0x58u));	/* 459f7c: mov eax, dword ptr [esp + 0x58] */
	M32((DWORD)(m->esp + 0x94u)) = m->ecx;	/* 459f80: mov dword ptr [esp + 0x94], ecx */
	M32((DWORD)(m->esi + 0x0u)) = m->eax;	/* 459f87: mov dword ptr [esi], eax */
	M32((DWORD)(m->esp + 0x90u)) = m->eax;	/* 459f89: mov dword ptr [esp + 0x90], eax */
	MF((DWORD)(m->esp + 0x60u)) = (float)ST(0); FPOP();	/* 459f90: fstp dword ptr [esp + 0x60] */
	m->edx = M32((DWORD)(m->esp + 0x60u));	/* 459f94: mov edx, dword ptr [esp + 0x60] */
	M32((DWORD)(m->esi + 0x4u)) = m->ecx;	/* 459f98: mov dword ptr [esi + 4], ecx */
	m->ecx = (DWORD)(m->esp + 0x90u);	/* 459f9b: lea ecx, [esp + 0x90] */
	M32((DWORD)(m->esp + 0x98u)) = m->edx;	/* 459fa2: mov dword ptr [esp + 0x98], edx */
	M32((DWORD)(m->esi + 0x8u)) = m->edx;	/* 459fa9: mov dword ptr [esi + 8], edx */
	m->esp -= 4; M32(m->esp) = 0x459fb1u; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 459fac: call 0x467760 */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 459fb1: fstp dword ptr [esp + 0x48] */
L_459fb5:
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 459fb5: mov eax, dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 459fb9: mov edx, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->ebx + 0x202e8c8u));	/* 459fbd: mov ecx, dword ptr [ebx + 0x202e8c8] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 459fc3: inc eax */
	{ DWORD a_ = m->edx, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 459fc4: add edx, 0x8888 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 459fca: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 459fcc: mov dword ptr [esp + 0x24], eax */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 459fd0: mov dword ptr [esp + 0x14], edx */
	if (m->sf != m->of) goto L_459d2d;	/* 459fd4: jl 0x459d2d */
L_459fda:
	m->eax = M32((DWORD)(m->ebp + 0x3e8u));	/* 459fda: mov eax, dword ptr [ebp + 0x3e8] */
	m->ecx = (DWORD)(m->esp + 0x220u);	/* 459fe0: lea ecx, [esp + 0x220] */
	M32((DWORD)(m->esp + 0x44u)) = m->eax;	/* 459fe7: mov dword ptr [esp + 0x44], eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 459feb: push 0 */
	m->edx = (DWORD)(m->esp + 0x1dcu);	/* 459fed: lea edx, [esp + 0x1dc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 459ff4: push ecx */
	m->eax = (DWORD)(m->esp + 0x8cu);	/* 459ff5: lea eax, [esp + 0x8c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 459ffc: push edx */
	m->ecx = (DWORD)(m->esp + 0x1d8u);	/* 459ffd: lea ecx, [esp + 0x1d8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45a004: push eax */
	m->eax = M32((DWORD)(m->esp + 0x54u));	/* 45a005: mov eax, dword ptr [esp + 0x54] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45a009: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45a00a: push 0 */
	m->ecx = (DWORD)(m->ebp + 0x384u);	/* 45a00c: lea ecx, [ebp + 0x384] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45a012: push eax */
	m->edi = (DWORD)(m->ebp + 0x154u);	/* 45a013: lea edi, [ebp + 0x154] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45a019: push ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45a01a: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45a01b: push eax */
	m->ecx = m->ebx;	/* 45a01c: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x45a023u; native_call(m, 0x471400u);	/* 45a01e: call 0x471400 */
	m->esi = M32((DWORD)(m->esp + 0x1ccu));	/* 45a023: mov esi, dword ptr [esp + 0x1cc] */
	m->ecx = (DWORD)(m->ebp + 0x180u);	/* 45a02a: lea ecx, [ebp + 0x180] */
	m->edx = m->ecx;	/* 45a030: mov edx, ecx */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45a032: cmp eax, 1 */
	M32((DWORD)(m->edx + 0x0u)) = m->esi;	/* 45a035: mov dword ptr [edx], esi */
	m->esi = M32((DWORD)(m->esp + 0x1d0u));	/* 45a037: mov esi, dword ptr [esp + 0x1d0] */
	M32((DWORD)(m->edx + 0x4u)) = m->esi;	/* 45a03e: mov dword ptr [edx + 4], esi */
	m->esi = M32((DWORD)(m->esp + 0x1d4u));	/* 45a041: mov esi, dword ptr [esp + 0x1d4] */
	M32((DWORD)(m->edx + 0x8u)) = m->esi;	/* 45a048: mov dword ptr [edx + 8], esi */
	if (!m->zf) goto L_45a07e;	/* 45a04b: jne 0x45a07e */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x84u)));	/* 45a04d: fld dword ptr [esp + 0x84] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x0u));	/* 45a054: fadd dword ptr [ecx] */
	MF((DWORD)(m->ecx + 0x0u)) = (float)ST(0); FPOP();	/* 45a056: fstp dword ptr [ecx] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x88u)));	/* 45a058: fld dword ptr [esp + 0x88] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x184u));	/* 45a05f: fadd dword ptr [ebp + 0x184] */
	MF((DWORD)(m->ebp + 0x184u)) = (float)ST(0); FPOP();	/* 45a065: fstp dword ptr [ebp + 0x184] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x8cu)));	/* 45a06b: fld dword ptr [esp + 0x8c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x188u));	/* 45a072: fadd dword ptr [ebp + 0x188] */
	MF((DWORD)(m->ebp + 0x188u)) = (float)ST(0); FPOP();	/* 45a078: fstp dword ptr [ebp + 0x188] */
L_45a07e:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x0u)));	/* 45a07e: fld dword ptr [ecx] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebx + 0x9ef904u)); FPOP();	/* 45a080: fcomp dword ptr [ebx + 0x9ef904] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a086: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a088: test ah, 1 */
	if (m->zf) goto L_45a097;	/* 45a08b: je 0x45a097 */
	m->eax = M32((DWORD)(m->ebx + 0x9ef904u));	/* 45a08d: mov eax, dword ptr [ebx + 0x9ef904] */
	M32((DWORD)(m->ecx + 0x0u)) = m->eax;	/* 45a093: mov dword ptr [ecx], eax */
	goto L_45a0ae;	/* 45a095: jmp 0x45a0ae */
L_45a097:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x0u)));	/* 45a097: fld dword ptr [ecx] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebx + 0x9ef910u)); FPOP();	/* 45a099: fcomp dword ptr [ebx + 0x9ef910] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a09f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a0a1: test ah, 0x41 */
	if (!m->zf) goto L_45a0ae;	/* 45a0a4: jne 0x45a0ae */
	m->edx = M32((DWORD)(m->ebx + 0x9ef910u));	/* 45a0a6: mov edx, dword ptr [ebx + 0x9ef910] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 45a0ac: mov dword ptr [ecx], edx */
L_45a0ae:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x184u)));	/* 45a0ae: fld dword ptr [ebp + 0x184] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebx + 0x9ef908u)); FPOP();	/* 45a0b4: fcomp dword ptr [ebx + 0x9ef908] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a0ba: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a0bc: test ah, 1 */
	if (m->zf) goto L_45a0cf;	/* 45a0bf: je 0x45a0cf */
	m->eax = M32((DWORD)(m->ebx + 0x9ef908u));	/* 45a0c1: mov eax, dword ptr [ebx + 0x9ef908] */
	M32((DWORD)(m->ebp + 0x184u)) = m->eax;	/* 45a0c7: mov dword ptr [ebp + 0x184], eax */
	goto L_45a0ee;	/* 45a0cd: jmp 0x45a0ee */
L_45a0cf:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x184u)));	/* 45a0cf: fld dword ptr [ebp + 0x184] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebx + 0x9ef914u)); FPOP();	/* 45a0d5: fcomp dword ptr [ebx + 0x9ef914] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a0db: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a0dd: test ah, 0x41 */
	if (!m->zf) goto L_45a0ee;	/* 45a0e0: jne 0x45a0ee */
	m->ecx = M32((DWORD)(m->ebx + 0x9ef914u));	/* 45a0e2: mov ecx, dword ptr [ebx + 0x9ef914] */
	M32((DWORD)(m->ebp + 0x184u)) = m->ecx;	/* 45a0e8: mov dword ptr [ebp + 0x184], ecx */
L_45a0ee:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x188u)));	/* 45a0ee: fld dword ptr [ebp + 0x188] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebx + 0x9ef90cu)); FPOP();	/* 45a0f4: fcomp dword ptr [ebx + 0x9ef90c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a0fa: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a0fc: test ah, 1 */
	if (m->zf) goto L_45a10f;	/* 45a0ff: je 0x45a10f */
	m->edx = M32((DWORD)(m->ebx + 0x9ef90cu));	/* 45a101: mov edx, dword ptr [ebx + 0x9ef90c] */
	M32((DWORD)(m->ebp + 0x188u)) = m->edx;	/* 45a107: mov dword ptr [ebp + 0x188], edx */
	goto L_45a12e;	/* 45a10d: jmp 0x45a12e */
L_45a10f:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x188u)));	/* 45a10f: fld dword ptr [ebp + 0x188] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebx + 0x9ef918u)); FPOP();	/* 45a115: fcomp dword ptr [ebx + 0x9ef918] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a11b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a11d: test ah, 0x41 */
	if (!m->zf) goto L_45a12e;	/* 45a120: jne 0x45a12e */
	m->eax = M32((DWORD)(m->ebx + 0x9ef918u));	/* 45a122: mov eax, dword ptr [ebx + 0x9ef918] */
	M32((DWORD)(m->ebp + 0x188u)) = m->eax;	/* 45a128: mov dword ptr [ebp + 0x188], eax */
L_45a12e:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x464u)));	/* 45a12e: fld dword ptr [ebp + 0x464] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x160u));	/* 45a134: fadd dword ptr [ebp + 0x160] */
	MF((DWORD)(m->ebp + 0x18cu)) = (float)ST(0);	/* 45a13a: fst dword ptr [ebp + 0x18c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a972cu)); FPOP();	/* 45a140: fcomp dword ptr [0x4a972c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a146: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a148: test ah, 0x41 */
	if (!m->zf) goto L_45a157;	/* 45a14b: jne 0x45a157 */
	M32((DWORD)(m->ebp + 0x18cu)) = 0x445e8000u;	/* 45a14d: mov dword ptr [ebp + 0x18c], 0x445e8000 */
L_45a157:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x18cu)));	/* 45a157: fld dword ptr [ebp + 0x18c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9728u)); FPOP();	/* 45a15d: fcomp dword ptr [0x4a9728] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a163: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a165: test ah, 1 */
	if (m->zf) goto L_45a174;	/* 45a168: je 0x45a174 */
	M32((DWORD)(m->ebp + 0x18cu)) = 0xc45e8000u;	/* 45a16a: mov dword ptr [ebp + 0x18c], 0xc45e8000 */
L_45a174:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x468u)));	/* 45a174: fld dword ptr [ebp + 0x468] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x164u));	/* 45a17a: fadd dword ptr [ebp + 0x164] */
	m->esi = M32((DWORD)(m->ebp + 0x474u));	/* 45a180: mov esi, dword ptr [ebp + 0x474] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45a186: test esi, esi */
	MF((DWORD)(m->ebp + 0x190u)) = (float)ST(0); FPOP();	/* 45a188: fstp dword ptr [ebp + 0x190] */
	if (!m->zf) goto L_45a1b0;	/* 45a18e: jne 0x45a1b0 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 45a190: fld dword ptr [0x4a9424] */
	M32((DWORD)(m->esp + 0x14u)) = 0xbf800000u;	/* 45a196: mov dword ptr [esp + 0x14], 0xbf800000 */
	M32((DWORD)(m->esp + 0x48u)) = 0x3f800000u;	/* 45a19e: mov dword ptr [esp + 0x48], 0x3f800000 */
	M32((DWORD)(m->esp + 0x24u)) = 0xbf800000u;	/* 45a1a6: mov dword ptr [esp + 0x24], 0xbf800000 */
	goto L_45a1c8;	/* 45a1ae: jmp 0x45a1c8 */
L_45a1b0:
	m->ecx = M32((DWORD)(m->ebp + 0x58u));	/* 45a1b0: mov ecx, dword ptr [ebp + 0x58] */
	m->edx = M32((DWORD)(m->ebp + 0x5cu));	/* 45a1b3: mov edx, dword ptr [ebp + 0x5c] */
	m->eax = M32((DWORD)(m->ebp + 0x60u));	/* 45a1b6: mov eax, dword ptr [ebp + 0x60] */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 45a1b9: mov dword ptr [esp + 0x14], ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x54u)));	/* 45a1bd: fld dword ptr [ebp + 0x54] */
	M32((DWORD)(m->esp + 0x48u)) = m->edx;	/* 45a1c0: mov dword ptr [esp + 0x48], edx */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 45a1c4: mov dword ptr [esp + 0x24], eax */
L_45a1c8:
	m->edx = M32((DWORD)(m->ebp + 0x44cu));	/* 45a1c8: mov edx, dword ptr [ebp + 0x44c] */
	{ DWORD a_ = m->edx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45a1ce: cmp edx, 1 */
	if (!m->zf) goto L_45a220;	/* 45a1d1: jne 0x45a220 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x194u)));	/* 45a1d3: fld dword ptr [ebp + 0x194] */
	ST(0) = ST(0) - ST(1);	/* 45a1d9: fsub st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 45a1db: fld dword ptr [esp + 0x10] */
	ST(0) = -ST(0);	/* 45a1df: fchs  */
	{ long double t = ST(1); FPUSH(t); }	/* 45a1e1: fld st(1) */
	FCOM(ST(0), ST(1)); FPOP(); FPOP();	/* 45a1e3: fcompp  */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a1e5: fnstsw ax */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->eax >> 8) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a1e7: test dl, ah */
	if (m->zf) goto L_45a201;	/* 45a1e9: je 0x45a201 */
	ST(0) = ST(0); FPOP();	/* 45a1eb: fstp st(0) */
	ST(0) = ST(0); FPOP();	/* 45a1ed: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 45a1ef: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x194u));	/* 45a1f3: fadd dword ptr [ebp + 0x194] */
L_45a1f9:
	MF((DWORD)(m->ebp + 0x194u)) = (float)ST(0); FPOP();	/* 45a1f9: fstp dword ptr [ebp + 0x194] */
	goto L_45a222;	/* 45a1ff: jmp 0x45a222 */
L_45a201:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x10u)); FPOP();	/* 45a201: fcomp dword ptr [esp + 0x10] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a205: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a207: test ah, 0x41 */
	if (!m->zf) goto L_45a1f9;	/* 45a20a: jne 0x45a1f9 */
	ST(0) = ST(0); FPOP();	/* 45a20c: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x194u)));	/* 45a20e: fld dword ptr [ebp + 0x194] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 45a214: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->ebp + 0x194u)) = (float)ST(0); FPOP();	/* 45a218: fstp dword ptr [ebp + 0x194] */
	goto L_45a222;	/* 45a21e: jmp 0x45a222 */
L_45a220:
	ST(0) = ST(0); FPOP();	/* 45a220: fstp st(0) */
L_45a222:
	m->ecx = M32((DWORD)(m->ebp + 0x450u));	/* 45a222: mov ecx, dword ptr [ebp + 0x450] */
	{ DWORD a_ = m->ecx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45a228: cmp ecx, 1 */
	if (!m->zf) goto L_45a282;	/* 45a22b: jne 0x45a282 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x194u)));	/* 45a22d: fld dword ptr [ebp + 0x194] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 45a233: fsub dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 45a237: fld dword ptr [esp + 0x10] */
	ST(0) = -ST(0);	/* 45a23b: fchs  */
	{ long double t = ST(1); FPUSH(t); }	/* 45a23d: fld st(1) */
	FCOM(ST(0), ST(1)); FPOP(); FPOP();	/* 45a23f: fcompp  */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a241: fnstsw ax */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->eax >> 8) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a243: test cl, ah */
	if (m->zf) goto L_45a25b;	/* 45a245: je 0x45a25b */
	ST(0) = ST(0); FPOP();	/* 45a247: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 45a249: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x194u));	/* 45a24d: fadd dword ptr [ebp + 0x194] */
	MF((DWORD)(m->ebp + 0x194u)) = (float)ST(0); FPOP();	/* 45a253: fstp dword ptr [ebp + 0x194] */
	goto L_45a282;	/* 45a259: jmp 0x45a282 */
L_45a25b:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x10u)); FPOP();	/* 45a25b: fcomp dword ptr [esp + 0x10] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a25f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a261: test ah, 0x41 */
	if (!m->zf) goto L_45a278;	/* 45a264: jne 0x45a278 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x194u)));	/* 45a266: fld dword ptr [ebp + 0x194] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 45a26c: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->ebp + 0x194u)) = (float)ST(0); FPOP();	/* 45a270: fstp dword ptr [ebp + 0x194] */
	goto L_45a282;	/* 45a276: jmp 0x45a282 */
L_45a278:
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 45a278: mov eax, dword ptr [esp + 0x14] */
	M32((DWORD)(m->ebp + 0x194u)) = m->eax;	/* 45a27c: mov dword ptr [ebp + 0x194], eax */
L_45a282:
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45a282: test edx, edx */
	if (!m->zf) goto L_45a2dc;	/* 45a284: jne 0x45a2dc */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45a286: test ecx, ecx */
	if (!m->zf) goto L_45a2dc;	/* 45a288: jne 0x45a2dc */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 45a28a: fld dword ptr [esp + 0x10] */
	ST(0) = -ST(0);	/* 45a28e: fchs  */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x194u)); FPOP();	/* 45a290: fcomp dword ptr [ebp + 0x194] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a296: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a298: test ah, 0x41 */
	if (!m->zf) goto L_45a2af;	/* 45a29b: jne 0x45a2af */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 45a29d: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x194u));	/* 45a2a1: fadd dword ptr [ebp + 0x194] */
	MF((DWORD)(m->ebp + 0x194u)) = (float)ST(0); FPOP();	/* 45a2a7: fstp dword ptr [ebp + 0x194] */
	goto L_45a2dc;	/* 45a2ad: jmp 0x45a2dc */
L_45a2af:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x194u)));	/* 45a2af: fld dword ptr [ebp + 0x194] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x10u)); FPOP();	/* 45a2b5: fcomp dword ptr [esp + 0x10] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a2b9: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a2bb: test ah, 0x41 */
	if (!m->zf) goto L_45a2d2;	/* 45a2be: jne 0x45a2d2 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x194u)));	/* 45a2c0: fld dword ptr [ebp + 0x194] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 45a2c6: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->ebp + 0x194u)) = (float)ST(0); FPOP();	/* 45a2ca: fstp dword ptr [ebp + 0x194] */
	goto L_45a2dc;	/* 45a2d0: jmp 0x45a2dc */
L_45a2d2:
	M32((DWORD)(m->ebp + 0x194u)) = 0x0u;	/* 45a2d2: mov dword ptr [ebp + 0x194], 0 */
L_45a2dc:
	m->edx = M32((DWORD)(m->ebp + 0x454u));	/* 45a2dc: mov edx, dword ptr [ebp + 0x454] */
	{ DWORD a_ = m->edx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45a2e2: cmp edx, 1 */
	if (!m->zf) goto L_45a33c;	/* 45a2e5: jne 0x45a33c */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x198u)));	/* 45a2e7: fld dword ptr [ebp + 0x198] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x48u));	/* 45a2ed: fsub dword ptr [esp + 0x48] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 45a2f1: fld dword ptr [esp + 0x10] */
	ST(0) = -ST(0);	/* 45a2f5: fchs  */
	{ long double t = ST(1); FPUSH(t); }	/* 45a2f7: fld st(1) */
	FCOM(ST(0), ST(1)); FPOP(); FPOP();	/* 45a2f9: fcompp  */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a2fb: fnstsw ax */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->eax >> 8) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a2fd: test dl, ah */
	if (m->zf) goto L_45a315;	/* 45a2ff: je 0x45a315 */
	ST(0) = ST(0); FPOP();	/* 45a301: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 45a303: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x198u));	/* 45a307: fadd dword ptr [ebp + 0x198] */
	MF((DWORD)(m->ebp + 0x198u)) = (float)ST(0); FPOP();	/* 45a30d: fstp dword ptr [ebp + 0x198] */
	goto L_45a33c;	/* 45a313: jmp 0x45a33c */
L_45a315:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x10u)); FPOP();	/* 45a315: fcomp dword ptr [esp + 0x10] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a319: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a31b: test ah, 0x41 */
	if (!m->zf) goto L_45a332;	/* 45a31e: jne 0x45a332 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x198u)));	/* 45a320: fld dword ptr [ebp + 0x198] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 45a326: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->ebp + 0x198u)) = (float)ST(0); FPOP();	/* 45a32a: fstp dword ptr [ebp + 0x198] */
	goto L_45a33c;	/* 45a330: jmp 0x45a33c */
L_45a332:
	m->ecx = M32((DWORD)(m->esp + 0x48u));	/* 45a332: mov ecx, dword ptr [esp + 0x48] */
	M32((DWORD)(m->ebp + 0x198u)) = m->ecx;	/* 45a336: mov dword ptr [ebp + 0x198], ecx */
L_45a33c:
	m->ecx = M32((DWORD)(m->ebp + 0x458u));	/* 45a33c: mov ecx, dword ptr [ebp + 0x458] */
	{ DWORD a_ = m->ecx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45a342: cmp ecx, 1 */
	if (!m->zf) goto L_45a39c;	/* 45a345: jne 0x45a39c */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x198u)));	/* 45a347: fld dword ptr [ebp + 0x198] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 45a34d: fsub dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 45a351: fld dword ptr [esp + 0x10] */
	ST(0) = -ST(0);	/* 45a355: fchs  */
	{ long double t = ST(1); FPUSH(t); }	/* 45a357: fld st(1) */
	FCOM(ST(0), ST(1)); FPOP(); FPOP();	/* 45a359: fcompp  */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a35b: fnstsw ax */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->eax >> 8) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a35d: test cl, ah */
	if (m->zf) goto L_45a375;	/* 45a35f: je 0x45a375 */
	ST(0) = ST(0); FPOP();	/* 45a361: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 45a363: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x198u));	/* 45a367: fadd dword ptr [ebp + 0x198] */
	MF((DWORD)(m->ebp + 0x198u)) = (float)ST(0); FPOP();	/* 45a36d: fstp dword ptr [ebp + 0x198] */
	goto L_45a39c;	/* 45a373: jmp 0x45a39c */
L_45a375:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x10u)); FPOP();	/* 45a375: fcomp dword ptr [esp + 0x10] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a379: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a37b: test ah, 0x41 */
	if (!m->zf) goto L_45a392;	/* 45a37e: jne 0x45a392 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x198u)));	/* 45a380: fld dword ptr [ebp + 0x198] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 45a386: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->ebp + 0x198u)) = (float)ST(0); FPOP();	/* 45a38a: fstp dword ptr [ebp + 0x198] */
	goto L_45a39c;	/* 45a390: jmp 0x45a39c */
L_45a392:
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 45a392: mov eax, dword ptr [esp + 0x24] */
	M32((DWORD)(m->ebp + 0x198u)) = m->eax;	/* 45a396: mov dword ptr [ebp + 0x198], eax */
L_45a39c:
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45a39c: test edx, edx */
	if (!m->zf) goto L_45a3f6;	/* 45a39e: jne 0x45a3f6 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45a3a0: test ecx, ecx */
	if (!m->zf) goto L_45a3f6;	/* 45a3a2: jne 0x45a3f6 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 45a3a4: fld dword ptr [esp + 0x10] */
	ST(0) = -ST(0);	/* 45a3a8: fchs  */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x198u)); FPOP();	/* 45a3aa: fcomp dword ptr [ebp + 0x198] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a3b0: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a3b2: test ah, 0x41 */
	if (!m->zf) goto L_45a3c9;	/* 45a3b5: jne 0x45a3c9 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 45a3b7: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x198u));	/* 45a3bb: fadd dword ptr [ebp + 0x198] */
	MF((DWORD)(m->ebp + 0x198u)) = (float)ST(0); FPOP();	/* 45a3c1: fstp dword ptr [ebp + 0x198] */
	goto L_45a3f6;	/* 45a3c7: jmp 0x45a3f6 */
L_45a3c9:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x198u)));	/* 45a3c9: fld dword ptr [ebp + 0x198] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x10u)); FPOP();	/* 45a3cf: fcomp dword ptr [esp + 0x10] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a3d3: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a3d5: test ah, 0x41 */
	if (!m->zf) goto L_45a3ec;	/* 45a3d8: jne 0x45a3ec */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x198u)));	/* 45a3da: fld dword ptr [ebp + 0x198] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 45a3e0: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->ebp + 0x198u)) = (float)ST(0); FPOP();	/* 45a3e4: fstp dword ptr [ebp + 0x198] */
	goto L_45a3f6;	/* 45a3ea: jmp 0x45a3f6 */
L_45a3ec:
	M32((DWORD)(m->ebp + 0x198u)) = 0x0u;	/* 45a3ec: mov dword ptr [ebp + 0x198], 0 */
L_45a3f6:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x470u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45a3f6: cmp dword ptr [ebp + 0x470], 1 */
	if (!m->zf) goto L_45a428;	/* 45a3fd: jne 0x45a428 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 45a3ff: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x19cu));	/* 45a403: fadd dword ptr [ebp + 0x19c] */
	MF((DWORD)(m->ebp + 0x19cu)) = (float)ST(0);	/* 45a409: fst dword ptr [ebp + 0x19c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 45a40f: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a415: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a417: test ah, 0x41 */
	if (!m->zf) goto L_45a44f;	/* 45a41a: jne 0x45a44f */
	M32((DWORD)(m->ebp + 0x19cu)) = 0x3f800000u;	/* 45a41c: mov dword ptr [ebp + 0x19c], 0x3f800000 */
	goto L_45a44f;	/* 45a426: jmp 0x45a44f */
L_45a428:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x19cu)));	/* 45a428: fld dword ptr [ebp + 0x19c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 45a42e: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->ebp + 0x19cu)) = (float)ST(0);	/* 45a432: fst dword ptr [ebp + 0x19c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45a438: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a43e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a440: test ah, 1 */
	if (m->zf) goto L_45a44f;	/* 45a443: je 0x45a44f */
	M32((DWORD)(m->ebp + 0x19cu)) = 0x0u;	/* 45a445: mov dword ptr [ebp + 0x19c], 0 */
L_45a44f:
	{ DWORD a_ = m->esi, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45a44f: cmp esi, 1 */
	if (!m->zf) goto L_45a47d;	/* 45a452: jne 0x45a47d */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 45a454: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x1a4u));	/* 45a458: fadd dword ptr [ebp + 0x1a4] */
	MF((DWORD)(m->ebp + 0x1a4u)) = (float)ST(0);	/* 45a45e: fst dword ptr [ebp + 0x1a4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 45a464: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a46a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a46c: test ah, 0x41 */
	if (!m->zf) goto L_45a4a4;	/* 45a46f: jne 0x45a4a4 */
	M32((DWORD)(m->ebp + 0x1a4u)) = 0x3f800000u;	/* 45a471: mov dword ptr [ebp + 0x1a4], 0x3f800000 */
	goto L_45a4a4;	/* 45a47b: jmp 0x45a4a4 */
L_45a47d:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x1a4u)));	/* 45a47d: fld dword ptr [ebp + 0x1a4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 45a483: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->ebp + 0x1a4u)) = (float)ST(0);	/* 45a487: fst dword ptr [ebp + 0x1a4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45a48d: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a493: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a495: test ah, 1 */
	if (m->zf) goto L_45a4a4;	/* 45a498: je 0x45a4a4 */
	M32((DWORD)(m->ebp + 0x1a4u)) = 0x0u;	/* 45a49a: mov dword ptr [ebp + 0x1a4], 0 */
L_45a4a4:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x194u)));	/* 45a4a4: fld dword ptr [ebp + 0x194] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45a4aa: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a4b0: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a4b2: test ah, 1 */
	if (m->zf) goto L_45a4f7;	/* 45a4b5: je 0x45a4f7 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x194u)));	/* 45a4b7: fld dword ptr [ebp + 0x194] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9474u)); FPOP();	/* 45a4bd: fcomp dword ptr [0x4a9474] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a4c3: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a4c5: test ah, 0x41 */
	if (!m->zf) goto L_45a4d2;	/* 45a4c8: jne 0x45a4d2 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x194u)));	/* 45a4ca: fld dword ptr [ebp + 0x194] */
	goto L_45a4d8;	/* 45a4d0: jmp 0x45a4d8 */
L_45a4d2:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9474u)));	/* 45a4d2: fld dword ptr [0x4a9474] */
L_45a4d8:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9734u)));	/* 45a4d8: fld dword ptr [0x4a9734] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x18cu));	/* 45a4de: fsub dword ptr [ebp + 0x18c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9724u));	/* 45a4e4: fmul dword ptr [0x4a9724] */
	ST(0) = ST(0) * ST(1);	/* 45a4ea: fmul st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9720u));	/* 45a4ec: fmul dword ptr [0x4a9720] */
	goto L_45a598;	/* 45a4f2: jmp 0x45a598 */
L_45a4f7:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x18cu)));	/* 45a4f7: fld dword ptr [ebp + 0x18c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45a4fd: fcomp dword ptr [0x4a93e8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x194u)));	/* 45a503: fld dword ptr [ebp + 0x194] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a509: fnstsw ax */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 45a50b: fcomp dword ptr [0x4a9424] */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a511: test ah, 1 */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a514: fnstsw ax */
	if (m->zf) goto L_45a547;	/* 45a516: je 0x45a547 */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a518: test ah, 1 */
	if (m->zf) goto L_45a525;	/* 45a51b: je 0x45a525 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x194u)));	/* 45a51d: fld dword ptr [ebp + 0x194] */
	goto L_45a52b;	/* 45a523: jmp 0x45a52b */
L_45a525:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 45a525: fld dword ptr [0x4a9424] */
L_45a52b:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x18cu)));	/* 45a52b: fld dword ptr [ebp + 0x18c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9734u));	/* 45a531: fadd dword ptr [0x4a9734] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a971cu));	/* 45a537: fmul dword ptr [0x4a971c] */
	ST(0) = ST(0) * ST(1);	/* 45a53d: fmul st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9718u));	/* 45a53f: fmul dword ptr [0x4a9718] */
	goto L_45a598;	/* 45a545: jmp 0x45a598 */
L_45a547:
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a547: test ah, 1 */
	if (m->zf) goto L_45a554;	/* 45a54a: je 0x45a554 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x194u)));	/* 45a54c: fld dword ptr [ebp + 0x194] */
	goto L_45a55a;	/* 45a552: jmp 0x45a55a */
L_45a554:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 45a554: fld dword ptr [0x4a9424] */
L_45a55a:
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9718u));	/* 45a55a: fmul dword ptr [0x4a9718] */
	MF((DWORD)(m->ebp + 0x1a0u)) = (float)ST(0);	/* 45a560: fst dword ptr [ebp + 0x1a0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x194u)));	/* 45a566: fld dword ptr [ebp + 0x194] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 45a56c: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a572: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a574: test ah, 0x41 */
	if (!m->zf) goto L_45a59e;	/* 45a577: jne 0x45a59e */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x194u)));	/* 45a579: fld dword ptr [ebp + 0x194] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 45a57f: fsub dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x18cu));	/* 45a585: fmul dword ptr [ebp + 0x18c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x54u)));	/* 45a58b: fld dword ptr [ebp + 0x54] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 45a58e: fsub dword ptr [0x4a9424] */
	ST(1) = ST(1) / ST(0); FPOP();	/* 45a594: fdivp st(1) */
	ST(0) = ST(0) + ST(1);	/* 45a596: fadd st(1) */
L_45a598:
	MF((DWORD)(m->ebp + 0x1a0u)) = (float)ST(0); FPOP();	/* 45a598: fstp dword ptr [ebp + 0x1a0] */
L_45a59e:
	ST(0) = ST(0); FPOP();	/* 45a59e: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x1a4u)));	/* 45a5a0: fld dword ptr [ebp + 0x1a4] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 45a5a6: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 45a5ac: fmul dword ptr [0x4a942c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 45a5b2: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x170u));	/* 45a5b8: fsub dword ptr [ebp + 0x170] */
	ST(1) = ST(1) * ST(0); FPOP();	/* 45a5be: fmulp st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x1a0u));	/* 45a5c0: fmul dword ptr [ebp + 0x1a0] */
	MF((DWORD)(m->ebp + 0x1a0u)) = (float)ST(0); FPOP();	/* 45a5c6: fstp dword ptr [ebp + 0x1a0] */
	goto L_45a741;	/* 45a5cc: jmp 0x45a741 */
L_45a5d1:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2b8u)));	/* 45a5d1: fld dword ptr [esp + 0x2b8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9714u));	/* 45a5d8: fmul dword ptr [0x4a9714] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0);	/* 45a5de: fst dword ptr [esp + 0x10] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 45a5e2: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a5e8: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a5ea: test ah, 0x41 */
	if (!m->zf) goto L_45a5f7;	/* 45a5ed: jne 0x45a5f7 */
	M32((DWORD)(m->esp + 0x10u)) = 0x3f800000u;	/* 45a5ef: mov dword ptr [esp + 0x10], 0x3f800000 */
L_45a5f7:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x1acu)));	/* 45a5f7: fld dword ptr [ebp + 0x1ac] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x154u));	/* 45a5fd: fsub dword ptr [ebp + 0x154] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x1b0u)));	/* 45a603: fld dword ptr [ebp + 0x1b0] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x158u));	/* 45a609: fsub dword ptr [ebp + 0x158] */
	m->edi = (DWORD)(m->ebp + 0x154u);	/* 45a60f: lea edi, [ebp + 0x154] */
	m->eax = (DWORD)(m->ebp + 0x180u);	/* 45a615: lea eax, [ebp + 0x180] */
	MF((DWORD)(m->esp + 0x5cu)) = (float)ST(0); FPOP();	/* 45a61b: fstp dword ptr [esp + 0x5c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x1b4u)));	/* 45a61f: fld dword ptr [ebp + 0x1b4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 45a625: fsub dword ptr [edi + 8] */
	MF((DWORD)(m->esp + 0x60u)) = (float)ST(0); FPOP();	/* 45a628: fstp dword ptr [esp + 0x60] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 45a62c: fmul dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 45a630: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x5cu));	/* 45a634: fmul dword ptr [esp + 0x5c] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 45a638: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 45a63c: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x60u));	/* 45a640: fmul dword ptr [esp + 0x60] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 45a644: fstp dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 45a648: fadd dword ptr [edi] */
	MF((DWORD)(m->esp + 0x58u)) = (float)ST(0); FPOP();	/* 45a64a: fstp dword ptr [esp + 0x58] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 45a64e: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 45a652: fadd dword ptr [edi + 4] */
	m->ecx = M32((DWORD)(m->esp + 0x58u));	/* 45a655: mov ecx, dword ptr [esp + 0x58] */
	MF((DWORD)(m->esp + 0x5cu)) = (float)ST(0); FPOP();	/* 45a659: fstp dword ptr [esp + 0x5c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 45a65d: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 45a661: fadd dword ptr [edi + 8] */
	m->edx = M32((DWORD)(m->esp + 0x5cu));	/* 45a664: mov edx, dword ptr [esp + 0x5c] */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 45a668: mov dword ptr [eax], ecx */
	MF((DWORD)(m->esp + 0x60u)) = (float)ST(0); FPOP();	/* 45a66a: fstp dword ptr [esp + 0x60] */
	m->ecx = M32((DWORD)(m->esp + 0x60u));	/* 45a66e: mov ecx, dword ptr [esp + 0x60] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 45a672: mov dword ptr [eax + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 45a675: mov edx, dword ptr [esp + 0x10] */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 45a679: mov dword ptr [eax + 8], ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45a67c: push edx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x1b8u)));	/* 45a67d: fld dword ptr [ebp + 0x1b8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x160u));	/* 45a683: fsub dword ptr [ebp + 0x160] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 45a689: fmul dword ptr [esp + 0x14] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x160u));	/* 45a68d: fadd dword ptr [ebp + 0x160] */
	MF((DWORD)(m->ebp + 0x18cu)) = (float)ST(0); FPOP();	/* 45a693: fstp dword ptr [ebp + 0x18c] */
	m->eax = M32((DWORD)(m->ebp + 0x1bcu));	/* 45a699: mov eax, dword ptr [ebp + 0x1bc] */
	m->ecx = M32((DWORD)(m->ebp + 0x190u));	/* 45a69f: mov ecx, dword ptr [ebp + 0x190] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45a6a5: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45a6a6: push ecx */
	m->esp -= 4; M32(m->esp) = 0x45a6acu; { long double r_ = native_call_fp(m, 0x46c1c0u); FPUSH(r_); }	/* 45a6a7: call 0x46c1c0 */
	MF((DWORD)(m->ebp + 0x190u)) = (float)ST(0); FPOP();	/* 45a6ac: fstp dword ptr [ebp + 0x190] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x1c0u)));	/* 45a6b2: fld dword ptr [ebp + 0x1c0] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x168u));	/* 45a6b8: fsub dword ptr [ebp + 0x168] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45a6be: add esp, 0xc */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 45a6c1: fmul dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x168u));	/* 45a6c5: fadd dword ptr [ebp + 0x168] */
	MF((DWORD)(m->ebp + 0x194u)) = (float)ST(0); FPOP();	/* 45a6cb: fstp dword ptr [ebp + 0x194] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x1c4u)));	/* 45a6d1: fld dword ptr [ebp + 0x1c4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x16cu));	/* 45a6d7: fsub dword ptr [ebp + 0x16c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 45a6dd: fmul dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x16cu));	/* 45a6e1: fadd dword ptr [ebp + 0x16c] */
	MF((DWORD)(m->ebp + 0x198u)) = (float)ST(0); FPOP();	/* 45a6e7: fstp dword ptr [ebp + 0x198] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x1c8u)));	/* 45a6ed: fld dword ptr [ebp + 0x1c8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x170u));	/* 45a6f3: fsub dword ptr [ebp + 0x170] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 45a6f9: fmul dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x170u));	/* 45a6fd: fadd dword ptr [ebp + 0x170] */
	MF((DWORD)(m->ebp + 0x19cu)) = (float)ST(0); FPOP();	/* 45a703: fstp dword ptr [ebp + 0x19c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x1ccu)));	/* 45a709: fld dword ptr [ebp + 0x1cc] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x174u));	/* 45a70f: fsub dword ptr [ebp + 0x174] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 45a715: fmul dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x174u));	/* 45a719: fadd dword ptr [ebp + 0x174] */
	MF((DWORD)(m->ebp + 0x1a0u)) = (float)ST(0); FPOP();	/* 45a71f: fstp dword ptr [ebp + 0x1a0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x1d0u)));	/* 45a725: fld dword ptr [ebp + 0x1d0] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x178u));	/* 45a72b: fsub dword ptr [ebp + 0x178] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 45a731: fmul dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x178u));	/* 45a735: fadd dword ptr [ebp + 0x178] */
	MF((DWORD)(m->ebp + 0x1a4u)) = (float)ST(0); FPOP();	/* 45a73b: fstp dword ptr [ebp + 0x1a4] */
L_45a741:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x17cu)));	/* 45a741: fld dword ptr [ebp + 0x17c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45a747: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a74d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a74f: test ah, 0x41 */
	if (!m->zf) goto L_45a78c;	/* 45a752: jne 0x45a78c */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 45a754: mov eax, dword ptr [esp + 0x34] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45a758: test eax, eax */
	if (m->zf) goto L_45a78c;	/* 45a75a: je 0x45a78c */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2b8u)));	/* 45a75c: fld dword ptr [esp + 0x2b8] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->eax + 0x2e08u));	/* 45a763: fdiv dword ptr [eax + 0x2e08] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x1a8u));	/* 45a769: fadd dword ptr [ebp + 0x1a8] */
	MF((DWORD)(m->ebp + 0x1a8u)) = (float)ST(0);	/* 45a76f: fst dword ptr [ebp + 0x1a8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 45a775: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a77b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a77d: test ah, 1 */
	if (!m->zf) goto L_45a78c;	/* 45a780: jne 0x45a78c */
	M32((DWORD)(m->ebp + 0x1a8u)) = 0x0u;	/* 45a782: mov dword ptr [ebp + 0x1a8], 0 */
L_45a78c:
	m->eax = M32((DWORD)(m->ebp + 0x884cu));	/* 45a78c: mov eax, dword ptr [ebp + 0x884c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45a792: test eax, eax */
	if (!m->zf) goto L_45cdb1;	/* 45a794: jne 0x45cdb1 */
	m->eax = M32((DWORD)(m->ebp + 0x48cu));	/* 45a79a: mov eax, dword ptr [ebp + 0x48c] */
	{ DWORD a_ = m->eax, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45a7a0: sub eax, 0 */
	if (m->zf) goto L_45a82f;	/* 45a7a3: je 0x45a82f */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 45a7a9: dec eax */
	if (!m->zf) goto L_45a94f;	/* 45a7aa: jne 0x45a94f */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x490u)));	/* 45a7b0: fld dword ptr [ebp + 0x490] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45a7b6: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a7bc: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a7be: test ah, 0x41 */
	if (!m->zf) goto L_45a805;	/* 45a7c1: jne 0x45a805 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x490u)), b_ = 0x3f800000u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45a7c3: cmp dword ptr [ebp + 0x490], 0x3f800000 */
	if (!m->zf) goto L_45a7ec;	/* 45a7cd: jne 0x45a7ec */
	m->edx = M32((DWORD)(m->esp + 0x2b4u));	/* 45a7cf: mov edx, dword ptr [esp + 0x2b4] */
	m->eax = M32((DWORD)(m->ebx + 0x202e8d4u));	/* 45a7d6: mov eax, dword ptr [ebx + 0x202e8d4] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45a7dc: cmp edx, eax */
	if (!m->zf) goto L_45a7ec;	/* 45a7de: jne 0x45a7ec */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 45a7e0: push 0x64 */
	{ DWORD v_ = 0x14u; m->esp -= 4; M32(m->esp) = v_; }	/* 45a7e2: push 0x14 */
	m->esp -= 4; M32(m->esp) = 0x45a7e9u; native_call(m, 0x456e50u);	/* 45a7e4: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45a7e9: add esp, 8 */
L_45a7ec:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2b8u)));	/* 45a7ec: fld dword ptr [esp + 0x2b8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9534u));	/* 45a7f3: fmul dword ptr [0x4a9534] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(m->ebp + 0x490u));	/* 45a7f9: fsubr dword ptr [ebp + 0x490] */
	MF((DWORD)(m->ebp + 0x490u)) = (float)ST(0); FPOP();	/* 45a7ff: fstp dword ptr [ebp + 0x490] */
L_45a805:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x490u)));	/* 45a805: fld dword ptr [ebp + 0x490] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45a80b: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a811: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a813: test ah, 0x41 */
	if (m->zf) goto L_45a94f;	/* 45a816: je 0x45a94f */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45a81c: xor eax, eax */
	M32((DWORD)(m->ebp + 0x48cu)) = m->eax;	/* 45a81e: mov dword ptr [ebp + 0x48c], eax */
	M32((DWORD)(m->ebp + 0x490u)) = m->eax;	/* 45a824: mov dword ptr [ebp + 0x490], eax */
	goto L_45a94f;	/* 45a82a: jmp 0x45a94f */
L_45a82f:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x490u)));	/* 45a82f: fld dword ptr [ebp + 0x490] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45a835: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a83b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a83d: test ah, 0x41 */
	if (m->zf) goto L_45a8d4;	/* 45a840: je 0x45a8d4 */
	m->eax = M32((DWORD)(m->ebp + 0x498u));	/* 45a846: mov eax, dword ptr [ebp + 0x498] */
	m->esi = M32((DWORD)(m->esp + 0x2b4u));	/* 45a84c: mov esi, dword ptr [esp + 0x2b4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45a853: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45a854: push esi */
	m->ecx = m->ebx;	/* 45a855: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x45a85cu; native_call(m, 0x45e810u);	/* 45a857: call 0x45e810 */
	m->ecx = M32((DWORD)(m->ebp + 0x49cu));	/* 45a85c: mov ecx, dword ptr [ebp + 0x49c] */
	m->edx = M32((DWORD)(m->ebp + 0x498u));	/* 45a862: mov edx, dword ptr [ebp + 0x498] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45a868: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45a869: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45a86a: push esi */
	m->ecx = m->ebx;	/* 45a86b: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x45a872u; native_call(m, 0x45e600u);	/* 45a86d: call 0x45e600 */
	m->edx = M32((DWORD)(m->ebp + 0x140u));	/* 45a872: mov edx, dword ptr [ebp + 0x140] */
	m->eax = M32((DWORD)(m->esp + 0x50u));	/* 45a878: mov eax, dword ptr [esp + 0x50] */
	m->ecx = M32((DWORD)(m->eax + m->edx*4 + 0x320u));	/* 45a87c: mov ecx, dword ptr [eax + edx*4 + 0x320] */
	m->eax = m->ecx;	/* 45a883: mov eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45a885: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45a888: sub eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45a88a: shl eax, 2 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45a88d: sub eax, ecx */
	{ DWORD a_ = m->edx, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45a88f: cmp edx, 4 */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45a892: lea eax, [eax + eax*4] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45a895: lea ecx, [eax + eax*4] */
	m->eax = (DWORD)(m->ebx + m->ecx*8 + 0x14d1ab4u);	/* 45a898: lea eax, [ebx + ecx*8 + 0x14d1ab4] */
	M32((DWORD)(m->esp + 0x34u)) = m->eax;	/* 45a89f: mov dword ptr [esp + 0x34], eax */
	if (!m->zf) goto L_45a8ad;	/* 45a8a3: jne 0x45a8ad */
	m->edx = (DWORD)(m->ebp + 0x587cu);	/* 45a8a5: lea edx, [ebp + 0x587c] */
	goto L_45a8c4;	/* 45a8ab: jmp 0x45a8c4 */
L_45a8ad:
	{ DWORD a_ = m->edx, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45a8ad: cmp edx, 5 */
	if (!m->zf) goto L_45a8be;	/* 45a8b0: jne 0x45a8be */
	m->ecx = (DWORD)(m->ebp + 0x701cu);	/* 45a8b2: lea ecx, [ebp + 0x701c] */
	M32((DWORD)(m->esp + 0x54u)) = m->ecx;	/* 45a8b8: mov dword ptr [esp + 0x54], ecx */
	goto L_45a8c8;	/* 45a8bc: jmp 0x45a8c8 */
L_45a8be:
	m->edx = (DWORD)(m->ebp + 0x40dcu);	/* 45a8be: lea edx, [ebp + 0x40dc] */
L_45a8c4:
	M32((DWORD)(m->esp + 0x54u)) = m->edx;	/* 45a8c4: mov dword ptr [esp + 0x54], edx */
L_45a8c8:
	m->eax = M32((DWORD)(m->eax + 0x2dc0u));	/* 45a8c8: mov eax, dword ptr [eax + 0x2dc0] */
	M32((DWORD)(m->ebp + 0x4ccu)) = m->eax;	/* 45a8ce: mov dword ptr [ebp + 0x4cc], eax */
L_45a8d4:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x490u)));	/* 45a8d4: fld dword ptr [ebp + 0x490] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 45a8da: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a8e0: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a8e2: test ah, 1 */
	if (m->zf) goto L_45a94f;	/* 45a8e5: je 0x45a94f */
	m->ecx = M32((DWORD)(m->ebp + 0x140u));	/* 45a8e7: mov ecx, dword ptr [ebp + 0x140] */
	m->edx = M32((DWORD)(m->esp + 0x50u));	/* 45a8ed: mov edx, dword ptr [esp + 0x50] */
	m->eax = M32((DWORD)(m->edx + m->ecx*4 + 0x320u));	/* 45a8f1: mov eax, dword ptr [edx + ecx*4 + 0x320] */
	{ DWORD a_ = m->eax, b_ = 0xbu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45a8f8: cmp eax, 0xb */
	if (!m->zf) goto L_45a90c;	/* 45a8fb: jne 0x45a90c */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2b8u)));	/* 45a8fd: fld dword ptr [esp + 0x2b8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9710u));	/* 45a904: fmul dword ptr [0x4a9710] */
	goto L_45a926;	/* 45a90a: jmp 0x45a926 */
L_45a90c:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2b8u)));	/* 45a90c: fld dword ptr [esp + 0x2b8] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45a913: cmp eax, 3 */
	if (!m->zf) goto L_45a920;	/* 45a916: jne 0x45a920 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a970cu));	/* 45a918: fmul dword ptr [0x4a970c] */
	goto L_45a926;	/* 45a91e: jmp 0x45a926 */
L_45a920:
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9534u));	/* 45a920: fmul dword ptr [0x4a9534] */
L_45a926:
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x490u));	/* 45a926: fadd dword ptr [ebp + 0x490] */
	MF((DWORD)(m->ebp + 0x490u)) = (float)ST(0); FPOP();	/* 45a92c: fstp dword ptr [ebp + 0x490] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x490u)));	/* 45a932: fld dword ptr [ebp + 0x490] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 45a938: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a93e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a940: test ah, 1 */
	if (!m->zf) goto L_45a94f;	/* 45a943: jne 0x45a94f */
	M32((DWORD)(m->ebp + 0x490u)) = 0x3f800000u;	/* 45a945: mov dword ptr [ebp + 0x490], 0x3f800000 */
L_45a94f:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x16cu)));	/* 45a94f: fld dword ptr [ebp + 0x16c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94a0u));	/* 45a955: fmul dword ptr [0x4a94a0] */
	m->edx = 0xc3e10000u;	/* 45a95b: mov edx, 0xc3e10000 */
	m->ecx = 0x43e10000u;	/* 45a960: mov ecx, 0x43e10000 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9454u));	/* 45a965: fcom dword ptr [0x4a9454] */
	MF((DWORD)(m->ebp + 0x390u)) = (float)ST(0);	/* 45a96b: fst dword ptr [ebp + 0x390] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a971: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a973: test ah, 1 */
	if (m->zf) goto L_45a982;	/* 45a976: je 0x45a982 */
	ST(0) = ST(0); FPOP();	/* 45a978: fstp st(0) */
	M32((DWORD)(m->ebp + 0x390u)) = m->edx;	/* 45a97a: mov dword ptr [ebp + 0x390], edx */
	goto L_45a995;	/* 45a980: jmp 0x45a995 */
L_45a982:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9718u)); FPOP();	/* 45a982: fcomp dword ptr [0x4a9718] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a988: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a98a: test ah, 0x41 */
	if (!m->zf) goto L_45a995;	/* 45a98d: jne 0x45a995 */
	M32((DWORD)(m->ebp + 0x390u)) = m->ecx;	/* 45a98f: mov dword ptr [ebp + 0x390], ecx */
L_45a995:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 45a995: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x170u));	/* 45a99b: fsub dword ptr [ebp + 0x170] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x160u)));	/* 45a9a1: fld dword ptr [ebp + 0x160] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9734u));	/* 45a9a7: fadd dword ptr [0x4a9734] */
	ST(1) = ST(1) * ST(0); FPOP();	/* 45a9ad: fmulp st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x40u));	/* 45a9af: fmul dword ptr [ebp + 0x40] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9724u));	/* 45a9b2: fmul dword ptr [0x4a9724] */
	MF((DWORD)(m->ebp + 0x394u)) = (float)ST(0); FPOP();	/* 45a9b8: fstp dword ptr [ebp + 0x394] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x16cu)));	/* 45a9be: fld dword ptr [ebp + 0x16c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93f0u));	/* 45a9c4: fmul dword ptr [0x4a93f0] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9454u));	/* 45a9ca: fcom dword ptr [0x4a9454] */
	MF((DWORD)(m->ebp + 0x398u)) = (float)ST(0);	/* 45a9d0: fst dword ptr [ebp + 0x398] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a9d6: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a9d8: test ah, 1 */
	if (m->zf) goto L_45a9e7;	/* 45a9db: je 0x45a9e7 */
	ST(0) = ST(0); FPOP();	/* 45a9dd: fstp st(0) */
	M32((DWORD)(m->ebp + 0x398u)) = m->edx;	/* 45a9df: mov dword ptr [ebp + 0x398], edx */
	goto L_45a9fa;	/* 45a9e5: jmp 0x45a9fa */
L_45a9e7:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9718u)); FPOP();	/* 45a9e7: fcomp dword ptr [0x4a9718] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45a9ed: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45a9ef: test ah, 0x41 */
	if (!m->zf) goto L_45a9fa;	/* 45a9f2: jne 0x45a9fa */
	M32((DWORD)(m->ebp + 0x398u)) = m->ecx;	/* 45a9f4: mov dword ptr [ebp + 0x398], ecx */
L_45a9fa:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x160u)));	/* 45a9fa: fld dword ptr [ebp + 0x160] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x174u));	/* 45aa00: fsub dword ptr [ebp + 0x174] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9734u));	/* 45aa06: fadd dword ptr [0x4a9734] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9724u));	/* 45aa0c: fmul dword ptr [0x4a9724] */
	MF((DWORD)(m->ebp + 0x39cu)) = (float)ST(0); FPOP();	/* 45aa12: fstp dword ptr [ebp + 0x39c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x168u)));	/* 45aa18: fld dword ptr [ebp + 0x168] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9474u)); FPOP();	/* 45aa1e: fcomp dword ptr [0x4a9474] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45aa24: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45aa26: test ah, 1 */
	if (m->zf) goto L_45aa33;	/* 45aa29: je 0x45aa33 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9474u)));	/* 45aa2b: fld dword ptr [0x4a9474] */
	goto L_45aa54;	/* 45aa31: jmp 0x45aa54 */
L_45aa33:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x168u)));	/* 45aa33: fld dword ptr [ebp + 0x168] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 45aa39: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45aa3f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45aa41: test ah, 0x41 */
	if (!m->zf) goto L_45aa4e;	/* 45aa44: jne 0x45aa4e */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 45aa46: fld dword ptr [0x4a9424] */
	goto L_45aa54;	/* 45aa4c: jmp 0x45aa54 */
L_45aa4e:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x168u)));	/* 45aa4e: fld dword ptr [ebp + 0x168] */
L_45aa54:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x178u)));	/* 45aa54: fld dword ptr [ebp + 0x178] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 45aa5a: fadd dword ptr [0x4a9424] */
	m->ecx = (DWORD)(m->ebp + 0x554u);	/* 45aa60: lea ecx, [ebp + 0x554] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 45aa66: fmul dword ptr [0x4a942c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 45aa6c: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x170u));	/* 45aa72: fsub dword ptr [ebp + 0x170] */
	ST(1) = ST(1) * ST(0); FPOP();	/* 45aa78: fmulp st(1) */
	ST(0) = ST(0) * ST(1);	/* 45aa7a: fmul st(1) */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 45aa7c: fsubr dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 45aa82: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->ebp + 0x3a0u)) = (float)ST(0); FPOP();	/* 45aa88: fstp dword ptr [ebp + 0x3a0] */
	m->eax = M32((DWORD)(m->ebp + 0x178u));	/* 45aa8e: mov eax, dword ptr [ebp + 0x178] */
	M32((DWORD)(m->ebp + 0x3a4u)) = m->eax;	/* 45aa94: mov dword ptr [ebp + 0x3a4], eax */
	m->edx = M32((DWORD)(m->ebp + 0x39cu));	/* 45aa9a: mov edx, dword ptr [ebp + 0x39c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45aaa0: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45aaa1: push 0 */
	ST(0) = ST(0); FPOP();	/* 45aaa3: fstp st(0) */
	m->esp -= 4; M32(m->esp) = 0x45aaaau; native_call(m, 0x46f770u);	/* 45aaa5: call 0x46f770 */
	m->eax = M32((DWORD)(m->ebp + 0x39cu));	/* 45aaaa: mov eax, dword ptr [ebp + 0x39c] */
	m->esi = (DWORD)(m->ebp + 0xd54u);	/* 45aab0: lea esi, [ebp + 0xd54] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45aab6: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45aab7: push 0 */
	m->ecx = m->esi;	/* 45aab9: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x45aac0u; native_call(m, 0x46f770u);	/* 45aabb: call 0x46f770 */
	m->edx = M32((DWORD)(m->ebp + 0x39cu));	/* 45aac0: mov edx, dword ptr [ebp + 0x39c] */
	m->ecx = (DWORD)(m->ebp + 0x1554u);	/* 45aac6: lea ecx, [ebp + 0x1554] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45aacc: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45aacd: push 0 */
	m->esp -= 4; M32(m->esp) = 0x45aad4u; native_call(m, 0x46f770u);	/* 45aacf: call 0x46f770 */
	m->eax = M32((DWORD)(m->ebp + 0x3a0u));	/* 45aad4: mov eax, dword ptr [ebp + 0x3a0] */
	m->ecx = (DWORD)(m->ebp + 0x2524u);	/* 45aada: lea ecx, [ebp + 0x2524] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45aae0: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45aae1: push 0 */
	m->esp -= 4; M32(m->esp) = 0x45aae8u; native_call(m, 0x46f770u);	/* 45aae3: call 0x46f770 */
	m->edx = M32((DWORD)(m->ebp + 0x3a4u));	/* 45aae8: mov edx, dword ptr [ebp + 0x3a4] */
	m->ecx = (DWORD)(m->ebp + 0x34f4u);	/* 45aaee: lea ecx, [ebp + 0x34f4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45aaf4: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45aaf5: push 0 */
	m->esp -= 4; M32(m->esp) = 0x45aafcu; native_call(m, 0x46f770u);	/* 45aaf7: call 0x46f770 */
	m->eax = M32((DWORD)(m->ebp + 0x17cu));	/* 45aafc: mov eax, dword ptr [ebp + 0x17c] */
	m->ecx = M32((DWORD)(m->esp + 0x54u));	/* 45ab02: mov ecx, dword ptr [esp + 0x54] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45ab06: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45ab07: push 0 */
	m->esp -= 4; M32(m->esp) = 0x45ab0eu; native_call(m, 0x46f770u);	/* 45ab09: call 0x46f770 */
	m->esp -= 4; M32(m->esp) = 0x45ab14u; native_call(m, M32(0x4a9204u));	/* 45ab0e: call dword ptr [0x4a9204] */
	m->ecx = M32((DWORD)(m->ebp + 0x15cu));	/* 45ab14: mov ecx, dword ptr [ebp + 0x15c] */
	m->edx = M32((DWORD)(m->ebp + 0x158u));	/* 45ab1a: mov edx, dword ptr [ebp + 0x158] */
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 45ab20: mov eax, dword ptr [edi] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45ab22: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45ab23: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45ab24: push eax */
	m->esp -= 4; M32(m->esp) = 0x45ab2bu; native_call(m, M32(0x4a9214u));	/* 45ab25: call dword ptr [0x4a9214] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x164u)));	/* 45ab2b: fld dword ptr [ebp + 0x164] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 45ab31: fmul dword ptr [0x4a93ec] */
	m->edi = M32((DWORD)(0x4a91f8u));	/* 45ab37: mov edi, dword ptr [0x4a91f8] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45ab3d: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 45ab3f: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45ab44: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45ab46: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 45ab47: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x45ab4cu; native_call(m, m->edi);	/* 45ab4a: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x174u)));	/* 45ab4c: fld dword ptr [ebp + 0x174] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 45ab52: fmul dword ptr [0x4a93ec] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45ab58: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45ab5a: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 45ab5c: push 0x3f800000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45ab61: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 45ab62: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x45ab67u; native_call(m, m->edi);	/* 45ab65: call edi */
	m->eax = (DWORD)(m->ebp + 0x3a8u);	/* 45ab67: lea eax, [ebp + 0x3a8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45ab6d: push eax */
	{ DWORD v_ = 0xba6u; m->esp -= 4; M32(m->esp) = v_; }	/* 45ab6e: push 0xba6 */
	m->esp -= 4; M32(m->esp) = 0x45ab79u; native_call(m, M32(0x4a9270u));	/* 45ab73: call dword ptr [0x4a9270] */
	m->eax = (DWORD)(m->ebp + 0x3a8u);	/* 45ab79: lea eax, [ebp + 0x3a8] */
	m->ecx = m->esi;	/* 45ab7f: mov ecx, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45ab81: push eax */
	m->esp -= 4; M32(m->esp) = 0x45ab87u; native_call(m, 0x46f8c0u);	/* 45ab82: call 0x46f8c0 */
	m->ecx = M32((DWORD)(m->ebp + 0x484u));	/* 45ab87: mov ecx, dword ptr [ebp + 0x484] */
	m->edx = M32((DWORD)(m->esp + 0x4cu));	/* 45ab8d: mov edx, dword ptr [esp + 0x4c] */
	m->esi = M32((DWORD)(0x4a926cu));	/* 45ab91: mov esi, dword ptr [0x4a926c] */
	m->eax = M32((DWORD)(m->edx + m->ecx*4 + 0xa98u));	/* 45ab97: mov eax, dword ptr [edx + ecx*4 + 0xa98] */
	m->ecx = M32((DWORD)(m->ebp + 0xd68u));	/* 45ab9e: mov ecx, dword ptr [ebp + 0xd68] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45aba4: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45aba7: lea eax, [eax + eax*4] */
	m->edx = (DWORD)(m->ecx + m->eax*4 + 0xcu);	/* 45abaa: lea edx, [ecx + eax*4 + 0xc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45abae: push edx */
	m->esp -= 4; M32(m->esp) = 0x45abb1u; native_call(m, m->esi);	/* 45abaf: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x398u)));	/* 45abb1: fld dword ptr [ebp + 0x398] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 45abb7: fmul dword ptr [0x4a93ec] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45abbd: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 45abbf: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45abc4: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45abc6: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 45abc7: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x45abccu; native_call(m, m->edi);	/* 45abca: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45abcc: push 0 */
	m->ecx = (DWORD)(m->ebp + 0x2524u);	/* 45abce: lea ecx, [ebp + 0x2524] */
	m->esp -= 4; M32(m->esp) = 0x45abd9u; native_call(m, 0x46f8c0u);	/* 45abd4: call 0x46f8c0 */
	m->eax = M32((DWORD)(m->ebp + 0x484u));	/* 45abd9: mov eax, dword ptr [ebp + 0x484] */
	m->ecx = M32((DWORD)(m->esp + 0x4cu));	/* 45abdf: mov ecx, dword ptr [esp + 0x4c] */
	m->eax = M32((DWORD)(m->ecx + m->eax*4 + 0xa90u));	/* 45abe3: mov eax, dword ptr [ecx + eax*4 + 0xa90] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45abea: lea eax, [eax + eax*4] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45abed: lea edx, [eax + eax*4] */
	m->eax = M32((DWORD)(m->ebp + 0xd68u));	/* 45abf0: mov eax, dword ptr [ebp + 0xd68] */
	m->ecx = (DWORD)(m->eax + m->edx*4 + 0xcu);	/* 45abf6: lea ecx, [eax + edx*4 + 0xc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45abfa: push ecx */
	m->esp -= 4; M32(m->esp) = 0x45abfdu; native_call(m, m->esi);	/* 45abfb: call esi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45abfd: push 0 */
	m->ecx = (DWORD)(m->ebp + 0x1554u);	/* 45abff: lea ecx, [ebp + 0x1554] */
	m->esp -= 4; M32(m->esp) = 0x45ac0au; native_call(m, 0x46f8c0u);	/* 45ac05: call 0x46f8c0 */
	m->edx = M32((DWORD)(m->ebp + 0x484u));	/* 45ac0a: mov edx, dword ptr [ebp + 0x484] */
	m->eax = M32((DWORD)(m->esp + 0x4cu));	/* 45ac10: mov eax, dword ptr [esp + 0x4c] */
	m->eax = M32((DWORD)(m->eax + m->edx*4 + 0xaa0u));	/* 45ac14: mov eax, dword ptr [eax + edx*4 + 0xaa0] */
	m->edx = M32((DWORD)(m->ebp + 0xd68u));	/* 45ac1b: mov edx, dword ptr [ebp + 0xd68] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45ac21: lea eax, [eax + eax*4] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45ac24: lea ecx, [eax + eax*4] */
	m->eax = (DWORD)(m->edx + m->ecx*4 + 0xcu);	/* 45ac27: lea eax, [edx + ecx*4 + 0xc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45ac2b: push eax */
	m->esp -= 4; M32(m->esp) = 0x45ac2eu; native_call(m, m->esi);	/* 45ac2c: call esi */
	m->eax = M32((DWORD)(m->ebp + 0x3f0u));	/* 45ac2e: mov eax, dword ptr [ebp + 0x3f0] */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x10u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45ac34: test ah, 0x10 */
	if (m->zf) goto L_45ac4e;	/* 45ac37: je 0x45ac4e */
	{ DWORD v_ = 0x40a00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 45ac39: push 0x40a00000 */
	{ DWORD v_ = 0x40a00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 45ac3e: push 0x40a00000 */
	{ DWORD v_ = 0x40a00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 45ac43: push 0x40a00000 */
	m->esp -= 4; M32(m->esp) = 0x45ac4eu; native_call(m, M32(0x4a9200u));	/* 45ac48: call dword ptr [0x4a9200] */
L_45ac4e:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45ac4e: push 0 */
	m->ecx = (DWORD)(m->ebp + 0x554u);	/* 45ac50: lea ecx, [ebp + 0x554] */
	m->esp -= 4; M32(m->esp) = 0x45ac5bu; native_call(m, 0x46f8c0u);	/* 45ac56: call 0x46f8c0 */
	m->ecx = M32((DWORD)(m->ebp + 0x484u));	/* 45ac5b: mov ecx, dword ptr [ebp + 0x484] */
	m->edx = M32((DWORD)(m->esp + 0x4cu));	/* 45ac61: mov edx, dword ptr [esp + 0x4c] */
	m->eax = M32((DWORD)(m->edx + m->ecx*4 + 0xaa8u));	/* 45ac65: mov eax, dword ptr [edx + ecx*4 + 0xaa8] */
	m->ecx = M32((DWORD)(m->ebp + 0xd68u));	/* 45ac6c: mov ecx, dword ptr [ebp + 0xd68] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45ac72: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45ac75: lea eax, [eax + eax*4] */
	m->edx = (DWORD)(m->ecx + m->eax*4 + 0xcu);	/* 45ac78: lea edx, [ecx + eax*4 + 0xc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45ac7c: push edx */
	m->esp -= 4; M32(m->esp) = 0x45ac7fu; native_call(m, m->esi);	/* 45ac7d: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x390u)));	/* 45ac7f: fld dword ptr [ebp + 0x390] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9468u));	/* 45ac85: fmul dword ptr [0x4a9468] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 45ac8b: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45ac90: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45ac92: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45ac94: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 45ac95: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x45ac9au; native_call(m, m->edi);	/* 45ac98: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x394u)));	/* 45ac9a: fld dword ptr [ebp + 0x394] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 45aca0: fmul dword ptr [0x4a93ec] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45aca6: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45aca8: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 45acaa: push 0x3f800000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45acaf: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 45acb0: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x45acb5u; native_call(m, m->edi);	/* 45acb3: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45acb5: push 0 */
	m->ecx = (DWORD)(m->ebp + 0x34f4u);	/* 45acb7: lea ecx, [ebp + 0x34f4] */
	m->esp -= 4; M32(m->esp) = 0x45acc2u; native_call(m, 0x46f8c0u);	/* 45acbd: call 0x46f8c0 */
	m->eax = M32((DWORD)(0xa0e7e8u));	/* 45acc2: mov eax, dword ptr [0xa0e7e8] */
	m->ecx = M32((DWORD)(0xa0e7ecu));	/* 45acc7: mov ecx, dword ptr [0xa0e7ec] */
	m->edx = M32((DWORD)(0xa0e7f0u));	/* 45accd: mov edx, dword ptr [0xa0e7f0] */
	M32((DWORD)(m->esp + 0x64u)) = m->eax;	/* 45acd3: mov dword ptr [esp + 0x64], eax */
	m->eax = M32((DWORD)(m->ebp + 0x484u));	/* 45acd7: mov eax, dword ptr [ebp + 0x484] */
	M32((DWORD)(m->esp + 0x68u)) = m->ecx;	/* 45acdd: mov dword ptr [esp + 0x68], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x7cu));	/* 45ace1: mov ecx, dword ptr [esp + 0x7c] */
	M32((DWORD)(m->esp + 0x6cu)) = m->edx;	/* 45ace5: mov dword ptr [esp + 0x6c], edx */
	m->eax = M32((DWORD)(m->ecx + m->eax*4 + 0x12d0u));	/* 45ace9: mov eax, dword ptr [ecx + eax*4 + 0x12d0] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45acf0: lea eax, [eax + eax*4] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45acf3: lea edx, [eax + eax*4] */
	m->eax = M32((DWORD)(m->ebp + 0x1568u));	/* 45acf6: mov eax, dword ptr [ebp + 0x1568] */
	m->ecx = (DWORD)(m->eax + m->edx*4 + 0xcu);	/* 45acfc: lea ecx, [eax + edx*4 + 0xc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45ad00: push ecx */
	m->esp -= 4; M32(m->esp) = 0x45ad03u; native_call(m, m->esi);	/* 45ad01: call esi */
	m->edx = M32((DWORD)(m->esp + 0x2b4u));	/* 45ad03: mov edx, dword ptr [esp + 0x2b4] */
	m->eax = M32((DWORD)(m->ebx + 0x202e8d8u));	/* 45ad0a: mov eax, dword ptr [ebx + 0x202e8d8] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45ad10: cmp edx, eax */
	if (!m->zf) goto L_45ad9b;	/* 45ad12: jne 0x45ad9b */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 45ad18: mov eax, dword ptr [esp + 0x34] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45ad1c: test eax, eax */
	if (m->zf) goto L_45ad9b;	/* 45ad1e: je 0x45ad9b */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x140u)), b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45ad20: cmp dword ptr [ebp + 0x140], 3 */
	if (!m->zf && m->sf == m->of) goto L_45ad9b;	/* 45ad27: jg 0x45ad9b */
	m->eax = M32((DWORD)(m->ebp + 0x49cu));	/* 45ad29: mov eax, dword ptr [ebp + 0x49c] */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 45ad2f: mov ecx, dword ptr [esp + 0x34] */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 45ad33: lea eax, [eax + eax*2] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + m->eax*4 + 0x16d8u)));	/* 45ad36: fld dword ptr [ecx + eax*4 + 0x16d8] */
	m->eax = (DWORD)(m->ecx + m->eax*4 + 0x16d8u);	/* 45ad3d: lea eax, [ecx + eax*4 + 0x16d8] */
	ST(0) = -ST(0);	/* 45ad44: fchs  */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 45ad46: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 45ad4a: fld dword ptr [eax + 4] */
	ST(0) = -ST(0);	/* 45ad4d: fchs  */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 45ad4f: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 45ad53: fld dword ptr [eax + 8] */
	ST(0) = -ST(0);	/* 45ad56: fchs  */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 45ad58: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 45ad5c: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x490u));	/* 45ad62: fsub dword ptr [ebp + 0x490] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 45ad68: mov edx, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 45ad6c: mov ecx, dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 45ad70: mov eax, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x64u)) = m->edx;	/* 45ad74: mov dword ptr [esp + 0x64], edx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94acu));	/* 45ad78: fmul dword ptr [0x4a94ac] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45ad7e: push ecx */
	M32((DWORD)(m->esp + 0x6cu)) = m->eax;	/* 45ad7f: mov dword ptr [esp + 0x6c], eax */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45ad83: push eax */
	M32((DWORD)(m->esp + 0x74u)) = m->ecx;	/* 45ad84: mov dword ptr [esp + 0x74], ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(m->esp + 0x20u));	/* 45ad88: fsubr dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x6cu)) = (float)ST(0); FPOP();	/* 45ad8c: fstp dword ptr [esp + 0x6c] */
	m->eax = M32((DWORD)(m->esp + 0x6cu));	/* 45ad90: mov eax, dword ptr [esp + 0x6c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45ad94: push eax */
	m->esp -= 4; M32(m->esp) = 0x45ad9bu; native_call(m, M32(0x4a9214u));	/* 45ad95: call dword ptr [0x4a9214] */
L_45ad9b:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45ad9b: push 0 */
	m->ecx = (DWORD)(m->ebp + 0x40dcu);	/* 45ad9d: lea ecx, [ebp + 0x40dc] */
	m->esp -= 4; M32(m->esp) = 0x45ada8u; native_call(m, 0x46f8c0u);	/* 45ada3: call 0x46f8c0 */
	m->ecx = M32((DWORD)(m->ebp + 0x484u));	/* 45ada8: mov ecx, dword ptr [ebp + 0x484] */
	m->edx = M32((DWORD)(m->esp + 0x7cu));	/* 45adae: mov edx, dword ptr [esp + 0x7c] */
	m->eax = M32((DWORD)(m->edx + m->ecx*4 + 0x12d8u));	/* 45adb2: mov eax, dword ptr [edx + ecx*4 + 0x12d8] */
	m->ecx = M32((DWORD)(m->ebp + 0x1568u));	/* 45adb9: mov ecx, dword ptr [ebp + 0x1568] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45adbf: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45adc2: lea eax, [eax + eax*4] */
	m->edx = (DWORD)(m->ecx + m->eax*4 + 0xcu);	/* 45adc5: lea edx, [ecx + eax*4 + 0xc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45adc9: push edx */
	m->esp -= 4; M32(m->esp) = 0x45adccu; native_call(m, m->esi);	/* 45adca: call esi */
	m->eax = M32((DWORD)(m->esp + 0x2b4u));	/* 45adcc: mov eax, dword ptr [esp + 0x2b4] */
	m->ecx = M32((DWORD)(m->ebx + 0x202e8d8u));	/* 45add3: mov ecx, dword ptr [ebx + 0x202e8d8] */
	m->edi = M32((DWORD)(m->esp + 0x34u));	/* 45add9: mov edi, dword ptr [esp + 0x34] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45addd: cmp eax, ecx */
	if (!m->zf) goto L_45ae5c;	/* 45addf: jne 0x45ae5c */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45ade1: test edi, edi */
	if (m->zf) goto L_45ae5c;	/* 45ade3: je 0x45ae5c */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x140u)), b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45ade5: cmp dword ptr [ebp + 0x140], 4 */
	if (!m->zf) goto L_45ae5c;	/* 45adec: jne 0x45ae5c */
	m->eax = M32((DWORD)(m->ebp + 0x49cu));	/* 45adee: mov eax, dword ptr [ebp + 0x49c] */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 45adf4: lea ecx, [eax + eax*2] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + m->ecx*4 + 0x16d8u)));	/* 45adf7: fld dword ptr [edi + ecx*4 + 0x16d8] */
	m->eax = (DWORD)(m->edi + m->ecx*4 + 0x16d8u);	/* 45adfe: lea eax, [edi + ecx*4 + 0x16d8] */
	ST(0) = -ST(0);	/* 45ae05: fchs  */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 45ae07: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 45ae0b: fld dword ptr [eax + 4] */
	ST(0) = -ST(0);	/* 45ae0e: fchs  */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 45ae10: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 45ae14: fld dword ptr [eax + 8] */
	ST(0) = -ST(0);	/* 45ae17: fchs  */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 45ae19: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 45ae1d: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x490u));	/* 45ae23: fsub dword ptr [ebp + 0x490] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 45ae29: mov edx, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 45ae2d: mov ecx, dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 45ae31: mov eax, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x64u)) = m->edx;	/* 45ae35: mov dword ptr [esp + 0x64], edx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94acu));	/* 45ae39: fmul dword ptr [0x4a94ac] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45ae3f: push ecx */
	M32((DWORD)(m->esp + 0x6cu)) = m->eax;	/* 45ae40: mov dword ptr [esp + 0x6c], eax */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45ae44: push eax */
	M32((DWORD)(m->esp + 0x74u)) = m->ecx;	/* 45ae45: mov dword ptr [esp + 0x74], ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(m->esp + 0x20u));	/* 45ae49: fsubr dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x6cu)) = (float)ST(0); FPOP();	/* 45ae4d: fstp dword ptr [esp + 0x6c] */
	m->eax = M32((DWORD)(m->esp + 0x6cu));	/* 45ae51: mov eax, dword ptr [esp + 0x6c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45ae55: push eax */
	m->esp -= 4; M32(m->esp) = 0x45ae5cu; native_call(m, M32(0x4a9214u));	/* 45ae56: call dword ptr [0x4a9214] */
L_45ae5c:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45ae5c: push 0 */
	m->ecx = (DWORD)(m->ebp + 0x587cu);	/* 45ae5e: lea ecx, [ebp + 0x587c] */
	m->esp -= 4; M32(m->esp) = 0x45ae69u; native_call(m, 0x46f8c0u);	/* 45ae64: call 0x46f8c0 */
	m->ecx = M32((DWORD)(m->ebp + 0x484u));	/* 45ae69: mov ecx, dword ptr [ebp + 0x484] */
	m->edx = M32((DWORD)(m->esp + 0x7cu));	/* 45ae6f: mov edx, dword ptr [esp + 0x7c] */
	m->eax = M32((DWORD)(m->edx + m->ecx*4 + 0x12e0u));	/* 45ae73: mov eax, dword ptr [edx + ecx*4 + 0x12e0] */
	m->ecx = M32((DWORD)(m->ebp + 0x1568u));	/* 45ae7a: mov ecx, dword ptr [ebp + 0x1568] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45ae80: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45ae83: lea eax, [eax + eax*4] */
	m->edx = (DWORD)(m->ecx + m->eax*4 + 0xcu);	/* 45ae86: lea edx, [ecx + eax*4 + 0xc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45ae8a: push edx */
	m->esp -= 4; M32(m->esp) = 0x45ae8du; native_call(m, m->esi);	/* 45ae8b: call esi */
	m->eax = M32((DWORD)(m->esp + 0x2b4u));	/* 45ae8d: mov eax, dword ptr [esp + 0x2b4] */
	m->ecx = M32((DWORD)(m->ebx + 0x202e8d8u));	/* 45ae94: mov ecx, dword ptr [ebx + 0x202e8d8] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45ae9a: cmp eax, ecx */
	if (!m->zf) goto L_45af1d;	/* 45ae9c: jne 0x45af1d */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 45ae9e: xor esi, esi */
	{ DWORD a_ = m->edi, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45aea0: cmp edi, esi */
	if (m->zf) goto L_45af1f;	/* 45aea2: je 0x45af1f */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x140u)), b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45aea4: cmp dword ptr [ebp + 0x140], 5 */
	if (!m->zf) goto L_45af1f;	/* 45aeab: jne 0x45af1f */
	m->eax = M32((DWORD)(m->ebp + 0x49cu));	/* 45aead: mov eax, dword ptr [ebp + 0x49c] */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 45aeb3: lea ecx, [eax + eax*2] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + m->ecx*4 + 0x2d94u)));	/* 45aeb6: fld dword ptr [edi + ecx*4 + 0x2d94] */
	m->eax = (DWORD)(m->edi + m->ecx*4 + 0x2d94u);	/* 45aebd: lea eax, [edi + ecx*4 + 0x2d94] */
	ST(0) = -ST(0);	/* 45aec4: fchs  */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 45aec6: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 45aeca: fld dword ptr [eax + 4] */
	ST(0) = -ST(0);	/* 45aecd: fchs  */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 45aecf: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 45aed3: fld dword ptr [eax + 8] */
	ST(0) = -ST(0);	/* 45aed6: fchs  */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 45aed8: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 45aedc: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x490u));	/* 45aee2: fsub dword ptr [ebp + 0x490] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 45aee8: mov edx, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 45aeec: mov ecx, dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 45aef0: mov eax, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x64u)) = m->edx;	/* 45aef4: mov dword ptr [esp + 0x64], edx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94acu));	/* 45aef8: fmul dword ptr [0x4a94ac] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45aefe: push ecx */
	M32((DWORD)(m->esp + 0x6cu)) = m->eax;	/* 45aeff: mov dword ptr [esp + 0x6c], eax */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45af03: push eax */
	M32((DWORD)(m->esp + 0x74u)) = m->ecx;	/* 45af04: mov dword ptr [esp + 0x74], ecx */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x20u));	/* 45af08: fadd dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x6cu)) = (float)ST(0); FPOP();	/* 45af0c: fstp dword ptr [esp + 0x6c] */
	m->eax = M32((DWORD)(m->esp + 0x6cu));	/* 45af10: mov eax, dword ptr [esp + 0x6c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45af14: push eax */
	m->esp -= 4; M32(m->esp) = 0x45af1bu; native_call(m, M32(0x4a9214u));	/* 45af15: call dword ptr [0x4a9214] */
	goto L_45af1f;	/* 45af1b: jmp 0x45af1f */
L_45af1d:
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 45af1d: xor esi, esi */
L_45af1f:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45af1f: push esi */
	m->ecx = (DWORD)(m->ebp + 0x701cu);	/* 45af20: lea ecx, [ebp + 0x701c] */
	m->esp -= 4; M32(m->esp) = 0x45af2bu; native_call(m, 0x46f8c0u);	/* 45af26: call 0x46f8c0 */
	m->esp -= 4; M32(m->esp) = 0x45af31u; native_call(m, M32(0x4a9258u));	/* 45af2b: call dword ptr [0x4a9258] */
	m->ecx = M32((DWORD)(m->esp + 0x2b4u));	/* 45af31: mov ecx, dword ptr [esp + 0x2b4] */
	m->eax = M32((DWORD)(m->ebx + 0x202e8d4u));	/* 45af38: mov eax, dword ptr [ebx + 0x202e8d4] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45af3e: cmp ecx, eax */
	if (!m->zf) goto L_45b185;	/* 45af40: jne 0x45b185 */
	{ DWORD a_ = m->edi, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45af46: cmp edi, esi */
	if (m->zf) goto L_45b15d;	/* 45af48: je 0x45b15d */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x2e10u)));	/* 45af4e: fld dword ptr [edi + 0x2e10] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45af54: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45af5a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45af5c: test ah, 0x41 */
	if (!m->zf) goto L_45b139;	/* 45af5f: jne 0x45b139 */
	m->eax = M32((DWORD)(m->ebx + 0x202e8c8u));	/* 45af65: mov eax, dword ptr [ebx + 0x202e8c8] */
	M32((DWORD)(m->esp + 0x24u)) = m->esi;	/* 45af6b: mov dword ptr [esp + 0x24], esi */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45af6f: cmp eax, esi */
	if (m->zf || m->sf != m->of) goto L_45b05d;	/* 45af71: jle 0x45b05d */
	m->edi = (DWORD)(m->ebx + 0x202ea80u);	/* 45af77: lea edi, [ebx + 0x202ea80] */
	m->esi = (DWORD)(m->ebx + 0x1ce1b94u);	/* 45af7d: lea esi, [ebx + 0x1ce1b94] */
L_45af83:
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 45af83: mov edx, dword ptr [esp + 0x24] */
	m->eax = M32((DWORD)(m->esp + 0x2b4u));	/* 45af87: mov eax, dword ptr [esp + 0x2b4] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45af8e: cmp edx, eax */
	if (m->zf) goto L_45b037;	/* 45af90: je 0x45b037 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0xffff7960u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45af96: cmp dword ptr [esi - 0x86a0], 1 */
	if (!m->zf) goto L_45b037;	/* 45af9d: jne 0x45b037 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 45afa3: fld dword ptr [esi] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45afa5: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45afab: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45afad: test ah, 0x41 */
	if (!m->zf) goto L_45afd0;	/* 45afb0: jne 0x45afd0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 45afb2: fld dword ptr [esi] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x2b8u));	/* 45afb4: fsub dword ptr [esp + 0x2b8] */
	MF((DWORD)(m->esi + 0x0u)) = (float)ST(0);	/* 45afbb: fst dword ptr [esi] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45afbd: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45afc3: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45afc5: test ah, 1 */
	if (m->zf) goto L_45afd0;	/* 45afc8: je 0x45afd0 */
	M32((DWORD)(m->esi + 0x0u)) = 0x0u;	/* 45afca: mov dword ptr [esi], 0 */
L_45afd0:
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 45afd0: mov eax, dword ptr [esp + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0xcu)));	/* 45afd4: fld dword ptr [ebp + 0xc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x2e10u));	/* 45afd7: fmul dword ptr [eax + 0x2e10] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0xfffffffcu)); FPOP();	/* 45afdd: fcomp dword ptr [esi - 4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45afe0: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45afe2: test ah, 1 */
	if (m->zf) goto L_45b01f;	/* 45afe5: je 0x45b01f */
	m->ecx = M32((DWORD)(m->ebp + 0x118u));	/* 45afe7: mov ecx, dword ptr [ebp + 0x118] */
	m->eax = M32((DWORD)(m->esi + 0xffff792cu));	/* 45afed: mov eax, dword ptr [esi - 0x86d4] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45aff3: cmp ecx, eax */
	if (m->zf) goto L_45b01f;	/* 45aff5: je 0x45b01f */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x0u)));	/* 45aff7: fld dword ptr [edi] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45aff9: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45afff: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45b001: test ah, 0x41 */
	if (m->zf) goto L_45b018;	/* 45b004: je 0x45b018 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 45b006: push 0x64 */
	{ DWORD v_ = 0x12u; m->esp -= 4; M32(m->esp) = v_; }	/* 45b008: push 0x12 */
	m->esp -= 4; M32(m->esp) = 0x45b00fu; native_call(m, 0x456e50u);	/* 45b00a: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45b00f: add esp, 8 */
	M32((DWORD)(m->esi + 0x0u)) = 0x3e800000u;	/* 45b012: mov dword ptr [esi], 0x3e800000 */
L_45b018:
	m->edx = M32((DWORD)(m->ebp + 0x10u));	/* 45b018: mov edx, dword ptr [ebp + 0x10] */
	M32((DWORD)(m->edi + 0x0u)) = m->edx;	/* 45b01b: mov dword ptr [edi], edx */
	goto L_45b03d;	/* 45b01d: jmp 0x45b03d */
L_45b01f:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x0u)));	/* 45b01f: fld dword ptr [edi] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x2b8u));	/* 45b021: fsub dword ptr [esp + 0x2b8] */
	MF((DWORD)(m->edi + 0x0u)) = (float)ST(0);	/* 45b028: fst dword ptr [edi] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45b02a: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45b030: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45b032: test ah, 1 */
	if (m->zf) goto L_45b03d;	/* 45b035: je 0x45b03d */
L_45b037:
	M32((DWORD)(m->edi + 0x0u)) = 0x0u;	/* 45b037: mov dword ptr [edi], 0 */
L_45b03d:
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 45b03d: mov eax, dword ptr [esp + 0x24] */
	m->ecx = M32((DWORD)(m->ebx + 0x202e8c8u));	/* 45b041: mov ecx, dword ptr [ebx + 0x202e8c8] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 45b047: inc eax */
	{ DWORD a_ = m->edi, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 45b048: add edi, 4 */
	{ DWORD a_ = m->esi, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 45b04b: add esi, 0x8888 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45b051: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 45b053: mov dword ptr [esp + 0x24], eax */
	if (m->sf != m->of) goto L_45af83;	/* 45b057: jl 0x45af83 */
L_45b05d:
	M32((DWORD)(m->ebx + 0x202ef30u)) = 0x0u;	/* 45b05d: mov dword ptr [ebx + 0x202ef30], 0 */
	m->eax = M32((DWORD)(m->ebx + 0x202e8c8u));	/* 45b067: mov eax, dword ptr [ebx + 0x202e8c8] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 45b06d: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45b06f: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_45b0bf;	/* 45b071: jle 0x45b0bf */
	m->edx = (DWORD)(m->ebx + 0x202ea80u);	/* 45b073: lea edx, [ebx + 0x202ea80] */
L_45b079:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x0u)));	/* 45b079: fld dword ptr [edx] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45b07b: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45b081: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45b083: test ah, 0x41 */
	if (!m->zf) goto L_45b0b1;	/* 45b086: jne 0x45b0b1 */
	m->eax = M32((DWORD)(m->ebx + 0x202ef30u));	/* 45b088: mov eax, dword ptr [ebx + 0x202ef30] */
	m->esi = M32((DWORD)(m->edx + 0x0u));	/* 45b08e: mov esi, dword ptr [edx] */
	M32((DWORD)(m->ebx + m->eax*4 + 0x202ec10u)) = m->esi;	/* 45b090: mov dword ptr [ebx + eax*4 + 0x202ec10], esi */
	m->eax = M32((DWORD)(m->ebx + 0x202ef30u));	/* 45b097: mov eax, dword ptr [ebx + 0x202ef30] */
	M32((DWORD)(m->ebx + m->eax*4 + 0x202eda0u)) = m->ecx;	/* 45b09d: mov dword ptr [ebx + eax*4 + 0x202eda0], ecx */
	m->eax = M32((DWORD)(m->ebx + 0x202ef30u));	/* 45b0a4: mov eax, dword ptr [ebx + 0x202ef30] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 45b0aa: inc eax */
	M32((DWORD)(m->ebx + 0x202ef30u)) = m->eax;	/* 45b0ab: mov dword ptr [ebx + 0x202ef30], eax */
L_45b0b1:
	m->eax = M32((DWORD)(m->ebx + 0x202e8c8u));	/* 45b0b1: mov eax, dword ptr [ebx + 0x202e8c8] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 45b0b7: inc ecx */
	{ DWORD a_ = m->edx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45b0b8: add edx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45b0bb: cmp ecx, eax */
	if (m->sf != m->of) goto L_45b079;	/* 45b0bd: jl 0x45b079 */
L_45b0bf:
	m->eax = M32((DWORD)(m->ebx + 0x202ef30u));	/* 45b0bf: mov eax, dword ptr [ebx + 0x202ef30] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45b0c5: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_45b185;	/* 45b0c7: jle 0x45b185 */
	m->edi = 0x1u;	/* 45b0cd: mov edi, 1 */
	m->edx = (DWORD)(m->ebx + 0x202ec10u);	/* 45b0d2: lea edx, [ebx + 0x202ec10] */
	M32((DWORD)(m->esp + 0x7cu)) = m->edi;	/* 45b0d8: mov dword ptr [esp + 0x7c], edi */
L_45b0dc:
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45b0dc: cmp edi, eax */
	m->esi = m->edi;	/* 45b0de: mov esi, edi */
	if (m->sf == m->of) goto L_45b122;	/* 45b0e0: jge 0x45b122 */
	m->ecx = (DWORD)(m->edx + 0x4u);	/* 45b0e2: lea ecx, [edx + 4] */
L_45b0e5:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x0u)));	/* 45b0e5: fld dword ptr [edx] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ecx + 0x0u)); FPOP();	/* 45b0e7: fcomp dword ptr [ecx] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45b0e9: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45b0eb: test ah, 1 */
	if (m->zf) goto L_45b114;	/* 45b0ee: je 0x45b114 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x0u)));	/* 45b0f0: fld dword ptr [edx] */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 45b0f2: mov eax, dword ptr [ecx] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 45b0f4: mov dword ptr [edx], eax */
	MF((DWORD)(m->ecx + 0x0u)) = (float)ST(0); FPOP();	/* 45b0f6: fstp dword ptr [ecx] */
	m->edi = M32((DWORD)(m->ecx + 0x190u));	/* 45b0f8: mov edi, dword ptr [ecx + 0x190] */
	m->eax = M32((DWORD)(m->edx + 0x190u));	/* 45b0fe: mov eax, dword ptr [edx + 0x190] */
	M32((DWORD)(m->edx + 0x190u)) = m->edi;	/* 45b104: mov dword ptr [edx + 0x190], edi */
	m->edi = M32((DWORD)(m->esp + 0x7cu));	/* 45b10a: mov edi, dword ptr [esp + 0x7c] */
	M32((DWORD)(m->ecx + 0x190u)) = m->eax;	/* 45b10e: mov dword ptr [ecx + 0x190], eax */
L_45b114:
	m->eax = M32((DWORD)(m->ebx + 0x202ef30u));	/* 45b114: mov eax, dword ptr [ebx + 0x202ef30] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 45b11a: inc esi */
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45b11b: add ecx, 4 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45b11e: cmp esi, eax */
	if (m->sf != m->of) goto L_45b0e5;	/* 45b120: jl 0x45b0e5 */
L_45b122:
	m->eax = M32((DWORD)(m->ebx + 0x202ef30u));	/* 45b122: mov eax, dword ptr [ebx + 0x202ef30] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 45b128: inc edi */
	{ DWORD a_ = m->edx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45b129: add edx, 4 */
	M32((DWORD)(m->esp + 0x7cu)) = m->edi;	/* 45b12c: mov dword ptr [esp + 0x7c], edi */
	m->ecx = (DWORD)(m->edi + 0xffffffffu);	/* 45b130: lea ecx, [edi - 1] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45b133: cmp ecx, eax */
	if (m->sf != m->of) goto L_45b0dc;	/* 45b135: jl 0x45b0dc */
	goto L_45b185;	/* 45b137: jmp 0x45b185 */
L_45b139:
	m->ecx = M32((DWORD)(m->ebx + 0x202e8c8u));	/* 45b139: mov ecx, dword ptr [ebx + 0x202e8c8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45b13f: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45b141: cmp ecx, esi */
	if (m->zf || m->sf != m->of) goto L_45b17f;	/* 45b143: jle 0x45b17f */
	m->ecx = (DWORD)(m->ebx + 0x202ea80u);	/* 45b145: lea ecx, [ebx + 0x202ea80] */
L_45b14b:
	M32((DWORD)(m->ecx + 0x0u)) = m->esi;	/* 45b14b: mov dword ptr [ecx], esi */
	m->edx = M32((DWORD)(m->ebx + 0x202e8c8u));	/* 45b14d: mov edx, dword ptr [ebx + 0x202e8c8] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 45b153: inc eax */
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45b154: add ecx, 4 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45b157: cmp eax, edx */
	if (m->sf != m->of) goto L_45b14b;	/* 45b159: jl 0x45b14b */
	goto L_45b17f;	/* 45b15b: jmp 0x45b17f */
L_45b15d:
	m->ecx = M32((DWORD)(m->ebx + 0x202e8c8u));	/* 45b15d: mov ecx, dword ptr [ebx + 0x202e8c8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45b163: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45b165: cmp ecx, esi */
	if (m->zf || m->sf != m->of) goto L_45b17f;	/* 45b167: jle 0x45b17f */
	m->ecx = (DWORD)(m->ebx + 0x202ea80u);	/* 45b169: lea ecx, [ebx + 0x202ea80] */
L_45b16f:
	M32((DWORD)(m->ecx + 0x0u)) = m->esi;	/* 45b16f: mov dword ptr [ecx], esi */
	m->edx = M32((DWORD)(m->ebx + 0x202e8c8u));	/* 45b171: mov edx, dword ptr [ebx + 0x202e8c8] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 45b177: inc eax */
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45b178: add ecx, 4 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45b17b: cmp eax, edx */
	if (m->sf != m->of) goto L_45b16f;	/* 45b17d: jl 0x45b16f */
L_45b17f:
	M32((DWORD)(m->ebx + 0x202ef30u)) = m->esi;	/* 45b17f: mov dword ptr [ebx + 0x202ef30], esi */
L_45b185:
	m->edi = M32((DWORD)(m->esp + 0x34u));	/* 45b185: mov edi, dword ptr [esp + 0x34] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 45b189: xor esi, esi */
	M32((DWORD)(m->ebp + 0x1ecu)) = m->esi;	/* 45b18b: mov dword ptr [ebp + 0x1ec], esi */
	M32((DWORD)(m->ebp + 0x374u)) = m->esi;	/* 45b191: mov dword ptr [ebp + 0x374], esi */
	m->eax = M32((DWORD)(m->ebp + 0x110u));	/* 45b197: mov eax, dword ptr [ebp + 0x110] */
	m->ecx = M32((DWORD)(m->ebx + 0x202e8d4u));	/* 45b19d: mov ecx, dword ptr [ebx + 0x202e8d4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45b1a3: cmp eax, ecx */
	if (!m->zf) goto L_45baec;	/* 45b1a5: jne 0x45baec */
	{ DWORD a_ = m->edi, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45b1ab: cmp edi, esi */
	m->edx = 0x1u;	/* 45b1ad: mov edx, 1 */
	if (m->zf) goto L_45baf1;	/* 45b1b2: je 0x45baf1 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x14cu)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45b1b8: cmp dword ptr [ebp + 0x14c], edx */
	if (!m->zf) goto L_45baf1;	/* 45b1be: jne 0x45baf1 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x46cu)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45b1c4: cmp dword ptr [ebp + 0x46c], edx */
	if (!m->zf) goto L_45b222;	/* 45b1ca: jne 0x45b222 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x120u)));	/* 45b1cc: fld dword ptr [ebp + 0x120] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9534u)); FPOP();	/* 45b1d2: fcomp dword ptr [0x4a9534] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45b1d8: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45b1da: test ah, 0x41 */
	if (!m->zf) goto L_45b222;	/* 45b1dd: jne 0x45b222 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x140u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45b1df: cmp dword ptr [ebp + 0x140], esi */
	if (m->sf != m->of) goto L_45b222;	/* 45b1e5: jl 0x45b222 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x17cu)));	/* 45b1e7: fld dword ptr [ebp + 0x17c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45b1ed: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45b1f3: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45b1f5: test ah, 0x41 */
	if (m->zf) goto L_45b222;	/* 45b1f8: je 0x45b222 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x490u)));	/* 45b1fa: fld dword ptr [ebp + 0x490] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 45b200: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45b206: fnstsw ax */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->eax >> 8) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45b208: test dl, ah */
	if (!m->zf) goto L_45b222;	/* 45b20a: jne 0x45b222 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x48cu)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45b20c: cmp dword ptr [ebp + 0x48c], esi */
	if (!m->zf) goto L_45b222;	/* 45b212: jne 0x45b222 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x128u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45b214: cmp dword ptr [ebp + 0x128], esi */
	if (m->zf || m->sf != m->of) goto L_45b222;	/* 45b21a: jle 0x45b222 */
	M32((DWORD)(m->ebp + 0x1ecu)) = m->edx;	/* 45b21c: mov dword ptr [ebp + 0x1ec], edx */
L_45b222:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x1ecu)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45b222: cmp dword ptr [ebp + 0x1ec], edx */
	if (!m->zf) goto L_45b2e4;	/* 45b228: jne 0x45b2e4 */
	m->esi = M32((DWORD)(m->esp + 0x34u));	/* 45b22e: mov esi, dword ptr [esp + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2b8u)));	/* 45b232: fld dword ptr [esp + 0x2b8] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esi + 0x2e08u));	/* 45b239: fdiv dword ptr [esi + 0x2e08] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 45b23f: call 0x49ec14 */
	m->edi = M32((DWORD)(m->esi + 0x2dc8u));	/* 45b244: mov edi, dword ptr [esi + 0x2dc8] */
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 45b24a: mov edx, dword ptr [esp + 0x34] */
	m->ecx = m->eax;	/* 45b24e: mov ecx, eax */
	m->esi = m->edi;	/* 45b250: mov esi, edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x2dccu)));	/* 45b252: fld dword ptr [edx + 0x2dcc] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 45b258: inc ecx */
	m->eax = M32((DWORD)(m->ebp + 0x1f0u));	/* 45b259: mov eax, dword ptr [ebp + 0x1f0] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45b25f: fcomp dword ptr [0x4a93e8] */
	{ long long p_ = (long long)(int)m->esi * (int)m->ecx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->esi = r_; }	/* 45b265: imul esi, ecx */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 45b268: add esi, eax */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45b26a: fnstsw ax */
	M32((DWORD)(m->esp + 0x14u)) = m->esi;	/* 45b26c: mov dword ptr [esp + 0x14], esi */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45b270: test ah, 0x41 */
	if (!m->zf) goto L_45b2d5;	/* 45b273: jne 0x45b2d5 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 45b275: dec ecx */
	m->eax = m->edx;	/* 45b276: mov eax, edx */
	M32((DWORD)(m->esp + 0x44u)) = m->ecx;	/* 45b278: mov dword ptr [esp + 0x44], ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x44u)));	/* 45b27c: fild dword ptr [esp + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x2e08u));	/* 45b280: fmul dword ptr [eax + 0x2e08] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(m->esp + 0x2b8u));	/* 45b286: fsubr dword ptr [esp + 0x2b8] */
	{ long double t = ST(0); FPUSH(t); }	/* 45b28d: fld st(0) */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->eax + 0x2dccu));	/* 45b28f: fdiv dword ptr [eax + 0x2dcc] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 45b295: call 0x49ec14 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 45b29a: inc eax */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45b29b: cmp edi, eax */
	if (m->zf || m->sf != m->of) goto L_45b2d3;	/* 45b29d: jle 0x45b2d3 */
	m->ecx = (DWORD)(m->eax + 0xffffffffu);	/* 45b29f: lea ecx, [eax - 1] */
	M32((DWORD)(m->esp + 0x44u)) = m->ecx;	/* 45b2a2: mov dword ptr [esp + 0x44], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 45b2a6: mov ecx, dword ptr [esp + 0x34] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x44u)));	/* 45b2aa: fild dword ptr [esp + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x2dccu));	/* 45b2ae: fmul dword ptr [ecx + 0x2dcc] */
	ST(0) = ST(1) - ST(0);	/* 45b2b4: fsubr st(1) */
	MF((DWORD)(m->ebp + 0x1f4u)) = (float)ST(0); FPOP();	/* 45b2b6: fstp dword ptr [ebp + 0x1f4] */
	m->ecx = M32((DWORD)(m->ecx + 0x2dc8u));	/* 45b2bc: mov ecx, dword ptr [ecx + 0x2dc8] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45b2c2: sub ecx, eax */
	ST(0) = ST(0); FPOP();	/* 45b2c4: fstp st(0) */
	M32((DWORD)(m->ebp + 0x1f0u)) = m->ecx;	/* 45b2c6: mov dword ptr [ebp + 0x1f0], ecx */
	{ DWORD a_ = m->esi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 45b2cc: sub esi, ecx */
	goto L_45b365;	/* 45b2ce: jmp 0x45b365 */
L_45b2d3:
	ST(0) = ST(0); FPOP();	/* 45b2d3: fstp st(0) */
L_45b2d5:
	M32((DWORD)(m->ebp + 0x1f0u)) = 0x0u;	/* 45b2d5: mov dword ptr [ebp + 0x1f0], 0 */
	goto L_45b369;	/* 45b2df: jmp 0x45b369 */
L_45b2e4:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x1f0u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45b2e4: cmp dword ptr [ebp + 0x1f0], esi */
	if (m->zf || m->sf != m->of) goto L_45b363;	/* 45b2ea: jle 0x45b363 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2b8u)));	/* 45b2ec: fld dword ptr [esp + 0x2b8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x1f4u));	/* 45b2f3: fadd dword ptr [ebp + 0x1f4] */
	MF((DWORD)(m->ebp + 0x1f4u)) = (float)ST(0);	/* 45b2f9: fst dword ptr [ebp + 0x1f4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->edi + 0x2dccu));	/* 45b2ff: fcom dword ptr [edi + 0x2dcc] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45b305: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45b307: test ah, 1 */
	if (!m->zf) goto L_45b361;	/* 45b30a: jne 0x45b361 */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->edi + 0x2dccu));	/* 45b30c: fdiv dword ptr [edi + 0x2dcc] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 45b312: call 0x49ec14 */
	m->ecx = M32((DWORD)(m->ebp + 0x1f0u));	/* 45b317: mov ecx, dword ptr [ebp + 0x1f0] */
	M32((DWORD)(m->esp + 0x44u)) = m->eax;	/* 45b31d: mov dword ptr [esp + 0x44], eax */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45b321: cmp eax, ecx */
	if (m->sf != m->of) goto L_45b33b;	/* 45b323: jl 0x45b33b */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45b325: xor eax, eax */
	m->esi = m->ecx;	/* 45b327: mov esi, ecx */
	M32((DWORD)(m->ebp + 0x1f0u)) = m->eax;	/* 45b329: mov dword ptr [ebp + 0x1f0], eax */
	M32((DWORD)(m->esp + 0x14u)) = m->esi;	/* 45b32f: mov dword ptr [esp + 0x14], esi */
	M32((DWORD)(m->ebp + 0x1f4u)) = m->eax;	/* 45b333: mov dword ptr [ebp + 0x1f4], eax */
	goto L_45b369;	/* 45b339: jmp 0x45b369 */
L_45b33b:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x44u)));	/* 45b33b: fild dword ptr [esp + 0x44] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45b33f: sub ecx, eax */
	m->esi = m->eax;	/* 45b341: mov esi, eax */
	M32((DWORD)(m->ebp + 0x1f0u)) = m->ecx;	/* 45b343: mov dword ptr [ebp + 0x1f0], ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->esi;	/* 45b349: mov dword ptr [esp + 0x14], esi */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x2dccu));	/* 45b34d: fmul dword ptr [edi + 0x2dcc] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(m->ebp + 0x1f4u));	/* 45b353: fsubr dword ptr [ebp + 0x1f4] */
	MF((DWORD)(m->ebp + 0x1f4u)) = (float)ST(0); FPOP();	/* 45b359: fstp dword ptr [ebp + 0x1f4] */
	goto L_45b369;	/* 45b35f: jmp 0x45b369 */
L_45b361:
	ST(0) = ST(0); FPOP();	/* 45b361: fstp st(0) */
L_45b363:
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 45b363: xor esi, esi */
L_45b365:
	M32((DWORD)(m->esp + 0x14u)) = m->esi;	/* 45b365: mov dword ptr [esp + 0x14], esi */
L_45b369:
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45b369: test esi, esi */
	M32((DWORD)(m->esp + 0x48u)) = 0x0u;	/* 45b36b: mov dword ptr [esp + 0x48], 0 */
	if (m->zf || m->sf != m->of) goto L_45badb;	/* 45b373: jle 0x45badb */
L_45b379:
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 45b379: xor esi, esi */
	m->eax = (DWORD)(m->ebp + 0x360u);	/* 45b37b: lea eax, [ebp + 0x360] */
L_45b381:
	{ DWORD a_ = M32((DWORD)(m->eax + 0x0u)), b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45b381: cmp dword ptr [eax], 0 */
	if (m->sf != m->of) goto L_45b395;	/* 45b384: jl 0x45b395 */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 45b386: inc esi */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45b387: add eax, 4 */
	{ DWORD a_ = m->esi, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45b38a: cmp esi, 5 */
	if (m->sf == m->of) goto L_45badb;	/* 45b38d: jge 0x45badb */
	goto L_45b381;	/* 45b393: jmp 0x45b381 */
L_45b395:
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45b395: test esi, esi */
	if (m->sf != m->of) goto L_45badb;	/* 45b397: jl 0x45badb */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 45b39d: mov ecx, dword ptr [esp + 0x34] */
	m->eax = M32((DWORD)(m->ecx + 0x2dc0u));	/* 45b3a1: mov eax, dword ptr [ecx + 0x2dc0] */
	m->edi = M32((DWORD)(m->ecx + 0x2dc4u));	/* 45b3a7: mov edi, dword ptr [ecx + 0x2dc4] */
	m->edx = M32((DWORD)(m->ebp + m->eax*4 + 0x130u));	/* 45b3ad: mov edx, dword ptr [ebp + eax*4 + 0x130] */
	{ DWORD a_ = m->edx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45b3b4: cmp edx, edi */
	if (m->sf == m->of) goto L_45b3c5;	/* 45b3b6: jge 0x45b3c5 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x11cu)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45b3b8: cmp dword ptr [ebp + 0x11c], 2 */
	if (!m->zf) goto L_45ba19;	/* 45b3bf: jne 0x45ba19 */
L_45b3c5:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45b3c5: test eax, eax */
	if (m->sf != m->of) goto L_45b9c7;	/* 45b3c7: jl 0x45b9c7 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x140u)), b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45b3cd: cmp dword ptr [ebp + 0x140], 5 */
	if (m->zf) goto L_45b3f0;	/* 45b3d4: je 0x45b3f0 */
	m->eax = M32((DWORD)(m->ebp + 0x49cu));	/* 45b3d6: mov eax, dword ptr [ebp + 0x49c] */
	m->edi = M32((DWORD)(m->esp + 0x34u));	/* 45b3dc: mov edi, dword ptr [esp + 0x34] */
	{ DWORD a_ = m->eax, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45b3e0: shl eax, 6 */
	m->ecx = (DWORD)(m->eax + m->edi*1 + 0x15e8u);	/* 45b3e3: lea ecx, [eax + edi + 0x15e8] */
	M32((DWORD)(m->esp + 0x4cu)) = m->ecx;	/* 45b3ea: mov dword ptr [esp + 0x4c], ecx */
	goto L_45b408;	/* 45b3ee: jmp 0x45b408 */
L_45b3f0:
	m->edx = M32((DWORD)(m->ebp + 0x49cu));	/* 45b3f0: mov edx, dword ptr [ebp + 0x49c] */
	m->edi = M32((DWORD)(m->esp + 0x34u));	/* 45b3f6: mov edi, dword ptr [esp + 0x34] */
	{ DWORD a_ = m->edx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45b3fa: shl edx, 6 */
	m->eax = (DWORD)(m->edx + m->edi*1 + 0x2ca4u);	/* 45b3fd: lea eax, [edx + edi + 0x2ca4] */
	M32((DWORD)(m->esp + 0x4cu)) = m->eax;	/* 45b404: mov dword ptr [esp + 0x4c], eax */
L_45b408:
	m->ecx = M32((DWORD)(m->esp + 0x4cu));	/* 45b408: mov ecx, dword ptr [esp + 0x4c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45b40c: push 0 */
	m->eax = (DWORD)(m->esp + 0x1e4u);	/* 45b40e: lea eax, [esp + 0x1e4] */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 45b415: mov edx, dword ptr [ecx] */
	m->ecx = M32((DWORD)(m->esp + 0x58u));	/* 45b417: mov ecx, dword ptr [esp + 0x58] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45b41b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45b41c: push eax */
	m->edx = M32((DWORD)(m->ecx + 0x20u));	/* 45b41d: mov edx, dword ptr [ecx + 0x20] */
	m->ecx = M32((DWORD)(m->edx + 0x0u));	/* 45b420: mov ecx, dword ptr [edx] */
	m->esp -= 4; M32(m->esp) = 0x45b427u; native_call(m, 0x46ab30u);	/* 45b422: call 0x46ab30 */
	m->eax = (DWORD)(m->esp + 0x1e0u);	/* 45b427: lea eax, [esp + 0x1e0] */
	m->ecx = (DWORD)(m->esp + 0x270u);	/* 45b42e: lea ecx, [esp + 0x270] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45b435: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45b436: push ecx */
	m->esp -= 4; M32(m->esp) = 0x45b43cu; native_call(m, 0x47d740u);	/* 45b437: call 0x47d740 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x6cu)));	/* 45b43c: fld dword ptr [esp + 0x6c] */
	ST(0) = -ST(0);	/* 45b440: fchs  */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x70u)));	/* 45b442: fld dword ptr [esp + 0x70] */
	ST(0) = -ST(0);	/* 45b446: fchs  */
	MF((DWORD)(m->esp + 0x64u)) = (float)ST(0); FPOP();	/* 45b448: fstp dword ptr [esp + 0x64] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x74u)));	/* 45b44c: fld dword ptr [esp + 0x74] */
	ST(0) = -ST(0);	/* 45b450: fchs  */
	MF((DWORD)(m->esp + 0x68u)) = (float)ST(0); FPOP();	/* 45b452: fstp dword ptr [esp + 0x68] */
	m->edx = (DWORD)(m->esp + 0xd8u);	/* 45b456: lea edx, [esp + 0xd8] */
	m->eax = (DWORD)(m->esp + 0x278u);	/* 45b45d: lea eax, [esp + 0x278] */
	MF((DWORD)(m->esp + 0x108u)) = (float)ST(0); FPOP();	/* 45b464: fstp dword ptr [esp + 0x108] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x64u)));	/* 45b46b: fld dword ptr [esp + 0x64] */
	MF((DWORD)(m->esp + 0x10cu)) = (float)ST(0); FPOP();	/* 45b46f: fstp dword ptr [esp + 0x10c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x68u)));	/* 45b476: fld dword ptr [esp + 0x68] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45b47a: push edx */
	m->ecx = (DWORD)(m->esp + 0x23cu);	/* 45b47b: lea ecx, [esp + 0x23c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45b482: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45b483: push ecx */
	MF((DWORD)(m->esp + 0x11cu)) = (float)ST(0); FPOP();	/* 45b484: fstp dword ptr [esp + 0x11c] */
	M32((DWORD)(m->esp + 0xe4u)) = 0x3f800000u;	/* 45b48b: mov dword ptr [esp + 0xe4], 0x3f800000 */
	M32((DWORD)(m->esp + 0xf4u)) = 0x0u;	/* 45b496: mov dword ptr [esp + 0xf4], 0 */
	M32((DWORD)(m->esp + 0x104u)) = 0x0u;	/* 45b4a1: mov dword ptr [esp + 0x104], 0 */
	M32((DWORD)(m->esp + 0xe8u)) = 0x0u;	/* 45b4ac: mov dword ptr [esp + 0xe8], 0 */
	M32((DWORD)(m->esp + 0xf8u)) = 0x3f800000u;	/* 45b4b7: mov dword ptr [esp + 0xf8], 0x3f800000 */
	M32((DWORD)(m->esp + 0x108u)) = 0x0u;	/* 45b4c2: mov dword ptr [esp + 0x108], 0 */
	M32((DWORD)(m->esp + 0xecu)) = 0x0u;	/* 45b4cd: mov dword ptr [esp + 0xec], 0 */
	M32((DWORD)(m->esp + 0xfcu)) = 0x0u;	/* 45b4d8: mov dword ptr [esp + 0xfc], 0 */
	M32((DWORD)(m->esp + 0x10cu)) = 0x3f800000u;	/* 45b4e3: mov dword ptr [esp + 0x10c], 0x3f800000 */
	M32((DWORD)(m->esp + 0xf0u)) = 0x0u;	/* 45b4ee: mov dword ptr [esp + 0xf0], 0 */
	M32((DWORD)(m->esp + 0x100u)) = 0x0u;	/* 45b4f9: mov dword ptr [esp + 0x100], 0 */
	M32((DWORD)(m->esp + 0x110u)) = 0x0u;	/* 45b504: mov dword ptr [esp + 0x110], 0 */
	M32((DWORD)(m->esp + 0x120u)) = 0x3f800000u;	/* 45b50f: mov dword ptr [esp + 0x120], 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x45b51fu; native_call(m, 0x47d380u);	/* 45b51a: call 0x47d380 */
	m->edx = (DWORD)(m->esp + 0x1f4u);	/* 45b51f: lea edx, [esp + 0x1f4] */
	m->eax = (DWORD)(m->esp + 0x244u);	/* 45b526: lea eax, [esp + 0x244] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45b52d: push edx */
	m->ecx = (DWORD)(m->esp + 0x1a4u);	/* 45b52e: lea ecx, [esp + 0x1a4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45b535: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45b536: push ecx */
	m->esp -= 4; M32(m->esp) = 0x45b53cu; native_call(m, 0x47d380u);	/* 45b537: call 0x47d380 */
	m->eax = M32((DWORD)(m->esp + 0x68u));	/* 45b53c: mov eax, dword ptr [esp + 0x68] */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45b540: add esp, 0x20 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 45b543: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)M32((DWORD)(m->edi + 0x2dc8u)); m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 45b544: idiv dword ptr [edi + 0x2dc8] */
	M32((DWORD)(m->esp + 0x44u)) = m->edx;	/* 45b54a: mov dword ptr [esp + 0x44], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x44u)));	/* 45b54e: fild dword ptr [esp + 0x44] */
	{ long double t = ST(0); FPUSH(t); }	/* 45b552: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x2dd0u));	/* 45b554: fmul dword ptr [edi + 0x2dd0] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 45b55a: fstp dword ptr [esp + 0x38] */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 45b55e: mov edx, dword ptr [esp + 0x38] */
	{ long double t = ST(0); FPUSH(t); }	/* 45b562: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x2dd4u));	/* 45b564: fmul dword ptr [edi + 0x2dd4] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 45b56a: fstp dword ptr [esp + 0x3c] */
	m->eax = M32((DWORD)(m->esp + 0x3cu));	/* 45b56e: mov eax, dword ptr [esp + 0x3c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x2dd8u));	/* 45b572: fmul dword ptr [edi + 0x2dd8] */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 45b578: mov dword ptr [esp + 0x28], edx */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 45b57c: fstp dword ptr [esp + 0x40] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1acu)));	/* 45b580: fld dword ptr [esp + 0x1ac] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 45b587: fmul dword ptr [esp + 0x40] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x19cu)));	/* 45b58b: fld dword ptr [esp + 0x19c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 45b592: fmul dword ptr [esp + 0x3c] */
	m->ecx = M32((DWORD)(m->esp + 0x40u));	/* 45b596: mov ecx, dword ptr [esp + 0x40] */
	m->edx = M32((DWORD)(m->esp + 0x4cu));	/* 45b59a: mov edx, dword ptr [esp + 0x4c] */
	M32((DWORD)(m->esp + 0x2cu)) = m->eax;	/* 45b59e: mov dword ptr [esp + 0x2c], eax */
	M32((DWORD)(m->esp + 0x30u)) = m->ecx;	/* 45b5a2: mov dword ptr [esp + 0x30], ecx */
	ST(1) = ST(1) + ST(0); FPOP();	/* 45b5a6: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18cu)));	/* 45b5a8: fld dword ptr [esp + 0x18c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x38u));	/* 45b5af: fmul dword ptr [esp + 0x38] */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 45b5b3: mov eax, dword ptr [edx] */
	m->ecx = M32((DWORD)(m->esp + 0x54u));	/* 45b5b5: mov ecx, dword ptr [esp + 0x54] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 45b5b9: faddp st(1) */
	m->edx = M32((DWORD)(m->ecx + 0x14u));	/* 45b5bb: mov edx, dword ptr [ecx + 0x14] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45b5be: lea eax, [eax + eax*4] */
	m->ecx = M32((DWORD)(0xa0e7ccu));	/* 45b5c1: mov ecx, dword ptr [0xa0e7cc] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x1bcu));	/* 45b5c7: fadd dword ptr [esp + 0x1bc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1b0u)));	/* 45b5ce: fld dword ptr [esp + 0x1b0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 45b5d5: fmul dword ptr [esp + 0x40] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1a0u)));	/* 45b5d9: fld dword ptr [esp + 0x1a0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 45b5e0: fmul dword ptr [esp + 0x3c] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45b5e4: lea eax, [eax + eax*4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 45b5e7: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x190u)));	/* 45b5e9: fld dword ptr [esp + 0x190] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x38u));	/* 45b5f0: fmul dword ptr [esp + 0x38] */
	m->eax = (DWORD)(m->edx + m->eax*4 + 0xcu);	/* 45b5f4: lea eax, [edx + eax*4 + 0xc] */
	m->edx = M32((DWORD)(0xa0e7d0u));	/* 45b5f8: mov edx, dword ptr [0xa0e7d0] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 45b5fe: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x1c0u));	/* 45b600: fadd dword ptr [esp + 0x1c0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1b4u)));	/* 45b607: fld dword ptr [esp + 0x1b4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 45b60e: fmul dword ptr [esp + 0x40] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1a4u)));	/* 45b612: fld dword ptr [esp + 0x1a4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 45b619: fmul dword ptr [esp + 0x3c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 45b61d: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x194u)));	/* 45b61f: fld dword ptr [esp + 0x194] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x38u));	/* 45b626: fmul dword ptr [esp + 0x38] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 45b62a: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x1c4u));	/* 45b62c: fadd dword ptr [esp + 0x1c4] */
	{ long double t = ST(0); FPUSH(t); }	/* 45b633: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x20u));	/* 45b635: fmul dword ptr [eax + 0x20] */
	{ long double t = ST(2); FPUSH(t); }	/* 45b638: fld st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x10u));	/* 45b63a: fmul dword ptr [eax + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 45b63d: faddp st(1) */
	{ long double t = ST(3); FPUSH(t); }	/* 45b63f: fld st(3) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 45b641: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 45b643: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x30u));	/* 45b645: fadd dword ptr [eax + 0x30] */
	MF((DWORD)(m->esp + 0x9cu)) = (float)ST(0); FPOP();	/* 45b648: fstp dword ptr [esp + 0x9c] */
	{ long double t = ST(2); FPUSH(t); }	/* 45b64f: fld st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 45b651: fmul dword ptr [eax + 4] */
	{ long double t = ST(1); FPUSH(t); }	/* 45b654: fld st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x24u));	/* 45b656: fmul dword ptr [eax + 0x24] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 45b659: faddp st(1) */
	{ long double t = ST(2); FPUSH(t); }	/* 45b65b: fld st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x14u));	/* 45b65d: fmul dword ptr [eax + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 45b660: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x34u));	/* 45b662: fadd dword ptr [eax + 0x34] */
	MF((DWORD)(m->esp + 0xa0u)) = (float)ST(0); FPOP();	/* 45b665: fstp dword ptr [esp + 0xa0] */
	{ long double t = ST(0); ST(0) = ST(2); ST(2) = t; }	/* 45b66c: fxch st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 45b66e: fmul dword ptr [eax + 8] */
	{ long double t = ST(0); ST(0) = ST(2); ST(2) = t; }	/* 45b671: fxch st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x28u));	/* 45b673: fmul dword ptr [eax + 0x28] */
	ST(2) = ST(2) + ST(0); FPOP();	/* 45b676: faddp st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x18u));	/* 45b678: fmul dword ptr [eax + 0x18] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 45b67b: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x38u));	/* 45b67d: fadd dword ptr [eax + 0x38] */
	m->eax = M32((DWORD)(0xa0e7c8u));	/* 45b680: mov eax, dword ptr [0xa0e7c8] */
	M32((DWORD)(m->esp + 0xb8u)) = m->ecx;	/* 45b685: mov dword ptr [esp + 0xb8], ecx */
	M32((DWORD)(m->esp + 0xb4u)) = m->eax;	/* 45b68c: mov dword ptr [esp + 0xb4], eax */
	m->eax = M32((DWORD)(m->ebp + 0x11cu));	/* 45b693: mov eax, dword ptr [ebp + 0x11c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45b699: test eax, eax */
	MF((DWORD)(m->esp + 0xa4u)) = (float)ST(0); FPOP();	/* 45b69b: fstp dword ptr [esp + 0xa4] */
	M32((DWORD)(m->esp + 0xbcu)) = m->edx;	/* 45b6a2: mov dword ptr [esp + 0xbc], edx */
	if (!m->zf) goto L_45b6d5;	/* 45b6a9: jne 0x45b6d5 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x160u)));	/* 45b6ab: fld dword ptr [ebp + 0x160] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 45b6b1: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45b6b6: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45b6b7: push 1 */
	m->ecx = (DWORD)(m->esp + 0xbcu);	/* 45b6b9: lea ecx, [esp + 0xbc] */
	m->esp -= 4; M32(m->esp) = 0x45b6c5u; native_call(m, 0x4677c0u);	/* 45b6c0: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x164u)));	/* 45b6c5: fld dword ptr [ebp + 0x164] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 45b6cb: call 0x49ec14 */
	goto L_45b75c;	/* 45b6d0: jmp 0x45b75c */
L_45b6d5:
	m->ecx = M32((DWORD)(m->ebp + 0x74u));	/* 45b6d5: mov ecx, dword ptr [ebp + 0x74] */
	{ DWORD a_ = m->ecx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45b6d8: shl ecx, 1 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45b6da: test ecx, ecx */
	if (m->zf || m->sf != m->of) goto L_45b6fd;	/* 45b6dc: jle 0x45b6fd */
	m->eax = M32((DWORD)(0xa1efb8u));	/* 45b6de: mov eax, dword ptr [0xa1efb8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 45b6e3: xor edx, edx */
	{ DWORD a_ = m->eax, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45b6e5: and eax, 0xfff */
	m->eax = M32((DWORD)(m->eax*4 + 0xa106f8u));	/* 45b6ea: mov eax, dword ptr [eax*4 + 0xa106f8] */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->ecx; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 45b6f1: div ecx */
	{ DWORD a_ = M32((DWORD)(0xa1efb8u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(0xa1efb8u)) = r_; }	/* 45b6f3: inc dword ptr [0xa1efb8] */
	m->edi = m->edx;	/* 45b6f9: mov edi, edx */
	goto L_45b6ff;	/* 45b6fb: jmp 0x45b6ff */
L_45b6fd:
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 45b6fd: xor edi, edi */
L_45b6ff:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x160u)));	/* 45b6ff: fld dword ptr [ebp + 0x160] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 45b705: call 0x49ec14 */
	m->ecx = M32((DWORD)(m->ebp + 0x74u));	/* 45b70a: mov ecx, dword ptr [ebp + 0x74] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45b70d: sub eax, ecx */
	m->ecx = (DWORD)(m->esp + 0xb4u);	/* 45b70f: lea ecx, [esp + 0xb4] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45b716: add eax, edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45b718: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45b719: push 1 */
	m->esp -= 4; M32(m->esp) = 0x45b720u; native_call(m, 0x4677c0u);	/* 45b71b: call 0x4677c0 */
	m->ecx = M32((DWORD)(m->ebp + 0x74u));	/* 45b720: mov ecx, dword ptr [ebp + 0x74] */
	{ DWORD a_ = m->ecx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45b723: shl ecx, 1 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45b725: test ecx, ecx */
	if (m->zf || m->sf != m->of) goto L_45b74a;	/* 45b727: jle 0x45b74a */
	m->edx = M32((DWORD)(0xa1efb8u));	/* 45b729: mov edx, dword ptr [0xa1efb8] */
	{ DWORD a_ = m->edx, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 45b72f: and edx, 0xfff */
	m->eax = M32((DWORD)(m->edx*4 + 0xa106f8u));	/* 45b735: mov eax, dword ptr [edx*4 + 0xa106f8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 45b73c: xor edx, edx */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->ecx; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 45b73e: div ecx */
	{ DWORD a_ = M32((DWORD)(0xa1efb8u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(0xa1efb8u)) = r_; }	/* 45b740: inc dword ptr [0xa1efb8] */
	m->edi = m->edx;	/* 45b746: mov edi, edx */
	goto L_45b74c;	/* 45b748: jmp 0x45b74c */
L_45b74a:
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 45b74a: xor edi, edi */
L_45b74c:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x164u)));	/* 45b74c: fld dword ptr [ebp + 0x164] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 45b752: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->ebp + 0x74u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45b757: sub eax, dword ptr [ebp + 0x74] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45b75a: add eax, edi */
L_45b75c:
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45b75c: push eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 45b75d: push 2 */
	m->ecx = (DWORD)(m->esp + 0xbcu);	/* 45b75f: lea ecx, [esp + 0xbc] */
	m->esp -= 4; M32(m->esp) = 0x45b76bu; native_call(m, 0x4677c0u);	/* 45b766: call 0x4677c0 */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 45b76b: lea eax, [esp + 0x28] */
	m->ecx = (DWORD)(m->esp + 0x9cu);	/* 45b76f: lea ecx, [esp + 0x9c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45b776: push eax */
	m->edi = (DWORD)(m->ebp + 0x154u);	/* 45b777: lea edi, [ebp + 0x154] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45b77d: push ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45b77e: push edi */
	m->ecx = m->ebx;	/* 45b77f: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x45b786u; native_call(m, 0x471740u);	/* 45b781: call 0x471740 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45b786: test eax, eax */
	if (!m->zf) goto L_45bab1;	/* 45b788: jne 0x45bab1 */
	m->eax = M32((DWORD)(m->ebp + 0x11cu));	/* 45b78e: mov eax, dword ptr [ebp + 0x11c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45b794: test eax, eax */
	if (m->zf) goto L_45b8b0;	/* 45b796: je 0x45b8b0 */
	m->eax = M32((DWORD)(m->ebp + 0x8820u));	/* 45b79c: mov eax, dword ptr [ebp + 0x8820] */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 45b7a2: lea edx, [esp + 0x28] */
	m->ecx = m->eax;	/* 45b7a6: mov ecx, eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45b7a8: push edx */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45b7a9: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45b7ac: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45b7ae: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45b7b1: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45b7b3: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45b7b6: add ecx, eax */
	m->eax = (DWORD)(m->esp + 0xa0u);	/* 45b7b8: lea eax, [esp + 0xa0] */
	m->edx = (DWORD)(m->ebx + m->ecx*8 + 0x1cd94fcu);	/* 45b7bf: lea edx, [ebx + ecx*8 + 0x1cd94fc] */
	m->ecx = m->ebx;	/* 45b7c6: mov ecx, ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45b7c8: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45b7c9: push eax */
	m->esp -= 4; M32(m->esp) = 0x45b7cfu; native_call(m, 0x471740u);	/* 45b7ca: call 0x471740 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45b7cf: test eax, eax */
	if (!m->zf) goto L_45b9ff;	/* 45b7d1: jne 0x45b9ff */
	m->eax = M32((DWORD)(m->ebp + 0x8820u));	/* 45b7d7: mov eax, dword ptr [ebp + 0x8820] */
	m->ecx = m->eax;	/* 45b7dd: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45b7df: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45b7e2: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45b7e4: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45b7e7: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45b7e9: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45b7ec: add ecx, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + m->ecx*8 + 0x1cd94fcu)));	/* 45b7ee: fld dword ptr [ebx + ecx*8 + 0x1cd94fc] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 45b7f5: fsub dword ptr [edi] */
	m->eax = (DWORD)(m->ebx + m->ecx*8 + 0x1cd94fcu);	/* 45b7f7: lea eax, [ebx + ecx*8 + 0x1cd94fc] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 45b7fe: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 45b802: fld dword ptr [eax + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 45b805: fsub dword ptr [edi + 4] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 45b808: mov edx, dword ptr [esp + 0x18] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 45b80c: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 45b810: fld dword ptr [eax + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 45b813: fsub dword ptr [edi + 8] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 45b816: mov eax, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 45b81a: mov dword ptr [esp + 0x28], edx */
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 45b81e: mov edx, dword ptr [esp + 0x34] */
	M32((DWORD)(m->esp + 0x2cu)) = m->eax;	/* 45b822: mov dword ptr [esp + 0x2c], eax */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 45b826: fstp dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 45b82a: mov ecx, dword ptr [esp + 0x20] */
	M32((DWORD)(m->esp + 0x30u)) = m->ecx;	/* 45b82e: mov dword ptr [esp + 0x30], ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x2df4u)));	/* 45b832: fld dword ptr [edx + 0x2df4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 45b838: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x20u));	/* 45b83c: fmul dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 45b840: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 45b844: fmul dword ptr [esp + 0x1c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 45b848: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 45b84a: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 45b84e: fmul dword ptr [esp + 0x18] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 45b852: faddp st(1) */
	{ long double t = ST(1); FPUSH(t); }	/* 45b854: fld st(1) */
	ST(0) = ST(0) * ST(2);	/* 45b856: fmul st(2) */
	FCOM(ST(0), ST(1)); FPOP(); FPOP();	/* 45b858: fcompp  */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45b85a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45b85c: test ah, 0x41 */
	ST(0) = ST(0); FPOP();	/* 45b85f: fstp st(0) */
	if (!m->zf) goto L_45b8b0;	/* 45b861: jne 0x45b8b0 */
	m->eax = M32((DWORD)(m->ebp + 0x140u));	/* 45b863: mov eax, dword ptr [ebp + 0x140] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45b869: test eax, eax */
	if (!m->zf) goto L_45b891;	/* 45b86b: jne 0x45b891 */
	m->ecx = M32((DWORD)(m->esp + 0x50u));	/* 45b86d: mov ecx, dword ptr [esp + 0x50] */
	m->edx = M32((DWORD)(m->ecx + 0x330u));	/* 45b871: mov edx, dword ptr [ecx + 0x330] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45b877: test edx, edx */
	if (m->sf != m->of) goto L_45b891;	/* 45b879: jl 0x45b891 */
	m->edx = M32((DWORD)(m->esp + 0x2b4u));	/* 45b87b: mov edx, dword ptr [esp + 0x2b4] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 45b882: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45b884: push edx */
	m->ecx = m->ebx;	/* 45b885: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x45b88cu; native_call(m, 0x45e880u);	/* 45b887: call 0x45e880 */
	goto L_45b9ff;	/* 45b88c: jmp 0x45b9ff */
L_45b891:
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45b891: cmp eax, 4 */
	if (!m->zf) goto L_45b9ff;	/* 45b894: jne 0x45b9ff */
	m->eax = M32((DWORD)(m->esp + 0x2b4u));	/* 45b89a: mov eax, dword ptr [esp + 0x2b4] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45b8a1: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45b8a3: push eax */
	m->ecx = m->ebx;	/* 45b8a4: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x45b8abu; native_call(m, 0x45e880u);	/* 45b8a6: call 0x45e880 */
	goto L_45b9ff;	/* 45b8ab: jmp 0x45b9ff */
L_45b8b0:
	m->ecx = M32((DWORD)(m->esp + 0x4cu));	/* 45b8b0: mov ecx, dword ptr [esp + 0x4c] */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 45b8b4: mov eax, dword ptr [ecx] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45b8b6: lea eax, [eax + eax*4] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45b8b9: lea edx, [eax + eax*4] */
	m->eax = M32((DWORD)(m->esp + 0x54u));	/* 45b8bc: mov eax, dword ptr [esp + 0x54] */
	m->ecx = M32((DWORD)(m->eax + 0x14u));	/* 45b8c0: mov ecx, dword ptr [eax + 0x14] */
	m->eax = (DWORD)(m->ecx + m->edx*4 + 0xcu);	/* 45b8c3: lea eax, [ecx + edx*4 + 0xc] */
	m->edx = M32((DWORD)(m->ebp + 0x140u));	/* 45b8c7: mov edx, dword ptr [ebp + 0x140] */
	m->ecx = M32((DWORD)(m->esp + 0x50u));	/* 45b8cd: mov ecx, dword ptr [esp + 0x50] */
	m->edx = M32((DWORD)(m->ecx + m->edx*4 + 0x320u));	/* 45b8d1: mov edx, dword ptr [ecx + edx*4 + 0x320] */
	m->ecx = (DWORD)(m->esi + m->esi*4 + 0x0u);	/* 45b8d8: lea ecx, [esi + esi*4] */
	m->ecx = (DWORD)(m->ebp + m->ecx*8 + 0x298u);	/* 45b8db: lea ecx, [ebp + ecx*8 + 0x298] */
	M32((DWORD)(m->ecx + 0x0u)) = 0x0u;	/* 45b8e2: mov dword ptr [ecx], 0 */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 45b8e8: mov dword ptr [ecx + 4], edx */
	m->edi = M32((DWORD)(m->esp + 0x9cu));	/* 45b8eb: mov edi, dword ptr [esp + 0x9c] */
	m->edx = (DWORD)(m->ecx + 0x8u);	/* 45b8f2: lea edx, [ecx + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edi;	/* 45b8f5: mov dword ptr [ecx + 8], edi */
	m->edi = M32((DWORD)(m->esp + 0xa0u));	/* 45b8f8: mov edi, dword ptr [esp + 0xa0] */
	M32((DWORD)(m->edx + 0x4u)) = m->edi;	/* 45b8ff: mov dword ptr [edx + 4], edi */
	m->edi = M32((DWORD)(m->esp + 0xa4u));	/* 45b902: mov edi, dword ptr [esp + 0xa4] */
	M32((DWORD)(m->edx + 0x8u)) = m->edi;	/* 45b909: mov dword ptr [edx + 8], edi */
	M32((DWORD)(m->ecx + 0x14u)) = 0xffffffffu;	/* 45b90c: mov dword ptr [ecx + 0x14], 0xffffffff */
	m->edi = M32((DWORD)(m->esp + 0xb4u));	/* 45b913: mov edi, dword ptr [esp + 0xb4] */
	m->edx = (DWORD)(m->ecx + 0x18u);	/* 45b91a: lea edx, [ecx + 0x18] */
	M32((DWORD)(m->ecx + 0x18u)) = m->edi;	/* 45b91d: mov dword ptr [ecx + 0x18], edi */
	m->edi = M32((DWORD)(m->esp + 0xb8u));	/* 45b920: mov edi, dword ptr [esp + 0xb8] */
	M32((DWORD)(m->edx + 0x4u)) = m->edi;	/* 45b927: mov dword ptr [edx + 4], edi */
	m->edi = M32((DWORD)(m->esp + 0xbcu));	/* 45b92a: mov edi, dword ptr [esp + 0xbc] */
	M32((DWORD)(m->edx + 0x8u)) = m->edi;	/* 45b931: mov dword ptr [edx + 8], edi */
	M32((DWORD)(m->ecx + 0x24u)) = m->eax;	/* 45b934: mov dword ptr [ecx + 0x24], eax */
	m->eax = M32((DWORD)(m->esp + 0x2b4u));	/* 45b937: mov eax, dword ptr [esp + 0x2b4] */
	m->edx = M32((DWORD)(m->ebx + 0x202e8d4u));	/* 45b93e: mov edx, dword ptr [ebx + 0x202e8d4] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45b944: cmp eax, edx */
	if (!m->zf) goto L_45b967;	/* 45b946: jne 0x45b967 */
	m->edi = M32((DWORD)(m->ebx + 0x202ef30u));	/* 45b948: mov edi, dword ptr [ebx + 0x202ef30] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45b94e: test edi, edi */
	if (m->zf || m->sf != m->of) goto L_45b962;	/* 45b950: jle 0x45b962 */
	m->eax = M32((DWORD)(m->esp + 0x48u));	/* 45b952: mov eax, dword ptr [esp + 0x48] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 45b956: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->edi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 45b957: idiv edi */
	m->edx = M32((DWORD)(m->ebx + m->edx*4 + 0x202eda0u));	/* 45b959: mov edx, dword ptr [ebx + edx*4 + 0x202eda0] */
	goto L_45b96d;	/* 45b960: jmp 0x45b96d */
L_45b962:
	{ DWORD a_ = m->edx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 45b962: or edx, 0xffffffff */
	goto L_45b96d;	/* 45b965: jmp 0x45b96d */
L_45b967:
	m->edx = M32((DWORD)(m->ebp + 0x8820u));	/* 45b967: mov edx, dword ptr [ebp + 0x8820] */
L_45b96d:
	m->eax = M32((DWORD)(m->esp + 0x48u));	/* 45b96d: mov eax, dword ptr [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45b971: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45b972: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x2bcu));	/* 45b973: mov ecx, dword ptr [esp + 0x2bc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45b97a: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45b97b: push ecx */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 45b97c: push -1 */
	m->ecx = m->ebx;	/* 45b97e: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x45b985u; native_call(m, 0x47ce50u);	/* 45b980: call 0x47ce50 */
	M32((DWORD)(m->ebp + m->esi*4 + 0x360u)) = m->eax;	/* 45b985: mov dword ptr [ebp + esi*4 + 0x360], eax */
	{ DWORD a_ = m->esi, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 45b98c: shl esi, 5 */
	M32((DWORD)(m->esi + m->ebp*1 + 0x1fcu)) = 0x1u;	/* 45b98f: mov dword ptr [esi + ebp + 0x1fc], 1 */
	m->eax = M32((DWORD)(m->ebp + 0x11cu));	/* 45b99a: mov eax, dword ptr [ebp + 0x11c] */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45b9a0: cmp eax, 2 */
	if (m->zf) goto L_45b9c7;	/* 45b9a3: je 0x45b9c7 */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 45b9a5: mov ecx, dword ptr [esp + 0x34] */
	m->edx = M32((DWORD)(m->ecx + 0x2dc0u));	/* 45b9a9: mov edx, dword ptr [ecx + 0x2dc0] */
	m->ecx = M32((DWORD)(m->ecx + 0x2dc4u));	/* 45b9af: mov ecx, dword ptr [ecx + 0x2dc4] */
	m->eax = (DWORD)(m->ebp + m->edx*4 + 0x130u);	/* 45b9b5: lea eax, [ebp + edx*4 + 0x130] */
	m->edx = M32((DWORD)(m->ebp + m->edx*4 + 0x130u));	/* 45b9bc: mov edx, dword ptr [ebp + edx*4 + 0x130] */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45b9c3: sub edx, ecx */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 45b9c5: mov dword ptr [eax], edx */
L_45b9c7:
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 45b9c7: mov edx, dword ptr [esp + 0x34] */
	M32((DWORD)(m->ebp + 0x17cu)) = 0x38d1b717u;	/* 45b9cb: mov dword ptr [ebp + 0x17c], 0x38d1b717 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2b8u)));	/* 45b9d5: fld dword ptr [esp + 0x2b8] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->edx + 0x2e08u));	/* 45b9dc: fdiv dword ptr [edx + 0x2e08] */
	MF((DWORD)(m->ebp + 0x1a8u)) = (float)ST(0);	/* 45b9e2: fst dword ptr [ebp + 0x1a8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 45b9e8: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45b9ee: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45b9f0: test ah, 1 */
	if (!m->zf) goto L_45b9ff;	/* 45b9f3: jne 0x45b9ff */
	M32((DWORD)(m->ebp + 0x1a8u)) = 0x0u;	/* 45b9f5: mov dword ptr [ebp + 0x1a8], 0 */
L_45b9ff:
	m->eax = M32((DWORD)(m->esp + 0x48u));	/* 45b9ff: mov eax, dword ptr [esp + 0x48] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 45ba03: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 45ba07: inc eax */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45ba08: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x48u)) = m->eax;	/* 45ba0a: mov dword ptr [esp + 0x48], eax */
	if (m->sf == m->of) goto L_45badb;	/* 45ba0e: jge 0x45badb */
	goto L_45b379;	/* 45ba14: jmp 0x45b379 */
L_45ba19:
	m->eax = M32((DWORD)(m->esp + 0x2b4u));	/* 45ba19: mov eax, dword ptr [esp + 0x2b4] */
	m->ecx = M32((DWORD)(m->ebx + 0x202e8d4u));	/* 45ba20: mov ecx, dword ptr [ebx + 0x202e8d4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45ba26: cmp eax, ecx */
	if (!m->zf) goto L_45ba87;	/* 45ba28: jne 0x45ba87 */
	m->eax = M32((DWORD)(m->ebp + 0x4a0u));	/* 45ba2a: mov eax, dword ptr [ebp + 0x4a0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45ba30: test eax, eax */
	if (!m->zf) goto L_45badb;	/* 45ba32: jne 0x45badb */
	m->ecx = 0x4b4528u;	/* 45ba38: mov ecx, 0x4b4528 */
	m->edx = (DWORD)(m->ebp + 0x4f4u);	/* 45ba3d: lea edx, [ebp + 0x4f4] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45ba43: test ecx, ecx */
	if (m->zf) goto L_45ba68;	/* 45ba45: je 0x45ba68 */
	m->edi = m->ecx;	/* 45ba47: mov edi, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 45ba49: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45ba4c: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 45ba4e: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 45ba50: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 45ba52: sub edi, ecx */
	m->eax = m->ecx;	/* 45ba54: mov eax, ecx */
	m->esi = m->edi;	/* 45ba56: mov esi, edi */
	m->edi = m->edx;	/* 45ba58: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45ba5a: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 45ba5d: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 45ba5f: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 45ba61: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 45ba64: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_45ba6b;	/* 45ba66: jmp 0x45ba6b */
L_45ba68:
	M8((DWORD)(m->edx + 0x0u)) = (BYTE)(0x0u);	/* 45ba68: mov byte ptr [edx], 0 */
L_45ba6b:
	m->ecx = M32((DWORD)(m->esp + 0x2b8u));	/* 45ba6b: mov ecx, dword ptr [esp + 0x2b8] */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 45ba72: push 0x64 */
	{ DWORD v_ = 0xa5u; m->esp -= 4; M32(m->esp) = v_; }	/* 45ba74: push 0xa5 */
	M32((DWORD)(m->ebp + 0x534u)) = m->ecx;	/* 45ba79: mov dword ptr [ebp + 0x534], ecx */
	m->esp -= 4; M32(m->esp) = 0x45ba84u; native_call(m, 0x456e50u);	/* 45ba7f: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45ba84: add esp, 8 */
L_45ba87:
	m->eax = M32((DWORD)(m->ebp + 0x4a0u));	/* 45ba87: mov eax, dword ptr [ebp + 0x4a0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45ba8d: test eax, eax */
	if (!m->zf) goto L_45badb;	/* 45ba8f: jne 0x45badb */
	m->edx = M32((DWORD)(m->esp + 0x2b4u));	/* 45ba91: mov edx, dword ptr [esp + 0x2b4] */
	m->ecx = m->ebx;	/* 45ba98: mov ecx, ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45ba9a: push edx */
	m->esp -= 4; M32(m->esp) = 0x45baa0u; native_call(m, 0x45e9e0u);	/* 45ba9b: call 0x45e9e0 */
	m->ecx = M32((DWORD)(m->ebp + 0x46cu));	/* 45baa0: mov ecx, dword ptr [ebp + 0x46c] */
	M32((DWORD)(m->ebp + 0x4a0u)) = m->ecx;	/* 45baa6: mov dword ptr [ebp + 0x4a0], ecx */
	goto L_45bf63;	/* 45baac: jmp 0x45bf63 */
L_45bab1:
	m->eax = M32((DWORD)(m->esp + 0x2b4u));	/* 45bab1: mov eax, dword ptr [esp + 0x2b4] */
	m->ecx = M32((DWORD)(m->ebx + 0x202e8d4u));	/* 45bab8: mov ecx, dword ptr [ebx + 0x202e8d4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45babe: cmp eax, ecx */
	if (!m->zf) goto L_45badb;	/* 45bac0: jne 0x45badb */
	m->eax = M32((DWORD)(m->ebp + 0x4a0u));	/* 45bac2: mov eax, dword ptr [ebp + 0x4a0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45bac8: test eax, eax */
	if (!m->zf) goto L_45badb;	/* 45baca: jne 0x45badb */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 45bacc: push 0x64 */
	{ DWORD v_ = 0xa5u; m->esp -= 4; M32(m->esp) = v_; }	/* 45bace: push 0xa5 */
	m->esp -= 4; M32(m->esp) = 0x45bad8u; native_call(m, 0x456e50u);	/* 45bad3: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45bad8: add esp, 8 */
L_45badb:
	m->ecx = M32((DWORD)(m->ebp + 0x46cu));	/* 45badb: mov ecx, dword ptr [ebp + 0x46c] */
	M32((DWORD)(m->ebp + 0x4a0u)) = m->ecx;	/* 45bae1: mov dword ptr [ebp + 0x4a0], ecx */
	goto L_45bf63;	/* 45bae7: jmp 0x45bf63 */
L_45baec:
	m->edx = 0x1u;	/* 45baec: mov edx, 1 */
L_45baf1:
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45baf1: cmp eax, ecx */
	if (m->zf) goto L_45bf63;	/* 45baf3: je 0x45bf63 */
	{ DWORD a_ = m->edi, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45baf9: cmp edi, esi */
	if (m->zf) goto L_45bf63;	/* 45bafb: je 0x45bf63 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x1e8u)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45bb01: cmp dword ptr [ebp + 0x1e8], edx */
	if (!m->zf) goto L_45bf63;	/* 45bb07: jne 0x45bf63 */
	m->edx = (DWORD)(m->ebp + 0x360u);	/* 45bb0d: lea edx, [ebp + 0x360] */
	m->eax = (DWORD)(m->ebp + 0x1fcu);	/* 45bb13: lea eax, [ebp + 0x1fc] */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 45bb19: mov dword ptr [esp + 0x14], edx */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 45bb1d: mov dword ptr [esp + 0x10], eax */
	m->esi = (DWORD)(m->ebp + 0x2a0u);	/* 45bb21: lea esi, [ebp + 0x2a0] */
	M32((DWORD)(m->esp + 0x7cu)) = 0x5u;	/* 45bb27: mov dword ptr [esp + 0x7c], 5 */
L_45bb2f:
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 45bb2f: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD a_ = M32((DWORD)(m->ecx + 0xfffffffcu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45bb33: cmp dword ptr [ecx - 4], 1 */
	if (!m->zf) goto L_45bf3b;	/* 45bb37: jne 0x45bf3b */
	m->edx = m->ecx;	/* 45bb3d: mov edx, ecx */
	{ DWORD a_ = M32((DWORD)(m->edx + 0x0u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45bb3f: cmp dword ptr [edx], 1 */
	if (!m->zf) goto L_45be98;	/* 45bb42: jne 0x45be98 */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 45bb48: mov eax, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->eax + 0x0u));	/* 45bb4c: mov eax, dword ptr [eax] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45bb4e: test eax, eax */
	if (m->sf != m->of) goto L_45bb5a;	/* 45bb50: jl 0x45bb5a */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45bb52: push eax */
	m->ecx = m->ebx;	/* 45bb53: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x45bb5au; native_call(m, 0x47cf10u);	/* 45bb55: call 0x47cf10 */
L_45bb5a:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x140u)), b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45bb5a: cmp dword ptr [ebp + 0x140], 5 */
	if (m->zf) goto L_45bb79;	/* 45bb61: je 0x45bb79 */
	m->ecx = M32((DWORD)(m->ebp + 0x49cu));	/* 45bb63: mov ecx, dword ptr [ebp + 0x49c] */
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 45bb69: mov edx, dword ptr [esp + 0x34] */
	{ DWORD a_ = m->ecx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45bb6d: shl ecx, 6 */
	m->edi = (DWORD)(m->ecx + m->edx*1 + 0x15e8u);	/* 45bb70: lea edi, [ecx + edx + 0x15e8] */
	goto L_45bb8d;	/* 45bb77: jmp 0x45bb8d */
L_45bb79:
	m->eax = M32((DWORD)(m->ebp + 0x49cu));	/* 45bb79: mov eax, dword ptr [ebp + 0x49c] */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 45bb7f: mov ecx, dword ptr [esp + 0x34] */
	{ DWORD a_ = m->eax, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45bb83: shl eax, 6 */
	m->edi = (DWORD)(m->eax + m->ecx*1 + 0x2ca4u);	/* 45bb86: lea edi, [eax + ecx + 0x2ca4] */
L_45bb8d:
	m->edx = M32((DWORD)(m->edi + 0x0u));	/* 45bb8d: mov edx, dword ptr [edi] */
	m->ecx = M32((DWORD)(m->esp + 0x54u));	/* 45bb8f: mov ecx, dword ptr [esp + 0x54] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45bb93: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45bb95: push edx */
	m->edx = M32((DWORD)(m->ecx + 0x20u));	/* 45bb96: mov edx, dword ptr [ecx + 0x20] */
	m->eax = (DWORD)(m->esp + 0x1e8u);	/* 45bb99: lea eax, [esp + 0x1e8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45bba0: push eax */
	m->ecx = M32((DWORD)(m->edx + 0x0u));	/* 45bba1: mov ecx, dword ptr [edx] */
	m->esp -= 4; M32(m->esp) = 0x45bba8u; native_call(m, 0x46ab30u);	/* 45bba3: call 0x46ab30 */
	m->eax = (DWORD)(m->esp + 0x1e0u);	/* 45bba8: lea eax, [esp + 0x1e0] */
	m->ecx = (DWORD)(m->esp + 0x270u);	/* 45bbaf: lea ecx, [esp + 0x270] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45bbb6: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45bbb7: push ecx */
	m->esp -= 4; M32(m->esp) = 0x45bbbdu; native_call(m, 0x47d740u);	/* 45bbb8: call 0x47d740 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x6cu)));	/* 45bbbd: fld dword ptr [esp + 0x6c] */
	ST(0) = -ST(0);	/* 45bbc1: fchs  */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x70u)));	/* 45bbc3: fld dword ptr [esp + 0x70] */
	ST(0) = -ST(0);	/* 45bbc7: fchs  */
	MF((DWORD)(m->esp + 0x64u)) = (float)ST(0); FPOP();	/* 45bbc9: fstp dword ptr [esp + 0x64] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x74u)));	/* 45bbcd: fld dword ptr [esp + 0x74] */
	ST(0) = -ST(0);	/* 45bbd1: fchs  */
	MF((DWORD)(m->esp + 0x68u)) = (float)ST(0); FPOP();	/* 45bbd3: fstp dword ptr [esp + 0x68] */
	m->edx = (DWORD)(m->esp + 0xd8u);	/* 45bbd7: lea edx, [esp + 0xd8] */
	m->eax = (DWORD)(m->esp + 0x278u);	/* 45bbde: lea eax, [esp + 0x278] */
	MF((DWORD)(m->esp + 0x108u)) = (float)ST(0); FPOP();	/* 45bbe5: fstp dword ptr [esp + 0x108] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x64u)));	/* 45bbec: fld dword ptr [esp + 0x64] */
	MF((DWORD)(m->esp + 0x10cu)) = (float)ST(0); FPOP();	/* 45bbf0: fstp dword ptr [esp + 0x10c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x68u)));	/* 45bbf7: fld dword ptr [esp + 0x68] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45bbfb: push edx */
	m->ecx = (DWORD)(m->esp + 0x23cu);	/* 45bbfc: lea ecx, [esp + 0x23c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45bc03: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45bc04: push ecx */
	MF((DWORD)(m->esp + 0x11cu)) = (float)ST(0); FPOP();	/* 45bc05: fstp dword ptr [esp + 0x11c] */
	M32((DWORD)(m->esp + 0xe4u)) = 0x3f800000u;	/* 45bc0c: mov dword ptr [esp + 0xe4], 0x3f800000 */
	M32((DWORD)(m->esp + 0xf4u)) = 0x0u;	/* 45bc17: mov dword ptr [esp + 0xf4], 0 */
	M32((DWORD)(m->esp + 0x104u)) = 0x0u;	/* 45bc22: mov dword ptr [esp + 0x104], 0 */
	M32((DWORD)(m->esp + 0xe8u)) = 0x0u;	/* 45bc2d: mov dword ptr [esp + 0xe8], 0 */
	M32((DWORD)(m->esp + 0xf8u)) = 0x3f800000u;	/* 45bc38: mov dword ptr [esp + 0xf8], 0x3f800000 */
	M32((DWORD)(m->esp + 0x108u)) = 0x0u;	/* 45bc43: mov dword ptr [esp + 0x108], 0 */
	M32((DWORD)(m->esp + 0xecu)) = 0x0u;	/* 45bc4e: mov dword ptr [esp + 0xec], 0 */
	M32((DWORD)(m->esp + 0xfcu)) = 0x0u;	/* 45bc59: mov dword ptr [esp + 0xfc], 0 */
	M32((DWORD)(m->esp + 0x10cu)) = 0x3f800000u;	/* 45bc64: mov dword ptr [esp + 0x10c], 0x3f800000 */
	M32((DWORD)(m->esp + 0xf0u)) = 0x0u;	/* 45bc6f: mov dword ptr [esp + 0xf0], 0 */
	M32((DWORD)(m->esp + 0x100u)) = 0x0u;	/* 45bc7a: mov dword ptr [esp + 0x100], 0 */
	M32((DWORD)(m->esp + 0x110u)) = 0x0u;	/* 45bc85: mov dword ptr [esp + 0x110], 0 */
	M32((DWORD)(m->esp + 0x120u)) = 0x3f800000u;	/* 45bc90: mov dword ptr [esp + 0x120], 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x45bca0u; native_call(m, 0x47d380u);	/* 45bc9b: call 0x47d380 */
	m->edx = (DWORD)(m->esp + 0x1f4u);	/* 45bca0: lea edx, [esp + 0x1f4] */
	m->eax = (DWORD)(m->esp + 0x244u);	/* 45bca7: lea eax, [esp + 0x244] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45bcae: push edx */
	m->ecx = (DWORD)(m->esp + 0x1a4u);	/* 45bcaf: lea ecx, [esp + 0x1a4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45bcb6: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45bcb7: push ecx */
	m->esp -= 4; M32(m->esp) = 0x45bcbdu; native_call(m, 0x47d380u);	/* 45bcb8: call 0x47d380 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1ccu)));	/* 45bcbd: fld dword ptr [esp + 0x1cc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0xa0e7b0u));	/* 45bcc4: fmul dword ptr [0xa0e7b0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1bcu)));	/* 45bcca: fld dword ptr [esp + 0x1bc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0xa0e7acu));	/* 45bcd1: fmul dword ptr [0xa0e7ac] */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45bcd7: add esp, 0x20 */
	ST(1) = ST(1) + ST(0); FPOP();	/* 45bcda: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18cu)));	/* 45bcdc: fld dword ptr [esp + 0x18c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0xa0e7a8u));	/* 45bce3: fmul dword ptr [0xa0e7a8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 45bce9: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x1bcu));	/* 45bceb: fadd dword ptr [esp + 0x1bc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1b0u)));	/* 45bcf2: fld dword ptr [esp + 0x1b0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0xa0e7b0u));	/* 45bcf9: fmul dword ptr [0xa0e7b0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1a0u)));	/* 45bcff: fld dword ptr [esp + 0x1a0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0xa0e7acu));	/* 45bd06: fmul dword ptr [0xa0e7ac] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 45bd0c: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x190u)));	/* 45bd0e: fld dword ptr [esp + 0x190] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0xa0e7a8u));	/* 45bd15: fmul dword ptr [0xa0e7a8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 45bd1b: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x1c0u));	/* 45bd1d: fadd dword ptr [esp + 0x1c0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1b4u)));	/* 45bd24: fld dword ptr [esp + 0x1b4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0xa0e7b0u));	/* 45bd2b: fmul dword ptr [0xa0e7b0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1a4u)));	/* 45bd31: fld dword ptr [esp + 0x1a4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0xa0e7acu));	/* 45bd38: fmul dword ptr [0xa0e7ac] */
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 45bd3e: mov eax, dword ptr [edi] */
	m->edx = M32((DWORD)(m->esp + 0x54u));	/* 45bd40: mov edx, dword ptr [esp + 0x54] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45bd44: push 0 */
	ST(1) = ST(1) + ST(0); FPOP();	/* 45bd46: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x198u)));	/* 45bd48: fld dword ptr [esp + 0x198] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0xa0e7a8u));	/* 45bd4f: fmul dword ptr [0xa0e7a8] */
	m->ecx = M32((DWORD)(m->edx + 0x14u));	/* 45bd55: mov ecx, dword ptr [edx + 0x14] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45bd58: lea eax, [eax + eax*4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 45bd5b: faddp st(1) */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45bd5d: lea eax, [eax + eax*4] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x1c8u));	/* 45bd60: fadd dword ptr [esp + 0x1c8] */
	m->eax = (DWORD)(m->ecx + m->eax*4 + 0xcu);	/* 45bd67: lea eax, [ecx + eax*4 + 0xc] */
	{ long double t = ST(0); FPUSH(t); }	/* 45bd6b: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x20u));	/* 45bd6d: fmul dword ptr [eax + 0x20] */
	{ long double t = ST(2); FPUSH(t); }	/* 45bd70: fld st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x10u));	/* 45bd72: fmul dword ptr [eax + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 45bd75: faddp st(1) */
	{ long double t = ST(3); FPUSH(t); }	/* 45bd77: fld st(3) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 45bd79: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 45bd7b: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x30u));	/* 45bd7d: fadd dword ptr [eax + 0x30] */
	MF((DWORD)(m->esp + 0xa0u)) = (float)ST(0); FPOP();	/* 45bd80: fstp dword ptr [esp + 0xa0] */
	{ long double t = ST(2); FPUSH(t); }	/* 45bd87: fld st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 45bd89: fmul dword ptr [eax + 4] */
	{ long double t = ST(1); FPUSH(t); }	/* 45bd8c: fld st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x24u));	/* 45bd8e: fmul dword ptr [eax + 0x24] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 45bd91: faddp st(1) */
	{ long double t = ST(2); FPUSH(t); }	/* 45bd93: fld st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x14u));	/* 45bd95: fmul dword ptr [eax + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 45bd98: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x34u));	/* 45bd9a: fadd dword ptr [eax + 0x34] */
	MF((DWORD)(m->esp + 0xa4u)) = (float)ST(0); FPOP();	/* 45bd9d: fstp dword ptr [esp + 0xa4] */
	{ long double t = ST(0); ST(0) = ST(2); ST(2) = t; }	/* 45bda4: fxch st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 45bda6: fmul dword ptr [eax + 8] */
	{ long double t = ST(0); ST(0) = ST(2); ST(2) = t; }	/* 45bda9: fxch st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x28u));	/* 45bdab: fmul dword ptr [eax + 0x28] */
	ST(2) = ST(2) + ST(0); FPOP();	/* 45bdae: faddp st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x18u));	/* 45bdb0: fmul dword ptr [eax + 0x18] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 45bdb3: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x38u));	/* 45bdb5: fadd dword ptr [eax + 0x38] */
	MF((DWORD)(m->esp + 0xa8u)) = (float)ST(0); FPOP();	/* 45bdb8: fstp dword ptr [esp + 0xa8] */
	m->edi = M32((DWORD)(m->edi + 0x0u));	/* 45bdbf: mov edi, dword ptr [edi] */
	m->eax = (DWORD)(m->edi + m->edi*4 + 0x0u);	/* 45bdc1: lea eax, [edi + edi*4] */
	m->edi = M32((DWORD)(m->esp + 0xa0u));	/* 45bdc4: mov edi, dword ptr [esp + 0xa0] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45bdcb: lea edx, [eax + eax*4] */
	m->eax = (DWORD)(m->ecx + m->edx*4 + 0xcu);	/* 45bdce: lea eax, [ecx + edx*4 + 0xc] */
	m->edx = M32((DWORD)(m->ebp + 0x140u));	/* 45bdd2: mov edx, dword ptr [ebp + 0x140] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 45bdd8: mov ecx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->esp + 0x48u)) = m->eax;	/* 45bddc: mov dword ptr [esp + 0x48], eax */
	m->eax = M32((DWORD)(m->esp + 0x54u));	/* 45bde0: mov eax, dword ptr [esp + 0x54] */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 45bde4: mov ecx, dword ptr [ecx + 8] */
	m->edx = M32((DWORD)(m->eax + m->edx*4 + 0x320u));	/* 45bde7: mov edx, dword ptr [eax + edx*4 + 0x320] */
	m->eax = (DWORD)(m->esi + 0xfffffff8u);	/* 45bdee: lea eax, [esi - 8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45bdf1: push eax */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 45bdf2: push -1 */
	M32((DWORD)(m->eax + 0x0u)) = 0x1u;	/* 45bdf4: mov dword ptr [eax], 1 */
	M32((DWORD)(m->esi + 0xfffffffcu)) = m->edx;	/* 45bdfa: mov dword ptr [esi - 4], edx */
	m->edx = m->esi;	/* 45bdfd: mov edx, esi */
	m->eax = M32((DWORD)(m->esp + 0x2c0u));	/* 45bdff: mov eax, dword ptr [esp + 0x2c0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45be06: push eax */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 45be07: push -1 */
	M32((DWORD)(m->edx + 0x0u)) = m->edi;	/* 45be09: mov dword ptr [edx], edi */
	m->edi = M32((DWORD)(m->esp + 0xb4u));	/* 45be0b: mov edi, dword ptr [esp + 0xb4] */
	M32((DWORD)(m->edx + 0x4u)) = m->edi;	/* 45be12: mov dword ptr [edx + 4], edi */
	m->edi = M32((DWORD)(m->esp + 0xb8u));	/* 45be15: mov edi, dword ptr [esp + 0xb8] */
	M32((DWORD)(m->edx + 0x8u)) = m->edi;	/* 45be1c: mov dword ptr [edx + 8], edi */
	M32((DWORD)(m->esi + 0xcu)) = m->ecx;	/* 45be1f: mov dword ptr [esi + 0xc], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 45be22: mov ecx, dword ptr [esp + 0x24] */
	m->edx = (DWORD)(m->esi + 0x10u);	/* 45be26: lea edx, [esi + 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45be29: add ecx, 0x10 */
	m->edi = M32((DWORD)(m->ecx + 0x0u));	/* 45be2c: mov edi, dword ptr [ecx] */
	M32((DWORD)(m->edx + 0x0u)) = m->edi;	/* 45be2e: mov dword ptr [edx], edi */
	m->edi = M32((DWORD)(m->ecx + 0x4u));	/* 45be30: mov edi, dword ptr [ecx + 4] */
	M32((DWORD)(m->edx + 0x4u)) = m->edi;	/* 45be33: mov dword ptr [edx + 4], edi */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 45be36: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 45be39: mov dword ptr [edx + 8], ecx */
	m->edx = M32((DWORD)(m->esp + 0x58u));	/* 45be3c: mov edx, dword ptr [esp + 0x58] */
	M32((DWORD)(m->esi + 0x1cu)) = m->edx;	/* 45be40: mov dword ptr [esi + 0x1c], edx */
	m->ecx = m->ebx;	/* 45be43: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x45be4au; native_call(m, 0x47ce50u);	/* 45be45: call 0x47ce50 */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 45be4a: mov ecx, dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 45be4e: mov edx, dword ptr [esp + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2b8u)));	/* 45be52: fld dword ptr [esp + 0x2b8] */
	M32((DWORD)(m->ecx + 0x0u)) = m->eax;	/* 45be59: mov dword ptr [ecx], eax */
	M32((DWORD)(m->ebp + 0x17cu)) = 0x38d1b717u;	/* 45be5b: mov dword ptr [ebp + 0x17c], 0x38d1b717 */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->edx + 0x2e08u));	/* 45be65: fdiv dword ptr [edx + 0x2e08] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x1a8u));	/* 45be6b: fadd dword ptr [ebp + 0x1a8] */
	MF((DWORD)(m->ebp + 0x1a8u)) = (float)ST(0);	/* 45be71: fst dword ptr [ebp + 0x1a8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 45be77: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45be7d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45be7f: test ah, 1 */
	if (!m->zf) goto L_45be8e;	/* 45be82: jne 0x45be8e */
	M32((DWORD)(m->ebp + 0x1a8u)) = 0x0u;	/* 45be84: mov dword ptr [ebp + 0x1a8], 0 */
L_45be8e:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 45be8e: mov eax, dword ptr [esp + 0x10] */
	M32((DWORD)(m->eax + 0x0u)) = 0x0u;	/* 45be92: mov dword ptr [eax], 0 */
L_45be98:
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 45be98: mov ecx, dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 45be9c: mov edx, dword ptr [ecx] */
	{ long long p_ = (long long)(int)m->edx * (int)0x4e8u; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edx = r_; }	/* 45be9e: imul edx, edx, 0x4e8 */
	m->eax = M32((DWORD)(m->edx + m->ebx*1 + 0x202ef38u));	/* 45bea4: mov eax, dword ptr [edx + ebx + 0x202ef38] */
	m->edi = (DWORD)(m->edx + m->ebx*1 + 0x202ef34u);	/* 45beab: lea edi, [edx + ebx + 0x202ef34] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45beb2: cmp eax, 1 */
	if (!m->zf) goto L_45bf3b;	/* 45beb5: jne 0x45bf3b */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 45bebb: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD v_ = 0xacu; m->esp -= 4; M32(m->esp) = v_; }	/* 45bebf: push 0xac */
	m->eax = M32((DWORD)(m->ecx + 0x4u));	/* 45bec4: mov eax, dword ptr [ecx + 4] */
	M32((DWORD)(m->edi + 0xb8u)) = m->eax;	/* 45bec7: mov dword ptr [edi + 0xb8], eax */
	m->eax = M32((DWORD)(m->ebx + 0xa24u));	/* 45becd: mov eax, dword ptr [ebx + 0xa24] */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 45bed3: mov ecx, dword ptr [ecx + 8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45bed6: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45bed7: push ecx */
	m->esp -= 4; M32(m->esp) = 0x45beddu; native_call(m, 0x46cbc0u);	/* 45bed8: call 0x46cbc0 */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 45bedd: mov edx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->edi + 0x6cu)) = m->eax;	/* 45bee1: mov dword ptr [edi + 0x6c], eax */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45bee4: add esp, 0xc */
	{ DWORD a_ = M32((DWORD)(m->edx + 0xcu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45bee7: cmp dword ptr [edx + 0xc], 1 */
	if (!m->zf) goto L_45befa;	/* 45beeb: jne 0x45befa */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x70u)));	/* 45beed: fld dword ptr [edi + 0x70] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x2b8u));	/* 45bef0: fsub dword ptr [esp + 0x2b8] */
	MF((DWORD)(m->edi + 0x74u)) = (float)ST(0); FPOP();	/* 45bef7: fstp dword ptr [edi + 0x74] */
L_45befa:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 45befa: mov eax, dword ptr [esp + 0x10] */
	m->ecx = (DWORD)(m->edi + 0x90u);	/* 45befe: lea ecx, [edi + 0x90] */
	{ DWORD a_ = m->eax, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45bf04: add eax, 0x10 */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 45bf07: mov edx, dword ptr [eax] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 45bf09: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 45bf0b: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 45bf0e: mov dword ptr [ecx + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 45bf11: mov edx, dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 45bf15: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 45bf18: mov dword ptr [ecx + 8], eax */
	m->eax = (DWORD)(m->edx + 0x10u);	/* 45bf1b: lea eax, [edx + 0x10] */
	m->ecx = (DWORD)(m->edi + 0x60u);	/* 45bf1e: lea ecx, [edi + 0x60] */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 45bf21: mov edx, dword ptr [eax] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 45bf23: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 45bf25: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 45bf28: mov dword ptr [ecx + 4], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 45bf2b: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 45bf2e: mov dword ptr [ecx + 8], eax */
	M32((DWORD)(m->edi + 0x9cu)) = 0x1u;	/* 45bf31: mov dword ptr [edi + 0x9c], 1 */
L_45bf3b:
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 45bf3b: mov edi, dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 45bf3f: mov edx, dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->esp + 0x7cu));	/* 45bf43: mov eax, dword ptr [esp + 0x7c] */
	{ DWORD a_ = m->edi, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 45bf47: add edi, 4 */
	{ DWORD a_ = m->edx, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45bf4a: add edx, 0x20 */
	{ DWORD a_ = m->esi, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 45bf4d: add esi, 0x28 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 45bf50: dec eax */
	M32((DWORD)(m->esp + 0x14u)) = m->edi;	/* 45bf51: mov dword ptr [esp + 0x14], edi */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 45bf55: mov dword ptr [esp + 0x10], edx */
	M32((DWORD)(m->esp + 0x7cu)) = m->eax;	/* 45bf59: mov dword ptr [esp + 0x7c], eax */
	if (!m->zf) goto L_45bb2f;	/* 45bf5d: jne 0x45bb2f */
L_45bf63:
	m->eax = M32((DWORD)(m->ebp + 0x3f0u));	/* 45bf63: mov eax, dword ptr [ebp + 0x3f0] */
	m->edi = M32((DWORD)(m->esp + 0x2b4u));	/* 45bf69: mov edi, dword ptr [esp + 0x2b4] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 45bf70: xor edx, edx */
	m->ecx = 0x1u;	/* 45bf72: mov ecx, 1 */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x4u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45bf77: test ah, 4 */
	if (!m->zf) goto L_45bfde;	/* 45bf7a: jne 0x45bfde */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x474u)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45bf7c: cmp dword ptr [ebp + 0x474], ecx */
	if (!m->zf) goto L_45bfde;	/* 45bf82: jne 0x45bfde */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x44cu)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45bf84: cmp dword ptr [ebp + 0x44c], ecx */
	if (m->zf) goto L_45bfa4;	/* 45bf8a: je 0x45bfa4 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x450u)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45bf8c: cmp dword ptr [ebp + 0x450], ecx */
	if (m->zf) goto L_45bfa4;	/* 45bf92: je 0x45bfa4 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x454u)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45bf94: cmp dword ptr [ebp + 0x454], ecx */
	if (m->zf) goto L_45bfa4;	/* 45bf9a: je 0x45bfa4 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x458u)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45bf9c: cmp dword ptr [ebp + 0x458], ecx */
	if (!m->zf) goto L_45bfde;	/* 45bfa2: jne 0x45bfde */
L_45bfa4:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2b8u)));	/* 45bfa4: fld dword ptr [esp + 0x2b8] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->ebp + 0x44u));	/* 45bfab: fdiv dword ptr [ebp + 0x44] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(m->ebp + 0x4acu));	/* 45bfae: fsubr dword ptr [ebp + 0x4ac] */
	MF((DWORD)(m->ebp + 0x4acu)) = (float)ST(0);	/* 45bfb4: fst dword ptr [ebp + 0x4ac] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45bfba: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45bfc0: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45bfc2: test ah, 1 */
	if (m->zf) goto L_45bfd3;	/* 45bfc5: je 0x45bfd3 */
	M32((DWORD)(m->ebp + 0x4acu)) = m->edx;	/* 45bfc7: mov dword ptr [ebp + 0x4ac], edx */
	M32((DWORD)(m->ebp + 0x4b4u)) = m->ecx;	/* 45bfcd: mov dword ptr [ebp + 0x4b4], ecx */
L_45bfd3:
	M32((DWORD)(m->ebp + 0x4b0u)) = m->edx;	/* 45bfd3: mov dword ptr [ebp + 0x4b0], edx */
	goto L_45c060;	/* 45bfd9: jmp 0x45c060 */
L_45bfde:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x4b0u)));	/* 45bfde: fld dword ptr [ebp + 0x4b0] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 45bfe4: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45bfea: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45bfec: test ah, 1 */
	if (m->zf) goto L_45c020;	/* 45bfef: je 0x45c020 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2b8u)));	/* 45bff1: fld dword ptr [esp + 0x2b8] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->ebp + 0x4cu));	/* 45bff8: fdiv dword ptr [ebp + 0x4c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x4b0u));	/* 45bffb: fadd dword ptr [ebp + 0x4b0] */
	MF((DWORD)(m->ebp + 0x4b0u)) = (float)ST(0);	/* 45c001: fst dword ptr [ebp + 0x4b0] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 45c007: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45c00d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45c00f: test ah, 0x41 */
	if (!m->zf) goto L_45c060;	/* 45c012: jne 0x45c060 */
	M32((DWORD)(m->ebp + 0x4b0u)) = 0x3f800000u;	/* 45c014: mov dword ptr [ebp + 0x4b0], 0x3f800000 */
	goto L_45c060;	/* 45c01e: jmp 0x45c060 */
L_45c020:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x4acu)));	/* 45c020: fld dword ptr [ebp + 0x4ac] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 45c026: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45c02c: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45c02e: test ah, 1 */
	if (m->zf) goto L_45c060;	/* 45c031: je 0x45c060 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2b8u)));	/* 45c033: fld dword ptr [esp + 0x2b8] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->ebp + 0x48u));	/* 45c03a: fdiv dword ptr [ebp + 0x48] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x4acu));	/* 45c03d: fadd dword ptr [ebp + 0x4ac] */
	MF((DWORD)(m->ebp + 0x4acu)) = (float)ST(0);	/* 45c043: fst dword ptr [ebp + 0x4ac] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 45c049: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45c04f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45c051: test ah, 0x41 */
	if (!m->zf) goto L_45c060;	/* 45c054: jne 0x45c060 */
	M32((DWORD)(m->ebp + 0x4acu)) = 0x3f800000u;	/* 45c056: mov dword ptr [ebp + 0x4ac], 0x3f800000 */
L_45c060:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x4acu)));	/* 45c060: fld dword ptr [ebp + 0x4ac] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a94f8u)); FPOP();	/* 45c066: fcomp dword ptr [0x4a94f8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45c06c: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45c06e: test ah, 0x41 */
	if (m->zf) goto L_45c07b;	/* 45c071: je 0x45c07b */
	M32((DWORD)(m->ebp + 0x4b8u)) = m->ecx;	/* 45c073: mov dword ptr [ebp + 0x4b8], ecx */
	goto L_45c081;	/* 45c079: jmp 0x45c081 */
L_45c07b:
	M32((DWORD)(m->ebp + 0x4b8u)) = m->edx;	/* 45c07b: mov dword ptr [ebp + 0x4b8], edx */
L_45c081:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x4b4u)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45c081: cmp dword ptr [ebp + 0x4b4], ecx */
	if (!m->zf) goto L_45c0a2;	/* 45c087: jne 0x45c0a2 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x4acu)));	/* 45c089: fld dword ptr [ebp + 0x4ac] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a942cu)); FPOP();	/* 45c08f: fcomp dword ptr [0x4a942c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45c095: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45c097: test ah, 1 */
	if (!m->zf) goto L_45c0a2;	/* 45c09a: jne 0x45c0a2 */
	M32((DWORD)(m->ebp + 0x4b4u)) = m->edx;	/* 45c09c: mov dword ptr [ebp + 0x4b4], edx */
L_45c0a2:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x14cu)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45c0a2: cmp dword ptr [ebp + 0x14c], ecx */
	if (!m->zf) goto L_45c523;	/* 45c0a8: jne 0x45c523 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x194u)));	/* 45c0ae: fld dword ptr [ebp + 0x194] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a942cu)); FPOP();	/* 45c0b4: fcomp dword ptr [0x4a942c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45c0ba: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45c0bc: test ah, 0x41 */
	if (!m->zf) goto L_45c0ee;	/* 45c0bf: jne 0x45c0ee */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x194u)));	/* 45c0c1: fld dword ptr [ebp + 0x194] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9534u)); FPOP();	/* 45c0c7: fcomp dword ptr [0x4a9534] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45c0cd: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45c0cf: test ah, 1 */
	if (m->zf) goto L_45c0e2;	/* 45c0d2: je 0x45c0e2 */
	m->ecx = M32((DWORD)(m->ebp + 0x194u));	/* 45c0d4: mov ecx, dword ptr [ebp + 0x194] */
	M32((DWORD)(m->ebp + 0x4a4u)) = m->ecx;	/* 45c0da: mov dword ptr [ebp + 0x4a4], ecx */
	goto L_45c0f8;	/* 45c0e0: jmp 0x45c0f8 */
L_45c0e2:
	M32((DWORD)(m->ebp + 0x4a4u)) = 0x40400000u;	/* 45c0e2: mov dword ptr [ebp + 0x4a4], 0x40400000 */
	goto L_45c0f8;	/* 45c0ec: jmp 0x45c0f8 */
L_45c0ee:
	M32((DWORD)(m->ebp + 0x4a4u)) = 0x3f000000u;	/* 45c0ee: mov dword ptr [ebp + 0x4a4], 0x3f000000 */
L_45c0f8:
	{ DWORD a_ = m->edi, b_ = M32((DWORD)(m->ebx + 0x202e8d8u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45c0f8: cmp edi, dword ptr [ebx + 0x202e8d8] */
	if (m->zf) goto L_45c3ed;	/* 45c0fe: je 0x45c3ed */
	m->eax = M32((DWORD)(m->ebp + 0x550u));	/* 45c104: mov eax, dword ptr [ebp + 0x550] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45c10a: test eax, eax */
	if (!m->zf) goto L_45c3ed;	/* 45c10c: jne 0x45c3ed */
	m->eax = M32((DWORD)(m->ebp + 0x3f0u));	/* 45c112: mov eax, dword ptr [ebp + 0x3f0] */
	m->edx = M32((DWORD)(m->ebp + 0x4a4u));	/* 45c118: mov edx, dword ptr [ebp + 0x4a4] */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x2u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45c11e: test ah, 2 */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 45c121: mov dword ptr [esp + 0x28], edx */
	if (m->zf) goto L_45c154;	/* 45c125: je 0x45c154 */
	m->eax = M32((DWORD)(m->ebx + 0x202e8d4u));	/* 45c127: mov eax, dword ptr [ebx + 0x202e8d4] */
	m->edx = M32((DWORD)(m->ebp + 0x8u));	/* 45c12d: mov edx, dword ptr [ebp + 8] */
	m->ecx = m->eax;	/* 45c130: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45c132: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45c135: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45c137: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45c13a: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45c13c: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45c13f: add ecx, eax */
	{ DWORD a_ = m->edx, b_ = M32((DWORD)(m->ebx + m->ecx*8 + 0x1cd93b0u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45c141: cmp edx, dword ptr [ebx + ecx*8 + 0x1cd93b0] */
	if (m->sf != m->of) goto L_45c154;	/* 45c148: jl 0x45c154 */
	M32((DWORD)(m->esp + 0x2cu)) = 0x3d808081u;	/* 45c14a: mov dword ptr [esp + 0x2c], 0x3d808081 */
	goto L_45c181;	/* 45c152: jmp 0x45c181 */
L_45c154:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x120u)));	/* 45c154: fld dword ptr [ebp + 0x120] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9534u)); FPOP();	/* 45c15a: fcomp dword ptr [0x4a9534] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45c160: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45c162: test ah, 0x41 */
	if (m->zf) goto L_45c179;	/* 45c165: je 0x45c179 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x120u)));	/* 45c167: fld dword ptr [ebp + 0x120] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9438u));	/* 45c16d: fmul dword ptr [0x4a9438] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 45c173: fstp dword ptr [esp + 0x2c] */
	goto L_45c181;	/* 45c177: jmp 0x45c181 */
L_45c179:
	M32((DWORD)(m->esp + 0x2cu)) = 0x3f800000u;	/* 45c179: mov dword ptr [esp + 0x2c], 0x3f800000 */
L_45c181:
	{ DWORD a_ = m->edi, b_ = M32((DWORD)(m->ebx + 0x202e8d4u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45c181: cmp edi, dword ptr [ebx + 0x202e8d4] */
	if (!m->zf) goto L_45c197;	/* 45c187: jne 0x45c197 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 45c189: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 45c18d: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 45c193: fstp dword ptr [esp + 0x2c] */
L_45c197:
	m->ecx = M32((DWORD)(m->esp + 0xc0u));	/* 45c197: mov ecx, dword ptr [esp + 0xc0] */
	M32((DWORD)(m->esp + 0x50u)) = 0x0u;	/* 45c19e: mov dword ptr [esp + 0x50], 0 */
	m->eax = M32((DWORD)(m->ecx + 0x13d0u));	/* 45c1a6: mov eax, dword ptr [ecx + 0x13d0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45c1ac: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_45c2c1;	/* 45c1ae: jle 0x45c2c1 */
	m->edi = (DWORD)(m->ecx + 0x12d0u);	/* 45c1b4: lea edi, [ecx + 0x12d0] */
L_45c1ba:
	{ DWORD a_ = M32((DWORD)(m->edi + 0x80u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45c1ba: cmp dword ptr [edi + 0x80], 1 */
	if (!m->zf) goto L_45c1da;	/* 45c1c1: jne 0x45c1da */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x178u)));	/* 45c1c3: fld dword ptr [ebp + 0x178] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45c1c9: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45c1cf: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45c1d1: test ah, 0x41 */
	if (!m->zf) goto L_45c2a7;	/* 45c1d4: jne 0x45c2a7 */
L_45c1da:
	m->eax = M32((DWORD)(0xa1efb8u));	/* 45c1da: mov eax, dword ptr [0xa1efb8] */
	m->edx = M32((DWORD)(m->ebp + 0x2538u));	/* 45c1df: mov edx, dword ptr [ebp + 0x2538] */
	m->ecx = m->eax;	/* 45c1e5: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 45c1e7: and ecx, 0xfff */
	m->ecx = M32((DWORD)(m->ecx*4 + 0xa106f8u));	/* 45c1ed: mov ecx, dword ptr [ecx*4 + 0xa106f8] */
	{ DWORD a_ = m->ecx, b_ = 0x7u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 45c1f4: and ecx, 7 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 45c1f7: inc eax */
	M32((DWORD)(0xa1efb8u)) = m->eax;	/* 45c1f8: mov dword ptr [0xa1efb8], eax */
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 45c1fd: mov eax, dword ptr [edi] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45c1ff: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45c202: lea eax, [eax + eax*4] */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45c205: shl eax, 2 */
	m->esi = (DWORD)(m->eax + m->edx*1 + 0xcu);	/* 45c208: lea esi, [eax + edx + 0xc] */
	m->eax = (DWORD)(m->eax + m->edx*1 + 0x58u);	/* 45c20c: lea eax, [eax + edx + 0x58] */
	m->edx = M32((DWORD)(m->esp + 0x80u));	/* 45c210: mov edx, dword ptr [esp + 0x80] */
	m->edx = M32((DWORD)(m->edx + 0x17fcu));	/* 45c217: mov edx, dword ptr [edx + 0x17fc] */
	M32((DWORD)(m->esp + 0x114u)) = m->ecx;	/* 45c21d: mov dword ptr [esp + 0x114], ecx */
	{ DWORD a_ = m->edx, b_ = 0x5u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45c224: add edx, 5 */
	M32((DWORD)(m->esp + 0x110u)) = m->edx;	/* 45c227: mov dword ptr [esp + 0x110], edx */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 45c22e: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x118u)) = m->ecx;	/* 45c230: mov dword ptr [esp + 0x118], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 45c237: mov edx, dword ptr [eax + 4] */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 45c23a: mov ecx, dword ptr [esp + 0x28] */
	M32((DWORD)(m->esp + 0x11cu)) = m->edx;	/* 45c23e: mov dword ptr [esp + 0x11c], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 45c245: mov eax, dword ptr [eax + 8] */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 45c248: mov edx, dword ptr [esp + 0x2c] */
	M32((DWORD)(m->esp + 0x120u)) = m->eax;	/* 45c24c: mov dword ptr [esp + 0x120], eax */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 45c253: mov eax, dword ptr [esp + 0x30] */
	M32((DWORD)(m->esp + 0x124u)) = m->ecx;	/* 45c257: mov dword ptr [esp + 0x124], ecx */
	m->ecx = (DWORD)(m->esp + 0x110u);	/* 45c25e: lea ecx, [esp + 0x110] */
	M32((DWORD)(m->esp + 0x12cu)) = m->eax;	/* 45c265: mov dword ptr [esp + 0x12c], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45c26c: xor eax, eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45c26e: push ecx */
	m->ecx = m->ebx;	/* 45c26f: mov ecx, ebx */
	M32((DWORD)(m->esp + 0x12cu)) = m->edx;	/* 45c271: mov dword ptr [esp + 0x12c], edx */
	M32((DWORD)(m->esp + 0x134u)) = m->esi;	/* 45c278: mov dword ptr [esp + 0x134], esi */
	M32((DWORD)(m->esp + 0x138u)) = m->eax;	/* 45c27f: mov dword ptr [esp + 0x138], eax */
	M32((DWORD)(m->esp + 0x13cu)) = m->eax;	/* 45c286: mov dword ptr [esp + 0x13c], eax */
	M32((DWORD)(m->esp + 0x140u)) = m->eax;	/* 45c28d: mov dword ptr [esp + 0x140], eax */
	M32((DWORD)(m->esp + 0x144u)) = m->eax;	/* 45c294: mov dword ptr [esp + 0x144], eax */
	m->esp -= 4; M32(m->esp) = 0x45c2a0u; native_call(m, 0x479950u);	/* 45c29b: call 0x479950 */
	m->ecx = M32((DWORD)(m->esp + 0xc0u));	/* 45c2a0: mov ecx, dword ptr [esp + 0xc0] */
L_45c2a7:
	m->eax = M32((DWORD)(m->esp + 0x50u));	/* 45c2a7: mov eax, dword ptr [esp + 0x50] */
	m->edx = M32((DWORD)(m->ecx + 0x13d0u));	/* 45c2ab: mov edx, dword ptr [ecx + 0x13d0] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 45c2b1: inc eax */
	{ DWORD a_ = m->edi, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 45c2b2: add edi, 4 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45c2b5: cmp eax, edx */
	M32((DWORD)(m->esp + 0x50u)) = m->eax;	/* 45c2b7: mov dword ptr [esp + 0x50], eax */
	if (m->sf != m->of) goto L_45c1ba;	/* 45c2bb: jl 0x45c1ba */
L_45c2c1:
	m->edx = M32((DWORD)(m->esp + 0x80u));	/* 45c2c1: mov edx, dword ptr [esp + 0x80] */
	M32((DWORD)(m->esp + 0x50u)) = 0x0u;	/* 45c2c8: mov dword ptr [esp + 0x50], 0 */
	m->eax = M32((DWORD)(m->edx + 0x17f0u));	/* 45c2d0: mov eax, dword ptr [edx + 0x17f0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45c2d6: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_45c3ed;	/* 45c2d8: jle 0x45c3ed */
	m->eax = m->edx;	/* 45c2de: mov eax, edx */
	m->edi = (DWORD)(m->eax + 0x16f0u);	/* 45c2e0: lea edi, [eax + 0x16f0] */
L_45c2e6:
	{ DWORD a_ = M32((DWORD)(m->edi + 0x80u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45c2e6: cmp dword ptr [edi + 0x80], 1 */
	if (!m->zf) goto L_45c306;	/* 45c2ed: jne 0x45c306 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x178u)));	/* 45c2ef: fld dword ptr [ebp + 0x178] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45c2f5: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45c2fb: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45c2fd: test ah, 0x41 */
	if (!m->zf) goto L_45c3cc;	/* 45c300: jne 0x45c3cc */
L_45c306:
	m->eax = M32((DWORD)(0xa1efb8u));	/* 45c306: mov eax, dword ptr [0xa1efb8] */
	m->edx = M32((DWORD)(m->ebp + 0x3508u));	/* 45c30b: mov edx, dword ptr [ebp + 0x3508] */
	m->ecx = m->eax;	/* 45c311: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 45c313: and ecx, 0xfff */
	m->ecx = M32((DWORD)(m->ecx*4 + 0xa106f8u));	/* 45c319: mov ecx, dword ptr [ecx*4 + 0xa106f8] */
	{ DWORD a_ = m->ecx, b_ = 0x7u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 45c320: and ecx, 7 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 45c323: inc eax */
	M32((DWORD)(0xa1efb8u)) = m->eax;	/* 45c324: mov dword ptr [0xa1efb8], eax */
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 45c329: mov eax, dword ptr [edi] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45c32b: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45c32e: lea eax, [eax + eax*4] */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45c331: shl eax, 2 */
	m->esi = (DWORD)(m->eax + m->edx*1 + 0xcu);	/* 45c334: lea esi, [eax + edx + 0xc] */
	m->eax = (DWORD)(m->eax + m->edx*1 + 0x58u);	/* 45c338: lea eax, [eax + edx + 0x58] */
	m->edx = M32((DWORD)(m->esp + 0x80u));	/* 45c33c: mov edx, dword ptr [esp + 0x80] */
	m->edx = M32((DWORD)(m->edx + 0x17fcu));	/* 45c343: mov edx, dword ptr [edx + 0x17fc] */
	M32((DWORD)(m->esp + 0x114u)) = m->ecx;	/* 45c349: mov dword ptr [esp + 0x114], ecx */
	{ DWORD a_ = m->edx, b_ = 0x5u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45c350: add edx, 5 */
	M32((DWORD)(m->esp + 0x110u)) = m->edx;	/* 45c353: mov dword ptr [esp + 0x110], edx */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 45c35a: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x118u)) = m->ecx;	/* 45c35c: mov dword ptr [esp + 0x118], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 45c363: mov edx, dword ptr [eax + 4] */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 45c366: mov ecx, dword ptr [esp + 0x28] */
	M32((DWORD)(m->esp + 0x11cu)) = m->edx;	/* 45c36a: mov dword ptr [esp + 0x11c], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 45c371: mov eax, dword ptr [eax + 8] */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 45c374: mov edx, dword ptr [esp + 0x2c] */
	M32((DWORD)(m->esp + 0x120u)) = m->eax;	/* 45c378: mov dword ptr [esp + 0x120], eax */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 45c37f: mov eax, dword ptr [esp + 0x30] */
	M32((DWORD)(m->esp + 0x124u)) = m->ecx;	/* 45c383: mov dword ptr [esp + 0x124], ecx */
	m->ecx = (DWORD)(m->esp + 0x110u);	/* 45c38a: lea ecx, [esp + 0x110] */
	M32((DWORD)(m->esp + 0x12cu)) = m->eax;	/* 45c391: mov dword ptr [esp + 0x12c], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45c398: xor eax, eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45c39a: push ecx */
	m->ecx = m->ebx;	/* 45c39b: mov ecx, ebx */
	M32((DWORD)(m->esp + 0x12cu)) = m->edx;	/* 45c39d: mov dword ptr [esp + 0x12c], edx */
	M32((DWORD)(m->esp + 0x134u)) = m->esi;	/* 45c3a4: mov dword ptr [esp + 0x134], esi */
	M32((DWORD)(m->esp + 0x138u)) = m->eax;	/* 45c3ab: mov dword ptr [esp + 0x138], eax */
	M32((DWORD)(m->esp + 0x13cu)) = m->eax;	/* 45c3b2: mov dword ptr [esp + 0x13c], eax */
	M32((DWORD)(m->esp + 0x140u)) = m->eax;	/* 45c3b9: mov dword ptr [esp + 0x140], eax */
	M32((DWORD)(m->esp + 0x144u)) = m->eax;	/* 45c3c0: mov dword ptr [esp + 0x144], eax */
	m->esp -= 4; M32(m->esp) = 0x45c3ccu; native_call(m, 0x479950u);	/* 45c3c7: call 0x479950 */
L_45c3cc:
	m->edx = M32((DWORD)(m->esp + 0x80u));	/* 45c3cc: mov edx, dword ptr [esp + 0x80] */
	m->eax = M32((DWORD)(m->esp + 0x50u));	/* 45c3d3: mov eax, dword ptr [esp + 0x50] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 45c3d7: inc eax */
	{ DWORD a_ = m->edi, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 45c3d8: add edi, 4 */
	m->ecx = M32((DWORD)(m->edx + 0x17f0u));	/* 45c3db: mov ecx, dword ptr [edx + 0x17f0] */
	M32((DWORD)(m->esp + 0x50u)) = m->eax;	/* 45c3e1: mov dword ptr [esp + 0x50], eax */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45c3e5: cmp eax, ecx */
	if (m->sf != m->of) goto L_45c2e6;	/* 45c3e7: jl 0x45c2e6 */
L_45c3ed:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2b8u)));	/* 45c3ed: fld dword ptr [esp + 0x2b8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x4a8u));	/* 45c3f4: fadd dword ptr [ebp + 0x4a8] */
	m->edi = M32((DWORD)(m->esp + 0x2b4u));	/* 45c3fa: mov edi, dword ptr [esp + 0x2b4] */
	MF((DWORD)(m->ebp + 0x4a8u)) = (float)ST(0);	/* 45c401: fst dword ptr [ebp + 0x4a8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9704u)); FPOP();	/* 45c407: fcomp dword ptr [0x4a9704] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45c40d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45c40f: test ah, 0x41 */
	if (!m->zf) goto L_45c523;	/* 45c412: jne 0x45c523 */
	{ DWORD a_ = m->edi, b_ = M32((DWORD)(m->ebx + 0x202e8d4u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45c418: cmp edi, dword ptr [ebx + 0x202e8d4] */
	if (!m->zf) goto L_45c456;	/* 45c41e: jne 0x45c456 */
	m->ecx = M32((DWORD)(m->ebp + 0x4b8u));	/* 45c420: mov ecx, dword ptr [ebp + 0x4b8] */
	m->eax = 0x1u;	/* 45c426: mov eax, 1 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45c42b: cmp ecx, eax */
	if (m->zf) goto L_45c437;	/* 45c42d: je 0x45c437 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x4b4u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45c42f: cmp dword ptr [ebp + 0x4b4], eax */
	if (!m->zf) goto L_45c456;	/* 45c435: jne 0x45c456 */
L_45c437:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x3fcu)));	/* 45c437: fld dword ptr [ebp + 0x3fc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45c43d: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45c443: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45c445: test ah, 0x41 */
	if (m->zf) goto L_45c456;	/* 45c448: je 0x45c456 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 45c44a: push 0x64 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 45c44c: push 0x10 */
	m->esp -= 4; M32(m->esp) = 0x45c453u; native_call(m, 0x456e50u);	/* 45c44e: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45c453: add esp, 8 */
L_45c456:
	{ DWORD a_ = m->edi, b_ = M32((DWORD)(m->ebx + 0x202e8dcu)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45c456: cmp edi, dword ptr [ebx + 0x202e8dc] */
	if (m->zf) goto L_45c519;	/* 45c45c: je 0x45c519 */
	{ DWORD a_ = m->edi, b_ = M32((DWORD)(m->ebx + 0x202e8d4u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45c462: cmp edi, dword ptr [ebx + 0x202e8d4] */
	if (!m->zf) goto L_45c4ae;	/* 45c468: jne 0x45c4ae */
	m->eax = M32((DWORD)(m->ebp + 0x474u));	/* 45c46a: mov eax, dword ptr [ebp + 0x474] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45c470: test eax, eax */
	if (!m->zf) goto L_45c491;	/* 45c472: jne 0x45c491 */
	m->eax = M32((DWORD)(m->esp + 0x80u));	/* 45c474: mov eax, dword ptr [esp + 0x80] */
	{ DWORD v_ = 0x28u; m->esp -= 4; M32(m->esp) = v_; }	/* 45c47b: push 0x28 */
	m->ecx = M32((DWORD)(m->eax + 0x17fcu));	/* 45c47d: mov ecx, dword ptr [eax + 0x17fc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45c483: push ecx */
	m->esp -= 4; M32(m->esp) = 0x45c489u; native_call(m, 0x456e50u);	/* 45c484: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45c489: add esp, 8 */
	goto L_45c519;	/* 45c48c: jmp 0x45c519 */
L_45c491:
	m->edx = M32((DWORD)(m->esp + 0x80u));	/* 45c491: mov edx, dword ptr [esp + 0x80] */
	{ DWORD v_ = 0x50u; m->esp -= 4; M32(m->esp) = v_; }	/* 45c498: push 0x50 */
	m->eax = M32((DWORD)(m->edx + 0x17fcu));	/* 45c49a: mov eax, dword ptr [edx + 0x17fc] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45c4a0: add eax, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45c4a3: push eax */
	m->esp -= 4; M32(m->esp) = 0x45c4a9u; native_call(m, 0x456e50u);	/* 45c4a4: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45c4a9: add esp, 8 */
	goto L_45c519;	/* 45c4ac: jmp 0x45c519 */
L_45c4ae:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x1a4u)));	/* 45c4ae: fld dword ptr [ebp + 0x1a4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45c4b4: fcomp dword ptr [0x4a93e8] */
	{ DWORD v_ = 0x47435000u; m->esp -= 4; M32(m->esp) = v_; }	/* 45c4ba: push 0x47435000 */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45c4bf: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45c4c1: test ah, 0x41 */
	if (m->zf) goto L_45c4eb;	/* 45c4c4: je 0x45c4eb */
	m->ecx = (DWORD)(m->ebx + 0x20f397cu);	/* 45c4c6: lea ecx, [ebx + 0x20f397c] */
	m->eax = (DWORD)(m->ebp + 0x180u);	/* 45c4cc: lea eax, [ebp + 0x180] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45c4d2: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45c4d3: push eax */
	m->eax = M32((DWORD)(m->esp + 0x8cu));	/* 45c4d4: mov eax, dword ptr [esp + 0x8c] */
	m->edx = (DWORD)(m->ebx + 0x20f3970u);	/* 45c4db: lea edx, [ebx + 0x20f3970] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45c4e1: push edx */
	m->ecx = M32((DWORD)(m->eax + 0x17fcu));	/* 45c4e2: mov ecx, dword ptr [eax + 0x17fc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45c4e8: push ecx */
	goto L_45c511;	/* 45c4e9: jmp 0x45c511 */
L_45c4eb:
	m->ecx = M32((DWORD)(m->esp + 0x84u));	/* 45c4eb: mov ecx, dword ptr [esp + 0x84] */
	m->edx = (DWORD)(m->ebx + 0x20f397cu);	/* 45c4f2: lea edx, [ebx + 0x20f397c] */
	m->eax = (DWORD)(m->ebp + 0x180u);	/* 45c4f8: lea eax, [ebp + 0x180] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45c4fe: push edx */
	m->edx = M32((DWORD)(m->ecx + 0x17fcu));	/* 45c4ff: mov edx, dword ptr [ecx + 0x17fc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45c505: push eax */
	m->eax = (DWORD)(m->ebx + 0x20f3970u);	/* 45c506: lea eax, [ebx + 0x20f3970] */
	{ DWORD a_ = m->edx, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45c50c: add edx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45c50f: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45c510: push edx */
L_45c511:
	m->esp -= 4; M32(m->esp) = 0x45c516u; native_call(m, 0x456ed0u);	/* 45c511: call 0x456ed0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45c516: add esp, 0x14 */
L_45c519:
	M32((DWORD)(m->ebp + 0x4a8u)) = 0x0u;	/* 45c519: mov dword ptr [ebp + 0x4a8], 0 */
L_45c523:
	m->eax = M32((DWORD)(m->ebp + 0x14cu));	/* 45c523: mov eax, dword ptr [ebp + 0x14c] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 45c529: dec eax */
	if (m->zf) goto L_45c642;	/* 45c52a: je 0x45c642 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 45c530: dec eax */
	if (m->zf) goto L_45c5f8;	/* 45c531: je 0x45c5f8 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 45c537: dec eax */
	if (!m->zf) goto L_45c546;	/* 45c538: jne 0x45c546 */
	m->eax = M32((DWORD)(m->ebp + 0x124u));	/* 45c53a: mov eax, dword ptr [ebp + 0x124] */
	M32((DWORD)(m->ebp + 0x120u)) = m->eax;	/* 45c540: mov dword ptr [ebp + 0x120], eax */
L_45c546:
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 45c546: xor esi, esi */
L_45c548:
	M32((DWORD)(m->ebp + 0x4ecu)) = m->esi;	/* 45c548: mov dword ptr [ebp + 0x4ec], esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x17cu)));	/* 45c54e: fld dword ptr [ebp + 0x17c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45c554: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45c55a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45c55c: test ah, 0x41 */
	if (!m->zf) goto L_45c588;	/* 45c55f: jne 0x45c588 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x17cu)));	/* 45c561: fld dword ptr [ebp + 0x17c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a942cu)); FPOP();	/* 45c567: fcomp dword ptr [0x4a942c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45c56d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45c56f: test ah, 1 */
	if (m->zf) goto L_45c588;	/* 45c572: je 0x45c588 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a942cu)));	/* 45c574: fld dword ptr [0x4a942c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x17cu));	/* 45c57a: fsub dword ptr [ebp + 0x17c] */
	ST(0) = ST(0) + ST(0);	/* 45c580: fadd st(0), st(0) */
	MF((DWORD)(m->ebp + 0x4ecu)) = (float)ST(0); FPOP();	/* 45c582: fstp dword ptr [ebp + 0x4ec] */
L_45c588:
	m->eax = M32((DWORD)(m->ebp + 0x3f0u));	/* 45c588: mov eax, dword ptr [ebp + 0x3f0] */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x2u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45c58e: test ah, 2 */
	if (m->zf) goto L_45cda6;	/* 45c591: je 0x45cda6 */
	m->eax = M32((DWORD)(m->ebx + 0x202e8d4u));	/* 45c597: mov eax, dword ptr [ebx + 0x202e8d4] */
	m->edx = M32((DWORD)(m->ebp + 0x8u));	/* 45c59d: mov edx, dword ptr [ebp + 8] */
	m->ecx = m->eax;	/* 45c5a0: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45c5a2: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45c5a5: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45c5a7: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45c5aa: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45c5ac: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45c5af: add ecx, eax */
	{ DWORD a_ = m->edx, b_ = M32((DWORD)(m->ebx + m->ecx*8 + 0x1cd93b0u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45c5b1: cmp edx, dword ptr [ebx + ecx*8 + 0x1cd93b0] */
	if (m->sf != m->of) goto L_45cda6;	/* 45c5b8: jl 0x45cda6 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x4a4u)));	/* 45c5be: fld dword ptr [ebp + 0x4a4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 45c5c4: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45c5ca: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45c5cc: test ah, 0x41 */
	if (!m->zf) goto L_45cdcc;	/* 45c5cf: jne 0x45cdcc */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x4a4u)));	/* 45c5d5: fld dword ptr [ebp + 0x4a4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 45c5db: fsub dword ptr [0x4a9424] */
L_45c5e1:
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94f8u));	/* 45c5e1: fmul dword ptr [0x4a94f8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x4ecu));	/* 45c5e7: fadd dword ptr [ebp + 0x4ec] */
	MF((DWORD)(m->ebp + 0x4ecu)) = (float)ST(0); FPOP();	/* 45c5ed: fstp dword ptr [ebp + 0x4ec] */
	goto L_45cdcc;	/* 45c5f3: jmp 0x45cdcc */
L_45c5f8:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x150u)));	/* 45c5f8: fld dword ptr [ebp + 0x150] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93fcu)); FPOP();	/* 45c5fe: fcomp dword ptr [0x4a93fc] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45c604: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45c606: test ah, 0x41 */
	if (!m->zf) goto L_45c546;	/* 45c609: jne 0x45c546 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 45c60f: xor esi, esi */
	M32((DWORD)(m->ebp + 0x14cu)) = 0x3u;	/* 45c611: mov dword ptr [ebp + 0x14c], 3 */
	M32((DWORD)(m->ebp + 0x150u)) = m->esi;	/* 45c61b: mov dword ptr [ebp + 0x150], esi */
	m->eax = M32((DWORD)(m->ebx + 0x202e8d4u));	/* 45c621: mov eax, dword ptr [ebx + 0x202e8d4] */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45c627: cmp edi, eax */
	if (!m->zf) goto L_45c548;	/* 45c629: jne 0x45c548 */
	m->ecx = M32((DWORD)(0x4b4414u));	/* 45c62f: mov ecx, dword ptr [0x4b4414] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45c635: push ecx */
	m->ecx = m->ebx;	/* 45c636: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x45c63du; native_call(m, 0x45c63du + M32(0x45c639u));	/* 0x473780 unless the patch DLL retargets it */	/* 45c638: call 0x473780 */
	goto L_45c548;	/* 45c63d: jmp 0x45c548 */
L_45c642:
	m->eax = M32((DWORD)(m->ebp + 0x128u));	/* 45c642: mov eax, dword ptr [ebp + 0x128] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 45c648: xor esi, esi */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45c64a: cmp eax, esi */
	if (!m->zf && m->sf == m->of) goto L_45cd6c;	/* 45c64c: jg 0x45cd6c */
	m->eax = (DWORD)(m->ebp + 0x154u);	/* 45c652: lea eax, [ebp + 0x154] */
	m->edx = (DWORD)(m->ebp + 0x4e0u);	/* 45c658: lea edx, [ebp + 0x4e0] */
	m->ecx = m->eax;	/* 45c65e: mov ecx, eax */
	M32((DWORD)(m->esp + 0x110u)) = 0x3u;	/* 45c660: mov dword ptr [esp + 0x110], 3 */
	M32((DWORD)(m->esp + 0x114u)) = m->esi;	/* 45c66b: mov dword ptr [esp + 0x114], esi */
	M32((DWORD)(m->esp + 0x130u)) = m->esi;	/* 45c672: mov dword ptr [esp + 0x130], esi */
	m->edi = M32((DWORD)(m->ecx + 0x0u));	/* 45c679: mov edi, dword ptr [ecx] */
	M32((DWORD)(m->esp + 0x134u)) = m->esi;	/* 45c67b: mov dword ptr [esp + 0x134], esi */
	M32((DWORD)(m->edx + 0x0u)) = m->edi;	/* 45c682: mov dword ptr [edx], edi */
	M32((DWORD)(m->esp + 0x138u)) = m->esi;	/* 45c684: mov dword ptr [esp + 0x138], esi */
	m->edi = M32((DWORD)(m->ecx + 0x4u));	/* 45c68b: mov edi, dword ptr [ecx + 4] */
	M32((DWORD)(m->esp + 0x13cu)) = m->esi;	/* 45c68e: mov dword ptr [esp + 0x13c], esi */
	M32((DWORD)(m->edx + 0x4u)) = m->edi;	/* 45c695: mov dword ptr [edx + 4], edi */
	M32((DWORD)(m->esp + 0x140u)) = m->esi;	/* 45c698: mov dword ptr [esp + 0x140], esi */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 45c69f: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 45c6a2: mov dword ptr [edx + 8], ecx */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 45c6a5: mov edx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x118u)) = m->edx;	/* 45c6a7: mov dword ptr [esp + 0x118], edx */
	m->ecx = M32((DWORD)(m->eax + 0x4u));	/* 45c6ae: mov ecx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x11cu)) = m->ecx;	/* 45c6b1: mov dword ptr [esp + 0x11c], ecx */
	m->edx = M32((DWORD)(m->eax + 0x8u));	/* 45c6b8: mov edx, dword ptr [eax + 8] */
	m->eax = (DWORD)(m->ebp + 0x180u);	/* 45c6bb: lea eax, [ebp + 0x180] */
	M32((DWORD)(m->esp + 0x120u)) = m->edx;	/* 45c6c1: mov dword ptr [esp + 0x120], edx */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 45c6c8: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x124u)) = m->ecx;	/* 45c6ca: mov dword ptr [esp + 0x124], ecx */
	m->ecx = (DWORD)(m->esp + 0x110u);	/* 45c6d1: lea ecx, [esp + 0x110] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 45c6d8: mov edx, dword ptr [eax + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45c6db: push ecx */
	m->ecx = m->ebx;	/* 45c6dc: mov ecx, ebx */
	M32((DWORD)(m->esp + 0x12cu)) = m->edx;	/* 45c6de: mov dword ptr [esp + 0x12c], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 45c6e5: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x130u)) = m->eax;	/* 45c6e8: mov dword ptr [esp + 0x130], eax */
	m->esp -= 4; M32(m->esp) = 0x45c6f4u; native_call(m, 0x479950u);	/* 45c6ef: call 0x479950 */
	m->esi = 0x14u;	/* 45c6f4: mov esi, 0x14 */
L_45c6f9:
	m->ecx = M32((DWORD)(0xa1efb8u));	/* 45c6f9: mov ecx, dword ptr [0xa1efb8] */
	m->edi = 0xe10u;	/* 45c6ff: mov edi, 0xe10 */
	m->edx = m->ecx;	/* 45c704: mov edx, ecx */
	M32((DWORD)(m->esp + 0x28u)) = 0x0u;	/* 45c706: mov dword ptr [esp + 0x28], 0 */
	{ DWORD a_ = m->edx, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 45c70e: and edx, 0xfff */
	M32((DWORD)(m->esp + 0x2cu)) = 0x0u;	/* 45c714: mov dword ptr [esp + 0x2c], 0 */
	M32((DWORD)(m->esp + 0x30u)) = 0x459c4000u;	/* 45c71c: mov dword ptr [esp + 0x30], 0x459c4000 */
	m->eax = M32((DWORD)(m->edx*4 + 0xa106f8u));	/* 45c724: mov eax, dword ptr [edx*4 + 0xa106f8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 45c72b: xor edx, edx */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->edi; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 45c72d: div edi */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 45c72f: inc ecx */
	M32((DWORD)(0xa1efb8u)) = m->ecx;	/* 45c730: mov dword ptr [0xa1efb8], ecx */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 45c736: lea ecx, [esp + 0x28] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45c73a: push edx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45c73b: push 1 */
	m->esp -= 4; M32(m->esp) = 0x45c742u; native_call(m, 0x4677c0u);	/* 45c73d: call 0x4677c0 */
	m->ecx = M32((DWORD)(0xa1efb8u));	/* 45c742: mov ecx, dword ptr [0xa1efb8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 45c748: xor edx, edx */
	m->eax = m->ecx;	/* 45c74a: mov eax, ecx */
	{ DWORD a_ = m->eax, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45c74c: and eax, 0xfff */
	m->eax = M32((DWORD)(m->eax*4 + 0xa106f8u));	/* 45c751: mov eax, dword ptr [eax*4 + 0xa106f8] */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->edi; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 45c758: div edi */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 45c75a: inc ecx */
	M32((DWORD)(0xa1efb8u)) = m->ecx;	/* 45c75b: mov dword ptr [0xa1efb8], ecx */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 45c761: lea ecx, [esp + 0x28] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45c765: push edx */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 45c766: push 2 */
	m->esp -= 4; M32(m->esp) = 0x45c76du; native_call(m, 0x4677c0u);	/* 45c768: call 0x4677c0 */
	m->ecx = M32((DWORD)(m->ebp + 0x10cu));	/* 45c76d: mov ecx, dword ptr [ebp + 0x10c] */
	m->eax = (DWORD)(m->ebp + 0x154u);	/* 45c773: lea eax, [ebp + 0x154] */
	M32((DWORD)(m->esp + 0x114u)) = m->ecx;	/* 45c779: mov dword ptr [esp + 0x114], ecx */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 45c780: xor edi, edi */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 45c782: mov edx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x110u)) = 0x9u;	/* 45c784: mov dword ptr [esp + 0x110], 9 */
	M32((DWORD)(m->esp + 0x118u)) = m->edx;	/* 45c78f: mov dword ptr [esp + 0x118], edx */
	M32((DWORD)(m->esp + 0x130u)) = m->edi;	/* 45c796: mov dword ptr [esp + 0x130], edi */
	m->ecx = M32((DWORD)(m->eax + 0x4u));	/* 45c79d: mov ecx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x134u)) = m->edi;	/* 45c7a0: mov dword ptr [esp + 0x134], edi */
	M32((DWORD)(m->esp + 0x11cu)) = m->ecx;	/* 45c7a7: mov dword ptr [esp + 0x11c], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 45c7ae: mov ecx, dword ptr [esp + 0x2c] */
	m->edx = M32((DWORD)(m->eax + 0x8u));	/* 45c7b2: mov edx, dword ptr [eax + 8] */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 45c7b5: mov eax, dword ptr [esp + 0x28] */
	M32((DWORD)(m->esp + 0x124u)) = m->eax;	/* 45c7b9: mov dword ptr [esp + 0x124], eax */
	M32((DWORD)(m->esp + 0x120u)) = m->edx;	/* 45c7c0: mov dword ptr [esp + 0x120], edx */
	m->edx = M32((DWORD)(m->esp + 0x30u));	/* 45c7c7: mov edx, dword ptr [esp + 0x30] */
	m->eax = (DWORD)(m->esp + 0x110u);	/* 45c7cb: lea eax, [esp + 0x110] */
	M32((DWORD)(m->esp + 0x128u)) = m->ecx;	/* 45c7d2: mov dword ptr [esp + 0x128], ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45c7d9: push eax */
	m->ecx = m->ebx;	/* 45c7da: mov ecx, ebx */
	M32((DWORD)(m->esp + 0x130u)) = m->edx;	/* 45c7dc: mov dword ptr [esp + 0x130], edx */
	M32((DWORD)(m->esp + 0x13cu)) = m->edi;	/* 45c7e3: mov dword ptr [esp + 0x13c], edi */
	M32((DWORD)(m->esp + 0x140u)) = m->edi;	/* 45c7ea: mov dword ptr [esp + 0x140], edi */
	M32((DWORD)(m->esp + 0x144u)) = m->edi;	/* 45c7f1: mov dword ptr [esp + 0x144], edi */
	m->esp -= 4; M32(m->esp) = 0x45c7fdu; native_call(m, 0x479950u);	/* 45c7f8: call 0x479950 */
	{ DWORD a_ = m->esi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->esi = r_; }	/* 45c7fd: dec esi */
	if (!m->zf) goto L_45c6f9;	/* 45c7fe: jne 0x45c6f9 */
	m->esi = M32((DWORD)(m->esp + 0x2b4u));	/* 45c804: mov esi, dword ptr [esp + 0x2b4] */
	m->eax = M32((DWORD)(m->ebx + 0x202e8d4u));	/* 45c80b: mov eax, dword ptr [ebx + 0x202e8d4] */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45c811: cmp esi, eax */
	if (!m->zf) goto L_45c829;	/* 45c813: jne 0x45c829 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x4c0u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45c815: cmp dword ptr [ebp + 0x4c0], esi */
	if (m->zf) goto L_45c829;	/* 45c81b: je 0x45c829 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 45c81d: push 0x64 */
	{ DWORD v_ = 0xdu; m->esp -= 4; M32(m->esp) = v_; }	/* 45c81f: push 0xd */
	m->esp -= 4; M32(m->esp) = 0x45c826u; native_call(m, 0x456e50u);	/* 45c821: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45c826: add esp, 8 */
L_45c829:
	M32((DWORD)(m->ebp + 0x14cu)) = 0x2u;	/* 45c829: mov dword ptr [ebp + 0x14c], 2 */
	m->edx = 0x1u;	/* 45c833: mov edx, 1 */
	M32((DWORD)(m->ebp + 0x150u)) = m->edi;	/* 45c838: mov dword ptr [ebp + 0x150], edi */
	M32((DWORD)(m->ebx + 0x202e8ecu)) = m->edx;	/* 45c83e: mov dword ptr [ebx + 0x202e8ec], edx */
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x20f3ad4u)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45c844: cmp dword ptr [ebx + 0x20f3ad4], edx */
	if (!m->zf) goto L_45ca1d;	/* 45c84a: jne 0x45ca1d */
	m->ecx = M32((DWORD)(m->ebp + 0x4c0u));	/* 45c850: mov ecx, dword ptr [ebp + 0x4c0] */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45c856: cmp ecx, esi */
	if (m->zf) goto L_45c9fd;	/* 45c858: je 0x45c9fd */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x4d8u)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45c85e: cmp dword ptr [ebp + 0x4d8], edx */
	if (!m->zf) goto L_45c8a5;	/* 45c864: jne 0x45c8a5 */
	m->eax = M32((DWORD)(m->ebx + 0x20f3ac0u));	/* 45c866: mov eax, dword ptr [ebx + 0x20f3ac0] */
	m->edi = 0x5u;	/* 45c86c: mov edi, 5 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45c871: cmp eax, edx */
	if (!m->zf) goto L_45c893;	/* 45c873: jne 0x45c893 */
	m->edx = M32((DWORD)(m->ebp + 0xdcu));	/* 45c875: mov edx, dword ptr [ebp + 0xdc] */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b4314u));	/* 45c87b: mov eax, dword ptr [edx*4 + 0x4b4314] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45c882: lea eax, [eax + eax*4] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 45c885: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45c886: sub eax, edx */
	m->edx = 0x1u;	/* 45c888: mov edx, 1 */
	m->esi = m->eax;	/* 45c88d: mov esi, eax */
	{ DWORD a_ = m->esi, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 45c88f: sar esi, 1 */
	goto L_45c8b4;	/* 45c891: jmp 0x45c8b4 */
L_45c893:
	m->eax = M32((DWORD)(m->ebp + 0xdcu));	/* 45c893: mov eax, dword ptr [ebp + 0xdc] */
	m->esi = M32((DWORD)(m->eax*4 + 0x4b4314u));	/* 45c899: mov esi, dword ptr [eax*4 + 0x4b4314] */
	m->esi = (DWORD)(m->esi + m->esi*4 + 0x0u);	/* 45c8a0: lea esi, [esi + esi*4] */
	goto L_45c8b4;	/* 45c8a3: jmp 0x45c8b4 */
L_45c8a5:
	m->eax = M32((DWORD)(m->ebp + 0xdcu));	/* 45c8a5: mov eax, dword ptr [ebp + 0xdc] */
	m->edi = m->edx;	/* 45c8ab: mov edi, edx */
	m->esi = M32((DWORD)(m->eax*4 + 0x4b4314u));	/* 45c8ad: mov esi, dword ptr [eax*4 + 0x4b4314] */
L_45c8b4:
	m->eax = m->ecx;	/* 45c8b4: mov eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45c8b6: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45c8b9: add eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45c8bb: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45c8be: add eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45c8c0: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45c8c3: add eax, ecx */
	m->ecx = M32((DWORD)(m->ebx + m->eax*8 + 0x1cd948cu));	/* 45c8c5: mov ecx, dword ptr [ebx + eax*8 + 0x1cd948c] */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45c8cc: add ecx, edi */
	m->eax = (DWORD)(m->ebx + m->eax*8 + 0x1cd948cu);	/* 45c8ce: lea eax, [ebx + eax*8 + 0x1cd948c] */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 45c8d5: mov dword ptr [eax], ecx */
	m->eax = M32((DWORD)(m->ebp + 0x4c0u));	/* 45c8d7: mov eax, dword ptr [ebp + 0x4c0] */
	m->ecx = m->eax;	/* 45c8dd: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45c8df: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45c8e2: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45c8e4: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45c8e7: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45c8e9: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45c8ec: add ecx, eax */
	m->eax = (DWORD)(m->ebx + m->ecx*8 + 0x1cd9494u);	/* 45c8ee: lea eax, [ebx + ecx*8 + 0x1cd9494] */
	m->ecx = M32((DWORD)(m->ebx + m->ecx*8 + 0x1cd9494u));	/* 45c8f5: mov ecx, dword ptr [ebx + ecx*8 + 0x1cd9494] */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45c8fc: add ecx, esi */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 45c8fe: mov dword ptr [eax], ecx */
	m->eax = M32((DWORD)(m->ebp + 0x4c0u));	/* 45c900: mov eax, dword ptr [ebp + 0x4c0] */
	m->ecx = m->eax;	/* 45c906: mov ecx, eax */
	m->edi = M32((DWORD)(m->ebx + 0x202e8d4u));	/* 45c908: mov edi, dword ptr [ebx + 0x202e8d4] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45c90e: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45c911: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45c913: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45c916: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45c918: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45c91b: add ecx, eax */
	m->eax = (DWORD)(m->ebx + m->ecx*8 + 0x0u);	/* 45c91d: lea eax, [ebx + ecx*8] */
	m->ecx = M32((DWORD)(m->ebx + m->ecx*8 + 0x1cd94b8u));	/* 45c920: mov ecx, dword ptr [ebx + ecx*8 + 0x1cd94b8] */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45c927: cmp ecx, edi */
	if (!m->zf) goto L_45c95d;	/* 45c929: jne 0x45c95d */
	m->edx = M32((DWORD)(m->eax + 0x1cd9494u));	/* 45c92b: mov edx, dword ptr [eax + 0x1cd9494] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45c931: push edx */
	m->esp -= 4; M32(m->esp) = 0x45c937u; native_call(m, 0x4326f0u);	/* 45c932: call 0x4326f0 */
	m->ecx = M32((DWORD)(m->ebp + 0x4c0u));	/* 45c937: mov ecx, dword ptr [ebp + 0x4c0] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45c93d: add esp, 4 */
	m->edx = m->ecx;	/* 45c940: mov edx, ecx */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45c942: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45c945: add edx, ecx */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45c947: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45c94a: add edx, ecx */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45c94c: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45c94f: add edx, ecx */
	M32((DWORD)(m->ebx + m->edx*8 + 0x1cd9484u)) = m->eax;	/* 45c951: mov dword ptr [ebx + edx*8 + 0x1cd9484], eax */
	m->edx = 0x1u;	/* 45c958: mov edx, 1 */
L_45c95d:
	m->eax = M32((DWORD)(m->ebp + 0x4c0u));	/* 45c95d: mov eax, dword ptr [ebp + 0x4c0] */
	m->ecx = M32((DWORD)(m->ebx + 0x202e8d4u));	/* 45c963: mov ecx, dword ptr [ebx + 0x202e8d4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45c969: cmp eax, ecx */
	if (!m->zf) goto L_45cd35;	/* 45c96b: jne 0x45cd35 */
	m->eax = M32((DWORD)(m->ebp + 0x4d8u));	/* 45c971: mov eax, dword ptr [ebp + 0x4d8] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45c977: cmp eax, edx */
	m->eax = M32((DWORD)(m->ebx + 0x20f3ab4u));	/* 45c979: mov eax, dword ptr [ebx + 0x20f3ab4] */
	if (!m->zf) goto L_45c9d2;	/* 45c97f: jne 0x45c9d2 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45c981: cmp eax, edx */
	{ DWORD v_ = 0x5u; m->esp -= 4; M32(m->esp) = v_; }	/* 45c983: push 5 */
	if (!m->zf) goto L_45c9ae;	/* 45c985: jne 0x45c9ae */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45c987: push esi */
	m->ecx = (DWORD)(m->ebp + 0x98u);	/* 45c988: lea ecx, [ebp + 0x98] */
	{ DWORD v_ = 0x5u; m->esp -= 4; M32(m->esp) = v_; }	/* 45c98e: push 5 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45c990: push ecx */
	{ DWORD v_ = 0x4b44f8u; m->esp -= 4; M32(m->esp) = v_; }	/* 45c991: push 0x4b44f8 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45c996: push ebx */
	m->esp -= 4; M32(m->esp) = 0x45c99cu; native_call(m, 0x473450u);	/* 45c997: call 0x473450 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45c99c: add esp, 0x18 */
	M32((DWORD)(m->ebx + 0x20fce4cu)) = 0xffffffffu;	/* 45c99f: mov dword ptr [ebx + 0x20fce4c], 0xffffffff */
	goto L_45cd35;	/* 45c9a9: jmp 0x45cd35 */
L_45c9ae:
	m->edx = (DWORD)(m->ebp + 0x98u);	/* 45c9ae: lea edx, [ebp + 0x98] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45c9b4: push edx */
	{ DWORD v_ = 0x4b44d4u; m->esp -= 4; M32(m->esp) = v_; }	/* 45c9b5: push 0x4b44d4 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45c9ba: push ebx */
	m->esp -= 4; M32(m->esp) = 0x45c9c0u; native_call(m, 0x473450u);	/* 45c9bb: call 0x473450 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45c9c0: add esp, 0x10 */
	M32((DWORD)(m->ebx + 0x20fce4cu)) = 0xffffffffu;	/* 45c9c3: mov dword ptr [ebx + 0x20fce4c], 0xffffffff */
	goto L_45cd35;	/* 45c9cd: jmp 0x45cd35 */
L_45c9d2:
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45c9d2: cmp eax, edx */
	if (!m->zf) goto L_45c9ea;	/* 45c9d4: jne 0x45c9ea */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45c9d6: push esi */
	{ DWORD v_ = 0x4b44c4u; m->esp -= 4; M32(m->esp) = v_; }	/* 45c9d7: push 0x4b44c4 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45c9dc: push ebx */
	m->esp -= 4; M32(m->esp) = 0x45c9e2u; native_call(m, 0x473450u);	/* 45c9dd: call 0x473450 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45c9e2: add esp, 0xc */
	goto L_45cd35;	/* 45c9e5: jmp 0x45cd35 */
L_45c9ea:
	{ DWORD v_ = 0x4b44bcu; m->esp -= 4; M32(m->esp) = v_; }	/* 45c9ea: push 0x4b44bc */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45c9ef: push ebx */
	m->esp -= 4; M32(m->esp) = 0x45c9f5u; native_call(m, 0x473450u);	/* 45c9f0: call 0x473450 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45c9f5: add esp, 8 */
	goto L_45cd35;	/* 45c9f8: jmp 0x45cd35 */
L_45c9fd:
	m->esi = M32((DWORD)(m->ebp + 0xe4u));	/* 45c9fd: mov esi, dword ptr [ebp + 0xe4] */
	{ DWORD v_ = 0x4b44b4u; m->esp -= 4; M32(m->esp) = v_; }	/* 45ca03: push 0x4b44b4 */
	{ DWORD a_ = m->esi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->esi = r_; }	/* 45ca08: dec esi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45ca09: push ebx */
	M32((DWORD)(m->ebp + 0xe4u)) = m->esi;	/* 45ca0a: mov dword ptr [ebp + 0xe4], esi */
	m->esp -= 4; M32(m->esp) = 0x45ca15u; native_call(m, 0x473450u);	/* 45ca10: call 0x473450 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45ca15: add esp, 8 */
	goto L_45cd35;	/* 45ca18: jmp 0x45cd35 */
L_45ca1d:
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x20f3ad8u)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45ca1d: cmp dword ptr [ebx + 0x20f3ad8], edx */
	if (!m->zf) goto L_45cb99;	/* 45ca23: jne 0x45cb99 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x4dcu)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45ca29: cmp dword ptr [ebp + 0x4dc], edx */
	if (!m->zf) goto L_45cd35;	/* 45ca2f: jne 0x45cd35 */
	m->ecx = M32((DWORD)(m->ebx + 0x202e8c8u));	/* 45ca35: mov ecx, dword ptr [ebx + 0x202e8c8] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 45ca3b: xor edi, edi */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45ca3d: cmp ecx, edi */
	M32((DWORD)(m->esp + 0x4cu)) = m->edi;	/* 45ca3f: mov dword ptr [esp + 0x4c], edi */
	if (m->zf || m->sf != m->of) goto L_45ca81;	/* 45ca43: jle 0x45ca81 */
	m->eax = (DWORD)(m->ebx + 0x1cd9484u);	/* 45ca45: lea eax, [ebx + 0x1cd9484] */
	m->esi = m->ecx;	/* 45ca4b: mov esi, ecx */
L_45ca4d:
	m->edx = M32((DWORD)(m->ebp + 0x118u));	/* 45ca4d: mov edx, dword ptr [ebp + 0x118] */
	{ DWORD a_ = M32((DWORD)(m->eax + 0x3cu)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45ca53: cmp dword ptr [eax + 0x3c], edx */
	if (!m->zf) goto L_45ca74;	/* 45ca56: jne 0x45ca74 */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 45ca58: mov edx, dword ptr [eax] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 45ca5a: inc edi */
	M32((DWORD)(m->esp + 0x44u)) = m->edi;	/* 45ca5b: mov dword ptr [esp + 0x44], edi */
	m->edi = M32((DWORD)(m->esp + 0x4cu));	/* 45ca5f: mov edi, dword ptr [esp + 0x4c] */
	m->edx = M32((DWORD)(m->edx*4 + 0x4b4314u));	/* 45ca63: mov edx, dword ptr [edx*4 + 0x4b4314] */
	{ DWORD a_ = m->edi, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 45ca6a: add edi, edx */
	M32((DWORD)(m->esp + 0x4cu)) = m->edi;	/* 45ca6c: mov dword ptr [esp + 0x4c], edi */
	m->edi = M32((DWORD)(m->esp + 0x44u));	/* 45ca70: mov edi, dword ptr [esp + 0x44] */
L_45ca74:
	{ DWORD a_ = m->eax, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45ca74: add eax, 0x8888 */
	{ DWORD a_ = m->esi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->esi = r_; }	/* 45ca79: dec esi */
	if (!m->zf) goto L_45ca4d;	/* 45ca7a: jne 0x45ca4d */
	m->edx = 0x1u;	/* 45ca7c: mov edx, 1 */
L_45ca81:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45ca81: test ecx, ecx */
	M32((DWORD)(m->esp + 0x24u)) = 0x0u;	/* 45ca83: mov dword ptr [esp + 0x24], 0 */
	if (m->zf || m->sf != m->of) goto L_45cae9;	/* 45ca8b: jle 0x45cae9 */
	m->esi = (DWORD)(m->ebx + 0x1cd948cu);	/* 45ca8d: lea esi, [ebx + 0x1cd948c] */
L_45ca93:
	m->eax = M32((DWORD)(m->esi + 0x34u));	/* 45ca93: mov eax, dword ptr [esi + 0x34] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45ca96: test eax, eax */
	if (m->sf != m->of) goto L_45cad0;	/* 45ca98: jl 0x45cad0 */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->ebp + 0x118u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45ca9a: cmp eax, dword ptr [ebp + 0x118] */
	if (m->zf) goto L_45cad0;	/* 45caa0: je 0x45cad0 */
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 45caa2: mov eax, dword ptr [esi] */
	m->ecx = M32((DWORD)(m->esp + 0x4cu));	/* 45caa4: mov ecx, dword ptr [esp + 0x4c] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45caa8: add eax, edi */
	M32((DWORD)(m->esi + 0x0u)) = m->eax;	/* 45caaa: mov dword ptr [esi], eax */
	m->eax = M32((DWORD)(m->esi + 0x8u));	/* 45caac: mov eax, dword ptr [esi + 8] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45caaf: add eax, ecx */
	M32((DWORD)(m->esi + 0x8u)) = m->eax;	/* 45cab1: mov dword ptr [esi + 8], eax */
	m->ecx = M32((DWORD)(m->esi + 0x2cu));	/* 45cab4: mov ecx, dword ptr [esi + 0x2c] */
	{ DWORD a_ = m->ecx, b_ = M32((DWORD)(m->ebx + 0x202e8d4u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45cab7: cmp ecx, dword ptr [ebx + 0x202e8d4] */
	if (!m->zf) goto L_45cad0;	/* 45cabd: jne 0x45cad0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45cabf: push eax */
	m->esp -= 4; M32(m->esp) = 0x45cac5u; native_call(m, 0x4326f0u);	/* 45cac0: call 0x4326f0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45cac5: add esp, 4 */
	M32((DWORD)(m->esi + 0xfffffff8u)) = m->eax;	/* 45cac8: mov dword ptr [esi - 8], eax */
	m->edx = 0x1u;	/* 45cacb: mov edx, 1 */
L_45cad0:
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 45cad0: mov eax, dword ptr [esp + 0x24] */
	m->ecx = M32((DWORD)(m->ebx + 0x202e8c8u));	/* 45cad4: mov ecx, dword ptr [ebx + 0x202e8c8] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 45cada: inc eax */
	{ DWORD a_ = m->esi, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 45cadb: add esi, 0x8888 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45cae1: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 45cae3: mov dword ptr [esp + 0x24], eax */
	if (m->sf != m->of) goto L_45ca93;	/* 45cae7: jl 0x45ca93 */
L_45cae9:
	m->eax = M32((DWORD)(m->ebx + 0x202e8d4u));	/* 45cae9: mov eax, dword ptr [ebx + 0x202e8d4] */
	m->ecx = m->eax;	/* 45caef: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45caf1: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45caf4: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45caf6: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45caf9: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45cafb: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45cafe: add ecx, eax */
	m->eax = M32((DWORD)(m->ebx + m->ecx*8 + 0x1cd94c0u));	/* 45cb00: mov eax, dword ptr [ebx + ecx*8 + 0x1cd94c0] */
	m->ecx = M32((DWORD)(m->ebp + 0x118u));	/* 45cb07: mov ecx, dword ptr [ebp + 0x118] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45cb0d: test eax, eax */
	if (m->sf != m->of) goto L_45cb52;	/* 45cb0f: jl 0x45cb52 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45cb11: cmp eax, ecx */
	if (m->zf) goto L_45cb56;	/* 45cb13: je 0x45cb56 */
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x20f3ab4u)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45cb15: cmp dword ptr [ebx + 0x20f3ab4], edx */
	if (!m->zf) goto L_45cb3a;	/* 45cb1b: jne 0x45cb3a */
	m->edx = M32((DWORD)(m->esp + 0x4cu));	/* 45cb1d: mov edx, dword ptr [esp + 0x4c] */
	m->eax = (DWORD)(m->ebp + 0x98u);	/* 45cb21: lea eax, [ebp + 0x98] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45cb27: push edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45cb28: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45cb29: push eax */
	{ DWORD v_ = 0x4b447cu; m->esp -= 4; M32(m->esp) = v_; }	/* 45cb2a: push 0x4b447c */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45cb2f: push ebx */
	m->esp -= 4; M32(m->esp) = 0x45cb35u; native_call(m, 0x473450u);	/* 45cb30: call 0x473450 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45cb35: add esp, 0x14 */
	goto L_45cb6b;	/* 45cb38: jmp 0x45cb6b */
L_45cb3a:
	m->ecx = (DWORD)(m->ebp + 0x98u);	/* 45cb3a: lea ecx, [ebp + 0x98] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45cb40: push edi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45cb41: push ecx */
	{ DWORD v_ = 0x4b4450u; m->esp -= 4; M32(m->esp) = v_; }	/* 45cb42: push 0x4b4450 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45cb47: push ebx */
	m->esp -= 4; M32(m->esp) = 0x45cb4du; native_call(m, 0x473450u);	/* 45cb48: call 0x473450 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45cb4d: add esp, 0x10 */
	goto L_45cb6b;	/* 45cb50: jmp 0x45cb6b */
L_45cb52:
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45cb52: cmp eax, ecx */
	if (!m->zf) goto L_45cb6b;	/* 45cb54: jne 0x45cb6b */
L_45cb56:
	m->edx = (DWORD)(m->ebp + 0x98u);	/* 45cb56: lea edx, [ebp + 0x98] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45cb5c: push edx */
	{ DWORD v_ = 0x4b442cu; m->esp -= 4; M32(m->esp) = v_; }	/* 45cb5d: push 0x4b442c */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45cb62: push ebx */
	m->esp -= 4; M32(m->esp) = 0x45cb68u; native_call(m, 0x473450u);	/* 45cb63: call 0x473450 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45cb68: add esp, 0xc */
L_45cb6b:
	m->eax = M32((DWORD)(m->ebp + 0x118u));	/* 45cb6b: mov eax, dword ptr [ebp + 0x118] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45cb71: test eax, eax */
	if (!m->zf) goto L_45cb7d;	/* 45cb73: jne 0x45cb7d */
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x202e8f4u)), b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(m->ebx + 0x202e8f4u)) = r_; }	/* 45cb75: add dword ptr [ebx + 0x202e8f4], edi */
	goto L_45cb83;	/* 45cb7b: jmp 0x45cb83 */
L_45cb7d:
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x202e8f0u)), b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(m->ebx + 0x202e8f0u)) = r_; }	/* 45cb7d: add dword ptr [ebx + 0x202e8f0], edi */
L_45cb83:
	m->eax = M32((DWORD)(m->ebp + 0x118u));	/* 45cb83: mov eax, dword ptr [ebp + 0x118] */
	M32((DWORD)(m->ebx + m->eax*4 + 0x20fce50u)) = 0xffffffffu;	/* 45cb89: mov dword ptr [ebx + eax*4 + 0x20fce50], 0xffffffff */
	goto L_45cd35;	/* 45cb94: jmp 0x45cd35 */
L_45cb99:
	m->ecx = M32((DWORD)(m->ebp + 0x4c0u));	/* 45cb99: mov ecx, dword ptr [ebp + 0x4c0] */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45cb9f: cmp ecx, esi */
	if (m->zf) goto L_45cce8;	/* 45cba1: je 0x45cce8 */
	m->eax = M32((DWORD)(m->ebx + 0x20f3ac0u));	/* 45cba7: mov eax, dword ptr [ebx + 0x20f3ac0] */
	m->edi = M32((DWORD)(m->ebp + 0xdcu));	/* 45cbad: mov edi, dword ptr [ebp + 0xdc] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45cbb3: cmp eax, edx */
	if (!m->zf) goto L_45cbc7;	/* 45cbb5: jne 0x45cbc7 */
	m->eax = M32((DWORD)(m->edi*4 + 0x4b4314u));	/* 45cbb7: mov eax, dword ptr [edi*4 + 0x4b4314] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 45cbbe: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45cbbf: sub eax, edx */
	m->esi = m->eax;	/* 45cbc1: mov esi, eax */
	{ DWORD a_ = m->esi, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 45cbc3: sar esi, 1 */
	goto L_45cbce;	/* 45cbc5: jmp 0x45cbce */
L_45cbc7:
	m->esi = M32((DWORD)(m->edi*4 + 0x4b4314u));	/* 45cbc7: mov esi, dword ptr [edi*4 + 0x4b4314] */
L_45cbce:
	m->edx = m->ecx;	/* 45cbce: mov edx, ecx */
	{ DWORD a_ = m->edi, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 45cbd0: add edi, 3 */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45cbd3: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45cbd6: add edx, ecx */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45cbd8: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45cbdb: add edx, ecx */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45cbdd: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45cbe0: add edx, ecx */
	m->eax = M32((DWORD)(m->ebx + m->edx*8 + 0x1cd9484u));	/* 45cbe2: mov eax, dword ptr [ebx + edx*8 + 0x1cd9484] */
	m->ecx = (DWORD)(m->ebx + m->edx*8 + 0x0u);	/* 45cbe9: lea ecx, [ebx + edx*8] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45cbec: cmp eax, edi */
	if (m->zf || m->sf != m->of) goto L_45cbf9;	/* 45cbee: jle 0x45cbf9 */
	m->eax = m->esi;	/* 45cbf0: mov eax, esi */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 45cbf2: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45cbf3: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45cbf5: sar eax, 1 */
	m->esi = m->eax;	/* 45cbf7: mov esi, eax */
L_45cbf9:
	m->edi = M32((DWORD)(m->ecx + 0x1cd948cu));	/* 45cbf9: mov edi, dword ptr [ecx + 0x1cd948c] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 45cbff: inc edi */
	M32((DWORD)(m->ecx + 0x1cd948cu)) = m->edi;	/* 45cc00: mov dword ptr [ecx + 0x1cd948c], edi */
	m->eax = M32((DWORD)(m->ebp + 0x4c0u));	/* 45cc06: mov eax, dword ptr [ebp + 0x4c0] */
	m->ecx = m->eax;	/* 45cc0c: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45cc0e: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45cc11: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45cc13: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45cc16: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45cc18: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45cc1b: add ecx, eax */
	m->edx = M32((DWORD)(m->ebx + m->ecx*8 + 0x1cd9494u));	/* 45cc1d: mov edx, dword ptr [ebx + ecx*8 + 0x1cd9494] */
	m->eax = (DWORD)(m->ebx + m->ecx*8 + 0x1cd9494u);	/* 45cc24: lea eax, [ebx + ecx*8 + 0x1cd9494] */
	{ DWORD a_ = m->edx, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45cc2b: add edx, esi */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 45cc2d: mov dword ptr [eax], edx */
	m->eax = M32((DWORD)(m->ebp + 0x4c0u));	/* 45cc2f: mov eax, dword ptr [ebp + 0x4c0] */
	m->edx = m->eax;	/* 45cc35: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45cc37: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45cc3a: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45cc3c: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45cc3f: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45cc41: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45cc44: add edx, eax */
	m->ecx = M32((DWORD)(m->ebx + m->edx*8 + 0x1cd94b8u));	/* 45cc46: mov ecx, dword ptr [ebx + edx*8 + 0x1cd94b8] */
	m->eax = (DWORD)(m->ebx + m->edx*8 + 0x0u);	/* 45cc4d: lea eax, [ebx + edx*8] */
	{ DWORD a_ = m->ecx, b_ = M32((DWORD)(m->ebx + 0x202e8d4u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45cc50: cmp ecx, dword ptr [ebx + 0x202e8d4] */
	if (!m->zf) goto L_45cc85;	/* 45cc56: jne 0x45cc85 */
	m->edx = M32((DWORD)(m->eax + 0x1cd9494u));	/* 45cc58: mov edx, dword ptr [eax + 0x1cd9494] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45cc5e: push edx */
	m->esp -= 4; M32(m->esp) = 0x45cc64u; native_call(m, 0x4326f0u);	/* 45cc5f: call 0x4326f0 */
	m->ecx = M32((DWORD)(m->ebp + 0x4c0u));	/* 45cc64: mov ecx, dword ptr [ebp + 0x4c0] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45cc6a: add esp, 4 */
	m->edx = m->ecx;	/* 45cc6d: mov edx, ecx */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45cc6f: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45cc72: add edx, ecx */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45cc74: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45cc77: add edx, ecx */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45cc79: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45cc7c: add edx, ecx */
	M32((DWORD)(m->ebx + m->edx*8 + 0x1cd9484u)) = m->eax;	/* 45cc7e: mov dword ptr [ebx + edx*8 + 0x1cd9484], eax */
L_45cc85:
	m->eax = M32((DWORD)(m->ebp + 0x4c0u));	/* 45cc85: mov eax, dword ptr [ebp + 0x4c0] */
	m->ecx = M32((DWORD)(m->ebx + 0x202e8d4u));	/* 45cc8b: mov ecx, dword ptr [ebx + 0x202e8d4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45cc91: cmp eax, ecx */
	if (!m->zf) goto L_45ccbd;	/* 45cc93: jne 0x45ccbd */
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x20f3ab4u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45cc95: cmp dword ptr [ebx + 0x20f3ab4], 1 */
	if (!m->zf) goto L_45ccaf;	/* 45cc9c: jne 0x45ccaf */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45cc9e: push esi */
	{ DWORD v_ = 0x4b44c4u; m->esp -= 4; M32(m->esp) = v_; }	/* 45cc9f: push 0x4b44c4 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45cca4: push ebx */
	m->esp -= 4; M32(m->esp) = 0x45ccaau; native_call(m, 0x473450u);	/* 45cca5: call 0x473450 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45ccaa: add esp, 0xc */
	goto L_45ccbd;	/* 45ccad: jmp 0x45ccbd */
L_45ccaf:
	{ DWORD v_ = 0x4b44bcu; m->esp -= 4; M32(m->esp) = v_; }	/* 45ccaf: push 0x4b44bc */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45ccb4: push ebx */
	m->esp -= 4; M32(m->esp) = 0x45ccbau; native_call(m, 0x473450u);	/* 45ccb5: call 0x473450 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45ccba: add esp, 8 */
L_45ccbd:
	m->eax = M32((DWORD)(m->ebp + 0x4c0u));	/* 45ccbd: mov eax, dword ptr [ebp + 0x4c0] */
	m->ecx = m->eax;	/* 45ccc3: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45ccc5: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45ccc8: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45ccca: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45cccd: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45cccf: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45ccd2: add ecx, eax */
	m->eax = M32((DWORD)(m->ebx + m->ecx*8 + 0x1cd94c0u));	/* 45ccd4: mov eax, dword ptr [ebx + ecx*8 + 0x1cd94c0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45ccdb: test eax, eax */
	if (m->sf != m->of) goto L_45cd35;	/* 45ccdd: jl 0x45cd35 */
	{ DWORD a_ = M32((DWORD)(m->ebx + m->eax*4 + 0x202e8f0u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(m->ebx + m->eax*4 + 0x202e8f0u)) = r_; }	/* 45ccdf: inc dword ptr [ebx + eax*4 + 0x202e8f0] */
	goto L_45cd35;	/* 45cce6: jmp 0x45cd35 */
L_45cce8:
	m->esi = M32((DWORD)(m->ebp + 0xe4u));	/* 45cce8: mov esi, dword ptr [ebp + 0xe4] */
	{ DWORD a_ = m->esi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->esi = r_; }	/* 45ccee: dec esi */
	M32((DWORD)(m->ebp + 0xe4u)) = m->esi;	/* 45ccef: mov dword ptr [ebp + 0xe4], esi */
	m->eax = M32((DWORD)(m->ebp + 0x4c0u));	/* 45ccf5: mov eax, dword ptr [ebp + 0x4c0] */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->ebx + 0x202e8d4u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45ccfb: cmp eax, dword ptr [ebx + 0x202e8d4] */
	if (!m->zf) goto L_45cd16;	/* 45cd01: jne 0x45cd16 */
	{ DWORD v_ = 0x4b44b4u; m->esp -= 4; M32(m->esp) = v_; }	/* 45cd03: push 0x4b44b4 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45cd08: push ebx */
	m->esp -= 4; M32(m->esp) = 0x45cd0eu; native_call(m, 0x473450u);	/* 45cd09: call 0x473450 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45cd0e: add esp, 8 */
	m->edx = 0x1u;	/* 45cd11: mov edx, 1 */
L_45cd16:
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x20f3abcu)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45cd16: cmp dword ptr [ebx + 0x20f3abc], edx */
	if (!m->zf) goto L_45cd35;	/* 45cd1c: jne 0x45cd35 */
	m->ecx = M32((DWORD)(m->ebp + 0x118u));	/* 45cd1e: mov ecx, dword ptr [ebp + 0x118] */
	m->eax = (DWORD)(m->ebx + m->ecx*4 + 0x202e8f0u);	/* 45cd24: lea eax, [ebx + ecx*4 + 0x202e8f0] */
	m->ecx = M32((DWORD)(m->ebx + m->ecx*4 + 0x202e8f0u));	/* 45cd2b: mov ecx, dword ptr [ebx + ecx*4 + 0x202e8f0] */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 45cd32: dec ecx */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 45cd33: mov dword ptr [eax], ecx */
L_45cd35:
	m->eax = M32((DWORD)(m->esp + 0x2b4u));	/* 45cd35: mov eax, dword ptr [esp + 0x2b4] */
	m->ecx = M32((DWORD)(m->ebp + 0x4c0u));	/* 45cd3c: mov ecx, dword ptr [ebp + 0x4c0] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45cd42: cmp ecx, eax */
	if (m->zf) goto L_45cd4c;	/* 45cd44: je 0x45cd4c */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0xe8u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(m->ebp + 0xe8u)) = r_; }	/* 45cd46: inc dword ptr [ebp + 0xe8] */
L_45cd4c:
	M32((DWORD)(m->ebx + m->eax*4 + 0x202ea80u)) = 0x0u;	/* 45cd4c: mov dword ptr [ebx + eax*4 + 0x202ea80], 0 */
	M32((DWORD)(m->ebp + 0x8868u)) = 0x1u;	/* 45cd57: mov dword ptr [ebp + 0x8868], 1 */
	M32((DWORD)(m->ebx + 0x202e8e8u)) = m->eax;	/* 45cd61: mov dword ptr [ebx + 0x202e8e8], eax */
	goto L_45c546;	/* 45cd67: jmp 0x45c546 */
L_45cd6c:
	m->edx = M32((DWORD)(m->ebp + 0x110u));	/* 45cd6c: mov edx, dword ptr [ebp + 0x110] */
	m->eax = M32((DWORD)(m->ebx + 0x202e8d4u));	/* 45cd72: mov eax, dword ptr [ebx + 0x202e8d4] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45cd78: cmp edx, eax */
	if (m->zf) goto L_45cd88;	/* 45cd7a: je 0x45cd88 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x11cu)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45cd7c: cmp dword ptr [ebp + 0x11c], esi */
	if (m->zf) goto L_45c548;	/* 45cd82: je 0x45c548 */
L_45cd88:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2b8u)));	/* 45cd88: fld dword ptr [esp + 0x2b8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x120u));	/* 45cd8f: fadd dword ptr [ebp + 0x120] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 45cd95: fadd dword ptr [0x4a9418] */
	MF((DWORD)(m->ebp + 0x124u)) = (float)ST(0); FPOP();	/* 45cd9b: fstp dword ptr [ebp + 0x124] */
	goto L_45c548;	/* 45cda1: jmp 0x45c548 */
L_45cda6:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x4a4u)));	/* 45cda6: fld dword ptr [ebp + 0x4a4] */
	goto L_45c5e1;	/* 45cdac: jmp 0x45c5e1 */
L_45cdb1:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2b8u)));	/* 45cdb1: fld dword ptr [esp + 0x2b8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x120u));	/* 45cdb8: fadd dword ptr [ebp + 0x120] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 45cdbe: xor esi, esi */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 45cdc0: fadd dword ptr [0x4a9418] */
	MF((DWORD)(m->ebp + 0x124u)) = (float)ST(0); FPOP();	/* 45cdc6: fstp dword ptr [ebp + 0x124] */
L_45cdcc:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2b8u)));	/* 45cdcc: fld dword ptr [esp + 0x2b8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x120u));	/* 45cdd3: fadd dword ptr [ebp + 0x120] */
	MF((DWORD)(m->ebp + 0x120u)) = (float)ST(0); FPOP();	/* 45cdd9: fstp dword ptr [ebp + 0x120] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2b8u)));	/* 45cddf: fld dword ptr [esp + 0x2b8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x150u));	/* 45cde6: fadd dword ptr [ebp + 0x150] */
	MF((DWORD)(m->ebp + 0x150u)) = (float)ST(0); FPOP();	/* 45cdec: fstp dword ptr [ebp + 0x150] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2b8u)));	/* 45cdf2: fld dword ptr [esp + 0x2b8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x100u));	/* 45cdf9: fadd dword ptr [ebp + 0x100] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u));	/* 45cdff: fcom dword ptr [0x4a9424] */
	MF((DWORD)(m->ebp + 0x100u)) = (float)ST(0);	/* 45ce05: fst dword ptr [ebp + 0x100] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45ce0b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45ce0d: test ah, 0x41 */
	if (!m->zf) goto L_45ce3e;	/* 45ce10: jne 0x45ce3e */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 45ce12: call 0x49ec14 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0xfcu)), b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(m->ebp + 0xfcu)) = r_; }	/* 45ce17: add dword ptr [ebp + 0xfc], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x100u)));	/* 45ce1d: fld dword ptr [ebp + 0x100] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 45ce23: call 0x49ec14 */
	M32((DWORD)(m->esp + 0x44u)) = m->eax;	/* 45ce28: mov dword ptr [esp + 0x44], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x44u)));	/* 45ce2c: fild dword ptr [esp + 0x44] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(m->ebp + 0x100u));	/* 45ce30: fsubr dword ptr [ebp + 0x100] */
	MF((DWORD)(m->ebp + 0x100u)) = (float)ST(0); FPOP();	/* 45ce36: fstp dword ptr [ebp + 0x100] */
	goto L_45ce40;	/* 45ce3c: jmp 0x45ce40 */
L_45ce3e:
	ST(0) = ST(0); FPOP();	/* 45ce3e: fstp st(0) */
L_45ce40:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x87f0u)));	/* 45ce40: fld dword ptr [ebp + 0x87f0] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45ce46: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45ce4c: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45ce4e: test ah, 0x41 */
	if (!m->zf) goto L_45ce79;	/* 45ce51: jne 0x45ce79 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x87f0u)));	/* 45ce53: fld dword ptr [ebp + 0x87f0] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x2b8u));	/* 45ce59: fsub dword ptr [esp + 0x2b8] */
	MF((DWORD)(m->ebp + 0x87f0u)) = (float)ST(0);	/* 45ce60: fst dword ptr [ebp + 0x87f0] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45ce66: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45ce6c: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45ce6e: test ah, 1 */
	if (m->zf) goto L_45ce79;	/* 45ce71: je 0x45ce79 */
	M32((DWORD)(m->ebp + 0x87f0u)) = m->esi;	/* 45ce73: mov dword ptr [ebp + 0x87f0], esi */
L_45ce79:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x8854u)));	/* 45ce79: fld dword ptr [ebp + 0x8854] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45ce7f: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45ce85: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45ce87: test ah, 0x41 */
	if (!m->zf) goto L_45ceb2;	/* 45ce8a: jne 0x45ceb2 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x8854u)));	/* 45ce8c: fld dword ptr [ebp + 0x8854] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x2b8u));	/* 45ce92: fsub dword ptr [esp + 0x2b8] */
	MF((DWORD)(m->ebp + 0x8854u)) = (float)ST(0);	/* 45ce99: fst dword ptr [ebp + 0x8854] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45ce9f: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45cea5: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45cea7: test ah, 1 */
	if (m->zf) goto L_45ceb2;	/* 45ceaa: je 0x45ceb2 */
	M32((DWORD)(m->ebp + 0x8854u)) = m->esi;	/* 45ceac: mov dword ptr [ebp + 0x8854], esi */
L_45ceb2:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x8858u)));	/* 45ceb2: fld dword ptr [ebp + 0x8858] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45ceb8: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45cebe: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45cec0: test ah, 0x41 */
	if (!m->zf) goto L_45ceeb;	/* 45cec3: jne 0x45ceeb */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x8858u)));	/* 45cec5: fld dword ptr [ebp + 0x8858] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x2b8u));	/* 45cecb: fsub dword ptr [esp + 0x2b8] */
	MF((DWORD)(m->ebp + 0x8858u)) = (float)ST(0);	/* 45ced2: fst dword ptr [ebp + 0x8858] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45ced8: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45cede: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45cee0: test ah, 1 */
	if (m->zf) goto L_45ceeb;	/* 45cee3: je 0x45ceeb */
	M32((DWORD)(m->ebp + 0x8858u)) = m->esi;	/* 45cee5: mov dword ptr [ebp + 0x8858], esi */
L_45ceeb:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x494u)));	/* 45ceeb: fld dword ptr [ebp + 0x494] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45cef1: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45cef7: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45cef9: test ah, 0x41 */
	if (!m->zf) goto L_45cf24;	/* 45cefc: jne 0x45cf24 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x494u)));	/* 45cefe: fld dword ptr [ebp + 0x494] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x2b8u));	/* 45cf04: fsub dword ptr [esp + 0x2b8] */
	MF((DWORD)(m->ebp + 0x494u)) = (float)ST(0);	/* 45cf0b: fst dword ptr [ebp + 0x494] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45cf11: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45cf17: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45cf19: test ah, 1 */
	if (m->zf) goto L_45cf24;	/* 45cf1c: je 0x45cf24 */
	M32((DWORD)(m->ebp + 0x494u)) = m->esi;	/* 45cf1e: mov dword ptr [ebp + 0x494], esi */
L_45cf24:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x534u)));	/* 45cf24: fld dword ptr [ebp + 0x534] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x2b8u));	/* 45cf2a: fsub dword ptr [esp + 0x2b8] */
	MF((DWORD)(m->ebp + 0x534u)) = (float)ST(0); FPOP();	/* 45cf31: fstp dword ptr [ebp + 0x534] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x540u)));	/* 45cf37: fld dword ptr [ebp + 0x540] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45cf3d: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45cf43: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45cf45: test ah, 0x41 */
	if (!m->zf) goto L_45cf70;	/* 45cf48: jne 0x45cf70 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x540u)));	/* 45cf4a: fld dword ptr [ebp + 0x540] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x2b8u));	/* 45cf50: fsub dword ptr [esp + 0x2b8] */
	MF((DWORD)(m->ebp + 0x540u)) = (float)ST(0);	/* 45cf57: fst dword ptr [ebp + 0x540] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45cf5d: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45cf63: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45cf65: test ah, 1 */
	if (m->zf) goto L_45cf70;	/* 45cf68: je 0x45cf70 */
	M32((DWORD)(m->ebp + 0x540u)) = m->esi;	/* 45cf6a: mov dword ptr [ebp + 0x540], esi */
L_45cf70:
	m->eax = M32((DWORD)(m->ebp + 0x12cu));	/* 45cf70: mov eax, dword ptr [ebp + 0x12c] */
	m->ecx = M32((DWORD)(m->ebp + 0x20u));	/* 45cf76: mov ecx, dword ptr [ebp + 0x20] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45cf79: cmp eax, ecx */
	if (m->sf == m->of) goto L_45cfc6;	/* 45cf7b: jge 0x45cfc6 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x448u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45cf7d: cmp dword ptr [ebp + 0x448], esi */
	if (m->zf || m->sf != m->of) goto L_45cfc6;	/* 45cf83: jle 0x45cfc6 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2b8u)));	/* 45cf85: fld dword ptr [esp + 0x2b8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x544u));	/* 45cf8c: fadd dword ptr [ebp + 0x544] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u));	/* 45cf92: fcom dword ptr [0x4a9424] */
	MF((DWORD)(m->ebp + 0x544u)) = (float)ST(0);	/* 45cf98: fst dword ptr [ebp + 0x544] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45cf9e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45cfa0: test ah, 1 */
	if (!m->zf) goto L_45cff5;	/* 45cfa3: jne 0x45cff5 */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 45cfa5: call 0x49ec14 */
	{ long long p_ = (long long)(int)m->eax * (int)M32((DWORD)(m->ebp + 0x448u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 45cfaa: imul eax, dword ptr [ebp + 0x448] */
	m->ecx = M32((DWORD)(m->ebp + 0x12cu));	/* 45cfb1: mov ecx, dword ptr [ebp + 0x12c] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45cfb7: add ecx, eax */
	m->eax = M32((DWORD)(m->ebp + 0x20u));	/* 45cfb9: mov eax, dword ptr [ebp + 0x20] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45cfbc: cmp ecx, eax */
	if (m->sf != m->of) goto L_45cfce;	/* 45cfbe: jl 0x45cfce */
	M32((DWORD)(m->ebp + 0x12cu)) = m->eax;	/* 45cfc0: mov dword ptr [ebp + 0x12c], eax */
L_45cfc6:
	M32((DWORD)(m->ebp + 0x544u)) = m->esi;	/* 45cfc6: mov dword ptr [ebp + 0x544], esi */
	goto L_45cff7;	/* 45cfcc: jmp 0x45cff7 */
L_45cfce:
	M32((DWORD)(m->ebp + 0x12cu)) = m->ecx;	/* 45cfce: mov dword ptr [ebp + 0x12c], ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x544u)));	/* 45cfd4: fld dword ptr [ebp + 0x544] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 45cfda: call 0x49ec14 */
	M32((DWORD)(m->esp + 0x44u)) = m->eax;	/* 45cfdf: mov dword ptr [esp + 0x44], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x44u)));	/* 45cfe3: fild dword ptr [esp + 0x44] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(m->ebp + 0x544u));	/* 45cfe7: fsubr dword ptr [ebp + 0x544] */
	MF((DWORD)(m->ebp + 0x544u)) = (float)ST(0); FPOP();	/* 45cfed: fstp dword ptr [ebp + 0x544] */
	goto L_45cff7;	/* 45cff3: jmp 0x45cff7 */
L_45cff5:
	ST(0) = ST(0); FPOP();	/* 45cff5: fstp st(0) */
L_45cff7:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x548u)));	/* 45cff7: fld dword ptr [ebp + 0x548] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45cffd: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45d003: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d005: test ah, 0x41 */
	if (!m->zf) goto L_45d030;	/* 45d008: jne 0x45d030 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x548u)));	/* 45d00a: fld dword ptr [ebp + 0x548] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x2b8u));	/* 45d010: fsub dword ptr [esp + 0x2b8] */
	MF((DWORD)(m->ebp + 0x548u)) = (float)ST(0);	/* 45d017: fst dword ptr [ebp + 0x548] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45d01d: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45d023: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d025: test ah, 1 */
	if (m->zf) goto L_45d030;	/* 45d028: je 0x45d030 */
	M32((DWORD)(m->ebp + 0x548u)) = m->esi;	/* 45d02a: mov dword ptr [ebp + 0x548], esi */
L_45d030:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x3f4u)));	/* 45d030: fld dword ptr [ebp + 0x3f4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45d036: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45d03c: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d03e: test ah, 0x41 */
	if (!m->zf) goto L_45d069;	/* 45d041: jne 0x45d069 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x3f4u)));	/* 45d043: fld dword ptr [ebp + 0x3f4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x2b8u));	/* 45d049: fsub dword ptr [esp + 0x2b8] */
	MF((DWORD)(m->ebp + 0x3f4u)) = (float)ST(0);	/* 45d050: fst dword ptr [ebp + 0x3f4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45d056: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45d05c: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d05e: test ah, 1 */
	if (m->zf) goto L_45d069;	/* 45d061: je 0x45d069 */
	M32((DWORD)(m->ebp + 0x3f4u)) = m->esi;	/* 45d063: mov dword ptr [ebp + 0x3f4], esi */
L_45d069:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x3f8u)));	/* 45d069: fld dword ptr [ebp + 0x3f8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45d06f: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45d075: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d077: test ah, 0x41 */
	if (!m->zf) goto L_45d0a2;	/* 45d07a: jne 0x45d0a2 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x3f8u)));	/* 45d07c: fld dword ptr [ebp + 0x3f8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x2b8u));	/* 45d082: fsub dword ptr [esp + 0x2b8] */
	MF((DWORD)(m->ebp + 0x3f8u)) = (float)ST(0);	/* 45d089: fst dword ptr [ebp + 0x3f8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45d08f: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45d095: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d097: test ah, 1 */
	if (m->zf) goto L_45d0a2;	/* 45d09a: je 0x45d0a2 */
	M32((DWORD)(m->ebp + 0x3f8u)) = m->esi;	/* 45d09c: mov dword ptr [ebp + 0x3f8], esi */
L_45d0a2:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x3fcu)));	/* 45d0a2: fld dword ptr [ebp + 0x3fc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45d0a8: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45d0ae: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d0b0: test ah, 0x41 */
	if (!m->zf) goto L_45d0db;	/* 45d0b3: jne 0x45d0db */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x3fcu)));	/* 45d0b5: fld dword ptr [ebp + 0x3fc] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x2b8u));	/* 45d0bb: fsub dword ptr [esp + 0x2b8] */
	MF((DWORD)(m->ebp + 0x3fcu)) = (float)ST(0);	/* 45d0c2: fst dword ptr [ebp + 0x3fc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45d0c8: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45d0ce: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d0d0: test ah, 1 */
	if (m->zf) goto L_45d0db;	/* 45d0d3: je 0x45d0db */
	M32((DWORD)(m->ebp + 0x3fcu)) = m->esi;	/* 45d0d5: mov dword ptr [ebp + 0x3fc], esi */
L_45d0db:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x400u)));	/* 45d0db: fld dword ptr [ebp + 0x400] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45d0e1: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45d0e7: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d0e9: test ah, 0x41 */
	if (!m->zf) goto L_45d114;	/* 45d0ec: jne 0x45d114 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x400u)));	/* 45d0ee: fld dword ptr [ebp + 0x400] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x2b8u));	/* 45d0f4: fsub dword ptr [esp + 0x2b8] */
	MF((DWORD)(m->ebp + 0x400u)) = (float)ST(0);	/* 45d0fb: fst dword ptr [ebp + 0x400] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45d101: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45d107: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d109: test ah, 1 */
	if (m->zf) goto L_45d114;	/* 45d10c: je 0x45d114 */
	M32((DWORD)(m->ebp + 0x400u)) = m->esi;	/* 45d10e: mov dword ptr [ebp + 0x400], esi */
L_45d114:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x180u)));	/* 45d114: fld dword ptr [ebp + 0x180] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x154u));	/* 45d11a: fsub dword ptr [ebp + 0x154] */
	MF((DWORD)(m->esp + 0x58u)) = (float)ST(0); FPOP();	/* 45d120: fstp dword ptr [esp + 0x58] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x184u)));	/* 45d124: fld dword ptr [ebp + 0x184] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x158u));	/* 45d12a: fsub dword ptr [ebp + 0x158] */
	m->edx = M32((DWORD)(m->esp + 0x58u));	/* 45d130: mov edx, dword ptr [esp + 0x58] */
	MF((DWORD)(m->esp + 0x5cu)) = (float)ST(0); FPOP();	/* 45d134: fstp dword ptr [esp + 0x5c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x188u)));	/* 45d138: fld dword ptr [ebp + 0x188] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x15cu));	/* 45d13e: fsub dword ptr [ebp + 0x15c] */
	m->eax = M32((DWORD)(m->esp + 0x5cu));	/* 45d144: mov eax, dword ptr [esp + 0x5c] */
	M32((DWORD)(m->ebp + 0x384u)) = m->edx;	/* 45d148: mov dword ptr [ebp + 0x384], edx */
	M32((DWORD)(m->ebp + 0x388u)) = m->eax;	/* 45d14e: mov dword ptr [ebp + 0x388], eax */
	MF((DWORD)(m->esp + 0x60u)) = (float)ST(0); FPOP();	/* 45d154: fstp dword ptr [esp + 0x60] */
	m->ecx = M32((DWORD)(m->esp + 0x60u));	/* 45d158: mov ecx, dword ptr [esp + 0x60] */
	M32((DWORD)(m->ebp + 0x38cu)) = m->ecx;	/* 45d15c: mov dword ptr [ebp + 0x38c], ecx */
	M32((DWORD)(m->ebp + 0x1e8u)) = m->esi;	/* 45d162: mov dword ptr [ebp + 0x1e8], esi */
	m->edx = M32((DWORD)(m->ebp + 0x110u));	/* 45d168: mov edx, dword ptr [ebp + 0x110] */
	m->eax = M32((DWORD)(m->ebx + 0x202e8d4u));	/* 45d16e: mov eax, dword ptr [ebx + 0x202e8d4] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45d174: cmp edx, eax */
	if (!m->zf) goto L_45d338;	/* 45d176: jne 0x45d338 */
	M32((DWORD)(m->ebp + 0x3f0u)) = m->esi;	/* 45d17c: mov dword ptr [ebp + 0x3f0], esi */
	m->eax = M32((DWORD)(m->ebp + 0x128u));	/* 45d182: mov eax, dword ptr [ebp + 0x128] */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->ebp + 0x1cu)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45d188: cmp eax, dword ptr [ebp + 0x1c] */
	if (m->sf != m->of) goto L_45d197;	/* 45d18b: jl 0x45d197 */
	M32((DWORD)(m->ebp + 0x3f0u)) = 0x1u;	/* 45d18d: mov dword ptr [ebp + 0x3f0], 1 */
L_45d197:
	m->ecx = M32((DWORD)(m->ebp + 0x1cu));	/* 45d197: mov ecx, dword ptr [ebp + 0x1c] */
	m->eax = M32((DWORD)(m->ebp + 0x128u));	/* 45d19a: mov eax, dword ptr [ebp + 0x128] */
	{ DWORD a_ = m->ecx, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45d1a0: add ecx, 0x64 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45d1a3: cmp eax, ecx */
	if (m->sf != m->of) goto L_45d1b5;	/* 45d1a5: jl 0x45d1b5 */
	m->eax = M32((DWORD)(m->ebp + 0x3f0u));	/* 45d1a7: mov eax, dword ptr [ebp + 0x3f0] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x2u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 45d1ad: or al, 2 */
	M32((DWORD)(m->ebp + 0x3f0u)) = m->eax;	/* 45d1af: mov dword ptr [ebp + 0x3f0], eax */
L_45d1b5:
	m->edx = M32((DWORD)(m->ebp + 0x12cu));	/* 45d1b5: mov edx, dword ptr [ebp + 0x12c] */
	m->eax = M32((DWORD)(m->ebp + 0x20u));	/* 45d1bb: mov eax, dword ptr [ebp + 0x20] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45d1be: cmp edx, eax */
	if (m->sf != m->of) goto L_45d1d0;	/* 45d1c0: jl 0x45d1d0 */
	m->eax = M32((DWORD)(m->ebp + 0x3f0u));	/* 45d1c2: mov eax, dword ptr [ebp + 0x3f0] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x4u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 45d1c8: or al, 4 */
	M32((DWORD)(m->ebp + 0x3f0u)) = m->eax;	/* 45d1ca: mov dword ptr [ebp + 0x3f0], eax */
L_45d1d0:
	m->eax = M32((DWORD)(m->ebp + 0x20u));	/* 45d1d0: mov eax, dword ptr [ebp + 0x20] */
	m->ecx = M32((DWORD)(m->ebp + 0x12cu));	/* 45d1d3: mov ecx, dword ptr [ebp + 0x12c] */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45d1d9: add eax, 0x64 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45d1dc: cmp ecx, eax */
	if (m->sf != m->of) goto L_45d1ee;	/* 45d1de: jl 0x45d1ee */
	m->eax = M32((DWORD)(m->ebp + 0x3f0u));	/* 45d1e0: mov eax, dword ptr [ebp + 0x3f0] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x8u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 45d1e6: or al, 8 */
	M32((DWORD)(m->ebp + 0x3f0u)) = m->eax;	/* 45d1e8: mov dword ptr [ebp + 0x3f0], eax */
L_45d1ee:
	m->ecx = M32((DWORD)(m->ebp + 0x130u));	/* 45d1ee: mov ecx, dword ptr [ebp + 0x130] */
	m->eax = M32((DWORD)(m->ebp + 0x28u));	/* 45d1f4: mov eax, dword ptr [ebp + 0x28] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45d1f7: cmp ecx, eax */
	if (m->sf != m->of) goto L_45d209;	/* 45d1f9: jl 0x45d209 */
	m->eax = M32((DWORD)(m->ebp + 0x3f0u));	/* 45d1fb: mov eax, dword ptr [ebp + 0x3f0] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x10u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 45d201: or al, 0x10 */
	M32((DWORD)(m->ebp + 0x3f0u)) = m->eax;	/* 45d203: mov dword ptr [ebp + 0x3f0], eax */
L_45d209:
	m->edx = M32((DWORD)(m->ebp + 0x134u));	/* 45d209: mov edx, dword ptr [ebp + 0x134] */
	m->eax = M32((DWORD)(m->ebp + 0x2cu));	/* 45d20f: mov eax, dword ptr [ebp + 0x2c] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45d212: cmp edx, eax */
	if (m->sf != m->of) goto L_45d224;	/* 45d214: jl 0x45d224 */
	m->eax = M32((DWORD)(m->ebp + 0x3f0u));	/* 45d216: mov eax, dword ptr [ebp + 0x3f0] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x20u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 45d21c: or al, 0x20 */
	M32((DWORD)(m->ebp + 0x3f0u)) = m->eax;	/* 45d21e: mov dword ptr [ebp + 0x3f0], eax */
L_45d224:
	m->eax = M32((DWORD)(m->ebp + 0x138u));	/* 45d224: mov eax, dword ptr [ebp + 0x138] */
	m->ecx = M32((DWORD)(m->ebp + 0x30u));	/* 45d22a: mov ecx, dword ptr [ebp + 0x30] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45d22d: cmp eax, ecx */
	if (m->sf != m->of) goto L_45d23f;	/* 45d22f: jl 0x45d23f */
	m->eax = M32((DWORD)(m->ebp + 0x3f0u));	/* 45d231: mov eax, dword ptr [ebp + 0x3f0] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 45d237: or al, 0x40 */
	M32((DWORD)(m->ebp + 0x3f0u)) = m->eax;	/* 45d239: mov dword ptr [ebp + 0x3f0], eax */
L_45d23f:
	m->ecx = M32((DWORD)(m->ebp + 0x13cu));	/* 45d23f: mov ecx, dword ptr [ebp + 0x13c] */
	m->eax = M32((DWORD)(m->ebp + 0x34u));	/* 45d245: mov eax, dword ptr [ebp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45d248: cmp ecx, eax */
	if (m->sf != m->of) goto L_45d25a;	/* 45d24a: jl 0x45d25a */
	m->eax = M32((DWORD)(m->ebp + 0x3f0u));	/* 45d24c: mov eax, dword ptr [ebp + 0x3f0] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x80u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 45d252: or al, 0x80 */
	M32((DWORD)(m->ebp + 0x3f0u)) = m->eax;	/* 45d254: mov dword ptr [ebp + 0x3f0], eax */
L_45d25a:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x3f4u)));	/* 45d25a: fld dword ptr [ebp + 0x3f4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45d260: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45d266: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d268: test ah, 0x41 */
	if (!m->zf) goto L_45d27c;	/* 45d26b: jne 0x45d27c */
	m->eax = M32((DWORD)(m->ebp + 0x3f0u));	/* 45d26d: mov eax, dword ptr [ebp + 0x3f0] */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 8)) | (((r_) & 0xff) << 8); }	/* 45d273: or ah, 1 */
	M32((DWORD)(m->ebp + 0x3f0u)) = m->eax;	/* 45d276: mov dword ptr [ebp + 0x3f0], eax */
L_45d27c:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x3f8u)));	/* 45d27c: fld dword ptr [ebp + 0x3f8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45d282: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45d288: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d28a: test ah, 0x41 */
	if (!m->zf) goto L_45d29e;	/* 45d28d: jne 0x45d29e */
	m->eax = M32((DWORD)(m->ebp + 0x3f0u));	/* 45d28f: mov eax, dword ptr [ebp + 0x3f0] */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x2u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 8)) | (((r_) & 0xff) << 8); }	/* 45d295: or ah, 2 */
	M32((DWORD)(m->ebp + 0x3f0u)) = m->eax;	/* 45d298: mov dword ptr [ebp + 0x3f0], eax */
L_45d29e:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x3fcu)));	/* 45d29e: fld dword ptr [ebp + 0x3fc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45d2a4: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45d2aa: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d2ac: test ah, 0x41 */
	if (!m->zf) goto L_45d2c0;	/* 45d2af: jne 0x45d2c0 */
	m->eax = M32((DWORD)(m->ebp + 0x3f0u));	/* 45d2b1: mov eax, dword ptr [ebp + 0x3f0] */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x4u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 8)) | (((r_) & 0xff) << 8); }	/* 45d2b7: or ah, 4 */
	M32((DWORD)(m->ebp + 0x3f0u)) = m->eax;	/* 45d2ba: mov dword ptr [ebp + 0x3f0], eax */
L_45d2c0:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x400u)));	/* 45d2c0: fld dword ptr [ebp + 0x400] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45d2c6: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45d2cc: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d2ce: test ah, 0x41 */
	if (!m->zf) goto L_45d2e2;	/* 45d2d1: jne 0x45d2e2 */
	m->eax = M32((DWORD)(m->ebp + 0x3f0u));	/* 45d2d3: mov eax, dword ptr [ebp + 0x3f0] */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x8u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 8)) | (((r_) & 0xff) << 8); }	/* 45d2d9: or ah, 8 */
	M32((DWORD)(m->ebp + 0x3f0u)) = m->eax;	/* 45d2dc: mov dword ptr [ebp + 0x3f0], eax */
L_45d2e2:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x4d4u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45d2e2: cmp dword ptr [ebp + 0x4d4], 1 */
	if (!m->zf) goto L_45d2fa;	/* 45d2e9: jne 0x45d2fa */
	m->eax = M32((DWORD)(m->ebp + 0x3f0u));	/* 45d2eb: mov eax, dword ptr [ebp + 0x3f0] */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x10u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 8)) | (((r_) & 0xff) << 8); }	/* 45d2f1: or ah, 0x10 */
	M32((DWORD)(m->ebp + 0x3f0u)) = m->eax;	/* 45d2f4: mov dword ptr [ebp + 0x3f0], eax */
L_45d2fa:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x12cu)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45d2fa: cmp dword ptr [ebp + 0x12c], esi */
	if (!m->zf && m->sf == m->of) goto L_45d311;	/* 45d300: jg 0x45d311 */
	m->eax = M32((DWORD)(m->ebp + 0x3f0u));	/* 45d302: mov eax, dword ptr [ebp + 0x3f0] */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x20u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 8)) | (((r_) & 0xff) << 8); }	/* 45d308: or ah, 0x20 */
	M32((DWORD)(m->ebp + 0x3f0u)) = m->eax;	/* 45d30b: mov dword ptr [ebp + 0x3f0], eax */
L_45d311:
	m->edx = M32((DWORD)(m->ebp + 0x104u));	/* 45d311: mov edx, dword ptr [ebp + 0x104] */
	{ DWORD a_ = m->edx, b_ = 0x80000001u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 45d317: and edx, 0x80000001 */
	if (!m->sf) goto L_45d324;	/* 45d31d: jns 0x45d324 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 45d31f: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffffeu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 45d320: or edx, 0xfffffffe */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 45d323: inc edx */
L_45d324:
	{ DWORD a_ = m->edx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45d324: cmp edx, 1 */
	if (!m->zf) goto L_45d338;	/* 45d327: jne 0x45d338 */
	m->eax = M32((DWORD)(m->ebp + 0x3f0u));	/* 45d329: mov eax, dword ptr [ebp + 0x3f0] */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 8)) | (((r_) & 0xff) << 8); }	/* 45d32f: or ah, 0x40 */
	M32((DWORD)(m->ebp + 0x3f0u)) = m->eax;	/* 45d332: mov dword ptr [ebp + 0x3f0], eax */
L_45d338:
	m->eax = M32((DWORD)(m->ebp + 0x54cu));	/* 45d338: mov eax, dword ptr [ebp + 0x54c] */
	{ DWORD a_ = m->eax, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45d33e: cmp eax, 7 */
	if (m->sf == m->of) goto L_45d395;	/* 45d341: jge 0x45d395 */
	if (!m->cf && !m->zf) goto L_45d38f;	/* 45d343: ja 0x45d38f */
	switch (m->eax) { case 0: goto L_45d34c; case 1: goto L_45d354; case 2: goto L_45d35c; case 3: goto L_45d364; case 4: goto L_45d36c; case 5: goto L_45d374; case 6: goto L_45d37c; case 7: goto L_45d384; default: abort(); }	/* 45d345: jmp dword ptr [eax*4 + 0x45d3b8] */
L_45d34c:
	m->ecx = (DWORD)(m->ebp + 0x554u);	/* 45d34c: lea ecx, [ebp + 0x554] */
	goto L_45d38a;	/* 45d352: jmp 0x45d38a */
L_45d354:
	m->ecx = (DWORD)(m->ebp + 0xd54u);	/* 45d354: lea ecx, [ebp + 0xd54] */
	goto L_45d38a;	/* 45d35a: jmp 0x45d38a */
L_45d35c:
	m->ecx = (DWORD)(m->ebp + 0x1554u);	/* 45d35c: lea ecx, [ebp + 0x1554] */
	goto L_45d38a;	/* 45d362: jmp 0x45d38a */
L_45d364:
	m->ecx = (DWORD)(m->ebp + 0x2524u);	/* 45d364: lea ecx, [ebp + 0x2524] */
	goto L_45d38a;	/* 45d36a: jmp 0x45d38a */
L_45d36c:
	m->ecx = (DWORD)(m->ebp + 0x34f4u);	/* 45d36c: lea ecx, [ebp + 0x34f4] */
	goto L_45d38a;	/* 45d372: jmp 0x45d38a */
L_45d374:
	m->ecx = (DWORD)(m->ebp + 0x587cu);	/* 45d374: lea ecx, [ebp + 0x587c] */
	goto L_45d38a;	/* 45d37a: jmp 0x45d38a */
L_45d37c:
	m->ecx = (DWORD)(m->ebp + 0x701cu);	/* 45d37c: lea ecx, [ebp + 0x701c] */
	goto L_45d38a;	/* 45d382: jmp 0x45d38a */
L_45d384:
	m->ecx = (DWORD)(m->ebp + 0x40dcu);	/* 45d384: lea ecx, [ebp + 0x40dc] */
L_45d38a:
	m->esp -= 4; M32(m->esp) = 0x45d38fu; native_call(m, 0x46fed0u);	/* 45d38a: call 0x46fed0 */
L_45d38f:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x54cu)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(m->ebp + 0x54cu)) = r_; }	/* 45d38f: inc dword ptr [ebp + 0x54c] */
L_45d395:
	m->edi = M32(m->esp); m->esp += 4;	/* 45d395: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45d396: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 45d397: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 45d398: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x2a0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45d399: add esp, 0x2a0 */
	m->esp += 4 + 8; return;	/* 45d39f: ret 8 */
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
