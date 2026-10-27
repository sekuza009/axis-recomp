import csv, sys
D='C:/Users/Alexander/Desktop/Axis/'
done={int(x,16) for x in open(sys.argv[1]).read().split()}
ret=open(D+'decomp/bin/AxisGL.exe','rb').read(); pat=open(D+'recomp/installed.exe','rb').read()
# .text: file offset = va - 0x400000 assumed (check)
import struct
def secs(b):
    pe=struct.unpack_from('<I',b,0x3c)[0]; n=struct.unpack_from('<H',b,pe+6)[0]; opt=struct.unpack_from('<H',b,pe+20)[0]
    o=pe+24+opt; r=[]
    for i in range(n):
        nm,vs,va,rs,ro=struct.unpack_from('<8sIIII',b,o+40*i); r.append((nm.rstrip(b'\0'),va,vs,ro,rs))
    return r
def f2(b,va):
    for nm,sva,vs,ro,rs in secs(b):
        if sva<=va-0x400000<sva+rs: return va-0x400000-sva+ro
ev={}
for r in csv.DictReader(open(D+'decomp/evidence.tsv'),delimiter='\t'): ev[int(r['address'],16)]=r
out=[]
for a,r in ev.items():
    sz=int(r['size'])
    if a>=0x49e000 or a in done or not (int(sys.argv[2])<=sz<=int(sys.argv[3])): continue
    if r['apis'].strip(): continue
    o1,o2=f2(ret,a),f2(pat,a)
    if o1 is None or o2 is None: continue
    if ret[o1:o1+sz]!=pat[o2:o2+sz]: continue
    callees=[c for c in r['named_callees'].split() if c]
    out.append((int(r['callees']),sz,a,r['name'],' '.join(callees)[:80],r['strings'][:50]))
out.sort()
for c in out: print('%d %4d %06x %-34s %s | %s'%c)
