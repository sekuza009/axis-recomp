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

static void lift_48c830(X86 *m);

/* net_processGamePacket (0x48c830), lifted by tools/lift.py */
static void lift_48c830(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 48c830: mov eax, dword ptr [esp + 8] */
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48c834: sub esp, 0x3c */
	{ DWORD a_ = m->eax, b_ = 0x40u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48c837: cmp eax, 0x40 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48c83a: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48c83b: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48c83c: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48c83d: push edi */
	m->ebp = m->ecx;	/* 48c83e: mov ebp, ecx */
	if (!m->zf) goto L_48db96;	/* 48c840: jne 0x48db96 */
	m->eax = M32((DWORD)(m->ebp + 0x2340d1du));	/* 48c846: mov eax, dword ptr [ebp + 0x2340d1d] */
	m->ebx = M32((DWORD)(m->esp + 0x58u));	/* 48c84c: mov ebx, dword ptr [esp + 0x58] */
	m->edi = 0x1u;	/* 48c850: mov edi, 1 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48c855: cmp eax, edi */
	if (!m->zf) goto L_48c8b0;	/* 48c857: jne 0x48c8b0 */
	m->eax = M32((DWORD)(m->ebp + 0x2340d08u));	/* 48c859: mov eax, dword ptr [ebp + 0x2340d08] */
	m->ecx = (DWORD)(m->ebp + 0x2340d29u);	/* 48c85f: lea ecx, [ebp + 0x2340d29] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48c865: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48c866: push edi */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c867: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48c869: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48c86fu; native_call(m, 0x46cc30u);	/* 48c86a: call 0x46cc30 */
	m->edx = M32((DWORD)(m->ebp + 0x2340d08u));	/* 48c86f: mov edx, dword ptr [ebp + 0x2340d08] */
	m->eax = (DWORD)(m->esp + 0x60u);	/* 48c875: lea eax, [esp + 0x60] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48c879: push edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48c87a: push edi */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c87b: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48c87d: push eax */
	m->esp -= 4; M32(m->esp) = 0x48c883u; native_call(m, 0x46cc30u);	/* 48c87e: call 0x46cc30 */
	m->ecx = M32((DWORD)(m->ebp + 0x2340d08u));	/* 48c883: mov ecx, dword ptr [ebp + 0x2340d08] */
	m->edx = (DWORD)(m->esp + 0x74u);	/* 48c889: lea edx, [esp + 0x74] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48c88d: push ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48c88e: push edi */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c88f: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48c891: push edx */
	m->esp -= 4; M32(m->esp) = 0x48c897u; native_call(m, 0x46cc30u);	/* 48c892: call 0x46cc30 */
	m->eax = M32((DWORD)(m->ebp + 0x2340d08u));	/* 48c897: mov eax, dword ptr [ebp + 0x2340d08] */
	m->ecx = M32((DWORD)(m->esp + 0x84u));	/* 48c89d: mov ecx, dword ptr [esp + 0x84] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48c8a4: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48c8a5: push ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48c8a6: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48c8a7: push ebx */
	m->esp -= 4; M32(m->esp) = 0x48c8adu; native_call(m, 0x46cc30u);	/* 48c8a8: call 0x46cc30 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48c8ad: add esp, 0x40 */
L_48c8b0:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x233cc20u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48c8b0: cmp dword ptr [ebp + 0x233cc20], edi */
	if (!m->zf) goto L_48c8c2;	/* 48c8b6: jne 0x48c8c2 */
	{ DWORD a_ = M8((DWORD)(m->ebx + 0x1u)), b_ = 0x1u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48c8b8: cmp byte ptr [ebx + 1], 1 */
	if (!m->zf) goto L_48db96;	/* 48c8bc: jne 0x48db96 */
L_48c8c2:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48c8c2: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x1u))) & 0xff) << 0);	/* 48c8c4: mov al, byte ptr [ebx + 1] */
	{ DWORD a_ = m->eax, b_ = 0xeu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48c8c7: cmp eax, 0xe */
	if (!m->cf && !m->zf) goto L_48db8d;	/* 48c8ca: ja 0x48db8d */
	switch (m->eax) { case 0: goto L_48c8d7; case 1: goto L_48ccbb; case 2: goto L_48d209; case 3: goto L_48d4d9; case 4: goto L_48d531; case 5: goto L_48d595; case 6: goto L_48d625; case 7: goto L_48d64d; case 8: goto L_48d68f; case 9: goto L_48d781; case 10: goto L_48d809; case 11: goto L_48d960; case 12: goto L_48d0e3; case 13: goto L_48dad6; case 14: goto L_48daf4; default: abort(); }	/* 48c8d0: jmp dword ptr [eax*4 + 0x48dba0] */
L_48c8d7:
	m->edx = (DWORD)(int)(short)(M16((DWORD)(m->ebx + 0x5u)));	/* 48c8d7: movsx edx, word ptr [ebx + 5] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48c8db: xor eax, eax */
	M32((DWORD)(m->esp + 0x58u)) = m->edx;	/* 48c8dd: mov dword ptr [esp + 0x58], edx */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x4u))) & 0xff) << 0);	/* 48c8e1: mov al, byte ptr [ebx + 4] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48c8e4: xor edx, edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x58u)));	/* 48c8e6: fild dword ptr [esp + 0x58] */
	m->esi = m->eax;	/* 48c8ea: mov esi, eax */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0xbu))) & 0xff) << 0);	/* 48c8ec: mov dl, byte ptr [ebx + 0xb] */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48c8ef: shr eax, 1 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 48c8f1: fmul dword ptr [0x4a9418] */
	{ DWORD a_ = m->eax, b_ = 0x7u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48c8f7: and eax, 7 */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 48c8fa: mov dword ptr [esp + 0x14], eax */
	m->eax = (DWORD)(int)(short)(M16((DWORD)(m->ebx + 0x7u)));	/* 48c8fe: movsx eax, word ptr [ebx + 7] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 48c902: fstp dword ptr [esp + 0x10] */
	m->ecx = (DWORD)(int)(short)(M16((DWORD)(m->ebx + 0x9u)));	/* 48c906: movsx ecx, word ptr [ebx + 9] */
	M32((DWORD)(m->esp + 0x58u)) = m->eax;	/* 48c90a: mov dword ptr [esp + 0x58], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x58u)));	/* 48c90e: fild dword ptr [esp + 0x58] */
	M32((DWORD)(m->esp + 0x58u)) = m->ecx;	/* 48c912: mov dword ptr [esp + 0x58], ecx */
	{ DWORD a_ = m->esi, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 48c916: shr esi, 4 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 48c919: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 48c91f: fstp dword ptr [esp + 0x18] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x58u)));	/* 48c923: fild dword ptr [esp + 0x58] */
	M32((DWORD)(m->esp + 0x58u)) = m->edx;	/* 48c927: mov dword ptr [esp + 0x58], edx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 48c92b: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 48c931: fstp dword ptr [esp + 0x1c] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x58u)));	/* 48c935: fild dword ptr [esp + 0x58] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa494u));	/* 48c939: fmul dword ptr [0x4aa494] */
	MF((DWORD)(m->esp + 0x58u)) = (float)ST(0);	/* 48c93f: fst dword ptr [esp + 0x58] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa288u)); FPOP();	/* 48c943: fcomp dword ptr [0x4aa288] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48c949: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48c94b: test ah, 0x41 */
	if (!m->zf) goto L_48c95e;	/* 48c94e: jne 0x48c95e */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x58u)));	/* 48c950: fld dword ptr [esp + 0x58] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a94c8u));	/* 48c954: fsub dword ptr [0x4a94c8] */
	MF((DWORD)(m->esp + 0x58u)) = (float)ST(0); FPOP();	/* 48c95a: fstp dword ptr [esp + 0x58] */
L_48c95e:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48c95e: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0xcu))) & 0xff) << 0);	/* 48c960: mov al, byte ptr [ebx + 0xc] */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 48c963: mov dword ptr [esp + 0x20], eax */
	m->eax = (DWORD)(m->esi + m->esi*2 + 0x0u);	/* 48c967: lea eax, [esi + esi*2] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 48c96a: fild dword ptr [esp + 0x20] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48c96e: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48c971: sub eax, esi */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa494u));	/* 48c973: fmul dword ptr [0x4aa494] */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 48c979: lea ecx, [eax + eax*2] */
	m->edx = (DWORD)(m->esi + m->ecx*8 + 0x0u);	/* 48c97c: lea edx, [esi + ecx*8] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 48c97f: fstp dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->ebp + m->edx*2 + 0x1755230u));	/* 48c983: mov eax, dword ptr [ebp + edx*2 + 0x1755230] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48c98a: test eax, eax */
	if (!m->zf) goto L_48c9b2;	/* 48c98c: jne 0x48c9b2 */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 48c98e: mov eax, dword ptr [ebp + 0x234240d] */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48c994: shl eax, 4 */
	{ DWORD a_ = m->esi, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 48c997: shl esi, 4 */
	M32((DWORD)(m->eax + m->ebp*1 + 0x2343006u)) = m->edi;	/* 48c99a: mov dword ptr [eax + ebp + 0x2343006], edi */
	M32((DWORD)(m->esi + m->ebp*1 + 0x234300eu)) = m->edi;	/* 48c9a1: mov dword ptr [esi + ebp + 0x234300e], edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 48c9a8: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48c9a9: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 48c9aa: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48c9ab: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48c9ac: add esp, 0x3c */
	m->esp += 4 + 12; return;	/* 48c9af: ret 0xc */
L_48c9b2:
	m->ecx = m->esi;	/* 48c9b2: mov ecx, esi */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48c9b4: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48c9b7: add ecx, esi */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48c9b9: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48c9bc: add ecx, esi */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48c9be: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48c9c1: add ecx, esi */
	m->edx = (m->edx & 0xffff0000u) | ((M16((DWORD)(m->ebp + m->ecx*8 + 0x1ecce60u))) & 0xffff);	/* 48c9c3: mov dx, word ptr [ebp + ecx*8 + 0x1ecce60] */
	m->edi = (DWORD)(m->ebp + m->ecx*8 + 0x1ecca70u);	/* 48c9cb: lea edi, [ebp + ecx*8 + 0x1ecca70] */
	{ DWORD a_ = (m->edx & 0xffff), b_ = M16((DWORD)(m->ebx + 0x2u)) & 0xffffu, r_ = a_ ^ b_; FLAGS(r_, 16); m->cf = 0; m->of = 0; m->edx = (m->edx & 0xffff0000u) | ((r_) & 0xffff); }	/* 48c9d2: xor dx, word ptr [ebx + 2] */
	{ DWORD a_ = ((m->edx >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48c9d6: test dh, 0x40 */
	if (m->zf) goto L_48c9e7;	/* 48c9d9: je 0x48c9e7 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48c9db: push esi */
	m->ecx = (DWORD)(m->ebp + 0x1f36c8u);	/* 48c9dc: lea ecx, [ebp + 0x1f36c8] */
	m->esp -= 4; M32(m->esp) = 0x48c9e7u; native_call(m, 0x45dca0u);	/* 48c9e2: call 0x45dca0 */
L_48c9e7:
	m->eax = M32((DWORD)(m->edi + 0x108u));	/* 48c9e7: mov eax, dword ptr [edi + 0x108] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48c9ed: test eax, eax */
	if (!m->zf) goto L_48ca56;	/* 48c9ef: jne 0x48ca56 */
	{ DWORD a_ = M8((DWORD)(m->ebx + 0x4u)), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48c9f1: test byte ptr [ebx + 4], 1 */
	if (m->zf) goto L_48ca56;	/* 48c9f5: je 0x48ca56 */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 48c9f7: mov eax, dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 48c9fb: mov edx, dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 48c9ff: mov ecx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 48ca03: mov dword ptr [esp + 0x24], eax */
	M32((DWORD)(m->esp + 0x38u)) = m->eax;	/* 48ca07: mov dword ptr [esp + 0x38], eax */
	m->eax = M32((DWORD)(m->esp + 0x58u));	/* 48ca0b: mov eax, dword ptr [esp + 0x58] */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 48ca0f: mov dword ptr [esp + 0x2c], edx */
	M32((DWORD)(m->esp + 0x40u)) = m->edx;	/* 48ca13: mov dword ptr [esp + 0x40], edx */
	M32((DWORD)(m->esp + 0x44u)) = m->eax;	/* 48ca17: mov dword ptr [esp + 0x44], eax */
	m->eax = M32((DWORD)(m->esp + 0x50u));	/* 48ca1b: mov eax, dword ptr [esp + 0x50] */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 48ca1f: lea edx, [esp + 0x30] */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 48ca23: mov dword ptr [esp + 0x28], ecx */
	M32((DWORD)(m->esp + 0x3cu)) = m->ecx;	/* 48ca27: mov dword ptr [esp + 0x3c], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 48ca2b: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ca2f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ca30: push eax */
	M32((DWORD)(m->esp + 0x50u)) = m->ecx;	/* 48ca31: mov dword ptr [esp + 0x50], ecx */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 48ca35: push -1 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48ca37: push esi */
	m->ecx = (DWORD)(m->ebp + 0x1f36c8u);	/* 48ca38: lea ecx, [ebp + 0x1f36c8] */
	M32((DWORD)(m->esp + 0x40u)) = m->esi;	/* 48ca3e: mov dword ptr [esp + 0x40], esi */
	M32((DWORD)(m->esp + 0x44u)) = 0x0u;	/* 48ca42: mov dword ptr [esp + 0x44], 0 */
	m->esp -= 4; M32(m->esp) = 0x48ca4fu; native_call(m, 0x45dc00u);	/* 48ca4a: call 0x45dc00 */
	m->ecx = m->ebp;	/* 48ca4f: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x48ca56u; native_call(m, 0x462150u);	/* 48ca51: call 0x462150 */
L_48ca56:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x120u)));	/* 48ca56: fld dword ptr [edi + 0x120] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 48ca5c: fadd dword ptr [0x4a9418] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 48ca62: mov eax, dword ptr [esp + 0x14] */
	m->edx = 0x1u;	/* 48ca66: mov edx, 1 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48ca6b: xor ecx, ecx */
	M32((DWORD)(m->edi + 0x1e8u)) = m->edx;	/* 48ca6d: mov dword ptr [edi + 0x1e8], edx */
	m->ecx = (m->ecx & 0xffff0000u) | ((M16((DWORD)(m->ebx + 0x2u))) & 0xffff);	/* 48ca73: mov cx, word ptr [ebx + 2] */
	{ DWORD a_ = m->eax, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48ca77: sub eax, 6 */
	MF((DWORD)(m->edi + 0x124u)) = (float)ST(0); FPOP();	/* 48ca7a: fstp dword ptr [edi + 0x124] */
	M32((DWORD)(m->edi + 0x3f0u)) = m->ecx;	/* 48ca80: mov dword ptr [edi + 0x3f0], ecx */
	if (m->zf) goto L_48cab9;	/* 48ca86: je 0x48cab9 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 48ca88: dec eax */
	if (m->zf) goto L_48caad;	/* 48ca89: je 0x48caad */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 48ca8b: mov edx, dword ptr [esp + 0x14] */
	m->ecx = (DWORD)(m->ebp + 0x1f36c8u);	/* 48ca8f: lea ecx, [ebp + 0x1f36c8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ca95: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48ca96: push esi */
	M32((DWORD)(m->edi + 0x3ecu)) = 0x0u;	/* 48ca97: mov dword ptr [edi + 0x3ec], 0 */
	m->esp -= 4; M32(m->esp) = 0x48caa6u; native_call(m, 0x45e810u);	/* 48caa1: call 0x45e810 */
	m->edx = 0x1u;	/* 48caa6: mov edx, 1 */
	goto L_48cabf;	/* 48caab: jmp 0x48cabf */
L_48caad:
	M32((DWORD)(m->edi + 0x3ecu)) = 0x2u;	/* 48caad: mov dword ptr [edi + 0x3ec], 2 */
	goto L_48cabf;	/* 48cab7: jmp 0x48cabf */
L_48cab9:
	M32((DWORD)(m->edi + 0x3ecu)) = m->edx;	/* 48cab9: mov dword ptr [edi + 0x3ec], edx */
L_48cabf:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 48cabf: mov eax, dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 48cac3: mov ecx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->edi + 0x1acu)) = m->eax;	/* 48cac7: mov dword ptr [edi + 0x1ac], eax */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 48cacd: mov eax, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->edi + 0x1b0u)) = m->ecx;	/* 48cad1: mov dword ptr [edi + 0x1b0], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x58u));	/* 48cad7: mov ecx, dword ptr [esp + 0x58] */
	M32((DWORD)(m->edi + 0x1b4u)) = m->eax;	/* 48cadb: mov dword ptr [edi + 0x1b4], eax */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 48cae1: mov eax, dword ptr [esp + 0x20] */
	M32((DWORD)(m->edi + 0x1b8u)) = m->ecx;	/* 48cae5: mov dword ptr [edi + 0x1b8], ecx */
	M32((DWORD)(m->edi + 0x1bcu)) = m->eax;	/* 48caeb: mov dword ptr [edi + 0x1bc], eax */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(m->ebx + 0xdu)));	/* 48caf1: movsx ecx, byte ptr [ebx + 0xd] */
	M32((DWORD)(m->esp + 0x58u)) = m->ecx;	/* 48caf5: mov dword ptr [esp + 0x58], ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x58u)));	/* 48caf9: fild dword ptr [esp + 0x58] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a955cu));	/* 48cafd: fmul dword ptr [0x4a955c] */
	MF((DWORD)(m->edi + 0x1c0u)) = (float)ST(0); FPOP();	/* 48cb03: fstp dword ptr [edi + 0x1c0] */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(m->ebx + 0xeu)));	/* 48cb09: movsx eax, byte ptr [ebx + 0xe] */
	M32((DWORD)(m->esp + 0x58u)) = m->eax;	/* 48cb0d: mov dword ptr [esp + 0x58], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x58u)));	/* 48cb11: fild dword ptr [esp + 0x58] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a955cu));	/* 48cb15: fmul dword ptr [0x4a955c] */
	MF((DWORD)(m->edi + 0x1c4u)) = (float)ST(0); FPOP();	/* 48cb1b: fstp dword ptr [edi + 0x1c4] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0xfu))) & 0xff) << 0);	/* 48cb21: mov cl, byte ptr [ebx + 0xf] */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 8); m->of = 0; m->ecx = (m->ecx & ~(0xffu << 0)) | (((r_) & 0xff) << 0); } }	/* 48cb24: shr cl, 4 */
	{ DWORD a_ = m->ecx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48cb27: and ecx, 0xff */
	M32((DWORD)(m->esp + 0x58u)) = m->ecx;	/* 48cb2d: mov dword ptr [esp + 0x58], ecx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48cb31: xor ecx, ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x58u)));	/* 48cb33: fild dword ptr [esp + 0x58] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa490u));	/* 48cb37: fmul dword ptr [0x4aa490] */
	MF((DWORD)(m->edi + 0x1c8u)) = (float)ST(0); FPOP();	/* 48cb3d: fstp dword ptr [edi + 0x1c8] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0xfu))) & 0xff) << 0);	/* 48cb43: mov al, byte ptr [ebx + 0xf] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0xfu & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 48cb46: and al, 0xf */
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48cb48: and eax, 0xff */
	M32((DWORD)(m->esp + 0x58u)) = m->eax;	/* 48cb4d: mov dword ptr [esp + 0x58], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x58u)));	/* 48cb51: fild dword ptr [esp + 0x58] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa490u));	/* 48cb55: fmul dword ptr [0x4aa490] */
	MF((DWORD)(m->edi + 0x1d0u)) = (float)ST(0); FPOP();	/* 48cb5b: fstp dword ptr [edi + 0x1d0] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x10u))) & 0xff) << 0);	/* 48cb61: mov cl, byte ptr [ebx + 0x10] */
	M32((DWORD)(m->esp + 0x58u)) = m->ecx;	/* 48cb64: mov dword ptr [esp + 0x58], ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x58u)));	/* 48cb68: fild dword ptr [esp + 0x58] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa48cu));	/* 48cb6c: fmul dword ptr [0x4aa48c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa288u));	/* 48cb72: fcom dword ptr [0x4aa288] */
	MF((DWORD)(m->edi + 0x1ccu)) = (float)ST(0);	/* 48cb78: fst dword ptr [edi + 0x1cc] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48cb7e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48cb80: test ah, 0x41 */
	if (!m->zf) goto L_48cb93;	/* 48cb83: jne 0x48cb93 */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a94c8u));	/* 48cb85: fsub dword ptr [0x4a94c8] */
	MF((DWORD)(m->edi + 0x1ccu)) = (float)ST(0); FPOP();	/* 48cb8b: fstp dword ptr [edi + 0x1cc] */
	goto L_48cb95;	/* 48cb91: jmp 0x48cb95 */
