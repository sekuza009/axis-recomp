extends Node3D
## The remaster's world (remaster_world.tscn, step 4): the light the remaster picture (AxisReplay.picture_mode 2) is lit
## by - the game's own lights turned into Godot's each frame (apply_lights, from AxisReplay.get_lights(): the stage's
## pools, src/render/draw_tags.h) - and the settings to tune them in the editor.
## - the map's ambient light: the environment's ambient colour (ambient_energy);
## - the map's point lights (from the map file) and the dynamic ones (each mech's glow, the explosions and flashes that
##   give light): OmniLight3Ds of the game's colour and radius (map_point_energy, dynamic_energy);
## - the map's directional light, when it has one: the Sun's direction and colour; otherwise the Sun as placed here
##   (sun_without_map_light);
## - the actors' own lights (an ambient and one from above) are for the mechs the game still draws: not used here.

@export var use_game_lights := true
@export_range(0.0, 2.0, 0.01) var ambient_energy := 0.25
@export_range(0.0, 8.0, 0.01) var map_point_energy := 1.0
@export_range(0.0, 8.0, 0.01) var dynamic_energy := 1.0
@export var dynamic_shadows := false
@export var sun_without_map_light := true
## the map's directional lights shine along their direction, as the game's code has it (shading.c: lit where a normal
## faces against it). Turned round (true) they shine the other way - a check only: an earlier reading that they were
## turned came from the 64-bit build's garbage normals (fixed on 2026-11-10); with them right, not turned matches the
## original on every map with directional lights (Bloodbath, CrimsonField, StarField, Abyss, Centropolis, Valhalla)
@export var turn_directional_lights := false
@export_range(1, 256) var max_point_lights := 64
@export_range(0.0, 4.0, 0.01) var map_directional_energy := 1.0
## how much of the game's own lighting the remaster keeps as a glow (AxisReplay.original_light): less when the map has
## lights of its own (Godot gives their light again), more when it has none (the Sun alone would leave it dark)
@export_range(0.0, 1.5, 0.01) var original_light_with_map_lights := 0.3
@export_range(0.0, 1.5, 0.01) var original_light_without := 0.6
## the lights on a lit map surface summed no higher than this (AxisReplay.light_cap), rolled off towards it: the game
## clamps its lighting at full white, Godot would add lights without end (hard white patches where many overlap)
@export_range(0.0, 8.0, 0.01) var light_cap := 1.0
var map_has_lights := false   # (apply_lights: the frame's map pool has directional or point lights)

var _omnis: Array[OmniLight3D] = []
var _suns: Array[DirectionalLight3D] = []   # (the map's second and further directional lights; the first is the Sun)
var _sun_basis: Basis
var _sun_colour: Color
var _sun_energy: float

func _ready() -> void:
	if OS.get_environment("AXIS_TURN_DIR") != "":   # (a check: the directional lights turned or not)
		turn_directional_lights = OS.get_environment("AXIS_TURN_DIR") == "1"
	_sun_basis = $Sun.transform.basis
	_sun_colour = $Sun.light_color
	_sun_energy = $Sun.light_energy

