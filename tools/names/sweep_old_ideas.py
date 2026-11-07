r"""sweep_old_ideas.py out.txt: after renames, the places that still use an old name (ID) or its words (IDEA) in comments
and names - each to be read against why the rename was made. Renames: the audit folder's functions_renames.csv and
data*_edits*.json (+ k_freeKeys). Run from recomp/."""
import json,glob,re,os,sys
os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..'))
T='tools/names/audit2026-11-07/'
R=[]
for l in open(T+'functions_renames.csv'):
    p=l.strip().split(',')
    if len(p)>=2: R.append((p[0],p[1],'fn'))
for f in glob.glob(T+'data_edits_*.json')+glob.glob(T+'data_deep_edits_P*.json'):
    for k,v in json.load(open(f,encoding='utf-8')).items():
        if 'name' in v:
            if '.' in k: s,n=k.split('.'); R.append((n,v['name'],'field:'+s))
            else: R.append((k,v['name'],'global'))
R.append(('k_freeKeys','k_mechTestKeys','static'))
files=[f for f in glob.glob('src/**/*.[ch]',recursive=True)+['src/scene.fields','src/README.txt','recomp.c','axisnet_recomp.c']+glob.glob('standalone/*.[ch]')+glob.glob('tools/**/*.txt',recursive=True)+glob.glob('tools/**/*.py',recursive=True)
       if os.path.isfile(f) and 'audit2026' not in f and 'scene.h' not in f and os.sep+'data'+os.sep not in f and 'tools/names/' not in f.replace(os.sep,'/')]
texts={f:open(f,encoding='latin-1').read().split('\n') for f in files}
def words(n):
    n=re.sub(r'^(g|k)_','',n); n=n.replace('_',' ')
    return [w.lower() for w in re.findall(r'[A-Z]?[a-z]+|[A-Z]+(?![a-z])|\d+',n)]
STOP={'the','a','of','draw','set','get','on','to','in','by','g','k','is','unused','cleared'}
out=[]
for old,new,kind in R:
    # 1) the old identifier itself (fields: as a member)
    pat=re.compile(r'(->|\.)\s*%s\b'%old) if kind.startswith('field') else re.compile(r'\b%s\b'%re.escape(old))
    # 2) the old idea: adjacent word pairs of the old name not both in the new one
    ow,nw=words(old),set(words(new))
    phrases=[]
    for a,b in zip(ow,ow[1:]):
        if (a in nw and b in nw) or a in STOP and b in STOP: continue
        phrases.append(r'\b%s[\s_-]*%s'%(a,b))
    if len(ow)==1 and ow[0] not in nw: phrases.append(r'\b%s\b'%ow[0])
    ph=re.compile('|'.join(phrases),re.I) if phrases else None
    for f,L in texts.items():
        for i,l in enumerate(L):
            if pat.search(l): out.append('ID  %s -> %s | %s:%d: %s'%(old,new,f,i+1,l.strip()[:220]))
            elif ph and ph.search(l): out.append('IDEA %s -> %s | %s:%d: %s'%(old,new,f,i+1,l.strip()[:220]))
open(sys.argv[1],'w',encoding='utf-8').write('\n'.join(out))
import collections
print(len(R),'renames;',sum(1 for o in out if o.startswith('ID ')),'identifier hits;',sum(1 for o in out if o.startswith('IDEA')),'idea hits')
c=collections.Counter(o.split(' |')[0] for o in out); print('\n'.join('%4d %s'%(n,k) for k,n in c.most_common()))