L_48cb93:
	ST(0) = ST(0); FPOP();	/* 48cb93: fstp st(0) */
L_48cb95:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x11u))) & 0xff) << 0);	/* 48cb95: mov al, byte ptr [ebx + 0x11] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x80u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48cb98: test al, 0x80 */
	if (m->zf) goto L_48cbc3;	/* 48cb9a: je 0x48cbc3 */
	{ DWORD a_ = m->eax, b_ = 0xfu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48cb9c: and eax, 0xf */
	M32((DWORD)(m->edi + 0x4c0u)) = m->eax;	/* 48cb9f: mov dword ptr [edi + 0x4c0], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48cba5: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x12u))) & 0xff) << 0);	/* 48cba7: mov al, byte ptr [ebx + 0x12] */
	M32((DWORD)(m->edi + 0x4c4u)) = m->eax;	/* 48cbaa: mov dword ptr [edi + 0x4c4], eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x11u))) & 0xff) << 0);	/* 48cbb0: mov al, byte ptr [ebx + 0x11] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48cbb3: test al, 0x40 */
	if (m->zf) goto L_48cbdd;	/* 48cbb5: je 0x48cbdd */
	m->eax = M32((DWORD)(m->edi + 0x128u));	/* 48cbb7: mov eax, dword ptr [edi + 0x128] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48cbbd: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_48cbdd;	/* 48cbbf: jle 0x48cbdd */
	goto L_48cbd3;	/* 48cbc1: jmp 0x48cbd3 */
L_48cbc3:
	{ DWORD a_ = M8((DWORD)(m->ebx + 0x4u)), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48cbc3: test byte ptr [ebx + 4], 1 */
	if (!m->zf) goto L_48cbe7;	/* 48cbc7: jne 0x48cbe7 */
	m->eax = M32((DWORD)(m->edi + 0x128u));	/* 48cbc9: mov eax, dword ptr [edi + 0x128] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48cbcf: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_48cbe7;	/* 48cbd1: jle 0x48cbe7 */
L_48cbd3:
	M32((DWORD)(m->edi + 0x128u)) = 0x0u;	/* 48cbd3: mov dword ptr [edi + 0x128], 0 */
L_48cbdd:
	M32((DWORD)(m->edi + 0x8854u)) = 0x3f000000u;	/* 48cbdd: mov dword ptr [edi + 0x8854], 0x3f000000 */
L_48cbe7:
	m->eax = (DWORD)(m->edi + 0x1fcu);	/* 48cbe7: lea eax, [edi + 0x1fc] */
	{ DWORD a_ = m->ebx, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 48cbed: add ebx, 0x14 */
	m->esi = 0x5u;	/* 48cbf0: mov esi, 5 */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((0x8u) & 0xff) << 0);	/* 48cbf5: mov cl, 8 */
L_48cbf7:
	{ DWORD a_ = M8((DWORD)(m->ebx + 0xffffffffu)), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48cbf7: test byte ptr [ebx - 1], 1 */
	if (m->zf) goto L_48cc9d;	/* 48cbfb: je 0x48cc9d */
	m->ebp = M32((DWORD)(m->edi + 0x118u));	/* 48cc01: mov ebp, dword ptr [edi + 0x118] */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48cc07: test ebp, ebp */
	if (m->sf != m->of) goto L_48cc9d;	/* 48cc09: jl 0x48cc9d */
	M32((DWORD)(m->eax + 0xfffffffcu)) = m->edx;	/* 48cc0f: mov dword ptr [eax - 4], edx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48cc12: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0xffffffffu))) & 0xff) << 0);	/* 48cc14: mov dl, byte ptr [ebx - 1] */
	m->ebp = m->edx;	/* 48cc17: mov ebp, edx */
	m->edx = 0x1u;	/* 48cc19: mov edx, 1 */
	{ DWORD a_ = m->ebp, c_ = (0x1u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ebp = r_; } }	/* 48cc1e: shr ebp, 1 */
	{ DWORD a_ = m->ebp, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 48cc20: and ebp, edx */
	M32((DWORD)(m->eax + 0x0u)) = m->ebp;	/* 48cc22: mov dword ptr [eax], ebp */
	{ DWORD a_ = M8((DWORD)(m->ebx + 0xffffffffu)), b_ = 0x4u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48cc24: test byte ptr [ebx - 1], 4 */
	if (m->zf) goto L_48cc3b;	/* 48cc28: je 0x48cc3b */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 48cc2a: xor ebp, ebp */
	m->ebp = (m->ebp & 0xffff0000u) | ((M16((DWORD)(m->ebx + 0x0u))) & 0xffff);	/* 48cc2c: mov bp, word ptr [ebx] */
	M32((DWORD)(m->eax + 0x4u)) = m->ebp;	/* 48cc2f: mov dword ptr [eax + 4], ebp */
	M32((DWORD)(m->eax + 0x8u)) = 0xffffffffu;	/* 48cc32: mov dword ptr [eax + 8], 0xffffffff */
	goto L_48cc4b;	/* 48cc39: jmp 0x48cc4b */
L_48cc3b:
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 48cc3b: xor ebp, ebp */
	M32((DWORD)(m->eax + 0x4u)) = 0xffffffffu;	/* 48cc3d: mov dword ptr [eax + 4], 0xffffffff */
	m->ebp = (m->ebp & 0xffff0000u) | ((M16((DWORD)(m->ebx + 0x0u))) & 0xffff);	/* 48cc44: mov bp, word ptr [ebx] */
	{ DWORD a_ = m->ebp, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebp = r_; }	/* 48cc47: dec ebp */
	M32((DWORD)(m->eax + 0x8u)) = m->ebp;	/* 48cc48: mov dword ptr [eax + 8], ebp */
L_48cc4b:
	{ DWORD a_ = M8((DWORD)(m->ebx + 0xffffffffu)), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48cc4b: test byte ptr [ebx - 1], cl */
	if (m->zf) goto L_48cc55;	/* 48cc4e: je 0x48cc55 */
	M32((DWORD)(m->eax + 0xcu)) = m->edx;	/* 48cc50: mov dword ptr [eax + 0xc], edx */
	goto L_48cc5c;	/* 48cc53: jmp 0x48cc5c */
L_48cc55:
	M32((DWORD)(m->eax + 0xcu)) = 0x0u;	/* 48cc55: mov dword ptr [eax + 0xc], 0 */
L_48cc5c:
	m->ebp = (DWORD)(int)(short)(M16((DWORD)(m->ebx + 0x6u)));	/* 48cc5c: movsx ebp, word ptr [ebx + 6] */
	M32((DWORD)(m->esp + 0x58u)) = m->ebp;	/* 48cc60: mov dword ptr [esp + 0x58], ebp */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x58u)));	/* 48cc64: fild dword ptr [esp + 0x58] */
	m->ebp = (DWORD)(int)(short)(M16((DWORD)(m->ebx + 0x4u)));	/* 48cc68: movsx ebp, word ptr [ebx + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 48cc6c: fmul dword ptr [0x4a9418] */
	M32((DWORD)(m->esp + 0x58u)) = m->ebp;	/* 48cc72: mov dword ptr [esp + 0x58], ebp */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x58u)));	/* 48cc76: fild dword ptr [esp + 0x58] */
	m->ebp = (DWORD)(int)(short)(M16((DWORD)(m->ebx + 0x2u)));	/* 48cc7a: movsx ebp, word ptr [ebx + 2] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 48cc7e: fmul dword ptr [0x4a9418] */
	M32((DWORD)(m->esp + 0x58u)) = m->ebp;	/* 48cc84: mov dword ptr [esp + 0x58], ebp */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x58u)));	/* 48cc88: fild dword ptr [esp + 0x58] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 48cc8c: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->eax + 0x10u)) = (float)ST(0); FPOP();	/* 48cc92: fstp dword ptr [eax + 0x10] */
	MF((DWORD)(m->eax + 0x14u)) = (float)ST(0); FPOP();	/* 48cc95: fstp dword ptr [eax + 0x14] */
	MF((DWORD)(m->eax + 0x18u)) = (float)ST(0); FPOP();	/* 48cc98: fstp dword ptr [eax + 0x18] */
	goto L_48cca4;	/* 48cc9b: jmp 0x48cca4 */
L_48cc9d:
	M32((DWORD)(m->eax + 0xfffffffcu)) = 0x0u;	/* 48cc9d: mov dword ptr [eax - 4], 0 */
