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

static void lift_475070(X86 *m);

/* particle_init (0x475070), lifted by tools/lift.py */
static void lift_475070(X86 *m)
{
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 475070: push ebp */
	m->ebp = m->esp;	/* 475071: mov ebp, esp */
	{ DWORD a_ = m->esp, b_ = 0xfffffff8u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esp = r_; }	/* 475073: and esp, 0xfffffff8 */
	{ DWORD a_ = m->esp, b_ = 0x104u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 475076: sub esp, 0x104 */
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 47507c: mov eax, dword ptr [ebp + 8] */
	m->edx = M32((DWORD)(m->ecx + 0x20f2da8u));	/* 47507f: mov edx, dword ptr [ecx + 0x20f2da8] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 475085: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 475086: push esi */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 475087: lea eax, [eax + eax*2] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 47508a: push edi */
	m->edi = M32((DWORD)(m->ebp + 0xcu));	/* 47508b: mov edi, dword ptr [ebp + 0xc] */
	M32((DWORD)(m->esp + 0x34u)) = m->ecx;	/* 47508e: mov dword ptr [esp + 0x34], ecx */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 475092: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 475095: lea eax, [eax + eax*4] */
	m->esi = (DWORD)(m->ecx + m->eax*4 + 0x20a99c0u);	/* 475098: lea esi, [ecx + eax*4 + 0x20a99c0] */
	m->eax = 0x1u;	/* 47509f: mov eax, 1 */
	M32((DWORD)(m->esi + 0x0u)) = m->edx;	/* 4750a4: mov dword ptr [esi], edx */
	m->edx = M32((DWORD)(m->ecx + 0x20f2da8u));	/* 4750a6: mov edx, dword ptr [ecx + 0x20f2da8] */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 4750ac: inc edx */
	M32((DWORD)(m->ecx + 0x20f2da8u)) = m->edx;	/* 4750ad: mov dword ptr [ecx + 0x20f2da8], edx */
	M32((DWORD)(m->esi + 0x4u)) = m->eax;	/* 4750b3: mov dword ptr [esi + 4], eax */
	{ DWORD a_ = M32((DWORD)(m->edi + 0x30u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4750b6: cmp dword ptr [edi + 0x30], eax */
	if (!m->zf) goto L_47517d;	/* 4750b9: jne 0x47517d */
	M32((DWORD)(m->esi + 0x8u)) = 0x32u;	/* 4750bf: mov dword ptr [esi + 8], 0x32 */
	m->eax = M32((DWORD)(m->edi + 0x34u));	/* 4750c6: mov eax, dword ptr [edi + 0x34] */
	M32((DWORD)(m->esi + 0xe4u)) = m->eax;	/* 4750c9: mov dword ptr [esi + 0xe4], eax */
	m->ecx = M32((DWORD)(m->edi + 0x38u));	/* 4750cf: mov ecx, dword ptr [edi + 0x38] */
	M32((DWORD)(m->esi + 0xe8u)) = m->ecx;	/* 4750d2: mov dword ptr [esi + 0xe8], ecx */
	m->edx = M32((DWORD)(m->edi + 0x3cu));	/* 4750d8: mov edx, dword ptr [edi + 0x3c] */
	M32((DWORD)(m->esi + 0xecu)) = m->edx;	/* 4750db: mov dword ptr [esi + 0xec], edx */
	m->eax = M32((DWORD)(m->edi + 0x40u));	/* 4750e1: mov eax, dword ptr [edi + 0x40] */
	M32((DWORD)(m->esi + 0xf0u)) = m->eax;	/* 4750e4: mov dword ptr [esi + 0xf0], eax */
	m->ecx = M32((DWORD)(m->edi + 0x44u));	/* 4750ea: mov ecx, dword ptr [edi + 0x44] */
	M32((DWORD)(m->esi + 0xf4u)) = m->ecx;	/* 4750ed: mov dword ptr [esi + 0xf4], ecx */
	m->edx = M32((DWORD)(m->edi + 0x48u));	/* 4750f3: mov edx, dword ptr [edi + 0x48] */
	m->eax = (DWORD)(m->edi + 0x4cu);	/* 4750f6: lea eax, [edi + 0x4c] */
	M32((DWORD)(m->esi + 0xf8u)) = m->edx;	/* 4750f9: mov dword ptr [esi + 0xf8], edx */
	m->ecx = (DWORD)(m->esi + 0xfcu);	/* 4750ff: lea ecx, [esi + 0xfc] */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 475105: mov edx, dword ptr [eax] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 475107: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 475109: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 47510c: mov dword ptr [ecx + 4], edx */
	m->edx = (DWORD)(m->esi + 0x108u);	/* 47510f: lea edx, [esi + 0x108] */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 475115: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 475118: mov dword ptr [ecx + 8], eax */
	m->ecx = (DWORD)(m->edi + 0x58u);	/* 47511b: lea ecx, [edi + 0x58] */
	m->eax = M32((DWORD)(m->edi + 0x58u));	/* 47511e: mov eax, dword ptr [edi + 0x58] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 475121: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->ecx + 0x4u));	/* 475123: mov eax, dword ptr [ecx + 4] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 475126: mov dword ptr [edx + 4], eax */
	m->eax = (DWORD)(m->esi + 0x114u);	/* 475129: lea eax, [esi + 0x114] */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 47512f: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 475132: mov dword ptr [edx + 8], ecx */
	m->edx = (DWORD)(m->edi + 0x64u);	/* 475135: lea edx, [edi + 0x64] */
	{ DWORD a_ = m->edi, b_ = 0x70u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 475138: add edi, 0x70 */
	m->ecx = M32((DWORD)(m->edx + 0x0u));	/* 47513b: mov ecx, dword ptr [edx] */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 47513d: mov dword ptr [eax], ecx */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 47513f: mov ecx, dword ptr [edx + 4] */
	M32((DWORD)(m->eax + 0x4u)) = m->ecx;	/* 475142: mov dword ptr [eax + 4], ecx */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 475145: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 475148: mov dword ptr [eax + 8], edx */
	m->ecx = M32((DWORD)(m->edi + 0x0u));	/* 47514b: mov ecx, dword ptr [edi] */
	m->eax = (DWORD)(m->esi + 0x120u);	/* 47514d: lea eax, [esi + 0x120] */
	M32((DWORD)(m->esi + 0x120u)) = m->ecx;	/* 475153: mov dword ptr [esi + 0x120], ecx */
	m->edx = M32((DWORD)(m->edi + 0x4u));	/* 475159: mov edx, dword ptr [edi + 4] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 47515c: mov dword ptr [eax + 4], edx */
	m->ecx = M32((DWORD)(m->edi + 0x8u));	/* 47515f: mov ecx, dword ptr [edi + 8] */
	M32((DWORD)(m->esi + 0x70u)) = 0x3c23d70au;	/* 475162: mov dword ptr [esi + 0x70], 0x3c23d70a */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 475169: mov dword ptr [eax + 8], ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47516c: xor eax, eax */
	M32((DWORD)(m->esi + 0x6cu)) = m->eax;	/* 47516e: mov dword ptr [esi + 0x6c], eax */
	M32((DWORD)(m->esi + 0x74u)) = m->eax;	/* 475171: mov dword ptr [esi + 0x74], eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 475174: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 475175: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 475176: pop ebx */
	m->esp = m->ebp;	/* 475177: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 475179: pop ebp */
	m->esp += 4 + 8; return;	/* 47517a: ret 8 */
L_47517d:
	m->edx = M32((DWORD)(m->edi + 0x0u));	/* 47517d: mov edx, dword ptr [edi] */
	m->ecx = (DWORD)(m->edi + 0x8u);	/* 47517f: lea ecx, [edi + 8] */
	M32((DWORD)(m->esi + 0x8u)) = m->edx;	/* 475182: mov dword ptr [esi + 8], edx */
	m->eax = M32((DWORD)(m->edi + 0x4u));	/* 475185: mov eax, dword ptr [edi + 4] */
	M32((DWORD)(m->esi + 0xcu)) = m->eax;	/* 475188: mov dword ptr [esi + 0xc], eax */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 47518b: mov edx, dword ptr [ecx] */
	m->eax = (DWORD)(m->esi + 0x10u);	/* 47518d: lea eax, [esi + 0x10] */
	m->ebx = (DWORD)(m->esi + 0x1cu);	/* 475190: lea ebx, [esi + 0x1c] */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 475193: mov dword ptr [esp + 0x10], eax */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 475197: mov dword ptr [eax], edx */
	m->edx = M32((DWORD)(m->ecx + 0x4u));	/* 475199: mov edx, dword ptr [ecx + 4] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 47519c: mov dword ptr [eax + 4], edx */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 47519f: mov ecx, dword ptr [ecx + 8] */
	m->edx = (DWORD)(m->edi + 0x14u);	/* 4751a2: lea edx, [edi + 0x14] */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 4751a5: mov dword ptr [eax + 8], ecx */
	m->eax = m->ebx;	/* 4751a8: mov eax, ebx */
	m->ecx = M32((DWORD)(m->edx + 0x0u));	/* 4751aa: mov ecx, dword ptr [edx] */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 4751ac: mov dword ptr [eax], ecx */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 4751ae: mov ecx, dword ptr [edx + 4] */
	M32((DWORD)(m->eax + 0x4u)) = m->ecx;	/* 4751b1: mov dword ptr [eax + 4], ecx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4751b4: xor ecx, ecx */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 4751b6: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 4751b9: mov dword ptr [eax + 8], edx */
	m->eax = M32((DWORD)(m->edi + 0x20u));	/* 4751bc: mov eax, dword ptr [edi + 0x20] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4751bf: cmp eax, ecx */
	M32((DWORD)(m->esi + 0x28u)) = m->eax;	/* 4751c1: mov dword ptr [esi + 0x28], eax */
	if (m->zf) goto L_4751d5;	/* 4751c4: je 0x4751d5 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4751c6: push eax */
	m->eax = (DWORD)(m->esi + 0x2cu);	/* 4751c7: lea eax, [esi + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4751ca: push eax */
	m->esp -= 4; M32(m->esp) = 0x4751d0u; native_call(m, 0x47d5a0u);	/* 4751cb: call 0x47d5a0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4751d0: add esp, 8 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4751d3: xor ecx, ecx */
L_4751d5:
	M32((DWORD)(m->esi + 0x6cu)) = m->ecx;	/* 4751d5: mov dword ptr [esi + 0x6c], ecx */
	M32((DWORD)(m->esi + 0x70u)) = 0x3f800000u;	/* 4751d8: mov dword ptr [esi + 0x70], 0x3f800000 */
	M32((DWORD)(m->esi + 0x74u)) = m->ecx;	/* 4751df: mov dword ptr [esi + 0x74], ecx */
	m->edx = M32((DWORD)(0xa1f23cu));	/* 4751e2: mov edx, dword ptr [0xa1f23c] */
	M32((DWORD)(m->esi + 0x78u)) = m->edx;	/* 4751e8: mov dword ptr [esi + 0x78], edx */
	M32((DWORD)(m->esi + 0x7cu)) = m->ecx;	/* 4751eb: mov dword ptr [esi + 0x7c], ecx */
	m->eax = M32((DWORD)(m->edi + 0x2cu));	/* 4751ee: mov eax, dword ptr [edi + 0x2c] */
	m->ecx = M32((DWORD)(m->esi + 0x8u));	/* 4751f1: mov ecx, dword ptr [esi + 8] */
	M32((DWORD)(m->esi + 0x80u)) = m->eax;	/* 4751f4: mov dword ptr [esi + 0x80], eax */
	m->eax = 0x66666667u;	/* 4751fa: mov eax, 0x66666667 */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 4751ff: imul ecx */
	{ DWORD a_ = m->edx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 475201: sar edx, 1 */
	m->eax = m->edx;	/* 475203: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 475205: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 475208: add edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x9u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47520a: cmp edx, 9 */
	if (!m->cf && !m->zf) goto L_476332;	/* 47520d: ja 0x476332 */
	switch (m->edx) { case 0: goto L_47521a; case 1: goto L_4752ac; case 2: goto L_4752e9; case 3: goto L_475440; case 4: goto L_4755af; case 5: goto L_4758ac; case 6: goto L_475d81; case 7: goto L_475d94; case 8: goto L_475db7; case 9: goto L_475ec9; default: abort(); }	/* 475213: jmp dword ptr [edx*4 + 0x47633c] */
L_47521a:
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47521a: cmp ecx, 4 */
	if (!m->cf && !m->zf) goto L_476332;	/* 47521d: ja 0x476332 */
	switch (m->ecx) { case 0: goto L_47522a; case 1: goto L_47522a; case 2: goto L_47523a; case 3: goto L_475268; case 4: goto L_475296; default: abort(); }	/* 475223: jmp dword ptr [ecx*4 + 0x476364] */
L_47522a:
	M32((DWORD)(m->esi + 0x70u)) = 0x3f000000u;	/* 47522a: mov dword ptr [esi + 0x70], 0x3f000000 */
	m->edi = M32(m->esp); m->esp += 4;	/* 475231: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 475232: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 475233: pop ebx */
	m->esp = m->ebp;	/* 475234: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 475236: pop ebp */
	m->esp += 4 + 8; return;	/* 475237: ret 8 */
L_47523a:
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 47523a: mov eax, dword ptr [esp + 0x34] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 47523e: mov edx, dword ptr [esp + 0x10] */
	{ DWORD v_ = 0x47435000u; m->esp -= 4; M32(m->esp) = v_; }	/* 475242: push 0x47435000 */
	m->ecx = (DWORD)(m->eax + 0x20f397cu);	/* 475247: lea ecx, [eax + 0x20f397c] */
	{ DWORD a_ = m->eax, b_ = 0x20f3970u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 47524d: add eax, 0x20f3970 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 475252: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 475253: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 475254: push eax */
	{ DWORD v_ = 0x2au; m->esp -= 4; M32(m->esp) = v_; }	/* 475255: push 0x2a */
	m->esp -= 4; M32(m->esp) = 0x47525cu; native_call(m, 0x456ed0u);	/* 475257: call 0x456ed0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47525c: add esp, 0x14 */
	m->edi = M32(m->esp); m->esp += 4;	/* 47525f: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 475260: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 475261: pop ebx */
	m->esp = m->ebp;	/* 475262: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 475264: pop ebp */
	m->esp += 4 + 8; return;	/* 475265: ret 8 */
L_475268:
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 475268: mov eax, dword ptr [esp + 0x34] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 47526c: mov edx, dword ptr [esp + 0x10] */
	{ DWORD v_ = 0x47c35000u; m->esp -= 4; M32(m->esp) = v_; }	/* 475270: push 0x47c35000 */
	m->ecx = (DWORD)(m->eax + 0x20f397cu);	/* 475275: lea ecx, [eax + 0x20f397c] */
	{ DWORD a_ = m->eax, b_ = 0x20f3970u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 47527b: add eax, 0x20f3970 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 475280: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 475281: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 475282: push eax */
	{ DWORD v_ = 0x28u; m->esp -= 4; M32(m->esp) = v_; }	/* 475283: push 0x28 */
	m->esp -= 4; M32(m->esp) = 0x47528au; native_call(m, 0x456ed0u);	/* 475285: call 0x456ed0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47528a: add esp, 0x14 */
	m->edi = M32(m->esp); m->esp += 4;	/* 47528d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 47528e: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 47528f: pop ebx */
	m->esp = m->ebp;	/* 475290: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 475292: pop ebp */
	m->esp += 4 + 8; return;	/* 475293: ret 8 */
L_475296:
	m->eax = M32((DWORD)(m->esi + 0x20u));	/* 475296: mov eax, dword ptr [esi + 0x20] */
	M32((DWORD)(m->esi + 0x70u)) = 0x0u;	/* 475299: mov dword ptr [esi + 0x70], 0 */
	M32((DWORD)(m->esi + 0x78u)) = m->eax;	/* 4752a0: mov dword ptr [esi + 0x78], eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 4752a3: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4752a4: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4752a5: pop ebx */
	m->esp = m->ebp;	/* 4752a6: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4752a8: pop ebp */
	m->esp += 4 + 8; return;	/* 4752a9: ret 8 */
L_4752ac:
	m->eax = (DWORD)(m->ecx + 0xfffffffbu);	/* 4752ac: lea eax, [ecx - 5] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4752af: cmp eax, 4 */
	if (!m->cf && !m->zf) goto L_476332;	/* 4752b2: ja 0x476332 */
	switch (m->eax) { case 0: goto L_4752bf; case 1: goto L_4752bf; case 2: goto L_4752bf; case 3: goto L_47522a; case 4: goto L_4752cf; default: abort(); }	/* 4752b8: jmp dword ptr [eax*4 + 0x476378] */
L_4752bf:
	M32((DWORD)(m->esi + 0x70u)) = 0x0u;	/* 4752bf: mov dword ptr [esi + 0x70], 0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4752c6: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4752c7: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4752c8: pop ebx */
	m->esp = m->ebp;	/* 4752c9: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4752cb: pop ebp */
	m->esp += 4 + 8; return;	/* 4752cc: ret 8 */
L_4752cf:
	M32((DWORD)(m->esi + 0x70u)) = 0x40000000u;	/* 4752cf: mov dword ptr [esi + 0x70], 0x40000000 */
	M32((DWORD)(m->esi + 0x84u)) = 0x3dcccccdu;	/* 4752d6: mov dword ptr [esi + 0x84], 0x3dcccccd */
	m->edi = M32(m->esp); m->esp += 4;	/* 4752e0: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4752e1: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4752e2: pop ebx */
	m->esp = m->ebp;	/* 4752e3: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4752e5: pop ebp */
	m->esp += 4 + 8; return;	/* 4752e6: ret 8 */
L_4752e9:
	m->eax = (DWORD)(m->ecx + 0xfffffff6u);	/* 4752e9: lea eax, [ecx - 0xa] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4752ec: cmp eax, 4 */
	if (!m->cf && !m->zf) goto L_476332;	/* 4752ef: ja 0x476332 */
	switch (m->eax) { case 0: goto L_4752fc; case 1: goto L_4753e8; case 2: goto L_4754d5; case 3: goto L_4754d5; case 4: goto L_475453; default: abort(); }	/* 4752f5: jmp dword ptr [eax*4 + 0x47638c] */
L_4752fc:
	M32((DWORD)(m->esi + 0x70u)) = 0x3c23d70au;	/* 4752fc: mov dword ptr [esi + 0x70], 0x3c23d70a */
	m->esp -= 4; M32(m->esp) = 0x475309u; native_call(m, M32(0x4a9204u));	/* 475303: call dword ptr [0x4a9204] */
	m->esp -= 4; M32(m->esp) = 0x47530fu; native_call(m, M32(0x4a9218u));	/* 475309: call dword ptr [0x4a9218] */
	m->ecx = M32((DWORD)(m->esi + 0x28u));	/* 47530f: mov ecx, dword ptr [esi + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 475312: push ecx */
	m->esp -= 4; M32(m->esp) = 0x475319u; native_call(m, M32(0x4a926cu));	/* 475313: call dword ptr [0x4a926c] */
	m->ecx = M32((DWORD)(0xa1efb8u));	/* 475319: mov ecx, dword ptr [0xa1efb8] */
	m->edi = 0x168u;	/* 47531f: mov edi, 0x168 */
	m->edx = m->ecx;	/* 475324: mov edx, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 475326: push 0x3f800000 */
	{ DWORD a_ = m->edx, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 47532b: and edx, 0xfff */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 475331: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 475333: push 0 */
	m->eax = M32((DWORD)(m->edx*4 + 0xa106f8u));	/* 475335: mov eax, dword ptr [edx*4 + 0xa106f8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 47533c: xor edx, edx */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->edi; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 47533e: div edi */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 475340: inc ecx */
	M32((DWORD)(0xa1efb8u)) = m->ecx;	/* 475341: mov dword ptr [0xa1efb8], ecx */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 475347: mov dword ptr [esp + 0x20], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 47534b: fild dword ptr [esp + 0x20] */
L_47534f:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47534f: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 475350: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x475359u; native_call(m, M32(0x4a91f8u));	/* 475353: call dword ptr [0x4a91f8] */
	{ DWORD a_ = m->esi, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 475359: add esi, 0x2c */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 47535c: push esi */
	{ DWORD v_ = 0xba6u; m->esp -= 4; M32(m->esp) = v_; }	/* 47535d: push 0xba6 */
	m->esp -= 4; M32(m->esp) = 0x475368u; native_call(m, M32(0x4a9270u));	/* 475362: call dword ptr [0x4a9270] */
	m->esp -= 4; M32(m->esp) = 0x47536eu; native_call(m, M32(0x4a9258u));	/* 475368: call dword ptr [0x4a9258] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7b0u)));	/* 47536e: fld dword ptr [0xa0e7b0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x20u));	/* 475374: fmul dword ptr [esi + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7acu)));	/* 475377: fld dword ptr [0xa0e7ac] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x10u));	/* 47537d: fmul dword ptr [esi + 0x10] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 475380: mov eax, dword ptr [esp + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 475384: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7a8u)));	/* 475386: fld dword ptr [0xa0e7a8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 47538c: fmul dword ptr [esi] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47538e: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x30u));	/* 475390: fadd dword ptr [esi + 0x30] */
	MF((DWORD)(m->eax + 0x0u)) = (float)ST(0); FPOP();	/* 475393: fstp dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7b0u)));	/* 475395: fld dword ptr [0xa0e7b0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x24u));	/* 47539b: fmul dword ptr [esi + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7acu)));	/* 47539e: fld dword ptr [0xa0e7ac] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x14u));	/* 4753a4: fmul dword ptr [esi + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4753a7: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7a8u)));	/* 4753a9: fld dword ptr [0xa0e7a8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 4753af: fmul dword ptr [esi + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4753b2: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x34u));	/* 4753b4: fadd dword ptr [esi + 0x34] */
	MF((DWORD)(m->eax + 0x4u)) = (float)ST(0); FPOP();	/* 4753b7: fstp dword ptr [eax + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7b0u)));	/* 4753ba: fld dword ptr [0xa0e7b0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x28u));	/* 4753c0: fmul dword ptr [esi + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7acu)));	/* 4753c3: fld dword ptr [0xa0e7ac] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x18u));	/* 4753c9: fmul dword ptr [esi + 0x18] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4753cc: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7a8u)));	/* 4753ce: fld dword ptr [0xa0e7a8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 4753d4: fmul dword ptr [esi + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4753d7: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x38u));	/* 4753d9: fadd dword ptr [esi + 0x38] */
	MF((DWORD)(m->eax + 0x8u)) = (float)ST(0); FPOP();	/* 4753dc: fstp dword ptr [eax + 8] */
	m->edi = M32(m->esp); m->esp += 4;	/* 4753df: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4753e0: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4753e1: pop ebx */
	m->esp = m->ebp;	/* 4753e2: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4753e4: pop ebp */
	m->esp += 4 + 8; return;	/* 4753e5: ret 8 */
L_4753e8:
	M32((DWORD)(m->esi + 0x70u)) = 0x3c23d70au;	/* 4753e8: mov dword ptr [esi + 0x70], 0x3c23d70a */
	m->esp -= 4; M32(m->esp) = 0x4753f5u; native_call(m, M32(0x4a9204u));	/* 4753ef: call dword ptr [0x4a9204] */
	m->esp -= 4; M32(m->esp) = 0x4753fbu; native_call(m, M32(0x4a9218u));	/* 4753f5: call dword ptr [0x4a9218] */
	m->eax = M32((DWORD)(m->esi + 0x28u));	/* 4753fb: mov eax, dword ptr [esi + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4753fe: push eax */
	m->esp -= 4; M32(m->esp) = 0x475405u; native_call(m, M32(0x4a926cu));	/* 4753ff: call dword ptr [0x4a926c] */
	m->ecx = M32((DWORD)(0xa1efb8u));	/* 475405: mov ecx, dword ptr [0xa1efb8] */
	m->edi = 0x168u;	/* 47540b: mov edi, 0x168 */
	m->edx = m->ecx;	/* 475410: mov edx, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 475412: push 0x3f800000 */
	{ DWORD a_ = m->edx, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 475417: and edx, 0xfff */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47541d: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47541f: push 0 */
	m->eax = M32((DWORD)(m->edx*4 + 0xa106f8u));	/* 475421: mov eax, dword ptr [edx*4 + 0xa106f8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 475428: xor edx, edx */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->edi; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 47542a: div edi */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 47542c: inc ecx */
	M32((DWORD)(0xa1efb8u)) = m->ecx;	/* 47542d: mov dword ptr [0xa1efb8], ecx */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 475433: mov dword ptr [esp + 0x20], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 475437: fild dword ptr [esp + 0x20] */
	goto L_47534f;	/* 47543b: jmp 0x47534f */
L_475440:
	m->eax = (DWORD)(m->ecx + 0xfffffff1u);	/* 475440: lea eax, [ecx - 0xf] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 475443: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_476332;	/* 475446: ja 0x476332 */
	switch (m->eax) { case 0: goto L_475453; case 1: goto L_475453; case 2: goto L_4754d5; case 3: goto L_475557; default: abort(); }	/* 47544c: jmp dword ptr [eax*4 + 0x4763a0] */
L_475453:
	M32((DWORD)(m->esi + 0x70u)) = 0x3f000000u;	/* 475453: mov dword ptr [esi + 0x70], 0x3f000000 */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 47545a: mov eax, dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7b0u)));	/* 47545e: fld dword ptr [0xa0e7b0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4cu));	/* 475464: fmul dword ptr [esi + 0x4c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7acu)));	/* 475467: fld dword ptr [0xa0e7ac] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x3cu));	/* 47546d: fmul dword ptr [esi + 0x3c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 475470: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7a8u)));	/* 475472: fld dword ptr [0xa0e7a8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x2cu));	/* 475478: fmul dword ptr [esi + 0x2c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47547b: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x5cu));	/* 47547d: fadd dword ptr [esi + 0x5c] */
	MF((DWORD)(m->eax + 0x0u)) = (float)ST(0); FPOP();	/* 475480: fstp dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7b0u)));	/* 475482: fld dword ptr [0xa0e7b0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x50u));	/* 475488: fmul dword ptr [esi + 0x50] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7acu)));	/* 47548b: fld dword ptr [0xa0e7ac] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x40u));	/* 475491: fmul dword ptr [esi + 0x40] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 475494: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7a8u)));	/* 475496: fld dword ptr [0xa0e7a8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x30u));	/* 47549c: fmul dword ptr [esi + 0x30] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47549f: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x60u));	/* 4754a1: fadd dword ptr [esi + 0x60] */
	MF((DWORD)(m->eax + 0x4u)) = (float)ST(0); FPOP();	/* 4754a4: fstp dword ptr [eax + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7b0u)));	/* 4754a7: fld dword ptr [0xa0e7b0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x54u));	/* 4754ad: fmul dword ptr [esi + 0x54] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7acu)));	/* 4754b0: fld dword ptr [0xa0e7ac] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x44u));	/* 4754b6: fmul dword ptr [esi + 0x44] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4754b9: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7a8u)));	/* 4754bb: fld dword ptr [0xa0e7a8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x34u));	/* 4754c1: fmul dword ptr [esi + 0x34] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4754c4: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x64u));	/* 4754c6: fadd dword ptr [esi + 0x64] */
	MF((DWORD)(m->eax + 0x8u)) = (float)ST(0); FPOP();	/* 4754c9: fstp dword ptr [eax + 8] */
	m->edi = M32(m->esp); m->esp += 4;	/* 4754cc: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4754cd: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4754ce: pop ebx */
	m->esp = m->ebp;	/* 4754cf: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4754d1: pop ebp */
	m->esp += 4 + 8; return;	/* 4754d2: ret 8 */
L_4754d5:
	M32((DWORD)(m->esi + 0x70u)) = 0x3c23d70au;	/* 4754d5: mov dword ptr [esi + 0x70], 0x3c23d70a */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 4754dc: mov eax, dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7b0u)));	/* 4754e0: fld dword ptr [0xa0e7b0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4cu));	/* 4754e6: fmul dword ptr [esi + 0x4c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7acu)));	/* 4754e9: fld dword ptr [0xa0e7ac] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x3cu));	/* 4754ef: fmul dword ptr [esi + 0x3c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4754f2: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7a8u)));	/* 4754f4: fld dword ptr [0xa0e7a8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x2cu));	/* 4754fa: fmul dword ptr [esi + 0x2c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4754fd: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x5cu));	/* 4754ff: fadd dword ptr [esi + 0x5c] */
	MF((DWORD)(m->eax + 0x0u)) = (float)ST(0); FPOP();	/* 475502: fstp dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7b0u)));	/* 475504: fld dword ptr [0xa0e7b0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x50u));	/* 47550a: fmul dword ptr [esi + 0x50] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7acu)));	/* 47550d: fld dword ptr [0xa0e7ac] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x40u));	/* 475513: fmul dword ptr [esi + 0x40] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 475516: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7a8u)));	/* 475518: fld dword ptr [0xa0e7a8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x30u));	/* 47551e: fmul dword ptr [esi + 0x30] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 475521: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x60u));	/* 475523: fadd dword ptr [esi + 0x60] */
	MF((DWORD)(m->eax + 0x4u)) = (float)ST(0); FPOP();	/* 475526: fstp dword ptr [eax + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7b0u)));	/* 475529: fld dword ptr [0xa0e7b0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x54u));	/* 47552f: fmul dword ptr [esi + 0x54] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7acu)));	/* 475532: fld dword ptr [0xa0e7ac] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x44u));	/* 475538: fmul dword ptr [esi + 0x44] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47553b: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7a8u)));	/* 47553d: fld dword ptr [0xa0e7a8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x34u));	/* 475543: fmul dword ptr [esi + 0x34] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 475546: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x64u));	/* 475548: fadd dword ptr [esi + 0x64] */
	MF((DWORD)(m->eax + 0x8u)) = (float)ST(0); FPOP();	/* 47554b: fstp dword ptr [eax + 8] */
	m->edi = M32(m->esp); m->esp += 4;	/* 47554e: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 47554f: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 475550: pop ebx */
	m->esp = m->ebp;	/* 475551: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 475553: pop ebp */
	m->esp += 4 + 8; return;	/* 475554: ret 8 */
L_475557:
	M32((DWORD)(m->esi + 0x70u)) = 0x3c23d70au;	/* 475557: mov dword ptr [esi + 0x70], 0x3c23d70a */
	m->esp -= 4; M32(m->esp) = 0x475564u; native_call(m, M32(0x4a9204u));	/* 47555e: call dword ptr [0x4a9204] */
	m->esp -= 4; M32(m->esp) = 0x47556au; native_call(m, M32(0x4a9218u));	/* 475564: call dword ptr [0x4a9218] */
	m->eax = M32((DWORD)(m->esi + 0x28u));	/* 47556a: mov eax, dword ptr [esi + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47556d: push eax */
	m->esp -= 4; M32(m->esp) = 0x475574u; native_call(m, M32(0x4a926cu));	/* 47556e: call dword ptr [0x4a926c] */
	m->ecx = M32((DWORD)(0xa1efb8u));	/* 475574: mov ecx, dword ptr [0xa1efb8] */
	m->edi = 0x168u;	/* 47557a: mov edi, 0x168 */
	m->edx = m->ecx;	/* 47557f: mov edx, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 475581: push 0x3f800000 */
	{ DWORD a_ = m->edx, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 475586: and edx, 0xfff */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47558c: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47558e: push 0 */
	m->eax = M32((DWORD)(m->edx*4 + 0xa106f8u));	/* 475590: mov eax, dword ptr [edx*4 + 0xa106f8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 475597: xor edx, edx */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->edi; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 475599: div edi */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 47559b: inc ecx */
	M32((DWORD)(0xa1efb8u)) = m->ecx;	/* 47559c: mov dword ptr [0xa1efb8], ecx */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 4755a2: mov dword ptr [esp + 0x20], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 4755a6: fild dword ptr [esp + 0x20] */
	goto L_47534f;	/* 4755aa: jmp 0x47534f */
L_4755af:
	m->eax = (DWORD)(m->ecx + 0xffffffecu);	/* 4755af: lea eax, [ecx - 0x14] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4755b2: cmp eax, 4 */
	if (!m->cf && !m->zf) goto L_476332;	/* 4755b5: ja 0x476332 */
	switch (m->eax) { case 0: goto L_4755c2; case 1: goto L_4756bc; case 2: goto L_4757a0; case 3: goto L_476332; case 4: goto L_4757b0; default: abort(); }	/* 4755bb: jmp dword ptr [eax*4 + 0x4763b0] */
L_4755c2:
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 4755c2: mov edi, dword ptr [esp + 0x10] */
	M32((DWORD)(m->esi + 0x70u)) = 0x3c23d70au;	/* 4755c6: mov dword ptr [esi + 0x70], 0x3c23d70a */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 4755cd: fld dword ptr [ebx] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 4755cf: fsub dword ptr [edi] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4755d1: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x4u)));	/* 4755d5: fld dword ptr [ebx + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 4755d8: fsub dword ptr [edi + 4] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4755db: mov eax, dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 4755df: mov dword ptr [esp + 0x24], eax */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 4755e3: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x8u)));	/* 4755e7: fld dword ptr [ebx + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 4755ea: fsub dword ptr [edi + 8] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 4755ed: mov ecx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 4755f1: mov dword ptr [esp + 0x28], ecx */
	m->ecx = (DWORD)(m->esp + 0x24u);	/* 4755f5: lea ecx, [esp + 0x24] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 4755f9: fstp dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 4755fd: mov edx, dword ptr [esp + 0x20] */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 475601: mov dword ptr [esp + 0x2c], edx */
	m->esp -= 4; M32(m->esp) = 0x47560au; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 475605: call 0x467760 */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 47560a: fstp dword ptr [esp + 0x10] */
	m->esp -= 4; M32(m->esp) = 0x475614u; native_call(m, M32(0x4a9204u));	/* 47560e: call dword ptr [0x4a9204] */
	m->esp -= 4; M32(m->esp) = 0x47561au; native_call(m, M32(0x4a9218u));	/* 475614: call dword ptr [0x4a9218] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 47561a: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9504u));	/* 47561e: fmul dword ptr [0x4a9504] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 475624: push ecx */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 475625: fdivr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47562b: fstp dword ptr [esp] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 47562e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 475633: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x47563eu; native_call(m, M32(0x4a9200u));	/* 475638: call dword ptr [0x4a9200] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x24u)));	/* 47563e: fld dword ptr [esi + 0x24] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 475641: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 475643: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 475645: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47564a: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47564c: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47564e: push 0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 475650: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 475653: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20u)));	/* 475656: fld dword ptr [esi + 0x20] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 475659: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47565c: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 47565f: fld dword ptr [ebx] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 475661: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 475664: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x18u)));	/* 475667: fld dword ptr [esi + 0x18] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47566a: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47566d: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x14u)));	/* 475670: fld dword ptr [esi + 0x14] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 475673: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 475676: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x0u)));	/* 475679: fld dword ptr [edi] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47567b: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47567e: fstp qword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x475686u; native_call(m, 0x4509d2u);	/* 475681: call 0x4509d2 */
	m->eax = (DWORD)(m->esp + 0xd0u);	/* 475686: lea eax, [esp + 0xd0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47568d: push eax */
	{ DWORD v_ = 0xba6u; m->esp -= 4; M32(m->esp) = v_; }	/* 47568e: push 0xba6 */
	m->esp -= 4; M32(m->esp) = 0x475699u; native_call(m, M32(0x4a9270u));	/* 475693: call dword ptr [0x4a9270] */
	m->ecx = (DWORD)(m->esp + 0xd0u);	/* 475699: lea ecx, [esp + 0xd0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4756a0: push ecx */
L_4756a1:
	{ DWORD a_ = m->esi, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4756a1: add esi, 0x2c */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4756a4: push esi */
	m->esp -= 4; M32(m->esp) = 0x4756aau; native_call(m, 0x47d740u);	/* 4756a5: call 0x47d740 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4756aa: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x4756b3u; native_call(m, M32(0x4a9258u));	/* 4756ad: call dword ptr [0x4a9258] */
	m->edi = M32(m->esp); m->esp += 4;	/* 4756b3: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4756b4: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4756b5: pop ebx */
	m->esp = m->ebp;	/* 4756b6: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4756b8: pop ebp */
	m->esp += 4 + 8; return;	/* 4756b9: ret 8 */
L_4756bc:
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 4756bc: mov edi, dword ptr [esp + 0x10] */
	M32((DWORD)(m->esi + 0x70u)) = 0x3c23d70au;	/* 4756c0: mov dword ptr [esi + 0x70], 0x3c23d70a */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 4756c7: fld dword ptr [ebx] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 4756c9: fsub dword ptr [edi] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4756cb: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x4u)));	/* 4756cf: fld dword ptr [ebx + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 4756d2: fsub dword ptr [edi + 4] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 4756d5: mov edx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 4756d9: mov dword ptr [esp + 0x24], edx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 4756dd: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x8u)));	/* 4756e1: fld dword ptr [ebx + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 4756e4: fsub dword ptr [edi + 8] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 4756e7: mov eax, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 4756eb: mov dword ptr [esp + 0x28], eax */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 4756ef: fstp dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 4756f3: mov ecx, dword ptr [esp + 0x20] */
	M32((DWORD)(m->esp + 0x2cu)) = m->ecx;	/* 4756f7: mov dword ptr [esp + 0x2c], ecx */
	m->ecx = (DWORD)(m->esp + 0x24u);	/* 4756fb: lea ecx, [esp + 0x24] */
	m->esp -= 4; M32(m->esp) = 0x475704u; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 4756ff: call 0x467760 */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 475704: fstp dword ptr [esp + 0x10] */
	m->esp -= 4; M32(m->esp) = 0x47570eu; native_call(m, M32(0x4a9204u));	/* 475708: call dword ptr [0x4a9204] */
	m->esp -= 4; M32(m->esp) = 0x475714u; native_call(m, M32(0x4a9218u));	/* 47570e: call dword ptr [0x4a9218] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 475714: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9504u));	/* 475718: fmul dword ptr [0x4a9504] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47571e: push ecx */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 47571f: fdivr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 475725: fstp dword ptr [esp] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 475728: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 47572d: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x475738u; native_call(m, M32(0x4a9200u));	/* 475732: call dword ptr [0x4a9200] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x24u)));	/* 475738: fld dword ptr [esi + 0x24] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47573b: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47573d: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 47573f: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 475744: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 475746: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 475748: push 0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47574a: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47574d: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20u)));	/* 475750: fld dword ptr [esi + 0x20] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 475753: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 475756: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 475759: fld dword ptr [ebx] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47575b: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47575e: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x18u)));	/* 475761: fld dword ptr [esi + 0x18] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 475764: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 475767: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x14u)));	/* 47576a: fld dword ptr [esi + 0x14] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47576d: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 475770: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x0u)));	/* 475773: fld dword ptr [edi] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 475775: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 475778: fstp qword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x475780u; native_call(m, 0x4509d2u);	/* 47577b: call 0x4509d2 */
	m->edx = (DWORD)(m->esp + 0xd0u);	/* 475780: lea edx, [esp + 0xd0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 475787: push edx */
	{ DWORD v_ = 0xba6u; m->esp -= 4; M32(m->esp) = v_; }	/* 475788: push 0xba6 */
	m->esp -= 4; M32(m->esp) = 0x475793u; native_call(m, M32(0x4a9270u));	/* 47578d: call dword ptr [0x4a9270] */
	m->eax = (DWORD)(m->esp + 0xd0u);	/* 475793: lea eax, [esp + 0xd0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47579a: push eax */
	goto L_4756a1;	/* 47579b: jmp 0x4756a1 */
