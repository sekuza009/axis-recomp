import sys, struct, capstone, csv
D='C:/Users/Alexander/Desktop/Axis/'
b=open(D+'recomp/installed.exe','rb').read()
pe=struct.unpack_from('<I',b,0x3c)[0]; n=struct.unpack_from('<H',b,pe+6)[0]; opt=struct.unpack_from('<H',b,pe+20)[0]
S=[struct.unpack_from('<8sIIII',b,pe+24+opt+40*i) for i in range(n)]
want=[int(x,16) for x in open(sys.argv[1]).read().split()]
bad={}
for a in want:
    for k in range(1,5): bad[a+k]=a
md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32); md.skipdata=True
for nm,vs,va,rs,ro in S:
    if not nm.startswith(b'.text') and nm.rstrip(b'\0') not in (b'.text',): continue
    for i in md.disasm(b[ro:ro+rs],0x400000+va):
        if i.mnemonic[0] in 'jc' and i.op_str.startswith('0x'):
            t=int(i.op_str,16)
            if t in bad: print('branch %06x -> %06x inside entry of %06x'%(i.address,t,bad[t]))
print('sections', [s[0] for s in S]); print('checked', len(want))
