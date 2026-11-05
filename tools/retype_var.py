r"""retype_var.py <file.c> <function> <var> <Type> [--dry]: in one function, a byte pointer local `u8 *var` used
through ((Type *)var) casts becomes `Type *var`:
  declarations   u8 *var = e;   ->  Type *var = (Type *)(e);     (u8 *var;  /  = NULL / = 0 kept as they are)
  assignments    var = e;       ->  var = (Type *)(e);
  the casts      ((Type *)var)  ->  var
  any other use  var            ->  ((u8 *)var)   (byte arithmetic, calls taking bytes: unchanged meaning)
A declarator list (u8 *a = .., *var = ..) or a parameter is refused. Check with tools/objcmp.py: the code is the same."""
import os, re, sys
os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
path, fn, var, T = sys.argv[1:5]
dry = '--dry' in sys.argv
t = open(path, encoding='latin-1', newline='').read()
nl = '\r\n' if '\r\n' in t else '\n'
t = t.replace('\r\n', '\n')
m = re.search(r'\(%s\)\s*\([^)]*\)\s*\n\{' % re.escape(fn), t)
if not m:
	sys.exit('no function ' + fn)
a = m.end() - 1
depth = 0
for b in range(a, len(t)):
	depth += {'{': 1, '}': -1}.get(t[b], 0)
	if depth == 0:
		break
body = t[a:b]
V = re.escape(var)
if re.search(r',\s*\*\s*%s\b' % V, body) or re.search(r'\bu8\s*\*\s*\w+\s*=[^;]*,\s*\*?\s*%s\b' % V, body):
	sys.exit('a declarator list holds %s: by hand' % var)
if not re.search(r'\bu8\s*\*\s*%s\b' % V, body):
	sys.exit('%s is not a u8 * local of %s' % (var, fn))
# a name declared again in the function (another block's variable, any type): its uses cannot be told apart here
decls = re.findall(r'\b(?:const\s+)?(?:u8|u16|u32|int|float|char|void|[A-Z]\w*)\s*\*+\s*%s\s*[=;,\[)]' % V, body)
decls += re.findall(r'\b(?:int|float|u32|char|long)\s+%s\s*[=;,\[]' % V, body)
if len(decls) > 1:
	sys.exit('%s is declared %d times in %s: by hand' % (var, len(decls), fn))


def rhs_end(s, i):
	d = 0
	while i < len(s):
		c = s[i]
		if c in '([{':
			d += 1
		elif c in ')]}':
			if d == 0:
				return i
			d -= 1
		elif c in ',;' and d == 0:
			return i
		i += 1
	return i


out, i, n_cast, n_bare = [], 0, 0, 0
PROT = '\x01'
# 1. the casts
body = re.sub(r'\(\(%s\s*\*\)\s*%s\)' % (re.escape(T), V), PROT, body)
n_cast = body.count(PROT)
# 2. declarations and assignments
res = []
pos = 0
for mm in re.finditer(r'(\bu8\s*\*\s*%s\b|(?<![\w.>])%s\b)(\s*=(?!=)\s*)' % (V, V), body):
	if mm.start() < pos:
		continue
	start_rhs = mm.end()
	end = rhs_end(body, start_rhs)
	rhs = body[start_rhs:end].strip()
	lhs = '%s *%s' % (T, PROT + 'V') if mm.group(1).startswith('u8') else PROT + 'V'
	if rhs in ('NULL', '0'):
		new_rhs = body[start_rhs:end]
	else:
		new_rhs = '(%s *)(%s)' % (T, rhs) if not re.fullmatch(r'\w+', rhs) else '(%s *)%s' % (T, rhs)
	res.append(body[pos:mm.start()] + lhs + mm.group(2) + new_rhs)
	pos = end
res.append(body[pos:])
body = ''.join(res)
body = re.sub(r'\bu8\s*\*\s*%s\b' % V, '%s *%s' % (T, PROT + 'V'), body)   # (u8 *var; with no initialiser)
# 3. other bare uses: as bytes
def bare(mo):
	global n_bare
	n_bare += 1
	return '((u8 *)' + PROT + 'V)'
body = re.sub(r'(?<![\w.>\x01])%s\b' % V, bare, body)
body = body.replace(PROT + 'V', var).replace(PROT, var)
nt = (t[:a] + body + t[b:]).replace('\n', nl)
print('%s %s: %d casts, %d byte uses wrapped' % (fn, var, n_cast, n_bare))
if not dry:
	open(path, 'w', encoding='latin-1', newline='').write(nt)