L_4757a0:
	M32((DWORD)(m->esi + 0x70u)) = 0x3c23d70au;	/* 4757a0: mov dword ptr [esi + 0x70], 0x3c23d70a */
	m->edi = M32(m->esp); m->esp += 4;	/* 4757a7: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4757a8: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4757a9: pop ebx */
	m->esp = m->ebp;	/* 4757aa: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4757ac: pop ebp */
	m->esp += 4 + 8; return;	/* 4757ad: ret 8 */
L_4757b0:
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 4757b0: mov edi, dword ptr [esp + 0x10] */
	M32((DWORD)(m->esi + 0x70u)) = 0x3f000000u;	/* 4757b4: mov dword ptr [esi + 0x70], 0x3f000000 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 4757bb: fld dword ptr [ebx] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 4757bd: fsub dword ptr [edi] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4757bf: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x4u)));	/* 4757c3: fld dword ptr [ebx + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 4757c6: fsub dword ptr [edi + 4] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 4757c9: mov ecx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x24u)) = m->ecx;	/* 4757cd: mov dword ptr [esp + 0x24], ecx */
	m->ecx = (DWORD)(m->esp + 0x24u);	/* 4757d1: lea ecx, [esp + 0x24] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 4757d5: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x8u)));	/* 4757d9: fld dword ptr [ebx + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 4757dc: fsub dword ptr [edi + 8] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 4757df: mov edx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 4757e3: mov dword ptr [esp + 0x28], edx */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 4757e7: fstp dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 4757eb: mov eax, dword ptr [esp + 0x20] */
	M32((DWORD)(m->esp + 0x2cu)) = m->eax;	/* 4757ef: mov dword ptr [esp + 0x2c], eax */
	m->esp -= 4; M32(m->esp) = 0x4757f8u; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 4757f3: call 0x467760 */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 4757f8: fstp dword ptr [esp + 0x10] */
	m->esp -= 4; M32(m->esp) = 0x475802u; native_call(m, M32(0x4a9204u));	/* 4757fc: call dword ptr [0x4a9204] */
	m->esp -= 4; M32(m->esp) = 0x475808u; native_call(m, M32(0x4a9218u));	/* 475802: call dword ptr [0x4a9218] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 475808: fld dword ptr [esi + 0x80] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9504u));	/* 47580e: fmul dword ptr [0x4a9504] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 475814: push ecx */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 475815: fadd dword ptr [0x4a9424] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 47581b: fdivr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 475821: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 475825: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9504u));	/* 475829: fmul dword ptr [0x4a9504] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 47582f: mov eax, dword ptr [esp + 0x18] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 475833: fdivr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 475839: fstp dword ptr [esp] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47583c: push eax */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47583d: push eax */
	m->esp -= 4; M32(m->esp) = 0x475844u; native_call(m, M32(0x4a9200u));	/* 47583e: call dword ptr [0x4a9200] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x24u)));	/* 475844: fld dword ptr [esi + 0x24] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 475847: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 475849: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 47584b: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 475850: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 475852: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 475854: push 0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 475856: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 475859: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20u)));	/* 47585c: fld dword ptr [esi + 0x20] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47585f: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 475862: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 475865: fld dword ptr [ebx] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 475867: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47586a: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x18u)));	/* 47586d: fld dword ptr [esi + 0x18] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 475870: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 475873: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x14u)));	/* 475876: fld dword ptr [esi + 0x14] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 475879: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 47587c: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x0u)));	/* 47587f: fld dword ptr [edi] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 475881: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 475884: fstp qword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47588cu; native_call(m, 0x4509d2u);	/* 475887: call 0x4509d2 */
	m->ecx = (DWORD)(m->esp + 0xd0u);	/* 47588c: lea ecx, [esp + 0xd0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 475893: push ecx */
	{ DWORD v_ = 0xba6u; m->esp -= 4; M32(m->esp) = v_; }	/* 475894: push 0xba6 */
	m->esp -= 4; M32(m->esp) = 0x47589fu; native_call(m, M32(0x4a9270u));	/* 475899: call dword ptr [0x4a9270] */
	m->edx = (DWORD)(m->esp + 0xd0u);	/* 47589f: lea edx, [esp + 0xd0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4758a6: push edx */
	goto L_4756a1;	/* 4758a7: jmp 0x4756a1 */