L_48cca4:
	{ DWORD a_ = m->ebx, b_ = 0x9u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 48cca4: add ebx, 9 */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48cca7: add eax, 0x20 */
	{ DWORD a_ = m->esi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->esi = r_; }	/* 48ccaa: dec esi */
	if (!m->zf) goto L_48cbf7;	/* 48ccab: jne 0x48cbf7 */
	m->edi = M32(m->esp); m->esp += 4;	/* 48ccb1: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48ccb2: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 48ccb3: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48ccb4: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48ccb5: add esp, 0x3c */
	m->esp += 4 + 12; return;	/* 48ccb8: ret 0xc */
L_48ccbb:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 48ccbb: mov al, byte ptr [ebx + 2] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x10u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48ccbe: cmp al, 0x10 */
	if (!m->cf && !m->zf) goto L_48db8d;	/* 48ccc0: ja 0x48db8d */
	{ DWORD a_ = M8((DWORD)(m->ebx + 0x3u)), b_ = 0xffu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48ccc6: cmp byte ptr [ebx + 3], 0xff */
	if (m->sf != m->of) goto L_48db8d;	/* 48ccca: jl 0x48db8d */
	{ DWORD a_ = M8((DWORD)(m->ebx + 0x4u)), b_ = 0xffu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48ccd0: cmp byte ptr [ebx + 4], 0xff */
	if (m->sf != m->of) goto L_48db8d;	/* 48ccd4: jl 0x48db8d */
	{ DWORD a_ = M8((DWORD)(m->ebx + 0x5u)), b_ = 0xffu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48ccda: cmp byte ptr [ebx + 5], 0xff */
	if (m->sf != m->of) goto L_48db8d;	/* 48ccde: jl 0x48db8d */
	{ DWORD a_ = M8((DWORD)(m->ebx + 0x6u)), b_ = 0xffu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48cce4: cmp byte ptr [ebx + 6], 0xff */
	if (m->sf != m->of) goto L_48db8d;	/* 48cce8: jl 0x48db8d */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48ccee: test al, al */
	if (!m->zf) goto L_48cf87;	/* 48ccf0: jne 0x48cf87 */
	m->eax = M32((DWORD)(m->ebx + 0x9u));	/* 48ccf6: mov eax, dword ptr [ebx + 9] */
	M32((DWORD)(m->ebp + 0x22f0408u)) = m->eax;	/* 48ccf9: mov dword ptr [ebp + 0x22f0408], eax */
	m->ecx = M32((DWORD)(m->ebx + 0xdu));	/* 48ccff: mov ecx, dword ptr [ebx + 0xd] */
	M32((DWORD)(m->ebp + 0x22f040cu)) = m->ecx;	/* 48cd02: mov dword ptr [ebp + 0x22f040c], ecx */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x3u))) & 0xff) << 0);	/* 48cd08: mov al, byte ptr [ebx + 3] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48cd0b: test al, al */
	if (m->sf != m->of) goto L_48cdcc;	/* 48cd0d: jl 0x48cdcc */
	m->ecx = M32((DWORD)(0x9dad94u));	/* 48cd13: mov ecx, dword ptr [0x9dad94] */
	m->eax = (DWORD)(int)(signed char)(((m->eax >> 0) & 0xff));	/* 48cd19: movsx eax, al */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48cd1c: cmp ecx, eax */
	if (m->zf) goto L_48cd93;	/* 48cd1e: je 0x48cd93 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 48cd20: xor esi, esi */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48cd22: cmp ecx, esi */
	if (m->sf != m->of) goto L_48cd37;	/* 48cd24: jl 0x48cd37 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x1f1cb0u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48cd26: cmp dword ptr [ebp + 0x1f1cb0], edi */
	if (m->zf) goto L_48cd37;	/* 48cd2c: je 0x48cd37 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x22f0408u)), b_ = 0x1eu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48cd2e: cmp dword ptr [ebp + 0x22f0408], 0x1e */
	if (m->zf || m->sf != m->of) goto L_48cd93;	/* 48cd35: jle 0x48cd93 */
L_48cd37:
	M32((DWORD)(0x9dad94u)) = m->eax;	/* 48cd37: mov dword ptr [0x9dad94], eax */
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(m->ebx + 0x4u)));	/* 48cd3c: movsx edx, byte ptr [ebx + 4] */
	M32((DWORD)(m->ebp + 0x1f1cb4u)) = m->edx;	/* 48cd40: mov dword ptr [ebp + 0x1f1cb4], edx */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(m->ebx + 0x6u)));	/* 48cd46: movsx eax, byte ptr [ebx + 6] */
	M32((DWORD)(m->ebp + 0x1f1cb8u)) = m->eax;	/* 48cd4a: mov dword ptr [ebp + 0x1f1cb8], eax */
	m->ecx = M32((DWORD)(0x9dad94u));	/* 48cd50: mov ecx, dword ptr [0x9dad94] */
	{ DWORD a_ = m->ecx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48cd56: shl ecx, 5 */
	{ DWORD a_ = m->ecx, b_ = 0x907b30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48cd59: add ecx, 0x907b30 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48cd5f: push ecx */
	m->ecx = m->ebp;	/* 48cd60: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x48cd67u; native_call(m, 0x461ec0u);	/* 48cd62: call 0x461ec0 */
	M32((DWORD)(m->ebp + 0x233cc20u)) = m->edi;	/* 48cd67: mov dword ptr [ebp + 0x233cc20], edi */
	M32((DWORD)(m->ebp + 0x233cc28u)) = m->esi;	/* 48cd6d: mov dword ptr [ebp + 0x233cc28], esi */
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(m->ebx + 0x5u)));	/* 48cd73: movsx edx, byte ptr [ebx + 5] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48cd77: push edx */
	m->ecx = (DWORD)(m->ebp + 0x1f36c8u);	/* 48cd78: lea ecx, [ebp + 0x1f36c8] */
	m->esp -= 4; M32(m->esp) = 0x48cd83u; native_call(m, 0x4732f0u);	/* 48cd7e: call 0x4732f0 */
	M32((DWORD)(m->ebp + 0x1f1cb0u)) = m->esi;	/* 48cd83: mov dword ptr [ebp + 0x1f1cb0], esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 48cd89: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48cd8a: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 48cd8b: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48cd8c: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48cd8d: add esp, 0x3c */
	m->esp += 4 + 12; return;	/* 48cd90: ret 0xc */
L_48cd93:
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(m->ebx + 0x4u)));	/* 48cd93: movsx eax, byte ptr [ebx + 4] */
	M32((DWORD)(m->ebp + 0x1f1cb4u)) = m->eax;	/* 48cd97: mov dword ptr [ebp + 0x1f1cb4], eax */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(m->ebx + 0x6u)));	/* 48cd9d: movsx ecx, byte ptr [ebx + 6] */
	M32((DWORD)(m->ebp + 0x1f1cb8u)) = m->ecx;	/* 48cda1: mov dword ptr [ebp + 0x1f1cb8], ecx */
	m->eax = M32((DWORD)(0x9dad94u));	/* 48cda7: mov eax, dword ptr [0x9dad94] */
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(m->ebx + 0x3u)));	/* 48cdac: movsx edx, byte ptr [ebx + 3] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48cdb0: cmp eax, edx */
	if (!m->zf) goto L_48cdcc;	/* 48cdb2: jne 0x48cdcc */
	m->eax = (DWORD)(int)(short)(M16((DWORD)(m->ebx + 0x7u)));	/* 48cdb4: movsx eax, word ptr [ebx + 7] */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0xbe3000u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48cdb8: cmp dword ptr [ebp + 0xbe3000], eax */
	if (m->zf) goto L_48cdcc;	/* 48cdbe: je 0x48cdcc */
	M32((DWORD)(m->ebp + 0x23423fdu)) = m->edi;	/* 48cdc0: mov dword ptr [ebp + 0x23423fd], edi */
	M32((DWORD)(m->ebp + 0x2342401u)) = m->edi;	/* 48cdc6: mov dword ptr [ebp + 0x2342401], edi */
L_48cdcc:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48cdcc: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2bu))) & 0xff) << 0);	/* 48cdce: mov al, byte ptr [ebx + 0x2b] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48cdd1: cmp eax, 4 */
	if (!m->cf && !m->zf) goto L_48cf39;	/* 48cdd4: ja 0x48cf39 */
	switch (m->eax) { case 0: goto L_48cde1; case 1: goto L_48ce27; case 2: goto L_48ce71; case 3: goto L_48ceaf; case 4: goto L_48ceeb; default: abort(); }	/* 48cdda: jmp dword ptr [eax*4 + 0x48dbdc] */
L_48cde1:
	m->esi = M32((DWORD)(m->ebp + 0x23423e5u));	/* 48cde1: mov esi, dword ptr [ebp + 0x23423e5] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48cde7: xor ecx, ecx */
	m->ecx = (m->ecx & 0xffff0000u) | ((M16((DWORD)(m->ebx + 0x2cu))) & 0xffff);	/* 48cde9: mov cx, word ptr [ebx + 0x2c] */
	m->eax = m->ecx;	/* 48cded: mov eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48cdef: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->esi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48cdf0: idiv esi */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48cdf2: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)M32((DWORD)(m->ebp + 0x15de6c8u)); m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48cdf3: idiv dword ptr [ebp + 0x15de6c8] */
	m->eax = m->edx;	/* 48cdf9: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48cdfb: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48cdfe: add eax, edx */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 48ce00: lea eax, [eax + eax*4] */
	m->edx = (DWORD)(m->edx + m->eax*4 + 0x0u);	/* 48ce03: lea edx, [edx + eax*4] */
	m->eax = m->ecx;	/* 48ce06: mov eax, ecx */
	m->ecx = m->edx;	/* 48ce08: mov ecx, edx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48ce0a: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->esi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48ce0b: idiv esi */
	m->edx = (DWORD)(m->edx + m->ecx*2 + 0x0u);	/* 48ce0d: lea edx, [edx + ecx*2] */
	m->ecx = M32((DWORD)(m->ebx + 0x2eu));	/* 48ce10: mov ecx, dword ptr [ebx + 0x2e] */
	m->eax = M32((DWORD)(m->ebp + m->edx*4 + 0x15bd1f8u));	/* 48ce13: mov eax, dword ptr [ebp + edx*4 + 0x15bd1f8] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ce1a: cmp eax, ecx */
	if (m->zf) goto L_48cf39;	/* 48ce1c: je 0x48cf39 */
	goto L_48cf29;	/* 48ce22: jmp 0x48cf29 */
L_48ce27:
	m->esi = M32((DWORD)(m->ebp + 0x23423e9u));	/* 48ce27: mov esi, dword ptr [ebp + 0x23423e9] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48ce2d: xor ecx, ecx */
	m->ecx = (m->ecx & 0xffff0000u) | ((M16((DWORD)(m->ebx + 0x2cu))) & 0xffff);	/* 48ce2f: mov cx, word ptr [ebx + 0x2c] */
	m->eax = m->ecx;	/* 48ce33: mov eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48ce35: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->esi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48ce36: idiv esi */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48ce38: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)M32((DWORD)(m->ebp + 0x15fff84u)); m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48ce39: idiv dword ptr [ebp + 0x15fff84] */
	m->eax = (DWORD)(m->edx + m->edx*2 + 0x0u);	/* 48ce3f: lea eax, [edx + edx*2] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48ce42: shl eax, 3 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48ce45: sub eax, edx */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 48ce47: lea eax, [eax + eax*4] */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48ce4a: shl eax, 1 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48ce4c: sub eax, edx */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 48ce4e: lea edx, [eax + eax*2] */
	m->eax = m->ecx;	/* 48ce51: mov eax, ecx */
	m->ecx = m->edx;	/* 48ce53: mov ecx, edx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48ce55: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->esi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48ce56: idiv esi */
	m->eax = M32((DWORD)(m->ebx + 0x2eu));	/* 48ce58: mov eax, dword ptr [ebx + 0x2e] */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48ce5b: add ecx, edx */
	m->edx = M32((DWORD)(m->ebp + m->ecx*4 + 0x15de6ccu));	/* 48ce5d: mov edx, dword ptr [ebp + ecx*4 + 0x15de6cc] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ce64: cmp edx, eax */
	if (m->zf) goto L_48cf39;	/* 48ce66: je 0x48cf39 */
	goto L_48cf29;	/* 48ce6c: jmp 0x48cf29 */
