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

static void lift_4685d0(X86 *m);
static void lift_4539f0(X86 *m);
static void lift_454740(X86 *m);
static void lift_46c580(X86 *m);
static void lift_41e7a0(X86 *m);
static void lift_463830(X86 *m);
static void lift_41ef60(X86 *m);
static void lift_46c540(X86 *m);
static void lift_43f980(X86 *m);
static void lift_41edf0(X86 *m);
static void lift_46e260(X86 *m);
static void lift_41f880(X86 *m);
static void lift_43f7f0(X86 *m);
static void lift_41f820(X86 *m);
static void lift_43f840(X86 *m);
static void lift_452de0(X86 *m);
static void lift_46e1e0(X86 *m);
static void lift_454d90(X86 *m);
static void lift_42ef30(X86 *m);
static void lift_4301e0(X86 *m);
static void lift_42f000(X86 *m);
static void lift_440c60(X86 *m);
static void lift_42b3e0(X86 *m);
static void lift_453560(X86 *m);
static void lift_4474a0(X86 *m);
static void lift_42ba40(X86 *m);
static void lift_42b830(X86 *m);
static void lift_42b590(X86 *m);
static void lift_447010(X86 *m);
static void lift_446590(X86 *m);
static void lift_446a10(X86 *m);
static void lift_43f580(X86 *m);

/* GetCurrentDirectoryA_wrap_43f580 (0x43f580), lifted by tools/lift.py */
static void lift_43f580(X86 *m)
{
	{ DWORD v_ = 0x76d224u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f580: push 0x76d224 */
	{ DWORD v_ = 0x105u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f585: push 0x105 */
	m->esp -= 4; M32(m->esp) = 0x43f590u; native_call(m, M32(0x4a9108u));	/* 43f58a: call dword ptr [0x4a9108] */
	m->esp += 4 + 0; return;	/* 43f590: ret  */
}

/* gfx_swapBuffers (0x4685d0), lifted by tools/lift.py */
static void lift_4685d0(X86 *m)
{
	m->esp -= 4; M32(m->esp) = 0x4685d6u; native_call(m, M32(0x4a91f0u));	/* 4685d0: call dword ptr [0x4a91f0] */
	m->eax = M32((DWORD)(0xa0e938u));	/* 4685d6: mov eax, dword ptr [0xa0e938] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4685db: push eax */
	m->esp -= 4; M32(m->esp) = 0x4685e2u; native_call(m, M32(0x4a9028u));	/* 4685dc: call dword ptr [0x4a9028] */
	m->esp += 4 + 0; return;	/* 4685e2: ret  */
}

/* arena_4539f0 (0x4539f0), lifted by tools/lift.py */
static void lift_4539f0(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 4539f0: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4539f4: push eax */
	{ DWORD v_ = 0x4a9678u; m->esp -= 4; M32(m->esp) = v_; }	/* 4539f5: push 0x4a9678 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4539fa: push 1 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4539fc: push 0 */
	{ DWORD v_ = 0x4a9668u; m->esp -= 4; M32(m->esp) = v_; }	/* 4539fe: push 0x4a9668 */
	m->esp -= 4; M32(m->esp) = 0x453a09u; native_call(m, M32(0x4a93b4u));	/* 453a03: call dword ptr [0x4a93b4] */
	m->esp += 4 + 0; return;	/* 453a09: ret  */
}

/* net_454740 (0x454740), lifted by tools/lift.py */
static void lift_454740(X86 *m)
{
	m->eax = M32((DWORD)(0xa0bb10u));	/* 454740: mov eax, dword ptr [0xa0bb10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454745: push eax */
	m->esp -= 4; M32(m->esp) = 0x45474cu; native_call(m, M32(0x4a9168u));	/* 454746: call dword ptr [0x4a9168] */
	m->ecx = M32((DWORD)(0xa0bf1cu));	/* 45474c: mov ecx, dword ptr [0xa0bf1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 454752: push ecx */
	m->esp -= 4; M32(m->esp) = 0x454759u; native_call(m, M32(0x4a9178u));	/* 454753: call dword ptr [0x4a9178] */
	m->esp += 4 + 0; return;	/* 454759: ret  */
}

/* FUN_0046c580 (0x46c580), lifted by tools/lift.py */
static void lift_46c580(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 46c580: mov eax, dword ptr [esp + 4] */
	m->ecx = M32((DWORD)(m->esp + 0x8u));	/* 46c584: mov ecx, dword ptr [esp + 8] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c588: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c58a: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c58b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46c592u; native_call(m, M32(0x4a9320u));	/* 46c58c: call dword ptr [0x4a9320] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c592: push eax */
	m->esp -= 4; M32(m->esp) = 0x46c599u; native_call(m, M32(0x4a9324u));	/* 46c593: call dword ptr [0x4a9324] */
	m->esp += 4 + 0; return;	/* 46c599: ret  */
}

/* profile_41e7a0 (0x41e7a0), lifted by tools/lift.py */
static void lift_41e7a0(X86 *m)
{
	m->ecx = M32((DWORD)(0x4ded18u));	/* 41e7a0: mov ecx, dword ptr [0x4ded18] */
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 41e7a6: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e7aa: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e7ac: push 0 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e7ae: push 0x10 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41e7b0: push ecx */
	M32((DWORD)(0x4df048u)) = m->eax;	/* 41e7b1: mov dword ptr [0x4df048], eax */
	m->esp -= 4; M32(m->esp) = 0x41e7bcu; native_call(m, M32(0x4a9328u));	/* 41e7b6: call dword ptr [0x4a9328] */
	m->esp += 4 + 0; return;	/* 41e7bc: ret  */
}

/* Stage_deletingDtor (0x463830), lifted by tools/lift.py */
static void lift_463830(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 463830: push esi */
	m->esi = m->ecx;	/* 463831: mov esi, ecx */
	m->esp -= 4; M32(m->esp) = 0x463838u; native_call(m, 0x46ff70u);	/* 463833: call 0x46ff70 */
	{ DWORD a_ = M8((DWORD)(m->esp + 0x8u)), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 463838: test byte ptr [esp + 8], 1 */
	if (m->zf) goto L_463848;	/* 46383d: je 0x463848 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46383f: push esi */
	m->esp -= 4; M32(m->esp) = 0x463845u; native_call(m, 0x49ef24u);	/* 463840: call 0x49ef24 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 463845: add esp, 4 */
L_463848:
	m->eax = m->esi;	/* 463848: mov eax, esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46384a: pop esi */
	m->esp += 4 + 4; return;	/* 46384b: ret 4 */
}

/* menu_vertex (0x41ef60), lifted by tools/lift.py */
static void lift_41ef60(X86 *m)
{
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x8u)));	/* 41ef60: fild dword ptr [esp + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4df014u));	/* 41ef64: fmul dword ptr [0x4df014] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 41ef6a: call 0x49ec14 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x4u)));	/* 41ef6f: fild dword ptr [esp + 4] */
	m->ecx = M32((DWORD)(0x4e045cu));	/* 41ef73: mov ecx, dword ptr [0x4e045c] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41ef79: sub ecx, eax */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x680bacu));	/* 41ef7b: fmul dword ptr [0x680bac] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41ef81: push ecx */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 41ef82: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41ef87: push eax */
	m->esp -= 4; M32(m->esp) = 0x41ef8eu; native_call(m, M32(0x4a91f4u));	/* 41ef88: call dword ptr [0x4a91f4] */
	m->esp += 4 + 0; return;	/* 41ef8e: ret  */
}

