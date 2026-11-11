extends Node
class_name RemasterView
## The remaster's camera (step 2): a Godot Camera3D made from the game's own camera each frame (the projection and
## view matrices of the world's view volume, src/render/draw_tags.h), with a check that it is right:
## - the overlay (AxisReplay.overlay; Ctrl+F10 in game, --overlay): the map's ground and objects rebuilt as a Godot
##   mesh from the frame and drawn by Godot's own 3D renderer through that camera, as a wireframe over the game's
##   picture - lined up when the camera is right;
## - report(): a sample of the world's points projected by the Camera3D (unproject_position) against where the game
##   drew them, in pixels.
## The picture (step 3; AxisReplay.picture_mode, Ctrl+F12 in game, --picture N): in modes 1 (the original lighting)
## and 2 (the remaster) the map is drawn by Godot - a second viewport with the same camera, the map rebuilt each frame
## from the game's own batches (AxisReplay.build_map_meshes) under remaster_world.tscn (its environment and light, to be
## edited in the editor), and the game's frame drawn into it by AxisMapEffect (its actors, effects and HUD over Godot's
## map, hidden behind it by its depth).

const MASK_MAP := (1 << 2) | (1 << 3)            # the ground and the map's objects
const MASK_WORLD := MASK_MAP | (1 << 4) | (1 << 8)   # with the actors and items
const TAG_NAMES := ["other", "sky", "ground", "objects", "actors", "actor view", "bullets", "particles", "items", "markers", "HUD"]

var replay: AxisReplay
var view: TextureRect
var sub: SubViewport
var cam: Camera3D
var mesh_inst: MeshInstance3D
var shown: TextureRect
var info := {}
var map_sub: SubViewport     # Godot's map (picture modes 1 and 2)
var map_cam: Camera3D
var map_mesh: MeshInstance3D       # (the first of map_meshes)
var map_meshes: Array[MeshInstance3D] = []
# the sky (picture mode 2): its own viewport, a child of the map's (so drawn first), its camera at the game's eye looking
# down -z (the sky's triangles come in the camera's space), its picture the map world's background (BG_CANVAS)
var sky_sub: SubViewport
var sky_cam: Camera3D
var sky_meshes: Array[MeshInstance3D] = []
var sky_back: TextureRect
## Godot's map world in metres: the game's units (its near plane is 100, its far a million) scaled by this - Godot's
## clustered point lights and shadows are made for scenes of metres
const WORLD_SCALE := 0.01
var world: Node3D           # remaster_world.tscn: its light (remaster_world.gd)

