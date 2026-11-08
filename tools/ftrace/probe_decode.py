"""probe_decode.py probe_*.txt ...: the records tools/ftrace/probe.c kept, decoded by src/scene.fields: per field of
each record type, how many records had it non-zero and its distinct values (up to 12). Match packets are decoded by
their kind (byte 1): 0 PlayerStatePacket, 1 GamePacket, 2 PlayerInfoPacket, 3 .. 9 and 13 MatchEventPacket, 10 / 11
TeamPacket, 12 FlagPiecePacket, 14 ItemStatesPacket.
  --seen   only the names (Record.field) seen non-zero, one a line"""
import collections, os, re, struct, sys

R = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..')
recs = {}
cur = None
for line in open(os.path.join(R, 'src', 'scene.fields'), encoding='latin-1'):
	m = re.match(r'struct (\w+) (0x[0-9a-f]+|\d+)', line)
	if m:
		cur = recs.setdefault(m.group(1), [])
		continue
	m = re.match(r'(0x[0-9a-f]+|\d+)\s+(0x[0-9a-f]+|\d+)\s+([^#]+?)\s*(?:#|$)', line)
	if cur is None or not m:
		continue
	decl = m.group(3).strip()
	if decl.startswith('union'):
		for d in re.findall(r'([\w ]+?\**\s*\w+(?:\[\w+\])*);', decl[decl.index('{') + 1:]):
			n = re.match(r'(.*?)(\w+)((?:\[\w+\])*)$', d.strip())
			cur.append((int(m.group(1), 0), int(m.group(2), 0), n.group(2), n.group(1).strip()))
		continue
	n = re.match(r'(.*?)(\w+)((?:\[\w+\])*)$', decl)
	if n:
		cur.append((int(m.group(1), 0), int(m.group(2), 0), n.group(2), n.group(1).strip()))

KIND = {0: 'PlayerStatePacket', 1: 'GamePacket', 2: 'PlayerInfoPacket', 10: 'TeamPacket', 11: 'TeamPacket',
        12: 'FlagPiecePacket', 14: 'ItemStatesPacket'}
for k in (3, 4, 5, 6, 7, 8, 9, 13):
	KIND[k] = 'MatchEventPacket'


def value(t, b):
	if t.startswith('char') and len(b) > 1:
		s = b.split(b'\0')[0]
		return repr(s.decode('latin-1')) if s else None
	if t == 'float' and len(b) == 4:
		return '%g' % struct.unpack('<f', b)[0]
	if len(b) in (1, 2, 4) and '*' not in t:
		signed = not t.startswith('u')
		return str(int.from_bytes(b, 'little', signed=signed))
	return b.hex()


stats = collections.defaultdict(lambda: [0, 0, collections.Counter()])   # name -> [records, non-zero, values]
for path in sys.argv[1:]:
	if path.startswith('--'):
		continue
	for line in open(path, encoding='latin-1'):
		parts = line.split()
		if len(parts) != 2:
			continue
		typ, data = parts[0], bytes.fromhex(parts[1])
		if typ == 'pkt':
			typ = KIND.get(data[1])
			if not typ:
				continue
		for off, size, name, t in recs.get(typ, []):
			b = data[off:off + size]
			if len(b) < size:
				continue
			st = stats['%s.%s' % (typ, name)]
			st[0] += 1
			if any(b):
				st[1] += 1
				v = value(t, b)
				if v is not None:
					st[2][v] += 1
if '--seen' in sys.argv:
	for n, (total, nz, vals) in sorted(stats.items()):
		if nz:
			print(n)
else:
	for n, (total, nz, vals) in sorted(stats.items()):
		print('%-40s %6d records, non-zero in %6d   %s' % (n, total, nz, ', '.join(v for v, _ in vals.most_common(12))[:160]))
