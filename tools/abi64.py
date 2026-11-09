"""abi64.py: the 64-bit pass's check of calls between the game's functions (PORTING.md, stage 6). A call written with
CALL_FN / CALL_THISFN / GAME_FN (src/game.h, src/calls.h and local macros) casts the function to the argument types
the call site gives; in the 32-bit builds any 4-byte type passes the same, but x86-64 passes a pointer in 64 bits, a
u32 in 32 and a float in another register: a call whose types disagree with the function's definition in kind
(pointer / 32-bit integer / float / double / 64-bit integer) gets a wrong argument there. Lists each disagreement:
the macro's file and line, the function, the argument, both types. Also the return types."""
import os, re, sys

R = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'src'))


def strip_comments(t):
    # (newlines kept, so the line numbers stay right)
    return re.sub(r'/\*.*?\*/', lambda m: re.sub(r'[^\n]', ' ', m.group(0)), re.sub(r'//[^\n]*', '', t), flags=re.S)


def split_args(s):
    out, depth, cur = [], 0, ''
    for c in s:
        if c in '([':
            depth += 1
        elif c in ')]':
            depth -= 1
        if c == ',' and depth == 0:
            out.append(cur.strip())
            cur = ''
        else:
            cur += c
    if cur.strip():
        out.append(cur.strip())
    return out


def kind(ty):
    ty = re.sub(r'\b(const|volatile|struct|unsigned|signed|CDECL|STDCALL|THISCALL|register)\b', ' ', ty)
    ty = re.sub(r'\s+', ' ', ty).strip()
    if '(' in ty and '*' in ty:
        return 'P'   # (a function pointer)
    if '*' in ty or '[' in ty or re.match(r'^APTR\b', ty) and False:
        return 'P'
    base = ty.split()[0] if ty else ''
    if base == 'FBT':   # (src/axis.h: a float in the 64-bit build; F2U_T a u32)
        return 'F'
    if base in ('float',):
        return 'F'
    if base in ('double',) or ty.startswith('long double'):
        return 'D'
    if 'long long' in ty or base in ('u64', 'i64', 'int64_t', 'uint64_t', 'size_t', 'uintptr_t', 'intptr_t'):
        return 'L'
    if base == '...':
        return '...'
    if base in ('void',) and '*' not in ty:
        return 'V'
    if base == 'va_list':
        return 'VA'
    return 'I'   # (u32, int, char, short, enums, typedefs of them, APTR in 64-bit)


def param_types(params):
    """'int x, const char *s' -> ['int', 'const char *']"""
    out = []
    for p in split_args(params):
        if p in ('void', ''):
            continue
        if p == '...':
            out.append('...')
            continue
        m = re.match(r'^(.*?)\(\s*\*\s*\w*\s*\)\s*\((.*)\)$', p)   # (a function pointer parameter)
        if m:
            out.append(m.group(1) + '(*)(' + m.group(2) + ')')
            continue
        m = re.match(r'^(.*?)(\w+)\s*(\[[^\]]*\])?$', p)
        if m and m.group(1).strip() and not m.group(1).strip().endswith(('(', ',')):
            out.append(m.group(1) + ('*' if m.group(3) else ''))
        else:
            out.append(p)
    return out


defs = {}
macros = []
for d, _, fs in os.walk(R):
    if os.sep + 'posix' in d:
        continue
    for f in fs:
        if not f.endswith(('.c', '.h')):
            continue
        p = os.path.join(d, f)
        t = strip_comments(open(p, encoding='latin-1').read())
        # definitions: "ret (name)(params) {"
        for m in re.finditer(r'^([A-Za-z_][\w \*]*?)\s*\(\s*(\w+)\s*\)\s*\(([^)]*(?:\([^)]*\)[^)]*)*)\)\s*\{', t, re.M):
            ret = re.sub(r'\b(CDECL|STDCALL|THISCALL|static|inline)\b', '', m.group(1)).strip()
            defs[m.group(2)] = (ret, param_types(m.group(3)), p, t[:m.start()].count('\n') + 1)
        # calls: CALL_FN(name, ret, types...) / CALL_THISFN / GAME_FN(name, addr, ret, types...) / GAME_THISFN
        for m in re.finditer(r'\b(CALL_FN|CALL_THISFN|GAME_FN|GAME_THISFN)\(', t):
            i = m.end()
            depth, j = 1, i
            while depth and j < len(t):
                if t[j] == '(':
                    depth += 1
                elif t[j] == ')':
                    depth -= 1
                j += 1
            args = split_args(t[i:j - 1])
            if m.group(1).startswith('GAME_'):
                if len(args) < 3:
                    continue
                name, ret, types = args[0], args[2], args[3:]
            else:
                if len(args) < 2:
                    continue
                name, ret, types = args[0], args[1], args[2:]
            if not re.match(r'^\w+$', name) or name == 'name':
                continue
            macros.append((name, ret, [x for x in types if x != 'void'], p, t[:m.start()].count('\n') + 1))

