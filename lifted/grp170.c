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

static void lift_4982f0(X86 *m);

/* hud_pass (0x4982f0), lifted by tools/lift.py */
static void lift_4982f0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4982f0: sub esp, 0x100 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4982f6: push esi */
	m->esi = m->ecx;	/* 4982f7: mov esi, ecx */
	m->eax = M32((DWORD)(m->esi + 0x233c9e8u));	/* 4982f9: mov eax, dword ptr [esi + 0x233c9e8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4982ff: test eax, eax */
	if (m->zf) goto L_4988ce;	/* 498301: je 0x4988ce */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 498307: mov ecx, dword ptr [0xa0e010] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49830d: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 49830e: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49830f: push edi */
	m->esp -= 4; M32(m->esp) = 0x498315u; native_call(m, 0x456b50u);	/* 498310: call 0x456b50 */
	m->edi = (DWORD)(m->esi + 0x74u);	/* 498315: lea edi, [esi + 0x74] */
	m->ecx = m->edi;	/* 498318: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x49831fu; native_call(m, 0x4841d0u);	/* 49831a: call 0x4841d0 */
	m->eax = M32((DWORD)(m->esi + 0xbe16f8u));	/* 49831f: mov eax, dword ptr [esi + 0xbe16f8] */
	m->ebx = 0x1u;	/* 498325: mov ebx, 1 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49832a: cmp eax, ebx */
	if (!m->zf) goto L_498362;	/* 49832c: jne 0x498362 */
	m->eax = M32((DWORD)(m->esi + 0xbe1704u));	/* 49832e: mov eax, dword ptr [esi + 0xbe1704] */
	m->ecx = M32((DWORD)(m->esi + 0xbe1700u));	/* 498334: mov ecx, dword ptr [esi + 0xbe1700] */
	m->edx = M32((DWORD)(m->esi + 0xbe16fcu));	/* 49833a: mov edx, dword ptr [esi + 0xbe16fc] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 498340: push 0x3f800000 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 498345: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 498346: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 498347: push edx */
	m->esp -= 4; M32(m->esp) = 0x49834eu; native_call(m, M32(0x4a91e0u));	/* 498348: call dword ptr [0x4a91e0] */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49834e: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 498353: push 0 */
	m->esp -= 4; M32(m->esp) = 0x49835bu; native_call(m, M32(0x4a91dcu));	/* 498355: call dword ptr [0x4a91dc] */
	{ DWORD v_ = 0x4100u; m->esp -= 4; M32(m->esp) = v_; }	/* 49835b: push 0x4100 */
	goto L_498374;	/* 498360: jmp 0x498374 */
L_498362:
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 498362: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 498367: push 0 */
	m->esp -= 4; M32(m->esp) = 0x49836fu; native_call(m, M32(0x4a91dcu));	/* 498369: call dword ptr [0x4a91dc] */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 49836f: push 0x100 */
