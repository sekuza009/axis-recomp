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

static void lift_407e40(X86 *m);
static void lift_40d840(X86 *m);
static void lift_43ea10(X86 *m);
static void lift_40cfd0(X86 *m);
static void lift_407410(X86 *m);

/* arena_createClick (0x407410), lifted by tools/lift.py */
static void lift_407410(X86 *m)
{
	m->eax = M32((DWORD)(0x4dbab0u));	/* 407410: mov eax, dword ptr [0x4dbab0] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 407415: push ebx */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 407416: xor ebx, ebx */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407418: cmp eax, ebx */
	if (!m->zf) goto L_407674;	/* 40741a: jne 0x407674 */
	{ DWORD a_ = M32((DWORD)(0x4db850u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407420: cmp dword ptr [0x4db850], ebx */
	if (!m->zf) goto L_407674;	/* 407426: jne 0x407674 */
	{ DWORD a_ = M32((DWORD)(0x4db518u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40742c: cmp dword ptr [0x4db518], ebx */
	if (!m->zf) goto L_407674;	/* 407432: jne 0x407674 */
	{ DWORD a_ = M32((DWORD)(0x4dbaccu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407438: cmp dword ptr [0x4dbacc], ebx */
	if (!m->zf) goto L_407674;	/* 40743e: jne 0x407674 */
	m->eax = M32((DWORD)(0x4dbb3cu));	/* 407444: mov eax, dword ptr [0x4dbb3c] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407449: cmp eax, 1 */
	if (m->zf) goto L_407674;	/* 40744c: je 0x407674 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407452: cmp eax, ebx */
	if (m->zf) goto L_407674;	/* 407454: je 0x407674 */
	{ DWORD a_ = M32((DWORD)(0x90d1c4u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40745a: cmp dword ptr [0x90d1c4], ebx */
	if (!m->zf) goto L_407674;	/* 407460: jne 0x407674 */
	{ DWORD a_ = M32((DWORD)(0x4ded8cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407466: cmp dword ptr [0x4ded8c], ebx */
	if (m->zf) goto L_407484;	/* 40746c: je 0x407484 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 40746e: push ebx */
	m->esp -= 4; M32(m->esp) = 0x407474u; native_call(m, 0x41e760u);	/* 40746f: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407474: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x40747cu; native_call(m, 0x452fe0u);	/* 407477: call 0x452fe0 */
	M32((DWORD)(0x4dbb3cu)) = m->ebx;	/* 40747c: mov dword ptr [0x4dbb3c], ebx */
	m->ebx = M32(m->esp); m->esp += 4;	/* 407482: pop ebx */
	m->esp += 4 + 0; return;	/* 407483: ret  */
L_407484:
	{ DWORD a_ = M32((DWORD)(0x4ded88u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407484: cmp dword ptr [0x4ded88], ebx */
	if (m->zf) goto L_407674;	/* 40748a: je 0x407674 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407490: cmp eax, 2 */
	if (!m->zf) goto L_407674;	/* 407493: jne 0x407674 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 407499: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 40749e: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4074a4: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4074a5: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4074abu; native_call(m, 0x404520u);	/* 4074a6: call 0x404520 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4074ab: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0xfu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4074ae: cmp eax, 0xf */
	if (!m->cf && !m->zf) goto L_407674;	/* 4074b1: ja 0x407674 */
	switch (m->eax) { case 0: goto L_4074be; case 1: goto L_4074c5; case 2: goto L_4074cc; case 3: goto L_4074df; case 4: goto L_4074fc; case 5: goto L_407526; case 6: goto L_4075e6; case 7: goto L_4075ed; case 8: goto L_4075f4; case 9: goto L_40760c; case 10: goto L_407674; case 11: goto L_40762d; case 12: goto L_40764e; case 13: goto L_407643; case 14: goto L_40764e; case 15: goto L_40765a; default: abort(); }	/* 4074b7: jmp dword ptr [eax*4 + 0x407678] */
L_4074be:
	m->esp -= 4; M32(m->esp) = 0x4074c3u; native_call(m, 0x404d70u);	/* 4074be: call 0x404d70 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4074c3: pop ebx */
	m->esp += 4 + 0; return;	/* 4074c4: ret  */
L_4074c5:
	m->esp -= 4; M32(m->esp) = 0x4074cau; native_call(m, 0x404f90u);	/* 4074c5: call 0x404f90 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4074ca: pop ebx */
	m->esp += 4 + 0; return;	/* 4074cb: ret  */
L_4074cc:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4074cc: push 2 */
	m->esp -= 4; M32(m->esp) = 0x4074d3u; native_call(m, 0x41e760u);	/* 4074ce: call 0x41e760 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4074d3: push 1 */
	m->esp -= 4; M32(m->esp) = 0x4074dau; native_call(m, 0x4068d0u);	/* 4074d5: call 0x4068d0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4074da: add esp, 8 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4074dd: pop ebx */
	m->esp += 4 + 0; return;	/* 4074de: ret  */
L_4074df:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4db549u))) & 0xff) << 0);	/* 4074df: mov al, byte ptr [0x4db549] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x2u & 0xffu, r_ = (a_ + b_) & 0xffu; FLAGS(r_, 8); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 4074e4: add al, 2 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x10u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4074e6: cmp al, 0x10 */
	M8((DWORD)(0x4db549u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 4074e8: mov byte ptr [0x4db549], al */
	if (m->zf || m->sf != m->of) goto L_407674;	/* 4074ed: jle 0x407674 */
	M8((DWORD)(0x4db549u)) = (BYTE)(0x2u);	/* 4074f3: mov byte ptr [0x4db549], 2 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4074fa: pop ebx */
	m->esp += 4 + 0; return;	/* 4074fb: ret  */
L_4074fc:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4db54au))) & 0xff) << 0);	/* 4074fc: mov al, byte ptr [0x4db54a] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((0x1u) & 0xff) << 0);	/* 407501: mov dl, 1 */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; m->edx = (m->edx & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 407503: sub dl, al */
	M8((DWORD)(0x4db54au)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 407505: mov byte ptr [0x4db54a], dl */
	if (!m->zf) goto L_4075dd;	/* 40750b: jne 0x4075dd */
	{ DWORD a_ = M8((DWORD)(0x4db54bu)), b_ = 0xdu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 407511: cmp byte ptr [0x4db54b], 0xd */
	if (m->zf || m->sf != m->of) goto L_407674;	/* 407518: jle 0x407674 */
	M8((DWORD)(0x4db54bu)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 40751e: mov byte ptr [0x4db54b], bl */
	m->ebx = M32(m->esp); m->esp += 4;	/* 407524: pop ebx */
	m->esp += 4 + 0; return;	/* 407525: ret  */
L_407526:
	m->eax = M32((DWORD)(0x67ef24u));	/* 407526: mov eax, dword ptr [0x67ef24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40752b: push eax */
	m->esp -= 4; M32(m->esp) = 0x407531u; native_call(m, 0x401590u);	/* 40752c: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407531: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 407534: test eax, eax */
	if (!m->zf) goto L_4075ac;	/* 407536: jne 0x4075ac */
	m->ecx = M32((DWORD)(0x9db0acu));	/* 407538: mov ecx, dword ptr [0x9db0ac] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40753e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x407544u; native_call(m, 0x401590u);	/* 40753f: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407544: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 407547: test eax, eax */
	if (!m->zf) goto L_4075ac;	/* 407549: jne 0x4075ac */
	m->edx = M32((DWORD)(0x6803a8u));	/* 40754b: mov edx, dword ptr [0x6803a8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 407551: push edx */
	m->esp -= 4; M32(m->esp) = 0x407557u; native_call(m, 0x401590u);	/* 407552: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407557: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40755a: test eax, eax */
	if (!m->zf) goto L_4075ac;	/* 40755c: jne 0x4075ac */
	m->eax = M32((DWORD)(0x9dad8cu));	/* 40755e: mov eax, dword ptr [0x9dad8c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 407563: push eax */
	m->esp -= 4; M32(m->esp) = 0x407569u; native_call(m, 0x401590u);	/* 407564: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407569: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40756c: test eax, eax */
	if (!m->zf) goto L_4075ac;	/* 40756e: jne 0x4075ac */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4db54au))) & 0xff) << 0);	/* 407570: mov al, byte ptr [0x4db54a] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 407575: cmp al, bl */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4db54bu))) & 0xff) << 0);	/* 407577: mov al, byte ptr [0x4db54b] */
	if (!m->zf) goto L_407595;	/* 40757c: jne 0x407595 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), r_ = (a_ + 1) & 0xffu; FLAGS(r_, 8); m->of = (r_ == 0x80u); m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 40757e: inc al */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0xdu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 407580: cmp al, 0xd */
	M8((DWORD)(0x4db54bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 407582: mov byte ptr [0x4db54b], al */
	if (m->zf || m->sf != m->of) goto L_407674;	/* 407587: jle 0x407674 */
	M8((DWORD)(0x4db54bu)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 40758d: mov byte ptr [0x4db54b], bl */
	m->ebx = M32(m->esp); m->esp += 4;	/* 407593: pop ebx */
	m->esp += 4 + 0; return;	/* 407594: ret  */
L_407595:
	{ DWORD a_ = ((m->eax >> 0) & 0xff), r_ = (a_ + 1) & 0xffu; FLAGS(r_, 8); m->of = (r_ == 0x80u); m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 407595: inc al */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0xeu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 407597: cmp al, 0xe */
	M8((DWORD)(0x4db54bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 407599: mov byte ptr [0x4db54b], al */
	if (m->zf || m->sf != m->of) goto L_407674;	/* 40759e: jle 0x407674 */
	M8((DWORD)(0x4db54bu)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 4075a4: mov byte ptr [0x4db54b], bl */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4075aa: pop ebx */
	m->esp += 4 + 0; return;	/* 4075ab: ret  */
L_4075ac:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4db54au))) & 0xff) << 0);	/* 4075ac: mov al, byte ptr [0x4db54a] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4075b1: cmp al, bl */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4db54bu))) & 0xff) << 0);	/* 4075b3: mov al, byte ptr [0x4db54b] */
	if (!m->zf) goto L_4075d0;	/* 4075b8: jne 0x4075d0 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), r_ = (a_ - 1) & 0xffu; FLAGS(r_, 8); m->of = (a_ == 0x80u); m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 4075ba: dec al */
	M8((DWORD)(0x4db54bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 4075bc: mov byte ptr [0x4db54b], al */
	if (!m->sf) goto L_407674;	/* 4075c1: jns 0x407674 */
	M8((DWORD)(0x4db54bu)) = (BYTE)(0xdu);	/* 4075c7: mov byte ptr [0x4db54b], 0xd */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4075ce: pop ebx */
	m->esp += 4 + 0; return;	/* 4075cf: ret  */
L_4075d0:
	{ DWORD a_ = ((m->eax >> 0) & 0xff), r_ = (a_ - 1) & 0xffu; FLAGS(r_, 8); m->of = (a_ == 0x80u); m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 4075d0: dec al */
	M8((DWORD)(0x4db54bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 4075d2: mov byte ptr [0x4db54b], al */
	if (!m->sf) goto L_407674;	/* 4075d7: jns 0x407674 */
L_4075dd:
	M8((DWORD)(0x4db54bu)) = (BYTE)(0xeu);	/* 4075dd: mov byte ptr [0x4db54b], 0xe */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4075e4: pop ebx */
	m->esp += 4 + 0; return;	/* 4075e5: ret  */
L_4075e6:
	m->esp -= 4; M32(m->esp) = 0x4075ebu; native_call(m, 0x404e10u);	/* 4075e6: call 0x404e10 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4075eb: pop ebx */
	m->esp += 4 + 0; return;	/* 4075ec: ret  */
L_4075ed:
	m->esp -= 4; M32(m->esp) = 0x4075f2u; native_call(m, 0x404ed0u);	/* 4075ed: call 0x404ed0 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4075f2: pop ebx */
	m->esp += 4 + 0; return;	/* 4075f3: ret  */
L_4075f4:
	{ DWORD a_ = M32((DWORD)(0x4ded54u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4075f4: cmp dword ptr [0x4ded54], ebx */
	if (!m->zf) goto L_407674;	/* 4075fa: jne 0x407674 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4075fc: push ebx */
	m->esp -= 4; M32(m->esp) = 0x407602u; native_call(m, 0x41e760u);	/* 4075fd: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407602: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x40760au; native_call(m, 0x4052c0u);	/* 407605: call 0x4052c0 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 40760a: pop ebx */
	m->esp += 4 + 0; return;	/* 40760b: ret  */
L_40760c:
	{ DWORD a_ = M32((DWORD)(0x4ded54u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40760c: cmp dword ptr [0x4ded54], ebx */
	if (!m->zf) goto L_407674;	/* 407612: jne 0x407674 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 407614: push ebx */
	m->esp -= 4; M32(m->esp) = 0x40761au; native_call(m, 0x41e760u);	/* 407615: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40761a: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x407622u; native_call(m, 0x405cf0u);	/* 40761d: call 0x405cf0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 407622: test eax, eax */
	if (!m->zf) goto L_407674;	/* 407624: jne 0x407674 */
	m->esp -= 4; M32(m->esp) = 0x40762bu; native_call(m, 0x4057a0u);	/* 407626: call 0x4057a0 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 40762b: pop ebx */
	m->esp += 4 + 0; return;	/* 40762c: ret  */
L_40762d:
	m->esp -= 4; M32(m->esp) = 0x407632u; native_call(m, 0x452fe0u);	/* 40762d: call 0x452fe0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 407632: push ebx */
	M32((DWORD)(0x4dbb3cu)) = m->ebx;	/* 407633: mov dword ptr [0x4dbb3c], ebx */
	m->esp -= 4; M32(m->esp) = 0x40763eu; native_call(m, 0x41e760u);	/* 407639: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40763e: add esp, 4 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 407641: pop ebx */
	m->esp += 4 + 0; return;	/* 407642: ret  */
L_407643:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 407643: push ebx */
	m->esp -= 4; M32(m->esp) = 0x407649u; native_call(m, 0x4068d0u);	/* 407644: call 0x4068d0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407649: add esp, 4 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 40764c: pop ebx */
	m->esp += 4 + 0; return;	/* 40764d: ret  */
L_40764e:
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40764e: push 1 */
	m->esp -= 4; M32(m->esp) = 0x407655u; native_call(m, 0x4068d0u);	/* 407650: call 0x4068d0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407655: add esp, 4 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 407658: pop ebx */
	m->esp += 4 + 0; return;	/* 407659: ret  */
L_40765a:
	{ DWORD a_ = M8((DWORD)(0x4db54au)), b_ = 0x1u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40765a: cmp byte ptr [0x4db54a], 1 */
	if (!m->zf) goto L_407674;	/* 407661: jne 0x407674 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 407663: push 2 */
	m->esp -= 4; M32(m->esp) = 0x40766au; native_call(m, 0x41e760u);	/* 407665: call 0x41e760 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40766a: push 1 */
	m->esp -= 4; M32(m->esp) = 0x407671u; native_call(m, 0x403490u);	/* 40766c: call 0x403490 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407671: add esp, 8 */
L_407674:
	m->ebx = M32(m->esp); m->esp += 4;	/* 407674: pop ebx */
	m->esp += 4 + 0; return;	/* 407675: ret  */
}

/* lobbyTop_connect (0x407e40), lifted by tools/lift.py */
static void lift_407e40(X86 *m)
{
	m->eax = M32((DWORD)(0x4dbb3cu));	/* 407e40: mov eax, dword ptr [0x4dbb3c] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 407e45: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 407e46: push esi */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407e47: cmp eax, 1 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 407e4a: push edi */
	if (m->zf) goto L_4080b7;	/* 407e4b: je 0x4080b7 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 407e51: xor ebx, ebx */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407e53: cmp eax, ebx */
	if (m->zf) goto L_4080b7;	/* 407e55: je 0x4080b7 */
	{ DWORD a_ = M32((DWORD)(0x90d1c4u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407e5b: cmp dword ptr [0x90d1c4], ebx */
	if (!m->zf) goto L_4080b7;	/* 407e61: jne 0x4080b7 */
	{ DWORD a_ = M32((DWORD)(0x4dbab0u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407e67: cmp dword ptr [0x4dbab0], ebx */
	if (m->zf) goto L_407efb;	/* 407e6d: je 0x407efb */
	{ DWORD a_ = M32((DWORD)(0x68039cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407e73: cmp dword ptr [0x68039c], ebx */
	if (!m->zf) goto L_4080b7;	/* 407e79: jne 0x4080b7 */
	m->edi = 0x9dc92cu;	/* 407e7f: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 407e84: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 407e87: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 407e89: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 407e8b: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 407e8d: dec ecx */
	if (!m->zf) goto L_407e9a;	/* 407e8e: jne 0x407e9a */
	m->edi = M32(m->esp); m->esp += 4;	/* 407e90: pop edi */
	M32((DWORD)(0x4dbab0u)) = m->ebx;	/* 407e91: mov dword ptr [0x4dbab0], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 407e97: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 407e98: pop ebx */
	m->esp += 4 + 0; return;	/* 407e99: ret  */
L_407e9a:
	{ DWORD v_ = 0x9dc92cu; m->esp -= 4; M32(m->esp) = v_; }	/* 407e9a: push 0x9dc92c */
	m->esp -= 4; M32(m->esp) = 0x407ea4u; native_call(m, 0x4343b0u);	/* 407e9f: call 0x4343b0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407ea4: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407ea7: cmp eax, 1 */
	if (!m->zf) goto L_407ec0;	/* 407eaa: jne 0x407ec0 */
	{ DWORD v_ = 0x6u; m->esp -= 4; M32(m->esp) = v_; }	/* 407eac: push 6 */
	m->esp -= 4; M32(m->esp) = 0x407eb3u; native_call(m, 0x41e760u);	/* 407eae: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407eb3: add esp, 4 */
	M32((DWORD)(0x4dbab0u)) = m->ebx;	/* 407eb6: mov dword ptr [0x4dbab0], ebx */
	m->edi = M32(m->esp); m->esp += 4;	/* 407ebc: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 407ebd: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 407ebe: pop ebx */
	m->esp += 4 + 0; return;	/* 407ebf: ret  */
L_407ec0:
	m->ecx = 0x8u;	/* 407ec0: mov ecx, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 407ec5: xor eax, eax */
	m->edi = 0x4db528u;	/* 407ec7: mov edi, 0x4db528 */
	M32((DWORD)(0x4dbab0u)) = m->ebx;	/* 407ecc: mov dword ptr [0x4dbab0], ebx */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 407ed2: rep stosd dword ptr es:[edi], eax */
	m->edi = 0x9dc92cu;	/* 407ed4: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 407ed9: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 407edc: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 407ede: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 407ee0: sub edi, ecx */
	m->eax = m->ecx;	/* 407ee2: mov eax, ecx */
	m->esi = m->edi;	/* 407ee4: mov esi, edi */
	m->edi = 0x4db528u;	/* 407ee6: mov edi, 0x4db528 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 407eeb: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 407eee: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 407ef0: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 407ef2: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 407ef5: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = M32(m->esp); m->esp += 4;	/* 407ef7: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 407ef8: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 407ef9: pop ebx */
	m->esp += 4 + 0; return;	/* 407efa: ret  */
L_407efb:
	{ DWORD a_ = M32((DWORD)(0x4dbaccu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407efb: cmp dword ptr [0x4dbacc], ebx */
	if (m->zf) goto L_407f52;	/* 407f01: je 0x407f52 */
	{ DWORD a_ = M32((DWORD)(0x68039cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407f03: cmp dword ptr [0x68039c], ebx */
	if (!m->zf) goto L_4080b7;	/* 407f09: jne 0x4080b7 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 407f0f: xor ecx, ecx */
	m->edi = 0x9dc92cu;	/* 407f11: mov edi, 0x9dc92c */
	M32((DWORD)(0x4db54eu)) = m->ecx;	/* 407f16: mov dword ptr [0x4db54e], ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 407f1c: xor eax, eax */
	M32((DWORD)(0x4db552u)) = m->ecx;	/* 407f1e: mov dword ptr [0x4db552], ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 407f24: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 407f27: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 407f29: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 407f2b: sub edi, ecx */
	M32((DWORD)(0x4dbaccu)) = m->ebx;	/* 407f2d: mov dword ptr [0x4dbacc], ebx */
	m->edx = m->ecx;	/* 407f33: mov edx, ecx */
	m->esi = m->edi;	/* 407f35: mov esi, edi */
	m->edi = 0x4db54eu;	/* 407f37: mov edi, 0x4db54e */
	M32((DWORD)(0x4e1868u)) = m->ebx;	/* 407f3c: mov dword ptr [0x4e1868], ebx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 407f42: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 407f45: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 407f47: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 407f49: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 407f4c: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = M32(m->esp); m->esp += 4;	/* 407f4e: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 407f4f: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 407f50: pop ebx */
	m->esp += 4 + 0; return;	/* 407f51: ret  */
L_407f52:
	{ DWORD a_ = M32((DWORD)(0x4db850u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407f52: cmp dword ptr [0x4db850], ebx */
	if (m->zf) goto L_407fad;	/* 407f58: je 0x407fad */
	{ DWORD a_ = M32((DWORD)(0x68039cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407f5a: cmp dword ptr [0x68039c], ebx */
	if (!m->zf) goto L_4080b7;	/* 407f60: jne 0x4080b7 */
	m->edi = 0x9dc92cu;	/* 407f66: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 407f6b: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 407f6e: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 407f70: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 407f72: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 407f74: dec ecx */
	if (!m->zf) goto L_407f81;	/* 407f75: jne 0x407f81 */
	m->edi = M32(m->esp); m->esp += 4;	/* 407f77: pop edi */
	M32((DWORD)(0x4db850u)) = m->ebx;	/* 407f78: mov dword ptr [0x4db850], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 407f7e: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 407f7f: pop ebx */
	m->esp += 4 + 0; return;	/* 407f80: ret  */
L_407f81:
	{ DWORD v_ = 0x9dc92cu; m->esp -= 4; M32(m->esp) = v_; }	/* 407f81: push 0x9dc92c */
	m->esp -= 4; M32(m->esp) = 0x407f8bu; native_call(m, 0x49ec09u);	/* 407f86: call 0x49ec09 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407f8b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0xfau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407f8e: cmp eax, 0xfa */
	if (!m->zf && m->sf == m->of) goto L_407f99;	/* 407f93: jg 0x407f99 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407f95: cmp eax, ebx */
	if (m->sf == m->of) goto L_407f9e;	/* 407f97: jge 0x407f9e */
L_407f99:
	m->eax = 0xfau;	/* 407f99: mov eax, 0xfa */
L_407f9e:
	m->edi = M32(m->esp); m->esp += 4;	/* 407f9e: pop edi */
	M32((DWORD)(0x4db850u)) = m->ebx;	/* 407f9f: mov dword ptr [0x4db850], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 407fa5: pop esi */
	M8((DWORD)(0x4db54cu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 407fa6: mov byte ptr [0x4db54c], al */
	m->ebx = M32(m->esp); m->esp += 4;	/* 407fab: pop ebx */
	m->esp += 4 + 0; return;	/* 407fac: ret  */
L_407fad:
	{ DWORD a_ = M32((DWORD)(0x4db518u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407fad: cmp dword ptr [0x4db518], ebx */
	if (m->zf) goto L_408008;	/* 407fb3: je 0x408008 */
	{ DWORD a_ = M32((DWORD)(0x68039cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407fb5: cmp dword ptr [0x68039c], ebx */
	if (!m->zf) goto L_4080b7;	/* 407fbb: jne 0x4080b7 */
	m->edi = 0x9dc92cu;	/* 407fc1: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 407fc6: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 407fc9: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 407fcb: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 407fcd: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 407fcf: dec ecx */
	if (!m->zf) goto L_407fdc;	/* 407fd0: jne 0x407fdc */
	m->edi = M32(m->esp); m->esp += 4;	/* 407fd2: pop edi */
	M32((DWORD)(0x4db518u)) = m->ebx;	/* 407fd3: mov dword ptr [0x4db518], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 407fd9: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 407fda: pop ebx */
	m->esp += 4 + 0; return;	/* 407fdb: ret  */
L_407fdc:
	{ DWORD v_ = 0x9dc92cu; m->esp -= 4; M32(m->esp) = v_; }	/* 407fdc: push 0x9dc92c */
	m->esp -= 4; M32(m->esp) = 0x407fe6u; native_call(m, 0x49ec09u);	/* 407fe1: call 0x49ec09 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407fe6: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0xfau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407fe9: cmp eax, 0xfa */
	if (!m->zf && m->sf == m->of) goto L_407ff4;	/* 407fee: jg 0x407ff4 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407ff0: cmp eax, ebx */
	if (m->sf == m->of) goto L_407ff9;	/* 407ff2: jge 0x407ff9 */
L_407ff4:
	m->eax = 0xfau;	/* 407ff4: mov eax, 0xfa */
L_407ff9:
	m->edi = M32(m->esp); m->esp += 4;	/* 407ff9: pop edi */
	M32((DWORD)(0x4db518u)) = m->ebx;	/* 407ffa: mov dword ptr [0x4db518], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 408000: pop esi */
	M8((DWORD)(0x4db54du)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 408001: mov byte ptr [0x4db54d], al */
	m->ebx = M32(m->esp); m->esp += 4;	/* 408006: pop ebx */
	m->esp += 4 + 0; return;	/* 408007: ret  */
L_408008:
	m->eax = M32((DWORD)(0x4e14f4u));	/* 408008: mov eax, dword ptr [0x4e14f4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40800d: push eax */
	m->esp -= 4; M32(m->esp) = 0x408013u; native_call(m, 0x401600u);	/* 40800e: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 408013: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 408016: test eax, eax */
	if (m->zf) goto L_408034;	/* 408018: je 0x408034 */
	{ DWORD a_ = M32((DWORD)(0x4ded54u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40801a: cmp dword ptr [0x4ded54], ebx */
	if (!m->zf) goto L_408034;	/* 408020: jne 0x408034 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 408022: push ebx */
	m->esp -= 4; M32(m->esp) = 0x408028u; native_call(m, 0x41e760u);	/* 408023: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 408028: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x408030u; native_call(m, 0x4052c0u);	/* 40802b: call 0x4052c0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 408030: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 408031: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 408032: pop ebx */
	m->esp += 4 + 0; return;	/* 408033: ret  */
L_408034:
	m->ecx = M32((DWORD)(0x4e1528u));	/* 408034: mov ecx, dword ptr [0x4e1528] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40803a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x408040u; native_call(m, 0x401600u);	/* 40803b: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 408040: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 408043: test eax, eax */
	if (m->zf) goto L_40806a;	/* 408045: je 0x40806a */
	{ DWORD a_ = M32((DWORD)(0x4ded54u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 408047: cmp dword ptr [0x4ded54], ebx */
	if (!m->zf) goto L_40806a;	/* 40804d: jne 0x40806a */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 40804f: push ebx */
	m->esp -= 4; M32(m->esp) = 0x408055u; native_call(m, 0x41e760u);	/* 408050: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 408055: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x40805du; native_call(m, 0x405cf0u);	/* 408058: call 0x405cf0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40805d: test eax, eax */
	if (!m->zf) goto L_4080b7;	/* 40805f: jne 0x4080b7 */
	m->esp -= 4; M32(m->esp) = 0x408066u; native_call(m, 0x4057a0u);	/* 408061: call 0x4057a0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 408066: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 408067: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 408068: pop ebx */
	m->esp += 4 + 0; return;	/* 408069: ret  */
L_40806a:
	m->edx = M32((DWORD)(0x4e0cdcu));	/* 40806a: mov edx, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 408070: push edx */
	m->esp -= 4; M32(m->esp) = 0x408076u; native_call(m, 0x401600u);	/* 408071: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 408076: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 408079: test eax, eax */
	if (m->zf) goto L_408091;	/* 40807b: je 0x408091 */
	m->esp -= 4; M32(m->esp) = 0x408082u; native_call(m, 0x452fe0u);	/* 40807d: call 0x452fe0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 408082: push ebx */
	M32((DWORD)(0x4dbb3cu)) = m->ebx;	/* 408083: mov dword ptr [0x4dbb3c], ebx */
	m->esp -= 4; M32(m->esp) = 0x40808eu; native_call(m, 0x41e760u);	/* 408089: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40808e: add esp, 4 */
L_408091:
	m->eax = M32((DWORD)(0x76d48cu));	/* 408091: mov eax, dword ptr [0x76d48c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 408096: push eax */
	m->esp -= 4; M32(m->esp) = 0x40809cu; native_call(m, 0x401600u);	/* 408097: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40809c: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40809f: test eax, eax */
	if (m->zf) goto L_4080b7;	/* 4080a1: je 0x4080b7 */
	m->esp -= 4; M32(m->esp) = 0x4080a8u; native_call(m, 0x452fe0u);	/* 4080a3: call 0x452fe0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4080a8: push ebx */
	M32((DWORD)(0x4dbb3cu)) = m->ebx;	/* 4080a9: mov dword ptr [0x4dbb3c], ebx */
	m->esp -= 4; M32(m->esp) = 0x4080b4u; native_call(m, 0x41e760u);	/* 4080af: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4080b4: add esp, 4 */
L_4080b7:
	m->edi = M32(m->esp); m->esp += 4;	/* 4080b7: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4080b8: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4080b9: pop ebx */
	m->esp += 4 + 0; return;	/* 4080ba: ret  */
}

/* arena_loadAndQuit (0x40d840), lifted by tools/lift.py */
static void lift_40d840(X86 *m)
{
	m->eax = M32((DWORD)(0x76d364u));	/* 40d840: mov eax, dword ptr [0x76d364] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40d845: push esi */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40d846: cmp eax, 1 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40d849: push edi */
	if (!m->zf) goto L_40d938;	/* 40d84a: jne 0x40d938 */
	{ DWORD v_ = 0x4ad5e4u; m->esp -= 4; M32(m->esp) = v_; }	/* 40d850: push 0x4ad5e4 */
	m->esp -= 4; M32(m->esp) = 0x40d85au; native_call(m, 0x40d4e0u);	/* 40d855: call 0x40d4e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40d85a: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40d85d: test eax, eax */
	if (!m->zf) goto L_40d86b;	/* 40d85f: jne 0x40d86b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40d861: push eax */
	m->esp -= 4; M32(m->esp) = 0x40d868u; native_call(m, M32(0x4a932cu));	/* 40d862: call dword ptr [0x4a932c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 40d868: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 40d869: pop esi */
	m->esp += 4 + 0; return;	/* 40d86a: ret  */
L_40d86b:
	m->ecx = 0x8u;	/* 40d86b: mov ecx, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40d870: xor eax, eax */
	m->edi = 0x4ded20u;	/* 40d872: mov edi, 0x4ded20 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 40d877: rep stosd dword ptr es:[edi], eax */
	m->edi = 0x5b191cu;	/* 40d879: mov edi, 0x5b191c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40d87e: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 40d881: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 40d883: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 40d885: sub edi, ecx */
	m->eax = m->ecx;	/* 40d887: mov eax, ecx */
	m->esi = m->edi;	/* 40d889: mov esi, edi */
	m->edi = 0x4ded20u;	/* 40d88b: mov edi, 0x4ded20 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 40d890: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40d893: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 40d895: mov ecx, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x5b1958u))) & 0xff) << 0);	/* 40d897: mov al, byte ptr [0x5b1958] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40d89c: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 40d89f: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40d8a1: xor ecx, ecx */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x1u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40d8a3: cmp al, 1 */
	M32((DWORD)(0x4ded46u)) = m->ecx;	/* 40d8a5: mov dword ptr [0x4ded46], ecx */
	M8((DWORD)(0x4ded4eu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 40d8ab: mov byte ptr [0x4ded4e], al */
	M32((DWORD)(0x4ded4au)) = m->ecx;	/* 40d8b0: mov dword ptr [0x4ded4a], ecx */
	if (!m->zf) goto L_40d8dd;	/* 40d8b6: jne 0x40d8dd */
	m->edi = 0x5b193cu;	/* 40d8b8: mov edi, 0x5b193c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40d8bd: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40d8c0: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 40d8c2: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 40d8c4: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 40d8c6: sub edi, ecx */
	m->edx = m->ecx;	/* 40d8c8: mov edx, ecx */
	m->esi = m->edi;	/* 40d8ca: mov esi, edi */
	m->edi = 0x4ded46u;	/* 40d8cc: mov edi, 0x4ded46 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 40d8d1: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40d8d4: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 40d8d6: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40d8d8: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 40d8db: rep movsb byte ptr es:[edi], byte ptr [esi] */
L_40d8dd:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x5b1950u))) & 0xff) << 0);	/* 40d8dd: mov al, byte ptr [0x5b1950] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x5b194cu))) & 0xff) << 0);	/* 40d8e2: mov cl, byte ptr [0x5b194c] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(0x5b1944u))) & 0xff) << 0);	/* 40d8e8: mov dl, byte ptr [0x5b1944] */
	M8((DWORD)(0x4ded44u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 40d8ee: mov byte ptr [0x4ded44], al */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x5b1948u))) & 0xff) << 0);	/* 40d8f3: mov al, byte ptr [0x5b1948] */
	M8((DWORD)(0x4ded43u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 40d8f8: mov byte ptr [0x4ded43], cl */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x5b1954u))) & 0xff) << 0);	/* 40d8fe: mov cl, byte ptr [0x5b1954] */
	M8((DWORD)(0x4ded42u)) = (BYTE)(0x0u);	/* 40d904: mov byte ptr [0x4ded42], 0 */
	M8((DWORD)(0x4ded40u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 40d90b: mov byte ptr [0x4ded40], dl */
	M8((DWORD)(0x4ded41u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 40d911: mov byte ptr [0x4ded41], al */
	M8((DWORD)(0x4ded45u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 40d916: mov byte ptr [0x4ded45], cl */
	m->esp -= 4; M32(m->esp) = 0x40d921u; native_call(m, 0x404640u);	/* 40d91c: call 0x404640 */
	m->esp -= 4; M32(m->esp) = 0x40d926u; native_call(m, 0x404b30u);	/* 40d921: call 0x404b30 */
	m->esp -= 4; M32(m->esp) = 0x40d92bu; native_call(m, 0x4057a0u);	/* 40d926: call 0x4057a0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 40d92b: pop edi */
	M32((DWORD)(0x9da49cu)) = 0x68u;	/* 40d92c: mov dword ptr [0x9da49c], 0x68 */
	m->esi = M32(m->esp); m->esp += 4;	/* 40d936: pop esi */
	m->esp += 4 + 0; return;	/* 40d937: ret  */
L_40d938:
	m->esp -= 4; M32(m->esp) = 0x40d93du; native_call(m, 0x404640u);	/* 40d938: call 0x404640 */
	m->esp -= 4; M32(m->esp) = 0x40d942u; native_call(m, 0x404b30u);	/* 40d93d: call 0x404b30 */
	m->ecx = 0x6u;	/* 40d942: mov ecx, 6 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40d947: xor eax, eax */
	m->edi = 0x4dbbd4u;	/* 40d949: mov edi, 0x4dbbd4 */
	{ DWORD v_ = 0x1869fu; m->esp -= 4; M32(m->esp) = v_; }	/* 40d94e: push 0x1869f */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 40d953: rep stosd dword ptr es:[edi], eax */
	m->edi = 0x4de748u;	/* 40d955: mov edi, 0x4de748 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40d95a: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 40d95d: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 40d95f: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 40d961: sub edi, ecx */
	m->edx = m->ecx;	/* 40d963: mov edx, ecx */
	m->esi = m->edi;	/* 40d965: mov esi, edi */
	m->edi = 0x4dbbd4u;	/* 40d967: mov edi, 0x4dbbd4 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 40d96c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40d96f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 40d971: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40d973: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 40d976: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x40d97du; native_call(m, 0x406200u);	/* 40d978: call 0x406200 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40d97d: add esp, 4 */
	M32((DWORD)(0x9da49cu)) = 0x69u;	/* 40d980: mov dword ptr [0x9da49c], 0x69 */
	m->edi = M32(m->esp); m->esp += 4;	/* 40d98a: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 40d98b: pop esi */
	m->esp += 4 + 0; return;	/* 40d98c: ret  */
}

/* room_43ea10 (0x43ea10), lifted by tools/lift.py */
static void lift_43ea10(X86 *m)
{
	m->eax = M32((DWORD)(0x9dd34cu));	/* 43ea10: mov eax, dword ptr [0x9dd34c] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ea15: push ebx */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 43ea16: xor ebx, ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43ea18: push esi */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43ea19: cmp eax, ebx */
	if (m->zf) goto L_43ea48;	/* 43ea1b: je 0x43ea48 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 43ea1d: fld dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x9dcd40u));	/* 43ea23: fadd dword ptr [0x9dcd40] */
	MF((DWORD)(0x9dcd40u)) = (float)ST(0);	/* 43ea29: fst dword ptr [0x9dcd40] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a944cu)); FPOP();	/* 43ea2f: fcomp dword ptr [0x4a944c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 43ea35: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 43ea37: test ah, 0x41 */
	if (!m->zf) goto L_43ea48;	/* 43ea3a: jne 0x43ea48 */
	M32((DWORD)(0x9dd34cu)) = m->ebx;	/* 43ea3c: mov dword ptr [0x9dd34c], ebx */
	M32((DWORD)(0x9dcd40u)) = m->ebx;	/* 43ea42: mov dword ptr [0x9dcd40], ebx */
L_43ea48:
	m->esp -= 4; M32(m->esp) = 0x43ea4du; native_call(m, 0x4388e0u);	/* 43ea48: call 0x4388e0 */
	m->eax = M32((DWORD)(0x9dce48u));	/* 43ea4d: mov eax, dword ptr [0x9dce48] */
	m->esi = 0x1u;	/* 43ea52: mov esi, 1 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43ea57: cmp eax, esi */
	if (m->zf) goto L_43ecfd;	/* 43ea59: je 0x43ecfd */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43ea5f: cmp eax, ebx */
	if (m->zf) goto L_43ecfd;	/* 43ea61: je 0x43ecfd */
	{ DWORD a_ = M32((DWORD)(0x9dd834u)), b_ = 0x63u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43ea67: cmp dword ptr [0x9dd834], 0x63 */
	if (m->zf) goto L_43ecfd;	/* 43ea6e: je 0x43ecfd */
	{ DWORD a_ = M32((DWORD)(0x90d1c4u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43ea74: cmp dword ptr [0x90d1c4], ebx */
	if (m->zf) goto L_43eaa1;	/* 43ea7a: je 0x43eaa1 */
	m->eax = M32((DWORD)(0x9dd4b4u));	/* 43ea7c: mov eax, dword ptr [0x9dd4b4] */
	m->ecx = M32((DWORD)(0x9dd4b0u));	/* 43ea81: mov ecx, dword ptr [0x9dd4b0] */
	m->edx = M32((DWORD)(0x9dd4acu));	/* 43ea87: mov edx, dword ptr [0x9dd4ac] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ea8d: push eax */
	m->eax = M32((DWORD)(0x9dd4a8u));	/* 43ea8e: mov eax, dword ptr [0x9dd4a8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ea93: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ea94: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ea95: push eax */
	m->esp -= 4; M32(m->esp) = 0x43ea9bu; native_call(m, 0x428c30u);	/* 43ea96: call 0x428c30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43ea9b: add esp, 0x10 */
	m->esi = M32(m->esp); m->esp += 4;	/* 43ea9e: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43ea9f: pop ebx */
	m->esp += 4 + 0; return;	/* 43eaa0: ret  */
L_43eaa1:
	{ DWORD a_ = M32((DWORD)(0x9dd6a0u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43eaa1: cmp dword ptr [0x9dd6a0], ebx */
	if (m->zf) goto L_43eb83;	/* 43eaa7: je 0x43eb83 */
	{ DWORD a_ = M32((DWORD)(0x9da498u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43eaad: cmp dword ptr [0x9da498], esi */
	if (!m->zf) goto L_43eb54;	/* 43eab3: jne 0x43eb54 */
	m->ecx = M32((DWORD)(0x76d484u));	/* 43eab9: mov ecx, dword ptr [0x76d484] */
	m->eax = (DWORD)(m->ecx + 0x1u);	/* 43eabf: lea eax, [ecx + 1] */
	{ DWORD a_ = m->eax, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43eac2: cmp eax, 5 */
	if (!m->cf && !m->zf) goto L_43eb42;	/* 43eac5: ja 0x43eb42 */
	switch (m->eax) { case 0: goto L_43eace; case 1: goto L_43eae2; case 2: goto L_43eaf8; case 3: goto L_43eb42; case 4: goto L_43eb0c; case 5: goto L_43eb26; default: abort(); }	/* 43eac7: jmp dword ptr [eax*4 + 0x43ed00] */
L_43eace:
	M32((DWORD)(0x4db858u)) = m->ebx;	/* 43eace: mov dword ptr [0x4db858], ebx */
	M32((DWORD)(0x4df018u)) = m->ebx;	/* 43ead4: mov dword ptr [0x4df018], ebx */
	M32((DWORD)(0x4db8b8u)) = m->ebx;	/* 43eada: mov dword ptr [0x4db8b8], ebx */
	goto L_43eb42;	/* 43eae0: jmp 0x43eb42 */
L_43eae2:
	M32((DWORD)(0x4db858u)) = m->ebx;	/* 43eae2: mov dword ptr [0x4db858], ebx */
	M32((DWORD)(0x4df018u)) = m->ebx;	/* 43eae8: mov dword ptr [0x4df018], ebx */
	M32((DWORD)(0x4db8b8u)) = m->ebx;	/* 43eaee: mov dword ptr [0x4db8b8], ebx */
	{ DWORD v_ = 0x40u; m->esp -= 4; M32(m->esp) = v_; }	/* 43eaf4: push 0x40 */
	goto L_43eb3a;	/* 43eaf6: jmp 0x43eb3a */
L_43eaf8:
	M32((DWORD)(0x4db858u)) = m->ebx;	/* 43eaf8: mov dword ptr [0x4db858], ebx */
	M32((DWORD)(0x4df018u)) = m->ebx;	/* 43eafe: mov dword ptr [0x4df018], ebx */
	M32((DWORD)(0x4db8b8u)) = m->esi;	/* 43eb04: mov dword ptr [0x4db8b8], esi */
	goto L_43eb42;	/* 43eb0a: jmp 0x43eb42 */
L_43eb0c:
	M32((DWORD)(0x4db858u)) = m->ebx;	/* 43eb0c: mov dword ptr [0x4db858], ebx */
	M32((DWORD)(0x4df018u)) = m->ebx;	/* 43eb12: mov dword ptr [0x4df018], ebx */
	M32((DWORD)(0x4db8b8u)) = m->ebx;	/* 43eb18: mov dword ptr [0x4db8b8], ebx */
	M32((DWORD)(0x907b2cu)) = m->esi;	/* 43eb1e: mov dword ptr [0x907b2c], esi */
	goto L_43eb42;	/* 43eb24: jmp 0x43eb42 */
L_43eb26:
	M32((DWORD)(0x4db858u)) = m->ebx;	/* 43eb26: mov dword ptr [0x4db858], ebx */
	M32((DWORD)(0x4df018u)) = m->ebx;	/* 43eb2c: mov dword ptr [0x4df018], ebx */
	M32((DWORD)(0x4db8b8u)) = m->ebx;	/* 43eb32: mov dword ptr [0x4db8b8], ebx */
	{ DWORD v_ = 0x2au; m->esp -= 4; M32(m->esp) = v_; }	/* 43eb38: push 0x2a */
L_43eb3a:
	m->esp -= 4; M32(m->esp) = 0x43eb3fu; native_call(m, 0x41ee40u);	/* 43eb3a: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43eb3f: add esp, 4 */
L_43eb42:
	M32((DWORD)(0x9dd6a0u)) = m->ebx;	/* 43eb42: mov dword ptr [0x9dd6a0], ebx */
	M32((DWORD)(0x9da498u)) = m->ebx;	/* 43eb48: mov dword ptr [0x9da498], ebx */
	M32((DWORD)(0x9dd3fcu)) = m->esi;	/* 43eb4e: mov dword ptr [0x9dd3fc], esi */
L_43eb54:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4ad498u)));	/* 43eb54: fld dword ptr [0x4ad498] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 43eb5a: fmul dword ptr [0x4b071c] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4dba80u));	/* 43eb60: fsubr dword ptr [0x4dba80] */
	MF((DWORD)(0x4dba80u)) = (float)ST(0);	/* 43eb66: fst dword ptr [0x4dba80] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9418u)); FPOP();	/* 43eb6c: fcomp dword ptr [0x4a9418] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 43eb72: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 43eb74: test ah, 1 */
	if (m->zf) goto L_43eb83;	/* 43eb77: je 0x43eb83 */
	M32((DWORD)(0x4dba80u)) = 0x447a0000u;	/* 43eb79: mov dword ptr [0x4dba80], 0x447a0000 */
L_43eb83:
	{ DWORD a_ = M32((DWORD)(0x9dd3fcu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43eb83: cmp dword ptr [0x9dd3fc], ebx */
	if (m->zf) goto L_43ec19;	/* 43eb89: je 0x43ec19 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x9dd6c0u)));	/* 43eb8f: fld dword ptr [0x9dd6c0] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 43eb95: fadd dword ptr [0x4b071c] */
	MF((DWORD)(0x9dd6c0u)) = (float)ST(0);	/* 43eb9b: fst dword ptr [0x9dd6c0] */
	FPUSH((long double)(int)M32((DWORD)(0x5b1914u)));	/* 43eba1: fild dword ptr [0x5b1914] */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 43eba7: fxch st(1) */
	FCOM(ST(0), ST(1)); FPOP(); FPOP();	/* 43eba9: fcompp  */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 43ebab: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 43ebad: test ah, 0x41 */
	if (!m->zf) goto L_43ebcb;	/* 43ebb0: jne 0x43ebcb */
	m->esp -= 4; M32(m->esp) = 0x43ebb7u; native_call(m, 0x434ff0u);	/* 43ebb2: call 0x434ff0 */
	M32((DWORD)(0x9dd6c0u)) = 0x0u;	/* 43ebb7: mov dword ptr [0x9dd6c0], 0 */
	M32((DWORD)(0x5b1914u)) = 0x5u;	/* 43ebc1: mov dword ptr [0x5b1914], 5 */
L_43ebcb:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4ad498u)));	/* 43ebcb: fld dword ptr [0x4ad498] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 43ebd1: fmul dword ptr [0x4b071c] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4dba80u));	/* 43ebd7: fsubr dword ptr [0x4dba80] */
	MF((DWORD)(0x4dba80u)) = (float)ST(0);	/* 43ebdd: fst dword ptr [0x4dba80] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9418u)); FPOP();	/* 43ebe3: fcomp dword ptr [0x4a9418] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 43ebe9: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 43ebeb: test ah, 1 */
	if (m->zf) goto L_43ebfa;	/* 43ebee: je 0x43ebfa */
	M32((DWORD)(0x4dba80u)) = 0x447a0000u;	/* 43ebf0: mov dword ptr [0x4dba80], 0x447a0000 */
L_43ebfa:
	{ DWORD a_ = M32((DWORD)(0xa0d7a0u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43ebfa: cmp dword ptr [0xa0d7a0], ebx */
	if (m->zf) goto L_43ec19;	/* 43ec00: je 0x43ec19 */
	m->esp -= 4; M32(m->esp) = 0x43ec07u; native_call(m, 0x434ff0u);	/* 43ec02: call 0x434ff0 */
	M32((DWORD)(0x9dd6a0u)) = m->ebx;	/* 43ec07: mov dword ptr [0x9dd6a0], ebx */
	M32((DWORD)(0x9da498u)) = m->ebx;	/* 43ec0d: mov dword ptr [0x9da498], ebx */
	M32((DWORD)(0x9dd3fcu)) = m->ebx;	/* 43ec13: mov dword ptr [0x9dd3fc], ebx */
L_43ec19:
	m->esp -= 4; M32(m->esp) = 0x43ec1eu; native_call(m, 0x43adc0u);	/* 43ec19: call 0x43adc0 */
	{ DWORD a_ = M32((DWORD)(0x9dd56cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43ec1e: cmp dword ptr [0x9dd56c], ebx */
	if (m->zf) goto L_43ecfd;	/* 43ec24: je 0x43ecfd */
	{ DWORD a_ = M32((DWORD)(0x9dd6b4u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43ec2a: cmp dword ptr [0x9dd6b4], ebx */
	if (m->zf) goto L_43ecef;	/* 43ec30: je 0x43ecef */
	{ DWORD a_ = M32((DWORD)(0x9dd6c8u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43ec36: cmp dword ptr [0x9dd6c8], ebx */
	if (m->zf) goto L_43ecfd;	/* 43ec3c: je 0x43ecfd */
	{ DWORD a_ = M32((DWORD)(0x68039cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43ec42: cmp dword ptr [0x68039c], ebx */
	if (!m->zf) goto L_43ecfd;	/* 43ec48: jne 0x43ecfd */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43ec4e: push edi */
	m->edi = 0x9dc92cu;	/* 43ec4f: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43ec54: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43ec57: xor eax, eax */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43ec59: xor edx, edx */
	M32((DWORD)(0x9dd6c8u)) = m->ebx;	/* 43ec5b: mov dword ptr [0x9dd6c8], ebx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43ec61: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43ec63: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43ec65: sub edi, ecx */
	M32((DWORD)(0x9dcee8u)) = m->edx;	/* 43ec67: mov dword ptr [0x9dcee8], edx */
	m->eax = m->ecx;	/* 43ec6d: mov eax, ecx */
	m->esi = m->edi;	/* 43ec6f: mov esi, edi */
	m->edi = 0x9dcee8u;	/* 43ec71: mov edi, 0x9dcee8 */
	M32((DWORD)(0x9dceecu)) = m->edx;	/* 43ec76: mov dword ptr [0x9dceec], edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43ec7c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43ec7f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 43ec81: mov ecx, eax */
	m->eax = M32((DWORD)(0x76d41cu));	/* 43ec83: mov eax, dword ptr [0x76d41c] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43ec88: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43ec8b: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 43ec8d: lea ecx, [eax + eax*8] */
	m->esi = 0x9dcee8u;	/* 43ec90: mov esi, 0x9dcee8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 43ec95: pop edi */
	m->edx = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 43ec96: lea edx, [eax + ecx*4] */
	m->eax = (DWORD)(m->edx*2 + 0x9087ffu);	/* 43ec99: lea eax, [edx*2 + 0x9087ff] */
L_43eca0:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 43eca0: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 43eca2: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 43eca4: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_43ecc4;	/* 43eca6: jne 0x43ecc4 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 43eca8: cmp cl, bl */
	if (m->zf) goto L_43ecc0;	/* 43ecaa: je 0x43ecc0 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 43ecac: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 43ecaf: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 43ecb1: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_43ecc4;	/* 43ecb4: jne 0x43ecc4 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43ecb6: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 43ecb9: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 43ecbc: cmp cl, bl */
	if (!m->zf) goto L_43eca0;	/* 43ecbe: jne 0x43eca0 */
L_43ecc0:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43ecc0: xor eax, eax */
	goto L_43ecc9;	/* 43ecc2: jmp 0x43ecc9 */
L_43ecc4:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 43ecc4: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 43ecc6: sbb eax, -1 */
L_43ecc9:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43ecc9: cmp eax, ebx */
	if (!m->zf) goto L_43ecd6;	/* 43eccb: jne 0x43ecd6 */
	M32((DWORD)(0x9dd6b4u)) = m->ebx;	/* 43eccd: mov dword ptr [0x9dd6b4], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 43ecd3: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43ecd4: pop ebx */
	m->esp += 4 + 0; return;	/* 43ecd5: ret  */
L_43ecd6:
	{ DWORD v_ = 0x27u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ecd6: push 0x27 */
	M32((DWORD)(0x9dd56cu)) = m->ebx;	/* 43ecd8: mov dword ptr [0x9dd56c], ebx */
	M32((DWORD)(0x9dd6b4u)) = m->ebx;	/* 43ecde: mov dword ptr [0x9dd6b4], ebx */
	m->esp -= 4; M32(m->esp) = 0x43ece9u; native_call(m, 0x41ee40u);	/* 43ece4: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43ece9: add esp, 4 */
	m->esi = M32(m->esp); m->esp += 4;	/* 43ecec: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43eced: pop ebx */
	m->esp += 4 + 0; return;	/* 43ecee: ret  */
L_43ecef:
	m->eax = M32((DWORD)(0x76d41cu));	/* 43ecef: mov eax, dword ptr [0x76d41c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ecf4: push eax */
	m->esp -= 4; M32(m->esp) = 0x43ecfau; native_call(m, 0x434dd0u);	/* 43ecf5: call 0x434dd0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43ecfa: add esp, 4 */
L_43ecfd:
	m->esi = M32(m->esp); m->esp += 4;	/* 43ecfd: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43ecfe: pop ebx */
	m->esp += 4 + 0; return;	/* 43ecff: ret  */
}

/* lobbyJoin_draw (0x40cfd0), lifted by tools/lift.py */
static void lift_40cfd0(X86 *m)
{
	m->eax = M32((DWORD)(0x4db71cu));	/* 40cfd0: mov eax, dword ptr [0x4db71c] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 40cfd5: push ebx */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 40cfd6: xor ebx, ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40cfd8: push esi */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40cfd9: cmp eax, ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40cfdb: push edi */
	if (m->zf) goto L_40d009;	/* 40cfdc: je 0x40d009 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 40cfde: fld dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4dbaf8u));	/* 40cfe4: fadd dword ptr [0x4dbaf8] */
	MF((DWORD)(0x4dbaf8u)) = (float)ST(0);	/* 40cfea: fst dword ptr [0x4dbaf8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a944cu)); FPOP();	/* 40cff0: fcomp dword ptr [0x4a944c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 40cff6: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40cff8: test ah, 0x41 */
	if (!m->zf) goto L_40d009;	/* 40cffb: jne 0x40d009 */
	M32((DWORD)(0x4db71cu)) = m->ebx;	/* 40cffd: mov dword ptr [0x4db71c], ebx */
	M32((DWORD)(0x4dbaf8u)) = m->ebx;	/* 40d003: mov dword ptr [0x4dbaf8], ebx */
L_40d009:
	m->esp -= 4; M32(m->esp) = 0x40d00eu; native_call(m, 0x4091b0u);	/* 40d009: call 0x4091b0 */
	m->eax = M32((DWORD)(0x4dbb3cu));	/* 40d00e: mov eax, dword ptr [0x4dbb3c] */
	m->edi = 0x1u;	/* 40d013: mov edi, 1 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40d018: cmp eax, edi */
	if (m->zf) goto L_40d36f;	/* 40d01a: je 0x40d36f */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40d020: cmp eax, ebx */
	if (m->zf) goto L_40d36f;	/* 40d022: je 0x40d36f */
	{ DWORD a_ = M32((DWORD)(0x4db51cu)), b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40d028: cmp dword ptr [0x4db51c], 5 */
	if (m->zf) goto L_40d36f;	/* 40d02f: je 0x40d36f */
	{ DWORD a_ = M32((DWORD)(0x90d1c4u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40d035: cmp dword ptr [0x90d1c4], ebx */
	if (m->zf) goto L_40d063;	/* 40d03b: je 0x40d063 */
	m->eax = M32((DWORD)(0x4db8d4u));	/* 40d03d: mov eax, dword ptr [0x4db8d4] */
	m->ecx = M32((DWORD)(0x4db8d0u));	/* 40d042: mov ecx, dword ptr [0x4db8d0] */
	m->edx = M32((DWORD)(0x4db8ccu));	/* 40d048: mov edx, dword ptr [0x4db8cc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40d04e: push eax */
	m->eax = M32((DWORD)(0x4db8c8u));	/* 40d04f: mov eax, dword ptr [0x4db8c8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40d054: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40d055: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40d056: push eax */
	m->esp -= 4; M32(m->esp) = 0x40d05cu; native_call(m, 0x428c30u);	/* 40d057: call 0x428c30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40d05c: add esp, 0x10 */
	m->edi = M32(m->esp); m->esp += 4;	/* 40d05f: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 40d060: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 40d061: pop ebx */
	m->esp += 4 + 0; return;	/* 40d062: ret  */
L_40d063:
	{ DWORD a_ = M32((DWORD)(0x4dba90u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40d063: cmp dword ptr [0x4dba90], ebx */
	if (m->zf) goto L_40d0a8;	/* 40d069: je 0x40d0a8 */
	m->esi = 0xau;	/* 40d06b: mov esi, 0xa */
L_40d070:
	m->esp -= 4; M32(m->esp) = 0x40d075u; native_call(m, 0x453260u);	/* 40d070: call 0x453260 */
	{ DWORD a_ = m->esi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->esi = r_; }	/* 40d075: dec esi */
	if (!m->zf) goto L_40d070;	/* 40d076: jne 0x40d070 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4ad498u)));	/* 40d078: fld dword ptr [0x4ad498] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 40d07e: fmul dword ptr [0x4b071c] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4dba80u));	/* 40d084: fsubr dword ptr [0x4dba80] */
	MF((DWORD)(0x4dba80u)) = (float)ST(0);	/* 40d08a: fst dword ptr [0x4dba80] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 40d090: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 40d096: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40d098: test ah, 0x41 */
	if (m->zf) goto L_40d0a8;	/* 40d09b: je 0x40d0a8 */
	m->esp -= 4; M32(m->esp) = 0x40d0a2u; native_call(m, 0x406810u);	/* 40d09d: call 0x406810 */
	M32((DWORD)(0x4dba90u)) = m->ebx;	/* 40d0a2: mov dword ptr [0x4dba90], ebx */
L_40d0a8:
	{ DWORD a_ = M32((DWORD)(0x4db858u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40d0a8: cmp dword ptr [0x4db858], ebx */
	if (m->zf) goto L_40d178;	/* 40d0ae: je 0x40d178 */
	{ DWORD a_ = M32((DWORD)(0x4df018u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40d0b4: cmp dword ptr [0x4df018], edi */
	if (!m->zf) goto L_40d149;	/* 40d0ba: jne 0x40d149 */
	m->ecx = M32((DWORD)(0x76d484u));	/* 40d0c0: mov ecx, dword ptr [0x76d484] */
	m->eax = (DWORD)(m->ecx + 0x1u);	/* 40d0c6: lea eax, [ecx + 1] */
	{ DWORD a_ = m->eax, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40d0c9: cmp eax, 5 */
	if (!m->cf && !m->zf) goto L_40d149;	/* 40d0cc: ja 0x40d149 */
	switch (m->eax) { case 0: goto L_40d0d5; case 1: goto L_40d0e9; case 2: goto L_40d0ff; case 3: goto L_40d149; case 4: goto L_40d113; case 5: goto L_40d12d; default: abort(); }	/* 40d0ce: jmp dword ptr [eax*4 + 0x40d374] */
L_40d0d5:
	M32((DWORD)(0x4db858u)) = m->ebx;	/* 40d0d5: mov dword ptr [0x4db858], ebx */
	M32((DWORD)(0x4df018u)) = m->ebx;	/* 40d0db: mov dword ptr [0x4df018], ebx */
	M32((DWORD)(0x4db8b8u)) = m->ebx;	/* 40d0e1: mov dword ptr [0x4db8b8], ebx */
	goto L_40d149;	/* 40d0e7: jmp 0x40d149 */
L_40d0e9:
	M32((DWORD)(0x4db858u)) = m->ebx;	/* 40d0e9: mov dword ptr [0x4db858], ebx */
	M32((DWORD)(0x4df018u)) = m->ebx;	/* 40d0ef: mov dword ptr [0x4df018], ebx */
	M32((DWORD)(0x4db8b8u)) = m->ebx;	/* 40d0f5: mov dword ptr [0x4db8b8], ebx */
	{ DWORD v_ = 0x40u; m->esp -= 4; M32(m->esp) = v_; }	/* 40d0fb: push 0x40 */
	goto L_40d141;	/* 40d0fd: jmp 0x40d141 */
L_40d0ff:
	M32((DWORD)(0x4db858u)) = m->ebx;	/* 40d0ff: mov dword ptr [0x4db858], ebx */
	M32((DWORD)(0x4df018u)) = m->ebx;	/* 40d105: mov dword ptr [0x4df018], ebx */
	M32((DWORD)(0x4db8b8u)) = m->edi;	/* 40d10b: mov dword ptr [0x4db8b8], edi */
	goto L_40d149;	/* 40d111: jmp 0x40d149 */
L_40d113:
	M32((DWORD)(0x4db858u)) = m->ebx;	/* 40d113: mov dword ptr [0x4db858], ebx */
	M32((DWORD)(0x4df018u)) = m->ebx;	/* 40d119: mov dword ptr [0x4df018], ebx */
	M32((DWORD)(0x4db8b8u)) = m->ebx;	/* 40d11f: mov dword ptr [0x4db8b8], ebx */
	M32((DWORD)(0x907b2cu)) = m->edi;	/* 40d125: mov dword ptr [0x907b2c], edi */
	goto L_40d149;	/* 40d12b: jmp 0x40d149 */
L_40d12d:
	M32((DWORD)(0x4db858u)) = m->ebx;	/* 40d12d: mov dword ptr [0x4db858], ebx */
	M32((DWORD)(0x4df018u)) = m->ebx;	/* 40d133: mov dword ptr [0x4df018], ebx */
	M32((DWORD)(0x4db8b8u)) = m->ebx;	/* 40d139: mov dword ptr [0x4db8b8], ebx */
	{ DWORD v_ = 0x46u; m->esp -= 4; M32(m->esp) = v_; }	/* 40d13f: push 0x46 */
L_40d141:
	m->esp -= 4; M32(m->esp) = 0x40d146u; native_call(m, 0x41ee40u);	/* 40d141: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40d146: add esp, 4 */
L_40d149:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4ad498u)));	/* 40d149: fld dword ptr [0x4ad498] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 40d14f: fmul dword ptr [0x4b071c] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4dba80u));	/* 40d155: fsubr dword ptr [0x4dba80] */
	MF((DWORD)(0x4dba80u)) = (float)ST(0);	/* 40d15b: fst dword ptr [0x4dba80] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9418u)); FPOP();	/* 40d161: fcomp dword ptr [0x4a9418] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 40d167: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40d169: test ah, 1 */
	if (m->zf) goto L_40d178;	/* 40d16c: je 0x40d178 */
	M32((DWORD)(0x4dba80u)) = 0x447a0000u;	/* 40d16e: mov dword ptr [0x4dba80], 0x447a0000 */
L_40d178:
	{ DWORD a_ = M32((DWORD)(0x4db8b8u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40d178: cmp dword ptr [0x4db8b8], ebx */
	if (m->zf) goto L_40d20e;	/* 40d17e: je 0x40d20e */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dbaf0u)));	/* 40d184: fld dword ptr [0x4dbaf0] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 40d18a: fadd dword ptr [0x4b071c] */
	MF((DWORD)(0x4dbaf0u)) = (float)ST(0);	/* 40d190: fst dword ptr [0x4dbaf0] */
	FPUSH((long double)(int)M32((DWORD)(0x5b1914u)));	/* 40d196: fild dword ptr [0x5b1914] */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 40d19c: fxch st(1) */
	FCOM(ST(0), ST(1)); FPOP(); FPOP();	/* 40d19e: fcompp  */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 40d1a0: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40d1a2: test ah, 0x41 */
	if (!m->zf) goto L_40d1c0;	/* 40d1a5: jne 0x40d1c0 */
	m->esp -= 4; M32(m->esp) = 0x40d1acu; native_call(m, 0x406640u);	/* 40d1a7: call 0x406640 */
	M32((DWORD)(0x4dbaf0u)) = 0x0u;	/* 40d1ac: mov dword ptr [0x4dbaf0], 0 */
	M32((DWORD)(0x5b1914u)) = 0x5u;	/* 40d1b6: mov dword ptr [0x5b1914], 5 */
L_40d1c0:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4ad498u)));	/* 40d1c0: fld dword ptr [0x4ad498] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 40d1c6: fmul dword ptr [0x4b071c] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4dba80u));	/* 40d1cc: fsubr dword ptr [0x4dba80] */
	MF((DWORD)(0x4dba80u)) = (float)ST(0);	/* 40d1d2: fst dword ptr [0x4dba80] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9418u)); FPOP();	/* 40d1d8: fcomp dword ptr [0x4a9418] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 40d1de: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40d1e0: test ah, 1 */
	if (m->zf) goto L_40d1ef;	/* 40d1e3: je 0x40d1ef */
	M32((DWORD)(0x4dba80u)) = 0x447a0000u;	/* 40d1e5: mov dword ptr [0x4dba80], 0x447a0000 */
L_40d1ef:
	{ DWORD a_ = M32((DWORD)(0xa0d7a0u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40d1ef: cmp dword ptr [0xa0d7a0], ebx */
	if (m->zf) goto L_40d20e;	/* 40d1f5: je 0x40d20e */
	m->esp -= 4; M32(m->esp) = 0x40d1fcu; native_call(m, 0x406640u);	/* 40d1f7: call 0x406640 */
	M32((DWORD)(0x4db858u)) = m->ebx;	/* 40d1fc: mov dword ptr [0x4db858], ebx */
	M32((DWORD)(0x4df018u)) = m->ebx;	/* 40d202: mov dword ptr [0x4df018], ebx */
	M32((DWORD)(0x4db8b8u)) = m->ebx;	/* 40d208: mov dword ptr [0x4db8b8], ebx */
L_40d20e:
	m->esp -= 4; M32(m->esp) = 0x40d213u; native_call(m, 0x40a070u);	/* 40d20e: call 0x40a070 */
	{ DWORD a_ = M32((DWORD)(0x4dbbecu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40d213: cmp dword ptr [0x4dbbec], ebx */
	if (m->zf) goto L_40d2f6;	/* 40d219: je 0x40d2f6 */
	{ DWORD a_ = M32((DWORD)(0x4db8bcu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40d21f: cmp dword ptr [0x4db8bc], ebx */
	if (m->zf) goto L_40d2e4;	/* 40d225: je 0x40d2e4 */
	{ DWORD a_ = M32((DWORD)(0x4db70cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40d22b: cmp dword ptr [0x4db70c], ebx */
	if (m->zf) goto L_40d36f;	/* 40d231: je 0x40d36f */
	{ DWORD a_ = M32((DWORD)(0x68039cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40d237: cmp dword ptr [0x68039c], ebx */
	if (!m->zf) goto L_40d36f;	/* 40d23d: jne 0x40d36f */
	m->edi = 0x9dc92cu;	/* 40d243: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40d248: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40d24b: xor eax, eax */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 40d24d: xor edx, edx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 40d24f: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 40d251: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 40d253: sub edi, ecx */
	M32((DWORD)(0x4db520u)) = m->edx;	/* 40d255: mov dword ptr [0x4db520], edx */
	m->eax = m->ecx;	/* 40d25b: mov eax, ecx */
	m->esi = m->edi;	/* 40d25d: mov esi, edi */
	m->edi = 0x4db520u;	/* 40d25f: mov edi, 0x4db520 */
	M32((DWORD)(0x4db524u)) = m->edx;	/* 40d264: mov dword ptr [0x4db524], edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 40d26a: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40d26d: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 40d26f: mov ecx, eax */
	m->eax = M32((DWORD)(0x76d41cu));	/* 40d271: mov eax, dword ptr [0x76d41c] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40d276: and ecx, 3 */
	M32((DWORD)(0x4db70cu)) = m->ebx;	/* 40d279: mov dword ptr [0x4db70c], ebx */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 40d27f: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 40d281: lea ecx, [eax + eax*8] */
	m->esi = 0x4db520u;	/* 40d284: mov esi, 0x4db520 */
	m->edx = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 40d289: lea edx, [eax + ecx*4] */
	m->eax = (DWORD)(m->edx*2 + 0x9087ffu);	/* 40d28c: lea eax, [edx*2 + 0x9087ff] */
L_40d293:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 40d293: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 40d295: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40d297: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_40d2b7;	/* 40d299: jne 0x40d2b7 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40d29b: cmp cl, bl */
	if (m->zf) goto L_40d2b3;	/* 40d29d: je 0x40d2b3 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 40d29f: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 40d2a2: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40d2a4: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_40d2b7;	/* 40d2a7: jne 0x40d2b7 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40d2a9: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 40d2ac: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40d2af: cmp cl, bl */
	if (!m->zf) goto L_40d293;	/* 40d2b1: jne 0x40d293 */
L_40d2b3:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40d2b3: xor eax, eax */
	goto L_40d2bc;	/* 40d2b5: jmp 0x40d2bc */
L_40d2b7:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 40d2b7: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 40d2b9: sbb eax, -1 */
L_40d2bc:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40d2bc: cmp eax, ebx */
	if (!m->zf) goto L_40d2ca;	/* 40d2be: jne 0x40d2ca */
	m->edi = M32(m->esp); m->esp += 4;	/* 40d2c0: pop edi */
	M32((DWORD)(0x4db8bcu)) = m->ebx;	/* 40d2c1: mov dword ptr [0x4db8bc], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 40d2c7: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 40d2c8: pop ebx */
	m->esp += 4 + 0; return;	/* 40d2c9: ret  */
L_40d2ca:
	{ DWORD v_ = 0x27u; m->esp -= 4; M32(m->esp) = v_; }	/* 40d2ca: push 0x27 */
	M32((DWORD)(0x4dbbecu)) = m->ebx;	/* 40d2cc: mov dword ptr [0x4dbbec], ebx */
	M32((DWORD)(0x4db8bcu)) = m->ebx;	/* 40d2d2: mov dword ptr [0x4db8bc], ebx */
	m->esp -= 4; M32(m->esp) = 0x40d2ddu; native_call(m, 0x41ee40u);	/* 40d2d8: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40d2dd: add esp, 4 */
	m->edi = M32(m->esp); m->esp += 4;	/* 40d2e0: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 40d2e1: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 40d2e2: pop ebx */
	m->esp += 4 + 0; return;	/* 40d2e3: ret  */
L_40d2e4:
	m->eax = M32((DWORD)(0x76d41cu));	/* 40d2e4: mov eax, dword ptr [0x76d41c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40d2e9: push eax */
	m->esp -= 4; M32(m->esp) = 0x40d2efu; native_call(m, 0x406200u);	/* 40d2ea: call 0x406200 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40d2ef: add esp, 4 */
	m->edi = M32(m->esp); m->esp += 4;	/* 40d2f2: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 40d2f3: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 40d2f4: pop ebx */
	m->esp += 4 + 0; return;	/* 40d2f5: ret  */
L_40d2f6:
	{ DWORD a_ = M32((DWORD)(0x4db714u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40d2f6: cmp dword ptr [0x4db714], ebx */
	if (m->zf) goto L_40d359;	/* 40d2fc: je 0x40d359 */
	{ DWORD a_ = M32((DWORD)(0x68039cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40d2fe: cmp dword ptr [0x68039c], ebx */
	if (!m->zf) goto L_40d36f;	/* 40d304: jne 0x40d36f */
	m->ecx = 0x6u;	/* 40d306: mov ecx, 6 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40d30b: xor eax, eax */
	m->edi = 0x4dbbd4u;	/* 40d30d: mov edi, 0x4dbbd4 */
	M32((DWORD)(0x4db714u)) = m->ebx;	/* 40d312: mov dword ptr [0x4db714], ebx */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 40d318: rep stosd dword ptr es:[edi], eax */
	m->edi = 0x9dc92cu;	/* 40d31a: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40d31f: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 40d322: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 40d324: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 40d326: sub edi, ecx */
	m->edx = m->ecx;	/* 40d328: mov edx, ecx */
	m->esi = m->edi;	/* 40d32a: mov esi, edi */
	m->edi = 0x4dbbd4u;	/* 40d32c: mov edi, 0x4dbbd4 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 40d331: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40d334: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 40d336: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40d338: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 40d33b: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4dbbd4u;	/* 40d33d: mov edi, 0x4dbbd4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40d342: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 40d345: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 40d347: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 40d349: dec ecx */
	if (m->zf) goto L_40d359;	/* 40d34a: je 0x40d359 */
	{ DWORD v_ = 0x1869fu; m->esp -= 4; M32(m->esp) = v_; }	/* 40d34c: push 0x1869f */
	m->esp -= 4; M32(m->esp) = 0x40d356u; native_call(m, 0x406200u);	/* 40d351: call 0x406200 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40d356: add esp, 4 */
L_40d359:
	{ DWORD a_ = M32((DWORD)(0x4dbbf0u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40d359: cmp dword ptr [0x4dbbf0], ebx */
	if (m->zf) goto L_40d36f;	/* 40d35f: je 0x40d36f */
	m->eax = M32((DWORD)(0x76d41cu));	/* 40d361: mov eax, dword ptr [0x76d41c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40d366: push eax */
	m->esp -= 4; M32(m->esp) = 0x40d36cu; native_call(m, 0x405690u);	/* 40d367: call 0x405690 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40d36c: add esp, 4 */
L_40d36f:
	m->edi = M32(m->esp); m->esp += 4;	/* 40d36f: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 40d370: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 40d371: pop ebx */
	m->esp += 4 + 0; return;	/* 40d372: ret  */
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
