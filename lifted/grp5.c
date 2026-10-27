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

static void lift_41ef20(X86 *m);
static void lift_470fc0(X86 *m);
static void lift_454760(X86 *m);
static void lift_42f0f0(X86 *m);
static void lift_487bd0(X86 *m);
static void lift_46bd00(X86 *m);
static void lift_4841f0(X86 *m);
static void lift_452d70(X86 *m);
static void lift_483fd0(X86 *m);
static void lift_483fb0(X86 *m);
static void lift_454690(X86 *m);
static void lift_463430(X86 *m);
static void lift_472900(X86 *m);
static void lift_427c30(X86 *m);
static void lift_427e30(X86 *m);
static void lift_428030(X86 *m);
static void lift_4280e0(X86 *m);
static void lift_428190(X86 *m);
static void lift_428240(X86 *m);
static void lift_4283e0(X86 *m);
static void lift_4284d0(X86 *m);
static void lift_4282f0(X86 *m);
static void lift_4285c0(X86 *m);
static void lift_4286b0(X86 *m);
static void lift_4287a0(X86 *m);
static void lift_427ce0(X86 *m);
static void lift_427ee0(X86 *m);
static void lift_46c840(X86 *m);
static void lift_46c5f0(X86 *m);
static void lift_46c950(X86 *m);
static void lift_46c710(X86 *m);
static void lift_401290(X86 *m);

