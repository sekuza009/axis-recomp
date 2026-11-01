"""inmatch.py screenshot.png...: whether a play test's screenshot shows the player in a match - the HUD's armour /
shield panel (dark blue, bottom left) - as "IN MATCH" or "NOT IN MATCH" (the loading screen, the free camera with
nobody spawned), with the panel area's blue share"""
import sys
from PIL import Image

def blue_share(path):
	im = Image.open(path).convert('RGB')
	w, h = im.size
	box = im.crop((int(w * 0.04), int(h * 0.88), int(w * 0.27), int(h * 0.96))).resize((64, 16))
	px = list(box.get_flattened_data()) if hasattr(box, 'get_flattened_data') else list(box.getdata())
	return sum(1 for r, g, b in px if b > 50 and b > r + 30 and b > g + 25) / len(px)

if __name__ == '__main__':
	for p in sys.argv[1:]:
		s = blue_share(p)
		print('%s %.2f %s' % ('IN MATCH' if s > 0.25 else 'NOT IN MATCH', s, p))