L_4758ac:
	{ DWORD a_ = m->ecx, b_ = 0x19u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4758ac: sub ecx, 0x19 */
	if (m->zf) goto L_475b58;	/* 4758af: je 0x475b58 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4758b5: dec ecx */
	if (!m->zf) goto L_476332;	/* 4758b6: jne 0x476332 */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((0xc4u) & 0xff) << 0);	/* 4758bc: mov cl, 0xc4 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((0xffu) & 0xff) << 0);	/* 4758be: mov al, 0xff */
	M32((DWORD)(m->esi + 0x70u)) = 0x0u;	/* 4758c0: mov dword ptr [esi + 0x70], 0 */
	M8((DWORD)(m->esi + 0x78u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 4758c7: mov byte ptr [esi + 0x78], cl */
	M8((DWORD)(m->esi + 0x79u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 4758ca: mov byte ptr [esi + 0x79], cl */
	M8((DWORD)(m->esi + 0x7au)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 4758cd: mov byte ptr [esi + 0x7a], al */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 4758d0: mov byte ptr [esi + 0x7b], al */
	m->esp -= 4; M32(m->esp) = 0x4758d9u; native_call(m, M32(0x4a9204u));	/* 4758d3: call dword ptr [0x4a9204] */
	m->esp -= 4; M32(m->esp) = 0x4758dfu; native_call(m, M32(0x4a9218u));	/* 4758d9: call dword ptr [0x4a9218] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x24u)));	/* 4758df: fld dword ptr [esi + 0x24] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 4758e2: xor edi, edi */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 4758e4: mov eax, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4758e8: push edi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4758e9: push edi */
	ST(0) = ST(0) + ST(0);	/* 4758ea: fadd st(0), st(0) */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4758ec: push 0x3ff00000 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4758f1: push edi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4758f2: push edi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4758f3: push edi */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x18u));	/* 4758f4: fsub dword ptr [esi + 0x18] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4758f7: sub esp, 8 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4758fa: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x8u)) = (double)ST(0); FPOP();	/* 4758fd: fstp qword ptr [esp + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20u)));	/* 475901: fld dword ptr [esi + 0x20] */
	ST(0) = ST(0) + ST(0);	/* 475904: fadd st(0), st(0) */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 475906: sub esp, 8 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 475909: sub esp, 8 */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x14u));	/* 47590c: fsub dword ptr [esi + 0x14] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47590f: sub esp, 8 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 475912: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x20u)) = (double)ST(0); FPOP();	/* 475915: fstp qword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 475919: fld dword ptr [ebx] */
	ST(0) = ST(0) + ST(0);	/* 47591b: fadd st(0), st(0) */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 47591d: fsub dword ptr [eax] */
	MDBL((DWORD)(m->esp + 0x18u)) = (double)ST(0); FPOP();	/* 47591f: fstp qword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x24u)));	/* 475923: fld dword ptr [esi + 0x24] */
	MDBL((DWORD)(m->esp + 0x10u)) = (double)ST(0); FPOP();	/* 475926: fstp qword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20u)));	/* 47592a: fld dword ptr [esi + 0x20] */
	MDBL((DWORD)(m->esp + 0x8u)) = (double)ST(0); FPOP();	/* 47592d: fstp qword ptr [esp + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 475931: fld dword ptr [ebx] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 475933: fstp qword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47593bu; native_call(m, 0x4509d2u);	/* 475936: call 0x4509d2 */
	m->ecx = (DWORD)(m->esp + 0xd0u);	/* 47593b: lea ecx, [esp + 0xd0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 475942: push ecx */
	{ DWORD v_ = 0xba6u; m->esp -= 4; M32(m->esp) = v_; }	/* 475943: push 0xba6 */
	m->esp -= 4; M32(m->esp) = 0x47594eu; native_call(m, M32(0x4a9270u));	/* 475948: call dword ptr [0x4a9270] */
	m->edx = (DWORD)(m->esp + 0xd0u);	/* 47594e: lea edx, [esp + 0xd0] */
	m->eax = (DWORD)(m->esi + 0x2cu);	/* 475955: lea eax, [esi + 0x2c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 475958: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 475959: push eax */
	m->esp -= 4; M32(m->esp) = 0x47595fu; native_call(m, 0x47d740u);	/* 47595a: call 0x47d740 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47595f: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x475968u; native_call(m, M32(0x4a9258u));	/* 475962: call dword ptr [0x4a9258] */
	{ DWORD a_ = M32((DWORD)(m->esi + 0xcu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 475968: cmp dword ptr [esi + 0xc], 1 */
	if (m->zf) goto L_476332;	/* 47596c: je 0x476332 */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 475972: mov eax, dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 475976: fld dword ptr [eax] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x0u));	/* 475978: fsub dword ptr [ebx] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 47597a: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 47597e: fld dword ptr [eax + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x4u));	/* 475981: fsub dword ptr [ebx + 4] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 475984: mov ecx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x24u)) = m->ecx;	/* 475988: mov dword ptr [esp + 0x24], ecx */
	m->ecx = (DWORD)(m->esp + 0x24u);	/* 47598c: lea ecx, [esp + 0x24] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 475990: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 475994: fld dword ptr [eax + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x8u));	/* 475997: fsub dword ptr [ebx + 8] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 47599a: mov edx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 47599e: mov dword ptr [esp + 0x28], edx */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 4759a2: fstp dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 4759a6: mov eax, dword ptr [esp + 0x20] */
	M32((DWORD)(m->esp + 0x2cu)) = m->eax;	/* 4759aa: mov dword ptr [esp + 0x2c], eax */
	m->esp -= 4; M32(m->esp) = 0x4759b3u; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 4759ae: call 0x467760 */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0);	/* 4759b3: fst dword ptr [esp + 0x10] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 4759b7: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4759bd: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4759bf: test ah, 0x41 */
	if (!m->zf) goto L_476332;	/* 4759c2: jne 0x476332 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4759c8: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa428u));	/* 4759cc: fmul dword ptr [0x4aa428] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4759d2: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4759d7: cmp eax, 1 */
	M32((DWORD)(m->esp + 0x38u)) = m->eax;	/* 4759da: mov dword ptr [esp + 0x38], eax */
	if (m->zf || m->sf != m->of) goto L_475ae5;	/* 4759de: jle 0x475ae5 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x38u)));	/* 4759e4: fild dword ptr [esp + 0x38] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4759e8: cmp eax, edi */
	M32((DWORD)(m->esp + 0x30u)) = m->edi;	/* 4759ea: mov dword ptr [esp + 0x30], edi */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4759ee: fdivr dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 4759f2: fstp dword ptr [esp + 0x10] */
	if (m->zf || m->sf != m->of) goto L_476332;	/* 4759f6: jle 0x476332 */
L_4759fc:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 4759fc: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 475a00: fmul dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 475a04: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 475a08: fmul dword ptr [esp + 0x10] */
	M32((DWORD)(m->esp + 0x54u)) = m->edi;	/* 475a0c: mov dword ptr [esp + 0x54], edi */
	M32((DWORD)(m->esp + 0x58u)) = m->edi;	/* 475a10: mov dword ptr [esp + 0x58], edi */
	M32((DWORD)(m->esp + 0x74u)) = m->edi;	/* 475a14: mov dword ptr [esp + 0x74], edi */
	M32((DWORD)(m->esp + 0x78u)) = m->edi;	/* 475a18: mov dword ptr [esp + 0x78], edi */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 475a1c: fstp dword ptr [esp + 0x40] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 475a20: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 475a24: fmul dword ptr [esp + 0x10] */
	M32((DWORD)(m->esp + 0x7cu)) = m->edi;	/* 475a28: mov dword ptr [esp + 0x7c], edi */
	M32((DWORD)(m->esp + 0x84u)) = m->edi;	/* 475a2c: mov dword ptr [esp + 0x84], edi */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 475a33: fstp dword ptr [esp + 0x44] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x30u)));	/* 475a37: fild dword ptr [esp + 0x30] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 475a3b: fstp dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 475a3f: fmul dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 475a43: fld dword ptr [esp + 0x40] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 475a47: fmul dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 475a4b: fstp dword ptr [esp + 0x4c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 475a4f: fld dword ptr [esp + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 475a53: fmul dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x50u)) = (float)ST(0); FPOP();	/* 475a57: fstp dword ptr [esp + 0x50] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x0u));	/* 475a5b: fadd dword ptr [ebx] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 475a5d: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 475a61: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x4u));	/* 475a65: fadd dword ptr [ebx + 4] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 475a68: mov ecx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x5cu)) = m->ecx;	/* 475a6c: mov dword ptr [esp + 0x5c], ecx */
	m->ecx = M32((DWORD)(0xa0e7b8u));	/* 475a70: mov ecx, dword ptr [0xa0e7b8] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 475a76: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x50u)));	/* 475a7a: fld dword ptr [esp + 0x50] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x8u));	/* 475a7e: fadd dword ptr [ebx + 8] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 475a81: mov edx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x68u)) = m->ecx;	/* 475a85: mov dword ptr [esp + 0x68], ecx */
	m->ecx = (DWORD)(m->esp + 0x54u);	/* 475a89: lea ecx, [esp + 0x54] */
	M32((DWORD)(m->esp + 0x60u)) = m->edx;	/* 475a8d: mov dword ptr [esp + 0x60], edx */
	m->edx = M32((DWORD)(0xa0e7bcu));	/* 475a91: mov edx, dword ptr [0xa0e7bc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 475a97: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 475a98: mov ecx, dword ptr [esp + 0x38] */
	M32((DWORD)(m->esp + 0x70u)) = m->edx;	/* 475a9c: mov dword ptr [esp + 0x70], edx */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 475aa0: fstp dword ptr [esp + 0x24] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 475aa4: mov eax, dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 475aa8: fld dword ptr [esi + 0x80] */
	M32((DWORD)(m->esp + 0x68u)) = m->eax;	/* 475aae: mov dword ptr [esp + 0x68], eax */
	m->eax = M32((DWORD)(0xa0e7c0u));	/* 475ab2: mov eax, dword ptr [0xa0e7c0] */
	MF((DWORD)(m->esp + 0x84u)) = (float)ST(0); FPOP();	/* 475ab7: fstp dword ptr [esp + 0x84] */
	M32((DWORD)(m->esp + 0x74u)) = m->eax;	/* 475abe: mov dword ptr [esp + 0x74], eax */
	m->esp -= 4; M32(m->esp) = 0x475ac7u; native_call(m, 0x479950u);	/* 475ac2: call 0x479950 */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 475ac7: mov eax, dword ptr [esp + 0x30] */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 475acb: mov ecx, dword ptr [esp + 0x38] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 475acf: inc eax */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 475ad0: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 475ad2: mov dword ptr [esp + 0x30], eax */
	if (m->sf != m->of) goto L_4759fc;	/* 475ad6: jl 0x4759fc */
	m->edi = M32(m->esp); m->esp += 4;	/* 475adc: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 475add: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 475ade: pop ebx */
	m->esp = m->ebp;	/* 475adf: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 475ae1: pop ebp */
	m->esp += 4 + 8; return;	/* 475ae2: ret 8 */
