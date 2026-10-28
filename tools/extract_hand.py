"""extract_hand.py out.c header name...: copy hand-written functions (and the static helpers / tables they need, given
as names too) from recomp.c into a new src file, in src syntax: "static T __cdecl name(" -> "T (name)(" for the
hooked ones (helpers stay static), G32 / GU32 / GF / S32 -> GAME_VAR / FIELD, DWORD -> u32. Prints the declarations
for tools/hand2src.py. The result still wants reading: comments, names and casts are worth a pass by hand.

  python tools/extract_hand.py src/menu/layouts.c "layouts.c: ..." rect1 rect_spec arena_404150 ...
"""
import os, re, sys
os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
s = open('recomp.c', 'rb').read().decode('utf-8-sig').replace('\r\n', '\n')
hooks = dict((n, a) for a, n in re.findall(r'\{ 0x([0-9a-f]+), \(void \*\)(\w+), "', s))
out_path, header, names = sys.argv[1], sys.argv[2], sys.argv[3:]
parts, decls = [], []
for n in names:
    m = re.search(r'((?:^(?:/\*|   )[^\n]*\n)*)(^static [^\n;]*?\b%s\b[^\n;]*?(?:\{[^\n]*\}[^\n]*\n|\n\{\n.*?\n\}\n|=[^;]*;\n|\{\n.*?\n\};\n))' % n, s, re.M | re.S)
    if not m:
        sys.exit('%s: not found' % n)
    comment, body = m.group(1), m.group(2)
    if n in hooks:
        body = re.sub(r'^static (?:(THISCALL) )?([^\n(]*?)\s*(?:__cdecl )?\b%s\(' % n,
                      lambda k: '%s%s(%s)(' % (k.group(2).replace('__cdecl', '').strip() + ' ',
                                               (k.group(1) + ' ') if k.group(1) else '', n), body, count=1, flags=re.M)
        head = body.split('{')[0].split('\n')[0]
        decl = re.sub(r'\(%s\)' % n, n, head.strip()).rstrip() + ';'
        decls.append(decl)
    parts.append(comment + body)
text = '\n'.join(parts)
text = re.sub(r'\bGU32\(', 'GAME_U32(', text)
text = re.sub(r'\bG32\(', 'GAME_I32(', text)
text = re.sub(r'\bGF\(', 'GAME_F32(', text)
text = re.sub(r'\bS32\(', 'FIELD_I32(', text)
text = re.sub(r'\bDWORD\b', 'u32', text)
pre = ('/* %s */\n#include "../game.h"\n\n#define GAME_I32(a) GAME_VAR(int, a)\n#define GAME_U32(a) GAME_VAR(u32, a)\n'
       '#define GAME_F32(a) GAME_VAR(float, a)\n#define FIELD_I32(p, o) GAME_VAR(int, (u8 *)(p) + (o))\n\n') % header
open(out_path, 'w').write(pre + text)
for d in decls:
    print(d.replace('u32', 'DWORD'))
