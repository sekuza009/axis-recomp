"""port_scan.py: what ties src/ (not src/data) to Windows, the x86 / x87 build, the original's memory layout and the
test harness - counts per kind, with the files that have the most. The portable branch works these down."""
import collections, glob, os, re

R = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
PAT = {
	'Windows / GL / net API calls (IMPORT_FN)': r'\bIMPORT_FN\(',
	'DirectX / DirectPlay COM calls (COM)': r'\bCOM\(',
	'inline assembly (__asm__)': r'__asm__',
	'x87 maths helpers (fld_m, FMUL ...)': r'\b(?:fld_m|fmul_m|fadd_m|fsub_m|fdiv_m|fsubr_m|fdivr_m|FMUL|FADD|FSUB|FDIV)\(',
	'stdcall / thiscall conventions': r'\b(?:STDCALL|THISCALL)\b',
	'addresses as u32 (ADDR / OBJ)': r'\b(?:ADDR|OBJ)\(',
	'fixed-address access (GAME_VAR / RELOC / IMG)': r'\b(?:GAME_VAR|RELOC|IMG)\(',
	'original strings by address (STR)': r'\bSTR\(0x',
	'harness / patch-layer paths (#if AXIS_DIRECT / NATIVE)': r'#\s*(?:if|ifdef|ifndef|elif)\b[^\n]*AXIS_(?:DIRECT|NATIVE)',
	'patch DLL call sites (PATCHED_ / SITE_)': r'\b(?:PATCHED_\w+|SITE_\w+)\(',
}

tot = collections.Counter()
per = collections.defaultdict(collections.Counter)
for f in glob.glob(os.path.join(R, 'src', '**', '*.[ch]'), recursive=True):
	rel = os.path.relpath(f, os.path.join(R, 'src')).replace(os.sep, '/')
	if rel.startswith('data/'):
		continue
	t = open(f, encoding='latin-1').read()
	for k, p in PAT.items():
		n = len(re.findall(p, t))
		if n:
			tot[k] += n
			per[k][rel] += n
for k in PAT:
	print('%6d in %3d files  %s' % (tot[k], len(per[k]), k))
	print('        ' + ', '.join('%s=%d' % x for x in per[k].most_common(5)))
