"""rename_files.py: the source-file renames of the type/file audit (group R): git mv, new header comments (R's text,
wrapped), and every reference in src/, the READMEs, recomp.c and the trace tools updated."""
import os, re, subprocess, textwrap

R = 'C:/Users/Alexander/Desktop/Axis/recomp/'
EDITS = 'C:/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/audit3/rest_R_edits.tsv'
MOVES = [  # order matters: text_passes.c is freed before text_codes.c takes its name
	('text/text_passes.c', 'text/text_draw.c'),
	('text/text_codes.c', 'text/text_passes.c'),
	('menu/armc_stats.c', 'menu/armc_parts_screen.c'),
	('replay/replay_message.c', 'hud/hud_message_box.c'),
	('net/net_tables.c', 'net/network.c'),
	('load/names.c', 'load/textures.c'),
	('load/skel_data.c', 'load/shapes_skeletons.c'),
	('menu/menu_records.c', 'menu/menu_misc.c'),
	('menu/arena_maps.c', 'menu/map_list.c'),
	('app/objects.c', 'app/destructors.c'),
	('load/space_pools.c', 'collision/collision_space.c'),
	('load/collision_tris.c', 'collision/collision_tris.c'),
]
# references: (regex, replacement), applied in this order to comments and scripts
REFS = [
	(r'\btext/text_passes\.c\b', 'text/text_draw.c'), (r'(?<![\w/])text_passes\.c\b', 'text_draw.c'),
	(r'\btext/text_codes\.c\b', 'text/text_passes.c'), (r'(?<![\w/])text_codes\.c\b', 'text_passes.c'),
	(r'\b(?:menu/)?armc_stats\.c\b', lambda m: m.group(0).replace('armc_stats.c', 'armc_parts_screen.c')),
	(r'\breplay/replay_message\.c\b', 'hud/hud_message_box.c'), (r'(?<![\w/])replay_message\.c\b', 'hud_message_box.c'),
	(r'\bnet_tables\.c\b', 'network.c'),
	(r'\bload/names\.c\b', 'load/textures.c'), (r'(?<![\w/])names\.c\b', 'textures.c'),
	(r'\bload/skel_data\.c\b', 'load/shapes_skeletons.c'), (r'(?<![\w/])skel_data\.c\b', 'shapes_skeletons.c'),
	(r'\bmenu_records(_test)?\.c\b', lambda m: 'menu_misc%s.c' % (m.group(1) or '')),
	(r'\bmenu_menu_records\.o\b', 'menu_menu_misc.o'), (r'\bmenu_records_test\.o\b', 'menu_misc_test.o'),
	(r'\barena_maps\.c\b', 'map_list.c'),
	(r'\bapp/objects\.c\b', 'app/destructors.c'),
	(r'\bload/space_pools\.c\b', 'collision/collision_space.c'), (r'(?<![\w/])space_pools\.c\b', 'collision_space.c'),
	(r'\bload/collision_tris\.c\b', 'collision/collision_tris.c'),
]

def git(*a):
	subprocess.run(['git', '-C', R] + list(a), check=True)

os.makedirs(R + 'src/collision', exist_ok=True)
for a, b in MOVES:
	git('mv', 'src/' + a, 'src/' + b)
if os.path.isdir(R + 'src/replay') and not os.listdir(R + 'src/replay'):
	os.rmdir(R + 'src/replay')

# references everywhere else (not the history: tools/names csv / audit reports, batches/)
targets = []
for root, dirs, files in os.walk(R + 'src'):
	if os.sep + 'data' in root.replace('/', os.sep):
		continue
	targets += [os.path.join(root, f) for f in files if f.endswith(('.c', '.h', '.fields', '.txt'))]
targets += [R + p for p in ('README.txt', 'recomp.c', 'tools/ftrace/build.sh', 'tools/rtrace/build.sh',
                            'tools/rtrace/README.txt', 'tools/srcaudit.py')]
for full in targets:
	if not os.path.exists(full):
		continue
	t = open(full, encoding='latin-1', newline='').read()
	nt = t
	for a, b in REFS:
		nt = re.sub(a, b, nt)
	if nt != t:
		open(full, 'w', encoding='latin-1', newline='').write(nt)
		print('refs', os.path.relpath(full, R))

# new header comments
newhdr = {}
for line in open(EDITS, encoding='latin-1'):
	f = line.rstrip('\r\n').split('\t')
	if len(f) >= 4 and f[0] == 'file' and f[3].strip():
		newhdr[f[2]] = f[3].strip()
for path, text in newhdr.items():
	full = R + 'src/' + path
	if not os.path.exists(full):
		print('NO FILE', path); continue
	t = open(full, encoding='latin-1', newline='').read()
	nl = '\r\n' if '\r\n' in t else '\n'
	if not t.startswith('/*'):
		print('NO HEADER', path); continue
	end = t.index('*/') + 2
	body = textwrap.wrap(text, 115, break_on_hyphens=False, break_long_words=False)
	hdr = '/* ' + body[0] + ''.join(nl + '   ' + l for l in body[1:]) + ' */'
	t = hdr + t[end:]
	open(full, 'w', encoding='latin-1', newline='').write(t)
# the header's own file name, where R gave no new text
for a, b in MOVES:
	full = R + 'src/' + b
	t = open(full, encoding='latin-1', newline='').read()
	old, new = os.path.basename(a), os.path.basename(b)
	if t.startswith('/* ' + old + ':'):
		t = '/* ' + new + ':' + t[len('/* ' + old + ':'):]
		open(full, 'w', encoding='latin-1', newline='').write(t)