bad = 0
seen = set()
for name, ret, types, p, line in macros:
    if name not in defs:
        continue
    dret, dtypes, dp, dline = defs[name]
    probs = []
    if kind(ret) != kind(dret) and not (kind(ret) == 'V' or kind(dret) == 'V'):
        probs.append('returns %s, defined %s' % (ret, dret))
    for k, (a, b) in enumerate(zip(types, dtypes)):
        if kind(a) == '...' or kind(b) == '...':
            break
        if kind(a) != kind(b):
            probs.append('argument %d: %s, defined %s' % (k + 1, a, b))
    if len(types) != len(dtypes) and '...' not in dtypes and '...' not in types:
        probs.append('%d arguments, defined %d' % (len(types), len(dtypes)))
    if probs:
        key = (name, os.path.relpath(p, R), line)
        if key in seen:
            continue
        seen.add(key)
        bad += 1
        print('%s:%d: %s (%s:%d): %s' % (os.path.relpath(p, R), line, name, os.path.relpath(dp, R), dline, '; '.join(probs)))
print('%d calls disagree with their functions in kind (%d call macros, %d definitions read)' % (bad, len(macros), len(defs)))


# ---- --fix: each disagreeing call macro rewritten so x86-64 passes what the function takes, the 32-bit code unchanged:
# a pointer / address disagreement by the definition's type with AP / AV on the argument (a same-size cast in the
# 32-bit builds); a float / bits disagreement with FBT / FB (the call has bits, the function a float) or F2U_T / F2U
# (the call has a float, the function its bits); a return by the definition's type, converted back with AP / AV
def fix_all():
    edits = {}
    for name, ret, types, p, line in macros:
        if name not in defs:
            continue
        dret, dtypes, dp, dline = defs[name]
        edits.setdefault(p, []).append((name, ret, types, dret, dtypes, line))
    total = 0
    for p, items in edits.items():
        raw = open(p, 'rb').read().decode('latin-1')
        crlf = '\r\n' in raw
        t = raw.replace('\r\n', '\n')
        for name, ret, types, dret, dtypes, line in items:
            n = fix_one(t, name, ret, types, dret, dtypes, line)
            if n is not None and n != t:
                t = n
                total += 1
        open(p, 'wb').write((t.replace('\n', '\r\n') if crlf else t).encode('latin-1'))
    print('%d call macros rewritten' % total)


def ptr_base(ty):
    ty = ty.strip()
    return ty[:-1].strip() if ty.endswith('*') and '(' not in ty else None


def fix_one(t, name, ret, types, dret, dtypes, line):
    # the macro call on that line: <MAC>(name, ...)(args)
    starts = [0]
    for l in t.split('\n'):
        starts.append(starts[-1] + len(l) + 1)
    lo = starts[line - 1]
    m = re.compile(r'\b(CALL_FN|CALL_THISFN|GAME_FN|GAME_THISFN)\(\s*' + name + r'\s*,').search(t, lo)
    if not m or m.start() > starts[line] + 400:
        return None
    i = m.end(1)
    depth, j = 0, i
    while True:
        if t[j] == '(':
            depth += 1
        elif t[j] == ')':
            depth -= 1
            if not depth:
                break
        j += 1
    head = t[i + 1:j]   # (the macro's arguments)
    hargs = split_args(head)
    k0 = 3 if m.group(1).startswith('GAME_') else 2
    # the call's arguments after it
    a0 = j + 1
    while t[a0] in ' \t\\n':
        a0 += 1
    if t[a0] != '(':
        return None
    depth, a1 = 0, a0
    while True:
        if t[a1] == '(':
            depth += 1
        elif t[a1] == ')':
            depth -= 1
            if not depth:
                break
        a1 += 1
    cargs = split_args(t[a0 + 1:a1])
    changed = False
    for k, (a, b) in enumerate(zip(types, dtypes)):
        ka, kb = kind(a), kind(b)
        if ka == '...' or kb == '...' or ka == kb or k >= len(cargs) or k0 + k >= len(hargs):
            continue
        if ka == 'I' and kb == 'P':
            base = ptr_base(b)
            if not base:
                continue
            hargs[k0 + k] = b.strip()
            cargs[k] = 'AP(%s, %s)' % (base, cargs[k])
        elif ka == 'P' and kb == 'I':
            hargs[k0 + k] = b.strip()
            cargs[k] = 'AV(%s)' % cargs[k]
        elif ka == 'I' and kb == 'F':
            hargs[k0 + k] = 'FBT'
            cargs[k] = 'FB(%s)' % cargs[k]
        elif ka == 'F' and kb == 'I':
            hargs[k0 + k] = 'F2U_T'
            cargs[k] = 'F2U(%s)' % cargs[k]
        else:
            continue
        changed = True
    wrap = None
    kr, kd = kind(ret), kind(dret)
    if kr != kd and 'V' not in (kr, kd):
        if kr == 'I' and kd == 'P':
            hargs[k0 - 1] = dret.strip()
            wrap = 'AV(%s)'
            changed = True
        elif kr == 'P' and kd == 'I':
            base = ptr_base(ret)
            if base:
                hargs[k0 - 1] = dret.strip()
                wrap = 'AP(' + base + ', %s)'
                changed = True
    if not changed:
        return None
    call = t[m.start():i] + '(' + ', '.join(hargs) + ')' + '(' + ', '.join(cargs) + ')'
    if wrap:
        call = wrap % call
    return t[:m.start()] + call + t[a1 + 1:]


if '--fix' in sys.argv:
    fix_all()
