r"""retype_var.py <file.c> <function> <var> <Type> [--dry]: in one function, a byte pointer local `u8 *var` used
through ((Type *)var) casts becomes `Type *var`:
  declarations   u8 *var = e;   ->  Type *var = (Type *)(e);     (u8 *var;  /  = NULL / = 0 kept as they are)
  assignments    var = e;       ->  var = (Type *)(e);
  the casts      ((Type *)var)  ->  var
  any other use  var            ->  ((u8 *)var)   (byte arithmetic, calls taking bytes: unchanged meaning)
A declarator list (u8 *a = .., *var = ..) is refused. --param: a u8 * / void * parameter instead (its type in the
signature changed; refused when that would wrap more byte uses than it removes casts, unless --force), or one typed
already (its casts dropped), or one with a typed alias (the casts use the alias). Comments and string literals are never
touched. Check with tools/objcmp.py: the code is the same."""
import os, re, sys
os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
_re_sub = re.sub


def code_sub(pattern, repl, s, flags=0):
	"""re.sub on the code only: comments and string / char literals kept as they are"""
	parts = re.split(r'(/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\')', s, flags=re.S)
	return ''.join(p if i % 2 else _re_sub(pattern, repl, p, flags=flags) for i, p in enumerate(parts))


def code_findall(pattern, s):
	parts = re.split(r'(/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\')', s, flags=re.S)
	return [x for i, p in enumerate(parts) if not i % 2 for x in re.findall(pattern, p)]


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
if '--param' in sys.argv:
	# a parameter: its declared type in the signature becomes T * (const kept); casts -> var; other uses as bytes
	sig_a = t.rfind('(', 0, m.end() - 2)
	sig_a = m.start() + m.group(0).index(')') + 1
	sig = t[sig_a:a]
	pm = re.search(r'(const\s+)?(?:u8|void)\s*\*\s*%s\b' % V, sig)
	if not pm and re.search(r'\b%s\s*\*\s*%s\b' % (re.escape(T), V), sig):
		# already a T *: the casts are redundant
		n = len(re.findall(r'\(\((?:const\s+)?%s\s*\*\)\s*%s\)' % (re.escape(T), V), body))
		body = code_sub(r'\(\((?:const\s+)?%s\s*\*\)\s*%s\)' % (re.escape(T), V), var, body)
		print('%s %s: %d redundant casts dropped' % (fn, var, n))
		if not dry:
			open(path, 'w', encoding='latin-1', newline='').write((t[:a] + body + t[b:]).replace('\n', nl))
		sys.exit(0)
	if not pm:
		sys.exit('%s is not a u8 * / void * parameter of %s' % (var, fn))
	if re.search(r'\b\w+\s*\*+\s*%s\s*[=;,\[]' % V, body) or re.search(r'(?:^|[;{]|\n)\s*%s\s*(?:[-+]?=(?!=)|\+\+|--)' % V, body):
		sys.exit('%s is declared again or assigned in %s: by hand' % (var, fn))
	al = re.search(r'\n\s*(?:const\s+)?%s\s*\*\s*(\w+)\s*=\s*\((?:const\s+)?%s\s*\*\)\s*%s\s*;' % (re.escape(T), re.escape(T), V), body)
	if al:
		# a typed alias of it is there already: the casts use the alias, nothing else changes
		n = len(re.findall(r'\(\((?:const\s+)?%s\s*\*\)\s*%s\)' % (re.escape(T), V), body[al.end():]))
		body = body[:al.end()] + code_sub(r'\(\((?:const\s+)?%s\s*\*\)\s*%s\)' % (re.escape(T), V), al.group(1), body[al.end():])
		print('%s %s: %d casts -> its alias %s' % (fn, var, n, al.group(1)))
		if not dry:
			open(path, 'w', encoding='latin-1', newline='').write((t[:a] + body + t[b:]).replace('\n', nl))
		sys.exit(0)
	const = pm.group(1) or ''
	sig = sig[:pm.start()] + '%s%s *%s' % (const, T, var) + sig[pm.end():]
	n_cast = len(re.findall(r'\(\((?:const\s+)?%s\s*\*\)\s*%s\)' % (re.escape(T), V), body))
	body = code_sub(r'\(\((?:const\s+)?%s\s*\*\)\s*%s\)' % (re.escape(T), V), '\x01', body)
	n_bare = len(code_findall(r'(?<![\w.>\x01])%s\b' % V, body))
	if n_bare > n_cast and '--force' not in sys.argv:
		sys.exit('%s %s: %d byte uses for %d casts: left' % (fn, var, n_bare, n_cast))
	body = code_sub(r'(?<![\w.>\x01])%s\b' % V, '((%su8 *)\x01)' % const, body).replace('\x01', var)
	nt = (t[:sig_a] + sig + body + t[b:]).replace('\n', nl)
	print('%s %s (parameter): %d casts, %d byte uses wrapped' % (fn, var, n_cast, n_bare))
	if not dry:
		open(path, 'w', encoding='latin-1', newline='').write(nt)
	sys.exit(0)
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
body = code_sub(r'\(\(%s\s*\*\)\s*%s\)' % (re.escape(T), V), PROT, body)
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
body = code_sub(r'\bu8\s*\*\s*%s\b' % V, '%s *%s' % (T, PROT + 'V'), body)   # (u8 *var; with no initialiser)
# 3. other bare uses: as bytes
def bare(mo):
	global n_bare
	n_bare += 1
	return '((u8 *)' + PROT + 'V)'
body = code_sub(r'(?<![\w.>\x01])%s\b' % V, bare, body)
body = body.replace(PROT + 'V', var).replace(PROT, var)
nt = (t[:a] + body + t[b:]).replace('\n', nl)
print('%s %s: %d casts, %d byte uses wrapped' % (fn, var, n_cast, n_bare))
if not dry:
	open(path, 'w', encoding='latin-1', newline='').write(nt)
