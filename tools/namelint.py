r"""namelint.py: check that function names agree with what the code does.
Call graph from decomp/evidence.tsv (apis, named_callees); bodies from recomp/src; machine code from installed.exe."""
import csv, glob, re, struct, sys, os
from collections import defaultdict
import capstone
from capstone import x86

D = 'C:/Users/Alexander/Desktop/Axis/'
csv.field_size_limit(10 ** 8)

# ---- call graph
F = {}          # name -> dict(addr, apis:set, callees:set)
for r in csv.DictReader(open(D + 'decomp/evidence.tsv', encoding='latin-1'), delimiter='\t'):
    F[r['name']] = dict(addr=int(r['address'], 16), apis=set(r['apis'].split()), callees=set(r['named_callees'].split()),
                        strings=r['strings'])
memo = {}


def reach(name, seen=None):
    """all APIs and functions reachable from name (inclusive)"""
    if name in memo:
        return memo[name]
    out, stack, seen = set(), [name], set()
    while stack:
        n = stack.pop()
        if n in seen:
            continue
        seen.add(n)
        out.add(n)
        f = F.get(n)
        if f:
            out |= f['apis']
            stack += list(f['callees'])
    memo[name] = out
    return out


def words(name):
    base = name.split('_', 1)[1] if '_' in name else name
    return [w.lower() for w in re.findall(r'[A-Z]?[a-z0-9]+|[A-Z]+(?![a-z])', base)]


GL = lambda s: any(x.startswith(('gl', 'wgl')) or x in ('SwapBuffers',) for x in s)
FILE_API = {'fopen', 'CreateFileA', 'ReadFile', '_lopen', '_lread', 'OpenFile', 'mmioOpenA', 'FindFirstFileA',
            'file_readScrambled', '_open', 'fread', 'fgets', 'fscanf', 'GetPrivateProfileStringA'}
SEND = lambda s: any(x in s for x in ('send', 'sendto', 'dplay_send', 'net_sendPacketData', 'net_send'))
SOUND = lambda s: any(x in s for x in ('sound_playNext', 'sound_playPanned', 'music_play', 'mciSendCommandA',
                                       'mciSendStringA', 'midiOutShortMsg', 'PlaySoundA', 'sndPlaySoundA'))
ALLOC_FREE = {'mem_free', 'operator_delete', 'free', 'GlobalFree', 'HeapFree', 'LocalFree', 'DeleteObject',
              'CloseHandle', 'fclose', 'glDeleteTextures', 'ReleaseDC', 'DestroyWindow', 'wglDeleteContext',
              'crt_free', 'mem_freeBlock'}

issues = defaultdict(list)


def flag(rule, name, why):
    issues[rule].append((name, why))


# ---- source bodies
SRC = {}
for path in glob.glob(D + 'recomp/src/**/*.c', recursive=True):
    if '/data/' in path.replace(os.sep, '/'):
        continue
    t = open(path, encoding='latin-1').read()
    for m in re.finditer(r'^([^\n;{}()#/*]*?)\(\s*(\w+)\s*\)\s*\(([^;{]*?)\)\s*\{', t, re.M | re.S):
        i, depth = m.end() - 1, 0
        for j in range(i, len(t)):
            if t[j] == '{':
                depth += 1
            elif t[j] == '}':
                depth -= 1
                if depth == 0:
                    break
        SRC[m.group(2)] = dict(ret=m.group(1).strip(), params=m.group(3), body=t[i:j + 1],
                               file=path.split('recomp/')[-1].replace(os.sep, '/'))


def strip_comments(s):
    return re.sub(r'/\*.*?\*/|//[^\n]*', '', s, flags=re.S)


# ---- machine code
b = open(D + 'recomp/installed.exe', 'rb').read()
pe = struct.unpack_from('<I', b, 0x3c)[0]
ns = struct.unpack_from('<H', b, pe + 6)[0]
opt = struct.unpack_from('<H', b, pe + 20)[0]
SECT = [struct.unpack_from('<8sIIII', b, pe + 24 + opt + 40 * i) for i in range(ns)]


def off(va):
    for nm, vs, sva, rs, ro in SECT:
        if sva <= va - 0x400000 < sva + rs:
            return va - 0x400000 - sva + ro