## the frame's lights (AxisReplay.get_lights())
func apply_lights(lights: Array, scale: float = 1.0, eye := Vector3.ZERO) -> void:
	var env: Environment = $Environment.environment
	map_has_lights = false
	# the point lights nearest the eye first (Metropolis has 511 of its own: max_point_lights of them, the nearest)
	var points := []
	for l in lights:
		if l.pool != 2 and (l.kind == 2 or l.kind == 3) and l.radius > 0.0:
			points.append(l)
		if l.pool == 0 and l.kind >= 1:
			map_has_lights = true
	if points.size() > max_point_lights:
		points.sort_custom(func(a, b): return (a.position * scale).distance_squared_to(eye) - (a.radius * scale) ** 2 < (b.position * scale).distance_squared_to(eye) - (b.radius * scale) ** 2)
		points.resize(max_point_lights)
	lights = lights.filter(func(l): return not ((l.kind == 2 or l.kind == 3) and l.pool != 2)) + points
	var used := 0
	var map_dir := false
	var dirs := 0
	if use_game_lights:
		for l in lights:
			if l.pool == 2:
				continue
			match int(l.kind):
				0:   # ambient
					if l.pool == 0:
						env.ambient_light_source = Environment.AMBIENT_SOURCE_COLOR
						env.ambient_light_color = l.colour
						env.ambient_light_energy = ambient_energy
				1:   # directional: the game's light travels along its direction (lit where a normal faces against it);
					# the first is the Sun (its shadows), the others lights of their own without shadows
					if l.pool == 0 and l.direction.length_squared() > 0.0:
						var d: Vector3 = l.direction.normalized()
						var up := Vector3.UP if absf(d.dot(Vector3.UP)) < 0.99 else Vector3.RIGHT
						var s: DirectionalLight3D = $Sun if not map_dir else _sun(dirs)
						if map_dir:
							dirs += 1
						map_dir = true
						s.transform.basis = Basis.looking_at(-d if turn_directional_lights else d, up)
						s.light_color = l.colour
						s.light_energy = map_directional_energy
						s.visible = true
				2, 3:   # point lights
					if used >= max_point_lights or l.radius <= 0.0:
						continue
					var o := _omni(used)
					used += 1
					o.position = l.position * scale
					o.omni_range = l.radius * scale
					# the game's kind 2 is full out to about half its radius, then fades to nothing at it: Godot's
					# attenuation 0 (constant, with a smooth edge) is that; kind 3 falls off with the distance squared
					o.omni_attenuation = 0.0 if l.kind == 2 else 2.0
					o.light_color = l.colour
					o.light_energy = map_point_energy if l.pool == 0 else dynamic_energy
					o.shadow_enabled = dynamic_shadows and l.pool == 1
					o.visible = true
	if not map_dir:   # (no directional light of the map's: the Sun as placed, or none)
		$Sun.transform.basis = _sun_basis
		$Sun.light_color = _sun_colour
		$Sun.light_energy = _sun_energy if sun_without_map_light else 0.0
	if OS.get_environment("AXIS_LIGHT_TEST") != "" and used < max_point_lights:   # (a check: a strong light at the camera)
		var o := _omni(used)
		used += 1
		o.position = get_viewport().get_camera_3d().global_position
		o.omni_range = 20000.0 * scale
		o.omni_attenuation = 0.0
		o.light_color = Color(1, 1, 1)
		o.light_energy = float(OS.get_environment("AXIS_LIGHT_TEST"))   # (white)
		o.shadow_enabled = false
		o.visible = true
	if OS.get_environment("AXIS_LIGHT_TEST") != "" and Engine.get_process_frames() % 120 == 0:
		var cam := get_viewport().get_camera_3d()
		print("lights test: ", used, " omnis; camera ", cam.global_position, " near ", cam.near, " far ", cam.far, "; first ", _omnis[0].global_position if used > 0 else Vector3(), " range ", _omnis[0].omni_range if used > 0 else 0.0, " in tree ", _omnis[0].is_inside_tree() if used > 0 else false, " world ", get_world_3d(), " cam world ", cam.get_world_3d())
	for i in range(dirs, _suns.size()):
		_suns[i].visible = false
	for i in range(used, _omnis.size()):
		_omnis[i].visible = false

func _sun(i: int) -> DirectionalLight3D:
	while _suns.size() <= i:
		var s := DirectionalLight3D.new()
		add_child(s)
		_suns.append(s)
	return _suns[i]

func _omni(i: int) -> OmniLight3D:
	while _omnis.size() <= i:
		var o := OmniLight3D.new()
		add_child(o)
		_omnis.append(o)
	return _omnis[i]