/* load_401290 (0x401290), lifted by tools/lift.py */
static void lift_401290(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 401290: mov eax, dword ptr [esp + 0xc] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 401294: dec eax */
	if (m->sf) goto L_4012b7;	/* 401295: js 0x4012b7 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 401297: push ebx */
	m->ebx = M32((DWORD)(m->esp + 0x14u));	/* 401298: mov ebx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 40129c: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x10u));	/* 40129d: mov ebp, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4012a1: push esi */
	m->esi = M32((DWORD)(m->esp + 0x10u));	/* 4012a2: mov esi, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4012a6: push edi */
	m->edi = (DWORD)(m->eax + 0x1u);	/* 4012a7: lea edi, [eax + 1] */
L_4012aa:
	m->ecx = m->esi;	/* 4012aa: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x4012aeu; native_call(m, m->ebx);	/* 4012ac: call ebx */
	{ DWORD a_ = m->esi, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4012ae: add esi, ebp */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4012b0: dec edi */
	if (!m->zf) goto L_4012aa;	/* 4012b1: jne 0x4012aa */
	m->edi = M32(m->esp); m->esp += 4;	/* 4012b3: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4012b4: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4012b5: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4012b6: pop ebx */
L_4012b7:
	m->esp += 4 + 16; return;	/* 4012b7: ret 0x10 */
}

/* FUN_0041ef20 (0x41ef20), lifted by tools/lift.py */
static void lift_41ef20(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 41ef20: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41ef24: push esi */
	m->esi = M32((DWORD)(0x4a91f8u));	/* 41ef25: mov esi, dword ptr [0x4a91f8] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ef2b: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ef2d: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ef2f: push 0x3f800000 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41ef34: push eax */
	m->esp -= 4; M32(m->esp) = 0x41ef37u; native_call(m, m->esi);	/* 41ef35: call esi */
	m->ecx = M32((DWORD)(m->esp + 0xcu));	/* 41ef37: mov ecx, dword ptr [esp + 0xc] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ef3b: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ef3d: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ef42: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41ef44: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41ef47u; native_call(m, m->esi);	/* 41ef45: call esi */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 41ef47: mov edx, dword ptr [esp + 0x10] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ef4b: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ef50: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41ef52: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41ef54: push edx */
	m->esp -= 4; M32(m->esp) = 0x41ef57u; native_call(m, m->esi);	/* 41ef55: call esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 41ef57: pop esi */
	m->esp += 4 + 0; return;	/* 41ef58: ret  */
}

/* FUN_00470fc0 (0x470fc0), lifted by tools/lift.py */
static void lift_470fc0(X86 *m)
{
	m->eax = M32((DWORD)(0xae2ec8u));	/* 470fc0: mov eax, dword ptr [0xae2ec8] */
	{ DWORD a_ = m->esp, b_ = 0x400u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 470fc5: sub esp, 0x400 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 470fcb: test eax, eax */
	if (m->zf) goto L_471007;	/* 470fcd: je 0x471007 */
	m->ecx = M32((DWORD)(m->esp + 0x410u));	/* 470fcf: mov ecx, dword ptr [esp + 0x410] */
	m->eax = (DWORD)(m->esp + 0x414u);	/* 470fd6: lea eax, [esp + 0x414] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 470fdd: push eax */
	m->edx = (DWORD)(m->esp + 0x4u);	/* 470fde: lea edx, [esp + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 470fe2: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 470fe3: push edx */
	m->esp -= 4; M32(m->esp) = 0x470fe9u; native_call(m, 0x49ed2eu);	/* 470fe4: call 0x49ed2e */
	m->ecx = M32((DWORD)(m->esp + 0x418u));	/* 470fe9: mov ecx, dword ptr [esp + 0x418] */
	m->edx = M32((DWORD)(m->esp + 0x414u));	/* 470ff0: mov edx, dword ptr [esp + 0x414] */
	m->eax = (DWORD)(m->esp + 0xcu);	/* 470ff7: lea eax, [esp + 0xc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 470ffb: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 470ffc: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 470ffd: push edx */
	m->esp -= 4; M32(m->esp) = 0x471004u; native_call(m, M32((DWORD)(0xae2ec8u)));	/* 470ffe: call dword ptr [0xae2ec8] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 471004: add esp, 0x18 */
L_471007:
	{ DWORD a_ = m->esp, b_ = 0x400u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 471007: add esp, 0x400 */
	m->esp += 4 + 0; return;	/* 47100d: ret  */
}

/* net_454760 (0x454760), lifted by tools/lift.py */
static void lift_454760(X86 *m)
{
	m->eax = M32((DWORD)(0xa0d788u));	/* 454760: mov eax, dword ptr [0xa0d788] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 454765: push esi */
	m->esi = M32((DWORD)(0x4a91b0u));	/* 454766: mov esi, dword ptr [0x4a91b0] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45476c: push edi */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 45476d: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45476f: cmp eax, edi */
	if (m->zf) goto L_45477c;	/* 454771: je 0x45477c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454773: push eax */
	m->esp -= 4; M32(m->esp) = 0x454776u; native_call(m, m->esi);	/* 454774: call esi */
	M32((DWORD)(0xa0d788u)) = m->edi;	/* 454776: mov dword ptr [0xa0d788], edi */
L_45477c:
	m->eax = M32((DWORD)(0xa0bf1cu));	/* 45477c: mov eax, dword ptr [0xa0bf1c] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 454781: cmp eax, edi */
	if (m->zf) goto L_45478e;	/* 454783: je 0x45478e */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454785: push eax */
	m->esp -= 4; M32(m->esp) = 0x454788u; native_call(m, m->esi);	/* 454786: call esi */
	M32((DWORD)(0xa0bf1cu)) = m->edi;	/* 454788: mov dword ptr [0xa0bf1c], edi */
L_45478e:
	m->eax = M32((DWORD)(0xa0bb10u));	/* 45478e: mov eax, dword ptr [0xa0bb10] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 454793: cmp eax, edi */
	if (m->zf) goto L_4547a0;	/* 454795: je 0x4547a0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454797: push eax */
	m->esp -= 4; M32(m->esp) = 0x45479au; native_call(m, m->esi);	/* 454798: call esi */
	M32((DWORD)(0xa0bb10u)) = m->edi;	/* 45479a: mov dword ptr [0xa0bb10], edi */
L_4547a0:
	{ DWORD a_ = M32((DWORD)(0xa0d784u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4547a0: cmp dword ptr [0xa0d784], edi */
	if (m->zf) goto L_4547ae;	/* 4547a6: je 0x4547ae */
	M32((DWORD)(0xa0d784u)) = m->edi;	/* 4547a8: mov dword ptr [0xa0d784], edi */
L_4547ae:
	m->edi = M32(m->esp); m->esp += 4;	/* 4547ae: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4547af: pop esi */
	m->esp += 4 + 0; return;	/* 4547b0: ret  */
}

/* FUN_0042f0f0 (0x42f0f0), lifted by tools/lift.py */
static void lift_42f0f0(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 42f0f0: mov eax, dword ptr [esp + 8] */
	m->ecx = M32((DWORD)(m->esp + 0x4u));	/* 42f0f4: mov ecx, dword ptr [esp + 4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42f0f8: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42f0f9: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42f0fa: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f0fb: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f0fd: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42f105u; native_call(m, M32(0x4a91d4u));	/* 42f0ff: call dword ptr [0x4a91d4] */
	m->esi = M32((DWORD)(0x4a91fcu));	/* 42f105: mov esi, dword ptr [0x4a91fc] */
	{ DWORD v_ = 0x1701u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f10b: push 0x1701 */
	m->esp -= 4; M32(m->esp) = 0x42f112u; native_call(m, m->esi);	/* 42f110: call esi */
	m->esp -= 4; M32(m->esp) = 0x42f118u; native_call(m, M32(0x4a9218u));	/* 42f112: call dword ptr [0x4a9218] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e1870u)));	/* 42f118: fld dword ptr [0x4e1870] */
	{ DWORD v_ = 0x40d38800u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f11e: push 0x40d38800 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f123: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f125: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f12a: push 0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42f12c: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 42f12f: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x68038cu)));	/* 42f132: fld dword ptr [0x68038c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42f138: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 42f13b: fstp qword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x42f143u; native_call(m, 0x4509c6u);	/* 42f13e: call 0x4509c6 */
	{ DWORD v_ = 0x1700u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f143: push 0x1700 */
	m->esp -= 4; M32(m->esp) = 0x42f14au; native_call(m, m->esi);	/* 42f148: call esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 42f14a: pop esi */
	m->esp += 4 + 0; return;	/* 42f14b: ret  */
}

/* input_asyncKeyPressed (0x487bd0), lifted by tools/lift.py */
static void lift_487bd0(X86 *m)
{
	m->eax = M32((DWORD)(0x4ded18u));	/* 487bd0: mov eax, dword ptr [0x4ded18] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 487bd5: push esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 487bd6: test eax, eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 487bd8: push edi */
	if (m->zf) goto L_487be9;	/* 487bd9: je 0x487be9 */
	m->esp -= 4; M32(m->esp) = 0x487be1u; native_call(m, M32(0x4a92fcu));	/* 487bdb: call dword ptr [0x4a92fc] */
	{ DWORD a_ = M32((DWORD)(0x4ded18u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 487be1: cmp dword ptr [0x4ded18], eax */
	if (!m->zf) goto L_487c28;	/* 487be7: jne 0x487c28 */
L_487be9:
	m->esi = M32((DWORD)(m->esp + 0xcu));	/* 487be9: mov esi, dword ptr [esp + 0xc] */
	m->edi = M32((DWORD)(0x4a92f8u));	/* 487bed: mov edi, dword ptr [0x4a92f8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 487bf3: push esi */
	m->esp -= 4; M32(m->esp) = 0x487bf6u; native_call(m, m->edi);	/* 487bf4: call edi */
	{ DWORD a_ = (m->eax & 0xffff), b_ = (m->eax & 0xffff) & 0xffffu, r_ = a_ & b_; FLAGS(r_, 16); m->cf = 0; m->of = 0; }	/* 487bf6: test ax, ax */
	if (!m->zf) goto L_487c06;	/* 487bf9: jne 0x487c06 */
	M32((DWORD)(m->esi*4 + 0xae2f24u)) = 0x0u;	/* 487bfb: mov dword ptr [esi*4 + 0xae2f24], 0 */
L_487c06:
	m->eax = M32((DWORD)(m->esi*4 + 0xae2f24u));	/* 487c06: mov eax, dword ptr [esi*4 + 0xae2f24] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 487c0d: test eax, eax */
	if (!m->zf) goto L_487c28;	/* 487c0f: jne 0x487c28 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 487c11: push esi */
	m->esp -= 4; M32(m->esp) = 0x487c14u; native_call(m, m->edi);	/* 487c12: call edi */
	{ DWORD a_ = (m->eax & 0xffff), b_ = (m->eax & 0xffff) & 0xffffu, r_ = a_ & b_; FLAGS(r_, 16); m->cf = 0; m->of = 0; }	/* 487c14: test ax, ax */
	if (m->zf) goto L_487c28;	/* 487c17: je 0x487c28 */
	m->eax = 0x1u;	/* 487c19: mov eax, 1 */
	m->edi = M32(m->esp); m->esp += 4;	/* 487c1e: pop edi */
	M32((DWORD)(m->esi*4 + 0xae2f24u)) = m->eax;	/* 487c1f: mov dword ptr [esi*4 + 0xae2f24], eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 487c26: pop esi */
	m->esp += 4 + 0; return;	/* 487c27: ret  */
L_487c28:
	m->edi = M32(m->esp); m->esp += 4;	/* 487c28: pop edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 487c29: xor eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 487c2b: pop esi */
	m->esp += 4 + 0; return;	/* 487c2c: ret  */
}

/* hud_46bd00 (0x46bd00), lifted by tools/lift.py */
static void lift_46bd00(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46bd00: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46bd01: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46bd02: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46bd03: push edi */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 46bd04: push 2 */
	m->esp -= 4; M32(m->esp) = 0x46bd0cu; native_call(m, M32(0x4a921cu));	/* 46bd06: call dword ptr [0x4a921c] */
	m->esp -= 4; M32(m->esp) = 0x46bd11u; native_call(m, 0x4685c0u);	/* 46bd0c: call 0x4685c0 */
	m->ebx = M32((DWORD)(m->esp + 0x18u));	/* 46bd11: mov ebx, dword ptr [esp + 0x18] */
	m->ebp = M32((DWORD)(m->esp + 0x14u));	/* 46bd15: mov ebp, dword ptr [esp + 0x14] */
	m->esi = M32((DWORD)(0x4a91f4u));	/* 46bd19: mov esi, dword ptr [0x4a91f4] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46bd1f: sub eax, ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46bd21: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46bd22: push ebp */
	m->esp -= 4; M32(m->esp) = 0x46bd25u; native_call(m, m->esi);	/* 46bd23: call esi */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 46bd25: mov eax, dword ptr [esp + 0x1c] */
	m->edi = (DWORD)(m->eax + 0x1u);	/* 46bd29: lea edi, [eax + 1] */
	m->esp -= 4; M32(m->esp) = 0x46bd31u; native_call(m, 0x4685c0u);	/* 46bd2c: call 0x4685c0 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46bd31: sub eax, ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46bd33: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46bd34: push edi */
	m->esp -= 4; M32(m->esp) = 0x46bd37u; native_call(m, m->esi);	/* 46bd35: call esi */
	m->esp -= 4; M32(m->esp) = 0x46bd3cu; native_call(m, 0x4685c0u);	/* 46bd37: call 0x4685c0 */
	m->ebx = M32((DWORD)(m->esp + 0x20u));	/* 46bd3c: mov ebx, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46bd40: sub eax, ebx */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 46bd42: dec eax */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46bd43: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46bd44: push edi */
	m->esp -= 4; M32(m->esp) = 0x46bd47u; native_call(m, m->esi);	/* 46bd45: call esi */
	m->esp -= 4; M32(m->esp) = 0x46bd4cu; native_call(m, 0x4685c0u);	/* 46bd47: call 0x4685c0 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46bd4c: sub eax, ebx */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 46bd4e: dec eax */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46bd4f: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46bd50: push ebp */
	m->esp -= 4; M32(m->esp) = 0x46bd53u; native_call(m, m->esi);	/* 46bd51: call esi */
	m->esp -= 4; M32(m->esp) = 0x46bd59u; native_call(m, M32(0x4a9220u));	/* 46bd53: call dword ptr [0x4a9220] */
	m->edi = M32(m->esp); m->esp += 4;	/* 46bd59: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46bd5a: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 46bd5b: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 46bd5c: pop ebx */
	m->esp += 4 + 0; return;	/* 46bd5d: ret  */
}

/* ViewVolume_captureMatrices (0x4841f0), lifted by tools/lift.py */
static void lift_4841f0(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 4841f0: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4841f4: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4841f5: push ebp */
	m->ebp = M32((DWORD)(0x4a9270u));	/* 4841f6: mov ebp, dword ptr [0x4a9270] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4841fc: push esi */
	m->esi = m->ecx;	/* 4841fd: mov esi, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4841ff: test eax, eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 484201: push edi */
	m->ebx = (DWORD)(m->esi + 0x90b0u);	/* 484202: lea ebx, [esi + 0x90b0] */
	if (m->zf) goto L_484216;	/* 484208: je 0x484216 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48420a: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48420b: push ebx */
	m->esp -= 4; M32(m->esp) = 0x484211u; native_call(m, 0x47d5a0u);	/* 48420c: call 0x47d5a0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 484211: add esp, 8 */
	goto L_48421e;	/* 484214: jmp 0x48421e */
L_484216:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 484216: push ebx */
	{ DWORD v_ = 0xba7u; m->esp -= 4; M32(m->esp) = v_; }	/* 484217: push 0xba7 */
	m->esp -= 4; M32(m->esp) = 0x48421eu; native_call(m, m->ebp);	/* 48421c: call ebp */
L_48421e:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 48421e: mov eax, dword ptr [esp + 0x18] */
	m->edi = (DWORD)(m->esi + 0x90f0u);	/* 484222: lea edi, [esi + 0x90f0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 484228: test eax, eax */
	if (m->zf) goto L_484238;	/* 48422a: je 0x484238 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48422c: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48422d: push edi */
	m->esp -= 4; M32(m->esp) = 0x484233u; native_call(m, 0x47d5a0u);	/* 48422e: call 0x47d5a0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 484233: add esp, 8 */
	goto L_484240;	/* 484236: jmp 0x484240 */
L_484238:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 484238: push edi */
	{ DWORD v_ = 0xba6u; m->esp -= 4; M32(m->esp) = v_; }	/* 484239: push 0xba6 */
	m->esp -= 4; M32(m->esp) = 0x484240u; native_call(m, m->ebp);	/* 48423e: call ebp */
L_484240:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 484240: push edi */
	{ DWORD a_ = m->esi, b_ = 0x9130u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 484241: add esi, 0x9130 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 484247: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 484248: push esi */
	m->esp -= 4; M32(m->esp) = 0x48424eu; native_call(m, 0x47d380u);	/* 484249: call 0x47d380 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48424e: add esp, 0xc */
	m->edi = M32(m->esp); m->esp += 4;	/* 484251: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 484252: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 484253: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 484254: pop ebx */
	m->esp += 4 + 8; return;	/* 484255: ret 8 */
}

/* net_452d70 (0x452d70), lifted by tools/lift.py */
static void lift_452d70(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 452d70: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 452d71: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 452d72: push edi */
	m->edi = M32((DWORD)(0x4a9184u));	/* 452d73: mov edi, dword ptr [0x4a9184] */
	m->esp -= 4; M32(m->esp) = 0x452d7bu; native_call(m, m->edi);	/* 452d79: call edi */
	m->ebx = m->eax;	/* 452d7b: mov ebx, eax */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 452d7d: xor esi, esi */
L_452d7f:
	m->eax = M32((DWORD)(0xa05630u));	/* 452d7f: mov eax, dword ptr [0xa05630] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 452d84: push 0 */
	{ DWORD v_ = 0x3eu; m->esp -= 4; M32(m->esp) = v_; }	/* 452d86: push 0x3e */
	{ DWORD v_ = 0xa052e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 452d88: push 0xa052e8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 452d8d: push eax */
	m->esp -= 4; M32(m->esp) = 0x452d93u; native_call(m, 0x4a82d4u);	/* 452d8e: call 0x4a82d4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 452d93: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_452d99;	/* 452d95: jle 0x452d99 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 452d97: add esi, eax */
L_452d99:
	m->esp -= 4; M32(m->esp) = 0x452d9bu; native_call(m, m->edi);	/* 452d99: call edi */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 452d9b: sub eax, ebx */
	{ DWORD a_ = m->eax, b_ = 0xbb8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 452d9d: cmp eax, 0xbb8 */
	if (!m->cf && !m->zf) goto L_452da9;	/* 452da2: ja 0x452da9 */
	{ DWORD a_ = m->esi, b_ = 0x3eu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 452da4: cmp esi, 0x3e */
	if (m->cf) goto L_452d7f;	/* 452da7: jb 0x452d7f */
L_452da9:
	m->eax = M32((DWORD)(0xa05306u));	/* 452da9: mov eax, dword ptr [0xa05306] */
	m->edi = M32(m->esp); m->esp += 4;	/* 452dae: pop edi */
	{ DWORD a_ = m->eax, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 452daf: sub eax, 0 */
	m->esi = M32(m->esp); m->esp += 4;	/* 452db2: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 452db3: pop ebx */
	if (m->zf) goto L_452dce;	/* 452db4: je 0x452dce */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 452db6: dec eax */
	if (!m->zf) goto L_452dd9;	/* 452db7: jne 0x452dd9 */
	M32((DWORD)(0xa0b350u)) = 0x1u;	/* 452db9: mov dword ptr [0xa0b350], 1 */
	M32((DWORD)(0xa0b300u)) = 0x0u;	/* 452dc3: mov dword ptr [0xa0b300], 0 */
	m->esp += 4 + 0; return;	/* 452dcd: ret  */
L_452dce:
	{ DWORD v_ = 0xa052e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 452dce: push 0xa052e8 */
	m->esp -= 4; M32(m->esp) = 0x452dd8u; native_call(m, 0x452de0u);	/* 452dd3: call 0x452de0 */
	m->ecx = M32(m->esp); m->esp += 4;	/* 452dd8: pop ecx */
L_452dd9:
	m->esp += 4 + 0; return;	/* 452dd9: ret  */
}

/* gfx_initVertexArrayExt (0x483fd0), lifted by tools/lift.py */
static void lift_483fd0(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 483fd0: push esi */
	m->esi = m->ecx;	/* 483fd1: mov esi, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 483fd3: push edi */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 483fd4: xor edi, edi */
	{ DWORD a_ = M32((DWORD)(m->esi + 0xcu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 483fd6: cmp dword ptr [esi + 0xc], 1 */
	if (!m->zf) goto L_483fee;	/* 483fda: jne 0x483fee */
	m->eax = M32((DWORD)(m->esi + 0x8u));	/* 483fdc: mov eax, dword ptr [esi + 8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 483fdf: push eax */
	m->esp -= 4; M32(m->esp) = 0x483fe5u; native_call(m, 0x49ef24u);	/* 483fe0: call 0x49ef24 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 483fe5: add esp, 4 */
	M32((DWORD)(m->esi + 0x8u)) = m->edi;	/* 483fe8: mov dword ptr [esi + 8], edi */
	M32((DWORD)(m->esi + 0xcu)) = m->edi;	/* 483feb: mov dword ptr [esi + 0xc], edi */
L_483fee:
	m->ecx = m->esi;	/* 483fee: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x483ff5u; native_call(m, 0x483fc0u);	/* 483ff0: call 0x483fc0 */
	{ DWORD v_ = 0x1f03u; m->esp -= 4; M32(m->esp) = v_; }	/* 483ff5: push 0x1f03 */
	m->esp -= 4; M32(m->esp) = 0x484000u; native_call(m, M32(0x4a9278u));	/* 483ffa: call dword ptr [0x4a9278] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 484000: cmp eax, edi */
	if (m->zf) goto L_484041;	/* 484002: je 0x484041 */
	{ DWORD v_ = 0x4c7b5cu; m->esp -= 4; M32(m->esp) = v_; }	/* 484004: push 0x4c7b5c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 484009: push eax */
	m->esp -= 4; M32(m->esp) = 0x48400fu; native_call(m, 0x4a0090u);	/* 48400a: call 0x4a0090 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48400f: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 484012: test eax, eax */
	if (m->zf) goto L_484041;	/* 484014: je 0x484041 */
	m->edi = M32((DWORD)(0x4a928cu));	/* 484016: mov edi, dword ptr [0x4a928c] */
	{ DWORD v_ = 0x4c7b48u; m->esp -= 4; M32(m->esp) = v_; }	/* 48401c: push 0x4c7b48 */
	M32((DWORD)(m->esi + 0x10u)) = 0x1u;	/* 484021: mov dword ptr [esi + 0x10], 1 */
	m->esp -= 4; M32(m->esp) = 0x48402au; native_call(m, m->edi);	/* 484028: call edi */
	{ DWORD v_ = 0x4c7b34u; m->esp -= 4; M32(m->esp) = v_; }	/* 48402a: push 0x4c7b34 */
	M32((DWORD)(m->esi + 0x14u)) = m->eax;	/* 48402f: mov dword ptr [esi + 0x14], eax */
	m->esp -= 4; M32(m->esp) = 0x484034u; native_call(m, m->edi);	/* 484032: call edi */
	{ DWORD v_ = 0x4c7b1cu; m->esp -= 4; M32(m->esp) = v_; }	/* 484034: push 0x4c7b1c */
	M32((DWORD)(m->esi + 0x18u)) = m->eax;	/* 484039: mov dword ptr [esi + 0x18], eax */
	m->esp -= 4; M32(m->esp) = 0x48403eu; native_call(m, m->edi);	/* 48403c: call edi */
	M32((DWORD)(m->esi + 0x1cu)) = m->eax;	/* 48403e: mov dword ptr [esi + 0x1c], eax */
L_484041:
	m->edi = M32(m->esp); m->esp += 4;	/* 484041: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 484042: pop esi */
	m->esp += 4 + 0; return;	/* 484043: ret  */
}

/* ViewVolume_dtor (0x483fb0), lifted by tools/lift.py */
static void lift_483fb0(X86 *m)
{
	M32((DWORD)(m->ecx + 0x0u)) = 0x4aa24cu;	/* 483fb0: mov dword ptr [ecx], 0x4aa24c */
	lift_483fd0(m); return;	/* 483fb6: jmp 0x483fd0 */
}

/* net_454690 (0x454690), lifted by tools/lift.py */
static void lift_454690(X86 *m)
{
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 454690: push edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 454691: xor eax, eax */
	m->ecx = 0x100u;	/* 454693: mov ecx, 0x100 */
	m->edi = 0xa0bb14u;	/* 454698: mov edi, 0xa0bb14 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 45469d: rep stosd dword ptr es:[edi], eax */
	m->ecx = 0x100u;	/* 45469f: mov ecx, 0x100 */
	m->edi = 0xa0d384u;	/* 4546a4: mov edi, 0xa0d384 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4546a9: rep stosd dword ptr es:[edi], eax */
	m->ecx = 0x500u;	/* 4546ab: mov ecx, 0x500 */
	m->edi = 0xa0bf20u;	/* 4546b0: mov edi, 0xa0bf20 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4546b5: rep stosd dword ptr es:[edi], eax */
	M32((DWORD)(0xa0d79cu)) = m->eax;	/* 4546b7: mov dword ptr [0xa0d79c], eax */
	M32((DWORD)(0xa0d7a0u)) = m->eax;	/* 4546bc: mov dword ptr [0xa0d7a0], eax */
	m->esp -= 4; M32(m->esp) = 0x4546c6u; lift_454760(m);	/* 4546c1: call 0x454760 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4546c6: pop edi */
	m->esp += 4 + 0; return;	/* 4546c7: ret  */
}

/* ViewVolume_deletingDtor (0x463430), lifted by tools/lift.py */
static void lift_463430(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 463430: push esi */
	m->esi = m->ecx;	/* 463431: mov esi, ecx */
	m->esp -= 4; M32(m->esp) = 0x463438u; lift_483fb0(m);	/* 463433: call 0x483fb0 */
	{ DWORD a_ = M8((DWORD)(m->esp + 0x8u)), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 463438: test byte ptr [esp + 8], 1 */
	if (m->zf) goto L_463448;	/* 46343d: je 0x463448 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46343f: push esi */
	m->esp -= 4; M32(m->esp) = 0x463445u; native_call(m, 0x49ef24u);	/* 463440: call 0x49ef24 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 463445: add esp, 4 */
L_463448:
	m->eax = m->esi;	/* 463448: mov eax, esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46344a: pop esi */
	m->esp += 4 + 4; return;	/* 46344b: ret 4 */
}

/* hud_472900 (0x472900), lifted by tools/lift.py */
static void lift_472900(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 472900: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 472904: push esi */
	m->esi = m->ecx;	/* 472905: mov esi, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 472907: push edi */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 472908: mov edx, dword ptr [eax] */
	{ DWORD v_ = 0x2601u; m->esp -= 4; M32(m->esp) = v_; }	/* 47290a: push 0x2601 */
	m->edi = (DWORD)(m->esi + 0x9ee048u);	/* 47290f: lea edi, [esi + 0x9ee048] */
	{ DWORD v_ = 0xb65u; m->esp -= 4; M32(m->esp) = v_; }	/* 472915: push 0xb65 */
	m->ecx = m->edi;	/* 47291a: mov ecx, edi */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 47291c: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47291e: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 472921: mov dword ptr [ecx + 4], edx */
	m->edx = M32((DWORD)(m->eax + 0x8u));	/* 472924: mov edx, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 472927: mov dword ptr [ecx + 8], edx */
	m->eax = M32((DWORD)(m->eax + 0xcu));	/* 47292a: mov eax, dword ptr [eax + 0xc] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 47292d: mov edx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->ecx + 0xcu)) = m->eax;	/* 472931: mov dword ptr [ecx + 0xc], eax */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 472934: mov ecx, dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 472938: mov eax, dword ptr [esp + 0x20] */
	M32((DWORD)(m->esi + 0x9ee058u)) = m->ecx;	/* 47293c: mov dword ptr [esi + 0x9ee058], ecx */
	M32((DWORD)(m->esi + 0x9ee05cu)) = m->edx;	/* 472942: mov dword ptr [esi + 0x9ee05c], edx */
	M32((DWORD)(m->esi + 0x9ee060u)) = m->eax;	/* 472948: mov dword ptr [esi + 0x9ee060], eax */
	m->esp -= 4; M32(m->esp) = 0x472954u; native_call(m, M32(0x4a9288u));	/* 47294e: call dword ptr [0x4a9288] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 472954: push edi */
	{ DWORD v_ = 0xb66u; m->esp -= 4; M32(m->esp) = v_; }	/* 472955: push 0xb66 */
	m->esp -= 4; M32(m->esp) = 0x472960u; native_call(m, M32(0x4a9284u));	/* 47295a: call dword ptr [0x4a9284] */
	m->ecx = M32((DWORD)(m->esi + 0x9ee060u));	/* 472960: mov ecx, dword ptr [esi + 0x9ee060] */
	m->edi = M32((DWORD)(0x4a9280u));	/* 472966: mov edi, dword ptr [0x4a9280] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47296c: push ecx */
	{ DWORD v_ = 0xb62u; m->esp -= 4; M32(m->esp) = v_; }	/* 47296d: push 0xb62 */
	m->esp -= 4; M32(m->esp) = 0x472974u; native_call(m, m->edi);	/* 472972: call edi */
	{ DWORD v_ = 0x1100u; m->esp -= 4; M32(m->esp) = v_; }	/* 472974: push 0x1100 */
	{ DWORD v_ = 0xc54u; m->esp -= 4; M32(m->esp) = v_; }	/* 472979: push 0xc54 */
	m->esp -= 4; M32(m->esp) = 0x472984u; native_call(m, M32(0x4a924cu));	/* 47297e: call dword ptr [0x4a924c] */
	m->edx = M32((DWORD)(m->esi + 0x9ee058u));	/* 472984: mov edx, dword ptr [esi + 0x9ee058] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47298a: push edx */
	{ DWORD v_ = 0xb63u; m->esp -= 4; M32(m->esp) = v_; }	/* 47298b: push 0xb63 */
	m->esp -= 4; M32(m->esp) = 0x472992u; native_call(m, m->edi);	/* 472990: call edi */
	m->eax = M32((DWORD)(m->esi + 0x9ee05cu));	/* 472992: mov eax, dword ptr [esi + 0x9ee05c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 472998: push eax */
	{ DWORD v_ = 0xb64u; m->esp -= 4; M32(m->esp) = v_; }	/* 472999: push 0xb64 */
	m->esp -= 4; M32(m->esp) = 0x4729a0u; native_call(m, m->edi);	/* 47299e: call edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 4729a0: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4729a1: pop esi */
	m->esp += 4 + 16; return;	/* 4729a2: ret 0x10 */
}

/* hud_427c30 (0x427c30), lifted by tools/lift.py */
static void lift_427c30(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 427c30: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 427c31: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 427c32: push esi */
	m->esi = M32((DWORD)(m->esp + 0x18u));	/* 427c33: mov esi, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 427c37: push edi */
	m->edi = M32((DWORD)(0x4a920cu));	/* 427c38: mov edi, dword ptr [0x4a920c] */
	m->eax = M32((DWORD)(m->esi*4 + 0x5b0910u));	/* 427c3e: mov eax, dword ptr [esi*4 + 0x5b0910] */
	m->ecx = M32((DWORD)(m->esi*4 + 0x5b0d10u));	/* 427c45: mov ecx, dword ptr [esi*4 + 0x5b0d10] */
	m->ebx = (DWORD)(m->esi*4 + 0x5b0d10u);	/* 427c4c: lea ebx, [esi*4 + 0x5b0d10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427c53: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427c54: push ecx */
	m->esp -= 4; M32(m->esp) = 0x427c57u; native_call(m, m->edi);	/* 427c55: call edi */
	m->ebp = M32((DWORD)(m->esp + 0x18u));	/* 427c57: mov ebp, dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 427c5b: mov edx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 427c5f: push ebp */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427c60: push edx */
	m->esp -= 4; M32(m->esp) = 0x427c66u; native_call(m, 0x41ef60u);	/* 427c61: call 0x41ef60 */
	m->ecx = M32((DWORD)(m->esi*4 + 0x5b0910u));	/* 427c66: mov ecx, dword ptr [esi*4 + 0x5b0910] */
	m->edx = M32((DWORD)(m->esi*4 + 0x4e0878u));	/* 427c6d: mov edx, dword ptr [esi*4 + 0x4e0878] */
	m->eax = (DWORD)(m->esi*4 + 0x4e0878u);	/* 427c74: lea eax, [esi*4 + 0x4e0878] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427c7b: add esp, 8 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 427c7e: mov dword ptr [esp + 0x1c], eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427c82: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427c83: push edx */
	m->esp -= 4; M32(m->esp) = 0x427c86u; native_call(m, m->edi);	/* 427c84: call edi */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 427c86: mov eax, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 427c8a: push ebp */
	{ DWORD a_ = m->eax, b_ = 0xdu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 427c8b: add eax, 0xd */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427c8e: push eax */
	m->esp -= 4; M32(m->esp) = 0x427c94u; native_call(m, 0x41ef60u);	/* 427c8f: call 0x41ef60 */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 427c94: mov edx, dword ptr [esp + 0x24] */
	m->ecx = M32((DWORD)(m->esi*4 + 0x4e0474u));	/* 427c98: mov ecx, dword ptr [esi*4 + 0x4e0474] */
	m->esi = (DWORD)(m->esi*4 + 0x4e0474u);	/* 427c9f: lea esi, [esi*4 + 0x4e0474] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427ca6: add esp, 8 */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 427ca9: mov eax, dword ptr [edx] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427cab: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427cac: push eax */
	m->esp -= 4; M32(m->esp) = 0x427cafu; native_call(m, m->edi);	/* 427cad: call edi */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 427caf: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ebp, b_ = 0xdu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 427cb3: add ebp, 0xd */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 427cb6: push ebp */
	m->eax = (DWORD)(m->ecx + 0xdu);	/* 427cb7: lea eax, [ecx + 0xd] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427cba: push eax */
	m->esp -= 4; M32(m->esp) = 0x427cc0u; native_call(m, 0x41ef60u);	/* 427cbb: call 0x41ef60 */
	m->edx = M32((DWORD)(m->esi + 0x0u));	/* 427cc0: mov edx, dword ptr [esi] */
	m->eax = M32((DWORD)(m->ebx + 0x0u));	/* 427cc2: mov eax, dword ptr [ebx] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427cc4: add esp, 8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427cc7: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427cc8: push eax */
	m->esp -= 4; M32(m->esp) = 0x427ccbu; native_call(m, m->edi);	/* 427cc9: call edi */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 427ccb: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 427ccf: push ebp */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427cd0: push ecx */
	m->esp -= 4; M32(m->esp) = 0x427cd6u; native_call(m, 0x41ef60u);	/* 427cd1: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427cd6: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 427cd9: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 427cda: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 427cdb: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 427cdc: pop ebx */
	m->esp += 4 + 0; return;	/* 427cdd: ret  */
}

/* hud_427e30 (0x427e30), lifted by tools/lift.py */
static void lift_427e30(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 427e30: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 427e31: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 427e32: push esi */
	m->esi = M32((DWORD)(m->esp + 0x18u));	/* 427e33: mov esi, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 427e37: push edi */
	m->edi = M32((DWORD)(0x4a920cu));	/* 427e38: mov edi, dword ptr [0x4a920c] */
	m->eax = M32((DWORD)(m->esi*4 + 0x5b0910u));	/* 427e3e: mov eax, dword ptr [esi*4 + 0x5b0910] */
	m->ecx = M32((DWORD)(m->esi*4 + 0x5b0d10u));	/* 427e45: mov ecx, dword ptr [esi*4 + 0x5b0d10] */
	m->ebx = (DWORD)(m->esi*4 + 0x5b0d10u);	/* 427e4c: lea ebx, [esi*4 + 0x5b0d10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427e53: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427e54: push ecx */
	m->esp -= 4; M32(m->esp) = 0x427e57u; native_call(m, m->edi);	/* 427e55: call edi */
	m->ebp = M32((DWORD)(m->esp + 0x18u));	/* 427e57: mov ebp, dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 427e5b: mov edx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 427e5f: push ebp */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427e60: push edx */
	m->esp -= 4; M32(m->esp) = 0x427e66u; native_call(m, 0x41ef60u);	/* 427e61: call 0x41ef60 */
	m->ecx = M32((DWORD)(m->esi*4 + 0x5b0910u));	/* 427e66: mov ecx, dword ptr [esi*4 + 0x5b0910] */
	m->edx = M32((DWORD)(m->esi*4 + 0x4e0878u));	/* 427e6d: mov edx, dword ptr [esi*4 + 0x4e0878] */
	m->eax = (DWORD)(m->esi*4 + 0x4e0878u);	/* 427e74: lea eax, [esi*4 + 0x4e0878] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427e7b: add esp, 8 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 427e7e: mov dword ptr [esp + 0x1c], eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427e82: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427e83: push edx */
	m->esp -= 4; M32(m->esp) = 0x427e86u; native_call(m, m->edi);	/* 427e84: call edi */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 427e86: mov eax, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 427e8a: push ebp */
	{ DWORD a_ = m->eax, b_ = 0x1fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 427e8b: add eax, 0x1f */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427e8e: push eax */
	m->esp -= 4; M32(m->esp) = 0x427e94u; native_call(m, 0x41ef60u);	/* 427e8f: call 0x41ef60 */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 427e94: mov edx, dword ptr [esp + 0x24] */
	m->ecx = M32((DWORD)(m->esi*4 + 0x4e0474u));	/* 427e98: mov ecx, dword ptr [esi*4 + 0x4e0474] */
	m->esi = (DWORD)(m->esi*4 + 0x4e0474u);	/* 427e9f: lea esi, [esi*4 + 0x4e0474] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427ea6: add esp, 8 */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 427ea9: mov eax, dword ptr [edx] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427eab: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427eac: push eax */
	m->esp -= 4; M32(m->esp) = 0x427eafu; native_call(m, m->edi);	/* 427ead: call edi */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 427eaf: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ebp, b_ = 0x1fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 427eb3: add ebp, 0x1f */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 427eb6: push ebp */
	m->eax = (DWORD)(m->ecx + 0x1fu);	/* 427eb7: lea eax, [ecx + 0x1f] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427eba: push eax */
	m->esp -= 4; M32(m->esp) = 0x427ec0u; native_call(m, 0x41ef60u);	/* 427ebb: call 0x41ef60 */
	m->edx = M32((DWORD)(m->esi + 0x0u));	/* 427ec0: mov edx, dword ptr [esi] */
	m->eax = M32((DWORD)(m->ebx + 0x0u));	/* 427ec2: mov eax, dword ptr [ebx] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427ec4: add esp, 8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427ec7: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427ec8: push eax */
	m->esp -= 4; M32(m->esp) = 0x427ecbu; native_call(m, m->edi);	/* 427ec9: call edi */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 427ecb: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 427ecf: push ebp */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427ed0: push ecx */
	m->esp -= 4; M32(m->esp) = 0x427ed6u; native_call(m, 0x41ef60u);	/* 427ed1: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427ed6: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 427ed9: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 427eda: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 427edb: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 427edc: pop ebx */
	m->esp += 4 + 0; return;	/* 427edd: ret  */
}

/* text_quad8 (0x428030), lifted by tools/lift.py */
static void lift_428030(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 428030: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428031: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 428032: push esi */
	m->esi = M32((DWORD)(m->esp + 0x18u));	/* 428033: mov esi, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->esi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->esi = r_; }	/* 428037: dec esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428038: push edi */
	m->edi = M32((DWORD)(0x4a920cu));	/* 428039: mov edi, dword ptr [0x4a920c] */
	m->eax = M32((DWORD)(m->esi*4 + 0x6803acu));	/* 42803f: mov eax, dword ptr [esi*4 + 0x6803ac] */
	m->ecx = M32((DWORD)(m->esi*4 + 0x6807acu));	/* 428046: mov ecx, dword ptr [esi*4 + 0x6807ac] */
	m->ebx = (DWORD)(m->esi*4 + 0x6807acu);	/* 42804d: lea ebx, [esi*4 + 0x6807ac] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 428054: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 428055: push ecx */
	m->esp -= 4; M32(m->esp) = 0x428058u; native_call(m, m->edi);	/* 428056: call edi */
	m->ebp = M32((DWORD)(m->esp + 0x18u));	/* 428058: mov ebp, dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 42805c: mov edx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428060: push ebp */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 428061: push edx */
	m->esp -= 4; M32(m->esp) = 0x428067u; native_call(m, 0x41ef60u);	/* 428062: call 0x41ef60 */
	m->ecx = M32((DWORD)(m->esi*4 + 0x6803acu));	/* 428067: mov ecx, dword ptr [esi*4 + 0x6803ac] */
	m->edx = M32((DWORD)(m->esi*4 + 0x67fb64u));	/* 42806e: mov edx, dword ptr [esi*4 + 0x67fb64] */
	m->eax = (DWORD)(m->esi*4 + 0x67fb64u);	/* 428075: lea eax, [esi*4 + 0x67fb64] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42807c: add esp, 8 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 42807f: mov dword ptr [esp + 0x1c], eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 428083: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 428084: push edx */
	m->esp -= 4; M32(m->esp) = 0x428087u; native_call(m, m->edi);	/* 428085: call edi */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 428087: mov eax, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42808b: push ebp */
	{ DWORD a_ = m->eax, b_ = 0x7u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42808c: add eax, 7 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42808f: push eax */
	m->esp -= 4; M32(m->esp) = 0x428095u; native_call(m, 0x41ef60u);	/* 428090: call 0x41ef60 */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 428095: mov edx, dword ptr [esp + 0x24] */
	m->ecx = M32((DWORD)(m->esi*4 + 0x67ff64u));	/* 428099: mov ecx, dword ptr [esi*4 + 0x67ff64] */
	m->esi = (DWORD)(m->esi*4 + 0x67ff64u);	/* 4280a0: lea esi, [esi*4 + 0x67ff64] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4280a7: add esp, 8 */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 4280aa: mov eax, dword ptr [edx] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4280ac: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4280ad: push eax */
	m->esp -= 4; M32(m->esp) = 0x4280b0u; native_call(m, m->edi);	/* 4280ae: call edi */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 4280b0: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ebp, b_ = 0xfu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 4280b4: add ebp, 0xf */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4280b7: push ebp */
	m->eax = (DWORD)(m->ecx + 0x7u);	/* 4280b8: lea eax, [ecx + 7] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4280bb: push eax */
	m->esp -= 4; M32(m->esp) = 0x4280c1u; native_call(m, 0x41ef60u);	/* 4280bc: call 0x41ef60 */
	m->edx = M32((DWORD)(m->esi + 0x0u));	/* 4280c1: mov edx, dword ptr [esi] */
	m->eax = M32((DWORD)(m->ebx + 0x0u));	/* 4280c3: mov eax, dword ptr [ebx] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4280c5: add esp, 8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4280c8: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4280c9: push eax */
	m->esp -= 4; M32(m->esp) = 0x4280ccu; native_call(m, m->edi);	/* 4280ca: call edi */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 4280cc: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4280d0: push ebp */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4280d1: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4280d7u; native_call(m, 0x41ef60u);	/* 4280d2: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4280d7: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4280da: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4280db: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4280dc: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4280dd: pop ebx */
	m->esp += 4 + 0; return;	/* 4280de: ret  */
}

/* text_quad16 (0x4280e0), lifted by tools/lift.py */
static void lift_4280e0(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4280e0: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4280e1: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4280e2: push esi */
	m->esi = M32((DWORD)(m->esp + 0x18u));	/* 4280e3: mov esi, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->esi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->esi = r_; }	/* 4280e7: dec esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4280e8: push edi */
	m->edi = M32((DWORD)(0x4a920cu));	/* 4280e9: mov edi, dword ptr [0x4a920c] */
	m->eax = M32((DWORD)(m->esi*4 + 0x9da4a8u));	/* 4280ef: mov eax, dword ptr [esi*4 + 0x9da4a8] */
	m->ecx = M32((DWORD)(m->esi*4 + 0x9da90cu));	/* 4280f6: mov ecx, dword ptr [esi*4 + 0x9da90c] */
	m->ebx = (DWORD)(m->esi*4 + 0x9da90cu);	/* 4280fd: lea ebx, [esi*4 + 0x9da90c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 428104: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 428105: push ecx */
	m->esp -= 4; M32(m->esp) = 0x428108u; native_call(m, m->edi);	/* 428106: call edi */
	m->ebp = M32((DWORD)(m->esp + 0x18u));	/* 428108: mov ebp, dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 42810c: mov edx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428110: push ebp */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 428111: push edx */
	m->esp -= 4; M32(m->esp) = 0x428117u; native_call(m, 0x41ef60u);	/* 428112: call 0x41ef60 */
	m->ecx = M32((DWORD)(m->esi*4 + 0x9da4a8u));	/* 428117: mov ecx, dword ptr [esi*4 + 0x9da4a8] */
	m->edx = M32((DWORD)(m->esi*4 + 0x9db510u));	/* 42811e: mov edx, dword ptr [esi*4 + 0x9db510] */
	m->eax = (DWORD)(m->esi*4 + 0x9db510u);	/* 428125: lea eax, [esi*4 + 0x9db510] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42812c: add esp, 8 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 42812f: mov dword ptr [esp + 0x1c], eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 428133: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 428134: push edx */
	m->esp -= 4; M32(m->esp) = 0x428137u; native_call(m, m->edi);	/* 428135: call edi */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 428137: mov eax, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42813b: push ebp */
	{ DWORD a_ = m->eax, b_ = 0xfu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42813c: add eax, 0xf */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42813f: push eax */
	m->esp -= 4; M32(m->esp) = 0x428145u; native_call(m, 0x41ef60u);	/* 428140: call 0x41ef60 */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 428145: mov edx, dword ptr [esp + 0x24] */
	m->ecx = M32((DWORD)(m->esi*4 + 0x9db0b0u));	/* 428149: mov ecx, dword ptr [esi*4 + 0x9db0b0] */
	m->esi = (DWORD)(m->esi*4 + 0x9db0b0u);	/* 428150: lea esi, [esi*4 + 0x9db0b0] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428157: add esp, 8 */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 42815a: mov eax, dword ptr [edx] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42815c: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42815d: push eax */
	m->esp -= 4; M32(m->esp) = 0x428160u; native_call(m, m->edi);	/* 42815e: call edi */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 428160: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ebp, b_ = 0xfu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 428164: add ebp, 0xf */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428167: push ebp */
	m->eax = (DWORD)(m->ecx + 0xfu);	/* 428168: lea eax, [ecx + 0xf] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42816b: push eax */
	m->esp -= 4; M32(m->esp) = 0x428171u; native_call(m, 0x41ef60u);	/* 42816c: call 0x41ef60 */
	m->edx = M32((DWORD)(m->esi + 0x0u));	/* 428171: mov edx, dword ptr [esi] */
	m->eax = M32((DWORD)(m->ebx + 0x0u));	/* 428173: mov eax, dword ptr [ebx] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428175: add esp, 8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 428178: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 428179: push eax */
	m->esp -= 4; M32(m->esp) = 0x42817cu; native_call(m, m->edi);	/* 42817a: call edi */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 42817c: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428180: push ebp */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 428181: push ecx */
	m->esp -= 4; M32(m->esp) = 0x428187u; native_call(m, 0x41ef60u);	/* 428182: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428187: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 42818a: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 42818b: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 42818c: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 42818d: pop ebx */
	m->esp += 4 + 0; return;	/* 42818e: ret  */
}

/* text_quad32 (0x428190), lifted by tools/lift.py */
static void lift_428190(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 428190: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428191: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 428192: push esi */
	m->esi = M32((DWORD)(m->esp + 0x18u));	/* 428193: mov esi, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->esi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->esi = r_; }	/* 428197: dec esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428198: push edi */
	m->edi = M32((DWORD)(0x4a920cu));	/* 428199: mov edi, dword ptr [0x4a920c] */
	m->eax = M32((DWORD)(m->esi*4 + 0x9da4a8u));	/* 42819f: mov eax, dword ptr [esi*4 + 0x9da4a8] */
	m->ecx = M32((DWORD)(m->esi*4 + 0x9da90cu));	/* 4281a6: mov ecx, dword ptr [esi*4 + 0x9da90c] */
	m->ebx = (DWORD)(m->esi*4 + 0x9da90cu);	/* 4281ad: lea ebx, [esi*4 + 0x9da90c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4281b4: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4281b5: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4281b8u; native_call(m, m->edi);	/* 4281b6: call edi */
	m->ebp = M32((DWORD)(m->esp + 0x18u));	/* 4281b8: mov ebp, dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 4281bc: mov edx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4281c0: push ebp */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4281c1: push edx */
	m->esp -= 4; M32(m->esp) = 0x4281c7u; native_call(m, 0x41ef60u);	/* 4281c2: call 0x41ef60 */
	m->ecx = M32((DWORD)(m->esi*4 + 0x9da4a8u));	/* 4281c7: mov ecx, dword ptr [esi*4 + 0x9da4a8] */
	m->edx = M32((DWORD)(m->esi*4 + 0x9db510u));	/* 4281ce: mov edx, dword ptr [esi*4 + 0x9db510] */
	m->eax = (DWORD)(m->esi*4 + 0x9db510u);	/* 4281d5: lea eax, [esi*4 + 0x9db510] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4281dc: add esp, 8 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 4281df: mov dword ptr [esp + 0x1c], eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4281e3: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4281e4: push edx */
	m->esp -= 4; M32(m->esp) = 0x4281e7u; native_call(m, m->edi);	/* 4281e5: call edi */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4281e7: mov eax, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4281eb: push ebp */
	{ DWORD a_ = m->eax, b_ = 0x17u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4281ec: add eax, 0x17 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4281ef: push eax */
	m->esp -= 4; M32(m->esp) = 0x4281f5u; native_call(m, 0x41ef60u);	/* 4281f0: call 0x41ef60 */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 4281f5: mov edx, dword ptr [esp + 0x24] */
	m->ecx = M32((DWORD)(m->esi*4 + 0x9db0b0u));	/* 4281f9: mov ecx, dword ptr [esi*4 + 0x9db0b0] */
	m->esi = (DWORD)(m->esi*4 + 0x9db0b0u);	/* 428200: lea esi, [esi*4 + 0x9db0b0] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428207: add esp, 8 */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 42820a: mov eax, dword ptr [edx] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42820c: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42820d: push eax */
	m->esp -= 4; M32(m->esp) = 0x428210u; native_call(m, m->edi);	/* 42820e: call edi */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 428210: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ebp, b_ = 0x1fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 428214: add ebp, 0x1f */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428217: push ebp */
	m->eax = (DWORD)(m->ecx + 0x17u);	/* 428218: lea eax, [ecx + 0x17] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42821b: push eax */
	m->esp -= 4; M32(m->esp) = 0x428221u; native_call(m, 0x41ef60u);	/* 42821c: call 0x41ef60 */
	m->edx = M32((DWORD)(m->esi + 0x0u));	/* 428221: mov edx, dword ptr [esi] */
	m->eax = M32((DWORD)(m->ebx + 0x0u));	/* 428223: mov eax, dword ptr [ebx] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428225: add esp, 8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 428228: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 428229: push eax */
	m->esp -= 4; M32(m->esp) = 0x42822cu; native_call(m, m->edi);	/* 42822a: call edi */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 42822c: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428230: push ebp */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 428231: push ecx */
	m->esp -= 4; M32(m->esp) = 0x428237u; native_call(m, 0x41ef60u);	/* 428232: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428237: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 42823a: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 42823b: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 42823c: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 42823d: pop ebx */
	m->esp += 4 + 0; return;	/* 42823e: ret  */
}

/* text_quad5 (0x428240), lifted by tools/lift.py */
static void lift_428240(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 428240: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428241: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 428242: push esi */
	m->esi = M32((DWORD)(m->esp + 0x18u));	/* 428243: mov esi, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->esi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->esi = r_; }	/* 428247: dec esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428248: push edi */
	m->edi = M32((DWORD)(0x4a920cu));	/* 428249: mov edi, dword ptr [0x4a920c] */
	m->eax = M32((DWORD)(m->esi*4 + 0x5b1114u));	/* 42824f: mov eax, dword ptr [esi*4 + 0x5b1114] */
	m->ecx = M32((DWORD)(m->esi*4 + 0x5b1514u));	/* 428256: mov ecx, dword ptr [esi*4 + 0x5b1514] */
	m->ebx = (DWORD)(m->esi*4 + 0x5b1514u);	/* 42825d: lea ebx, [esi*4 + 0x5b1514] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 428264: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 428265: push ecx */
	m->esp -= 4; M32(m->esp) = 0x428268u; native_call(m, m->edi);	/* 428266: call edi */
	m->ebp = M32((DWORD)(m->esp + 0x18u));	/* 428268: mov ebp, dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 42826c: mov edx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428270: push ebp */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 428271: push edx */
	m->esp -= 4; M32(m->esp) = 0x428277u; native_call(m, 0x41ef60u);	/* 428272: call 0x41ef60 */
	m->ecx = M32((DWORD)(m->esi*4 + 0x5b1114u));	/* 428277: mov ecx, dword ptr [esi*4 + 0x5b1114] */
	m->edx = M32((DWORD)(m->esi*4 + 0x4e10e8u));	/* 42827e: mov edx, dword ptr [esi*4 + 0x4e10e8] */
	m->eax = (DWORD)(m->esi*4 + 0x4e10e8u);	/* 428285: lea eax, [esi*4 + 0x4e10e8] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42828c: add esp, 8 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 42828f: mov dword ptr [esp + 0x1c], eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 428293: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 428294: push edx */
	m->esp -= 4; M32(m->esp) = 0x428297u; native_call(m, m->edi);	/* 428295: call edi */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 428297: mov eax, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42829b: push ebp */
	{ DWORD a_ = m->eax, b_ = 0x7u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42829c: add eax, 7 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42829f: push eax */
	m->esp -= 4; M32(m->esp) = 0x4282a5u; native_call(m, 0x41ef60u);	/* 4282a0: call 0x41ef60 */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 4282a5: mov edx, dword ptr [esp + 0x24] */
	m->ecx = M32((DWORD)(m->esi*4 + 0x4e0ce4u));	/* 4282a9: mov ecx, dword ptr [esi*4 + 0x4e0ce4] */
	m->esi = (DWORD)(m->esi*4 + 0x4e0ce4u);	/* 4282b0: lea esi, [esi*4 + 0x4e0ce4] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4282b7: add esp, 8 */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 4282ba: mov eax, dword ptr [edx] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4282bc: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4282bd: push eax */
	m->esp -= 4; M32(m->esp) = 0x4282c0u; native_call(m, m->edi);	/* 4282be: call edi */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 4282c0: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ebp, b_ = 0x7u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 4282c4: add ebp, 7 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4282c7: push ebp */
	m->eax = (DWORD)(m->ecx + 0x7u);	/* 4282c8: lea eax, [ecx + 7] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4282cb: push eax */
	m->esp -= 4; M32(m->esp) = 0x4282d1u; native_call(m, 0x41ef60u);	/* 4282cc: call 0x41ef60 */
	m->edx = M32((DWORD)(m->esi + 0x0u));	/* 4282d1: mov edx, dword ptr [esi] */
	m->eax = M32((DWORD)(m->ebx + 0x0u));	/* 4282d3: mov eax, dword ptr [ebx] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4282d5: add esp, 8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4282d8: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4282d9: push eax */
	m->esp -= 4; M32(m->esp) = 0x4282dcu; native_call(m, m->edi);	/* 4282da: call edi */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 4282dc: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4282e0: push ebp */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4282e1: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4282e7u; native_call(m, 0x41ef60u);	/* 4282e2: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4282e7: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4282ea: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4282eb: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4282ec: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4282ed: pop ebx */
	m->esp += 4 + 0; return;	/* 4282ee: ret  */
}

/* profile_4283e0 (0x4283e0), lifted by tools/lift.py */
static void lift_4283e0(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4283e0: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4283e1: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4283e2: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4283e3: push edi */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4283e4: push 7 */
	m->esp -= 4; M32(m->esp) = 0x4283ecu; native_call(m, M32(0x4a921cu));	/* 4283e6: call dword ptr [0x4a921c] */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x24u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4283ec: cmp dword ptr [esp + 0x24], 1 */
	if (!m->zf) goto L_42844f;	/* 4283f1: jne 0x42844f */
	m->esi = M32((DWORD)(0x4a920cu));	/* 4283f3: mov esi, dword ptr [0x4a920c] */
	{ DWORD v_ = 0x3f280000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4283f9: push 0x3f280000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4283fe: push 0 */
	m->esp -= 4; M32(m->esp) = 0x428402u; native_call(m, m->esi);	/* 428400: call esi */
	m->edi = M32((DWORD)(m->esp + 0x18u));	/* 428402: mov edi, dword ptr [esp + 0x18] */
	m->ebx = M32((DWORD)(m->esp + 0x14u));	/* 428406: mov ebx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42840a: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42840b: push ebx */
	m->esp -= 4; M32(m->esp) = 0x428411u; native_call(m, 0x41ef60u);	/* 42840c: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428411: add esp, 8 */
	{ DWORD v_ = 0x3f280000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428414: push 0x3f280000 */
	{ DWORD v_ = 0x3f200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428419: push 0x3f200000 */
	m->esp -= 4; M32(m->esp) = 0x428420u; native_call(m, m->esi);	/* 42841e: call esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428420: push edi */
	m->edi = M32((DWORD)(m->esp + 0x20u));	/* 428421: mov edi, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428425: push edi */
	m->esp -= 4; M32(m->esp) = 0x42842bu; native_call(m, 0x41ef60u);	/* 428426: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42842b: add esp, 8 */
	{ DWORD v_ = 0x3f500000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42842e: push 0x3f500000 */
	{ DWORD v_ = 0x3f200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428433: push 0x3f200000 */
	m->esp -= 4; M32(m->esp) = 0x42843au; native_call(m, m->esi);	/* 428438: call esi */
	m->ebp = M32((DWORD)(m->esp + 0x20u));	/* 42843a: mov ebp, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42843e: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42843f: push edi */
	m->esp -= 4; M32(m->esp) = 0x428445u; native_call(m, 0x41ef60u);	/* 428440: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428445: add esp, 8 */
	{ DWORD v_ = 0x3f500000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428448: push 0x3f500000 */
	goto L_4284a9;	/* 42844d: jmp 0x4284a9 */
L_42844f:
	m->esi = M32((DWORD)(0x4a920cu));	/* 42844f: mov esi, dword ptr [0x4a920c] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428455: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42845a: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42845eu; native_call(m, m->esi);	/* 42845c: call esi */
	m->edi = M32((DWORD)(m->esp + 0x18u));	/* 42845e: mov edi, dword ptr [esp + 0x18] */
	m->ebx = M32((DWORD)(m->esp + 0x14u));	/* 428462: mov ebx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428466: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 428467: push ebx */
	m->esp -= 4; M32(m->esp) = 0x42846du; native_call(m, 0x41ef60u);	/* 428468: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42846d: add esp, 8 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428470: push 0x3f000000 */
	{ DWORD v_ = 0x3f200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428475: push 0x3f200000 */
	m->esp -= 4; M32(m->esp) = 0x42847cu; native_call(m, m->esi);	/* 42847a: call esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42847c: push edi */
	m->edi = M32((DWORD)(m->esp + 0x20u));	/* 42847d: mov edi, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428481: push edi */
	m->esp -= 4; M32(m->esp) = 0x428487u; native_call(m, 0x41ef60u);	/* 428482: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428487: add esp, 8 */
	{ DWORD v_ = 0x3f280000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42848a: push 0x3f280000 */
	{ DWORD v_ = 0x3f200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42848f: push 0x3f200000 */
	m->esp -= 4; M32(m->esp) = 0x428496u; native_call(m, m->esi);	/* 428494: call esi */
	m->ebp = M32((DWORD)(m->esp + 0x20u));	/* 428496: mov ebp, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42849a: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42849b: push edi */
	m->esp -= 4; M32(m->esp) = 0x4284a1u; native_call(m, 0x41ef60u);	/* 42849c: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4284a1: add esp, 8 */
	{ DWORD v_ = 0x3f280000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4284a4: push 0x3f280000 */
L_4284a9:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4284a9: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4284adu; native_call(m, m->esi);	/* 4284ab: call esi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4284ad: push ebp */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4284ae: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4284b4u; native_call(m, 0x41ef60u);	/* 4284af: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4284b4: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x4284bdu; native_call(m, M32(0x4a9220u));	/* 4284b7: call dword ptr [0x4a9220] */
	m->edi = M32(m->esp); m->esp += 4;	/* 4284bd: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4284be: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4284bf: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4284c0: pop ebx */
	m->esp += 4 + 0; return;	/* 4284c1: ret  */
}

/* menu_drawTexQuad_4284d0 (0x4284d0), lifted by tools/lift.py */
static void lift_4284d0(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4284d0: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4284d1: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4284d2: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4284d3: push edi */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4284d4: push 7 */
	m->esp -= 4; M32(m->esp) = 0x4284dcu; native_call(m, M32(0x4a921cu));	/* 4284d6: call dword ptr [0x4a921c] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 4284dc: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4284e0: push 0x3e800000 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4284e5: cmp eax, 1 */
	if (!m->zf) goto L_428549;	/* 4284e8: jne 0x428549 */
	m->esi = M32((DWORD)(0x4a920cu));	/* 4284ea: mov esi, dword ptr [0x4a920c] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4284f0: push 0x3f000000 */
	m->esp -= 4; M32(m->esp) = 0x4284f7u; native_call(m, m->esi);	/* 4284f5: call esi */
	m->edi = M32((DWORD)(m->esp + 0x18u));	/* 4284f7: mov edi, dword ptr [esp + 0x18] */
	m->ebx = M32((DWORD)(m->esp + 0x14u));	/* 4284fb: mov ebx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4284ff: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 428500: push ebx */
	m->esp -= 4; M32(m->esp) = 0x428506u; native_call(m, 0x41ef60u);	/* 428501: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428506: add esp, 8 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428509: push 0x3e800000 */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42850e: push 0x3f400000 */
	m->esp -= 4; M32(m->esp) = 0x428515u; native_call(m, m->esi);	/* 428513: call esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428515: push edi */
	m->edi = M32((DWORD)(m->esp + 0x20u));	/* 428516: mov edi, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42851a: push edi */
	m->esp -= 4; M32(m->esp) = 0x428520u; native_call(m, 0x41ef60u);	/* 42851b: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428520: add esp, 8 */
	{ DWORD v_ = 0x3ec00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428523: push 0x3ec00000 */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428528: push 0x3f400000 */
	m->esp -= 4; M32(m->esp) = 0x42852fu; native_call(m, m->esi);	/* 42852d: call esi */
	m->ebp = M32((DWORD)(m->esp + 0x20u));	/* 42852f: mov ebp, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428533: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428534: push edi */
	m->esp -= 4; M32(m->esp) = 0x42853au; native_call(m, 0x41ef60u);	/* 428535: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42853a: add esp, 8 */
	{ DWORD v_ = 0x3ec00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42853d: push 0x3ec00000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428542: push 0x3f000000 */
	goto L_4285a0;	/* 428547: jmp 0x4285a0 */
L_428549:
	m->esi = M32((DWORD)(0x4a920cu));	/* 428549: mov esi, dword ptr [0x4a920c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42854f: push 0 */
	m->esp -= 4; M32(m->esp) = 0x428553u; native_call(m, m->esi);	/* 428551: call esi */
	m->edi = M32((DWORD)(m->esp + 0x18u));	/* 428553: mov edi, dword ptr [esp + 0x18] */
	m->ebx = M32((DWORD)(m->esp + 0x14u));	/* 428557: mov ebx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42855b: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42855c: push ebx */
	m->esp -= 4; M32(m->esp) = 0x428562u; native_call(m, 0x41ef60u);	/* 42855d: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428562: add esp, 8 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428565: push 0x3e800000 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42856a: push 0x3e800000 */
	m->esp -= 4; M32(m->esp) = 0x428571u; native_call(m, m->esi);	/* 42856f: call esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428571: push edi */
	m->edi = M32((DWORD)(m->esp + 0x20u));	/* 428572: mov edi, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428576: push edi */
	m->esp -= 4; M32(m->esp) = 0x42857cu; native_call(m, 0x41ef60u);	/* 428577: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42857c: add esp, 8 */
	{ DWORD v_ = 0x3ec00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42857f: push 0x3ec00000 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428584: push 0x3e800000 */
	m->esp -= 4; M32(m->esp) = 0x42858bu; native_call(m, m->esi);	/* 428589: call esi */
	m->ebp = M32((DWORD)(m->esp + 0x20u));	/* 42858b: mov ebp, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42858f: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428590: push edi */
	m->esp -= 4; M32(m->esp) = 0x428596u; native_call(m, 0x41ef60u);	/* 428591: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428596: add esp, 8 */
	{ DWORD v_ = 0x3ec00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428599: push 0x3ec00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42859e: push 0 */
L_4285a0:
	m->esp -= 4; M32(m->esp) = 0x4285a2u; native_call(m, m->esi);	/* 4285a0: call esi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4285a2: push ebp */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4285a3: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4285a9u; native_call(m, 0x41ef60u);	/* 4285a4: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4285a9: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x4285b2u; native_call(m, M32(0x4a9220u));	/* 4285ac: call dword ptr [0x4a9220] */
	m->edi = M32(m->esp); m->esp += 4;	/* 4285b2: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4285b3: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4285b4: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4285b5: pop ebx */
	m->esp += 4 + 0; return;	/* 4285b6: ret  */
}

/* menu_drawTexQuad_4282f0 (0x4282f0), lifted by tools/lift.py */
static void lift_4282f0(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4282f0: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4282f1: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4282f2: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4282f3: push edi */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4282f4: push 7 */
	m->esp -= 4; M32(m->esp) = 0x4282fcu; native_call(m, M32(0x4a921cu));	/* 4282f6: call dword ptr [0x4a921c] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 4282fc: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = 0x3ec00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428300: push 0x3ec00000 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 428305: cmp eax, 1 */
	if (!m->zf) goto L_428369;	/* 428308: jne 0x428369 */
	m->esi = M32((DWORD)(0x4a920cu));	/* 42830a: mov esi, dword ptr [0x4a920c] */
	{ DWORD v_ = 0x3ec28f5cu; m->esp -= 4; M32(m->esp) = v_; }	/* 428310: push 0x3ec28f5c */
	m->esp -= 4; M32(m->esp) = 0x428317u; native_call(m, m->esi);	/* 428315: call esi */
	m->edi = M32((DWORD)(m->esp + 0x18u));	/* 428317: mov edi, dword ptr [esp + 0x18] */
	m->ebx = M32((DWORD)(m->esp + 0x14u));	/* 42831b: mov ebx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42831f: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 428320: push ebx */
	m->esp -= 4; M32(m->esp) = 0x428326u; native_call(m, 0x41ef60u);	/* 428321: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428326: add esp, 8 */
	{ DWORD v_ = 0x3ec00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428329: push 0x3ec00000 */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42832e: push 0x3f400000 */
	m->esp -= 4; M32(m->esp) = 0x428335u; native_call(m, m->esi);	/* 428333: call esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428335: push edi */
	m->edi = M32((DWORD)(m->esp + 0x20u));	/* 428336: mov edi, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42833a: push edi */
	m->esp -= 4; M32(m->esp) = 0x428340u; native_call(m, 0x41ef60u);	/* 42833b: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428340: add esp, 8 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428343: push 0x3f000000 */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428348: push 0x3f400000 */
	m->esp -= 4; M32(m->esp) = 0x42834fu; native_call(m, m->esi);	/* 42834d: call esi */
	m->ebp = M32((DWORD)(m->esp + 0x20u));	/* 42834f: mov ebp, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428353: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428354: push edi */
	m->esp -= 4; M32(m->esp) = 0x42835au; native_call(m, 0x41ef60u);	/* 428355: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42835a: add esp, 8 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42835d: push 0x3f000000 */
	{ DWORD v_ = 0x3ec28f5cu; m->esp -= 4; M32(m->esp) = v_; }	/* 428362: push 0x3ec28f5c */
	goto L_4283c6;	/* 428367: jmp 0x4283c6 */
L_428369:
	m->esi = M32((DWORD)(0x4a920cu));	/* 428369: mov esi, dword ptr [0x4a920c] */
	{ DWORD v_ = 0x3ba3d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 42836f: push 0x3ba3d70a */
	m->esp -= 4; M32(m->esp) = 0x428376u; native_call(m, m->esi);	/* 428374: call esi */
	m->edi = M32((DWORD)(m->esp + 0x18u));	/* 428376: mov edi, dword ptr [esp + 0x18] */
	m->ebx = M32((DWORD)(m->esp + 0x14u));	/* 42837a: mov ebx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42837e: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42837f: push ebx */
	m->esp -= 4; M32(m->esp) = 0x428385u; native_call(m, 0x41ef60u);	/* 428380: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428385: add esp, 8 */
	{ DWORD v_ = 0x3ec00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428388: push 0x3ec00000 */
	{ DWORD v_ = 0x3ec00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42838d: push 0x3ec00000 */
	m->esp -= 4; M32(m->esp) = 0x428394u; native_call(m, m->esi);	/* 428392: call esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428394: push edi */
	m->edi = M32((DWORD)(m->esp + 0x20u));	/* 428395: mov edi, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428399: push edi */
	m->esp -= 4; M32(m->esp) = 0x42839fu; native_call(m, 0x41ef60u);	/* 42839a: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42839f: add esp, 8 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4283a2: push 0x3f000000 */
	{ DWORD v_ = 0x3ec00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4283a7: push 0x3ec00000 */
	m->esp -= 4; M32(m->esp) = 0x4283aeu; native_call(m, m->esi);	/* 4283ac: call esi */
	m->ebp = M32((DWORD)(m->esp + 0x20u));	/* 4283ae: mov ebp, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4283b2: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4283b3: push edi */
	m->esp -= 4; M32(m->esp) = 0x4283b9u; native_call(m, 0x41ef60u);	/* 4283b4: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4283b9: add esp, 8 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4283bc: push 0x3f000000 */
	{ DWORD v_ = 0x3ba3d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 4283c1: push 0x3ba3d70a */
L_4283c6:
	m->esp -= 4; M32(m->esp) = 0x4283c8u; native_call(m, m->esi);	/* 4283c6: call esi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4283c8: push ebp */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4283c9: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4283cfu; native_call(m, 0x41ef60u);	/* 4283ca: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4283cf: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x4283d8u; native_call(m, M32(0x4a9220u));	/* 4283d2: call dword ptr [0x4a9220] */
	m->edi = M32(m->esp); m->esp += 4;	/* 4283d8: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4283d9: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4283da: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4283db: pop ebx */
	m->esp += 4 + 0; return;	/* 4283dc: ret  */
}

/* menu_drawTexQuad_4285c0 (0x4285c0), lifted by tools/lift.py */
static void lift_4285c0(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4285c0: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4285c1: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4285c2: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4285c3: push edi */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4285c4: push 7 */
	m->esp -= 4; M32(m->esp) = 0x4285ccu; native_call(m, M32(0x4a921cu));	/* 4285c6: call dword ptr [0x4a921c] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 4285cc: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4285d0: push 0x3e800000 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4285d5: cmp eax, 1 */
	if (!m->zf) goto L_428639;	/* 4285d8: jne 0x428639 */
	m->esi = M32((DWORD)(0x4a920cu));	/* 4285da: mov esi, dword ptr [0x4a920c] */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4285e0: push 0x3f400000 */
	m->esp -= 4; M32(m->esp) = 0x4285e7u; native_call(m, m->esi);	/* 4285e5: call esi */
	m->edi = M32((DWORD)(m->esp + 0x18u));	/* 4285e7: mov edi, dword ptr [esp + 0x18] */
	m->ebx = M32((DWORD)(m->esp + 0x14u));	/* 4285eb: mov ebx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4285ef: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4285f0: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4285f6u; native_call(m, 0x41ef60u);	/* 4285f1: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4285f6: add esp, 8 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4285f9: push 0x3e800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4285fe: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x428605u; native_call(m, m->esi);	/* 428603: call esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428605: push edi */
	m->edi = M32((DWORD)(m->esp + 0x20u));	/* 428606: mov edi, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42860a: push edi */
	m->esp -= 4; M32(m->esp) = 0x428610u; native_call(m, 0x41ef60u);	/* 42860b: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428610: add esp, 8 */
	{ DWORD v_ = 0x3ec00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428613: push 0x3ec00000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428618: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x42861fu; native_call(m, m->esi);	/* 42861d: call esi */
	m->ebp = M32((DWORD)(m->esp + 0x20u));	/* 42861f: mov ebp, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428623: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428624: push edi */
	m->esp -= 4; M32(m->esp) = 0x42862au; native_call(m, 0x41ef60u);	/* 428625: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42862a: add esp, 8 */
	{ DWORD v_ = 0x3ec00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42862d: push 0x3ec00000 */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428632: push 0x3f400000 */
	goto L_428696;	/* 428637: jmp 0x428696 */
L_428639:
	m->esi = M32((DWORD)(0x4a920cu));	/* 428639: mov esi, dword ptr [0x4a920c] */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42863f: push 0x3e800000 */
	m->esp -= 4; M32(m->esp) = 0x428646u; native_call(m, m->esi);	/* 428644: call esi */
	m->edi = M32((DWORD)(m->esp + 0x18u));	/* 428646: mov edi, dword ptr [esp + 0x18] */
	m->ebx = M32((DWORD)(m->esp + 0x14u));	/* 42864a: mov ebx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42864e: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42864f: push ebx */
	m->esp -= 4; M32(m->esp) = 0x428655u; native_call(m, 0x41ef60u);	/* 428650: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428655: add esp, 8 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428658: push 0x3e800000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42865d: push 0x3f000000 */
	m->esp -= 4; M32(m->esp) = 0x428664u; native_call(m, m->esi);	/* 428662: call esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428664: push edi */
	m->edi = M32((DWORD)(m->esp + 0x20u));	/* 428665: mov edi, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428669: push edi */
	m->esp -= 4; M32(m->esp) = 0x42866fu; native_call(m, 0x41ef60u);	/* 42866a: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42866f: add esp, 8 */
	{ DWORD v_ = 0x3ec00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428672: push 0x3ec00000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428677: push 0x3f000000 */
	m->esp -= 4; M32(m->esp) = 0x42867eu; native_call(m, m->esi);	/* 42867c: call esi */
	m->ebp = M32((DWORD)(m->esp + 0x20u));	/* 42867e: mov ebp, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428682: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428683: push edi */
	m->esp -= 4; M32(m->esp) = 0x428689u; native_call(m, 0x41ef60u);	/* 428684: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428689: add esp, 8 */
	{ DWORD v_ = 0x3ec00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42868c: push 0x3ec00000 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428691: push 0x3e800000 */
L_428696:
	m->esp -= 4; M32(m->esp) = 0x428698u; native_call(m, m->esi);	/* 428696: call esi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428698: push ebp */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 428699: push ebx */
	m->esp -= 4; M32(m->esp) = 0x42869fu; native_call(m, 0x41ef60u);	/* 42869a: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42869f: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x4286a8u; native_call(m, M32(0x4a9220u));	/* 4286a2: call dword ptr [0x4a9220] */
	m->edi = M32(m->esp); m->esp += 4;	/* 4286a8: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4286a9: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4286aa: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4286ab: pop ebx */
	m->esp += 4 + 0; return;	/* 4286ac: ret  */
}

/* menu_drawTexQuad_4286b0 (0x4286b0), lifted by tools/lift.py */
static void lift_4286b0(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4286b0: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4286b1: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4286b2: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4286b3: push edi */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4286b4: push 7 */
	m->esp -= 4; M32(m->esp) = 0x4286bcu; native_call(m, M32(0x4a921cu));	/* 4286b6: call dword ptr [0x4a921c] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 4286bc: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = 0x3ec00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4286c0: push 0x3ec00000 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4286c5: cmp eax, 1 */
	if (!m->zf) goto L_428729;	/* 4286c8: jne 0x428729 */
	m->esi = M32((DWORD)(0x4a920cu));	/* 4286ca: mov esi, dword ptr [0x4a920c] */
	{ DWORD v_ = 0x3f600000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4286d0: push 0x3f600000 */
	m->esp -= 4; M32(m->esp) = 0x4286d7u; native_call(m, m->esi);	/* 4286d5: call esi */
	m->edi = M32((DWORD)(m->esp + 0x18u));	/* 4286d7: mov edi, dword ptr [esp + 0x18] */
	m->ebx = M32((DWORD)(m->esp + 0x14u));	/* 4286db: mov ebx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4286df: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4286e0: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4286e6u; native_call(m, 0x41ef60u);	/* 4286e1: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4286e6: add esp, 8 */
	{ DWORD v_ = 0x3ec00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4286e9: push 0x3ec00000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4286ee: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4286f5u; native_call(m, m->esi);	/* 4286f3: call esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4286f5: push edi */
	m->edi = M32((DWORD)(m->esp + 0x20u));	/* 4286f6: mov edi, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4286fa: push edi */
	m->esp -= 4; M32(m->esp) = 0x428700u; native_call(m, 0x41ef60u);	/* 4286fb: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428700: add esp, 8 */
	{ DWORD v_ = 0x3f200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428703: push 0x3f200000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428708: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x42870fu; native_call(m, m->esi);	/* 42870d: call esi */
	m->ebp = M32((DWORD)(m->esp + 0x20u));	/* 42870f: mov ebp, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428713: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428714: push edi */
	m->esp -= 4; M32(m->esp) = 0x42871au; native_call(m, 0x41ef60u);	/* 428715: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42871a: add esp, 8 */
	{ DWORD v_ = 0x3f200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42871d: push 0x3f200000 */
	{ DWORD v_ = 0x3f600000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428722: push 0x3f600000 */
	goto L_428786;	/* 428727: jmp 0x428786 */
L_428729:
	m->esi = M32((DWORD)(0x4a920cu));	/* 428729: mov esi, dword ptr [0x4a920c] */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42872f: push 0x3f400000 */
	m->esp -= 4; M32(m->esp) = 0x428736u; native_call(m, m->esi);	/* 428734: call esi */
	m->edi = M32((DWORD)(m->esp + 0x18u));	/* 428736: mov edi, dword ptr [esp + 0x18] */
	m->ebx = M32((DWORD)(m->esp + 0x14u));	/* 42873a: mov ebx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42873e: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42873f: push ebx */
	m->esp -= 4; M32(m->esp) = 0x428745u; native_call(m, 0x41ef60u);	/* 428740: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428745: add esp, 8 */
	{ DWORD v_ = 0x3ec00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428748: push 0x3ec00000 */
	{ DWORD v_ = 0x3f600000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42874d: push 0x3f600000 */
	m->esp -= 4; M32(m->esp) = 0x428754u; native_call(m, m->esi);	/* 428752: call esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428754: push edi */
	m->edi = M32((DWORD)(m->esp + 0x20u));	/* 428755: mov edi, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428759: push edi */
	m->esp -= 4; M32(m->esp) = 0x42875fu; native_call(m, 0x41ef60u);	/* 42875a: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42875f: add esp, 8 */
	{ DWORD v_ = 0x3f200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428762: push 0x3f200000 */
	{ DWORD v_ = 0x3f600000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428767: push 0x3f600000 */
	m->esp -= 4; M32(m->esp) = 0x42876eu; native_call(m, m->esi);	/* 42876c: call esi */
	m->ebp = M32((DWORD)(m->esp + 0x20u));	/* 42876e: mov ebp, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428772: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428773: push edi */
	m->esp -= 4; M32(m->esp) = 0x428779u; native_call(m, 0x41ef60u);	/* 428774: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428779: add esp, 8 */
	{ DWORD v_ = 0x3f200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42877c: push 0x3f200000 */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428781: push 0x3f400000 */
L_428786:
	m->esp -= 4; M32(m->esp) = 0x428788u; native_call(m, m->esi);	/* 428786: call esi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428788: push ebp */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 428789: push ebx */
	m->esp -= 4; M32(m->esp) = 0x42878fu; native_call(m, 0x41ef60u);	/* 42878a: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42878f: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x428798u; native_call(m, M32(0x4a9220u));	/* 428792: call dword ptr [0x4a9220] */
	m->edi = M32(m->esp); m->esp += 4;	/* 428798: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 428799: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 42879a: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 42879b: pop ebx */
	m->esp += 4 + 0; return;	/* 42879c: ret  */
}

/* menu_drawTexQuad_4287a0 (0x4287a0), lifted by tools/lift.py */
static void lift_4287a0(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4287a0: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4287a1: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4287a2: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4287a3: push edi */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4287a4: push 7 */
	m->esp -= 4; M32(m->esp) = 0x4287acu; native_call(m, M32(0x4a921cu));	/* 4287a6: call dword ptr [0x4a921c] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 4287ac: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = 0x3f200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4287b0: push 0x3f200000 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4287b5: cmp eax, 1 */
	if (!m->zf) goto L_428819;	/* 4287b8: jne 0x428819 */
	m->esi = M32((DWORD)(0x4a920cu));	/* 4287ba: mov esi, dword ptr [0x4a920c] */
	{ DWORD v_ = 0x3f600000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4287c0: push 0x3f600000 */
	m->esp -= 4; M32(m->esp) = 0x4287c7u; native_call(m, m->esi);	/* 4287c5: call esi */
	m->edi = M32((DWORD)(m->esp + 0x18u));	/* 4287c7: mov edi, dword ptr [esp + 0x18] */
	m->ebx = M32((DWORD)(m->esp + 0x14u));	/* 4287cb: mov ebx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4287cf: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4287d0: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4287d6u; native_call(m, 0x41ef60u);	/* 4287d1: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4287d6: add esp, 8 */
	{ DWORD v_ = 0x3f200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4287d9: push 0x3f200000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4287de: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4287e5u; native_call(m, m->esi);	/* 4287e3: call esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4287e5: push edi */
	m->edi = M32((DWORD)(m->esp + 0x20u));	/* 4287e6: mov edi, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4287ea: push edi */
	m->esp -= 4; M32(m->esp) = 0x4287f0u; native_call(m, 0x41ef60u);	/* 4287eb: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4287f0: add esp, 8 */
	{ DWORD v_ = 0x3f600000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4287f3: push 0x3f600000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4287f8: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4287ffu; native_call(m, m->esi);	/* 4287fd: call esi */
	m->ebp = M32((DWORD)(m->esp + 0x20u));	/* 4287ff: mov ebp, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428803: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428804: push edi */
	m->esp -= 4; M32(m->esp) = 0x42880au; native_call(m, 0x41ef60u);	/* 428805: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42880a: add esp, 8 */
	{ DWORD v_ = 0x3f600000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42880d: push 0x3f600000 */
	{ DWORD v_ = 0x3f600000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428812: push 0x3f600000 */
	goto L_428876;	/* 428817: jmp 0x428876 */
L_428819:
	m->esi = M32((DWORD)(0x4a920cu));	/* 428819: mov esi, dword ptr [0x4a920c] */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42881f: push 0x3f400000 */
	m->esp -= 4; M32(m->esp) = 0x428826u; native_call(m, m->esi);	/* 428824: call esi */
	m->edi = M32((DWORD)(m->esp + 0x18u));	/* 428826: mov edi, dword ptr [esp + 0x18] */
	m->ebx = M32((DWORD)(m->esp + 0x14u));	/* 42882a: mov ebx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42882e: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42882f: push ebx */
	m->esp -= 4; M32(m->esp) = 0x428835u; native_call(m, 0x41ef60u);	/* 428830: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428835: add esp, 8 */
	{ DWORD v_ = 0x3f200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428838: push 0x3f200000 */
	{ DWORD v_ = 0x3f600000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42883d: push 0x3f600000 */
	m->esp -= 4; M32(m->esp) = 0x428844u; native_call(m, m->esi);	/* 428842: call esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428844: push edi */
	m->edi = M32((DWORD)(m->esp + 0x20u));	/* 428845: mov edi, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428849: push edi */
	m->esp -= 4; M32(m->esp) = 0x42884fu; native_call(m, 0x41ef60u);	/* 42884a: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42884f: add esp, 8 */
	{ DWORD v_ = 0x3f600000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428852: push 0x3f600000 */
	{ DWORD v_ = 0x3f600000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428857: push 0x3f600000 */
	m->esp -= 4; M32(m->esp) = 0x42885eu; native_call(m, m->esi);	/* 42885c: call esi */
	m->ebp = M32((DWORD)(m->esp + 0x20u));	/* 42885e: mov ebp, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428862: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428863: push edi */
	m->esp -= 4; M32(m->esp) = 0x428869u; native_call(m, 0x41ef60u);	/* 428864: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428869: add esp, 8 */
	{ DWORD v_ = 0x3f600000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42886c: push 0x3f600000 */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428871: push 0x3f400000 */
L_428876:
	m->esp -= 4; M32(m->esp) = 0x428878u; native_call(m, m->esi);	/* 428876: call esi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428878: push ebp */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 428879: push ebx */
	m->esp -= 4; M32(m->esp) = 0x42887fu; native_call(m, 0x41ef60u);	/* 42887a: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42887f: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x428888u; native_call(m, M32(0x4a9220u));	/* 428882: call dword ptr [0x4a9220] */
	m->edi = M32(m->esp); m->esp += 4;	/* 428888: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 428889: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 42888a: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 42888b: pop ebx */
	m->esp += 4 + 0; return;	/* 42888c: ret  */
}

/* hud_427ce0 (0x427ce0), lifted by tools/lift.py */
static void lift_427ce0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427ce0: sub esp, 8 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 427ce3: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 427ce4: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x1cu));	/* 427ce5: mov ebp, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 427ce9: push esi */
	m->esi = M32((DWORD)(0x4a920cu));	/* 427cea: mov esi, dword ptr [0x4a920c] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 427cf0: push edi */
	m->eax = (DWORD)(m->ebp*4 + 0x4e16d8u);	/* 427cf1: lea eax, [ebp*4 + 0x4e16d8] */
	m->ecx = (DWORD)(m->ebp*4 + 0x4e1548u);	/* 427cf8: lea ecx, [ebp*4 + 0x4e1548] */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 427cff: mov dword ptr [esp + 0x10], eax */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 427d03: mov dword ptr [esp + 0x14], ecx */
	m->eax = M32((DWORD)(m->eax + 0x0u));	/* 427d07: mov eax, dword ptr [eax] */
	m->ecx = M32((DWORD)(m->ecx + 0x0u));	/* 427d09: mov ecx, dword ptr [ecx] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427d0b: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427d0c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x427d0fu; native_call(m, m->esi);	/* 427d0d: call esi */
	m->edi = M32((DWORD)(m->esp + 0x20u));	/* 427d0f: mov edi, dword ptr [esp + 0x20] */
	m->ebx = M32((DWORD)(m->esp + 0x1cu));	/* 427d13: mov ebx, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 427d17: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 427d18: push ebx */
	m->esp -= 4; M32(m->esp) = 0x427d1eu; native_call(m, 0x41ef60u);	/* 427d19: call 0x41ef60 */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 427d1e: mov edx, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->ebp*4 + 0x5b199cu));	/* 427d22: mov ecx, dword ptr [ebp*4 + 0x5b199c] */
	m->ebp = (DWORD)(m->ebp*4 + 0x5b199cu);	/* 427d29: lea ebp, [ebp*4 + 0x5b199c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427d30: add esp, 8 */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 427d33: mov eax, dword ptr [edx] */
	M32((DWORD)(m->esp + 0x20u)) = m->ebp;	/* 427d35: mov dword ptr [esp + 0x20], ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427d39: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427d3a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x427d3du; native_call(m, m->esi);	/* 427d3b: call esi */
	m->ebp = (DWORD)(m->ebx + 0xdu);	/* 427d3d: lea ebp, [ebx + 0xd] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 427d40: push edi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 427d41: push ebp */
	m->esp -= 4; M32(m->esp) = 0x427d47u; native_call(m, 0x41ef60u);	/* 427d42: call 0x41ef60 */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 427d47: mov edx, dword ptr [esp + 0x2c] */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 427d4b: mov ecx, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427d4f: add esp, 8 */
	m->eax = (DWORD)(m->edx*4 + 0x5b1b64u);	/* 427d52: lea eax, [edx*4 + 0x5b1b64] */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 427d59: mov edx, dword ptr [ecx] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 427d5b: mov dword ptr [esp + 0x1c], eax */
	m->eax = M32((DWORD)(m->eax + 0x0u));	/* 427d5f: mov eax, dword ptr [eax] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427d61: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427d62: push edx */
	m->esp -= 4; M32(m->esp) = 0x427d65u; native_call(m, m->esi);	/* 427d63: call esi */
	m->eax = (DWORD)(m->edi + 0xdu);	/* 427d65: lea eax, [edi + 0xd] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427d68: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 427d69: push ebp */
	M32((DWORD)(m->esp + 0x2cu)) = m->eax;	/* 427d6a: mov dword ptr [esp + 0x2c], eax */
	m->esp -= 4; M32(m->esp) = 0x427d73u; native_call(m, 0x41ef60u);	/* 427d6e: call 0x41ef60 */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 427d73: mov eax, dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 427d77: mov edx, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427d7b: add esp, 8 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 427d7e: mov ecx, dword ptr [eax] */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 427d80: mov eax, dword ptr [edx] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427d82: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427d83: push eax */
	m->esp -= 4; M32(m->esp) = 0x427d86u; native_call(m, m->esi);	/* 427d84: call esi */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 427d86: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427d8a: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 427d8b: push ebx */
	m->esp -= 4; M32(m->esp) = 0x427d91u; native_call(m, 0x41ef60u);	/* 427d8c: call 0x41ef60 */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 427d91: mov eax, dword ptr [esp + 0x30] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427d95: add esp, 8 */
	m->edx = M32((DWORD)(m->eax*4 + 0x4df638u));	/* 427d98: mov edx, dword ptr [eax*4 + 0x4df638] */
	m->ecx = (DWORD)(m->eax*4 + 0x4df458u);	/* 427d9f: lea ecx, [eax*4 + 0x4df458] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427da6: push edx */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 427da7: mov dword ptr [esp + 0x20], ecx */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 427dab: mov eax, dword ptr [ecx] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427dad: push eax */
	m->esp -= 4; M32(m->esp) = 0x427db0u; native_call(m, m->esi);	/* 427dae: call esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 427db0: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 427db1: push ebx */
	m->esp -= 4; M32(m->esp) = 0x427db7u; native_call(m, 0x41ef60u);	/* 427db2: call 0x41ef60 */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 427db7: mov eax, dword ptr [esp + 0x30] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427dbb: add esp, 8 */
	m->edx = M32((DWORD)(m->eax*4 + 0x4df638u));	/* 427dbe: mov edx, dword ptr [eax*4 + 0x4df638] */
	m->ecx = (DWORD)(m->eax*4 + 0x83a600u);	/* 427dc5: lea ecx, [eax*4 + 0x83a600] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427dcc: push edx */
	M32((DWORD)(m->esp + 0x24u)) = m->ecx;	/* 427dcd: mov dword ptr [esp + 0x24], ecx */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 427dd1: mov eax, dword ptr [ecx] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427dd3: push eax */
	m->esp -= 4; M32(m->esp) = 0x427dd6u; native_call(m, m->esi);	/* 427dd4: call esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 427dd6: push edi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 427dd7: push ebp */
	m->esp -= 4; M32(m->esp) = 0x427dddu; native_call(m, 0x41ef60u);	/* 427dd8: call 0x41ef60 */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 427ddd: mov ecx, dword ptr [esp + 0x30] */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 427de1: mov eax, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427de5: add esp, 8 */
	m->edx = M32((DWORD)(m->ecx*4 + 0x83a7e0u));	/* 427de8: mov edx, dword ptr [ecx*4 + 0x83a7e0] */
	m->edi = (DWORD)(m->ecx*4 + 0x83a7e0u);	/* 427def: lea edi, [ecx*4 + 0x83a7e0] */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 427df6: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427df8: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427df9: push ecx */
	m->esp -= 4; M32(m->esp) = 0x427dfcu; native_call(m, m->esi);	/* 427dfa: call esi */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 427dfc: mov edx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427e00: push edx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 427e01: push ebp */
	m->esp -= 4; M32(m->esp) = 0x427e07u; native_call(m, 0x41ef60u);	/* 427e02: call 0x41ef60 */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 427e07: mov ecx, dword ptr [esp + 0x24] */
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 427e0b: mov eax, dword ptr [edi] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427e0d: add esp, 8 */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 427e10: mov edx, dword ptr [ecx] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427e12: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427e13: push edx */
	m->esp -= 4; M32(m->esp) = 0x427e16u; native_call(m, m->esi);	/* 427e14: call esi */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 427e16: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427e1a: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 427e1b: push ebx */
	m->esp -= 4; M32(m->esp) = 0x427e21u; native_call(m, 0x41ef60u);	/* 427e1c: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427e21: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 427e24: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 427e25: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 427e26: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 427e27: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427e28: add esp, 8 */
	m->esp += 4 + 0; return;	/* 427e2b: ret  */
}

/* hud_427ee0 (0x427ee0), lifted by tools/lift.py */
static void lift_427ee0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427ee0: sub esp, 8 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 427ee3: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 427ee4: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x1cu));	/* 427ee5: mov ebp, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 427ee9: push esi */
	m->esi = M32((DWORD)(0x4a920cu));	/* 427eea: mov esi, dword ptr [0x4a920c] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 427ef0: push edi */
	m->eax = (DWORD)(m->ebp*4 + 0x4e16d8u);	/* 427ef1: lea eax, [ebp*4 + 0x4e16d8] */
	m->ecx = (DWORD)(m->ebp*4 + 0x4e1548u);	/* 427ef8: lea ecx, [ebp*4 + 0x4e1548] */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 427eff: mov dword ptr [esp + 0x10], eax */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 427f03: mov dword ptr [esp + 0x14], ecx */
	m->eax = M32((DWORD)(m->eax + 0x0u));	/* 427f07: mov eax, dword ptr [eax] */
	m->ecx = M32((DWORD)(m->ecx + 0x0u));	/* 427f09: mov ecx, dword ptr [ecx] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427f0b: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427f0c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x427f0fu; native_call(m, m->esi);	/* 427f0d: call esi */
	m->edi = M32((DWORD)(m->esp + 0x20u));	/* 427f0f: mov edi, dword ptr [esp + 0x20] */
	m->ebx = M32((DWORD)(m->esp + 0x1cu));	/* 427f13: mov ebx, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 427f17: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 427f18: push ebx */
	m->esp -= 4; M32(m->esp) = 0x427f1eu; native_call(m, 0x41ef60u);	/* 427f19: call 0x41ef60 */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 427f1e: mov edx, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->ebp*4 + 0x5b199cu));	/* 427f22: mov ecx, dword ptr [ebp*4 + 0x5b199c] */
	m->ebp = (DWORD)(m->ebp*4 + 0x5b199cu);	/* 427f29: lea ebp, [ebp*4 + 0x5b199c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427f30: add esp, 8 */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 427f33: mov eax, dword ptr [edx] */
	M32((DWORD)(m->esp + 0x20u)) = m->ebp;	/* 427f35: mov dword ptr [esp + 0x20], ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427f39: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427f3a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x427f3du; native_call(m, m->esi);	/* 427f3b: call esi */
	m->ebp = (DWORD)(m->ebx + 0x1fu);	/* 427f3d: lea ebp, [ebx + 0x1f] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 427f40: push edi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 427f41: push ebp */
	m->esp -= 4; M32(m->esp) = 0x427f47u; native_call(m, 0x41ef60u);	/* 427f42: call 0x41ef60 */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 427f47: mov edx, dword ptr [esp + 0x2c] */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 427f4b: mov ecx, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427f4f: add esp, 8 */
	m->eax = (DWORD)(m->edx*4 + 0x5b1b64u);	/* 427f52: lea eax, [edx*4 + 0x5b1b64] */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 427f59: mov edx, dword ptr [ecx] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 427f5b: mov dword ptr [esp + 0x1c], eax */
	m->eax = M32((DWORD)(m->eax + 0x0u));	/* 427f5f: mov eax, dword ptr [eax] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427f61: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427f62: push edx */
	m->esp -= 4; M32(m->esp) = 0x427f65u; native_call(m, m->esi);	/* 427f63: call esi */
	m->eax = (DWORD)(m->edi + 0x1fu);	/* 427f65: lea eax, [edi + 0x1f] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427f68: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 427f69: push ebp */
	M32((DWORD)(m->esp + 0x2cu)) = m->eax;	/* 427f6a: mov dword ptr [esp + 0x2c], eax */
	m->esp -= 4; M32(m->esp) = 0x427f73u; native_call(m, 0x41ef60u);	/* 427f6e: call 0x41ef60 */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 427f73: mov eax, dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 427f77: mov edx, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427f7b: add esp, 8 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 427f7e: mov ecx, dword ptr [eax] */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 427f80: mov eax, dword ptr [edx] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427f82: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427f83: push eax */
	m->esp -= 4; M32(m->esp) = 0x427f86u; native_call(m, m->esi);	/* 427f84: call esi */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 427f86: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427f8a: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 427f8b: push ebx */
	m->esp -= 4; M32(m->esp) = 0x427f91u; native_call(m, 0x41ef60u);	/* 427f8c: call 0x41ef60 */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 427f91: mov eax, dword ptr [esp + 0x30] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427f95: add esp, 8 */
	m->edx = M32((DWORD)(m->eax*4 + 0x4df638u));	/* 427f98: mov edx, dword ptr [eax*4 + 0x4df638] */
	m->ecx = (DWORD)(m->eax*4 + 0x4df458u);	/* 427f9f: lea ecx, [eax*4 + 0x4df458] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427fa6: push edx */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 427fa7: mov dword ptr [esp + 0x20], ecx */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 427fab: mov eax, dword ptr [ecx] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427fad: push eax */
	m->esp -= 4; M32(m->esp) = 0x427fb0u; native_call(m, m->esi);	/* 427fae: call esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 427fb0: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 427fb1: push ebx */
	m->esp -= 4; M32(m->esp) = 0x427fb7u; native_call(m, 0x41ef60u);	/* 427fb2: call 0x41ef60 */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 427fb7: mov eax, dword ptr [esp + 0x30] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427fbb: add esp, 8 */
	m->edx = M32((DWORD)(m->eax*4 + 0x4df638u));	/* 427fbe: mov edx, dword ptr [eax*4 + 0x4df638] */
	m->ecx = (DWORD)(m->eax*4 + 0x83a600u);	/* 427fc5: lea ecx, [eax*4 + 0x83a600] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427fcc: push edx */
	M32((DWORD)(m->esp + 0x24u)) = m->ecx;	/* 427fcd: mov dword ptr [esp + 0x24], ecx */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 427fd1: mov eax, dword ptr [ecx] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427fd3: push eax */
	m->esp -= 4; M32(m->esp) = 0x427fd6u; native_call(m, m->esi);	/* 427fd4: call esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 427fd6: push edi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 427fd7: push ebp */
	m->esp -= 4; M32(m->esp) = 0x427fddu; native_call(m, 0x41ef60u);	/* 427fd8: call 0x41ef60 */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 427fdd: mov ecx, dword ptr [esp + 0x30] */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 427fe1: mov eax, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427fe5: add esp, 8 */
	m->edx = M32((DWORD)(m->ecx*4 + 0x83a7e0u));	/* 427fe8: mov edx, dword ptr [ecx*4 + 0x83a7e0] */
	m->edi = (DWORD)(m->ecx*4 + 0x83a7e0u);	/* 427fef: lea edi, [ecx*4 + 0x83a7e0] */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 427ff6: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427ff8: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427ff9: push ecx */
	m->esp -= 4; M32(m->esp) = 0x427ffcu; native_call(m, m->esi);	/* 427ffa: call esi */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 427ffc: mov edx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 428000: push edx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428001: push ebp */
	m->esp -= 4; M32(m->esp) = 0x428007u; native_call(m, 0x41ef60u);	/* 428002: call 0x41ef60 */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 428007: mov ecx, dword ptr [esp + 0x24] */
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 42800b: mov eax, dword ptr [edi] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42800d: add esp, 8 */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 428010: mov edx, dword ptr [ecx] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 428012: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 428013: push edx */
	m->esp -= 4; M32(m->esp) = 0x428016u; native_call(m, m->esi);	/* 428014: call esi */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 428016: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42801a: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42801b: push ebx */
	m->esp -= 4; M32(m->esp) = 0x428021u; native_call(m, 0x41ef60u);	/* 42801c: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428021: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 428024: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 428025: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 428026: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 428027: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428028: add esp, 8 */
	m->esp += 4 + 0; return;	/* 42802b: ret  */
}

/* sys_errorMessageNoName (0x46c840), lifted by tools/lift.py */
static void lift_46c840(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x514u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c840: sub esp, 0x514 */
	m->eax = (DWORD)(m->esp + 0x0u);	/* 46c846: lea eax, [esp] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c84a: push esi */
	m->esi = 0x1u;	/* 46c84b: mov esi, 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c850: push eax */
	M32((DWORD)(0xa1efe0u)) = m->esi;	/* 46c851: mov dword ptr [0xa1efe0], esi */
	m->esp -= 4; M32(m->esp) = 0x46c85du; native_call(m, M32(0x4a90f4u));	/* 46c857: call dword ptr [0x4a90f4] */
	m->ecx = M32((DWORD)(m->esp + 0x12u));	/* 46c85d: mov ecx, dword ptr [esp + 0x12] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 46c861: mov edx, dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->esp + 0xeu));	/* 46c865: mov eax, dword ptr [esp + 0xe] */
	{ DWORD a_ = m->ecx, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46c869: and ecx, 0xffff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c86f: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 46c870: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->edx, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 46c874: and edx, 0xffff */
	{ DWORD a_ = m->eax, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46c87a: and eax, 0xffff */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c87f: push edx */
	m->edx = M32((DWORD)(m->esp + 0x12u));	/* 46c880: mov edx, dword ptr [esp + 0x12] */
	{ DWORD a_ = m->ecx, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46c884: and ecx, 0xffff */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c88a: push eax */
	m->eax = M32((DWORD)(m->esp + 0x12u));	/* 46c88b: mov eax, dword ptr [esp + 0x12] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c88f: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 46c890: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->edx, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 46c894: and edx, 0xffff */
	{ DWORD a_ = m->eax, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46c89a: and eax, 0xffff */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c89f: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46c8a0: and ecx, 0xffff */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c8a6: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c8a7: push ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 46c8a8: lea edx, [esp + 0x34] */
	{ DWORD v_ = 0x4c58a0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c8ac: push 0x4c58a0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c8b1: push edx */
	m->esp -= 4; M32(m->esp) = 0x46c8b7u; native_call(m, 0x49e9ddu);	/* 46c8b2: call 0x49e9dd */
	m->ecx = M32((DWORD)(m->esp + 0x540u));	/* 46c8b7: mov ecx, dword ptr [esp + 0x540] */
	m->eax = (DWORD)(m->esp + 0x544u);	/* 46c8be: lea eax, [esp + 0x544] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c8c5: push eax */
	m->edx = (DWORD)(m->esp + 0x140u);	/* 46c8c6: lea edx, [esp + 0x140] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c8cd: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c8ce: push edx */
	m->esp -= 4; M32(m->esp) = 0x46c8d4u; native_call(m, 0x49ed2eu);	/* 46c8cf: call 0x49ed2e */
	m->eax = M32((DWORD)(0xa1efdcu));	/* 46c8d4: mov eax, dword ptr [0xa1efdc] */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c8d9: add esp, 0x30 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46c8dc: cmp eax, esi */
	if (!m->zf) goto L_46c92e;	/* 46c8de: jne 0x46c92e */
	{ DWORD v_ = 0x4c5838u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c8e0: push 0x4c5838 */
	{ DWORD v_ = 0x4c582cu; m->esp -= 4; M32(m->esp) = v_; }	/* 46c8e5: push 0x4c582c */
	m->esp -= 4; M32(m->esp) = 0x46c8efu; native_call(m, 0x49e9cau);	/* 46c8ea: call 0x49e9ca */
	m->esi = m->eax;	/* 46c8ef: mov esi, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c8f1: add esp, 8 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46c8f4: test esi, esi */
	if (m->zf) goto L_46c92e;	/* 46c8f6: je 0x46c92e */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c8f8: push 2 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c8fa: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c8fc: push esi */
	m->esp -= 4; M32(m->esp) = 0x46c902u; native_call(m, 0x49e91eu);	/* 46c8fd: call 0x49e91e */
	m->eax = (DWORD)(m->esp + 0x124u);	/* 46c902: lea eax, [esp + 0x124] */
	m->ecx = (DWORD)(m->esp + 0x24u);	/* 46c909: lea ecx, [esp + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c90d: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c90e: push ecx */
	{ DWORD v_ = 0x4c5824u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c90f: push 0x4c5824 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c914: push esi */
	m->esp -= 4; M32(m->esp) = 0x46c91au; native_call(m, 0x49f135u);	/* 46c915: call 0x49f135 */
	{ DWORD v_ = 0x4c57d0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c91a: push 0x4c57d0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c91f: push esi */
	m->esp -= 4; M32(m->esp) = 0x46c925u; native_call(m, 0x49f135u);	/* 46c920: call 0x49f135 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c925: push esi */
	m->esp -= 4; M32(m->esp) = 0x46c92bu; native_call(m, 0x49e7e0u);	/* 46c926: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c92b: add esp, 0x28 */
L_46c92e:
	m->edx = (DWORD)(m->esp + 0x118u);	/* 46c92e: lea edx, [esp + 0x118] */
	m->eax = (DWORD)(m->esp + 0x18u);	/* 46c935: lea eax, [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c939: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c93a: push eax */
	m->esp -= 4; M32(m->esp) = 0x46c941u; native_call(m, M32((DWORD)(0x4c57ccu)));	/* 46c93b: call dword ptr [0x4c57cc] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c941: add esp, 8 */
	m->esi = M32(m->esp); m->esp += 4;	/* 46c944: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x514u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c945: add esp, 0x514 */
	m->esp += 4 + 0; return;	/* 46c94b: ret  */
}

/* sys_errorMessage (0x46c5f0), lifted by tools/lift.py */
static void lift_46c5f0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x514u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c5f0: sub esp, 0x514 */
	m->eax = (DWORD)(m->esp + 0x0u);	/* 46c5f6: lea eax, [esp] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c5fa: push esi */
	m->esi = 0x1u;	/* 46c5fb: mov esi, 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c600: push eax */
	M32((DWORD)(0xa1efe0u)) = m->esi;	/* 46c601: mov dword ptr [0xa1efe0], esi */
	m->esp -= 4; M32(m->esp) = 0x46c60du; native_call(m, M32(0x4a90f4u));	/* 46c607: call dword ptr [0x4a90f4] */
	m->ecx = M32((DWORD)(m->esp + 0x12u));	/* 46c60d: mov ecx, dword ptr [esp + 0x12] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 46c611: mov edx, dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->esp + 0xeu));	/* 46c615: mov eax, dword ptr [esp + 0xe] */
	{ DWORD a_ = m->ecx, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46c619: and ecx, 0xffff */
	{ DWORD a_ = m->edx, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 46c61f: and edx, 0xffff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c625: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 46c626: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c62a: push edx */
	m->edx = M32((DWORD)(m->esp + 0x12u));	/* 46c62b: mov edx, dword ptr [esp + 0x12] */
	{ DWORD a_ = m->eax, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46c62f: and eax, 0xffff */
	{ DWORD a_ = m->ecx, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46c634: and ecx, 0xffff */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c63a: push eax */
	m->eax = M32((DWORD)(m->esp + 0x12u));	/* 46c63b: mov eax, dword ptr [esp + 0x12] */
	{ DWORD a_ = m->edx, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 46c63f: and edx, 0xffff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c645: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 46c646: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c64a: push edx */
	m->edx = M32((DWORD)(m->esp + 0x530u));	/* 46c64b: mov edx, dword ptr [esp + 0x530] */
	{ DWORD a_ = m->eax, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46c652: and eax, 0xffff */
	{ DWORD a_ = m->ecx, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46c657: and ecx, 0xffff */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c65d: push eax */
	m->eax = M32((DWORD)(m->edx + 0x4u));	/* 46c65e: mov eax, dword ptr [edx + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c661: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c662: push eax */
	m->ecx = (DWORD)(m->esp + 0x38u);	/* 46c663: lea ecx, [esp + 0x38] */
	{ DWORD v_ = 0x4c583cu; m->esp -= 4; M32(m->esp) = v_; }	/* 46c667: push 0x4c583c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c66c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46c672u; native_call(m, 0x49e9ddu);	/* 46c66d: call 0x49e9dd */
	m->eax = M32((DWORD)(m->esp + 0x548u));	/* 46c672: mov eax, dword ptr [esp + 0x548] */
	m->edx = (DWORD)(m->esp + 0x54cu);	/* 46c679: lea edx, [esp + 0x54c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c680: push edx */
	m->ecx = (DWORD)(m->esp + 0x144u);	/* 46c681: lea ecx, [esp + 0x144] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c688: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c689: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46c68fu; native_call(m, 0x49ed2eu);	/* 46c68a: call 0x49ed2e */
	m->eax = M32((DWORD)(0xa1efdcu));	/* 46c68f: mov eax, dword ptr [0xa1efdc] */
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c694: add esp, 0x34 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46c697: cmp eax, esi */
	if (!m->zf) goto L_46c6e9;	/* 46c699: jne 0x46c6e9 */
	{ DWORD v_ = 0x4c5838u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c69b: push 0x4c5838 */
	{ DWORD v_ = 0x4c582cu; m->esp -= 4; M32(m->esp) = v_; }	/* 46c6a0: push 0x4c582c */
	m->esp -= 4; M32(m->esp) = 0x46c6aau; native_call(m, 0x49e9cau);	/* 46c6a5: call 0x49e9ca */
	m->esi = m->eax;	/* 46c6aa: mov esi, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c6ac: add esp, 8 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46c6af: test esi, esi */
	if (m->zf) goto L_46c6e9;	/* 46c6b1: je 0x46c6e9 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c6b3: push 2 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c6b5: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c6b7: push esi */
	m->esp -= 4; M32(m->esp) = 0x46c6bdu; native_call(m, 0x49e91eu);	/* 46c6b8: call 0x49e91e */
	m->edx = (DWORD)(m->esp + 0x124u);	/* 46c6bd: lea edx, [esp + 0x124] */
	m->eax = (DWORD)(m->esp + 0x24u);	/* 46c6c4: lea eax, [esp + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c6c8: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c6c9: push eax */
	{ DWORD v_ = 0x4c5824u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c6ca: push 0x4c5824 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c6cf: push esi */
	m->esp -= 4; M32(m->esp) = 0x46c6d5u; native_call(m, 0x49f135u);	/* 46c6d0: call 0x49f135 */
	{ DWORD v_ = 0x4c57d0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c6d5: push 0x4c57d0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c6da: push esi */
	m->esp -= 4; M32(m->esp) = 0x46c6e0u; native_call(m, 0x49f135u);	/* 46c6db: call 0x49f135 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c6e0: push esi */
	m->esp -= 4; M32(m->esp) = 0x46c6e6u; native_call(m, 0x49e7e0u);	/* 46c6e1: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c6e6: add esp, 0x28 */
L_46c6e9:
	m->ecx = (DWORD)(m->esp + 0x118u);	/* 46c6e9: lea ecx, [esp + 0x118] */
	m->edx = (DWORD)(m->esp + 0x18u);	/* 46c6f0: lea edx, [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c6f4: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c6f5: push edx */
	m->esp -= 4; M32(m->esp) = 0x46c6fcu; native_call(m, M32((DWORD)(0x4c57ccu)));	/* 46c6f6: call dword ptr [0x4c57cc] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c6fc: add esp, 8 */
	m->esi = M32(m->esp); m->esp += 4;	/* 46c6ff: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x514u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c700: add esp, 0x514 */
	m->esp += 4 + 0; return;	/* 46c706: ret  */
}

/* sys_errorTerminate (0x46c950), lifted by tools/lift.py */
static void lift_46c950(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x514u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c950: sub esp, 0x514 */
	m->eax = (DWORD)(m->esp + 0x0u);	/* 46c956: lea eax, [esp] */
	M32((DWORD)(0xa1efe4u)) = 0x1u;	/* 46c95a: mov dword ptr [0xa1efe4], 1 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c964: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c965: push eax */
	m->esp -= 4; M32(m->esp) = 0x46c96cu; native_call(m, M32(0x4a90f4u));	/* 46c966: call dword ptr [0x4a90f4] */
	m->ecx = M32((DWORD)(m->esp + 0x12u));	/* 46c96c: mov ecx, dword ptr [esp + 0x12] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 46c970: mov edx, dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->esp + 0xeu));	/* 46c974: mov eax, dword ptr [esp + 0xe] */
	{ DWORD a_ = m->ecx, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46c978: and ecx, 0xffff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c97e: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 46c97f: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->edx, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 46c983: and edx, 0xffff */
	{ DWORD a_ = m->eax, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46c989: and eax, 0xffff */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c98e: push edx */
	m->edx = M32((DWORD)(m->esp + 0x12u));	/* 46c98f: mov edx, dword ptr [esp + 0x12] */
	{ DWORD a_ = m->ecx, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46c993: and ecx, 0xffff */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c999: push eax */
	m->eax = M32((DWORD)(m->esp + 0x12u));	/* 46c99a: mov eax, dword ptr [esp + 0x12] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c99e: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 46c99f: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->edx, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 46c9a3: and edx, 0xffff */
	{ DWORD a_ = m->eax, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46c9a9: and eax, 0xffff */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c9ae: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46c9af: and ecx, 0xffff */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c9b5: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c9b6: push ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 46c9b7: lea edx, [esp + 0x34] */
	{ DWORD v_ = 0x4c58c8u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c9bb: push 0x4c58c8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c9c0: push edx */
	m->esp -= 4; M32(m->esp) = 0x46c9c6u; native_call(m, 0x49e9ddu);	/* 46c9c1: call 0x49e9dd */
	m->ecx = M32((DWORD)(m->esp + 0x540u));	/* 46c9c6: mov ecx, dword ptr [esp + 0x540] */
	m->eax = (DWORD)(m->esp + 0x544u);	/* 46c9cd: lea eax, [esp + 0x544] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c9d4: push eax */
	m->edx = (DWORD)(m->esp + 0x140u);	/* 46c9d5: lea edx, [esp + 0x140] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c9dc: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c9dd: push edx */
	m->esp -= 4; M32(m->esp) = 0x46c9e3u; native_call(m, 0x49ed2eu);	/* 46c9de: call 0x49ed2e */
	m->eax = M32((DWORD)(0xa1efdcu));	/* 46c9e3: mov eax, dword ptr [0xa1efdc] */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c9e8: add esp, 0x30 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46c9eb: cmp eax, 1 */
	if (!m->zf) goto L_46ca3e;	/* 46c9ee: jne 0x46ca3e */
	{ DWORD v_ = 0x4c5838u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c9f0: push 0x4c5838 */
	{ DWORD v_ = 0x4c582cu; m->esp -= 4; M32(m->esp) = v_; }	/* 46c9f5: push 0x4c582c */
	m->esp -= 4; M32(m->esp) = 0x46c9ffu; native_call(m, 0x49e9cau);	/* 46c9fa: call 0x49e9ca */
	m->esi = m->eax;	/* 46c9ff: mov esi, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46ca01: add esp, 8 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46ca04: test esi, esi */
	if (m->zf) goto L_46ca3e;	/* 46ca06: je 0x46ca3e */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ca08: push 2 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ca0a: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46ca0c: push esi */
	m->esp -= 4; M32(m->esp) = 0x46ca12u; native_call(m, 0x49e91eu);	/* 46ca0d: call 0x49e91e */
	m->eax = (DWORD)(m->esp + 0x124u);	/* 46ca12: lea eax, [esp + 0x124] */
	m->ecx = (DWORD)(m->esp + 0x24u);	/* 46ca19: lea ecx, [esp + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46ca1d: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46ca1e: push ecx */
	{ DWORD v_ = 0x4c5824u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ca1f: push 0x4c5824 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46ca24: push esi */
	m->esp -= 4; M32(m->esp) = 0x46ca2au; native_call(m, 0x49f135u);	/* 46ca25: call 0x49f135 */
	{ DWORD v_ = 0x4c57d0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ca2a: push 0x4c57d0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46ca2f: push esi */
	m->esp -= 4; M32(m->esp) = 0x46ca35u; native_call(m, 0x49f135u);	/* 46ca30: call 0x49f135 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46ca35: push esi */
	m->esp -= 4; M32(m->esp) = 0x46ca3bu; native_call(m, 0x49e7e0u);	/* 46ca36: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46ca3b: add esp, 0x28 */
L_46ca3e:
	m->edx = (DWORD)(m->esp + 0x118u);	/* 46ca3e: lea edx, [esp + 0x118] */
	m->eax = (DWORD)(m->esp + 0x18u);	/* 46ca45: lea eax, [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46ca49: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46ca4a: push eax */
	m->esp -= 4; M32(m->esp) = 0x46ca51u; native_call(m, M32((DWORD)(0x4c57ccu)));	/* 46ca4b: call dword ptr [0x4c57cc] */
	m->eax = M32((DWORD)(0xa1efe8u));	/* 46ca51: mov eax, dword ptr [0xa1efe8] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46ca56: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46ca59: test eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 46ca5b: pop esi */
	if (m->zf) goto L_46ca60;	/* 46ca5c: je 0x46ca60 */
	m->esp -= 4; M32(m->esp) = 0x46ca60u; native_call(m, m->eax);	/* 46ca5e: call eax */
L_46ca60:
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ca60: push 1 */
	m->esp -= 4; M32(m->esp) = 0x46ca67u; native_call(m, 0x49edacu);	/* 46ca62: call 0x49edac */
	abort();	/* the last call does not return */
}

/* sys_fatalError (0x46c710), lifted by tools/lift.py */
static void lift_46c710(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x514u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c710: sub esp, 0x514 */
	m->eax = (DWORD)(m->esp + 0x0u);	/* 46c716: lea eax, [esp] */
	M32((DWORD)(0xa1efe4u)) = 0x1u;	/* 46c71a: mov dword ptr [0xa1efe4], 1 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c724: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c725: push eax */
	m->esp -= 4; M32(m->esp) = 0x46c72cu; native_call(m, M32(0x4a90f4u));	/* 46c726: call dword ptr [0x4a90f4] */
	m->ecx = M32((DWORD)(m->esp + 0x12u));	/* 46c72c: mov ecx, dword ptr [esp + 0x12] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 46c730: mov edx, dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->esp + 0xeu));	/* 46c734: mov eax, dword ptr [esp + 0xe] */
	{ DWORD a_ = m->ecx, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46c738: and ecx, 0xffff */
	{ DWORD a_ = m->edx, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 46c73e: and edx, 0xffff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c744: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 46c745: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c749: push edx */
	m->edx = M32((DWORD)(m->esp + 0x12u));	/* 46c74a: mov edx, dword ptr [esp + 0x12] */
	{ DWORD a_ = m->eax, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46c74e: and eax, 0xffff */
	{ DWORD a_ = m->ecx, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46c753: and ecx, 0xffff */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c759: push eax */
	m->eax = M32((DWORD)(m->esp + 0x12u));	/* 46c75a: mov eax, dword ptr [esp + 0x12] */
	{ DWORD a_ = m->edx, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 46c75e: and edx, 0xffff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c764: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 46c765: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c769: push edx */
	m->edx = M32((DWORD)(m->esp + 0x530u));	/* 46c76a: mov edx, dword ptr [esp + 0x530] */
	{ DWORD a_ = m->eax, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46c771: and eax, 0xffff */
	{ DWORD a_ = m->ecx, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46c776: and ecx, 0xffff */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c77c: push eax */
	m->eax = M32((DWORD)(m->edx + 0x4u));	/* 46c77d: mov eax, dword ptr [edx + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c780: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c781: push eax */
	m->ecx = (DWORD)(m->esp + 0x38u);	/* 46c782: lea ecx, [esp + 0x38] */
	{ DWORD v_ = 0x4c586cu; m->esp -= 4; M32(m->esp) = v_; }	/* 46c786: push 0x4c586c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c78b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46c791u; native_call(m, 0x49e9ddu);	/* 46c78c: call 0x49e9dd */
	m->eax = M32((DWORD)(m->esp + 0x548u));	/* 46c791: mov eax, dword ptr [esp + 0x548] */
	m->edx = (DWORD)(m->esp + 0x54cu);	/* 46c798: lea edx, [esp + 0x54c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c79f: push edx */
	m->ecx = (DWORD)(m->esp + 0x144u);	/* 46c7a0: lea ecx, [esp + 0x144] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c7a7: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c7a8: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46c7aeu; native_call(m, 0x49ed2eu);	/* 46c7a9: call 0x49ed2e */
	m->eax = M32((DWORD)(0xa1efdcu));	/* 46c7ae: mov eax, dword ptr [0xa1efdc] */
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c7b3: add esp, 0x34 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46c7b6: cmp eax, 1 */
	if (!m->zf) goto L_46c809;	/* 46c7b9: jne 0x46c809 */
	{ DWORD v_ = 0x4c5838u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c7bb: push 0x4c5838 */
	{ DWORD v_ = 0x4c582cu; m->esp -= 4; M32(m->esp) = v_; }	/* 46c7c0: push 0x4c582c */
	m->esp -= 4; M32(m->esp) = 0x46c7cau; native_call(m, 0x49e9cau);	/* 46c7c5: call 0x49e9ca */
	m->esi = m->eax;	/* 46c7ca: mov esi, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c7cc: add esp, 8 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46c7cf: test esi, esi */
	if (m->zf) goto L_46c809;	/* 46c7d1: je 0x46c809 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c7d3: push 2 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c7d5: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c7d7: push esi */
	m->esp -= 4; M32(m->esp) = 0x46c7ddu; native_call(m, 0x49e91eu);	/* 46c7d8: call 0x49e91e */
	m->edx = (DWORD)(m->esp + 0x124u);	/* 46c7dd: lea edx, [esp + 0x124] */
	m->eax = (DWORD)(m->esp + 0x24u);	/* 46c7e4: lea eax, [esp + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c7e8: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c7e9: push eax */
	{ DWORD v_ = 0x4c5824u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c7ea: push 0x4c5824 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c7ef: push esi */
	m->esp -= 4; M32(m->esp) = 0x46c7f5u; native_call(m, 0x49f135u);	/* 46c7f0: call 0x49f135 */
	{ DWORD v_ = 0x4c57d0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c7f5: push 0x4c57d0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c7fa: push esi */
	m->esp -= 4; M32(m->esp) = 0x46c800u; native_call(m, 0x49f135u);	/* 46c7fb: call 0x49f135 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c800: push esi */
	m->esp -= 4; M32(m->esp) = 0x46c806u; native_call(m, 0x49e7e0u);	/* 46c801: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c806: add esp, 0x28 */
L_46c809:
	m->ecx = (DWORD)(m->esp + 0x118u);	/* 46c809: lea ecx, [esp + 0x118] */
	m->edx = (DWORD)(m->esp + 0x18u);	/* 46c810: lea edx, [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c814: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c815: push edx */
	m->esp -= 4; M32(m->esp) = 0x46c81cu; native_call(m, M32((DWORD)(0x4c57ccu)));	/* 46c816: call dword ptr [0x4c57cc] */
	m->eax = M32((DWORD)(0xa1efe8u));	/* 46c81c: mov eax, dword ptr [0xa1efe8] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c821: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46c824: test eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 46c826: pop esi */
	if (m->zf) goto L_46c82b;	/* 46c827: je 0x46c82b */
	m->esp -= 4; M32(m->esp) = 0x46c82bu; native_call(m, m->eax);	/* 46c829: call eax */
L_46c82b:
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c82b: push 1 */
	m->esp -= 4; M32(m->esp) = 0x46c832u; native_call(m, 0x49edacu);	/* 46c82d: call 0x49edac */
	abort();	/* the last call does not return */
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