L_475ae5:
	m->edx = M32((DWORD)(m->ebx + 0x0u));	/* 475ae5: mov edx, dword ptr [ebx] */
	m->ecx = M32((DWORD)(m->ebx + 0x8u));	/* 475ae7: mov ecx, dword ptr [ebx + 8] */
	m->eax = M32((DWORD)(m->ebx + 0x4u));	/* 475aea: mov eax, dword ptr [ebx + 4] */
	M32((DWORD)(m->esp + 0x5cu)) = m->edx;	/* 475aed: mov dword ptr [esp + 0x5c], edx */
	m->edx = M32((DWORD)(0xa0e7b8u));	/* 475af1: mov edx, dword ptr [0xa0e7b8] */
	M32((DWORD)(m->esp + 0x64u)) = m->ecx;	/* 475af7: mov dword ptr [esp + 0x64], ecx */
	m->ecx = M32((DWORD)(0xa0e7c0u));	/* 475afb: mov ecx, dword ptr [0xa0e7c0] */
	M32((DWORD)(m->esp + 0x68u)) = m->edx;	/* 475b01: mov dword ptr [esp + 0x68], edx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 475b05: fld dword ptr [esi + 0x80] */
	M32((DWORD)(m->esp + 0x60u)) = m->eax;	/* 475b0b: mov dword ptr [esp + 0x60], eax */
	m->eax = M32((DWORD)(0xa0e7bcu));	/* 475b0f: mov eax, dword ptr [0xa0e7bc] */
	m->edx = (DWORD)(m->esp + 0x54u);	/* 475b14: lea edx, [esp + 0x54] */
	M32((DWORD)(m->esp + 0x70u)) = m->ecx;	/* 475b18: mov dword ptr [esp + 0x70], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 475b1c: mov ecx, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 475b20: push edx */
	MF((DWORD)(m->esp + 0x84u)) = (float)ST(0); FPOP();	/* 475b21: fstp dword ptr [esp + 0x84] */
	M32((DWORD)(m->esp + 0x58u)) = m->edi;	/* 475b28: mov dword ptr [esp + 0x58], edi */
	M32((DWORD)(m->esp + 0x5cu)) = m->edi;	/* 475b2c: mov dword ptr [esp + 0x5c], edi */
	M32((DWORD)(m->esp + 0x70u)) = m->eax;	/* 475b30: mov dword ptr [esp + 0x70], eax */
	M32((DWORD)(m->esp + 0x78u)) = m->edi;	/* 475b34: mov dword ptr [esp + 0x78], edi */
	M32((DWORD)(m->esp + 0x7cu)) = m->edi;	/* 475b38: mov dword ptr [esp + 0x7c], edi */
	M32((DWORD)(m->esp + 0x80u)) = m->edi;	/* 475b3c: mov dword ptr [esp + 0x80], edi */
	M32((DWORD)(m->esp + 0x88u)) = m->edi;	/* 475b43: mov dword ptr [esp + 0x88], edi */
	m->esp -= 4; M32(m->esp) = 0x475b4fu; native_call(m, 0x479950u);	/* 475b4a: call 0x479950 */
	m->edi = M32(m->esp); m->esp += 4;	/* 475b4f: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 475b50: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 475b51: pop ebx */
	m->esp = m->ebp;	/* 475b52: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 475b54: pop ebp */
	m->esp += 4 + 8; return;	/* 475b55: ret 8 */