L_498374:
	m->ebp = M32((DWORD)(0x4a91e8u));	/* 498374: mov ebp, dword ptr [0x4a91e8] */
	m->esp -= 4; M32(m->esp) = 0x49837cu; native_call(m, m->ebp);	/* 49837a: call ebp */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49837c: push 0x3f800000 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 498381: push ebx */
	m->esp -= 4; M32(m->esp) = 0x498387u; native_call(m, 0x4685f0u);	/* 498382: call 0x4685f0 */
	m->eax = M32((DWORD)(m->esi + 0x233c9d0u));	/* 498387: mov eax, dword ptr [esi + 0x233c9d0] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49838d: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498390: cmp eax, ebx */
	if (m->zf) goto L_4984c5;	/* 498392: je 0x4984c5 */
	m->eax = (DWORD)(m->esi + 0x22e7068u);	/* 498398: lea eax, [esi + 0x22e7068] */
	m->ecx = (DWORD)(m->esi + 0x22e70fcu);	/* 49839e: lea ecx, [esi + 0x22e70fc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4983a4: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4983a5: push ecx */
	m->ecx = m->edi;	/* 4983a6: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x4983adu; native_call(m, 0x4841f0u);	/* 4983a8: call 0x4841f0 */
	m->ecx = m->edi;	/* 4983ad: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x4983b4u; native_call(m, 0x484260u);	/* 4983af: call 0x484260 */
	m->ecx = M32((DWORD)(m->esi + 0x233c9fcu));	/* 4983b4: mov ecx, dword ptr [esi + 0x233c9fc] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4983ba: test ecx, ecx */
	if (!m->zf) goto L_4983eb;	/* 4983bc: jne 0x4983eb */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x23424f2u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4983be: cmp dword ptr [esi + 0x23424f2], 2 */
	if (!m->zf) goto L_4983eb;	/* 4983c5: jne 0x4983eb */
	m->eax = M32((DWORD)(m->esi + 0x2340c64u));	/* 4983c7: mov eax, dword ptr [esi + 0x2340c64] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4983cd: test eax, eax */
	if (m->sf != m->of) goto L_4983eb;	/* 4983cf: jl 0x4983eb */
	m->edx = m->eax;	/* 4983d1: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4983d3: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4983d6: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4983d8: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4983db: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4983dd: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4983e0: add edx, eax */
	M32((DWORD)(m->esi + m->edx*8 + 0x1eccfc0u)) = m->ebx;	/* 4983e2: mov dword ptr [esi + edx*8 + 0x1eccfc0], ebx */
	goto L_49841a;	/* 4983e9: jmp 0x49841a */
L_4983eb:
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4983eb: cmp ecx, ebx */
	if (!m->zf) goto L_49841a;	/* 4983ed: jne 0x49841a */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x233cc10u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4983ef: cmp dword ptr [esi + 0x233cc10], 2 */
	if (!m->zf) goto L_49841a;	/* 4983f6: jne 0x49841a */
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 4983f8: mov eax, dword ptr [esi + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4983fe: test eax, eax */
	if (m->sf != m->of) goto L_49841a;	/* 498400: jl 0x49841a */
	m->ecx = m->eax;	/* 498402: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498404: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498407: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498409: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49840c: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49840e: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498411: add ecx, eax */
	M32((DWORD)(m->esi + m->ecx*8 + 0x1eccfc0u)) = m->ebx;	/* 498413: mov dword ptr [esi + ecx*8 + 0x1eccfc0], ebx */
L_49841a:
	m->ebx = (DWORD)(m->esi + 0x1f36c8u);	/* 49841a: lea ebx, [esi + 0x1f36c8] */
	m->esp -= 4; M32(m->esp) = 0x498425u; { long double r_ = native_call_fp(m, 0x468700u); FPUSH(r_); }	/* 498420: call 0x468700 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 498425: push ecx */
	m->ecx = m->ebx;	/* 498426: mov ecx, ebx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 498428: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x498430u; native_call(m, 0x496f20u);	/* 49842b: call 0x496f20 */
	m->esp -= 4; M32(m->esp) = 0x498435u; { long double r_ = native_call_fp(m, 0x468700u); FPUSH(r_); }	/* 498430: call 0x468700 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 498435: push ecx */
	m->ecx = m->ebx;	/* 498436: mov ecx, ebx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 498438: fstp dword ptr [esp] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49843b: push edi */
	m->esp -= 4; M32(m->esp) = 0x498441u; native_call(m, 0x497d20u);	/* 49843c: call 0x497d20 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 498441: push edi */
	m->ecx = m->ebx;	/* 498442: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x498449u; native_call(m, 0x490da0u);	/* 498444: call 0x490da0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 498449: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49844b: push edi */
	m->ecx = m->ebx;	/* 49844c: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x498453u; native_call(m, 0x45e170u);	/* 49844e: call 0x45e170 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 498453: push edi */
	m->ecx = m->ebx;	/* 498454: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x49845bu; native_call(m, 0x47d060u);	/* 498456: call 0x47d060 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49845b: push edi */
	m->ecx = m->ebx;	/* 49845c: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x498463u; native_call(m, 0x479af0u);	/* 49845e: call 0x479af0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 498463: push edi */
	m->ecx = m->ebx;	/* 498464: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x49846bu; native_call(m, 0x48f970u);	/* 498466: call 0x48f970 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0xbe170cu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49846b: cmp dword ptr [esi + 0xbe170c], 1 */
	if (!m->zf) goto L_4984a2;	/* 498472: jne 0x4984a2 */
	m->edx = M32((DWORD)(m->ebx + 0x9ee060u));	/* 498474: mov edx, dword ptr [ebx + 0x9ee060] */
	m->eax = M32((DWORD)(m->ebx + 0x9ee05cu));	/* 49847a: mov eax, dword ptr [ebx + 0x9ee05c] */
	m->ecx = M32((DWORD)(m->ebx + 0x9ee058u));	/* 498480: mov ecx, dword ptr [ebx + 0x9ee058] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 498486: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 498487: push eax */
	m->edx = (DWORD)(m->ebx + 0x9ee048u);	/* 498488: lea edx, [ebx + 0x9ee048] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49848e: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49848f: push edx */
	m->ecx = m->ebx;	/* 498490: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x498497u; native_call(m, 0x472900u);	/* 498492: call 0x472900 */
	{ DWORD v_ = 0xb60u; m->esp -= 4; M32(m->esp) = v_; }	/* 498497: push 0xb60 */
	m->esp -= 4; M32(m->esp) = 0x4984a2u; native_call(m, M32(0x4a9224u));	/* 49849c: call dword ptr [0x4a9224] */
L_4984a2:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x22f040cu)));	/* 4984a2: fld dword ptr [esi + 0x22f040c] */
	m->eax = M32((DWORD)(m->esi + 0x1f1664u));	/* 4984a8: mov eax, dword ptr [esi + 0x1f1664] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4984ae: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4984af: fstp dword ptr [esp] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4984b2: push eax */
	m->ecx = m->edi;	/* 4984b3: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x4984bau; native_call(m, 0x485af0u);	/* 4984b5: call 0x485af0 */
	{ DWORD v_ = 0xb60u; m->esp -= 4; M32(m->esp) = v_; }	/* 4984ba: push 0xb60 */
	m->esp -= 4; M32(m->esp) = 0x4984c5u; native_call(m, M32(0x4a922cu));	/* 4984bf: call dword ptr [0x4a922c] */
