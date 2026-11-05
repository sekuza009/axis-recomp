r"""addr_access.py addr|name... [--range=n]: every instruction of the original (installed.exe's code) that touches an
address, as read / write / address-taken (lea, push of the address, mov reg, imm), by disassembling each function of
decomp/out/functions.csv. A name is looked up in src/globals.h. --range=n: also accesses within n bytes after it
(an array or a record reached through its first element). For checking that a global is really unread before
naming it unused, or what its readers are."""
import csv, os, re, struct, sys
import capstone
from capstone import x86

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
b = open('installed.exe', 'rb').read()
pe = struct.unpack_from('<I', b, 0x3c)[0]
nsec = struct.unpack_from('<H', b, pe + 6)[0]
opt = struct.unpack_from('<H', b, pe + 20)[0]
secs = [struct.unpack_from('<8sIIII', b, pe + 24 + opt + 40 * k) for k in range(nsec)]


def off(a):
	for nm, vs, va, rs, rp in secs:
		if 0x400000 + va <= a < 0x400000 + va + rs:
			return rp + a - 0x400000 - va
	return None


g = open('src/globals.h', encoding='latin-1').read()
names = {m.group(1): int(m.group(2), 16) for m in re.finditer(r'^#define (\w+) GAME_VAR\([^,]+, (0x[0-9a-f]+)\)', g, re.M)}
rng = 0
targets = []
for a in sys.argv[1:]:
	if a.startswith('--range='):
		rng = int(a.split('=')[1], 0)
	elif re.fullmatch(r'0x[0-9a-fA-F]+', a):
		targets.append((a, int(a, 16)))
	elif a in names:
		targets.append((a, names[a]))
	else:
		print('unknown', a)

funcs = [(int(r['address'], 16), int(r['size']), r['name']) for r in csv.DictReader(open('../decomp/out/functions.csv'))]
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
md.detail = True
hits = {t: [] for t in targets}
for start, size, fname in funcs:
	o = off(start)
	if o is None or size <= 0:
		continue
	for ins in md.disasm(b[o:o + size], start):
		ops = ins.operands
		for k, op in enumerate(ops):
			if op.type == x86.X86_OP_MEM:
				d = op.mem.disp & 0xffffffff
				kind = 'addr' if ins.mnemonic == 'lea' else ('write' if k == 0 and ins.mnemonic.startswith(('mov', 'fst', 'fist', 'inc', 'dec', 'add', 'sub', 'or', 'and', 'xor', 'set', 'pop')) and not ins.mnemonic.startswith('movs') else 'read')
				if ins.mnemonic in ('add', 'sub', 'or', 'and', 'xor', 'inc', 'dec') and k == 0:
					kind = 'read+write'
				if ins.mnemonic.startswith(('fst', 'fist')):
					kind = 'write'
			elif op.type == x86.X86_OP_IMM:
				d = op.imm & 0xffffffff
				kind = 'addr'
			else:
				continue
			for t in targets:
				if t[1] <= d <= t[1] + rng:
					hits[t].append((ins.address, fname, kind, d - t[1], '%s %s' % (ins.mnemonic, ins.op_str)))
for t in targets:
	h = hits[t]
	kinds = sorted(set(x[2] for x in h))
	print('== %s %#x: %d accesses (%s)' % (t[0], t[1], len(h), ', '.join(kinds) or 'none'))
	for a, fn, kind, d, text in h:
		print('   %#x %-28s %-10s +%d  %s' % (a, fn, kind, d, text))
