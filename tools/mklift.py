"""mklift.py <out.c> <addr> ...: run tools/lift.py on the given functions (hex, no 0x), with every direct callee that is
not in the list as a native call (+addr; ST0-returning ones as ^addr): game functions, the 0x4a8xxx thunks and patch
code (0xb00000+), "jmp [IAT]" / "jmp rel32" stubs. Run from recomp."""
import sys, csv, struct, capstone, subprocess
D='C:/Users/Alexander/Desktop/Axis/'
out=sys.argv[1]; funcs=[int(a,16) for a in sys.argv[2:]]
b=open(D+'recomp/installed.exe','rb').read()
pe=struct.unpack_from('<I',b,0x3c)[0]; n=struct.unpack_from('<H',b,pe+6)[0]; opt=struct.unpack_from('<H',b,pe+20)[0]
secs=[struct.unpack_from('<8sIIII',b,pe+24+opt+40*i) for i in range(n)]
def off(va):
    for nm,vs,v,rs,ro in secs:
        if v<=va-0x400000<v+rs: return va-0x400000-v+ro
size={int(r['address'],16):int(r['size']) for r in csv.DictReader(open(D+'decomp/out/functions.csv'))}
FP={0x4301e0, 0x46c100, 0x467760, 0x49fe7a, 0x487490, 0x461210, 0x4686d0, 0x4686f0, 0x468700, 0x46c140, 0x46c1c0}   # timer_now, FUN_0046c100, Vec3_normalize (returns the length), atof, timer_getGameTime, armc_461210 (leaves its average), the 0x4c4dec.. float getters, actor_46c140 / actor_46c1c0 (angle steps): ST0 results
SKIP={0x49ec14}          # __ftol: built into the lifter
nat=set(); fp=set()
md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
for f in funcs:
    o=off(f)
    for i in md.disasm(b[o:o+size[f]],f):
        if i.mnemonic in('call','jmp') and i.op_str.startswith('0x'):
            t=int(i.op_str,16)
            o2 = off(t); thunk = o2 is not None and b[o2:o2 + 2] == bytes([0xff, 0x25]) and 0x4a9000 <= struct.unpack_from('<I', b, o2 + 2)[0] < 0x4a9400 or (o2 is not None and t not in size and b[o2] == 0xe9)   # jmp [IAT] / jmp rel32 stubs
            if (t in size or 0x4a8000 <= t < 0x4a9000 or t >= 0xb00000 or thunk) and t not in funcs and t not in SKIP:   # 0xb00000+: patch code
                (fp if t in FP else nat).add(t)
cmd=['python','tools/lift.py',out]+['0x%x'%f for f in funcs]+['+0x%x'%t for t in sorted(nat)]+['^0x%x'%t for t in sorted(fp)]+['--']
print(' '.join(cmd)); r=subprocess.run(cmd); sys.exit(r.returncode)
