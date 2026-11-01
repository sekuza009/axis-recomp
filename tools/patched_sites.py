r"""patched_sites.py: the call sites the patch layer (axisnet_recomp.c) retargets - "{0x<site>, 0x<target>, ...}"
entries of its hook tables - and whether the rebuilt C follows each: a PATCHED_CALL / PATCHED_THISCALL (or another
mention) of the site in src/, else the C function that holds the site (decomp/out/functions.csv) and whether that
function calls the target directly. A direct call there skips the patch (as the KYRIE catalogue did)."""
import bisect, csv, glob, os, re

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
src = {f: open(f, 'rb').read().decode('latin-1') for f in glob.glob('src/**/*.[ch]', recursive=True) if os.sep + 'data' + os.sep not in f}
alltext = '\n'.join(src.values())
pl = open('axisnet_recomp.c', 'rb').read().decode('latin-1')
sites = {(int(a, 16), int(b, 16)) for a, b in re.findall(r'\{\s*(0x4[0-9a-f]{5}),\s*(0x4[0-9a-f]{5}),\s*(?:\(void \*\))?\w+\s*\}', pl)}
# single sites: "IMG(0x...);   /* call 0x<target> ..." (one call rewritten in place)
sites |= {(int(a, 16), int(b, 16)) for a, b in re.findall(r'IMG\((0x4[0-9a-f]{5})\);\s*/\*\s*call (0x4[0-9a-f]{5})', pl)}
sites = sorted(sites)
rows = sorted((int(r['address'], 16), int(r['size']), r['name']) for r in csv.DictReader(open('../decomp/out/functions.csv')))
starts = [r[0] for r in rows]
names = {int(a, 16): n for n, a in re.findall(r'\b(\w+)\s*,\s*(0x4[0-9a-f]{5})\)', alltext)}
bad = 0
for site, target in sites:
	if re.search(r'\b0x0*%x\b' % site, alltext):
		continue   # (named in src: followed)
	k = bisect.bisect_right(starts, site) - 1
	fn = rows[k][2] if k >= 0 and rows[k][0] <= site < rows[k][0] + rows[k][1] else '?'
	body = ''
	for t in src.values():
		m = re.search(r'\(%s\)\s*\(' % re.escape(fn), t)
		if m:
			end = t.find('\n}', m.end())
			body = t[m.start():end]
			break
	tname = names.get(target, '0x%x' % target)
	direct = bool(re.search(r'\b%s\b|0x0*%x\b' % (re.escape(tname), target), body))
	print('%s site 0x%x (-> 0x%x %s) in %s: %s' % ('SKIPPED' if direct else '?      ', site, target, tname, fn,
	      'the C calls it directly' if direct else 'no direct call found (inlined, or not rebuilt as a call)'))
	bad += direct
print('%d call sites; %d skipped by a direct call' % (len(sites), bad))
