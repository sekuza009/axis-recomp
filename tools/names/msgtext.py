r"""msgtext.py addr...: the game's message line at a message-table address (0x80-byte slots from 0x74de24, read from
initdata/msgeng.dat as data_loadMessages does: "//" and empty lines skipped). For naming what a label shows"""
import os, sys

here = os.path.dirname(os.path.abspath(__file__))
lines = []
for line in open(os.path.join(here, '..', '..', '..', 'initdata', 'msgeng.dat'), 'rb').read().decode('latin-1').split('\n'):
	line = line.rstrip('\r')
	if line.startswith('//') or not line:
		continue
	lines.append(line[:0x7e])
for a in sys.argv[1:]:
	a = int(a, 16)
	k, off = divmod(a - 0x74de24, 0x80)
	print('0x%x  #%d%s  %s' % (a, k, '+%d' % off if off else '', lines[k] if 0 <= k < len(lines) else '?'))