L_48ce71:
	m->esi = M32((DWORD)(m->ebp + 0x23423edu));	/* 48ce71: mov esi, dword ptr [ebp + 0x23423ed] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48ce77: xor ecx, ecx */
	m->ecx = (m->ecx & 0xffff0000u) | ((M16((DWORD)(m->ebx + 0x2cu))) & 0xffff);	/* 48ce79: mov cx, word ptr [ebx + 0x2c] */
	m->eax = m->ecx;	/* 48ce7d: mov eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48ce7f: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->esi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48ce80: idiv esi */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48ce82: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)M32((DWORD)(m->ebp + 0x163b588u)); m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48ce83: idiv dword ptr [ebp + 0x163b588] */
	m->eax = (DWORD)(m->edx + m->edx*8 + 0x0u);	/* 48ce89: lea eax, [edx + edx*8] */
	m->edx = (DWORD)(m->edx + m->eax*2 + 0x0u);	/* 48ce8c: lea edx, [edx + eax*2] */
	m->eax = m->ecx;	/* 48ce8f: mov eax, ecx */
	{ DWORD a_ = m->edx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 48ce91: shl edx, 6 */
	m->ecx = m->edx;	/* 48ce94: mov ecx, edx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48ce96: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->esi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48ce97: idiv esi */
	m->eax = M32((DWORD)(m->ebx + 0x2eu));	/* 48ce99: mov eax, dword ptr [ebx + 0x2e] */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48ce9c: add ecx, edx */
	m->edx = M32((DWORD)(m->ebp + m->ecx*4 + 0x15fff88u));	/* 48ce9e: mov edx, dword ptr [ebp + ecx*4 + 0x15fff88] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48cea5: cmp edx, eax */
	if (m->zf) goto L_48cf39;	/* 48cea7: je 0x48cf39 */
	goto L_48cf29;	/* 48cead: jmp 0x48cf29 */
L_48ceaf:
	m->esi = M32((DWORD)(m->ebp + 0x23423f1u));	/* 48ceaf: mov esi, dword ptr [ebp + 0x23423f1] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48ceb5: xor ecx, ecx */
	m->ecx = (m->ecx & 0xffff0000u) | ((M16((DWORD)(m->ebx + 0x2cu))) & 0xffff);	/* 48ceb7: mov cx, word ptr [ebx + 0x2c] */
	m->eax = m->ecx;	/* 48cebb: mov eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48cebd: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->esi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48cebe: idiv esi */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48cec0: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)M32((DWORD)(m->ebp + 0x1679b34u)); m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48cec1: idiv dword ptr [ebp + 0x1679b34] */
	m->eax = (DWORD)(m->edx + m->edx*4 + 0x0u);	/* 48cec7: lea eax, [edx + edx*4] */
	{ DWORD a_ = m->eax, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48ceca: shl eax, 6 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48cecd: sub eax, edx */
	m->edx = (DWORD)(m->edx + m->eax*4 + 0x0u);	/* 48cecf: lea edx, [edx + eax*4] */
	m->eax = m->ecx;	/* 48ced2: mov eax, ecx */
	m->ecx = m->edx;	/* 48ced4: mov ecx, edx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48ced6: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->esi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48ced7: idiv esi */
	m->eax = M32((DWORD)(m->ebx + 0x2eu));	/* 48ced9: mov eax, dword ptr [ebx + 0x2e] */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48cedc: add ecx, edx */
	m->edx = M32((DWORD)(m->ebp + m->ecx*4 + 0x163b58cu));	/* 48cede: mov edx, dword ptr [ebp + ecx*4 + 0x163b58c] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48cee5: cmp edx, eax */
	if (m->zf) goto L_48cf39;	/* 48cee7: je 0x48cf39 */
	goto L_48cf29;	/* 48cee9: jmp 0x48cf29 */
L_48ceeb:
	m->esi = M32((DWORD)(m->ebp + 0x23423f5u));	/* 48ceeb: mov esi, dword ptr [ebp + 0x23423f5] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48cef1: xor ecx, ecx */
	m->ecx = (m->ecx & 0xffff0000u) | ((M16((DWORD)(m->ebx + 0x2cu))) & 0xffff);	/* 48cef3: mov cx, word ptr [ebx + 0x2c] */
	m->eax = m->ecx;	/* 48cef7: mov eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48cef9: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->esi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48cefa: idiv esi */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48cefc: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)M32((DWORD)(m->ebp + 0x16c5178u)); m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48cefd: idiv dword ptr [ebp + 0x16c5178] */
	m->eax = (DWORD)(m->edx + m->edx*2 + 0x0u);	/* 48cf03: lea eax, [edx + edx*2] */
	{ DWORD a_ = m->eax, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48cf06: shl eax, 6 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48cf09: add eax, edx */
	M32((DWORD)(m->esp + 0x58u)) = m->eax;	/* 48cf0b: mov dword ptr [esp + 0x58], eax */
	m->eax = m->ecx;	/* 48cf0f: mov eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48cf11: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->esi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48cf12: idiv esi */
	m->eax = M32((DWORD)(m->esp + 0x58u));	/* 48cf14: mov eax, dword ptr [esp + 0x58] */
	m->ecx = (DWORD)(m->edx + m->eax*8 + 0x0u);	/* 48cf18: lea ecx, [edx + eax*8] */
	m->eax = M32((DWORD)(m->ebx + 0x2eu));	/* 48cf1b: mov eax, dword ptr [ebx + 0x2e] */
	m->edx = M32((DWORD)(m->ebp + m->ecx*4 + 0x1679b38u));	/* 48cf1e: mov edx, dword ptr [ebp + ecx*4 + 0x1679b38] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48cf25: cmp edx, eax */
	if (m->zf) goto L_48cf39;	/* 48cf27: je 0x48cf39 */
L_48cf29:
	M32((DWORD)(m->ebp + 0x23423fdu)) = m->edi;	/* 48cf29: mov dword ptr [ebp + 0x23423fd], edi */
	M32((DWORD)(m->ebp + 0x2342401u)) = 0x2u;	/* 48cf2f: mov dword ptr [ebp + 0x2342401], 2 */
L_48cf39:
	m->esi = M32((DWORD)(m->ebp + 0x23423f9u));	/* 48cf39: mov esi, dword ptr [ebp + 0x23423f9] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48cf3f: xor ecx, ecx */
	m->ecx = (m->ecx & 0xffff0000u) | ((M16((DWORD)(m->ebx + 0x32u))) & 0xffff);	/* 48cf41: mov cx, word ptr [ebx + 0x32] */
	m->eax = m->ecx;	/* 48cf45: mov eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48cf47: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->esi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48cf48: idiv esi */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48cf4a: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)M32((DWORD)(m->ebp + 0x175522cu)); m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48cf4b: idiv dword ptr [ebp + 0x175522c] */
	m->eax = (DWORD)(m->edx + m->edx*8 + 0x0u);	/* 48cf51: lea eax, [edx + edx*8] */
	m->eax = (DWORD)(m->edx + m->eax*4 + 0x0u);	/* 48cf54: lea eax, [edx + eax*4] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48cf57: shl eax, 3 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48cf5a: sub eax, edx */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 48cf5c: lea edx, [eax + eax*4] */
	m->eax = m->ecx;	/* 48cf5f: mov eax, ecx */
	m->ecx = m->edx;	/* 48cf61: mov ecx, edx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48cf63: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->esi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48cf64: idiv esi */
	m->edx = (DWORD)(m->edx + m->ecx*2 + 0x0u);	/* 48cf66: lea edx, [edx + ecx*2] */
	m->ecx = M32((DWORD)(m->ebx + 0x34u));	/* 48cf69: mov ecx, dword ptr [ebx + 0x34] */
	m->eax = M32((DWORD)(m->ebp + m->edx*4 + 0x16c517cu));	/* 48cf6c: mov eax, dword ptr [ebp + edx*4 + 0x16c517c] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48cf73: cmp eax, ecx */
	if (m->zf) goto L_48cf87;	/* 48cf75: je 0x48cf87 */
	M32((DWORD)(m->ebp + 0x23423fdu)) = m->edi;	/* 48cf77: mov dword ptr [ebp + 0x23423fd], edi */
	M32((DWORD)(m->ebp + 0x2342401u)) = 0x3u;	/* 48cf7d: mov dword ptr [ebp + 0x2342401], 3 */
L_48cf87:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48cf87: xor eax, eax */
	m->edx = M32((DWORD)(m->ebx + 0x11u));	/* 48cf89: mov edx, dword ptr [ebx + 0x11] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 48cf8c: mov al, byte ptr [ebx + 2] */
	m->ecx = m->eax;	/* 48cf8f: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48cf91: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48cf94: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48cf96: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48cf99: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48cf9b: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48cf9e: add ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48cfa0: xor eax, eax */
	M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccb6cu)) = m->edx;	/* 48cfa2: mov dword ptr [ebp + ecx*8 + 0x1eccb6c], edx */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 48cfa9: mov al, byte ptr [ebx + 2] */
	m->ecx = m->eax;	/* 48cfac: mov ecx, eax */
	m->edx = M32((DWORD)(m->ebx + 0x15u));	/* 48cfae: mov edx, dword ptr [ebx + 0x15] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48cfb1: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48cfb4: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48cfb6: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48cfb9: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48cfbb: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48cfbe: add ecx, eax */
	m->eax = m->edi;	/* 48cfc0: mov eax, edi */
	M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccb70u)) = m->edx;	/* 48cfc2: mov dword ptr [ebp + ecx*8 + 0x1eccb70], edx */
	m->ecx = M32((DWORD)(m->ebp + 0x234240du));	/* 48cfc9: mov ecx, dword ptr [ebp + 0x234240d] */
	m->edx = M32((DWORD)(m->ebx + 0x19u));	/* 48cfcf: mov edx, dword ptr [ebx + 0x19] */
	{ DWORD a_ = m->eax, c_ = (((m->ecx >> 0) & 0xff)) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48cfd2: shl eax, cl */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48cfd4: test edx, eax */
	if (m->zf) goto L_48cfe2;	/* 48cfd6: je 0x48cfe2 */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48cfd8: shl ecx, 4 */
	M32((DWORD)(m->ecx + m->ebp*1 + 0x234300au)) = m->edi;	/* 48cfdb: mov dword ptr [ecx + ebp + 0x234300a], edi */
L_48cfe2:
	m->ecx = M32((DWORD)(m->ebp + 0x234240du));	/* 48cfe2: mov ecx, dword ptr [ebp + 0x234240d] */
	m->eax = M32((DWORD)(m->ebx + 0x1du));	/* 48cfe8: mov eax, dword ptr [ebx + 0x1d] */
	m->edx = m->edi;	/* 48cfeb: mov edx, edi */
	{ DWORD a_ = m->edx, c_ = (((m->ecx >> 0) & 0xff)) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 48cfed: shl edx, cl */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48cfef: test eax, edx */
	if (m->zf) goto L_48d00c;	/* 48cff1: je 0x48d00c */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 48cff3: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48cff6: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48cff9: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 48cffb: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 48cffe: lea ecx, [ecx + eax*8] */
	M32((DWORD)(m->ebp + m->ecx*2 + 0x179d1feu)) = 0x0u;	/* 48d001: mov dword ptr [ebp + ecx*2 + 0x179d1fe], 0 */
L_48d00c:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48d00c: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 48d00e: mov al, byte ptr [ebx + 2] */
	m->ecx = m->eax;	/* 48d011: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d013: shl ecx, 4 */
	m->edx = (DWORD)(int)(short)(M16((DWORD)(m->ebx + 0x21u)));	/* 48d016: movsx edx, word ptr [ebx + 0x21] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48d01a: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d01c: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48d01f: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d021: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48d024: add ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48d026: xor eax, eax */
	M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccb54u)) = m->edx;	/* 48d028: mov dword ptr [ebp + ecx*8 + 0x1eccb54], edx */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 48d02f: mov al, byte ptr [ebx + 2] */
	m->ecx = m->eax;	/* 48d032: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d034: shl ecx, 4 */
	m->edx = (DWORD)(int)(short)(M16((DWORD)(m->ebx + 0x23u)));	/* 48d037: movsx edx, word ptr [ebx + 0x23] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48d03b: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d03d: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48d040: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d042: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48d045: add ecx, eax */
	M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccb58u)) = m->edx;	/* 48d047: mov dword ptr [ebp + ecx*8 + 0x1eccb58], edx */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 48d04e: mov al, byte ptr [ebx + 2] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48d051: test al, al */
	if (!m->zf) goto L_48d069;	/* 48d053: jne 0x48d069 */
	m->edx = (DWORD)(int)(short)(M16((DWORD)(m->ebx + 0x25u)));	/* 48d055: movsx edx, word ptr [ebx + 0x25] */
	M32((DWORD)(m->ebp + 0x2221fb8u)) = m->edx;	/* 48d059: mov dword ptr [ebp + 0x2221fb8], edx */
	m->eax = (DWORD)(int)(short)(M16((DWORD)(m->ebx + 0x27u)));	/* 48d05f: movsx eax, word ptr [ebx + 0x27] */
	M32((DWORD)(m->ebp + 0x2221fbcu)) = m->eax;	/* 48d063: mov dword ptr [ebp + 0x2221fbc], eax */
L_48d069:
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 48d069: mov eax, dword ptr [ebp + 8] */
	m->ecx = 0x1201u;	/* 48d06c: mov ecx, 0x1201 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d071: cmp eax, 3 */
	if (!m->zf) goto L_48d07e;	/* 48d074: jne 0x48d07e */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x1f35c4u)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d076: cmp dword ptr [ebp + 0x1f35c4], ecx */
	if (m->zf || m->sf != m->of) goto L_48d0b2;	/* 48d07c: jle 0x48d0b2 */
L_48d07e:
	m->eax = (m->eax & 0xffff0000u) | ((M16((DWORD)(m->ebx + 0x29u))) & 0xffff);	/* 48d07e: mov ax, word ptr [ebx + 0x29] */
	{ DWORD a_ = (m->eax & 0xffff), b_ = (m->eax & 0xffff) & 0xffffu, r_ = a_ & b_; FLAGS(r_, 16); m->cf = 0; m->of = 0; }	/* 48d082: test ax, ax */
	if (m->sf != m->of) goto L_48d0b2;	/* 48d085: jl 0x48d0b2 */
	m->eax = (DWORD)(int)(short)((m->eax & 0xffff));	/* 48d087: movsx eax, ax */
	{ DWORD a_ = m->eax, b_ = 0xdf8ecu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48d08a: add eax, 0xdf8ec */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 48d08f: lea edx, [eax + eax*4] */
	m->eax = (DWORD)(m->ebp + m->edx*8 + 0x0u);	/* 48d092: lea eax, [ebp + edx*8] */
	m->edx = M32((DWORD)(m->ebp + m->edx*8 + 0x0u));	/* 48d096: mov edx, dword ptr [ebp + edx*8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48d09a: test edx, edx */
	if (!m->zf) goto L_48d0b2;	/* 48d09c: jne 0x48d0b2 */
	M32((DWORD)(m->eax + 0x0u)) = m->edi;	/* 48d09e: mov dword ptr [eax], edi */
	m->eax = (DWORD)(int)(short)(M16((DWORD)(m->ebx + 0x29u)));	/* 48d0a0: movsx eax, word ptr [ebx + 0x29] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 48d0a4: lea eax, [eax + eax*4] */
	M32((DWORD)(m->ebp + m->eax*8 + 0x22ee4e4u)) = 0x0u;	/* 48d0a7: mov dword ptr [ebp + eax*8 + 0x22ee4e4], 0 */
L_48d0b2:
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 48d0b2: mov eax, dword ptr [ebp + 8] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d0b5: cmp eax, 3 */
	if (!m->zf) goto L_48db96;	/* 48d0b8: jne 0x48db96 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x1f35c4u)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d0be: cmp dword ptr [ebp + 0x1f35c4], ecx */
	if (m->zf || m->sf != m->of) goto L_48db96;	/* 48d0c4: jle 0x48db96 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d0ca: cmp eax, eax */
	if (!m->zf) goto L_48db96;	/* 48d0cc: jne 0x48db96 */
	m->ecx = m->ebp;	/* 48d0d2: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x48d0d9u; native_call(m, 0x462150u);	/* 48d0d4: call 0x462150 */
	m->edi = M32(m->esp); m->esp += 4;	/* 48d0d9: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48d0da: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 48d0db: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48d0dc: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48d0dd: add esp, 0x3c */
	m->esp += 4 + 12; return;	/* 48d0e0: ret 0xc */
L_48d0e3:
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 48d0e3: mov cl, byte ptr [ebx + 2] */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = 0x10u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48d0e6: cmp cl, 0x10 */
	if (!m->zf && m->sf == m->of) goto L_48db8d;	/* 48d0e9: jg 0x48db8d */
	m->eax = (m->eax & 0xffff0000u) | ((M16((DWORD)(m->ebx + 0x3u))) & 0xffff);	/* 48d0ef: mov ax, word ptr [ebx + 3] */
	{ DWORD a_ = (m->eax & 0xffff), b_ = 0x170u & 0xffffu, r_ = (a_ - b_) & 0xffffu; FLAGS(r_, 16); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 15) & 1; }	/* 48d0f3: cmp ax, 0x170 */
	if (!m->zf && m->sf == m->of) goto L_48db8d;	/* 48d0f7: jg 0x48db8d */
	{ DWORD a_ = (m->eax & 0xffff), b_ = (m->eax & 0xffff) & 0xffffu, r_ = a_ & b_; FLAGS(r_, 16); m->cf = 0; m->of = 0; }	/* 48d0fd: test ax, ax */
	if (m->sf != m->of) goto L_48d161;	/* 48d100: jl 0x48d161 */
	m->ecx = (DWORD)(int)(signed char)(((m->ecx >> 0) & 0xff));	/* 48d102: movsx ecx, cl */
	m->edx = (DWORD)(int)(short)((m->eax & 0xffff));	/* 48d105: movsx edx, ax */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 48d108: lea eax, [ecx + ecx*2] */
	m->edi = 0x10u;	/* 48d10b: mov edi, 0x10 */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48d110: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48d113: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 48d115: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 48d118: lea ecx, [ecx + eax*8] */
	m->eax = (DWORD)(m->ebp + m->ecx*2 + 0x0u);	/* 48d11b: lea eax, [ebp + ecx*2] */
	m->eax = (DWORD)(m->eax + m->edx*4 + 0x179cbf2u);	/* 48d11f: lea eax, [eax + edx*4 + 0x179cbf2] */
	m->esi = (DWORD)(m->eax + 0x3u);	/* 48d126: lea esi, [eax + 3] */
	m->eax = (DWORD)(m->ebx + 0x6u);	/* 48d129: lea eax, [ebx + 6] */