L_475b58:
	m->eax = (m->eax & ~(0xffu << 0)) | (((0xffu) & 0xff) << 0);	/* 475b58: mov al, 0xff */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((0xc4u) & 0xff) << 0);	/* 475b5a: mov cl, 0xc4 */
	M32((DWORD)(m->esi + 0x70u)) = 0x0u;	/* 475b5c: mov dword ptr [esi + 0x70], 0 */
	M8((DWORD)(m->esi + 0x78u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 475b63: mov byte ptr [esi + 0x78], al */
	M8((DWORD)(m->esi + 0x79u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 475b66: mov byte ptr [esi + 0x79], cl */
	M8((DWORD)(m->esi + 0x7au)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 475b69: mov byte ptr [esi + 0x7a], cl */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 475b6c: mov byte ptr [esi + 0x7b], al */
	m->esp -= 4; M32(m->esp) = 0x475b75u; native_call(m, M32(0x4a9204u));	/* 475b6f: call dword ptr [0x4a9204] */
	m->esp -= 4; M32(m->esp) = 0x475b7bu; native_call(m, M32(0x4a9218u));	/* 475b75: call dword ptr [0x4a9218] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x24u)));	/* 475b7b: fld dword ptr [esi + 0x24] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 475b7e: xor edi, edi */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 475b80: mov eax, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 475b84: push edi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 475b85: push edi */
	ST(0) = ST(0) + ST(0);	/* 475b86: fadd st(0), st(0) */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 475b88: push 0x3ff00000 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 475b8d: push edi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 475b8e: push edi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 475b8f: push edi */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x18u));	/* 475b90: fsub dword ptr [esi + 0x18] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 475b93: sub esp, 8 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 475b96: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x8u)) = (double)ST(0); FPOP();	/* 475b99: fstp qword ptr [esp + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20u)));	/* 475b9d: fld dword ptr [esi + 0x20] */
	ST(0) = ST(0) + ST(0);	/* 475ba0: fadd st(0), st(0) */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 475ba2: sub esp, 8 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 475ba5: sub esp, 8 */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x14u));	/* 475ba8: fsub dword ptr [esi + 0x14] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 475bab: sub esp, 8 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 475bae: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x20u)) = (double)ST(0); FPOP();	/* 475bb1: fstp qword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 475bb5: fld dword ptr [ebx] */
	ST(0) = ST(0) + ST(0);	/* 475bb7: fadd st(0), st(0) */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 475bb9: fsub dword ptr [eax] */
	MDBL((DWORD)(m->esp + 0x18u)) = (double)ST(0); FPOP();	/* 475bbb: fstp qword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x24u)));	/* 475bbf: fld dword ptr [esi + 0x24] */
	MDBL((DWORD)(m->esp + 0x10u)) = (double)ST(0); FPOP();	/* 475bc2: fstp qword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20u)));	/* 475bc6: fld dword ptr [esi + 0x20] */
	MDBL((DWORD)(m->esp + 0x8u)) = (double)ST(0); FPOP();	/* 475bc9: fstp qword ptr [esp + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 475bcd: fld dword ptr [ebx] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 475bcf: fstp qword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x475bd7u; native_call(m, 0x4509d2u);	/* 475bd2: call 0x4509d2 */
	m->ecx = (DWORD)(m->esp + 0xd0u);	/* 475bd7: lea ecx, [esp + 0xd0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 475bde: push ecx */
	{ DWORD v_ = 0xba6u; m->esp -= 4; M32(m->esp) = v_; }	/* 475bdf: push 0xba6 */
	m->esp -= 4; M32(m->esp) = 0x475beau; native_call(m, M32(0x4a9270u));	/* 475be4: call dword ptr [0x4a9270] */
	m->edx = (DWORD)(m->esp + 0xd0u);	/* 475bea: lea edx, [esp + 0xd0] */
	m->eax = (DWORD)(m->esi + 0x2cu);	/* 475bf1: lea eax, [esi + 0x2c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 475bf4: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 475bf5: push eax */
	m->esp -= 4; M32(m->esp) = 0x475bfbu; native_call(m, 0x47d740u);	/* 475bf6: call 0x47d740 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 475bfb: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x475c04u; native_call(m, M32(0x4a9258u));	/* 475bfe: call dword ptr [0x4a9258] */
	{ DWORD a_ = M32((DWORD)(m->esi + 0xcu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 475c04: cmp dword ptr [esi + 0xc], 1 */
	if (m->zf) goto L_476332;	/* 475c08: je 0x476332 */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 475c0e: mov eax, dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 475c12: fld dword ptr [eax] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x0u));	/* 475c14: fsub dword ptr [ebx] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 475c16: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 475c1a: fld dword ptr [eax + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x4u));	/* 475c1d: fsub dword ptr [ebx + 4] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 475c20: mov ecx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x24u)) = m->ecx;	/* 475c24: mov dword ptr [esp + 0x24], ecx */
	m->ecx = (DWORD)(m->esp + 0x24u);	/* 475c28: lea ecx, [esp + 0x24] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 475c2c: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 475c30: fld dword ptr [eax + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x8u));	/* 475c33: fsub dword ptr [ebx + 8] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 475c36: mov edx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 475c3a: mov dword ptr [esp + 0x28], edx */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 475c3e: fstp dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 475c42: mov eax, dword ptr [esp + 0x20] */
	M32((DWORD)(m->esp + 0x2cu)) = m->eax;	/* 475c46: mov dword ptr [esp + 0x2c], eax */
	m->esp -= 4; M32(m->esp) = 0x475c4fu; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 475c4a: call 0x467760 */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0);	/* 475c4f: fst dword ptr [esp + 0x10] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 475c53: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 475c59: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 475c5b: test ah, 0x41 */
	if (!m->zf) goto L_476332;	/* 475c5e: jne 0x476332 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 475c64: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa428u));	/* 475c68: fmul dword ptr [0x4aa428] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 475c6e: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 475c73: cmp eax, 1 */
	M32((DWORD)(m->esp + 0x38u)) = m->eax;	/* 475c76: mov dword ptr [esp + 0x38], eax */
	if (m->zf || m->sf != m->of) goto L_475ae5;	/* 475c7a: jle 0x475ae5 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x38u)));	/* 475c80: fild dword ptr [esp + 0x38] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 475c84: cmp eax, edi */
	M32((DWORD)(m->esp + 0x30u)) = m->edi;	/* 475c86: mov dword ptr [esp + 0x30], edi */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 475c8a: fdivr dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 475c8e: fstp dword ptr [esp + 0x10] */
	if (m->zf || m->sf != m->of) goto L_476332;	/* 475c92: jle 0x476332 */
L_475c98:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 475c98: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 475c9c: fmul dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 475ca0: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 475ca4: fmul dword ptr [esp + 0x10] */
	M32((DWORD)(m->esp + 0x54u)) = m->edi;	/* 475ca8: mov dword ptr [esp + 0x54], edi */
	M32((DWORD)(m->esp + 0x58u)) = m->edi;	/* 475cac: mov dword ptr [esp + 0x58], edi */
	M32((DWORD)(m->esp + 0x74u)) = m->edi;	/* 475cb0: mov dword ptr [esp + 0x74], edi */
	M32((DWORD)(m->esp + 0x78u)) = m->edi;	/* 475cb4: mov dword ptr [esp + 0x78], edi */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 475cb8: fstp dword ptr [esp + 0x4c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 475cbc: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 475cc0: fmul dword ptr [esp + 0x10] */
	M32((DWORD)(m->esp + 0x7cu)) = m->edi;	/* 475cc4: mov dword ptr [esp + 0x7c], edi */
	M32((DWORD)(m->esp + 0x84u)) = m->edi;	/* 475cc8: mov dword ptr [esp + 0x84], edi */
	MF((DWORD)(m->esp + 0x50u)) = (float)ST(0); FPOP();	/* 475ccf: fstp dword ptr [esp + 0x50] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x30u)));	/* 475cd3: fild dword ptr [esp + 0x30] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 475cd7: fstp dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 475cdb: fmul dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 475cdf: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 475ce3: fmul dword ptr [esp + 0x4c] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 475ce7: fstp dword ptr [esp + 0x40] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 475ceb: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x50u));	/* 475cef: fmul dword ptr [esp + 0x50] */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 475cf3: fstp dword ptr [esp + 0x44] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x0u));	/* 475cf7: fadd dword ptr [ebx] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 475cf9: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 475cfd: fld dword ptr [esp + 0x40] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x4u));	/* 475d01: fadd dword ptr [ebx + 4] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 475d04: mov ecx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x5cu)) = m->ecx;	/* 475d08: mov dword ptr [esp + 0x5c], ecx */
	m->ecx = M32((DWORD)(0xa0e7b8u));	/* 475d0c: mov ecx, dword ptr [0xa0e7b8] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 475d12: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 475d16: fld dword ptr [esp + 0x44] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x8u));	/* 475d1a: fadd dword ptr [ebx + 8] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 475d1d: mov edx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x68u)) = m->ecx;	/* 475d21: mov dword ptr [esp + 0x68], ecx */
	m->ecx = (DWORD)(m->esp + 0x54u);	/* 475d25: lea ecx, [esp + 0x54] */
	M32((DWORD)(m->esp + 0x60u)) = m->edx;	/* 475d29: mov dword ptr [esp + 0x60], edx */
	m->edx = M32((DWORD)(0xa0e7bcu));	/* 475d2d: mov edx, dword ptr [0xa0e7bc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 475d33: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 475d34: mov ecx, dword ptr [esp + 0x38] */
	M32((DWORD)(m->esp + 0x70u)) = m->edx;	/* 475d38: mov dword ptr [esp + 0x70], edx */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 475d3c: fstp dword ptr [esp + 0x24] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 475d40: mov eax, dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 475d44: fld dword ptr [esi + 0x80] */
	M32((DWORD)(m->esp + 0x68u)) = m->eax;	/* 475d4a: mov dword ptr [esp + 0x68], eax */
	m->eax = M32((DWORD)(0xa0e7c0u));	/* 475d4e: mov eax, dword ptr [0xa0e7c0] */
	MF((DWORD)(m->esp + 0x84u)) = (float)ST(0); FPOP();	/* 475d53: fstp dword ptr [esp + 0x84] */
	M32((DWORD)(m->esp + 0x74u)) = m->eax;	/* 475d5a: mov dword ptr [esp + 0x74], eax */
	m->esp -= 4; M32(m->esp) = 0x475d63u; native_call(m, 0x479950u);	/* 475d5e: call 0x479950 */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 475d63: mov eax, dword ptr [esp + 0x30] */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 475d67: mov ecx, dword ptr [esp + 0x38] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 475d6b: inc eax */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 475d6c: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 475d6e: mov dword ptr [esp + 0x30], eax */
	if (m->sf != m->of) goto L_475c98;	/* 475d72: jl 0x475c98 */
	m->edi = M32(m->esp); m->esp += 4;	/* 475d78: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 475d79: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 475d7a: pop ebx */
	m->esp = m->ebp;	/* 475d7b: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 475d7d: pop ebp */
	m->esp += 4 + 8; return;	/* 475d7e: ret 8 */
