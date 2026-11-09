"""fit.py: which formula the OpenGL driver uses for glRotatef (and gluLookAt), checked bit for bit against
build/glprobe.exe's answers (tools/glprobe/glprobe.c), for standalone/glstate.c. Prints each candidate's matches."""
import math, os, random, struct, subprocess, sys
import numpy as np

f32 = np.float32
R = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..')
random.seed(7)


def tobits(v):
	return struct.unpack('<I', struct.pack('<f', float(v)))[0]


cases = []
for i in range(3000):
	k = i % 6
	a = f32(random.uniform(-360, 360))
	if k == 0:   # a general axis, unit-ish
		v = [random.uniform(-1, 1) for _ in range(3)]
		n = math.sqrt(sum(x * x for x in v))
		ax = [f32(x / n) for x in v]
	elif k == 1:   # a general axis, not unit
		ax = [f32(random.uniform(-3, 3)) for _ in range(3)]
	elif k == 2:   # x-aligned, not quite unit
		ax = [f32(random.choice([-1, 1]) * random.uniform(0.99998, 1.00002)), f32(0), f32(0)]
	elif k == 3:
		ax = [f32(0), f32(random.choice([-1, 1]) * random.uniform(0.99998, 1.00002)), f32(0)]
	elif k == 4:
		ax = [f32(0), f32(0), f32(random.choice([-1, 1]) * random.uniform(0.99998, 1.00002))]
	else:   # exactly unit aligned
		ax = [f32(0), f32(0), f32(0)]
		ax[random.randrange(3)] = f32(random.choice([-1, 1]))
	cases.append((a, ax))
inp = ''.join('R %.9g %.9g %.9g %.9g\n' % (a, *ax) for a, ax in cases)
out = subprocess.run([os.path.join(R, 'build', 'glprobe.exe')], input=inp, capture_output=True, text=True).stdout.split('\n')
drv = [[int(w, 16) for w in line.split()] for line in out if line.strip()]
assert len(drv) == len(cases), (len(drv), len(cases))

D2R_F = float(f32(math.pi / 180))


def sincos(a):
	r = float(a) * D2R_F
	return f32(math.sin(r)), f32(math.cos(r))


def general(a, x, y, z, norm):
	s, c = sincos(a)
	if norm == 'sqrt_div':
		mag = f32(np.sqrt(f32(f32(f32(x * x) + f32(y * y)) + f32(z * z))))
		x, y, z = f32(x / mag), f32(y / mag), f32(z / mag)
	elif norm == 'rsqrt_mul':
		inv = f32(f32(1) / f32(np.sqrt(f32(f32(f32(x * x) + f32(y * y)) + f32(z * z)))))
		x, y, z = f32(x * inv), f32(y * inv), f32(z * inv)
	elif norm == 'dbl':
		mag = math.sqrt(float(x) ** 2 + float(y) ** 2 + float(z) ** 2)
		x, y, z = f32(float(x) / mag), f32(float(y) / mag), f32(float(z) / mag)
	elif norm == 'dbl_all':
		mag = math.sqrt(float(x) ** 2 + float(y) ** 2 + float(z) ** 2)
		X, Y, Z = float(x) / mag, float(y) / mag, float(z) / mag
		r = float(a) * D2R_F
		S, C = math.sin(r), math.cos(r)
		o = 1 - C
		m = [X * X * o + C, Y * X * o + Z * S, X * Z * o - Y * S, 0, X * Y * o - Z * S, Y * Y * o + C, Y * Z * o + X * S, 0,
		     X * Z * o + Y * S, Y * Z * o - X * S, Z * Z * o + C, 0, 0, 0, 0, 1]
		return [f32(v) for v in m]
	xx, yy, zz, xy, yz, zx = f32(x * x), f32(y * y), f32(z * z), f32(x * y), f32(y * z), f32(z * x)
	xs, ys, zs, oc = f32(x * s), f32(y * s), f32(z * s), f32(f32(1) - c)
	m = [f32(0)] * 16
	m[0] = f32(f32(oc * xx) + c); m[4] = f32(f32(oc * xy) - zs); m[8] = f32(f32(oc * zx) + ys)
	m[1] = f32(f32(oc * xy) + zs); m[5] = f32(f32(oc * yy) + c); m[9] = f32(f32(oc * yz) - xs)
	m[2] = f32(f32(oc * zx) - ys); m[6] = f32(f32(oc * yz) + xs); m[10] = f32(f32(oc * zz) + c)
	m[15] = f32(1)
	return m


