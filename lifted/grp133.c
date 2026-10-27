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

static void lift_406200(X86 *m);
static void lift_4052c0(X86 *m);
static void lift_4057a0(X86 *m);
static void lift_406c30(X86 *m);
static void lift_4079c0(X86 *m);
static void lift_4355b0(X86 *m);
static void lift_405b80(X86 *m);
static void lift_434dd0(X86 *m);

/* room_434dd0 (0x434dd0), lifted by tools/lift.py */
static void lift_434dd0(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 434dd0: push esi */
	m->esi = M32((DWORD)(m->esp + 0x8u));	/* 434dd1: mov esi, dword ptr [esp + 8] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 434dd5: push edi */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 434dd6: xor edi, edi */
	m->eax = (DWORD)(m->esi + m->esi*8 + 0x0u);	/* 434dd8: lea eax, [esi + esi*8] */
	M32((DWORD)(0x9dd56cu)) = m->edi;	/* 434ddb: mov dword ptr [0x9dd56c], edi */
	m->ecx = (DWORD)(m->esi + m->eax*4 + 0x0u);	/* 434de1: lea ecx, [esi + eax*4] */
	m->edx = (DWORD)(m->ecx*2 + 0x9087efu);	/* 434de4: lea edx, [ecx*2 + 0x9087ef] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 434deb: push edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 434dec: push edi */
	m->esp -= 4; M32(m->esp) = 0x434df2u; native_call(m, 0x452ec0u);	/* 434ded: call 0x452ec0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 434df2: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 434df5: test eax, eax */
	if (!m->zf) goto L_434e0b;	/* 434df7: jne 0x434e0b */
	{ DWORD v_ = 0x3fu; m->esp -= 4; M32(m->esp) = v_; }	/* 434df9: push 0x3f */
	m->esp -= 4; M32(m->esp) = 0x434e00u; native_call(m, 0x41ee40u);	/* 434dfb: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 434e00: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x434e08u; native_call(m, 0x452fe0u);	/* 434e03: call 0x452fe0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 434e08: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 434e09: pop esi */
	m->esp += 4 + 0; return;	/* 434e0a: ret  */
L_434e0b:
	M32((DWORD)(0x4db710u)) = m->esi;	/* 434e0b: mov dword ptr [0x4db710], esi */
	m->esp -= 4; M32(m->esp) = 0x434e16u; native_call(m, 0x453260u);	/* 434e11: call 0x453260 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 434e16: test eax, eax */
	if (!m->zf) goto L_434e2c;	/* 434e18: jne 0x434e2c */
	{ DWORD v_ = 0x40u; m->esp -= 4; M32(m->esp) = v_; }	/* 434e1a: push 0x40 */
	m->esp -= 4; M32(m->esp) = 0x434e21u; native_call(m, 0x41ee40u);	/* 434e1c: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 434e21: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x434e29u; native_call(m, 0x452fe0u);	/* 434e24: call 0x452fe0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 434e29: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 434e2a: pop esi */
	m->esp += 4 + 0; return;	/* 434e2b: ret  */
L_434e2c:
	m->eax = M32((DWORD)(0x4ded18u));	/* 434e2c: mov eax, dword ptr [0x4ded18] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 434e31: push edi */
	{ DWORD v_ = 0x7d0u; m->esp -= 4; M32(m->esp) = v_; }	/* 434e32: push 0x7d0 */
	{ DWORD v_ = 0x378u; m->esp -= 4; M32(m->esp) = v_; }	/* 434e37: push 0x378 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 434e3c: push eax */
	M32((DWORD)(0x4dbb10u)) = m->edi;	/* 434e3d: mov dword ptr [0x4dbb10], edi */
	M32((DWORD)(0x4db8b4u)) = 0x1u;	/* 434e43: mov dword ptr [0x4db8b4], 1 */
	M32((DWORD)(0x4dbb78u)) = m->edi;	/* 434e4d: mov dword ptr [0x4dbb78], edi */
	M32((DWORD)(0x4db708u)) = m->edi;	/* 434e53: mov dword ptr [0x4db708], edi */
	m->esp -= 4; M32(m->esp) = 0x434e5fu; native_call(m, M32(0x4a9334u));	/* 434e59: call dword ptr [0x4a9334] */
	m->edi = M32(m->esp); m->esp += 4;	/* 434e5f: pop edi */
	M32((DWORD)(0xa0bad0u)) = m->eax;	/* 434e60: mov dword ptr [0xa0bad0], eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 434e65: pop esi */
	m->esp += 4 + 0; return;	/* 434e66: ret  */
}