L_475d81:
	m->eax = (DWORD)(m->ecx + 0xffffffe2u);	/* 475d81: lea eax, [ecx - 0x1e] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 475d84: cmp eax, 4 */
	if (!m->cf && !m->zf) goto L_476332;	/* 475d87: ja 0x476332 */
	switch (m->eax) { case 0: goto L_475da7; case 1: goto L_475da7; case 2: goto L_475da7; case 3: goto L_475da7; case 4: goto L_475da7; default: abort(); }	/* 475d8d: jmp dword ptr [eax*4 + 0x4763c4] */
L_475d94:
	m->eax = (DWORD)(m->ecx + 0xffffffddu);	/* 475d94: lea eax, [ecx - 0x23] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 475d97: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_476332;	/* 475d9a: ja 0x476332 */
	switch (m->eax) { case 0: goto L_475da7; case 1: goto L_475da7; case 2: goto L_475da7; case 3: goto L_475da7; default: abort(); }	/* 475da0: jmp dword ptr [eax*4 + 0x4763d8] */
L_475da7:
	M32((DWORD)(m->esi + 0x70u)) = 0x3f800000u;	/* 475da7: mov dword ptr [esi + 0x70], 0x3f800000 */
	m->edi = M32(m->esp); m->esp += 4;	/* 475dae: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 475daf: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 475db0: pop ebx */
	m->esp = m->ebp;	/* 475db1: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 475db3: pop ebp */
	m->esp += 4 + 8; return;	/* 475db4: ret 8 */
L_475db7:
	m->eax = (DWORD)(m->ecx + 0xffffffd8u);	/* 475db7: lea eax, [ecx - 0x28] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 475dba: cmp eax, 4 */
	if (!m->cf && !m->zf) goto L_476332;	/* 475dbd: ja 0x476332 */
	switch (m->eax) { case 0: goto L_47623c; case 1: goto L_475dca; case 2: goto L_476125; case 3: goto L_475f45; case 4: goto L_476035; default: abort(); }	/* 475dc3: jmp dword ptr [eax*4 + 0x4763e8] */
