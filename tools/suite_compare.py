r"""suite_compare.py [scenario...]: standalone/suite.sh's screenshots side by side - for each step one image of three
columns (the installed AxisGL.exe, AxisRC with nothing split, AxisRC), <dir>/cmp_<scenario>_<step>.png - and how
far apart they are (mean absolute difference of small greyscale copies, 0 .. 255): split vs no-split (what the
splits changed) and no-split vs original (what the rebuild already did differently)."""
import os, re, sys
from PIL import Image, ImageChops, ImageStat

D = 'C:/Users/ALEXAN~1/AppData/Local/Temp/claude/C--Users-Alexander-Desktop-Axis/0b4df063-0171-44b1-8c17-2ffdad638f27/scratchpad'
def small(p):
	return Image.open(p).convert('L').resize((96, 54))
def dist(a, b):
	return ImageStat.Stat(ImageChops.difference(small(a), small(b))).mean[0]
names = sys.argv[1:] or sorted({m.group(1) for f in os.listdir(D) for m in [re.match(r'gl_([a-z0-9]+)-', f)] if m})
for n in names:
	steps = [re.match(r'gl_%s-(\w+)\.png' % n, f).group(1) for f in sorted(os.listdir(D), key=lambda f: os.path.getmtime(os.path.join(D, f)))
	         if re.match(r'gl_%s-(\w+)\.png' % n, f)]
	print('== %s' % n)
	for s in steps:
		p = ['%s/%s_%s-%s.png' % (D, k, n, s) for k in ('gl', 'ns', 'sp')]
		if not all(os.path.exists(x) for x in p):
			print('  %-10s missing %s' % (s, ' '.join(k for k, x in zip(('gl', 'ns', 'sp'), p) if not os.path.exists(x))))
			continue
		ims = [Image.open(x).convert('RGB').resize((640, 360)) for x in p]
		out = Image.new('RGB', (640 * 3 + 20, 360), (255, 255, 255))
		for k, im in enumerate(ims):
			out.paste(im, (k * 650, 0))
		out.save('%s/cmp_%s_%s.png' % (D, n, s))
		print('  %-10s split vs no-split %5.1f   no-split vs original %5.1f' % (s, dist(p[1], p[2]), dist(p[0], p[1])))
