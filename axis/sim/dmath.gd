class_name AxisDMath
extends RefCounted
## Sine, cosine and arctangent that come out the same on every machine, for the simulation (multiplayer across
## platforms). Godot's sin / cos / atan2 come from the platform's maths library, which may differ in the last bit
## between Windows, Linux and macOS builds; these are fdlibm's (FreeBSD msun: k_sin.c, k_cos.c, e_rem_pio2.c,
## s_atan.c, e_atan2.c), written with only + - * / on doubles, which IEEE 754 fixes everywhere. (GDScript runs each
## operation on its own, so nothing is fused into a multiply-add.) All within an ulp of the true value.
##
## The argument reduction is Cody-Waite's with pi/2 in three parts, the whole of it every time (fdlibm's medium
## case without its shortcuts): exact enough for |x| up to about 1e9, far past anything the game passes.
##
## The constants are given by their bits: Godot's parser reads some long decimal literals one ulp off (it read
## pi/2's first part, 1.57079632673412561417, as the next double up), and every platform must hold the same ones.

## a double from its IEEE 754 bits (the high and low words, as fdlibm gives them)
static func _bits(hi: int, lo: int) -> float:
	var a := PackedByteArray()
	a.resize(8)
	a.encode_u32(0, lo)
	a.encode_u32(4, hi)
	return a.decode_double(0)


static var S1 := _bits(0xbfc55555, 0x55555549)   # -0.16666666666666632
static var S2 := _bits(0x3f811111, 0x1110f8a6)   # 0.00833333333332249
static var S3 := _bits(0xbf2a01a0, 0x19c161d5)   # -0.0001984126982985795
static var S4 := _bits(0x3ec71de3, 0x57b1fe7d)   # 2.7557313707070068e-06
static var S5 := _bits(0xbe5ae5e6, 0x8a2b9ceb)   # -2.5050760253406863e-08
static var S6 := _bits(0x3de5d93a, 0x5acfd57c)   # 1.58969099521155e-10
static var C1 := _bits(0x3fa55555, 0x5555554c)   # 0.0416666666666666
static var C2 := _bits(0xbf56c16c, 0x16c15177)   # -0.001388888888887411
static var C3 := _bits(0x3efa01a0, 0x19cb1590)   # 2.480158728947673e-05
static var C4 := _bits(0xbe927e4f, 0x809c52ad)   # -2.7557314351390663e-07
static var C5 := _bits(0x3e21ee9e, 0xbdb4b1c4)   # 2.087572321298175e-09
static var C6 := _bits(0xbda8fae9, 0xbe8838d4)   # -1.1359647557788195e-11
static var INV_PIO2 := _bits(0x3fe45f30, 0x6dc9c883)   # 0.6366197723675814
static var PIO2_1 := _bits(0x3ff921fb, 0x54400000)   # 1.5707963267341256
static var PIO2_1T := _bits(0x3dd0b461, 0x1a626331)   # 6.077100506506192e-11
static var PIO2_2 := _bits(0x3dd0b461, 0x1a600000)   # 6.077100506303966e-11
static var PIO2_2T := _bits(0x3ba3198a, 0x2e037073)   # 2.0222662487959506e-21
static var PIO2_3 := _bits(0x3ba3198a, 0x2e000000)   # 2.0222662487111665e-21
static var PIO2_3T := _bits(0x397b839a, 0x252049c1)   # 8.4784276603689e-32
static var PIO4 := _bits(0x3fe921fb, 0x54442d18)   # 0.7853981633974483
static var TWO_66 := _bits(0x44100000, 0)
static var TWO_60 := _bits(0x43b00000, 0)
static var TWO_M27 := _bits(0x3e400000, 0)
static var TWO_M60 := _bits(0x3c300000, 0)
const ROUNDER := 6755399441055744.0   # 1.5 x 2^52: x + this - this rounds x to a whole number (ties to even)

static var ATAN_HI: Array[float] = [_bits(0x3fddac67, 0x0561bb4f), _bits(0x3fe921fb, 0x54442d18), _bits(0x3fef730b, 0xd281f69b), _bits(0x3ff921fb, 0x54442d18)]
static var ATAN_LO: Array[float] = [_bits(0x3c7a2b7f, 0x222f65e2), _bits(0x3c81a626, 0x33145c07), _bits(0x3c700788, 0x7af0cbbd), _bits(0x3c91a626, 0x33145c07)]
static var AT: Array[float] = [_bits(0x3fd55555, 0x5555550d), _bits(0xbfc99999, 0x9998ebc4), _bits(0x3fc24924, 0x920083ff), _bits(0xbfbc71c6, 0xfe231671), _bits(0x3fb745cd, 0xc54c206e), _bits(0xbfb3b0f2, 0xaf749a6d), _bits(0x3fb10d66, 0xa0d03d51), _bits(0xbfadde2d, 0x52defd9a), _bits(0x3fa97b4b, 0x24760deb), _bits(0xbfa2b444, 0x2c6a6c2f), _bits(0x3f90ad3a, 0xe322da11)]
static var PI_HI := _bits(0x400921fb, 0x54442d18)   # 3.141592653589793
static var PI_LO := _bits(0x3ca1a626, 0x33145c07)   # 1.2246467991473532e-16