L_475dca:
	M32((DWORD)(m->esi + 0x70u)) = 0x40000000u;	/* 475dca: mov dword ptr [esi + 0x70], 0x40000000 */
	m->eax = M32((DWORD)(m->edi + 0x24u));	/* 475dd1: mov eax, dword ptr [edi + 0x24] */
	m->edx = (DWORD)(m->esi + 0x84u);	/* 475dd4: lea edx, [esi + 0x84] */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 475dda: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->edx + 0x0u)) = m->ecx;	/* 475ddc: mov dword ptr [edx], ecx */
	m->ecx = M32((DWORD)(m->eax + 0x4u));	/* 475dde: mov ecx, dword ptr [eax + 4] */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 475de1: mov dword ptr [edx + 4], ecx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 475de4: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 475de7: mov dword ptr [edx + 8], eax */
	m->ecx = M32((DWORD)(m->edi + 0x24u));	/* 475dea: mov ecx, dword ptr [edi + 0x24] */
	{ DWORD a_ = m->ecx, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 475ded: add ecx, 0xc */
	m->edx = (DWORD)(m->esi + 0x90u);	/* 475df0: lea edx, [esi + 0x90] */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 475df6: mov eax, dword ptr [ecx] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 475df8: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->ecx + 0x4u));	/* 475dfa: mov eax, dword ptr [ecx + 4] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 475dfd: mov dword ptr [edx + 4], eax */
	m->eax = (DWORD)(m->esi + 0x9cu);	/* 475e00: lea eax, [esi + 0x9c] */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 475e06: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 475e09: mov dword ptr [edx + 8], ecx */
	m->edx = M32((DWORD)(m->edi + 0x24u));	/* 475e0c: mov edx, dword ptr [edi + 0x24] */
	{ DWORD a_ = m->edx, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 475e0f: add edx, 0x18 */
	m->ecx = M32((DWORD)(m->edx + 0x0u));	/* 475e12: mov ecx, dword ptr [edx] */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 475e14: mov dword ptr [eax], ecx */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 475e16: mov ecx, dword ptr [edx + 4] */
	M32((DWORD)(m->eax + 0x4u)) = m->ecx;	/* 475e19: mov dword ptr [eax + 4], ecx */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 475e1c: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 475e1f: mov dword ptr [eax + 8], edx */
	m->eax = M32((DWORD)(m->edi + 0x28u));	/* 475e22: mov eax, dword ptr [edi + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 475e25: fld dword ptr [eax] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa428u));	/* 475e27: fmul dword ptr [0x4aa428] */
	M32((DWORD)(m->esi + 0xb8u)) = 0x3f000000u;	/* 475e2d: mov dword ptr [esi + 0xb8], 0x3f000000 */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 475e37: fadd dword ptr [0x4a942c] */
	MF((DWORD)(m->esi + 0xb4u)) = (float)ST(0); FPOP();	/* 475e3d: fstp dword ptr [esi + 0xb4] */
	m->eax = M32((DWORD)(m->edi + 0x28u));	/* 475e43: mov eax, dword ptr [edi + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0xcu)));	/* 475e46: fld dword ptr [eax + 0xc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa428u));	/* 475e49: fmul dword ptr [0x4aa428] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 475e4f: fadd dword ptr [0x4a942c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 475e55: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa428u));	/* 475e58: fmul dword ptr [0x4aa428] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 475e5e: fadd dword ptr [0x4a942c] */
	MF((DWORD)(m->esi + 0xbcu)) = (float)ST(0); FPOP();	/* 475e64: fstp dword ptr [esi + 0xbc] */
	MF((DWORD)(m->esi + 0xc0u)) = (float)ST(0); FPOP();	/* 475e6a: fstp dword ptr [esi + 0xc0] */
	m->edi = M32((DWORD)(m->edi + 0x28u));	/* 475e70: mov edi, dword ptr [edi + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x14u)));	/* 475e73: fld dword ptr [edi + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa428u));	/* 475e76: fmul dword ptr [0x4aa428] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 475e7c: fadd dword ptr [0x4a942c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x10u)));	/* 475e82: fld dword ptr [edi + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa428u));	/* 475e85: fmul dword ptr [0x4aa428] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 475e8b: fadd dword ptr [0x4a942c] */
	MF((DWORD)(m->esi + 0xc4u)) = (float)ST(0); FPOP();	/* 475e91: fstp dword ptr [esi + 0xc4] */
	MF((DWORD)(m->esi + 0xc8u)) = (float)ST(0); FPOP();	/* 475e97: fstp dword ptr [esi + 0xc8] */
L_475e9d:
	m->ecx = M32((DWORD)(0xa1f23cu));	/* 475e9d: mov ecx, dword ptr [0xa1f23c] */
	M32((DWORD)(m->esi + 0xd4u)) = m->ecx;	/* 475ea3: mov dword ptr [esi + 0xd4], ecx */
	m->edx = M32((DWORD)(0xa1f23cu));	/* 475ea9: mov edx, dword ptr [0xa1f23c] */
	M32((DWORD)(m->esi + 0xd8u)) = m->edx;	/* 475eaf: mov dword ptr [esi + 0xd8], edx */
	m->eax = M32((DWORD)(0xa1f23cu));	/* 475eb5: mov eax, dword ptr [0xa1f23c] */
	M32((DWORD)(m->esi + 0xdcu)) = m->eax;	/* 475eba: mov dword ptr [esi + 0xdc], eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 475ec0: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 475ec1: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 475ec2: pop ebx */
	m->esp = m->ebp;	/* 475ec3: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 475ec5: pop ebp */
	m->esp += 4 + 8; return;	/* 475ec6: ret 8 */
L_475ec9:
	m->eax = (DWORD)(m->ecx + 0xffffffd3u);	/* 475ec9: lea eax, [ecx - 0x2d] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 475ecc: cmp eax, 4 */
	if (!m->cf && !m->zf) goto L_476332;	/* 475ecf: ja 0x476332 */
	switch (m->eax) { case 0: goto L_475edc; case 1: goto L_475f45; case 2: goto L_476035; case 3: goto L_476125; case 4: goto L_47623c; default: abort(); }	/* 475ed5: jmp dword ptr [eax*4 + 0x4763fc] */
L_475edc:
	M32((DWORD)(m->esi + 0x70u)) = 0x40000000u;	/* 475edc: mov dword ptr [esi + 0x70], 0x40000000 */
	m->edx = M32((DWORD)(m->edi + 0x24u));	/* 475ee3: mov edx, dword ptr [edi + 0x24] */
	m->ecx = (DWORD)(m->esi + 0x84u);	/* 475ee6: lea ecx, [esi + 0x84] */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 475eec: mov eax, dword ptr [edx] */
	M32((DWORD)(m->ecx + 0x0u)) = m->eax;	/* 475eee: mov dword ptr [ecx], eax */
	m->eax = M32((DWORD)(m->edx + 0x4u));	/* 475ef0: mov eax, dword ptr [edx + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 475ef3: mov dword ptr [ecx + 4], eax */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 475ef6: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 475ef9: mov dword ptr [ecx + 8], edx */
	m->eax = M32((DWORD)(m->edi + 0x24u));	/* 475efc: mov eax, dword ptr [edi + 0x24] */
	{ DWORD a_ = m->eax, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 475eff: add eax, 0xc */
	m->ecx = (DWORD)(m->esi + 0x90u);	/* 475f02: lea ecx, [esi + 0x90] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 475f08: fld dword ptr [esi + 0x80] */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 475f0e: mov edx, dword ptr [eax] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 475f10: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 475f12: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 475f15: mov dword ptr [ecx + 4], edx */
	m->edx = (DWORD)(m->esi + 0x9cu);	/* 475f18: lea edx, [esi + 0x9c] */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 475f1e: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 475f21: mov dword ptr [ecx + 8], eax */
	m->ecx = M32((DWORD)(m->edi + 0x24u));	/* 475f24: mov ecx, dword ptr [edi + 0x24] */
	{ DWORD a_ = m->ecx, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 475f27: add ecx, 0x18 */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4aa424u));	/* 475f2a: fadd dword ptr [0x4aa424] */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 475f30: mov eax, dword ptr [ecx] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 475f32: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->ecx + 0x4u));	/* 475f34: mov eax, dword ptr [ecx + 4] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 475f37: mov dword ptr [edx + 4], eax */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 475f3a: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 475f3d: mov dword ptr [edx + 8], ecx */
	goto L_476189;	/* 475f40: jmp 0x476189 */
L_475f45:
	M32((DWORD)(m->esi + 0x70u)) = 0x40000000u;	/* 475f45: mov dword ptr [esi + 0x70], 0x40000000 */
	m->ecx = M32((DWORD)(m->edi + 0x24u));	/* 475f4c: mov ecx, dword ptr [edi + 0x24] */
	m->eax = (DWORD)(m->esi + 0x84u);	/* 475f4f: lea eax, [esi + 0x84] */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 475f55: mov edx, dword ptr [ecx] */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 475f57: mov dword ptr [eax], edx */
	m->edx = M32((DWORD)(m->ecx + 0x4u));	/* 475f59: mov edx, dword ptr [ecx + 4] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 475f5c: mov dword ptr [eax + 4], edx */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 475f5f: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 475f62: mov dword ptr [eax + 8], ecx */
	m->edx = M32((DWORD)(m->edi + 0x24u));	/* 475f65: mov edx, dword ptr [edi + 0x24] */
	{ DWORD a_ = m->edx, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 475f68: add edx, 0xc */
	m->eax = (DWORD)(m->esi + 0x90u);	/* 475f6b: lea eax, [esi + 0x90] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 475f71: fld dword ptr [esi + 0x80] */
	m->ecx = M32((DWORD)(m->edx + 0x0u));	/* 475f77: mov ecx, dword ptr [edx] */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 475f79: mov dword ptr [eax], ecx */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 475f7b: mov ecx, dword ptr [edx + 4] */
	M32((DWORD)(m->eax + 0x4u)) = m->ecx;	/* 475f7e: mov dword ptr [eax + 4], ecx */
	m->ecx = (DWORD)(m->esi + 0x9cu);	/* 475f81: lea ecx, [esi + 0x9c] */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 475f87: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 475f8a: mov dword ptr [eax + 8], edx */
	m->eax = M32((DWORD)(m->edi + 0x24u));	/* 475f8d: mov eax, dword ptr [edi + 0x24] */
	{ DWORD a_ = m->eax, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 475f90: add eax, 0x18 */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a93f0u));	/* 475f93: fadd dword ptr [0x4a93f0] */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 475f99: mov edx, dword ptr [eax] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 475f9b: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 475f9d: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 475fa0: mov dword ptr [ecx + 4], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 475fa3: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 475fa6: mov dword ptr [ecx + 8], eax */
	m->ecx = M32((DWORD)(m->edi + 0x28u));	/* 475fa9: mov ecx, dword ptr [edi + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x0u)));	/* 475fac: fld dword ptr [ecx] */
	ST(0) = ST(0) / ST(1);	/* 475fae: fdiv st(1) */
	M32((DWORD)(m->esi + 0xb8u)) = 0x3f000000u;	/* 475fb0: mov dword ptr [esi + 0xb8], 0x3f000000 */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 475fba: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 475fc0: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esi + 0xb4u)) = (float)ST(0); FPOP();	/* 475fc6: fstp dword ptr [esi + 0xb4] */
	m->eax = M32((DWORD)(m->edi + 0x28u));	/* 475fcc: mov eax, dword ptr [edi + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0xcu)));	/* 475fcf: fld dword ptr [eax + 0xc] */
	ST(0) = ST(0) / ST(1);	/* 475fd2: fdiv st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 475fd4: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 475fda: fmul dword ptr [0x4a942c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 475fe0: fld dword ptr [eax + 8] */
	ST(0) = ST(0) / ST(2);	/* 475fe3: fdiv st(2) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 475fe5: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 475feb: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esi + 0xbcu)) = (float)ST(0); FPOP();	/* 475ff1: fstp dword ptr [esi + 0xbc] */
	MF((DWORD)(m->esi + 0xc0u)) = (float)ST(0); FPOP();	/* 475ff7: fstp dword ptr [esi + 0xc0] */
	m->edi = M32((DWORD)(m->edi + 0x28u));	/* 475ffd: mov edi, dword ptr [edi + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x14u)));	/* 476000: fld dword ptr [edi + 0x14] */
	ST(0) = ST(0) / ST(1);	/* 476003: fdiv st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 476005: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 47600b: fmul dword ptr [0x4a942c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x10u)));	/* 476011: fld dword ptr [edi + 0x10] */
	ST(0) = ST(0) / ST(2);	/* 476014: fdiv st(2) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 476016: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 47601c: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esi + 0xc4u)) = (float)ST(0); FPOP();	/* 476022: fstp dword ptr [esi + 0xc4] */
	MF((DWORD)(m->esi + 0xc8u)) = (float)ST(0); FPOP();	/* 476028: fstp dword ptr [esi + 0xc8] */
	ST(0) = ST(0); FPOP();	/* 47602e: fstp st(0) */
	goto L_47630f;	/* 476030: jmp 0x47630f */
L_476035:
	M32((DWORD)(m->esi + 0x70u)) = 0x40000000u;	/* 476035: mov dword ptr [esi + 0x70], 0x40000000 */
	m->eax = M32((DWORD)(m->edi + 0x24u));	/* 47603c: mov eax, dword ptr [edi + 0x24] */
	m->edx = (DWORD)(m->esi + 0x84u);	/* 47603f: lea edx, [esi + 0x84] */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 476045: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->edx + 0x0u)) = m->ecx;	/* 476047: mov dword ptr [edx], ecx */
	m->ecx = M32((DWORD)(m->eax + 0x4u));	/* 476049: mov ecx, dword ptr [eax + 4] */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 47604c: mov dword ptr [edx + 4], ecx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47604f: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 476052: mov dword ptr [edx + 8], eax */
	m->ecx = M32((DWORD)(m->edi + 0x24u));	/* 476055: mov ecx, dword ptr [edi + 0x24] */
	{ DWORD a_ = m->ecx, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 476058: add ecx, 0xc */
	m->edx = (DWORD)(m->esi + 0x90u);	/* 47605b: lea edx, [esi + 0x90] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 476061: fld dword ptr [esi + 0x80] */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 476067: mov eax, dword ptr [ecx] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 476069: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->ecx + 0x4u));	/* 47606b: mov eax, dword ptr [ecx + 4] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 47606e: mov dword ptr [edx + 4], eax */
	m->eax = (DWORD)(m->esi + 0x9cu);	/* 476071: lea eax, [esi + 0x9c] */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 476077: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 47607a: mov dword ptr [edx + 8], ecx */
	m->edx = M32((DWORD)(m->edi + 0x24u));	/* 47607d: mov edx, dword ptr [edi + 0x24] */
	{ DWORD a_ = m->edx, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 476080: add edx, 0x18 */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a93f0u));	/* 476083: fadd dword ptr [0x4a93f0] */
	m->ecx = M32((DWORD)(m->edx + 0x0u));	/* 476089: mov ecx, dword ptr [edx] */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 47608b: mov dword ptr [eax], ecx */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 47608d: mov ecx, dword ptr [edx + 4] */
	M32((DWORD)(m->eax + 0x4u)) = m->ecx;	/* 476090: mov dword ptr [eax + 4], ecx */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 476093: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 476096: mov dword ptr [eax + 8], edx */
	m->eax = M32((DWORD)(m->edi + 0x28u));	/* 476099: mov eax, dword ptr [edi + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 47609c: fld dword ptr [eax] */
	ST(0) = ST(0) / ST(1);	/* 47609e: fdiv st(1) */
	M32((DWORD)(m->esi + 0xb8u)) = 0x3f000000u;	/* 4760a0: mov dword ptr [esi + 0xb8], 0x3f000000 */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4760aa: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4760b0: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esi + 0xb4u)) = (float)ST(0); FPOP();	/* 4760b6: fstp dword ptr [esi + 0xb4] */
	m->eax = M32((DWORD)(m->edi + 0x28u));	/* 4760bc: mov eax, dword ptr [edi + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0xcu)));	/* 4760bf: fld dword ptr [eax + 0xc] */
	ST(0) = ST(0) / ST(1);	/* 4760c2: fdiv st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4760c4: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4760ca: fmul dword ptr [0x4a942c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 4760d0: fld dword ptr [eax + 8] */
	ST(0) = ST(0) / ST(2);	/* 4760d3: fdiv st(2) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4760d5: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4760db: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esi + 0xbcu)) = (float)ST(0); FPOP();	/* 4760e1: fstp dword ptr [esi + 0xbc] */
	MF((DWORD)(m->esi + 0xc0u)) = (float)ST(0); FPOP();	/* 4760e7: fstp dword ptr [esi + 0xc0] */
	m->edi = M32((DWORD)(m->edi + 0x28u));	/* 4760ed: mov edi, dword ptr [edi + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x14u)));	/* 4760f0: fld dword ptr [edi + 0x14] */
	ST(0) = ST(0) / ST(1);	/* 4760f3: fdiv st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4760f5: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4760fb: fmul dword ptr [0x4a942c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x10u)));	/* 476101: fld dword ptr [edi + 0x10] */
	ST(0) = ST(0) / ST(2);	/* 476104: fdiv st(2) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 476106: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 47610c: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esi + 0xc4u)) = (float)ST(0); FPOP();	/* 476112: fstp dword ptr [esi + 0xc4] */
	MF((DWORD)(m->esi + 0xc8u)) = (float)ST(0); FPOP();	/* 476118: fstp dword ptr [esi + 0xc8] */
	ST(0) = ST(0); FPOP();	/* 47611e: fstp st(0) */
	goto L_475e9d;	/* 476120: jmp 0x475e9d */