L_4984c5:
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 4984c5: push 0x100 */
	m->esp -= 4; M32(m->esp) = 0x4984ccu; native_call(m, m->ebp);	/* 4984ca: call ebp */
	m->ecx = m->edi;	/* 4984cc: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x4984d3u; native_call(m, 0x484260u);	/* 4984ce: call 0x484260 */
	m->ebx = (DWORD)(m->esi + 0x1f36c8u);	/* 4984d3: lea ebx, [esi + 0x1f36c8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4984d9: push 1 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4984db: push edi */
	m->ecx = m->ebx;	/* 4984dc: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x4984e3u; native_call(m, 0x45e170u);	/* 4984de: call 0x45e170 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x22f040cu)));	/* 4984e3: fld dword ptr [esi + 0x22f040c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4984e9: push ecx */
	m->ecx = M32((DWORD)(m->esi + 0x1f1664u));	/* 4984ea: mov ecx, dword ptr [esi + 0x1f1664] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4984f0: fstp dword ptr [esp] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4984f3: push ecx */
	m->ecx = m->edi;	/* 4984f4: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x4984fbu; native_call(m, 0x485af0u);	/* 4984f6: call 0x485af0 */
	m->eax = M32((DWORD)(m->esi + 0x233c9d0u));	/* 4984fb: mov eax, dword ptr [esi + 0x233c9d0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 498501: test eax, eax */
	if (m->zf) goto L_498535;	/* 498503: je 0x498535 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498505: cmp eax, 2 */
	if (!m->zf) goto L_49851e;	/* 498508: jne 0x49851e */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49850a: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 49850f: push 0 */
	m->esp -= 4; M32(m->esp) = 0x498517u; native_call(m, M32(0x4a91dcu));	/* 498511: call dword ptr [0x4a91dc] */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 498517: push 0x100 */
	m->esp -= 4; M32(m->esp) = 0x49851eu; native_call(m, m->ebp);	/* 49851c: call ebp */
