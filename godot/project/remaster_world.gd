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
@export_range(1, 256) var max_point_lights := 64

var _omnis: Array[OmniLight3D] = []
var _sun_basis: Basis
var _sun_colour: Color
var _sun_energy: float

func _ready() -> void:
	_sun_basis = $Sun.transform.basis
	_sun_colour = $Sun.light_color
	_sun_energy = $Sun.light_energy

## the frame's lights (AxisReplay.get_lights())
func apply_lights(lights: Array, scale: float = 1.0) -> void:
	var env: Environment = $Environment.environment
	var used := 0
	var map_dir := false
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
				1:   # directional: the game's light travels along its direction (lit where a normal faces against it)
					if l.pool == 0 and not map_dir and l.direction.length_squared() > 0.0:
						map_dir = true
						var d: Vector3 = l.direction.normalized()
						var up := Vector3.UP if absf(d.dot(Vector3.UP)) < 0.99 else Vector3.RIGHT
						$Sun.transform.basis = Basis.looking_at(d, up)
						$Sun.light_color = l.colour
						$Sun.light_energy = _sun_energy
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
	for i in range(used, _omnis.size()):
		_omnis[i].visible = false

func _omni(i: int) -> OmniLight3D:
	while _omnis.size() <= i:
		var o := OmniLight3D.new()
		add_child(o)
		_omnis.append(o)
	return _omnis[i]