L_48d12c:
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0xffffffffu))) & 0xff) << 0);	/* 48d12c: mov cl, byte ptr [eax - 1] */
	M8((DWORD)(m->esi + 0xfffffffdu)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 48d12f: mov byte ptr [esi - 3], cl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 48d132: mov dl, byte ptr [eax] */
	M8((DWORD)(m->esi + 0xfffffffeu)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 48d134: mov byte ptr [esi - 2], dl */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 48d137: mov cl, byte ptr [eax + 1] */
	M8((DWORD)(m->esi + 0xffffffffu)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 48d13a: mov byte ptr [esi - 1], cl */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0xffffffffu))) & 0xff) << 0);	/* 48d13d: mov cl, byte ptr [eax - 1] */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48d140: test cl, cl */
	if (!m->zf) goto L_48d155;	/* 48d142: jne 0x48d155 */
	{ DWORD a_ = M8((DWORD)(m->eax + 0x0u)), b_ = 0x0u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48d144: cmp byte ptr [eax], 0 */
	if (!m->zf) goto L_48d155;	/* 48d147: jne 0x48d155 */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 48d149: mov cl, byte ptr [eax + 1] */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48d14c: test cl, cl */
	if (!m->zf) goto L_48d155;	/* 48d14e: jne 0x48d155 */
	M8((DWORD)(m->esi + 0x0u)) = (BYTE)(0x0u);	/* 48d150: mov byte ptr [esi], 0 */
	goto L_48d158;	/* 48d153: jmp 0x48d158 */
L_48d155:
	M8((DWORD)(m->esi + 0x0u)) = (BYTE)(0xffu);	/* 48d155: mov byte ptr [esi], 0xff */
L_48d158:
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48d158: add eax, 3 */
	{ DWORD a_ = m->esi, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 48d15b: add esi, 4 */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 48d15e: dec edi */
	if (!m->zf) goto L_48d12c;	/* 48d15f: jne 0x48d12c */
L_48d161:
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(m->ebx + 0x2u)));	/* 48d161: movsx ecx, byte ptr [ebx + 2] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 48d165: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48d168: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48d16b: sub eax, ecx */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 48d16d: lea edx, [eax + eax*2] */
	m->eax = (DWORD)(m->ecx + m->edx*8 + 0x0u);	/* 48d170: lea eax, [ecx + edx*8] */
	m->ecx = M32((DWORD)(m->ebp + m->eax*2 + 0x179d1fau));	/* 48d173: mov ecx, dword ptr [ebp + eax*2 + 0x179d1fa] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48d17a: test ecx, ecx */
	m->eax = (DWORD)(m->ebp + m->eax*2 + 0x0u);	/* 48d17c: lea eax, [ebp + eax*2] */
	if (!m->zf) goto L_48db96;	/* 48d180: jne 0x48db96 */
	m->ecx = M32((DWORD)(m->eax + 0x179d1f6u));	/* 48d186: mov ecx, dword ptr [eax + 0x179d1f6] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48d18c: test ecx, ecx */
	if (!m->zf) goto L_48d1cc;	/* 48d18e: jne 0x48d1cc */
	m->ecx = M32((DWORD)(m->ebp + 0x234240du));	/* 48d190: mov ecx, dword ptr [ebp + 0x234240d] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 48d196: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48d199: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48d19c: sub eax, ecx */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 48d19e: lea edx, [eax + eax*2] */
	m->eax = (DWORD)(m->ecx + m->edx*8 + 0x0u);	/* 48d1a1: lea eax, [ecx + edx*8] */
	m->ecx = M32((DWORD)(m->ebp + m->eax*2 + 0x179d1f6u));	/* 48d1a4: mov ecx, dword ptr [ebp + eax*2 + 0x179d1f6] */
	m->edx = 0x1u;	/* 48d1ab: mov edx, 1 */
	m->eax = (DWORD)(m->ebp + m->eax*2 + 0x0u);	/* 48d1b0: lea eax, [ebp + eax*2] */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d1b4: cmp ecx, edx */
	if (m->zf) goto L_48d1c0;	/* 48d1b6: je 0x48d1c0 */
	{ DWORD a_ = M32((DWORD)(m->eax + 0x179d1fau)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d1b8: cmp dword ptr [eax + 0x179d1fa], edx */
	if (!m->zf) goto L_48d1d1;	/* 48d1be: jne 0x48d1d1 */
L_48d1c0:
	M32((DWORD)(m->eax + 0x179d1feu)) = 0x0u;	/* 48d1c0: mov dword ptr [eax + 0x179d1fe], 0 */
	goto L_48d1d1;	/* 48d1ca: jmp 0x48d1d1 */
L_48d1cc:
	m->edx = 0x1u;	/* 48d1cc: mov edx, 1 */
L_48d1d1:
	M32((DWORD)(m->ebp + 0x2342425u)) = 0x40a00000u;	/* 48d1d1: mov dword ptr [ebp + 0x2342425], 0x40a00000 */
	{ DWORD a_ = M16((DWORD)(m->ebx + 0x3u)), b_ = 0x0u & 0xffffu, r_ = (a_ - b_) & 0xffffu; FLAGS(r_, 16); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 15) & 1; }	/* 48d1db: cmp word ptr [ebx + 3], 0 */
	if (m->sf != m->of) goto L_48db96;	/* 48d1e0: jl 0x48db96 */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(m->ebx + 0x2u)));	/* 48d1e6: movsx ecx, byte ptr [ebx + 2] */
	m->edi = M32(m->esp); m->esp += 4;	/* 48d1ea: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48d1eb: pop esi */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 48d1ec: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48d1ef: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48d1f2: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 48d1f4: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 48d1f7: lea ecx, [ecx + eax*8] */
	M32((DWORD)(m->ebp + m->ecx*2 + 0x179d1fau)) = m->edx;	/* 48d1fa: mov dword ptr [ebp + ecx*2 + 0x179d1fa], edx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 48d201: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48d202: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48d203: add esp, 0x3c */
	m->esp += 4 + 12; return;	/* 48d206: ret 0xc */
L_48d209:
	m->esi = (DWORD)(m->ebx + 0x2u);	/* 48d209: lea esi, [ebx + 2] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48d20c: or ecx, 0xffffffff */
	m->edi = m->esi;	/* 48d20f: mov edi, esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48d211: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48d213: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48d215: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 48d217: dec ecx */
	M32((DWORD)(m->esp + 0x58u)) = m->esi;	/* 48d218: mov dword ptr [esp + 0x58], esi */
	{ DWORD a_ = m->ecx, b_ = 0x11u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d21c: cmp ecx, 0x11 */
	if (!m->cf) goto L_48db8d;	/* 48d21f: jae 0x48db8d */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x11u))) & 0xff) << 0);	/* 48d225: mov al, byte ptr [esi + 0x11] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48d228: test al, al */
	if (m->sf != m->of) goto L_48db8d;	/* 48d22a: jl 0x48db8d */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x8u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48d230: cmp al, 8 */
	if (!m->zf && m->sf == m->of) goto L_48db8d;	/* 48d232: jg 0x48db8d */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x14u))) & 0xff) << 0);	/* 48d238: mov al, byte ptr [esi + 0x14] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x10u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48d23b: cmp al, 0x10 */
	if (!m->cf) goto L_48db8d;	/* 48d23d: jae 0x48db8d */
	m->ecx = M32((DWORD)(m->ebp + 0x15de6c8u));	/* 48d243: mov ecx, dword ptr [ebp + 0x15de6c8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48d249: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x15u))) & 0xff) << 0);	/* 48d24b: mov dl, byte ptr [esi + 0x15] */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d24e: cmp edx, ecx */
	if (!m->zf && m->sf == m->of) goto L_48db8d;	/* 48d250: jg 0x48db8d */
	m->edx = M32((DWORD)(m->ebp + 0x15fff84u));	/* 48d256: mov edx, dword ptr [ebp + 0x15fff84] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48d25c: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x16u))) & 0xff) << 0);	/* 48d25e: mov cl, byte ptr [esi + 0x16] */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d261: cmp ecx, edx */
	if (!m->zf && m->sf == m->of) goto L_48db8d;	/* 48d263: jg 0x48db8d */
	m->ecx = M32((DWORD)(m->ebp + 0x163b588u));	/* 48d269: mov ecx, dword ptr [ebp + 0x163b588] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48d26f: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x17u))) & 0xff) << 0);	/* 48d271: mov dl, byte ptr [esi + 0x17] */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d274: cmp edx, ecx */
	if (!m->zf && m->sf == m->of) goto L_48db8d;	/* 48d276: jg 0x48db8d */
	m->edx = M32((DWORD)(m->ebp + 0x1679b34u));	/* 48d27c: mov edx, dword ptr [ebp + 0x1679b34] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48d282: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x18u))) & 0xff) << 0);	/* 48d284: mov cl, byte ptr [esi + 0x18] */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d287: cmp ecx, edx */
	if (!m->zf && m->sf == m->of) goto L_48db8d;	/* 48d289: jg 0x48db8d */
	m->ecx = M32((DWORD)(m->ebp + 0x16c5178u));	/* 48d28f: mov ecx, dword ptr [ebp + 0x16c5178] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48d295: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x19u))) & 0xff) << 0);	/* 48d297: mov dl, byte ptr [esi + 0x19] */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d29a: cmp edx, ecx */
	if (!m->zf && m->sf == m->of) goto L_48db8d;	/* 48d29c: jg 0x48db8d */
	m->ecx = M32((DWORD)(m->ebp + 0x175522cu));	/* 48d2a2: mov ecx, dword ptr [ebp + 0x175522c] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48d2a8: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1au))) & 0xff) << 0);	/* 48d2aa: mov dl, byte ptr [esi + 0x1a] */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d2ad: cmp edx, ecx */
	if (!m->zf && m->sf == m->of) goto L_48db8d;	/* 48d2af: jg 0x48db8d */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48d2b5: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1bu))) & 0xff) << 0);	/* 48d2b7: mov dl, byte ptr [esi + 0x1b] */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d2ba: cmp edx, ecx */
	if (!m->zf && m->sf == m->of) goto L_48db8d;	/* 48d2bc: jg 0x48db8d */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48d2c2: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1cu))) & 0xff) << 0);	/* 48d2c4: mov dl, byte ptr [esi + 0x1c] */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d2c7: cmp edx, ecx */
	if (!m->zf && m->sf == m->of) goto L_48db8d;	/* 48d2c9: jg 0x48db8d */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48d2cf: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1du))) & 0xff) << 0);	/* 48d2d1: mov dl, byte ptr [esi + 0x1d] */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d2d4: cmp edx, ecx */
	if (!m->zf && m->sf == m->of) goto L_48db8d;	/* 48d2d6: jg 0x48db8d */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48d2dc: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1eu))) & 0xff) << 0);	/* 48d2de: mov dl, byte ptr [esi + 0x1e] */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d2e1: cmp edx, ecx */
	if (!m->zf && m->sf == m->of) goto L_48db8d;	/* 48d2e3: jg 0x48db8d */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48d2e9: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1fu))) & 0xff) << 0);	/* 48d2eb: mov dl, byte ptr [esi + 0x1f] */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d2ee: cmp edx, ecx */
	if (!m->zf && m->sf == m->of) goto L_48db8d;	/* 48d2f0: jg 0x48db8d */
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48d2f6: and eax, 0xff */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48d2fb: xor edx, edx */
	m->ecx = m->eax;	/* 48d2fd: mov ecx, eax */
	m->ebx = (DWORD)(m->ebp + 0x1f36c8u);	/* 48d2ff: lea ebx, [ebp + 0x1f36c8] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d305: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48d308: add ecx, eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48d30a: push esi */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d30b: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48d30e: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d310: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48d313: add ecx, eax */
	M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccb7cu)) = m->eax;	/* 48d315: mov dword ptr [ebp + ecx*8 + 0x1eccb7c], eax */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x14u))) & 0xff) << 0);	/* 48d31c: mov dl, byte ptr [esi + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d31f: push edx */
	m->ecx = m->ebx;	/* 48d320: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x48d327u; native_call(m, 0x473940u);	/* 48d322: call 0x473940 */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(m->esi + 0x11u)));	/* 48d327: movsx eax, byte ptr [esi + 0x11] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48d32b: xor ecx, ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48d32d: push eax */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x14u))) & 0xff) << 0);	/* 48d32e: mov cl, byte ptr [esi + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d331: push ecx */
	m->ecx = m->ebx;	/* 48d332: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x48d339u; native_call(m, 0x473a10u);	/* 48d334: call 0x473a10 */
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(m->esi + 0x12u)));	/* 48d339: movsx edx, byte ptr [esi + 0x12] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48d33d: xor eax, eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d33f: push edx */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x14u))) & 0xff) << 0);	/* 48d340: mov al, byte ptr [esi + 0x14] */
	m->ecx = m->ebx;	/* 48d343: mov ecx, ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48d345: push eax */
	m->esp -= 4; M32(m->esp) = 0x48d34bu; native_call(m, 0x473a80u);	/* 48d346: call 0x473a80 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48d34b: xor ecx, ecx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48d34d: xor edx, edx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x15u))) & 0xff) << 0);	/* 48d34f: mov cl, byte ptr [esi + 0x15] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x14u))) & 0xff) << 0);	/* 48d352: mov dl, byte ptr [esi + 0x14] */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 48d355: dec ecx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d356: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d357: push edx */
	m->ecx = m->ebx;	/* 48d358: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x48d35fu; native_call(m, 0x473b10u);	/* 48d35a: call 0x473b10 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48d35f: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48d361: xor ecx, ecx */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x16u))) & 0xff) << 0);	/* 48d363: mov al, byte ptr [esi + 0x16] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x14u))) & 0xff) << 0);	/* 48d366: mov cl, byte ptr [esi + 0x14] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 48d369: dec eax */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48d36a: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d36b: push ecx */
	m->ecx = m->ebx;	/* 48d36c: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x48d373u; native_call(m, 0x473c20u);	/* 48d36e: call 0x473c20 */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48d373: xor edx, edx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48d375: xor eax, eax */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x17u))) & 0xff) << 0);	/* 48d377: mov dl, byte ptr [esi + 0x17] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x14u))) & 0xff) << 0);	/* 48d37a: mov al, byte ptr [esi + 0x14] */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 48d37d: dec edx */
	m->ecx = m->ebx;	/* 48d37e: mov ecx, ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d380: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48d381: push eax */
	m->esp -= 4; M32(m->esp) = 0x48d387u; native_call(m, 0x473d30u);	/* 48d382: call 0x473d30 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48d387: xor ecx, ecx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48d389: xor edx, edx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x18u))) & 0xff) << 0);	/* 48d38b: mov cl, byte ptr [esi + 0x18] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x14u))) & 0xff) << 0);	/* 48d38e: mov dl, byte ptr [esi + 0x14] */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 48d391: dec ecx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d392: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d393: push edx */
	m->ecx = m->ebx;	/* 48d394: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x48d39bu; native_call(m, 0x473e40u);	/* 48d396: call 0x473e40 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48d39b: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48d39d: xor ecx, ecx */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x19u))) & 0xff) << 0);	/* 48d39f: mov al, byte ptr [esi + 0x19] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x14u))) & 0xff) << 0);	/* 48d3a2: mov cl, byte ptr [esi + 0x14] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 48d3a5: dec eax */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48d3a6: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d3a7: push ecx */
	m->ecx = m->ebx;	/* 48d3a8: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x48d3afu; native_call(m, 0x473f50u);	/* 48d3aa: call 0x473f50 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 48d3af: xor edi, edi */