/* arena_406200 (0x406200), lifted by tools/lift.py */
static void lift_406200(X86 *m)
{
	m->eax = M32((DWORD)(0x4dba84u));	/* 406200: mov eax, dword ptr [0x4dba84] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 406205: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 406206: push edi */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 406207: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406209: cmp eax, edi */
	M32((DWORD)(0x4dbbecu)) = m->edi;	/* 40620b: mov dword ptr [0x4dbbec], edi */
	M32((DWORD)(0x4dbbf0u)) = m->edi;	/* 406211: mov dword ptr [0x4dbbf0], edi */
	if (m->zf) goto L_40621e;	/* 406217: je 0x40621e */
	m->esp -= 4; M32(m->esp) = 0x40621eu; native_call(m, 0x452fe0u);	/* 406219: call 0x452fe0 */
L_40621e:
	m->esi = M32((DWORD)(m->esp + 0xcu));	/* 40621e: mov esi, dword ptr [esp + 0xc] */
	{ DWORD a_ = m->esi, b_ = 0x1869fu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406222: cmp esi, 0x1869f */
	if (!m->zf) goto L_406231;	/* 406228: jne 0x406231 */
	{ DWORD v_ = 0x4dbbd4u; m->esp -= 4; M32(m->esp) = v_; }	/* 40622a: push 0x4dbbd4 */
	goto L_40623f;	/* 40622f: jmp 0x40623f */
L_406231:
	m->eax = (DWORD)(m->esi + m->esi*8 + 0x0u);	/* 406231: lea eax, [esi + esi*8] */
	m->ecx = (DWORD)(m->esi + m->eax*4 + 0x0u);	/* 406234: lea ecx, [esi + eax*4] */
	m->edx = (DWORD)(m->ecx*2 + 0x9087efu);	/* 406237: lea edx, [ecx*2 + 0x9087ef] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40623e: push edx */
L_40623f:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40623f: push edi */
	m->esp -= 4; M32(m->esp) = 0x406245u; native_call(m, 0x452ec0u);	/* 406240: call 0x452ec0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 406245: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406248: cmp eax, edi */
	if (!m->zf) goto L_40625e;	/* 40624a: jne 0x40625e */
	{ DWORD v_ = 0x3fu; m->esp -= 4; M32(m->esp) = v_; }	/* 40624c: push 0x3f */
	m->esp -= 4; M32(m->esp) = 0x406253u; native_call(m, 0x41ee40u);	/* 40624e: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 406253: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x40625bu; native_call(m, 0x452fe0u);	/* 406256: call 0x452fe0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 40625b: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 40625c: pop esi */
	m->esp += 4 + 0; return;	/* 40625d: ret  */
L_40625e:
	M32((DWORD)(0x4db710u)) = m->esi;	/* 40625e: mov dword ptr [0x4db710], esi */
	m->esp -= 4; M32(m->esp) = 0x406269u; native_call(m, 0x453260u);	/* 406264: call 0x453260 */
	m->eax = M32((DWORD)(0x4ded18u));	/* 406269: mov eax, dword ptr [0x4ded18] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40626e: push edi */
	{ DWORD v_ = 0x7d0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40626f: push 0x7d0 */
	{ DWORD v_ = 0x378u; m->esp -= 4; M32(m->esp) = v_; }	/* 406274: push 0x378 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 406279: push eax */
	M32((DWORD)(0x4dbb10u)) = m->edi;	/* 40627a: mov dword ptr [0x4dbb10], edi */
	M32((DWORD)(0x4db8b4u)) = 0x1u;	/* 406280: mov dword ptr [0x4db8b4], 1 */
	M32((DWORD)(0x4dbb78u)) = m->edi;	/* 40628a: mov dword ptr [0x4dbb78], edi */
	M32((DWORD)(0x4db708u)) = m->edi;	/* 406290: mov dword ptr [0x4db708], edi */
	m->esp -= 4; M32(m->esp) = 0x40629cu; native_call(m, M32(0x4a9334u));	/* 406296: call dword ptr [0x4a9334] */
	m->edi = M32(m->esp); m->esp += 4;	/* 40629c: pop edi */
	M32((DWORD)(0xa0bad0u)) = m->eax;	/* 40629d: mov dword ptr [0xa0bad0], eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 4062a2: pop esi */
	m->esp += 4 + 0; return;	/* 4062a3: ret  */
}

/* lobby_roomNameCheck (0x4052c0), lifted by tools/lift.py */
static void lift_4052c0(X86 *m)
{
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4052c0: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4052c1: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4052c2: push edi */
	m->edi = M32((DWORD)(0x67ef04u));	/* 4052c3: mov edi, dword ptr [0x67ef04] */
	m->ebp = 0x1u;	/* 4052c9: mov ebp, 1 */
	M32((DWORD)(0x67ef14u)) = m->ebp;	/* 4052ce: mov dword ptr [0x67ef14], ebp */
	M32((DWORD)(0x67ef04u)) = m->ebp;	/* 4052d4: mov dword ptr [0x67ef04], ebp */
	m->esp -= 4; M32(m->esp) = 0x4052dfu; native_call(m, 0x405140u);	/* 4052da: call 0x405140 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4052df: push 0 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4052e1: push ebp */
	m->esp -= 4; M32(m->esp) = 0x4052e7u; native_call(m, 0x452ec0u);	/* 4052e2: call 0x452ec0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4052e7: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4052ea: test eax, eax */
	if (m->zf) goto L_4055fe;	/* 4052ec: je 0x4055fe */
	m->esi = 0x4ad554u;	/* 4052f2: mov esi, 0x4ad554 */
	m->eax = 0x4ded20u;	/* 4052f7: mov eax, 0x4ded20 */
L_4052fc:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 4052fc: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4052fe: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405300: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_405320;	/* 405302: jne 0x405320 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405304: test cl, cl */
	if (m->zf) goto L_40531c;	/* 405306: je 0x40531c */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 405308: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 40530b: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40530d: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_405320;	/* 405310: jne 0x405320 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 405312: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 405315: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405318: test cl, cl */
	if (!m->zf) goto L_4052fc;	/* 40531a: jne 0x4052fc */
L_40531c:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40531c: xor eax, eax */
	goto L_405325;	/* 40531e: jmp 0x405325 */
L_405320:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405320: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405322: sbb eax, -1 */
L_405325:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 405325: test eax, eax */
	if (m->zf) goto L_4053d2;	/* 405327: je 0x4053d2 */
	m->esi = 0x4ad548u;	/* 40532d: mov esi, 0x4ad548 */
	m->eax = 0x4ded20u;	/* 405332: mov eax, 0x4ded20 */
L_405337:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 405337: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405339: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40533b: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_40535b;	/* 40533d: jne 0x40535b */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40533f: test cl, cl */
	if (m->zf) goto L_405357;	/* 405341: je 0x405357 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 405343: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405346: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405348: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_40535b;	/* 40534b: jne 0x40535b */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40534d: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 405350: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405353: test cl, cl */
	if (!m->zf) goto L_405337;	/* 405355: jne 0x405337 */
L_405357:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 405357: xor eax, eax */
	goto L_405360;	/* 405359: jmp 0x405360 */
L_40535b:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 40535b: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 40535d: sbb eax, -1 */
L_405360:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 405360: test eax, eax */
	if (m->zf) goto L_4053d2;	/* 405362: je 0x4053d2 */
	m->esi = 0x4ad53cu;	/* 405364: mov esi, 0x4ad53c */
	m->eax = 0x4ded20u;	/* 405369: mov eax, 0x4ded20 */
L_40536e:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 40536e: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405370: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405372: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_405392;	/* 405374: jne 0x405392 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405376: test cl, cl */
	if (m->zf) goto L_40538e;	/* 405378: je 0x40538e */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 40537a: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 40537d: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40537f: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_405392;	/* 405382: jne 0x405392 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 405384: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 405387: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40538a: test cl, cl */
	if (!m->zf) goto L_40536e;	/* 40538c: jne 0x40536e */
L_40538e:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40538e: xor eax, eax */
	goto L_405397;	/* 405390: jmp 0x405397 */
L_405392:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405392: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405394: sbb eax, -1 */
L_405397:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 405397: test eax, eax */
	if (m->zf) goto L_4053d2;	/* 405399: je 0x4053d2 */
	m->esi = 0x4ad530u;	/* 40539b: mov esi, 0x4ad530 */
	m->eax = 0x4ded20u;	/* 4053a0: mov eax, 0x4ded20 */
L_4053a5:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 4053a5: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4053a7: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4053a9: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_4053c9;	/* 4053ab: jne 0x4053c9 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4053ad: test cl, cl */
	if (m->zf) goto L_4053c5;	/* 4053af: je 0x4053c5 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 4053b1: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4053b4: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4053b6: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_4053c9;	/* 4053b9: jne 0x4053c9 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4053bb: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4053be: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4053c1: test cl, cl */
	if (!m->zf) goto L_4053a5;	/* 4053c3: jne 0x4053a5 */
L_4053c5:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4053c5: xor eax, eax */
	goto L_4053ce;	/* 4053c7: jmp 0x4053ce */
L_4053c9:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4053c9: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4053cb: sbb eax, -1 */
L_4053ce:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4053ce: test eax, eax */
	if (!m->zf) goto L_4053d9;	/* 4053d0: jne 0x4053d9 */
L_4053d2:
	M8((DWORD)(0x4ded40u)) = (BYTE)(0x18u);	/* 4053d2: mov byte ptr [0x4ded40], 0x18 */
L_4053d9:
	m->esi = 0x4ad524u;	/* 4053d9: mov esi, 0x4ad524 */
	m->eax = 0x4ded20u;	/* 4053de: mov eax, 0x4ded20 */
L_4053e3:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 4053e3: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4053e5: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4053e7: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_405407;	/* 4053e9: jne 0x405407 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4053eb: test cl, cl */
	if (m->zf) goto L_405403;	/* 4053ed: je 0x405403 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 4053ef: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4053f2: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4053f4: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_405407;	/* 4053f7: jne 0x405407 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4053f9: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4053fc: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4053ff: test cl, cl */
	if (!m->zf) goto L_4053e3;	/* 405401: jne 0x4053e3 */
L_405403:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 405403: xor eax, eax */
	goto L_40540c;	/* 405405: jmp 0x40540c */
L_405407:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405407: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405409: sbb eax, -1 */
L_40540c:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40540c: test eax, eax */
	if (m->zf) goto L_4054b9;	/* 40540e: je 0x4054b9 */
	m->esi = 0x4ad514u;	/* 405414: mov esi, 0x4ad514 */
	m->eax = 0x4ded20u;	/* 405419: mov eax, 0x4ded20 */
L_40541e:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 40541e: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405420: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405422: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_405442;	/* 405424: jne 0x405442 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405426: test cl, cl */
	if (m->zf) goto L_40543e;	/* 405428: je 0x40543e */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 40542a: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 40542d: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40542f: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_405442;	/* 405432: jne 0x405442 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 405434: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 405437: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40543a: test cl, cl */
	if (!m->zf) goto L_40541e;	/* 40543c: jne 0x40541e */
L_40543e:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40543e: xor eax, eax */
	goto L_405447;	/* 405440: jmp 0x405447 */
L_405442:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405442: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405444: sbb eax, -1 */
L_405447:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 405447: test eax, eax */
	if (m->zf) goto L_4054b9;	/* 405449: je 0x4054b9 */
	m->esi = 0x4ad504u;	/* 40544b: mov esi, 0x4ad504 */
	m->eax = 0x4ded20u;	/* 405450: mov eax, 0x4ded20 */
L_405455:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 405455: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405457: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405459: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_405479;	/* 40545b: jne 0x405479 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40545d: test cl, cl */
	if (m->zf) goto L_405475;	/* 40545f: je 0x405475 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 405461: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405464: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405466: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_405479;	/* 405469: jne 0x405479 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40546b: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 40546e: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405471: test cl, cl */
	if (!m->zf) goto L_405455;	/* 405473: jne 0x405455 */
L_405475:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 405475: xor eax, eax */
	goto L_40547e;	/* 405477: jmp 0x40547e */
L_405479:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405479: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 40547b: sbb eax, -1 */
L_40547e:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40547e: test eax, eax */
	if (m->zf) goto L_4054b9;	/* 405480: je 0x4054b9 */
	m->esi = 0x4ad4f4u;	/* 405482: mov esi, 0x4ad4f4 */
	m->eax = 0x4ded20u;	/* 405487: mov eax, 0x4ded20 */
L_40548c:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 40548c: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 40548e: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405490: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_4054b0;	/* 405492: jne 0x4054b0 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405494: test cl, cl */
	if (m->zf) goto L_4054ac;	/* 405496: je 0x4054ac */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 405498: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 40549b: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40549d: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_4054b0;	/* 4054a0: jne 0x4054b0 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4054a2: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4054a5: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4054a8: test cl, cl */
	if (!m->zf) goto L_40548c;	/* 4054aa: jne 0x40548c */
L_4054ac:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4054ac: xor eax, eax */
	goto L_4054b5;	/* 4054ae: jmp 0x4054b5 */
L_4054b0:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4054b0: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4054b2: sbb eax, -1 */
L_4054b5:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4054b5: test eax, eax */
	if (!m->zf) goto L_4054c0;	/* 4054b7: jne 0x4054c0 */
L_4054b9:
	M8((DWORD)(0x4ded40u)) = (BYTE)(0x16u);	/* 4054b9: mov byte ptr [0x4ded40], 0x16 */
L_4054c0:
	m->esi = 0x4ad4e8u;	/* 4054c0: mov esi, 0x4ad4e8 */
	m->eax = 0x4ded20u;	/* 4054c5: mov eax, 0x4ded20 */
L_4054ca:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 4054ca: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4054cc: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4054ce: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_4054ee;	/* 4054d0: jne 0x4054ee */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4054d2: test cl, cl */
	if (m->zf) goto L_4054ea;	/* 4054d4: je 0x4054ea */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 4054d6: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4054d9: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4054db: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_4054ee;	/* 4054de: jne 0x4054ee */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4054e0: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4054e3: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4054e6: test cl, cl */
	if (!m->zf) goto L_4054ca;	/* 4054e8: jne 0x4054ca */
L_4054ea:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4054ea: xor eax, eax */
	goto L_4054f3;	/* 4054ec: jmp 0x4054f3 */
L_4054ee:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4054ee: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4054f0: sbb eax, -1 */
L_4054f3:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4054f3: test eax, eax */
	if (m->zf) goto L_4055a0;	/* 4054f5: je 0x4055a0 */
	m->esi = 0x4ad4d8u;	/* 4054fb: mov esi, 0x4ad4d8 */
	m->eax = 0x4ded20u;	/* 405500: mov eax, 0x4ded20 */
L_405505:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 405505: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405507: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405509: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_405529;	/* 40550b: jne 0x405529 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40550d: test cl, cl */
	if (m->zf) goto L_405525;	/* 40550f: je 0x405525 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 405511: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405514: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405516: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_405529;	/* 405519: jne 0x405529 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40551b: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 40551e: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405521: test cl, cl */
	if (!m->zf) goto L_405505;	/* 405523: jne 0x405505 */
L_405525:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 405525: xor eax, eax */
	goto L_40552e;	/* 405527: jmp 0x40552e */
L_405529:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405529: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 40552b: sbb eax, -1 */
L_40552e:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40552e: test eax, eax */
	if (m->zf) goto L_4055a0;	/* 405530: je 0x4055a0 */
	m->esi = 0x4ad4c8u;	/* 405532: mov esi, 0x4ad4c8 */
	m->eax = 0x4ded20u;	/* 405537: mov eax, 0x4ded20 */
L_40553c:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 40553c: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 40553e: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405540: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_405560;	/* 405542: jne 0x405560 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405544: test cl, cl */
	if (m->zf) goto L_40555c;	/* 405546: je 0x40555c */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 405548: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 40554b: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40554d: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_405560;	/* 405550: jne 0x405560 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 405552: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 405555: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405558: test cl, cl */
	if (!m->zf) goto L_40553c;	/* 40555a: jne 0x40553c */
L_40555c:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40555c: xor eax, eax */
	goto L_405565;	/* 40555e: jmp 0x405565 */
L_405560:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405560: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405562: sbb eax, -1 */
L_405565:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 405565: test eax, eax */
	if (m->zf) goto L_4055a0;	/* 405567: je 0x4055a0 */
	m->esi = 0x4ad4b8u;	/* 405569: mov esi, 0x4ad4b8 */
	m->eax = 0x4ded20u;	/* 40556e: mov eax, 0x4ded20 */
L_405573:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 405573: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405575: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405577: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_405597;	/* 405579: jne 0x405597 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40557b: test cl, cl */
	if (m->zf) goto L_405593;	/* 40557d: je 0x405593 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 40557f: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405582: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405584: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_405597;	/* 405587: jne 0x405597 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 405589: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 40558c: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40558f: test cl, cl */
	if (!m->zf) goto L_405573;	/* 405591: jne 0x405573 */
L_405593:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 405593: xor eax, eax */
	goto L_40559c;	/* 405595: jmp 0x40559c */
L_405597:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405597: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405599: sbb eax, -1 */
L_40559c:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40559c: test eax, eax */
	if (!m->zf) goto L_4055a7;	/* 40559e: jne 0x4055a7 */
L_4055a0:
	M8((DWORD)(0x4ded40u)) = (BYTE)(0x17u);	/* 4055a0: mov byte ptr [0x4ded40], 0x17 */
L_4055a7:
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x4ded42u)));	/* 4055a7: movsx eax, byte ptr [0x4ded42] */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(0x4ded40u)));	/* 4055ae: movsx ecx, byte ptr [0x4ded40] */
	m->edx = M32((DWORD)(0x4dedd0u));	/* 4055b5: mov edx, dword ptr [0x4dedd0] */
	{ DWORD a_ = m->eax, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4055bb: shl eax, 8 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4055be: or eax, ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4055c0: push edx */
	m->edx = M32((DWORD)(0x4ded44u));	/* 4055c1: mov edx, dword ptr [0x4ded44] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4055c7: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x4ded45u))) & 0xff) << 0);	/* 4055c9: mov cl, byte ptr [0x4ded45] */
	{ DWORD a_ = m->edx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4055cf: and edx, 0xff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4055d5: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4055d6: push edx */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(0x4ded43u)));	/* 4055d7: movsx ecx, byte ptr [0x4ded43] */
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(0x4ded41u)));	/* 4055de: movsx edx, byte ptr [0x4ded41] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4055e5: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4055e6: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4055e7: push eax */
	{ DWORD v_ = 0x4dedb0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4055e8: push 0x4dedb0 */
	{ DWORD v_ = 0x4ded20u; m->esp -= 4; M32(m->esp) = v_; }	/* 4055ed: push 0x4ded20 */
	m->esp -= 4; M32(m->esp) = 0x4055f7u; native_call(m, 0x453090u);	/* 4055f2: call 0x453090 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4055f7: add esp, 0x20 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4055fa: test eax, eax */
	if (!m->zf) goto L_40561d;	/* 4055fc: jne 0x40561d */
L_4055fe:
	M32((DWORD)(0x4db55cu)) = m->ebp;	/* 4055fe: mov dword ptr [0x4db55c], ebp */
	M32((DWORD)(0x67ef14u)) = 0x0u;	/* 405604: mov dword ptr [0x67ef14], 0 */
	M32((DWORD)(0x67ef04u)) = m->edi;	/* 40560e: mov dword ptr [0x67ef04], edi */
	m->esp -= 4; M32(m->esp) = 0x405619u; native_call(m, 0x452fe0u);	/* 405614: call 0x452fe0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 405619: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 40561a: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 40561b: pop ebp */
	m->esp += 4 + 0; return;	/* 40561c: ret  */
L_40561d:
	m->esp -= 4; M32(m->esp) = 0x405622u; native_call(m, 0x457310u);	/* 40561d: call 0x457310 */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x4ded40u)));	/* 405622: movsx eax, byte ptr [0x4ded40] */
	m->ecx = 0x8u;	/* 405629: mov ecx, 8 */
	m->esi = 0x4ded20u;	/* 40562e: mov esi, 0x4ded20 */
	m->edi = 0x67fb44u;	/* 405633: mov edi, 0x67fb44 */
	M32((DWORD)(0x9dad94u)) = m->eax;	/* 405638: mov dword ptr [0x9dad94], eax */
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(0x4ded43u)));	/* 40563d: movsx edx, byte ptr [0x4ded43] */
	m->eax = M32((DWORD)(0x4ded44u));	/* 405644: mov eax, dword ptr [0x4ded44] */
	M32((DWORD)(0x4dbbf4u)) = m->ebp;	/* 405649: mov dword ptr [0x4dbbf4], ebp */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40564f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(0x4ded42u)));	/* 405651: movsx ecx, byte ptr [0x4ded42] */
	M32((DWORD)(0x9da3e0u)) = m->ecx;	/* 405658: mov dword ptr [0x9da3e0], ecx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40565e: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x4ded45u))) & 0xff) << 0);	/* 405660: mov cl, byte ptr [0x4ded45] */
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 405666: and eax, 0xff */
	m->edi = M32(m->esp); m->esp += 4;	/* 40566b: pop edi */
	M32((DWORD)(0x4ded54u)) = m->ebp;	/* 40566c: mov dword ptr [0x4ded54], ebp */
	m->esi = M32(m->esp); m->esp += 4;	/* 405672: pop esi */
	M32((DWORD)(0x76d368u)) = m->edx;	/* 405673: mov dword ptr [0x76d368], edx */
	M32((DWORD)(0x4df8e8u)) = m->eax;	/* 405679: mov dword ptr [0x4df8e8], eax */
	M32((DWORD)(0x76d408u)) = m->ecx;	/* 40567e: mov dword ptr [0x76d408], ecx */
	M32((DWORD)(0x4dbb3cu)) = 0x0u;	/* 405684: mov dword ptr [0x4dbb3c], 0 */
	m->ebp = M32(m->esp); m->esp += 4;	/* 40568e: pop ebp */
	m->esp += 4 + 0; return;	/* 40568f: ret  */
}

