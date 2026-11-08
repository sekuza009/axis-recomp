"""mkimports.py: src/imports.h, the game's import-table slots by function name (IMP_<name>), read from game.exe's
own import directory. Imports by ordinal (Winsock, DirectSound) are named from the DLLs' ordinal tables. Run from anywhere."""
import os, struct

R = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
WSOCK32_ORDINALS = {2: 'bind', 3: 'closesocket', 4: 'connect', 9: 'htons', 11: 'inet_addr', 12: 'inet_ntoa', 16: 'recv',
                    19: 'send', 22: 'shutdown', 23: 'socket', 52: 'gethostbyname', 57: 'gethostname', 101: 'WSAAsyncSelect',
                    112: 'WSASetLastError', 115: 'WSAStartup', 116: 'WSACleanup'}

def main():
	img = open(os.path.join(R, 'game.exe'), 'rb').read()
	pe = struct.unpack_from('<I', img, 0x3c)[0]
	nsec = struct.unpack_from('<H', img, pe + 6)[0]
	optsz = struct.unpack_from('<H', img, pe + 20)[0]
	opt = pe + 24
	base = struct.unpack_from('<I', img, opt + 28)[0]
	imp_rva = struct.unpack_from('<I', img, opt + 96 + 8)[0]
	secs = []
	for i in range(nsec):
		s = opt + optsz + i * 40
		vsize, va, rsize, raw = struct.unpack_from('<IIII', img, s + 8)
		secs.append((va, max(vsize, rsize), raw))
	def off(rva):
		for va, size, raw in secs:
			if va <= rva < va + size:
				return rva - va + raw
		raise ValueError(hex(rva))
	def cstr(rva):
		o = off(rva)
		return img[o:img.index(b'\0', o)].decode('latin-1')
	out = []
	d = off(imp_rva)
	while True:
		ilt, _, _, name_rva, iat = struct.unpack_from('<IIIII', img, d)
		if not name_rva:
			break
		dll = cstr(name_rva)
		t = ilt or iat
		k = 0
		while True:
			e = struct.unpack_from('<I', img, off(t) + k * 4)[0]
			if not e:
				break
			if e & 0x80000000:
				name = (WSOCK32_ORDINALS if dll.lower() in ('wsock32.dll', 'ws2_32.dll') else {1: 'DirectSoundCreate'} if dll.lower() == 'dsound.dll' else {}).get(e & 0xffff)
				name = name or '%s_ordinal%d' % (dll.split('.')[0].lower(), e & 0xffff)
			else:
				name = cstr(e + 2)
			out.append((base + iat + k * 4, name, dll))
			k += 1
		d += 20
	lines = ['/* imports.h (tools/mkimports.py, from game.exe\'s import directory): each imported function\'s slot in the',
	         '   game\'s import table, as IMP_<name>; called as IMPORT_FN(name, ret, arg types...)(args) (src/axis.h) */',
	         '#pragma once']
	for slot, name, dll in sorted(out):
		lines.append('#define IMP_%s 0x%x   /* %s */' % (name, slot, dll))
	open(os.path.join(R, 'src', 'imports.h'), 'w', newline='\n').write('\n'.join(lines) + '\n')
	print('%d imports' % len(out))

main()
