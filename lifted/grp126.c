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

static void lift_437140(X86 *m);
static void lift_405690(X86 *m);
static void lift_435d30(X86 *m);
static void lift_433e60(X86 *m);
static void lift_4419d0(X86 *m);
static void lift_441e00(X86 *m);
static void lift_436e10(X86 *m);
static void lift_441260(X86 *m);
static void lift_42ada0(X86 *m);
static void lift_454c10(X86 *m);
static void lift_454d20(X86 *m);
static void lift_406a60(X86 *m);

/* lobby_406a60 (0x406a60), lifted by tools/lift.py */
static void lift_406a60(X86 *m)
{
	m->eax = M32((DWORD)(0x4dbb3cu));	/* 406a60: mov eax, dword ptr [0x4dbb3c] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406a65: cmp eax, 1 */
	if (m->zf) goto L_406b18;	/* 406a68: je 0x406b18 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 406a6e: test eax, eax */
	if (m->zf) goto L_406b18;	/* 406a70: je 0x406b18 */
	m->ecx = M32((DWORD)(0x90d1c4u));	/* 406a76: mov ecx, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 406a7c: test ecx, ecx */
	if (!m->zf) goto L_406b18;	/* 406a7e: jne 0x406b18 */
	m->ecx = M32((DWORD)(0x4dbbd0u));	/* 406a84: mov ecx, dword ptr [0x4dbbd0] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 406a8a: test ecx, ecx */
	if (!m->zf) goto L_406b18;	/* 406a8c: jne 0x406b18 */
	m->ecx = M32((DWORD)(0x4ded8cu));	/* 406a92: mov ecx, dword ptr [0x4ded8c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 406a98: test ecx, ecx */
	if (m->zf) goto L_406ab1;	/* 406a9a: je 0x406ab1 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 406a9c: push 0 */
	M32((DWORD)(0x4dbb3cu)) = 0x0u;	/* 406a9e: mov dword ptr [0x4dbb3c], 0 */
	m->esp -= 4; M32(m->esp) = 0x406aadu; native_call(m, 0x41e760u);	/* 406aa8: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 406aad: add esp, 4 */
	m->esp += 4 + 0; return;	/* 406ab0: ret  */
L_406ab1:
	m->ecx = M32((DWORD)(0x4ded88u));	/* 406ab1: mov ecx, dword ptr [0x4ded88] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 406ab7: test ecx, ecx */
	if (m->zf) goto L_406b18;	/* 406ab9: je 0x406b18 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406abb: cmp eax, 2 */
	if (!m->zf) goto L_406b18;	/* 406abe: jne 0x406b18 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 406ac0: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 406ac5: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 406acb: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 406acc: push ecx */
	m->esp -= 4; M32(m->esp) = 0x406ad2u; native_call(m, 0x404460u);	/* 406acd: call 0x404460 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 406ad2: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406ad5: cmp eax, 5 */
	if (!m->cf && !m->zf) goto L_406b18;	/* 406ad8: ja 0x406b18 */
	switch (m->eax) { case 0: goto L_406ae1; case 1: goto L_406b18; case 2: goto L_406ae6; case 3: goto L_406aff; case 4: goto L_406b19; case 5: goto L_406b2e; default: abort(); }	/* 406ada: jmp dword ptr [eax*4 + 0x406b40] */
L_406ae1:
	native_call(m, 0x404cd0u); return;	/* 406ae1: jmp 0x404cd0 */
L_406ae6:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 406ae6: push 0 */
	m->esp -= 4; M32(m->esp) = 0x406aedu; native_call(m, 0x41e760u);	/* 406ae8: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 406aed: add esp, 4 */
	M32((DWORD)(0x4dc24cu)) = 0x2u;	/* 406af0: mov dword ptr [0x4dc24c], 2 */
	native_call(m, 0x40ee20u); return;	/* 406afa: jmp 0x40ee20 */
L_406aff:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 406aff: push 0 */
	m->esp -= 4; M32(m->esp) = 0x406b06u; native_call(m, 0x41e760u);	/* 406b01: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 406b06: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x406b0eu; native_call(m, 0x4050a0u);	/* 406b09: call 0x4050a0 */
	M32((DWORD)(0x4dbb3cu)) = 0x0u;	/* 406b0e: mov dword ptr [0x4dbb3c], 0 */
L_406b18:
	m->esp += 4 + 0; return;	/* 406b18: ret  */
L_406b19:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 406b19: push 0 */
	m->esp -= 4; M32(m->esp) = 0x406b20u; native_call(m, 0x41e760u);	/* 406b1b: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 406b20: add esp, 4 */
	M32((DWORD)(0x4dbb3cu)) = 0x0u;	/* 406b23: mov dword ptr [0x4dbb3c], 0 */
	m->esp += 4 + 0; return;	/* 406b2d: ret  */
L_406b2e:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 406b2e: push 0 */
	m->esp -= 4; M32(m->esp) = 0x406b35u; native_call(m, 0x41e760u);	/* 406b30: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 406b35: add esp, 4 */
	native_call(m, 0x4050f0u); return;	/* 406b38: jmp 0x4050f0 */
}

/* menu_437140 (0x437140), lifted by tools/lift.py */
static void lift_437140(X86 *m)
{
	m->eax = M32((DWORD)(0x76d48cu));	/* 437140: mov eax, dword ptr [0x76d48c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 437145: push eax */
	m->esp -= 4; M32(m->esp) = 0x43714bu; native_call(m, 0x401600u);	/* 437146: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43714b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43714e: test eax, eax */
	if (m->zf) goto L_437161;	/* 437150: je 0x437161 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 437152: push 0 */
	m->esp -= 4; M32(m->esp) = 0x437159u; native_call(m, 0x41e760u);	/* 437154: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 437159: add esp, 4 */
	native_call(m, 0x435a40u); return;	/* 43715c: jmp 0x435a40 */
L_437161:
	m->ecx = M32((DWORD)(0x4e1514u));	/* 437161: mov ecx, dword ptr [0x4e1514] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 437167: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43716du; native_call(m, 0x401600u);	/* 437168: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43716d: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 437170: test eax, eax */
	if (m->zf) goto L_437183;	/* 437172: je 0x437183 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 437174: push 0 */
	m->esp -= 4; M32(m->esp) = 0x43717bu; native_call(m, 0x41e760u);	/* 437176: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43717b: add esp, 4 */
	native_call(m, 0x4334c0u); return;	/* 43717e: jmp 0x4334c0 */
L_437183:
	m->edx = M32((DWORD)(0x4e14f8u));	/* 437183: mov edx, dword ptr [0x4e14f8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 437189: push edx */
	m->esp -= 4; M32(m->esp) = 0x43718fu; native_call(m, 0x401600u);	/* 43718a: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43718f: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 437192: test eax, eax */
	if (m->zf) goto L_4371a5;	/* 437194: je 0x4371a5 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 437196: push 0 */
	m->esp -= 4; M32(m->esp) = 0x43719du; native_call(m, 0x41e760u);	/* 437198: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43719d: add esp, 4 */
	native_call(m, 0x433590u); return;	/* 4371a0: jmp 0x433590 */
L_4371a5:
	m->eax = M32((DWORD)(0x4e0cdcu));	/* 4371a5: mov eax, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4371aa: push eax */
	m->esp -= 4; M32(m->esp) = 0x4371b0u; native_call(m, 0x401600u);	/* 4371ab: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4371b0: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4371b3: test eax, eax */
	if (m->zf) goto L_4371c6;	/* 4371b5: je 0x4371c6 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4371b7: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4371beu; native_call(m, 0x41e760u);	/* 4371b9: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4371be: add esp, 4 */
	native_call(m, 0x433790u); return;	/* 4371c1: jmp 0x433790 */
L_4371c6:
	m->ecx = M32((DWORD)(0x4e151cu));	/* 4371c6: mov ecx, dword ptr [0x4e151c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4371cc: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4371d2u; native_call(m, 0x401600u);	/* 4371cd: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4371d2: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4371d5: test eax, eax */
	if (m->zf) goto L_4371e8;	/* 4371d7: je 0x4371e8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4371d9: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4371e0u; native_call(m, 0x41e760u);	/* 4371db: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4371e0: add esp, 4 */
	native_call(m, 0x433800u); return;	/* 4371e3: jmp 0x433800 */
L_4371e8:
	m->edx = M32((DWORD)(0x4e0cd4u));	/* 4371e8: mov edx, dword ptr [0x4e0cd4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4371ee: push edx */
	m->esp -= 4; M32(m->esp) = 0x4371f4u; native_call(m, 0x401600u);	/* 4371ef: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4371f4: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4371f7: test eax, eax */
	if (m->zf) goto L_437214;	/* 4371f9: je 0x437214 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4371fb: push 0 */
	m->esp -= 4; M32(m->esp) = 0x437202u; native_call(m, 0x41e760u);	/* 4371fd: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 437202: add esp, 4 */
	M32((DWORD)(0x4dc24cu)) = 0x3u;	/* 437205: mov dword ptr [0x4dc24c], 3 */
	native_call(m, 0x40ee20u); return;	/* 43720f: jmp 0x40ee20 */
L_437214:
	m->eax = M32((DWORD)(0x4e153cu));	/* 437214: mov eax, dword ptr [0x4e153c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 437219: push eax */
	m->esp -= 4; M32(m->esp) = 0x43721fu; native_call(m, 0x401600u);	/* 43721a: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43721f: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 437222: test eax, eax */
	if (m->zf) goto L_437235;	/* 437224: je 0x437235 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 437226: push 0 */
	m->esp -= 4; M32(m->esp) = 0x43722du; native_call(m, 0x41e760u);	/* 437228: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43722d: add esp, 4 */
	native_call(m, 0x435a40u); return;	/* 437230: jmp 0x435a40 */
L_437235:
	m->esp += 4 + 0; return;	/* 437235: ret  */
}

/* arena_405690 (0x405690), lifted by tools/lift.py */
static void lift_405690(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 405690: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 405694: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 405695: push ebp */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 405696: xor ebp, ebp */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 405698: lea ecx, [eax + eax*8] */
	M32((DWORD)(0x4dbbecu)) = m->ebp;	/* 40569b: mov dword ptr [0x4dbbec], ebp */
	M32((DWORD)(0x4dbbf0u)) = m->ebp;	/* 4056a1: mov dword ptr [0x4dbbf0], ebp */
	m->ebx = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 4056a7: lea ebx, [eax + ecx*4] */
	{ DWORD a_ = m->ebx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ebx = r_; } }	/* 4056aa: shl ebx, 1 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x9087eeu))) & 0xff) << 0);	/* 4056ac: mov dl, byte ptr [ebx + 0x9087ee] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x9087edu))) & 0xff) << 0);	/* 4056b2: mov cl, byte ptr [ebx + 0x9087ed] */
	M8((DWORD)(0x4ded45u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 4056b8: mov byte ptr [0x4ded45], dl */
	M8((DWORD)(0x4db54du)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 4056be: mov byte ptr [0x4db54d], dl */
	m->edx = M32((DWORD)(0x4dedd0u));	/* 4056c4: mov edx, dword ptr [0x4dedd0] */
	M8((DWORD)(0x4ded44u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 4056ca: mov byte ptr [0x4ded44], cl */
	M8((DWORD)(0x4db54cu)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 4056d0: mov byte ptr [0x4db54c], cl */
	m->ecx = M32((DWORD)(m->ebx + 0x9087c0u));	/* 4056d6: mov ecx, dword ptr [ebx + 0x9087c0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4056dc: push edx */
	{ DWORD v_ = 0x4dedb0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4056dd: push 0x4dedb0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4056e2: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4056e3: push eax */
	m->esp -= 4; M32(m->esp) = 0x4056e9u; native_call(m, 0x453180u);	/* 4056e4: call 0x453180 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4056e9: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = 0x1f4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4056ec: cmp eax, 0x1f4 */
	if (m->zf) goto L_405714;	/* 4056f1: je 0x405714 */
	{ DWORD a_ = m->eax, b_ = 0x1f5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4056f3: cmp eax, 0x1f5 */
	if (!m->zf) goto L_405707;	/* 4056f8: jne 0x405707 */
	{ DWORD v_ = 0x36u; m->esp -= 4; M32(m->esp) = v_; }	/* 4056fa: push 0x36 */
	m->esp -= 4; M32(m->esp) = 0x405701u; native_call(m, 0x41ee40u);	/* 4056fc: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 405701: add esp, 4 */
	m->ebp = M32(m->esp); m->esp += 4;	/* 405704: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 405705: pop ebx */
	m->esp += 4 + 0; return;	/* 405706: ret  */
L_405707:
	{ DWORD v_ = 0x35u; m->esp -= 4; M32(m->esp) = v_; }	/* 405707: push 0x35 */
	m->esp -= 4; M32(m->esp) = 0x40570eu; native_call(m, 0x41ee40u);	/* 405709: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40570e: add esp, 4 */
	m->ebp = M32(m->esp); m->esp += 4;	/* 405711: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 405712: pop ebx */
	m->esp += 4 + 0; return;	/* 405713: ret  */
L_405714:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 405714: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 405715: push edi */
	m->esp -= 4; M32(m->esp) = 0x40571bu; native_call(m, 0x457310u);	/* 405716: call 0x457310 */
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(m->ebx + 0x9087e5u)));	/* 40571b: movsx edx, byte ptr [ebx + 0x9087e5] */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(m->ebx + 0x9087e4u)));	/* 405722: movsx eax, byte ptr [ebx + 0x9087e4] */
	m->esi = (DWORD)(m->ebx + 0x9087c4u);	/* 405729: lea esi, [ebx + 0x9087c4] */
	m->ecx = 0x8u;	/* 40572f: mov ecx, 8 */
	m->edi = 0x67fb44u;	/* 405734: mov edi, 0x67fb44 */
	M32((DWORD)(0x9dad94u)) = m->edx;	/* 405739: mov dword ptr [0x9dad94], edx */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40573f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(m->ebx + 0x9087ecu)));	/* 405741: movsx ecx, byte ptr [ebx + 0x9087ec] */
	M32((DWORD)(0x9da3e0u)) = m->eax;	/* 405748: mov dword ptr [0x9da3e0], eax */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 40574d: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x9087edu))) & 0xff) << 0);	/* 40574f: mov dl, byte ptr [ebx + 0x9087ed] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 405755: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x9087eeu))) & 0xff) << 0);	/* 405757: mov al, byte ptr [ebx + 0x9087ee] */
	m->edi = M32(m->esp); m->esp += 4;	/* 40575d: pop edi */
	M32((DWORD)(0x4dbb3cu)) = m->ebp;	/* 40575e: mov dword ptr [0x4dbb3c], ebp */
	M32((DWORD)(0x4db8b4u)) = m->ebp;	/* 405764: mov dword ptr [0x4db8b4], ebp */
	m->esi = M32(m->esp); m->esp += 4;	/* 40576a: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 40576b: pop ebp */
	M32((DWORD)(0x67ef14u)) = 0x1u;	/* 40576c: mov dword ptr [0x67ef14], 1 */
	M32((DWORD)(0x67ef04u)) = 0x2u;	/* 405776: mov dword ptr [0x67ef04], 2 */
	M32((DWORD)(0x76d368u)) = m->ecx;	/* 405780: mov dword ptr [0x76d368], ecx */
	M32((DWORD)(0x4df8e8u)) = m->edx;	/* 405786: mov dword ptr [0x4df8e8], edx */
	M32((DWORD)(0x76d408u)) = m->eax;	/* 40578c: mov dword ptr [0x76d408], eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 405791: pop ebx */
	m->esp += 4 + 0; return;	/* 405792: ret  */
}