L_48d3b1:
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48d3b1: xor edx, edx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48d3b3: xor eax, eax */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + m->edi*1 + 0x1au))) & 0xff) << 0);	/* 48d3b5: mov dl, byte ptr [esi + edi + 0x1a] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x14u))) & 0xff) << 0);	/* 48d3b9: mov al, byte ptr [esi + 0x14] */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 48d3bc: dec edx */
	m->ecx = m->ebx;	/* 48d3bd: mov ecx, ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d3bf: push edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48d3c0: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48d3c1: push eax */
	m->esp -= 4; M32(m->esp) = 0x48d3c7u; native_call(m, 0x474060u);	/* 48d3c2: call 0x474060 */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 48d3c7: inc edi */
	{ DWORD a_ = m->edi, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d3c8: cmp edi, 6 */
	if (m->sf != m->of) goto L_48d3b1;	/* 48d3cb: jl 0x48d3b1 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48d3cd: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x14u))) & 0xff) << 0);	/* 48d3cf: mov al, byte ptr [esi + 0x14] */
	m->edx = m->eax;	/* 48d3d2: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 48d3d4: shl edx, 4 */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(m->esi + 0x13u)));	/* 48d3d7: movsx ecx, byte ptr [esi + 0x13] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 48d3db: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 48d3dd: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 48d3e0: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 48d3e2: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 48d3e5: add edx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48d3e7: xor eax, eax */
	M32((DWORD)(m->ebp + m->edx*8 + 0x1eccb4cu)) = m->ecx;	/* 48d3e9: mov dword ptr [ebp + edx*8 + 0x1eccb4c], ecx */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x14u))) & 0xff) << 0);	/* 48d3f0: mov al, byte ptr [esi + 0x14] */
	m->ecx = m->eax;	/* 48d3f3: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d3f5: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48d3f8: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d3fa: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48d3fd: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d3ff: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48d402: add ecx, eax */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48d404: test esi, esi */
	m->eax = (DWORD)(m->ebp + m->ecx*8 + 0x1eccb08u);	/* 48d406: lea eax, [ebp + ecx*8 + 0x1eccb08] */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 48d40d: mov dword ptr [esp + 0x20], eax */
	if (m->zf) goto L_48d43a;	/* 48d411: je 0x48d43a */
	m->edx = M32((DWORD)(m->esp + 0x58u));	/* 48d413: mov edx, dword ptr [esp + 0x58] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48d417: or ecx, 0xffffffff */
	m->edi = m->edx;	/* 48d41a: mov edi, edx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48d41c: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48d41e: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48d420: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48d422: sub edi, ecx */
	m->eax = m->ecx;	/* 48d424: mov eax, ecx */
	m->esi = m->edi;	/* 48d426: mov esi, edi */
	m->edi = M32((DWORD)(m->esp + 0x20u));	/* 48d428: mov edi, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d42c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48d42f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48d431: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48d433: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48d436: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_48d441;	/* 48d438: jmp 0x48d441 */
L_48d43a:
	m->edx = M32((DWORD)(m->esp + 0x58u));	/* 48d43a: mov edx, dword ptr [esp + 0x58] */
	M8((DWORD)(m->eax + 0x0u)) = (BYTE)(0x0u);	/* 48d43e: mov byte ptr [eax], 0 */
L_48d441:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48d441: xor eax, eax */
	m->esi = (DWORD)(m->edx + 0x2bu);	/* 48d443: lea esi, [edx + 0x2b] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edx + 0x14u))) & 0xff) << 0);	/* 48d446: mov al, byte ptr [edx + 0x14] */
	m->ecx = m->eax;	/* 48d449: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d44b: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48d44e: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d450: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48d453: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d455: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48d458: add ecx, eax */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 48d45a: xor edi, edi */
	m->eax = (DWORD)(m->ebp + m->ecx*8 + 0x0u);	/* 48d45c: lea eax, [ebp + ecx*8] */
	m->ecx = M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccb4cu));	/* 48d460: mov ecx, dword ptr [ebp + ecx*8 + 0x1eccb4c] */
	M32((DWORD)(m->eax + 0x1eccb50u)) = m->ecx;	/* 48d467: mov dword ptr [eax + 0x1eccb50], ecx */
	goto L_48d473;	/* 48d46d: jmp 0x48d473 */
L_48d46f:
	m->edx = M32((DWORD)(m->esp + 0x58u));	/* 48d46f: mov edx, dword ptr [esp + 0x58] */
L_48d473:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0xau))) & 0xff) << 0);	/* 48d473: mov al, byte ptr [esi + 0xa] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 48d476: mov cl, byte ptr [esi] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48d478: push eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0xfffffff6u))) & 0xff) << 0);	/* 48d479: mov al, byte ptr [esi - 0xa] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d47c: push ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x9u))) & 0xff) << 0);	/* 48d47d: mov cl, byte ptr [esi + 9] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48d480: push eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0xffffffffu))) & 0xff) << 0);	/* 48d481: mov al, byte ptr [esi - 1] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d484: push ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0xfffffff5u))) & 0xff) << 0);	/* 48d485: mov cl, byte ptr [esi - 0xb] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48d488: push eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48d489: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edx + 0x14u))) & 0xff) << 0);	/* 48d48b: mov al, byte ptr [edx + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d48e: push ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48d48f: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48d490: push eax */
	m->ecx = m->ebx;	/* 48d491: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x48d498u; native_call(m, 0x474fd0u);	/* 48d493: call 0x474fd0 */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 48d498: inc edi */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 48d499: add esi, 2 */
	{ DWORD a_ = m->edi, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d49c: cmp edi, 5 */
	if (m->sf != m->of) goto L_48d46f;	/* 48d49f: jl 0x48d46f */
	m->edx = M32((DWORD)(m->esp + 0x58u));	/* 48d4a1: mov edx, dword ptr [esp + 0x58] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48d4a5: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->edx + 0x14u))) & 0xff) << 0);	/* 48d4a7: mov cl, byte ptr [edx + 0x14] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 48d4aa: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48d4ad: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48d4b0: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 48d4b2: lea eax, [eax + eax*2] */
	m->edx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 48d4b5: lea edx, [ecx + eax*8] */
	m->eax = M32((DWORD)(m->ebp + m->edx*2 + 0x1755278u));	/* 48d4b8: mov eax, dword ptr [ebp + edx*2 + 0x1755278] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48d4bf: test eax, eax */
	if (m->sf != m->of) goto L_48db96;	/* 48d4c1: jl 0x48db96 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d4c7: push ecx */
	m->ecx = m->ebx;	/* 48d4c8: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x48d4cfu; native_call(m, 0x474390u);	/* 48d4ca: call 0x474390 */
	m->edi = M32(m->esp); m->esp += 4;	/* 48d4cf: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48d4d0: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 48d4d1: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48d4d2: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48d4d3: add esp, 0x3c */
	m->esp += 4 + 12; return;	/* 48d4d6: ret 0xc */
L_48d4d9:
	{ DWORD a_ = M8((DWORD)(m->ebx + 0x2u)), b_ = 0x6bu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48d4d9: cmp byte ptr [ebx + 2], 0x6b */
	if (!m->zf) goto L_48db8d;	/* 48d4dd: jne 0x48db8d */
	m->ecx = M32((DWORD)(m->ebp + 0x23423b5u));	/* 48d4e3: mov ecx, dword ptr [ebp + 0x23423b5] */
	m->eax = 0x2u;	/* 48d4e9: mov eax, 2 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d4ee: cmp ecx, eax */
	if (m->zf) goto L_48db96;	/* 48d4f0: je 0x48db96 */
	m->ecx = m->ebp;	/* 48d4f6: mov ecx, ebp */
	M32((DWORD)(m->ebp + 0x23423b5u)) = m->eax;	/* 48d4f8: mov dword ptr [ebp + 0x23423b5], eax */
	m->esp -= 4; M32(m->esp) = 0x48d503u; native_call(m, 0x462f30u);	/* 48d4fe: call 0x462f30 */
	m->eax = M32((DWORD)(m->ebp + 0x23423a1u));	/* 48d503: mov eax, dword ptr [ebp + 0x23423a1] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48d509: test eax, eax */
	if (!m->zf) goto L_48db96;	/* 48d50b: jne 0x48db96 */
	M32((DWORD)(m->ebp + 0x23423a1u)) = m->edi;	/* 48d511: mov dword ptr [ebp + 0x23423a1], edi */
	M32((DWORD)(m->ebp + 0x23423a5u)) = 0x40400000u;	/* 48d517: mov dword ptr [ebp + 0x23423a5], 0x40400000 */
	M32((DWORD)(0x9f67f8u)) = m->edi;	/* 48d521: mov dword ptr [0x9f67f8], edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 48d527: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48d528: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 48d529: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48d52a: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48d52b: add esp, 0x3c */
	m->esp += 4 + 12; return;	/* 48d52e: ret 0xc */
L_48d531:
	{ DWORD a_ = M8((DWORD)(m->ebx + 0x2u)), b_ = 0x6bu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48d531: cmp byte ptr [ebx + 2], 0x6b */
	if (!m->zf) goto L_48db8d;	/* 48d535: jne 0x48db8d */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x22f0408u)), b_ = 0x1eu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d53b: cmp dword ptr [ebp + 0x22f0408], 0x1e */
	if (m->zf || m->sf != m->of) goto L_48db96;	/* 48d542: jle 0x48db96 */
	m->eax = M32((DWORD)(m->ebp + 0x23423b5u));	/* 48d548: mov eax, dword ptr [ebp + 0x23423b5] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 48d54e: xor esi, esi */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d550: cmp eax, esi */
	if (m->zf) goto L_48db96;	/* 48d552: je 0x48db96 */
	m->ecx = m->ebp;	/* 48d558: mov ecx, ebp */
	M32((DWORD)(m->ebp + 0x23423b5u)) = m->esi;	/* 48d55a: mov dword ptr [ebp + 0x23423b5], esi */
	m->esp -= 4; M32(m->esp) = 0x48d565u; native_call(m, 0x462f90u);	/* 48d560: call 0x462f90 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2342399u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d565: cmp dword ptr [ebp + 0x2342399], esi */
	if (!m->zf) goto L_48db96;	/* 48d56b: jne 0x48db96 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x22e7184u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d571: cmp dword ptr [ebp + 0x22e7184], edi */
	if (!m->zf) goto L_48d60b;	/* 48d577: jne 0x48d60b */
	m->eax = M32((DWORD)(m->ebp + 0x2221fb8u));	/* 48d57d: mov eax, dword ptr [ebp + 0x2221fb8] */
	m->ecx = M32((DWORD)(m->ebp + 0x2221fbcu));	/* 48d583: mov ecx, dword ptr [ebp + 0x2221fbc] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d589: cmp eax, ecx */
	if (m->zf || m->sf != m->of) goto L_48d5f7;	/* 48d58b: jle 0x48d5f7 */
	M32((DWORD)(m->ebp + 0x23423bdu)) = m->esi;	/* 48d58d: mov dword ptr [ebp + 0x23423bd], esi */
	goto L_48d60b;	/* 48d593: jmp 0x48d60b */
L_48d595:
	{ DWORD a_ = M8((DWORD)(m->ebx + 0x2u)), b_ = 0x6bu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48d595: cmp byte ptr [ebx + 2], 0x6b */
	if (!m->zf) goto L_48db8d;	/* 48d599: jne 0x48db8d */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x22f0408u)), b_ = 0x1eu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d59f: cmp dword ptr [ebp + 0x22f0408], 0x1e */
	if (m->zf || m->sf != m->of) goto L_48db96;	/* 48d5a6: jle 0x48db96 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x23423b5u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d5ac: cmp dword ptr [ebp + 0x23423b5], edi */
	if (m->zf) goto L_48db96;	/* 48d5b2: je 0x48db96 */
	m->ecx = m->ebp;	/* 48d5b8: mov ecx, ebp */
	M32((DWORD)(m->ebp + 0x23423b5u)) = m->edi;	/* 48d5ba: mov dword ptr [ebp + 0x23423b5], edi */
	m->esp -= 4; M32(m->esp) = 0x48d5c5u; native_call(m, 0x462fd0u);	/* 48d5c0: call 0x462fd0 */
	m->eax = M32((DWORD)(m->ebp + 0x2342399u));	/* 48d5c5: mov eax, dword ptr [ebp + 0x2342399] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48d5cb: test eax, eax */
	if (!m->zf) goto L_48db96;	/* 48d5cd: jne 0x48db96 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x22e7184u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d5d3: cmp dword ptr [ebp + 0x22e7184], edi */
	if (!m->zf) goto L_48d60b;	/* 48d5d9: jne 0x48d60b */
	m->eax = M32((DWORD)(m->ebp + 0x2221fb8u));	/* 48d5db: mov eax, dword ptr [ebp + 0x2221fb8] */
	m->ecx = M32((DWORD)(m->ebp + 0x2221fbcu));	/* 48d5e1: mov ecx, dword ptr [ebp + 0x2221fbc] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d5e7: cmp eax, ecx */
	if (m->zf || m->sf != m->of) goto L_48d5f7;	/* 48d5e9: jle 0x48d5f7 */
	M32((DWORD)(m->ebp + 0x23423bdu)) = 0x0u;	/* 48d5eb: mov dword ptr [ebp + 0x23423bd], 0 */
	goto L_48d60b;	/* 48d5f5: jmp 0x48d60b */
L_48d5f7:
	if (m->sf == m->of) goto L_48d601;	/* 48d5f7: jge 0x48d601 */
	M32((DWORD)(m->ebp + 0x23423bdu)) = m->edi;	/* 48d5f9: mov dword ptr [ebp + 0x23423bd], edi */
	goto L_48d60b;	/* 48d5ff: jmp 0x48d60b */
L_48d601:
	M32((DWORD)(m->ebp + 0x23423bdu)) = 0xffffffffu;	/* 48d601: mov dword ptr [ebp + 0x23423bd], 0xffffffff */