func setup(p_replay: AxisReplay, p_view: TextureRect) -> void:
	replay = p_replay
	view = p_view
	sub = SubViewport.new()
	sub.transparent_bg = true
	sub.own_world_3d = true
	sub.debug_draw = Viewport.DEBUG_DRAW_WIREFRAME
	sub.render_target_update_mode = SubViewport.UPDATE_ALWAYS
	add_child(sub)
	cam = Camera3D.new()
	cam.keep_aspect = Camera3D.KEEP_HEIGHT
	sub.add_child(cam)
	cam.current = true
	mesh_inst = MeshInstance3D.new()
	var m := StandardMaterial3D.new()
	m.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED
	m.albedo_color = Color(0.1, 1.0, 0.4)
	m.cull_mode = BaseMaterial3D.CULL_DISABLED
	mesh_inst.material_override = m
	sub.add_child(mesh_inst)
	shown = TextureRect.new()
	shown.texture = sub.get_texture()
	shown.mouse_filter = Control.MOUSE_FILTER_IGNORE
	shown.set_anchors_preset(Control.PRESET_FULL_RECT)
	shown.expand_mode = TextureRect.EXPAND_IGNORE_SIZE
	shown.visible = false
	view.add_child(shown)
	# the map's viewport: rendered every frame it is needed, never shown itself (the effect draws the game into it, the
	# game's frame texture shows the result)
	map_sub = SubViewport.new()
	map_sub.transparent_bg = true
	map_sub.own_world_3d = true
	map_sub.render_target_update_mode = SubViewport.UPDATE_DISABLED
	add_child(map_sub)
	world = load("res://remaster_world.tscn").instantiate()
	map_sub.add_child(world)
	map_cam = Camera3D.new()
	map_cam.keep_aspect = Camera3D.KEEP_HEIGHT
	var effect := AxisMapEffect.new()
	effect.set_replay(replay)
	var comp := Compositor.new()
	comp.compositor_effects = [effect]
	map_cam.compositor = comp
	map_sub.add_child(map_cam)
	map_cam.current = true
	map_mesh = MeshInstance3D.new()
	map_sub.add_child(map_mesh)
	map_mesh.scale = Vector3.ONE * WORLD_SCALE
	map_meshes.append(map_mesh)
	sky_sub = SubViewport.new()
	sky_sub.own_world_3d = true
	sky_sub.render_target_update_mode = SubViewport.UPDATE_DISABLED
	map_sub.add_child(sky_sub)
	var sky_env := WorldEnvironment.new()
	sky_env.environment = Environment.new()
	sky_env.environment.background_mode = Environment.BG_COLOR
	sky_env.environment.background_color = Color(0, 0, 0)
	sky_env.environment.tonemap_mode = Environment.TONE_MAPPER_LINEAR
	sky_sub.add_child(sky_env)
	sky_cam = Camera3D.new()
	sky_cam.keep_aspect = Camera3D.KEEP_HEIGHT
	sky_sub.add_child(sky_cam)
	sky_cam.current = true
	var layer := CanvasLayer.new()
	layer.layer = -1
	map_sub.add_child(layer)
	sky_back = TextureRect.new()
	sky_back.texture = sky_sub.get_texture()
	sky_back.set_anchors_preset(Control.PRESET_FULL_RECT)
	sky_back.expand_mode = TextureRect.EXPAND_IGNORE_SIZE
	sky_back.visible = false
	# (the sky viewport holds the game's gamma values as if linear, stored as sRGB; the map world's background reads its
	# canvas as sRGB into linear: so here sRGB -> the gamma value -> linear (^2.2) -> sRGB)
	var sm := ShaderMaterial.new()
	sm.shader = Shader.new()
	sm.shader.code = "shader_type canvas_item;\n" + \
		"vec3 to_linear(vec3 c) { return mix(c / 12.92, pow((c + 0.055) / 1.055, vec3(2.4)), step(0.04045, c)); }\n" + \
		"vec3 to_srgb(vec3 c) { return mix(c * 12.92, 1.055 * pow(c, vec3(1.0 / 2.4)) - 0.055, step(0.0031308, c)); }\n" + \
		"void fragment() { vec4 t = texture(TEXTURE, UV); COLOR = vec4(to_srgb(pow(to_linear(t.rgb), vec3(2.2))), 1.0); }\n"
	sky_back.material = sm
	layer.add_child(sky_back)
	replay.set_map_viewport(true)

