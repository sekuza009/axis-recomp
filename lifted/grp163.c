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

static void lift_430400(X86 *m);

/* app_checkCdAndLoad (0x430400), lifted by tools/lift.py */
static void lift_430400(X86 *m)
{
	m->eax = M32((DWORD)&g_lift_fs0);	/* 430400: mov eax, dword ptr fs:[0] */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 430406: push -1 */
	{ DWORD v_ = 0x4a87feu; m->esp -= 4; M32(m->esp) = v_; }	/* 430408: push 0x4a87fe */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43040d: push eax */
	M32((DWORD)&g_lift_fs0) = m->esp;	/* 43040e: mov dword ptr fs:[0], esp */
	{ DWORD a_ = m->esp, b_ = 0x144u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 430415: sub esp, 0x144 */
	m->ecx = 0x100u;	/* 43041b: mov ecx, 0x100 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 430420: xor eax, eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 430422: push ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 430423: push edi */
	m->edi = 0x4d1688u;	/* 430424: mov edi, 0x4d1688 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 430429: xor ebx, ebx */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 43042b: rep stosd dword ptr es:[edi], eax */
	m->ecx = 0x100u;	/* 43042d: mov ecx, 0x100 */
	m->edi = 0x4d1a98u;	/* 430432: mov edi, 0x4d1a98 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 430437: rep stosd dword ptr es:[edi], eax */
	M32((DWORD)(0x9dd84cu)) = m->ebx;	/* 430439: mov dword ptr [0x9dd84c], ebx */
	m->esp -= 4; M32(m->esp) = 0x430444u; native_call(m, 0x4515d0u);	/* 43043f: call 0x4515d0 */
	m->esp -= 4; M32(m->esp) = 0x430449u; native_call(m, 0x42bde0u);	/* 430444: call 0x42bde0 */
	m->esp -= 4; M32(m->esp) = 0x43044eu; native_call(m, 0x46c270u);	/* 430449: call 0x46c270 */
	m->esp -= 4; M32(m->esp) = 0x430453u; native_call(m, 0x42bee0u);	/* 43044e: call 0x42bee0 */
	m->esp -= 4; M32(m->esp) = 0x430458u; native_call(m, 0x430390u);	/* 430453: call 0x430390 */
	m->esp -= 4; M32(m->esp) = 0x43045du; native_call(m, 0x42b590u);	/* 430458: call 0x42b590 */
	m->esp -= 4; M32(m->esp) = 0x430462u; native_call(m, 0x42b830u);	/* 43045d: call 0x42b830 */
	m->esp -= 4; M32(m->esp) = 0x430467u; native_call(m, 0x42ba40u);	/* 430462: call 0x42ba40 */
	m->esp -= 4; M32(m->esp) = 0x43046cu; native_call(m, 0x42bc00u);	/* 430467: call 0x42bc00 */
	m->esp -= 4; M32(m->esp) = 0x430471u; native_call(m, 0x4460d0u);	/* 43046c: call 0x4460d0 */
	m->esp -= 4; M32(m->esp) = 0x430476u; native_call(m, 0x42f940u);	/* 430471: call 0x42f940 */
	m->esp -= 4; M32(m->esp) = 0x43047bu; native_call(m, 0x42fb40u);	/* 430476: call 0x42fb40 */
	{ DWORD v_ = 0x280u; m->esp -= 4; M32(m->esp) = v_; }	/* 43047b: push 0x280 */
	m->esp -= 4; M32(m->esp) = 0x430485u; native_call(m, 0x4017b0u);	/* 430480: call 0x4017b0 */
	{ DWORD v_ = 0x1e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 430485: push 0x1e0 */
	m->esp -= 4; M32(m->esp) = 0x43048fu; native_call(m, 0x4017c0u);	/* 43048a: call 0x4017c0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43048f: add esp, 8 */
	M32((DWORD)(0x4d7348u)) = m->ebx;	/* 430492: mov dword ptr [0x4d7348], ebx */
	m->esp -= 4; M32(m->esp) = 0x43049du; native_call(m, 0x4302d0u);	/* 430498: call 0x4302d0 */
	m->eax = M32((DWORD)(0x9dbf0cu));	/* 43049d: mov eax, dword ptr [0x9dbf0c] */
	M32((DWORD)(0x4d23d0u)) = 0x1u;	/* 4304a2: mov dword ptr [0x4d23d0], 1 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4304ac: cmp eax, ebx */
	M32((DWORD)(0x67ef14u)) = m->ebx;	/* 4304ae: mov dword ptr [0x67ef14], ebx */
	if (!m->zf) goto L_43050c;	/* 4304b4: jne 0x43050c */
	m->eax = M32((DWORD)(m->esp + 0x15cu));	/* 4304b6: mov eax, dword ptr [esp + 0x15c] */
	m->ecx = M32((DWORD)(0x4ded18u));	/* 4304bd: mov ecx, dword ptr [0x4ded18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4304c3: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4304c4: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4304cau; native_call(m, 0x401410u);	/* 4304c5: call 0x401410 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4304ca: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4304cd: test eax, eax */
	if (!m->zf) goto L_430502;	/* 4304cf: jne 0x430502 */
	m->edx = M32((DWORD)(0x4ded18u));	/* 4304d1: mov edx, dword ptr [0x4ded18] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4304d7: push ebx */
	{ DWORD v_ = 0x7510a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4304d8: push 0x7510a4 */
	{ DWORD v_ = 0x751624u; m->esp -= 4; M32(m->esp) = v_; }	/* 4304dd: push 0x751624 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4304e2: push edx */
	m->esp -= 4; M32(m->esp) = 0x4304e9u; native_call(m, M32(0x4a9324u));	/* 4304e3: call dword ptr [0x4a9324] */
	m->edi = M32(m->esp); m->esp += 4;	/* 4304e9: pop edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4304ea: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4304ec: pop ebx */
	m->ecx = M32((DWORD)(m->esp + 0x144u));	/* 4304ed: mov ecx, dword ptr [esp + 0x144] */
	M32((DWORD)&g_lift_fs0) = m->ecx;	/* 4304f4: mov dword ptr fs:[0], ecx */
	{ DWORD a_ = m->esp, b_ = 0x150u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4304fb: add esp, 0x150 */
	m->esp += 4 + 0; return;	/* 430501: ret  */
L_430502:
	M32((DWORD)(0x9dbf0cu)) = 0x1u;	/* 430502: mov dword ptr [0x9dbf0c], 1 */
L_43050c:
	{ DWORD a_ = M32((DWORD)(0x76d410u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43050c: cmp dword ptr [0x76d410], ebx */
	if (!m->zf) goto L_430603;	/* 430512: jne 0x430603 */
	m->esp -= 4; M32(m->esp) = 0x43051du; native_call(m, 0x41e6d0u);	/* 430518: call 0x41e6d0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43051d: test eax, eax */
	if (!m->zf) goto L_430547;	/* 43051f: jne 0x430547 */
	{ DWORD v_ = 0x4b04b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 430521: push 0x4b04b0 */
	m->esp -= 4; M32(m->esp) = 0x43052bu; native_call(m, 0x41edf0u);	/* 430526: call 0x41edf0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43052b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43052e: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 430530: pop edi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 430531: pop ebx */
	m->ecx = M32((DWORD)(m->esp + 0x144u));	/* 430532: mov ecx, dword ptr [esp + 0x144] */
	M32((DWORD)&g_lift_fs0) = m->ecx;	/* 430539: mov dword ptr fs:[0], ecx */
	{ DWORD a_ = m->esp, b_ = 0x150u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 430540: add esp, 0x150 */
	m->esp += 4 + 0; return;	/* 430546: ret  */
L_430547:
	m->esp -= 4; M32(m->esp) = 0x43054cu; native_call(m, 0x41e550u);	/* 430547: call 0x41e550 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43054c: test eax, eax */
	if (!m->zf) goto L_430576;	/* 43054e: jne 0x430576 */
	{ DWORD v_ = 0x4b04b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 430550: push 0x4b04b0 */
	m->esp -= 4; M32(m->esp) = 0x43055au; native_call(m, 0x41edf0u);	/* 430555: call 0x41edf0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43055a: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43055d: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 43055f: pop edi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 430560: pop ebx */
	m->ecx = M32((DWORD)(m->esp + 0x144u));	/* 430561: mov ecx, dword ptr [esp + 0x144] */
	M32((DWORD)&g_lift_fs0) = m->ecx;	/* 430568: mov dword ptr fs:[0], ecx */
	{ DWORD a_ = m->esp, b_ = 0x150u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43056f: add esp, 0x150 */
	m->esp += 4 + 0; return;	/* 430575: ret  */
L_430576:
	m->esp -= 4; M32(m->esp) = 0x43057bu; native_call(m, 0x41e5b0u);	/* 430576: call 0x41e5b0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43057b: test eax, eax */
	if (!m->zf) goto L_4305a5;	/* 43057d: jne 0x4305a5 */
	{ DWORD v_ = 0x4b04b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43057f: push 0x4b04b0 */
	m->esp -= 4; M32(m->esp) = 0x430589u; native_call(m, 0x41edf0u);	/* 430584: call 0x41edf0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 430589: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43058c: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 43058e: pop edi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43058f: pop ebx */
	m->ecx = M32((DWORD)(m->esp + 0x144u));	/* 430590: mov ecx, dword ptr [esp + 0x144] */
	M32((DWORD)&g_lift_fs0) = m->ecx;	/* 430597: mov dword ptr fs:[0], ecx */
	{ DWORD a_ = m->esp, b_ = 0x150u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43059e: add esp, 0x150 */
	m->esp += 4 + 0; return;	/* 4305a4: ret  */
L_4305a5:
	m->esp -= 4; M32(m->esp) = 0x4305aau; native_call(m, 0x41e610u);	/* 4305a5: call 0x41e610 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4305aa: test eax, eax */
	if (!m->zf) goto L_4305d4;	/* 4305ac: jne 0x4305d4 */
	{ DWORD v_ = 0x4b04b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4305ae: push 0x4b04b0 */
	m->esp -= 4; M32(m->esp) = 0x4305b8u; native_call(m, 0x41edf0u);	/* 4305b3: call 0x41edf0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4305b8: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4305bb: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 4305bd: pop edi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4305be: pop ebx */
	m->ecx = M32((DWORD)(m->esp + 0x144u));	/* 4305bf: mov ecx, dword ptr [esp + 0x144] */
	M32((DWORD)&g_lift_fs0) = m->ecx;	/* 4305c6: mov dword ptr fs:[0], ecx */
	{ DWORD a_ = m->esp, b_ = 0x150u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4305cd: add esp, 0x150 */
	m->esp += 4 + 0; return;	/* 4305d3: ret  */
L_4305d4:
	m->esp -= 4; M32(m->esp) = 0x4305d9u; native_call(m, 0x41e670u);	/* 4305d4: call 0x41e670 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4305d9: test eax, eax */
	if (!m->zf) goto L_430603;	/* 4305db: jne 0x430603 */
	{ DWORD v_ = 0x4b04b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4305dd: push 0x4b04b0 */
	m->esp -= 4; M32(m->esp) = 0x4305e7u; native_call(m, 0x41edf0u);	/* 4305e2: call 0x41edf0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4305e7: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4305ea: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 4305ec: pop edi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4305ed: pop ebx */
	m->ecx = M32((DWORD)(m->esp + 0x144u));	/* 4305ee: mov ecx, dword ptr [esp + 0x144] */
	M32((DWORD)&g_lift_fs0) = m->ecx;	/* 4305f5: mov dword ptr fs:[0], ecx */
	{ DWORD a_ = m->esp, b_ = 0x150u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4305fc: add esp, 0x150 */
	m->esp += 4 + 0; return;	/* 430602: ret  */
L_430603:
	m->eax = M32((DWORD)(0x4ded18u));	/* 430603: mov eax, dword ptr [0x4ded18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 430608: push eax */
	m->esp -= 4; M32(m->esp) = 0x43060eu; native_call(m, 0x467a50u);	/* 430609: call 0x467a50 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43060e: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 430611: test eax, eax */
	if (!m->zf) goto L_43061d;	/* 430613: jne 0x43061d */
	M32((DWORD)(0xa0e80cu)) = m->ebx;	/* 430615: mov dword ptr [0xa0e80c], ebx */
	goto L_43062c;	/* 43061b: jmp 0x43062c */
L_43061d:
	M32((DWORD)(0xa0e80cu)) = 0x1u;	/* 43061d: mov dword ptr [0xa0e80c], 1 */
	m->esp -= 4; M32(m->esp) = 0x43062cu; native_call(m, 0x42bd40u);	/* 430627: call 0x42bd40 */
L_43062c:
	M32((DWORD)(0x4ded68u)) = 0x136u;	/* 43062c: mov dword ptr [0x4ded68], 0x136 */
	M32((DWORD)(0x4ded6cu)) = 0xe6u;	/* 430636: mov dword ptr [0x4ded6c], 0xe6 */
	m->esp -= 4; M32(m->esp) = 0x430645u; native_call(m, 0x431680u);	/* 430640: call 0x431680 */
	m->esp -= 4; M32(m->esp) = 0x43064au; native_call(m, 0x401780u);	/* 430645: call 0x401780 */
	M32((DWORD)(0x68038cu)) = 0x42340000u;	/* 43064a: mov dword ptr [0x68038c], 0x42340000 */
	m->esp -= 4; M32(m->esp) = 0x430659u; native_call(m, 0x401000u);	/* 430654: call 0x401000 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 430659: test eax, eax */
	if (!m->zf) goto L_430688;	/* 43065b: jne 0x430688 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43065d: push ebx */
	{ DWORD v_ = 0x4b2554u; m->esp -= 4; M32(m->esp) = v_; }	/* 43065e: push 0x4b2554 */
	{ DWORD v_ = 0x4b2528u; m->esp -= 4; M32(m->esp) = v_; }	/* 430663: push 0x4b2528 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 430668: push ebx */
	m->esp -= 4; M32(m->esp) = 0x43066fu; native_call(m, M32(0x4a9324u));	/* 430669: call dword ptr [0x4a9324] */
	m->edi = M32(m->esp); m->esp += 4;	/* 43066f: pop edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 430670: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 430672: pop ebx */
	m->ecx = M32((DWORD)(m->esp + 0x144u));	/* 430673: mov ecx, dword ptr [esp + 0x144] */
	M32((DWORD)&g_lift_fs0) = m->ecx;	/* 43067a: mov dword ptr fs:[0], ecx */
	{ DWORD a_ = m->esp, b_ = 0x150u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 430681: add esp, 0x150 */
	m->esp += 4 + 0; return;	/* 430687: ret  */
L_430688:
	m->ecx = M32((DWORD)(0x83a9d0u));	/* 430688: mov ecx, dword ptr [0x83a9d0] */
	m->edx = M32((DWORD)(0x83a9ccu));	/* 43068e: mov edx, dword ptr [0x83a9cc] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 430694: push esi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 430695: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 430696: push edx */
	{ DWORD v_ = 0x40u; m->esp -= 4; M32(m->esp) = v_; }	/* 430697: push 0x40 */
	{ DWORD v_ = 0x40u; m->esp -= 4; M32(m->esp) = v_; }	/* 430699: push 0x40 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43069b: push ebx */
	{ DWORD v_ = 0x28u; m->esp -= 4; M32(m->esp) = v_; }	/* 43069c: push 0x28 */
	{ DWORD v_ = 0x4b1304u; m->esp -= 4; M32(m->esp) = v_; }	/* 43069e: push 0x4b1304 */
	m->ecx = 0x4e1878u;	/* 4306a3: mov ecx, 0x4e1878 */
	m->esp -= 4; M32(m->esp) = 0x4306adu; native_call(m, 0x455080u);	/* 4306a8: call 0x455080 */
	m->eax = M32((DWORD)(0x83a9d0u));	/* 4306ad: mov eax, dword ptr [0x83a9d0] */
	m->ecx = M32((DWORD)(0x83a9ccu));	/* 4306b2: mov ecx, dword ptr [0x83a9cc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4306b8: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4306b9: push ecx */
	{ DWORD v_ = 0x40u; m->esp -= 4; M32(m->esp) = v_; }	/* 4306ba: push 0x40 */
	{ DWORD v_ = 0x80u; m->esp -= 4; M32(m->esp) = v_; }	/* 4306bc: push 0x80 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4306c1: push ebx */
	{ DWORD v_ = 0x28u; m->esp -= 4; M32(m->esp) = v_; }	/* 4306c2: push 0x28 */
	{ DWORD v_ = 0x4b1304u; m->esp -= 4; M32(m->esp) = v_; }	/* 4306c4: push 0x4b1304 */
	m->ecx = 0x5b1db8u;	/* 4306c9: mov ecx, 0x5b1db8 */
	m->esp -= 4; M32(m->esp) = 0x4306d3u; native_call(m, 0x455080u);	/* 4306ce: call 0x455080 */
	m->edx = M32((DWORD)(0x83a9d0u));	/* 4306d3: mov edx, dword ptr [0x83a9d0] */
	m->eax = M32((DWORD)(0x83a9ccu));	/* 4306d9: mov eax, dword ptr [0x83a9cc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4306de: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4306df: push eax */
	{ DWORD v_ = 0x40u; m->esp -= 4; M32(m->esp) = v_; }	/* 4306e0: push 0x40 */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 4306e2: push 0x100 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4306e7: push ebx */
	{ DWORD v_ = 0x28u; m->esp -= 4; M32(m->esp) = v_; }	/* 4306e8: push 0x28 */
	{ DWORD v_ = 0x4b1304u; m->esp -= 4; M32(m->esp) = v_; }	/* 4306ea: push 0x4b1304 */
	m->ecx = 0x680cd8u;	/* 4306ef: mov ecx, 0x680cd8 */
	m->esp -= 4; M32(m->esp) = 0x4306f9u; native_call(m, 0x455080u);	/* 4306f4: call 0x455080 */
	m->ecx = M32((DWORD)(0x83a9d0u));	/* 4306f9: mov ecx, dword ptr [0x83a9d0] */
	m->edx = M32((DWORD)(0x83a9ccu));	/* 4306ff: mov edx, dword ptr [0x83a9cc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 430705: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 430706: push edx */
	{ DWORD v_ = 0x80u; m->esp -= 4; M32(m->esp) = v_; }	/* 430707: push 0x80 */
	{ DWORD v_ = 0x80u; m->esp -= 4; M32(m->esp) = v_; }	/* 43070c: push 0x80 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 430711: push ebx */
	{ DWORD v_ = 0x28u; m->esp -= 4; M32(m->esp) = v_; }	/* 430712: push 0x28 */
	{ DWORD v_ = 0x4b1304u; m->esp -= 4; M32(m->esp) = v_; }	/* 430714: push 0x4b1304 */
	m->ecx = 0x76d498u;	/* 430719: mov ecx, 0x76d498 */
	m->esp -= 4; M32(m->esp) = 0x430723u; native_call(m, 0x455080u);	/* 43071e: call 0x455080 */
	m->eax = M32((DWORD)(0x83a9d0u));	/* 430723: mov eax, dword ptr [0x83a9d0] */
	m->ecx = M32((DWORD)(0x83a9ccu));	/* 430728: mov ecx, dword ptr [0x83a9cc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43072e: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43072f: push ecx */
	{ DWORD v_ = 0x80u; m->esp -= 4; M32(m->esp) = v_; }	/* 430730: push 0x80 */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 430735: push 0x100 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43073a: push ebx */
	{ DWORD v_ = 0x50u; m->esp -= 4; M32(m->esp) = v_; }	/* 43073b: push 0x50 */
	{ DWORD v_ = 0x4b1304u; m->esp -= 4; M32(m->esp) = v_; }	/* 43073d: push 0x4b1304 */
	m->ecx = 0x90d1e0u;	/* 430742: mov ecx, 0x90d1e0 */
	m->esp -= 4; M32(m->esp) = 0x43074cu; native_call(m, 0x455080u);	/* 430747: call 0x455080 */
	m->edx = M32((DWORD)(0x83a9d0u));	/* 43074c: mov edx, dword ptr [0x83a9d0] */
	m->eax = M32((DWORD)(0x83a9ccu));	/* 430752: mov eax, dword ptr [0x83a9cc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 430757: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 430758: push eax */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 430759: push 0x100 */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 43075e: push 0x100 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 430763: push ebx */
	{ DWORD v_ = 0x28u; m->esp -= 4; M32(m->esp) = v_; }	/* 430764: push 0x28 */
	{ DWORD v_ = 0x4b1304u; m->esp -= 4; M32(m->esp) = v_; }	/* 430766: push 0x4b1304 */
	m->ecx = 0x83a9e0u;	/* 43076b: mov ecx, 0x83a9e0 */
	m->esp -= 4; M32(m->esp) = 0x430775u; native_call(m, 0x455080u);	/* 430770: call 0x455080 */
	{ DWORD v_ = 0x83a9e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 430775: push 0x83a9e0 */
	{ DWORD v_ = 0x90d1e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43077a: push 0x90d1e0 */
	{ DWORD v_ = 0x76d498u; m->esp -= 4; M32(m->esp) = v_; }	/* 43077f: push 0x76d498 */
	{ DWORD v_ = 0x680cd8u; m->esp -= 4; M32(m->esp) = v_; }	/* 430784: push 0x680cd8 */
	{ DWORD v_ = 0x5b1db8u; m->esp -= 4; M32(m->esp) = v_; }	/* 430789: push 0x5b1db8 */
	{ DWORD v_ = 0x4e1878u; m->esp -= 4; M32(m->esp) = v_; }	/* 43078e: push 0x4e1878 */
	m->ecx = 0x83a5e0u;	/* 430793: mov ecx, 0x83a5e0 */
	m->esp -= 4; M32(m->esp) = 0x43079du; native_call(m, 0x4569d0u);	/* 430798: call 0x4569d0 */
	{ DWORD v_ = 0x4b2514u; m->esp -= 4; M32(m->esp) = v_; }	/* 43079d: push 0x4b2514 */
	M32((DWORD)(0xa0e010u)) = 0x83a5e0u;	/* 4307a2: mov dword ptr [0xa0e010], 0x83a5e0 */
	m->esp -= 4; M32(m->esp) = 0x4307b1u; native_call(m, 0x46b950u);	/* 4307ac: call 0x46b950 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4307b1: add esp, 4 */
	m->edx = (DWORD)(m->esp + 0xd0u);	/* 4307b4: lea edx, [esp + 0xd0] */
	m->edi = 0x4b24c4u;	/* 4307bb: mov edi, 0x4b24c4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4307c0: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4307c3: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4307c5: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4307c7: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4307c9: sub edi, ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4307cb: push ebx */
	m->eax = m->ecx;	/* 4307cc: mov eax, ecx */
	m->esi = m->edi;	/* 4307ce: mov esi, edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4307d0: shr ecx, 2 */
	m->edi = m->edx;	/* 4307d3: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x14u);	/* 4307d5: lea edx, [esp + 0x14] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4307d9: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4307db: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4307dd: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4307df: and ecx, 3 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4307e2: push ebx */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4307e3: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b24b4u;	/* 4307e5: mov edi, 0x4b24b4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4307ea: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4307ed: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4307ef: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4307f1: sub edi, ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4307f3: push ebx */
	m->eax = m->ecx;	/* 4307f4: mov eax, ecx */
	m->esi = m->edi;	/* 4307f6: mov esi, edi */
	m->edi = m->edx;	/* 4307f8: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x5cu);	/* 4307fa: lea edx, [esp + 0x5c] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4307fe: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 430801: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 430803: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 430805: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430807: and ecx, 3 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43080a: push ebx */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43080b: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b24a4u;	/* 43080d: mov edi, 0x4b24a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430812: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 430815: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 430817: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 430819: sub edi, ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43081b: push ebx */
	m->eax = m->ecx;	/* 43081c: mov eax, ecx */
	m->esi = m->edi;	/* 43081e: mov esi, edi */
	m->edi = m->edx;	/* 430820: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0xa4u);	/* 430822: lea edx, [esp + 0xa4] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 430829: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43082c: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 43082e: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 430830: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430832: and ecx, 3 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 430835: push ebx */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 430836: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2490u;	/* 430838: mov edi, 0x4b2490 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43083d: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 430840: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 430842: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 430844: sub edi, ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 430846: push ebx */
	m->eax = m->ecx;	/* 430847: mov eax, ecx */
	m->esi = m->edi;	/* 430849: mov esi, edi */
	m->edi = m->edx;	/* 43084b: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0xecu);	/* 43084d: lea edx, [esp + 0xec] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 430854: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 430857: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 430859: mov ecx, eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43085b: push edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43085c: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43085f: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 430861: mov ecx, dword ptr [0xa0e010] */
	m->esp -= 4; M32(m->esp) = 0x43086cu; native_call(m, 0x456be0u);	/* 430867: call 0x456be0 */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 43086c: mov ecx, dword ptr [0xa0e010] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 430872: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 430873: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 430874: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 430875: push ebx */
	M32((DWORD)(0x76d448u)) = m->eax;	/* 430876: mov dword ptr [0x76d448], eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43087b: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43087c: push ebx */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 43087d: lea eax, [esp + 0x28] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 430881: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 430882: push eax */
	m->esp -= 4; M32(m->esp) = 0x430888u; native_call(m, 0x456be0u);	/* 430883: call 0x456be0 */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 430888: mov ecx, dword ptr [0xa0e010] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43088e: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43088f: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 430890: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 430891: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 430892: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 430893: push ebx */
	m->edx = (DWORD)(m->esp + 0x68u);	/* 430894: lea edx, [esp + 0x68] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 430898: push ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 430899: push edx */
	M32((DWORD)(0x9dad90u)) = m->eax;	/* 43089a: mov dword ptr [0x9dad90], eax */
	m->esp -= 4; M32(m->esp) = 0x4308a4u; native_call(m, 0x456be0u);	/* 43089f: call 0x456be0 */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 4308a4: mov ecx, dword ptr [0xa0e010] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4308aa: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4308ab: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4308ac: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4308ad: push ebx */
	M32((DWORD)(0x9dae1cu)) = m->eax;	/* 4308ae: mov dword ptr [0x9dae1c], eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4308b3: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4308b4: push ebx */
	m->eax = (DWORD)(m->esp + 0xa8u);	/* 4308b5: lea eax, [esp + 0xa8] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4308bc: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4308bd: push eax */
	m->esp -= 4; M32(m->esp) = 0x4308c3u; native_call(m, 0x456be0u);	/* 4308be: call 0x456be0 */
	M32((DWORD)(0x76d360u)) = m->eax;	/* 4308c3: mov dword ptr [0x76d360], eax */
	m->esp -= 4; M32(m->esp) = 0x4308cdu; native_call(m, 0x466c00u);	/* 4308c8: call 0x466c00 */
	m->esp -= 4; M32(m->esp) = 0x4308d2u; native_call(m, 0x46afe0u);	/* 4308cd: call 0x46afe0 */
	{ DWORD v_ = 0x2343acbu; m->esp -= 4; M32(m->esp) = v_; }	/* 4308d2: push 0x2343acb */
	m->esp -= 4; M32(m->esp) = 0x4308dcu; native_call(m, 0x49f1aau);	/* 4308d7: call 0x49f1aa */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4308dc: add esp, 4 */
	M32((DWORD)(m->esp + 0xcu)) = m->eax;	/* 4308df: mov dword ptr [esp + 0xc], eax */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4308e3: cmp eax, ebx */
	M32((DWORD)(m->esp + 0x158u)) = m->ebx;	/* 4308e5: mov dword ptr [esp + 0x158], ebx */
	if (m->zf) goto L_4308f7;	/* 4308ec: je 0x4308f7 */
	m->ecx = m->eax;	/* 4308ee: mov ecx, eax */
	m->esp -= 4; M32(m->esp) = 0x4308f5u; native_call(m, 0x460570u);	/* 4308f0: call 0x460570 */
	goto L_4308f9;	/* 4308f5: jmp 0x4308f9 */
L_4308f7:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4308f7: xor eax, eax */
L_4308f9:
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 4308f9: push 0x64 */
	{ DWORD v_ = 0x4b2504u; m->esp -= 4; M32(m->esp) = v_; }	/* 4308fb: push 0x4b2504 */
	M32((DWORD)(m->esp + 0x160u)) = 0xffffffffu;	/* 430900: mov dword ptr [esp + 0x160], 0xffffffff */
	M32((DWORD)(0x9087b4u)) = m->eax;	/* 43090b: mov dword ptr [0x9087b4], eax */
	m->esp -= 4; M32(m->esp) = 0x430915u; native_call(m, 0x456d10u);	/* 430910: call 0x456d10 */
	m->edi = 0x4b24f0u;	/* 430915: mov edi, 0x4b24f0 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43091a: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43091d: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43091f: add esp, 8 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 430922: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 430924: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 430926: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x110u);	/* 430928: lea edx, [esp + 0x110] */
	m->eax = m->ecx;	/* 43092f: mov eax, ecx */
	m->esi = m->edi;	/* 430931: mov esi, edi */
	m->edi = m->edx;	/* 430933: mov edi, edx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 430935: push ebx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 430936: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 430939: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 43093b: mov ecx, eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43093d: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43093e: push ebx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43093f: and ecx, 3 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 430942: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 430943: push ebx */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 430944: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 430946: mov ecx, dword ptr [0xa0e010] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43094c: push ebx */
	m->edx = (DWORD)(m->esp + 0x128u);	/* 43094d: lea edx, [esp + 0x128] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 430954: push ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 430955: push edx */
	M32((DWORD)(0x4df028u)) = 0x0u;	/* 430956: mov dword ptr [0x4df028], 0 */
	M32((DWORD)(0x4df024u)) = 0x0u;	/* 430960: mov dword ptr [0x4df024], 0 */
	M32((DWORD)(0x4df02cu)) = 0x43fa0000u;	/* 43096a: mov dword ptr [0x4df02c], 0x43fa0000 */
	M32((DWORD)(0x680378u)) = 0x0u;	/* 430974: mov dword ptr [0x680378], 0 */
	M32((DWORD)(0x68037cu)) = 0x0u;	/* 43097e: mov dword ptr [0x68037c], 0 */
	M32((DWORD)(0x680380u)) = 0x43c80000u;	/* 430988: mov dword ptr [0x680380], 0x43c80000 */
	M32((DWORD)(0x4dd0b0u)) = m->ebx;	/* 430992: mov dword ptr [0x4dd0b0], ebx */
	m->esp -= 4; M32(m->esp) = 0x43099du; native_call(m, 0x456be0u);	/* 430998: call 0x456be0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43099d: push 0x3f800000 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4309a2: push ebx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4309a3: push 0x3f800000 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4309a8: push ebx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4309a9: push 0x76d438 */
	M32((DWORD)(0x76d3f0u)) = m->eax;	/* 4309ae: mov dword ptr [0x76d3f0], eax */
	m->esp -= 4; M32(m->esp) = 0x4309b8u; native_call(m, 0x41f0e0u);	/* 4309b3: call 0x41f0e0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4309b8: push 0x3f800000 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4309bd: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4309be: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4309bf: push ebx */
	{ DWORD v_ = 0x76d350u; m->esp -= 4; M32(m->esp) = v_; }	/* 4309c0: push 0x76d350 */
	m->esp -= 4; M32(m->esp) = 0x4309cau; native_call(m, 0x41f0e0u);	/* 4309c5: call 0x41f0e0 */
	FPUSH((long double)(int)M32((DWORD)(0x5b1998u)));	/* 4309ca: fild dword ptr [0x5b1998] */
	m->eax = M32((DWORD)(0x5b1998u));	/* 4309d0: mov eax, dword ptr [0x5b1998] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4309d5: add esp, 0x28 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4309d8: cdq  */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9578u));	/* 4309d9: fmul dword ptr [0x4a9578] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4309df: sub eax, edx */
	M32((DWORD)(0x9da434u)) = 0x40a00000u;	/* 4309e1: mov dword ptr [0x9da434], 0x40a00000 */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4309eb: sar eax, 1 */
	MF((DWORD)(0x680bacu)) = (float)ST(0); FPOP();	/* 4309ed: fstp dword ptr [0x680bac] */
	FPUSH((long double)(int)M32((DWORD)(0x4e045cu)));	/* 4309f3: fild dword ptr [0x4e045c] */
	M32((DWORD)(0x4e1520u)) = m->eax;	/* 4309f9: mov dword ptr [0x4e1520], eax */
	m->eax = M32((DWORD)(0x4e045cu));	/* 4309fe: mov eax, dword ptr [0x4e045c] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 430a03: cdq  */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9574u));	/* 430a04: fmul dword ptr [0x4a9574] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 430a0a: sub eax, edx */
	M32((DWORD)(0x76d474u)) = m->ebx;	/* 430a0c: mov dword ptr [0x76d474], ebx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 430a12: sar eax, 1 */
	MF((DWORD)(0x4df014u)) = (float)ST(0); FPOP();	/* 430a14: fstp dword ptr [0x4df014] */
	M32((DWORD)(0x4df900u)) = m->ebx;	/* 430a1a: mov dword ptr [0x4df900], ebx */
	M32((DWORD)(0x680394u)) = m->eax;	/* 430a20: mov dword ptr [0x680394], eax */
	M32((DWORD)(0x4dd96cu)) = 0x0u;	/* 430a25: mov dword ptr [0x4dd96c], 0 */
	M32((DWORD)(0x4dd0b8u)) = m->ebx;	/* 430a2f: mov dword ptr [0x4dd0b8], ebx */
	M32((DWORD)(0x4de1e0u)) = 0x3dcccccdu;	/* 430a35: mov dword ptr [0x4de1e0], 0x3dcccccd */
	M32((DWORD)(0x4de1d8u)) = 0x3ca3d70au;	/* 430a3f: mov dword ptr [0x4de1d8], 0x3ca3d70a */
	M32((DWORD)(0x4de1e8u)) = 0x0u;	/* 430a49: mov dword ptr [0x4de1e8], 0 */
	M32((DWORD)(0x4df03cu)) = m->ebx;	/* 430a53: mov dword ptr [0x4df03c], ebx */
	M32((DWORD)(0x4df910u)) = 0x0u;	/* 430a59: mov dword ptr [0x4df910], 0 */
	m->eax = M32((DWORD)(0x4e0c90u));	/* 430a63: mov eax, dword ptr [0x4e0c90] */
	m->ecx = M32((DWORD)(m->esp + 0x150u));	/* 430a68: mov ecx, dword ptr [esp + 0x150] */
	m->esi = M32(m->esp); m->esp += 4;	/* 430a6f: pop esi */
	M32((DWORD)(0x4e1868u)) = m->ebx;	/* 430a70: mov dword ptr [0x4e1868], ebx */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0xfffffe0cu);	/* 430a76: lea eax, [eax + eax*4 - 0x1f4] */
	M32((DWORD)(0x5ae9c4u)) = m->ebx;	/* 430a7d: mov dword ptr [0x5ae9c4], ebx */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 430a83: shl eax, 2 */
	M32((DWORD)(0x4dd984u)) = m->eax;	/* 430a86: mov dword ptr [0x4dd984], eax */
	M32((DWORD)(0x5b1dacu)) = m->ebx;	/* 430a8b: mov dword ptr [0x5b1dac], ebx */
	m->edi = M32(m->esp); m->esp += 4;	/* 430a91: pop edi */
	m->eax = 0x1u;	/* 430a92: mov eax, 1 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 430a97: pop ebx */
	M32((DWORD)&g_lift_fs0) = m->ecx;	/* 430a98: mov dword ptr fs:[0], ecx */
	{ DWORD a_ = m->esp, b_ = 0x150u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 430a9f: add esp, 0x150 */
	m->esp += 4 + 0; return;	/* 430aa5: ret  */
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