def mesa(a, x, y, z, norm):
	s, c = sincos(a)
	m = [f32(0)] * 16
	m[0] = m[5] = m[10] = m[15] = f32(1)
	if x == 0 and y == 0 and z != 0:
		m[0] = m[5] = c
		m[1], m[4] = (-s, s) if z < 0 else (s, -s)
		return m
	if x == 0 and z == 0 and y != 0:
		m[0] = m[10] = c
		m[2], m[8] = (s, -s) if y < 0 else (-s, s)
		return m
	if y == 0 and z == 0 and x != 0:
		m[5] = m[10] = c
		m[6], m[9] = (-s, s) if x < 0 else (s, -s)
		return m
	return general(a, x, y, z, norm)


cands = {}
for norm in ('sqrt_div', 'rsqrt_mul', 'dbl', 'dbl_all'):
	cands['general ' + norm] = (lambda n: lambda a, ax: general(a, *ax, n))(norm)
	cands['mesa ' + norm] = (lambda n: lambda a, ax: mesa(a, *ax, n))(norm)
kinds = ['general unit', 'general', 'x ~unit', 'y ~unit', 'z ~unit', 'aligned unit']
for name, fn in cands.items():
	by = [0] * 6
	for i, (a, ax) in enumerate(cases):
		m = fn(a, ax)
		by[i % 6] += all(tobits(m[j]) == drv[i][j] for j in range(16))
	print('%-20s' % name, ' '.join('%s %d/500' % (kinds[k], by[k]) for k in range(6)))

# ---- the sine and cosine alone, from the axis-aligned cases (x: c at [5], s at [6] with sign) ----
if '--sincos' in sys.argv:
	import itertools
	pts = []
	for i, (a, ax) in enumerate(cases):
		if i % 6 in (2, 5) and ax[1] == 0 and ax[2] == 0:
			sgn = 1 if ax[0] > 0 else -1
			c = struct.unpack('<f', struct.pack('<I', drv[i][5]))[0]
			s = struct.unpack('<f', struct.pack('<I', drv[i][6]))[0] * sgn
			pts.append((a, f32(s), f32(c)))
	print(len(pts), 'x-axis points')
	PI = math.pi
	def tryf(name, fn):
		ok = sum(1 for a, s, c in pts if fn(a) == (s, c))
		print('%-40s %d/%d' % (name, ok, len(pts)))
	tryf('dbl(a)*f32(pi/180) dbl sin', lambda a: (f32(math.sin(float(a) * D2R_F)), f32(math.cos(float(a) * D2R_F))))
	tryf('dbl(a)*pi/180', lambda a: (f32(math.sin(float(a) * PI / 180)), f32(math.cos(float(a) * PI / 180))))
	tryf('f32(a*f32 d2r) dbl sin', lambda a: (f32(math.sin(float(f32(a * f32(D2R_F))))), f32(math.cos(float(f32(a * f32(D2R_F)))))))
	def red(a):
		a = f32(a)
		return f32(math.fmod(float(a), 360.0))
	tryf('fmod360 f32, dbl*f32 d2r', lambda a: (f32(math.sin(float(red(a)) * D2R_F)), f32(math.cos(float(red(a)) * D2R_F))))
	tryf('fmod360, dbl*pi/180', lambda a: (f32(math.sin(float(red(a)) * PI / 180)), f32(math.cos(float(red(a)) * PI / 180))))
	tryf('np.sin f32 of f32 rad', lambda a: (np.sin(f32(a * f32(D2R_F))), np.cos(f32(a * f32(D2R_F)))))
	for a, s, c in pts[:6]:
		r = float(a) * D2R_F
		print('  a %.9g  drv s %.9g c %.9g | dbl s %.9g c %.9g' % (a, s, c, f32(math.sin(r)), f32(math.cos(r))))

if '--ratio' in sys.argv:
	for i, (a, ax) in enumerate(cases):
		if i % 6 == 2 and i < 200:
			x = float(ax[0])
			sgn = 1 if x > 0 else -1
			s = struct.unpack('<f', struct.pack('<I', drv[i][6]))[0] * sgn
			m0 = struct.unpack('<f', struct.pack('<I', drv[i][0]))[0]
			r = float(a) * D2R_F
			sd = math.sin(r)
			print('x %.9f  s_drv/s_dbl %.9f  1/|x| %.9f  m0 %.9g  f32(|x|*s)==drv %s  f32(s/|x|)==drv %s' % (
				x, s / sd, 1 / abs(x), m0, f32(abs(x) * sd) == f32(s), f32(sd / abs(x)) == f32(s)))

if '--dump' in sys.argv:   # the cases and the driver's answers, for fitc.c
	with open(sys.argv[sys.argv.index('--dump') + 1], 'w') as f:
		for i, (a, ax) in enumerate(cases):
			if i % 6 != 5:   # (the exactly unit aligned ones: the special case, matched already)
				f.write('%.9g %.9g %.9g %.9g %s\n' % (a, ax[0], ax[1], ax[2], ' '.join('%08x' % w for w in drv[i])))
