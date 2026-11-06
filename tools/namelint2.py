import re
exec(open(__import__('os').path.join(__import__('os').path.dirname(__import__('os').path.abspath(__file__)), 'namelint.py')).read().split('# ---- source bodies')[0])
INPUT = lambda s: any(x.startswith('input_') or x in ('GetAsyncKeyState', 'GetKeyState') for x in s)
DRAWW = ('draw', 'render', 'paint', 'gl', 'gfx', 'hud', 'text', 'print', 'font', 'frame', 'view', 'shade', 'fog', 'tex',
         'texture', 'light', 'camera', 'projection', 'matrix', 'clear', 'blit', 'fill', 'rect', 'quad', 'line', 'vertex',
         'screen', 'flush', 'swap', 'show', 'scissor', 'viewport', 'fade', 'overlay', 'flash', 'display', 'icon',
         'cursor', 'box', 'bar', 'board', 'preview', 'map', 'image', 'shape', 'colour', 'color', 'billboard', 'sky', 'bind')
for name, f in sorted(F.items()):
    if name.startswith(('FUN_', 'crt_', '_')):
        continue
    w = words(name); R = reach(name)
    if w and w[-1] in ('keys',) and not INPUT(R):
        flag('keys: never reads input', name, ' '.join(sorted(f['callees']))[:120])
    if w and w[-1] in ('clicks', 'mouse') and not INPUT(R) and 'GetCursorPos' not in R:
        flag('clicks/mouse: never reads input', name, ' '.join(sorted(f['callees']))[:120])
    direct = {a for a in f['apis'] if a.startswith(('gl', 'wgl'))}
    if direct and not any(x in DRAWW for x in [y.lower() for y in w] + [name.split('_')[0].lower()]):
        flag('calls OpenGL, name says nothing of drawing', name, ' '.join(sorted(direct))[:100])
    fa = f['apis'] & {'CreateFileA', 'ReadFile', 'WriteFile', '_lopen', 'OpenFile'} | (f['callees'] & {'fopen'})
    if fa and not any(x in ('load', 'read', 'write', 'save', 'file', 'open', 'dat', 'cfg', 'init', 'log', 'wav', 'exists',
                            'store', 'data', 'export', 'import', 'find', 'record', 'make', 'table', 'disk', 'drive', 'cd',
                            'startup', 'replay', 'movie', 'scramble', 'reg', 'error', 'profile', 'profiles', 'ini', 'messages')
                      for x in w + [name.split('_')[0].lower()]):
        flag('opens files, name says nothing of files', name, ' '.join(sorted(fa)))
for rule in sorted(issues):
    print('\n## %s (%d)' % (rule, len(issues[rule])))
    for n, why in issues[rule]:
        print('  %-36s %s' % (n, why))