EXT = {r['name']: int(r.get('extent') or r['size']) for r in csv.DictReader(open(D + 'decomp/out/functions.csv'))}
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
md.detail = True


def mem_writes(name):
    """stores to memory not addressed off esp/ebp (static data or through a pointer)"""
    f = F[name]
    o, n = off(f['addr']), EXT.get(name, 0)
    out = []
    for ins in md.disasm(b[o:o + n], f['addr']):
        if ins.mnemonic.startswith(('cmp', 'test', 'push', 'call', 'j', 'lea', 'fcom', 'fucom')):
            continue
        for op in ins.operands:
            if op.type == x86.X86_OP_MEM and (op.access & capstone.CS_AC_WRITE):
                base = ins.reg_name(op.mem.base) if op.mem.base else None
                if base in ('esp', 'ebp'):
                    continue
                out.append('%06x %s %s' % (ins.address, ins.mnemonic, ins.op_str))
    return out


# ---- rules
for name, f in F.items():
    if name.startswith(('FUN_', 'thunk', 'crt_', '__', '_')) or name in ('operator_new', 'operator_delete'):
        continue
    w = words(name)
    if not w:
        continue
    v = w[0]
    R = reach(name)
    if v in ('draw', 'render', 'paint') and not GL(R):
        flag('draw: never reaches OpenGL', name, '')
    if v == 'load' and not (FILE_API & R):
        flag('load: never reaches a file API', name, ' '.join(sorted(f['apis'] | f['callees']))[:150])
    if v == 'send' and not SEND(R):
        flag('send: never reaches a network send', name, ' '.join(sorted(f['callees']))[:150])
    if v == 'play' and name.split('_')[0] in ('sound', 'music', 'movie') and not SOUND(R):
        flag('play: never reaches sound output', name, '')
    if v in ('free', 'release', 'dtor', 'destroy', 'delete', 'close', 'unload') and not (ALLOC_FREE & R) \
            and not any(a.startswith(('Release', 'Close', 'Destroy', 'Delete', 'Free')) for a in R):
        flag('free/release: never reaches a free/close/release', name, ' '.join(sorted(f['apis'] | f['callees']))[:150])
    if v == 'get' and name in EXT:
        mw = mem_writes(name)
        if mw:
            flag('get: writes memory', name, '; '.join(mw[:4]) + (' ...' if len(mw) > 4 else ''))

# is/has/can: return values
for name, s in SRC.items():
    w = words(name)
    if not w or w[0] not in ('is', 'has', 'can', 'should', 'was', 'needs', 'any'):
        continue
    if s['ret'].split()[-1:] in (['void'], ['void THISCALL'.split()[0]]) or re.match(r'void\b', s['ret']):
        flag('is/has: returns void', name, s['file'])
        continue
    rets = re.findall(r'\breturn\b([^;]*);', strip_comments(s['body']))
    bad = []
    for e in rets:
        e = e.strip()
        if re.fullmatch(r'\(?\s*[01]\s*\)?|-?1|', e):
            continue
        if re.search(r'==|!=|<=|>=|(?<![<>-])[<>](?![<>])|^!|&&|\|\|', e):
            continue
        if re.match(r'\(?\s*(\w+_)?(is|has|can|should|was|needs|any)[A-Z]\w*\s*\(', e):
            continue
        bad.append(e)
    if bad:
        flag('is/has: returns something other than 0/1 or a test', name, s['file'] + ': ' + ' | '.join(bad)[:200])

# setX: the body mentions X
STOP = {'by', 'from', 'to', 'all', 'and', 'of', 'for', 'the', 'next', 'new', 'default', 'defaults', 'in', 'on', 'up'}
for name, s in SRC.items():
    w = words(name)
    if len(w) < 2 or w[0] != 'set':
        continue
    body = strip_comments(s['body'] + ' ' + s['params']).lower()
    nouns = [x for x in w[1:] if x not in STOP and len(x) > 2]
    missing = [x for x in nouns if x[:4] not in body]
    if nouns and len(missing) == len(nouns):
        flag('set: body never mentions what is set', name, s['file'] + ': ' + ','.join(missing))

print('functions in graph %d, with source bodies %d' % (len(F), len(SRC)))
for rule in sorted(issues):
    print('\n## %s (%d)' % (rule, len(issues[rule])))
    for n, why in sorted(issues[rule]):
        print('  %-36s %s' % (n, why))