/* mci_pause (0x46c540), lifted by tools/lift.py */
static void lift_46c540(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c540: sub esp, 0xc */
	m->eax = M32((DWORD)(0xa1efc8u));	/* 46c543: mov eax, dword ptr [0xa1efc8] */
	m->ecx = M32((DWORD)(0xa1efccu));	/* 46c548: mov ecx, dword ptr [0xa1efcc] */
	m->edx = M32((DWORD)(0xa1efd0u));	/* 46c54e: mov edx, dword ptr [0xa1efd0] */
	M32((DWORD)(m->esp + 0x0u)) = m->eax;	/* 46c554: mov dword ptr [esp], eax */
	m->eax = (DWORD)(m->esp + 0x0u);	/* 46c558: lea eax, [esp] */
	M32((DWORD)(m->esp + 0x4u)) = m->ecx;	/* 46c55c: mov dword ptr [esp + 4], ecx */
	m->ecx = M32((DWORD)(0xa1efd8u));	/* 46c560: mov ecx, dword ptr [0xa1efd8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c566: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c567: push 1 */
	{ DWORD v_ = 0x809u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c569: push 0x809 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c56e: push ecx */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 46c56f: mov dword ptr [esp + 0x18], edx */
	m->esp -= 4; M32(m->esp) = 0x46c579u; native_call(m, M32(0x4a9368u));	/* 46c573: call dword ptr [0x4a9368] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c579: add esp, 0xc */
	m->esp += 4 + 0; return;	/* 46c57c: ret  */
}

/* FUN_0043f980 (0x43f980), lifted by tools/lift.py */
static void lift_43f980(X86 *m)
{
	m->eax = M32((DWORD)(0x68039cu));	/* 43f980: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43f985: test eax, eax */
	if (m->zf) goto L_43f9c0;	/* 43f987: je 0x43f9c0 */
	m->eax = M32((DWORD)(0x9dd888u));	/* 43f989: mov eax, dword ptr [0x9dd888] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43f98e: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43f98f: push eax */
	m->esp -= 4; M32(m->esp) = 0x43f996u; native_call(m, M32(0x4a92e0u));	/* 43f990: call dword ptr [0x4a92e0] */
	m->ecx = M32((DWORD)(0x9dd888u));	/* 43f996: mov ecx, dword ptr [0x9dd888] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 43f99c: inc eax */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43f99d: push eax */
	{ DWORD v_ = 0x9dc92cu; m->esp -= 4; M32(m->esp) = v_; }	/* 43f99e: push 0x9dc92c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43f9a3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43f9aau; native_call(m, M32(0x4a92e4u));	/* 43f9a4: call dword ptr [0x4a92e4] */
	m->edi = 0x9dc92cu;	/* 43f9aa: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43f9af: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43f9b2: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43f9b4: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43f9b6: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43f9b8: dec ecx */
	m->edi = M32(m->esp); m->esp += 4;	/* 43f9b9: pop edi */
	M32((DWORD)(0x9dbf10u)) = m->ecx;	/* 43f9ba: mov dword ptr [0x9dbf10], ecx */
L_43f9c0:
	m->esp += 4 + 0; return;	/* 43f9c0: ret  */
}

/* sys_messageBox (0x41edf0), lifted by tools/lift.py */
static void lift_41edf0(X86 *m)
{
	m->edx = M32((DWORD)(m->esp + 0x4u));	/* 41edf0: mov edx, dword ptr [esp + 4] */
	m->ecx = (DWORD)(m->esp + 0x8u);	/* 41edf4: lea ecx, [esp + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41edf8: push ecx */
	m->eax = (DWORD)(m->esp + 0xcu);	/* 41edf9: lea eax, [esp + 0xc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41edfd: push edx */
	{ DWORD v_ = 0x4dd0d0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41edfe: push 0x4dd0d0 */
	M32((DWORD)(0x4dd0b4u)) = m->eax;	/* 41ee03: mov dword ptr [0x4dd0b4], eax */
	m->esp -= 4; M32(m->esp) = 0x41ee0du; native_call(m, 0x49ed2eu);	/* 41ee08: call 0x49ed2e */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41ee0d: add esp, 0xc */
	M32((DWORD)(0x4dd0b4u)) = 0x0u;	/* 41ee10: mov dword ptr [0x4dd0b4], 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ee1a: push 0 */
	{ DWORD v_ = 0x4b043cu; m->esp -= 4; M32(m->esp) = v_; }	/* 41ee1c: push 0x4b043c */
	{ DWORD v_ = 0x4dd0d0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ee21: push 0x4dd0d0 */
	m->esp -= 4; M32(m->esp) = 0x41ee2cu; native_call(m, M32(0x4a9320u));	/* 41ee26: call dword ptr [0x4a9320] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41ee2c: push eax */
	m->esp -= 4; M32(m->esp) = 0x41ee33u; native_call(m, M32(0x4a9324u));	/* 41ee2d: call dword ptr [0x4a9324] */
	m->esp += 4 + 0; return;	/* 41ee33: ret  */
}

/* ptx_error (0x46e260), lifted by tools/lift.py */
static void lift_46e260(X86 *m)
{
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 46e260: push 0x4b182c */
	{ DWORD v_ = 0x4d0878u; m->esp -= 4; M32(m->esp) = v_; }	/* 46e265: push 0x4d0878 */
	m->esp -= 4; M32(m->esp) = 0x46e26fu; native_call(m, 0x49f135u);	/* 46e26a: call 0x49f135 */
	{ DWORD v_ = 0x4c6fd0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46e26f: push 0x4c6fd0 */
	{ DWORD v_ = 0x4d0878u; m->esp -= 4; M32(m->esp) = v_; }	/* 46e274: push 0x4d0878 */
	m->esp -= 4; M32(m->esp) = 0x46e27eu; native_call(m, 0x49f135u);	/* 46e279: call 0x49f135 */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 46e27e: mov ecx, dword ptr [esp + 0x18] */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 46e282: lea eax, [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46e286: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46e287: push ecx */
	{ DWORD v_ = 0x4d0878u; m->esp -= 4; M32(m->esp) = v_; }	/* 46e288: push 0x4d0878 */
	m->esp -= 4; M32(m->esp) = 0x46e292u; native_call(m, 0x49fec7u);	/* 46e28d: call 0x49fec7 */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 46e292: mov eax, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46e296: add esp, 0x1c */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46e299: test eax, eax */
	if (m->zf) goto L_46e2a3;	/* 46e29b: je 0x46e2a3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46e29d: push eax */
	m->esp -= 4; M32(m->esp) = 0x46e2a3u; native_call(m, 0x49edacu);	/* 46e29e: call 0x49edac */
L_46e2a3:
	m->esp += 4 + 0; return;	/* 46e2a3: ret  */
}

/* reg_writeEndMode (0x41f880), lifted by tools/lift.py */
static void lift_41f880(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41f880: push ecx */
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 41f881: mov eax, dword ptr [esp + 8] */
	m->ecx = (DWORD)(m->esp + 0x8u);	/* 41f885: lea ecx, [esp + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41f889: push ecx */
	{ DWORD v_ = 0xf003fu; m->esp -= 4; M32(m->esp) = v_; }	/* 41f88a: push 0xf003f */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f88f: push 0 */
	{ DWORD v_ = 0x4b0458u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f891: push 0x4b0458 */
	{ DWORD v_ = 0x80000001u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f896: push 0x80000001 */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 41f89b: mov dword ptr [esp + 0x14], eax */
	m->esp -= 4; M32(m->esp) = 0x41f8a5u; native_call(m, M32(0x4a9004u));	/* 41f89f: call dword ptr [0x4a9004] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41f8a5: test eax, eax */
	if (!m->zf) goto L_41f8c3;	/* 41f8a7: jne 0x41f8c3 */
	m->edx = (DWORD)(m->esp + 0x0u);	/* 41f8a9: lea edx, [esp] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f8ad: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41f8af: push edx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f8b0: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41f8b2: push eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 41f8b3: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = 0x4b0450u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f8b7: push 0x4b0450 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41f8bc: push eax */
	m->esp -= 4; M32(m->esp) = 0x41f8c3u; native_call(m, M32(0x4a9000u));	/* 41f8bd: call dword ptr [0x4a9000] */
L_41f8c3:
	m->ecx = M32((DWORD)(m->esp + 0x8u));	/* 41f8c3: mov ecx, dword ptr [esp + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41f8c7: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41f8ceu; native_call(m, M32(0x4a900cu));	/* 41f8c8: call dword ptr [0x4a900c] */
	m->ecx = M32(m->esp); m->esp += 4;	/* 41f8ce: pop ecx */
	m->esp += 4 + 0; return;	/* 41f8cf: ret  */
}

/* reg_writeStartMode (0x43f7f0), lifted by tools/lift.py */
static void lift_43f7f0(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43f7f0: push ecx */
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 43f7f1: mov eax, dword ptr [esp + 8] */
	m->ecx = (DWORD)(m->esp + 0x8u);	/* 43f7f5: lea ecx, [esp + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43f7f9: push ecx */
	{ DWORD v_ = 0xf003fu; m->esp -= 4; M32(m->esp) = v_; }	/* 43f7fa: push 0xf003f */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f7ff: push 0 */
	{ DWORD v_ = 0x4b0458u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f801: push 0x4b0458 */
	{ DWORD v_ = 0x80000001u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f806: push 0x80000001 */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 43f80b: mov dword ptr [esp + 0x14], eax */
	m->esp -= 4; M32(m->esp) = 0x43f815u; native_call(m, M32(0x4a9004u));	/* 43f80f: call dword ptr [0x4a9004] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43f815: test eax, eax */
	if (!m->zf) goto L_43f833;	/* 43f817: jne 0x43f833 */
	m->edx = (DWORD)(m->esp + 0x0u);	/* 43f819: lea edx, [esp] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f81d: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43f81f: push edx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f820: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43f822: push eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 43f823: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = 0x4b29dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 43f827: push 0x4b29dc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43f82c: push eax */
	m->esp -= 4; M32(m->esp) = 0x43f833u; native_call(m, M32(0x4a9000u));	/* 43f82d: call dword ptr [0x4a9000] */
L_43f833:
	m->ecx = M32((DWORD)(m->esp + 0x8u));	/* 43f833: mov ecx, dword ptr [esp + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43f837: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43f83eu; native_call(m, M32(0x4a900cu));	/* 43f838: call dword ptr [0x4a900c] */
	m->ecx = M32(m->esp); m->esp += 4;	/* 43f83e: pop ecx */
	m->esp += 4 + 0; return;	/* 43f83f: ret  */
}

/* menu_frameBegin (0x41f820), lifted by tools/lift.py */
static void lift_41f820(X86 *m)
{
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f820: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f822: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f824: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f826: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41f82eu; native_call(m, M32(0x4a91e0u));	/* 41f828: call dword ptr [0x4a91e0] */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f82e: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f833: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41f83bu; native_call(m, M32(0x4a91dcu));	/* 41f835: call dword ptr [0x4a91dc] */
	{ DWORD v_ = 0x4100u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f83b: push 0x4100 */
	m->esp -= 4; M32(m->esp) = 0x41f846u; native_call(m, M32(0x4a91e8u));	/* 41f840: call dword ptr [0x4a91e8] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f846: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f84b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f850: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f855: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41f860u; native_call(m, M32(0x4a9228u));	/* 41f85a: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0xbe2u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f860: push 0xbe2 */
	m->esp -= 4; M32(m->esp) = 0x41f86bu; native_call(m, M32(0x4a9224u));	/* 41f865: call dword ptr [0x4a9224] */
	{ DWORD v_ = 0x303u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f86b: push 0x303 */
	{ DWORD v_ = 0x302u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f870: push 0x302 */
	m->esp -= 4; M32(m->esp) = 0x41f87bu; native_call(m, M32(0x4a91ecu));	/* 41f875: call dword ptr [0x4a91ec] */
	m->esp += 4 + 0; return;	/* 41f87b: ret  */
}

/* app_registerWindowClassEx (0x43f840), lifted by tools/lift.py */
static void lift_43f840(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43f840: sub esp, 0x30 */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 43f843: mov eax, dword ptr [esp + 0x34] */
	M32((DWORD)(m->esp + 0x0u)) = 0x30u;	/* 43f847: mov dword ptr [esp], 0x30 */
	M32((DWORD)(m->esp + 0x2cu)) = 0x0u;	/* 43f84f: mov dword ptr [esp + 0x2c], 0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 43f857: mov ecx, dword ptr [eax] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 43f859: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x4u)) = m->ecx;	/* 43f85c: mov dword ptr [esp + 4], ecx */
	m->ecx = M32((DWORD)(m->eax + 0x8u));	/* 43f860: mov ecx, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x8u)) = m->edx;	/* 43f863: mov dword ptr [esp + 8], edx */
	m->edx = M32((DWORD)(m->eax + 0xcu));	/* 43f867: mov edx, dword ptr [eax + 0xc] */
	M32((DWORD)(m->esp + 0xcu)) = m->ecx;	/* 43f86a: mov dword ptr [esp + 0xc], ecx */
	m->ecx = M32((DWORD)(m->eax + 0x10u));	/* 43f86e: mov ecx, dword ptr [eax + 0x10] */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 43f871: mov dword ptr [esp + 0x10], edx */
	m->edx = M32((DWORD)(m->eax + 0x14u));	/* 43f875: mov edx, dword ptr [eax + 0x14] */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 43f878: mov dword ptr [esp + 0x14], ecx */
	m->ecx = M32((DWORD)(m->eax + 0x18u));	/* 43f87c: mov ecx, dword ptr [eax + 0x18] */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 43f87f: mov dword ptr [esp + 0x18], edx */
	m->edx = M32((DWORD)(m->eax + 0x1cu));	/* 43f883: mov edx, dword ptr [eax + 0x1c] */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 43f886: mov dword ptr [esp + 0x1c], ecx */
	m->ecx = M32((DWORD)(m->eax + 0x20u));	/* 43f88a: mov ecx, dword ptr [eax + 0x20] */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 43f88d: mov dword ptr [esp + 0x20], edx */
	m->edx = M32((DWORD)(m->eax + 0x24u));	/* 43f891: mov edx, dword ptr [eax + 0x24] */
	m->eax = (DWORD)(m->esp + 0x0u);	/* 43f894: lea eax, [esp] */
	M32((DWORD)(m->esp + 0x24u)) = m->ecx;	/* 43f898: mov dword ptr [esp + 0x24], ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43f89c: push eax */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 43f89d: mov dword ptr [esp + 0x2c], edx */
	m->esp -= 4; M32(m->esp) = 0x43f8a7u; native_call(m, M32(0x4a92e8u));	/* 43f8a1: call dword ptr [0x4a92e8] */
	{ DWORD a_ = m->eax, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43f8a7: and eax, 0xffff */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43f8ac: add esp, 0x30 */
	m->esp += 4 + 0; return;	/* 43f8af: ret  */
}

/* net_452de0 (0x452de0), lifted by tools/lift.py */
static void lift_452de0(X86 *m)
{
	m->eax = M32((DWORD)(0xa0b35cu));	/* 452de0: mov eax, dword ptr [0xa0b35c] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 452de5: push esi */
	m->esi = M32((DWORD)(m->esp + 0x8u));	/* 452de6: mov esi, dword ptr [esp + 8] */
	m->ecx = m->eax;	/* 452dea: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 452dec: shl ecx, 5 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 452def: sub ecx, eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 452df1: push esi */
	m->edx = (DWORD)(m->ecx*2 + 0xa05330u);	/* 452df2: lea edx, [ecx*2 + 0xa05330] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 452df9: push edx */
	m->esp -= 4; M32(m->esp) = 0x452e00u; native_call(m, M32(0x4a911cu));	/* 452dfa: call dword ptr [0x4a911c] */
	m->ecx = M32((DWORD)(0xa0b35cu));	/* 452e00: mov ecx, dword ptr [0xa0b35c] */
	m->edx = M32((DWORD)(m->esi + 0x2au));	/* 452e06: mov edx, dword ptr [esi + 0x2a] */
	m->eax = m->ecx;	/* 452e09: mov eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 452e0b: shl eax, 5 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 452e0e: sub eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 452e10: shl eax, 1 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 452e12: inc ecx */
	M32((DWORD)(m->eax + 0xa0535au)) = m->edx;	/* 452e13: mov dword ptr [eax + 0xa0535a], edx */
	m->edx = M32((DWORD)(m->esi + 0x26u));	/* 452e19: mov edx, dword ptr [esi + 0x26] */
	M32((DWORD)(m->eax + 0xa05356u)) = m->edx;	/* 452e1c: mov dword ptr [eax + 0xa05356], edx */
	m->edx = M32((DWORD)(m->esi + 0x22u));	/* 452e22: mov edx, dword ptr [esi + 0x22] */
	M32((DWORD)(m->eax + 0xa05352u)) = m->edx;	/* 452e25: mov dword ptr [eax + 0xa05352], edx */
	m->edx = M32((DWORD)(m->esi + 0x2eu));	/* 452e2b: mov edx, dword ptr [esi + 0x2e] */
	M32((DWORD)(m->eax + 0xa0535eu)) = m->edx;	/* 452e2e: mov dword ptr [eax + 0xa0535e], edx */
	m->edx = M32((DWORD)(m->esi + 0x36u));	/* 452e34: mov edx, dword ptr [esi + 0x36] */
	M32((DWORD)(m->eax + 0xa05366u)) = m->edx;	/* 452e37: mov dword ptr [eax + 0xa05366], edx */
	m->edx = M32((DWORD)(m->esi + 0x3au));	/* 452e3d: mov edx, dword ptr [esi + 0x3a] */
	M32((DWORD)(m->eax + 0xa0536au)) = m->edx;	/* 452e40: mov dword ptr [eax + 0xa0536a], edx */
	m->edx = M32((DWORD)(m->esi + 0x32u));	/* 452e46: mov edx, dword ptr [esi + 0x32] */
	M32((DWORD)(m->eax + 0xa05362u)) = m->edx;	/* 452e49: mov dword ptr [eax + 0xa05362], edx */
	M32((DWORD)(0xa0b35cu)) = m->ecx;	/* 452e4f: mov dword ptr [0xa0b35c], ecx */
	m->esi = M32(m->esp); m->esp += 4;	/* 452e55: pop esi */
	m->esp += 4 + 0; return;	/* 452e56: ret  */
}

/* ptx_crtlError (0x46e1e0), lifted by tools/lift.py */
static void lift_46e1e0(X86 *m)
{
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46e1e0: push edi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 46e1e1: push 0x4b182c */
	{ DWORD v_ = 0x4d0878u; m->esp -= 4; M32(m->esp) = v_; }	/* 46e1e6: push 0x4d0878 */
	m->esp -= 4; M32(m->esp) = 0x46e1f0u; native_call(m, 0x49f135u);	/* 46e1eb: call 0x49f135 */
	m->eax = M32((DWORD)(0xaef35cu));	/* 46e1f0: mov eax, dword ptr [0xaef35c] */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4d0780u));	/* 46e1f5: mov ecx, dword ptr [eax*4 + 0x4d0780] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46e1fc: push ecx */
	{ DWORD v_ = 0x4c6fc0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46e1fd: push 0x4c6fc0 */
	{ DWORD v_ = 0x4d0878u; m->esp -= 4; M32(m->esp) = v_; }	/* 46e202: push 0x4d0878 */
	m->esp -= 4; M32(m->esp) = 0x46e20cu; native_call(m, 0x49f135u);	/* 46e207: call 0x49f135 */
	m->edi = M32((DWORD)(m->esp + 0x20u));	/* 46e20c: mov edi, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46e210: add esp, 0x14 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46e213: test edi, edi */
	if (m->zf) goto L_46e249;	/* 46e215: je 0x46e249 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46e217: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46e21a: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 46e21c: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 46e21e: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 46e220: dec ecx */
	if (m->zf) goto L_46e249;	/* 46e221: je 0x46e249 */
	{ DWORD v_ = 0x4c6fb0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46e223: push 0x4c6fb0 */
	{ DWORD v_ = 0x4d0878u; m->esp -= 4; M32(m->esp) = v_; }	/* 46e228: push 0x4d0878 */
	m->esp -= 4; M32(m->esp) = 0x46e232u; native_call(m, 0x49f135u);	/* 46e22d: call 0x49f135 */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 46e232: mov eax, dword ptr [esp + 0x14] */
	m->edx = (DWORD)(m->esp + 0x18u);	/* 46e236: lea edx, [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46e23a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46e23b: push eax */
	{ DWORD v_ = 0x4d0878u; m->esp -= 4; M32(m->esp) = v_; }	/* 46e23c: push 0x4d0878 */
	m->esp -= 4; M32(m->esp) = 0x46e246u; native_call(m, 0x49fec7u);	/* 46e241: call 0x49fec7 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46e246: add esp, 0x14 */
L_46e249:
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 46e249: mov eax, dword ptr [esp + 8] */
	m->edi = M32(m->esp); m->esp += 4;	/* 46e24d: pop edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46e24e: test eax, eax */
	if (m->zf) goto L_46e258;	/* 46e250: je 0x46e258 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46e252: push eax */
	m->esp -= 4; M32(m->esp) = 0x46e258u; native_call(m, 0x49edacu);	/* 46e253: call 0x49edac */
L_46e258:
	m->esp += 4 + 0; return;	/* 46e258: ret  */
}

/* dplay_454d90 (0x454d90), lifted by tools/lift.py */
static void lift_454d90(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 454d90: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 454d91: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 454d92: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x14u));	/* 454d93: mov ebp, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 454d97: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 454d98: push edi */
	m->edi = m->ebp;	/* 454d99: mov edi, ebp */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 454d9b: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 454d9e: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 454da0: repne scasb al, byte ptr es:[edi] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 454da2: mov edx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x10u)) = 0x0u;	/* 454da6: mov dword ptr [esp + 0x10], 0 */
	m->ecx = ~m->ecx;	/* 454dae: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 454db0: dec ecx */
	m->edi = m->edx;	/* 454db1: mov edi, edx */
	m->ebx = m->ecx;	/* 454db3: mov ebx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 454db5: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 454db8: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 454dba: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 454dbc: dec ecx */
	m->eax = 0x1u;	/* 454dbd: mov eax, 1 */
	m->esi = m->ecx;	/* 454dc2: mov esi, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + 0x0u))) & 0xff) << 0);	/* 454dc4: mov cl, byte ptr [ebp] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 454dc7: sub eax, ebx */
	M8((DWORD)(m->esp + 0x1cu)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 454dc9: mov byte ptr [esp + 0x1c], cl */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 454dcd: add esi, eax */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454dcf: test esi, esi */
	if (m->zf || m->sf != m->of) goto L_454e15;	/* 454dd1: jle 0x454e15 */
	m->edi = m->edx;	/* 454dd3: mov edi, edx */
L_454dd5:
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 454dd5: mov eax, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454dd9: test eax, eax */
	if (m->zf) goto L_454df8;	/* 454ddb: je 0x454df8 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + 0x1cu))) & 0xff) << 0);	/* 454ddd: mov dl, byte ptr [esp + 0x1c] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x0u))) & 0xff) << 0);	/* 454de1: mov al, byte ptr [edi] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 454de3: cmp al, dl */
	if (!m->zf) goto L_454e07;	/* 454de5: jne 0x454e07 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 454de7: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 454de8: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 454de9: push edi */
	m->esp -= 4; M32(m->esp) = 0x454defu; native_call(m, 0x49fbe0u);	/* 454dea: call 0x49fbe0 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 454def: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454df2: test eax, eax */
	if (m->zf) goto L_454e1d;	/* 454df4: je 0x454e1d */
	goto L_454e07;	/* 454df6: jmp 0x454e07 */
L_454df8:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 454df8: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 454df9: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 454dfa: push edi */
	m->esp -= 4; M32(m->esp) = 0x454e00u; native_call(m, 0x4a8740u);	/* 454dfb: call 0x4a8740 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 454e00: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454e03: test eax, eax */
	if (m->zf) goto L_454e2d;	/* 454e05: je 0x454e2d */
L_454e07:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 454e07: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 454e0b: inc eax */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 454e0c: inc edi */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 454e0d: cmp eax, esi */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 454e0f: mov dword ptr [esp + 0x10], eax */
	if (m->sf != m->of) goto L_454dd5;	/* 454e13: jl 0x454dd5 */
L_454e15:
	m->edi = M32(m->esp); m->esp += 4;	/* 454e15: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 454e16: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 454e17: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 454e18: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 454e1a: pop ebx */
	m->ecx = M32(m->esp); m->esp += 4;	/* 454e1b: pop ecx */
	m->esp += 4 + 0; return;	/* 454e1c: ret  */
L_454e1d:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 454e1d: mov eax, dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 454e21: mov ecx, dword ptr [esp + 0x18] */
	m->edi = M32(m->esp); m->esp += 4;	/* 454e25: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 454e26: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 454e27: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 454e28: add eax, ecx */
	m->ebx = M32(m->esp); m->esp += 4;	/* 454e2a: pop ebx */
	m->ecx = M32(m->esp); m->esp += 4;	/* 454e2b: pop ecx */
	m->esp += 4 + 0; return;	/* 454e2c: ret  */
L_454e2d:
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 454e2d: mov edx, dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 454e31: mov eax, dword ptr [esp + 0x18] */
	m->edi = M32(m->esp); m->esp += 4;	/* 454e35: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 454e36: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 454e37: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 454e38: add eax, edx */
	m->ebx = M32(m->esp); m->esp += 4;	/* 454e3a: pop ebx */
	m->ecx = M32(m->esp); m->esp += 4;	/* 454e3b: pop ecx */
	m->esp += 4 + 0; return;	/* 454e3c: ret  */
}

/* app_42ef30 (0x42ef30), lifted by tools/lift.py */
static void lift_42ef30(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 42ef30: mov eax, dword ptr [esp + 4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42ef34: test eax, eax */
	if (m->zf) goto L_42eff3;	/* 42ef36: je 0x42eff3 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42ef3c: cmp eax, 1 */
	if (!m->zf) goto L_42ef5a;	/* 42ef3f: jne 0x42ef5a */
	m->eax = M32((DWORD)(0x4ded18u));	/* 42ef41: mov eax, dword ptr [0x4ded18] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42ef46: push 0 */
	{ DWORD v_ = 0x751024u; m->esp -= 4; M32(m->esp) = v_; }	/* 42ef48: push 0x751024 */
	{ DWORD v_ = 0x7511a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42ef4d: push 0x7511a4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42ef52: push eax */
	m->esp -= 4; M32(m->esp) = 0x42ef59u; native_call(m, M32(0x4a9324u));	/* 42ef53: call dword ptr [0x4a9324] */
	m->esp += 4 + 0; return;	/* 42ef59: ret  */
L_42ef5a:
	{ DWORD a_ = m->eax, b_ = 0xfffffffcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42ef5a: cmp eax, -4 */
	if (!m->zf) goto L_42ef79;	/* 42ef5d: jne 0x42ef79 */
	m->ecx = M32((DWORD)(0x4ded18u));	/* 42ef5f: mov ecx, dword ptr [0x4ded18] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42ef65: push 0 */
	{ DWORD v_ = 0x751024u; m->esp -= 4; M32(m->esp) = v_; }	/* 42ef67: push 0x751024 */
	{ DWORD v_ = 0x751224u; m->esp -= 4; M32(m->esp) = v_; }	/* 42ef6c: push 0x751224 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42ef71: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42ef78u; native_call(m, M32(0x4a9324u));	/* 42ef72: call dword ptr [0x4a9324] */
	m->esp += 4 + 0; return;	/* 42ef78: ret  */
L_42ef79:
	{ DWORD a_ = m->eax, b_ = 0xfffffffbu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42ef79: cmp eax, -5 */
	if (!m->zf) goto L_42ef98;	/* 42ef7c: jne 0x42ef98 */
	m->edx = M32((DWORD)(0x4ded18u));	/* 42ef7e: mov edx, dword ptr [0x4ded18] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42ef84: push 0 */
	{ DWORD v_ = 0x751024u; m->esp -= 4; M32(m->esp) = v_; }	/* 42ef86: push 0x751024 */
	{ DWORD v_ = 0x7512a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42ef8b: push 0x7512a4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42ef90: push edx */
	m->esp -= 4; M32(m->esp) = 0x42ef97u; native_call(m, M32(0x4a9324u));	/* 42ef91: call dword ptr [0x4a9324] */
	m->esp += 4 + 0; return;	/* 42ef97: ret  */
L_42ef98:
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42ef98: cmp eax, -1 */
	if (!m->zf) goto L_42efb6;	/* 42ef9b: jne 0x42efb6 */
	m->eax = M32((DWORD)(0x4ded18u));	/* 42ef9d: mov eax, dword ptr [0x4ded18] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42efa2: push 0 */
	{ DWORD v_ = 0x751024u; m->esp -= 4; M32(m->esp) = v_; }	/* 42efa4: push 0x751024 */
	{ DWORD v_ = 0x751324u; m->esp -= 4; M32(m->esp) = v_; }	/* 42efa9: push 0x751324 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42efae: push eax */
	m->esp -= 4; M32(m->esp) = 0x42efb5u; native_call(m, M32(0x4a9324u));	/* 42efaf: call dword ptr [0x4a9324] */
	m->esp += 4 + 0; return;	/* 42efb5: ret  */
L_42efb6:
	{ DWORD a_ = m->eax, b_ = 0xfffffffeu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42efb6: cmp eax, -2 */
	if (!m->zf) goto L_42efd5;	/* 42efb9: jne 0x42efd5 */
	m->ecx = M32((DWORD)(0x4ded18u));	/* 42efbb: mov ecx, dword ptr [0x4ded18] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42efc1: push 0 */
	{ DWORD v_ = 0x751024u; m->esp -= 4; M32(m->esp) = v_; }	/* 42efc3: push 0x751024 */
	{ DWORD v_ = 0x7513a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42efc8: push 0x7513a4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42efcd: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42efd4u; native_call(m, M32(0x4a9324u));	/* 42efce: call dword ptr [0x4a9324] */
	m->esp += 4 + 0; return;	/* 42efd4: ret  */
L_42efd5:
	{ DWORD a_ = m->eax, b_ = 0xfffffffdu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42efd5: cmp eax, -3 */
	if (!m->zf) goto L_42eff3;	/* 42efd8: jne 0x42eff3 */
	m->edx = M32((DWORD)(0x4ded18u));	/* 42efda: mov edx, dword ptr [0x4ded18] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42efe0: push 0 */
	{ DWORD v_ = 0x751024u; m->esp -= 4; M32(m->esp) = v_; }	/* 42efe2: push 0x751024 */
	{ DWORD v_ = 0x751424u; m->esp -= 4; M32(m->esp) = v_; }	/* 42efe7: push 0x751424 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42efec: push edx */
	m->esp -= 4; M32(m->esp) = 0x42eff3u; native_call(m, M32(0x4a9324u));	/* 42efed: call dword ptr [0x4a9324] */
L_42eff3:
	m->esp += 4 + 0; return;	/* 42eff3: ret  */
}

/* timer_now (0x4301e0), lifted by tools/lift.py */
static void lift_4301e0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4301e0: sub esp, 8 */
	m->eax = (DWORD)(m->esp + 0x0u);	/* 4301e3: lea eax, [esp] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4301e7: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4301e8: push eax */
	m->esp -= 4; M32(m->esp) = 0x4301efu; native_call(m, M32(0x4a9140u));	/* 4301e9: call dword ptr [0x4a9140] */
	m->esi = M32((DWORD)(0x67ef1cu));	/* 4301ef: mov esi, dword ptr [0x67ef1c] */
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 4301f5: mov eax, dword ptr [esp + 8] */
	m->edx = M32((DWORD)(m->esp + 0x4u));	/* 4301f9: mov edx, dword ptr [esp + 4] */
	m->ecx = 0x20u;	/* 4301fd: mov ecx, 0x20 */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 430202: sub ecx, esi */
	M32((DWORD)(0x5ae9ccu)) = m->eax;	/* 430204: mov dword ptr [0x5ae9cc], eax */
	{ DWORD a_ = m->eax, c_ = (((m->ecx >> 0) & 0xff)) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 430209: shl eax, cl */
	m->ecx = m->esi;	/* 43020b: mov ecx, esi */
	M32((DWORD)(0x5ae9c8u)) = m->edx;	/* 43020d: mov dword ptr [0x5ae9c8], edx */
	{ DWORD a_ = m->edx, c_ = (((m->ecx >> 0) & 0xff)) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 430213: shr edx, cl */
	m->ecx = M32((DWORD)(0x4b1048u));	/* 430215: mov ecx, dword ptr [0x4b1048] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43021b: or eax, edx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43021d: xor edx, edx */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43021f: cmp ecx, edx */
	if (m->zf) goto L_430239;	/* 430221: je 0x430239 */
	FPUSH((long double)*(const double *)(DWORD)(0x9db980u));	/* 430223: fld qword ptr [0x9db980] */
	M32((DWORD)(0x9dbf08u)) = m->eax;	/* 430229: mov dword ptr [0x9dbf08], eax */
	M32((DWORD)(0x4b1048u)) = m->edx;	/* 43022e: mov dword ptr [0x4b1048], edx */
	m->esi = M32(m->esp); m->esp += 4;	/* 430234: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 430235: add esp, 8 */
	m->esp += 4 + 0; return;	/* 430238: ret  */
L_430239:
	m->ecx = M32((DWORD)(0x9dbf08u));	/* 430239: mov ecx, dword ptr [0x9dbf08] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43023f: cmp eax, ecx */
	if (!m->cf && !m->zf) goto L_43025f;	/* 430241: ja 0x43025f */
	m->esi = m->ecx;	/* 430243: mov esi, ecx */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 430245: sub esi, eax */
	{ DWORD a_ = m->esi, b_ = 0x10000000u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 430247: cmp esi, 0x10000000 */
	if (!m->cf) goto L_43025f;	/* 43024d: jae 0x43025f */
	FPUSH((long double)*(const double *)(DWORD)(0x9db980u));	/* 43024f: fld qword ptr [0x9db980] */
	M32((DWORD)(0x9dbf08u)) = m->eax;	/* 430255: mov dword ptr [0x9dbf08], eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 43025a: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43025b: add esp, 8 */
	m->esp += 4 + 0; return;	/* 43025e: ret  */
L_43025f:
	m->esi = m->eax;	/* 43025f: mov esi, eax */
	M32((DWORD)(m->esp + 0x8u)) = m->edx;	/* 430261: mov dword ptr [esp + 8], edx */
	{ DWORD a_ = m->esi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 430265: sub esi, ecx */
	M32((DWORD)(0x9dbf08u)) = m->eax;	/* 430267: mov dword ptr [0x9dbf08], eax */
	M32((DWORD)(m->esp + 0x4u)) = m->esi;	/* 43026c: mov dword ptr [esp + 4], esi */
	FPUSH((long double)*(const long long *)(DWORD)(m->esp + 0x4u));	/* 430270: fild qword ptr [esp + 4] */
	ST(0) = ST(0) * (long double)*(const double *)(DWORD)(0x4ded58u);	/* 430274: fmul qword ptr [0x4ded58] */
	ST(0) = ST(0) + (long double)*(const double *)(DWORD)(0x9db980u);	/* 43027a: fadd qword ptr [0x9db980] */
	FCOM(ST(0), (long double)*(const double *)(DWORD)(0x9db988u));	/* 430280: fcom qword ptr [0x9db988] */
	MDBL((DWORD)(0x9db980u)) = (double)ST(0);	/* 430286: fst qword ptr [0x9db980] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 43028c: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 43028e: test ah, 0x40 */
	if (m->zf) goto L_4302b1;	/* 430291: je 0x4302b1 */
	m->eax = M32((DWORD)(0x9dbf00u));	/* 430293: mov eax, dword ptr [0x9dbf00] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 430298: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x186a0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 430299: cmp eax, 0x186a0 */
	M32((DWORD)(0x9dbf00u)) = m->eax;	/* 43029e: mov dword ptr [0x9dbf00], eax */
	if (m->zf || m->sf != m->of) goto L_4302b7;	/* 4302a3: jle 0x4302b7 */
	ST(0) = ST(0) + (long double)*(const double *)(DWORD)(0x4a94e0u);	/* 4302a5: fadd qword ptr [0x4a94e0] */
	MDBL((DWORD)(0x9db980u)) = (double)ST(0);	/* 4302ab: fst qword ptr [0x9db980] */
L_4302b1:
	M32((DWORD)(0x9dbf00u)) = m->edx;	/* 4302b1: mov dword ptr [0x9dbf00], edx */
L_4302b7:
	MDBL((DWORD)(0x9db988u)) = (double)ST(0);	/* 4302b7: fst qword ptr [0x9db988] */
	m->esi = M32(m->esp); m->esp += 4;	/* 4302bd: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4302be: add esp, 8 */
	m->esp += 4 + 0; return;	/* 4302c1: ret  */
}

/* gfx_setPixelFormat (0x42f000), lifted by tools/lift.py */
static void lift_42f000(X86 *m)
{
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x9dbefcu))) & 0xff) << 0);	/* 42f000: mov cl, byte ptr [0x9dbefc] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42f006: push ebx */
	m->eax = (m->eax & ~(0xffu << 0)) | (((0x1u) & 0xff) << 0);	/* 42f007: mov al, 1 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 42f009: xor ebx, ebx */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42f00b: test al, cl */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42f00d: push esi */
	if (!m->zf) goto L_42f0aa;	/* 42f00e: jne 0x42f0aa */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->ecx = (m->ecx & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 42f014: or cl, al */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x83a9c4u))) & 0xff) << 0);	/* 42f016: mov al, byte ptr [0x83a9c4] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), r_ = (a_ + 1) & 0xffu; FLAGS(r_, 8); m->of = (r_ == 0x80u); m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 42f01b: inc al */
	M8((DWORD)(0x9dbefcu)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 42f01d: mov byte ptr [0x9dbefc], cl */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffu; m->cf = (int)((a_ >> (8 - c_)) & 1); FLAGS(r_, 8); m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); } }	/* 42f023: shl al, 4 */
	M8((DWORD)(0x4b1029u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 42f026: mov byte ptr [0x4b1029], al */
	M8((DWORD)(0x4b102au)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 42f02b: mov byte ptr [0x4b102a], bl */
	M8((DWORD)(0x4b102bu)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 42f031: mov byte ptr [0x4b102b], bl */
	M8((DWORD)(0x4b102cu)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 42f037: mov byte ptr [0x4b102c], bl */
	M8((DWORD)(0x4b102du)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 42f03d: mov byte ptr [0x4b102d], bl */
	M8((DWORD)(0x4b102eu)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 42f043: mov byte ptr [0x4b102e], bl */
	M8((DWORD)(0x4b102fu)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 42f049: mov byte ptr [0x4b102f], bl */
	M8((DWORD)(0x4b1030u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 42f04f: mov byte ptr [0x4b1030], bl */
	M8((DWORD)(0x4b1031u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 42f055: mov byte ptr [0x4b1031], bl */
	M8((DWORD)(0x4b1032u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 42f05b: mov byte ptr [0x4b1032], bl */
	M8((DWORD)(0x4b1033u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 42f061: mov byte ptr [0x4b1033], bl */
	M8((DWORD)(0x4b1034u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 42f067: mov byte ptr [0x4b1034], bl */
	M8((DWORD)(0x4b1035u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 42f06d: mov byte ptr [0x4b1035], bl */
	M8((DWORD)(0x4b1036u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 42f073: mov byte ptr [0x4b1036], bl */
	M8((DWORD)(0x4b1037u)) = (BYTE)(0x10u);	/* 42f079: mov byte ptr [0x4b1037], 0x10 */
	M8((DWORD)(0x4b1038u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 42f080: mov byte ptr [0x4b1038], bl */
	M8((DWORD)(0x4b1039u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 42f086: mov byte ptr [0x4b1039], bl */
	M8((DWORD)(0x4b103au)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 42f08c: mov byte ptr [0x4b103a], bl */
	M8((DWORD)(0x4b103bu)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 42f092: mov byte ptr [0x4b103b], bl */
	M32((DWORD)(0x4b103cu)) = m->ebx;	/* 42f098: mov dword ptr [0x4b103c], ebx */
	M32((DWORD)(0x4b1040u)) = m->ebx;	/* 42f09e: mov dword ptr [0x4b1040], ebx */
	M32((DWORD)(0x4b1044u)) = m->ebx;	/* 42f0a4: mov dword ptr [0x4b1044], ebx */
L_42f0aa:
	m->esi = M32((DWORD)(m->esp + 0xcu));	/* 42f0aa: mov esi, dword ptr [esp + 0xc] */
	{ DWORD v_ = 0x4b1020u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f0ae: push 0x4b1020 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42f0b3: push esi */
	m->esp -= 4; M32(m->esp) = 0x42f0bau; native_call(m, M32(0x4a902cu));	/* 42f0b4: call dword ptr [0x4a902c] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42f0ba: cmp eax, ebx */
	if (!m->zf) goto L_42f0c3;	/* 42f0bc: jne 0x42f0c3 */
	m->esi = M32(m->esp); m->esp += 4;	/* 42f0be: pop esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42f0bf: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 42f0c1: pop ebx */
	m->esp += 4 + 0; return;	/* 42f0c2: ret  */
L_42f0c3:
	{ DWORD a_ = M8((DWORD)(0x4b1024u)), b_ = 0x80u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42f0c3: test byte ptr [0x4b1024], 0x80 */
	if (m->zf) goto L_42f0d1;	/* 42f0ca: je 0x42f0d1 */
	m->esi = M32(m->esp); m->esp += 4;	/* 42f0cc: pop esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42f0cd: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 42f0cf: pop ebx */
	m->esp += 4 + 0; return;	/* 42f0d0: ret  */
L_42f0d1:
	{ DWORD v_ = 0x4b1020u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f0d1: push 0x4b1020 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42f0d6: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42f0d7: push esi */
	m->esp -= 4; M32(m->esp) = 0x42f0deu; native_call(m, M32(0x4a9030u));	/* 42f0d8: call dword ptr [0x4a9030] */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 42f0de: neg eax */
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42f0e0: sbb eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 42f0e2: pop esi */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 42f0e3: neg eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 42f0e5: pop ebx */
	m->esp += 4 + 0; return;	/* 42f0e6: ret  */
}

/* autoplay_listFiles (0x440c60), lifted by tools/lift.py */
static void lift_440c60(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x118u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 440c60: sub esp, 0x118 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 440c66: push ebx */
	{ DWORD v_ = 0x4b2a8cu; m->esp -= 4; M32(m->esp) = v_; }	/* 440c67: push 0x4b2a8c */
	m->esp -= 4; M32(m->esp) = 0x440c71u; native_call(m, 0x49f8a6u);	/* 440c6c: call 0x49f8a6 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 440c71: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 440c74: test eax, eax */
	if (!m->zf) goto L_440d66;	/* 440c76: jne 0x440d66 */
	m->eax = (DWORD)(m->esp + 0x4u);	/* 440c7c: lea eax, [esp + 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 440c80: push eax */
	{ DWORD v_ = 0x4b2a84u; m->esp -= 4; M32(m->esp) = v_; }	/* 440c81: push 0x4b2a84 */
	m->esp -= 4; M32(m->esp) = 0x440c8bu; native_call(m, 0x49f694u);	/* 440c86: call 0x49f694 */
	m->ebx = m->eax;	/* 440c8b: mov ebx, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 440c8d: add esp, 8 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 440c90: test ebx, ebx */
	if (m->sf == m->of) goto L_440ca9;	/* 440c92: jge 0x440ca9 */
	{ DWORD v_ = 0x4b2a80u; m->esp -= 4; M32(m->esp) = v_; }	/* 440c94: push 0x4b2a80 */
	m->esp -= 4; M32(m->esp) = 0x440c9eu; native_call(m, 0x49f8a6u);	/* 440c99: call 0x49f8a6 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 440c9e: add esp, 4 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 440ca1: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x118u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 440ca2: add esp, 0x118 */
	m->esp += 4 + 0; return;	/* 440ca8: ret  */
L_440ca9:
	m->edx = M32((DWORD)(0x9dd928u));	/* 440ca9: mov edx, dword ptr [0x9dd928] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 440caf: push ebp */
	m->ecx = m->edx;	/* 440cb0: mov ecx, edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 440cb2: push esi */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 440cb3: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 440cb6: add ecx, edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 440cb8: push edi */
	m->edi = (DWORD)(m->esp + 0x24u);	/* 440cb9: lea edi, [esp + 0x24] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 440cbd: xor eax, eax */
	m->ebp = (DWORD)(m->ecx*4 + 0x9dda88u);	/* 440cbf: lea ebp, [ecx*4 + 0x9dda88] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 440cc6: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 440cc9: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 440ccb: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 440ccd: sub edi, ecx */
	m->eax = m->ecx;	/* 440ccf: mov eax, ecx */
	m->esi = m->edi;	/* 440cd1: mov esi, edi */
	m->edi = m->ebp;	/* 440cd3: mov edi, ebp */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 440cd5: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 440cd8: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 440cda: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 440cdc: and ecx, 3 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 440cdf: inc edx */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 440ce0: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 440ce2: lea ecx, [esp + 0x10] */
	M32((DWORD)(0x9dd928u)) = m->edx;	/* 440ce6: mov dword ptr [0x9dd928], edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 440cec: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 440ced: push ebx */
	m->esp -= 4; M32(m->esp) = 0x440cf3u; native_call(m, 0x49f75eu);	/* 440cee: call 0x49f75e */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 440cf3: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 440cf6: test eax, eax */
	if (!m->zf) goto L_440d50;	/* 440cf8: jne 0x440d50 */
L_440cfa:
	m->edx = M32((DWORD)(0x9dd928u));	/* 440cfa: mov edx, dword ptr [0x9dd928] */
	m->edi = (DWORD)(m->esp + 0x24u);	/* 440d00: lea edi, [esp + 0x24] */
	m->eax = m->edx;	/* 440d04: mov eax, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 440d06: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 440d09: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 440d0c: add eax, edx */
	m->ebp = (DWORD)(m->eax*4 + 0x9dda88u);	/* 440d0e: lea ebp, [eax*4 + 0x9dda88] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 440d15: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 440d17: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 440d19: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 440d1b: sub edi, ecx */
	m->eax = m->ecx;	/* 440d1d: mov eax, ecx */
	m->esi = m->edi;	/* 440d1f: mov esi, edi */
	m->edi = m->ebp;	/* 440d21: mov edi, ebp */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 440d23: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 440d26: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 440d28: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 440d2a: and ecx, 3 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 440d2d: inc edx */
	{ DWORD a_ = m->edx, b_ = 0x3feu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 440d2e: cmp edx, 0x3fe */
	M32((DWORD)(0x9dd928u)) = m->edx;	/* 440d34: mov dword ptr [0x9dd928], edx */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 440d3a: rep movsb byte ptr es:[edi], byte ptr [esi] */
	if (!m->zf && m->sf == m->of) goto L_440d50;	/* 440d3c: jg 0x440d50 */
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 440d3e: lea ecx, [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 440d42: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 440d43: push ebx */
	m->esp -= 4; M32(m->esp) = 0x440d49u; native_call(m, 0x49f75eu);	/* 440d44: call 0x49f75e */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 440d49: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 440d4c: test eax, eax */
	if (m->zf) goto L_440cfa;	/* 440d4e: je 0x440cfa */
L_440d50:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 440d50: push ebx */
	m->esp -= 4; M32(m->esp) = 0x440d56u; native_call(m, 0x49f823u);	/* 440d51: call 0x49f823 */
	{ DWORD v_ = 0x4b2a80u; m->esp -= 4; M32(m->esp) = v_; }	/* 440d56: push 0x4b2a80 */
	m->esp -= 4; M32(m->esp) = 0x440d60u; native_call(m, 0x49f8a6u);	/* 440d5b: call 0x49f8a6 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 440d60: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 440d63: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 440d64: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 440d65: pop ebp */
L_440d66:
	m->ebx = M32(m->esp); m->esp += 4;	/* 440d66: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x118u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 440d67: add esp, 0x118 */
	m->esp += 4 + 0; return;	/* 440d6d: ret  */
}

/* data_loadMessages (0x42b3e0), lifted by tools/lift.py */
static void lift_42b3e0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x18cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42b3e0: sub esp, 0x18c */
	m->ecx = 0x41u;	/* 42b3e6: mov ecx, 0x41 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42b3eb: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x84u);	/* 42b3ed: lea edx, [esp + 0x84] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42b3f4: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42b3f5: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42b3f6: push edi */
	m->edi = (DWORD)(m->esp + 0x90u);	/* 42b3f7: lea edi, [esp + 0x90] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 42b3fe: rep stosd dword ptr es:[edi], eax */
	M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1;	/* 42b400: stosb byte ptr es:[edi], al */
	m->edi = 0x9dae7cu;	/* 42b401: mov edi, 0x9dae7c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42b406: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42b409: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42b40b: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42b40d: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42b40f: sub edi, ecx */
	m->eax = m->ecx;	/* 42b411: mov eax, ecx */
	m->esi = m->edi;	/* 42b413: mov esi, edi */
	m->edi = m->edx;	/* 42b415: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x90u);	/* 42b417: lea edx, [esp + 0x90] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42b41e: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42b421: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 42b423: mov ecx, eax */
	m->eax = M32((DWORD)(0x9dae74u));	/* 42b425: mov eax, dword ptr [0x9dae74] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42b42a: and ecx, 3 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42b42d: cmp eax, 1 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 42b430: rep movsb byte ptr es:[edi], byte ptr [esi] */
	if (!m->zf) goto L_42b47b;	/* 42b432: jne 0x42b47b */
	m->edi = 0x4b1430u;	/* 42b434: mov edi, 0x4b1430 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42b439: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42b43c: xor eax, eax */
	{ DWORD v_ = 0x4ad5e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b43e: push 0x4ad5e0 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42b443: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42b445: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42b447: sub edi, ecx */
	m->esi = m->edi;	/* 42b449: mov esi, edi */
	m->ebx = m->ecx;	/* 42b44b: mov ebx, ecx */
	m->edi = m->edx;	/* 42b44d: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42b44f: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42b452: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 42b454: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 42b456: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42b457: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42b45a: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebx;	/* 42b45c: mov ecx, ebx */
	m->eax = (DWORD)(m->esp + 0x94u);	/* 42b45e: lea eax, [esp + 0x94] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42b465: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42b468: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 42b469: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x42b470u; native_call(m, 0x49e9cau);	/* 42b46b: call 0x49e9ca */
	m->esi = m->eax;	/* 42b470: mov esi, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42b472: add esp, 8 */
	M32((DWORD)(m->esp + 0xcu)) = m->esi;	/* 42b475: mov dword ptr [esp + 0xc], esi */
	goto L_42b4c0;	/* 42b479: jmp 0x42b4c0 */
L_42b47b:
	m->edi = 0x4b1424u;	/* 42b47b: mov edi, 0x4b1424 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42b480: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42b483: xor eax, eax */
	{ DWORD v_ = 0x4ad5e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b485: push 0x4ad5e0 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42b48a: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42b48c: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42b48e: sub edi, ecx */
	m->esi = m->edi;	/* 42b490: mov esi, edi */
	m->ebx = m->ecx;	/* 42b492: mov ebx, ecx */
	m->edi = m->edx;	/* 42b494: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42b496: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42b499: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 42b49b: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 42b49d: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42b49e: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42b4a1: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebx;	/* 42b4a3: mov ecx, ebx */
	m->eax = (DWORD)(m->esp + 0x94u);	/* 42b4a5: lea eax, [esp + 0x94] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42b4ac: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42b4af: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 42b4b0: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x42b4b7u; native_call(m, 0x49e9cau);	/* 42b4b2: call 0x49e9ca */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42b4b7: add esp, 8 */
	M32((DWORD)(m->esp + 0xcu)) = m->eax;	/* 42b4ba: mov dword ptr [esp + 0xc], eax */
	m->esi = m->eax;	/* 42b4be: mov esi, eax */
L_42b4c0:
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 42b4c0: xor ebx, ebx */
	{ DWORD a_ = m->esi, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42b4c2: cmp esi, ebx */
	if (!m->zf) goto L_42b4df;	/* 42b4c4: jne 0x42b4df */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42b4c6: push ebx */
	{ DWORD v_ = 0x4b141cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42b4c7: push 0x4b141c */
	{ DWORD v_ = 0x4b13f8u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b4cc: push 0x4b13f8 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42b4d1: push ebx */
	m->esp -= 4; M32(m->esp) = 0x42b4d8u; native_call(m, M32(0x4a9324u));	/* 42b4d2: call dword ptr [0x4a9324] */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 42b4d8: push -1 */
	m->esp -= 4; M32(m->esp) = 0x42b4dfu; native_call(m, 0x49edacu);	/* 42b4da: call 0x49edac */
L_42b4df:
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42b4df: push ebp */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 42b4e0: xor ebp, ebp */
L_42b4e2:
	m->ecx = 0x20u;	/* 42b4e2: mov ecx, 0x20 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42b4e7: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x14u);	/* 42b4e9: lea edi, [esp + 0x14] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42b4ed: push esi */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 42b4ee: rep stosd dword ptr es:[edi], eax */
	m->ecx = (DWORD)(m->esp + 0x18u);	/* 42b4f0: lea ecx, [esp + 0x18] */
	{ DWORD v_ = 0x80u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b4f4: push 0x80 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42b4f9: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42b4ffu; native_call(m, 0x49ecd7u);	/* 42b4fa: call 0x49ecd7 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42b4ff: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42b502: test eax, eax */
	if (m->zf) goto L_42b575;	/* 42b504: je 0x42b575 */
	{ DWORD a_ = M8((DWORD)(m->esp + 0x14u)), b_ = 0x2fu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42b506: cmp byte ptr [esp + 0x14], 0x2f */
	if (!m->zf) goto L_42b514;	/* 42b50b: jne 0x42b514 */
	{ DWORD a_ = M8((DWORD)(m->esp + 0x15u)), b_ = 0x2fu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42b50d: cmp byte ptr [esp + 0x15], 0x2f */
	if (m->zf) goto L_42b4e2;	/* 42b512: je 0x42b4e2 */
L_42b514:
	m->edi = (DWORD)(m->esp + 0x14u);	/* 42b514: lea edi, [esp + 0x14] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42b518: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42b51b: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42b51d: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42b51f: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 42b521: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42b522: cmp ecx, 1 */
	if (m->zf) goto L_42b4e2;	/* 42b525: je 0x42b4e2 */
	m->edi = (DWORD)(m->esp + 0x14u);	/* 42b527: lea edi, [esp + 0x14] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42b52b: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42b52e: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42b530: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42b532: sub edi, ecx */
	m->edx = (DWORD)(m->ebp + 0x74de24u);	/* 42b534: lea edx, [ebp + 0x74de24] */
	m->eax = m->ecx;	/* 42b53a: mov eax, ecx */
	m->esi = m->edi;	/* 42b53c: mov esi, edi */
	m->edi = m->edx;	/* 42b53e: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42b540: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42b543: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 42b545: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42b547: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42b549: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 42b54c: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = m->edx;	/* 42b54e: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42b550: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42b553: repne scasb al, byte ptr es:[edi] */
	m->esi = M32((DWORD)(m->esp + 0x10u));	/* 42b555: mov esi, dword ptr [esp + 0x10] */
	m->ecx = ~m->ecx;	/* 42b559: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 42b55b: dec ecx */
	{ DWORD a_ = m->ebp, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 42b55c: add ebp, 0x80 */
	M8((DWORD)(m->ecx + m->ebp*1 + 0x74dda3u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 42b562: mov byte ptr [ecx + ebp + 0x74dda3], bl */
	M8((DWORD)(m->ecx + m->ebp*1 + 0x74dda4u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 42b569: mov byte ptr [ecx + ebp + 0x74dda4], bl */
	goto L_42b4e2;	/* 42b570: jmp 0x42b4e2 */
L_42b575:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42b575: push esi */
	m->esp -= 4; M32(m->esp) = 0x42b57bu; native_call(m, 0x49e7e0u);	/* 42b576: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42b57b: add esp, 4 */
	m->ebp = M32(m->esp); m->esp += 4;	/* 42b57e: pop ebp */
	m->edi = M32(m->esp); m->esp += 4;	/* 42b57f: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 42b580: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 42b581: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x18cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42b582: add esp, 0x18c */
	m->esp += 4 + 0; return;	/* 42b588: ret  */
}

/* dplay_enumSessionsCallback (0x453560), lifted by tools/lift.py */
static void lift_453560(X86 *m)
{
	m->eax = M32((DWORD)(0xa0b418u));	/* 453560: mov eax, dword ptr [0xa0b418] */
	{ DWORD a_ = m->esp, b_ = 0x8cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453565: sub esp, 0x8c */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45356b: cmp eax, 1 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45356e: push ebx */
	m->ebx = M32((DWORD)(m->esp + 0x94u));	/* 45356f: mov ebx, dword ptr [esp + 0x94] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 453576: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 453577: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 453578: push edi */
	if (!m->zf) goto L_45358e;	/* 453579: jne 0x45358e */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45357b: test ebx, ebx */
	if (!m->zf) goto L_4535a5;	/* 45357d: jne 0x4535a5 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45357f: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 453581: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 453582: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 453583: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 453584: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x8cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453585: add esp, 0x8c */
	m->esp += 4 + 16; return;	/* 45358b: ret 0x10 */
L_45358e:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45358e: test eax, eax */
	if (!m->zf) goto L_4535a5;	/* 453590: jne 0x4535a5 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 453592: test ebx, ebx */
	if (!m->zf) goto L_4535a5;	/* 453594: jne 0x4535a5 */
L_453596:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 453596: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 453598: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 453599: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 45359a: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 45359b: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x8cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45359c: add esp, 0x8c */
	m->esp += 4 + 16; return;	/* 4535a2: ret 0x10 */
L_4535a5:
	m->ecx = 0x21u;	/* 4535a5: mov ecx, 0x21 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4535aa: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x14u);	/* 4535ac: lea edi, [esp + 0x14] */
	m->ebp = (DWORD)(m->ebx + 0x8u);	/* 4535b0: lea ebp, [ebx + 8] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4535b3: rep stosd dword ptr es:[edi], eax */
	M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1;	/* 4535b5: stosb byte ptr es:[edi], al */
	m->ecx = 0x4u;	/* 4535b6: mov ecx, 4 */
	m->edi = 0x4aae70u;	/* 4535bb: mov edi, 0x4aae70 */
	m->esi = m->ebp;	/* 4535c0: mov esi, ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4535c2: xor eax, eax */
	while (m->ecx) { { DWORD a_ = M32(m->esi), b_ = M32(m->edi), r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); m->esi += 4; m->edi += 4; } m->ecx--; if (!m->zf) break; }	/* 4535c4: repe cmpsd dword ptr [esi], dword ptr es:[edi] */
	if (m->zf) goto L_453701;	/* 4535c6: je 0x453701 */
	m->ecx = M32((DWORD)(0xa0b41cu));	/* 4535cc: mov ecx, dword ptr [0xa0b41c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4535d2: test ecx, ecx */
	if (m->zf || m->sf != m->of) goto L_453609;	/* 4535d4: jle 0x453609 */
	M32((DWORD)(m->esp + 0x10u)) = 0xa0b474u;	/* 4535d6: mov dword ptr [esp + 0x10], 0xa0b474 */
L_4535de:
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 4535de: mov edx, dword ptr [esp + 0x10] */
	m->ecx = 0x4u;	/* 4535e2: mov ecx, 4 */
	m->esi = m->ebp;	/* 4535e7: mov esi, ebp */
	m->edi = M32((DWORD)(m->edx + 0x0u));	/* 4535e9: mov edi, dword ptr [edx] */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4535eb: add edi, ecx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4535ed: xor edx, edx */
	while (m->ecx) { { DWORD a_ = M32(m->esi), b_ = M32(m->edi), r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); m->esi += 4; m->edi += 4; } m->ecx--; if (!m->zf) break; }	/* 4535ef: repe cmpsd dword ptr [esi], dword ptr es:[edi] */
	if (m->zf) goto L_453596;	/* 4535f1: je 0x453596 */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 4535f3: mov edx, dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(0xa0b41cu));	/* 4535f7: mov ecx, dword ptr [0xa0b41c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4535fd: inc eax */
	{ DWORD a_ = m->edx, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4535fe: add edx, 8 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 453601: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 453603: mov dword ptr [esp + 0x10], edx */
	if (m->sf != m->of) goto L_4535de;	/* 453607: jl 0x4535de */
L_453609:
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 453609: push 0x10 */
	{ DWORD v_ = 0x42u; m->esp -= 4; M32(m->esp) = v_; }	/* 45360b: push 0x42 */
	m->esp -= 4; M32(m->esp) = 0x453613u; native_call(m, M32(0x4a9070u));	/* 45360d: call dword ptr [0x4a9070] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 453613: push eax */
	m->esp -= 4; M32(m->esp) = 0x45361au; native_call(m, M32(0x4a9198u));	/* 453614: call dword ptr [0x4a9198] */
	{ DWORD v_ = 0x46u; m->esp -= 4; M32(m->esp) = v_; }	/* 45361a: push 0x46 */
	m->ecx = (DWORD)(m->esp + 0x46u);	/* 45361c: lea ecx, [esp + 0x46] */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 453620: mov dword ptr [esp + 0x18], eax */
	m->eax = M32((DWORD)(m->ebx + 0x30u));	/* 453624: mov eax, dword ptr [ebx + 0x30] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 453627: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 453628: push ecx */
	m->esp -= 4; M32(m->esp) = 0x45362eu; native_call(m, 0x49ea80u);	/* 453629: call 0x49ea80 */
	m->edx = M32((DWORD)(m->ebx + 0x2cu));	/* 45362e: mov edx, dword ptr [ebx + 0x2c] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 453631: mov ecx, dword ptr [esp + 0x20] */
	m->eax = m->ebp;	/* 453635: mov eax, ebp */
	M32((DWORD)(m->esp + 0x4au)) = m->edx;	/* 453637: mov dword ptr [esp + 0x4a], edx */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45363b: add esp, 0xc */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 45363e: mov edx, dword ptr [eax] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 453640: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 453642: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 453645: mov dword ptr [ecx + 4], edx */
	m->edx = M32((DWORD)(m->eax + 0x8u));	/* 453648: mov edx, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 45364b: mov dword ptr [ecx + 8], edx */
	m->eax = M32((DWORD)(m->eax + 0xcu));	/* 45364e: mov eax, dword ptr [eax + 0xc] */
	M32((DWORD)(m->ecx + 0xcu)) = m->eax;	/* 453651: mov dword ptr [ecx + 0xc], eax */
	m->edx = M32((DWORD)(m->ebp + 0x4u));	/* 453654: mov edx, dword ptr [ebp + 4] */
	m->ecx = M32((DWORD)(m->ebp + 0x0u));	/* 453657: mov ecx, dword ptr [ebp] */
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 45365a: mov eax, dword ptr [ebp + 8] */
	M32((DWORD)(m->esp + 0x1cu)) = m->edx;	/* 45365d: mov dword ptr [esp + 0x1c], edx */
	m->edx = (DWORD)(m->ebx + 0x18u);	/* 453661: lea edx, [ebx + 0x18] */
	M32((DWORD)(m->esp + 0x18u)) = m->ecx;	/* 453664: mov dword ptr [esp + 0x18], ecx */
	m->ecx = M32((DWORD)(m->ebp + 0xcu));	/* 453668: mov ecx, dword ptr [ebp + 0xc] */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 45366b: mov dword ptr [esp + 0x20], eax */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 45366f: mov eax, dword ptr [edx] */
	M32((DWORD)(m->esp + 0x24u)) = m->ecx;	/* 453671: mov dword ptr [esp + 0x24], ecx */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 453675: mov dword ptr [esp + 0x28], eax */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 453679: mov ecx, dword ptr [edx + 4] */
	M32((DWORD)(m->esp + 0x2cu)) = m->ecx;	/* 45367c: mov dword ptr [esp + 0x2c], ecx */
	m->eax = M32((DWORD)(m->edx + 0x8u));	/* 453680: mov eax, dword ptr [edx + 8] */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 453683: mov dword ptr [esp + 0x30], eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x44u))) & 0xff) << 0);	/* 453687: mov al, byte ptr [ebx + 0x44] */
	m->ecx = M32((DWORD)(m->edx + 0xcu));	/* 45368a: mov ecx, dword ptr [edx + 0xc] */
	m->edx = (m->edx & 0xffff0000u) | ((M16((DWORD)(m->ebx + 0x40u))) & 0xffff);	/* 45368d: mov dx, word ptr [ebx + 0x40] */
	M8((DWORD)(m->esp + 0x3bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 453691: mov byte ptr [esp + 0x3b], al */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x28u))) & 0xff) << 0);	/* 453695: mov al, byte ptr [ebx + 0x28] */
	M32((DWORD)(m->esp + 0x34u)) = m->ecx;	/* 453698: mov dword ptr [esp + 0x34], ecx */
	m->ecx = M32((DWORD)(m->ebx + 0x48u));	/* 45369c: mov ecx, dword ptr [ebx + 0x48] */
	M8((DWORD)(m->esp + 0x3au)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 45369f: mov byte ptr [esp + 0x3a], al */
	m->eax = M32((DWORD)(0xa0b418u));	/* 4536a3: mov eax, dword ptr [0xa0b418] */
	M16((DWORD)(m->esp + 0x38u)) = (WORD)((m->edx & 0xffff));	/* 4536a8: mov word ptr [esp + 0x38], dx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x48u))) & 0xff) << 0);	/* 4536ad: mov dl, byte ptr [ebx + 0x48] */
	{ DWORD a_ = m->ecx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4536b0: shr ecx, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4536b3: test eax, eax */
	M8((DWORD)(m->esp + 0x3cu)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 4536b5: mov byte ptr [esp + 0x3c], cl */
	M8((DWORD)(m->esp + 0x3du)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 4536b9: mov byte ptr [esp + 0x3d], dl */
	if (!m->zf) goto L_4536df;	/* 4536bd: jne 0x4536df */
	m->ecx = M32((DWORD)(m->ebx + 0x4cu));	/* 4536bf: mov ecx, dword ptr [ebx + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4536c2: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4536c8u; native_call(m, 0x454390u);	/* 4536c3: call 0x454390 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 4536c8: push 0x10 */
	m->edx = (DWORD)(m->esp + 0x90u);	/* 4536ca: lea edx, [esp + 0x90] */
	{ DWORD v_ = 0xa0b460u; m->esp -= 4; M32(m->esp) = v_; }	/* 4536d1: push 0xa0b460 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4536d6: push edx */
	m->esp -= 4; M32(m->esp) = 0x4536dcu; native_call(m, 0x49ea80u);	/* 4536d7: call 0x49ea80 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4536dc: add esp, 0x10 */
L_4536df:
	{ DWORD a_ = m->esp, b_ = 0x88u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4536df: sub esp, 0x88 */
	m->ecx = 0x21u;	/* 4536e5: mov ecx, 0x21 */
	m->esi = (DWORD)(m->esp + 0x9cu);	/* 4536ea: lea esi, [esp + 0x9c] */
	m->edi = m->esp;	/* 4536f1: mov edi, esp */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4536f3: rep movsd dword ptr es:[edi], dword ptr [esi] */
	M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1;	/* 4536f5: movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x4536fbu; native_call(m, 0x4540b0u);	/* 4536f6: call 0x4540b0 */
	{ DWORD a_ = m->esp, b_ = 0x88u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4536fb: add esp, 0x88 */
L_453701:
	m->edi = M32(m->esp); m->esp += 4;	/* 453701: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 453702: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 453703: pop ebp */
	m->eax = 0x1u;	/* 453704: mov eax, 1 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 453709: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x8cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45370a: add esp, 0x8c */
	m->esp += 4 + 16; return;	/* 453710: ret 0x10 */
}

/* profile_create (0x4474a0), lifted by tools/lift.py */
static void lift_4474a0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x188u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4474a0: sub esp, 0x188 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4474a6: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4474a9: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x4u);	/* 4474ab: lea edx, [esp + 4] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4474af: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4474b0: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4474b1: push edi */
	m->edi = 0x9dae7cu;	/* 4474b2: mov edi, 0x9dae7c */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4474b7: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4474b9: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4474bb: sub edi, ecx */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 4474bd: push 0x4ad170 */
	m->eax = m->ecx;	/* 4474c2: mov eax, ecx */
	m->esi = m->edi;	/* 4474c4: mov esi, edi */
	m->edi = m->edx;	/* 4474c6: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x14u);	/* 4474c8: lea edx, [esp + 0x14] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4474cc: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4474cf: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4474d1: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4474d3: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4474d5: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4474d8: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2ab4u;	/* 4474da: mov edi, 0x4b2ab4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4474df: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4474e2: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4474e4: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4474e6: sub edi, ecx */
	m->esi = m->edi;	/* 4474e8: mov esi, edi */
	m->ebx = m->ecx;	/* 4474ea: mov ebx, ecx */
	m->edi = m->edx;	/* 4474ec: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4474ee: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4474f1: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 4474f3: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4474f5: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4474f6: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4474f9: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebx;	/* 4474fb: mov ecx, ebx */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 4474fd: lea eax, [esp + 0x14] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 447501: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 447504: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 447505: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x44750cu; native_call(m, 0x49e9cau);	/* 447507: call 0x49e9ca */
	m->edi = m->eax;	/* 44750c: mov edi, eax */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 44750e: xor esi, esi */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447510: add esp, 8 */
	{ DWORD a_ = m->edi, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 447513: cmp edi, esi */
	if (!m->zf) goto L_447527;	/* 447515: jne 0x447527 */
	M32((DWORD)(0x9f9008u)) = m->esi;	/* 447517: mov dword ptr [0x9f9008], esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 44751d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44751e: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 44751f: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x188u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447520: add esp, 0x188 */
	m->esp += 4 + 0; return;	/* 447526: ret  */
L_447527:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 447527: push edi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 447528: push 1 */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 44752a: lea ecx, [esp + 0x14] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 44752e: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 447530: push ecx */
	m->esp -= 4; M32(m->esp) = 0x447536u; native_call(m, 0x49e836u);	/* 447531: call 0x49e836 */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 447536: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44753a: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = 0xfefefef7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44753d: cmp eax, 0xfefefef7 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 447542: push edi */
	if (m->zf) goto L_44755d;	/* 447543: je 0x44755d */
	m->esp -= 4; M32(m->esp) = 0x44754au; native_call(m, 0x49e7e0u);	/* 447545: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44754a: add esp, 4 */
	M32((DWORD)(0x9f9008u)) = m->esi;	/* 44754d: mov dword ptr [0x9f9008], esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 447553: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 447554: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 447555: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x188u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447556: add esp, 0x188 */
	m->esp += 4 + 0; return;	/* 44755c: ret  */
L_44755d:
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44755d: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 44755f: push 4 */
	{ DWORD v_ = 0x9f9008u; m->esp -= 4; M32(m->esp) = v_; }	/* 447561: push 0x9f9008 */
	m->esp -= 4; M32(m->esp) = 0x44756bu; native_call(m, 0x49e836u);	/* 447566: call 0x49e836 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44756b: push edi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44756c: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 44756e: push 4 */
	{ DWORD v_ = 0x9f8c58u; m->esp -= 4; M32(m->esp) = v_; }	/* 447570: push 0x9f8c58 */
	m->esp -= 4; M32(m->esp) = 0x44757au; native_call(m, 0x49e836u);	/* 447575: call 0x49e836 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44757a: push edi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44757b: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 44757d: push 4 */
	{ DWORD v_ = 0x9f8c4cu; m->esp -= 4; M32(m->esp) = v_; }	/* 44757f: push 0x9f8c4c */
	m->esp -= 4; M32(m->esp) = 0x447589u; native_call(m, 0x49e836u);	/* 447584: call 0x49e836 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 447589: push edi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44758a: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 44758c: push 4 */
	{ DWORD v_ = 0x9f8c5cu; m->esp -= 4; M32(m->esp) = v_; }	/* 44758e: push 0x9f8c5c */
	m->esp -= 4; M32(m->esp) = 0x447598u; native_call(m, 0x49e836u);	/* 447593: call 0x49e836 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447598: add esp, 0x40 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44759b: push edi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44759c: push 1 */
	{ DWORD v_ = 0x20u; m->esp -= 4; M32(m->esp) = v_; }	/* 44759e: push 0x20 */
	{ DWORD v_ = 0x9f8fe8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4475a0: push 0x9f8fe8 */
	m->esp -= 4; M32(m->esp) = 0x4475aau; native_call(m, 0x49e836u);	/* 4475a5: call 0x49e836 */
	{ DWORD v_ = 0x4b2b04u; m->esp -= 4; M32(m->esp) = v_; }	/* 4475aa: push 0x4b2b04 */
	m->esp -= 4; M32(m->esp) = 0x4475b4u; native_call(m, 0x49f8a6u);	/* 4475af: call 0x49f8a6 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4475b4: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4475b7: test eax, eax */
	if (m->zf) goto L_4475d2;	/* 4475b9: je 0x4475d2 */
	{ DWORD v_ = 0x4b2adcu; m->esp -= 4; M32(m->esp) = v_; }	/* 4475bb: push 0x4b2adc */
	m->esp -= 4; M32(m->esp) = 0x4475c5u; native_call(m, 0x49f94au);	/* 4475c0: call 0x49f94a */
	{ DWORD v_ = 0x4b2adcu; m->esp -= 4; M32(m->esp) = v_; }	/* 4475c5: push 0x4b2adc */
	m->esp -= 4; M32(m->esp) = 0x4475cfu; native_call(m, 0x49f8a6u);	/* 4475ca: call 0x49f8a6 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4475cf: add esp, 8 */
L_4475d2:
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4475d2: push ebp */
	{ DWORD v_ = 0x4b2a80u; m->esp -= 4; M32(m->esp) = v_; }	/* 4475d3: push 0x4b2a80 */
	m->esp -= 4; M32(m->esp) = 0x4475ddu; native_call(m, 0x49f8a6u);	/* 4475d8: call 0x49f8a6 */
	m->eax = M32((DWORD)(0x9f9008u));	/* 4475dd: mov eax, dword ptr [0x9f9008] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4475e2: add esp, 4 */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4475e5: xor edx, edx */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4475e7: cmp eax, esi */
	if (m->zf || m->sf != m->of) goto L_44764b;	/* 4475e9: jle 0x44764b */
	m->ebp = 0x9f684cu;	/* 4475eb: mov ebp, 0x9f684c */
L_4475f0:
	m->esi = 0x9f8fe8u;	/* 4475f0: mov esi, 0x9f8fe8 */
	m->eax = m->ebp;	/* 4475f5: mov eax, ebp */
L_4475f7:
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 4475f7: mov bl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->ebx >> 0) & 0xff)) & 0xff) << 0);	/* 4475f9: mov cl, bl */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4475fb: cmp bl, byte ptr [esi] */
	if (!m->zf) goto L_44761b;	/* 4475fd: jne 0x44761b */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4475ff: test cl, cl */
	if (m->zf) goto L_447617;	/* 447601: je 0x447617 */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 447603: mov bl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->ebx >> 0) & 0xff)) & 0xff) << 0);	/* 447606: mov cl, bl */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 447608: cmp bl, byte ptr [esi + 1] */
	if (!m->zf) goto L_44761b;	/* 44760b: jne 0x44761b */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44760d: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 447610: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 447613: test cl, cl */
	if (!m->zf) goto L_4475f7;	/* 447615: jne 0x4475f7 */
L_447617:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 447617: xor eax, eax */
	goto L_447620;	/* 447619: jmp 0x447620 */
L_44761b:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 44761b: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 44761d: sbb eax, -1 */
L_447620:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 447620: test eax, eax */
	if (m->zf) goto L_447645;	/* 447622: je 0x447645 */
	m->eax = M32((DWORD)(0x9f9008u));	/* 447624: mov eax, dword ptr [0x9f9008] */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 447629: inc edx */
	{ DWORD a_ = m->ebp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 44762a: add ebp, 0x48 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44762d: cmp edx, eax */
	if (m->sf != m->of) goto L_4475f0;	/* 44762f: jl 0x4475f0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 447631: push edi */
	m->esp -= 4; M32(m->esp) = 0x447637u; native_call(m, 0x49e7e0u);	/* 447632: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447637: add esp, 4 */
	m->ebp = M32(m->esp); m->esp += 4;	/* 44763a: pop ebp */
	m->edi = M32(m->esp); m->esp += 4;	/* 44763b: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44763c: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 44763d: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x188u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44763e: add esp, 0x188 */
	m->esp += 4 + 0; return;	/* 447644: ret  */
L_447645:
	M32((DWORD)(0x9f8c58u)) = m->edx;	/* 447645: mov dword ptr [0x9f8c58], edx */
L_44764b:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44764b: push edi */
	m->esp -= 4; M32(m->esp) = 0x447651u; native_call(m, 0x49e7e0u);	/* 44764c: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447651: add esp, 4 */
	m->ebp = M32(m->esp); m->esp += 4;	/* 447654: pop ebp */
	m->edi = M32(m->esp); m->esp += 4;	/* 447655: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 447656: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 447657: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x188u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447658: add esp, 0x188 */
	m->esp += 4 + 0; return;	/* 44765e: ret  */
}

/* data_loadSkirmishInfo (0x42ba40), lifted by tools/lift.py */
static void lift_42ba40(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x188u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42ba40: sub esp, 0x188 */
	m->ecx = 0x41u;	/* 42ba46: mov ecx, 0x41 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42ba4b: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x80u);	/* 42ba4d: lea edx, [esp + 0x80] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42ba54: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ba55: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ba56: push edi */
	m->edi = (DWORD)(m->esp + 0x8cu);	/* 42ba57: lea edi, [esp + 0x8c] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 42ba5e: rep stosd dword ptr es:[edi], eax */
	M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1;	/* 42ba60: stosb byte ptr es:[edi], al */
	m->edi = 0x9dae7cu;	/* 42ba61: mov edi, 0x9dae7c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42ba66: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42ba69: xor eax, eax */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 42ba6b: push 0x4ad170 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42ba70: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42ba72: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42ba74: sub edi, ecx */
	m->eax = m->ecx;	/* 42ba76: mov eax, ecx */
	m->esi = m->edi;	/* 42ba78: mov esi, edi */
	m->edi = m->edx;	/* 42ba7a: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x90u);	/* 42ba7c: lea edx, [esp + 0x90] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42ba83: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42ba86: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 42ba88: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42ba8a: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42ba8c: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 42ba8f: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b1554u;	/* 42ba91: mov edi, 0x4b1554 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42ba96: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42ba99: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42ba9b: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42ba9d: sub edi, ecx */
	m->esi = m->edi;	/* 42ba9f: mov esi, edi */
	m->ebx = m->ecx;	/* 42baa1: mov ebx, ecx */
	m->edi = m->edx;	/* 42baa3: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42baa5: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42baa8: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 42baaa: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 42baac: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42baad: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42bab0: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebx;	/* 42bab2: mov ecx, ebx */
	m->eax = (DWORD)(m->esp + 0x90u);	/* 42bab4: lea eax, [esp + 0x90] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42babb: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42babe: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 42babf: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x42bac6u; native_call(m, 0x49e9cau);	/* 42bac1: call 0x49e9ca */
	m->esi = m->eax;	/* 42bac6: mov esi, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42bac8: add esp, 8 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42bacb: test esi, esi */
	if (!m->zf) goto L_42bae8;	/* 42bacd: jne 0x42bae8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42bacf: push eax */
	{ DWORD v_ = 0x4b141cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42bad0: push 0x4b141c */
	{ DWORD v_ = 0x4b1534u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bad5: push 0x4b1534 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42bada: push eax */
	m->esp -= 4; M32(m->esp) = 0x42bae1u; native_call(m, M32(0x4a9324u));	/* 42badb: call dword ptr [0x4a9324] */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 42bae1: push -1 */
	m->esp -= 4; M32(m->esp) = 0x42bae8u; native_call(m, 0x49edacu);	/* 42bae3: call 0x49edac */
L_42bae8:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bae8: push 2 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42baea: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42baec: push esi */
	m->esp -= 4; M32(m->esp) = 0x42baf2u; native_call(m, 0x49e91eu);	/* 42baed: call 0x49e91e */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42baf2: push esi */
	m->esp -= 4; M32(m->esp) = 0x42baf8u; native_call(m, 0x49efddu);	/* 42baf3: call 0x49efdd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42baf8: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = 0x2710u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42bafb: cmp eax, 0x2710 */
	if (m->sf == m->of) goto L_42bb26;	/* 42bb00: jge 0x42bb26 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42bb02: push esi */
	m->esp -= 4; M32(m->esp) = 0x42bb08u; native_call(m, 0x49e7e0u);	/* 42bb03: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42bb08: add esp, 4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bb0b: push 0 */
	{ DWORD v_ = 0x4b141cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42bb0d: push 0x4b141c */
	{ DWORD v_ = 0x4b1534u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bb12: push 0x4b1534 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bb17: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42bb1fu; native_call(m, M32(0x4a9324u));	/* 42bb19: call dword ptr [0x4a9324] */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 42bb1f: push -1 */
	m->esp -= 4; M32(m->esp) = 0x42bb26u; native_call(m, 0x49edacu);	/* 42bb21: call 0x49edac */
L_42bb26:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bb26: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bb28: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42bb2a: push esi */
	m->esp -= 4; M32(m->esp) = 0x42bb30u; native_call(m, 0x49e91eu);	/* 42bb2b: call 0x49e91e */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42bb30: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bb31: push 1 */
	m->ecx = (DWORD)(m->esp + 0x20u);	/* 42bb33: lea ecx, [esp + 0x20] */
	{ DWORD v_ = 0x80u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bb37: push 0x80 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42bb3c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42bb42u; native_call(m, 0x49e836u);	/* 42bb3d: call 0x49e836 */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42bb42: add esp, 0x1c */
	m->edi = 0x4b1510u;	/* 42bb45: mov edi, 0x4b1510 */
	m->eax = (DWORD)(m->esp + 0xcu);	/* 42bb4a: lea eax, [esp + 0xc] */
L_42bb4e:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42bb4e: mov dl, byte ptr [eax] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x0u))) & 0xff) << 0);	/* 42bb50: mov bl, byte ptr [edi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42bb52: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42bb54: cmp dl, bl */
	if (!m->zf) goto L_42bb76;	/* 42bb56: jne 0x42bb76 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42bb58: test cl, cl */
	if (m->zf) goto L_42bb72;	/* 42bb5a: je 0x42bb72 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42bb5c: mov dl, byte ptr [eax + 1] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x1u))) & 0xff) << 0);	/* 42bb5f: mov bl, byte ptr [edi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42bb62: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42bb64: cmp dl, bl */
	if (!m->zf) goto L_42bb76;	/* 42bb66: jne 0x42bb76 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42bb68: add eax, 2 */
	{ DWORD a_ = m->edi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42bb6b: add edi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42bb6e: test cl, cl */
	if (!m->zf) goto L_42bb4e;	/* 42bb70: jne 0x42bb4e */
L_42bb72:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42bb72: xor eax, eax */
	goto L_42bb7b;	/* 42bb74: jmp 0x42bb7b */
L_42bb76:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42bb76: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42bb78: sbb eax, -1 */
L_42bb7b:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42bb7b: test eax, eax */
	if (m->zf) goto L_42bba3;	/* 42bb7d: je 0x42bba3 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42bb7f: push esi */
	m->esp -= 4; M32(m->esp) = 0x42bb85u; native_call(m, 0x49e7e0u);	/* 42bb80: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42bb85: add esp, 4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bb88: push 0 */
	{ DWORD v_ = 0x4b141cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42bb8a: push 0x4b141c */
	{ DWORD v_ = 0x4b1534u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bb8f: push 0x4b1534 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bb94: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42bb9cu; native_call(m, M32(0x4a9324u));	/* 42bb96: call dword ptr [0x4a9324] */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 42bb9c: push -1 */
	m->esp -= 4; M32(m->esp) = 0x42bba3u; native_call(m, 0x49edacu);	/* 42bb9e: call 0x49edac */
L_42bba3:
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bba3: push 1 */
	{ DWORD v_ = 0x61a8u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bba5: push 0x61a8 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42bbaa: push esi */
	m->esp -= 4; M32(m->esp) = 0x42bbb0u; native_call(m, 0x49e91eu);	/* 42bbab: call 0x49e91e */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42bbb0: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bbb1: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bbb3: push 4 */
	{ DWORD v_ = 0x90d1d8u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bbb5: push 0x90d1d8 */
	m->esp -= 4; M32(m->esp) = 0x42bbbfu; native_call(m, 0x49e836u);	/* 42bbba: call 0x49e836 */
	m->eax = M32((DWORD)(0x90d1d8u));	/* 42bbbf: mov eax, dword ptr [0x90d1d8] */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42bbc4: add esp, 0x1c */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 42bbc7: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42bbc9: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_42bbed;	/* 42bbcb: jle 0x42bbed */
	m->ebx = 0x9db998u;	/* 42bbcd: mov ebx, 0x9db998 */
L_42bbd2:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42bbd2: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bbd3: push 1 */
	{ DWORD v_ = 0x5cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42bbd5: push 0x5c */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42bbd7: push ebx */
	m->esp -= 4; M32(m->esp) = 0x42bbddu; native_call(m, 0x49e836u);	/* 42bbd8: call 0x49e836 */
	m->eax = M32((DWORD)(0x90d1d8u));	/* 42bbdd: mov eax, dword ptr [0x90d1d8] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42bbe2: add esp, 0x10 */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 42bbe5: inc edi */
	{ DWORD a_ = m->ebx, b_ = 0x5cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 42bbe6: add ebx, 0x5c */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42bbe9: cmp edi, eax */
	if (m->sf != m->of) goto L_42bbd2;	/* 42bbeb: jl 0x42bbd2 */
L_42bbed:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42bbed: push esi */
	m->esp -= 4; M32(m->esp) = 0x42bbf3u; native_call(m, 0x49e7e0u);	/* 42bbee: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42bbf3: add esp, 4 */
	m->edi = M32(m->esp); m->esp += 4;	/* 42bbf6: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 42bbf7: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 42bbf8: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x188u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42bbf9: add esp, 0x188 */
	m->esp += 4 + 0; return;	/* 42bbff: ret  */
}

/* data_loadMapInfo (0x42b830), lifted by tools/lift.py */
static void lift_42b830(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x1b8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42b830: sub esp, 0x1b8 */
	m->ecx = 0x41u;	/* 42b836: mov ecx, 0x41 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42b83b: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0xb0u);	/* 42b83d: lea edx, [esp + 0xb0] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42b844: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42b845: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42b846: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42b847: push edi */
	m->edi = (DWORD)(m->esp + 0xc0u);	/* 42b848: lea edi, [esp + 0xc0] */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b84f: push 0x4ad170 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 42b854: rep stosd dword ptr es:[edi], eax */
	M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1;	/* 42b856: stosb byte ptr es:[edi], al */
	m->edi = 0x4dedf8u;	/* 42b857: mov edi, 0x4dedf8 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42b85c: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42b85f: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42b861: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42b863: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42b865: sub edi, ecx */
	m->eax = m->ecx;	/* 42b867: mov eax, ecx */
	m->esi = m->edi;	/* 42b869: mov esi, edi */
	m->edi = m->edx;	/* 42b86b: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0xc4u);	/* 42b86d: lea edx, [esp + 0xc4] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42b874: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42b877: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 42b879: mov ecx, eax */
	m->eax = M32((DWORD)(0x9dae74u));	/* 42b87b: mov eax, dword ptr [0x9dae74] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42b880: and ecx, 3 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42b883: cmp eax, 1 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 42b886: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b1504u;	/* 42b888: mov edi, 0x4b1504 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42b88d: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42b890: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42b892: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42b894: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42b896: sub edi, ecx */
	m->esi = m->edi;	/* 42b898: mov esi, edi */
	m->ebx = m->ecx;	/* 42b89a: mov ebx, ecx */
	m->edi = m->edx;	/* 42b89c: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42b89e: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42b8a1: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 42b8a3: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 42b8a5: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42b8a6: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42b8a9: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebx;	/* 42b8ab: mov ecx, ebx */
	m->eax = (DWORD)(m->esp + 0xc4u);	/* 42b8ad: lea eax, [esp + 0xc4] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42b8b4: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42b8b7: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 42b8b8: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x42b8bfu; native_call(m, 0x49e9cau);	/* 42b8ba: call 0x49e9ca */
	m->ebp = m->eax;	/* 42b8bf: mov ebp, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42b8c1: add esp, 8 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42b8c4: test ebp, ebp */
	if (!m->zf) goto L_42b8e1;	/* 42b8c6: jne 0x42b8e1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42b8c8: push eax */
	{ DWORD v_ = 0x4b141cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42b8c9: push 0x4b141c */
	{ DWORD v_ = 0x4b14e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b8ce: push 0x4b14e0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42b8d3: push eax */
	m->esp -= 4; M32(m->esp) = 0x42b8dau; native_call(m, M32(0x4a9324u));	/* 42b8d4: call dword ptr [0x4a9324] */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 42b8da: push -1 */
	m->esp -= 4; M32(m->esp) = 0x42b8e1u; native_call(m, 0x49edacu);	/* 42b8dc: call 0x49edac */
L_42b8e1:
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42b8e1: push ebp */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b8e2: push 1 */
	m->ecx = (DWORD)(m->esp + 0x48u);	/* 42b8e4: lea ecx, [esp + 0x48] */
	{ DWORD v_ = 0x80u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b8e8: push 0x80 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42b8ed: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42b8f3u; native_call(m, 0x49e836u);	/* 42b8ee: call 0x49e836 */
	m->ecx = 0xcu;	/* 42b8f3: mov ecx, 0xc */
	m->esi = (DWORD)(m->esp + 0x50u);	/* 42b8f8: lea esi, [esp + 0x50] */
	m->edi = (DWORD)(m->esp + 0x20u);	/* 42b8fc: lea edi, [esp + 0x20] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42b900: add esp, 0x10 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42b903: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->esi = 0x4b14c0u;	/* 42b905: mov esi, 0x4b14c0 */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42b90a: lea eax, [esp + 0x10] */
L_42b90e:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42b90e: mov dl, byte ptr [eax] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 42b910: mov bl, byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42b912: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42b914: cmp dl, bl */
	if (!m->zf) goto L_42b936;	/* 42b916: jne 0x42b936 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42b918: test cl, cl */
	if (m->zf) goto L_42b932;	/* 42b91a: je 0x42b932 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42b91c: mov dl, byte ptr [eax + 1] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 42b91f: mov bl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42b922: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42b924: cmp dl, bl */
	if (!m->zf) goto L_42b936;	/* 42b926: jne 0x42b936 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42b928: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42b92b: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42b92e: test cl, cl */
	if (!m->zf) goto L_42b90e;	/* 42b930: jne 0x42b90e */
L_42b932:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42b932: xor eax, eax */
	goto L_42b93b;	/* 42b934: jmp 0x42b93b */
L_42b936:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42b936: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42b938: sbb eax, -1 */
L_42b93b:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42b93b: test eax, eax */
	if (m->zf) goto L_42b963;	/* 42b93d: je 0x42b963 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42b93f: push ebp */
	m->esp -= 4; M32(m->esp) = 0x42b945u; native_call(m, 0x49e7e0u);	/* 42b940: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42b945: add esp, 4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b948: push 0 */
	{ DWORD v_ = 0x4b141cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42b94a: push 0x4b141c */
	{ DWORD v_ = 0x4b14e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b94f: push 0x4b14e0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b954: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42b95cu; native_call(m, M32(0x4a9324u));	/* 42b956: call dword ptr [0x4a9324] */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 42b95c: push -1 */
	m->esp -= 4; M32(m->esp) = 0x42b963u; native_call(m, 0x49edacu);	/* 42b95e: call 0x49edac */
L_42b963:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + 0x72u))) & 0xff) << 0);	/* 42b963: mov al, byte ptr [esp + 0x72] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42b967: push ebp */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x1au & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42b968: cmp al, 0x1a */
	if (m->zf) goto L_42b98f;	/* 42b96a: je 0x42b98f */
	m->esp -= 4; M32(m->esp) = 0x42b971u; native_call(m, 0x49e7e0u);	/* 42b96c: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42b971: add esp, 4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b974: push 0 */
	{ DWORD v_ = 0x4b141cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42b976: push 0x4b141c */
	{ DWORD v_ = 0x4b14e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b97b: push 0x4b14e0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b980: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42b988u; native_call(m, M32(0x4a9324u));	/* 42b982: call dword ptr [0x4a9324] */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 42b988: push -1 */
	m->esp -= 4; M32(m->esp) = 0x42b98fu; native_call(m, 0x49edacu);	/* 42b98a: call 0x49edac */
L_42b98f:
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b98f: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b991: push 4 */
	{ DWORD v_ = 0x67ef00u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b993: push 0x67ef00 */
	m->esp -= 4; M32(m->esp) = 0x42b99du; native_call(m, 0x49e836u);	/* 42b998: call 0x49e836 */
	m->eax = M32((DWORD)(0x67ef00u));	/* 42b99d: mov eax, dword ptr [0x67ef00] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42b9a2: add esp, 0x10 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 42b9a5: xor ebx, ebx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42b9a7: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_42b9ea;	/* 42b9a9: jle 0x42b9ea */
	m->edi = 0x5ae9d0u;	/* 42b9ab: mov edi, 0x5ae9d0 */
	m->esi = 0x907b30u;	/* 42b9b0: mov esi, 0x907b30 */
L_42b9b5:
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42b9b5: push ebp */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b9b6: push 1 */
	{ DWORD v_ = 0x20u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b9b8: push 0x20 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42b9ba: push esi */
	m->esp -= 4; M32(m->esp) = 0x42b9c0u; native_call(m, 0x49e836u);	/* 42b9bb: call 0x49e836 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42b9c0: push esi */
	m->esp -= 4; M32(m->esp) = 0x42b9c6u; native_call(m, 0x42b390u);	/* 42b9c1: call 0x42b390 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42b9c6: push ebp */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b9c7: push 1 */
	{ DWORD v_ = 0x50u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b9c9: push 0x50 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42b9cb: push edi */
	m->esp -= 4; M32(m->esp) = 0x42b9d1u; native_call(m, 0x49e836u);	/* 42b9cc: call 0x49e836 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42b9d1: push edi */
	m->esp -= 4; M32(m->esp) = 0x42b9d7u; native_call(m, 0x42b390u);	/* 42b9d2: call 0x42b390 */
	m->eax = M32((DWORD)(0x67ef00u));	/* 42b9d7: mov eax, dword ptr [0x67ef00] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42b9dc: add esp, 0x28 */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 42b9df: inc ebx */
	{ DWORD a_ = m->esi, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42b9e0: add esi, 0x20 */
	{ DWORD a_ = m->edi, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42b9e3: add edi, 0x50 */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42b9e6: cmp ebx, eax */
	if (m->sf != m->of) goto L_42b9b5;	/* 42b9e8: jl 0x42b9b5 */
L_42b9ea:
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42b9ea: push ebp */
	m->esp -= 4; M32(m->esp) = 0x42b9f0u; native_call(m, 0x49e7e0u);	/* 42b9eb: call 0x49e7e0 */
	m->eax = M32((DWORD)(0x67ef00u));	/* 42b9f0: mov eax, dword ptr [0x67ef00] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42b9f5: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42b9f8: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_42ba2a;	/* 42b9fa: jle 0x42ba2a */
	m->edx = 0x907b30u;	/* 42b9fc: mov edx, 0x907b30 */
	m->esi = m->eax;	/* 42ba01: mov esi, eax */
L_42ba03:
	m->edi = m->edx;	/* 42ba03: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42ba05: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42ba08: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42ba0a: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42ba0c: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 42ba0e: dec ecx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42ba0f: test ecx, ecx */
	if (m->zf || m->sf != m->of) goto L_42ba24;	/* 42ba11: jle 0x42ba24 */
L_42ba13:
	{ DWORD a_ = M8((DWORD)(m->edx + m->ecx*1 + 0xffffffffu)), b_ = 0x20u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42ba13: cmp byte ptr [edx + ecx - 1], 0x20 */
	if (!m->zf) goto L_42ba24;	/* 42ba18: jne 0x42ba24 */
	M8((DWORD)(m->edx + m->ecx*1 + 0xffffffffu)) = (BYTE)(0x0u);	/* 42ba1a: mov byte ptr [edx + ecx - 1], 0 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 42ba1f: dec ecx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42ba20: test ecx, ecx */
	if (!m->zf && m->sf == m->of) goto L_42ba13;	/* 42ba22: jg 0x42ba13 */
L_42ba24:
	{ DWORD a_ = m->edx, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 42ba24: add edx, 0x20 */
	{ DWORD a_ = m->esi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->esi = r_; }	/* 42ba27: dec esi */
	if (!m->zf) goto L_42ba03;	/* 42ba28: jne 0x42ba03 */
L_42ba2a:
	m->edi = M32(m->esp); m->esp += 4;	/* 42ba2a: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 42ba2b: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 42ba2c: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 42ba2d: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x1b8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42ba2e: add esp, 0x1b8 */
	m->esp += 4 + 0; return;	/* 42ba34: ret  */
}

/* data_loadPilotProfiles (0x42b590), lifted by tools/lift.py */
static void lift_42b590(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x1e4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42b590: sub esp, 0x1e4 */
	m->ecx = 0x41u;	/* 42b596: mov ecx, 0x41 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42b59b: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x5cu);	/* 42b59d: lea edx, [esp + 0x5c] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42b5a1: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42b5a2: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42b5a3: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42b5a4: push edi */
	m->edi = (DWORD)(m->esp + 0x6cu);	/* 42b5a5: lea edi, [esp + 0x6c] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 42b5a9: rep stosd dword ptr es:[edi], eax */
	M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1;	/* 42b5ab: stosb byte ptr es:[edi], al */
	m->edi = 0x9dae7cu;	/* 42b5ac: mov edi, 0x9dae7c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42b5b1: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42b5b4: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42b5b6: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42b5b8: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42b5ba: sub edi, ecx */
	m->eax = m->ecx;	/* 42b5bc: mov eax, ecx */
	m->esi = m->edi;	/* 42b5be: mov esi, edi */
	m->edi = m->edx;	/* 42b5c0: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x6cu);	/* 42b5c2: lea edx, [esp + 0x6c] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42b5c6: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42b5c9: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 42b5cb: mov ecx, eax */
	m->eax = M32((DWORD)(0x9dae74u));	/* 42b5cd: mov eax, dword ptr [0x9dae74] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42b5d2: and ecx, 3 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42b5d5: cmp eax, 1 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 42b5d8: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b14b4u;	/* 42b5da: mov edi, 0x4b14b4 */
	if (m->zf) goto L_42b5e6;	/* 42b5df: je 0x42b5e6 */
	m->edi = 0x4b14a8u;	/* 42b5e1: mov edi, 0x4b14a8 */
L_42b5e6:
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42b5e6: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42b5e9: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42b5eb: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42b5ed: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42b5ef: sub edi, ecx */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b5f1: push 0x4ad170 */
	m->esi = m->edi;	/* 42b5f6: mov esi, edi */
	m->ebx = m->ecx;	/* 42b5f8: mov ebx, ecx */
	m->edi = m->edx;	/* 42b5fa: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42b5fc: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42b5ff: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 42b601: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 42b603: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42b604: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42b607: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebx;	/* 42b609: mov ecx, ebx */
	m->eax = (DWORD)(m->esp + 0x70u);	/* 42b60b: lea eax, [esp + 0x70] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42b60f: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42b612: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 42b613: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x42b61au; native_call(m, 0x49e9cau);	/* 42b615: call 0x49e9ca */
	m->ebp = m->eax;	/* 42b61a: mov ebp, eax */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 42b61c: xor edi, edi */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42b61e: add esp, 8 */
	{ DWORD a_ = m->ebp, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42b621: cmp ebp, edi */
	if (!m->zf) goto L_42b63e;	/* 42b623: jne 0x42b63e */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42b625: push edi */
	{ DWORD v_ = 0x4b141cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42b626: push 0x4b141c */
	{ DWORD v_ = 0x4b1480u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b62b: push 0x4b1480 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42b630: push edi */
	m->esp -= 4; M32(m->esp) = 0x42b637u; native_call(m, M32(0x4a9324u));	/* 42b631: call dword ptr [0x4a9324] */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 42b637: push -1 */
	m->esp -= 4; M32(m->esp) = 0x42b63eu; native_call(m, 0x49edacu);	/* 42b639: call 0x49edac */
L_42b63e:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b63e: push 2 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42b640: push edi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42b641: push ebp */
	m->esp -= 4; M32(m->esp) = 0x42b647u; native_call(m, 0x49e91eu);	/* 42b642: call 0x49e91e */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42b647: push ebp */
	m->esp -= 4; M32(m->esp) = 0x42b64du; native_call(m, 0x49efddu);	/* 42b648: call 0x49efdd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42b64d: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = 0x2710u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42b650: cmp eax, 0x2710 */
	if (m->sf == m->of) goto L_42b679;	/* 42b655: jge 0x42b679 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42b657: push ebp */
	m->esp -= 4; M32(m->esp) = 0x42b65du; native_call(m, 0x49e7e0u);	/* 42b658: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42b65d: add esp, 4 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42b660: push edi */
	{ DWORD v_ = 0x4b141cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42b661: push 0x4b141c */
	{ DWORD v_ = 0x4b1480u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b666: push 0x4b1480 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42b66b: push edi */
	m->esp -= 4; M32(m->esp) = 0x42b672u; native_call(m, M32(0x4a9324u));	/* 42b66c: call dword ptr [0x4a9324] */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 42b672: push -1 */
	m->esp -= 4; M32(m->esp) = 0x42b679u; native_call(m, 0x49edacu);	/* 42b674: call 0x49edac */
L_42b679:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42b679: push edi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42b67a: push edi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42b67b: push ebp */
	m->esp -= 4; M32(m->esp) = 0x42b681u; native_call(m, 0x49e91eu);	/* 42b67c: call 0x49e91e */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42b681: push ebp */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b682: push 1 */
	m->ecx = (DWORD)(m->esp + 0x188u);	/* 42b684: lea ecx, [esp + 0x188] */
	{ DWORD v_ = 0x80u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b68b: push 0x80 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42b690: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42b696u; native_call(m, 0x49e836u);	/* 42b691: call 0x49e836 */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42b696: add esp, 0x1c */
	m->esi = 0x4b145cu;	/* 42b699: mov esi, 0x4b145c */
	m->eax = (DWORD)(m->esp + 0x174u);	/* 42b69e: lea eax, [esp + 0x174] */
L_42b6a5:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42b6a5: mov dl, byte ptr [eax] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 42b6a7: mov bl, byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42b6a9: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42b6ab: cmp dl, bl */
	if (!m->zf) goto L_42b6cd;	/* 42b6ad: jne 0x42b6cd */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42b6af: test cl, cl */
	if (m->zf) goto L_42b6c9;	/* 42b6b1: je 0x42b6c9 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42b6b3: mov dl, byte ptr [eax + 1] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 42b6b6: mov bl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42b6b9: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42b6bb: cmp dl, bl */
	if (!m->zf) goto L_42b6cd;	/* 42b6bd: jne 0x42b6cd */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42b6bf: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42b6c2: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42b6c5: test cl, cl */
	if (!m->zf) goto L_42b6a5;	/* 42b6c7: jne 0x42b6a5 */
L_42b6c9:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42b6c9: xor eax, eax */
	goto L_42b6d2;	/* 42b6cb: jmp 0x42b6d2 */
L_42b6cd:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42b6cd: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42b6cf: sbb eax, -1 */
L_42b6d2:
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42b6d2: cmp eax, edi */
	if (m->zf) goto L_42b6f8;	/* 42b6d4: je 0x42b6f8 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42b6d6: push ebp */
	m->esp -= 4; M32(m->esp) = 0x42b6dcu; native_call(m, 0x49e7e0u);	/* 42b6d7: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42b6dc: add esp, 4 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42b6df: push edi */
	{ DWORD v_ = 0x4b141cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42b6e0: push 0x4b141c */
	{ DWORD v_ = 0x4b1480u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b6e5: push 0x4b1480 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42b6ea: push edi */
	m->esp -= 4; M32(m->esp) = 0x42b6f1u; native_call(m, M32(0x4a9324u));	/* 42b6eb: call dword ptr [0x4a9324] */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 42b6f1: push -1 */
	m->esp -= 4; M32(m->esp) = 0x42b6f8u; native_call(m, 0x49edacu);	/* 42b6f3: call 0x49edac */
L_42b6f8:
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b6f8: push 1 */
	{ DWORD v_ = 0x1046au; m->esp -= 4; M32(m->esp) = v_; }	/* 42b6fa: push 0x1046a */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42b6ff: push ebp */
	m->esp -= 4; M32(m->esp) = 0x42b705u; native_call(m, 0x49e91eu);	/* 42b700: call 0x49e91e */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42b705: push ebp */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b706: push 1 */
	m->eax = (DWORD)(m->esp + 0x2cu);	/* 42b708: lea eax, [esp + 0x2c] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b70c: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42b70e: push eax */
	m->esp -= 4; M32(m->esp) = 0x42b714u; native_call(m, 0x49e836u);	/* 42b70f: call 0x49e836 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42b714: push ebp */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b715: push 1 */
	m->ecx = (DWORD)(m->esp + 0x40u);	/* 42b717: lea ecx, [esp + 0x40] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b71b: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42b71d: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42b723u; native_call(m, 0x49e836u);	/* 42b71e: call 0x49e836 */
	m->eax = M32((DWORD)(m->esp + 0x48u));	/* 42b723: mov eax, dword ptr [esp + 0x48] */
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42b727: add esp, 0x2c */
	{ DWORD a_ = m->eax, b_ = 0x115cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42b72a: sub eax, 0x115c */
	{ DWORD a_ = m->eax, b_ = 0x67u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42b72f: cmp eax, 0x67 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 42b732: mov dword ptr [esp + 0x1c], eax */
	if (m->zf) goto L_42b751;	/* 42b736: je 0x42b751 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42b738: push edi */
	{ DWORD v_ = 0x4b141cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42b739: push 0x4b141c */
	{ DWORD v_ = 0x4b143cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42b73e: push 0x4b143c */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42b743: push edi */
	m->esp -= 4; M32(m->esp) = 0x42b74au; native_call(m, M32(0x4a9324u));	/* 42b744: call dword ptr [0x4a9324] */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 42b74a: push -1 */
	m->esp -= 4; M32(m->esp) = 0x42b751u; native_call(m, 0x49edacu);	/* 42b74c: call 0x49edac */
L_42b751:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 42b751: mov eax, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 42b755: xor ebx, ebx */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42b757: cmp eax, edi */
	M8((DWORD)(m->esp + 0x14u)) = (BYTE)(0x61u);	/* 42b759: mov byte ptr [esp + 0x14], 0x61 */
	if (m->zf || m->sf != m->of) goto L_42b7b8;	/* 42b75e: jle 0x42b7b8 */
	M32((DWORD)(m->esp + 0x10u)) = 0x9f9040u;	/* 42b760: mov dword ptr [esp + 0x10], 0x9f9040 */
L_42b768:
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42b768: push ebp */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 42b769: push 1 */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 42b76b: lea edx, [esp + 0x28] */
	{ DWORD v_ = 0x4cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42b76f: push 0x4c */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42b771: push edx */
	m->esp -= 4; M32(m->esp) = 0x42b777u; native_call(m, 0x49e836u);	/* 42b772: call 0x49e836 */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 42b777: mov eax, dword ptr [esp + 0x24] */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 42b77b: lea ecx, [esp + 0x30] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42b77f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42b780: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42b786u; native_call(m, 0x42b3c0u);	/* 42b781: call 0x42b3c0 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + 0x2cu))) & 0xff) << 0);	/* 42b786: mov al, byte ptr [esp + 0x2c] */
	m->edi = M32((DWORD)(m->esp + 0x28u));	/* 42b78a: mov edi, dword ptr [esp + 0x28] */
	m->ecx = 0x13u;	/* 42b78e: mov ecx, 0x13 */
	m->esi = (DWORD)(m->esp + 0x38u);	/* 42b793: lea esi, [esp + 0x38] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42b797: add esp, 0x18 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), r_ = (a_ + 1) & 0xffu; FLAGS(r_, 8); m->of = (r_ == 0x80u); m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 42b79a: inc al */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42b79c: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 42b79e: mov ecx, dword ptr [esp + 0x10] */
	M8((DWORD)(m->esp + 0x14u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 42b7a2: mov byte ptr [esp + 0x14], al */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 42b7a6: mov eax, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 42b7aa: inc ebx */
	{ DWORD a_ = m->ecx, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 42b7ab: add ecx, 0x4c */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42b7ae: cmp ebx, eax */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 42b7b0: mov dword ptr [esp + 0x10], ecx */
	if (m->sf != m->of) goto L_42b768;	/* 42b7b4: jl 0x42b768 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 42b7b6: xor edi, edi */
L_42b7b8:
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42b7b8: push ebp */
	m->esp -= 4; M32(m->esp) = 0x42b7beu; native_call(m, 0x49e7e0u);	/* 42b7b9: call 0x49e7e0 */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 42b7be: mov ecx, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42b7c2: add esp, 4 */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42b7c5: cmp ecx, edi */
	if (m->zf || m->sf != m->of) goto L_42b824;	/* 42b7c7: jle 0x42b824 */
	m->eax = 0x9f9070u;	/* 42b7c9: mov eax, 0x9f9070 */
	m->edx = 0x1eu;	/* 42b7ce: mov edx, 0x1e */
	m->esi = 0x32u;	/* 42b7d3: mov esi, 0x32 */
L_42b7d8:
	{ DWORD a_ = M32((DWORD)(m->eax + 0xfffffff8u)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42b7d8: cmp dword ptr [eax - 8], edx */
	if (m->zf || m->sf != m->of) goto L_42b7e0;	/* 42b7db: jle 0x42b7e0 */
	M32((DWORD)(m->eax + 0xfffffff8u)) = m->edi;	/* 42b7dd: mov dword ptr [eax - 8], edi */
L_42b7e0:
	{ DWORD a_ = M32((DWORD)(m->eax + 0x0u)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42b7e0: cmp dword ptr [eax], edx */
	if (m->zf || m->sf != m->of) goto L_42b7e6;	/* 42b7e2: jle 0x42b7e6 */
	M32((DWORD)(m->eax + 0x0u)) = m->edi;	/* 42b7e4: mov dword ptr [eax], edi */
L_42b7e6:
	{ DWORD a_ = M32((DWORD)(m->eax + 0x4u)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42b7e6: cmp dword ptr [eax + 4], edx */
	if (m->zf || m->sf != m->of) goto L_42b7ee;	/* 42b7e9: jle 0x42b7ee */
	M32((DWORD)(m->eax + 0x4u)) = m->edi;	/* 42b7eb: mov dword ptr [eax + 4], edi */
L_42b7ee:
	{ DWORD a_ = M32((DWORD)(m->eax + 0xfffffffcu)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42b7ee: cmp dword ptr [eax - 4], edx */
	if (m->zf || m->sf != m->of) goto L_42b7f6;	/* 42b7f1: jle 0x42b7f6 */
	M32((DWORD)(m->eax + 0xfffffffcu)) = m->edi;	/* 42b7f3: mov dword ptr [eax - 4], edi */
L_42b7f6:
	{ DWORD a_ = M32((DWORD)(m->eax + 0xcu)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42b7f6: cmp dword ptr [eax + 0xc], edx */
	if (m->zf || m->sf != m->of) goto L_42b7fe;	/* 42b7f9: jle 0x42b7fe */
	M32((DWORD)(m->eax + 0xcu)) = m->edi;	/* 42b7fb: mov dword ptr [eax + 0xc], edi */
L_42b7fe:
	{ DWORD a_ = M32((DWORD)(m->eax + 0x8u)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42b7fe: cmp dword ptr [eax + 8], edx */
	if (m->zf || m->sf != m->of) goto L_42b806;	/* 42b801: jle 0x42b806 */
	M32((DWORD)(m->eax + 0x8u)) = m->edi;	/* 42b803: mov dword ptr [eax + 8], edi */
L_42b806:
	{ DWORD a_ = M32((DWORD)(m->eax + 0x10u)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42b806: cmp dword ptr [eax + 0x10], edx */
	if (m->zf || m->sf != m->of) goto L_42b80e;	/* 42b809: jle 0x42b80e */
	M32((DWORD)(m->eax + 0x10u)) = m->edi;	/* 42b80b: mov dword ptr [eax + 0x10], edi */
L_42b80e:
	{ DWORD a_ = M32((DWORD)(m->eax + 0x18u)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42b80e: cmp dword ptr [eax + 0x18], edx */
	if (m->zf || m->sf != m->of) goto L_42b816;	/* 42b811: jle 0x42b816 */
	M32((DWORD)(m->eax + 0x18u)) = m->edi;	/* 42b813: mov dword ptr [eax + 0x18], edi */
L_42b816:
	{ DWORD a_ = M32((DWORD)(m->eax + 0x14u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42b816: cmp dword ptr [eax + 0x14], esi */
	if (m->zf || m->sf != m->of) goto L_42b81e;	/* 42b819: jle 0x42b81e */
	M32((DWORD)(m->eax + 0x14u)) = m->edi;	/* 42b81b: mov dword ptr [eax + 0x14], edi */
L_42b81e:
	{ DWORD a_ = m->eax, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42b81e: add eax, 0x4c */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 42b821: dec ecx */
	if (!m->zf) goto L_42b7d8;	/* 42b822: jne 0x42b7d8 */
L_42b824:
	m->edi = M32(m->esp); m->esp += 4;	/* 42b824: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 42b825: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 42b826: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 42b827: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x1e4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42b828: add esp, 0x1e4 */
	m->esp += 4 + 0; return;	/* 42b82e: ret  */
}

/* profile_saveProgress (0x447010), lifted by tools/lift.py */
static void lift_447010(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x5b4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447010: sub esp, 0x5b4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 447016: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 447019: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x84u);	/* 44701b: lea edx, [esp + 0x84] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 447022: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 447023: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 447024: push edi */
	m->edi = 0x9dae7cu;	/* 447025: mov edi, 0x9dae7c */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44702a: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44702c: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44702e: sub edi, ecx */
	{ DWORD v_ = 0x4b2ab0u; m->esp -= 4; M32(m->esp) = v_; }	/* 447030: push 0x4b2ab0 */
	m->eax = m->ecx;	/* 447035: mov eax, ecx */
	m->esi = m->edi;	/* 447037: mov esi, edi */
	m->edi = m->edx;	/* 447039: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x94u);	/* 44703b: lea edx, [esp + 0x94] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 447042: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 447045: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 447047: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 447049: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44704b: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 44704e: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2ab4u;	/* 447050: mov edi, 0x4b2ab4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 447055: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 447058: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44705a: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44705c: sub edi, ecx */
	m->esi = m->edi;	/* 44705e: mov esi, edi */
	m->ebx = m->ecx;	/* 447060: mov ebx, ecx */
	m->edi = m->edx;	/* 447062: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 447064: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 447067: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 447069: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 44706b: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44706c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 44706f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->eax = M32((DWORD)(0x9f8d74u));	/* 447071: mov eax, dword ptr [0x9f8d74] */
	m->ecx = m->ebx;	/* 447076: mov ecx, ebx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 447078: and ecx, 3 */
	M32((DWORD)(0x9f8c58u)) = m->eax;	/* 44707b: mov dword ptr [0x9f8c58], eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 447080: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->esp + 0x94u);	/* 447082: lea ecx, [esp + 0x94] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 447089: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44708fu; native_call(m, 0x49e9cau);	/* 44708a: call 0x49e9ca */
	m->ebx = m->eax;	/* 44708f: mov ebx, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447091: add esp, 8 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 447094: test ebx, ebx */
	if (!m->zf) goto L_4470a7;	/* 447096: jne 0x4470a7 */
	m->edi = M32(m->esp); m->esp += 4;	/* 447098: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 447099: pop esi */
	M32((DWORD)(0x9f9008u)) = m->eax;	/* 44709a: mov dword ptr [0x9f9008], eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 44709f: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x5b4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4470a0: add esp, 0x5b4 */
	m->esp += 4 + 0; return;	/* 4470a6: ret  */
L_4470a7:
	m->ecx = 0x8u;	/* 4470a7: mov ecx, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4470ac: xor eax, eax */
	m->edi = 0x9f8fe8u;	/* 4470ae: mov edi, 0x9f8fe8 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4470b3: push ebx */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4470b4: rep stosd dword ptr es:[edi], eax */
	m->eax = M32((DWORD)(0x9f8c58u));	/* 4470b6: mov eax, dword ptr [0x9f8c58] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4470bb: or ecx, 0xffffffff */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4470be: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4470c0: push 4 */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 4470c2: lea edx, [eax + eax*8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4470c5: xor eax, eax */
	M32((DWORD)(m->esp + 0x18u)) = 0xfefefef7u;	/* 4470c7: mov dword ptr [esp + 0x18], 0xfefefef7 */
	m->edi = (DWORD)(m->edx*8 + 0x9f684cu);	/* 4470cf: lea edi, [edx*8 + 0x9f684c] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4470d6: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4470d8: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4470da: sub edi, ecx */
	m->eax = m->ecx;	/* 4470dc: mov eax, ecx */
	m->esi = m->edi;	/* 4470de: mov esi, edi */
	m->edi = 0x9f8fe8u;	/* 4470e0: mov edi, 0x9f8fe8 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4470e5: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4470e8: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4470ea: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4470ec: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4470ef: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->esp + 0x18u);	/* 4470f1: lea ecx, [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4470f5: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4470fbu; native_call(m, 0x49f58au);	/* 4470f6: call 0x49f58a */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4470fb: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4470fc: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4470fe: push 4 */
	{ DWORD v_ = 0x9f9008u; m->esp -= 4; M32(m->esp) = v_; }	/* 447100: push 0x9f9008 */
	m->esp -= 4; M32(m->esp) = 0x44710au; native_call(m, 0x49f58au);	/* 447105: call 0x49f58a */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44710a: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44710b: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 44710d: push 4 */
	{ DWORD v_ = 0x9f8c58u; m->esp -= 4; M32(m->esp) = v_; }	/* 44710f: push 0x9f8c58 */
	m->esp -= 4; M32(m->esp) = 0x447119u; native_call(m, 0x49f58au);	/* 447114: call 0x49f58a */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 447119: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44711a: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 44711c: push 4 */
	{ DWORD v_ = 0x9f8c4cu; m->esp -= 4; M32(m->esp) = v_; }	/* 44711e: push 0x9f8c4c */
	m->esp -= 4; M32(m->esp) = 0x447128u; native_call(m, 0x49f58au);	/* 447123: call 0x49f58a */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447128: add esp, 0x40 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44712b: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44712c: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 44712e: push 4 */
	{ DWORD v_ = 0x9f8c5cu; m->esp -= 4; M32(m->esp) = v_; }	/* 447130: push 0x9f8c5c */
	m->esp -= 4; M32(m->esp) = 0x44713au; native_call(m, 0x49f58au);	/* 447135: call 0x49f58a */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44713a: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44713b: push 1 */
	{ DWORD v_ = 0x20u; m->esp -= 4; M32(m->esp) = v_; }	/* 44713d: push 0x20 */
	{ DWORD v_ = 0x9f8fe8u; m->esp -= 4; M32(m->esp) = v_; }	/* 44713f: push 0x9f8fe8 */
	m->esp -= 4; M32(m->esp) = 0x447149u; native_call(m, 0x49f58au);	/* 447144: call 0x49f58a */
	m->eax = M32((DWORD)(0x9f9008u));	/* 447149: mov eax, dword ptr [0x9f9008] */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44714e: add esp, 0x20 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 447151: xor esi, esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 447153: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_447177;	/* 447155: jle 0x447177 */
	m->edi = 0x9f6848u;	/* 447157: mov edi, 0x9f6848 */
L_44715c:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44715c: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44715d: push 1 */
	{ DWORD v_ = 0x48u; m->esp -= 4; M32(m->esp) = v_; }	/* 44715f: push 0x48 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 447161: push edi */
	m->esp -= 4; M32(m->esp) = 0x447167u; native_call(m, 0x49f58au);	/* 447162: call 0x49f58a */
	m->eax = M32((DWORD)(0x9f9008u));	/* 447167: mov eax, dword ptr [0x9f9008] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44716c: add esp, 0x10 */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 44716f: inc esi */
	{ DWORD a_ = m->edi, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 447170: add edi, 0x48 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 447173: cmp esi, eax */
	if (m->sf != m->of) goto L_44715c;	/* 447175: jl 0x44715c */
L_447177:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 447177: push ebx */
	m->esp -= 4; M32(m->esp) = 0x44717du; native_call(m, 0x49e7e0u);	/* 447178: call 0x49e7e0 */
	m->esp -= 4; M32(m->esp) = 0x447182u; native_call(m, 0x4464b0u);	/* 44717d: call 0x4464b0 */
	{ DWORD v_ = 0x4b2adcu; m->esp -= 4; M32(m->esp) = v_; }	/* 447182: push 0x4b2adc */
	m->esp -= 4; M32(m->esp) = 0x44718cu; native_call(m, 0x49f8a6u);	/* 447187: call 0x49f8a6 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44718c: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44718f: test eax, eax */
	if (m->zf) goto L_4471aa;	/* 447191: je 0x4471aa */
	{ DWORD v_ = 0x4b2adcu; m->esp -= 4; M32(m->esp) = v_; }	/* 447193: push 0x4b2adc */
	m->esp -= 4; M32(m->esp) = 0x44719du; native_call(m, 0x49f94au);	/* 447198: call 0x49f94a */
	{ DWORD v_ = 0x4b2adcu; m->esp -= 4; M32(m->esp) = v_; }	/* 44719d: push 0x4b2adc */
	m->esp -= 4; M32(m->esp) = 0x4471a7u; native_call(m, 0x49f8a6u);	/* 4471a2: call 0x49f8a6 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4471a7: add esp, 8 */
L_4471aa:
	m->ecx = 0x20u;	/* 4471aa: mov ecx, 0x20 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4471af: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x10u);	/* 4471b1: lea edi, [esp + 0x10] */
	{ DWORD v_ = 0x4b2ab0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4471b5: push 0x4b2ab0 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4471ba: rep stosd dword ptr es:[edi], eax */
	m->eax = M32((DWORD)(0x9f8d74u));	/* 4471bc: mov eax, dword ptr [0x9f8d74] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4471c1: or ecx, 0xffffffff */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 4471c4: lea edx, [eax + eax*8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4471c7: xor eax, eax */
	m->edi = (DWORD)(m->edx*8 + 0x9f684cu);	/* 4471c9: lea edi, [edx*8 + 0x9f684c] */
	m->edx = (DWORD)(m->esp + 0x14u);	/* 4471d0: lea edx, [esp + 0x14] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4471d4: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4471d6: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4471d8: sub edi, ecx */
	m->eax = m->ecx;	/* 4471da: mov eax, ecx */
	m->esi = m->edi;	/* 4471dc: mov esi, edi */
	m->edi = m->edx;	/* 4471de: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x14u);	/* 4471e0: lea edx, [esp + 0x14] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4471e4: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4471e7: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4471e9: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4471eb: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4471ed: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4471f0: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2afcu;	/* 4471f2: mov edi, 0x4b2afc */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4471f7: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4471fa: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4471fc: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4471fe: sub edi, ecx */
	m->esi = m->edi;	/* 447200: mov esi, edi */
	m->ebx = m->ecx;	/* 447202: mov ebx, ecx */
	m->edi = m->edx;	/* 447204: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 447206: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 447209: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 44720b: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 44720d: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44720e: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 447211: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebx;	/* 447213: mov ecx, ebx */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 447215: lea eax, [esp + 0x14] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 447219: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44721c: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 44721d: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x447224u; native_call(m, 0x49e9cau);	/* 44721f: call 0x49e9ca */
	m->ebx = m->eax;	/* 447224: mov ebx, eax */
	m->eax = M32((DWORD)(0x9f8d74u));	/* 447226: mov eax, dword ptr [0x9f8d74] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44722b: add esp, 8 */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44722e: lea ecx, [eax + eax*8] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 447231: test ebx, ebx */
	m->edx = M32((DWORD)(m->ecx*8 + 0x9f688cu));	/* 447233: mov edx, dword ptr [ecx*8 + 0x9f688c] */
	M32((DWORD)(0x9f1818u)) = m->edx;	/* 44723a: mov dword ptr [0x9f1818], edx */
	if (m->zf) goto L_4472fb;	/* 447240: je 0x4472fb */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 447246: xor esi, esi */
L_447248:
	m->esp -= 4; M32(m->esp) = 0x44724du; native_call(m, 0x49f92cu);	/* 447248: call 0x49f92c */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 44724d: cdq  */
	m->ecx = 0xfeu;	/* 44724e: mov ecx, 0xfe */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 447253: idiv ecx */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 447255: inc esi */
	{ DWORD a_ = m->esi, b_ = 0x2710u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 447256: cmp esi, 0x2710 */
	M8((DWORD)(m->esi + 0x9f3ac3u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 44725c: mov byte ptr [esi + 0x9f3ac3], dl */
	if (m->sf != m->of) goto L_447248;	/* 447262: jl 0x447248 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 447264: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 447265: push 1 */
	{ DWORD v_ = 0x2710u; m->esp -= 4; M32(m->esp) = v_; }	/* 447267: push 0x2710 */
	{ DWORD v_ = 0x9f3ac4u; m->esp -= 4; M32(m->esp) = v_; }	/* 44726c: push 0x9f3ac4 */
	m->esp -= 4; M32(m->esp) = 0x447276u; native_call(m, 0x49f58au);	/* 447271: call 0x49f58a */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 447276: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 447277: push 1 */
	{ DWORD v_ = 0x2710u; m->esp -= 4; M32(m->esp) = v_; }	/* 447279: push 0x2710 */
	{ DWORD v_ = 0x9f3ac4u; m->esp -= 4; M32(m->esp) = v_; }	/* 44727e: push 0x9f3ac4 */
	m->esp -= 4; M32(m->esp) = 0x447288u; native_call(m, 0x49f58au);	/* 447283: call 0x49f58a */
	m->ecx = 0xebu;	/* 447288: mov ecx, 0xeb */
	m->esi = 0x9f1718u;	/* 44728d: mov esi, 0x9f1718 */
	m->edi = (DWORD)(m->esp + 0x234u);	/* 447292: lea edi, [esp + 0x234] */
	m->edx = (DWORD)(m->esp + 0x234u);	/* 447299: lea edx, [esp + 0x234] */
	{ DWORD v_ = 0x7eu; m->esp -= 4; M32(m->esp) = v_; }	/* 4472a0: push 0x7e */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4472a2: push edx */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4472a3: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x4472aau; native_call(m, 0x445ee0u);	/* 4472a5: call 0x445ee0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4472aa: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4472ab: push 1 */
	m->eax = (DWORD)(m->esp + 0x244u);	/* 4472ad: lea eax, [esp + 0x244] */
	{ DWORD v_ = 0x3acu; m->esp -= 4; M32(m->esp) = v_; }	/* 4472b4: push 0x3ac */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4472b9: push eax */
	m->esp -= 4; M32(m->esp) = 0x4472bfu; native_call(m, 0x49f58au);	/* 4472ba: call 0x49f58a */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4472bf: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4472c0: push 1 */
	{ DWORD v_ = 0x2710u; m->esp -= 4; M32(m->esp) = v_; }	/* 4472c2: push 0x2710 */
	{ DWORD v_ = 0x9f3ac4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4472c7: push 0x9f3ac4 */
	m->esp -= 4; M32(m->esp) = 0x4472d1u; native_call(m, 0x49f58au);	/* 4472cc: call 0x49f58a */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4472d1: add esp, 0x48 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4472d4: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4472d5: push 1 */
	{ DWORD v_ = 0x2710u; m->esp -= 4; M32(m->esp) = v_; }	/* 4472d7: push 0x2710 */
	{ DWORD v_ = 0x9f3ac4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4472dc: push 0x9f3ac4 */
	m->esp -= 4; M32(m->esp) = 0x4472e6u; native_call(m, 0x49f58au);	/* 4472e1: call 0x49f58a */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4472e6: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4472e7: push 1 */
	{ DWORD v_ = 0x1387u; m->esp -= 4; M32(m->esp) = v_; }	/* 4472e9: push 0x1387 */
	{ DWORD v_ = 0x9f3ac4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4472ee: push 0x9f3ac4 */
	m->esp -= 4; M32(m->esp) = 0x4472f8u; native_call(m, 0x49f58au);	/* 4472f3: call 0x49f58a */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4472f8: add esp, 0x20 */
L_4472fb:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4472fb: push ebx */
	m->esp -= 4; M32(m->esp) = 0x447301u; native_call(m, 0x49e7e0u);	/* 4472fc: call 0x49e7e0 */
	{ DWORD v_ = 0x4b2a80u; m->esp -= 4; M32(m->esp) = v_; }	/* 447301: push 0x4b2a80 */
	m->esp -= 4; M32(m->esp) = 0x44730bu; native_call(m, 0x49f8a6u);	/* 447306: call 0x49f8a6 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44730b: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 44730e: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44730f: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 447310: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x5b4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447311: add esp, 0x5b4 */
	m->esp += 4 + 0; return;	/* 447317: ret  */
}

/* profile_load (0x446590), lifted by tools/lift.py */
static void lift_446590(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x5b8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 446590: sub esp, 0x5b8 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 446596: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 446599: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x88u);	/* 44659b: lea edx, [esp + 0x88] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4465a2: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4465a3: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4465a4: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4465a5: push edi */
	m->edi = 0x9dae7cu;	/* 4465a6: mov edi, 0x9dae7c */
	{ DWORD v_ = 0x4b2ab0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4465ab: push 0x4b2ab0 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4465b0: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4465b2: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4465b4: sub edi, ecx */
	m->eax = m->ecx;	/* 4465b6: mov eax, ecx */
	m->esi = m->edi;	/* 4465b8: mov esi, edi */
	m->edi = m->edx;	/* 4465ba: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x9cu);	/* 4465bc: lea edx, [esp + 0x9c] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4465c3: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4465c6: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4465c8: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4465ca: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4465cc: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4465cf: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2ab4u;	/* 4465d1: mov edi, 0x4b2ab4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4465d6: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4465d9: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4465db: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4465dd: sub edi, ecx */
	m->esi = m->edi;	/* 4465df: mov esi, edi */
	m->ebx = m->ecx;	/* 4465e1: mov ebx, ecx */
	m->edi = m->edx;	/* 4465e3: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4465e5: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4465e8: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 4465ea: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4465ec: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4465ed: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4465f0: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->eax = M32((DWORD)(0x9f8d74u));	/* 4465f2: mov eax, dword ptr [0x9f8d74] */
	m->ecx = m->ebx;	/* 4465f7: mov ecx, ebx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4465f9: and ecx, 3 */
	M32((DWORD)(0x9f8c58u)) = m->eax;	/* 4465fc: mov dword ptr [0x9f8c58], eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 446601: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->esp + 0x9cu);	/* 446603: lea ecx, [esp + 0x9c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44660a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x446610u; native_call(m, 0x49e9cau);	/* 44660b: call 0x49e9ca */
	m->ebx = m->eax;	/* 446610: mov ebx, eax */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 446612: xor ebp, ebp */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 446614: add esp, 8 */
	{ DWORD a_ = m->ebx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 446617: cmp ebx, ebp */
	if (!m->zf) goto L_44662c;	/* 446619: jne 0x44662c */
	m->edi = M32(m->esp); m->esp += 4;	/* 44661b: pop edi */
	M32((DWORD)(0x9f9008u)) = m->ebp;	/* 44661c: mov dword ptr [0x9f9008], ebp */
	m->esi = M32(m->esp); m->esp += 4;	/* 446622: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 446623: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 446624: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x5b8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 446625: add esp, 0x5b8 */
	m->esp += 4 + 0; return;	/* 44662b: ret  */
L_44662c:
	m->ecx = 0x8u;	/* 44662c: mov ecx, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 446631: xor eax, eax */
	m->edi = 0x9f8fe8u;	/* 446633: mov edi, 0x9f8fe8 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 446638: push ebx */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 446639: rep stosd dword ptr es:[edi], eax */
	m->eax = M32((DWORD)(0x9f8c58u));	/* 44663b: mov eax, dword ptr [0x9f8c58] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 446640: or ecx, 0xffffffff */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 446643: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 446645: push 4 */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 446647: lea edx, [eax + eax*8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44664a: xor eax, eax */
	M32((DWORD)(m->esp + 0x1cu)) = 0xfefefef7u;	/* 44664c: mov dword ptr [esp + 0x1c], 0xfefefef7 */
	m->edi = (DWORD)(m->edx*8 + 0x9f684cu);	/* 446654: lea edi, [edx*8 + 0x9f684c] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44665b: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44665d: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44665f: sub edi, ecx */
	m->eax = m->ecx;	/* 446661: mov eax, ecx */
	m->esi = m->edi;	/* 446663: mov esi, edi */
	m->edi = 0x9f8fe8u;	/* 446665: mov edi, 0x9f8fe8 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44666a: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 44666d: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 44666f: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 446671: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 446674: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 446676: lea ecx, [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44667a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x446680u; native_call(m, 0x49f58au);	/* 44667b: call 0x49f58a */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 446680: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 446681: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 446683: push 4 */
	{ DWORD v_ = 0x9f9008u; m->esp -= 4; M32(m->esp) = v_; }	/* 446685: push 0x9f9008 */
	m->esp -= 4; M32(m->esp) = 0x44668fu; native_call(m, 0x49f58au);	/* 44668a: call 0x49f58a */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44668f: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 446690: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 446692: push 4 */
	{ DWORD v_ = 0x9f8c58u; m->esp -= 4; M32(m->esp) = v_; }	/* 446694: push 0x9f8c58 */
	m->esp -= 4; M32(m->esp) = 0x44669eu; native_call(m, 0x49f58au);	/* 446699: call 0x49f58a */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44669e: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44669f: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4466a1: push 4 */
	{ DWORD v_ = 0x9f8c4cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4466a3: push 0x9f8c4c */
	m->esp -= 4; M32(m->esp) = 0x4466adu; native_call(m, 0x49f58au);	/* 4466a8: call 0x49f58a */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4466ad: add esp, 0x40 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4466b0: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4466b1: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4466b3: push 4 */
	{ DWORD v_ = 0x9f8c5cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4466b5: push 0x9f8c5c */
	m->esp -= 4; M32(m->esp) = 0x4466bfu; native_call(m, 0x49f58au);	/* 4466ba: call 0x49f58a */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4466bf: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4466c0: push 1 */
	{ DWORD v_ = 0x20u; m->esp -= 4; M32(m->esp) = v_; }	/* 4466c2: push 0x20 */
	{ DWORD v_ = 0x9f8fe8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4466c4: push 0x9f8fe8 */
	m->esp -= 4; M32(m->esp) = 0x4466ceu; native_call(m, 0x49f58au);	/* 4466c9: call 0x49f58a */
	m->eax = M32((DWORD)(0x9f9008u));	/* 4466ce: mov eax, dword ptr [0x9f9008] */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4466d3: add esp, 0x20 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 4466d6: xor esi, esi */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4466d8: cmp eax, ebp */
	if (m->zf || m->sf != m->of) goto L_4466fc;	/* 4466da: jle 0x4466fc */
	m->edi = 0x9f6848u;	/* 4466dc: mov edi, 0x9f6848 */
L_4466e1:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4466e1: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4466e2: push 1 */
	{ DWORD v_ = 0x48u; m->esp -= 4; M32(m->esp) = v_; }	/* 4466e4: push 0x48 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4466e6: push edi */
	m->esp -= 4; M32(m->esp) = 0x4466ecu; native_call(m, 0x49f58au);	/* 4466e7: call 0x49f58a */
	m->eax = M32((DWORD)(0x9f9008u));	/* 4466ec: mov eax, dword ptr [0x9f9008] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4466f1: add esp, 0x10 */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 4466f4: inc esi */
	{ DWORD a_ = m->edi, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4466f5: add edi, 0x48 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4466f8: cmp esi, eax */
	if (m->sf != m->of) goto L_4466e1;	/* 4466fa: jl 0x4466e1 */
L_4466fc:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4466fc: push ebx */
	m->esp -= 4; M32(m->esp) = 0x446702u; native_call(m, 0x49e7e0u);	/* 4466fd: call 0x49e7e0 */
	m->esp -= 4; M32(m->esp) = 0x446707u; native_call(m, 0x4464b0u);	/* 446702: call 0x4464b0 */
	{ DWORD v_ = 0x4b2adcu; m->esp -= 4; M32(m->esp) = v_; }	/* 446707: push 0x4b2adc */
	m->esp -= 4; M32(m->esp) = 0x446711u; native_call(m, 0x49f8a6u);	/* 44670c: call 0x49f8a6 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 446711: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 446714: test eax, eax */
	if (m->zf) goto L_44672f;	/* 446716: je 0x44672f */
	{ DWORD v_ = 0x4b2adcu; m->esp -= 4; M32(m->esp) = v_; }	/* 446718: push 0x4b2adc */
	m->esp -= 4; M32(m->esp) = 0x446722u; native_call(m, 0x49f94au);	/* 44671d: call 0x49f94a */
	{ DWORD v_ = 0x4b2adcu; m->esp -= 4; M32(m->esp) = v_; }	/* 446722: push 0x4b2adc */
	m->esp -= 4; M32(m->esp) = 0x44672cu; native_call(m, 0x49f8a6u);	/* 446727: call 0x49f8a6 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44672c: add esp, 8 */
L_44672f:
	m->edx = M32((DWORD)(0x9f8d74u));	/* 44672f: mov edx, dword ptr [0x9f8d74] */
	m->ecx = 0x20u;	/* 446735: mov ecx, 0x20 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44673a: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x18u);	/* 44673c: lea edi, [esp + 0x18] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 446740: rep stosd dword ptr es:[edi], eax */
	m->edx = (DWORD)(m->edx + m->edx*8 + 0x0u);	/* 446742: lea edx, [edx + edx*8] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 446745: or ecx, 0xffffffff */
	{ DWORD a_ = m->edx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 446748: shl edx, 3 */
	m->ebx = (DWORD)(m->esp + 0x18u);	/* 44674b: lea ebx, [esp + 0x18] */
	m->edi = (DWORD)(m->edx + 0x9f684cu);	/* 44674f: lea edi, [edx + 0x9f684c] */
	M32((DWORD)(m->esp + 0x14u)) = m->edi;	/* 446755: mov dword ptr [esp + 0x14], edi */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 446759: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44675b: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44675d: sub edi, ecx */
	m->eax = m->ecx;	/* 44675f: mov eax, ecx */
	m->esi = m->edi;	/* 446761: mov esi, edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 446763: shr ecx, 2 */
	m->edi = m->ebx;	/* 446766: mov edi, ebx */
	m->ebx = (DWORD)(m->esp + 0x18u);	/* 446768: lea ebx, [esp + 0x18] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 44676c: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 44676e: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 446770: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 446772: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 446775: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 446777: or ecx, 0xffffffff */
	m->edi = 0x4b2afcu;	/* 44677a: mov edi, 0x4b2afc */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44677f: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 446781: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 446783: sub edi, ecx */
	m->esi = m->edi;	/* 446785: mov esi, edi */
	m->edi = m->ebx;	/* 446787: mov edi, ebx */
	m->ebx = m->ecx;	/* 446789: mov ebx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44678b: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44678e: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 446790: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 446792: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 446793: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 446796: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebx;	/* 446798: mov ecx, ebx */
	{ DWORD a_ = m->ebx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 44679a: or ebx, 0xffffffff */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44679d: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4467a0: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = 0x20u;	/* 4467a2: mov ecx, 0x20 */
	m->edi = 0x9f1718u;	/* 4467a7: mov edi, 0x9f1718 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4467ac: rep stosd dword ptr es:[edi], eax */
	m->edi = 0x4b0fa0u;	/* 4467ae: mov edi, 0x4b0fa0 */
	m->ecx = m->ebx;	/* 4467b3: mov ecx, ebx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4467b5: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4467b7: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4467b9: sub edi, ecx */
	m->eax = m->ecx;	/* 4467bb: mov eax, ecx */
	m->esi = m->edi;	/* 4467bd: mov esi, edi */
	m->edi = 0x9f1718u;	/* 4467bf: mov edi, 0x9f1718 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4467c4: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4467c7: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4467c9: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4467cb: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4467cd: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4467d0: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esi = M32((DWORD)(m->esp + 0x14u));	/* 4467d2: mov esi, dword ptr [esp + 0x14] */
	m->ecx = 0x20u;	/* 4467d6: mov ecx, 0x20 */
	m->edi = 0x9f1798u;	/* 4467db: mov edi, 0x9f1798 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4467e0: rep stosd dword ptr es:[edi], eax */
	m->ecx = 0x20u;	/* 4467e2: mov ecx, 0x20 */
	m->edi = 0x9f1798u;	/* 4467e7: mov edi, 0x9f1798 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4467ec: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = M32((DWORD)(m->edx + 0x9f688cu));	/* 4467ee: mov ecx, dword ptr [edx + 0x9f688c] */
	m->edi = 0x9f1820u;	/* 4467f4: mov edi, 0x9f1820 */
	M32((DWORD)(0x9f1818u)) = m->ecx;	/* 4467f9: mov dword ptr [0x9f1818], ecx */
	m->ecx = 0x64u;	/* 4467ff: mov ecx, 0x64 */
	M32((DWORD)(0x9f181cu)) = m->ebp;	/* 446804: mov dword ptr [0x9f181c], ebp */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44680a: xor edx, edx */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 44680c: rep stosd dword ptr es:[edi], eax */
	m->ecx = 0x10u;	/* 44680e: mov ecx, 0x10 */
	m->edi = 0x9f19b0u;	/* 446813: mov edi, 0x9f19b0 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 446818: rep stosd dword ptr es:[edi], eax */
	M32((DWORD)(0x9f19f0u)) = m->edx;	/* 44681a: mov dword ptr [0x9f19f0], edx */
	M32((DWORD)(0x9f1a0cu)) = m->eax;	/* 446820: mov dword ptr [0x9f1a0c], eax */
	M32((DWORD)(0x9f19f4u)) = m->edx;	/* 446825: mov dword ptr [0x9f19f4], edx */
	M32((DWORD)(0x9f1a10u)) = m->eax;	/* 44682b: mov dword ptr [0x9f1a10], eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 446830: xor ecx, ecx */
	M32((DWORD)(0x9f1a2cu)) = m->ecx;	/* 446832: mov dword ptr [0x9f1a2c], ecx */
	m->edi = 0x4b2af4u;	/* 446838: mov edi, 0x4b2af4 */
	M32((DWORD)(0x9f1a30u)) = m->ecx;	/* 44683d: mov dword ptr [0x9f1a30], ecx */
	m->ecx = m->ebx;	/* 446843: mov ecx, ebx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 446845: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 446847: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 446849: sub edi, ecx */
	m->edx = m->ecx;	/* 44684b: mov edx, ecx */
	m->esi = m->edi;	/* 44684d: mov esi, edi */
	m->edi = 0x9f19f0u;	/* 44684f: mov edi, 0x9f19f0 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 446854: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 446857: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 446859: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44685b: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 44685e: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2aecu;	/* 446860: mov edi, 0x4b2aec */
	m->ecx = m->ebx;	/* 446865: mov ecx, ebx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 446867: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 446869: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44686b: sub edi, ecx */
	m->eax = m->ecx;	/* 44686d: mov eax, ecx */
	m->esi = m->edi;	/* 44686f: mov esi, edi */
	m->edi = 0x9f1a0cu;	/* 446871: mov edi, 0x9f1a0c */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 446876: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 446879: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 44687b: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44687d: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44687f: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 446882: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2ae4u;	/* 446884: mov edi, 0x4b2ae4 */
	m->ecx = m->ebx;	/* 446889: mov ecx, ebx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44688b: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44688d: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44688f: sub edi, ecx */
	m->eax = 0x9f1a38u;	/* 446891: mov eax, 0x9f1a38 */
	m->edx = m->ecx;	/* 446896: mov edx, ecx */
	m->esi = m->edi;	/* 446898: mov esi, edi */
	m->edi = 0x9f1a2cu;	/* 44689a: mov edi, 0x9f1a2c */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44689f: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4468a2: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4468a4: mov ecx, edx */
	m->edx = 0x3ecccccdu;	/* 4468a6: mov edx, 0x3ecccccd */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4468ab: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4468ae: rep movsb byte ptr es:[edi], byte ptr [esi] */
	M32((DWORD)(0x9f19f8u)) = m->ebp;	/* 4468b0: mov dword ptr [0x9f19f8], ebp */
	M32((DWORD)(0x9f19fcu)) = m->ebp;	/* 4468b6: mov dword ptr [0x9f19fc], ebp */
	M32((DWORD)(0x9f1a00u)) = m->ebp;	/* 4468bc: mov dword ptr [0x9f1a00], ebp */
	M32((DWORD)(0x9f1a04u)) = m->ebp;	/* 4468c2: mov dword ptr [0x9f1a04], ebp */
	M32((DWORD)(0x9f1a08u)) = m->ebp;	/* 4468c8: mov dword ptr [0x9f1a08], ebp */
	M32((DWORD)(0x9f1a1cu)) = m->ebp;	/* 4468ce: mov dword ptr [0x9f1a1c], ebp */
	M32((DWORD)(0x9f1a20u)) = 0x2u;	/* 4468d4: mov dword ptr [0x9f1a20], 2 */
	M32((DWORD)(0x9f1a24u)) = 0x8u;	/* 4468de: mov dword ptr [0x9f1a24], 8 */
	M32((DWORD)(0x9f1a28u)) = m->ebx;	/* 4468e8: mov dword ptr [0x9f1a28], ebx */
	M32((DWORD)(0x9f1a18u)) = 0x11u;	/* 4468ee: mov dword ptr [0x9f1a18], 0x11 */
	M32((DWORD)(0x9f1a14u)) = m->ebx;	/* 4468f8: mov dword ptr [0x9f1a14], ebx */
	m->ecx = 0x432a0000u;	/* 4468fe: mov ecx, 0x432a0000 */
L_446903:
	M32((DWORD)(m->eax + 0xfffffffcu)) = m->ecx;	/* 446903: mov dword ptr [eax - 4], ecx */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 446906: mov dword ptr [eax], edx */
	M32((DWORD)(m->eax + 0x4u)) = m->ebp;	/* 446908: mov dword ptr [eax + 4], ebp */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 44690b: mov dword ptr [eax + 8], ecx */
	M32((DWORD)(m->eax + 0xcu)) = m->edx;	/* 44690e: mov dword ptr [eax + 0xc], edx */
	M32((DWORD)(m->eax + 0x10u)) = m->ebp;	/* 446911: mov dword ptr [eax + 0x10], ebp */
	{ DWORD a_ = m->eax, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 446914: add eax, 0x18 */
	{ DWORD a_ = m->eax, b_ = 0x9f1ac8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 446917: cmp eax, 0x9f1ac8 */
	if (m->sf != m->of) goto L_446903;	/* 44691c: jl 0x446903 */
	m->eax = (DWORD)(m->esp + 0x18u);	/* 44691e: lea eax, [esp + 0x18] */
	{ DWORD v_ = 0x4b2ab0u; m->esp -= 4; M32(m->esp) = v_; }	/* 446922: push 0x4b2ab0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 446927: push eax */
	m->esp -= 4; M32(m->esp) = 0x44692du; native_call(m, 0x49e9cau);	/* 446928: call 0x49e9ca */
	m->ebx = m->eax;	/* 44692d: mov ebx, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44692f: add esp, 8 */
	{ DWORD a_ = m->ebx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 446932: cmp ebx, ebp */
	if (m->zf) goto L_4469ed;	/* 446934: je 0x4469ed */
L_44693a:
	m->esp -= 4; M32(m->esp) = 0x44693fu; native_call(m, 0x49f92cu);	/* 44693a: call 0x49f92c */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 44693f: cdq  */
	m->ecx = 0xfeu;	/* 446940: mov ecx, 0xfe */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 446945: idiv ecx */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 446947: inc ebp */
	{ DWORD a_ = m->ebp, b_ = 0x2710u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 446948: cmp ebp, 0x2710 */
	M8((DWORD)(m->ebp + 0x9f3ac3u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 44694e: mov byte ptr [ebp + 0x9f3ac3], dl */
	if (m->sf != m->of) goto L_44693a;	/* 446954: jl 0x44693a */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 446956: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 446957: push 1 */
	{ DWORD v_ = 0x2710u; m->esp -= 4; M32(m->esp) = v_; }	/* 446959: push 0x2710 */
	{ DWORD v_ = 0x9f3ac4u; m->esp -= 4; M32(m->esp) = v_; }	/* 44695e: push 0x9f3ac4 */
	m->esp -= 4; M32(m->esp) = 0x446968u; native_call(m, 0x49f58au);	/* 446963: call 0x49f58a */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 446968: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 446969: push 1 */
	{ DWORD v_ = 0x2710u; m->esp -= 4; M32(m->esp) = v_; }	/* 44696b: push 0x2710 */
	{ DWORD v_ = 0x9f3ac4u; m->esp -= 4; M32(m->esp) = v_; }	/* 446970: push 0x9f3ac4 */
	m->esp -= 4; M32(m->esp) = 0x44697au; native_call(m, 0x49f58au);	/* 446975: call 0x49f58a */
	m->ecx = 0xebu;	/* 44697a: mov ecx, 0xeb */
	m->esi = 0x9f1718u;	/* 44697f: mov esi, 0x9f1718 */
	m->edi = (DWORD)(m->esp + 0x23cu);	/* 446984: lea edi, [esp + 0x23c] */
	m->edx = (DWORD)(m->esp + 0x23cu);	/* 44698b: lea edx, [esp + 0x23c] */
	{ DWORD v_ = 0x7eu; m->esp -= 4; M32(m->esp) = v_; }	/* 446992: push 0x7e */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 446994: push edx */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 446995: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x44699cu; native_call(m, 0x445ee0u);	/* 446997: call 0x445ee0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44699c: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44699d: push 1 */
	m->eax = (DWORD)(m->esp + 0x24cu);	/* 44699f: lea eax, [esp + 0x24c] */
	{ DWORD v_ = 0x3acu; m->esp -= 4; M32(m->esp) = v_; }	/* 4469a6: push 0x3ac */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4469ab: push eax */
	m->esp -= 4; M32(m->esp) = 0x4469b1u; native_call(m, 0x49f58au);	/* 4469ac: call 0x49f58a */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4469b1: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4469b2: push 1 */
	{ DWORD v_ = 0x2710u; m->esp -= 4; M32(m->esp) = v_; }	/* 4469b4: push 0x2710 */
	{ DWORD v_ = 0x9f3ac4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4469b9: push 0x9f3ac4 */
	m->esp -= 4; M32(m->esp) = 0x4469c3u; native_call(m, 0x49f58au);	/* 4469be: call 0x49f58a */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4469c3: add esp, 0x48 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4469c6: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4469c7: push 1 */
	{ DWORD v_ = 0x2710u; m->esp -= 4; M32(m->esp) = v_; }	/* 4469c9: push 0x2710 */
	{ DWORD v_ = 0x9f3ac4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4469ce: push 0x9f3ac4 */
	m->esp -= 4; M32(m->esp) = 0x4469d8u; native_call(m, 0x49f58au);	/* 4469d3: call 0x49f58a */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4469d8: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4469d9: push 1 */
	{ DWORD v_ = 0x1387u; m->esp -= 4; M32(m->esp) = v_; }	/* 4469db: push 0x1387 */
	{ DWORD v_ = 0x9f3ac4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4469e0: push 0x9f3ac4 */
	m->esp -= 4; M32(m->esp) = 0x4469eau; native_call(m, 0x49f58au);	/* 4469e5: call 0x49f58a */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4469ea: add esp, 0x20 */
L_4469ed:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4469ed: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4469f3u; native_call(m, 0x49e7e0u);	/* 4469ee: call 0x49e7e0 */
	{ DWORD v_ = 0x4b2a80u; m->esp -= 4; M32(m->esp) = v_; }	/* 4469f3: push 0x4b2a80 */
	m->esp -= 4; M32(m->esp) = 0x4469fdu; native_call(m, 0x49f8a6u);	/* 4469f8: call 0x49f8a6 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4469fd: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 446a00: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 446a01: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 446a02: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 446a03: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x5b8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 446a04: add esp, 0x5b8 */
	m->esp += 4 + 0; return;	/* 446a0a: ret  */
}

/* profile_save (0x446a10), lifted by tools/lift.py */
static void lift_446a10(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x634u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 446a10: sub esp, 0x634 */
	m->ecx = 0x8u;	/* 446a16: mov ecx, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 446a1b: xor eax, eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 446a1d: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 446a1e: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 446a1f: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 446a20: push edi */
	m->edi = 0x9f8fe8u;	/* 446a21: mov edi, 0x9f8fe8 */
	{ DWORD v_ = 0x4b2ab0u; m->esp -= 4; M32(m->esp) = v_; }	/* 446a26: push 0x4b2ab0 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 446a2b: rep stosd dword ptr es:[edi], eax */
	m->eax = M32((DWORD)(0x9f8c58u));	/* 446a2d: mov eax, dword ptr [0x9f8c58] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 446a32: or ecx, 0xffffffff */
	m->eax = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 446a35: lea eax, [eax + eax*8] */
	m->edi = (DWORD)(m->eax*8 + 0x9f684cu);	/* 446a38: lea edi, [eax*8 + 0x9f684c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 446a3f: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 446a41: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 446a43: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 446a45: sub edi, ecx */
	m->edx = m->ecx;	/* 446a47: mov edx, ecx */
	m->esi = m->edi;	/* 446a49: mov esi, edi */
	m->edi = 0x9f8fe8u;	/* 446a4b: mov edi, 0x9f8fe8 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 446a50: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 446a53: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 446a55: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x118u);	/* 446a57: lea edx, [esp + 0x118] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 446a5e: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 446a61: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x9dae7cu;	/* 446a63: mov edi, 0x9dae7c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 446a68: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 446a6b: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 446a6d: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 446a6f: sub edi, ecx */
	m->eax = m->ecx;	/* 446a71: mov eax, ecx */
	m->esi = m->edi;	/* 446a73: mov esi, edi */
	m->edi = m->edx;	/* 446a75: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x118u);	/* 446a77: lea edx, [esp + 0x118] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 446a7e: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 446a81: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 446a83: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 446a85: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 446a87: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 446a8a: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2ab4u;	/* 446a8c: mov edi, 0x4b2ab4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 446a91: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 446a94: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 446a96: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 446a98: sub edi, ecx */
	m->esi = m->edi;	/* 446a9a: mov esi, edi */
	m->ebx = m->ecx;	/* 446a9c: mov ebx, ecx */
	m->edi = m->edx;	/* 446a9e: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 446aa0: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 446aa3: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 446aa5: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 446aa7: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 446aa8: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 446aab: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->eax = M32((DWORD)(0x9f8d74u));	/* 446aad: mov eax, dword ptr [0x9f8d74] */
	m->ecx = m->ebx;	/* 446ab2: mov ecx, ebx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 446ab4: and ecx, 3 */
	M32((DWORD)(0x9f8c58u)) = m->eax;	/* 446ab7: mov dword ptr [0x9f8c58], eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 446abc: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->esp + 0x118u);	/* 446abe: lea ecx, [esp + 0x118] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 446ac5: push ecx */
	m->esp -= 4; M32(m->esp) = 0x446acbu; native_call(m, 0x49e9cau);	/* 446ac6: call 0x49e9ca */
	m->ebp = m->eax;	/* 446acb: mov ebp, eax */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 446acd: xor ebx, ebx */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 446acf: add esp, 8 */
	{ DWORD a_ = m->ebp, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 446ad2: cmp ebp, ebx */
	if (!m->zf) goto L_446ae7;	/* 446ad4: jne 0x446ae7 */
	m->edi = M32(m->esp); m->esp += 4;	/* 446ad6: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 446ad7: pop esi */
	M32((DWORD)(0x9f9008u)) = m->ebx;	/* 446ad8: mov dword ptr [0x9f9008], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 446ade: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 446adf: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x634u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 446ae0: add esp, 0x634 */
	m->esp += 4 + 0; return;	/* 446ae6: ret  */
L_446ae7:
	m->ecx = 0x8u;	/* 446ae7: mov ecx, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 446aec: xor eax, eax */
	m->edi = 0x9f8fe8u;	/* 446aee: mov edi, 0x9f8fe8 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 446af3: push ebp */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 446af4: rep stosd dword ptr es:[edi], eax */
	m->eax = M32((DWORD)(0x9f8c58u));	/* 446af6: mov eax, dword ptr [0x9f8c58] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 446afb: or ecx, 0xffffffff */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 446afe: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 446b00: push 4 */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 446b02: lea edx, [eax + eax*8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 446b05: xor eax, eax */
	M32((DWORD)(m->esp + 0x1cu)) = 0xfefefef7u;	/* 446b07: mov dword ptr [esp + 0x1c], 0xfefefef7 */
	m->edi = (DWORD)(m->edx*8 + 0x9f684cu);	/* 446b0f: lea edi, [edx*8 + 0x9f684c] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 446b16: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 446b18: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 446b1a: sub edi, ecx */
	m->eax = m->ecx;	/* 446b1c: mov eax, ecx */
	m->esi = m->edi;	/* 446b1e: mov esi, edi */
	m->edi = 0x9f8fe8u;	/* 446b20: mov edi, 0x9f8fe8 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 446b25: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 446b28: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 446b2a: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 446b2c: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 446b2f: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 446b31: lea ecx, [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 446b35: push ecx */
	m->esp -= 4; M32(m->esp) = 0x446b3bu; native_call(m, 0x49f58au);	/* 446b36: call 0x49f58a */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 446b3b: push ebp */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 446b3c: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 446b3e: push 4 */
	{ DWORD v_ = 0x9f9008u; m->esp -= 4; M32(m->esp) = v_; }	/* 446b40: push 0x9f9008 */
	m->esp -= 4; M32(m->esp) = 0x446b4au; native_call(m, 0x49f58au);	/* 446b45: call 0x49f58a */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 446b4a: push ebp */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 446b4b: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 446b4d: push 4 */
	{ DWORD v_ = 0x9f8c58u; m->esp -= 4; M32(m->esp) = v_; }	/* 446b4f: push 0x9f8c58 */
	m->esp -= 4; M32(m->esp) = 0x446b59u; native_call(m, 0x49f58au);	/* 446b54: call 0x49f58a */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 446b59: push ebp */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 446b5a: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 446b5c: push 4 */
	{ DWORD v_ = 0x9f8c4cu; m->esp -= 4; M32(m->esp) = v_; }	/* 446b5e: push 0x9f8c4c */
	m->esp -= 4; M32(m->esp) = 0x446b68u; native_call(m, 0x49f58au);	/* 446b63: call 0x49f58a */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 446b68: add esp, 0x40 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 446b6b: push ebp */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 446b6c: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 446b6e: push 4 */
	{ DWORD v_ = 0x9f8c5cu; m->esp -= 4; M32(m->esp) = v_; }	/* 446b70: push 0x9f8c5c */
	m->esp -= 4; M32(m->esp) = 0x446b7au; native_call(m, 0x49f58au);	/* 446b75: call 0x49f58a */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 446b7a: push ebp */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 446b7b: push 1 */
	{ DWORD v_ = 0x20u; m->esp -= 4; M32(m->esp) = v_; }	/* 446b7d: push 0x20 */
	{ DWORD v_ = 0x9f8fe8u; m->esp -= 4; M32(m->esp) = v_; }	/* 446b7f: push 0x9f8fe8 */
	m->esp -= 4; M32(m->esp) = 0x446b89u; native_call(m, 0x49f58au);	/* 446b84: call 0x49f58a */
	m->eax = M32((DWORD)(0x9f9008u));	/* 446b89: mov eax, dword ptr [0x9f9008] */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 446b8e: add esp, 0x20 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 446b91: xor esi, esi */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 446b93: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_446bb7;	/* 446b95: jle 0x446bb7 */
	m->edi = 0x9f6848u;	/* 446b97: mov edi, 0x9f6848 */
L_446b9c:
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 446b9c: push ebp */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 446b9d: push 1 */
	{ DWORD v_ = 0x48u; m->esp -= 4; M32(m->esp) = v_; }	/* 446b9f: push 0x48 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 446ba1: push edi */
	m->esp -= 4; M32(m->esp) = 0x446ba7u; native_call(m, 0x49f58au);	/* 446ba2: call 0x49f58a */
	m->eax = M32((DWORD)(0x9f9008u));	/* 446ba7: mov eax, dword ptr [0x9f9008] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 446bac: add esp, 0x10 */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 446baf: inc esi */
	{ DWORD a_ = m->edi, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 446bb0: add edi, 0x48 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 446bb3: cmp esi, eax */
	if (m->sf != m->of) goto L_446b9c;	/* 446bb5: jl 0x446b9c */
L_446bb7:
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 446bb7: push ebp */
	m->esp -= 4; M32(m->esp) = 0x446bbdu; native_call(m, 0x49e7e0u);	/* 446bb8: call 0x49e7e0 */
	{ DWORD v_ = 0x4b2adcu; m->esp -= 4; M32(m->esp) = v_; }	/* 446bbd: push 0x4b2adc */
	m->esp -= 4; M32(m->esp) = 0x446bc7u; native_call(m, 0x49f8a6u);	/* 446bc2: call 0x49f8a6 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 446bc7: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 446bca: test eax, eax */
	if (m->zf) goto L_446be5;	/* 446bcc: je 0x446be5 */
	{ DWORD v_ = 0x4b2adcu; m->esp -= 4; M32(m->esp) = v_; }	/* 446bce: push 0x4b2adc */
	m->esp -= 4; M32(m->esp) = 0x446bd8u; native_call(m, 0x49f94au);	/* 446bd3: call 0x49f94a */
	{ DWORD v_ = 0x4b2adcu; m->esp -= 4; M32(m->esp) = v_; }	/* 446bd8: push 0x4b2adc */
	m->esp -= 4; M32(m->esp) = 0x446be2u; native_call(m, 0x49f8a6u);	/* 446bdd: call 0x49f8a6 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 446be2: add esp, 8 */
L_446be5:
	m->ecx = 0x20u;	/* 446be5: mov ecx, 0x20 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 446bea: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x14u);	/* 446bec: lea edi, [esp + 0x14] */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 446bf0: push 0x4ad170 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 446bf5: rep stosd dword ptr es:[edi], eax */
	m->eax = M32((DWORD)(0x9f8d74u));	/* 446bf7: mov eax, dword ptr [0x9f8d74] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 446bfc: or ecx, 0xffffffff */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 446bff: lea edx, [eax + eax*8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 446c02: xor eax, eax */
	m->edi = (DWORD)(m->edx*8 + 0x9f684cu);	/* 446c04: lea edi, [edx*8 + 0x9f684c] */
	m->edx = (DWORD)(m->esp + 0x18u);	/* 446c0b: lea edx, [esp + 0x18] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 446c0f: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 446c11: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 446c13: sub edi, ecx */
	m->eax = m->ecx;	/* 446c15: mov eax, ecx */
	m->esi = m->edi;	/* 446c17: mov esi, edi */
	m->edi = m->edx;	/* 446c19: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x18u);	/* 446c1b: lea edx, [esp + 0x18] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 446c1f: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 446c22: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 446c24: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 446c26: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 446c28: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 446c2b: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2afcu;	/* 446c2d: mov edi, 0x4b2afc */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 446c32: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 446c35: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 446c37: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 446c39: sub edi, ecx */
	m->esi = m->edi;	/* 446c3b: mov esi, edi */
	m->ebp = m->ecx;	/* 446c3d: mov ebp, ecx */
	m->edi = m->edx;	/* 446c3f: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 446c41: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 446c44: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebp;	/* 446c46: mov ecx, ebp */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 446c48: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 446c49: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 446c4c: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebp;	/* 446c4e: mov ecx, ebp */
	m->eax = (DWORD)(m->esp + 0x18u);	/* 446c50: lea eax, [esp + 0x18] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 446c54: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 446c57: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 446c58: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x446c5fu; native_call(m, 0x49e9cau);	/* 446c5a: call 0x49e9ca */
	m->edi = m->eax;	/* 446c5f: mov edi, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 446c61: add esp, 8 */
	{ DWORD a_ = m->edi, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 446c64: cmp edi, ebx */
	if (m->zf) goto L_446d70;	/* 446c66: je 0x446d70 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 446c6c: push ebx */
	{ DWORD v_ = 0x4e20u; m->esp -= 4; M32(m->esp) = v_; }	/* 446c6d: push 0x4e20 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 446c72: push edi */
	m->esp -= 4; M32(m->esp) = 0x446c78u; native_call(m, 0x49e91eu);	/* 446c73: call 0x49e91e */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 446c78: push edi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 446c79: push 1 */
	m->ecx = (DWORD)(m->esp + 0xa8u);	/* 446c7b: lea ecx, [esp + 0xa8] */
	{ DWORD v_ = 0x80u; m->esp -= 4; M32(m->esp) = v_; }	/* 446c82: push 0x80 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 446c87: push ecx */
	m->esp -= 4; M32(m->esp) = 0x446c8du; native_call(m, 0x49e836u);	/* 446c88: call 0x49e836 */
	m->edx = (DWORD)(m->esp + 0xb0u);	/* 446c8d: lea edx, [esp + 0xb0] */
	{ DWORD v_ = 0x7eu; m->esp -= 4; M32(m->esp) = v_; }	/* 446c94: push 0x7e */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 446c96: push edx */
	m->esp -= 4; M32(m->esp) = 0x446c9cu; native_call(m, 0x445f40u);	/* 446c97: call 0x445f40 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 446c9c: add esp, 0x24 */
	m->esi = 0x4b0fa0u;	/* 446c9f: mov esi, 0x4b0fa0 */
	m->eax = (DWORD)(m->esp + 0x94u);	/* 446ca4: lea eax, [esp + 0x94] */
L_446cab:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 446cab: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 446cad: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 446caf: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_446ccf;	/* 446cb1: jne 0x446ccf */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 446cb3: cmp cl, bl */
	if (m->zf) goto L_446ccb;	/* 446cb5: je 0x446ccb */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 446cb7: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 446cba: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 446cbc: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_446ccf;	/* 446cbf: jne 0x446ccf */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 446cc1: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 446cc4: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 446cc7: cmp cl, bl */
	if (!m->zf) goto L_446cab;	/* 446cc9: jne 0x446cab */
L_446ccb:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 446ccb: xor eax, eax */
	goto L_446cd4;	/* 446ccd: jmp 0x446cd4 */
L_446ccf:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 446ccf: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 446cd1: sbb eax, -1 */
L_446cd4:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 446cd4: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 446cd6: cmp eax, ebx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | ((((m->zf) ? 1u : 0u) & 0xff) << 0);	/* 446cd8: sete cl */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 446cdb: push edi */
	m->esi = m->ecx;	/* 446cdc: mov esi, ecx */
	m->esp -= 4; M32(m->esp) = 0x446ce3u; native_call(m, 0x49e7e0u);	/* 446cde: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 446ce3: add esp, 4 */
	{ DWORD a_ = m->esi, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 446ce6: cmp esi, ebx */
	if (m->zf) goto L_446d70;	/* 446ce8: je 0x446d70 */
	m->edx = (DWORD)(m->esp + 0x14u);	/* 446cee: lea edx, [esp + 0x14] */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 446cf2: push 0x4ad170 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 446cf7: push edx */
	m->esp -= 4; M32(m->esp) = 0x446cfdu; native_call(m, 0x49e9cau);	/* 446cf8: call 0x49e9ca */
	m->ebp = m->eax;	/* 446cfd: mov ebp, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 446cff: add esp, 8 */
	{ DWORD a_ = m->ebp, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 446d02: cmp ebp, ebx */
	if (m->zf) goto L_446fcf;	/* 446d04: je 0x446fcf */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 446d0a: push ebx */
	{ DWORD v_ = 0x4e20u; m->esp -= 4; M32(m->esp) = v_; }	/* 446d0b: push 0x4e20 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 446d10: push ebp */
	m->esp -= 4; M32(m->esp) = 0x446d16u; native_call(m, 0x49e91eu);	/* 446d11: call 0x49e91e */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 446d16: push ebp */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 446d17: push 1 */
	m->eax = (DWORD)(m->esp + 0x2acu);	/* 446d19: lea eax, [esp + 0x2ac] */
	{ DWORD v_ = 0x3acu; m->esp -= 4; M32(m->esp) = v_; }	/* 446d20: push 0x3ac */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 446d25: push eax */
	m->esp -= 4; M32(m->esp) = 0x446d2bu; native_call(m, 0x49e836u);	/* 446d26: call 0x49e836 */
	m->ecx = (DWORD)(m->esp + 0x2b4u);	/* 446d2b: lea ecx, [esp + 0x2b4] */
	{ DWORD v_ = 0x7eu; m->esp -= 4; M32(m->esp) = v_; }	/* 446d32: push 0x7e */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 446d34: push ecx */
	m->esp -= 4; M32(m->esp) = 0x446d3au; native_call(m, 0x445ee0u);	/* 446d35: call 0x445ee0 */
	m->eax = M32((DWORD)(0x9f8d74u));	/* 446d3a: mov eax, dword ptr [0x9f8d74] */
	m->ecx = 0xebu;	/* 446d3f: mov ecx, 0xeb */
	m->esi = (DWORD)(m->esp + 0x2bcu);	/* 446d44: lea esi, [esp + 0x2bc] */
	m->edi = 0x9f1718u;	/* 446d4b: mov edi, 0x9f1718 */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 446d50: lea edx, [eax + eax*8] */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 446d53: add esp, 0x24 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 446d56: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->esi = (DWORD)(m->edx*8 + 0x9f684cu);	/* 446d58: lea esi, [edx*8 + 0x9f684c] */
	m->ecx = 0x20u;	/* 446d5f: mov ecx, 0x20 */
	m->edi = 0x9f1798u;	/* 446d64: mov edi, 0x9f1798 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 446d69: rep movsd dword ptr es:[edi], dword ptr [esi] */
	goto L_446fcf;	/* 446d6b: jmp 0x446fcf */
L_446d70:
	m->ecx = 0x20u;	/* 446d70: mov ecx, 0x20 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 446d75: xor eax, eax */
	m->edi = 0x9f1718u;	/* 446d77: mov edi, 0x9f1718 */
	{ DWORD a_ = m->edx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 446d7c: or edx, 0xffffffff */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 446d7f: rep stosd dword ptr es:[edi], eax */
	m->edi = 0x4b0fa0u;	/* 446d81: mov edi, 0x4b0fa0 */
	m->ecx = m->edx;	/* 446d86: mov ecx, edx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 446d88: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 446d8a: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 446d8c: sub edi, ecx */
	m->eax = m->ecx;	/* 446d8e: mov eax, ecx */
	m->esi = m->edi;	/* 446d90: mov esi, edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 446d92: shr ecx, 2 */
	m->edi = 0x9f1718u;	/* 446d95: mov edi, 0x9f1718 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 446d9a: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 446d9c: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 446d9e: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 446da0: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 446da3: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = 0x20u;	/* 446da5: mov ecx, 0x20 */
	m->edi = 0x9f1798u;	/* 446daa: mov edi, 0x9f1798 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 446daf: rep stosd dword ptr es:[edi], eax */
	m->eax = M32((DWORD)(0x9f8d74u));	/* 446db1: mov eax, dword ptr [0x9f8d74] */
	m->ecx = 0x20u;	/* 446db6: mov ecx, 0x20 */
	m->edi = 0x9f1798u;	/* 446dbb: mov edi, 0x9f1798 */
	m->eax = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 446dc0: lea eax, [eax + eax*8] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 446dc3: shl eax, 3 */
	m->esi = (DWORD)(m->eax + 0x9f684cu);	/* 446dc6: lea esi, [eax + 0x9f684c] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 446dcc: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = M32((DWORD)(m->eax + 0x9f688cu));	/* 446dce: mov ecx, dword ptr [eax + 0x9f688c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 446dd4: xor eax, eax */
	M32((DWORD)(0x9f1818u)) = m->ecx;	/* 446dd6: mov dword ptr [0x9f1818], ecx */
	m->ecx = 0x64u;	/* 446ddc: mov ecx, 0x64 */
	m->edi = 0x9f1820u;	/* 446de1: mov edi, 0x9f1820 */
	M32((DWORD)(0x9f181cu)) = m->ebx;	/* 446de6: mov dword ptr [0x9f181c], ebx */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 446dec: rep stosd dword ptr es:[edi], eax */
	m->ecx = 0x10u;	/* 446dee: mov ecx, 0x10 */
	m->edi = 0x9f19b0u;	/* 446df3: mov edi, 0x9f19b0 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 446df8: rep stosd dword ptr es:[edi], eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 446dfa: xor ecx, ecx */
	M32((DWORD)(0x9f19f0u)) = m->eax;	/* 446dfc: mov dword ptr [0x9f19f0], eax */
	M32((DWORD)(0x9f1a0cu)) = m->ecx;	/* 446e01: mov dword ptr [0x9f1a0c], ecx */
	M32((DWORD)(0x9f19f4u)) = m->eax;	/* 446e07: mov dword ptr [0x9f19f4], eax */
	M32((DWORD)(0x9f1a10u)) = m->ecx;	/* 446e0c: mov dword ptr [0x9f1a10], ecx */
	M32((DWORD)(0x9f1a2cu)) = m->eax;	/* 446e12: mov dword ptr [0x9f1a2c], eax */
	m->edi = 0x4b2af4u;	/* 446e17: mov edi, 0x4b2af4 */
	m->ecx = m->edx;	/* 446e1c: mov ecx, edx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 446e1e: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 446e20: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 446e22: sub edi, ecx */
	M32((DWORD)(0x9f1a30u)) = m->eax;	/* 446e24: mov dword ptr [0x9f1a30], eax */
	m->eax = m->ecx;	/* 446e29: mov eax, ecx */
	m->esi = m->edi;	/* 446e2b: mov esi, edi */
	m->edi = 0x9f19f0u;	/* 446e2d: mov edi, 0x9f19f0 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 446e32: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 446e35: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 446e37: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 446e39: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 446e3b: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 446e3e: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2aecu;	/* 446e40: mov edi, 0x4b2aec */
	m->ecx = m->edx;	/* 446e45: mov ecx, edx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 446e47: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 446e49: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 446e4b: sub edi, ecx */
	m->eax = m->ecx;	/* 446e4d: mov eax, ecx */
	m->esi = m->edi;	/* 446e4f: mov esi, edi */
	m->edi = 0x9f1a0cu;	/* 446e51: mov edi, 0x9f1a0c */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 446e56: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 446e59: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 446e5b: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 446e5d: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 446e5f: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 446e62: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2ae4u;	/* 446e64: mov edi, 0x4b2ae4 */
	m->ecx = m->edx;	/* 446e69: mov ecx, edx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 446e6b: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 446e6d: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 446e6f: sub edi, ecx */
	m->eax = m->ecx;	/* 446e71: mov eax, ecx */
	m->esi = m->edi;	/* 446e73: mov esi, edi */
	m->edi = 0x9f1a2cu;	/* 446e75: mov edi, 0x9f1a2c */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 446e7a: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 446e7d: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 446e7f: mov ecx, eax */
	m->eax = 0x9f1a38u;	/* 446e81: mov eax, 0x9f1a38 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 446e86: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 446e89: rep movsb byte ptr es:[edi], byte ptr [esi] */
	M32((DWORD)(0x9f1a28u)) = m->edx;	/* 446e8b: mov dword ptr [0x9f1a28], edx */
	M32((DWORD)(0x9f1a14u)) = m->edx;	/* 446e91: mov dword ptr [0x9f1a14], edx */
	M32((DWORD)(0x9f19f8u)) = m->ebx;	/* 446e97: mov dword ptr [0x9f19f8], ebx */
	M32((DWORD)(0x9f19fcu)) = m->ebx;	/* 446e9d: mov dword ptr [0x9f19fc], ebx */
	M32((DWORD)(0x9f1a00u)) = m->ebx;	/* 446ea3: mov dword ptr [0x9f1a00], ebx */
	M32((DWORD)(0x9f1a04u)) = m->ebx;	/* 446ea9: mov dword ptr [0x9f1a04], ebx */
	M32((DWORD)(0x9f1a08u)) = m->ebx;	/* 446eaf: mov dword ptr [0x9f1a08], ebx */
	M32((DWORD)(0x9f1a1cu)) = m->ebx;	/* 446eb5: mov dword ptr [0x9f1a1c], ebx */
	M32((DWORD)(0x9f1a20u)) = 0x2u;	/* 446ebb: mov dword ptr [0x9f1a20], 2 */
	M32((DWORD)(0x9f1a24u)) = 0x8u;	/* 446ec5: mov dword ptr [0x9f1a24], 8 */
	M32((DWORD)(0x9f1a18u)) = 0x11u;	/* 446ecf: mov dword ptr [0x9f1a18], 0x11 */
	m->ecx = 0x432a0000u;	/* 446ed9: mov ecx, 0x432a0000 */
	m->edx = 0x3ecccccdu;	/* 446ede: mov edx, 0x3ecccccd */
L_446ee3:
	M32((DWORD)(m->eax + 0xfffffffcu)) = m->ecx;	/* 446ee3: mov dword ptr [eax - 4], ecx */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 446ee6: mov dword ptr [eax], edx */
	M32((DWORD)(m->eax + 0x4u)) = m->ebx;	/* 446ee8: mov dword ptr [eax + 4], ebx */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 446eeb: mov dword ptr [eax + 8], ecx */
	M32((DWORD)(m->eax + 0xcu)) = m->edx;	/* 446eee: mov dword ptr [eax + 0xc], edx */
	M32((DWORD)(m->eax + 0x10u)) = m->ebx;	/* 446ef1: mov dword ptr [eax + 0x10], ebx */
	{ DWORD a_ = m->eax, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 446ef4: add eax, 0x18 */
	{ DWORD a_ = m->eax, b_ = 0x9f1ac8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 446ef7: cmp eax, 0x9f1ac8 */
	if (m->sf != m->of) goto L_446ee3;	/* 446efc: jl 0x446ee3 */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 446efe: lea ecx, [esp + 0x14] */
	{ DWORD v_ = 0x4b2ab0u; m->esp -= 4; M32(m->esp) = v_; }	/* 446f02: push 0x4b2ab0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 446f07: push ecx */
	m->esp -= 4; M32(m->esp) = 0x446f0du; native_call(m, 0x49e9cau);	/* 446f08: call 0x49e9ca */
	m->ebp = m->eax;	/* 446f0d: mov ebp, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 446f0f: add esp, 8 */
	{ DWORD a_ = m->ebp, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 446f12: cmp ebp, ebx */
	if (m->zf) goto L_446fcf;	/* 446f14: je 0x446fcf */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 446f1a: xor esi, esi */
L_446f1c:
	m->esp -= 4; M32(m->esp) = 0x446f21u; native_call(m, 0x49f92cu);	/* 446f1c: call 0x49f92c */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 446f21: cdq  */
	m->ecx = 0xfeu;	/* 446f22: mov ecx, 0xfe */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 446f27: idiv ecx */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 446f29: inc esi */
	{ DWORD a_ = m->esi, b_ = 0x2710u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 446f2a: cmp esi, 0x2710 */
	M8((DWORD)(m->esi + 0x9f3ac3u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 446f30: mov byte ptr [esi + 0x9f3ac3], dl */
	if (m->sf != m->of) goto L_446f1c;	/* 446f36: jl 0x446f1c */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 446f38: push ebp */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 446f39: push 1 */
	{ DWORD v_ = 0x2710u; m->esp -= 4; M32(m->esp) = v_; }	/* 446f3b: push 0x2710 */
	{ DWORD v_ = 0x9f3ac4u; m->esp -= 4; M32(m->esp) = v_; }	/* 446f40: push 0x9f3ac4 */
	m->esp -= 4; M32(m->esp) = 0x446f4au; native_call(m, 0x49f58au);	/* 446f45: call 0x49f58a */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 446f4a: push ebp */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 446f4b: push 1 */
	{ DWORD v_ = 0x2710u; m->esp -= 4; M32(m->esp) = v_; }	/* 446f4d: push 0x2710 */
	{ DWORD v_ = 0x9f3ac4u; m->esp -= 4; M32(m->esp) = v_; }	/* 446f52: push 0x9f3ac4 */
	m->esp -= 4; M32(m->esp) = 0x446f5cu; native_call(m, 0x49f58au);	/* 446f57: call 0x49f58a */
	m->ecx = 0xebu;	/* 446f5c: mov ecx, 0xeb */
	m->esi = 0x9f1718u;	/* 446f61: mov esi, 0x9f1718 */
	m->edi = (DWORD)(m->esp + 0x2b8u);	/* 446f66: lea edi, [esp + 0x2b8] */
	m->edx = (DWORD)(m->esp + 0x2b8u);	/* 446f6d: lea edx, [esp + 0x2b8] */
	{ DWORD v_ = 0x7eu; m->esp -= 4; M32(m->esp) = v_; }	/* 446f74: push 0x7e */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 446f76: push edx */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 446f77: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x446f7eu; native_call(m, 0x445ee0u);	/* 446f79: call 0x445ee0 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 446f7e: push ebp */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 446f7f: push 1 */
	m->eax = (DWORD)(m->esp + 0x2c8u);	/* 446f81: lea eax, [esp + 0x2c8] */
	{ DWORD v_ = 0x3acu; m->esp -= 4; M32(m->esp) = v_; }	/* 446f88: push 0x3ac */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 446f8d: push eax */
	m->esp -= 4; M32(m->esp) = 0x446f93u; native_call(m, 0x49f58au);	/* 446f8e: call 0x49f58a */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 446f93: push ebp */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 446f94: push 1 */
	{ DWORD v_ = 0x2710u; m->esp -= 4; M32(m->esp) = v_; }	/* 446f96: push 0x2710 */
	{ DWORD v_ = 0x9f3ac4u; m->esp -= 4; M32(m->esp) = v_; }	/* 446f9b: push 0x9f3ac4 */
	m->esp -= 4; M32(m->esp) = 0x446fa5u; native_call(m, 0x49f58au);	/* 446fa0: call 0x49f58a */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 446fa5: add esp, 0x48 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 446fa8: push ebp */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 446fa9: push 1 */
	{ DWORD v_ = 0x2710u; m->esp -= 4; M32(m->esp) = v_; }	/* 446fab: push 0x2710 */
	{ DWORD v_ = 0x9f3ac4u; m->esp -= 4; M32(m->esp) = v_; }	/* 446fb0: push 0x9f3ac4 */
	m->esp -= 4; M32(m->esp) = 0x446fbau; native_call(m, 0x49f58au);	/* 446fb5: call 0x49f58a */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 446fba: push ebp */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 446fbb: push 1 */
	{ DWORD v_ = 0x1387u; m->esp -= 4; M32(m->esp) = v_; }	/* 446fbd: push 0x1387 */
	{ DWORD v_ = 0x9f3ac4u; m->esp -= 4; M32(m->esp) = v_; }	/* 446fc2: push 0x9f3ac4 */
	m->esp -= 4; M32(m->esp) = 0x446fccu; native_call(m, 0x49f58au);	/* 446fc7: call 0x49f58a */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 446fcc: add esp, 0x20 */
L_446fcf:
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 446fcf: push ebp */
	m->esp -= 4; M32(m->esp) = 0x446fd5u; native_call(m, 0x49e7e0u);	/* 446fd0: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 446fd5: add esp, 4 */
	{ DWORD v_ = 0x4b2a80u; m->esp -= 4; M32(m->esp) = v_; }	/* 446fd8: push 0x4b2a80 */
	m->esp -= 4; M32(m->esp) = 0x446fe2u; native_call(m, 0x49f8a6u);	/* 446fdd: call 0x49f8a6 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 446fe2: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x446feau; native_call(m, 0x4463a0u);	/* 446fe5: call 0x4463a0 */
	m->ecx = M32((DWORD)(0x9f181cu));	/* 446fea: mov ecx, dword ptr [0x9f181c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 446ff0: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 446ff1: pop esi */
	M32((DWORD)(0x4dcf34u)) = m->ebx;	/* 446ff2: mov dword ptr [0x4dcf34], ebx */
	M32((DWORD)(0x9f62e0u)) = m->ebx;	/* 446ff8: mov dword ptr [0x9f62e0], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 446ffe: pop ebp */
	M32((DWORD)(0x9f62fcu)) = m->ecx;	/* 446fff: mov dword ptr [0x9f62fc], ecx */
	m->ebx = M32(m->esp); m->esp += 4;	/* 447005: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x634u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447006: add esp, 0x634 */
	m->esp += 4 + 0; return;	/* 44700c: ret  */
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
