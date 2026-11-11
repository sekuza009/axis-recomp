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
## the map lit as the game lights it (AxisReplay.vertex_lighting): the game's own lit colour - per vertex, with its
## models' base colours - with Godot's Sun shadow and ambient occlusion on it; one directional light then (the Sun:
## the map's first, or shadowless where the map has none), no point lights. Off: the map lit by Godot's lights from
## the game's (per pixel: round pools where a light is near a big face, the models' base colours not known)
@export var per_vertex_lighting := true
## (per vertex) how much the Sun's shadow darkens a surface facing it (AxisReplay.shadow_strength)
@export_range(0.0, 1.0, 0.01) var shadow_strength := 0.5
## (per vertex) the Sun's shadow only on a map open to the sky (one the game draws a sky for): an enclosed map's
## directional light is the game's fill light - its roof would shadow the whole arena (Midgard's walls black at 1.0)
@export var shadows_need_sky := true
var map_has_sky := false
## (per vertex) the dynamic lights - explosions, muzzle flashes, the mechs' glow - as Godot's too: a soft glow per pixel
## on the surfaces' textures, over the game's own per-vertex light of them (dynamic_highlight_energy)
## the Sun's shadow: its penumbra (the light's angular size, degrees: 0 hard edges), how far it reaches (metres; the
## world is the game's units x 0.01), the shadow map's size and Godot's soft shadow filter (0 hard .. 5 ultra)
@export_range(0.0, 5.0, 0.1) var sun_shadow_softness := 1.0
@export_range(20.0, 1000.0, 1.0) var sun_shadow_distance := 300.0
@export_enum("2048:2048", "4096:4096", "8192:8192") var shadow_map_size := 4096
@export_range(0, 5) var shadow_filter := 2
var _shadow_applied := ""
@export var dynamic_highlights := true
@export_range(0.0, 4.0, 0.01) var dynamic_highlight_energy := 0.5
## glows the game has not got (its light pool 3, objects.c draw_particleGlows): a soft light of the particle's colour
## at each booster thrust puff, muzzle flash and shot in flight (the tracers), fading with it
@export var particle_glows := true
@export_range(0.0, 4.0, 0.01) var booster_glow_energy := 2.0
@export_range(0.0, 4.0, 0.01) var muzzle_glow_energy := 1.0
@export_range(0.0, 4.0, 0.01) var shot_glow_energy := 1.5   # (remaster_view.update_sky: the frame drew a sky)
## (per pixel only) the lights on a lit map surface summed no higher than this (AxisReplay.light_cap), rolled off towards it: the game
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
	var shadow_key := "%s %s %d %d" % [sun_shadow_softness, sun_shadow_distance, shadow_map_size, shadow_filter]
	if shadow_key != _shadow_applied:   # (the Sun's shadow settings, when they change)
		_shadow_applied = shadow_key
		$Sun.light_angular_distance = sun_shadow_softness
		$Sun.directional_shadow_max_distance = sun_shadow_distance
		RenderingServer.directional_shadow_atlas_set_size(shadow_map_size, true)
		RenderingServer.directional_soft_shadow_filter_set_quality(shadow_filter)
	map_has_lights = false
	# the point lights nearest the eye first (Metropolis has 511 of its own: max_point_lights of them, the nearest)
	var points := []
	for l in lights:
		if l.pool != 2 and (l.kind == 2 or l.kind == 3) and l.radius > 0.0 and _point_used(l):
			points.append(l)   # (per vertex the map's point lights are the game's own, in its colour: of Godot's only the dynamic ones)
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
						if map_dir and per_vertex_lighting:
							continue   # (one directional light, per vertex: the Sun's shadow alone)
						var s: DirectionalLight3D = $Sun if not map_dir else _sun(dirs)
						if map_dir:
							dirs += 1
						map_dir = true
						s.transform.basis = Basis.looking_at(-d if turn_directional_lights else d, up)
						s.light_color = l.colour
						s.light_energy = map_directional_energy
						s.visible = true
						s.shadow_enabled = not per_vertex_lighting or map_has_sky or not shadows_need_sky
				2, 3:   # point lights
					if not _point_used(l) or used >= max_point_lights or l.radius <= 0.0:
						continue
					var o := _omni(used)
					used += 1
					o.position = l.position * scale
					o.omni_range = l.radius * scale
					# the game's kind 2 is full out to about half its radius, then fades to nothing at it: Godot's
					# attenuation 0 (constant, with a smooth edge) is that; kind 3 falls off with the distance squared
					o.omni_attenuation = 0.0 if l.kind == 2 else 2.0
					o.light_color = Color(l.colour.r, l.colour.g, l.colour.b)
					o.light_energy = map_point_energy if l.pool == 0 else (dynamic_highlight_energy if per_vertex_lighting else dynamic_energy)
					if l.pool == 3:   # (a particle's glow: by what it is - its kind in the direction's x - and its fading alpha)
						var k := int(l.direction.x)
						o.light_energy = (booster_glow_energy if k <= 7 else muzzle_glow_energy if k <= 18 else shot_glow_energy) * l.colour.a
					o.shadow_enabled = dynamic_shadows and l.pool == 1
					o.visible = true
	if not map_dir:   # (no directional light of the map's: the Sun as placed, or none)
		$Sun.transform.basis = _sun_basis
		$Sun.light_color = _sun_colour
		$Sun.light_energy = _sun_energy if sun_without_map_light else 0.0
		if per_vertex_lighting:   # (per vertex the Sun is the one light the map's surfaces take: no shadow of a sun
			$Sun.light_energy = maxf($Sun.light_energy, 1.0)   # the map has not got)
			$Sun.shadow_enabled = false
		else:
			$Sun.shadow_enabled = true
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

## whether a point light of the game's becomes one of Godot's: per vertex the map's own are the game's alone (in its
## colour), so only the dynamic ones (dynamic_highlights) and the particles' glows (particle_glows)
func _point_used(l: Dictionary) -> bool:
	if l.pool == 3:
		return particle_glows
	return not per_vertex_lighting or (dynamic_highlights and l.pool == 1)

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
