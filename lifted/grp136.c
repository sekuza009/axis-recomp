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

static void lift_43ef70(X86 *m);

/* menuState800_gameRoom (0x43ef70), lifted by tools/lift.py */
static void lift_43ef70(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ef70: push ecx */
	m->eax = M32((DWORD)(0x76d42cu));	/* 43ef71: mov eax, dword ptr [0x76d42c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43ef76: test eax, eax */
	if (m->zf) goto L_43f006;	/* 43ef78: je 0x43f006 */
	m->eax = M32((DWORD)(0x67ef34u));	/* 43ef7e: mov eax, dword ptr [0x67ef34] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43ef83: push esi */
	m->esi = M32((DWORD)(0x4ded68u));	/* 43ef84: mov esi, dword ptr [0x4ded68] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43ef8a: sub eax, esi */
	M32((DWORD)(m->esp + 0x4u)) = m->eax;	/* 43ef8c: mov dword ptr [esp + 4], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x4u)));	/* 43ef90: fild dword ptr [esp + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 43ef94: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a941cu));	/* 43ef9a: fmul dword ptr [0x4a941c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 43efa0: call 0x49ec14 */
	m->ecx = M32((DWORD)(0x67fb38u));	/* 43efa5: mov ecx, dword ptr [0x67fb38] */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 43efab: add esi, eax */
	M32((DWORD)(0x4ded68u)) = m->esi;	/* 43efad: mov dword ptr [0x4ded68], esi */
	m->esi = M32((DWORD)(0x4ded6cu));	/* 43efb3: mov esi, dword ptr [0x4ded6c] */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43efb9: sub ecx, esi */
	M32((DWORD)(m->esp + 0x4u)) = m->ecx;	/* 43efbb: mov dword ptr [esp + 4], ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x4u)));	/* 43efbf: fild dword ptr [esp + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 43efc3: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a941cu));	/* 43efc9: fmul dword ptr [0x4a941c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 43efcf: call 0x49ec14 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680bc0u)));	/* 43efd4: fld dword ptr [0x680bc0] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 43efda: fsub dword ptr [0x4b071c] */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 43efe0: add esi, eax */
	M32((DWORD)(0x4ded6cu)) = m->esi;	/* 43efe2: mov dword ptr [0x4ded6c], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43efe8: pop esi */
	MF((DWORD)(0x680bc0u)) = (float)ST(0);	/* 43efe9: fst dword ptr [0x680bc0] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 43efef: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 43eff5: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 43eff7: test ah, 1 */
	if (m->zf) goto L_43f006;	/* 43effa: je 0x43f006 */
	M32((DWORD)(0x76d42cu)) = 0x0u;	/* 43effc: mov dword ptr [0x76d42c], 0 */
L_43f006:
	m->eax = M32((DWORD)(0x9dd834u));	/* 43f006: mov eax, dword ptr [0x9dd834] */
	{ DWORD a_ = m->eax, b_ = 0x63u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43f00b: cmp eax, 0x63 */
	if (!m->cf && !m->zf) goto L_43f0c7;	/* 43f00e: ja 0x43f0c7 */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43f014: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x43f0f0u))) & 0xff) << 0);	/* 43f016: mov dl, byte ptr [eax + 0x43f0f0] */
	switch (m->edx) { case 0: goto L_43f085; case 1: goto L_43f096; case 2: goto L_43f0a7; case 3: goto L_43f0b8; case 4: goto L_43f023; case 5: goto L_43f034; case 6: goto L_43f045; case 7: goto L_43f056; case 8: goto L_43f0c7; default: abort(); }	/* 43f01c: jmp dword ptr [edx*4 + 0x43f0cc] */
L_43f023:
	m->esp -= 4; M32(m->esp) = 0x43f028u; native_call(m, 0x43df80u);	/* 43f023: call 0x43df80 */
	m->esp -= 4; M32(m->esp) = 0x43f02du; native_call(m, 0x441740u);	/* 43f028: call 0x441740 */
	m->esp -= 4; M32(m->esp) = 0x43f032u; native_call(m, 0x4392c0u);	/* 43f02d: call 0x4392c0 */
	m->ecx = M32(m->esp); m->esp += 4;	/* 43f032: pop ecx */
	m->esp += 4 + 0; return;	/* 43f033: ret  */
L_43f034:
	m->esp -= 4; M32(m->esp) = 0x43f039u; native_call(m, 0x43e290u);	/* 43f034: call 0x43e290 */
	m->esp -= 4; M32(m->esp) = 0x43f03eu; native_call(m, 0x441740u);	/* 43f039: call 0x441740 */
	m->esp -= 4; M32(m->esp) = 0x43f043u; native_call(m, 0x4399c0u);	/* 43f03e: call 0x4399c0 */
	m->ecx = M32(m->esp); m->esp += 4;	/* 43f043: pop ecx */
	m->esp += 4 + 0; return;	/* 43f044: ret  */
