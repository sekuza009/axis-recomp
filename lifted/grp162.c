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

static void lift_43f9d0(X86 *m);

/* WinMain (0x43f9d0), lifted by tools/lift.py */
static void lift_43f9d0(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 43f9d0: mov eax, dword ptr [esp + 0xc] */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43f9d4: sub esp, 0x1c */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43f9d7: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43f9d8: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43f9d9: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43f9da: push eax */
	m->esp -= 4; M32(m->esp) = 0x43f9e0u; native_call(m, 0x43f160u);	/* 43f9db: call 0x43f160 */
	m->esi = M32((DWORD)(0x4a92ccu));	/* 43f9e0: mov esi, dword ptr [0x4a92cc] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43f9e6: add esp, 4 */
	{ DWORD v_ = 0x4b2854u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f9e9: push 0x4b2854 */
	{ DWORD v_ = 0x4b2834u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f9ee: push 0x4b2834 */
	m->esp -= 4; M32(m->esp) = 0x43f9f5u; native_call(m, m->esi);	/* 43f9f3: call esi */
	m->ebx = M32((DWORD)(0x4a9328u));	/* 43f9f5: mov ebx, dword ptr [0x4a9328] */
	m->edi = M32((DWORD)(0x4a9110u));	/* 43f9fb: mov edi, dword ptr [0x4a9110] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43fa01: test eax, eax */
	if (m->zf) goto L_43fa15;	/* 43fa03: je 0x43fa15 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fa05: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fa07: push 0 */
	{ DWORD v_ = 0x12u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fa09: push 0x12 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43fa0b: push eax */
	m->esp -= 4; M32(m->esp) = 0x43fa0eu; native_call(m, m->ebx);	/* 43fa0c: call ebx */
	{ DWORD v_ = 0x1f4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fa0e: push 0x1f4 */
	m->esp -= 4; M32(m->esp) = 0x43fa15u; native_call(m, m->edi);	/* 43fa13: call edi */
L_43fa15:
	{ DWORD v_ = 0x9dd878u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fa15: push 0x9dd878 */
	m->esp -= 4; M32(m->esp) = 0x43fa20u; native_call(m, M32(0x4a910cu));	/* 43fa1a: call dword ptr [0x4a910c] */
	m->esp -= 4; M32(m->esp) = 0x43fa26u; native_call(m, M32(0x4a9364u));	/* 43fa20: call dword ptr [0x4a9364] */
	{ DWORD v_ = 0x7d0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fa26: push 0x7d0 */
	M32((DWORD)(0x9dd8e8u)) = m->eax;	/* 43fa2b: mov dword ptr [0x9dd8e8], eax */
	m->esp -= 4; M32(m->esp) = 0x43fa32u; native_call(m, m->edi);	/* 43fa30: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fa32: push 0 */
	{ DWORD v_ = 0x4b0714u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fa34: push 0x4b0714 */
	m->esp -= 4; M32(m->esp) = 0x43fa3bu; native_call(m, m->esi);	/* 43fa39: call esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43fa3b: test eax, eax */
	if (m->zf) goto L_43fa5e;	/* 43fa3d: je 0x43fa5e */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fa3f: push 0 */
	{ DWORD v_ = 0x4b2554u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fa41: push 0x4b2554 */
	{ DWORD v_ = 0x4b2a00u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fa46: push 0x4b2a00 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fa4b: push 0 */
	m->esp -= 4; M32(m->esp) = 0x43fa53u; native_call(m, M32(0x4a9324u));	/* 43fa4d: call dword ptr [0x4a9324] */
	m->edi = M32(m->esp); m->esp += 4;	/* 43fa53: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43fa54: pop esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43fa55: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43fa57: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fa58: add esp, 0x1c */
	m->esp += 4 + 16; return;	/* 43fa5b: ret 0x10 */
L_43fa5e:
	m->esp -= 4; M32(m->esp) = 0x43fa63u; native_call(m, 0x401000u);	/* 43fa5e: call 0x401000 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43fa63: test eax, eax */
	if (!m->zf) goto L_43fa84;	/* 43fa65: jne 0x43fa84 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43fa67: push eax */
	{ DWORD v_ = 0x4b2554u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fa68: push 0x4b2554 */
	{ DWORD v_ = 0x4b2528u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fa6d: push 0x4b2528 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43fa72: push eax */
	m->esp -= 4; M32(m->esp) = 0x43fa79u; native_call(m, M32(0x4a9324u));	/* 43fa73: call dword ptr [0x4a9324] */
	m->edi = M32(m->esp); m->esp += 4;	/* 43fa79: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43fa7a: pop esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43fa7b: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43fa7d: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fa7e: add esp, 0x1c */
	m->esp += 4 + 16; return;	/* 43fa81: ret 0x10 */
L_43fa84:
	m->esp -= 4; M32(m->esp) = 0x43fa8au; native_call(m, M32(0x4a9100u));	/* 43fa84: call dword ptr [0x4a9100] */
	{ DWORD a_ = (m->eax & 0xffff), b_ = 0x412u & 0xffffu, r_ = (a_ - b_) & 0xffffu; FLAGS(r_, 16); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 15) & 1; }	/* 43fa8a: cmp ax, 0x412 */
	M16((DWORD)(0x9dd858u)) = (WORD)((m->eax & 0xffff));	/* 43fa8e: mov word ptr [0x9dd858], ax */
	if (m->zf) goto L_43fae5;	/* 43fa94: je 0x43fae5 */
	{ DWORD a_ = (m->eax & 0xffff), b_ = 0x812u & 0xffffu, r_ = (a_ - b_) & 0xffffu; FLAGS(r_, 16); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 15) & 1; }	/* 43fa96: cmp ax, 0x812 */
	if (m->zf) goto L_43fae5;	/* 43fa9a: je 0x43fae5 */
	M32((DWORD)(0x9dae74u)) = 0x2u;	/* 43fa9c: mov dword ptr [0x9dae74], 2 */
	M32((DWORD)(0x9dd8c8u)) = 0x4b27e4u;	/* 43faa6: mov dword ptr [0x9dd8c8], 0x4b27e4 */
L_43fab0:
	m->esp -= 4; M32(m->esp) = 0x43fab5u; native_call(m, 0x43f300u);	/* 43fab0: call 0x43f300 */
	m->eax = M32((DWORD)(0x76d410u));	/* 43fab5: mov eax, dword ptr [0x76d410] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43faba: test eax, eax */
	if (!m->zf) goto L_43fbc1;	/* 43fabc: jne 0x43fbc1 */
	m->esp -= 4; M32(m->esp) = 0x43fac7u; native_call(m, 0x41e260u);	/* 43fac2: call 0x41e260 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43fac7: test eax, eax */
	if (!m->zf) goto L_43fafb;	/* 43fac9: jne 0x43fafb */
	m->ecx = M32((DWORD)(0x9dd8c8u));	/* 43facb: mov ecx, dword ptr [0x9dd8c8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43fad1: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43fad7u; native_call(m, 0x41edf0u);	/* 43fad2: call 0x41edf0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fad7: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43fada: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 43fadc: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43fadd: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43fade: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fadf: add esp, 0x1c */
	m->esp += 4 + 16; return;	/* 43fae2: ret 0x10 */
L_43fae5:
	M32((DWORD)(0x9dae74u)) = 0x1u;	/* 43fae5: mov dword ptr [0x9dae74], 1 */
	M32((DWORD)(0x9dd8c8u)) = 0x4b2794u;	/* 43faef: mov dword ptr [0x9dd8c8], 0x4b2794 */
	goto L_43fab0;	/* 43faf9: jmp 0x43fab0 */
L_43fafb:
	m->esp -= 4; M32(m->esp) = 0x43fb00u; native_call(m, 0x43f770u);	/* 43fafb: call 0x43f770 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43fb00: test eax, eax */
	if (!m->zf) goto L_43fb1c;	/* 43fb02: jne 0x43fb1c */
	{ DWORD v_ = 0x4b04b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fb04: push 0x4b04b0 */
	m->esp -= 4; M32(m->esp) = 0x43fb0eu; native_call(m, 0x41edf0u);	/* 43fb09: call 0x41edf0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fb0e: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43fb11: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 43fb13: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43fb14: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43fb15: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fb16: add esp, 0x1c */
	m->esp += 4 + 16; return;	/* 43fb19: ret 0x10 */
L_43fb1c:
	m->esp -= 4; M32(m->esp) = 0x43fb21u; native_call(m, 0x41e6d0u);	/* 43fb1c: call 0x41e6d0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43fb21: test eax, eax */
	if (!m->zf) goto L_43fb3d;	/* 43fb23: jne 0x43fb3d */
	{ DWORD v_ = 0x4b04b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fb25: push 0x4b04b0 */
	m->esp -= 4; M32(m->esp) = 0x43fb2fu; native_call(m, 0x41edf0u);	/* 43fb2a: call 0x41edf0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fb2f: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43fb32: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 43fb34: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43fb35: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43fb36: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fb37: add esp, 0x1c */
	m->esp += 4 + 16; return;	/* 43fb3a: ret 0x10 */
L_43fb3d:
	m->esp -= 4; M32(m->esp) = 0x43fb42u; native_call(m, 0x41e550u);	/* 43fb3d: call 0x41e550 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43fb42: test eax, eax */
	if (!m->zf) goto L_43fb5e;	/* 43fb44: jne 0x43fb5e */
	{ DWORD v_ = 0x4b04b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fb46: push 0x4b04b0 */
	m->esp -= 4; M32(m->esp) = 0x43fb50u; native_call(m, 0x41edf0u);	/* 43fb4b: call 0x41edf0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fb50: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43fb53: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 43fb55: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43fb56: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43fb57: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fb58: add esp, 0x1c */
	m->esp += 4 + 16; return;	/* 43fb5b: ret 0x10 */
L_43fb5e:
	m->esp -= 4; M32(m->esp) = 0x43fb63u; native_call(m, 0x41e5b0u);	/* 43fb5e: call 0x41e5b0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43fb63: test eax, eax */
	if (!m->zf) goto L_43fb7f;	/* 43fb65: jne 0x43fb7f */
	{ DWORD v_ = 0x4b04b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fb67: push 0x4b04b0 */
	m->esp -= 4; M32(m->esp) = 0x43fb71u; native_call(m, 0x41edf0u);	/* 43fb6c: call 0x41edf0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fb71: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43fb74: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 43fb76: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43fb77: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43fb78: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fb79: add esp, 0x1c */
	m->esp += 4 + 16; return;	/* 43fb7c: ret 0x10 */
L_43fb7f:
	m->esp -= 4; M32(m->esp) = 0x43fb84u; native_call(m, 0x41e610u);	/* 43fb7f: call 0x41e610 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43fb84: test eax, eax */
	if (!m->zf) goto L_43fba0;	/* 43fb86: jne 0x43fba0 */
	{ DWORD v_ = 0x4b04b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fb88: push 0x4b04b0 */
	m->esp -= 4; M32(m->esp) = 0x43fb92u; native_call(m, 0x41edf0u);	/* 43fb8d: call 0x41edf0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fb92: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43fb95: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 43fb97: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43fb98: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43fb99: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fb9a: add esp, 0x1c */
	m->esp += 4 + 16; return;	/* 43fb9d: ret 0x10 */
L_43fba0:
	m->esp -= 4; M32(m->esp) = 0x43fba5u; native_call(m, 0x41e670u);	/* 43fba0: call 0x41e670 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43fba5: test eax, eax */
	if (!m->zf) goto L_43fbc1;	/* 43fba7: jne 0x43fbc1 */
	{ DWORD v_ = 0x4b04b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fba9: push 0x4b04b0 */
	m->esp -= 4; M32(m->esp) = 0x43fbb3u; native_call(m, 0x41edf0u);	/* 43fbae: call 0x41edf0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fbb3: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43fbb6: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 43fbb8: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43fbb9: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43fbba: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fbbb: add esp, 0x1c */
	m->esp += 4 + 16; return;	/* 43fbbe: ret 0x10 */
L_43fbc1:
	{ DWORD v_ = 0x4b2854u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fbc1: push 0x4b2854 */
	{ DWORD v_ = 0x4b2834u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fbc6: push 0x4b2834 */
	m->esp -= 4; M32(m->esp) = 0x43fbcdu; native_call(m, m->esi);	/* 43fbcb: call esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43fbcd: test eax, eax */
	if (m->zf) goto L_43fbda;	/* 43fbcf: je 0x43fbda */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fbd1: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fbd3: push 0 */
	{ DWORD v_ = 0x12u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fbd5: push 0x12 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43fbd7: push eax */
	m->esp -= 4; M32(m->esp) = 0x43fbdau; native_call(m, m->ebx);	/* 43fbd8: call ebx */
L_43fbda:
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 43fbda: mov edx, dword ptr [esp + 0x38] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 43fbde: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43fbe2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43fbe3: push eax */
	m->esp -= 4; M32(m->esp) = 0x43fbe9u; native_call(m, 0x43fcc0u);	/* 43fbe4: call 0x43fcc0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fbe9: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43fbec: test eax, eax */
	if (!m->zf) goto L_43fc13;	/* 43fbee: jne 0x43fc13 */
	m->ecx = M32((DWORD)(0x4ded18u));	/* 43fbf0: mov ecx, dword ptr [0x4ded18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43fbf6: push eax */
	{ DWORD v_ = 0x4b141cu; m->esp -= 4; M32(m->esp) = v_; }	/* 43fbf7: push 0x4b141c */
	{ DWORD v_ = 0x4b29ecu; m->esp -= 4; M32(m->esp) = v_; }	/* 43fbfc: push 0x4b29ec */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43fc01: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43fc08u; native_call(m, M32(0x4a9324u));	/* 43fc02: call dword ptr [0x4a9324] */
	m->edi = M32(m->esp); m->esp += 4;	/* 43fc08: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43fc09: pop esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43fc0a: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43fc0c: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fc0d: add esp, 0x1c */
	m->esp += 4 + 16; return;	/* 43fc10: ret 0x10 */
L_43fc13:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fc13: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fc15: push 0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fc17: push 1 */
	{ DWORD v_ = 0x61u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fc19: push 0x61 */
	M32((DWORD)(0x4b2790u)) = 0x1u;	/* 43fc1b: mov dword ptr [0x4b2790], 1 */
	m->esp -= 4; M32(m->esp) = 0x43fc2bu; native_call(m, M32(0x4a92d0u));	/* 43fc25: call dword ptr [0x4a92d0] */
	m->eax = M32((DWORD)(0x4b2790u));	/* 43fc2b: mov eax, dword ptr [0x4b2790] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43fc30: test eax, eax */
	if (m->zf) goto L_43fcb1;	/* 43fc32: je 0x43fcb1 */
	m->esi = M32((DWORD)(0x4a92d4u));	/* 43fc34: mov esi, dword ptr [0x4a92d4] */
	m->edi = M32((DWORD)(0x4a92d8u));	/* 43fc3a: mov edi, dword ptr [0x4a92d8] */
	m->ebx = M32((DWORD)(0x4a9348u));	/* 43fc40: mov ebx, dword ptr [0x4a9348] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 43fc46: push ebp */
	m->ebp = M32((DWORD)(0x4a934cu));	/* 43fc47: mov ebp, dword ptr [0x4a934c] */
L_43fc4d:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fc4d: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fc4f: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fc51: push 0 */
	m->edx = (DWORD)(m->esp + 0x1cu);	/* 43fc53: lea edx, [esp + 0x1c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fc57: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43fc59: push edx */
	m->esp -= 4; M32(m->esp) = 0x43fc5cu; native_call(m, m->esi);	/* 43fc5a: call esi */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43fc5c: cmp eax, 1 */
	if (!m->zf) goto L_43fc9d;	/* 43fc5f: jne 0x43fc9d */
L_43fc61:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fc61: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fc63: push 0 */
	m->eax = (DWORD)(m->esp + 0x18u);	/* 43fc65: lea eax, [esp + 0x18] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fc69: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43fc6b: push eax */
	m->esp -= 4; M32(m->esp) = 0x43fc6eu; native_call(m, m->edi);	/* 43fc6c: call edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43fc6e: test eax, eax */
	if (m->zf) goto L_43fc89;	/* 43fc70: je 0x43fc89 */
	m->eax = M32((DWORD)(0x68039cu));	/* 43fc72: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43fc77: test eax, eax */
	if (m->zf) goto L_43fc82;	/* 43fc79: je 0x43fc82 */
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 43fc7b: lea ecx, [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43fc7f: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43fc82u; native_call(m, m->ebx);	/* 43fc80: call ebx */
L_43fc82:
	m->edx = (DWORD)(m->esp + 0x10u);	/* 43fc82: lea edx, [esp + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43fc86: push edx */
	m->esp -= 4; M32(m->esp) = 0x43fc89u; native_call(m, m->ebp);	/* 43fc87: call ebp */
L_43fc89:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fc89: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fc8b: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fc8d: push 0 */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 43fc8f: lea eax, [esp + 0x1c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fc93: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43fc95: push eax */
	m->esp -= 4; M32(m->esp) = 0x43fc98u; native_call(m, m->esi);	/* 43fc96: call esi */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43fc98: cmp eax, 1 */
	if (m->zf) goto L_43fc61;	/* 43fc9b: je 0x43fc61 */
L_43fc9d:
	m->esp -= 4; M32(m->esp) = 0x43fca2u; native_call(m, 0x43f980u);	/* 43fc9d: call 0x43f980 */
	m->esp -= 4; M32(m->esp) = 0x43fca7u; native_call(m, 0x4202d0u);	/* 43fca2: call 0x4202d0 */
	m->eax = M32((DWORD)(0x4b2790u));	/* 43fca7: mov eax, dword ptr [0x4b2790] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43fcac: test eax, eax */
	if (!m->zf) goto L_43fc4d;	/* 43fcae: jne 0x43fc4d */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43fcb0: pop ebp */
L_43fcb1:
	m->edi = M32(m->esp); m->esp += 4;	/* 43fcb1: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43fcb2: pop esi */
	m->eax = 0x1u;	/* 43fcb3: mov eax, 1 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43fcb8: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fcb9: add esp, 0x1c */
	m->esp += 4 + 16; return;	/* 43fcbc: ret 0x10 */
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
