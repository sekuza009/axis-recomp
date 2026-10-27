"""dis.py addr... : disassemble functions (size from functions.csv) from the patched reference exe"""
import sys, csv, struct, capstone
D='C:/Users/Alexander/Desktop/Axis/'
b=open(D+'recomp/installed.exe','rb').read()
pe=struct.unpack_from('<I',b,0x3c)[0]; n=struct.unpack_from('<H',b,pe+6)[0]; opt=struct.unpack_from('<H',b,pe+20)[0]
S=[struct.unpack_from('<8sIIII',b,pe+24+opt+40*i) for i in range(n)]
def off(va):
    for nm,vs,sva,rs,ro in S:
        if sva<=va-0x400000<sva+rs: return va-0x400000-sva+ro
sz={int(r['address'],16):(int(r['size']),r['name']) for r in csv.DictReader(open(D+'decomp/out/functions.csv'))}
md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
for a in sys.argv[1:]:
    a=int(a,16); s,name=sz[a]; o=off(a)
    print('== %06x %s (%d)'%(a,name,s))
    for i in md.disasm(b[o:o+s],a): print('  %06x  %-8s %s'%(i.address,i.mnemonic,i.op_str))