## __kernel_sin: sin(x + y) for |x| <= pi/4 (y the tail of the reduced argument)
static func _ksin(x: float, y: float) -> float:
	var z := x * x
	var v := z * x
	var r := S2 + z * (S3 + z * (S4 + z * (S5 + z * S6)))
	return x - ((z * (0.5 * y - v * r) - y) - v * S1)


## __kernel_cos: cos(x + y) for |x| <= pi/4
static func _kcos(x: float, y: float) -> float:
	var z := x * x
	var w := z * z
	var r := z * (C1 + z * (C2 + z * C3)) + w * w * (C4 + z * (C5 + z * C6))
	var hz := 0.5 * z
	w = 1.0 - hz
	return w + (((1.0 - w) - hz) + (z * r - x * y))


## x as n x pi/2 + (y0 + y1): [n, y0, y1]
static func _reduce(x: float) -> Array:
	if absf(x) <= PIO4:
		return [0, x, 0.0]
	var fn := (x * INV_PIO2 + ROUNDER) - ROUNDER
	var r := x - fn * PIO2_1
	var w := fn * PIO2_1T
	var t := r
	w = fn * PIO2_2
	r = t - w
	w = fn * PIO2_2T - ((t - r) - w)
	t = r
	w = fn * PIO2_3
	r = t - w
	w = fn * PIO2_3T - ((t - r) - w)
	var y0 := r - w
	return [int(fn), y0, (r - y0) - w]


static func sin_d(x: float) -> float:
	if is_nan(x) or is_inf(x):
		return NAN
	var q := _reduce(x)
	match int(q[0]) & 3:
		0: return _ksin(q[1], q[2])
		1: return _kcos(q[1], q[2])
		2: return -_ksin(q[1], q[2])
	return -_kcos(q[1], q[2])


static func cos_d(x: float) -> float:
	if is_nan(x) or is_inf(x):
		return NAN
	var q := _reduce(x)
	match int(q[0]) & 3:
		0: return _kcos(q[1], q[2])
		1: return -_ksin(q[1], q[2])
		2: return -_kcos(q[1], q[2])
	return _ksin(q[1], q[2])


static func atan_d(x: float) -> float:
	if is_nan(x):
		return x
	var neg := x < 0.0
	var ax := absf(x)
	if ax >= TWO_66:
		return -(ATAN_HI[3] + ATAN_LO[3]) if neg else ATAN_HI[3] + ATAN_LO[3]
	var id := -1
	if ax < 0.4375:
		if ax < TWO_M27:
			return x
	elif ax < 1.1875:
		if ax < 0.6875:
			id = 0
			ax = (2.0 * ax - 1.0) / (2.0 + ax)
		else:
			id = 1
			ax = (ax - 1.0) / (ax + 1.0)
	elif ax < 2.4375:
		id = 2
		ax = (ax - 1.5) / (1.0 + 1.5 * ax)
	else:
		id = 3
		ax = -1.0 / ax
	var z := ax * ax
	var w := z * z
	var s1: float = z * (AT[0] + w * (AT[2] + w * (AT[4] + w * (AT[6] + w * (AT[8] + w * AT[10])))))
	var s2: float = w * (AT[1] + w * (AT[3] + w * (AT[5] + w * (AT[7] + w * AT[9]))))
	if id < 0:
		var r := ax - ax * (s1 + s2)
		return -r if neg else r
	var zz: float = ATAN_HI[id] - ((ax * (s1 + s2) - ATAN_LO[id]) - ax)
	return -zz if neg else zz


static func _neg_sign(v: float) -> bool:
	return v < 0.0 or (v == 0.0 and 1.0 / v < 0.0)


static func atan2_d(y: float, x: float) -> float:
	if is_nan(x) or is_nan(y):
		return NAN
	if x == 1.0:
		return atan_d(y)
	var m := (2 if _neg_sign(x) else 0) + (1 if _neg_sign(y) else 0)
	if y == 0.0:
		match m:
			0, 1: return y
			2: return PI_HI
		return -PI_HI
	if x == 0.0:
		return -PI_HI * 0.5 if m & 1 else PI_HI * 0.5
	if is_inf(x) or is_inf(y):   # (as fdlibm's special cases)
		if is_inf(x) and is_inf(y):
			var v := PI_HI * 0.25 if x > 0.0 else PI_HI * 0.75
			return -v if y < 0.0 else v
		if is_inf(y):
			return -PI_HI * 0.5 if y < 0.0 else PI_HI * 0.5
		if x > 0.0:
			return -0.0 if y < 0.0 else 0.0
		return -PI_HI if y < 0.0 else PI_HI
	var q := absf(y / x)
	var z := 0.0
	if q > TWO_60:
		z = PI_HI * 0.5 + 0.5 * PI_LO
	elif x < 0.0 and q < TWO_M60:
		z = 0.0
	else:
		z = atan_d(q)
	match m:
		0: return z
		1: return -z
		2: return PI_HI - (z - PI_LO)
	return (z - PI_LO) - PI_HI
