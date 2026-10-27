"""cands2.py done.txt minsize maxsize: unrebuilt game functions (unchanged by patches) whose calls all go to rebuilt
functions; lists size, direct-call targets, and flags for indirect calls / imports"""
import sys, csv, struct, capstone
D='C:/Users/Alexander/Desktop/Axis/'
done={int(x,16) for x in open(sys.argv[1]).read().split()}
lo,hi=int(sys.argv[2]),int(sys.argv[3])
ret=open(D+'decomp/bin/AxisGL.exe','rb').read(); pat=open(D+'recomp/installed.exe','rb').read()
def secs(b):
    pe=struct.unpack_from('<I',b,0x3c)[0]; n=struct.unpack_from('<H',b,pe+6)[0]; opt=struct.unpack_from('<H',b,pe+20)[0]
    return [struct.unpack_from('<8sIIII',b,pe+24+opt+40*i) for i in range(n)]
def off(b,va):
    for nm,vs,sva,rs,ro in secs(b):
        if sva<=va-0x400000<sva+rs: return va-0x400000-sva+ro
md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
fs=[(int(r['address'],16),int(r['size']),r['name']) for r in csv.DictReader(open(D+'decomp/out/functions.csv'))]
for a,sz,name in fs:
    if a>=0x49e000 or a in done or not lo<=sz<=hi: continue
    o1,o2=off(ret,a),off(pat,a)
    if o1 is None or o2 is None or ret[o1:o1+sz]!=pat[o2:o2+sz]: continue
    calls=set(); ind=0; fp=0
    for i in md.disasm(pat[o2:o2+sz],a):
        if i.mnemonic=='call':
            if i.op_str.startswith('0x'): calls.add(int(i.op_str,16))
            else: ind+=1
        if i.mnemonic.startswith('j') and i.op_str.startswith('0x') and not a<=int(i.op_str,16)<a+sz:
            calls.add(int(i.op_str,16))
        if i.mnemonic=='jmp' and not i.op_str.startswith('0x'): ind+=1
        if i.mnemonic.startswith('f'): fp+=1
    if ind or any(c not in done for c in calls): continue
    print('%4d %06x %-34s calls=%d fp=%d'%(sz,a,name,len(calls),fp))
