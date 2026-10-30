r"""srcaudit.py: checks for the readable rebuilds in src/:
1. every function defined in src/ ("ret (name)(...)") is wired into recomp.c as a readable rebuild (not a lifted
   wrapper or a hand-written static), so the tests run it;
2. no address the patch DLL rewrites (axisnet_recomp.c: (BYTE *)0x4..... sites and the wrapped call table) lies
   inside a rebuilt function unless the src code names that address (PATCHED_CALL / code_matches)."""
import re, csv, glob, os
os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
s = open('recomp.c', encoding='utf-8-sig').read()
src = {f: open(f).read() for f in glob.glob('src/**/*.c', recursive=True)}
names = set()
for t in src.values(): names |= set(re.findall(r'^\w[\w \*]*?\((\w+)\)\(', t, re.M))
for t in src.values(): names |= set(m + '_deletingDtor' for m in re.findall(r'^DELETING\((\w+), ', t, re.M))
bad = 0
for n in sorted(names):
    if re.search(r'LIFT_PLAIN8?\(%s,' % n, s) or re.search(r'static [^\n;]*\b%s\((char|DWORD|void|int)[^;\n]*(\{|$)' % n, s, re.M):
        print('NOT WIRED (old version still in recomp.c):', n); bad += 1
    elif not re.search(r'readable rebuild in src/[^\n]*\r?\n[^\n]*\b%s\(' % n, s) and not re.search(r'\b(int|void|unsigned)[^\n;(]*\b%s\([^;\n]*\);' % n, s):
        print('NO DECLARATION in recomp.c:', n); bad += 1
dll = open('axisnet_recomp.c', encoding='latin-1').read()
sites = set(int(a, 16) for a in re.findall(r'\(BYTE \*\)\s*(0x4[0-9a-f]{5})', dll))
sites |= set(int(a, 16) for a in re.findall(r'\{(0x4[0-9a-f]{5}), 0x4[0-9a-f]{5}, \(void \*\)', dll))
fns = [(int(r['address'], 16), int(r['size']), r['name']) for r in csv.DictReader(open('../decomp/out/functions.csv'))]
alltext = ''.join(src.values())
for a in sorted(sites):
    own = [n for b, z, n in fns if b <= a < b + z]
    if own and own[0] in names and ('%x' % a) not in alltext and ('%x' % (a + 6)) not in alltext:
        print('PATCH-DLL SITE NOT FOLLOWED: %#x in %s' % (a, own[0])); bad += 1
# 3. a call from src to a function rebuilt in src must go through its game.h name (the original address), so the
#    installed version runs and the harness can stub it; without one it calls the C function directly
game = open('src/game.h').read()
for n in sorted(names):
    if re.search(r'#define %s\(' % n, game): continue
    for f, t in src.items():
        if re.search(r'(?<![\w(])%s\(' % n, t):
            print('DIRECT CALL (no game.h name): %s in %s' % (n, f)); bad += 1
# 4. a function whose original the tests call as thiscall (TC(...)) must be defined THISCALL in src: the tests call
#    the rebuild as recomp.c declares it, so a cdecl rebuild of a thiscall original still passes them, and the game
#    (which passes this in ecx) gives it garbage (game_processGameModeInit crashed at a match's start, 2026-10-30)
thiscall = set(re.findall(r'(?m)^ST\((\w+),[^\n]*?\bTC\(', s))
for t in src.values():
    for m in re.finditer(r'^\w[\w \*]*?\((\w+)\)\(', t, re.M):
        if m.group(1) in thiscall and 'THISCALL' not in m.group(0):
            print('NOT THISCALL (its original is): %s' % m.group(1)); bad += 1
print('%d functions in src, %d problems' % (len(names), bad))
