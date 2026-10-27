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

static void lift_460570(X86 *m);

/* game_loadAllData (0x460570), lifted by tools/lift.py */
static void lift_460570(X86 *m)
{
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 460570: push -1 */
	{ DWORD v_ = 0x4a8b56u; m->esp -= 4; M32(m->esp) = v_; }	/* 460572: push 0x4a8b56 */
	m->eax = M32((DWORD)&g_lift_fs0);	/* 460577: mov eax, dword ptr fs:[0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46057d: push eax */
	M32((DWORD)&g_lift_fs0) = m->esp;	/* 46057e: mov dword ptr fs:[0], esp */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 460585: sub esp, 0xc */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 460588: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 460589: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46058a: push esi */
	m->esi = m->ecx;	/* 46058b: mov esi, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46058d: push edi */
	M32((DWORD)(m->esp + 0x18u)) = m->esi;	/* 46058e: mov dword ptr [esp + 0x18], esi */
	m->ecx = (DWORD)(m->esi + 0xcu);	/* 460592: lea ecx, [esi + 0xc] */
	m->esp -= 4; M32(m->esp) = 0x46059au; native_call(m, 0x487430u);	/* 460595: call 0x487430 */
	m->ecx = (DWORD)(m->esi + 0x74u);	/* 46059a: lea ecx, [esi + 0x74] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 46059d: xor ebx, ebx */
	M32((DWORD)(m->esp + 0x24u)) = m->ebx;	/* 46059f: mov dword ptr [esp + 0x24], ebx */
	M32((DWORD)(m->ecx + 0x0u)) = 0x4aa24cu;	/* 4605a3: mov dword ptr [ecx], 0x4aa24c */
	m->esp -= 4; M32(m->esp) = 0x4605aeu; native_call(m, 0x483fc0u);	/* 4605a9: call 0x483fc0 */
	m->ebp = (DWORD)(m->esi + 0x1f36c8u);	/* 4605ae: lea ebp, [esi + 0x1f36c8] */
	M8((DWORD)(m->esp + 0x24u)) = (BYTE)(0x1u);	/* 4605b4: mov byte ptr [esp + 0x24], 1 */
	m->edi = m->ebp;	/* 4605b9: mov edi, ebp */
	M32((DWORD)(m->esp + 0x14u)) = m->edi;	/* 4605bb: mov dword ptr [esp + 0x14], edi */
	m->ecx = (DWORD)(m->edi + 0xa10u);	/* 4605bf: lea ecx, [edi + 0xa10] */
	m->esp -= 4; M32(m->esp) = 0x4605cau; native_call(m, 0x463790u);	/* 4605c5: call 0x463790 */
	{ DWORD v_ = 0x45fff0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4605ca: push 0x45fff0 */
	{ DWORD v_ = 0x400u; m->esp -= 4; M32(m->esp) = v_; }	/* 4605cf: push 0x400 */
	m->eax = (DWORD)(m->edi + 0x9cd000u);	/* 4605d4: lea eax, [edi + 0x9cd000] */
	{ DWORD v_ = 0x2cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4605da: push 0x2c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4605dc: push eax */
	M8((DWORD)(m->esp + 0x34u)) = (BYTE)(0x2u);	/* 4605dd: mov byte ptr [esp + 0x34], 2 */
	m->esp -= 4; M32(m->esp) = 0x4605e7u; native_call(m, 0x401290u);	/* 4605e2: call 0x401290 */
	m->ecx = (DWORD)(m->edi + 0x9ccffcu);	/* 4605e7: lea ecx, [edi + 0x9ccffc] */
	M32((DWORD)(m->ecx + 0x0u)) = 0x4aa248u;	/* 4605ed: mov dword ptr [ecx], 0x4aa248 */
	m->esp -= 4; M32(m->esp) = 0x4605f8u; native_call(m, 0x483d60u);	/* 4605f3: call 0x483d60 */
	{ DWORD v_ = 0x45fff0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4605f8: push 0x45fff0 */
	{ DWORD v_ = 0x400u; m->esp -= 4; M32(m->esp) = v_; }	/* 4605fd: push 0x400 */
	m->ecx = (DWORD)(m->edi + 0x9d8014u);	/* 460602: lea ecx, [edi + 0x9d8014] */
	{ DWORD v_ = 0x2cu; m->esp -= 4; M32(m->esp) = v_; }	/* 460608: push 0x2c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46060a: push ecx */
	M8((DWORD)(m->esp + 0x34u)) = (BYTE)(0x3u);	/* 46060b: mov byte ptr [esp + 0x34], 3 */
	m->esp -= 4; M32(m->esp) = 0x460615u; native_call(m, 0x401290u);	/* 460610: call 0x401290 */
	m->ecx = (DWORD)(m->edi + 0x9d8010u);	/* 460615: lea ecx, [edi + 0x9d8010] */
	M32((DWORD)(m->ecx + 0x0u)) = 0x4aa248u;	/* 46061b: mov dword ptr [ecx], 0x4aa248 */
	m->esp -= 4; M32(m->esp) = 0x460626u; native_call(m, 0x483d60u);	/* 460621: call 0x483d60 */
	m->ecx = (DWORD)(m->edi + 0x9e3020u);	/* 460626: lea ecx, [edi + 0x9e3020] */
	M8((DWORD)(m->esp + 0x24u)) = (BYTE)(0x4u);	/* 46062c: mov byte ptr [esp + 0x24], 4 */
	m->esp -= 4; M32(m->esp) = 0x460636u; native_call(m, 0x462560u);	/* 460631: call 0x462560 */
	{ DWORD v_ = 0x45fff0u; m->esp -= 4; M32(m->esp) = v_; }	/* 460636: push 0x45fff0 */
	{ DWORD v_ = 0x126u; m->esp -= 4; M32(m->esp) = v_; }	/* 46063b: push 0x126 */
	m->edx = (DWORD)(m->edi + 0x9ee080u);	/* 460640: lea edx, [edi + 0x9ee080] */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 460646: push 0xc */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 460648: push edx */
	M8((DWORD)(m->esp + 0x34u)) = (BYTE)(0x5u);	/* 460649: mov byte ptr [esp + 0x34], 5 */
	m->esp -= 4; M32(m->esp) = 0x460653u; native_call(m, 0x401290u);	/* 46064e: call 0x401290 */
	{ DWORD v_ = 0x45fff0u; m->esp -= 4; M32(m->esp) = v_; }	/* 460653: push 0x45fff0 */
	{ DWORD v_ = 0x31u; m->esp -= 4; M32(m->esp) = v_; }	/* 460658: push 0x31 */
	m->eax = (DWORD)(m->edi + 0x9eee54u);	/* 46065a: lea eax, [edi + 0x9eee54] */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 460660: push 0xc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 460662: push eax */
	m->esp -= 4; M32(m->esp) = 0x460668u; native_call(m, 0x401290u);	/* 460663: call 0x401290 */
	{ DWORD v_ = 0x45fff0u; m->esp -= 4; M32(m->esp) = v_; }	/* 460668: push 0x45fff0 */
	{ DWORD v_ = 0x30u; m->esp -= 4; M32(m->esp) = v_; }	/* 46066d: push 0x30 */
	m->ecx = (DWORD)(m->edi + 0x9ef0ccu);	/* 46066f: lea ecx, [edi + 0x9ef0cc] */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 460675: push 0xc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 460677: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46067du; native_call(m, 0x401290u);	/* 460678: call 0x401290 */
	{ DWORD v_ = 0x45fff0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46067d: push 0x45fff0 */
	{ DWORD v_ = 0x79u; m->esp -= 4; M32(m->esp) = v_; }	/* 460682: push 0x79 */
	m->edx = (DWORD)(m->edi + 0x9ef350u);	/* 460684: lea edx, [edi + 0x9ef350] */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 46068a: push 0xc */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46068c: push edx */
	m->esp -= 4; M32(m->esp) = 0x460692u; native_call(m, 0x401290u);	/* 46068d: call 0x401290 */
	{ DWORD v_ = 0x45fff0u; m->esp -= 4; M32(m->esp) = v_; }	/* 460692: push 0x45fff0 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 460697: push 4 */
	m->eax = (DWORD)(m->edi + 0xdc0244u);	/* 460699: lea eax, [edi + 0xdc0244] */
	{ DWORD v_ = 0x20cu; m->esp -= 4; M32(m->esp) = v_; }	/* 46069f: push 0x20c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4606a4: push eax */
	m->esp -= 4; M32(m->esp) = 0x4606aau; native_call(m, 0x401290u);	/* 4606a5: call 0x401290 */
	m->ecx = (DWORD)(m->edi + 0xdc0a78u);	/* 4606aa: lea ecx, [edi + 0xdc0a78] */
	m->esp -= 4; M32(m->esp) = 0x4606b5u; native_call(m, 0x462cf0u);	/* 4606b0: call 0x462cf0 */
	m->ecx = (DWORD)(m->edi + 0xdc0cc4u);	/* 4606b5: lea ecx, [edi + 0xdc0cc4] */
	M8((DWORD)(m->esp + 0x24u)) = (BYTE)(0x6u);	/* 4606bb: mov byte ptr [esp + 0x24], 6 */
	m->esp -= 4; M32(m->esp) = 0x4606c5u; native_call(m, 0x462cf0u);	/* 4606c0: call 0x462cf0 */
	{ DWORD v_ = 0x45fff0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4606c5: push 0x45fff0 */
	{ DWORD v_ = 0x3e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4606ca: push 0x3e8 */
	m->ecx = (DWORD)(m->edi + 0xe36214u);	/* 4606cf: lea ecx, [edi + 0xe36214] */
	{ DWORD v_ = 0x14u; m->esp -= 4; M32(m->esp) = v_; }	/* 4606d5: push 0x14 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4606d7: push ecx */
	M8((DWORD)(m->esp + 0x34u)) = (BYTE)(0x7u);	/* 4606d8: mov byte ptr [esp + 0x34], 7 */
	m->esp -= 4; M32(m->esp) = 0x4606e2u; native_call(m, 0x401290u);	/* 4606dd: call 0x401290 */
	m->ecx = (DWORD)(m->edi + 0xe3c93cu);	/* 4606e2: lea ecx, [edi + 0xe3c93c] */
	M32((DWORD)(m->ecx + 0x0u)) = 0x4aa244u;	/* 4606e8: mov dword ptr [ecx], 0x4aa244 */
	m->esp -= 4; M32(m->esp) = 0x4606f3u; native_call(m, 0x466a20u);	/* 4606ee: call 0x466a20 */
	{ DWORD v_ = 0x45fff0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4606f3: push 0x45fff0 */
	{ DWORD v_ = 0xf4240u; m->esp -= 4; M32(m->esp) = v_; }	/* 4606f8: push 0xf4240 */
	m->edx = (DWORD)(m->edi + 0xf30dc8u);	/* 4606fd: lea edx, [edi + 0xf30dc8] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 460703: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 460705: push edx */
	M8((DWORD)(m->esp + 0x34u)) = (BYTE)(0x8u);	/* 460706: mov byte ptr [esp + 0x34], 8 */
	m->esp -= 4; M32(m->esp) = 0x460710u; native_call(m, 0x401290u);	/* 46070b: call 0x401290 */
	m->ecx = (DWORD)(m->edi + 0x13016d0u);	/* 460710: lea ecx, [edi + 0x13016d0] */
	M32((DWORD)(m->ecx + 0x0u)) = 0x4aa240u;	/* 460716: mov dword ptr [ecx], 0x4aa240 */
	m->esp -= 4; M32(m->esp) = 0x460721u; native_call(m, 0x46ae70u);	/* 46071c: call 0x46ae70 */
	{ DWORD v_ = 0x45fff0u; m->esp -= 4; M32(m->esp) = v_; }	/* 460721: push 0x45fff0 */
	{ DWORD v_ = 0x3e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 460726: push 0x3e8 */
	m->eax = (DWORD)(m->edi + 0x131ae44u);	/* 46072b: lea eax, [edi + 0x131ae44] */
	{ DWORD v_ = 0x2ccu; m->esp -= 4; M32(m->esp) = v_; }	/* 460731: push 0x2cc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 460736: push eax */
	M8((DWORD)(m->esp + 0x34u)) = (BYTE)(0x9u);	/* 460737: mov byte ptr [esp + 0x34], 9 */
	m->esp -= 4; M32(m->esp) = 0x460741u; native_call(m, 0x401290u);	/* 46073c: call 0x401290 */
	{ DWORD v_ = 0x45fff0u; m->esp -= 4; M32(m->esp) = v_; }	/* 460741: push 0x45fff0 */
	{ DWORD v_ = 0x32u; m->esp -= 4; M32(m->esp) = v_; }	/* 460746: push 0x32 */
	m->ecx = (DWORD)(m->edi + 0x14d1ab4u);	/* 460748: lea ecx, [edi + 0x14d1ab4] */
	{ DWORD v_ = 0x2e18u; m->esp -= 4; M32(m->esp) = v_; }	/* 46074e: push 0x2e18 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 460753: push ecx */
	m->esp -= 4; M32(m->esp) = 0x460759u; native_call(m, 0x401290u);	/* 460754: call 0x401290 */
	{ DWORD v_ = 0x463960u; m->esp -= 4; M32(m->esp) = v_; }	/* 460759: push 0x463960 */
	{ DWORD v_ = 0x463850u; m->esp -= 4; M32(m->esp) = v_; }	/* 46075e: push 0x463850 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 460763: push 0x10 */
	m->edx = (DWORD)(m->edi + 0x1561b68u);	/* 460765: lea edx, [edi + 0x1561b68] */
	{ DWORD v_ = 0x47fd2u; m->esp -= 4; M32(m->esp) = v_; }	/* 46076b: push 0x47fd2 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 460770: push edx */
	m->esp -= 4; M32(m->esp) = 0x460776u; native_call(m, 0x49fd2du);	/* 460771: call 0x49fd2d */
	m->ecx = (DWORD)(m->edi + 0x19e188cu);	/* 460776: lea ecx, [edi + 0x19e188c] */
	M8((DWORD)(m->esp + 0x24u)) = (BYTE)(0xau);	/* 46077c: mov byte ptr [esp + 0x24], 0xa */
	M32((DWORD)(m->ecx + 0x0u)) = 0x4aa244u;	/* 460781: mov dword ptr [ecx], 0x4aa244 */
	m->esp -= 4; M32(m->esp) = 0x46078cu; native_call(m, 0x466a20u);	/* 460787: call 0x466a20 */
	m->ecx = (DWORD)(m->edi + 0x1cbe198u);	/* 46078c: lea ecx, [edi + 0x1cbe198] */
	M8((DWORD)(m->esp + 0x24u)) = (BYTE)(0xbu);	/* 460792: mov byte ptr [esp + 0x24], 0xb */
	M32((DWORD)(m->ecx + 0x0u)) = 0x4aa240u;	/* 460797: mov dword ptr [ecx], 0x4aa240 */
	m->esp -= 4; M32(m->esp) = 0x4607a2u; native_call(m, 0x46ae70u);	/* 46079d: call 0x46ae70 */
	{ DWORD v_ = 0x45fff0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4607a2: push 0x45fff0 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 4607a7: push 0x64 */
	m->eax = (DWORD)(m->edi + 0x1cd6fb4u);	/* 4607a9: lea eax, [edi + 0x1cd6fb4] */
	{ DWORD v_ = 0x5cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4607af: push 0x5c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4607b1: push eax */
	M8((DWORD)(m->esp + 0x34u)) = (BYTE)(0xcu);	/* 4607b2: mov byte ptr [esp + 0x34], 0xc */
	m->esp -= 4; M32(m->esp) = 0x4607bcu; native_call(m, 0x401290u);	/* 4607b7: call 0x401290 */
	{ DWORD v_ = 0x45ff30u; m->esp -= 4; M32(m->esp) = v_; }	/* 4607bc: push 0x45ff30 */
	{ DWORD v_ = 0x463a40u; m->esp -= 4; M32(m->esp) = v_; }	/* 4607c1: push 0x463a40 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 4607c6: push 0x64 */
	m->ecx = (DWORD)(m->edi + 0x1cd93a8u);	/* 4607c8: lea ecx, [edi + 0x1cd93a8] */
	{ DWORD v_ = 0x8888u; m->esp -= 4; M32(m->esp) = v_; }	/* 4607ce: push 0x8888 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4607d3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4607d9u; native_call(m, 0x49fd2du);	/* 4607d4: call 0x49fd2d */
	{ DWORD v_ = 0x45fff0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4607d9: push 0x45fff0 */
	{ DWORD v_ = 0x190u; m->esp -= 4; M32(m->esp) = v_; }	/* 4607de: push 0x190 */
	m->edx = (DWORD)(m->edi + 0x202ef34u);	/* 4607e3: lea edx, [edi + 0x202ef34] */
	{ DWORD v_ = 0x4e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4607e9: push 0x4e8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4607ee: push edx */
	M8((DWORD)(m->esp + 0x34u)) = (BYTE)(0xdu);	/* 4607ef: mov byte ptr [esp + 0x34], 0xd */
	m->esp -= 4; M32(m->esp) = 0x4607f9u; native_call(m, 0x401290u);	/* 4607f4: call 0x401290 */
	{ DWORD v_ = 0x45fff0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4607f9: push 0x45fff0 */
	{ DWORD v_ = 0x3e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4607fe: push 0x3e8 */
	m->eax = (DWORD)(m->edi + 0x20a99c0u);	/* 460803: lea eax, [edi + 0x20a99c0] */
	{ DWORD v_ = 0x12cu; m->esp -= 4; M32(m->esp) = v_; }	/* 460809: push 0x12c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46080e: push eax */
	m->esp -= 4; M32(m->esp) = 0x460814u; native_call(m, 0x401290u);	/* 46080f: call 0x401290 */
	{ DWORD v_ = 0x45fff0u; m->esp -= 4; M32(m->esp) = v_; }	/* 460814: push 0x45fff0 */
	{ DWORD v_ = 0xc8u; m->esp -= 4; M32(m->esp) = v_; }	/* 460819: push 0xc8 */
	m->ecx = (DWORD)(m->edi + 0x20f300cu);	/* 46081e: lea ecx, [edi + 0x20f300c] */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 460824: push 0xc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 460826: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46082cu; native_call(m, 0x401290u);	/* 460827: call 0x401290 */
	{ DWORD v_ = 0x45fff0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46082c: push 0x45fff0 */
	{ DWORD v_ = 0x20u; m->esp -= 4; M32(m->esp) = v_; }	/* 460831: push 0x20 */
	m->edx = (DWORD)(m->edi + 0x20fab74u);	/* 460833: lea edx, [edi + 0x20fab74] */
	{ DWORD v_ = 0x14u; m->esp -= 4; M32(m->esp) = v_; }	/* 460839: push 0x14 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46083b: push edx */
	m->esp -= 4; M32(m->esp) = 0x460841u; native_call(m, 0x401290u);	/* 46083c: call 0x401290 */
	{ DWORD v_ = 0x45fff0u; m->esp -= 4; M32(m->esp) = v_; }	/* 460841: push 0x45fff0 */
	{ DWORD v_ = 0xc8u; m->esp -= 4; M32(m->esp) = v_; }	/* 460846: push 0xc8 */
	m->eax = (DWORD)(m->edi + 0x20fadf8u);	/* 46084b: lea eax, [edi + 0x20fadf8] */
	{ DWORD v_ = 0x28u; m->esp -= 4; M32(m->esp) = v_; }	/* 460851: push 0x28 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 460853: push eax */
	m->esp -= 4; M32(m->esp) = 0x460859u; native_call(m, 0x401290u);	/* 460854: call 0x401290 */
	{ DWORD v_ = 0x45fff0u; m->esp -= 4; M32(m->esp) = v_; }	/* 460859: push 0x45fff0 */
	{ DWORD v_ = 0x2000u; m->esp -= 4; M32(m->esp) = v_; }	/* 46085e: push 0x2000 */
	m->ecx = (DWORD)(m->edi + 0x20fcfe4u);	/* 460863: lea ecx, [edi + 0x20fcfe4] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 460869: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46086b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x460871u; native_call(m, 0x401290u);	/* 46086c: call 0x401290 */
	m->ecx = (DWORD)(m->edi + 0x2148ed8u);	/* 460871: lea ecx, [edi + 0x2148ed8] */
	m->esp -= 4; M32(m->esp) = 0x46087cu; native_call(m, 0x4637f0u);	/* 460877: call 0x4637f0 */
	M32((DWORD)(m->edi + 0x0u)) = 0x4aa23cu;	/* 46087c: mov dword ptr [edi], 0x4aa23c */
	M32((DWORD)(m->edi + 0x4u)) = m->ebx;	/* 460882: mov dword ptr [edi + 4], ebx */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 460885: or eax, 0xffffffff */
	M32((DWORD)(m->esi + 0x0u)) = 0x4aa238u;	/* 460888: mov dword ptr [esi], 0x4aa238 */
	M32((DWORD)(m->esi + 0x4u)) = m->eax;	/* 46088e: mov dword ptr [esi + 4], eax */
	m->ecx = (DWORD)(m->esi + 0xcu);	/* 460891: lea ecx, [esi + 0xc] */
	M8((DWORD)(m->esp + 0x24u)) = (BYTE)(0xeu);	/* 460894: mov byte ptr [esp + 0x24], 0xe */
	M32((DWORD)(m->esi + 0x8u)) = m->eax;	/* 460899: mov dword ptr [esi + 8], eax */
	m->esp -= 4; M32(m->esp) = 0x4608a1u; native_call(m, 0x487480u);	/* 46089c: call 0x487480 */
	m->edx = (DWORD)(m->esi + 0x91e4u);	/* 4608a1: lea edx, [esi + 0x91e4] */
	{ DWORD v_ = 0x1e8480u; m->esp -= 4; M32(m->esp) = v_; }	/* 4608a7: push 0x1e8480 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4608ac: push edx */
	{ DWORD v_ = 0x2710u; m->esp -= 4; M32(m->esp) = v_; }	/* 4608ad: push 0x2710 */
	m->edi = (DWORD)(m->esi + 0x48u);	/* 4608b2: lea edi, [esi + 0x48] */
	m->ecx = 0xau;	/* 4608b5: mov ecx, 0xa */
	m->eax = 0x3d088889u;	/* 4608ba: mov eax, 0x3d088889 */
	{ DWORD v_ = 0x190u; m->esp -= 4; M32(m->esp) = v_; }	/* 4608bf: push 0x190 */
	{ DWORD v_ = 0xfa0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4608c4: push 0xfa0 */
	{ DWORD v_ = 0x4e20u; m->esp -= 4; M32(m->esp) = v_; }	/* 4608c9: push 0x4e20 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4608ce: rep stosd dword ptr es:[edi], eax */
	{ DWORD v_ = 0x3e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4608d0: push 0x3e8 */
	{ DWORD v_ = 0x2710u; m->esp -= 4; M32(m->esp) = v_; }	/* 4608d5: push 0x2710 */
	m->ecx = (DWORD)(m->esi + 0x74u);	/* 4608da: lea ecx, [esi + 0x74] */
	M32((DWORD)(m->esi + 0x70u)) = m->ebx;	/* 4608dd: mov dword ptr [esi + 0x70], ebx */
	m->esp -= 4; M32(m->esp) = 0x4608e5u; native_call(m, 0x484050u);	/* 4608e0: call 0x484050 */
	{ DWORD v_ = 0x4c45e4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4608e5: push 0x4c45e4 */
	{ DWORD v_ = 0x4c45dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 4608ea: push 0x4c45dc */
	{ DWORD v_ = 0x4c45d4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4608ef: push 0x4c45d4 */
	{ DWORD v_ = 0x4c45ccu; m->esp -= 4; M32(m->esp) = v_; }	/* 4608f4: push 0x4c45cc */
	{ DWORD v_ = 0x4c45c0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4608f9: push 0x4c45c0 */
	{ DWORD v_ = 0x4c45b8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4608fe: push 0x4c45b8 */
	{ DWORD v_ = 0x4c45b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 460903: push 0x4c45b0 */
	{ DWORD v_ = 0x4b1784u; m->esp -= 4; M32(m->esp) = v_; }	/* 460908: push 0x4b1784 */
	{ DWORD v_ = 0x4c45a8u; m->esp -= 4; M32(m->esp) = v_; }	/* 46090d: push 0x4c45a8 */
	m->ecx = m->ebp;	/* 460912: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x460919u; native_call(m, 0x4700a0u);	/* 460914: call 0x4700a0 */
	{ DWORD v_ = 0x4b4418u; m->esp -= 4; M32(m->esp) = v_; }	/* 460919: push 0x4b4418 */
	m->ecx = m->ebp;	/* 46091e: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x460925u; native_call(m, 0x460925u + M32(0x460921u));	/* 0x473780 unless the patch DLL retargets it */	/* 460920: call 0x473780 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 460925: test eax, eax */
	if (!m->zf) goto L_46093b;	/* 460927: jne 0x46093b */
	{ DWORD v_ = 0x4c4598u; m->esp -= 4; M32(m->esp) = v_; }	/* 460929: push 0x4c4598 */
	{ DWORD v_ = 0xa0e778u; m->esp -= 4; M32(m->esp) = v_; }	/* 46092e: push 0xa0e778 */
	m->esp -= 4; M32(m->esp) = 0x460938u; native_call(m, 0x46c710u);	/* 460933: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 460938: add esp, 8 */
L_46093b:
	{ DWORD v_ = 0x4c4588u; m->esp -= 4; M32(m->esp) = v_; }	/* 46093b: push 0x4c4588 */
	m->ecx = m->ebp;	/* 460940: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x460947u; native_call(m, 0x4875d0u);	/* 460942: call 0x4875d0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 460947: test eax, eax */
	if (!m->zf) goto L_46095d;	/* 460949: jne 0x46095d */
	{ DWORD v_ = 0x4c4598u; m->esp -= 4; M32(m->esp) = v_; }	/* 46094b: push 0x4c4598 */
	{ DWORD v_ = 0xa0e778u; m->esp -= 4; M32(m->esp) = v_; }	/* 460950: push 0xa0e778 */
	m->esp -= 4; M32(m->esp) = 0x46095au; native_call(m, 0x46c710u);	/* 460955: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46095a: add esp, 8 */
L_46095d:
	M32((DWORD)(m->esi + 0x233ca30u)) = m->ebx;	/* 46095d: mov dword ptr [esi + 0x233ca30], ebx */
	m->eax = 0x44e10000u;	/* 460963: mov eax, 0x44e10000 */
	M32((DWORD)(m->esi + 0x233ca58u)) = m->ebx;	/* 460968: mov dword ptr [esi + 0x233ca58], ebx */
	m->edi = 0x1u;	/* 46096e: mov edi, 1 */
	M32((DWORD)(m->esi + 0x233ca80u)) = m->eax;	/* 460973: mov dword ptr [esi + 0x233ca80], eax */
	M32((DWORD)(m->esi + 0x233caa8u)) = m->edi;	/* 460979: mov dword ptr [esi + 0x233caa8], edi */
	M32((DWORD)(m->esi + 0x233cad0u)) = m->ebx;	/* 46097f: mov dword ptr [esi + 0x233cad0], ebx */
	M32((DWORD)(m->esi + 0x233caf8u)) = m->ebx;	/* 460985: mov dword ptr [esi + 0x233caf8], ebx */
	M32((DWORD)(m->esi + 0x233ca34u)) = m->ebx;	/* 46098b: mov dword ptr [esi + 0x233ca34], ebx */
	M32((DWORD)(m->esi + 0x233ca5cu)) = m->ebx;	/* 460991: mov dword ptr [esi + 0x233ca5c], ebx */
	M32((DWORD)(m->esi + 0x233ca84u)) = 0x41200000u;	/* 460997: mov dword ptr [esi + 0x233ca84], 0x41200000 */
	M32((DWORD)(m->esi + 0x233caacu)) = m->ebx;	/* 4609a1: mov dword ptr [esi + 0x233caac], ebx */
	M32((DWORD)(m->esi + 0x233cad4u)) = m->ebx;	/* 4609a7: mov dword ptr [esi + 0x233cad4], ebx */
	M32((DWORD)(m->esi + 0x233cafcu)) = m->ebx;	/* 4609ad: mov dword ptr [esi + 0x233cafc], ebx */
	M32((DWORD)(m->esi + 0x233ca38u)) = m->ebx;	/* 4609b3: mov dword ptr [esi + 0x233ca38], ebx */
	m->edx = 0x43960000u;	/* 4609b9: mov edx, 0x43960000 */
	M32((DWORD)(m->esi + 0x233ca60u)) = m->ebx;	/* 4609be: mov dword ptr [esi + 0x233ca60], ebx */
	M32((DWORD)(m->esi + 0x233ca88u)) = m->edx;	/* 4609c4: mov dword ptr [esi + 0x233ca88], edx */
	M32((DWORD)(m->esi + 0x233cab0u)) = m->ebx;	/* 4609ca: mov dword ptr [esi + 0x233cab0], ebx */
	M32((DWORD)(m->esi + 0x233cad8u)) = m->ebx;	/* 4609d0: mov dword ptr [esi + 0x233cad8], ebx */
	M32((DWORD)(m->esi + 0x233cb00u)) = m->ebx;	/* 4609d6: mov dword ptr [esi + 0x233cb00], ebx */
	M32((DWORD)(m->esi + 0x233ca3cu)) = m->ebx;	/* 4609dc: mov dword ptr [esi + 0x233ca3c], ebx */
	m->ecx = 0x453b8000u;	/* 4609e2: mov ecx, 0x453b8000 */
	M32((DWORD)(m->esi + 0x233ca64u)) = m->ebx;	/* 4609e7: mov dword ptr [esi + 0x233ca64], ebx */
	M32((DWORD)(m->esi + 0x233ca8cu)) = m->ecx;	/* 4609ed: mov dword ptr [esi + 0x233ca8c], ecx */
	M32((DWORD)(m->esi + 0x233cab4u)) = m->ebx;	/* 4609f3: mov dword ptr [esi + 0x233cab4], ebx */
	M32((DWORD)(m->esi + 0x233cadcu)) = m->ebx;	/* 4609f9: mov dword ptr [esi + 0x233cadc], ebx */
	M32((DWORD)(m->esi + 0x233cb04u)) = m->ebx;	/* 4609ff: mov dword ptr [esi + 0x233cb04], ebx */
	M32((DWORD)(m->esi + 0x233ca40u)) = m->ebx;	/* 460a05: mov dword ptr [esi + 0x233ca40], ebx */
	M32((DWORD)(m->esi + 0x233ca68u)) = 0x44610000u;	/* 460a0b: mov dword ptr [esi + 0x233ca68], 0x44610000 */
	M32((DWORD)(m->esi + 0x233ca90u)) = m->eax;	/* 460a15: mov dword ptr [esi + 0x233ca90], eax */
	M32((DWORD)(m->esi + 0x233cab8u)) = m->ebx;	/* 460a1b: mov dword ptr [esi + 0x233cab8], ebx */
	M32((DWORD)(m->esi + 0x233cae0u)) = m->edi;	/* 460a21: mov dword ptr [esi + 0x233cae0], edi */
	M32((DWORD)(m->esi + 0x233cb08u)) = m->ebx;	/* 460a27: mov dword ptr [esi + 0x233cb08], ebx */
	M32((DWORD)(m->esi + 0x233ca44u)) = m->ebx;	/* 460a2d: mov dword ptr [esi + 0x233ca44], ebx */
	M32((DWORD)(m->esi + 0x233ca6cu)) = 0xc4610000u;	/* 460a33: mov dword ptr [esi + 0x233ca6c], 0xc4610000 */
	M32((DWORD)(m->esi + 0x233ca94u)) = m->eax;	/* 460a3d: mov dword ptr [esi + 0x233ca94], eax */
	M32((DWORD)(m->esi + 0x233cabcu)) = m->ebx;	/* 460a43: mov dword ptr [esi + 0x233cabc], ebx */
	M32((DWORD)(m->esi + 0x233cae4u)) = m->edi;	/* 460a49: mov dword ptr [esi + 0x233cae4], edi */
	M32((DWORD)(m->esi + 0x233cb0cu)) = m->ebx;	/* 460a4f: mov dword ptr [esi + 0x233cb0c], ebx */
	M32((DWORD)(m->esi + 0x233ca48u)) = 0x42480000u;	/* 460a55: mov dword ptr [esi + 0x233ca48], 0x42480000 */
	M32((DWORD)(m->esi + 0x233ca70u)) = m->edx;	/* 460a5f: mov dword ptr [esi + 0x233ca70], edx */
	M32((DWORD)(m->esi + 0x233ca9cu)) = m->ecx;	/* 460a65: mov dword ptr [esi + 0x233ca9c], ecx */
	M32((DWORD)(m->esi + 0x233ca98u)) = m->eax;	/* 460a6b: mov dword ptr [esi + 0x233ca98], eax */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 460a71: push -1 */
	m->ecx = m->ebp;	/* 460a73: mov ecx, ebp */
	M32((DWORD)(m->esi + 0x233cac0u)) = m->ebx;	/* 460a75: mov dword ptr [esi + 0x233cac0], ebx */
	M32((DWORD)(m->esi + 0x233cae8u)) = m->ebx;	/* 460a7b: mov dword ptr [esi + 0x233cae8], ebx */
	M32((DWORD)(m->esi + 0x233cb10u)) = m->ebx;	/* 460a81: mov dword ptr [esi + 0x233cb10], ebx */
	M32((DWORD)(m->esi + 0x233ca4cu)) = m->ebx;	/* 460a87: mov dword ptr [esi + 0x233ca4c], ebx */
	M32((DWORD)(m->esi + 0x233ca74u)) = 0xc2c80000u;	/* 460a8d: mov dword ptr [esi + 0x233ca74], 0xc2c80000 */
	M32((DWORD)(m->esi + 0x233cac4u)) = m->ebx;	/* 460a97: mov dword ptr [esi + 0x233cac4], ebx */
	M32((DWORD)(m->esi + 0x233caecu)) = m->ebx;	/* 460a9d: mov dword ptr [esi + 0x233caec], ebx */
	M32((DWORD)(m->esi + 0x233cb14u)) = m->ebx;	/* 460aa3: mov dword ptr [esi + 0x233cb14], ebx */
	M32((DWORD)(m->esi + 0x233ca50u)) = m->ebx;	/* 460aa9: mov dword ptr [esi + 0x233ca50], ebx */
	M32((DWORD)(m->esi + 0x233ca78u)) = m->eax;	/* 460aaf: mov dword ptr [esi + 0x233ca78], eax */
	M32((DWORD)(m->esi + 0x233caa0u)) = m->eax;	/* 460ab5: mov dword ptr [esi + 0x233caa0], eax */
	M32((DWORD)(m->esi + 0x233cac8u)) = m->ebx;	/* 460abb: mov dword ptr [esi + 0x233cac8], ebx */
	M32((DWORD)(m->esi + 0x233caf0u)) = m->edi;	/* 460ac1: mov dword ptr [esi + 0x233caf0], edi */
	M32((DWORD)(m->esi + 0x233cb18u)) = m->ebx;	/* 460ac7: mov dword ptr [esi + 0x233cb18], ebx */
	M32((DWORD)(m->esi + 0x233ca54u)) = m->ebx;	/* 460acd: mov dword ptr [esi + 0x233ca54], ebx */
	M32((DWORD)(m->esi + 0x233ca7cu)) = m->ebx;	/* 460ad3: mov dword ptr [esi + 0x233ca7c], ebx */
	M32((DWORD)(m->esi + 0x233caa4u)) = m->eax;	/* 460ad9: mov dword ptr [esi + 0x233caa4], eax */
	M32((DWORD)(m->esi + 0x233caccu)) = m->ebx;	/* 460adf: mov dword ptr [esi + 0x233cacc], ebx */
	M32((DWORD)(m->esi + 0x233caf4u)) = m->edi;	/* 460ae5: mov dword ptr [esi + 0x233caf4], edi */
	M32((DWORD)(m->esi + 0x233cb1cu)) = m->edi;	/* 460aeb: mov dword ptr [esi + 0x233cb1c], edi */
	M32((DWORD)(m->esi + 0x233cc10u)) = m->edi;	/* 460af1: mov dword ptr [esi + 0x233cc10], edi */
	m->esp -= 4; M32(m->esp) = 0x460afcu; native_call(m, 0x45dfb0u);	/* 460af7: call 0x45dfb0 */
	m->eax = 0x6u;	/* 460afc: mov eax, 6 */
	m->ebp = (DWORD)(m->esi + 0x234334bu);	/* 460b01: lea ebp, [esi + 0x234334b] */
	M32((DWORD)(m->esi + 0x23423e5u)) = m->eax;	/* 460b07: mov dword ptr [esi + 0x23423e5], eax */
	M32((DWORD)(m->esi + 0x23423edu)) = m->eax;	/* 460b0d: mov dword ptr [esi + 0x23423ed], eax */
	M32((DWORD)(m->esi + 0x2340c64u)) = 0xffffffffu;	/* 460b13: mov dword ptr [esi + 0x2340c64], 0xffffffff */
	M32((DWORD)(m->esi + 0x2340c68u)) = m->ebx;	/* 460b1d: mov dword ptr [esi + 0x2340c68], ebx */
	M32((DWORD)(m->esi + 0x2340c6cu)) = m->ebx;	/* 460b23: mov dword ptr [esi + 0x2340c6c], ebx */
	M32((DWORD)(m->esi + 0x2340c70u)) = m->ebx;	/* 460b29: mov dword ptr [esi + 0x2340c70], ebx */
	M32((DWORD)(m->esi + 0x23423e9u)) = 0x3u;	/* 460b2f: mov dword ptr [esi + 0x23423e9], 3 */
	M32((DWORD)(m->esi + 0x23423f1u)) = 0x7u;	/* 460b39: mov dword ptr [esi + 0x23423f1], 7 */
	M32((DWORD)(m->esi + 0x23423f5u)) = 0xau;	/* 460b43: mov dword ptr [esi + 0x23423f5], 0xa */
	M32((DWORD)(m->esi + 0x23423f9u)) = 0x18u;	/* 460b4d: mov dword ptr [esi + 0x23423f9], 0x18 */
	m->eax = m->ebp;	/* 460b57: mov eax, ebp */
	m->ecx = 0x1eu;	/* 460b59: mov ecx, 0x1e */
L_460b5e:
	M8((DWORD)(m->eax + 0x0u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 460b5e: mov byte ptr [eax], bl */
	{ DWORD a_ = m->eax, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 460b60: add eax, 0x40 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 460b63: dec ecx */
	if (!m->zf) goto L_460b5e;	/* 460b64: jne 0x460b5e */
	{ DWORD v_ = 0x4ad5e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 460b66: push 0x4ad5e0 */
	{ DWORD v_ = 0x4c457cu; m->esp -= 4; M32(m->esp) = v_; }	/* 460b6b: push 0x4c457c */
	m->esp -= 4; M32(m->esp) = 0x460b75u; native_call(m, 0x49e9cau);	/* 460b70: call 0x49e9ca */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 460b75: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 460b78: cmp eax, ebx */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 460b7a: mov dword ptr [esp + 0x14], eax */
	if (m->zf) goto L_460bd0;	/* 460b7e: je 0x460bd0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 460b80: push eax */
	{ DWORD v_ = 0x3fu; m->esp -= 4; M32(m->esp) = v_; }	/* 460b81: push 0x3f */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 460b83: push ebp */
	M32((DWORD)(m->esp + 0x1cu)) = m->edi;	/* 460b84: mov dword ptr [esp + 0x1c], edi */
	m->esp -= 4; M32(m->esp) = 0x460b8du; native_call(m, 0x49ecd7u);	/* 460b88: call 0x49ecd7 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 460b8d: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 460b90: test eax, eax */
	if (m->zf) goto L_460bc3;	/* 460b92: je 0x460bc3 */
	m->edi = (DWORD)(m->esi + 0x234338bu);	/* 460b94: lea edi, [esi + 0x234338b] */
L_460b9a:
	{ DWORD a_ = M32((DWORD)(m->esp + 0x10u)), b_ = 0x1eu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 460b9a: cmp dword ptr [esp + 0x10], 0x1e */
	if (m->sf == m->of) goto L_460bc3;	/* 460b9f: jge 0x460bc3 */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 460ba1: mov ecx, dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 460ba5: mov edx, dword ptr [esp + 0x10] */
	m->eax = m->edi;	/* 460ba9: mov eax, edi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 460bab: push ecx */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 460bac: inc edx */
	{ DWORD v_ = 0x3fu; m->esp -= 4; M32(m->esp) = v_; }	/* 460bad: push 0x3f */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 460baf: push eax */
	M32((DWORD)(m->esp + 0x1cu)) = m->edx;	/* 460bb0: mov dword ptr [esp + 0x1c], edx */
	{ DWORD a_ = m->edi, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 460bb4: add edi, 0x40 */
	m->esp -= 4; M32(m->esp) = 0x460bbcu; native_call(m, 0x49ecd7u);	/* 460bb7: call 0x49ecd7 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 460bbc: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 460bbf: test eax, eax */
	if (!m->zf) goto L_460b9a;	/* 460bc1: jne 0x460b9a */
L_460bc3:
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 460bc3: mov edx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 460bc7: push edx */
	m->esp -= 4; M32(m->esp) = 0x460bcdu; native_call(m, 0x49e7e0u);	/* 460bc8: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 460bcd: add esp, 4 */
L_460bd0:
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 460bd0: xor edx, edx */
L_460bd2:
	m->edi = m->ebp;	/* 460bd2: mov edi, ebp */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 460bd4: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 460bd7: xor eax, eax */
	{ DWORD a_ = m->ebp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 460bd9: add ebp, 0x40 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 460bdc: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 460bde: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 460be0: dec ecx */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 460be1: add ecx, edx */
	{ DWORD a_ = m->edx, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 460be3: add edx, 0x40 */
	{ DWORD a_ = m->edx, b_ = 0x780u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 460be6: cmp edx, 0x780 */
	M8((DWORD)(m->ecx + m->esi*1 + 0x234334au)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 460bec: mov byte ptr [ecx + esi + 0x234334a], bl */
	if (m->sf != m->of) goto L_460bd2;	/* 460bf3: jl 0x460bd2 */
	m->ecx = m->esi;	/* 460bf5: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x460bfcu; native_call(m, 0x4617f0u);	/* 460bf7: call 0x4617f0 */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 460bfc: mov ecx, dword ptr [esp + 0x1c] */
	m->eax = m->esi;	/* 460c00: mov eax, esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 460c02: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 460c03: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 460c04: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 460c05: pop ebx */
	M32((DWORD)&g_lift_fs0) = m->ecx;	/* 460c06: mov dword ptr fs:[0], ecx */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 460c0d: add esp, 0x18 */
	m->esp += 4 + 0; return;	/* 460c10: ret  */
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
