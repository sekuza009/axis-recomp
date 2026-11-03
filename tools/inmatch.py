"""inmatch.py screenshot.png... [--any]: whether a play test's screenshot shows the player in a match - the HUD's
armour / shield panel (dark blue, bottom left) - as "IN MATCH" or "NOT IN MATCH" (the loading screen, the free
camera with nobody spawned), with the panel area's blue share. --any: one verdict for all the screenshots given
(play.sh passes both match shots): in a match when any of them shows the panel.

A screen tint (a hit's red, a respawn's white fade) or the death screen ("Press fire button to start") hides the
panel, so a run can be in a match with neither shot showing it. When the team scoreboard (top centre: a red box,
then a blue one) is up the verdict says so - "NOT IN MATCH (scoreboard up: look at the shots)" - but it is NOT a
pass: the free camera with nobody spawned shows the scoreboard too (2026-11-03, sp_skirmish-loading.png)."""
import sys
from PIL import Image


def pixels(im):
	return list(im.get_flattened_data()) if hasattr(im, 'get_flattened_data') else list(im.getdata())


def blue_share(path):
	im = Image.open(path).convert('RGB')
	w, h = im.size
	box = im.crop((int(w * 0.04), int(h * 0.88), int(w * 0.27), int(h * 0.96))).resize((64, 16))
	px = pixels(box)
	return sum(1 for r, g, b in px if b > 50 and b > r + 30 and b > g + 25) / len(px)


def scoreboard(path):
	"""the team scoreboard's two boxes (their mean colours): the left one clearly red, the right one clearly blue"""
	im = Image.open(path).convert('RGB')
	w, h = im.size

	def mean(x0, x1):
		px = pixels(im.crop((int(w * x0), int(h * 0.016), int(w * x1), int(h * 0.05))))
		return [sum(p[c] for p in px) / len(px) for c in range(3)]
	r, g, b = mean(0.447, 0.497)
	r2, g2, b2 = mean(0.503, 0.553)
	return r > g + 60 and r > b + 60 and b2 > r2 + 40 and b2 > g2 + 20


def verdict(paths):
	shares = [blue_share(p) for p in paths]
	best = max(shares)
	if best > 0.25:
		return 'IN MATCH', best
	if any(scoreboard(p) for p in paths):
		return 'NOT IN MATCH (scoreboard up: look at the shots)', best
	return 'NOT IN MATCH', best


if __name__ == '__main__':
	files = [a for a in sys.argv[1:] if not a.startswith('--')]
	if '--any' in sys.argv:
		v, s = verdict(files)
		print('%s %.2f %s' % (v, s, ' '.join(files)))
	else:
		for p in files:
			v, s = verdict([p])
			print('%s %.2f %s' % (v, s, p))
