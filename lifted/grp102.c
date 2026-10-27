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

static void lift_453fd0(X86 *m);
static void lift_4549a0(X86 *m);
static void lift_4549c0(X86 *m);
static void lift_454ac0(X86 *m);
static void lift_454ae0(X86 *m);
static void lift_454bd0(X86 *m);
static void lift_454bf0(X86 *m);
static void lift_454ce0(X86 *m);
static void lift_454d00(X86 *m);
static void lift_453260(X86 *m);
static void lift_453920(X86 *m);

/* dplay_release (0x453920), lifted by tools/lift.py */
static void lift_453920(X86 *m)
{
	m->eax = M32((DWORD)(0xa0b398u));	/* 453920: mov eax, dword ptr [0xa0b398] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 453925: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 453926: push ebp */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 453927: xor ebp, ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 453929: push esi */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45392a: cmp eax, ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45392c: push edi */
	if (m->zf) goto L_45393b;	/* 45392d: je 0x45393b */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 45392f: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 453931: push eax */
	m->esp -= 4; M32(m->esp) = 0x453935u; native_call(m, M32((DWORD)(m->ecx + 0x8u)));	/* 453932: call dword ptr [ecx + 8] */
	M32((DWORD)(0xa0b398u)) = m->ebp;	/* 453935: mov dword ptr [0xa0b398], ebp */
L_45393b:
	m->eax = M32((DWORD)(0xa0b404u));	/* 45393b: mov eax, dword ptr [0xa0b404] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 453940: cmp eax, ebp */
	if (m->zf) goto L_453977;	/* 453942: je 0x453977 */
	m->ecx = M32((DWORD)(0xa0b424u));	/* 453944: mov ecx, dword ptr [0xa0b424] */
	{ DWORD a_ = m->ecx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45394a: cmp ecx, ebp */
	if (m->zf) goto L_453960;	/* 45394c: je 0x453960 */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 45394e: mov edx, dword ptr [eax] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 453950: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 453951: push eax */
	m->esp -= 4; M32(m->esp) = 0x453955u; native_call(m, M32((DWORD)(m->edx + 0x24u)));	/* 453952: call dword ptr [edx + 0x24] */
	m->eax = M32((DWORD)(0xa0b404u));	/* 453955: mov eax, dword ptr [0xa0b404] */
	M32((DWORD)(0xa0b424u)) = m->ebp;	/* 45395a: mov dword ptr [0xa0b424], ebp */
L_453960:
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 453960: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 453962: push eax */
	m->esp -= 4; M32(m->esp) = 0x453966u; native_call(m, M32((DWORD)(m->ecx + 0x10u)));	/* 453963: call dword ptr [ecx + 0x10] */
	m->eax = M32((DWORD)(0xa0b404u));	/* 453966: mov eax, dword ptr [0xa0b404] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45396b: push eax */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 45396c: mov edx, dword ptr [eax] */
	m->esp -= 4; M32(m->esp) = 0x453971u; native_call(m, M32((DWORD)(m->edx + 0x8u)));	/* 45396e: call dword ptr [edx + 8] */
	M32((DWORD)(0xa0b404u)) = m->ebp;	/* 453971: mov dword ptr [0xa0b404], ebp */
L_453977:
	m->eax = M32((DWORD)(0xa0baf0u));	/* 453977: mov eax, dword ptr [0xa0baf0] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45397c: cmp eax, ebp */
	if (m->zf) goto L_45398f;	/* 45397e: je 0x45398f */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 453980: push eax */
	m->esp -= 4; M32(m->esp) = 0x453986u; native_call(m, 0x49ee81u);	/* 453981: call 0x49ee81 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453986: add esp, 4 */
	M32((DWORD)(0xa0baf0u)) = m->ebp;	/* 453989: mov dword ptr [0xa0baf0], ebp */
L_45398f:
	m->eax = M32((DWORD)(0xa0bab0u));	/* 45398f: mov eax, dword ptr [0xa0bab0] */
	m->edi = M32((DWORD)(0x4a918cu));	/* 453994: mov edi, dword ptr [0x4a918c] */
	m->esi = M32((DWORD)(0x4a9078u));	/* 45399a: mov esi, dword ptr [0x4a9078] */
	m->ebx = M32((DWORD)(0x4a9190u));	/* 4539a0: mov ebx, dword ptr [0x4a9190] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4539a6: cmp eax, ebp */
	if (m->zf) goto L_4539bb;	/* 4539a8: je 0x4539bb */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4539aa: push eax */
	m->esp -= 4; M32(m->esp) = 0x4539adu; native_call(m, m->esi);	/* 4539ab: call esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4539ad: push eax */
	m->esp -= 4; M32(m->esp) = 0x4539b0u; native_call(m, m->edi);	/* 4539ae: call edi */
	m->eax = M32((DWORD)(0xa0bab0u));	/* 4539b0: mov eax, dword ptr [0xa0bab0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4539b5: push eax */
	m->esp -= 4; M32(m->esp) = 0x4539b8u; native_call(m, m->esi);	/* 4539b6: call esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4539b8: push eax */
	m->esp -= 4; M32(m->esp) = 0x4539bbu; native_call(m, m->ebx);	/* 4539b9: call ebx */
L_4539bb:
	m->eax = M32((DWORD)(0xa0baf4u));	/* 4539bb: mov eax, dword ptr [0xa0baf4] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4539c0: cmp eax, ebp */
	if (m->zf) goto L_4539dc;	/* 4539c2: je 0x4539dc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4539c4: push eax */
	m->esp -= 4; M32(m->esp) = 0x4539c7u; native_call(m, m->esi);	/* 4539c5: call esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4539c7: push eax */
	m->esp -= 4; M32(m->esp) = 0x4539cau; native_call(m, m->edi);	/* 4539c8: call edi */
	m->ecx = M32((DWORD)(0xa0baf4u));	/* 4539ca: mov ecx, dword ptr [0xa0baf4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4539d0: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4539d3u; native_call(m, m->esi);	/* 4539d1: call esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4539d3: push eax */
	m->esp -= 4; M32(m->esp) = 0x4539d6u; native_call(m, m->ebx);	/* 4539d4: call ebx */
	M32((DWORD)(0xa0baf4u)) = m->ebp;	/* 4539d6: mov dword ptr [0xa0baf4], ebp */
L_4539dc:
	m->esp -= 4; M32(m->esp) = 0x4539e2u; native_call(m, M32(0x4a93b8u));	/* 4539dc: call dword ptr [0x4a93b8] */
	m->edi = M32(m->esp); m->esp += 4;	/* 4539e2: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4539e3: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4539e4: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4539e5: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4539e7: pop ebx */
	m->esp += 4 + 0; return;	/* 4539e8: ret  */
}

/* dplay_enumSessions (0x453fd0), lifted by tools/lift.py */
static void lift_453fd0(X86 *m)
{
	m->edx = M32((DWORD)(0xa0b404u));	/* 453fd0: mov edx, dword ptr [0xa0b404] */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453fd6: sub esp, 0x50 */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 453fd9: test edx, edx */
	if (!m->zf) goto L_453fe3;	/* 453fdb: jne 0x453fe3 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 453fdd: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453fdf: add esp, 0x50 */
	m->esp += 4 + 0; return;	/* 453fe2: ret  */
L_453fe3:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 453fe3: push edi */
	m->ecx = 0x14u;	/* 453fe4: mov ecx, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 453fe9: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x4u);	/* 453feb: lea edi, [esp + 4] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 453fef: rep stosd dword ptr es:[edi], eax */
	m->eax = M32((DWORD)(0xa0bad8u));	/* 453ff1: mov eax, dword ptr [0xa0bad8] */
	M32((DWORD)(m->esp + 0x4u)) = 0x50u;	/* 453ff6: mov dword ptr [esp + 4], 0x50 */
	m->edi = M32(m->esp); m->esp += 4;	/* 453ffe: pop edi */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 453fff: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x8u)) = m->ecx;	/* 454001: mov dword ptr [esp + 8], ecx */
	m->ecx = M32((DWORD)(m->eax + 0x4u));	/* 454005: mov ecx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0xcu)) = m->ecx;	/* 454008: mov dword ptr [esp + 0xc], ecx */
	m->ecx = M32((DWORD)(m->eax + 0x8u));	/* 45400c: mov ecx, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 45400f: mov dword ptr [esp + 0x10], ecx */
	m->ecx = M32((DWORD)(0x4a96e8u));	/* 454013: mov ecx, dword ptr [0x4a96e8] */
	m->eax = M32((DWORD)(m->eax + 0xcu));	/* 454019: mov eax, dword ptr [eax + 0xc] */
	M32((DWORD)(m->esp + 0x18u)) = m->ecx;	/* 45401c: mov dword ptr [esp + 0x18], ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 454020: mov dword ptr [esp + 0x14], eax */
	m->eax = M32((DWORD)(0x4a96ecu));	/* 454024: mov eax, dword ptr [0x4a96ec] */
	m->ecx = M32((DWORD)(0x4a96f0u));	/* 454029: mov ecx, dword ptr [0x4a96f0] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 45402f: mov dword ptr [esp + 0x1c], eax */
	m->eax = M32((DWORD)(0x4a96f4u));	/* 454033: mov eax, dword ptr [0x4a96f4] */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 454038: mov dword ptr [esp + 0x20], ecx */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 45403c: mov dword ptr [esp + 0x24], eax */
	m->eax = M32((DWORD)(0xa0b418u));	/* 454040: mov eax, dword ptr [0xa0b418] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454045: test eax, eax */
	if (!m->zf) goto L_45406f;	/* 454047: jne 0x45406f */
	m->ecx = M32((DWORD)(m->edx + 0x0u));	/* 454049: mov ecx, dword ptr [edx] */
	{ DWORD v_ = 0x12u; m->esp -= 4; M32(m->esp) = v_; }	/* 45404b: push 0x12 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45404d: push 0 */
	{ DWORD v_ = 0x453560u; m->esp -= 4; M32(m->esp) = v_; }	/* 45404f: push 0x453560 */
	m->eax = (DWORD)(m->esp + 0xcu);	/* 454054: lea eax, [esp + 0xc] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 454058: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45405a: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45405b: push edx */
	m->esp -= 4; M32(m->esp) = 0x45405fu; native_call(m, M32((DWORD)(m->ecx + 0x34u)));	/* 45405c: call dword ptr [ecx + 0x34] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45405f: test eax, eax */
	if (m->sf == m->of) goto L_454069;	/* 454061: jge 0x454069 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 454063: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 454065: add esp, 0x50 */
	m->esp += 4 + 0; return;	/* 454068: ret  */