L_48d60b:
	M32((DWORD)(m->ebp + 0x2342399u)) = m->edi;	/* 48d60b: mov dword ptr [ebp + 0x2342399], edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 48d611: pop edi */
	M32((DWORD)(m->ebp + 0x234239du)) = 0x41200000u;	/* 48d612: mov dword ptr [ebp + 0x234239d], 0x41200000 */
	m->esi = M32(m->esp); m->esp += 4;	/* 48d61c: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 48d61d: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48d61e: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48d61f: add esp, 0x3c */
	m->esp += 4 + 12; return;	/* 48d622: ret 0xc */
L_48d625:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 48d625: mov al, byte ptr [ebx + 2] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x10u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48d628: cmp al, 0x10 */
	if (!m->cf && !m->zf) goto L_48db8d;	/* 48d62a: ja 0x48db8d */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48d630: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48d632: and eax, 0xff */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x3u))) & 0xff) << 0);	/* 48d637: mov cl, byte ptr [ebx + 3] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d63a: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48d63b: push eax */
	m->ecx = m->ebp;	/* 48d63c: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x48d643u; native_call(m, 0x463030u);	/* 48d63e: call 0x463030 */
	m->edi = M32(m->esp); m->esp += 4;	/* 48d643: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48d644: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 48d645: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48d646: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48d647: add esp, 0x3c */
	m->esp += 4 + 12; return;	/* 48d64a: ret 0xc */
L_48d64d:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 48d64d: mov dl, byte ptr [ebx + 2] */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = 0x10u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48d650: cmp dl, 0x10 */
	if (!m->cf && !m->zf) goto L_48db8d;	/* 48d653: ja 0x48db8d */
	m->esi = (DWORD)(m->ebx + 0x3u);	/* 48d659: lea esi, [ebx + 3] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48d65c: or ecx, 0xffffffff */
	m->edi = m->esi;	/* 48d65f: mov edi, esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48d661: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48d663: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48d665: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 48d667: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0x39u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d668: cmp ecx, 0x39 */
	if (!m->cf) goto L_48db8d;	/* 48d66b: jae 0x48db8d */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(m->ebx + 0x3cu)));	/* 48d671: movsx eax, byte ptr [ebx + 0x3c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48d675: push eax */
	{ DWORD a_ = m->edx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48d676: and edx, 0xff */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48d67c: push esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d67d: push edx */
	m->ecx = m->ebp;	/* 48d67e: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x48d685u; native_call(m, 0x462c30u);	/* 48d680: call 0x462c30 */
	m->edi = M32(m->esp); m->esp += 4;	/* 48d685: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48d686: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 48d687: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48d688: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48d689: add esp, 0x3c */
	m->esp += 4 + 12; return;	/* 48d68c: ret 0xc */
L_48d68f:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 48d68f: mov dl, byte ptr [ebx + 2] */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = 0x10u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48d692: cmp dl, 0x10 */
	if (!m->cf && !m->zf) goto L_48db8d;	/* 48d695: ja 0x48db8d */
	m->esi = (DWORD)(m->ebx + 0x3u);	/* 48d69b: lea esi, [ebx + 3] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48d69e: or ecx, 0xffffffff */
	m->edi = m->esi;	/* 48d6a1: mov edi, esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48d6a3: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48d6a5: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48d6a7: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 48d6a9: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0x11u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d6aa: cmp ecx, 0x11 */
	if (!m->cf) goto L_48db8d;	/* 48d6ad: jae 0x48db8d */
	m->edi = (DWORD)(m->ebp + 0x1f36c8u);	/* 48d6b3: lea edi, [ebp + 0x1f36c8] */
	{ DWORD a_ = m->edx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48d6b9: and edx, 0xff */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d6bf: push edx */
	m->ecx = m->edi;	/* 48d6c0: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x48d6c7u; native_call(m, 0x4743b0u);	/* 48d6c2: call 0x4743b0 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48d6c7: xor ecx, ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48d6c9: push esi */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 48d6ca: mov cl, byte ptr [ebx + 2] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d6cd: push ecx */
	m->ecx = m->edi;	/* 48d6ce: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x48d6d5u; native_call(m, 0x473940u);	/* 48d6d0: call 0x473940 */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48d6d5: xor edx, edx */
	m->ecx = m->edi;	/* 48d6d7: mov ecx, edi */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 48d6d9: mov dl, byte ptr [ebx + 2] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d6dc: push edx */
	m->esp -= 4; M32(m->esp) = 0x48d6e2u; native_call(m, 0x4743e0u);	/* 48d6dd: call 0x4743e0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48d6e2: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 48d6e4: mov al, byte ptr [ebx + 2] */
	m->ecx = m->eax;	/* 48d6e7: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d6e9: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48d6ec: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d6ee: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48d6f1: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d6f3: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48d6f6: add ecx, eax */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48d6f8: test esi, esi */
	m->edx = (DWORD)(m->ebp + m->ecx*8 + 0x1eccb08u);	/* 48d6fa: lea edx, [ebp + ecx*8 + 0x1eccb08] */
	if (m->zf) goto L_48d724;	/* 48d701: je 0x48d724 */
	m->edi = m->esi;	/* 48d703: mov edi, esi */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48d705: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48d708: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48d70a: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48d70c: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48d70e: sub edi, ecx */
	m->eax = m->ecx;	/* 48d710: mov eax, ecx */
	m->esi = m->edi;	/* 48d712: mov esi, edi */
	m->edi = m->edx;	/* 48d714: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d716: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48d719: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48d71b: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48d71d: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48d720: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_48d727;	/* 48d722: jmp 0x48d727 */
L_48d724:
	M8((DWORD)(m->edx + 0x0u)) = (BYTE)(0x0u);	/* 48d724: mov byte ptr [edx], 0 */
L_48d727:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48d727: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 48d729: mov al, byte ptr [ebx + 2] */
	m->ecx = m->eax;	/* 48d72c: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d72e: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48d731: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d733: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48d736: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d738: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48d73b: add ecx, eax */
	M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccb7cu)) = m->eax;	/* 48d73d: mov dword ptr [ebp + ecx*8 + 0x1eccb7c], eax */
	m->edx = M32((DWORD)(m->ebp + 0x234240du));	/* 48d744: mov edx, dword ptr [ebp + 0x234240d] */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 48d74a: shl edx, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48d74d: xor eax, eax */
	m->ecx = m->ebp;	/* 48d74f: mov ecx, ebp */
	M32((DWORD)(m->edx + m->ebp*1 + 0x234300au)) = 0x1u;	/* 48d751: mov dword ptr [edx + ebp + 0x234300a], 1 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 48d75c: mov al, byte ptr [ebx + 2] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48d75f: push eax */
	m->esp -= 4; M32(m->esp) = 0x48d765u; native_call(m, 0x462b50u);	/* 48d760: call 0x462b50 */
	m->eax = M32((DWORD)(m->ebp + 0x4u));	/* 48d765: mov eax, dword ptr [ebp + 4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48d768: test eax, eax */
	if (!m->zf) goto L_48db96;	/* 48d76a: jne 0x48db96 */
	m->ecx = m->ebp;	/* 48d770: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x48d777u; native_call(m, 0x48ead0u);	/* 48d772: call 0x48ead0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 48d777: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48d778: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 48d779: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48d77a: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48d77b: add esp, 0x3c */
	m->esp += 4 + 12; return;	/* 48d77e: ret 0xc */
L_48d781:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 48d781: mov al, byte ptr [ebx + 2] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x10u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48d784: cmp al, 0x10 */
	if (!m->cf && !m->zf) goto L_48db8d;	/* 48d786: ja 0x48db8d */
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48d78c: and eax, 0xff */
	m->ecx = m->ebp;	/* 48d791: mov ecx, ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48d793: push eax */
	m->esp -= 4; M32(m->esp) = 0x48d799u; native_call(m, 0x462bc0u);	/* 48d794: call 0x462bc0 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48d799: xor ecx, ecx */
	m->esi = (DWORD)(m->ebp + 0x1f36c8u);	/* 48d79b: lea esi, [ebp + 0x1f36c8] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 48d7a1: mov cl, byte ptr [ebx + 2] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d7a4: push ecx */
	m->ecx = m->esi;	/* 48d7a5: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x48d7acu; native_call(m, 0x4743b0u);	/* 48d7a7: call 0x4743b0 */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48d7ac: xor edx, edx */
	m->ecx = m->esi;	/* 48d7ae: mov ecx, esi */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 48d7b0: mov dl, byte ptr [ebx + 2] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d7b3: push edx */
	m->esp -= 4; M32(m->esp) = 0x48d7b9u; native_call(m, 0x4743e0u);	/* 48d7b4: call 0x4743e0 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48d7b9: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 48d7bb: mov cl, byte ptr [ebx + 2] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 48d7be: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48d7c1: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48d7c4: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 48d7c6: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 48d7c9: lea ecx, [ecx + eax*8] */
	M8((DWORD)(m->ebp + m->ecx*2 + 0x1755234u)) = (BYTE)(0x0u);	/* 48d7cc: mov byte ptr [ebp + ecx*2 + 0x1755234], 0 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48d7d4: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 48d7d6: mov cl, byte ptr [ebx + 2] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 48d7d9: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48d7dc: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48d7df: sub eax, ecx */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 48d7e1: lea edx, [eax + eax*2] */
	m->eax = (DWORD)(m->ecx + m->edx*8 + 0x0u);	/* 48d7e4: lea eax, [ecx + edx*8] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48d7e7: xor ecx, ecx */
	M32((DWORD)(m->ebp + m->eax*2 + 0x1755278u)) = 0xffffffffu;	/* 48d7e9: mov dword ptr [ebp + eax*2 + 0x1755278], 0xffffffff */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 48d7f4: mov cl, byte ptr [ebx + 2] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d7f7: push ecx */
	m->ecx = m->esi;	/* 48d7f8: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x48d7ffu; native_call(m, 0x45dca0u);	/* 48d7fa: call 0x45dca0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 48d7ff: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48d800: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 48d801: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48d802: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48d803: add esp, 0x3c */
	m->esp += 4 + 12; return;	/* 48d806: ret 0xc */
L_48d809:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 48d809: mov al, byte ptr [ebx + 2] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x10u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48d80c: cmp al, 0x10 */
	if (!m->cf) goto L_48db8d;	/* 48d80e: jae 0x48db8d */
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(m->ebx + 0x3u)));	/* 48d814: movsx edx, byte ptr [ebx + 3] */
	m->esi = (DWORD)(m->ebp + 0x1f36c8u);	/* 48d818: lea esi, [ebp + 0x1f36c8] */
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48d81e: and eax, 0xff */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d823: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48d824: push eax */
	m->ecx = m->esi;	/* 48d825: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x48d82cu; native_call(m, 0x473a80u);	/* 48d827: call 0x473a80 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x22e7184u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d82c: cmp dword ptr [ebp + 0x22e7184], edi */
	if (!m->zf) goto L_48d898;	/* 48d832: jne 0x48d898 */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(m->ebx + 0x3u)));	/* 48d834: movsx eax, byte ptr [ebx + 3] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48d838: push eax */
	m->ecx = m->ebp;	/* 48d839: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x48d840u; native_call(m, 0x463740u);	/* 48d83b: call 0x463740 */
	m->ecx = (DWORD)(m->eax*4 + 0x4a9824u);	/* 48d840: lea ecx, [eax*4 + 0x4a9824] */
	m->edx = (DWORD)(m->eax*4 + 0x4a9810u);	/* 48d847: lea edx, [eax*4 + 0x4a9810] */
	m->eax = (DWORD)(m->eax*4 + 0x4a97fcu);	/* 48d84e: lea eax, [eax*4 + 0x4a97fc] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 48d855: xor edi, edi */
	M32((DWORD)(m->esp + 0x58u)) = m->ecx;	/* 48d857: mov dword ptr [esp + 0x58], ecx */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 48d85b: mov dword ptr [esp + 0x10], edx */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 48d85f: mov dword ptr [esp + 0x14], eax */
