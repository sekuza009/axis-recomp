"""hand2src.py "decl" ...: move hand-written functions from recomp.c to their readable rebuild in src/.
For each declaration (e.g. "void armc_40e670(void);"), the function of that name defined in recomp.c as
"static ... name(...)\\r\\n{ ... \\r\\n}" (or on one line) is replaced by the declaration, marked as a readable rebuild.
Its comment above stays. recomp.c keeps its BOM and CRLF line endings; nothing is written if a name is not found
exactly once (exit code 1).

  python tools/hand2src.py "void armc_40e670(void);" "int armc_40f830(int i);"
"""
import os, re, sys
os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
raw = open('recomp.c', 'rb').read()
bom = raw.startswith(b'\xef\xbb\xbf')
s = raw.decode('utf-8-sig')
EXT = '/* readable rebuild in src/ (its own translation unit, see src/axis.h) */\r\n'
for decl in sys.argv[1:]:
    decl = decl.strip().rstrip(';') + ';'
    name = re.search(r'(\w+)\s*\(', decl).group(1)
    multi = list(re.finditer(r'^static [^\r\n;]*?\b%s\([^)]*\)[^\r\n;{]*\r\n\{\r\n.*?\r\n\}\r\n' % name, s, re.M | re.S))
    one = list(re.finditer(r'^static [^\r\n;]*?\b%s\([^)]*\)[^\r\n;{]*\{[^\r\n]*\}[ \t]*(/\*[^\r\n]*\*/)?\r\n' % name, s, re.M))
    found = multi + one
    if len(found) != 1:
        sys.exit('%s: definition found %d times - nothing written' % (name, len(found)))
    m = found[0]
    s = s[:m.start()] + EXT + decl + '\r\n' + s[m.end():]
    print('moved', name)
open('recomp.c', 'wb').write((b'\xef\xbb\xbf' if bom else b'') + s.encode())