L_476125:
	M32((DWORD)(m->esi + 0x70u)) = 0x40000000u;	/* 476125: mov dword ptr [esi + 0x70], 0x40000000 */
	m->edx = M32((DWORD)(m->edi + 0x24u));	/* 47612c: mov edx, dword ptr [edi + 0x24] */
	m->ecx = (DWORD)(m->esi + 0x84u);	/* 47612f: lea ecx, [esi + 0x84] */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 476135: mov eax, dword ptr [edx] */
	M32((DWORD)(m->ecx + 0x0u)) = m->eax;	/* 476137: mov dword ptr [ecx], eax */
	m->eax = M32((DWORD)(m->edx + 0x4u));	/* 476139: mov eax, dword ptr [edx + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 47613c: mov dword ptr [ecx + 4], eax */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 47613f: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 476142: mov dword ptr [ecx + 8], edx */
	m->eax = M32((DWORD)(m->edi + 0x24u));	/* 476145: mov eax, dword ptr [edi + 0x24] */
	{ DWORD a_ = m->eax, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 476148: add eax, 0xc */
	m->ecx = (DWORD)(m->esi + 0x90u);	/* 47614b: lea ecx, [esi + 0x90] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 476151: fld dword ptr [esi + 0x80] */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 476157: mov edx, dword ptr [eax] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 476159: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47615b: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 47615e: mov dword ptr [ecx + 4], edx */
	m->edx = (DWORD)(m->esi + 0x9cu);	/* 476161: lea edx, [esi + 0x9c] */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 476167: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 47616a: mov dword ptr [ecx + 8], eax */
	m->ecx = M32((DWORD)(m->edi + 0x24u));	/* 47616d: mov ecx, dword ptr [edi + 0x24] */
	{ DWORD a_ = m->ecx, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 476170: add ecx, 0x18 */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a93f0u));	/* 476173: fadd dword ptr [0x4a93f0] */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 476179: mov eax, dword ptr [ecx] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 47617b: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->ecx + 0x4u));	/* 47617d: mov eax, dword ptr [ecx + 4] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 476180: mov dword ptr [edx + 4], eax */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 476183: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 476186: mov dword ptr [edx + 8], ecx */
L_476189:
	m->edx = M32((DWORD)(m->edi + 0x28u));	/* 476189: mov edx, dword ptr [edi + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x0u)));	/* 47618c: fld dword ptr [edx] */
	ST(0) = ST(0) / ST(1);	/* 47618e: fdiv st(1) */
	M32((DWORD)(m->esi + 0xb8u)) = 0x3f000000u;	/* 476190: mov dword ptr [esi + 0xb8], 0x3f000000 */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 47619a: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4761a0: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esi + 0xb4u)) = (float)ST(0); FPOP();	/* 4761a6: fstp dword ptr [esi + 0xb4] */
	m->eax = M32((DWORD)(m->edi + 0x28u));	/* 4761ac: mov eax, dword ptr [edi + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0xcu)));	/* 4761af: fld dword ptr [eax + 0xc] */
	ST(0) = ST(0) / ST(1);	/* 4761b2: fdiv st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4761b4: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4761ba: fmul dword ptr [0x4a942c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 4761c0: fld dword ptr [eax + 8] */
	ST(0) = ST(0) / ST(2);	/* 4761c3: fdiv st(2) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4761c5: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4761cb: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esi + 0xbcu)) = (float)ST(0); FPOP();	/* 4761d1: fstp dword ptr [esi + 0xbc] */
	MF((DWORD)(m->esi + 0xc0u)) = (float)ST(0); FPOP();	/* 4761d7: fstp dword ptr [esi + 0xc0] */
	m->edi = M32((DWORD)(m->edi + 0x28u));	/* 4761dd: mov edi, dword ptr [edi + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x14u)));	/* 4761e0: fld dword ptr [edi + 0x14] */
	ST(0) = ST(0) / ST(1);	/* 4761e3: fdiv st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4761e5: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4761eb: fmul dword ptr [0x4a942c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x10u)));	/* 4761f1: fld dword ptr [edi + 0x10] */
	ST(0) = ST(0) / ST(2);	/* 4761f4: fdiv st(2) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4761f6: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4761fc: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esi + 0xc4u)) = (float)ST(0); FPOP();	/* 476202: fstp dword ptr [esi + 0xc4] */
	MF((DWORD)(m->esi + 0xc8u)) = (float)ST(0); FPOP();	/* 476208: fstp dword ptr [esi + 0xc8] */
	m->eax = M32((DWORD)(0xa1f23cu));	/* 47620e: mov eax, dword ptr [0xa1f23c] */
	M32((DWORD)(m->esi + 0xd4u)) = m->eax;	/* 476213: mov dword ptr [esi + 0xd4], eax */
	m->ecx = M32((DWORD)(0xa1f23cu));	/* 476219: mov ecx, dword ptr [0xa1f23c] */
	M32((DWORD)(m->esi + 0xd8u)) = m->ecx;	/* 47621f: mov dword ptr [esi + 0xd8], ecx */
	m->edx = M32((DWORD)(0xa1f23cu));	/* 476225: mov edx, dword ptr [0xa1f23c] */
	ST(0) = ST(0); FPOP();	/* 47622b: fstp st(0) */
	M32((DWORD)(m->esi + 0xdcu)) = m->edx;	/* 47622d: mov dword ptr [esi + 0xdc], edx */
	m->edi = M32(m->esp); m->esp += 4;	/* 476233: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 476234: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 476235: pop ebx */
	m->esp = m->ebp;	/* 476236: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 476238: pop ebp */
	m->esp += 4 + 8; return;	/* 476239: ret 8 */
L_47623c:
	M32((DWORD)(m->esi + 0x70u)) = 0x40000000u;	/* 47623c: mov dword ptr [esi + 0x70], 0x40000000 */
	m->ecx = M32((DWORD)(m->edi + 0x24u));	/* 476243: mov ecx, dword ptr [edi + 0x24] */
	m->eax = (DWORD)(m->esi + 0x84u);	/* 476246: lea eax, [esi + 0x84] */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 47624c: mov edx, dword ptr [ecx] */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 47624e: mov dword ptr [eax], edx */
	m->edx = M32((DWORD)(m->ecx + 0x4u));	/* 476250: mov edx, dword ptr [ecx + 4] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 476253: mov dword ptr [eax + 4], edx */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 476256: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 476259: mov dword ptr [eax + 8], ecx */
	m->edx = M32((DWORD)(m->edi + 0x24u));	/* 47625c: mov edx, dword ptr [edi + 0x24] */
	{ DWORD a_ = m->edx, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 47625f: add edx, 0xc */
	m->eax = (DWORD)(m->esi + 0x90u);	/* 476262: lea eax, [esi + 0x90] */
	m->ecx = M32((DWORD)(m->edx + 0x0u));	/* 476268: mov ecx, dword ptr [edx] */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 47626a: mov dword ptr [eax], ecx */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 47626c: mov ecx, dword ptr [edx + 4] */
	M32((DWORD)(m->eax + 0x4u)) = m->ecx;	/* 47626f: mov dword ptr [eax + 4], ecx */
	m->ecx = (DWORD)(m->esi + 0x9cu);	/* 476272: lea ecx, [esi + 0x9c] */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 476278: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 47627b: mov dword ptr [eax + 8], edx */
	m->eax = M32((DWORD)(m->edi + 0x24u));	/* 47627e: mov eax, dword ptr [edi + 0x24] */
	{ DWORD a_ = m->eax, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 476281: add eax, 0x18 */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 476284: mov edx, dword ptr [eax] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 476286: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 476288: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 47628b: mov dword ptr [ecx + 4], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47628e: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 476291: mov dword ptr [ecx + 8], eax */
	m->ecx = M32((DWORD)(m->edi + 0x28u));	/* 476294: mov ecx, dword ptr [edi + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x0u)));	/* 476297: fld dword ptr [ecx] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa428u));	/* 476299: fmul dword ptr [0x4aa428] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 47629f: fadd dword ptr [0x4a942c] */
	MF((DWORD)(m->esi + 0xb4u)) = (float)ST(0); FPOP();	/* 4762a5: fstp dword ptr [esi + 0xb4] */
	M32((DWORD)(m->esi + 0xb8u)) = 0x3f000000u;	/* 4762ab: mov dword ptr [esi + 0xb8], 0x3f000000 */
	m->eax = M32((DWORD)(m->edi + 0x28u));	/* 4762b5: mov eax, dword ptr [edi + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0xcu)));	/* 4762b8: fld dword ptr [eax + 0xc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa428u));	/* 4762bb: fmul dword ptr [0x4aa428] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4762c1: fadd dword ptr [0x4a942c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 4762c7: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa428u));	/* 4762ca: fmul dword ptr [0x4aa428] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4762d0: fadd dword ptr [0x4a942c] */
	MF((DWORD)(m->esi + 0xbcu)) = (float)ST(0); FPOP();	/* 4762d6: fstp dword ptr [esi + 0xbc] */
	MF((DWORD)(m->esi + 0xc0u)) = (float)ST(0); FPOP();	/* 4762dc: fstp dword ptr [esi + 0xc0] */
	m->edi = M32((DWORD)(m->edi + 0x28u));	/* 4762e2: mov edi, dword ptr [edi + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x14u)));	/* 4762e5: fld dword ptr [edi + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa428u));	/* 4762e8: fmul dword ptr [0x4aa428] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4762ee: fadd dword ptr [0x4a942c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x10u)));	/* 4762f4: fld dword ptr [edi + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa428u));	/* 4762f7: fmul dword ptr [0x4aa428] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4762fd: fadd dword ptr [0x4a942c] */
	MF((DWORD)(m->esi + 0xc4u)) = (float)ST(0); FPOP();	/* 476303: fstp dword ptr [esi + 0xc4] */
	MF((DWORD)(m->esi + 0xc8u)) = (float)ST(0); FPOP();	/* 476309: fstp dword ptr [esi + 0xc8] */
L_47630f:
	m->edx = M32((DWORD)(0xa1f23cu));	/* 47630f: mov edx, dword ptr [0xa1f23c] */
	M32((DWORD)(m->esi + 0xd4u)) = m->edx;	/* 476315: mov dword ptr [esi + 0xd4], edx */
	m->eax = M32((DWORD)(0xa1f23cu));	/* 47631b: mov eax, dword ptr [0xa1f23c] */
	M32((DWORD)(m->esi + 0xd8u)) = m->eax;	/* 476320: mov dword ptr [esi + 0xd8], eax */
	m->ecx = M32((DWORD)(0xa1f23cu));	/* 476326: mov ecx, dword ptr [0xa1f23c] */
	M32((DWORD)(m->esi + 0xdcu)) = m->ecx;	/* 47632c: mov dword ptr [esi + 0xdc], ecx */
L_476332:
	m->edi = M32(m->esp); m->esp += 4;	/* 476332: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 476333: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 476334: pop ebx */
	m->esp = m->ebp;	/* 476335: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 476337: pop ebp */
	m->esp += 4 + 8; return;	/* 476338: ret 8 */
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
