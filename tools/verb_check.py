r"""verb_check.py: a second check of function names, against their code rather than their comments. A name whose verb
promises an action (draw, load / read, write / save, send, free / release, clear / reset, play, open, close) is
listed when the function's body shows nothing of the kind: no call or statement matching that action (the calls
count by their names too, so a draw that only calls other draw functions passes). For review by hand."""
import glob, os, re

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
DEF = re.compile(r'^\w[\w \*]*?\((\w+)\)\(', re.M)
VERBS = {
	'draw|render|show|display|print|blit|paint': r'\bgl[A-Z]|text_\w+|gfx_\w+|_draw\w*|draw\w*|menu_vertex|quad|hud_\w+|render\w*|tex_bind|vertex|_show\w*|Swap|sprite|panel\w*|layer\w*|frame\w*',
	'load|read|parse|import': r'fread|fopen|fgets|fscanf|read\w*|load\w*|_parse\w*|RegQuery|strtok|atoi|atof|fgetc|getc|scanf|memcpy|copy\w*|strcpy|Scrambled',
	'write|save|store|export|dump': r'fwrite|fputs|FPUTS|fprintf|write\w*|save\w*|RegSet|Scrambled|fclose|store\w*|memcpy|copy\w*|strcpy|\w+ = ',
	'send|post|broadcast|announce': r'send\w*|Send\w*|post\w*|Post\w*|packet|dplay\w*|net_\w+|socket|msg_\w+',
	'free|release|destroy|delete|dtor': r'free\w*|Free\w*|Release\w*|release\w*|delete\w*|Delete\w*|destroy\w*|dtor\w*|Close\w*|close\w*|= 0|clear\w*',
	'clear|reset|zero|empty': r'= 0|= -1|memset|clear\w*|zero\w*|fill\w*|reset\w*|= NULL|= 0x0',
	'play': r'sound_\w+|music_\w+|dsbuf\w*|Play\w*|play\w*|mci\w*|stream\w*',
	'open': r'open\w*|Open\w*|fopen|= 1|show\w*|layout\w*|enter\w*|state\w*',
	'close|quit|exit|leave': r'close\w*|Close\w*|= 0|Quit\w*|quit\w*|exit\w*|Exit\w*|leave\w*|state\w*|Destroy\w*|return\w*',
}


def body(t, start):
	i = t.find('{', start)
	if i < 0:
		return ''
	depth = 0
	for j in range(i, len(t)):
		if t[j] == '{':
			depth += 1
		elif t[j] == '}':
			depth -= 1
			if depth == 0:
				return t[i:j + 1]
	return t[i:]


def strip_comments(s):
	return re.sub(r'/\*.*?\*/', ' ', s, flags=re.S)


rows = []
for f in glob.glob('src/**/*.c', recursive=True):
	if os.sep + 'data' + os.sep in f:
		continue
	t = open(f, encoding='latin-1').read()
	for m in DEF.finditer(t):
		name = m.group(1)
		words = [w.lower() for w in re.findall(r'[A-Z]?[a-z]+', name.split('_', 1)[-1])]
		code = strip_comments(body(t, m.end()))
		for verbs, evidence in VERBS.items():
			vs = verbs.split('|')
			if any(w in vs for w in words[:1]):   # (the name's first word after the prefix: its verb)
				if not re.search(evidence, code):
					rows.append('%-34s %-10s %s' % (name, words[0], f.replace(os.sep, '/')))
for r in sorted(rows):
	print(r)
print(len(rows), 'names whose verb the body does not show')