L_49851e:
	m->esp -= 4; M32(m->esp) = 0x498523u; native_call(m, 0x4685c0u);	/* 49851e: call 0x4685c0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 498523: push eax */
	m->esp -= 4; M32(m->esp) = 0x498529u; native_call(m, 0x4685b0u);	/* 498524: call 0x4685b0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 498529: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 49852a: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 49852c: push 0 */
	m->ecx = m->ebx;	/* 49852e: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x498535u; native_call(m, 0x48fde0u);	/* 498530: call 0x48fde0 */
L_498535:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 498535: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 49853a: push 0 */
	m->esp -= 4; M32(m->esp) = 0x498541u; native_call(m, 0x4685f0u);	/* 49853c: call 0x4685f0 */
	m->eax = M32((DWORD)(m->esi + 0x2340ce4u));	/* 498541: mov eax, dword ptr [esi + 0x2340ce4] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 498547: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49854a: test eax, eax */
	if (!m->zf) goto L_498894;	/* 49854c: jne 0x498894 */
	m->eax = M32((DWORD)(m->esi + 0x233c9d0u));	/* 498552: mov eax, dword ptr [esi + 0x233c9d0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 498558: test eax, eax */
	if (!m->zf) goto L_49883d;	/* 49855a: jne 0x49883d */
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 498560: mov eax, dword ptr [esi + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 498566: test eax, eax */
	if (m->sf != m->of) goto L_498585;	/* 498568: jl 0x498585 */
	m->eax = M32((DWORD)(m->esi + 0x2342399u));	/* 49856a: mov eax, dword ptr [esi + 0x2342399] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 498570: test eax, eax */
	if (!m->zf) goto L_498585;	/* 498572: jne 0x498585 */
	m->eax = M32((DWORD)(m->esi + 0x23423a1u));	/* 498574: mov eax, dword ptr [esi + 0x23423a1] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49857a: test eax, eax */
	if (!m->zf) goto L_498585;	/* 49857c: jne 0x498585 */
	m->ecx = m->esi;	/* 49857e: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x498585u; native_call(m, 0x498585u + M32(0x498581u));	/* 0x4913a0 unless the patch DLL retargets it */	/* 498580: call 0x4913a0 */
L_498585:
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 498585: mov eax, dword ptr [esi + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49858b: test eax, eax */
	if (m->sf != m->of) goto L_4985cb;	/* 49858d: jl 0x4985cb */
	m->edx = m->eax;	/* 49858f: mov edx, eax */
	m->edi = 0x1u;	/* 498591: mov edi, 1 */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 498596: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 498599: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49859b: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49859e: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4985a0: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4985a3: add edx, eax */
	{ DWORD a_ = M32((DWORD)(m->esi + m->edx*8 + 0x1eccbbcu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4985a5: cmp dword ptr [esi + edx*8 + 0x1eccbbc], edi */
	if (!m->zf) goto L_4985d0;	/* 4985ac: jne 0x4985d0 */
	m->eax = M32((DWORD)(m->esi + 0x2342399u));	/* 4985ae: mov eax, dword ptr [esi + 0x2342399] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4985b4: test eax, eax */
	if (!m->zf) goto L_4985d0;	/* 4985b6: jne 0x4985d0 */
	m->eax = M32((DWORD)(m->esi + 0x23423a1u));	/* 4985b8: mov eax, dword ptr [esi + 0x23423a1] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4985be: test eax, eax */
	if (!m->zf) goto L_4985d0;	/* 4985c0: jne 0x4985d0 */
	m->ecx = m->esi;	/* 4985c2: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x4985c9u; native_call(m, 0x4985c9u + M32(0x4985c5u));	/* 0x491f50 unless the patch DLL retargets it */	/* 4985c4: call 0x491f50 */
	goto L_4985d0;	/* 4985c9: jmp 0x4985d0 */
L_4985cb:
	m->edi = 0x1u;	/* 4985cb: mov edi, 1 */
L_4985d0:
	m->eax = M32((DWORD)(m->esi + 0x2340cf4u));	/* 4985d0: mov eax, dword ptr [esi + 0x2340cf4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4985d6: test eax, eax */
	if (!m->zf) goto L_4986fa;	/* 4985d8: jne 0x4986fa */
	m->eax = M32((DWORD)(m->esi + 0x2340cecu));	/* 4985de: mov eax, dword ptr [esi + 0x2340cec] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4985e4: test eax, eax */
	if (!m->zf) goto L_4986fa;	/* 4985e6: jne 0x4986fa */
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 4985ec: mov eax, dword ptr [esi + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4985f2: test eax, eax */
	if (m->sf != m->of) goto L_498659;	/* 4985f4: jl 0x498659 */
	m->ecx = M32((DWORD)(m->esi + 0x233c9fcu));	/* 4985f6: mov ecx, dword ptr [esi + 0x233c9fc] */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4985fc: cmp ecx, edi */
	if (!m->zf) goto L_49861a;	/* 4985fe: jne 0x49861a */
	m->edx = m->eax;	/* 498600: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 498602: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 498605: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 498607: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49860a: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49860c: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49860f: add edx, eax */
	{ DWORD a_ = M32((DWORD)(m->esi + m->edx*8 + 0x1eccbbcu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498611: cmp dword ptr [esi + edx*8 + 0x1eccbbc], edi */
	if (m->zf) goto L_49863e;	/* 498618: je 0x49863e */
L_49861a:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49861a: test ecx, ecx */
	if (!m->zf) goto L_498659;	/* 49861c: jne 0x498659 */
	m->eax = M32((DWORD)(m->esi + 0x2340c64u));	/* 49861e: mov eax, dword ptr [esi + 0x2340c64] */
	m->ecx = m->eax;	/* 498624: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498626: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498629: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49862b: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49862e: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498630: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498633: add ecx, eax */
	{ DWORD a_ = M32((DWORD)(m->esi + m->ecx*8 + 0x1eccbbcu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498635: cmp dword ptr [esi + ecx*8 + 0x1eccbbc], edi */
	if (!m->zf) goto L_498659;	/* 49863c: jne 0x498659 */
L_49863e:
	m->eax = M32((DWORD)(m->esi + 0x2342399u));	/* 49863e: mov eax, dword ptr [esi + 0x2342399] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 498644: test eax, eax */
	if (!m->zf) goto L_498659;	/* 498646: jne 0x498659 */
	m->eax = M32((DWORD)(m->esi + 0x23423a1u));	/* 498648: mov eax, dword ptr [esi + 0x23423a1] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49864e: test eax, eax */
	if (!m->zf) goto L_498659;	/* 498650: jne 0x498659 */
	m->ecx = m->esi;	/* 498652: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x498659u; native_call(m, 0x498659u + M32(0x498655u));	/* 0x4926f0 unless the patch DLL retargets it */	/* 498654: call 0x4926f0 */
L_498659:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x234328fu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498659: cmp dword ptr [esi + 0x234328f], edi */
	if (m->zf) goto L_49869e;	/* 49865f: je 0x49869e */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2340d04u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498661: cmp dword ptr [esi + 0x2340d04], edi */
	if (m->zf) goto L_49869e;	/* 498667: je 0x49869e */
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 498669: mov eax, dword ptr [esi + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49866f: test eax, eax */
	if (m->sf != m->of) goto L_49868e;	/* 498671: jl 0x49868e */
	m->edx = m->eax;	/* 498673: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 498675: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 498678: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49867a: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49867d: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49867f: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 498682: add edx, eax */
	{ DWORD a_ = M32((DWORD)(m->esi + m->edx*8 + 0x1eccbbcu)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498684: cmp dword ptr [esi + edx*8 + 0x1eccbbc], 2 */
	if (m->zf) goto L_49869e;	/* 49868c: je 0x49869e */
L_49868e:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2342399u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49868e: cmp dword ptr [esi + 0x2342399], edi */
	if (m->zf) goto L_49869e;	/* 498694: je 0x49869e */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x23423a1u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498696: cmp dword ptr [esi + 0x23423a1], edi */
	if (!m->zf) goto L_4986a5;	/* 49869c: jne 0x4986a5 */
L_49869e:
	m->ecx = m->esi;	/* 49869e: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x4986a5u; native_call(m, 0x4986a5u + M32(0x4986a1u));	/* 0x494930 unless the patch DLL retargets it */	/* 4986a0: call 0x494930 */
L_4986a5:
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 4986a5: mov eax, dword ptr [esi + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4986ab: test eax, eax */
	if (m->sf != m->of) goto L_4986fa;	/* 4986ad: jl 0x4986fa */
	m->ecx = M32((DWORD)(m->esi + 0x234243eu));	/* 4986af: mov ecx, dword ptr [esi + 0x234243e] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4986b5: test ecx, ecx */
	if (m->sf != m->of) goto L_4986fa;	/* 4986b7: jl 0x4986fa */
	m->ecx = m->eax;	/* 4986b9: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4986bb: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4986be: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4986c0: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4986c3: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4986c5: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4986c8: add ecx, eax */
	m->eax = M32((DWORD)(m->esi + m->ecx*8 + 0x1eccb78u));	/* 4986ca: mov eax, dword ptr [esi + ecx*8 + 0x1eccb78] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4986d1: test eax, eax */
	if (!m->zf) goto L_4986fa;	/* 4986d3: jne 0x4986fa */
	m->eax = M32((DWORD)(m->esi + 0x2340d35u));	/* 4986d5: mov eax, dword ptr [esi + 0x2340d35] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4986db: test eax, eax */
	if (!m->zf) goto L_4986fa;	/* 4986dd: jne 0x4986fa */
	m->eax = M32((DWORD)(m->esi + 0x2342399u));	/* 4986df: mov eax, dword ptr [esi + 0x2342399] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4986e5: test eax, eax */
	if (!m->zf) goto L_4986fa;	/* 4986e7: jne 0x4986fa */
	m->eax = M32((DWORD)(m->esi + 0x23423a1u));	/* 4986e9: mov eax, dword ptr [esi + 0x23423a1] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4986ef: test eax, eax */
	if (!m->zf) goto L_4986fa;	/* 4986f1: jne 0x4986fa */
	m->ecx = m->esi;	/* 4986f3: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x4986fau; native_call(m, 0x495140u);	/* 4986f5: call 0x495140 */
L_4986fa:
	m->eax = M32((DWORD)(m->esi + 0x2340ce8u));	/* 4986fa: mov eax, dword ptr [esi + 0x2340ce8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 498700: test eax, eax */
	if (!m->zf) goto L_49871e;	/* 498702: jne 0x49871e */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233cc40u)));	/* 498704: fld dword ptr [esi + 0x233cc40] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 49870a: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 498710: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 498712: test ah, 0x41 */
	if (!m->zf) goto L_49871e;	/* 498715: jne 0x49871e */
	m->ecx = m->esi;	/* 498717: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49871eu; native_call(m, 0x495190u);	/* 498719: call 0x495190 */
L_49871e:
	m->eax = M32((DWORD)(m->esi + 0x2340d35u));	/* 49871e: mov eax, dword ptr [esi + 0x2340d35] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 498724: test eax, eax */
	if (m->zf) goto L_49872f;	/* 498726: je 0x49872f */
	m->ecx = m->esi;	/* 498728: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49872fu; native_call(m, 0x4953d0u);	/* 49872a: call 0x4953d0 */
L_49872f:
	m->eax = M32((DWORD)(m->esi + 0x2342399u));	/* 49872f: mov eax, dword ptr [esi + 0x2342399] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 498735: test eax, eax */
	if (!m->zf) goto L_49874a;	/* 498737: jne 0x49874a */
	m->eax = M32((DWORD)(m->esi + 0x23423a1u));	/* 498739: mov eax, dword ptr [esi + 0x23423a1] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49873f: test eax, eax */
	if (!m->zf) goto L_49874a;	/* 498741: jne 0x49874a */
	m->ecx = m->esi;	/* 498743: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49874au; native_call(m, 0x496610u);	/* 498745: call 0x496610 */
L_49874a:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2342399u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49874a: cmp dword ptr [esi + 0x2342399], edi */
	if (!m->zf) goto L_498779;	/* 498750: jne 0x498779 */
	m->eax = M32((DWORD)(m->esi + 0x23428f6u));	/* 498752: mov eax, dword ptr [esi + 0x23428f6] */
	m->edx = m->eax;	/* 498758: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49875a: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49875d: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49875f: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 498762: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 498764: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 498767: add edx, eax */
	{ DWORD a_ = M32((DWORD)(m->esi + m->edx*8 + 0x1eccbbcu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498769: cmp dword ptr [esi + edx*8 + 0x1eccbbc], edi */
	if (!m->zf) goto L_498779;	/* 498770: jne 0x498779 */
	m->ecx = m->esi;	/* 498772: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x498779u; native_call(m, 0x496a30u);	/* 498774: call 0x496a30 */
L_498779:
	m->eax = M32((DWORD)(m->esi + 0x233c9fcu));	/* 498779: mov eax, dword ptr [esi + 0x233c9fc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49877f: test eax, eax */
	if (!m->zf) goto L_498842;	/* 498781: jne 0x498842 */
	m->ecx = m->esi;	/* 498787: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49878eu; native_call(m, 0x496b80u);	/* 498789: call 0x496b80 */
	m->eax = M32((DWORD)(m->esi + 0x233c9fcu));	/* 49878e: mov eax, dword ptr [esi + 0x233c9fc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 498794: test eax, eax */
	if (!m->zf) goto L_498842;	/* 498796: jne 0x498842 */
	m->eax = M32((DWORD)(m->esi + 0x23424f2u));	/* 49879c: mov eax, dword ptr [esi + 0x23424f2] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4987a2: test eax, eax */
	if (m->sf != m->of) goto L_498842;	/* 4987a4: jl 0x498842 */
	m->eax = M32((DWORD)(m->esi + 0x2340c64u));	/* 4987aa: mov eax, dword ptr [esi + 0x2340c64] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4987b0: test eax, eax */
	if (m->sf != m->of) goto L_498842;	/* 4987b2: jl 0x498842 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4987b8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4987bd: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4987c2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4987c7: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4987d2u; native_call(m, M32(0x4a9228u));	/* 4987cc: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x6u; m->esp -= 4; M32(m->esp) = v_; }	/* 4987d2: push 6 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 4987d4: push 0x10 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 4987d6: push 0x10 */
	m->ecx = m->esi;	/* 4987d8: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x4987dfu; native_call(m, 0x496820u);	/* 4987da: call 0x496820 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4987df: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4987e4: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4987e9: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4987ee: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4987f8u; native_call(m, 0x44ad30u);	/* 4987f3: call 0x44ad30 */
	m->eax = M32((DWORD)(m->esi + 0x23424f2u));	/* 4987f8: mov eax, dword ptr [esi + 0x23424f2] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4987fe: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 498801: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_498812;	/* 498803: jle 0x498812 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 498805: push eax */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 498806: lea eax, [esp + 0x14] */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 49880a: push 0x4b0320 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49880f: push eax */
	goto L_498820;	/* 498810: jmp 0x498820 */
L_498812:
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 498812: add eax, 0xa */
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 498815: lea ecx, [esp + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 498819: push eax */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 49881a: push 0x4b0320 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49881f: push ecx */
L_498820:
	m->esp -= 4; M32(m->esp) = 0x498825u; native_call(m, 0x49e9ddu);	/* 498820: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 498825: add esp, 0xc */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 498828: lea edx, [esp + 0x10] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 49882c: push 0x10 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49882e: push edx */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 49882f: push 0x10 */
	{ DWORD v_ = 0x28u; m->esp -= 4; M32(m->esp) = v_; }	/* 498831: push 0x28 */
	m->esp -= 4; M32(m->esp) = 0x498838u; native_call(m, 0x44ad60u);	/* 498833: call 0x44ad60 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 498838: add esp, 0x10 */
	goto L_498842;	/* 49883b: jmp 0x498842 */
L_49883d:
	m->edi = 0x1u;	/* 49883d: mov edi, 1 */
L_498842:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x22e7184u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498842: cmp dword ptr [esi + 0x22e7184], edi */
	if (!m->zf) goto L_498851;	/* 498848: jne 0x498851 */
	m->ecx = m->esi;	/* 49884a: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x498851u; native_call(m, 0x496240u);	/* 49884c: call 0x496240 */
L_498851:
	m->ecx = m->esi;	/* 498851: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x498858u; native_call(m, 0x48b420u);	/* 498853: call 0x48b420 */
	{ DWORD a_ = M32((DWORD)(0x83a9d4u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498858: cmp dword ptr [0x83a9d4], edi */
	if (!m->zf) goto L_498867;	/* 49885e: jne 0x498867 */
	m->ecx = m->esi;	/* 498860: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x498867u; native_call(m, 0x498867u + M32(0x498863u));	/* 0x495510 unless the patch DLL retargets it */	/* 498862: call 0x495510 */
L_498867:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2340cecu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498867: cmp dword ptr [esi + 0x2340cec], edi */
	if (!m->zf) goto L_498876;	/* 49886d: jne 0x498876 */
	m->ecx = m->esi;	/* 49886f: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x498876u; native_call(m, 0x4955a0u);	/* 498871: call 0x4955a0 */
L_498876:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2340cf4u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498876: cmp dword ptr [esi + 0x2340cf4], edi */
	if (!m->zf) goto L_498885;	/* 49887c: jne 0x498885 */
	m->ecx = m->esi;	/* 49887e: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x498885u; native_call(m, 0x495610u);	/* 498880: call 0x495610 */
L_498885:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2340d1du)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498885: cmp dword ptr [esi + 0x2340d1d], edi */
	if (!m->zf) goto L_498894;	/* 49888b: jne 0x498894 */
	m->ecx = m->esi;	/* 49888d: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x498894u; native_call(m, 0x496d10u);	/* 49888f: call 0x496d10 */
L_498894:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x2342f02u)));	/* 498894: fld dword ptr [esi + 0x2342f02] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 49889a: fcomp dword ptr [0x4a93e8] */
	m->edi = M32(m->esp); m->esp += 4;	/* 4988a0: pop edi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4988a1: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4988a2: pop ebx */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4988a3: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4988a5: test ah, 0x41 */
	if (!m->zf) goto L_4988b4;	/* 4988a8: jne 0x4988b4 */
	m->eax = M32((DWORD)(m->esi + 0x2342399u));	/* 4988aa: mov eax, dword ptr [esi + 0x2342399] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4988b0: test eax, eax */
	if (m->zf) goto L_4988c7;	/* 4988b2: je 0x4988c7 */
L_4988b4:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233cc4cu)));	/* 4988b4: fld dword ptr [esi + 0x233cc4c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 4988ba: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4988c0: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4988c2: test ah, 0x41 */
	if (!m->zf) goto L_4988ce;	/* 4988c5: jne 0x4988ce */
L_4988c7:
	m->ecx = m->esi;	/* 4988c7: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x4988ceu; native_call(m, 0x496c20u);	/* 4988c9: call 0x496c20 */
L_4988ce:
	m->esi = M32(m->esp); m->esp += 4;	/* 4988ce: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4988cf: add esp, 0x100 */
	m->esp += 4 + 0; return;	/* 4988d5: ret  */
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