/* room_435d30 (0x435d30), lifted by tools/lift.py */
static void lift_435d30(X86 *m)
{
	m->eax = M32((DWORD)(0x9dce48u));	/* 435d30: mov eax, dword ptr [0x9dce48] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 435d35: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 435d36: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 435d37: push esi */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 435d38: cmp eax, 1 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 435d3b: push edi */
	if (m->zf) goto L_435e49;	/* 435d3c: je 0x435e49 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 435d42: test eax, eax */
	if (m->zf) goto L_435e49;	/* 435d44: je 0x435e49 */
	m->eax = M32((DWORD)(0x90d1c4u));	/* 435d4a: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 435d4f: test eax, eax */
	if (!m->zf) goto L_435e49;	/* 435d51: jne 0x435e49 */
	m->eax = M32((DWORD)(0x4ded88u));	/* 435d57: mov eax, dword ptr [0x4ded88] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 435d5c: test eax, eax */
	if (m->zf) goto L_435e28;	/* 435d5e: je 0x435e28 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 435d64: xor ebp, ebp */
	m->ebx = 0x9daf88u;	/* 435d66: mov ebx, 0x9daf88 */
L_435d6b:
	m->eax = M32((DWORD)(0x4ded6cu));	/* 435d6b: mov eax, dword ptr [0x4ded6c] */
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435d70: sub esp, 0x2c */
	m->ecx = 0xbu;	/* 435d73: mov ecx, 0xb */
	m->esi = m->ebx;	/* 435d78: mov esi, ebx */
	m->edi = m->esp;	/* 435d7a: mov edi, esp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 435d7c: push eax */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 435d7d: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 435d7f: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 435d85: push ecx */
	m->esp -= 4; M32(m->esp) = 0x435d8bu; native_call(m, 0x41eea0u);	/* 435d86: call 0x41eea0 */
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435d8b: add esp, 0x34 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 435d8e: cmp eax, 1 */
	if (m->zf) goto L_435da4;	/* 435d91: je 0x435da4 */
	{ DWORD a_ = m->ebx, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 435d93: add ebx, 0x2c */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 435d96: inc ebp */
	{ DWORD a_ = m->ebx, b_ = 0x9db090u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 435d97: cmp ebx, 0x9db090 */
	if (m->sf != m->of) goto L_435d6b;	/* 435d9d: jl 0x435d6b */
	goto L_435e28;	/* 435d9f: jmp 0x435e28 */
L_435da4:
	{ DWORD a_ = m->ebp, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 435da4: cmp ebp, 5 */
	if (!m->cf && !m->zf) goto L_435e28;	/* 435da7: ja 0x435e28 */
	switch (m->ebp) { case 0: goto L_435db0; case 1: goto L_435dc1; case 2: goto L_435dd2; case 3: goto L_435de3; case 4: goto L_435e08; case 5: goto L_435e19; default: abort(); }	/* 435da9: jmp dword ptr [ebp*4 + 0x435e50] */
L_435db0:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 435db0: push 0 */
	m->esp -= 4; M32(m->esp) = 0x435db7u; native_call(m, 0x41e760u);	/* 435db2: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435db7: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x435dbfu; native_call(m, 0x4334c0u);	/* 435dba: call 0x4334c0 */
	goto L_435e28;	/* 435dbf: jmp 0x435e28 */
L_435dc1:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 435dc1: push 0 */
	m->esp -= 4; M32(m->esp) = 0x435dc8u; native_call(m, 0x41e760u);	/* 435dc3: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435dc8: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x435dd0u; native_call(m, 0x433590u);	/* 435dcb: call 0x433590 */
	goto L_435e28;	/* 435dd0: jmp 0x435e28 */
L_435dd2:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 435dd2: push 0 */
	m->esp -= 4; M32(m->esp) = 0x435dd9u; native_call(m, 0x41e760u);	/* 435dd4: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435dd9: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x435de1u; native_call(m, 0x433790u);	/* 435ddc: call 0x433790 */
	goto L_435e28;	/* 435de1: jmp 0x435e28 */
L_435de3:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 435de3: push 0 */
	m->esp -= 4; M32(m->esp) = 0x435deau; native_call(m, 0x41e760u);	/* 435de5: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435dea: add esp, 4 */
	M32((DWORD)(0x4dc24cu)) = 0x3u;	/* 435ded: mov dword ptr [0x4dc24c], 3 */
	m->esp -= 4; M32(m->esp) = 0x435dfcu; native_call(m, 0x40ee20u);	/* 435df7: call 0x40ee20 */
	M32((DWORD)(0x4deb48u)) = 0x0u;	/* 435dfc: mov dword ptr [0x4deb48], 0 */
	goto L_435e28;	/* 435e06: jmp 0x435e28 */
L_435e08:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 435e08: push 0 */
	m->esp -= 4; M32(m->esp) = 0x435e0fu; native_call(m, 0x41e760u);	/* 435e0a: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435e0f: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x435e17u; native_call(m, 0x433800u);	/* 435e12: call 0x433800 */
	goto L_435e28;	/* 435e17: jmp 0x435e28 */
L_435e19:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 435e19: push 0 */
	m->esp -= 4; M32(m->esp) = 0x435e20u; native_call(m, 0x41e760u);	/* 435e1b: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435e20: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x435e28u; native_call(m, 0x435a40u);	/* 435e23: call 0x435a40 */
L_435e28:
	m->eax = M32((DWORD)(0x4ded8cu));	/* 435e28: mov eax, dword ptr [0x4ded8c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 435e2d: test eax, eax */
	if (m->zf) goto L_435e49;	/* 435e2f: je 0x435e49 */
	m->eax = M32((DWORD)(0x9dae10u));	/* 435e31: mov eax, dword ptr [0x9dae10] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 435e36: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_435e49;	/* 435e38: jle 0x435e49 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 435e3a: push 0 */
	m->esp -= 4; M32(m->esp) = 0x435e41u; native_call(m, 0x41e760u);	/* 435e3c: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435e41: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x435e49u; native_call(m, 0x435a40u);	/* 435e44: call 0x435a40 */
L_435e49:
	m->edi = M32(m->esp); m->esp += 4;	/* 435e49: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 435e4a: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 435e4b: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 435e4c: pop ebx */
	m->esp += 4 + 0; return;	/* 435e4d: ret  */
}

/* room_433e60 (0x433e60), lifted by tools/lift.py */
static void lift_433e60(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 433e60: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 433e61: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 433e62: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 433e63: push edi */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 433e64: xor ebp, ebp */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 433e66: xor esi, esi */
	m->esp -= 4; M32(m->esp) = 0x433e6du; native_call(m, 0x401460u);	/* 433e68: call 0x401460 */
	m->ecx = 0x100u;	/* 433e6d: mov ecx, 0x100 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 433e72: xor eax, eax */
	m->edi = 0x9dc92cu;	/* 433e74: mov edi, 0x9dc92c */
	m->ebx = 0x1u;	/* 433e79: mov ebx, 1 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 433e7e: rep stosd dword ptr es:[edi], eax */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 433e80: mov eax, dword ptr [esp + 0x14] */
	M32((DWORD)(0x68039cu)) = m->ebx;	/* 433e84: mov dword ptr [0x68039c], ebx */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 433e8a: cmp eax, 3 */
	M32((DWORD)(0x9dd348u)) = m->ebp;	/* 433e8d: mov dword ptr [0x9dd348], ebp */
	M32((DWORD)(0x9dd32cu)) = m->ebp;	/* 433e93: mov dword ptr [0x9dd32c], ebp */
	M32((DWORD)(0x9dd3f8u)) = m->ebp;	/* 433e99: mov dword ptr [0x9dd3f8], ebp */
	M32((DWORD)(0x9dd564u)) = m->ebp;	/* 433e9f: mov dword ptr [0x9dd564], ebp */
	M32((DWORD)(0x9dd6ccu)) = m->ebp;	/* 433ea5: mov dword ptr [0x9dd6cc], ebp */
	M32((DWORD)(0x4e1868u)) = m->ebp;	/* 433eab: mov dword ptr [0x4e1868], ebp */
	if (!m->cf && !m->zf) goto L_433fb9;	/* 433eb1: ja 0x433fb9 */
	switch (m->eax) { case 0: goto L_433ebe; case 1: goto L_433ef9; case 2: goto L_433f37; case 3: goto L_433f78; default: abort(); }	/* 433eb7: jmp dword ptr [eax*4 + 0x434004] */
L_433ebe:
	{ DWORD v_ = 0x1eu; m->esp -= 4; M32(m->esp) = v_; }	/* 433ebe: push 0x1e */
	m->esp -= 4; M32(m->esp) = 0x433ec5u; native_call(m, 0x431560u);	/* 433ec0: call 0x431560 */
	m->edi = 0x9dd1d8u;	/* 433ec5: mov edi, 0x9dd1d8 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433eca: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 433ecd: xor eax, eax */
	M32((DWORD)(0x9dd348u)) = m->ebx;	/* 433ecf: mov dword ptr [0x9dd348], ebx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 433ed5: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 433ed7: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 433ed9: sub edi, ecx */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 433edb: push 0x10 */
	m->eax = m->ecx;	/* 433edd: mov eax, ecx */
	m->esi = m->edi;	/* 433edf: mov esi, edi */
	m->edi = 0x9dc92cu;	/* 433ee1: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 433ee6: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 433ee9: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 433eeb: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433eed: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 433ef0: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 433ef2: xor esi, esi */
	goto L_433fb1;	/* 433ef4: jmp 0x433fb1 */
L_433ef9:
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 433ef9: push 0xc */
	m->esp -= 4; M32(m->esp) = 0x433f00u; native_call(m, 0x431560u);	/* 433efb: call 0x431560 */
	m->edi = 0x9dd1f6u;	/* 433f00: mov edi, 0x9dd1f6 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433f05: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 433f08: xor eax, eax */
	M32((DWORD)(0x9dd3f8u)) = m->ebx;	/* 433f0a: mov dword ptr [0x9dd3f8], ebx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 433f10: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 433f12: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 433f14: sub edi, ecx */
	M32((DWORD)(0x4e1868u)) = m->ebx;	/* 433f16: mov dword ptr [0x4e1868], ebx */
	m->edx = m->ecx;	/* 433f1c: mov edx, ecx */
	m->esi = m->edi;	/* 433f1e: mov esi, edi */
	m->edi = 0x9dc92cu;	/* 433f20: mov edi, 0x9dc92c */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 433f25: push 0xc */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 433f27: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 433f2a: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 433f2c: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433f2e: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 433f31: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esi = m->ebx;	/* 433f33: mov esi, ebx */
	goto L_433fb1;	/* 433f35: jmp 0x433fb1 */
L_433f37:
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 433f37: push 0xc */
	m->esp -= 4; M32(m->esp) = 0x433f3eu; native_call(m, 0x431560u);	/* 433f39: call 0x431560 */
	m->edi = 0x9dd202u;	/* 433f3e: mov edi, 0x9dd202 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433f43: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 433f46: xor eax, eax */
	M32((DWORD)(0x9dd564u)) = m->ebx;	/* 433f48: mov dword ptr [0x9dd564], ebx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 433f4e: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 433f50: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 433f52: sub edi, ecx */
	M32((DWORD)(0x4e1868u)) = m->ebx;	/* 433f54: mov dword ptr [0x4e1868], ebx */
	m->eax = m->ecx;	/* 433f5a: mov eax, ecx */
	m->esi = m->edi;	/* 433f5c: mov esi, edi */
	m->edi = 0x9dc92cu;	/* 433f5e: mov edi, 0x9dc92c */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 433f63: push 0xc */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 433f65: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 433f68: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 433f6a: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433f6c: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 433f6f: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esi = 0x2u;	/* 433f71: mov esi, 2 */
	goto L_433fb1;	/* 433f76: jmp 0x433fb1 */
L_433f78:
	{ DWORD v_ = 0x28u; m->esp -= 4; M32(m->esp) = v_; }	/* 433f78: push 0x28 */
	m->esp -= 4; M32(m->esp) = 0x433f7fu; native_call(m, 0x431560u);	/* 433f7a: call 0x431560 */
	m->edi = 0x9dd20eu;	/* 433f7f: mov edi, 0x9dd20e */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433f84: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 433f87: xor eax, eax */
	M32((DWORD)(0x9dd6ccu)) = m->ebx;	/* 433f89: mov dword ptr [0x9dd6cc], ebx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 433f8f: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 433f91: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 433f93: sub edi, ecx */
	{ DWORD v_ = 0x28u; m->esp -= 4; M32(m->esp) = v_; }	/* 433f95: push 0x28 */
	m->edx = m->ecx;	/* 433f97: mov edx, ecx */
	m->esi = m->edi;	/* 433f99: mov esi, edi */
	m->edi = 0x9dc92cu;	/* 433f9b: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 433fa0: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 433fa3: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 433fa5: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433fa7: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 433faa: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esi = 0x3u;	/* 433fac: mov esi, 3 */
L_433fb1:
	m->esp -= 4; M32(m->esp) = 0x433fb6u; native_call(m, 0x43f460u);	/* 433fb1: call 0x43f460 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 433fb6: add esp, 8 */
L_433fb9:
	m->eax = M32((DWORD)(0x9dd6e8u));	/* 433fb9: mov eax, dword ptr [0x9dd6e8] */
	m->edx = M32((DWORD)(0x9dd6ecu));	/* 433fbe: mov edx, dword ptr [0x9dd6ec] */
	m->ecx = (DWORD)(m->esi + m->esi*2 + 0x0u);	/* 433fc4: lea ecx, [esi + esi*2] */
	{ DWORD a_ = m->eax, b_ = 0x94u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 433fc7: add eax, 0x94 */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 433fcc: shl ecx, 4 */
	M32((DWORD)(0x9da3d8u)) = m->eax;	/* 433fcf: mov dword ptr [0x9da3d8], eax */
	m->edi = 0x9dc92cu;	/* 433fd4: mov edi, 0x9dc92c */
	m->eax = (DWORD)(m->ecx + m->edx*1 + 0x3cu);	/* 433fd9: lea eax, [ecx + edx + 0x3c] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433fdd: or ecx, 0xffffffff */
	M32((DWORD)(0x9da3dcu)) = m->eax;	/* 433fe0: mov dword ptr [0x9da3dc], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 433fe5: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 433fe7: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 433fe9: not ecx */
	m->edi = M32(m->esp); m->esp += 4;	/* 433feb: pop edi */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 433fec: dec ecx */
	m->esi = M32(m->esp); m->esp += 4;	/* 433fed: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 433fee: pop ebp */
	M32((DWORD)(0x9da434u)) = 0x40a00000u;	/* 433fef: mov dword ptr [0x9da434], 0x40a00000 */
	M32((DWORD)(0x9dbf10u)) = m->ecx;	/* 433ff9: mov dword ptr [0x9dbf10], ecx */
	m->ebx = M32(m->esp); m->esp += 4;	/* 433fff: pop ebx */
	m->esp += 4 + 0; return;	/* 434000: ret  */
}

/* mainmenu_startNetGame (0x4419d0), lifted by tools/lift.py */
static void lift_4419d0(X86 *m)
{
	m->eax = M32((DWORD)(0x9db994u));	/* 4419d0: mov eax, dword ptr [0x9db994] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4419d5: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4419d6: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4419d7: push esi */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4419d8: cmp eax, 1 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4419db: push edi */
	if (m->zf) goto L_441bde;	/* 4419dc: je 0x441bde */
	m->eax = M32((DWORD)(0x9eeab4u));	/* 4419e2: mov eax, dword ptr [0x9eeab4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4419e7: test eax, eax */
	if (m->zf) goto L_4419f5;	/* 4419e9: je 0x4419f5 */
	m->esp -= 4; M32(m->esp) = 0x4419f0u; native_call(m, 0x441810u);	/* 4419eb: call 0x441810 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4419f0: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4419f1: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4419f2: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4419f3: pop ebx */
	m->esp += 4 + 0; return;	/* 4419f4: ret  */
L_4419f5:
	m->eax = M32((DWORD)(0x4ded88u));	/* 4419f5: mov eax, dword ptr [0x4ded88] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4419fa: test eax, eax */
	if (m->zf) goto L_441b9a;	/* 4419fc: je 0x441b9a */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 441a02: mov dword ptr [0x4dda44], 0 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 441a0c: xor ebp, ebp */
	m->ebx = 0x4deb80u;	/* 441a0e: mov ebx, 0x4deb80 */
L_441a13:
	m->eax = M32((DWORD)(0x4ded6cu));	/* 441a13: mov eax, dword ptr [0x4ded6c] */
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441a18: sub esp, 0x2c */
	m->ecx = 0xbu;	/* 441a1b: mov ecx, 0xb */
	m->esi = m->ebx;	/* 441a20: mov esi, ebx */
	m->edi = m->esp;	/* 441a22: mov edi, esp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 441a24: push eax */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 441a25: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 441a27: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 441a2d: push ecx */
	m->esp -= 4; M32(m->esp) = 0x441a33u; native_call(m, 0x41eea0u);	/* 441a2e: call 0x41eea0 */
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441a33: add esp, 0x34 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441a36: cmp eax, 1 */
	if (m->zf) goto L_441a4c;	/* 441a39: je 0x441a4c */
	{ DWORD a_ = m->ebx, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 441a3b: add ebx, 0x2c */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 441a3e: inc ebp */
	{ DWORD a_ = m->ebx, b_ = 0x4dec88u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441a3f: cmp ebx, 0x4dec88 */
	if (m->sf != m->of) goto L_441a13;	/* 441a45: jl 0x441a13 */
	goto L_441b9a;	/* 441a47: jmp 0x441b9a */
L_441a4c:
	{ DWORD a_ = m->ebp, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441a4c: cmp ebp, 5 */
	if (!m->cf && !m->zf) goto L_441b9a;	/* 441a4f: ja 0x441b9a */
	switch (m->ebp) { case 0: goto L_441a5c; case 1: goto L_441a7a; case 2: goto L_441aa4; case 3: goto L_441b1f; case 4: goto L_441b46; case 5: goto L_441b6b; default: abort(); }	/* 441a55: jmp dword ptr [ebp*4 + 0x441be4] */
L_441a5c:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 441a5c: push 0 */
	m->esp -= 4; M32(m->esp) = 0x441a63u; native_call(m, 0x41e760u);	/* 441a5e: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441a63: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x441a6bu; native_call(m, 0x447750u);	/* 441a66: call 0x447750 */
	M32((DWORD)(0x4deb48u)) = 0x0u;	/* 441a6b: mov dword ptr [0x4deb48], 0 */
	goto L_441b9a;	/* 441a75: jmp 0x441b9a */
L_441a7a:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 441a7a: push 0 */
	m->esp -= 4; M32(m->esp) = 0x441a81u; native_call(m, 0x41e760u);	/* 441a7c: call 0x41e760 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 441a81: push 2 */
	m->esp -= 4; M32(m->esp) = 0x441a88u; native_call(m, 0x441250u);	/* 441a83: call 0x441250 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441a88: add esp, 8 */
	M32((DWORD)(0x67ef20u)) = 0x190u;	/* 441a8b: mov dword ptr [0x67ef20], 0x190 */
	M32((DWORD)(0x4deb48u)) = 0x0u;	/* 441a95: mov dword ptr [0x4deb48], 0 */
	goto L_441b9a;	/* 441a9f: jmp 0x441b9a */
L_441aa4:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 441aa4: push 0 */
	m->esp -= 4; M32(m->esp) = 0x441aabu; native_call(m, 0x41e760u);	/* 441aa6: call 0x41e760 */
	{ DWORD v_ = 0x65u; m->esp -= 4; M32(m->esp) = v_; }	/* 441aab: push 0x65 */
	m->esp -= 4; M32(m->esp) = 0x441ab2u; native_call(m, 0x451b80u);	/* 441aad: call 0x451b80 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441ab2: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 441ab5: test eax, eax */
	if (m->zf) goto L_441ae9;	/* 441ab7: je 0x441ae9 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441ab9: cmp eax, 2 */
	if (!m->zf) goto L_441ad4;	/* 441abc: jne 0x441ad4 */
	{ DWORD v_ = 0x6u; m->esp -= 4; M32(m->esp) = v_; }	/* 441abe: push 6 */
	m->esp -= 4; M32(m->esp) = 0x441ac5u; native_call(m, 0x41e760u);	/* 441ac0: call 0x41e760 */
	{ DWORD v_ = 0x2au; m->esp -= 4; M32(m->esp) = v_; }	/* 441ac5: push 0x2a */
	m->esp -= 4; M32(m->esp) = 0x441accu; native_call(m, 0x41ee40u);	/* 441ac7: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441acc: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 441acf: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 441ad0: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 441ad1: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 441ad2: pop ebx */
	m->esp += 4 + 0; return;	/* 441ad3: ret  */
L_441ad4:
	m->edx = M32((DWORD)(0x4ded18u));	/* 441ad4: mov edx, dword ptr [0x4ded18] */
	{ DWORD v_ = 0x65u; m->esp -= 4; M32(m->esp) = v_; }	/* 441ada: push 0x65 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 441adc: push edx */
	m->esp -= 4; M32(m->esp) = 0x441ae2u; native_call(m, 0x452170u);	/* 441add: call 0x452170 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441ae2: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 441ae5: test eax, eax */
	if (!m->zf) goto L_441aff;	/* 441ae7: jne 0x441aff */
L_441ae9:
	{ DWORD v_ = 0x6u; m->esp -= 4; M32(m->esp) = v_; }	/* 441ae9: push 6 */
	m->esp -= 4; M32(m->esp) = 0x441af0u; native_call(m, 0x41e760u);	/* 441aeb: call 0x41e760 */
	{ DWORD v_ = 0x29u; m->esp -= 4; M32(m->esp) = v_; }	/* 441af0: push 0x29 */
	m->esp -= 4; M32(m->esp) = 0x441af7u; native_call(m, 0x41ee40u);	/* 441af2: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441af7: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 441afa: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 441afb: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 441afc: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 441afd: pop ebx */
	m->esp += 4 + 0; return;	/* 441afe: ret  */
L_441aff:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 441aff: push 2 */
	m->esp -= 4; M32(m->esp) = 0x441b06u; native_call(m, 0x441250u);	/* 441b01: call 0x441250 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441b06: add esp, 4 */
	M32((DWORD)(0x67ef20u)) = 0x320u;	/* 441b09: mov dword ptr [0x67ef20], 0x320 */
	M32((DWORD)(0x4deb48u)) = 0x0u;	/* 441b13: mov dword ptr [0x4deb48], 0 */
	goto L_441b9a;	/* 441b1d: jmp 0x441b9a */
L_441b1f:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 441b1f: push 0 */
	m->esp -= 4; M32(m->esp) = 0x441b26u; native_call(m, 0x41e760u);	/* 441b21: call 0x41e760 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 441b26: push 2 */
	m->esp -= 4; M32(m->esp) = 0x441b2du; native_call(m, 0x441250u);	/* 441b28: call 0x441250 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441b2d: add esp, 8 */
	M32((DWORD)(0x67ef20u)) = 0x258u;	/* 441b30: mov dword ptr [0x67ef20], 0x258 */
	M32((DWORD)(0x4deb48u)) = 0x0u;	/* 441b3a: mov dword ptr [0x4deb48], 0 */
	goto L_441b9a;	/* 441b44: jmp 0x441b9a */
L_441b46:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 441b46: push 0 */
	m->esp -= 4; M32(m->esp) = 0x441b4du; native_call(m, 0x41e760u);	/* 441b48: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441b4d: add esp, 4 */
	M32((DWORD)(0x4dc24cu)) = 0x1u;	/* 441b50: mov dword ptr [0x4dc24c], 1 */
	m->esp -= 4; M32(m->esp) = 0x441b5fu; native_call(m, 0x40ee20u);	/* 441b5a: call 0x40ee20 */
	M32((DWORD)(0x4deb48u)) = 0x0u;	/* 441b5f: mov dword ptr [0x4deb48], 0 */
	goto L_441b9a;	/* 441b69: jmp 0x441b9a */
L_441b6b:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 441b6b: push 0 */
	m->esp -= 4; M32(m->esp) = 0x441b72u; native_call(m, 0x41e760u);	/* 441b6d: call 0x41e760 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 441b72: push 4 */
	m->esp -= 4; M32(m->esp) = 0x441b79u; native_call(m, 0x441250u);	/* 441b74: call 0x441250 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441b79: add esp, 8 */
	M32((DWORD)(0x4deb48u)) = 0x1u;	/* 441b7c: mov dword ptr [0x4deb48], 1 */
	M32((DWORD)(0x67ef20u)) = 0xd2u;	/* 441b86: mov dword ptr [0x67ef20], 0xd2 */
	m->esp -= 4; M32(m->esp) = 0x441b95u; native_call(m, 0x447010u);	/* 441b90: call 0x447010 */
	m->esp -= 4; M32(m->esp) = 0x441b9au; native_call(m, 0x48b420u);	/* 441b95: call 0x48b420 */
L_441b9a:
	m->eax = M32((DWORD)(0x4ded8cu));	/* 441b9a: mov eax, dword ptr [0x4ded8c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 441b9f: test eax, eax */
	if (m->zf) goto L_441bde;	/* 441ba1: je 0x441bde */
	m->eax = M32((DWORD)(0x9dae10u));	/* 441ba3: mov eax, dword ptr [0x9dae10] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 441ba8: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_441bde;	/* 441baa: jle 0x441bde */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 441bac: push 4 */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 441bae: mov dword ptr [0x4dda44], 0 */
	m->esp -= 4; M32(m->esp) = 0x441bbdu; native_call(m, 0x441250u);	/* 441bb8: call 0x441250 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441bbd: add esp, 4 */
	M32((DWORD)(0x4deb48u)) = 0x1u;	/* 441bc0: mov dword ptr [0x4deb48], 1 */
	M32((DWORD)(0x67ef20u)) = 0xd2u;	/* 441bca: mov dword ptr [0x67ef20], 0xd2 */
	m->esp -= 4; M32(m->esp) = 0x441bd9u; native_call(m, 0x447010u);	/* 441bd4: call 0x447010 */
	m->esp -= 4; M32(m->esp) = 0x441bdeu; native_call(m, 0x48b420u);	/* 441bd9: call 0x48b420 */
L_441bde:
	m->edi = M32(m->esp); m->esp += 4;	/* 441bde: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 441bdf: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 441be0: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 441be1: pop ebx */
	m->esp += 4 + 0; return;	/* 441be2: ret  */
}

/* mainmenu_processKeys (0x441e00), lifted by tools/lift.py */
static void lift_441e00(X86 *m)
{
	m->eax = M32((DWORD)(0x9db994u));	/* 441e00: mov eax, dword ptr [0x9db994] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 441e05: push esi */
	m->esi = 0x1u;	/* 441e06: mov esi, 1 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 441e0b: push edi */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441e0c: cmp eax, esi */
	if (m->zf) goto L_442047;	/* 441e0e: je 0x442047 */
	m->eax = M32((DWORD)(0x9eeab4u));	/* 441e14: mov eax, dword ptr [0x9eeab4] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 441e19: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441e1b: cmp eax, edi */
	if (m->zf) goto L_441e27;	/* 441e1d: je 0x441e27 */
	m->esp -= 4; M32(m->esp) = 0x441e24u; native_call(m, 0x441c00u);	/* 441e1f: call 0x441c00 */
	m->edi = M32(m->esp); m->esp += 4;	/* 441e24: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 441e25: pop esi */
	m->esp += 4 + 0; return;	/* 441e26: ret  */
L_441e27:
	m->eax = M32((DWORD)(0x4e1500u));	/* 441e27: mov eax, dword ptr [0x4e1500] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 441e2c: push eax */
	m->esp -= 4; M32(m->esp) = 0x441e32u; native_call(m, 0x401600u);	/* 441e2d: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441e32: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441e35: cmp eax, esi */
	if (!m->zf) goto L_441e50;	/* 441e37: jne 0x441e50 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 441e39: push edi */
	m->esp -= 4; M32(m->esp) = 0x441e3fu; native_call(m, 0x41e760u);	/* 441e3a: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441e3f: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x441e47u; native_call(m, 0x447750u);	/* 441e42: call 0x447750 */
	M32((DWORD)(0x4deb48u)) = m->edi;	/* 441e47: mov dword ptr [0x4deb48], edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 441e4d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 441e4e: pop esi */
	m->esp += 4 + 0; return;	/* 441e4f: ret  */
L_441e50:
	m->ecx = M32((DWORD)(0x4e1508u));	/* 441e50: mov ecx, dword ptr [0x4e1508] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 441e56: push ecx */
	m->esp -= 4; M32(m->esp) = 0x441e5cu; native_call(m, 0x401600u);	/* 441e57: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441e5c: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441e5f: cmp eax, esi */
	if (!m->zf) goto L_441e90;	/* 441e61: jne 0x441e90 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 441e63: push edi */
	m->esp -= 4; M32(m->esp) = 0x441e69u; native_call(m, 0x41e760u);	/* 441e64: call 0x41e760 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 441e69: push 2 */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 441e6b: mov dword ptr [0x4dda44], 0 */
	m->esp -= 4; M32(m->esp) = 0x441e7au; native_call(m, 0x441250u);	/* 441e75: call 0x441250 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441e7a: add esp, 8 */
	M32((DWORD)(0x4deb48u)) = m->edi;	/* 441e7d: mov dword ptr [0x4deb48], edi */
	M32((DWORD)(0x67ef20u)) = 0x190u;	/* 441e83: mov dword ptr [0x67ef20], 0x190 */
	m->edi = M32(m->esp); m->esp += 4;	/* 441e8d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 441e8e: pop esi */
	m->esp += 4 + 0; return;	/* 441e8f: ret  */
L_441e90:
	m->edx = M32((DWORD)(0x4e1504u));	/* 441e90: mov edx, dword ptr [0x4e1504] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 441e96: push edx */
	m->esp -= 4; M32(m->esp) = 0x441e9cu; native_call(m, 0x401600u);	/* 441e97: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441e9c: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441e9f: cmp eax, esi */
	if (!m->zf) goto L_441f1f;	/* 441ea1: jne 0x441f1f */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 441ea3: push edi */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 441ea4: mov dword ptr [0x4dda44], 0 */
	m->esp -= 4; M32(m->esp) = 0x441eb3u; native_call(m, 0x41e760u);	/* 441eae: call 0x41e760 */
	{ DWORD v_ = 0x65u; m->esp -= 4; M32(m->esp) = v_; }	/* 441eb3: push 0x65 */
	m->esp -= 4; M32(m->esp) = 0x441ebau; native_call(m, 0x451b80u);	/* 441eb5: call 0x451b80 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441eba: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441ebd: cmp eax, edi */
	if (m->zf) goto L_441eee;	/* 441ebf: je 0x441eee */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441ec1: cmp eax, 2 */
	if (!m->zf) goto L_441eda;	/* 441ec4: jne 0x441eda */
	{ DWORD v_ = 0x6u; m->esp -= 4; M32(m->esp) = v_; }	/* 441ec6: push 6 */
	m->esp -= 4; M32(m->esp) = 0x441ecdu; native_call(m, 0x41e760u);	/* 441ec8: call 0x41e760 */
	{ DWORD v_ = 0x2au; m->esp -= 4; M32(m->esp) = v_; }	/* 441ecd: push 0x2a */
	m->esp -= 4; M32(m->esp) = 0x441ed4u; native_call(m, 0x41ee40u);	/* 441ecf: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441ed4: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 441ed7: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 441ed8: pop esi */
	m->esp += 4 + 0; return;	/* 441ed9: ret  */
L_441eda:
	m->eax = M32((DWORD)(0x4ded18u));	/* 441eda: mov eax, dword ptr [0x4ded18] */
	{ DWORD v_ = 0x65u; m->esp -= 4; M32(m->esp) = v_; }	/* 441edf: push 0x65 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 441ee1: push eax */
	m->esp -= 4; M32(m->esp) = 0x441ee7u; native_call(m, 0x452170u);	/* 441ee2: call 0x452170 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441ee7: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 441eea: test eax, eax */
	if (!m->zf) goto L_441f02;	/* 441eec: jne 0x441f02 */
L_441eee:
	{ DWORD v_ = 0x6u; m->esp -= 4; M32(m->esp) = v_; }	/* 441eee: push 6 */
	m->esp -= 4; M32(m->esp) = 0x441ef5u; native_call(m, 0x41e760u);	/* 441ef0: call 0x41e760 */
	{ DWORD v_ = 0x29u; m->esp -= 4; M32(m->esp) = v_; }	/* 441ef5: push 0x29 */
	m->esp -= 4; M32(m->esp) = 0x441efcu; native_call(m, 0x41ee40u);	/* 441ef7: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441efc: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 441eff: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 441f00: pop esi */
	m->esp += 4 + 0; return;	/* 441f01: ret  */
L_441f02:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 441f02: push 2 */
	m->esp -= 4; M32(m->esp) = 0x441f09u; native_call(m, 0x441250u);	/* 441f04: call 0x441250 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441f09: add esp, 4 */
	M32((DWORD)(0x4deb48u)) = m->edi;	/* 441f0c: mov dword ptr [0x4deb48], edi */
	M32((DWORD)(0x67ef20u)) = 0x320u;	/* 441f12: mov dword ptr [0x67ef20], 0x320 */
	m->edi = M32(m->esp); m->esp += 4;	/* 441f1c: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 441f1d: pop esi */
	m->esp += 4 + 0; return;	/* 441f1e: ret  */
L_441f1f:
	m->ecx = M32((DWORD)(0x4e1524u));	/* 441f1f: mov ecx, dword ptr [0x4e1524] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 441f25: push ecx */
	m->esp -= 4; M32(m->esp) = 0x441f2bu; native_call(m, 0x401600u);	/* 441f26: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441f2b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441f2e: cmp eax, esi */
	if (!m->zf) goto L_441f5f;	/* 441f30: jne 0x441f5f */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 441f32: push edi */
	m->esp -= 4; M32(m->esp) = 0x441f38u; native_call(m, 0x41e760u);	/* 441f33: call 0x41e760 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 441f38: push 2 */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 441f3a: mov dword ptr [0x4dda44], 0 */
	m->esp -= 4; M32(m->esp) = 0x441f49u; native_call(m, 0x441250u);	/* 441f44: call 0x441250 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441f49: add esp, 8 */
	M32((DWORD)(0x4deb48u)) = m->edi;	/* 441f4c: mov dword ptr [0x4deb48], edi */
	M32((DWORD)(0x67ef20u)) = 0x258u;	/* 441f52: mov dword ptr [0x67ef20], 0x258 */
	m->edi = M32(m->esp); m->esp += 4;	/* 441f5c: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 441f5d: pop esi */
	m->esp += 4 + 0; return;	/* 441f5e: ret  */
L_441f5f:
	m->edx = M32((DWORD)(0x4e0cd4u));	/* 441f5f: mov edx, dword ptr [0x4e0cd4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 441f65: push edx */
	m->esp -= 4; M32(m->esp) = 0x441f6bu; native_call(m, 0x401600u);	/* 441f66: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441f6b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441f6e: cmp eax, esi */
	if (!m->zf) goto L_441f99;	/* 441f70: jne 0x441f99 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 441f72: push edi */
	m->esp -= 4; M32(m->esp) = 0x441f78u; native_call(m, 0x41e760u);	/* 441f73: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441f78: add esp, 4 */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 441f7b: mov dword ptr [0x4dda44], 0 */
	M32((DWORD)(0x4dc24cu)) = m->esi;	/* 441f85: mov dword ptr [0x4dc24c], esi */
	m->esp -= 4; M32(m->esp) = 0x441f90u; native_call(m, 0x40ee20u);	/* 441f8b: call 0x40ee20 */
	M32((DWORD)(0x4deb48u)) = m->edi;	/* 441f90: mov dword ptr [0x4deb48], edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 441f96: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 441f97: pop esi */
	m->esp += 4 + 0; return;	/* 441f98: ret  */
L_441f99:
	m->eax = M32((DWORD)(0x4e153cu));	/* 441f99: mov eax, dword ptr [0x4e153c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 441f9e: push eax */
	m->esp -= 4; M32(m->esp) = 0x441fa4u; native_call(m, 0x401600u);	/* 441f9f: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441fa4: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441fa7: cmp eax, esi */
	if (!m->zf) goto L_441fe2;	/* 441fa9: jne 0x441fe2 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 441fab: push edi */
	m->esp -= 4; M32(m->esp) = 0x441fb1u; native_call(m, 0x41e760u);	/* 441fac: call 0x41e760 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 441fb1: push 4 */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 441fb3: mov dword ptr [0x4dda44], 0 */
	m->esp -= 4; M32(m->esp) = 0x441fc2u; native_call(m, 0x441250u);	/* 441fbd: call 0x441250 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441fc2: add esp, 8 */
	M32((DWORD)(0x4deb48u)) = m->esi;	/* 441fc5: mov dword ptr [0x4deb48], esi */
	M32((DWORD)(0x67ef20u)) = 0xd2u;	/* 441fcb: mov dword ptr [0x67ef20], 0xd2 */
	m->esp -= 4; M32(m->esp) = 0x441fdau; native_call(m, 0x447010u);	/* 441fd5: call 0x447010 */
	m->esp -= 4; M32(m->esp) = 0x441fdfu; native_call(m, 0x48b420u);	/* 441fda: call 0x48b420 */
	m->edi = M32(m->esp); m->esp += 4;	/* 441fdf: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 441fe0: pop esi */
	m->esp += 4 + 0; return;	/* 441fe1: ret  */
L_441fe2:
	m->ecx = M32((DWORD)(0x76d48cu));	/* 441fe2: mov ecx, dword ptr [0x76d48c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 441fe8: push ecx */
	m->esp -= 4; M32(m->esp) = 0x441feeu; native_call(m, 0x401600u);	/* 441fe9: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441fee: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 441ff1: test eax, eax */
	if (m->zf) goto L_442029;	/* 441ff3: je 0x442029 */
	{ DWORD a_ = M32((DWORD)(0x9dae10u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441ff5: cmp dword ptr [0x9dae10], edi */
	if (m->zf || m->sf != m->of) goto L_442029;	/* 441ffb: jle 0x442029 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 441ffd: push 4 */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 441fff: mov dword ptr [0x4dda44], 0 */
	m->esp -= 4; M32(m->esp) = 0x44200eu; native_call(m, 0x441250u);	/* 442009: call 0x441250 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44200e: add esp, 4 */
	M32((DWORD)(0x4deb48u)) = m->esi;	/* 442011: mov dword ptr [0x4deb48], esi */
	M32((DWORD)(0x67ef20u)) = 0xd2u;	/* 442017: mov dword ptr [0x67ef20], 0xd2 */
	m->esp -= 4; M32(m->esp) = 0x442026u; native_call(m, 0x48b420u);	/* 442021: call 0x48b420 */
	m->edi = M32(m->esp); m->esp += 4;	/* 442026: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 442027: pop esi */
	m->esp += 4 + 0; return;	/* 442028: ret  */
L_442029:
	m->edx = M32((DWORD)(0x9da440u));	/* 442029: mov edx, dword ptr [0x9da440] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44202f: push edx */
	m->esp -= 4; M32(m->esp) = 0x442035u; native_call(m, 0x401600u);	/* 442030: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 442035: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 442038: cmp eax, esi */
	if (!m->zf) goto L_442047;	/* 44203a: jne 0x442047 */
	m->esp -= 4; M32(m->esp) = 0x442041u; native_call(m, 0x440d70u);	/* 44203c: call 0x440d70 */
	M32((DWORD)(0x9eeab4u)) = m->esi;	/* 442041: mov dword ptr [0x9eeab4], esi */
L_442047:
	m->edi = M32(m->esp); m->esp += 4;	/* 442047: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 442048: pop esi */
	m->esp += 4 + 0; return;	/* 442049: ret  */
}

/* menu_436e10 (0x436e10), lifted by tools/lift.py */
static void lift_436e10(X86 *m)
{
	m->eax = M32((DWORD)(0x9dae70u));	/* 436e10: mov eax, dword ptr [0x9dae70] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 436e15: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 436e16: push eax */
	m->esp -= 4; M32(m->esp) = 0x436e1cu; native_call(m, 0x401600u);	/* 436e17: call 0x401600 */
	m->edi = 0x1u;	/* 436e1c: mov edi, 1 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436e21: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436e24: cmp eax, edi */
	if (!m->zf) goto L_436e84;	/* 436e26: jne 0x436e84 */
	m->ecx = M32((DWORD)(0x4ded6cu));	/* 436e28: mov ecx, dword ptr [0x4ded6c] */
	m->edx = M32((DWORD)(0x4ded68u));	/* 436e2e: mov edx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 436e34: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 436e35: push edx */
	m->esp -= 4; M32(m->esp) = 0x436e3bu; native_call(m, 0x432240u);	/* 436e36: call 0x432240 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436e3b: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436e3e: cmp eax, 4 */
	if (!m->zf) goto L_436e61;	/* 436e41: jne 0x436e61 */
	m->eax = M32((DWORD)(0x68039cu));	/* 436e43: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 436e48: test eax, eax */
	if (!m->zf) goto L_4370d5;	/* 436e4a: jne 0x4370d5 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 436e50: push 0 */
	m->esp -= 4; M32(m->esp) = 0x436e57u; native_call(m, 0x41e760u);	/* 436e52: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436e57: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x436e5fu; native_call(m, 0x4346c0u);	/* 436e5a: call 0x4346c0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 436e5f: pop edi */
	m->esp += 4 + 0; return;	/* 436e60: ret  */
L_436e61:
	{ DWORD a_ = m->eax, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436e61: cmp eax, 5 */
	if (!m->zf) goto L_436e84;	/* 436e64: jne 0x436e84 */
	m->eax = M32((DWORD)(0x68039cu));	/* 436e66: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 436e6b: test eax, eax */
	if (!m->zf) goto L_4370d5;	/* 436e6d: jne 0x4370d5 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 436e73: push 0 */
	m->esp -= 4; M32(m->esp) = 0x436e7au; native_call(m, 0x41e760u);	/* 436e75: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436e7a: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x436e82u; native_call(m, 0x434640u);	/* 436e7d: call 0x434640 */
	m->edi = M32(m->esp); m->esp += 4;	/* 436e82: pop edi */
	m->esp += 4 + 0; return;	/* 436e83: ret  */
L_436e84:
	m->eax = M32((DWORD)(0x4e1510u));	/* 436e84: mov eax, dword ptr [0x4e1510] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 436e89: push eax */
	m->esp -= 4; M32(m->esp) = 0x436e8fu; native_call(m, 0x401600u);	/* 436e8a: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436e8f: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436e92: cmp eax, edi */
	if (!m->zf) goto L_436eb4;	/* 436e94: jne 0x436eb4 */
	m->eax = M32((DWORD)(0x68039cu));	/* 436e96: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 436e9b: test eax, eax */
	if (!m->zf) goto L_4370d5;	/* 436e9d: jne 0x4370d5 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 436ea3: push 0 */
	m->esp -= 4; M32(m->esp) = 0x436eaau; native_call(m, 0x41e760u);	/* 436ea5: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436eaa: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x436eb2u; native_call(m, 0x4346c0u);	/* 436ead: call 0x4346c0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 436eb2: pop edi */
	m->esp += 4 + 0; return;	/* 436eb3: ret  */
L_436eb4:
	m->ecx = M32((DWORD)(0x4e0cdcu));	/* 436eb4: mov ecx, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 436eba: push ecx */
	m->esp -= 4; M32(m->esp) = 0x436ec0u; native_call(m, 0x401600u);	/* 436ebb: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436ec0: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436ec3: cmp eax, edi */
	if (!m->zf) goto L_436ee5;	/* 436ec5: jne 0x436ee5 */
	m->eax = M32((DWORD)(0x68039cu));	/* 436ec7: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 436ecc: test eax, eax */
	if (!m->zf) goto L_4370d5;	/* 436ece: jne 0x4370d5 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 436ed4: push 0 */
	m->esp -= 4; M32(m->esp) = 0x436edbu; native_call(m, 0x41e760u);	/* 436ed6: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436edb: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x436ee3u; native_call(m, 0x434640u);	/* 436ede: call 0x434640 */
	m->edi = M32(m->esp); m->esp += 4;	/* 436ee3: pop edi */
	m->esp += 4 + 0; return;	/* 436ee4: ret  */
L_436ee5:
	m->edx = M32((DWORD)(0x680390u));	/* 436ee5: mov edx, dword ptr [0x680390] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 436eeb: push edx */
	m->esp -= 4; M32(m->esp) = 0x436ef1u; native_call(m, 0x401600u);	/* 436eec: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436ef1: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436ef4: cmp eax, edi */
	if (!m->zf) goto L_4370d5;	/* 436ef6: jne 0x4370d5 */
	m->eax = M32((DWORD)(0x68039cu));	/* 436efc: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 436f01: test eax, eax */
	if (!m->zf) goto L_4370d5;	/* 436f03: jne 0x4370d5 */
	m->eax = M32((DWORD)(0x67ef24u));	/* 436f09: mov eax, dword ptr [0x67ef24] */
	M32((DWORD)(0x9dc428u)) = 0x14u;	/* 436f0e: mov dword ptr [0x9dc428], 0x14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 436f18: push eax */
	m->esp -= 4; M32(m->esp) = 0x436f1eu; native_call(m, 0x401590u);	/* 436f19: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436f1e: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436f21: cmp eax, edi */
	if (m->zf) goto L_436f38;	/* 436f23: je 0x436f38 */
	m->ecx = M32((DWORD)(0x9db0acu));	/* 436f25: mov ecx, dword ptr [0x9db0ac] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 436f2b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x436f31u; native_call(m, 0x401590u);	/* 436f2c: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436f31: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436f34: cmp eax, edi */
	if (!m->zf) goto L_436f47;	/* 436f36: jne 0x436f47 */
L_436f38:
	M32((DWORD)(0x9dc428u)) = 0xau;	/* 436f38: mov dword ptr [0x9dc428], 0xa */
	goto L_43701d;	/* 436f42: jmp 0x43701d */
L_436f47:
	m->eax = M32((DWORD)(0x9dc428u));	/* 436f47: mov eax, dword ptr [0x9dc428] */
	{ DWORD a_ = m->eax, b_ = 0x14u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436f4c: cmp eax, 0x14 */
	if (!m->zf) goto L_437014;	/* 436f4f: jne 0x437014 */
	m->eax = M32((DWORD)(0x74de1cu));	/* 436f55: mov eax, dword ptr [0x74de1c] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 436f5a: dec eax */
	if (m->zf) goto L_436fc3;	/* 436f5b: je 0x436fc3 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 436f5d: dec eax */
	if (!m->zf) goto L_4370d5;	/* 436f5e: jne 0x4370d5 */
	m->edx = M32((DWORD)(0x9dd358u));	/* 436f64: mov edx, dword ptr [0x9dd358] */
	m->eax = M32((DWORD)(0x9dd35cu));	/* 436f6a: mov eax, dword ptr [0x9dd35c] */
	{ DWORD a_ = m->edx, b_ = 0x15cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 436f6f: add edx, 0x15c */
	{ DWORD a_ = m->eax, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 436f75: add eax, 0x44 */
	M32((DWORD)(0x76d42cu)) = m->edi;	/* 436f78: mov dword ptr [0x76d42c], edi */
	M32((DWORD)(0x9dd348u)) = m->edi;	/* 436f7e: mov dword ptr [0x9dd348], edi */
	M32((DWORD)(0x74de1cu)) = 0x2u;	/* 436f84: mov dword ptr [0x74de1c], 2 */
	M32((DWORD)(0x680bc0u)) = 0x41a00000u;	/* 436f8e: mov dword ptr [0x680bc0], 0x41a00000 */
	M32((DWORD)(0x9da4a4u)) = 0x3ecccccdu;	/* 436f98: mov dword ptr [0x9da4a4], 0x3ecccccd */
	M32((DWORD)(0x67ef34u)) = m->edx;	/* 436fa2: mov dword ptr [0x67ef34], edx */
	M32((DWORD)(0x67fb38u)) = m->eax;	/* 436fa8: mov dword ptr [0x67fb38], eax */
	M32((DWORD)(0x9dd3f8u)) = 0x0u;	/* 436fad: mov dword ptr [0x9dd3f8], 0 */
	M32((DWORD)(0x9dc428u)) = 0x0u;	/* 436fb7: mov dword ptr [0x9dc428], 0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 436fc1: pop edi */
	m->esp += 4 + 0; return;	/* 436fc2: ret  */
L_436fc3:
	m->ecx = M32((DWORD)(0x9dd6e8u));	/* 436fc3: mov ecx, dword ptr [0x9dd6e8] */
	m->edx = M32((DWORD)(0x9dd6f4u));	/* 436fc9: mov edx, dword ptr [0x9dd6f4] */
	{ DWORD a_ = m->ecx, b_ = 0x172u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 436fcf: add ecx, 0x172 */
	{ DWORD a_ = m->edx, b_ = 0xffffffd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 436fd5: add edx, -0x30 */
	M32((DWORD)(0x76d42cu)) = m->edi;	/* 436fd8: mov dword ptr [0x76d42c], edi */
	M32((DWORD)(0x74de1cu)) = 0x2u;	/* 436fde: mov dword ptr [0x74de1c], 2 */
	M32((DWORD)(0x680bc0u)) = 0x41a00000u;	/* 436fe8: mov dword ptr [0x680bc0], 0x41a00000 */
	M32((DWORD)(0x9da4a4u)) = 0x3ecccccdu;	/* 436ff2: mov dword ptr [0x9da4a4], 0x3ecccccd */
	M32((DWORD)(0x67ef34u)) = m->ecx;	/* 436ffc: mov dword ptr [0x67ef34], ecx */
	M32((DWORD)(0x67fb38u)) = m->edx;	/* 437002: mov dword ptr [0x67fb38], edx */
	M32((DWORD)(0x9dc428u)) = 0x0u;	/* 437008: mov dword ptr [0x9dc428], 0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 437012: pop edi */
	m->esp += 4 + 0; return;	/* 437013: ret  */
L_437014:
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 437014: cmp eax, 0xa */
	if (!m->zf) goto L_4370d5;	/* 437017: jne 0x4370d5 */
L_43701d:
	m->eax = M32((DWORD)(0x74de1cu));	/* 43701d: mov eax, dword ptr [0x74de1c] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 437022: dec eax */
	if (m->zf) goto L_437076;	/* 437023: je 0x437076 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 437025: dec eax */
	if (!m->zf) goto L_4370d5;	/* 437026: jne 0x4370d5 */
	m->eax = M32((DWORD)(0x9dd6e8u));	/* 43702c: mov eax, dword ptr [0x9dd6e8] */
	m->ecx = M32((DWORD)(0x9dd6f4u));	/* 437031: mov ecx, dword ptr [0x9dd6f4] */
	{ DWORD a_ = m->eax, b_ = 0xaau & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 437037: add eax, 0xaa */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43703c: add ecx, -0x30 */
	M32((DWORD)(0x74de1cu)) = m->edi;	/* 43703f: mov dword ptr [0x74de1c], edi */
	M32((DWORD)(0x76d42cu)) = m->edi;	/* 437045: mov dword ptr [0x76d42c], edi */
	M32((DWORD)(0x680bc0u)) = 0x41a00000u;	/* 43704b: mov dword ptr [0x680bc0], 0x41a00000 */
	M32((DWORD)(0x9da4a4u)) = 0x3ecccccdu;	/* 437055: mov dword ptr [0x9da4a4], 0x3ecccccd */
	M32((DWORD)(0x67ef34u)) = m->eax;	/* 43705f: mov dword ptr [0x67ef34], eax */
	M32((DWORD)(0x67fb38u)) = m->ecx;	/* 437064: mov dword ptr [0x67fb38], ecx */
	M32((DWORD)(0x9dc428u)) = 0x0u;	/* 43706a: mov dword ptr [0x9dc428], 0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 437074: pop edi */
	m->esp += 4 + 0; return;	/* 437075: ret  */
L_437076:
	m->edx = M32((DWORD)(0x9dd358u));	/* 437076: mov edx, dword ptr [0x9dd358] */
	m->eax = M32((DWORD)(0x9dd35cu));	/* 43707c: mov eax, dword ptr [0x9dd35c] */
	{ DWORD a_ = m->edx, b_ = 0x15cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 437081: add edx, 0x15c */
	{ DWORD a_ = m->eax, b_ = 0xd4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 437087: add eax, 0xd4 */
	M32((DWORD)(0x74de1cu)) = 0x0u;	/* 43708c: mov dword ptr [0x74de1c], 0 */
	M32((DWORD)(0x76d42cu)) = m->edi;	/* 437096: mov dword ptr [0x76d42c], edi */
	M32((DWORD)(0x680bc0u)) = 0x41a00000u;	/* 43709c: mov dword ptr [0x680bc0], 0x41a00000 */
	M32((DWORD)(0x9da4a4u)) = 0x3ecccccdu;	/* 4370a6: mov dword ptr [0x9da4a4], 0x3ecccccd */
	M32((DWORD)(0x9dd564u)) = 0x0u;	/* 4370b0: mov dword ptr [0x9dd564], 0 */
	M32((DWORD)(0x9dd6ccu)) = m->edi;	/* 4370ba: mov dword ptr [0x9dd6cc], edi */
	M32((DWORD)(0x67ef34u)) = m->edx;	/* 4370c0: mov dword ptr [0x67ef34], edx */
	M32((DWORD)(0x67fb38u)) = m->eax;	/* 4370c6: mov dword ptr [0x67fb38], eax */
	M32((DWORD)(0x9dc428u)) = 0x0u;	/* 4370cb: mov dword ptr [0x9dc428], 0 */
L_4370d5:
	m->edi = M32(m->esp); m->esp += 4;	/* 4370d5: pop edi */
	m->esp += 4 + 0; return;	/* 4370d6: ret  */
}

/* armc_enter (0x441260), lifted by tools/lift.py */
static void lift_441260(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 441260: push ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 441261: fld dword ptr [0x4b071c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9418u)); FPOP();	/* 441267: fcomp dword ptr [0x4a9418] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44126d: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 44126e: push ebp */
	m->ebx = 0x44cu;	/* 44126f: mov ebx, 0x44c */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 441274: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 441275: push edi */
	M32((DWORD)(m->esp + 0x10u)) = m->ebx;	/* 441276: mov dword ptr [esp + 0x10], ebx */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 44127a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 44127c: test ah, 0x41 */
	if (!m->zf) goto L_44128b;	/* 44127f: jne 0x44128b */
	M32((DWORD)(0x4b071cu)) = 0x40000000u;	/* 441281: mov dword ptr [0x4b071c], 0x40000000 */
L_44128b:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 44128b: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a940cu));	/* 441291: fmul dword ptr [0x4a940c] */
	m->esi = M32((DWORD)(m->esp + 0x18u));	/* 441297: mov esi, dword ptr [esp + 0x18] */
	m->edi = m->esi;	/* 44129b: mov edi, esi */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 44129d: call 0x49ec14 */
	m->edx = M32((DWORD)(0x4deb48u));	/* 4412a2: mov edx, dword ptr [0x4deb48] */
	m->ecx = m->eax;	/* 4412a8: mov ecx, eax */
	M32((DWORD)(0x4b2a74u)) = m->ecx;	/* 4412aa: mov dword ptr [0x4b2a74], ecx */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 4412b0: xor ebp, ebp */
	FPUSH((long double)(int)M32((DWORD)(0x4b2a74u)));	/* 4412b2: fild dword ptr [0x4b2a74] */
	{ DWORD a_ = m->edx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4412b8: cmp edx, ebp */
	MF((DWORD)(0x4b2a78u)) = (float)ST(0); FPOP();	/* 4412ba: fstp dword ptr [0x4b2a78] */
	if (m->zf) goto L_4412e3;	/* 4412c0: je 0x4412e3 */
	m->ebx = 0x3b6u;	/* 4412c2: mov ebx, 0x3b6 */
	M32((DWORD)(0x4df024u)) = m->ebp;	/* 4412c7: mov dword ptr [0x4df024], ebp */
	M32((DWORD)(m->esp + 0x10u)) = m->ebx;	/* 4412cd: mov dword ptr [esp + 0x10], ebx */
	M32((DWORD)(0x4df028u)) = m->ebp;	/* 4412d1: mov dword ptr [0x4df028], ebp */
	M32((DWORD)(0x680378u)) = m->ebp;	/* 4412d7: mov dword ptr [0x680378], ebp */
	M32((DWORD)(0x68037cu)) = m->ebp;	/* 4412dd: mov dword ptr [0x68037c], ebp */
L_4412e3:
	{ DWORD a_ = M32((DWORD)(0x67ef14u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4412e3: cmp dword ptr [0x67ef14], ebp */
	if (m->zf) goto L_441308;	/* 4412e9: je 0x441308 */
	m->ecx = m->eax;	/* 4412eb: mov ecx, eax */
	m->ebx = 0x898u;	/* 4412ed: mov ebx, 0x898 */
	M32((DWORD)(0x4b2a74u)) = m->ecx;	/* 4412f2: mov dword ptr [0x4b2a74], ecx */
	M32((DWORD)(m->esp + 0x10u)) = m->ebx;	/* 4412f8: mov dword ptr [esp + 0x10], ebx */
	FPUSH((long double)(int)M32((DWORD)(0x4b2a74u)));	/* 4412fc: fild dword ptr [0x4b2a74] */
	MF((DWORD)(0x4b2a78u)) = (float)ST(0); FPOP();	/* 441302: fstp dword ptr [0x4b2a78] */
L_441308:
	m->eax = M32((DWORD)(m->esi + 0x3534u));	/* 441308: mov eax, dword ptr [esi + 0x3534] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44130e: cmp eax, ebp */
	if (m->zf) goto L_441320;	/* 441310: je 0x441320 */
L_441312:
	m->esi = m->edi;	/* 441312: mov esi, edi */
	m->edi = m->eax;	/* 441314: mov edi, eax */
	m->eax = M32((DWORD)(m->edi + 0x3534u));	/* 441316: mov eax, dword ptr [edi + 0x3534] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44131c: cmp eax, ebp */
	if (!m->zf) goto L_441312;	/* 44131e: jne 0x441312 */
L_441320:
	m->eax = M32((DWORD)(0x680370u));	/* 441320: mov eax, dword ptr [0x680370] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441325: cmp eax, 4 */
	if (!m->cf && !m->zf) goto L_44171b;	/* 441328: ja 0x44171b */
	switch (m->eax) { case 0: goto L_441335; case 1: goto L_4413f6; case 2: goto L_441529; case 3: goto L_441572; case 4: goto L_4416dc; default: abort(); }	/* 44132e: jmp dword ptr [eax*4 + 0x441724] */
L_441335:
	M32((DWORD)(m->esi + 0x3520u)) = 0x3f800000u;	/* 441335: mov dword ptr [esi + 0x3520], 0x3f800000 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x68038cu)));	/* 44133f: fld dword ptr [0x68038c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a94e8u)); FPOP();	/* 441345: fcomp dword ptr [0x4a94e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 44134b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 44134d: test ah, 0x41 */
	if (!m->zf) goto L_441364;	/* 441350: jne 0x441364 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x68038cu)));	/* 441352: fld dword ptr [0x68038c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 441358: fsub dword ptr [0x4b071c] */
	MF((DWORD)(0x68038cu)) = (float)ST(0); FPOP();	/* 44135e: fstp dword ptr [0x68038c] */
L_441364:
	{ DWORD a_ = M32((DWORD)(0x4b2a70u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441364: cmp dword ptr [0x4b2a70], ebp */
	if (m->zf) goto L_4413b6;	/* 44136a: je 0x4413b6 */
	m->eax = M32((DWORD)(0x4df024u));	/* 44136c: mov eax, dword ptr [0x4df024] */
	m->ecx = M32((DWORD)(0x4df028u));	/* 441371: mov ecx, dword ptr [0x4df028] */
	m->edx = M32((DWORD)(0x4df02cu));	/* 441377: mov edx, dword ptr [0x4df02c] */
	M32((DWORD)(0x9dd930u)) = m->eax;	/* 44137d: mov dword ptr [0x9dd930], eax */
	m->eax = M32((DWORD)(0x680378u));	/* 441382: mov eax, dword ptr [0x680378] */
	M32((DWORD)(0x9dd934u)) = m->ecx;	/* 441387: mov dword ptr [0x9dd934], ecx */
	m->ecx = M32((DWORD)(0x68037cu));	/* 44138d: mov ecx, dword ptr [0x68037c] */
	M32((DWORD)(0x9dd938u)) = m->edx;	/* 441393: mov dword ptr [0x9dd938], edx */
	m->edx = M32((DWORD)(0x680380u));	/* 441399: mov edx, dword ptr [0x680380] */
	M32((DWORD)(0x9dd918u)) = m->eax;	/* 44139f: mov dword ptr [0x9dd918], eax */
	M32((DWORD)(0x9dd91cu)) = m->ecx;	/* 4413a4: mov dword ptr [0x9dd91c], ecx */
	M32((DWORD)(0x9dd920u)) = m->edx;	/* 4413aa: mov dword ptr [0x9dd920], edx */
	M32((DWORD)(0x4b2a70u)) = m->ebp;	/* 4413b0: mov dword ptr [0x4b2a70], ebp */
L_4413b6:
	m->ecx = M32((DWORD)(0x76d410u));	/* 4413b6: mov ecx, dword ptr [0x76d410] */
	m->eax = 0x1u;	/* 4413bc: mov eax, 1 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4413c1: cmp ecx, eax */
	if (!m->zf) goto L_44171b;	/* 4413c3: jne 0x44171b */
	{ DWORD a_ = M32((DWORD)(0x9da49cu)), b_ = 0x65u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4413c9: cmp dword ptr [0x9da49c], 0x65 */
	if (!m->zf) goto L_44171b;	/* 4413d0: jne 0x44171b */
	M32((DWORD)(0x4dc24cu)) = m->eax;	/* 4413d6: mov dword ptr [0x4dc24c], eax */
	m->esp -= 4; M32(m->esp) = 0x4413e0u; native_call(m, 0x40ee20u);	/* 4413db: call 0x40ee20 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4413e0: pop edi */
	M32((DWORD)(0x4deb48u)) = m->ebp;	/* 4413e1: mov dword ptr [0x4deb48], ebp */
	m->esi = M32(m->esp); m->esp += 4;	/* 4413e7: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4413e8: pop ebp */
	M32((DWORD)(0x9da49cu)) = 0x66u;	/* 4413e9: mov dword ptr [0x9da49c], 0x66 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4413f3: pop ebx */
	m->ecx = M32(m->esp); m->esp += 4;	/* 4413f4: pop ecx */
	m->esp += 4 + 0; return;	/* 4413f5: ret  */
L_4413f6:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df02cu)));	/* 4413f6: fld dword ptr [0x4df02c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4b2a78u));	/* 4413fc: fsub dword ptr [0x4b2a78] */
	MF((DWORD)(0x4df02cu)) = (float)ST(0); FPOP();	/* 441402: fstp dword ptr [0x4df02c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680380u)));	/* 441408: fld dword ptr [0x680380] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4b2a78u));	/* 44140e: fsub dword ptr [0x4b2a78] */
	MF((DWORD)(0x680380u)) = (float)ST(0); FPOP();	/* 441414: fstp dword ptr [0x680380] */
	m->edx = M32((DWORD)(m->esi + 0x193cu));	/* 44141a: mov edx, dword ptr [esi + 0x193c] */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 441420: add edx, ecx */
	m->eax = m->edx;	/* 441422: mov eax, edx */
	M32((DWORD)(m->esi + 0x193cu)) = m->edx;	/* 441424: mov dword ptr [esi + 0x193c], edx */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44142a: cmp eax, ebx */
	if (m->sf != m->of) goto L_44171b;	/* 44142c: jl 0x44171b */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x1940u)));	/* 441432: fld dword ptr [esi + 0x1940] */
	M32((DWORD)(m->esi + 0x193cu)) = m->ebp;	/* 441438: mov dword ptr [esi + 0x193c], ebp */
	m->eax = M32((DWORD)(0x67ef14u));	/* 44143e: mov eax, dword ptr [0x67ef14] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441443: cmp eax, ebp */
	if (m->zf) goto L_44144f;	/* 441445: je 0x44144f */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a95c8u));	/* 441447: fsub dword ptr [0x4a95c8] */
	goto L_441455;	/* 44144d: jmp 0x441455 */
L_44144f:
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a95c4u));	/* 44144f: fsub dword ptr [0x4a95c4] */
L_441455:
	MF((DWORD)(m->esi + 0x1940u)) = (float)ST(0); FPOP();	/* 441455: fstp dword ptr [esi + 0x1940] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 44145b: fild dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x9dd938u)));	/* 44145f: fld dword ptr [0x9dd938] */
	m->eax = M32((DWORD)(0x9dd930u));	/* 441465: mov eax, dword ptr [0x9dd930] */
	m->ecx = M32((DWORD)(0x9dd918u));	/* 44146a: mov ecx, dword ptr [0x9dd918] */
	ST(0) = ST(0) - ST(1);	/* 441470: fsub st(1) */
	m->edx = M32((DWORD)(0x9dd934u));	/* 441472: mov edx, dword ptr [0x9dd934] */
	M32((DWORD)(0x4df024u)) = m->eax;	/* 441478: mov dword ptr [0x4df024], eax */
	m->eax = M32((DWORD)(0x9dd91cu));	/* 44147d: mov eax, dword ptr [0x9dd91c] */
	M32((DWORD)(0x680378u)) = m->ecx;	/* 441482: mov dword ptr [0x680378], ecx */
	M32((DWORD)(0x4df028u)) = m->edx;	/* 441488: mov dword ptr [0x4df028], edx */
	M32((DWORD)(0x68037cu)) = m->eax;	/* 44148e: mov dword ptr [0x68037c], eax */
	MF((DWORD)(0x4df02cu)) = (float)ST(0); FPOP();	/* 441493: fstp dword ptr [0x4df02c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x9dd920u)));	/* 441499: fld dword ptr [0x9dd920] */
	ST(0) = ST(0) - ST(1);	/* 44149f: fsub st(1) */
	M32((DWORD)(0x680370u)) = m->ebp;	/* 4414a1: mov dword ptr [0x680370], ebp */
	MF((DWORD)(0x680380u)) = (float)ST(0); FPOP();	/* 4414a7: fstp dword ptr [0x680380] */
	M32((DWORD)(m->esi + 0x3520u)) = 0x3f800000u;	/* 4414ad: mov dword ptr [esi + 0x3520], 0x3f800000 */
	ST(0) = ST(0); FPOP();	/* 4414b7: fstp st(0) */
	m->esp -= 4; M32(m->esp) = 0x4414beu; native_call(m, 0x441200u);	/* 4414b9: call 0x441200 */
	m->ecx = M32((DWORD)(0x67ef20u));	/* 4414be: mov ecx, dword ptr [0x67ef20] */
	m->edx = M32((DWORD)(0x4df024u));	/* 4414c4: mov edx, dword ptr [0x4df024] */
	m->eax = 0x1u;	/* 4414ca: mov eax, 1 */
	M32((DWORD)(0x76d3e8u)) = m->ecx;	/* 4414cf: mov dword ptr [0x76d3e8], ecx */
	m->ecx = M32((DWORD)(0x4df02cu));	/* 4414d5: mov ecx, dword ptr [0x4df02c] */
	M32((DWORD)(0x9eeaa8u)) = m->eax;	/* 4414db: mov dword ptr [0x9eeaa8], eax */
	M32((DWORD)(0x4b2a70u)) = m->eax;	/* 4414e0: mov dword ptr [0x4b2a70], eax */
	m->eax = M32((DWORD)(0x4df028u));	/* 4414e5: mov eax, dword ptr [0x4df028] */
	M32((DWORD)(0x9dd930u)) = m->edx;	/* 4414ea: mov dword ptr [0x9dd930], edx */
	m->edx = M32((DWORD)(0x680378u));	/* 4414f0: mov edx, dword ptr [0x680378] */
	M32((DWORD)(0x9dd934u)) = m->eax;	/* 4414f6: mov dword ptr [0x9dd934], eax */
	m->eax = M32((DWORD)(0x68037cu));	/* 4414fb: mov eax, dword ptr [0x68037c] */
	M32((DWORD)(0x9dd938u)) = m->ecx;	/* 441500: mov dword ptr [0x9dd938], ecx */
	m->ecx = M32((DWORD)(0x680380u));	/* 441506: mov ecx, dword ptr [0x680380] */
	m->edi = M32(m->esp); m->esp += 4;	/* 44150c: pop edi */
	M32((DWORD)(0x4deb48u)) = m->ebp;	/* 44150d: mov dword ptr [0x4deb48], ebp */
	m->esi = M32(m->esp); m->esp += 4;	/* 441513: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 441514: pop ebp */
	M32((DWORD)(0x9dd918u)) = m->edx;	/* 441515: mov dword ptr [0x9dd918], edx */
	M32((DWORD)(0x9dd91cu)) = m->eax;	/* 44151b: mov dword ptr [0x9dd91c], eax */
	M32((DWORD)(0x9dd920u)) = m->ecx;	/* 441520: mov dword ptr [0x9dd920], ecx */
	m->ebx = M32(m->esp); m->esp += 4;	/* 441526: pop ebx */
	m->ecx = M32(m->esp); m->esp += 4;	/* 441527: pop ecx */
	m->esp += 4 + 0; return;	/* 441528: ret  */
L_441529:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 441529: fld dword ptr [0x4b071c] */
	ST(0) = ST(0) + ST(0);	/* 44152f: fadd st(0), st(0) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x68038cu));	/* 441531: fadd dword ptr [0x68038c] */
	MF((DWORD)(0x68038cu)) = (float)ST(0);	/* 441537: fst dword ptr [0x68038c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9550u)); FPOP();	/* 44153d: fcomp dword ptr [0x4a9550] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 441543: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 441545: test ah, 1 */
	if (!m->zf) goto L_44171b;	/* 441548: jne 0x44171b */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 44154e: push 4 */
	M32((DWORD)(0x68038cu)) = 0x42b40000u;	/* 441550: mov dword ptr [0x68038c], 0x42b40000 */
	M32((DWORD)(0x680370u)) = 0x1u;	/* 44155a: mov dword ptr [0x680370], 1 */
	m->esp -= 4; M32(m->esp) = 0x441569u; native_call(m, 0x41e760u);	/* 441564: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441569: add esp, 4 */
	m->edi = M32(m->esp); m->esp += 4;	/* 44156c: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44156d: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 44156e: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 44156f: pop ebx */
	m->ecx = M32(m->esp); m->esp += 4;	/* 441570: pop ecx */
	m->esp += 4 + 0; return;	/* 441571: ret  */
L_441572:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df02cu)));	/* 441572: fld dword ptr [0x4df02c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4b2a78u));	/* 441578: fadd dword ptr [0x4b2a78] */
	MF((DWORD)(0x4df02cu)) = (float)ST(0); FPOP();	/* 44157e: fstp dword ptr [0x4df02c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680380u)));	/* 441584: fld dword ptr [0x680380] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4b2a78u));	/* 44158a: fadd dword ptr [0x4b2a78] */
	MF((DWORD)(0x680380u)) = (float)ST(0); FPOP();	/* 441590: fstp dword ptr [0x680380] */
	m->edx = M32((DWORD)(m->esi + 0x193cu));	/* 441596: mov edx, dword ptr [esi + 0x193c] */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44159c: add edx, ecx */
	m->eax = m->edx;	/* 44159e: mov eax, edx */
	M32((DWORD)(m->esi + 0x193cu)) = m->edx;	/* 4415a0: mov dword ptr [esi + 0x193c], edx */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4415a6: cmp eax, ebx */
	if (m->sf != m->of) goto L_4416ab;	/* 4415a8: jl 0x4416ab */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x1940u)));	/* 4415ae: fld dword ptr [esi + 0x1940] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a95c4u));	/* 4415b4: fadd dword ptr [0x4a95c4] */
	M32((DWORD)(m->esi + 0x193cu)) = m->ebp;	/* 4415ba: mov dword ptr [esi + 0x193c], ebp */
	{ DWORD v_ = 0x67fb3cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4415c0: push 0x67fb3c */
	MF((DWORD)(m->esi + 0x1940u)) = (float)ST(0); FPOP();	/* 4415c5: fstp dword ptr [esi + 0x1940] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 4415cb: fild dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(0x9dd930u));	/* 4415cf: mov edx, dword ptr [0x9dd930] */
	m->eax = M32((DWORD)(0x9dd918u));	/* 4415d5: mov eax, dword ptr [0x9dd918] */
	m->ecx = M32((DWORD)(0x9dd934u));	/* 4415da: mov ecx, dword ptr [0x9dd934] */
	M32((DWORD)(0x4df024u)) = m->edx;	/* 4415e0: mov dword ptr [0x4df024], edx */
	{ long double t = ST(0); FPUSH(t); }	/* 4415e6: fld st(0) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x9dd938u));	/* 4415e8: fadd dword ptr [0x9dd938] */
	m->edx = M32((DWORD)(0x9dd91cu));	/* 4415ee: mov edx, dword ptr [0x9dd91c] */
	M32((DWORD)(0x680378u)) = m->eax;	/* 4415f4: mov dword ptr [0x680378], eax */
	M32((DWORD)(0x4df028u)) = m->ecx;	/* 4415f9: mov dword ptr [0x4df028], ecx */
	M32((DWORD)(0x68037cu)) = m->edx;	/* 4415ff: mov dword ptr [0x68037c], edx */
	M32((DWORD)(0x680370u)) = m->ebp;	/* 441605: mov dword ptr [0x680370], ebp */
	MF((DWORD)(0x4df02cu)) = (float)ST(0); FPOP();	/* 44160b: fstp dword ptr [0x4df02c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x9dd920u));	/* 441611: fadd dword ptr [0x9dd920] */
	MF((DWORD)(0x680380u)) = (float)ST(0); FPOP();	/* 441617: fstp dword ptr [0x680380] */
	M32((DWORD)(m->esi + 0x3520u)) = 0x3f800000u;	/* 44161d: mov dword ptr [esi + 0x3520], 0x3f800000 */
	m->edi = M32((DWORD)(0x9dae10u));	/* 441627: mov edi, dword ptr [0x9dae10] */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 44162d: dec edi */
	M32((DWORD)(0x9dae10u)) = m->edi;	/* 44162e: mov dword ptr [0x9dae10], edi */
	m->esp -= 4; M32(m->esp) = 0x441639u; native_call(m, 0x441190u);	/* 441634: call 0x441190 */
	m->ecx = M32((DWORD)(0x4deb48u));	/* 441639: mov ecx, dword ptr [0x4deb48] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44163f: add esp, 4 */
	m->eax = 0x1u;	/* 441642: mov eax, 1 */
	{ DWORD a_ = m->ecx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441647: cmp ecx, ebp */
	M32((DWORD)(0x9eeaa8u)) = m->eax;	/* 441649: mov dword ptr [0x9eeaa8], eax */
	if (!m->zf) goto L_441656;	/* 44164e: jne 0x441656 */
	M32((DWORD)(0x4deb48u)) = m->ebp;	/* 441650: mov dword ptr [0x4deb48], ebp */
L_441656:
	m->ecx = M32((DWORD)(0x67ef20u));	/* 441656: mov ecx, dword ptr [0x67ef20] */
	m->edx = M32((DWORD)(0x4df024u));	/* 44165c: mov edx, dword ptr [0x4df024] */
	M32((DWORD)(0x76d3e8u)) = m->ecx;	/* 441662: mov dword ptr [0x76d3e8], ecx */
	m->ecx = M32((DWORD)(0x4df02cu));	/* 441668: mov ecx, dword ptr [0x4df02c] */
	M32((DWORD)(0x4b2a70u)) = m->eax;	/* 44166e: mov dword ptr [0x4b2a70], eax */
	m->eax = M32((DWORD)(0x4df028u));	/* 441673: mov eax, dword ptr [0x4df028] */
	M32((DWORD)(0x9dd930u)) = m->edx;	/* 441678: mov dword ptr [0x9dd930], edx */
	m->edx = M32((DWORD)(0x680378u));	/* 44167e: mov edx, dword ptr [0x680378] */
	M32((DWORD)(0x9dd934u)) = m->eax;	/* 441684: mov dword ptr [0x9dd934], eax */
	m->eax = M32((DWORD)(0x68037cu));	/* 441689: mov eax, dword ptr [0x68037c] */
	M32((DWORD)(0x9dd938u)) = m->ecx;	/* 44168e: mov dword ptr [0x9dd938], ecx */
	m->ecx = M32((DWORD)(0x680380u));	/* 441694: mov ecx, dword ptr [0x680380] */
	M32((DWORD)(0x9dd918u)) = m->edx;	/* 44169a: mov dword ptr [0x9dd918], edx */
	M32((DWORD)(0x9dd91cu)) = m->eax;	/* 4416a0: mov dword ptr [0x9dd91c], eax */
	M32((DWORD)(0x9dd920u)) = m->ecx;	/* 4416a5: mov dword ptr [0x9dd920], ecx */
L_4416ab:
	FPUSH(x87_ldm((const float *)(DWORD)(0x68038cu)));	/* 4416ab: fld dword ptr [0x68038c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a94e8u)); FPOP();	/* 4416b1: fcomp dword ptr [0x4a94e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4416b7: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4416b9: test ah, 0x41 */
	if (!m->zf) goto L_44171b;	/* 4416bc: jne 0x44171b */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 4416be: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4416c4: fmul dword ptr [0x4a942c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 4416ca: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4416cb: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4416cc: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4416cd: pop ebx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x68038cu));	/* 4416ce: fsubr dword ptr [0x68038c] */
	MF((DWORD)(0x68038cu)) = (float)ST(0); FPOP();	/* 4416d4: fstp dword ptr [0x68038c] */
	m->ecx = M32(m->esp); m->esp += 4;	/* 4416da: pop ecx */
	m->esp += 4 + 0; return;	/* 4416db: ret  */
L_4416dc:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 4416dc: fld dword ptr [0x4b071c] */
	ST(0) = ST(0) + ST(0);	/* 4416e2: fadd st(0), st(0) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x68038cu));	/* 4416e4: fadd dword ptr [0x68038c] */
	MF((DWORD)(0x68038cu)) = (float)ST(0);	/* 4416ea: fst dword ptr [0x68038c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9550u)); FPOP();	/* 4416f0: fcomp dword ptr [0x4a9550] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4416f6: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4416f8: test ah, 1 */
	if (!m->zf) goto L_44171b;	/* 4416fb: jne 0x44171b */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4416fd: push 4 */
	M32((DWORD)(0x68038cu)) = 0x42b40000u;	/* 4416ff: mov dword ptr [0x68038c], 0x42b40000 */
	M32((DWORD)(0x680370u)) = 0x3u;	/* 441709: mov dword ptr [0x680370], 3 */
	m->esp -= 4; M32(m->esp) = 0x441718u; native_call(m, 0x41e760u);	/* 441713: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441718: add esp, 4 */
L_44171b:
	m->edi = M32(m->esp); m->esp += 4;	/* 44171b: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44171c: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 44171d: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 44171e: pop ebx */
	m->ecx = M32(m->esp); m->esp += 4;	/* 44171f: pop ecx */
	m->esp += 4 + 0; return;	/* 441720: ret  */
}

/* match_debugHandler (0x42ada0), lifted by tools/lift.py */
static void lift_42ada0(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42ada0: push ecx */
	m->eax = M32((DWORD)(0x4de6fcu));	/* 42ada1: mov eax, dword ptr [0x4de6fc] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ada6: push esi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 42ada7: xor esi, esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ada9: push edi */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42adaa: cmp eax, esi */
	if (m->zf) goto L_42ae1d;	/* 42adac: je 0x42ae1d */
	{ DWORD a_ = M32((DWORD)(0x68039cu)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42adae: cmp dword ptr [0x68039c], esi */
	if (!m->zf) goto L_42b116;	/* 42adb4: jne 0x42b116 */
	m->edi = 0x9dc92cu;	/* 42adba: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42adbf: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42adc2: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42adc4: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42adc6: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 42adc8: dec ecx */
	if (m->zf) goto L_42adf4;	/* 42adc9: je 0x42adf4 */
	{ DWORD v_ = 0x9dc92cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42adcb: push 0x9dc92c */
	m->esp -= 4; M32(m->esp) = 0x42add5u; native_call(m, 0x4512c0u);	/* 42add0: call 0x4512c0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42add5: add esp, 4 */
	M32((DWORD)(0x4de6fcu)) = m->esi;	/* 42add8: mov dword ptr [0x4de6fc], esi */
	M32((DWORD)(0x9fd95cu)) = 0x1u;	/* 42adde: mov dword ptr [0x9fd95c], 1 */
	M32((DWORD)(0x9fd948u)) = 0x9dc92cu;	/* 42ade8: mov dword ptr [0x9fd948], 0x9dc92c */
	goto L_42ae00;	/* 42adf2: jmp 0x42ae00 */
L_42adf4:
	M32((DWORD)(0x4de6fcu)) = m->esi;	/* 42adf4: mov dword ptr [0x4de6fc], esi */
	M32((DWORD)(0x9fd95cu)) = m->esi;	/* 42adfa: mov dword ptr [0x9fd95c], esi */
L_42ae00:
	M32((DWORD)(0x68039cu)) = m->esi;	/* 42ae00: mov dword ptr [0x68039c], esi */
	m->esp -= 4; M32(m->esp) = 0x42ae0bu; native_call(m, 0x431590u);	/* 42ae06: call 0x431590 */
	m->eax = M32((DWORD)(0x4ded18u));	/* 42ae0b: mov eax, dword ptr [0x4ded18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42ae10: push eax */
	m->esp -= 4; M32(m->esp) = 0x42ae16u; native_call(m, 0x401310u);	/* 42ae11: call 0x401310 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42ae16: add esp, 4 */
	m->edi = M32(m->esp); m->esp += 4;	/* 42ae19: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 42ae1a: pop esi */
	m->ecx = M32(m->esp); m->esp += 4;	/* 42ae1b: pop ecx */
	m->esp += 4 + 0; return;	/* 42ae1c: ret  */
L_42ae1d:
	m->ecx = M32((DWORD)(0x4defa8u));	/* 42ae1d: mov ecx, dword ptr [0x4defa8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42ae23: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42ae29u; native_call(m, 0x401600u);	/* 42ae24: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42ae29: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42ae2c: test eax, eax */
	if (m->zf) goto L_42ae72;	/* 42ae2e: je 0x42ae72 */
	m->esp -= 4; M32(m->esp) = 0x42ae35u; native_call(m, 0x401460u);	/* 42ae30: call 0x401460 */
	m->edi = 0x1u;	/* 42ae35: mov edi, 1 */
	{ DWORD v_ = 0x32u; m->esp -= 4; M32(m->esp) = v_; }	/* 42ae3a: push 0x32 */
	M32((DWORD)(0x68039cu)) = m->edi;	/* 42ae3c: mov dword ptr [0x68039c], edi */
	m->esp -= 4; M32(m->esp) = 0x42ae47u; native_call(m, 0x431560u);	/* 42ae42: call 0x431560 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42ae47: add esp, 4 */
	M32((DWORD)(0x4de6fcu)) = m->edi;	/* 42ae4a: mov dword ptr [0x4de6fc], edi */
	M32((DWORD)(0x9da434u)) = 0x41a00000u;	/* 42ae50: mov dword ptr [0x9da434], 0x41a00000 */
	M32((DWORD)(0x9da3d8u)) = 0x32u;	/* 42ae5a: mov dword ptr [0x9da3d8], 0x32 */
	m->edi = M32(m->esp); m->esp += 4;	/* 42ae64: pop edi */
	M32((DWORD)(0x9da3dcu)) = 0x1ccu;	/* 42ae65: mov dword ptr [0x9da3dc], 0x1cc */
	m->esi = M32(m->esp); m->esp += 4;	/* 42ae6f: pop esi */
	m->ecx = M32(m->esp); m->esp += 4;	/* 42ae70: pop ecx */
	m->esp += 4 + 0; return;	/* 42ae71: ret  */
L_42ae72:
	m->edx = M32((DWORD)(0x76d48cu));	/* 42ae72: mov edx, dword ptr [0x76d48c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42ae78: push edx */
	m->esp -= 4; M32(m->esp) = 0x42ae7eu; native_call(m, 0x401600u);	/* 42ae79: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42ae7e: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42ae81: test eax, eax */
	if (m->zf) goto L_42aebd;	/* 42ae83: je 0x42aebd */
	m->eax = M32((DWORD)(0xa0baf8u));	/* 42ae85: mov eax, dword ptr [0xa0baf8] */
	m->edi = 0x1u;	/* 42ae8a: mov edi, 1 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42ae8f: cmp eax, esi */
	if (m->zf) goto L_42aeae;	/* 42ae91: je 0x42aeae */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ae93: push esi */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ae94: push esi */
	{ DWORD v_ = 0x9f9418u; m->esp -= 4; M32(m->esp) = v_; }	/* 42ae95: push 0x9f9418 */
	M32((DWORD)(0x9f941cu)) = m->edi;	/* 42ae9a: mov dword ptr [0x9f941c], edi */
	m->esp -= 4; M32(m->esp) = 0x42aea5u; native_call(m, 0x451270u);	/* 42aea0: call 0x451270 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42aea5: add esp, 0xc */
	M32((DWORD)(0x9f941cu)) = m->esi;	/* 42aea8: mov dword ptr [0x9f941c], esi */
L_42aeae:
	M32((DWORD)(0x4de6f8u)) = m->edi;	/* 42aeae: mov dword ptr [0x4de6f8], edi */
	m->esp -= 4; M32(m->esp) = 0x42aeb9u; native_call(m, 0x41e8b0u);	/* 42aeb4: call 0x41e8b0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 42aeb9: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 42aeba: pop esi */
	m->ecx = M32(m->esp); m->esp += 4;	/* 42aebb: pop ecx */
	m->esp += 4 + 0; return;	/* 42aebc: ret  */
L_42aebd:
	m->eax = M32((DWORD)(0x4def00u));	/* 42aebd: mov eax, dword ptr [0x4def00] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42aec2: push eax */
	m->esp -= 4; M32(m->esp) = 0x42aec8u; native_call(m, 0x401590u);	/* 42aec3: call 0x401590 */
	m->edi = 0x1u;	/* 42aec8: mov edi, 1 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42aecd: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42aed0: cmp eax, edi */
	if (!m->zf) goto L_42af32;	/* 42aed2: jne 0x42af32 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 42aed4: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4de6c0u));	/* 42aeda: fmul dword ptr [0x4de6c0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9534u));	/* 42aee0: fmul dword ptr [0x4a9534] */
	{ long double t = ST(0); FPUSH(t); }	/* 42aee6: fld st(0) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4de344u));	/* 42aee8: fadd dword ptr [0x4de344] */
	MF((DWORD)(0x4de344u)) = (float)ST(0); FPOP();	/* 42aeee: fstp dword ptr [0x4de344] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4de6c8u)));	/* 42aef4: fld dword ptr [0x4de6c8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 42aefa: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9534u));	/* 42af00: fmul dword ptr [0x4a9534] */
	MF((DWORD)(m->esp + 0x8u)) = (float)ST(0);	/* 42af06: fst dword ptr [esp + 8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4de34cu));	/* 42af0a: fadd dword ptr [0x4de34c] */
	MF((DWORD)(0x4de34cu)) = (float)ST(0); FPOP();	/* 42af10: fstp dword ptr [0x4de34c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4df024u));	/* 42af16: fadd dword ptr [0x4df024] */
	MF((DWORD)(0x4df024u)) = (float)ST(0); FPOP();	/* 42af1c: fstp dword ptr [0x4df024] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x8u)));	/* 42af22: fld dword ptr [esp + 8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4df02cu));	/* 42af26: fadd dword ptr [0x4df02c] */
	MF((DWORD)(0x4df02cu)) = (float)ST(0); FPOP();	/* 42af2c: fstp dword ptr [0x4df02c] */
L_42af32:
	m->ecx = M32((DWORD)(0x4def08u));	/* 42af32: mov ecx, dword ptr [0x4def08] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42af38: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42af3eu; native_call(m, 0x401590u);	/* 42af39: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42af3e: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42af41: cmp eax, edi */
	if (!m->zf) goto L_42afab;	/* 42af43: jne 0x42afab */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 42af45: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4de6c0u));	/* 42af4b: fmul dword ptr [0x4de6c0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9534u));	/* 42af51: fmul dword ptr [0x4a9534] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4de344u)));	/* 42af57: fld dword ptr [0x4de344] */
	ST(0) = ST(0) - ST(1);	/* 42af5d: fsub st(1) */
	MF((DWORD)(0x4de344u)) = (float)ST(0); FPOP();	/* 42af5f: fstp dword ptr [0x4de344] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4de6c8u)));	/* 42af65: fld dword ptr [0x4de6c8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 42af6b: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9534u));	/* 42af71: fmul dword ptr [0x4a9534] */
	MF((DWORD)(m->esp + 0x8u)) = (float)ST(0); FPOP();	/* 42af77: fstp dword ptr [esp + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4de34cu)));	/* 42af7b: fld dword ptr [0x4de34c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x8u));	/* 42af81: fsub dword ptr [esp + 8] */
	MF((DWORD)(0x4de34cu)) = (float)ST(0); FPOP();	/* 42af85: fstp dword ptr [0x4de34c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df024u)));	/* 42af8b: fld dword ptr [0x4df024] */
	ST(0) = ST(0) - ST(1);	/* 42af91: fsub st(1) */
	MF((DWORD)(0x4df024u)) = (float)ST(0); FPOP();	/* 42af93: fstp dword ptr [0x4df024] */
	ST(0) = ST(0); FPOP();	/* 42af99: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df02cu)));	/* 42af9b: fld dword ptr [0x4df02c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x8u));	/* 42afa1: fsub dword ptr [esp + 8] */
	MF((DWORD)(0x4df02cu)) = (float)ST(0); FPOP();	/* 42afa5: fstp dword ptr [0x4df02c] */
L_42afab:
	m->edx = M32((DWORD)(0x4def10u));	/* 42afab: mov edx, dword ptr [0x4def10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42afb1: push edx */
	m->esp -= 4; M32(m->esp) = 0x42afb7u; native_call(m, 0x401590u);	/* 42afb2: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42afb7: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42afba: cmp eax, edi */
	if (!m->zf) goto L_42afc3;	/* 42afbc: jne 0x42afc3 */
	m->esp -= 4; M32(m->esp) = 0x42afc3u; native_call(m, 0x42aa30u);	/* 42afbe: call 0x42aa30 */
L_42afc3:
	m->eax = M32((DWORD)(0x4def18u));	/* 42afc3: mov eax, dword ptr [0x4def18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42afc8: push eax */
	m->esp -= 4; M32(m->esp) = 0x42afceu; native_call(m, 0x401590u);	/* 42afc9: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42afce: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42afd1: cmp eax, edi */
	if (!m->zf) goto L_42afda;	/* 42afd3: jne 0x42afda */
	m->esp -= 4; M32(m->esp) = 0x42afdau; native_call(m, 0x42aad0u);	/* 42afd5: call 0x42aad0 */
L_42afda:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4de6c0u)));	/* 42afda: fld dword ptr [0x4de6c0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9560u));	/* 42afe0: fmul dword ptr [0x4a9560] */
	m->ecx = M32((DWORD)(0x4de344u));	/* 42afe6: mov ecx, dword ptr [0x4de344] */
	m->edx = M32((DWORD)(0x4de34cu));	/* 42afec: mov edx, dword ptr [0x4de34c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42aff2: xor eax, eax */
	M32((DWORD)(0x680378u)) = m->ecx;	/* 42aff4: mov dword ptr [0x680378], ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4de344u));	/* 42affa: fsubr dword ptr [0x4de344] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x9fd954u))) & 0xff) << 0);	/* 42b000: mov al, byte ptr [0x9fd954] */
	M32((DWORD)(0x680380u)) = m->edx;	/* 42b005: mov dword ptr [0x680380], edx */
	m->edx = M32((DWORD)(0x4de344u));	/* 42b00b: mov edx, dword ptr [0x4de344] */
	MF((DWORD)(0x4df024u)) = (float)ST(0); FPOP();	/* 42b011: fstp dword ptr [0x4df024] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4de348u)));	/* 42b017: fld dword ptr [0x4de348] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 42b01d: fadd dword ptr [0x4a9418] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 42b023: lea ecx, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 42b026: lea eax, [eax + ecx*2] */
	m->ecx = M32((DWORD)(0x4de348u));	/* 42b029: mov ecx, dword ptr [0x4de348] */
	MF((DWORD)(0x4df028u)) = (float)ST(0); FPOP();	/* 42b02f: fstp dword ptr [0x4df028] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4de6c8u)));	/* 42b035: fld dword ptr [0x4de6c8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9560u));	/* 42b03b: fmul dword ptr [0x4a9560] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 42b041: shl eax, 3 */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4de34cu));	/* 42b044: fsubr dword ptr [0x4de34c] */
	M32((DWORD)(m->eax + 0x4dfa1cu)) = m->edx;	/* 42b04a: mov dword ptr [eax + 0x4dfa1c], edx */
	m->edx = M32((DWORD)(0x4de34cu));	/* 42b050: mov edx, dword ptr [0x4de34c] */
	M32((DWORD)(m->eax + 0x4dfa20u)) = m->ecx;	/* 42b056: mov dword ptr [eax + 0x4dfa20], ecx */
	M32((DWORD)(m->eax + 0x4dfa24u)) = m->edx;	/* 42b05c: mov dword ptr [eax + 0x4dfa24], edx */
	MF((DWORD)(0x4df02cu)) = (float)ST(0); FPOP();	/* 42b062: fstp dword ptr [0x4df02c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4de6c4u)));	/* 42b068: fld dword ptr [0x4de6c4] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4de348u));	/* 42b06e: fadd dword ptr [0x4de348] */
	m->eax = M32((DWORD)(0x680388u));	/* 42b074: mov eax, dword ptr [0x680388] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42b079: push eax */
	MF((DWORD)(0x68037cu)) = (float)ST(0); FPOP();	/* 42b07a: fstp dword ptr [0x68037c] */
	m->esp -= 4; M32(m->esp) = 0x42b085u; native_call(m, 0x401600u);	/* 42b080: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42b085: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42b088: cmp eax, edi */
	if (!m->zf) goto L_42b0a0;	/* 42b08a: jne 0x42b0a0 */
	m->ecx = M32((DWORD)(0x4e0464u));	/* 42b08c: mov ecx, dword ptr [0x4e0464] */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 42b092: dec ecx */
	{ DWORD a_ = m->ecx, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->ecx = r_; }	/* 42b093: neg ecx */
	{ DWORD a_ = m->ecx, b_ = m->ecx, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 42b095: sbb ecx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 42b097: add ecx, 2 */
	M32((DWORD)(0x4e0464u)) = m->ecx;	/* 42b09a: mov dword ptr [0x4e0464], ecx */
L_42b0a0:
	m->edx = M32((DWORD)(0x4e0468u));	/* 42b0a0: mov edx, dword ptr [0x4e0468] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42b0a6: push edx */
	m->esp -= 4; M32(m->esp) = 0x42b0acu; native_call(m, 0x401600u);	/* 42b0a7: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42b0ac: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42b0af: cmp eax, edi */
	if (!m->zf) goto L_42b0b9;	/* 42b0b1: jne 0x42b0b9 */
	{ DWORD a_ = M32((DWORD)(0x4de6e0u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(0x4de6e0u)) = r_; }	/* 42b0b3: inc dword ptr [0x4de6e0] */
L_42b0b9:
	m->eax = M32((DWORD)(0x4e046cu));	/* 42b0b9: mov eax, dword ptr [0x4e046c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42b0be: push eax */
	m->esp -= 4; M32(m->esp) = 0x42b0c4u; native_call(m, 0x401600u);	/* 42b0bf: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42b0c4: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42b0c7: cmp eax, edi */
	m->esi = 0xau;	/* 42b0c9: mov esi, 0xa */
	if (!m->zf) goto L_42b0d6;	/* 42b0ce: jne 0x42b0d6 */
	{ DWORD a_ = M32((DWORD)(0x4de6e0u)), b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(0x4de6e0u)) = r_; }	/* 42b0d0: add dword ptr [0x4de6e0], esi */
L_42b0d6:
	m->ecx = M32((DWORD)(0x4e0470u));	/* 42b0d6: mov ecx, dword ptr [0x4e0470] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42b0dc: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42b0e2u; native_call(m, 0x401600u);	/* 42b0dd: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42b0e2: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42b0e5: cmp eax, edi */
	if (!m->zf) goto L_42b0ef;	/* 42b0e7: jne 0x42b0ef */
	{ DWORD a_ = M32((DWORD)(0x4de6e0u)), r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); M32((DWORD)(0x4de6e0u)) = r_; }	/* 42b0e9: dec dword ptr [0x4de6e0] */
L_42b0ef:
	m->edx = M32((DWORD)(0x4e0874u));	/* 42b0ef: mov edx, dword ptr [0x4e0874] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42b0f5: push edx */
	m->esp -= 4; M32(m->esp) = 0x42b0fbu; native_call(m, 0x401600u);	/* 42b0f6: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42b0fb: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42b0fe: cmp eax, edi */
	if (!m->zf) goto L_42b108;	/* 42b100: jne 0x42b108 */
	{ DWORD a_ = M32((DWORD)(0x4de6e0u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(0x4de6e0u)) = r_; }	/* 42b102: sub dword ptr [0x4de6e0], esi */
L_42b108:
	{ DWORD a_ = M32((DWORD)(0x4de6e0u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42b108: cmp dword ptr [0x4de6e0], edi */
	if (m->sf == m->of) goto L_42b116;	/* 42b10e: jge 0x42b116 */
	M32((DWORD)(0x4de6e0u)) = m->edi;	/* 42b110: mov dword ptr [0x4de6e0], edi */
L_42b116:
	m->edi = M32(m->esp); m->esp += 4;	/* 42b116: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 42b117: pop esi */
	m->ecx = M32(m->esp); m->esp += 4;	/* 42b118: pop ecx */
	m->esp += 4 + 0; return;	/* 42b119: ret  */
}

/* arena_454c10 (0x454c10), lifted by tools/lift.py */
static void lift_454c10(X86 *m)
{
	m->eax = M32((DWORD)(0xa0d7acu));	/* 454c10: mov eax, dword ptr [0xa0d7ac] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454c15: test eax, eax */
	if (m->zf) goto L_454c4a;	/* 454c17: je 0x454c4a */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 454c19: mov eax, dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 454c1d: mov ecx, dword ptr [esp + 0x1c] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 454c21: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454c25: push eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 454c26: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 454c2a: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 454c2b: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 454c2f: push edx */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 454c30: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454c34: push eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 454c35: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 454c39: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 454c3a: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 454c3e: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454c3f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 454c40: push ecx */
	m->esp -= 4; M32(m->esp) = 0x454c46u; native_call(m, 0x453cf0u);	/* 454c41: call 0x453cf0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 454c46: add esp, 0x20 */
	m->esp += 4 + 0; return;	/* 454c49: ret  */
L_454c4a:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 454c4a: xor eax, eax */
	m->esp += 4 + 0; return;	/* 454c4c: ret  */
}

/* arena_454d20 (0x454d20), lifted by tools/lift.py */
static void lift_454d20(X86 *m)
{
	m->eax = M32((DWORD)(0xa0d7b0u));	/* 454d20: mov eax, dword ptr [0xa0d7b0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454d25: test eax, eax */
	if (m->zf) goto L_454d5a;	/* 454d27: je 0x454d5a */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 454d29: mov eax, dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 454d2d: mov ecx, dword ptr [esp + 0x1c] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 454d31: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454d35: push eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 454d36: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 454d3a: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 454d3b: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 454d3f: push edx */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 454d40: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454d44: push eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 454d45: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 454d49: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 454d4a: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 454d4e: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454d4f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 454d50: push ecx */
	m->esp -= 4; M32(m->esp) = 0x454d56u; native_call(m, 0x453cf0u);	/* 454d51: call 0x453cf0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 454d56: add esp, 0x20 */
	m->esp += 4 + 0; return;	/* 454d59: ret  */
L_454d5a:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 454d5a: xor eax, eax */
	m->esp += 4 + 0; return;	/* 454d5c: ret  */
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
