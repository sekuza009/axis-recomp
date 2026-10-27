"""splice.py <batch-no> <code.c> <tests.c> <spec>: append a batch to recomp.c.
spec lines: name addr ret nfull nfast   (tests table + hook table get one entry each)"""
import sys
n,codef,testf,specf=sys.argv[1:5]
src=open('recomp.c',encoding='utf-8-sig').read()
spec=[l.split() for l in open(specf) if l.strip() and not l.startswith('#')]
code=open(codef).read(); tests=open(testf).read()
def once(anchor):
    assert src.count(anchor)==1, anchor
def rows(items,per): return ''.join('\t'+', '.join(items[i:i+per])+',\n' for i in range(0,len(items),per))
for a in ('static FILE *g_log;','#define T(name, ret, nfull, nfast)','\n};\n\nstatic const struct { DWORD addr, base, limit;','\n};\n\nstatic DWORD WINAPI worker'):
    once(a)
src=src.replace('static FILE *g_log;', code+'static FILE *g_log;')
src=src.replace('#define T(name, ret, nfull, nfast)', tests+'#define T(name, ret, nfull, nfast)')
T=['T(%s, %s, %s, %s)'%(s[0],s[2],s[3],s[4]) for s in spec]
src=src.replace('\n};\n\nstatic const struct { DWORD addr, base, limit;', '\n\t/* batch %s */\n'%n+rows(T,4).rstrip('\n')+'\n};\n\nstatic const struct { DWORD addr, base, limit;')
H=['{ 0x%s, (void *)%s, "%s" }'%(s[1],s[0],s[0]) for s in spec]
src=src.replace('\n};\n\nstatic DWORD WINAPI worker', '\n\t/* batch %s */\n'%n+rows(H,2).rstrip('\n')+'\n};\n\nstatic DWORD WINAPI worker')
open('recomp.c','w',encoding='utf-8-sig').write(src)
print(len(spec),'functions spliced')