L_48d863:
	m->ecx = M32((DWORD)(m->esp + 0x58u));	/* 48d863: mov ecx, dword ptr [esp + 0x58] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 48d867: mov eax, dword ptr [esp + 0x10] */
	{ DWORD v_ = 0x3f7fbe77u; m->esp -= 4; M32(m->esp) = v_; }	/* 48d86b: push 0x3f7fbe77 */
	{ DWORD v_ = 0xbf800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 48d870: push 0xbf800000 */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 48d875: mov edx, dword ptr [ecx] */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 48d877: mov ecx, dword ptr [eax] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48d879: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d87b: push edx */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 48d87c: mov edx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d880: push ecx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48d881: xor ecx, ecx */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 48d883: mov eax, dword ptr [edx] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 48d885: mov cl, byte ptr [ebx + 2] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48d888: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48d889: push edi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d88a: push ecx */
	m->ecx = m->esi;	/* 48d88b: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x48d892u; native_call(m, 0x474b50u);	/* 48d88d: call 0x474b50 */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 48d892: inc edi */
	{ DWORD a_ = m->edi, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d893: cmp edi, 5 */
	if (m->sf != m->of) goto L_48d863;	/* 48d896: jl 0x48d863 */
L_48d898:
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48d898: xor edx, edx */
	m->edi = (DWORD)(m->ebx + 0x4u);	/* 48d89a: lea edi, [ebx + 4] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 48d89d: mov dl, byte ptr [ebx + 2] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48d8a0: push edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d8a1: push edx */
	m->ecx = m->esi;	/* 48d8a2: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x48d8a9u; native_call(m, 0x473940u);	/* 48d8a4: call 0x473940 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48d8a9: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 48d8ab: mov al, byte ptr [ebx + 2] */
	m->ecx = m->eax;	/* 48d8ae: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d8b0: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48d8b3: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d8b5: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48d8b8: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d8ba: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48d8bd: add ecx, eax */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48d8bf: test edi, edi */
	m->edx = (DWORD)(m->ebp + m->ecx*8 + 0x1eccb08u);	/* 48d8c1: lea edx, [ebp + ecx*8 + 0x1eccb08] */
	if (m->zf) goto L_48d8e9;	/* 48d8c8: je 0x48d8e9 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48d8ca: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48d8cd: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48d8cf: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48d8d1: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48d8d3: sub edi, ecx */
	m->eax = m->ecx;	/* 48d8d5: mov eax, ecx */
	m->esi = m->edi;	/* 48d8d7: mov esi, edi */
	m->edi = m->edx;	/* 48d8d9: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d8db: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48d8de: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48d8e0: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48d8e2: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48d8e5: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_48d8ec;	/* 48d8e7: jmp 0x48d8ec */
L_48d8e9:
	M8((DWORD)(m->edx + 0x0u)) = (BYTE)(0x0u);	/* 48d8e9: mov byte ptr [edx], 0 */
L_48d8ec:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48d8ec: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 48d8ee: mov al, byte ptr [ebx + 2] */
	m->ecx = m->eax;	/* 48d8f1: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d8f3: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48d8f6: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d8f8: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48d8fb: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d8fd: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48d900: add ecx, eax */
	M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccb7cu)) = m->eax;	/* 48d902: mov dword ptr [ebp + ecx*8 + 0x1eccb7c], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48d909: xor eax, eax */
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(m->ebx + 0x3u)));	/* 48d90b: movsx edx, byte ptr [ebx + 3] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 48d90f: mov al, byte ptr [ebx + 2] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d912: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48d913: push eax */
	m->ecx = m->ebp;	/* 48d914: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x48d91bu; native_call(m, 0x462d30u);	/* 48d916: call 0x462d30 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x3u))) & 0xff) << 0);	/* 48d91b: mov al, byte ptr [ebx + 3] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48d91e: test al, al */
	if (m->sf == m->of) goto L_48db96;	/* 48d920: jge 0x48db96 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48d926: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 48d928: mov al, byte ptr [ebx + 2] */
	m->ecx = m->eax;	/* 48d92b: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d92d: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48d930: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d932: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48d935: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48d937: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48d93a: add ecx, eax */
	{ DWORD a_ = M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccb48u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d93c: cmp dword ptr [ebp + ecx*8 + 0x1eccb48], 1 */
	if (!m->zf) goto L_48db96;	/* 48d944: jne 0x48db96 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48d94a: push eax */
	m->ecx = (DWORD)(m->ebp + 0x1f36c8u);	/* 48d94b: lea ecx, [ebp + 0x1f36c8] */
	m->esp -= 4; M32(m->esp) = 0x48d956u; native_call(m, 0x45dca0u);	/* 48d951: call 0x45dca0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48d956: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 48d958: mov al, byte ptr [ebx + 2] */
	goto L_48daa9;	/* 48d95b: jmp 0x48daa9 */
L_48d960:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 48d960: mov al, byte ptr [ebx + 2] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x10u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48d963: cmp al, 0x10 */
	if (m->sf == m->of) goto L_48db8d;	/* 48d965: jge 0x48db8d */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(m->ebx + 0x3u)));	/* 48d96b: movsx ecx, byte ptr [ebx + 3] */
	m->edx = (DWORD)(int)(signed char)(((m->eax >> 0) & 0xff));	/* 48d96f: movsx edx, al */
	m->esi = (DWORD)(m->ebp + 0x1f36c8u);	/* 48d972: lea esi, [ebp + 0x1f36c8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d978: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d979: push edx */
	m->ecx = m->esi;	/* 48d97a: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x48d981u; native_call(m, 0x473a80u);	/* 48d97c: call 0x473a80 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x22e7184u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d981: cmp dword ptr [ebp + 0x22e7184], edi */
	if (!m->zf) goto L_48d9ec;	/* 48d987: jne 0x48d9ec */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(m->ebx + 0x3u)));	/* 48d989: movsx eax, byte ptr [ebx + 3] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48d98d: push eax */
	m->ecx = m->ebp;	/* 48d98e: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x48d995u; native_call(m, 0x463740u);	/* 48d990: call 0x463740 */
	m->ecx = (DWORD)(m->eax*4 + 0x4a9824u);	/* 48d995: lea ecx, [eax*4 + 0x4a9824] */
	m->edx = (DWORD)(m->eax*4 + 0x4a9810u);	/* 48d99c: lea edx, [eax*4 + 0x4a9810] */
	m->eax = (DWORD)(m->eax*4 + 0x4a97fcu);	/* 48d9a3: lea eax, [eax*4 + 0x4a97fc] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 48d9aa: xor edi, edi */
	M32((DWORD)(m->esp + 0x58u)) = m->ecx;	/* 48d9ac: mov dword ptr [esp + 0x58], ecx */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 48d9b0: mov dword ptr [esp + 0x10], edx */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 48d9b4: mov dword ptr [esp + 0x14], eax */
L_48d9b8:
	m->ecx = M32((DWORD)(m->esp + 0x58u));	/* 48d9b8: mov ecx, dword ptr [esp + 0x58] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 48d9bc: mov eax, dword ptr [esp + 0x10] */
	{ DWORD v_ = 0x3f7fbe77u; m->esp -= 4; M32(m->esp) = v_; }	/* 48d9c0: push 0x3f7fbe77 */
	{ DWORD v_ = 0xbf800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 48d9c5: push 0xbf800000 */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 48d9ca: mov edx, dword ptr [ecx] */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 48d9cc: mov ecx, dword ptr [eax] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48d9ce: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d9d0: push edx */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 48d9d1: mov edx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d9d5: push ecx */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(m->ebx + 0x2u)));	/* 48d9d6: movsx ecx, byte ptr [ebx + 2] */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 48d9da: mov eax, dword ptr [edx] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48d9dc: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48d9dd: push edi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d9de: push ecx */
	m->ecx = m->esi;	/* 48d9df: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x48d9e6u; native_call(m, 0x474b50u);	/* 48d9e1: call 0x474b50 */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 48d9e6: inc edi */
	{ DWORD a_ = m->edi, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48d9e7: cmp edi, 5 */
	if (m->sf != m->of) goto L_48d9b8;	/* 48d9ea: jl 0x48d9b8 */
L_48d9ec:
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(m->ebx + 0x2u)));	/* 48d9ec: movsx edx, byte ptr [ebx + 2] */
	m->edi = (DWORD)(m->ebx + 0x4u);	/* 48d9f0: lea edi, [ebx + 4] */
	m->ecx = m->esi;	/* 48d9f3: mov ecx, esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48d9f5: push edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48d9f6: push edx */
	m->esp -= 4; M32(m->esp) = 0x48d9fcu; native_call(m, 0x473940u);	/* 48d9f7: call 0x473940 */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(m->ebx + 0x2u)));	/* 48d9fc: movsx eax, byte ptr [ebx + 2] */
	m->ecx = m->eax;	/* 48da00: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48da02: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48da05: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48da07: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48da0a: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48da0c: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48da0f: add ecx, eax */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48da11: test edi, edi */
	m->edx = (DWORD)(m->ebp + m->ecx*8 + 0x1eccb08u);	/* 48da13: lea edx, [ebp + ecx*8 + 0x1eccb08] */
	if (m->zf) goto L_48da3b;	/* 48da1a: je 0x48da3b */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48da1c: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48da1f: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48da21: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48da23: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48da25: sub edi, ecx */
	m->eax = m->ecx;	/* 48da27: mov eax, ecx */
	m->esi = m->edi;	/* 48da29: mov esi, edi */
	m->edi = m->edx;	/* 48da2b: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48da2d: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48da30: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48da32: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48da34: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48da37: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_48da3e;	/* 48da39: jmp 0x48da3e */
L_48da3b:
	M8((DWORD)(m->edx + 0x0u)) = (BYTE)(0x0u);	/* 48da3b: mov byte ptr [edx], 0 */
L_48da3e:
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(m->ebx + 0x2u)));	/* 48da3e: movsx eax, byte ptr [ebx + 2] */
	m->ecx = m->eax;	/* 48da42: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48da44: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48da47: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48da49: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48da4c: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48da4e: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48da51: add ecx, eax */
	M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccb7cu)) = m->eax;	/* 48da53: mov dword ptr [ebp + ecx*8 + 0x1eccb7c], eax */
	m->ecx = m->ebp;	/* 48da5a: mov ecx, ebp */
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(m->ebx + 0x3u)));	/* 48da5c: movsx edx, byte ptr [ebx + 3] */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(m->ebx + 0x2u)));	/* 48da60: movsx eax, byte ptr [ebx + 2] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48da64: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48da65: push eax */
	m->esp -= 4; M32(m->esp) = 0x48da6bu; native_call(m, 0x462e30u);	/* 48da66: call 0x462e30 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x3u))) & 0xff) << 0);	/* 48da6b: mov al, byte ptr [ebx + 3] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48da6e: test al, al */
	if (m->sf == m->of) goto L_48db96;	/* 48da70: jge 0x48db96 */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(m->ebx + 0x2u)));	/* 48da76: movsx eax, byte ptr [ebx + 2] */
	m->ecx = m->eax;	/* 48da7a: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48da7c: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48da7f: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48da81: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48da84: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48da86: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48da89: add ecx, eax */
	{ DWORD a_ = M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccb48u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48da8b: cmp dword ptr [ebp + ecx*8 + 0x1eccb48], 1 */
	if (!m->zf) goto L_48db96;	/* 48da93: jne 0x48db96 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48da99: push eax */
	m->ecx = (DWORD)(m->ebp + 0x1f36c8u);	/* 48da9a: lea ecx, [ebp + 0x1f36c8] */
	m->esp -= 4; M32(m->esp) = 0x48daa5u; native_call(m, 0x45dca0u);	/* 48daa0: call 0x45dca0 */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(m->ebx + 0x2u)));	/* 48daa5: movsx eax, byte ptr [ebx + 2] */
L_48daa9:
	m->edx = m->eax;	/* 48daa9: mov edx, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 48daab: pop edi */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 48daac: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 48daaf: add edx, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 48dab1: pop esi */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 48dab2: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 48dab5: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 48dab7: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 48daba: add edx, eax */
	m->eax = M32((DWORD)(m->ebp + m->edx*8 + 0x1eccb58u));	/* 48dabc: mov eax, dword ptr [ebp + edx*8 + 0x1eccb58] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48dac3: inc eax */
	m->ebp = (DWORD)(m->ebp + m->edx*8 + 0x1eccb58u);	/* 48dac4: lea ebp, [ebp + edx*8 + 0x1eccb58] */
	M32((DWORD)(m->ebp + 0x0u)) = m->eax;	/* 48dacb: mov dword ptr [ebp], eax */
	m->ebp = M32(m->esp); m->esp += 4;	/* 48dace: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48dacf: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48dad0: add esp, 0x3c */
	m->esp += 4 + 12; return;	/* 48dad3: ret 0xc */
L_48dad6:
	{ DWORD a_ = M8((DWORD)(m->ebx + 0x2u)), b_ = 0x6bu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48dad6: cmp byte ptr [ebx + 2], 0x6b */
	if (!m->zf) goto L_48db8d;	/* 48dada: jne 0x48db8d */
	m->edi = M32(m->esp); m->esp += 4;	/* 48dae0: pop edi */
	M32((DWORD)(m->ebp + 0x233cc4cu)) = 0x40a00000u;	/* 48dae1: mov dword ptr [ebp + 0x233cc4c], 0x40a00000 */
	m->esi = M32(m->esp); m->esp += 4;	/* 48daeb: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 48daec: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48daed: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48daee: add esp, 0x3c */
	m->esp += 4 + 12; return;	/* 48daf1: ret 0xc */
L_48daf4:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2343253u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48daf4: cmp dword ptr [ebp + 0x2343253], edi */
	if (m->zf) goto L_48db96;	/* 48dafa: je 0x48db96 */
	m->eax = M32((DWORD)(m->ebp + 0x22f0400u));	/* 48db00: mov eax, dword ptr [ebp + 0x22f0400] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 48db06: xor edi, edi */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48db08: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48db0a: cmp eax, edi */
	if (m->zf || m->sf != m->of) goto L_48db79;	/* 48db0c: jle 0x48db79 */
	m->esi = (DWORD)(m->ebp + 0x22ee4e4u);	/* 48db0e: lea esi, [ebp + 0x22ee4e4] */
L_48db14:
	{ DWORD a_ = m->ecx, b_ = 0x7cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48db14: cmp ecx, 0x7c */
	if (m->sf == m->of) goto L_48db79;	/* 48db17: jge 0x48db79 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0xffffffdcu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48db19: cmp dword ptr [esi - 0x24], edi */
	if (m->sf != m->of) goto L_48db6b;	/* 48db1c: jl 0x48db6b */
	m->eax = m->ecx;	/* 48db1e: mov eax, ecx */
	{ DWORD a_ = m->eax, b_ = 0x80000001u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48db20: and eax, 0x80000001 */
	if (!m->sf) goto L_48db2c;	/* 48db25: jns 0x48db2c */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 48db27: dec eax */
	{ DWORD a_ = m->eax, b_ = 0xfffffffeu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48db28: or eax, 0xfffffffe */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48db2b: inc eax */
L_48db2c:
	m->eax = m->ecx;	/* 48db2c: mov eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48db2e: cdq  */
	if (!m->zf) goto L_48db3b;	/* 48db2f: jne 0x48db3b */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48db31: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48db33: sar eax, 1 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + m->ebx*1 + 0x2u))) & 0xff) << 0);	/* 48db35: mov al, byte ptr [eax + ebx + 2] */
	goto L_48db46;	/* 48db39: jmp 0x48db46 */
L_48db3b:
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48db3b: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48db3d: sar eax, 1 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + m->ebx*1 + 0x2u))) & 0xff) << 0);	/* 48db3f: mov al, byte ptr [eax + ebx + 2] */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48db43: sar eax, 4 */
L_48db46:
	{ DWORD a_ = m->eax, b_ = 0xfu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48db46: and eax, 0xf */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48db49: cmp eax, edi */
	M32((DWORD)(m->esp + 0x54u)) = m->eax;	/* 48db4b: mov dword ptr [esp + 0x54], eax */
	if (!m->zf) goto L_48db58;	/* 48db4f: jne 0x48db58 */
	M32((DWORD)(m->esi + 0xfffffffcu)) = m->edi;	/* 48db51: mov dword ptr [esi - 4], edi */
	M32((DWORD)(m->esi + 0x0u)) = m->edi;	/* 48db54: mov dword ptr [esi], edi */
	goto L_48db6b;	/* 48db56: jmp 0x48db6b */
L_48db58:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x54u)));	/* 48db58: fild dword ptr [esp + 0x54] */
	M32((DWORD)(m->esi + 0xfffffffcu)) = 0x1u;	/* 48db5c: mov dword ptr [esi - 4], 1 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 48db63: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esi + 0x0u)) = (float)ST(0); FPOP();	/* 48db69: fstp dword ptr [esi] */
L_48db6b:
	m->eax = M32((DWORD)(m->ebp + 0x22f0400u));	/* 48db6b: mov eax, dword ptr [ebp + 0x22f0400] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48db71: inc ecx */
	{ DWORD a_ = m->esi, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 48db72: add esi, 0x28 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48db75: cmp ecx, eax */
	if (m->sf != m->of) goto L_48db14;	/* 48db77: jl 0x48db14 */
L_48db79:
	m->edi = M32(m->esp); m->esp += 4;	/* 48db79: pop edi */
	M32((DWORD)(m->ebp + 0x2343253u)) = 0x1u;	/* 48db7a: mov dword ptr [ebp + 0x2343253], 1 */
	m->esi = M32(m->esp); m->esp += 4;	/* 48db84: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 48db85: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48db86: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48db87: add esp, 0x3c */
	m->esp += 4 + 12; return;	/* 48db8a: ret 0xc */
L_48db8d:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48db8d: push ebx */
	m->esp -= 4; M32(m->esp) = 0x48db93u; native_call(m, 0x48b420u);	/* 48db8e: call 0x48b420 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48db93: add esp, 4 */
L_48db96:
	m->edi = M32(m->esp); m->esp += 4;	/* 48db96: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48db97: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 48db98: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48db99: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48db9a: add esp, 0x3c */
	m->esp += 4 + 12; return;	/* 48db9d: ret 0xc */
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