/* lobby_checkReservedName (0x4057a0), lifted by tools/lift.py */
static void lift_4057a0(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4057a0: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4057a1: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4057a2: push edi */
	M32((DWORD)(0x4dbbf4u)) = 0x2u;	/* 4057a3: mov dword ptr [0x4dbbf4], 2 */
	M32((DWORD)(0x67ef14u)) = 0x1u;	/* 4057ad: mov dword ptr [0x67ef14], 1 */
	M32((DWORD)(0x67ef04u)) = 0x1u;	/* 4057b7: mov dword ptr [0x67ef04], 1 */
	m->esp -= 4; M32(m->esp) = 0x4057c6u; native_call(m, 0x457310u);	/* 4057c1: call 0x457310 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4057c6: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4057c8: push 0 */
	M32((DWORD)(0x4dbb3cu)) = 0x0u;	/* 4057ca: mov dword ptr [0x4dbb3c], 0 */
	m->esp -= 4; M32(m->esp) = 0x4057d9u; native_call(m, 0x452ec0u);	/* 4057d4: call 0x452ec0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4057d9: add esp, 8 */
	m->esi = 0x4ad554u;	/* 4057dc: mov esi, 0x4ad554 */
	m->eax = 0x4ded20u;	/* 4057e1: mov eax, 0x4ded20 */
L_4057e6:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 4057e6: mov dl, byte ptr [eax] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 4057e8: mov bl, byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4057ea: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4057ec: cmp dl, bl */
	if (!m->zf) goto L_40580e;	/* 4057ee: jne 0x40580e */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4057f0: test cl, cl */
	if (m->zf) goto L_40580a;	/* 4057f2: je 0x40580a */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 4057f4: mov dl, byte ptr [eax + 1] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 4057f7: mov bl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4057fa: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4057fc: cmp dl, bl */
	if (!m->zf) goto L_40580e;	/* 4057fe: jne 0x40580e */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 405800: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 405803: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405806: test cl, cl */
	if (!m->zf) goto L_4057e6;	/* 405808: jne 0x4057e6 */
L_40580a:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40580a: xor eax, eax */
	goto L_405813;	/* 40580c: jmp 0x405813 */
L_40580e:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 40580e: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405810: sbb eax, -1 */
L_405813:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 405813: test eax, eax */
	if (m->zf) goto L_4058cc;	/* 405815: je 0x4058cc */
	m->esi = 0x4ad548u;	/* 40581b: mov esi, 0x4ad548 */
	m->eax = 0x4ded20u;	/* 405820: mov eax, 0x4ded20 */
L_405825:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 405825: mov dl, byte ptr [eax] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 405827: mov bl, byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405829: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40582b: cmp dl, bl */
	if (!m->zf) goto L_40584d;	/* 40582d: jne 0x40584d */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40582f: test cl, cl */
	if (m->zf) goto L_405849;	/* 405831: je 0x405849 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 405833: mov dl, byte ptr [eax + 1] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 405836: mov bl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405839: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40583b: cmp dl, bl */
	if (!m->zf) goto L_40584d;	/* 40583d: jne 0x40584d */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40583f: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 405842: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405845: test cl, cl */
	if (!m->zf) goto L_405825;	/* 405847: jne 0x405825 */
L_405849:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 405849: xor eax, eax */
	goto L_405852;	/* 40584b: jmp 0x405852 */
L_40584d:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 40584d: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 40584f: sbb eax, -1 */
L_405852:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 405852: test eax, eax */
	if (m->zf) goto L_4058cc;	/* 405854: je 0x4058cc */
	m->esi = 0x4ad53cu;	/* 405856: mov esi, 0x4ad53c */
	m->eax = 0x4ded20u;	/* 40585b: mov eax, 0x4ded20 */
L_405860:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 405860: mov dl, byte ptr [eax] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 405862: mov bl, byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405864: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405866: cmp dl, bl */
	if (!m->zf) goto L_405888;	/* 405868: jne 0x405888 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40586a: test cl, cl */
	if (m->zf) goto L_405884;	/* 40586c: je 0x405884 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 40586e: mov dl, byte ptr [eax + 1] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 405871: mov bl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405874: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405876: cmp dl, bl */
	if (!m->zf) goto L_405888;	/* 405878: jne 0x405888 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40587a: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 40587d: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405880: test cl, cl */
	if (!m->zf) goto L_405860;	/* 405882: jne 0x405860 */
L_405884:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 405884: xor eax, eax */
	goto L_40588d;	/* 405886: jmp 0x40588d */
L_405888:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405888: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 40588a: sbb eax, -1 */
L_40588d:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40588d: test eax, eax */
	if (m->zf) goto L_4058cc;	/* 40588f: je 0x4058cc */
	m->esi = 0x4ad530u;	/* 405891: mov esi, 0x4ad530 */
	m->eax = 0x4ded20u;	/* 405896: mov eax, 0x4ded20 */
L_40589b:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 40589b: mov dl, byte ptr [eax] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 40589d: mov bl, byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 40589f: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4058a1: cmp dl, bl */
	if (!m->zf) goto L_4058c3;	/* 4058a3: jne 0x4058c3 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4058a5: test cl, cl */
	if (m->zf) goto L_4058bf;	/* 4058a7: je 0x4058bf */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 4058a9: mov dl, byte ptr [eax + 1] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 4058ac: mov bl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4058af: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4058b1: cmp dl, bl */
	if (!m->zf) goto L_4058c3;	/* 4058b3: jne 0x4058c3 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4058b5: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4058b8: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4058bb: test cl, cl */
	if (!m->zf) goto L_40589b;	/* 4058bd: jne 0x40589b */
L_4058bf:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4058bf: xor eax, eax */
	goto L_4058c8;	/* 4058c1: jmp 0x4058c8 */
L_4058c3:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4058c3: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4058c5: sbb eax, -1 */
L_4058c8:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4058c8: test eax, eax */
	if (!m->zf) goto L_4058d3;	/* 4058ca: jne 0x4058d3 */
L_4058cc:
	M8((DWORD)(0x4ded40u)) = (BYTE)(0x18u);	/* 4058cc: mov byte ptr [0x4ded40], 0x18 */
L_4058d3:
	m->esi = 0x4ad524u;	/* 4058d3: mov esi, 0x4ad524 */
	m->eax = 0x4ded20u;	/* 4058d8: mov eax, 0x4ded20 */
L_4058dd:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 4058dd: mov dl, byte ptr [eax] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 4058df: mov bl, byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4058e1: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4058e3: cmp dl, bl */
	if (!m->zf) goto L_405905;	/* 4058e5: jne 0x405905 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4058e7: test cl, cl */
	if (m->zf) goto L_405901;	/* 4058e9: je 0x405901 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 4058eb: mov dl, byte ptr [eax + 1] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 4058ee: mov bl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4058f1: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4058f3: cmp dl, bl */
	if (!m->zf) goto L_405905;	/* 4058f5: jne 0x405905 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4058f7: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4058fa: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4058fd: test cl, cl */
	if (!m->zf) goto L_4058dd;	/* 4058ff: jne 0x4058dd */
L_405901:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 405901: xor eax, eax */
	goto L_40590a;	/* 405903: jmp 0x40590a */
L_405905:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405905: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405907: sbb eax, -1 */
L_40590a:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40590a: test eax, eax */
	if (m->zf) goto L_4059c3;	/* 40590c: je 0x4059c3 */
	m->esi = 0x4ad514u;	/* 405912: mov esi, 0x4ad514 */
	m->eax = 0x4ded20u;	/* 405917: mov eax, 0x4ded20 */
L_40591c:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 40591c: mov dl, byte ptr [eax] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 40591e: mov bl, byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405920: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405922: cmp dl, bl */
	if (!m->zf) goto L_405944;	/* 405924: jne 0x405944 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405926: test cl, cl */
	if (m->zf) goto L_405940;	/* 405928: je 0x405940 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 40592a: mov dl, byte ptr [eax + 1] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 40592d: mov bl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405930: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405932: cmp dl, bl */
	if (!m->zf) goto L_405944;	/* 405934: jne 0x405944 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 405936: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 405939: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40593c: test cl, cl */
	if (!m->zf) goto L_40591c;	/* 40593e: jne 0x40591c */
L_405940:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 405940: xor eax, eax */
	goto L_405949;	/* 405942: jmp 0x405949 */
L_405944:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405944: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405946: sbb eax, -1 */
L_405949:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 405949: test eax, eax */
	if (m->zf) goto L_4059c3;	/* 40594b: je 0x4059c3 */
	m->esi = 0x4ad504u;	/* 40594d: mov esi, 0x4ad504 */
	m->eax = 0x4ded20u;	/* 405952: mov eax, 0x4ded20 */
L_405957:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 405957: mov dl, byte ptr [eax] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 405959: mov bl, byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 40595b: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40595d: cmp dl, bl */
	if (!m->zf) goto L_40597f;	/* 40595f: jne 0x40597f */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405961: test cl, cl */
	if (m->zf) goto L_40597b;	/* 405963: je 0x40597b */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 405965: mov dl, byte ptr [eax + 1] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 405968: mov bl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 40596b: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40596d: cmp dl, bl */
	if (!m->zf) goto L_40597f;	/* 40596f: jne 0x40597f */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 405971: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 405974: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405977: test cl, cl */
	if (!m->zf) goto L_405957;	/* 405979: jne 0x405957 */
L_40597b:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40597b: xor eax, eax */
	goto L_405984;	/* 40597d: jmp 0x405984 */
L_40597f:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 40597f: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405981: sbb eax, -1 */
L_405984:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 405984: test eax, eax */
	if (m->zf) goto L_4059c3;	/* 405986: je 0x4059c3 */
	m->esi = 0x4ad4f4u;	/* 405988: mov esi, 0x4ad4f4 */
	m->eax = 0x4ded20u;	/* 40598d: mov eax, 0x4ded20 */
L_405992:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 405992: mov dl, byte ptr [eax] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 405994: mov bl, byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405996: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405998: cmp dl, bl */
	if (!m->zf) goto L_4059ba;	/* 40599a: jne 0x4059ba */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40599c: test cl, cl */
	if (m->zf) goto L_4059b6;	/* 40599e: je 0x4059b6 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 4059a0: mov dl, byte ptr [eax + 1] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 4059a3: mov bl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4059a6: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4059a8: cmp dl, bl */
	if (!m->zf) goto L_4059ba;	/* 4059aa: jne 0x4059ba */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4059ac: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4059af: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4059b2: test cl, cl */
	if (!m->zf) goto L_405992;	/* 4059b4: jne 0x405992 */
L_4059b6:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4059b6: xor eax, eax */
	goto L_4059bf;	/* 4059b8: jmp 0x4059bf */
L_4059ba:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4059ba: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4059bc: sbb eax, -1 */
L_4059bf:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4059bf: test eax, eax */
	if (!m->zf) goto L_4059ca;	/* 4059c1: jne 0x4059ca */
L_4059c3:
	M8((DWORD)(0x4ded40u)) = (BYTE)(0x16u);	/* 4059c3: mov byte ptr [0x4ded40], 0x16 */
L_4059ca:
	m->esi = 0x4ad4e8u;	/* 4059ca: mov esi, 0x4ad4e8 */
	m->eax = 0x4ded20u;	/* 4059cf: mov eax, 0x4ded20 */
L_4059d4:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 4059d4: mov dl, byte ptr [eax] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 4059d6: mov bl, byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4059d8: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4059da: cmp dl, bl */
	if (!m->zf) goto L_4059fc;	/* 4059dc: jne 0x4059fc */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4059de: test cl, cl */
	if (m->zf) goto L_4059f8;	/* 4059e0: je 0x4059f8 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 4059e2: mov dl, byte ptr [eax + 1] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 4059e5: mov bl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4059e8: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4059ea: cmp dl, bl */
	if (!m->zf) goto L_4059fc;	/* 4059ec: jne 0x4059fc */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4059ee: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4059f1: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4059f4: test cl, cl */
	if (!m->zf) goto L_4059d4;	/* 4059f6: jne 0x4059d4 */
L_4059f8:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4059f8: xor eax, eax */
	goto L_405a01;	/* 4059fa: jmp 0x405a01 */
L_4059fc:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4059fc: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4059fe: sbb eax, -1 */
L_405a01:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 405a01: test eax, eax */
	if (m->zf) goto L_405aba;	/* 405a03: je 0x405aba */
	m->esi = 0x4ad4d8u;	/* 405a09: mov esi, 0x4ad4d8 */
	m->eax = 0x4ded20u;	/* 405a0e: mov eax, 0x4ded20 */
L_405a13:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 405a13: mov dl, byte ptr [eax] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 405a15: mov bl, byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405a17: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405a19: cmp dl, bl */
	if (!m->zf) goto L_405a3b;	/* 405a1b: jne 0x405a3b */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405a1d: test cl, cl */
	if (m->zf) goto L_405a37;	/* 405a1f: je 0x405a37 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 405a21: mov dl, byte ptr [eax + 1] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 405a24: mov bl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405a27: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405a29: cmp dl, bl */
	if (!m->zf) goto L_405a3b;	/* 405a2b: jne 0x405a3b */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 405a2d: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 405a30: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405a33: test cl, cl */
	if (!m->zf) goto L_405a13;	/* 405a35: jne 0x405a13 */
L_405a37:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 405a37: xor eax, eax */
	goto L_405a40;	/* 405a39: jmp 0x405a40 */
L_405a3b:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405a3b: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405a3d: sbb eax, -1 */
L_405a40:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 405a40: test eax, eax */
	if (m->zf) goto L_405aba;	/* 405a42: je 0x405aba */
	m->esi = 0x4ad4c8u;	/* 405a44: mov esi, 0x4ad4c8 */
	m->eax = 0x4ded20u;	/* 405a49: mov eax, 0x4ded20 */
L_405a4e:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 405a4e: mov dl, byte ptr [eax] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 405a50: mov bl, byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405a52: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405a54: cmp dl, bl */
	if (!m->zf) goto L_405a76;	/* 405a56: jne 0x405a76 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405a58: test cl, cl */
	if (m->zf) goto L_405a72;	/* 405a5a: je 0x405a72 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 405a5c: mov dl, byte ptr [eax + 1] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 405a5f: mov bl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405a62: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405a64: cmp dl, bl */
	if (!m->zf) goto L_405a76;	/* 405a66: jne 0x405a76 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 405a68: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 405a6b: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405a6e: test cl, cl */
	if (!m->zf) goto L_405a4e;	/* 405a70: jne 0x405a4e */
L_405a72:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 405a72: xor eax, eax */
	goto L_405a7b;	/* 405a74: jmp 0x405a7b */
L_405a76:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405a76: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405a78: sbb eax, -1 */
L_405a7b:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 405a7b: test eax, eax */
	if (m->zf) goto L_405aba;	/* 405a7d: je 0x405aba */
	m->esi = 0x4ad4b8u;	/* 405a7f: mov esi, 0x4ad4b8 */
	m->eax = 0x4ded20u;	/* 405a84: mov eax, 0x4ded20 */
L_405a89:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 405a89: mov dl, byte ptr [eax] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 405a8b: mov bl, byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405a8d: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405a8f: cmp dl, bl */
	if (!m->zf) goto L_405ab1;	/* 405a91: jne 0x405ab1 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405a93: test cl, cl */
	if (m->zf) goto L_405aad;	/* 405a95: je 0x405aad */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 405a97: mov dl, byte ptr [eax + 1] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 405a9a: mov bl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405a9d: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405a9f: cmp dl, bl */
	if (!m->zf) goto L_405ab1;	/* 405aa1: jne 0x405ab1 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 405aa3: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 405aa6: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405aa9: test cl, cl */
	if (!m->zf) goto L_405a89;	/* 405aab: jne 0x405a89 */
L_405aad:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 405aad: xor eax, eax */
	goto L_405ab6;	/* 405aaf: jmp 0x405ab6 */
L_405ab1:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405ab1: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405ab3: sbb eax, -1 */
L_405ab6:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 405ab6: test eax, eax */
	if (!m->zf) goto L_405ac1;	/* 405ab8: jne 0x405ac1 */
L_405aba:
	M8((DWORD)(0x4ded40u)) = (BYTE)(0x17u);	/* 405aba: mov byte ptr [0x4ded40], 0x17 */
L_405ac1:
	m->eax = M32((DWORD)(0x4dedd0u));	/* 405ac1: mov eax, dword ptr [0x4dedd0] */
	m->edx = M32((DWORD)(0x4ded44u));	/* 405ac6: mov edx, dword ptr [0x4ded44] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 405acc: xor ecx, ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 405ace: push eax */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x4ded45u))) & 0xff) << 0);	/* 405acf: mov cl, byte ptr [0x4ded45] */
	{ DWORD a_ = m->edx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 405ad5: and edx, 0xff */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x4ded43u)));	/* 405adb: movsx eax, byte ptr [0x4ded43] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 405ae2: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 405ae3: push edx */
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(0x4ded42u)));	/* 405ae4: movsx edx, byte ptr [0x4ded42] */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(0x4ded41u)));	/* 405aeb: movsx ecx, byte ptr [0x4ded41] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 405af2: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 405af3: push ecx */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x4ded40u)));	/* 405af4: movsx eax, byte ptr [0x4ded40] */
	{ DWORD a_ = m->edx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 405afb: shl edx, 8 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 405afe: or edx, eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 405b00: push edx */
	{ DWORD v_ = 0x4dedb0u; m->esp -= 4; M32(m->esp) = v_; }	/* 405b01: push 0x4dedb0 */
	{ DWORD v_ = 0x4ded20u; m->esp -= 4; M32(m->esp) = v_; }	/* 405b06: push 0x4ded20 */
	m->esp -= 4; M32(m->esp) = 0x405b10u; native_call(m, 0x453090u);	/* 405b0b: call 0x453090 */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(0x4ded40u)));	/* 405b10: movsx ecx, byte ptr [0x4ded40] */
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(0x4ded42u)));	/* 405b17: movsx edx, byte ptr [0x4ded42] */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x4ded43u)));	/* 405b1e: movsx eax, byte ptr [0x4ded43] */
	M32((DWORD)(0x9dad94u)) = m->ecx;	/* 405b25: mov dword ptr [0x9dad94], ecx */
	m->ecx = 0x8u;	/* 405b2b: mov ecx, 8 */
	m->esi = 0x4ded20u;	/* 405b30: mov esi, 0x4ded20 */
	m->edi = 0x67fb44u;	/* 405b35: mov edi, 0x67fb44 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 405b3a: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = M32((DWORD)(0x4ded44u));	/* 405b3c: mov ecx, dword ptr [0x4ded44] */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 405b42: add esp, 0x20 */
	M32((DWORD)(0x9da3e0u)) = m->edx;	/* 405b45: mov dword ptr [0x9da3e0], edx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 405b4b: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(0x4ded45u))) & 0xff) << 0);	/* 405b4d: mov dl, byte ptr [0x4ded45] */
	{ DWORD a_ = m->ecx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 405b53: and ecx, 0xff */
	m->edi = M32(m->esp); m->esp += 4;	/* 405b59: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 405b5a: pop esi */
	M32((DWORD)(0x76d368u)) = m->eax;	/* 405b5b: mov dword ptr [0x76d368], eax */
	M32((DWORD)(0x4df8e8u)) = m->ecx;	/* 405b60: mov dword ptr [0x4df8e8], ecx */
	M32((DWORD)(0x76d408u)) = m->edx;	/* 405b66: mov dword ptr [0x76d408], edx */
	M32((DWORD)(0x4ded54u)) = 0x1u;	/* 405b6c: mov dword ptr [0x4ded54], 1 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 405b76: pop ebx */
	m->esp += 4 + 0; return;	/* 405b77: ret  */
}

