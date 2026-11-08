"""a test copy of DServer/axis_server.py (the user's file untouched) with two switches:
  --outdated  the answers that make the game show THIS PROGRAM HAS BEEN UPDATED: hosting answered 3, every list
              ends with type 3, Ladder login / new ID answered 0x2a
  --ghost     every list starts with a made-up game at an address nobody answers (127.0.0.2): locked, password,
              map 5, time limit 7, rotation 1 - joining it times out"""
import re, sys
src = open('C:/Users/Alexander/Desktop/Axis/DServer/axis_server.py', encoding='utf-8').read()
out = sys.argv[1]
def rep(a, b, n=1):
	global src
	assert src.count(a) == n, (a, src.count(a))
	src = src.replace(a, b)
rep('    ap.add_argument("--no-ladder"', '    ap.add_argument("--outdated", action="store_true")\n    ap.add_argument("--ghost", action="store_true")\n    ap.add_argument("--no-ladder"')
rep('async def main():\n', 'TEST = {"outdated": False, "ghost": False}\n\n\nasync def main():\n')
# the switches read once the arguments are parsed
m = re.search(r'\n(    \w+ = ap\.parse_args\(\)\n)', src)
assert m, 'no parse_args'
src = src.replace(m.group(1), m.group(1) + '    TEST["outdated"], TEST["ghost"] = %s.outdated, %s.ghost\n' % ((re.search(r'(\w+) = ap\.parse_args', m.group(1)).group(1),) * 2), 1)
# hosting answers
rep('            self.games.register(conn, body)\n            return struct.pack("<I", 0)', '            self.games.register(conn, body)\n            return struct.pack("<I", 3 if TEST["outdated"] else 0)')
rep('            self.rooms.register(conn, b)\n            return struct.pack("<I", 0)', '            self.rooms.register(conn, b)\n            return struct.pack("<I", 3 if TEST["outdated"] else 0)')
# list endings and the ghost entry
rep('        out = bytearray()\n        for item in self.items.values():', '''        out = bytearray()
        if TEST["ghost"]:
            g = bytearray(self.size)
            put_str(g, self.off_name, 0x32, "Ghost " + self.kind)
            put_str(g, self.off_ip, 16, "172.24.208.1")
            base = self.off_ip + 16 + (0x1E if self.size == 0x79 else 0)   # (a room record has the host's name first)
            if self.size == 0x79:
                put_str(g, self.off_ip + 16, 0x1E, "ghosthost")
            g[base:base + 7] = bytes([5, 8, 1, 1, 20, 7, 1])   # map, max players, players, mode, frag, time, rotation
            g[self.off_type + 8] = 1   # locked
            put_str(g, self.off_type + 9, 8, "pw123")
            out += g
        for item in self.items.values():''')
rep('        end[self.off_type:self.off_type + 4] = struct.pack("<I", 1)', '        end[self.off_type:self.off_type + 4] = struct.pack("<I", 3 if TEST["outdated"] else 1)')
# Ladder login / new ID
rep('        if mid in (14, 15):\n', '        if mid in (14, 15) and TEST["outdated"]:\n            return self.profile(0x2A)\n        if mid in (14, 15):\n')
open(out, 'w', encoding='utf-8').write(src)
print('written', out)
