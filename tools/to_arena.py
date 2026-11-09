"""to_arena.py: the 64-bit pass's mechanical rewrite (PORTING.md, stage 6). A pointer cast of a game address -
(T *)IMG(a), (T *)STR(..), (T *)RELOC(v), (T *)OBJ(x), (T *)ADDR(x), (T *)MSG(n) - becomes AP(T, ...): the same
cast in the 32-bit builds (src/axis.h), the address taken from g_arena in the 64-bit one. With file arguments only
those files; with --check, only counts. Writes files byte for byte otherwise unchanged (CRLF kept)."""
import os, re, sys

MACROS = ('IMG', 'RELOC', 'STR', 'MSG', 'OBJ', 'ADDR', 'VT', 'GAME_VAR')
CAST = re.compile(r'\(\s*((?:const\s+|volatile\s+|unsigned\s+|signed\s+|struct\s+)*[A-Za-z_][A-Za-z_0-9]*(?:\s+[A-Za-z_][A-Za-z_0-9]*)*\s*\*+)\s*\)\s*(' + '|'.join(MACROS) + r')\(')


def close_paren(t, i):
    """t[i] == '(' -> the index of its closing paren (strings and chars skipped)"""
    depth = 0
    j = i
    while j < len(t):
        c = t[j]
        if c in '"\'':
            q = c
            j += 1
            while t[j] != q:
                j += 2 if t[j] == '\\' else 1
        elif c == '(':
            depth += 1
        elif c == ')':
            depth -= 1
            if not depth:
                return j
        j += 1
    raise ValueError('unbalanced')


def rewrite(t):
    out, pos, n = [], 0, 0
    for m in CAST.finditer(t):
        if m.start() < pos:
            continue
        # (not a cast inside a macro definition's parameter list such as #define X(T *) - none expected)
        typ = re.sub(r'\s+', ' ', m.group(1)).strip()
        typ = typ[:-1].rstrip()   # (the cast's type less its last *)
        open_ = m.end() - 1
        end = close_paren(t, open_)
        inner = t[m.start(2):end + 1]
        out.append(t[pos:m.start()])
        out.append('AP(%s, %s)' % (typ, inner))
        pos = end + 1
        n += 1
    out.append(t[pos:])
    return ''.join(out), n


def main():
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    check = '--check' in sys.argv
    root = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'src')
    files = args or [os.path.join(d, f) for d, _, fs in os.walk(root) for f in fs if f.endswith(('.c', '.h'))]
    total = 0
    for f in sorted(files):
        if f.replace('\\', '/').endswith('src/axis.h'):
            continue
        raw = open(f, 'rb').read()
        t = raw.decode('latin-1')
        # (repeat: a rewritten cast may hold another, e.g. (char *)STR(..) inside (u8 *)RELOC(..))
        new, n = rewrite(t)
        while n:
            new2, n2 = rewrite(new)
            if not n2:
                break
            new, n = new2, n + n2
        cnt = len(CAST.findall(t))
        if cnt:
            total += cnt
            if not check:
                open(f, 'wb').write(new.encode('latin-1'))
    print('%d casts %s' % (total, 'found' if check else 'rewritten'))


main()