## the Camera3D set from the game's matrices (false: no camera this frame - the menus)
func apply_camera(frame: Vector2i, c: Camera3D = null, s: SubViewport = null, k: float = 1.0) -> bool:
	if c == null:
		c = cam
		s = sub
	if replay == null or not replay.has_camera() or frame.x <= 0 or frame.y <= 0:
		return false
	s.size = frame
	var p: Projection = replay.get_camera_projection()
	var v: Transform3D = replay.get_camera_view()
	var vp: Rect2i = replay.get_camera_viewport()
	var cv := v.affine_inverse()
	c.global_transform = Transform3D(cv.basis, cv.origin * k)
	var fovy := rad_to_deg(2.0 * atan(1.0 / p.y.y))
	var near := p.w.z / (p.z.z - 1.0)
	var far := p.w.z / (p.z.z + 1.0)
	# the game's projection fills its viewport, which may be smaller than the frame (the frame's extra row above the
	# screen): a frustum covering the whole frame at the same scale, its centre moved by the viewport's - and by the
	# projection's own off-axis shift
	var upp := (2.0 * near / p.y.y) / vp.size.y   # (near-plane units per pixel)
	var centre := Vector2(vp.position) + Vector2(vp.size) * 0.5 - Vector2(frame) * 0.5
	var off := Vector2(p.z.x * near / p.x.x - centre.x * upp, p.z.y * near / p.y.y + centre.y * upp)   # (a frustum moved up draws things lower)
	c.set_frustum(upp * frame.y * k, off * k, near * k, far * k)
	info = { "fovy": fovy, "near": near, "far": far, "aspect": p.y.y / p.x.x, "frame_aspect": float(frame.x) / frame.y,
		"det": v.basis.determinant(), "off_axis": Vector2(p.z.x, p.z.y), "viewport": vp }
	return true

## per frame: Godot's map in picture modes 1 and 2; the overlay's camera and mesh when it is on
var timing := { "build": 0.0, "assign": 0.0, "lights": 0.0, "sky": 0.0 }   # (the last update's parts, ms: game.gd's perf log)

func update(frame: Vector2i) -> void:
	var t0 := Time.get_ticks_usec()
	var map_on := replay != null and replay.picture_mode > 0 and apply_camera(frame, map_cam, map_sub, WORLD_SCALE)
	map_sub.render_target_update_mode = SubViewport.UPDATE_ALWAYS if map_on else SubViewport.UPDATE_DISABLED
	if map_on:
		var built: Array = replay.build_map_meshes()
		var t1 := Time.get_ticks_usec()
		timing.build = (t1 - t0) / 1000.0
		while map_meshes.size() < built.size():
			var mi := MeshInstance3D.new()
			map_sub.add_child(mi)
			mi.scale = Vector3.ONE * WORLD_SCALE
			map_meshes.append(mi)
		var shadowless: int = replay.get_first_shadowless_mesh()
		for i in map_meshes.size():
			map_meshes[i].mesh = built[i] if i < built.size() else null
			# (no shadow from the effects - Godot would cast a see-through sprite's as a solid rectangle - nor from the
			# first-person weapon, its depth squeezed in front of the near plane)
			map_meshes[i].cast_shadow = GeometryInstance3D.SHADOW_CASTING_SETTING_OFF if i >= shadowless else GeometryInstance3D.SHADOW_CASTING_SETTING_ON
		var t2 := Time.get_ticks_usec()
		timing.assign = (t2 - t1) / 1000.0
		var pv: bool = world.per_vertex_lighting
		world.apply_lights(replay.get_lights(not pv or world.dynamic_highlights, not pv), WORLD_SCALE, map_cam.global_position)
		timing.lights = (Time.get_ticks_usec() - t2) / 1000.0
		var keep: float = world.original_light_with_map_lights if world.map_has_lights else world.original_light_without
		if absf(replay.original_light - keep) > 0.001:
			replay.original_light = keep
		var vtx: bool = world.per_vertex_lighting if OS.get_environment("AXIS_VERTEX_LIGHT") == "" else OS.get_environment("AXIS_VERTEX_LIGHT") == "1"
		if replay.vertex_lighting != vtx:
			replay.vertex_lighting = vtx
		if absf(replay.shadow_strength - world.shadow_strength) > 0.001:
			replay.shadow_strength = world.shadow_strength
		var cap: float = world.light_cap if OS.get_environment("AXIS_LIGHT_CAP") == "" else OS.get_environment("AXIS_LIGHT_CAP").to_float()
		if absf(replay.light_cap - cap) > 0.001:
			replay.light_cap = cap
	var t3 := Time.get_ticks_usec()
	update_sky(frame, map_on)
	timing.sky = (Time.get_ticks_usec() - t3) / 1000.0
	var on := replay != null and replay.overlay and apply_camera(frame)
	shown.visible = on
	if not on:
		return
	shown.stretch_mode = view.stretch_mode
	shown.texture_filter = view.texture_filter
	var tris: PackedVector3Array = replay.get_world_triangles(MASK_MAP)
	if tris.size() < 3:
		mesh_inst.mesh = null
		return
	var arrays := []
	arrays.resize(Mesh.ARRAY_MAX)
	arrays[Mesh.ARRAY_VERTEX] = tris
	var mesh := ArrayMesh.new()
	mesh.add_surface_from_arrays(Mesh.PRIMITIVE_TRIANGLES, arrays)
	mesh_inst.mesh = mesh

