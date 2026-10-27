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

static void lift_430ca0(X86 *m);

/* menu_loadIntroTextures (0x430ca0), lifted by tools/lift.py */
static void lift_430ca0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x7c0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 430ca0: sub esp, 0x7c0 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430ca6: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 430ca9: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x5c0u);	/* 430cab: lea edx, [esp + 0x5c0] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 430cb2: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 430cb3: push edi */
	m->edi = 0x4b25dcu;	/* 430cb4: mov edi, 0x4b25dc */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 430cb9: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 430cbb: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 430cbd: sub edi, ecx */
	m->eax = m->ecx;	/* 430cbf: mov eax, ecx */
	m->esi = m->edi;	/* 430cc1: mov esi, edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 430cc3: shr ecx, 2 */
	m->edi = m->edx;	/* 430cc6: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x608u);	/* 430cc8: lea edx, [esp + 0x608] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 430ccf: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 430cd1: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 430cd3: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430cd5: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 430cd8: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430cda: or ecx, 0xffffffff */
	m->edi = 0x4b25ccu;	/* 430cdd: mov edi, 0x4b25cc */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 430ce2: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 430ce4: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 430ce6: sub edi, ecx */
	m->eax = m->ecx;	/* 430ce8: mov eax, ecx */
	m->esi = m->edi;	/* 430cea: mov esi, edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 430cec: shr ecx, 2 */
	m->edi = m->edx;	/* 430cef: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x648u);	/* 430cf1: lea edx, [esp + 0x648] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 430cf8: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 430cfa: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 430cfc: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430cfe: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 430d01: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b25bcu;	/* 430d03: mov edi, 0x4b25bc */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430d08: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 430d0b: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 430d0d: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 430d0f: sub edi, ecx */
	m->eax = m->ecx;	/* 430d11: mov eax, ecx */
	m->esi = m->edi;	/* 430d13: mov esi, edi */
	m->edi = m->edx;	/* 430d15: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x688u);	/* 430d17: lea edx, [esp + 0x688] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 430d1e: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 430d21: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 430d23: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 430d25: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430d27: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 430d2a: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b25acu;	/* 430d2c: mov edi, 0x4b25ac */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430d31: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 430d34: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 430d36: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 430d38: sub edi, ecx */
	m->eax = m->ecx;	/* 430d3a: mov eax, ecx */
	m->esi = m->edi;	/* 430d3c: mov esi, edi */
	m->edi = m->edx;	/* 430d3e: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x6c8u);	/* 430d40: lea edx, [esp + 0x6c8] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 430d47: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 430d4a: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 430d4c: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 430d4e: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430d50: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 430d53: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b259cu;	/* 430d55: mov edi, 0x4b259c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430d5a: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 430d5d: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 430d5f: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 430d61: sub edi, ecx */
	m->eax = m->ecx;	/* 430d63: mov eax, ecx */
	m->esi = m->edi;	/* 430d65: mov esi, edi */
	m->edi = m->edx;	/* 430d67: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x708u);	/* 430d69: lea edx, [esp + 0x708] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 430d70: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 430d73: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 430d75: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430d77: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 430d7a: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b258cu;	/* 430d7c: mov edi, 0x4b258c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430d81: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 430d84: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 430d86: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 430d88: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 430d8a: sub edi, ecx */
	m->eax = m->ecx;	/* 430d8c: mov eax, ecx */
	m->esi = m->edi;	/* 430d8e: mov esi, edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 430d90: shr ecx, 2 */
	m->edi = m->edx;	/* 430d93: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x748u);	/* 430d95: lea edx, [esp + 0x748] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 430d9c: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 430d9e: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 430da0: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430da2: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 430da5: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430da7: or ecx, 0xffffffff */
	m->edi = 0x4b257cu;	/* 430daa: mov edi, 0x4b257c */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 430daf: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 430db1: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 430db3: sub edi, ecx */
	m->eax = m->ecx;	/* 430db5: mov eax, ecx */
	m->esi = m->edi;	/* 430db7: mov esi, edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 430db9: shr ecx, 2 */
	m->edi = m->edx;	/* 430dbc: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x788u);	/* 430dbe: lea edx, [esp + 0x788] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 430dc5: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 430dc7: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 430dc9: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430dcb: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 430dce: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430dd0: or ecx, 0xffffffff */
	m->edi = 0x4b256cu;	/* 430dd3: mov edi, 0x4b256c */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 430dd8: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 430dda: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 430ddc: sub edi, ecx */
	m->eax = m->ecx;	/* 430dde: mov eax, ecx */
	m->esi = m->edi;	/* 430de0: mov esi, edi */
	m->edi = m->edx;	/* 430de2: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x1c8u);	/* 430de4: lea edx, [esp + 0x1c8] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 430deb: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 430dee: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 430df0: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 430df2: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430df4: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 430df7: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2480u;	/* 430df9: mov edi, 0x4b2480 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430dfe: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 430e01: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 430e03: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 430e05: sub edi, ecx */
	m->eax = m->ecx;	/* 430e07: mov eax, ecx */
	m->esi = m->edi;	/* 430e09: mov esi, edi */
	m->edi = m->edx;	/* 430e0b: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x208u);	/* 430e0d: lea edx, [esp + 0x208] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 430e14: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 430e17: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 430e19: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 430e1b: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430e1d: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 430e20: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2470u;	/* 430e22: mov edi, 0x4b2470 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430e27: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 430e2a: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 430e2c: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 430e2e: sub edi, ecx */
	m->eax = m->ecx;	/* 430e30: mov eax, ecx */
	m->esi = m->edi;	/* 430e32: mov esi, edi */
	m->edi = m->edx;	/* 430e34: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x3c8u);	/* 430e36: lea edx, [esp + 0x3c8] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 430e3d: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 430e40: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 430e42: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 430e44: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430e46: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 430e49: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b245cu;	/* 430e4b: mov edi, 0x4b245c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430e50: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 430e53: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 430e55: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 430e57: sub edi, ecx */
	m->eax = m->ecx;	/* 430e59: mov eax, ecx */
	m->esi = m->edi;	/* 430e5b: mov esi, edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 430e5d: shr ecx, 2 */
	m->edi = m->edx;	/* 430e60: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x408u);	/* 430e62: lea edx, [esp + 0x408] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 430e69: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 430e6b: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 430e6d: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430e6f: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 430e72: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430e74: or ecx, 0xffffffff */
	m->edi = 0x4b2448u;	/* 430e77: mov edi, 0x4b2448 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 430e7c: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 430e7e: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 430e80: sub edi, ecx */
	m->eax = m->ecx;	/* 430e82: mov eax, ecx */
	m->esi = m->edi;	/* 430e84: mov esi, edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 430e86: shr ecx, 2 */
	m->edi = m->edx;	/* 430e89: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x348u);	/* 430e8b: lea edx, [esp + 0x348] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 430e92: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 430e94: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 430e96: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430e98: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 430e9b: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430e9d: or ecx, 0xffffffff */
	m->edi = 0x4b2434u;	/* 430ea0: mov edi, 0x4b2434 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 430ea5: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 430ea7: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 430ea9: sub edi, ecx */
	m->eax = m->ecx;	/* 430eab: mov eax, ecx */
	m->esi = m->edi;	/* 430ead: mov esi, edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 430eaf: shr ecx, 2 */
	m->edi = m->edx;	/* 430eb2: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x388u);	/* 430eb4: lea edx, [esp + 0x388] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 430ebb: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 430ebd: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 430ebf: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430ec1: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 430ec4: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2420u;	/* 430ec6: mov edi, 0x4b2420 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430ecb: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 430ece: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 430ed0: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 430ed2: sub edi, ecx */
	m->eax = m->ecx;	/* 430ed4: mov eax, ecx */
	m->esi = m->edi;	/* 430ed6: mov esi, edi */
	m->edi = m->edx;	/* 430ed8: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x2c8u);	/* 430eda: lea edx, [esp + 0x2c8] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 430ee1: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 430ee4: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 430ee6: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 430ee8: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430eea: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 430eed: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b240cu;	/* 430eef: mov edi, 0x4b240c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430ef4: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 430ef7: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 430ef9: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 430efb: sub edi, ecx */
	m->eax = m->ecx;	/* 430efd: mov eax, ecx */
	m->esi = m->edi;	/* 430eff: mov esi, edi */
	m->edi = m->edx;	/* 430f01: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x308u);	/* 430f03: lea edx, [esp + 0x308] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 430f0a: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 430f0d: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 430f0f: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 430f11: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430f13: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 430f16: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b23f8u;	/* 430f18: mov edi, 0x4b23f8 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430f1d: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 430f20: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 430f22: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 430f24: sub edi, ecx */
	m->eax = m->ecx;	/* 430f26: mov eax, ecx */
	m->esi = m->edi;	/* 430f28: mov esi, edi */
	m->edi = m->edx;	/* 430f2a: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 430f2c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 430f2f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 430f31: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430f33: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 430f36: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430f38: or ecx, 0xffffffff */
	m->edi = 0x4b23e4u;	/* 430f3b: mov edi, 0x4b23e4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 430f40: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x248u);	/* 430f42: lea edx, [esp + 0x248] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 430f49: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 430f4b: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 430f4d: sub edi, ecx */
	m->eax = m->ecx;	/* 430f4f: mov eax, ecx */
	m->esi = m->edi;	/* 430f51: mov esi, edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 430f53: shr ecx, 2 */
	m->edi = m->edx;	/* 430f56: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x288u);	/* 430f58: lea edx, [esp + 0x288] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 430f5f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 430f61: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 430f63: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430f65: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 430f68: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430f6a: or ecx, 0xffffffff */
	m->edi = 0x4b23d0u;	/* 430f6d: mov edi, 0x4b23d0 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 430f72: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 430f74: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 430f76: sub edi, ecx */
	m->eax = m->ecx;	/* 430f78: mov eax, ecx */
	m->esi = m->edi;	/* 430f7a: mov esi, edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 430f7c: shr ecx, 2 */
	m->edi = m->edx;	/* 430f7f: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x448u);	/* 430f81: lea edx, [esp + 0x448] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 430f88: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 430f8a: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 430f8c: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430f8e: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 430f91: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430f93: or ecx, 0xffffffff */
	m->edi = 0x4b23c0u;	/* 430f96: mov edi, 0x4b23c0 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 430f9b: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 430f9d: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 430f9f: sub edi, ecx */
	m->eax = m->ecx;	/* 430fa1: mov eax, ecx */
	m->esi = m->edi;	/* 430fa3: mov esi, edi */
	m->edi = m->edx;	/* 430fa5: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x488u);	/* 430fa7: lea edx, [esp + 0x488] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 430fae: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 430fb1: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 430fb3: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 430fb5: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430fb7: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 430fba: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b23b0u;	/* 430fbc: mov edi, 0x4b23b0 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430fc1: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 430fc4: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 430fc6: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 430fc8: sub edi, ecx */
	m->eax = m->ecx;	/* 430fca: mov eax, ecx */
	m->esi = m->edi;	/* 430fcc: mov esi, edi */
	m->edi = m->edx;	/* 430fce: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x4c8u);	/* 430fd0: lea edx, [esp + 0x4c8] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 430fd7: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 430fda: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 430fdc: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 430fde: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430fe0: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 430fe3: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b23a0u;	/* 430fe5: mov edi, 0x4b23a0 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430fea: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 430fed: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 430fef: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 430ff1: sub edi, ecx */
	m->eax = m->ecx;	/* 430ff3: mov eax, ecx */
	m->esi = m->edi;	/* 430ff5: mov esi, edi */
	m->edi = m->edx;	/* 430ff7: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x508u);	/* 430ff9: lea edx, [esp + 0x508] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 431000: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 431003: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 431005: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 431007: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 431009: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43100c: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2390u;	/* 43100e: mov edi, 0x4b2390 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 431013: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 431016: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 431018: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43101a: sub edi, ecx */
	m->eax = m->ecx;	/* 43101c: mov eax, ecx */
	m->esi = m->edi;	/* 43101e: mov esi, edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 431020: shr ecx, 2 */
	m->edi = m->edx;	/* 431023: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x548u);	/* 431025: lea edx, [esp + 0x548] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43102c: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 43102e: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 431030: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 431032: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 431035: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 431037: or ecx, 0xffffffff */
	m->edi = 0x4b2380u;	/* 43103a: mov edi, 0x4b2380 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43103f: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 431041: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 431043: sub edi, ecx */
	m->eax = m->ecx;	/* 431045: mov eax, ecx */
	m->esi = m->edi;	/* 431047: mov esi, edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 431049: shr ecx, 2 */
	m->edi = m->edx;	/* 43104c: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x588u);	/* 43104e: lea edx, [esp + 0x588] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 431055: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 431057: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 431059: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43105b: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43105e: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 431060: or ecx, 0xffffffff */
	m->edi = 0x4b2370u;	/* 431063: mov edi, 0x4b2370 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 431068: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43106a: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43106c: sub edi, ecx */
	m->eax = m->ecx;	/* 43106e: mov eax, ecx */
	m->esi = m->edi;	/* 431070: mov esi, edi */
	m->edi = m->edx;	/* 431072: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x188u);	/* 431074: lea edx, [esp + 0x188] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43107b: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43107e: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 431080: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 431082: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 431084: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 431087: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4ad574u;	/* 431089: mov edi, 0x4ad574 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43108e: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 431091: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 431093: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 431095: sub edi, ecx */
	m->eax = m->ecx;	/* 431097: mov eax, ecx */
	m->esi = m->edi;	/* 431099: mov esi, edi */
	m->edi = m->edx;	/* 43109b: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x148u);	/* 43109d: lea edx, [esp + 0x148] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4310a4: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4310a7: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4310a9: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4310ab: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4310ad: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4310b0: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2360u;	/* 4310b2: mov edi, 0x4b2360 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4310b7: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4310ba: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4310bc: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4310be: sub edi, ecx */
	m->eax = m->ecx;	/* 4310c0: mov eax, ecx */
	m->esi = m->edi;	/* 4310c2: mov esi, edi */
	m->edi = m->edx;	/* 4310c4: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0xc8u);	/* 4310c6: lea edx, [esp + 0xc8] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4310cd: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4310d0: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4310d2: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4310d4: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4310d6: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4310d9: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2354u;	/* 4310db: mov edi, 0x4b2354 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4310e0: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4310e3: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4310e5: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4310e7: sub edi, ecx */
	m->eax = m->ecx;	/* 4310e9: mov eax, ecx */
	m->esi = m->edi;	/* 4310eb: mov esi, edi */
	m->edi = m->edx;	/* 4310ed: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4310ef: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4310f2: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4310f4: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4310f6: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4310f8: and ecx, 3 */
	m->edx = (DWORD)(m->esp + 0x48u);	/* 4310fb: lea edx, [esp + 0x48] */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4310ff: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 431101: or ecx, 0xffffffff */
	m->edi = 0x4b2344u;	/* 431104: mov edi, 0x4b2344 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 431109: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43110b: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43110d: sub edi, ecx */
	m->eax = m->ecx;	/* 43110f: mov eax, ecx */
	m->esi = m->edi;	/* 431111: mov esi, edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 431113: shr ecx, 2 */
	m->edi = m->edx;	/* 431116: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x88u);	/* 431118: lea edx, [esp + 0x88] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43111f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 431121: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 431123: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 431125: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 431128: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2330u;	/* 43112a: mov edi, 0x4b2330 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43112f: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 431132: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 431134: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 431136: sub edi, ecx */
	m->eax = m->ecx;	/* 431138: mov eax, ecx */
	m->esi = m->edi;	/* 43113a: mov esi, edi */
	m->edi = m->edx;	/* 43113c: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x108u);	/* 43113e: lea edx, [esp + 0x108] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 431145: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 431148: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 43114a: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43114c: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43114e: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 431151: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2320u;	/* 431153: mov edi, 0x4b2320 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 431158: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43115b: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43115d: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43115f: sub edi, ecx */
	m->eax = m->ecx;	/* 431161: mov eax, ecx */
	m->esi = m->edi;	/* 431163: mov esi, edi */
	m->edi = m->edx;	/* 431165: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x8u);	/* 431167: lea edx, [esp + 8] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43116b: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43116e: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 431170: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 431172: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 431174: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 431177: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b255cu;	/* 431179: mov edi, 0x4b255c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43117e: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 431181: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 431183: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 431185: sub edi, ecx */
	m->eax = m->ecx;	/* 431187: mov eax, ecx */
	m->esi = m->edi;	/* 431189: mov esi, edi */
	m->edi = m->edx;	/* 43118b: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43118d: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 431190: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 431192: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 431194: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 431197: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD a_ = M32((DWORD)(0x4dda34u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(0x4dda34u)) = r_; }	/* 431199: inc dword ptr [0x4dda34] */
	m->esp -= 4; M32(m->esp) = 0x4311a4u; native_call(m, 0x41f100u);	/* 43119f: call 0x41f100 */
	{ DWORD v_ = 0x40000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4311a4: push 0x40000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4311a9: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4311b0u; native_call(m, 0x41e730u);	/* 4311ab: call 0x41e730 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4311b0: add esp, 8 */
	m->esi = 0x9dad6cu;	/* 4311b3: mov esi, 0x9dad6c */
	m->edi = (DWORD)(m->esp + 0x5c8u);	/* 4311b8: lea edi, [esp + 0x5c8] */
L_4311bf:
	m->ecx = M32((DWORD)(0xa0e010u));	/* 4311bf: mov ecx, dword ptr [0xa0e010] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4311c5: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4311c7: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4311c9: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4311cb: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4311cd: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4311cf: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4311d1: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4311d3: push edi */
	m->esp -= 4; M32(m->esp) = 0x4311d9u; native_call(m, 0x456be0u);	/* 4311d4: call 0x456be0 */
	M32((DWORD)(m->esi + 0x0u)) = m->eax;	/* 4311d9: mov dword ptr [esi], eax */
	m->eax = M32((DWORD)(0x4dda34u));	/* 4311db: mov eax, dword ptr [0x4dda34] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4311e0: inc eax */
	M32((DWORD)(0x4dda34u)) = m->eax;	/* 4311e1: mov dword ptr [0x4dda34], eax */
	m->esp -= 4; M32(m->esp) = 0x4311ebu; native_call(m, 0x41f100u);	/* 4311e6: call 0x41f100 */
	{ DWORD a_ = m->esi, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4311eb: add esi, 4 */
	{ DWORD a_ = m->edi, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4311ee: add edi, 0x40 */
	{ DWORD a_ = m->esi, b_ = 0x9dad8cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4311f1: cmp esi, 0x9dad8c */
	if (m->sf != m->of) goto L_4311bf;	/* 4311f7: jl 0x4311bf */
	m->esi = 0x4deb4cu;	/* 4311f9: mov esi, 0x4deb4c */
	m->edi = (DWORD)(m->esp + 0x1c8u);	/* 4311fe: lea edi, [esp + 0x1c8] */
L_431205:
	m->ecx = M32((DWORD)(0xa0e010u));	/* 431205: mov ecx, dword ptr [0xa0e010] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43120b: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43120d: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43120f: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431211: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431213: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431215: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431217: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 431219: push edi */
	m->esp -= 4; M32(m->esp) = 0x43121fu; native_call(m, 0x456be0u);	/* 43121a: call 0x456be0 */
	M32((DWORD)(m->esi + 0x0u)) = m->eax;	/* 43121f: mov dword ptr [esi], eax */
	m->eax = M32((DWORD)(0x4dda34u));	/* 431221: mov eax, dword ptr [0x4dda34] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 431226: inc eax */
	M32((DWORD)(0x4dda34u)) = m->eax;	/* 431227: mov dword ptr [0x4dda34], eax */
	m->esp -= 4; M32(m->esp) = 0x431231u; native_call(m, 0x41f100u);	/* 43122c: call 0x41f100 */
	{ DWORD a_ = m->esi, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 431231: add esi, 4 */
	{ DWORD a_ = m->edi, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 431234: add edi, 0x40 */
	{ DWORD a_ = m->esi, b_ = 0x4deb54u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 431237: cmp esi, 0x4deb54 */
	if (m->sf != m->of) goto L_431205;	/* 43123d: jl 0x431205 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 43123f: xor esi, esi */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 431241: xor edi, edi */
L_431243:
	m->ecx = M32((DWORD)(0xa0e010u));	/* 431243: mov ecx, dword ptr [0xa0e010] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431249: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43124b: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43124d: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43124f: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431251: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431253: push 0 */
	m->edx = (DWORD)(m->esp + m->esi*1 + 0x3e0u);	/* 431255: lea edx, [esp + esi + 0x3e0] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43125c: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43125e: push edx */
	m->esp -= 4; M32(m->esp) = 0x431264u; native_call(m, 0x456be0u);	/* 43125f: call 0x456be0 */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 431264: mov ecx, dword ptr [0xa0e010] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43126a: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43126c: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43126e: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431270: push 0 */
	M32((DWORD)(m->edi + 0x76d478u)) = m->eax;	/* 431272: mov dword ptr [edi + 0x76d478], eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431278: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43127a: push 0 */
	m->eax = (DWORD)(m->esp + m->esi*1 + 0x360u);	/* 43127c: lea eax, [esp + esi + 0x360] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431283: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 431285: push eax */
	m->esp -= 4; M32(m->esp) = 0x43128bu; native_call(m, 0x456be0u);	/* 431286: call 0x456be0 */
	M32((DWORD)(m->edi + 0x4df040u)) = m->eax;	/* 43128b: mov dword ptr [edi + 0x4df040], eax */
	m->eax = M32((DWORD)(0x4dda34u));	/* 431291: mov eax, dword ptr [0x4dda34] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 431296: inc eax */
	M32((DWORD)(0x4dda34u)) = m->eax;	/* 431297: mov dword ptr [0x4dda34], eax */
	m->esp -= 4; M32(m->esp) = 0x4312a1u; native_call(m, 0x41f100u);	/* 43129c: call 0x41f100 */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 4312a1: mov ecx, dword ptr [0xa0e010] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4312a7: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4312a9: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4312ab: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4312ad: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4312af: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4312b1: push 0 */
	m->edx = (DWORD)(m->esp + m->esi*1 + 0x260u);	/* 4312b3: lea edx, [esp + esi + 0x260] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4312ba: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4312bc: push edx */
	m->esp -= 4; M32(m->esp) = 0x4312c2u; native_call(m, 0x456be0u);	/* 4312bd: call 0x456be0 */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 4312c2: mov ecx, dword ptr [0xa0e010] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4312c8: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4312ca: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4312cc: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4312ce: push 0 */
	M32((DWORD)(m->edi + 0x5b1978u)) = m->eax;	/* 4312d0: mov dword ptr [edi + 0x5b1978], eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4312d6: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4312d8: push 0 */
	m->eax = (DWORD)(m->esp + m->esi*1 + 0x2e0u);	/* 4312da: lea eax, [esp + esi + 0x2e0] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4312e1: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4312e3: push eax */
	m->esp -= 4; M32(m->esp) = 0x4312e9u; native_call(m, 0x456be0u);	/* 4312e4: call 0x456be0 */
	M32((DWORD)(m->edi + 0x4df904u)) = m->eax;	/* 4312e9: mov dword ptr [edi + 0x4df904], eax */
	m->eax = M32((DWORD)(0x4dda34u));	/* 4312ef: mov eax, dword ptr [0x4dda34] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4312f4: inc eax */
	M32((DWORD)(0x4dda34u)) = m->eax;	/* 4312f5: mov dword ptr [0x4dda34], eax */
	m->esp -= 4; M32(m->esp) = 0x4312ffu; native_call(m, 0x41f100u);	/* 4312fa: call 0x41f100 */
	{ DWORD a_ = m->esi, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4312ff: add esi, 0x40 */
	{ DWORD a_ = m->edi, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 431302: add edi, 4 */
	{ DWORD a_ = m->esi, b_ = 0x80u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 431305: cmp esi, 0x80 */
	if (m->sf != m->of) goto L_431243;	/* 43130b: jl 0x431243 */
	m->esi = 0x9da45cu;	/* 431311: mov esi, 0x9da45c */
	m->edi = (DWORD)(m->esp + 0x448u);	/* 431316: lea edi, [esp + 0x448] */
L_43131d:
	m->ecx = M32((DWORD)(0xa0e010u));	/* 43131d: mov ecx, dword ptr [0xa0e010] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431323: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431325: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431327: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431329: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43132b: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43132d: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43132f: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 431331: push edi */
	m->esp -= 4; M32(m->esp) = 0x431337u; native_call(m, 0x456be0u);	/* 431332: call 0x456be0 */
	M32((DWORD)(m->esi + 0x0u)) = m->eax;	/* 431337: mov dword ptr [esi], eax */
	m->eax = M32((DWORD)(0x4dda34u));	/* 431339: mov eax, dword ptr [0x4dda34] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 43133e: inc eax */
	M32((DWORD)(0x4dda34u)) = m->eax;	/* 43133f: mov dword ptr [0x4dda34], eax */
	m->esp -= 4; M32(m->esp) = 0x431349u; native_call(m, 0x41f100u);	/* 431344: call 0x41f100 */
	{ DWORD a_ = m->esi, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 431349: add esi, 4 */
	{ DWORD a_ = m->edi, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43134c: add edi, 0x40 */
	{ DWORD a_ = m->esi, b_ = 0x9da474u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43134f: cmp esi, 0x9da474 */
	if (m->sf != m->of) goto L_43131d;	/* 431355: jl 0x43131d */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 431357: mov ecx, dword ptr [0xa0e010] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43135d: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43135f: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431361: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431363: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431365: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431367: push 0 */
	m->edx = (DWORD)(m->esp + 0x1a0u);	/* 431369: lea edx, [esp + 0x1a0] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431370: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 431372: push edx */
	m->esp -= 4; M32(m->esp) = 0x431378u; native_call(m, 0x456be0u);	/* 431373: call 0x456be0 */
	m->edi = M32((DWORD)(0x4dda34u));	/* 431378: mov edi, dword ptr [0x4dda34] */
	M32((DWORD)(0x4df450u)) = m->eax;	/* 43137e: mov dword ptr [0x4df450], eax */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 431383: inc edi */
	M32((DWORD)(0x4dda34u)) = m->edi;	/* 431384: mov dword ptr [0x4dda34], edi */
	m->esp -= 4; M32(m->esp) = 0x43138fu; native_call(m, 0x41f100u);	/* 43138a: call 0x41f100 */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 43138f: mov ecx, dword ptr [0xa0e010] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431395: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431397: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431399: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43139b: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43139d: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43139f: push 0 */
	m->eax = (DWORD)(m->esp + 0x160u);	/* 4313a1: lea eax, [esp + 0x160] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4313a8: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4313aa: push eax */
	m->esp -= 4; M32(m->esp) = 0x4313b0u; native_call(m, 0x456be0u);	/* 4313ab: call 0x456be0 */
	m->esi = M32((DWORD)(0x4dda34u));	/* 4313b0: mov esi, dword ptr [0x4dda34] */
	M32((DWORD)(0x9db0a4u)) = m->eax;	/* 4313b6: mov dword ptr [0x9db0a4], eax */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 4313bb: inc esi */
	M32((DWORD)(0x4dda34u)) = m->esi;	/* 4313bc: mov dword ptr [0x4dda34], esi */
	m->esp -= 4; M32(m->esp) = 0x4313c7u; native_call(m, 0x41f100u);	/* 4313c2: call 0x41f100 */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 4313c7: mov ecx, dword ptr [0xa0e010] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4313cd: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4313cf: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4313d1: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4313d3: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4313d5: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4313d7: push 0 */
	m->edx = (DWORD)(m->esp + 0xe0u);	/* 4313d9: lea edx, [esp + 0xe0] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4313e0: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4313e2: push edx */
	m->esp -= 4; M32(m->esp) = 0x4313e8u; native_call(m, 0x456be0u);	/* 4313e3: call 0x456be0 */
	m->ecx = M32((DWORD)(0x4dda34u));	/* 4313e8: mov ecx, dword ptr [0x4dda34] */
	M32((DWORD)(0x4e152cu)) = m->eax;	/* 4313ee: mov dword ptr [0x4e152c], eax */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4313f3: inc ecx */
	M32((DWORD)(0x4dda34u)) = m->ecx;	/* 4313f4: mov dword ptr [0x4dda34], ecx */
	m->esp -= 4; M32(m->esp) = 0x4313ffu; native_call(m, 0x41f100u);	/* 4313fa: call 0x41f100 */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 4313ff: mov ecx, dword ptr [0xa0e010] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431405: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431407: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431409: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43140b: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43140d: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43140f: push 0 */
	m->eax = (DWORD)(m->esp + 0x60u);	/* 431411: lea eax, [esp + 0x60] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431415: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 431417: push eax */
	m->esp -= 4; M32(m->esp) = 0x43141du; native_call(m, 0x456be0u);	/* 431418: call 0x456be0 */
	M32((DWORD)(0x4e186cu)) = m->eax;	/* 43141d: mov dword ptr [0x4e186c], eax */
	m->eax = M32((DWORD)(0x4dda34u));	/* 431422: mov eax, dword ptr [0x4dda34] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 431427: inc eax */
	M32((DWORD)(0x4dda34u)) = m->eax;	/* 431428: mov dword ptr [0x4dda34], eax */
	m->esp -= 4; M32(m->esp) = 0x431432u; native_call(m, 0x41f100u);	/* 43142d: call 0x41f100 */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 431432: mov ecx, dword ptr [0xa0e010] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431438: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43143a: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43143c: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43143e: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431440: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431442: push 0 */
	m->edx = (DWORD)(m->esp + 0xa0u);	/* 431444: lea edx, [esp + 0xa0] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43144b: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43144d: push edx */
	m->esp -= 4; M32(m->esp) = 0x431453u; native_call(m, 0x456be0u);	/* 43144e: call 0x456be0 */
	m->edi = M32((DWORD)(0x4dda34u));	/* 431453: mov edi, dword ptr [0x4dda34] */
	M32((DWORD)(0x76d36cu)) = m->eax;	/* 431459: mov dword ptr [0x76d36c], eax */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 43145e: inc edi */
	M32((DWORD)(0x4dda34u)) = m->edi;	/* 43145f: mov dword ptr [0x4dda34], edi */
	m->esp -= 4; M32(m->esp) = 0x43146au; native_call(m, 0x41f100u);	/* 431465: call 0x41f100 */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 43146a: mov ecx, dword ptr [0xa0e010] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431470: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431472: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431474: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431476: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431478: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43147a: push 0 */
	m->eax = (DWORD)(m->esp + 0x120u);	/* 43147c: lea eax, [esp + 0x120] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431483: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 431485: push eax */
	m->esp -= 4; M32(m->esp) = 0x43148bu; native_call(m, 0x456be0u);	/* 431486: call 0x456be0 */
	m->esi = M32((DWORD)(0x4dda34u));	/* 43148b: mov esi, dword ptr [0x4dda34] */
	M32((DWORD)(0x4e0cd0u)) = m->eax;	/* 431491: mov dword ptr [0x4e0cd0], eax */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 431496: inc esi */
	M32((DWORD)(0x4dda34u)) = m->esi;	/* 431497: mov dword ptr [0x4dda34], esi */
	m->esp -= 4; M32(m->esp) = 0x4314a2u; native_call(m, 0x41f100u);	/* 43149d: call 0x41f100 */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 4314a2: mov ecx, dword ptr [0xa0e010] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4314a8: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4314aa: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4314ac: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4314ae: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4314b0: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4314b2: push 0 */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 4314b4: lea edx, [esp + 0x20] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4314b8: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4314ba: push edx */
	m->esp -= 4; M32(m->esp) = 0x4314c0u; native_call(m, 0x456be0u);	/* 4314bb: call 0x456be0 */
	M32((DWORD)(0x4dfa00u)) = m->eax;	/* 4314c0: mov dword ptr [0x4dfa00], eax */
	m->eax = M32((DWORD)(0x4dda34u));	/* 4314c5: mov eax, dword ptr [0x4dda34] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4314ca: inc eax */
	M32((DWORD)(0x4dda34u)) = m->eax;	/* 4314cb: mov dword ptr [0x4dda34], eax */
	m->esp -= 4; M32(m->esp) = 0x4314d5u; native_call(m, 0x41f100u);	/* 4314d0: call 0x41f100 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4314d5: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4314d6: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x7c0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4314d7: add esp, 0x7c0 */
	m->esp += 4 + 0; return;	/* 4314dd: ret  */
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
