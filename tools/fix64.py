"""fix64.py: the 64-bit pass's diagnostic-driven rewrite (PORTING.md, stage 6). Reads clang's diagnostics from a 64-bit
compile of src/ (files given as arguments: the compiler's output) and, where a game address meets a pointer, writes the
conversion of src/axis.h in place:

  (T *)v               -> AP(T, v)          (int-to-pointer casts)
  (u32)p, (int)p ...   -> AV(p), (int)AV(p) (pointer-to-int casts)
  a u32 passed / assigned / returned where a T pointer is wanted -> AP(T, v)
  a pointer passed / assigned where a u32 is wanted -> AV(p)

AP / AV are the plain casts in the 32-bit builds, so those stay as they were (checked with tools/objcmp.py). A
diagnostic inside a macro's definition, a header shared by every file or a shape this script does not know is listed
for a hand edit instead. --dry: list only."""
import collections, os, re, sys

ROOT = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
SKIP = ('src/axis.h', 'src/plat/posix/', 'src/addr_consts.h', 'src/data/')
TYPE_WORDS = {'u8', 'u16', 'u32', 'u64', 'i32', 'int', 'char', 'float', 'double', 'void', 'short', 'long', 'unsigned',
              'signed', 'const', 'volatile', 'struct', 'BYTE', 'WORD', 'DWORD', 'uintptr_t', 'size_t', 'intptr_t',
              'HANDLE', 'HWND', 'HDC', 'BOOL', 'LONG', 'UINT', 'ULONG'}
DIAG = re.compile(r'^(src/[^:]+):(\d+):(\d+): (?:warning|error): (.*?)(?: \[(-W[\w-]+)\])?$')
IDENT = re.compile(r'[A-Za-z_]\w*')


def skip_ws(t, i):
    while i < len(t) and t[i] in ' \t\r\n':
        i += 1
    return i


def match_close(t, i):
    """t[i] in '([{' -> index just past its closing bracket (strings skipped)"""
    pairs = {'(': ')', '[': ']', '{': '}'}
    stack = []
    j = i
    while j < len(t):
        c = t[j]
        if c in '"\'':
            q = c
            j += 1
            while t[j] != q:
                j += 2 if t[j] == '\\' else 1
        elif c in pairs:
            stack.append(pairs[c])
        elif c in ')]}':
            if not stack or stack.pop() != c:
                raise ValueError('bracket mismatch at %d' % j)
            if not stack:
                return j + 1
        j += 1
    raise ValueError('unbalanced')


def is_type(s):
    toks = re.findall(r'[A-Za-z_]\w*|\*|\S', s)
    if not toks or any(not (IDENT.fullmatch(x) or x == '*') for x in toks):
        return False
    return '*' in toks or toks[0] in TYPE_WORDS or toks[-1] in TYPE_WORDS or (len(toks) == 1 and toks[0].endswith('_t'))


def unary_end(t, i):
    """the end of the unary expression starting at i (after spaces)"""
    i = skip_ws(t, i)
    if t.startswith('sizeof', i) and not (t[i + 6].isalnum() or t[i + 6] == '_'):
        return unary_end(t, i + 6)
    if t.startswith('++', i) or t.startswith('--', i):
        return unary_end(t, i + 2)
    if t[i] in '&*-+!~':
        return unary_end(t, i + 1)
    if t[i] == '(':
        e = match_close(t, i)
        if is_type(t[i + 1:e - 1]):
            return unary_end(t, e)   # (a cast)
        j = e
    elif t[i] == '"':
        j = i
        while j < len(t) and t[j] == '"':
            j = match_str(t, j)
            j2 = skip_ws(t, j)
            if j2 < len(t) and t[j2] == '"':
                j = j2
        return j
    elif t[i] == "'":
        j = match_str(t, i)
    else:
        m = re.compile(r'[A-Za-z_]\w*|[0-9][\w.]*').match(t, i)
        if not m:
            raise ValueError('no operand at %d: %r' % (i, t[i:i + 20]))
        j = m.end()
    while True:   # postfix
        k = skip_ws(t, j)
        if k < len(t) and t[k] in '[(':
            j = match_close(t, k)
        elif t.startswith('->', k):
            j = IDENT.match(t, skip_ws(t, k + 2)).end()
        elif k < len(t) and t[k] == '.' and not t[k + 1].isdigit():
            j = IDENT.match(t, skip_ws(t, k + 1)).end()
        elif t.startswith('++', k) or t.startswith('--', k):
            j = k + 2
        else:
            return j


def match_str(t, i):
    q = t[i]
    j = i + 1
    while t[j] != q:
        j += 2 if t[j] == '\\' else 1
    return j + 1


def assign_end(t, i):
    """the end of an assignment-expression from i: the next , ; ) ] } at depth 0"""
    j = i
    while j < len(t):
        c = t[j]
        if c in '"\'':
            j = match_str(t, j)
            continue
        if c in '([{':
            j = match_close(t, j)
            continue
        if c in ',;)]}':
            break
        j += 1
    while t[j - 1] in ' \t\r\n':
        j -= 1
    return j


def ptr_base(ty):
    """'const char *' -> 'const char'; None for function pointers and the like"""
    ty = ty.strip()
    if '(' in ty or not ty.endswith('*'):
        return None
    return ty[:-1].rstrip()


def first_type(msg, after):
    m = re.search(after + r" '([^']+)'", msg)
    return m.group(1) if m else None