L_43f045:
	m->esp -= 4; M32(m->esp) = 0x43f04au; native_call(m, 0x43e610u);	/* 43f045: call 0x43e610 */
	m->esp -= 4; M32(m->esp) = 0x43f04fu; native_call(m, 0x441740u);	/* 43f04a: call 0x441740 */
	m->esp -= 4; M32(m->esp) = 0x43f054u; native_call(m, 0x439e00u);	/* 43f04f: call 0x439e00 */
	m->ecx = M32(m->esp); m->esp += 4;	/* 43f054: pop ecx */
	m->esp += 4 + 0; return;	/* 43f055: ret  */
L_43f056:
	m->esp -= 4; M32(m->esp) = 0x43f05bu; native_call(m, 0x43e720u);	/* 43f056: call 0x43e720 */
	{ DWORD a_ = M32((DWORD)(0x67ef14u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43f05b: cmp dword ptr [0x67ef14], 1 */
	if (!m->zf) goto L_43f079;	/* 43f062: jne 0x43f079 */
	{ DWORD a_ = M32((DWORD)(0x9dce48u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43f064: cmp dword ptr [0x9dce48], 2 */
	if (!m->zf) goto L_43f079;	/* 43f06b: jne 0x43f079 */
	m->esp -= 4; M32(m->esp) = 0x43f072u; native_call(m, 0x441740u);	/* 43f06d: call 0x441740 */
	m->esp -= 4; M32(m->esp) = 0x43f077u; native_call(m, 0x43df00u);	/* 43f072: call 0x43df00 */
	m->ecx = M32(m->esp); m->esp += 4;	/* 43f077: pop ecx */
	m->esp += 4 + 0; return;	/* 43f078: ret  */
L_43f079:
	m->esp -= 4; M32(m->esp) = 0x43f07eu; native_call(m, 0x441740u);	/* 43f079: call 0x441740 */
	m->esp -= 4; M32(m->esp) = 0x43f083u; native_call(m, 0x437e00u);	/* 43f07e: call 0x437e00 */
	m->ecx = M32(m->esp); m->esp += 4;	/* 43f083: pop ecx */
	m->esp += 4 + 0; return;	/* 43f084: ret  */
L_43f085:
	m->esp -= 4; M32(m->esp) = 0x43f08au; native_call(m, 0x441740u);	/* 43f085: call 0x441740 */
	m->esp -= 4; M32(m->esp) = 0x43f08fu; native_call(m, 0x437a10u);	/* 43f08a: call 0x437a10 */
	m->esp -= 4; M32(m->esp) = 0x43f094u; native_call(m, 0x43e7b0u);	/* 43f08f: call 0x43e7b0 */
	m->ecx = M32(m->esp); m->esp += 4;	/* 43f094: pop ecx */
	m->esp += 4 + 0; return;	/* 43f095: ret  */
L_43f096:
	m->esp -= 4; M32(m->esp) = 0x43f09bu; native_call(m, 0x441740u);	/* 43f096: call 0x441740 */
	m->esp -= 4; M32(m->esp) = 0x43f0a0u; native_call(m, 0x437a10u);	/* 43f09b: call 0x437a10 */
	m->esp -= 4; M32(m->esp) = 0x43f0a5u; native_call(m, 0x43ea10u);	/* 43f0a0: call 0x43ea10 */
	m->ecx = M32(m->esp); m->esp += 4;	/* 43f0a5: pop ecx */
	m->esp += 4 + 0; return;	/* 43f0a6: ret  */
L_43f0a7:
	m->esp -= 4; M32(m->esp) = 0x43f0acu; native_call(m, 0x441740u);	/* 43f0a7: call 0x441740 */
	m->esp -= 4; M32(m->esp) = 0x43f0b1u; native_call(m, 0x437a10u);	/* 43f0ac: call 0x437a10 */
	m->esp -= 4; M32(m->esp) = 0x43f0b6u; native_call(m, 0x43ed20u);	/* 43f0b1: call 0x43ed20 */
	m->ecx = M32(m->esp); m->esp += 4;	/* 43f0b6: pop ecx */
	m->esp += 4 + 0; return;	/* 43f0b7: ret  */
L_43f0b8:
	m->esp -= 4; M32(m->esp) = 0x43f0bdu; native_call(m, 0x441740u);	/* 43f0b8: call 0x441740 */
	m->esp -= 4; M32(m->esp) = 0x43f0c2u; native_call(m, 0x437a10u);	/* 43f0bd: call 0x437a10 */
	m->esp -= 4; M32(m->esp) = 0x43f0c7u; native_call(m, 0x43ede0u);	/* 43f0c2: call 0x43ede0 */
L_43f0c7:
	m->ecx = M32(m->esp); m->esp += 4;	/* 43f0c7: pop ecx */
	m->esp += 4 + 0; return;	/* 43f0c8: ret  */
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