L_454069:
	m->edx = M32((DWORD)(0xa0b404u));	/* 454069: mov edx, dword ptr [0xa0b404] */
L_45406f:
	{ DWORD a_ = M32((DWORD)(0xa0b418u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45406f: cmp dword ptr [0xa0b418], 1 */
	if (!m->zf) goto L_454098;	/* 454076: jne 0x454098 */
	m->ecx = M32((DWORD)(m->edx + 0x0u));	/* 454078: mov ecx, dword ptr [edx] */
	{ DWORD v_ = 0x12u; m->esp -= 4; M32(m->esp) = v_; }	/* 45407a: push 0x12 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45407c: push 0 */
	{ DWORD v_ = 0x453560u; m->esp -= 4; M32(m->esp) = v_; }	/* 45407e: push 0x453560 */
	m->eax = (DWORD)(m->esp + 0xcu);	/* 454083: lea eax, [esp + 0xc] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 454087: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454089: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45408a: push edx */
	m->esp -= 4; M32(m->esp) = 0x45408eu; native_call(m, M32((DWORD)(m->ecx + 0x34u)));	/* 45408b: call dword ptr [ecx + 0x34] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45408e: test eax, eax */
	if (m->sf == m->of) goto L_454098;	/* 454090: jge 0x454098 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 454092: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 454094: add esp, 0x50 */
	m->esp += 4 + 0; return;	/* 454097: ret  */
L_454098:
	m->eax = 0x1u;	/* 454098: mov eax, 1 */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45409d: add esp, 0x50 */
	m->esp += 4 + 0; return;	/* 4540a0: ret  */
}

/* arena_4549a0 (0x4549a0), lifted by tools/lift.py */
static void lift_4549a0(X86 *m)
{
	m->eax = M32((DWORD)(0xa0d7a4u));	/* 4549a0: mov eax, dword ptr [0xa0d7a4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4549a5: test eax, eax */
	if (m->zf) goto L_4549b8;	/* 4549a7: je 0x4549b8 */
	M32((DWORD)(0xa0d7a4u)) = 0x0u;	/* 4549a9: mov dword ptr [0xa0d7a4], 0 */
	lift_453920(m); return;	/* 4549b3: jmp 0x453920 */
L_4549b8:
	m->esp += 4 + 0; return;	/* 4549b8: ret  */
}

/* arena_4549c0 (0x4549c0), lifted by tools/lift.py */
static void lift_4549c0(X86 *m)
{
	m->eax = M32((DWORD)(0xa0d7a4u));	/* 4549c0: mov eax, dword ptr [0xa0d7a4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4549c5: test eax, eax */
	if (m->zf) goto L_4549ce;	/* 4549c7: je 0x4549ce */
	lift_453fd0(m); return;	/* 4549c9: jmp 0x453fd0 */
L_4549ce:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4549ce: xor eax, eax */
	m->esp += 4 + 0; return;	/* 4549d0: ret  */
}

/* arena_454ac0 (0x454ac0), lifted by tools/lift.py */
static void lift_454ac0(X86 *m)
{
	m->eax = M32((DWORD)(0xa0d7a8u));	/* 454ac0: mov eax, dword ptr [0xa0d7a8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454ac5: test eax, eax */
	if (m->zf) goto L_454ad8;	/* 454ac7: je 0x454ad8 */
	M32((DWORD)(0xa0d7a8u)) = 0x0u;	/* 454ac9: mov dword ptr [0xa0d7a8], 0 */
	lift_453920(m); return;	/* 454ad3: jmp 0x453920 */
L_454ad8:
	m->esp += 4 + 0; return;	/* 454ad8: ret  */
}

/* arena_454ae0 (0x454ae0), lifted by tools/lift.py */
static void lift_454ae0(X86 *m)
{
	m->eax = M32((DWORD)(0xa0d7a8u));	/* 454ae0: mov eax, dword ptr [0xa0d7a8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454ae5: test eax, eax */
	if (m->zf) goto L_454aee;	/* 454ae7: je 0x454aee */
	lift_453fd0(m); return;	/* 454ae9: jmp 0x453fd0 */
L_454aee:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 454aee: xor eax, eax */
	m->esp += 4 + 0; return;	/* 454af0: ret  */
}

/* arena_454bd0 (0x454bd0), lifted by tools/lift.py */
static void lift_454bd0(X86 *m)
{
	m->eax = M32((DWORD)(0xa0d7acu));	/* 454bd0: mov eax, dword ptr [0xa0d7ac] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454bd5: test eax, eax */
	if (m->zf) goto L_454be8;	/* 454bd7: je 0x454be8 */
	M32((DWORD)(0xa0d7acu)) = 0x0u;	/* 454bd9: mov dword ptr [0xa0d7ac], 0 */
	lift_453920(m); return;	/* 454be3: jmp 0x453920 */
L_454be8:
	m->esp += 4 + 0; return;	/* 454be8: ret  */
}

/* arena_454bf0 (0x454bf0), lifted by tools/lift.py */
static void lift_454bf0(X86 *m)
{
	m->eax = M32((DWORD)(0xa0d7acu));	/* 454bf0: mov eax, dword ptr [0xa0d7ac] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454bf5: test eax, eax */
	if (m->zf) goto L_454bfe;	/* 454bf7: je 0x454bfe */
	lift_453fd0(m); return;	/* 454bf9: jmp 0x453fd0 */
L_454bfe:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 454bfe: xor eax, eax */
	m->esp += 4 + 0; return;	/* 454c00: ret  */
}

/* arena_454ce0 (0x454ce0), lifted by tools/lift.py */
static void lift_454ce0(X86 *m)
{
	m->eax = M32((DWORD)(0xa0d7b0u));	/* 454ce0: mov eax, dword ptr [0xa0d7b0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454ce5: test eax, eax */
	if (m->zf) goto L_454cf8;	/* 454ce7: je 0x454cf8 */
	M32((DWORD)(0xa0d7b0u)) = 0x0u;	/* 454ce9: mov dword ptr [0xa0d7b0], 0 */
	lift_453920(m); return;	/* 454cf3: jmp 0x453920 */
L_454cf8:
	m->esp += 4 + 0; return;	/* 454cf8: ret  */
}

/* arena_454d00 (0x454d00), lifted by tools/lift.py */
static void lift_454d00(X86 *m)
{
	m->eax = M32((DWORD)(0xa0d7b0u));	/* 454d00: mov eax, dword ptr [0xa0d7b0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454d05: test eax, eax */
	if (m->zf) goto L_454d0e;	/* 454d07: je 0x454d0e */
	lift_453fd0(m); return;	/* 454d09: jmp 0x453fd0 */
L_454d0e:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 454d0e: xor eax, eax */
	m->esp += 4 + 0; return;	/* 454d10: ret  */
}

/* arena_453260 (0x453260), lifted by tools/lift.py */
static void lift_453260(X86 *m)
{
	m->eax = M32((DWORD)(0xa0b418u));	/* 453260: mov eax, dword ptr [0xa0b418] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 453265: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_453285;	/* 453268: ja 0x453285 */
	switch (m->eax) { case 0: goto L_453271; case 1: goto L_453276; case 2: goto L_45327b; case 3: goto L_453280; default: abort(); }	/* 45326a: jmp dword ptr [eax*4 + 0x453288] */
L_453271:
	lift_4549c0(m); return;	/* 453271: jmp 0x4549c0 */
L_453276:
	lift_454ae0(m); return;	/* 453276: jmp 0x454ae0 */
L_45327b:
	lift_454bf0(m); return;	/* 45327b: jmp 0x454bf0 */
L_453280:
	lift_454d00(m); return;	/* 453280: jmp 0x454d00 */
L_453285:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 453285: xor eax, eax */
	m->esp += 4 + 0; return;	/* 453287: ret  */
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
