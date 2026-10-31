r"""list_placeholders.py prefix ...: the src functions still named prefix_<address>, with their description comments"""
import glob, re, sys
pre = sys.argv[1:]
for f in sorted(glob.glob('src/**/*.c', recursive=True)):
    lines = open(f).read().split('\n')
    for i, l in enumerate(lines):
        m = re.match(r'^\w[\w \*]*?\((\w+)\)\((.*)', l)
        if not m or not re.fullmatch(r'(%s)_[0-9a-f]{6,8}' % '|'.join(pre), m.group(1)):
            continue
        com, j = [], i - 1
        while j >= 0 and (lines[j].startswith('/*') or lines[j].startswith('   ')):
            com.insert(0, lines[j].strip())
            if lines[j].startswith('/*'):
                break
            j -= 1
        tail = re.search(r'/\*(.*?)\*/\s*$', l)
        desc = ' '.join(com) or (tail.group(1).strip() if tail else '')
        print('%s %s(%s | %s' % (m.group(1), f[4:], m.group(2)[:60], desc[:260]))