def plan(msg, flag):
    """-> (kind, pointer base type or None)"""
    if flag in ('-Wint-to-pointer-cast', '-Wint-to-void-pointer-cast'):
        return 'cast_ap', None
    if flag in ('-Wpointer-to-int-cast', '-Wvoid-pointer-to-int-cast'):
        return 'cast_av', None
    if flag == '-Wint-conversion':
        if msg.startswith('incompatible integer to pointer conversion'):
            ty = first_type(msg, 'to parameter of type') or first_type(msg, 'initializing') or \
                first_type(msg, 'assigning to') or first_type(msg, 'with result type')
            b = ptr_base(ty) if ty else None
            return ('wrap_ap', b) if b else (None, None)
        if msg.startswith('incompatible pointer to integer conversion'):
            return 'wrap_av', None
    return None, None


def apply(t, pos, kind, base):
    if kind == 'cast_ap':
        if t[pos] != '(':
            return None
        e = match_close(t, pos)
        ty = t[pos + 1:e - 1]
        b = ptr_base(ty)
        if not b:
            return None
        end = unary_end(t, e)
        return t[:pos] + 'AP(%s, %s)' % (b, t[e:end].strip()) + t[end:]
    if kind == 'cast_av':
        if t[pos] != '(':
            return None
        e = match_close(t, pos)
        ty = t[pos + 1:e - 1].strip()
        end = unary_end(t, e)
        inner = t[e:end].strip()
        if ty in ('u32', 'DWORD', 'unsigned', 'unsigned int', 'uint32_t'):
            return t[:pos] + 'AV(%s)' % inner + t[end:]
        return t[:pos] + '(%s)AV(%s)' % (ty, inner) + t[end:]
    if kind in ('wrap_ap', 'wrap_av'):
        p = skip_ws(t, pos)
        m = re.compile(r'[A-Za-z_]\w*\s*=(?!=)').match(t, p)
        if m:   # (an initialisation: clang points at the declarator's name)
            p = m.end() - 1
        if t[p] == '=' and t[p + 1] != '=':
            p = skip_ws(t, p + 1)
        end = assign_end(t, p)
        inner = t[p:end]
        if not inner.strip():
            return None
        # (a pointer stored where the 64-bit build has a 32-bit field: AREF, the pointer itself in the 32-bit builds)
        new = 'AP(%s, %s)' % (base, inner) if kind == 'wrap_ap' else 'AREF(%s)' % inner
        return t[:p] + new + t[end:]
    return None


def main():
    dry = '--dry' in sys.argv
    diags = collections.OrderedDict()
    for f in [a for a in sys.argv[1:] if not a.startswith('--')]:
        lines = open(f, encoding='latin-1').read().split('\n')
        for k, line in enumerate(lines):
            m = DIAG.match(line)
            if not m:
                continue
            path, ln, col, msg, flag = m.group(1), int(m.group(2)), int(m.group(3)), m.group(4), m.group(5)
            # (from a macro: the next lines say "expanded from macro"; such a site is listed, not edited)
            macro = any('expanded from macro' in lines[x] for x in range(k + 1, min(k + 6, len(lines)))
                        if not DIAG.match(lines[x]) and 'note:' in lines[x])
            diags.setdefault((path, ln, col), (msg, flag, macro))
    byfile = collections.defaultdict(list)
    manual = []
    for (path, ln, col), (msg, flag, macro) in diags.items():
        kind, base = plan(msg, flag)
        if not kind:
            if flag in ('-Wint-conversion', '-Wint-to-pointer-cast', '-Wpointer-to-int-cast', None):
                manual.append('%s:%d:%d: %s' % (path, ln, col, msg))
            continue
        if path.startswith(SKIP) or path.endswith('.h'):
            manual.append('%s:%d:%d: %s%s' % (path, ln, col, msg, ' (macro)' if macro else ''))
            continue
        byfile[path].append((ln, col, kind, base, msg))
    done = 0
    for path, items in byfile.items():
        full = os.path.join(ROOT, path)
        raw = open(full, 'rb').read().decode('latin-1')
        crlf = '\r\n' in raw
        t = raw.replace('\r\n', '\n')
        starts = [0]
        for line in t.split('\n'):
            starts.append(starts[-1] + len(line) + 1)
        # (right to left: an inner site is rewritten before the outer one re-reads its extent)
        for ln, col, kind, base, msg in sorted(items, key=lambda x: -(starts[x[0] - 1] + x[1] - 1)):
            pos = starts[ln - 1] + col - 1
            line = t[starts[ln - 1]:t.find('\n', starts[ln - 1])]
            prev = t[starts[ln - 2]:starts[ln - 1] - 1] if ln > 1 else ''
            if line.lstrip().startswith('#') or prev.rstrip().endswith('\\'):   # (a macro's definition)
                manual.append('%s:%d:%d: %s (#define)' % (path, ln, col, msg))
                continue
            try:
                new = apply(t, pos, kind, base)
            except (ValueError, AttributeError, IndexError) as e:
                new = None
            if new is None:
                manual.append('%s:%d:%d: %s (shape)' % (path, ln, col, msg))
                continue
            t = new
            done += 1
        if not dry:
            open(full, 'wb').write((t.replace('\n', '\r\n') if crlf else t).encode('latin-1'))
    for m in manual:
        print('MANUAL ' + m)
    print('%d sites rewritten, %d left for hand edits' % (done, len(manual)))


main()
