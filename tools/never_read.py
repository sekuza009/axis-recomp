r"""never_read.py [--all]: the named globals (src/globals.h) the original never reads: no instruction reads the
address, none takes its address (lea / push / mov of the address), and none reaches it through an index or a base
below it (a memory operand with a register and a displacement up to 0x200 below it, or an address taken up to 0x400
below it). For checking that such globals are named as kept-only or unused rather than as if something used them.
Prints the name, its writers and its comment."""
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


gtext = open('src/globals.h', encoding='latin-1').read()
glob_ = {}
for m in re.finditer(r'^#define (\w+) GAME_VAR\(([^,]+), (0x[0-9a-f]+)\)[^\n]*?(?:/\*\s*(.*?)\s*\*/)?\s*$', gtext, re.M):
	glob_[int(m.group(3), 16)] = (m.group(1), m.group(2), m.group(4) or '')
addrs = sorted(glob_)
import bisect

direct = {a: set() for a in addrs}      # kinds seen at the exact address
writers = {a: set() for a in addrs}
near_reads = []                          # (low, high) ranges reached through a register or an address taken
funcs = [(int(r['address'], 16), int(r['size']), r['name']) for r in csv.DictReader(open('../decomp/out/functions.csv'))]
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
md.detail = True
WRITES = ('mov', 'fst', 'fist', 'pop', 'set')
for start, size, fname in funcs:
	o = off(start)
	if o is None or size <= 0:
		continue
	for ins in md.disasm(b[o:o + size], start):
		for k, op in enumerate(ins.operands):
			if op.type == x86.X86_OP_MEM:
				d = op.mem.disp & 0xffffffff
				if d < 0x400000:
					continue
				if ins.mnemonic == 'lea':
					kind = 'addr'
				elif k == 0 and ins.mnemonic.startswith(WRITES) and not ins.mnemonic.startswith('movs'):
					kind = 'write'
				else:
					kind = 'read'
				reg = op.mem.base != 0 or op.mem.index != 0
				if reg:
					near_reads.append((d, d + 0x200))
				i = bisect.bisect_left(addrs, d)
				if i < len(addrs) and addrs[i] == d:
					direct[d].add(kind)
					if kind == 'write':
						writers[d].add(fname)
			elif op.type == x86.X86_OP_IMM:
				d = op.imm & 0xffffffff
				if d < 0x400000:
					continue
				near_reads.append((d, d + 0x400))
				if d in direct:
					direct[d].add('addr')
near_reads.sort()
lows = [r[0] for r in near_reads]


def reached(a):
	i = bisect.bisect_right(lows, a)
	# any range starting at or below a that covers it (starting strictly below: the exact address is 'direct')
	for j in range(i - 1, max(-1, i - 4000), -1):
		lo, hi = near_reads[j]
		if lo < a <= hi:
			return True
		if a - lo > 0x400:
			break
	return False


out = []
for a in addrs:
	kinds = direct[a]
	if 'read' in kinds or 'addr' in kinds:
		continue
	if reached(a):
		continue
	name, typ, com = glob_[a]
	if name.startswith('g_unused') and '--all' not in sys.argv:
		continue
	out.append('%-30s %#x %-8s writers: %s\n      %s' % (name, a, typ, ', '.join(sorted(writers[a]))[:90] or '(none)', com[:150]))
print('\n'.join(out))
print(len(out), 'named globals the original never reads (g_unused ones not listed)')
