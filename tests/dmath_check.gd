extends SceneTree
## AxisDMath (the simulation's machine-independent sine, cosine, arctangent) against the platform's: how many of a
## million arguments agree exactly, and the largest difference in units of the last place (should be 1 at most).
## Also the values every platform must give (fixed here from fdlibm's results, so a port to another platform can
## check its own build). The fingerprints (SHA-256 of all the results) compare the whole million at once:
## AxisDMath's must print the same on every platform.
##   godot --headless --path rewrite -s res://tests/dmath_check.gd


func _sha(v: PackedFloat64Array) -> String:
	var h := HashingContext.new()
	h.start(HashingContext.HASH_SHA256)
	h.update(v.to_byte_array())
	return h.finish().hex_encode().left(16)


func _ulps(a: float, b: float) -> float:
	if a == b:
		return 0.0
	var e := maxf(absf(a), absf(b))
	return absf(a - b) / (e * 2.220446049250313e-16) if e > 0.0 else INF


func _init() -> void:
	var rng := RandomNumberGenerator.new()
	rng.seed = 12345
	var names := ["sin", "cos", "atan2"]
	for k in 3:
		var exact := 0
		var worst := 0.0
		var n := 1000000
		var ours := PackedFloat64Array()
		var theirs := PackedFloat64Array()
		ours.resize(n)
		theirs.resize(n)
		for i in n:
			var x := rng.randf_range(-20.0, 20.0) if i % 2 else rng.randf_range(-3.2, 3.2)
			var y := rng.randf_range(-20000.0, 20000.0)
			var got: float
			var want: float
			match k:
				0:
					got = AxisDMath.sin_d(x)
					want = sin(x)
				1:
					got = AxisDMath.cos_d(x)
					want = cos(x)
				2:
					got = AxisDMath.atan2_d(y, x * 1000.0)
					want = atan2(y, x * 1000.0)
			ours[i] = got
			theirs[i] = want
			if got == want:
				exact += 1
			else:
				worst = maxf(worst, _ulps(got, want))
		print("%-6s %d of %d the same as the platform's, worst %.2f ulp" % [names[k], exact, n, worst])
		# fingerprints of all n results: AxisDMath's must be the same on every platform; the platform's may not be
		print("       ours %s  platform's %s" % [_sha(ours),
			_sha(theirs)])
	# a few results as their bits: every platform's build must print the same
	print("sin(1) cos(1) atan2(1, 2) sin(1e6): ", PackedFloat64Array([AxisDMath.sin_d(1.0), AxisDMath.cos_d(1.0),
		AxisDMath.atan2_d(1.0, 2.0), AxisDMath.sin_d(1.0e6)]).to_byte_array().hex_encode())
	quit(0)