/* lobby_connect (0x406c30), lifted by tools/lift.py */
static void lift_406c30(X86 *m)
{
	m->eax = M32((DWORD)(0x4dbb3cu));	/* 406c30: mov eax, dword ptr [0x4dbb3c] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 406c35: push ebx */
	m->ebx = 0x1u;	/* 406c36: mov ebx, 1 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 406c3b: push esi */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406c3c: cmp eax, ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 406c3e: push edi */
	if (m->zf) goto L_40722a;	/* 406c3f: je 0x40722a */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 406c45: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406c47: cmp eax, edi */
	if (m->zf) goto L_40722a;	/* 406c49: je 0x40722a */
	{ DWORD a_ = M32((DWORD)(0x4db8bcu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406c4f: cmp dword ptr [0x4db8bc], edi */
	if (!m->zf) goto L_40722a;	/* 406c55: jne 0x40722a */
	{ DWORD a_ = M32((DWORD)(0x4db714u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406c5b: cmp dword ptr [0x4db714], edi */
	if (!m->zf) goto L_40722a;	/* 406c61: jne 0x40722a */
	{ DWORD a_ = M32((DWORD)(0x90d1c4u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406c67: cmp dword ptr [0x90d1c4], edi */
	if (!m->zf) goto L_40722a;	/* 406c6d: jne 0x40722a */
	{ DWORD a_ = M32((DWORD)(0x4ded8cu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406c73: cmp dword ptr [0x4ded8c], edi */
	if (m->zf) goto L_406cb3;	/* 406c79: je 0x406cb3 */
	{ DWORD a_ = M32((DWORD)(0x4db858u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406c7b: cmp dword ptr [0x4db858], edi */
	if (!m->zf) goto L_40722a;	/* 406c81: jne 0x40722a */
	{ DWORD a_ = M32((DWORD)(0x4dba90u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406c87: cmp dword ptr [0x4dba90], edi */
	if (!m->zf) goto L_40722a;	/* 406c8d: jne 0x40722a */
	M32((DWORD)(0xa0b36cu)) = m->edi;	/* 406c93: mov dword ptr [0xa0b36c], edi */
	m->esp -= 4; M32(m->esp) = 0x406c9eu; native_call(m, 0x452fe0u);	/* 406c99: call 0x452fe0 */
	m->esp -= 4; M32(m->esp) = 0x406ca3u; native_call(m, 0x451e60u);	/* 406c9e: call 0x451e60 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 406ca3: push edi */
	m->esp -= 4; M32(m->esp) = 0x406ca9u; native_call(m, 0x41e760u);	/* 406ca4: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 406ca9: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 406cac: xor eax, eax */
	M32((DWORD)(0x4dbb3cu)) = m->eax;	/* 406cae: mov dword ptr [0x4dbb3c], eax */
L_406cb3:
	{ DWORD a_ = M32((DWORD)(0x4ded88u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406cb3: cmp dword ptr [0x4ded88], edi */
	if (m->zf) goto L_407114;	/* 406cb9: je 0x407114 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406cbf: cmp eax, 2 */
	if (!m->zf) goto L_407114;	/* 406cc2: jne 0x407114 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 406cc8: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 406ccd: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 406cd3: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 406cd4: push ecx */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 406cd5: mov dword ptr [0x4dda44], 0 */
	m->esp -= 4; M32(m->esp) = 0x406ce4u; native_call(m, 0x4044a0u);	/* 406cdf: call 0x4044a0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 406ce4: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406ce7: cmp eax, 0x10 */
	if (!m->cf && !m->zf) goto L_407034;	/* 406cea: ja 0x407034 */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 406cf0: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x407254u))) & 0xff) << 0);	/* 406cf2: mov dl, byte ptr [eax + 0x407254] */
	switch (m->edx) { case 0: goto L_406cff; case 1: goto L_406d9c; case 2: goto L_406e1b; case 3: goto L_406e3a; case 4: goto L_406ead; case 5: goto L_406f17; case 6: goto L_406f81; case 7: goto L_406fd3; case 8: goto L_407034; default: abort(); }	/* 406cf8: jmp dword ptr [edx*4 + 0x407230] */
L_406cff:
	{ DWORD a_ = M32((DWORD)(0x4dba90u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406cff: cmp dword ptr [0x4dba90], edi */
	if (!m->zf) goto L_406e66;	/* 406d05: jne 0x406e66 */
	{ DWORD a_ = M32((DWORD)(0x4db858u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406d0b: cmp dword ptr [0x4db858], edi */
	if (!m->zf) goto L_406e66;	/* 406d11: jne 0x406e66 */
	{ DWORD a_ = M32((DWORD)(0x4db8b8u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406d17: cmp dword ptr [0x4db8b8], edi */
	if (!m->zf) goto L_406e66;	/* 406d1d: jne 0x406e66 */
	{ DWORD a_ = M32((DWORD)(0x4db714u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406d23: cmp dword ptr [0x4db714], edi */
	if (!m->zf) goto L_40722a;	/* 406d29: jne 0x40722a */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 406d2f: push edi */
	m->esp -= 4; M32(m->esp) = 0x406d35u; native_call(m, 0x41e760u);	/* 406d30: call 0x41e760 */
	m->eax = M32((DWORD)(0x4db854u));	/* 406d35: mov eax, dword ptr [0x4db854] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 406d3a: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406d3d: cmp eax, edi */
	if (m->zf) goto L_406d4c;	/* 406d3f: je 0x406d4c */
	M32((DWORD)(0x4db718u)) = m->edi;	/* 406d41: mov dword ptr [0x4db718], edi */
	m->esp -= 4; M32(m->esp) = 0x406d4cu; native_call(m, 0x451e60u);	/* 406d47: call 0x451e60 */
L_406d4c:
	{ DWORD a_ = M32((DWORD)(0x4dba84u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406d4c: cmp dword ptr [0x4dba84], edi */
	if (m->zf) goto L_406d59;	/* 406d52: je 0x406d59 */
	m->esp -= 4; M32(m->esp) = 0x406d59u; native_call(m, 0x452fe0u);	/* 406d54: call 0x452fe0 */
L_406d59:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 406d59: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 406d5a: push ebx */
	M32((DWORD)(0xa0b368u)) = m->edi;	/* 406d5b: mov dword ptr [0xa0b368], edi */
	m->esp -= 4; M32(m->esp) = 0x406d66u; native_call(m, 0x452ec0u);	/* 406d61: call 0x452ec0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 406d66: add esp, 8 */
	M32((DWORD)(0x680bb8u)) = m->edi;	/* 406d69: mov dword ptr [0x680bb8], edi */
	M32((DWORD)(0x4dba90u)) = m->ebx;	/* 406d6f: mov dword ptr [0x4dba90], ebx */
	M32((DWORD)(0x4dba80u)) = 0x43160000u;	/* 406d75: mov dword ptr [0x4dba80], 0x43160000 */
	M32((DWORD)(0x67ef30u)) = m->edi;	/* 406d7f: mov dword ptr [0x67ef30], edi */
	M32((DWORD)(0x4dbaacu)) = m->edi;	/* 406d85: mov dword ptr [0x4dbaac], edi */
	M32((DWORD)(0x4dba84u)) = m->ebx;	/* 406d8b: mov dword ptr [0x4dba84], ebx */
	M32((DWORD)(0x4db854u)) = m->edi;	/* 406d91: mov dword ptr [0x4db854], edi */
	goto L_407114;	/* 406d97: jmp 0x407114 */
L_406d9c:
	{ DWORD a_ = M32((DWORD)(0x4dba90u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406d9c: cmp dword ptr [0x4dba90], edi */
	if (!m->zf) goto L_406e66;	/* 406da2: jne 0x406e66 */
	{ DWORD a_ = M32((DWORD)(0x4db858u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406da8: cmp dword ptr [0x4db858], edi */
	if (!m->zf) goto L_406e66;	/* 406dae: jne 0x406e66 */
	{ DWORD a_ = M32((DWORD)(0x4db8b8u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406db4: cmp dword ptr [0x4db8b8], edi */
	if (!m->zf) goto L_406e66;	/* 406dba: jne 0x406e66 */
	{ DWORD a_ = M32((DWORD)(0x4db714u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406dc0: cmp dword ptr [0x4db714], edi */
	if (!m->zf) goto L_40722a;	/* 406dc6: jne 0x40722a */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 406dcc: push edi */
	m->esp -= 4; M32(m->esp) = 0x406dd2u; native_call(m, 0x41e760u);	/* 406dcd: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 406dd2: add esp, 4 */
	M32((DWORD)(0x4db718u)) = m->edi;	/* 406dd5: mov dword ptr [0x4db718], edi */
	m->esp -= 4; M32(m->esp) = 0x406de0u; native_call(m, 0x451e60u);	/* 406ddb: call 0x451e60 */
	m->esp -= 4; M32(m->esp) = 0x406de5u; native_call(m, 0x452fe0u);	/* 406de0: call 0x452fe0 */
	M32((DWORD)(0xa0b368u)) = m->edi;	/* 406de5: mov dword ptr [0xa0b368], edi */
	m->esp -= 4; M32(m->esp) = 0x406df0u; native_call(m, 0x4060f0u);	/* 406deb: call 0x4060f0 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406df0: cmp eax, ebx */
	if (!m->zf) goto L_407114;	/* 406df2: jne 0x407114 */
	M32((DWORD)(0x4dbaacu)) = m->ebx;	/* 406df8: mov dword ptr [0x4dbaac], ebx */
	M32((DWORD)(0x4db858u)) = m->ebx;	/* 406dfe: mov dword ptr [0x4db858], ebx */
	M32((DWORD)(0x4db854u)) = m->ebx;	/* 406e04: mov dword ptr [0x4db854], ebx */
	M32((DWORD)(0x4dba84u)) = m->edi;	/* 406e0a: mov dword ptr [0x4dba84], edi */
	M32((DWORD)(0x4db718u)) = m->ebx;	/* 406e10: mov dword ptr [0x4db718], ebx */
	goto L_407114;	/* 406e16: jmp 0x407114 */
L_406e1b:
	{ DWORD a_ = M32((DWORD)(0x4db714u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406e1b: cmp dword ptr [0x4db714], edi */
	if (!m->zf) goto L_40722a;	/* 406e21: jne 0x40722a */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 406e27: push edi */
	m->esp -= 4; M32(m->esp) = 0x406e2du; native_call(m, 0x41e760u);	/* 406e28: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 406e2d: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x406e35u; native_call(m, 0x405230u);	/* 406e30: call 0x405230 */
	goto L_407114;	/* 406e35: jmp 0x407114 */
L_406e3a:
	{ DWORD a_ = M32((DWORD)(0x4dba90u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406e3a: cmp dword ptr [0x4dba90], edi */
	if (!m->zf) goto L_406e66;	/* 406e40: jne 0x406e66 */
	{ DWORD a_ = M32((DWORD)(0x4db858u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406e42: cmp dword ptr [0x4db858], edi */
	if (!m->zf) goto L_406e66;	/* 406e48: jne 0x406e66 */
	{ DWORD a_ = M32((DWORD)(0x4db8b8u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406e4a: cmp dword ptr [0x4db8b8], edi */
	if (!m->zf) goto L_406e66;	/* 406e50: jne 0x406e66 */
	{ DWORD a_ = M32((DWORD)(0x4db714u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406e52: cmp dword ptr [0x4db714], edi */
	if (!m->zf) goto L_40722a;	/* 406e58: jne 0x40722a */
	{ DWORD a_ = M32((DWORD)(0x67ef30u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406e5e: cmp dword ptr [0x67ef30], edi */
	if (!m->zf && m->sf == m->of) goto L_406e74;	/* 406e64: jg 0x406e74 */
L_406e66:
	{ DWORD v_ = 0x6u; m->esp -= 4; M32(m->esp) = v_; }	/* 406e66: push 6 */
	m->esp -= 4; M32(m->esp) = 0x406e6du; native_call(m, 0x41e760u);	/* 406e68: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 406e6d: add esp, 4 */
	m->edi = M32(m->esp); m->esp += 4;	/* 406e70: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 406e71: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 406e72: pop ebx */
	m->esp += 4 + 0; return;	/* 406e73: ret  */
L_406e74:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 406e74: push edi */
	m->esp -= 4; M32(m->esp) = 0x406e7au; native_call(m, 0x41e760u);	/* 406e75: call 0x41e760 */
	m->eax = M32((DWORD)(0x4dbaacu));	/* 406e7a: mov eax, dword ptr [0x4dbaac] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 406e7f: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406e82: cmp eax, edi */
	if (m->zf) goto L_406e9c;	/* 406e84: je 0x406e9c */
	M32((DWORD)(0x4dbbecu)) = m->ebx;	/* 406e86: mov dword ptr [0x4dbbec], ebx */
	M32((DWORD)(0x4dbbf0u)) = m->edi;	/* 406e8c: mov dword ptr [0x4dbbf0], edi */
	m->esp -= 4; M32(m->esp) = 0x406e97u; native_call(m, 0x405200u);	/* 406e92: call 0x405200 */
	goto L_407114;	/* 406e97: jmp 0x407114 */
L_406e9c:
	M32((DWORD)(0x4dbbf0u)) = m->ebx;	/* 406e9c: mov dword ptr [0x4dbbf0], ebx */
	M32((DWORD)(0x4dbbecu)) = m->edi;	/* 406ea2: mov dword ptr [0x4dbbec], edi */
	goto L_407114;	/* 406ea8: jmp 0x407114 */
L_406ead:
	{ DWORD a_ = M32((DWORD)(0x4db714u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406ead: cmp dword ptr [0x4db714], edi */
	if (!m->zf) goto L_40722a;	/* 406eb3: jne 0x40722a */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 406eb9: push edi */
	M32((DWORD)(0xa0b36cu)) = m->edi;	/* 406eba: mov dword ptr [0xa0b36c], edi */
	m->esp -= 4; M32(m->esp) = 0x406ec5u; native_call(m, 0x41e760u);	/* 406ec0: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 406ec5: add esp, 4 */
	M32((DWORD)(0x4dba80u)) = 0x3f800000u;	/* 406ec8: mov dword ptr [0x4dba80], 0x3f800000 */
	M32((DWORD)(0x4df018u)) = m->ebx;	/* 406ed2: mov dword ptr [0x4df018], ebx */
	M32((DWORD)(0x76d484u)) = 0xffffffffu;	/* 406ed8: mov dword ptr [0x76d484], 0xffffffff */
	M32((DWORD)(0x4db718u)) = m->edi;	/* 406ee2: mov dword ptr [0x4db718], edi */
	m->esp -= 4; M32(m->esp) = 0x406eedu; native_call(m, 0x452fe0u);	/* 406ee8: call 0x452fe0 */
	m->esp -= 4; M32(m->esp) = 0x406ef2u; native_call(m, 0x451e60u);	/* 406eed: call 0x451e60 */
	{ DWORD a_ = M32((DWORD)(0x4db8b8u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406ef2: cmp dword ptr [0x4db8b8], ebx */
	if (!m->zf) goto L_406f0c;	/* 406ef8: jne 0x406f0c */
	M32((DWORD)(0x4db8b8u)) = m->edi;	/* 406efa: mov dword ptr [0x4db8b8], edi */
	M32((DWORD)(0x4db858u)) = m->edi;	/* 406f00: mov dword ptr [0x4db858], edi */
	M32((DWORD)(0x4df018u)) = m->edi;	/* 406f06: mov dword ptr [0x4df018], edi */
L_406f0c:
	M32((DWORD)(0xa0d7a0u)) = m->ebx;	/* 406f0c: mov dword ptr [0xa0d7a0], ebx */
	goto L_407114;	/* 406f12: jmp 0x407114 */
L_406f17:
	{ DWORD a_ = M32((DWORD)(0x4dba90u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406f17: cmp dword ptr [0x4dba90], edi */
	if (!m->zf) goto L_406e66;	/* 406f1d: jne 0x406e66 */
	{ DWORD a_ = M32((DWORD)(0x4db858u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406f23: cmp dword ptr [0x4db858], edi */
	if (!m->zf) goto L_406e66;	/* 406f29: jne 0x406e66 */
	{ DWORD a_ = M32((DWORD)(0x4db8b8u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406f2f: cmp dword ptr [0x4db8b8], edi */
	if (!m->zf) goto L_406e66;	/* 406f35: jne 0x406e66 */
	{ DWORD a_ = M32((DWORD)(0x4db714u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406f3b: cmp dword ptr [0x4db714], edi */
	if (!m->zf) goto L_40722a;	/* 406f41: jne 0x40722a */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 406f47: push edi */
	M32((DWORD)(0xa0b36cu)) = m->edi;	/* 406f48: mov dword ptr [0xa0b36c], edi */
	m->esp -= 4; M32(m->esp) = 0x406f53u; native_call(m, 0x41e760u);	/* 406f4e: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 406f53: add esp, 4 */
	M32((DWORD)(0x4dba80u)) = 0x3f800000u;	/* 406f56: mov dword ptr [0x4dba80], 0x3f800000 */
	M32((DWORD)(0x4df018u)) = m->ebx;	/* 406f60: mov dword ptr [0x4df018], ebx */
	m->esp -= 4; M32(m->esp) = 0x406f6bu; native_call(m, 0x452fe0u);	/* 406f66: call 0x452fe0 */
	m->esp -= 4; M32(m->esp) = 0x406f70u; native_call(m, 0x451e60u);	/* 406f6b: call 0x451e60 */
	M32((DWORD)(0x4dbb3cu)) = m->edi;	/* 406f70: mov dword ptr [0x4dbb3c], edi */
	M32((DWORD)(0xa0d7a0u)) = m->ebx;	/* 406f76: mov dword ptr [0xa0d7a0], ebx */
	goto L_407114;	/* 406f7c: jmp 0x407114 */
L_406f81:
	{ DWORD a_ = M32((DWORD)(0x4db714u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406f81: cmp dword ptr [0x4db714], edi */
	if (!m->zf) goto L_40722a;	/* 406f87: jne 0x40722a */
	m->eax = M32((DWORD)(0x4df818u));	/* 406f8d: mov eax, dword ptr [0x4df818] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406f92: cmp eax, edi */
	if (m->zf || m->sf != m->of) goto L_406faf;	/* 406f94: jle 0x406faf */
	m->ecx = M32((DWORD)(0x680bb0u));	/* 406f96: mov ecx, dword ptr [0x680bb0] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 406f9c: dec eax */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 406f9d: add ecx, eax */
	M32((DWORD)(0x4df818u)) = m->eax;	/* 406f9f: mov dword ptr [0x4df818], eax */
	M32((DWORD)(0x76d41cu)) = m->ecx;	/* 406fa4: mov dword ptr [0x76d41c], ecx */
	goto L_407114;	/* 406faa: jmp 0x407114 */
L_406faf:
	m->ecx = M32((DWORD)(0x680bb0u));	/* 406faf: mov ecx, dword ptr [0x680bb0] */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406fb5: cmp ecx, edi */
	if (m->zf || m->sf != m->of) goto L_406fc0;	/* 406fb7: jle 0x406fc0 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 406fb9: dec ecx */
	M32((DWORD)(0x680bb0u)) = m->ecx;	/* 406fba: mov dword ptr [0x680bb0], ecx */
L_406fc0:
	m->ecx = M32((DWORD)(0x680bb0u));	/* 406fc0: mov ecx, dword ptr [0x680bb0] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 406fc6: add ecx, eax */
	M32((DWORD)(0x76d41cu)) = m->ecx;	/* 406fc8: mov dword ptr [0x76d41c], ecx */
	goto L_407114;	/* 406fce: jmp 0x407114 */
L_406fd3:
	{ DWORD a_ = M32((DWORD)(0x4db714u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406fd3: cmp dword ptr [0x4db714], edi */
	if (!m->zf) goto L_40722a;	/* 406fd9: jne 0x40722a */
	m->esi = M32((DWORD)(0x680bb0u));	/* 406fdf: mov esi, dword ptr [0x680bb0] */
	m->ecx = M32((DWORD)(0x4df818u));	/* 406fe5: mov ecx, dword ptr [0x4df818] */
	m->edx = M32((DWORD)(0x67ef30u));	/* 406feb: mov edx, dword ptr [0x67ef30] */
	m->eax = (DWORD)(m->esi + m->ecx*1 + 0x0u);	/* 406ff1: lea eax, [esi + ecx] */
	m->ebx = (DWORD)(m->edx + 0xffffffffu);	/* 406ff4: lea ebx, [edx - 1] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406ff7: cmp eax, ebx */
	if (m->sf == m->of) goto L_40722a;	/* 406ff9: jge 0x40722a */
	{ DWORD a_ = m->ecx, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406fff: cmp ecx, 8 */
	if (m->sf == m->of) goto L_40701c;	/* 407002: jge 0x40701c */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407004: cmp eax, edx */
	if (m->sf == m->of) goto L_407027;	/* 407006: jge 0x407027 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 407008: inc ecx */
	{ DWORD a_ = m->esi, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 407009: add esi, ecx */
	M32((DWORD)(0x4df818u)) = m->ecx;	/* 40700b: mov dword ptr [0x4df818], ecx */
	M32((DWORD)(0x76d41cu)) = m->esi;	/* 407011: mov dword ptr [0x76d41c], esi */
	goto L_407114;	/* 407017: jmp 0x407114 */
L_40701c:
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40701c: cmp eax, edx */
	if (m->sf == m->of) goto L_407027;	/* 40701e: jge 0x407027 */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 407020: inc esi */
	M32((DWORD)(0x680bb0u)) = m->esi;	/* 407021: mov dword ptr [0x680bb0], esi */
L_407027:
	{ DWORD a_ = m->esi, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 407027: add esi, ecx */
	M32((DWORD)(0x76d41cu)) = m->esi;	/* 407029: mov dword ptr [0x76d41c], esi */
	goto L_407114;	/* 40702f: jmp 0x407114 */
L_407034:
	{ DWORD a_ = m->eax, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407034: cmp eax, 6 */
	if (m->sf != m->of) goto L_407114;	/* 407037: jl 0x407114 */
	{ DWORD a_ = m->eax, b_ = 0xeu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40703d: cmp eax, 0xe */
	if (!m->zf && m->sf == m->of) goto L_407114;	/* 407040: jg 0x407114 */
	{ DWORD a_ = M32((DWORD)(0x4db714u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407046: cmp dword ptr [0x4db714], edi */
	if (!m->zf) goto L_40722a;	/* 40704c: jne 0x40722a */
	m->edx = M32((DWORD)(0x680bb0u));	/* 407052: mov edx, dword ptr [0x680bb0] */
	m->esi = (DWORD)(m->eax + 0xfffffffau);	/* 407058: lea esi, [eax - 6] */
	m->eax = M32((DWORD)(0x67ef30u));	/* 40705b: mov eax, dword ptr [0x67ef30] */
	{ DWORD a_ = m->edx, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 407060: add edx, esi */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407062: cmp edx, eax */
	if (m->sf == m->of) goto L_40722a;	/* 407064: jge 0x40722a */
	{ DWORD a_ = m->esi, b_ = M32((DWORD)(0x4df818u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40706a: cmp esi, dword ptr [0x4df818] */
	if (!m->zf) goto L_4070e9;	/* 407070: jne 0x4070e9 */
	{ DWORD a_ = M32((DWORD)(0x4db71cu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407072: cmp dword ptr [0x4db71c], edi */
	if (m->zf) goto L_4070e9;	/* 407078: je 0x4070e9 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40707a: cmp eax, edi */
	if (m->zf || m->sf != m->of) goto L_40722a;	/* 40707c: jle 0x40722a */
	{ DWORD a_ = M32((DWORD)(0x4dba90u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407082: cmp dword ptr [0x4dba90], edi */
	if (!m->zf) goto L_406e66;	/* 407088: jne 0x406e66 */
	{ DWORD a_ = M32((DWORD)(0x4db858u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40708e: cmp dword ptr [0x4db858], edi */
	if (!m->zf) goto L_406e66;	/* 407094: jne 0x406e66 */
	{ DWORD a_ = M32((DWORD)(0x4db8b8u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40709a: cmp dword ptr [0x4db8b8], edi */
	if (!m->zf) goto L_406e66;	/* 4070a0: jne 0x406e66 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4070a6: push edi */
	m->esp -= 4; M32(m->esp) = 0x4070acu; native_call(m, 0x41e760u);	/* 4070a7: call 0x41e760 */
	m->eax = M32((DWORD)(0x4dbaacu));	/* 4070ac: mov eax, dword ptr [0x4dbaac] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4070b1: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4070b4: cmp eax, edi */
	if (m->zf) goto L_4070cb;	/* 4070b6: je 0x4070cb */
	M32((DWORD)(0x4dbbecu)) = m->ebx;	/* 4070b8: mov dword ptr [0x4dbbec], ebx */
	M32((DWORD)(0x4dbbf0u)) = m->edi;	/* 4070be: mov dword ptr [0x4dbbf0], edi */
	m->esp -= 4; M32(m->esp) = 0x4070c9u; native_call(m, 0x405200u);	/* 4070c4: call 0x405200 */
	goto L_4070d7;	/* 4070c9: jmp 0x4070d7 */
L_4070cb:
	M32((DWORD)(0x4dbbf0u)) = m->ebx;	/* 4070cb: mov dword ptr [0x4dbbf0], ebx */
	M32((DWORD)(0x4dbbecu)) = m->edi;	/* 4070d1: mov dword ptr [0x4dbbec], edi */
L_4070d7:
	M32((DWORD)(0x4db71cu)) = m->edi;	/* 4070d7: mov dword ptr [0x4db71c], edi */
	M32((DWORD)(0x4dbaf8u)) = 0x0u;	/* 4070dd: mov dword ptr [0x4dbaf8], 0 */
	goto L_407114;	/* 4070e7: jmp 0x407114 */
L_4070e9:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4070e9: push edi */
	m->esp -= 4; M32(m->esp) = 0x4070efu; native_call(m, 0x41e760u);	/* 4070ea: call 0x41e760 */
	m->eax = M32((DWORD)(0x680bb0u));	/* 4070ef: mov eax, dword ptr [0x680bb0] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4070f4: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4070f7: add eax, esi */
	M32((DWORD)(0x4db71cu)) = m->ebx;	/* 4070f9: mov dword ptr [0x4db71c], ebx */
	M32((DWORD)(0x4dbaf8u)) = 0x0u;	/* 4070ff: mov dword ptr [0x4dbaf8], 0 */
	M32((DWORD)(0x4df818u)) = m->esi;	/* 407109: mov dword ptr [0x4df818], esi */
	M32((DWORD)(0x76d41cu)) = m->eax;	/* 40710f: mov dword ptr [0x76d41c], eax */
L_407114:
	{ DWORD a_ = M32((DWORD)(0x4ded94u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407114: cmp dword ptr [0x4ded94], edi */
	if (m->zf) goto L_40722a;	/* 40711a: je 0x40722a */
	{ DWORD a_ = M32((DWORD)(0x4dbb3cu)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407120: cmp dword ptr [0x4dbb3c], 2 */
	if (!m->zf) goto L_40722a;	/* 407127: jne 0x40722a */
	{ DWORD a_ = M32((DWORD)(0x4db714u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40712d: cmp dword ptr [0x4db714], edi */
	if (!m->zf) goto L_40722a;	/* 407133: jne 0x40722a */
	m->ecx = M32((DWORD)(0x4ded6cu));	/* 407139: mov ecx, dword ptr [0x4ded6c] */
	m->edx = M32((DWORD)(0x4ded68u));	/* 40713f: mov edx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 407145: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 407146: push edx */
	m->esp -= 4; M32(m->esp) = 0x40714cu; native_call(m, 0x4044a0u);	/* 407147: call 0x4044a0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40714c: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0xfu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40714f: sub eax, 0xf */
	if (m->zf) goto L_4071dd;	/* 407152: je 0x4071dd */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 407158: dec eax */
	if (!m->zf) goto L_40722a;	/* 407159: jne 0x40722a */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dda44u)));	/* 40715f: fld dword ptr [0x4dda44] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93d0u)); FPOP();	/* 407165: fcomp dword ptr [0x4a93d0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 40716b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40716d: test ah, 1 */
	if (!m->zf) goto L_40722a;	/* 407170: jne 0x40722a */
	m->esi = M32((DWORD)(0x680bb0u));	/* 407176: mov esi, dword ptr [0x680bb0] */
	m->edx = M32((DWORD)(0x4df818u));	/* 40717c: mov edx, dword ptr [0x4df818] */
	m->ecx = M32((DWORD)(0x67ef30u));	/* 407182: mov ecx, dword ptr [0x67ef30] */
	m->eax = (DWORD)(m->esi + m->edx*1 + 0x0u);	/* 407188: lea eax, [esi + edx] */
	m->edi = (DWORD)(m->ecx + 0xffffffffu);	/* 40718b: lea edi, [ecx - 1] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40718e: cmp eax, edi */
	if (m->sf == m->of) goto L_40722a;	/* 407190: jge 0x40722a */
	{ DWORD a_ = m->edx, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407196: cmp edx, 8 */
	if (m->sf == m->of) goto L_4071bc;	/* 407199: jge 0x4071bc */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40719b: cmp eax, ecx */
	if (m->sf == m->of) goto L_4071c7;	/* 40719d: jge 0x4071c7 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 40719f: inc edx */
	m->edi = M32(m->esp); m->esp += 4;	/* 4071a0: pop edi */
	{ DWORD a_ = m->esi, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4071a1: add esi, edx */
	M32((DWORD)(0x4df818u)) = m->edx;	/* 4071a3: mov dword ptr [0x4df818], edx */
	M32((DWORD)(0x76d41cu)) = m->esi;	/* 4071a9: mov dword ptr [0x76d41c], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4071af: pop esi */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 4071b0: mov dword ptr [0x4dda44], 0 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4071ba: pop ebx */
	m->esp += 4 + 0; return;	/* 4071bb: ret  */
L_4071bc:
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4071bc: cmp eax, ecx */
	if (m->sf == m->of) goto L_4071c7;	/* 4071be: jge 0x4071c7 */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 4071c0: inc esi */
	M32((DWORD)(0x680bb0u)) = m->esi;	/* 4071c1: mov dword ptr [0x680bb0], esi */
L_4071c7:
	{ DWORD a_ = m->esi, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4071c7: add esi, edx */
	m->edi = M32(m->esp); m->esp += 4;	/* 4071c9: pop edi */
	M32((DWORD)(0x76d41cu)) = m->esi;	/* 4071ca: mov dword ptr [0x76d41c], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4071d0: pop esi */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 4071d1: mov dword ptr [0x4dda44], 0 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4071db: pop ebx */
	m->esp += 4 + 0; return;	/* 4071dc: ret  */
L_4071dd:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dda44u)));	/* 4071dd: fld dword ptr [0x4dda44] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93d0u)); FPOP();	/* 4071e3: fcomp dword ptr [0x4a93d0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4071e9: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4071eb: test ah, 1 */
	if (!m->zf) goto L_40722a;	/* 4071ee: jne 0x40722a */
	m->eax = M32((DWORD)(0x4df818u));	/* 4071f0: mov eax, dword ptr [0x4df818] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4071f5: cmp eax, edi */
	if (m->zf || m->sf != m->of) goto L_407201;	/* 4071f7: jle 0x407201 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4071f9: dec eax */
	M32((DWORD)(0x4df818u)) = m->eax;	/* 4071fa: mov dword ptr [0x4df818], eax */
	goto L_407212;	/* 4071ff: jmp 0x407212 */
L_407201:
	m->ecx = M32((DWORD)(0x680bb0u));	/* 407201: mov ecx, dword ptr [0x680bb0] */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407207: cmp ecx, edi */
	if (m->zf || m->sf != m->of) goto L_407212;	/* 407209: jle 0x407212 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 40720b: dec ecx */
	M32((DWORD)(0x680bb0u)) = m->ecx;	/* 40720c: mov dword ptr [0x680bb0], ecx */
L_407212:
	m->ecx = M32((DWORD)(0x680bb0u));	/* 407212: mov ecx, dword ptr [0x680bb0] */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 407218: mov dword ptr [0x4dda44], 0 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 407222: add ecx, eax */
	M32((DWORD)(0x76d41cu)) = m->ecx;	/* 407224: mov dword ptr [0x76d41c], ecx */
L_40722a:
	m->edi = M32(m->esp); m->esp += 4;	/* 40722a: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 40722b: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 40722c: pop ebx */
	m->esp += 4 + 0; return;	/* 40722d: ret  */
}

/* lobbyJoin_keysChat (0x4079c0), lifted by tools/lift.py */
static void lift_4079c0(X86 *m)
{
	m->eax = M32((DWORD)(0x4db714u));	/* 4079c0: mov eax, dword ptr [0x4db714] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4079c5: push esi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 4079c6: xor esi, esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4079c8: push edi */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4079c9: cmp eax, esi */
	if (!m->zf) goto L_407e32;	/* 4079cb: jne 0x407e32 */
	m->eax = M32((DWORD)(0x4dbb3cu));	/* 4079d1: mov eax, dword ptr [0x4dbb3c] */
	m->edi = 0x1u;	/* 4079d6: mov edi, 1 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4079db: cmp eax, edi */
	if (m->zf) goto L_407e32;	/* 4079dd: je 0x407e32 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4079e3: cmp eax, esi */
	if (m->zf) goto L_407e32;	/* 4079e5: je 0x407e32 */
	{ DWORD a_ = M32((DWORD)(0x4db8bcu)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4079eb: cmp dword ptr [0x4db8bc], esi */
	if (!m->zf) goto L_407e32;	/* 4079f1: jne 0x407e32 */
	{ DWORD a_ = M32((DWORD)(0x90d1c4u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4079f7: cmp dword ptr [0x90d1c4], esi */
	if (!m->zf) goto L_407e32;	/* 4079fd: jne 0x407e32 */
	{ DWORD a_ = M32((DWORD)(0x4db8b4u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407a03: cmp dword ptr [0x4db8b4], esi */
	if (m->zf) goto L_407a4d;	/* 407a09: je 0x407a4d */
	m->eax = M32((DWORD)(0x4e0cdcu));	/* 407a0b: mov eax, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 407a10: push eax */
	m->esp -= 4; M32(m->esp) = 0x407a16u; native_call(m, 0x401600u);	/* 407a11: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407a16: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 407a19: test eax, eax */
	if (m->zf) goto L_407e32;	/* 407a1b: je 0x407e32 */
	M32((DWORD)(0x4dbb10u)) = m->esi;	/* 407a21: mov dword ptr [0x4dbb10], esi */
	M32((DWORD)(0x4dbb78u)) = m->esi;	/* 407a27: mov dword ptr [0x4dbb78], esi */
	m->esp -= 4; M32(m->esp) = 0x407a32u; native_call(m, 0x452fe0u);	/* 407a2d: call 0x452fe0 */
	m->ecx = M32((DWORD)(0x4ded18u));	/* 407a32: mov ecx, dword ptr [0x4ded18] */
	{ DWORD v_ = 0x378u; m->esp -= 4; M32(m->esp) = v_; }	/* 407a38: push 0x378 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 407a3d: push ecx */
	M32((DWORD)(0x4db8b4u)) = m->esi;	/* 407a3e: mov dword ptr [0x4db8b4], esi */
	m->esp -= 4; M32(m->esp) = 0x407a4au; native_call(m, M32(0x4a9330u));	/* 407a44: call dword ptr [0x4a9330] */
	m->edi = M32(m->esp); m->esp += 4;	/* 407a4a: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 407a4b: pop esi */
	m->esp += 4 + 0; return;	/* 407a4c: ret  */
L_407a4d:
	m->edx = M32((DWORD)(0x9db0a0u));	/* 407a4d: mov edx, dword ptr [0x9db0a0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 407a53: push edx */
	m->esp -= 4; M32(m->esp) = 0x407a59u; native_call(m, 0x401590u);	/* 407a54: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407a59: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 407a5c: test eax, eax */
	if (m->zf) goto L_407ac3;	/* 407a5e: je 0x407ac3 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dda44u)));	/* 407a60: fld dword ptr [0x4dda44] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93d0u)); FPOP();	/* 407a66: fcomp dword ptr [0x4a93d0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 407a6c: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 407a6e: test ah, 1 */
	if (!m->zf) goto L_407e32;	/* 407a71: jne 0x407e32 */
	m->eax = M32((DWORD)(0x4df818u));	/* 407a77: mov eax, dword ptr [0x4df818] */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 407a7c: mov dword ptr [0x4dda44], 0 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407a86: cmp eax, esi */
	if (m->zf || m->sf != m->of) goto L_407aa1;	/* 407a88: jle 0x407aa1 */
	m->ecx = M32((DWORD)(0x680bb0u));	/* 407a8a: mov ecx, dword ptr [0x680bb0] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 407a90: dec eax */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 407a91: add ecx, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 407a93: pop edi */
	M32((DWORD)(0x4df818u)) = m->eax;	/* 407a94: mov dword ptr [0x4df818], eax */
	M32((DWORD)(0x76d41cu)) = m->ecx;	/* 407a99: mov dword ptr [0x76d41c], ecx */
	m->esi = M32(m->esp); m->esp += 4;	/* 407a9f: pop esi */
	m->esp += 4 + 0; return;	/* 407aa0: ret  */
L_407aa1:
	m->ecx = M32((DWORD)(0x680bb0u));	/* 407aa1: mov ecx, dword ptr [0x680bb0] */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407aa7: cmp ecx, esi */
	if (m->zf || m->sf != m->of) goto L_407ab2;	/* 407aa9: jle 0x407ab2 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 407aab: dec ecx */
	M32((DWORD)(0x680bb0u)) = m->ecx;	/* 407aac: mov dword ptr [0x680bb0], ecx */
L_407ab2:
	m->ecx = M32((DWORD)(0x680bb0u));	/* 407ab2: mov ecx, dword ptr [0x680bb0] */
	m->edi = M32(m->esp); m->esp += 4;	/* 407ab8: pop edi */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 407ab9: add ecx, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 407abb: pop esi */
	M32((DWORD)(0x76d41cu)) = m->ecx;	/* 407abc: mov dword ptr [0x76d41c], ecx */
	m->esp += 4 + 0; return;	/* 407ac2: ret  */
L_407ac3:
	m->edx = M32((DWORD)(0x76d330u));	/* 407ac3: mov edx, dword ptr [0x76d330] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 407ac9: push edx */
	m->esp -= 4; M32(m->esp) = 0x407acfu; native_call(m, 0x401590u);	/* 407aca: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407acf: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 407ad2: test eax, eax */
	if (m->zf) goto L_407b48;	/* 407ad4: je 0x407b48 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dda44u)));	/* 407ad6: fld dword ptr [0x4dda44] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93d0u)); FPOP();	/* 407adc: fcomp dword ptr [0x4a93d0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 407ae2: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 407ae4: test ah, 1 */
	if (!m->zf) goto L_407e32;	/* 407ae7: jne 0x407e32 */
	m->esi = M32((DWORD)(0x680bb0u));	/* 407aed: mov esi, dword ptr [0x680bb0] */
	m->edx = M32((DWORD)(0x4df818u));	/* 407af3: mov edx, dword ptr [0x4df818] */
	m->ecx = M32((DWORD)(0x67ef30u));	/* 407af9: mov ecx, dword ptr [0x67ef30] */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 407aff: mov dword ptr [0x4dda44], 0 */
	m->eax = (DWORD)(m->esi + m->edx*1 + 0x0u);	/* 407b09: lea eax, [esi + edx] */
	m->edi = (DWORD)(m->ecx + 0xffffffffu);	/* 407b0c: lea edi, [ecx - 1] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407b0f: cmp eax, edi */
	if (m->sf == m->of) goto L_407e32;	/* 407b11: jge 0x407e32 */
	{ DWORD a_ = m->edx, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407b17: cmp edx, 8 */
	if (m->sf == m->of) goto L_407b32;	/* 407b1a: jge 0x407b32 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407b1c: cmp eax, ecx */
	if (m->sf == m->of) goto L_407b3d;	/* 407b1e: jge 0x407b3d */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 407b20: inc edx */
	m->edi = M32(m->esp); m->esp += 4;	/* 407b21: pop edi */
	{ DWORD a_ = m->esi, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 407b22: add esi, edx */
	M32((DWORD)(0x4df818u)) = m->edx;	/* 407b24: mov dword ptr [0x4df818], edx */
	M32((DWORD)(0x76d41cu)) = m->esi;	/* 407b2a: mov dword ptr [0x76d41c], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 407b30: pop esi */
	m->esp += 4 + 0; return;	/* 407b31: ret  */
L_407b32:
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407b32: cmp eax, ecx */
	if (m->sf == m->of) goto L_407b3d;	/* 407b34: jge 0x407b3d */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 407b36: inc esi */
	M32((DWORD)(0x680bb0u)) = m->esi;	/* 407b37: mov dword ptr [0x680bb0], esi */
L_407b3d:
	{ DWORD a_ = m->esi, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 407b3d: add esi, edx */
	m->edi = M32(m->esp); m->esp += 4;	/* 407b3f: pop edi */
	M32((DWORD)(0x76d41cu)) = m->esi;	/* 407b40: mov dword ptr [0x76d41c], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 407b46: pop esi */
	m->esp += 4 + 0; return;	/* 407b47: ret  */
L_407b48:
	m->eax = M32((DWORD)(0x4e14f8u));	/* 407b48: mov eax, dword ptr [0x4e14f8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 407b4d: push eax */
	m->esp -= 4; M32(m->esp) = 0x407b53u; native_call(m, 0x401600u);	/* 407b4e: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407b53: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 407b56: test eax, eax */
	if (m->zf) goto L_407b94;	/* 407b58: je 0x407b94 */
	{ DWORD a_ = M32((DWORD)(0x4dba90u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407b5a: cmp dword ptr [0x4dba90], esi */
	if (!m->zf) goto L_407e32;	/* 407b60: jne 0x407e32 */
	{ DWORD a_ = M32((DWORD)(0x4db858u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407b66: cmp dword ptr [0x4db858], esi */
	if (!m->zf) goto L_407e32;	/* 407b6c: jne 0x407e32 */
	{ DWORD a_ = M32((DWORD)(0x4db8b8u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407b72: cmp dword ptr [0x4db8b8], esi */
	if (!m->zf) goto L_407e32;	/* 407b78: jne 0x407e32 */
	{ DWORD a_ = M32((DWORD)(0x67ef30u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407b7e: cmp dword ptr [0x67ef30], esi */
	if (m->zf || m->sf != m->of) goto L_407e32;	/* 407b84: jle 0x407e32 */
	{ DWORD a_ = M32((DWORD)(0x4dbaacu)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407b8a: cmp dword ptr [0x4dbaac], esi */
	if (m->zf) goto L_407bf3;	/* 407b90: je 0x407bf3 */
	goto L_407bdf;	/* 407b92: jmp 0x407bdf */
L_407b94:
	m->ecx = M32((DWORD)(0x9dae70u));	/* 407b94: mov ecx, dword ptr [0x9dae70] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 407b9a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x407ba0u; native_call(m, 0x401600u);	/* 407b9b: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407ba0: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 407ba3: test eax, eax */
	if (m->zf) goto L_407c02;	/* 407ba5: je 0x407c02 */
	{ DWORD a_ = M32((DWORD)(0x4dba90u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407ba7: cmp dword ptr [0x4dba90], esi */
	if (!m->zf) goto L_407e32;	/* 407bad: jne 0x407e32 */
	{ DWORD a_ = M32((DWORD)(0x4db858u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407bb3: cmp dword ptr [0x4db858], esi */
	if (!m->zf) goto L_407e32;	/* 407bb9: jne 0x407e32 */
	{ DWORD a_ = M32((DWORD)(0x4db8b8u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407bbf: cmp dword ptr [0x4db8b8], esi */
	if (!m->zf) goto L_407e32;	/* 407bc5: jne 0x407e32 */
	{ DWORD a_ = M32((DWORD)(0x67ef30u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407bcb: cmp dword ptr [0x67ef30], esi */
	if (m->zf || m->sf != m->of) goto L_407e32;	/* 407bd1: jle 0x407e32 */
	{ DWORD a_ = M32((DWORD)(0x4dbaacu)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407bd7: cmp dword ptr [0x4dbaac], esi */
	if (m->zf) goto L_407bf3;	/* 407bdd: je 0x407bf3 */
L_407bdf:
	M32((DWORD)(0x4dbbecu)) = m->edi;	/* 407bdf: mov dword ptr [0x4dbbec], edi */
	M32((DWORD)(0x4dbbf0u)) = m->esi;	/* 407be5: mov dword ptr [0x4dbbf0], esi */
	m->esp -= 4; M32(m->esp) = 0x407bf0u; native_call(m, 0x405200u);	/* 407beb: call 0x405200 */
	m->edi = M32(m->esp); m->esp += 4;	/* 407bf0: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 407bf1: pop esi */
	m->esp += 4 + 0; return;	/* 407bf2: ret  */
L_407bf3:
	M32((DWORD)(0x4dbbf0u)) = m->edi;	/* 407bf3: mov dword ptr [0x4dbbf0], edi */
	M32((DWORD)(0x4dbbecu)) = m->esi;	/* 407bf9: mov dword ptr [0x4dbbec], esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 407bff: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 407c00: pop esi */
	m->esp += 4 + 0; return;	/* 407c01: ret  */
L_407c02:
	m->edx = M32((DWORD)(0x76d48cu));	/* 407c02: mov edx, dword ptr [0x76d48c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 407c08: push edx */
	m->esp -= 4; M32(m->esp) = 0x407c0eu; native_call(m, 0x401600u);	/* 407c09: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407c0e: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 407c11: test eax, eax */
	if (m->zf) goto L_407c3e;	/* 407c13: je 0x407c3e */
	M32((DWORD)(0xa0b36cu)) = m->esi;	/* 407c15: mov dword ptr [0xa0b36c], esi */
	m->esp -= 4; M32(m->esp) = 0x407c20u; native_call(m, 0x452fe0u);	/* 407c1b: call 0x452fe0 */
	m->esp -= 4; M32(m->esp) = 0x407c25u; native_call(m, 0x451e60u);	/* 407c20: call 0x451e60 */
	M32((DWORD)(0x4df018u)) = m->edi;	/* 407c25: mov dword ptr [0x4df018], edi */
	M32((DWORD)(0x4dbb3cu)) = m->esi;	/* 407c2b: mov dword ptr [0x4dbb3c], esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 407c31: pop edi */
	M32((DWORD)(0x4dba80u)) = 0x3f800000u;	/* 407c32: mov dword ptr [0x4dba80], 0x3f800000 */
	m->esi = M32(m->esp); m->esp += 4;	/* 407c3c: pop esi */
	m->esp += 4 + 0; return;	/* 407c3d: ret  */
L_407c3e:
	m->eax = M32((DWORD)(0x4e1524u));	/* 407c3e: mov eax, dword ptr [0x4e1524] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 407c43: push eax */
	m->esp -= 4; M32(m->esp) = 0x407c49u; native_call(m, 0x401600u);	/* 407c44: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407c49: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 407c4c: test eax, eax */
	if (m->zf) goto L_407ca3;	/* 407c4e: je 0x407ca3 */
	M32((DWORD)(0xa0b36cu)) = m->esi;	/* 407c50: mov dword ptr [0xa0b36c], esi */
	M32((DWORD)(0x4dba80u)) = 0x3f800000u;	/* 407c56: mov dword ptr [0x4dba80], 0x3f800000 */
	M32((DWORD)(0x4df018u)) = m->edi;	/* 407c60: mov dword ptr [0x4df018], edi */
	M32((DWORD)(0x76d484u)) = 0xffffffffu;	/* 407c66: mov dword ptr [0x76d484], 0xffffffff */
	M32((DWORD)(0x4db718u)) = m->esi;	/* 407c70: mov dword ptr [0x4db718], esi */
	m->esp -= 4; M32(m->esp) = 0x407c7bu; native_call(m, 0x452fe0u);	/* 407c76: call 0x452fe0 */
	m->esp -= 4; M32(m->esp) = 0x407c80u; native_call(m, 0x451e60u);	/* 407c7b: call 0x451e60 */
	{ DWORD a_ = M32((DWORD)(0x4db8b8u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407c80: cmp dword ptr [0x4db8b8], edi */
	if (!m->zf) goto L_407c9a;	/* 407c86: jne 0x407c9a */
	M32((DWORD)(0x4db8b8u)) = m->esi;	/* 407c88: mov dword ptr [0x4db8b8], esi */
	M32((DWORD)(0x4db858u)) = m->esi;	/* 407c8e: mov dword ptr [0x4db858], esi */
	M32((DWORD)(0x4df018u)) = m->esi;	/* 407c94: mov dword ptr [0x4df018], esi */
L_407c9a:
	M32((DWORD)(0xa0d7a0u)) = m->edi;	/* 407c9a: mov dword ptr [0xa0d7a0], edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 407ca0: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 407ca1: pop esi */
	m->esp += 4 + 0; return;	/* 407ca2: ret  */
L_407ca3:
	m->ecx = M32((DWORD)(0x4e0cdcu));	/* 407ca3: mov ecx, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 407ca9: push ecx */
	m->esp -= 4; M32(m->esp) = 0x407cafu; native_call(m, 0x401600u);	/* 407caa: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407caf: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 407cb2: test eax, eax */
	if (m->zf) goto L_407d03;	/* 407cb4: je 0x407d03 */
	{ DWORD a_ = M32((DWORD)(0x4dba90u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407cb6: cmp dword ptr [0x4dba90], esi */
	if (!m->zf) goto L_407e32;	/* 407cbc: jne 0x407e32 */
	{ DWORD a_ = M32((DWORD)(0x4db858u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407cc2: cmp dword ptr [0x4db858], esi */
	if (!m->zf) goto L_407e32;	/* 407cc8: jne 0x407e32 */
	{ DWORD a_ = M32((DWORD)(0x4db8b8u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407cce: cmp dword ptr [0x4db8b8], esi */
	if (!m->zf) goto L_407e32;	/* 407cd4: jne 0x407e32 */
	M32((DWORD)(0xa0b36cu)) = m->esi;	/* 407cda: mov dword ptr [0xa0b36c], esi */
	M32((DWORD)(0x4dba80u)) = 0x3f800000u;	/* 407ce0: mov dword ptr [0x4dba80], 0x3f800000 */
	M32((DWORD)(0x4df018u)) = m->edi;	/* 407cea: mov dword ptr [0x4df018], edi */
	m->esp -= 4; M32(m->esp) = 0x407cf5u; native_call(m, 0x452fe0u);	/* 407cf0: call 0x452fe0 */
	m->esp -= 4; M32(m->esp) = 0x407cfau; native_call(m, 0x451e60u);	/* 407cf5: call 0x451e60 */
	M32((DWORD)(0x4dbb3cu)) = m->esi;	/* 407cfa: mov dword ptr [0x4dbb3c], esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 407d00: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 407d01: pop esi */
	m->esp += 4 + 0; return;	/* 407d02: ret  */
L_407d03:
	m->edx = M32((DWORD)(0x4e14f4u));	/* 407d03: mov edx, dword ptr [0x4e14f4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 407d09: push edx */
	m->esp -= 4; M32(m->esp) = 0x407d0fu; native_call(m, 0x401600u);	/* 407d0a: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407d0f: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 407d12: test eax, eax */
	if (m->zf) goto L_407d9f;	/* 407d14: je 0x407d9f */
	{ DWORD a_ = M32((DWORD)(0x4dba90u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407d1a: cmp dword ptr [0x4dba90], esi */
	if (!m->zf) goto L_407e32;	/* 407d20: jne 0x407e32 */
	{ DWORD a_ = M32((DWORD)(0x4db858u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407d26: cmp dword ptr [0x4db858], esi */
	if (!m->zf) goto L_407e32;	/* 407d2c: jne 0x407e32 */
	{ DWORD a_ = M32((DWORD)(0x4db8b8u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407d32: cmp dword ptr [0x4db8b8], esi */
	if (!m->zf) goto L_407e32;	/* 407d38: jne 0x407e32 */
	{ DWORD a_ = M32((DWORD)(0x4db854u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407d3e: cmp dword ptr [0x4db854], esi */
	if (m->zf) goto L_407d51;	/* 407d44: je 0x407d51 */
	M32((DWORD)(0x4db718u)) = m->esi;	/* 407d46: mov dword ptr [0x4db718], esi */
	m->esp -= 4; M32(m->esp) = 0x407d51u; native_call(m, 0x451e60u);	/* 407d4c: call 0x451e60 */
L_407d51:
	{ DWORD a_ = M32((DWORD)(0x4dba84u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407d51: cmp dword ptr [0x4dba84], esi */
	if (m->zf) goto L_407d5e;	/* 407d57: je 0x407d5e */
	m->esp -= 4; M32(m->esp) = 0x407d5eu; native_call(m, 0x452fe0u);	/* 407d59: call 0x452fe0 */
L_407d5e:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 407d5e: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 407d5f: push edi */
	M32((DWORD)(0xa0b368u)) = m->esi;	/* 407d60: mov dword ptr [0xa0b368], esi */
	m->esp -= 4; M32(m->esp) = 0x407d6bu; native_call(m, 0x452ec0u);	/* 407d66: call 0x452ec0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407d6b: add esp, 8 */
	M32((DWORD)(0x4dba90u)) = m->edi;	/* 407d6e: mov dword ptr [0x4dba90], edi */
	M32((DWORD)(0x4dba84u)) = m->edi;	/* 407d74: mov dword ptr [0x4dba84], edi */
	M32((DWORD)(0x680bb8u)) = m->esi;	/* 407d7a: mov dword ptr [0x680bb8], esi */
	M32((DWORD)(0x67ef30u)) = m->esi;	/* 407d80: mov dword ptr [0x67ef30], esi */
	M32((DWORD)(0x4dbaacu)) = m->esi;	/* 407d86: mov dword ptr [0x4dbaac], esi */
	M32((DWORD)(0x4db854u)) = m->esi;	/* 407d8c: mov dword ptr [0x4db854], esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 407d92: pop edi */
	M32((DWORD)(0x4dba80u)) = 0x43160000u;	/* 407d93: mov dword ptr [0x4dba80], 0x43160000 */
	m->esi = M32(m->esp); m->esp += 4;	/* 407d9d: pop esi */
	m->esp += 4 + 0; return;	/* 407d9e: ret  */
L_407d9f:
	m->eax = M32((DWORD)(0x4e1528u));	/* 407d9f: mov eax, dword ptr [0x4e1528] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 407da4: push eax */
	m->esp -= 4; M32(m->esp) = 0x407daau; native_call(m, 0x401600u);	/* 407da5: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407daa: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 407dad: test eax, eax */
	if (m->zf) goto L_407e09;	/* 407daf: je 0x407e09 */
	{ DWORD a_ = M32((DWORD)(0x4dba90u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407db1: cmp dword ptr [0x4dba90], esi */
	if (!m->zf) goto L_407e32;	/* 407db7: jne 0x407e32 */
	{ DWORD a_ = M32((DWORD)(0x4db858u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407db9: cmp dword ptr [0x4db858], esi */
	if (!m->zf) goto L_407e32;	/* 407dbf: jne 0x407e32 */
	{ DWORD a_ = M32((DWORD)(0x4db8b8u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407dc1: cmp dword ptr [0x4db8b8], esi */
	if (!m->zf) goto L_407e32;	/* 407dc7: jne 0x407e32 */
	M32((DWORD)(0x4db718u)) = m->esi;	/* 407dc9: mov dword ptr [0x4db718], esi */
	m->esp -= 4; M32(m->esp) = 0x407dd4u; native_call(m, 0x451e60u);	/* 407dcf: call 0x451e60 */
	m->esp -= 4; M32(m->esp) = 0x407dd9u; native_call(m, 0x452fe0u);	/* 407dd4: call 0x452fe0 */
	M32((DWORD)(0xa0b368u)) = m->esi;	/* 407dd9: mov dword ptr [0xa0b368], esi */
	m->esp -= 4; M32(m->esp) = 0x407de4u; native_call(m, 0x4060f0u);	/* 407ddf: call 0x4060f0 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407de4: cmp eax, edi */
	if (!m->zf) goto L_407e32;	/* 407de6: jne 0x407e32 */
	M32((DWORD)(0x4dbaacu)) = m->edi;	/* 407de8: mov dword ptr [0x4dbaac], edi */
	M32((DWORD)(0x4db858u)) = m->edi;	/* 407dee: mov dword ptr [0x4db858], edi */
	M32((DWORD)(0x4db854u)) = m->edi;	/* 407df4: mov dword ptr [0x4db854], edi */
	M32((DWORD)(0x4db718u)) = m->edi;	/* 407dfa: mov dword ptr [0x4db718], edi */
	M32((DWORD)(0x4dba84u)) = m->esi;	/* 407e00: mov dword ptr [0x4dba84], esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 407e06: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 407e07: pop esi */
	m->esp += 4 + 0; return;	/* 407e08: ret  */
L_407e09:
	m->ecx = M32((DWORD)(0x4e1514u));	/* 407e09: mov ecx, dword ptr [0x4e1514] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 407e0f: push ecx */
	m->esp -= 4; M32(m->esp) = 0x407e15u; native_call(m, 0x401600u);	/* 407e10: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407e15: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 407e18: test eax, eax */
	if (m->zf) goto L_407e32;	/* 407e1a: je 0x407e32 */
	{ DWORD a_ = M32((DWORD)(0x4db714u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407e1c: cmp dword ptr [0x4db714], esi */
	if (!m->zf) goto L_407e32;	/* 407e22: jne 0x407e32 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 407e24: push esi */
	m->esp -= 4; M32(m->esp) = 0x407e2au; native_call(m, 0x41e760u);	/* 407e25: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407e2a: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x407e32u; native_call(m, 0x405230u);	/* 407e2d: call 0x405230 */
L_407e32:
	m->edi = M32(m->esp); m->esp += 4;	/* 407e32: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 407e33: pop esi */
	m->esp += 4 + 0; return;	/* 407e34: ret  */
}

/* room_4355b0 (0x4355b0), lifted by tools/lift.py */
static void lift_4355b0(X86 *m)
{
	m->eax = M32((DWORD)(0x4ded60u));	/* 4355b0: mov eax, dword ptr [0x4ded60] */
	m->ecx = 0x2u;	/* 4355b5: mov ecx, 2 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4355ba: push ebx */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4355bb: cmp eax, ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4355bd: push ebp */
	if (m->zf) goto L_4356ed;	/* 4355be: je 0x4356ed */
	m->ebx = 0x1u;	/* 4355c4: mov ebx, 1 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 4355c9: xor ebp, ebp */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4355cb: cmp eax, ebx */
	if (!m->zf) goto L_435693;	/* 4355cd: jne 0x435693 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4355d3: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4355d4: push edi */
	M32((DWORD)(0x4dba88u)) = m->ebp;	/* 4355d5: mov dword ptr [0x4dba88], ebp */
	M32((DWORD)(0x67ef14u)) = m->ebx;	/* 4355db: mov dword ptr [0x67ef14], ebx */
	M32((DWORD)(0x67ef04u)) = m->ebx;	/* 4355e1: mov dword ptr [0x67ef04], ebx */
	m->esp -= 4; M32(m->esp) = 0x4355ecu; native_call(m, 0x457310u);	/* 4355e7: call 0x457310 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4355ec: push ebp */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4355ed: push ebp */
	M32((DWORD)(0x9dce48u)) = m->ebp;	/* 4355ee: mov dword ptr [0x9dce48], ebp */
	m->esp -= 4; M32(m->esp) = 0x4355f9u; native_call(m, 0x452ec0u);	/* 4355f4: call 0x452ec0 */
	m->eax = M32((DWORD)(0x5b1b54u));	/* 4355f9: mov eax, dword ptr [0x5b1b54] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4355fe: xor edx, edx */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(0x5b1b53u)));	/* 435600: movsx ecx, byte ptr [0x5b1b53] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 8) & 0xff)) & 0xff) << 0);	/* 435607: mov dl, ah */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 435609: push ebp */
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43560a: and eax, 0xff */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43560f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 435610: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 435611: push ecx */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x5b1b51u)));	/* 435612: movsx eax, byte ptr [0x5b1b51] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 435619: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43561a: push ecx */
	{ DWORD v_ = 0x9dd570u; m->esp -= 4; M32(m->esp) = v_; }	/* 43561b: push 0x9dd570 */
	{ DWORD v_ = 0x5b1b30u; m->esp -= 4; M32(m->esp) = v_; }	/* 435620: push 0x5b1b30 */
	m->esp -= 4; M32(m->esp) = 0x43562au; native_call(m, 0x453090u);	/* 435625: call 0x453090 */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(0x5b1b50u)));	/* 43562a: movsx ecx, byte ptr [0x5b1b50] */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x5b1b53u)));	/* 435631: movsx eax, byte ptr [0x5b1b53] */
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(0x5b1b52u)));	/* 435638: movsx edx, byte ptr [0x5b1b52] */
	M32((DWORD)(0x9dad94u)) = m->ecx;	/* 43563f: mov dword ptr [0x9dad94], ecx */
	m->ecx = 0x8u;	/* 435645: mov ecx, 8 */
	m->esi = 0x5b1b30u;	/* 43564a: mov esi, 0x5b1b30 */
	m->edi = 0x67fb44u;	/* 43564f: mov edi, 0x67fb44 */
	M32((DWORD)(0x76d368u)) = m->eax;	/* 435654: mov dword ptr [0x76d368], eax */
	m->eax = M32((DWORD)(0x5b1b54u));	/* 435659: mov eax, dword ptr [0x5b1b54] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43565e: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 435660: mov ecx, eax */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435662: add esp, 0x28 */
	M32((DWORD)(0x9da3e0u)) = m->edx;	/* 435665: mov dword ptr [0x9da3e0], edx */
	{ DWORD a_ = m->ecx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43566b: and ecx, 0xff */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 435671: xor edx, edx */
	M32((DWORD)(0x4df8e8u)) = m->ecx;	/* 435673: mov dword ptr [0x4df8e8], ecx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 8) & 0xff)) & 0xff) << 0);	/* 435679: mov dl, ah */
	m->eax = M32((DWORD)(0x4ded60u));	/* 43567b: mov eax, dword ptr [0x4ded60] */
	m->edi = M32(m->esp); m->esp += 4;	/* 435680: pop edi */
	M32((DWORD)(0x76d408u)) = m->edx;	/* 435681: mov dword ptr [0x76d408], edx */
	M32((DWORD)(0x4ded54u)) = m->ebx;	/* 435687: mov dword ptr [0x4ded54], ebx */
	m->ecx = 0x2u;	/* 43568d: mov ecx, 2 */
	m->esi = M32(m->esp); m->esp += 4;	/* 435692: pop esi */
L_435693:
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 435693: cmp eax, ebp */
	if (!m->zf) goto L_4356ac;	/* 435695: jne 0x4356ac */
	M32((DWORD)(0x4dba88u)) = m->ebp;	/* 435697: mov dword ptr [0x4dba88], ebp */
	M32((DWORD)(0x4ded54u)) = m->ebp;	/* 43569d: mov dword ptr [0x4ded54], ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4356a3: pop ebp */
	M32((DWORD)(0x4ded60u)) = m->ecx;	/* 4356a4: mov dword ptr [0x4ded60], ecx */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4356aa: pop ebx */
	m->esp += 4 + 0; return;	/* 4356ab: ret  */
L_4356ac:
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4356ac: cmp eax, 3 */
	if (!m->zf) goto L_4356cc;	/* 4356af: jne 0x4356cc */
	M32((DWORD)(0x4dba88u)) = m->ebp;	/* 4356b1: mov dword ptr [0x4dba88], ebp */
	M32((DWORD)(0x4ded54u)) = m->ebp;	/* 4356b7: mov dword ptr [0x4ded54], ebp */
	M32((DWORD)(0x907b2cu)) = m->ebx;	/* 4356bd: mov dword ptr [0x907b2c], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4356c3: pop ebp */
	M32((DWORD)(0x4ded60u)) = m->ecx;	/* 4356c4: mov dword ptr [0x4ded60], ecx */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4356ca: pop ebx */
	m->esp += 4 + 0; return;	/* 4356cb: ret  */
L_4356cc:
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4356cc: cmp eax, 4 */
	if (!m->zf) goto L_4356ed;	/* 4356cf: jne 0x4356ed */
	{ DWORD v_ = 0x2au; m->esp -= 4; M32(m->esp) = v_; }	/* 4356d1: push 0x2a */
	M32((DWORD)(0x4dba88u)) = m->ebp;	/* 4356d3: mov dword ptr [0x4dba88], ebp */
	M32((DWORD)(0x4ded60u)) = m->ecx;	/* 4356d9: mov dword ptr [0x4ded60], ecx */
	M32((DWORD)(0x4ded54u)) = m->ebp;	/* 4356df: mov dword ptr [0x4ded54], ebp */
	m->esp -= 4; M32(m->esp) = 0x4356eau; native_call(m, 0x41ee40u);	/* 4356e5: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4356ea: add esp, 4 */
L_4356ed:
	m->ebp = M32(m->esp); m->esp += 4;	/* 4356ed: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4356ee: pop ebx */
	m->esp += 4 + 0; return;	/* 4356ef: ret  */
}

/* arena_405b80 (0x405b80), lifted by tools/lift.py */
static void lift_405b80(X86 *m)
{
	m->eax = M32((DWORD)(0x4ded60u));	/* 405b80: mov eax, dword ptr [0x4ded60] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 405b85: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 405b86: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 405b87: push esi */
	m->esi = 0x2u;	/* 405b88: mov esi, 2 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 405b8d: cmp eax, esi */
	if (m->zf) goto L_405ce5;	/* 405b8f: je 0x405ce5 */
	m->ebp = 0x1u;	/* 405b95: mov ebp, 1 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 405b9a: xor ebx, ebx */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 405b9c: cmp eax, ebp */
	if (!m->zf) goto L_405c7a;	/* 405b9e: jne 0x405c7a */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 405ba4: push edi */
	M32((DWORD)(0x4dba88u)) = m->ebx;	/* 405ba5: mov dword ptr [0x4dba88], ebx */
	M32((DWORD)(0x67ef14u)) = m->ebp;	/* 405bab: mov dword ptr [0x67ef14], ebp */
	M32((DWORD)(0x67ef04u)) = m->ebp;	/* 405bb1: mov dword ptr [0x67ef04], ebp */
	m->esp -= 4; M32(m->esp) = 0x405bbcu; native_call(m, 0x457310u);	/* 405bb7: call 0x457310 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 405bbc: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 405bbd: push ebx */
	M32((DWORD)(0x4dbb3cu)) = m->ebx;	/* 405bbe: mov dword ptr [0x4dbb3c], ebx */
	m->esp -= 4; M32(m->esp) = 0x405bc9u; native_call(m, 0x452ec0u);	/* 405bc4: call 0x452ec0 */
	m->eax = M32((DWORD)(0x4dedd0u));	/* 405bc9: mov eax, dword ptr [0x4dedd0] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 405bce: xor ecx, ecx */
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(0x4ded43u)));	/* 405bd0: movsx edx, byte ptr [0x4ded43] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 405bd7: push eax */
	m->eax = M32((DWORD)(0x4ded44u));	/* 405bd8: mov eax, dword ptr [0x4ded44] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->eax >> 8) & 0xff)) & 0xff) << 0);	/* 405bdd: mov cl, ah */
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 405bdf: and eax, 0xff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 405be4: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 405be5: push eax */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(0x4ded42u)));	/* 405be6: movsx ecx, byte ptr [0x4ded42] */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x4ded41u)));	/* 405bed: movsx eax, byte ptr [0x4ded41] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 405bf4: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 405bf5: push eax */
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(0x4ded40u)));	/* 405bf6: movsx edx, byte ptr [0x4ded40] */
	{ DWORD a_ = m->ecx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 405bfd: shl ecx, 8 */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 405c00: or ecx, edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 405c02: push ecx */
	{ DWORD v_ = 0x4dedb0u; m->esp -= 4; M32(m->esp) = v_; }	/* 405c03: push 0x4dedb0 */
	{ DWORD v_ = 0x4ded20u; m->esp -= 4; M32(m->esp) = v_; }	/* 405c08: push 0x4ded20 */
	m->esp -= 4; M32(m->esp) = 0x405c12u; native_call(m, 0x453090u);	/* 405c0d: call 0x453090 */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x4ded40u)));	/* 405c12: movsx eax, byte ptr [0x4ded40] */
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(0x4ded43u)));	/* 405c19: movsx edx, byte ptr [0x4ded43] */
	m->ecx = 0x8u;	/* 405c20: mov ecx, 8 */
	m->esi = 0x4ded20u;	/* 405c25: mov esi, 0x4ded20 */
	m->edi = 0x67fb44u;	/* 405c2a: mov edi, 0x67fb44 */
	M32((DWORD)(0x9dad94u)) = m->eax;	/* 405c2f: mov dword ptr [0x9dad94], eax */
	m->eax = M32((DWORD)(0x4ded44u));	/* 405c34: mov eax, dword ptr [0x4ded44] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 405c39: add esp, 0x28 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 405c3c: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(0x4ded42u)));	/* 405c3e: movsx ecx, byte ptr [0x4ded42] */
	M32((DWORD)(0x9da3e0u)) = m->ecx;	/* 405c45: mov dword ptr [0x9da3e0], ecx */
	m->ecx = m->eax;	/* 405c4b: mov ecx, eax */
	M32((DWORD)(0x76d368u)) = m->edx;	/* 405c4d: mov dword ptr [0x76d368], edx */
	{ DWORD a_ = m->ecx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 405c53: and ecx, 0xff */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 405c59: xor edx, edx */
	M32((DWORD)(0x4df8e8u)) = m->ecx;	/* 405c5b: mov dword ptr [0x4df8e8], ecx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 8) & 0xff)) & 0xff) << 0);	/* 405c61: mov dl, ah */
	m->eax = M32((DWORD)(0x4ded60u));	/* 405c63: mov eax, dword ptr [0x4ded60] */
	M32((DWORD)(0x76d408u)) = m->edx;	/* 405c68: mov dword ptr [0x76d408], edx */
	M32((DWORD)(0x4ded54u)) = m->ebp;	/* 405c6e: mov dword ptr [0x4ded54], ebp */
	m->esi = 0x2u;	/* 405c74: mov esi, 2 */
	m->edi = M32(m->esp); m->esp += 4;	/* 405c79: pop edi */
L_405c7a:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 405c7a: cmp eax, ebx */
	if (!m->zf) goto L_405c99;	/* 405c7c: jne 0x405c99 */
	m->esp -= 4; M32(m->esp) = 0x405c83u; native_call(m, 0x451e60u);	/* 405c7e: call 0x451e60 */
	M32((DWORD)(0x4ded60u)) = m->esi;	/* 405c83: mov dword ptr [0x4ded60], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 405c89: pop esi */
	M32((DWORD)(0x4dba88u)) = m->ebx;	/* 405c8a: mov dword ptr [0x4dba88], ebx */
	M32((DWORD)(0x4ded54u)) = m->ebx;	/* 405c90: mov dword ptr [0x4ded54], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 405c96: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 405c97: pop ebx */
	m->esp += 4 + 0; return;	/* 405c98: ret  */
L_405c99:
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 405c99: cmp eax, 3 */
	if (!m->zf) goto L_405cbf;	/* 405c9c: jne 0x405cbf */
	m->esp -= 4; M32(m->esp) = 0x405ca3u; native_call(m, 0x451e60u);	/* 405c9e: call 0x451e60 */
	M32((DWORD)(0x4ded60u)) = m->esi;	/* 405ca3: mov dword ptr [0x4ded60], esi */
	M32((DWORD)(0x907b2cu)) = m->ebp;	/* 405ca9: mov dword ptr [0x907b2c], ebp */
	m->esi = M32(m->esp); m->esp += 4;	/* 405caf: pop esi */
	M32((DWORD)(0x4dba88u)) = m->ebx;	/* 405cb0: mov dword ptr [0x4dba88], ebx */
	M32((DWORD)(0x4ded54u)) = m->ebx;	/* 405cb6: mov dword ptr [0x4ded54], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 405cbc: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 405cbd: pop ebx */
	m->esp += 4 + 0; return;	/* 405cbe: ret  */
L_405cbf:
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 405cbf: cmp eax, 4 */
	if (!m->zf) goto L_405ce5;	/* 405cc2: jne 0x405ce5 */
	m->esp -= 4; M32(m->esp) = 0x405cc9u; native_call(m, 0x451e60u);	/* 405cc4: call 0x451e60 */
	{ DWORD v_ = 0x46u; m->esp -= 4; M32(m->esp) = v_; }	/* 405cc9: push 0x46 */
	M32((DWORD)(0x4dba88u)) = m->ebx;	/* 405ccb: mov dword ptr [0x4dba88], ebx */
	M32((DWORD)(0x4ded60u)) = m->esi;	/* 405cd1: mov dword ptr [0x4ded60], esi */
	M32((DWORD)(0x4ded54u)) = m->ebx;	/* 405cd7: mov dword ptr [0x4ded54], ebx */
	m->esp -= 4; M32(m->esp) = 0x405ce2u; native_call(m, 0x41ee40u);	/* 405cdd: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 405ce2: add esp, 4 */
L_405ce5:
	m->esi = M32(m->esp); m->esp += 4;	/* 405ce5: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 405ce6: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 405ce7: pop ebx */
	m->esp += 4 + 0; return;	/* 405ce8: ret  */
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
