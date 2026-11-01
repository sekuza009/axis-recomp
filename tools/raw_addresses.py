r"""raw_addresses.py [kind...]: the addresses of the game's image (0x401000 .. 0xb6b000) still written as plain numbers
in src/ (not IMG(), not a function's FN_ADDR, not an offset after + or -), by where they stand. Inside a macro that
relocates (GAME_VAR, IMPORT, GAME_CDECL, K()...) they are fine; elsewhere each one is either a number that is no
address, or a value that reaches the image only through GAME_VAR / RELOC later. With kinds, examples of those."""
import collections, glob, os, re, sys

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
c = collections.Counter(); ex = collections.defaultdict(list)
for f in glob.glob('src/**/*.[ch]', recursive=True):
	if os.path.basename(os.path.dirname(f)) == 'data' or f.endswith(('globals.h', 'scene.h', 'axis.h')):
		continue
	t = open(f, encoding='latin-1').read()
	mask = re.sub(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\\n])*"', lambda m: ' ' * len(m.group(0)), t, flags=re.S)
	for line in mask.split('\n'):
		for m in re.finditer(r'(?<![\w.(])0x0*([0-9a-f]{6,7})\b', line):
			a = int(m.group(1), 16)
			if not 0x401000 <= a < 0xb6b000:
				continue
			pre = line[:m.start()]
			if re.search(r'IMG\(\s*$|FN_ADDR\(\w+,\s*$|FN_VIA\(|GAME_(?:THIS)?FN\(\w+,\s*$|\bcase\s*$|[-+]\s*$', pre):
				continue
			if re.search(r'\b(GAME_VAR|IMPORT|GAME_CDECL|GAME_THISCALL|PATCHED_CALL|PATCHED_THISCALL|code_matches|K|F|T|FMT)\([^()]*$', pre):
				k = 'inside a relocating macro'
			elif re.search(r'\b[A-Z]\w*\([^()]*,\s*$', pre): k = 'macro argument (offset?)'
			elif re.search(r'[{,]\s*$', pre): k = 'table / later argument'
			elif re.search(r'(=|return)\s*$', pre): k = 'assigned'
			elif re.search(r'(<|>|==|!=)\s*$', pre): k = 'compared'
			elif re.search(r'\(\s*$', pre): k = 'first argument'
			else: k = 'other'
			c[k] += 1; ex[k].append(f.replace('\\', '/').split('src/')[-1] + ': ' + line.strip()[:130])
print(dict(c))
for k in sys.argv[1:]:
	print('==', k); print('\n'.join(ex[k][:int(os.environ.get('N', '12'))]))