## the sky in its viewport, the map world's background, when the frame has one (picture mode 2)
func update_sky(frame: Vector2i, map_on: bool) -> void:
	var built: Array = replay.build_sky_meshes() if map_on else []
	var on := built.size() > 0
	world.map_has_sky = on
	sky_sub.render_target_update_mode = SubViewport.UPDATE_ALWAYS if on else SubViewport.UPDATE_DISABLED
	sky_back.visible = on
	var env: Environment = world.get_node("Environment").environment
	env.background_mode = Environment.BG_CANVAS if on else Environment.BG_COLOR
	if not on:
		return
	var cc: Color = replay.get_clear_colour()   # (the game's clear colour, in its gamma: shows through the sky)
	sky_sub.get_child(0).environment.background_color = Color(cc.r, cc.g, cc.b).linear_to_srgb()   # (as the sky: the game's gamma)
	apply_camera(frame, sky_cam, sky_sub, 1.0)
	sky_cam.global_transform = Transform3D.IDENTITY   # (the sky's triangles are in the camera's space)
	sky_back.size = Vector2(frame)
	while sky_meshes.size() < built.size():
		var mi := MeshInstance3D.new()
		sky_sub.add_child(mi)
		sky_meshes.append(mi)
	for i in sky_meshes.size():
		sky_meshes[i].mesh = built[i] if i < built.size() else null

## the check: where Godot's camera puts a sample of the world's points against where the game drew them
func report(frame: Vector2i) -> String:
	if not apply_camera(frame):
		return "no camera this frame"
	var s: Array = replay.get_world_samples(MASK_WORLD, 2000)
	var world: PackedVector3Array = s[0]
	var screen: PackedVector2Array = s[1]
	var errs := PackedFloat32Array()
	var total := 0.0
	for i in world.size():
		if cam.is_position_behind(world[i]):
			continue
		var e := cam.unproject_position(world[i]).distance_to(screen[i])
		errs.append(e)
		total += e
	errs.sort()
	var n := errs.size()
	var pct := func(q: float) -> float: return errs[mini(n - 1, int(q * n))] if n > 0 else 0.0
	var stats: PackedInt32Array = replay.get_tag_stats()
	var parts := []
	for t in TAG_NAMES.size():
		if stats[t] > 0:
			parts.append("%s %d" % [TAG_NAMES[t], stats[t]])
	var lights := {}
	for l in replay.get_lights():
		var k := "%s %s" % [["map", "dynamic", "actor", "particle glow"][l.pool], ["ambient", "directional", "point", "point (1/d^2)"][l.kind]]
		lights[k] = lights.get(k, 0) + 1
	parts.append("lights %s" % [lights])
	return "camera: fov %.2f, aspect %.4f, viewport %s in %s, near %.2f, far %.1f, view det %.3f, off-axis %s; Godot's Camera3D against the game: %d points, mean %.3f px, median %.3f, 95%% %.3f, 99%% %.3f, worst %.3f; triangles: %s" % [
		info.fovy, info.aspect, info.viewport, frame, info.near, info.far, info.det, info.off_axis, n,
		total / maxi(n, 1), pct.call(0.5), pct.call(0.95), pct.call(0.99), pct.call(1.0), ", ".join(parts)]
