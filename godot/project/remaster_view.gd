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
## from the game's own batches (AxisReplay.build_map_mesh) under remaster_world.tscn (its environment and light, to be
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
var map_mesh: MeshInstance3D
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
func update(frame: Vector2i) -> void:
	var map_on := replay != null and replay.picture_mode > 0 and apply_camera(frame, map_cam, map_sub, WORLD_SCALE)
	map_sub.render_target_update_mode = SubViewport.UPDATE_ALWAYS if map_on else SubViewport.UPDATE_DISABLED
	if map_on:
		map_mesh.mesh = replay.build_map_mesh()
		world.apply_lights(replay.get_lights(), WORLD_SCALE)
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
		var k := "%s %s" % [["map", "dynamic", "actor"][l.pool], ["ambient", "directional", "point", "point (1/d^2)"][l.kind]]
		lights[k] = lights.get(k, 0) + 1
	parts.append("lights %s" % [lights])
	return "camera: fov %.2f, aspect %.4f, viewport %s in %s, near %.2f, far %.1f, view det %.3f, off-axis %s; Godot's Camera3D against the game: %d points, mean %.3f px, median %.3f, 95%% %.3f, 99%% %.3f, worst %.3f; triangles: %s" % [
		info.fovy, info.aspect, info.viewport, frame, info.near, info.far, info.det, info.off_axis, n,
		total / maxi(n, 1), pct.call(0.5), pct.call(0.95), pct.call(0.99), pct.call(1.0), ", ".join(parts)]
