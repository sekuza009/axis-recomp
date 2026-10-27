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

static void lift_44b670(X86 *m);
static void lift_44b6e0(X86 *m);
static void lift_44c390(X86 *m);
static void lift_44c400(X86 *m);
static void lift_44c480(X86 *m);
static void lift_44b600(X86 *m);

/* profile_44b600 (0x44b600), lifted by tools/lift.py */
static void lift_44b600(X86 *m)
{
	m->esp -= 4; M32(m->esp) = 0x44b605u; native_call(m, 0x401460u);	/* 44b600: call 0x401460 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 44b605: push 0x10 */
	M32((DWORD)(0x68039cu)) = 0x1u;	/* 44b607: mov dword ptr [0x68039c], 1 */
	m->esp -= 4; M32(m->esp) = 0x44b616u; native_call(m, 0x431560u);	/* 44b611: call 0x431560 */
	m->eax = M32((DWORD)(0x9f8eacu));	/* 44b616: mov eax, dword ptr [0x9f8eac] */
	m->ecx = M32((DWORD)(0x9f8ea8u));	/* 44b61b: mov ecx, dword ptr [0x9f8ea8] */
	{ DWORD a_ = m->eax, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44b621: add eax, 0x24 */
	{ DWORD a_ = m->ecx, b_ = 0x38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44b624: add ecx, 0x38 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 44b627: push 0x10 */
	M32((DWORD)(0x9da434u)) = 0x40a00000u;	/* 44b629: mov dword ptr [0x9da434], 0x40a00000 */
	M32((DWORD)(0x9da3d8u)) = m->eax;	/* 44b633: mov dword ptr [0x9da3d8], eax */
	M32((DWORD)(0x9da3dcu)) = m->ecx;	/* 44b638: mov dword ptr [0x9da3dc], ecx */
	M32((DWORD)(0x9f8f10u)) = 0x2u;	/* 44b63e: mov dword ptr [0x9f8f10], 2 */
	M32((DWORD)(0x90d1c4u)) = 0x1u;	/* 44b648: mov dword ptr [0x90d1c4], 1 */
	M32((DWORD)(0x9f8f34u)) = 0x0u;	/* 44b652: mov dword ptr [0x9f8f34], 0 */
	m->esp -= 4; M32(m->esp) = 0x44b661u; native_call(m, 0x43f460u);	/* 44b65c: call 0x43f460 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44b661: add esp, 8 */
	m->esp += 4 + 0; return;	/* 44b664: ret  */
}

/* profile_44b670 (0x44b670), lifted by tools/lift.py */
static void lift_44b670(X86 *m)
{
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44b670: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44b677u; native_call(m, 0x41e760u);	/* 44b672: call 0x41e760 */
	m->ecx = M32((DWORD)(0x9f8f0cu));	/* 44b677: mov ecx, dword ptr [0x9f8f0c] */
	m->eax = 0x1u;	/* 44b67d: mov eax, 1 */
	M32((DWORD)(0x90d1c4u)) = m->eax;	/* 44b682: mov dword ptr [0x90d1c4], eax */
	M32((DWORD)(0x76d42cu)) = m->eax;	/* 44b687: mov dword ptr [0x76d42c], eax */
	m->eax = M32((DWORD)(0x9f8f1cu));	/* 44b68c: mov eax, dword ptr [0x9f8f1c] */
	{ DWORD a_ = m->ecx, b_ = 0x4au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44b691: add ecx, 0x4a */
	{ DWORD a_ = m->eax, b_ = 0x9cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44b694: add eax, 0x9c */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44b699: add esp, 4 */
	M32((DWORD)(0x9f8f10u)) = 0x3u;	/* 44b69c: mov dword ptr [0x9f8f10], 3 */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 44b6a6: mov dword ptr [0x4dda44], 0 */
	M32((DWORD)(0x74de1cu)) = 0x0u;	/* 44b6b0: mov dword ptr [0x74de1c], 0 */
	M32((DWORD)(0x680bc0u)) = 0x41a00000u;	/* 44b6ba: mov dword ptr [0x680bc0], 0x41a00000 */
	M32((DWORD)(0x9da4a4u)) = 0x3e4ccccdu;	/* 44b6c4: mov dword ptr [0x9da4a4], 0x3e4ccccd */
	M32((DWORD)(0x67ef34u)) = m->eax;	/* 44b6ce: mov dword ptr [0x67ef34], eax */
	M32((DWORD)(0x67fb38u)) = m->ecx;	/* 44b6d3: mov dword ptr [0x67fb38], ecx */
	m->esp += 4 + 0; return;	/* 44b6d9: ret  */
}

/* profile_44b6e0 (0x44b6e0), lifted by tools/lift.py */
static void lift_44b6e0(X86 *m)
{
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44b6e0: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44b6e7u; native_call(m, 0x41e760u);	/* 44b6e2: call 0x41e760 */
	m->ecx = M32((DWORD)(0x9f683cu));	/* 44b6e7: mov ecx, dword ptr [0x9f683c] */
	m->eax = 0x1u;	/* 44b6ed: mov eax, 1 */
	M32((DWORD)(0x90d1c4u)) = m->eax;	/* 44b6f2: mov dword ptr [0x90d1c4], eax */
	M32((DWORD)(0x76d42cu)) = m->eax;	/* 44b6f7: mov dword ptr [0x76d42c], eax */
	m->eax = M32((DWORD)(0x9f6834u));	/* 44b6fc: mov eax, dword ptr [0x9f6834] */
	{ DWORD a_ = m->ecx, b_ = 0x4au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44b701: add ecx, 0x4a */
	{ DWORD a_ = m->eax, b_ = 0x9cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44b704: add eax, 0x9c */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44b709: add esp, 4 */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 44b70c: mov dword ptr [0x4dda44], 0 */
	M32((DWORD)(0x9f8f10u)) = 0x5u;	/* 44b716: mov dword ptr [0x9f8f10], 5 */
	M32((DWORD)(0x74de1cu)) = 0x0u;	/* 44b720: mov dword ptr [0x74de1c], 0 */
	M32((DWORD)(0x680bc0u)) = 0x41a00000u;	/* 44b72a: mov dword ptr [0x680bc0], 0x41a00000 */
	M32((DWORD)(0x9da4a4u)) = 0x3e4ccccdu;	/* 44b734: mov dword ptr [0x9da4a4], 0x3e4ccccd */
	M32((DWORD)(0x67ef34u)) = m->eax;	/* 44b73e: mov dword ptr [0x67ef34], eax */
	M32((DWORD)(0x67fb38u)) = m->ecx;	/* 44b743: mov dword ptr [0x67fb38], ecx */
	m->esp += 4 + 0; return;	/* 44b749: ret  */
}

/* profile_44c390 (0x44c390), lifted by tools/lift.py */
static void lift_44c390(X86 *m)
{
	m->eax = M32((DWORD)(0x4ded88u));	/* 44c390: mov eax, dword ptr [0x4ded88] */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 44c395: mov dword ptr [0x4dda44], 0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44c39f: test eax, eax */
	if (m->zf) goto L_44c3e5;	/* 44c3a1: je 0x44c3e5 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 44c3a3: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 44c3a8: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44c3ae: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44c3af: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44c3b5u; native_call(m, 0x44b320u);	/* 44c3b0: call 0x44b320 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c3b5: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44c3b8: sub eax, 0 */
	if (m->zf) goto L_44c3cc;	/* 44c3bb: je 0x44c3cc */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 44c3bd: dec eax */
	if (!m->zf) goto L_44c3e5;	/* 44c3be: jne 0x44c3e5 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44c3c0: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44c3c7u; native_call(m, 0x41e760u);	/* 44c3c2: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c3c7: add esp, 4 */
	goto L_44c3db;	/* 44c3ca: jmp 0x44c3db */
L_44c3cc:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44c3cc: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44c3d3u; native_call(m, 0x41e760u);	/* 44c3ce: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c3d3: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x44c3dbu; native_call(m, 0x44ba60u);	/* 44c3d6: call 0x44ba60 */
L_44c3db:
	M32((DWORD)(0x9f8f10u)) = 0x1u;	/* 44c3db: mov dword ptr [0x9f8f10], 1 */
L_44c3e5:
	m->eax = M32((DWORD)(0x4ded8cu));	/* 44c3e5: mov eax, dword ptr [0x4ded8c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44c3ea: test eax, eax */
	if (m->zf) goto L_44c3f8;	/* 44c3ec: je 0x44c3f8 */
	M32((DWORD)(0x9f8f10u)) = 0x1u;	/* 44c3ee: mov dword ptr [0x9f8f10], 1 */
L_44c3f8:
	m->esp += 4 + 0; return;	/* 44c3f8: ret  */
}

/* profile_44c400 (0x44c400), lifted by tools/lift.py */
static void lift_44c400(X86 *m)
{
	m->eax = M32((DWORD)(0x4ded88u));	/* 44c400: mov eax, dword ptr [0x4ded88] */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 44c405: mov dword ptr [0x4dda44], 0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44c40f: test eax, eax */
	if (m->zf) goto L_44c45f;	/* 44c411: je 0x44c45f */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 44c413: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 44c418: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44c41e: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44c41f: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44c425u; native_call(m, 0x44b360u);	/* 44c420: call 0x44b360 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c425: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44c428: sub eax, 0 */
	if (m->zf) goto L_44c450;	/* 44c42b: je 0x44c450 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 44c42d: dec eax */
	if (!m->zf) goto L_44c45f;	/* 44c42e: jne 0x44c45f */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44c430: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44c437u; native_call(m, 0x41e760u);	/* 44c432: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c437: add esp, 4 */
	M32((DWORD)(0x9f8f10u)) = 0x1u;	/* 44c43a: mov dword ptr [0x9f8f10], 1 */
	M32((DWORD)(0x76d42cu)) = 0x0u;	/* 44c444: mov dword ptr [0x76d42c], 0 */
	goto L_44c45f;	/* 44c44e: jmp 0x44c45f */
L_44c450:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44c450: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44c457u; native_call(m, 0x41e760u);	/* 44c452: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c457: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x44c45fu; native_call(m, 0x44bc00u);	/* 44c45a: call 0x44bc00 */
L_44c45f:
	m->eax = M32((DWORD)(0x4ded8cu));	/* 44c45f: mov eax, dword ptr [0x4ded8c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44c464: test eax, eax */
	if (m->zf) goto L_44c472;	/* 44c466: je 0x44c472 */
	M32((DWORD)(0x9f8f10u)) = 0x1u;	/* 44c468: mov dword ptr [0x9f8f10], 1 */
L_44c472:
	m->esp += 4 + 0; return;	/* 44c472: ret  */
}

/* profile_44c480 (0x44c480), lifted by tools/lift.py */
static void lift_44c480(X86 *m)
{
	m->eax = M32((DWORD)(0x4ded88u));	/* 44c480: mov eax, dword ptr [0x4ded88] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44c485: push esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44c486: test eax, eax */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 44c488: mov dword ptr [0x4dda44], 0 */
	m->esi = 0x1u;	/* 44c492: mov esi, 1 */
	if (m->zf) goto L_44c52a;	/* 44c497: je 0x44c52a */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 44c49d: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 44c4a2: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44c4a8: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44c4a9: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44c4afu; native_call(m, 0x44b3e0u);	/* 44c4aa: call 0x44b3e0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c4af: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44c4b2: cmp eax, 0xa */
	if (!m->cf && !m->zf) goto L_44c52a;	/* 44c4b5: ja 0x44c52a */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44c4b7: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x44c548u))) & 0xff) << 0);	/* 44c4b9: mov dl, byte ptr [eax + 0x44c548] */
	switch (m->edx) { case 0: goto L_44c4c6; case 1: goto L_44c4f9; case 2: goto L_44c510; default: abort(); }	/* 44c4bf: jmp dword ptr [edx*4 + 0x44c53c] */
L_44c4c6:
	{ DWORD a_ = M32((DWORD)(0x9f8d30u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44c4c6: cmp dword ptr [0x9f8d30], eax */
	if (m->zf) goto L_44c52a;	/* 44c4cc: je 0x44c52a */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 44c4ce: push 2 */
	M32((DWORD)(0x9f8d30u)) = m->eax;	/* 44c4d0: mov dword ptr [0x9f8d30], eax */
	M32((DWORD)(0x9f8d68u)) = m->esi;	/* 44c4d5: mov dword ptr [0x9f8d68], esi */
	m->esp -= 4; M32(m->esp) = 0x44c4e0u; native_call(m, 0x41e760u);	/* 44c4db: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c4e0: add esp, 4 */
	M32((DWORD)(0x9f8ee4u)) = 0x0u;	/* 44c4e3: mov dword ptr [0x9f8ee4], 0 */
	M32((DWORD)(0x9f6828u)) = 0x0u;	/* 44c4ed: mov dword ptr [0x9f6828], 0 */
	goto L_44c52a;	/* 44c4f7: jmp 0x44c52a */
L_44c4f9:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44c4f9: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44c500u; native_call(m, 0x41e760u);	/* 44c4fb: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c500: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x44c508u; native_call(m, 0x44b990u);	/* 44c503: call 0x44b990 */
	M32((DWORD)(0x9f8f10u)) = m->esi;	/* 44c508: mov dword ptr [0x9f8f10], esi */
	goto L_44c52a;	/* 44c50e: jmp 0x44c52a */
L_44c510:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44c510: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44c517u; native_call(m, 0x41e760u);	/* 44c512: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c517: add esp, 4 */
	M32((DWORD)(0x9f8f10u)) = m->esi;	/* 44c51a: mov dword ptr [0x9f8f10], esi */
	M32((DWORD)(0x76d42cu)) = 0x0u;	/* 44c520: mov dword ptr [0x76d42c], 0 */
L_44c52a:
	m->eax = M32((DWORD)(0x4ded8cu));	/* 44c52a: mov eax, dword ptr [0x4ded8c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44c52f: test eax, eax */
	if (m->zf) goto L_44c539;	/* 44c531: je 0x44c539 */
	M32((DWORD)(0x9f8f10u)) = m->esi;	/* 44c533: mov dword ptr [0x9f8f10], esi */
L_44c539:
	m->esi = M32(m->esp); m->esp += 4;	/* 44c539: pop esi */
	m->esp += 4 + 0; return;	/* 44c53a: ret  */
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
