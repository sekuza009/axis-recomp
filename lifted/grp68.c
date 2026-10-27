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

static void lift_44cf70(X86 *m);
static void lift_4392c0(X86 *m);

/* room_4392c0 (0x4392c0), lifted by tools/lift.py */
static void lift_4392c0(X86 *m)
{
	m->eax = M32((DWORD)(0x90d1c4u));	/* 4392c0: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4392c5: sub esp, 0x24 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4392c8: test eax, eax */
	if (m->zf) goto L_4392f2;	/* 4392ca: je 0x4392f2 */
	m->eax = M32((DWORD)(0x9dd364u));	/* 4392cc: mov eax, dword ptr [0x9dd364] */
	m->ecx = M32((DWORD)(0x9dd360u));	/* 4392d1: mov ecx, dword ptr [0x9dd360] */
	m->edx = M32((DWORD)(0x9dd35cu));	/* 4392d7: mov edx, dword ptr [0x9dd35c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4392dd: push eax */
	m->eax = M32((DWORD)(0x9dd358u));	/* 4392de: mov eax, dword ptr [0x9dd358] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4392e3: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4392e4: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4392e5: push eax */
	m->esp -= 4; M32(m->esp) = 0x4392ebu; native_call(m, 0x428c30u);	/* 4392e6: call 0x428c30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4392eb: add esp, 0x10 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4392ee: add esp, 0x24 */
	m->esp += 4 + 0; return;	/* 4392f1: ret  */
L_4392f2:
	m->ecx = M32((DWORD)(0x4ded6cu));	/* 4392f2: mov ecx, dword ptr [0x4ded6c] */
	m->edx = M32((DWORD)(0x4ded68u));	/* 4392f8: mov edx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4392fe: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4392ff: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 439300: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 439301: push edi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439302: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439303: push edx */
	m->esp -= 4; M32(m->esp) = 0x439309u; native_call(m, 0x432200u);	/* 439304: call 0x432200 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 439309: push 2 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 43930b: mov dword ptr [esp + 0x1c], eax */
	m->esp -= 4; M32(m->esp) = 0x439314u; native_call(m, 0x41ef90u);	/* 43930f: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 439314: add esp, 0xc */
	m->esp -= 4; M32(m->esp) = 0x43931du; native_call(m, M32(0x4a9218u));	/* 439317: call dword ptr [0x4a9218] */
	m->ebp = M32((DWORD)(0x4a9228u));	/* 43931d: mov ebp, dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439323: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439328: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43932d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439332: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x439339u; native_call(m, m->ebp);	/* 439337: call ebp */
	m->eax = M32((DWORD)(0x4deb50u));	/* 439339: mov eax, dword ptr [0x4deb50] */
	m->ecx = M32((DWORD)(0x9dd364u));	/* 43933e: mov ecx, dword ptr [0x9dd364] */
	m->edx = M32((DWORD)(0x9dd360u));	/* 439344: mov edx, dword ptr [0x9dd360] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43934a: push eax */
	m->eax = M32((DWORD)(0x9dd35cu));	/* 43934b: mov eax, dword ptr [0x9dd35c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439350: push ecx */
	m->ecx = M32((DWORD)(0x9dd358u));	/* 439351: mov ecx, dword ptr [0x9dd358] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439357: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439358: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439359: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43935fu; native_call(m, 0x427a90u);	/* 43935a: call 0x427a90 */
	m->edx = M32((DWORD)(0x9dceccu));	/* 43935f: mov edx, dword ptr [0x9dcecc] */
	m->eax = M32((DWORD)(0x9dcec8u));	/* 439365: mov eax, dword ptr [0x9dcec8] */
	m->ecx = M32((DWORD)(0x9dcec4u));	/* 43936a: mov ecx, dword ptr [0x9dcec4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439370: push edx */
	m->edx = M32((DWORD)(0x9dcec0u));	/* 439371: mov edx, dword ptr [0x9dcec0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439377: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439378: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439379: push edx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43937a: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x439384u; native_call(m, 0x41f0e0u);	/* 43937f: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd35cu));	/* 439384: mov eax, dword ptr [0x9dd35c] */
	m->ecx = M32((DWORD)(0x9dd358u));	/* 439389: mov ecx, dword ptr [0x9dd358] */
	{ DWORD a_ = m->eax, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43938f: add eax, 0x10 */
	{ DWORD v_ = 0x7583a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 439392: push 0x7583a4 */
	{ DWORD a_ = m->ecx, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 439397: add ecx, 0x40 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43939a: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43939b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4393a1u; native_call(m, 0x4028b0u);	/* 43939c: call 0x4028b0 */
	m->edx = M32((DWORD)(0x9dceccu));	/* 4393a1: mov edx, dword ptr [0x9dcecc] */
	m->eax = M32((DWORD)(0x9dcec8u));	/* 4393a7: mov eax, dword ptr [0x9dcec8] */
	m->ecx = M32((DWORD)(0x9dcec4u));	/* 4393ac: mov ecx, dword ptr [0x9dcec4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4393b2: push edx */
	m->edx = M32((DWORD)(0x9dcec0u));	/* 4393b3: mov edx, dword ptr [0x9dcec0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4393b9: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4393ba: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4393bb: push edx */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 4393bc: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x4393c6u; native_call(m, 0x41f0e0u);	/* 4393c1: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd35cu));	/* 4393c6: mov eax, dword ptr [0x9dd35c] */
	m->ecx = M32((DWORD)(0x9dd360u));	/* 4393cb: mov ecx, dword ptr [0x9dd360] */
	m->edx = M32((DWORD)(0x9dd358u));	/* 4393d1: mov edx, dword ptr [0x9dd358] */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4393d7: add esp, 0x48 */
	{ DWORD a_ = m->eax, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4393da: add eax, 0x24 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffc0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4393dd: add ecx, -0x40 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4393e0: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4393e1: push ecx */
	{ DWORD a_ = m->edx, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4393e2: add edx, 0x40 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4393e5: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4393e6: push edx */
	m->esp -= 4; M32(m->esp) = 0x4393ecu; native_call(m, 0x427a40u);	/* 4393e7: call 0x427a40 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4393ec: add esp, 0x10 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 4393ef: xor esi, esi */
	m->edi = 0x758424u;	/* 4393f1: mov edi, 0x758424 */
L_4393f6:
	m->eax = M32((DWORD)(0x9dd35cu));	/* 4393f6: mov eax, dword ptr [0x9dd35c] */
	m->edx = M32((DWORD)(0x9dd358u));	/* 4393fb: mov edx, dword ptr [0x9dd358] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 439401: push edi */
	{ DWORD a_ = m->edx, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 439402: add edx, 0x40 */
	m->ecx = (DWORD)(m->esi + m->eax*1 + 0x58u);	/* 439405: lea ecx, [esi + eax + 0x58] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439409: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43940a: push edx */
	m->esp -= 4; M32(m->esp) = 0x439410u; native_call(m, 0x4028b0u);	/* 43940b: call 0x4028b0 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439410: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 439415: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 439417: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 439419: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43941b: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x439425u; native_call(m, 0x41f0e0u);	/* 439420: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd35cu));	/* 439425: mov eax, dword ptr [0x9dd35c] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43942a: push 1 */
	m->ecx = (DWORD)(m->esi + m->eax*1 + 0x70u);	/* 43942c: lea ecx, [esi + eax + 0x70] */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x50u);	/* 439430: lea eax, [esi + eax + 0x50] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439434: push ecx */
	m->ecx = M32((DWORD)(0x9dd358u));	/* 439435: mov ecx, dword ptr [0x9dd358] */
	m->edx = (DWORD)(m->ecx + 0x1a8u);	/* 43943b: lea edx, [ecx + 0x1a8] */
	{ DWORD a_ = m->ecx, b_ = 0xb8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 439441: add ecx, 0xb8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439447: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439448: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439449: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43944fu; native_call(m, 0x427970u);	/* 43944a: call 0x427970 */
	m->ecx = M32((DWORD)(0x9dceccu));	/* 43944f: mov ecx, dword ptr [0x9dcecc] */
	m->edx = M32((DWORD)(0x9dcec8u));	/* 439455: mov edx, dword ptr [0x9dcec8] */
	m->eax = M32((DWORD)(0x9dcec4u));	/* 43945b: mov eax, dword ptr [0x9dcec4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439460: push ecx */
	m->ecx = M32((DWORD)(0x9dcec0u));	/* 439461: mov ecx, dword ptr [0x9dcec0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439467: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439468: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439469: push ecx */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43946a: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x439474u; native_call(m, 0x41f0e0u);	/* 43946f: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd35cu));	/* 439474: mov eax, dword ptr [0x9dd35c] */
	m->ecx = M32((DWORD)(0x9dd358u));	/* 439479: mov ecx, dword ptr [0x9dd358] */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43947f: add esp, 0x48 */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x70u);	/* 439482: lea edx, [esi + eax + 0x70] */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x50u);	/* 439486: lea eax, [esi + eax + 0x50] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43948a: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43948c: push edx */
	m->edx = (DWORD)(m->ecx + 0x1a8u);	/* 43948d: lea edx, [ecx + 0x1a8] */
	{ DWORD a_ = m->ecx, b_ = 0xb8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 439493: add ecx, 0xb8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439499: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43949a: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43949b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4394a1u; native_call(m, 0x427970u);	/* 43949c: call 0x427970 */
	{ DWORD a_ = m->edi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4394a1: add edi, 0x80 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4394a7: add esp, 0x14 */
	{ DWORD a_ = m->esi, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4394aa: add esi, 0x30 */
	{ DWORD a_ = m->edi, b_ = 0x758524u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4394ad: cmp edi, 0x758524 */
	if (m->sf != m->of) goto L_4393f6;	/* 4394b3: jl 0x4393f6 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4394b9: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4394be: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4394c3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4394c8: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4394cd: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4394d7u; native_call(m, 0x41f0e0u);	/* 4394d2: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd830u));	/* 4394d7: mov eax, dword ptr [0x9dd830] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4394dc: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4394df: test eax, eax */
	if (!m->zf) goto L_439507;	/* 4394e1: jne 0x439507 */
	m->ecx = M32((DWORD)(0x9dd35cu));	/* 4394e3: mov ecx, dword ptr [0x9dd35c] */
	m->edx = M32((DWORD)(0x9dd358u));	/* 4394e9: mov edx, dword ptr [0x9dd358] */
	{ DWORD a_ = m->ecx, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4394ef: add ecx, 0x58 */
	{ DWORD v_ = 0x9dd1d8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4394f2: push 0x9dd1d8 */
	{ DWORD a_ = m->edx, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4394f7: add edx, 0xc8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4394fd: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4394fe: push edx */
	m->esp -= 4; M32(m->esp) = 0x439504u; native_call(m, 0x402620u);	/* 4394ff: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 439504: add esp, 0xc */
L_439507:
	m->eax = M32((DWORD)(0x9dd38cu));	/* 439507: mov eax, dword ptr [0x9dd38c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43950c: test eax, eax */
	if (!m->zf) goto L_439570;	/* 43950e: jne 0x439570 */
	m->edi = 0x9dd1f6u;	/* 439510: mov edi, 0x9dd1f6 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 439515: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 439518: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43951a: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43951c: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43951e: dec ecx */
	m->edi = (DWORD)(m->esp + 0x14u);	/* 43951f: lea edi, [esp + 0x14] */
	m->edx = m->ecx;	/* 439523: mov edx, ecx */
	m->ecx = 0x7u;	/* 439525: mov ecx, 7 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 43952a: rep stosd dword ptr es:[edi], eax */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43952c: test edx, edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 43952e: stosw word ptr es:[edi], ax */
	if (m->zf || m->sf != m->of) goto L_439549;	/* 439530: jle 0x439549 */
	m->ecx = m->edx;	/* 439532: mov ecx, edx */
	m->eax = 0x2a2a2a2au;	/* 439534: mov eax, 0x2a2a2a2a */
	m->edi = (DWORD)(m->esp + 0x14u);	/* 439539: lea edi, [esp + 0x14] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43953d: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 439540: rep stosd dword ptr es:[edi], eax */
	m->ecx = m->edx;	/* 439542: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 439544: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1; m->ecx--; }	/* 439547: rep stosb byte ptr es:[edi], al */
L_439549:
	m->ecx = M32((DWORD)(0x9dd35cu));	/* 439549: mov ecx, dword ptr [0x9dd35c] */
	m->edx = M32((DWORD)(0x9dd358u));	/* 43954f: mov edx, dword ptr [0x9dd358] */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 439555: lea eax, [esp + 0x14] */
	{ DWORD a_ = m->ecx, b_ = 0x88u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 439559: add ecx, 0x88 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43955f: push eax */
	{ DWORD a_ = m->edx, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 439560: add edx, 0xc8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439566: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439567: push edx */
	m->esp -= 4; M32(m->esp) = 0x43956du; native_call(m, 0x402620u);	/* 439568: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43956d: add esp, 0xc */
L_439570:
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 439570: xor ebx, ebx */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 439572: xor esi, esi */
	m->edi = 0x758524u;	/* 439574: mov edi, 0x758524 */
L_439579:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 439579: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x439584u; native_call(m, M32(0x4a9224u));	/* 43957e: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 439584: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 439589: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43958b: and ecx, 0x800001ff */
	if (!m->sf) goto L_43959b;	/* 439591: jns 0x43959b */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 439593: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 439594: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 43959a: inc ecx */
L_43959b:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 43959b: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43959c: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4395a2: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4395a3: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 4395a5: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4395ab: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 4395ae: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x4395b7u; native_call(m, 0x4566c0u);	/* 4395b2: call 0x4566c0 */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 4395b7: mov ecx, dword ptr [esp + 0x10] */
	m->eax = (DWORD)(m->ebx + 0x2u);	/* 4395bb: lea eax, [ebx + 2] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4395be: cmp ecx, eax */
	if (!m->zf) goto L_439624;	/* 4395c0: jne 0x439624 */
	m->eax = M32((DWORD)(0x9dd838u));	/* 4395c2: mov eax, dword ptr [0x9dd838] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4395c7: test eax, eax */
	if (!m->zf) goto L_439624;	/* 4395c9: jne 0x439624 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4395cb: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4395d0: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4395d5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4395da: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4395e1u; native_call(m, m->ebp);	/* 4395df: call ebp */
	m->ecx = M32((DWORD)(0x9dd364u));	/* 4395e1: mov ecx, dword ptr [0x9dd364] */
	m->eax = M32((DWORD)(0x9dd358u));	/* 4395e7: mov eax, dword ptr [0x9dd358] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4395ec: push 1 */
	m->edx = (DWORD)(m->ecx + 0xffffffe0u);	/* 4395ee: lea edx, [ecx - 0x20] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffc0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4395f1: add ecx, -0x40 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4395f4: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xa8u);	/* 4395f5: lea edx, [esi + eax + 0xa8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4395fc: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x30u);	/* 4395fd: lea eax, [esi + eax + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439601: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439602: push eax */
	m->esp -= 4; M32(m->esp) = 0x439608u; native_call(m, 0x4282f0u);	/* 439603: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x9dceccu));	/* 439608: mov ecx, dword ptr [0x9dcecc] */
	m->edx = M32((DWORD)(0x9dcec8u));	/* 43960e: mov edx, dword ptr [0x9dcec8] */
	m->eax = M32((DWORD)(0x9dcec4u));	/* 439614: mov eax, dword ptr [0x9dcec4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439619: push ecx */
	m->ecx = M32((DWORD)(0x9dcec0u));	/* 43961a: mov ecx, dword ptr [0x9dcec0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439620: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439621: push eax */
	goto L_43967b;	/* 439622: jmp 0x43967b */
L_439624:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 439624: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439629: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43962e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439633: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43963au; native_call(m, m->ebp);	/* 439638: call ebp */
	m->ecx = M32((DWORD)(0x9dd364u));	/* 43963a: mov ecx, dword ptr [0x9dd364] */
	m->eax = M32((DWORD)(0x9dd358u));	/* 439640: mov eax, dword ptr [0x9dd358] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 439645: push 1 */
	m->edx = (DWORD)(m->ecx + 0xffffffe0u);	/* 439647: lea edx, [ecx - 0x20] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffc0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43964a: add ecx, -0x40 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43964d: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xa8u);	/* 43964e: lea edx, [esi + eax + 0xa8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439655: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x30u);	/* 439656: lea eax, [esi + eax + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43965a: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43965b: push eax */
	m->esp -= 4; M32(m->esp) = 0x439661u; native_call(m, 0x4282f0u);	/* 43965c: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x9dd344u));	/* 439661: mov ecx, dword ptr [0x9dd344] */
	m->edx = M32((DWORD)(0x9dd340u));	/* 439667: mov edx, dword ptr [0x9dd340] */
	m->eax = M32((DWORD)(0x9dd33cu));	/* 43966d: mov eax, dword ptr [0x9dd33c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439672: push ecx */
	m->ecx = M32((DWORD)(0x9dd338u));	/* 439673: mov ecx, dword ptr [0x9dd338] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439679: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43967a: push eax */
L_43967b:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43967b: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43967c: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x439686u; native_call(m, 0x41f0e0u);	/* 439681: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd358u));	/* 439686: mov eax, dword ptr [0x9dd358] */
	m->ecx = M32((DWORD)(0x9dd364u));	/* 43968b: mov ecx, dword ptr [0x9dd364] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 439691: add esp, 0x28 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 439694: add ecx, -0x38 */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xa8u);	/* 439697: lea edx, [esi + eax + 0xa8] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43969e: push edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43969f: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x30u);	/* 4396a0: lea edx, [esi + eax + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4396a4: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4396a5: push edx */
	m->esp -= 4; M32(m->esp) = 0x4396abu; native_call(m, 0x4029d0u);	/* 4396a6: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4396ab: add esp, 0x10 */
	{ DWORD a_ = m->edi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4396ae: add edi, 0x80 */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 4396b4: inc ebx */
	{ DWORD a_ = m->esi, b_ = 0xa0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4396b5: add esi, 0xa0 */
	{ DWORD a_ = m->edi, b_ = 0x7586a4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4396bb: cmp edi, 0x7586a4 */
	if (m->sf != m->of) goto L_439579;	/* 4396c1: jl 0x439579 */
	m->eax = M32((DWORD)(0x9dd838u));	/* 4396c7: mov eax, dword ptr [0x9dd838] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4396cc: test eax, eax */
	if (m->zf) goto L_439757;	/* 4396ce: je 0x439757 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4396d4: push 0x3f333333 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4396d9: push 0x3f333333 */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 4396de: push 0x3e4ccccd */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 4396e3: push 0x3e4ccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 4396e8: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x4396f2u; native_call(m, 0x41f0e0u);	/* 4396ed: call 0x41f0e0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4396f2: push 1 */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 4396f4: push 0x140 */
	{ DWORD v_ = 0x21cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4396f9: push 0x21c */
	{ DWORD v_ = 0xc8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4396fe: push 0xc8 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 439703: push 0x64 */
	m->esp -= 4; M32(m->esp) = 0x43970au; native_call(m, 0x427970u);	/* 439705: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43970a: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43970f: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439711: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439716: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43971b: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x439725u; native_call(m, 0x41f0e0u);	/* 439720: call 0x41f0e0 */
	{ DWORD v_ = 0x74f6a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 439725: push 0x74f6a4 */
	{ DWORD v_ = 0x217u; m->esp -= 4; M32(m->esp) = v_; }	/* 43972a: push 0x217 */
	{ DWORD v_ = 0xdcu; m->esp -= 4; M32(m->esp) = v_; }	/* 43972f: push 0xdc */
	{ DWORD v_ = 0x69u; m->esp -= 4; M32(m->esp) = v_; }	/* 439734: push 0x69 */
	m->esp -= 4; M32(m->esp) = 0x43973bu; native_call(m, 0x4029d0u);	/* 439736: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43973b: add esp, 0x4c */
	{ DWORD v_ = 0x74f724u; m->esp -= 4; M32(m->esp) = v_; }	/* 43973e: push 0x74f724 */
	{ DWORD v_ = 0x217u; m->esp -= 4; M32(m->esp) = v_; }	/* 439743: push 0x217 */
	{ DWORD v_ = 0xf4u; m->esp -= 4; M32(m->esp) = v_; }	/* 439748: push 0xf4 */
	{ DWORD v_ = 0x69u; m->esp -= 4; M32(m->esp) = v_; }	/* 43974d: push 0x69 */
	m->esp -= 4; M32(m->esp) = 0x439754u; native_call(m, 0x4029d0u);	/* 43974f: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 439754: add esp, 0x10 */
L_439757:
	m->eax = M32((DWORD)(0x9dd850u));	/* 439757: mov eax, dword ptr [0x9dd850] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43975c: test eax, eax */
	if (m->zf) goto L_43997c;	/* 43975e: je 0x43997c */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 439764: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 439769: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43976f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439770: push ecx */
	m->esp -= 4; M32(m->esp) = 0x439776u; native_call(m, 0x4321c0u);	/* 439771: call 0x4321c0 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439776: push 0x3f000000 */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43977b: push 0x3dcccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 439780: push 0x3dcccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 439785: push 0x3dcccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43978a: push 0x9da480 */
	M32((DWORD)(m->esp + 0x2cu)) = m->eax;	/* 43978f: mov dword ptr [esp + 0x2c], eax */
	m->esp -= 4; M32(m->esp) = 0x439798u; native_call(m, 0x41f0e0u);	/* 439793: call 0x41f0e0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 439798: push 1 */
	{ DWORD v_ = 0x1e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43979a: push 0x1e0 */
	{ DWORD v_ = 0x280u; m->esp -= 4; M32(m->esp) = v_; }	/* 43979f: push 0x280 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4397a4: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4397a6: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4397adu; native_call(m, 0x427970u);	/* 4397a8: call 0x427970 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 4397ad: push 0x3f4ccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 4397b2: push 0x3dcccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 4397b7: push 0x3dcccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 4397bc: push 0x3dcccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 4397c1: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x4397cbu; native_call(m, 0x41f0e0u);	/* 4397c6: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4397cb: add esp, 0x44 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4397ce: push 1 */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 4397d0: push 0x140 */
	{ DWORD v_ = 0x21cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4397d5: push 0x21c */
	{ DWORD v_ = 0xb4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4397da: push 0xb4 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 4397df: push 0x64 */
	m->esp -= 4; M32(m->esp) = 0x4397e6u; native_call(m, 0x427970u);	/* 4397e1: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4397e6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4397eb: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4397f0: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4397f5: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 4397f7: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x439801u; native_call(m, 0x41f0e0u);	/* 4397fc: call 0x41f0e0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 439801: push 0 */
	{ DWORD v_ = 0x13cu; m->esp -= 4; M32(m->esp) = v_; }	/* 439803: push 0x13c */
	{ DWORD v_ = 0x218u; m->esp -= 4; M32(m->esp) = v_; }	/* 439808: push 0x218 */
	{ DWORD v_ = 0xb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 43980d: push 0xb8 */
	{ DWORD v_ = 0x68u; m->esp -= 4; M32(m->esp) = v_; }	/* 439812: push 0x68 */
	m->esp -= 4; M32(m->esp) = 0x439819u; native_call(m, 0x427970u);	/* 439814: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439819: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43981e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439823: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439828: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43982d: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x439837u; native_call(m, 0x41f0e0u);	/* 439832: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 439837: add esp, 0x50 */
	{ DWORD v_ = 0x74dfa4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43983a: push 0x74dfa4 */
	{ DWORD v_ = 0x21cu; m->esp -= 4; M32(m->esp) = v_; }	/* 43983f: push 0x21c */
	{ DWORD v_ = 0xc8u; m->esp -= 4; M32(m->esp) = v_; }	/* 439844: push 0xc8 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 439849: push 0x64 */
	m->esp -= 4; M32(m->esp) = 0x439850u; native_call(m, 0x4029d0u);	/* 43984b: call 0x4029d0 */
	{ DWORD v_ = 0x74e024u; m->esp -= 4; M32(m->esp) = v_; }	/* 439850: push 0x74e024 */
	{ DWORD v_ = 0x21cu; m->esp -= 4; M32(m->esp) = v_; }	/* 439855: push 0x21c */
	{ DWORD v_ = 0xdcu; m->esp -= 4; M32(m->esp) = v_; }	/* 43985a: push 0xdc */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 43985f: push 0x64 */
	m->esp -= 4; M32(m->esp) = 0x439866u; native_call(m, 0x4029d0u);	/* 439861: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 439866: add esp, 0x20 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 439869: xor ebp, ebp */
	m->esi = 0xb4u;	/* 43986b: mov esi, 0xb4 */
	m->ebx = 0x7517a4u;	/* 439870: mov ebx, 0x7517a4 */
L_439875:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 439875: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x439880u; native_call(m, M32(0x4a9224u));	/* 43987a: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 439880: mov eax, dword ptr [0x9db0a4] */
	m->edx = m->eax;	/* 439885: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 439887: and edx, 0x800001ff */
	if (!m->sf) goto L_439897;	/* 43988d: jns 0x439897 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 43988f: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 439890: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 439896: inc edx */
L_439897:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439897: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 439898: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 43989e: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43989f: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4398a5: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4398a7: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 4398aa: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x4398b3u; native_call(m, 0x4566c0u);	/* 4398ae: call 0x4566c0 */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x10u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4398b3: cmp dword ptr [esp + 0x10], ebp */
	if (!m->zf) goto L_4398fc;	/* 4398b7: jne 0x4398fc */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4398b9: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4398be: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4398c3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4398c8: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4398d3u; native_call(m, M32(0x4a9228u));	/* 4398cd: call dword ptr [0x4a9228] */
	m->edi = (DWORD)(m->esi + 0x78u);	/* 4398d3: lea edi, [esi + 0x78] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4398d6: push 1 */
	{ DWORD v_ = 0x124u; m->esp -= 4; M32(m->esp) = v_; }	/* 4398d8: push 0x124 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4398dd: push edi */
	{ DWORD v_ = 0x104u; m->esp -= 4; M32(m->esp) = v_; }	/* 4398de: push 0x104 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4398e3: push esi */
	m->esp -= 4; M32(m->esp) = 0x4398e9u; native_call(m, 0x4282f0u);	/* 4398e4: call 0x4282f0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4398e9: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4398ee: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4398f3: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4398f8: push 0 */
	goto L_439940;	/* 4398fa: jmp 0x439940 */
L_4398fc:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 4398fc: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439901: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439906: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43990b: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x439916u; native_call(m, M32(0x4a9228u));	/* 439910: call dword ptr [0x4a9228] */
	m->edi = (DWORD)(m->esi + 0x78u);	/* 439916: lea edi, [esi + 0x78] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 439919: push 1 */
	{ DWORD v_ = 0x124u; m->esp -= 4; M32(m->esp) = v_; }	/* 43991b: push 0x124 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 439920: push edi */
	{ DWORD v_ = 0x104u; m->esp -= 4; M32(m->esp) = v_; }	/* 439921: push 0x104 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 439926: push esi */
	m->esp -= 4; M32(m->esp) = 0x43992cu; native_call(m, 0x4282f0u);	/* 439927: call 0x4282f0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43992c: push 0x3f800000 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 439931: push 0x3f333333 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 439936: push 0x3f333333 */
	{ DWORD v_ = 0x3e99999au; m->esp -= 4; M32(m->esp) = v_; }	/* 43993b: push 0x3e99999a */
L_439940:
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 439940: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43994au; native_call(m, 0x41f0e0u);	/* 439945: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43994a: add esp, 0x28 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43994d: push ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43994e: push edi */
	{ DWORD v_ = 0x10cu; m->esp -= 4; M32(m->esp) = v_; }	/* 43994f: push 0x10c */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 439954: push esi */
	m->esp -= 4; M32(m->esp) = 0x43995au; native_call(m, 0x4029d0u);	/* 439955: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43995a: add esp, 0x10 */
	{ DWORD a_ = m->ebx, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 43995d: add ebx, 0x80 */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 439963: inc ebp */
	{ DWORD a_ = m->esi, b_ = 0xa0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 439964: add esi, 0xa0 */
	{ DWORD a_ = m->ebx, b_ = 0x7518a4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43996a: cmp ebx, 0x7518a4 */
	if (m->sf != m->of) goto L_439875;	/* 439970: jl 0x439875 */
	m->ebp = M32((DWORD)(0x4a9228u));	/* 439976: mov ebp, dword ptr [0x4a9228] */
L_43997c:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43997c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439981: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439986: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43998b: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x439992u; native_call(m, m->ebp);	/* 439990: call ebp */
	m->edx = M32((DWORD)(0x9dd364u));	/* 439992: mov edx, dword ptr [0x9dd364] */
	m->eax = M32((DWORD)(0x9dd360u));	/* 439998: mov eax, dword ptr [0x9dd360] */
	m->ecx = M32((DWORD)(0x9dd35cu));	/* 43999d: mov ecx, dword ptr [0x9dd35c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4399a3: push edx */
	m->edx = M32((DWORD)(0x9dd358u));	/* 4399a4: mov edx, dword ptr [0x9dd358] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4399aa: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4399ab: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4399ac: push edx */
	m->esp -= 4; M32(m->esp) = 0x4399b2u; native_call(m, 0x428a00u);	/* 4399ad: call 0x428a00 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4399b2: add esp, 0x10 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4399b5: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4399b6: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4399b7: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4399b8: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4399b9: add esp, 0x24 */
	m->esp += 4 + 0; return;	/* 4399bc: ret  */
}

/* profile_44cf70 (0x44cf70), lifted by tools/lift.py */
static void lift_44cf70(X86 *m)
{
	m->eax = M32((DWORD)(0x9f9008u));	/* 44cf70: mov eax, dword ptr [0x9f9008] */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44cf75: sub esp, 0x24 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44cf78: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_44d6ea;	/* 44cf7a: jle 0x44d6ea */
	m->eax = M32((DWORD)(0x9f8d74u));	/* 44cf80: mov eax, dword ptr [0x9f8d74] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44cf85: push ebx */
	m->ebx = 0x1u;	/* 44cf86: mov ebx, 1 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 44cf8b: push ebp */
	m->eax = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44cf8c: lea eax, [eax + eax*8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44cf8f: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44cf90: push edi */
	m->ecx = M32((DWORD)(m->eax*8 + 0x9f688cu));	/* 44cf91: mov ecx, dword ptr [eax*8 + 0x9f688c] */
	m->eax = M32((DWORD)(0x9f8f10u));	/* 44cf98: mov eax, dword ptr [0x9f8f10] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44cf9d: cmp eax, ebx */
	M32((DWORD)(0x9f8d6cu)) = m->ecx;	/* 44cf9f: mov dword ptr [0x9f8d6c], ecx */
	if (!m->zf) goto L_44cfc4;	/* 44cfa5: jne 0x44cfc4 */
	m->edx = M32((DWORD)(0x9f8ebcu));	/* 44cfa7: mov edx, dword ptr [0x9f8ebc] */
	m->eax = M32((DWORD)(0x9f8eb8u));	/* 44cfad: mov eax, dword ptr [0x9f8eb8] */
	m->ecx = M32((DWORD)(0x9f8eb4u));	/* 44cfb2: mov ecx, dword ptr [0x9f8eb4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44cfb8: push edx */
	m->edx = M32((DWORD)(0x9f8eb0u));	/* 44cfb9: mov edx, dword ptr [0x9f8eb0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44cfbf: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44cfc0: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44cfc1: push edx */
	goto L_44cffa;	/* 44cfc2: jmp 0x44cffa */
L_44cfc4:
	FPUSH(x87_ldm((const float *)(DWORD)(0x9f8eb8u)));	/* 44cfc4: fld dword ptr [0x9f8eb8] */
	m->eax = M32((DWORD)(0x9f8ebcu));	/* 44cfca: mov eax, dword ptr [0x9f8ebc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 44cfcf: fmul dword ptr [0x4a942c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44cfd5: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44cfd6: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 44cfd7: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x9f8eb4u)));	/* 44cfda: fld dword ptr [0x9f8eb4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 44cfe0: fmul dword ptr [0x4a942c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44cfe6: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 44cfe7: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x9f8eb0u)));	/* 44cfea: fld dword ptr [0x9f8eb0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 44cff0: fmul dword ptr [0x4a942c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44cff6: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 44cff7: fstp dword ptr [esp] */
L_44cffa:
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 44cffa: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x44d004u; native_call(m, 0x41f0e0u);	/* 44cfff: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44d004: add esp, 0x14 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 44d007: xor edi, edi */
	m->esi = 0x75e824u;	/* 44d009: mov esi, 0x75e824 */
L_44d00e:
	m->ecx = M32((DWORD)(0x9f8e4cu));	/* 44d00e: mov ecx, dword ptr [0x9f8e4c] */
	m->eax = M32((DWORD)(0x9f8e48u));	/* 44d014: mov eax, dword ptr [0x9f8e48] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44d019: push esi */
	{ DWORD a_ = m->eax, b_ = 0x10cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44d01a: add eax, 0x10c */
	m->edx = (DWORD)(m->edi + m->ecx*1 + 0x24u);	/* 44d01f: lea edx, [edi + ecx + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d023: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d024: push eax */
	m->esp -= 4; M32(m->esp) = 0x44d02au; native_call(m, 0x402620u);	/* 44d025: call 0x402620 */
	{ DWORD a_ = m->esi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 44d02a: add esi, 0x80 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44d030: add esp, 0xc */
	{ DWORD a_ = m->edi, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44d033: add edi, 0x14 */
	{ DWORD a_ = m->esi, b_ = 0x75eea4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44d036: cmp esi, 0x75eea4 */
	if (m->sf != m->of) goto L_44d00e;	/* 44d03c: jl 0x44d00e */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d03e: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x44d049u; native_call(m, M32(0x4a9224u));	/* 44d043: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x4dfa00u));	/* 44d049: mov eax, dword ptr [0x4dfa00] */
	m->ecx = m->eax;	/* 44d04e: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44d050: and ecx, 0x800001ff */
	if (!m->sf) goto L_44d060;	/* 44d056: jns 0x44d060 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 44d058: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44d059: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 44d05f: inc ecx */
L_44d060:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 44d060: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44d061: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d067: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44d068: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 44d06a: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 44d070: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 44d073: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x44d07cu; native_call(m, 0x4566c0u);	/* 44d077: call 0x4566c0 */
	m->eax = M32((DWORD)(0x9f8f10u));	/* 44d07c: mov eax, dword ptr [0x9f8f10] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d081: push 0x3f800000 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44d086: cmp eax, ebx */
	if (!m->zf) goto L_44d09b;	/* 44d088: jne 0x44d09b */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d08a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d08f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d094: push 0x3f800000 */
	goto L_44d0aa;	/* 44d099: jmp 0x44d0aa */
L_44d09b:
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d09b: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d0a0: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d0a5: push 0x3f000000 */
L_44d0aa:
	m->esp -= 4; M32(m->esp) = 0x44d0b0u; native_call(m, M32(0x4a9228u));	/* 44d0aa: call dword ptr [0x4a9228] */
	m->ecx = M32((DWORD)(0x9f8d6cu));	/* 44d0b0: mov ecx, dword ptr [0x9f8d6c] */
	m->esi = 0x3u;	/* 44d0b6: mov esi, 3 */
	m->eax = m->ecx;	/* 44d0bb: mov eax, ecx */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d0bd: push 7 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 44d0bf: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->esi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 44d0c0: idiv esi */
	m->eax = 0x55555556u;	/* 44d0c2: mov eax, 0x55555556 */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 44d0c7: mov dword ptr [esp + 0x14], edx */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 44d0cb: imul ecx */
	m->eax = m->edx;	/* 44d0cd: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 44d0cf: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44d0d2: add edx, eax */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 44d0d4: mov dword ptr [esp + 0x18], edx */
	m->esp -= 4; M32(m->esp) = 0x44d0deu; native_call(m, M32(0x4a921cu));	/* 44d0d8: call dword ptr [0x4a921c] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 44d0de: fild dword ptr [esp + 0x14] */
	m->ebp = M32((DWORD)(0x4a920cu));	/* 44d0e2: mov ebp, dword ptr [0x4a920c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a95ecu));	/* 44d0e8: fmul dword ptr [0x4a95ec] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 44d0ee: fst dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 44d0f2: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 44d0f8: fstp dword ptr [esp + 0x18] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 44d0fc: fild dword ptr [esp + 0x10] */
	m->esi = M32((DWORD)(m->esp + 0x18u));	/* 44d100: mov esi, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44d104: push esi */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a95ecu));	/* 44d105: fmul dword ptr [0x4a95ec] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 44d10b: fst dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 44d10f: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 44d115: fstp dword ptr [esp + 0x20] */
	m->edi = M32((DWORD)(m->esp + 0x20u));	/* 44d119: mov edi, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44d11d: push edi */
	m->esp -= 4; M32(m->esp) = 0x44d120u; native_call(m, m->ebp);	/* 44d11e: call ebp */
	m->ecx = M32((DWORD)(0x9f8e4cu));	/* 44d120: mov ecx, dword ptr [0x9f8e4c] */
	m->edx = M32((DWORD)(0x9f8e48u));	/* 44d126: mov edx, dword ptr [0x9f8e48] */
	{ DWORD a_ = m->ecx, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44d12c: add ecx, 0x24 */
	{ DWORD a_ = m->edx, b_ = 0x1a4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44d12f: add edx, 0x1a4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d135: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d136: push edx */
	m->esp -= 4; M32(m->esp) = 0x44d13cu; native_call(m, 0x41ef60u);	/* 44d137: call 0x41ef60 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 44d13c: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a95e8u));	/* 44d140: fadd dword ptr [0x4a95e8] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44d146: add esp, 8 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 44d149: fmul dword ptr [0x4a957c] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44d14f: push esi */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 44d150: fstp dword ptr [esp + 0x20] */
	m->esi = M32((DWORD)(m->esp + 0x20u));	/* 44d154: mov esi, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44d158: push esi */
	m->esp -= 4; M32(m->esp) = 0x44d15bu; native_call(m, m->ebp);	/* 44d159: call ebp */
	m->eax = M32((DWORD)(0x9f8e4cu));	/* 44d15b: mov eax, dword ptr [0x9f8e4c] */
	m->ecx = M32((DWORD)(0x9f8e48u));	/* 44d160: mov ecx, dword ptr [0x9f8e48] */
	{ DWORD a_ = m->eax, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44d166: add eax, 0x24 */
	{ DWORD a_ = m->ecx, b_ = 0x1e4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44d169: add ecx, 0x1e4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d16f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d170: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44d176u; native_call(m, 0x41ef60u);	/* 44d171: call 0x41ef60 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 44d176: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a95e8u));	/* 44d17a: fadd dword ptr [0x4a95e8] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44d180: add esp, 8 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 44d183: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 44d189: fstp dword ptr [esp + 0x1c] */
	m->ebx = M32((DWORD)(m->esp + 0x1cu));	/* 44d18d: mov ebx, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d191: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44d192: push esi */
	m->esp -= 4; M32(m->esp) = 0x44d195u; native_call(m, m->ebp);	/* 44d193: call ebp */
	m->edx = M32((DWORD)(0x9f8e4cu));	/* 44d195: mov edx, dword ptr [0x9f8e4c] */
	m->eax = M32((DWORD)(0x9f8e48u));	/* 44d19b: mov eax, dword ptr [0x9f8e48] */
	{ DWORD a_ = m->edx, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44d1a0: add edx, 0x64 */
	{ DWORD a_ = m->eax, b_ = 0x1e4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44d1a3: add eax, 0x1e4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d1a8: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d1a9: push eax */
	m->esp -= 4; M32(m->esp) = 0x44d1afu; native_call(m, 0x41ef60u);	/* 44d1aa: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44d1af: add esp, 8 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d1b2: push ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44d1b3: push edi */
	m->esp -= 4; M32(m->esp) = 0x44d1b6u; native_call(m, m->ebp);	/* 44d1b4: call ebp */
	m->ecx = M32((DWORD)(0x9f8e4cu));	/* 44d1b6: mov ecx, dword ptr [0x9f8e4c] */
	m->edx = M32((DWORD)(0x9f8e48u));	/* 44d1bc: mov edx, dword ptr [0x9f8e48] */
	{ DWORD a_ = m->ecx, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44d1c2: add ecx, 0x64 */
	{ DWORD a_ = m->edx, b_ = 0x1a4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44d1c5: add edx, 0x1a4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d1cb: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d1cc: push edx */
	m->esp -= 4; M32(m->esp) = 0x44d1d2u; native_call(m, 0x41ef60u);	/* 44d1cd: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44d1d2: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x44d1dbu; native_call(m, M32(0x4a9220u));	/* 44d1d5: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d1db: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x44d1e6u; native_call(m, M32(0x4a922cu));	/* 44d1e0: call dword ptr [0x4a922c] */
	{ DWORD v_ = 0x3e99999au; m->esp -= 4; M32(m->esp) = v_; }	/* 44d1e6: push 0x3e99999a */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d1eb: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d1ed: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d1f2: push 0x3f800000 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d1f7: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x44d201u; native_call(m, 0x41f0e0u);	/* 44d1fc: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9f8e4cu));	/* 44d201: mov eax, dword ptr [0x9f8e4c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d206: push 0 */
	m->ecx = (DWORD)(m->eax + 0x64u);	/* 44d208: lea ecx, [eax + 0x64] */
	{ DWORD a_ = m->eax, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44d20b: add eax, 0x24 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d20e: push ecx */
	m->ecx = M32((DWORD)(0x9f8e48u));	/* 44d20f: mov ecx, dword ptr [0x9f8e48] */
	m->edx = (DWORD)(m->ecx + 0x1e4u);	/* 44d215: lea edx, [ecx + 0x1e4] */
	{ DWORD a_ = m->ecx, b_ = 0x1a4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44d21b: add ecx, 0x1a4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d221: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d222: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d223: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44d229u; native_call(m, 0x427970u);	/* 44d224: call 0x427970 */
	m->eax = M32((DWORD)(0x9f8f10u));	/* 44d229: mov eax, dword ptr [0x9f8f10] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44d22e: add esp, 0x28 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44d231: cmp eax, 1 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d234: push 0x3f800000 */
	if (!m->zf) goto L_44d24c;	/* 44d239: jne 0x44d24c */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d23b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d240: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d245: push 0x3f800000 */
	goto L_44d25b;	/* 44d24a: jmp 0x44d25b */
L_44d24c:
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d24c: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d251: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d256: push 0x3f000000 */
L_44d25b:
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d25b: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x44d265u; native_call(m, 0x41f0e0u);	/* 44d260: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9f8d6cu));	/* 44d265: mov eax, dword ptr [0x9f8d6c] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44d26a: add esp, 0x14 */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44d26d: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 44d270: lea edx, [eax + ecx*2] */
	m->ecx = M32((DWORD)(0x9f8e4cu));	/* 44d273: mov ecx, dword ptr [0x9f8e4c] */
	{ DWORD a_ = m->ecx, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44d279: add ecx, 0x24 */
	m->eax = (DWORD)(m->edx*4 + 0x9f9040u);	/* 44d27c: lea eax, [edx*4 + 0x9f9040] */
	m->edx = M32((DWORD)(0x9f8e48u));	/* 44d283: mov edx, dword ptr [0x9f8e48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d289: push eax */
	{ DWORD a_ = m->edx, b_ = 0x14eu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44d28a: add edx, 0x14e */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d290: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d291: push edx */
	m->esp -= 4; M32(m->esp) = 0x44d297u; native_call(m, 0x402620u);	/* 44d292: call 0x402620 */
	m->eax = M32((DWORD)(0x9f8d6cu));	/* 44d297: mov eax, dword ptr [0x9f8d6c] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44d29c: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 44d29f: lea edx, [eax + ecx*2] */
	m->eax = (DWORD)(m->edx*4 + 0x9f9050u);	/* 44d2a2: lea eax, [edx*4 + 0x9f9050] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d2a9: push eax */
	m->eax = M32((DWORD)(0x9f8e48u));	/* 44d2aa: mov eax, dword ptr [0x9f8e48] */
	m->ecx = (DWORD)(m->eax + 0x38u);	/* 44d2af: lea ecx, [eax + 0x38] */
	{ DWORD a_ = m->eax, b_ = 0x14eu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44d2b2: add eax, 0x14e */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d2b7: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d2b8: push eax */
	m->esp -= 4; M32(m->esp) = 0x44d2beu; native_call(m, 0x402620u);	/* 44d2b9: call 0x402620 */
	m->eax = M32((DWORD)(0x9f8d6cu));	/* 44d2be: mov eax, dword ptr [0x9f8d6c] */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44d2c3: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 44d2c6: lea eax, [eax + edx*2] */
	m->ecx = M32((DWORD)(m->eax*4 + 0x9f9060u));	/* 44d2c9: mov ecx, dword ptr [eax*4 + 0x9f9060] */
	m->eax = M32((DWORD)(0x9f8e48u));	/* 44d2d0: mov eax, dword ptr [0x9f8e48] */
	{ DWORD a_ = m->ecx, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44d2d5: shl ecx, 7 */
	{ DWORD a_ = m->ecx, b_ = 0x75eea4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44d2d8: add ecx, 0x75eea4 */
	m->edx = (DWORD)(m->eax + 0x4cu);	/* 44d2de: lea edx, [eax + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d2e1: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x14eu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44d2e2: add eax, 0x14e */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d2e7: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d2e8: push eax */
	m->esp -= 4; M32(m->esp) = 0x44d2eeu; native_call(m, 0x402620u);	/* 44d2e9: call 0x402620 */
	m->eax = (DWORD)(m->esp + 0x44u);	/* 44d2ee: lea eax, [esp + 0x44] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 44d2f2: push 0xa */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d2f4: push eax */
	m->eax = M32((DWORD)(0x9f8d6cu));	/* 44d2f5: mov eax, dword ptr [0x9f8d6c] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44d2fa: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 44d2fd: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->edx*4 + 0x9f9064u));	/* 44d300: mov eax, dword ptr [edx*4 + 0x9f9064] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d307: push eax */
	m->esp -= 4; M32(m->esp) = 0x44d30du; native_call(m, 0x49fb53u);	/* 44d308: call 0x49fb53 */
	m->edx = M32((DWORD)(0x9f8e4cu));	/* 44d30d: mov edx, dword ptr [0x9f8e4c] */
	m->eax = M32((DWORD)(0x9f8e48u));	/* 44d313: mov eax, dword ptr [0x9f8e48] */
	m->ecx = (DWORD)(m->esp + 0x50u);	/* 44d318: lea ecx, [esp + 0x50] */
	{ DWORD a_ = m->edx, b_ = 0x60u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44d31c: add edx, 0x60 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d31f: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x14eu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44d320: add eax, 0x14e */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d325: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d326: push eax */
	m->esp -= 4; M32(m->esp) = 0x44d32cu; native_call(m, 0x402620u);	/* 44d327: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44d32c: add esp, 0x3c */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44d32f: xor eax, eax */
	M32((DWORD)(m->esp + 0x10u)) = 0x50u;	/* 44d331: mov dword ptr [esp + 0x10], 0x50 */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 44d339: mov dword ptr [esp + 0x14], eax */
L_44d33d:
	{ DWORD a_ = m->eax, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44d33d: cmp eax, 8 */
	if (!m->cf && !m->zf) goto L_44d457;	/* 44d340: ja 0x44d457 */
	switch (m->eax) { case 0: goto L_44d34d; case 1: goto L_44d36b; case 2: goto L_44d38a; case 3: goto L_44d3a8; case 4: goto L_44d3c7; case 5: goto L_44d3e2; case 6: goto L_44d3fe; case 7: goto L_44d419; case 8: goto L_44d435; default: abort(); }	/* 44d346: jmp dword ptr [eax*4 + 0x44d6f0] */
L_44d34d:
	m->eax = M32((DWORD)(0x9f8d6cu));	/* 44d34d: mov eax, dword ptr [0x9f8d6c] */
	m->ecx = (DWORD)(m->esp + 0x20u);	/* 44d352: lea ecx, [esp + 0x20] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 44d356: push 0xa */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d358: push ecx */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44d359: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 44d35c: lea eax, [eax + edx*2] */
	m->ecx = M32((DWORD)(m->eax*4 + 0x9f9068u));	/* 44d35f: mov ecx, dword ptr [eax*4 + 0x9f9068] */
	goto L_44d44e;	/* 44d366: jmp 0x44d44e */
L_44d36b:
	m->eax = M32((DWORD)(0x9f8d6cu));	/* 44d36b: mov eax, dword ptr [0x9f8d6c] */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 44d370: lea edx, [esp + 0x20] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 44d374: push 0xa */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d376: push edx */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44d377: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 44d37a: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->edx*4 + 0x9f906cu));	/* 44d37d: mov eax, dword ptr [edx*4 + 0x9f906c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d384: push eax */
	goto L_44d44f;	/* 44d385: jmp 0x44d44f */
L_44d38a:
	m->eax = M32((DWORD)(0x9f8d6cu));	/* 44d38a: mov eax, dword ptr [0x9f8d6c] */
	m->ecx = (DWORD)(m->esp + 0x20u);	/* 44d38f: lea ecx, [esp + 0x20] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 44d393: push 0xa */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d395: push ecx */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44d396: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 44d399: lea eax, [eax + edx*2] */
	m->ecx = M32((DWORD)(m->eax*4 + 0x9f9070u));	/* 44d39c: mov ecx, dword ptr [eax*4 + 0x9f9070] */
	goto L_44d44e;	/* 44d3a3: jmp 0x44d44e */
L_44d3a8:
	m->eax = M32((DWORD)(0x9f8d6cu));	/* 44d3a8: mov eax, dword ptr [0x9f8d6c] */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 44d3ad: lea edx, [esp + 0x20] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 44d3b1: push 0xa */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d3b3: push edx */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44d3b4: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 44d3b7: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->edx*4 + 0x9f9074u));	/* 44d3ba: mov eax, dword ptr [edx*4 + 0x9f9074] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d3c1: push eax */
	goto L_44d44f;	/* 44d3c2: jmp 0x44d44f */
L_44d3c7:
	m->eax = M32((DWORD)(0x9f8d6cu));	/* 44d3c7: mov eax, dword ptr [0x9f8d6c] */
	m->ecx = (DWORD)(m->esp + 0x20u);	/* 44d3cc: lea ecx, [esp + 0x20] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 44d3d0: push 0xa */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d3d2: push ecx */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44d3d3: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 44d3d6: lea eax, [eax + edx*2] */
	m->ecx = M32((DWORD)(m->eax*4 + 0x9f9078u));	/* 44d3d9: mov ecx, dword ptr [eax*4 + 0x9f9078] */
	goto L_44d44e;	/* 44d3e0: jmp 0x44d44e */
L_44d3e2:
	m->eax = M32((DWORD)(0x9f8d6cu));	/* 44d3e2: mov eax, dword ptr [0x9f8d6c] */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 44d3e7: lea edx, [esp + 0x20] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 44d3eb: push 0xa */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d3ed: push edx */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44d3ee: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 44d3f1: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->edx*4 + 0x9f907cu));	/* 44d3f4: mov eax, dword ptr [edx*4 + 0x9f907c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d3fb: push eax */
	goto L_44d44f;	/* 44d3fc: jmp 0x44d44f */
L_44d3fe:
	m->eax = M32((DWORD)(0x9f8d6cu));	/* 44d3fe: mov eax, dword ptr [0x9f8d6c] */
	m->ecx = (DWORD)(m->esp + 0x20u);	/* 44d403: lea ecx, [esp + 0x20] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 44d407: push 0xa */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d409: push ecx */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44d40a: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 44d40d: lea eax, [eax + edx*2] */
	m->ecx = M32((DWORD)(m->eax*4 + 0x9f9080u));	/* 44d410: mov ecx, dword ptr [eax*4 + 0x9f9080] */
	goto L_44d44e;	/* 44d417: jmp 0x44d44e */
L_44d419:
	m->eax = M32((DWORD)(0x9f8d6cu));	/* 44d419: mov eax, dword ptr [0x9f8d6c] */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 44d41e: lea edx, [esp + 0x20] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 44d422: push 0xa */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d424: push edx */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44d425: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 44d428: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->edx*4 + 0x9f9084u));	/* 44d42b: mov eax, dword ptr [edx*4 + 0x9f9084] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d432: push eax */
	goto L_44d44f;	/* 44d433: jmp 0x44d44f */
L_44d435:
	m->eax = M32((DWORD)(0x9f8d6cu));	/* 44d435: mov eax, dword ptr [0x9f8d6c] */
	m->ecx = (DWORD)(m->esp + 0x20u);	/* 44d43a: lea ecx, [esp + 0x20] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 44d43e: push 0xa */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d440: push ecx */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44d441: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 44d444: lea eax, [eax + edx*2] */
	m->ecx = M32((DWORD)(m->eax*4 + 0x9f9088u));	/* 44d447: mov ecx, dword ptr [eax*4 + 0x9f9088] */
L_44d44e:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d44e: push ecx */
L_44d44f:
	m->esp -= 4; M32(m->esp) = 0x44d454u; native_call(m, 0x49fb53u);	/* 44d44f: call 0x49fb53 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44d454: add esp, 0xc */
L_44d457:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + 0x20u))) & 0xff) << 0);	/* 44d457: mov al, byte ptr [esp + 0x20] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44d45b: xor edx, edx */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x2du & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 44d45d: cmp al, 0x2d */
	if (m->zf) goto L_44d480;	/* 44d45f: je 0x44d480 */
	m->edi = (DWORD)(m->esp + 0x20u);	/* 44d461: lea edi, [esp + 0x20] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44d465: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44d468: xor eax, eax */
	m->edx = 0x8u;	/* 44d46a: mov edx, 8 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44d46f: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44d471: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 44d473: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44d474: cmp ecx, 2 */
	if (!m->cf) goto L_44d498;	/* 44d477: jae 0x44d498 */
	m->edx = 0x10u;	/* 44d479: mov edx, 0x10 */
	goto L_44d498;	/* 44d47e: jmp 0x44d498 */
L_44d480:
	m->edi = (DWORD)(m->esp + 0x20u);	/* 44d480: lea edi, [esp + 0x20] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44d484: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44d487: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44d489: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44d48b: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 44d48d: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44d48e: cmp ecx, 3 */
	if (!m->cf) goto L_44d498;	/* 44d491: jae 0x44d498 */
	m->edx = 0x8u;	/* 44d493: mov edx, 8 */
L_44d498:
	m->edi = 0x4b3e2cu;	/* 44d498: mov edi, 0x4b3e2c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44d49d: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44d4a0: xor eax, eax */
	m->ebx = (DWORD)(m->esp + 0x20u);	/* 44d4a2: lea ebx, [esp + 0x20] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44d4a6: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44d4a8: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44d4aa: sub edi, ecx */
	m->esi = m->edi;	/* 44d4ac: mov esi, edi */
	m->edi = m->ebx;	/* 44d4ae: mov edi, ebx */
	m->ebx = m->ecx;	/* 44d4b0: mov ebx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44d4b2: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44d4b5: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 44d4b7: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 44d4b9: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44d4ba: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 44d4bd: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebx;	/* 44d4bf: mov ecx, ebx */
	m->eax = (DWORD)(m->esp + 0x20u);	/* 44d4c1: lea eax, [esp + 0x20] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44d4c5: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d4c8: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 44d4c9: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x9f8e4cu));	/* 44d4cb: mov ecx, dword ptr [0x9f8e4c] */
	m->esi = M32((DWORD)(m->esp + 0x14u));	/* 44d4d1: mov esi, dword ptr [esp + 0x14] */
	m->eax = (DWORD)(m->esi + m->ecx*1 + 0x24u);	/* 44d4d5: lea eax, [esi + ecx + 0x24] */
	m->ecx = M32((DWORD)(0x9f8e48u));	/* 44d4d9: mov ecx, dword ptr [0x9f8e48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d4df: push eax */
	m->edx = (DWORD)(m->ecx + m->edx*1 + 0x166u);	/* 44d4e0: lea edx, [ecx + edx + 0x166] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d4e7: push edx */
	m->esp -= 4; M32(m->esp) = 0x44d4edu; native_call(m, 0x402620u);	/* 44d4e8: call 0x402620 */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 44d4ed: mov eax, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44d4f1: add esp, 0xc */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 44d4f4: inc eax */
	{ DWORD a_ = m->esi, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 44d4f5: add esi, 0x14 */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 44d4f8: mov dword ptr [esp + 0x14], eax */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 44d4fc: mov dword ptr [esp + 0x10], esi */
	m->ecx = (DWORD)(m->eax + 0x4u);	/* 44d500: lea ecx, [eax + 4] */
	{ DWORD a_ = m->ecx, b_ = 0xdu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44d503: cmp ecx, 0xd */
	if (m->sf != m->of) goto L_44d33d;	/* 44d506: jl 0x44d33d */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d50c: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x44d517u; native_call(m, M32(0x4a9224u));	/* 44d511: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 44d517: mov eax, dword ptr [0x9db0a4] */
	m->edx = m->eax;	/* 44d51c: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44d51e: and edx, 0x800001ff */
	if (!m->sf) goto L_44d52e;	/* 44d524: jns 0x44d52e */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 44d526: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44d527: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 44d52d: inc edx */
L_44d52e:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d52e: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 44d52f: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 44d535: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44d536: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44d53c: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 44d53e: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 44d541: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x44d54au; native_call(m, 0x4566c0u);	/* 44d545: call 0x4566c0 */
	m->ebx = M32((DWORD)(0x4a9228u));	/* 44d54a: mov ebx, dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d550: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d555: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d55a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d55f: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44d566u; native_call(m, m->ebx);	/* 44d564: call ebx */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 44d566: xor esi, esi */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 44d568: xor edi, edi */
	goto L_44d572;	/* 44d56a: jmp 0x44d572 */
L_44d56c:
	m->ebx = M32((DWORD)(0x4a9228u));	/* 44d56c: mov ebx, dword ptr [0x4a9228] */
L_44d572:
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d572: push 7 */
	m->esp -= 4; M32(m->esp) = 0x44d57au; native_call(m, M32(0x4a921cu));	/* 44d574: call dword ptr [0x4a921c] */
	m->eax = M32((DWORD)(0x9f8f10u));	/* 44d57a: mov eax, dword ptr [0x9f8f10] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d57f: push 0x3f800000 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44d584: cmp eax, 1 */
	if (!m->zf) goto L_44d59a;	/* 44d587: jne 0x44d59a */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d589: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d58e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d593: push 0x3f800000 */
	goto L_44d5a9;	/* 44d598: jmp 0x44d5a9 */
L_44d59a:
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d59a: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d59f: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d5a4: push 0x3f000000 */
L_44d5a9:
	m->esp -= 4; M32(m->esp) = 0x44d5abu; native_call(m, m->ebx);	/* 44d5a9: call ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x9f8ec0u)));	/* 44d5ab: fld dword ptr [edi + 0x9f8ec0] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x9f8d34u));	/* 44d5b1: fsub dword ptr [edi + 0x9f8d34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 44d5b7: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 44d5bd: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x9f8d34u));	/* 44d5c3: fadd dword ptr [edi + 0x9f8d34] */
	MF((DWORD)(m->edi + 0x9f8d34u)) = (float)ST(0);	/* 44d5c9: fst dword ptr [edi + 0x9f8d34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 44d5cf: fmul dword ptr [0x4a9420] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9468u));	/* 44d5d5: fadd dword ptr [0x4a9468] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 44d5db: fst dword ptr [esp + 0x14] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a953cu)); FPOP();	/* 44d5df: fcomp dword ptr [0x4a953c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 44d5e5: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 44d5e7: test ah, 0x41 */
	if (!m->zf) goto L_44d5f4;	/* 44d5ea: jne 0x44d5f4 */
	M32((DWORD)(m->esp + 0x14u)) = 0x3f733333u;	/* 44d5ec: mov dword ptr [esp + 0x14], 0x3f733333 */
L_44d5f4:
	{ DWORD v_ = 0x3e400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d5f4: push 0x3e400000 */
	{ DWORD v_ = 0x3d4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44d5f9: push 0x3d4ccccd */
	m->esp -= 4; M32(m->esp) = 0x44d600u; native_call(m, m->ebp);	/* 44d5fe: call ebp */
	m->edx = M32((DWORD)(0x9f8e4cu));	/* 44d600: mov edx, dword ptr [0x9f8e4c] */
	m->ecx = M32((DWORD)(0x9f8e48u));	/* 44d606: mov ecx, dword ptr [0x9f8e48] */
	{ DWORD a_ = m->ecx, b_ = 0x18au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44d60c: add ecx, 0x18a */
	m->eax = (DWORD)(m->esi + m->edx*1 + 0x78u);	/* 44d612: lea eax, [esi + edx + 0x78] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d616: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d617: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44d61du; native_call(m, 0x41ef60u);	/* 44d618: call 0x41ef60 */
	m->ebx = M32((DWORD)(m->esp + 0x1cu));	/* 44d61d: mov ebx, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44d621: add esp, 8 */
	{ DWORD v_ = 0x3e400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d624: push 0x3e400000 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d629: push ebx */
	m->esp -= 4; M32(m->esp) = 0x44d62cu; native_call(m, m->ebp);	/* 44d62a: call ebp */
	m->edx = M32((DWORD)(0x9f8e4cu));	/* 44d62c: mov edx, dword ptr [0x9f8e4c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x9f8d34u)));	/* 44d632: fld dword ptr [edi + 0x9f8d34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a95f0u));	/* 44d638: fmul dword ptr [0x4a95f0] */
	m->eax = (DWORD)(m->esi + m->edx*1 + 0x78u);	/* 44d63e: lea eax, [esi + edx + 0x78] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d642: push eax */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 44d643: call 0x49ec14 */
	m->ecx = M32((DWORD)(0x9f8e48u));	/* 44d648: mov ecx, dword ptr [0x9f8e48] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44d64e: sub ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x18au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44d650: add ecx, 0x18a */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d656: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44d65cu; native_call(m, 0x41ef60u);	/* 44d657: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44d65c: add esp, 8 */
	{ DWORD v_ = 0x3e400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d65f: push 0x3e400000 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d664: push ebx */
	m->esp -= 4; M32(m->esp) = 0x44d667u; native_call(m, m->ebp);	/* 44d665: call ebp */
	m->edx = M32((DWORD)(0x9f8e4cu));	/* 44d667: mov edx, dword ptr [0x9f8e4c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x9f8d34u)));	/* 44d66d: fld dword ptr [edi + 0x9f8d34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a95f0u));	/* 44d673: fmul dword ptr [0x4a95f0] */
	m->eax = (DWORD)(m->esi + m->edx*1 + 0x7du);	/* 44d679: lea eax, [esi + edx + 0x7d] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d67d: push eax */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 44d67e: call 0x49ec14 */
	m->ecx = M32((DWORD)(0x9f8e48u));	/* 44d683: mov ecx, dword ptr [0x9f8e48] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44d689: sub ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x18au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44d68b: add ecx, 0x18a */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d691: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44d697u; native_call(m, 0x41ef60u);	/* 44d692: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44d697: add esp, 8 */
	{ DWORD v_ = 0x3e400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d69a: push 0x3e400000 */
	{ DWORD v_ = 0x3d4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44d69f: push 0x3d4ccccd */
	m->esp -= 4; M32(m->esp) = 0x44d6a6u; native_call(m, m->ebp);	/* 44d6a4: call ebp */
	m->edx = M32((DWORD)(0x9f8e4cu));	/* 44d6a6: mov edx, dword ptr [0x9f8e4c] */
	m->ecx = M32((DWORD)(0x9f8e48u));	/* 44d6ac: mov ecx, dword ptr [0x9f8e48] */
	{ DWORD a_ = m->ecx, b_ = 0x18au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44d6b2: add ecx, 0x18a */
	m->eax = (DWORD)(m->esi + m->edx*1 + 0x7du);	/* 44d6b8: lea eax, [esi + edx + 0x7d] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d6bc: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d6bd: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44d6c3u; native_call(m, 0x41ef60u);	/* 44d6be: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44d6c3: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x44d6ccu; native_call(m, M32(0x4a9220u));	/* 44d6c6: call dword ptr [0x4a9220] */
	{ DWORD a_ = m->edi, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44d6cc: add edi, 4 */
	{ DWORD a_ = m->esi, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 44d6cf: add esi, 0x14 */
	{ DWORD a_ = m->edi, b_ = 0x24u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44d6d2: cmp edi, 0x24 */
	if (m->sf != m->of) goto L_44d56c;	/* 44d6d5: jl 0x44d56c */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d6db: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x44d6e6u; native_call(m, M32(0x4a922cu));	/* 44d6e0: call dword ptr [0x4a922c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 44d6e6: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44d6e7: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 44d6e8: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 44d6e9: pop ebx */
L_44d6ea:
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44d6ea: add esp, 0x24 */
	m->esp += 4 + 0; return;	/* 44d6ed: ret  */
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
