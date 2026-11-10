extends Node
class_name RemasterView
## The remaster's camera (step 2): a Godot Camera3D made from the game's own camera each frame (the projection and
## view matrices of the world's view volume, src/render/draw_tags.h), with a check that it is right:
## - the overlay (AxisReplay.overlay; Ctrl+F10 in game, --overlay): the map's ground and objects rebuilt as a Godot
##   mesh from the frame and drawn by Godot's own 3D renderer through that camera, as a wireframe over the game's
##   picture - lined up when the camera is right;
## - report(): a sample of the world's points projected by the Camera3D (unproject_position) against where the game
##   drew them, in pixels.

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

## the Camera3D set from the game's matrices (false: no camera this frame - the menus)
func apply_camera(frame: Vector2i) -> bool:
	if replay == null or not replay.has_camera() or frame.x <= 0 or frame.y <= 0:
		return false
	sub.size = frame
	var p: Projection = replay.get_camera_projection()
	var v: Transform3D = replay.get_camera_view()
	var vp: Rect2i = replay.get_camera_viewport()
	cam.global_transform = v.affine_inverse()
	var fovy := rad_to_deg(2.0 * atan(1.0 / p.y.y))
	var near := p.w.z / (p.z.z - 1.0)
	var far := p.w.z / (p.z.z + 1.0)
	# the game's projection fills its viewport, which may be smaller than the frame (the frame's extra row above the
	# screen): a frustum covering the whole frame at the same scale, its centre moved by the viewport's - and by the
	# projection's own off-axis shift
	var upp := (2.0 * near / p.y.y) / vp.size.y   # (near-plane units per pixel)
	var centre := Vector2(vp.position) + Vector2(vp.size) * 0.5 - Vector2(frame) * 0.5
	var off := Vector2(p.z.x * near / p.x.x - centre.x * upp, p.z.y * near / p.y.y + centre.y * upp)   # (a frustum moved up draws things lower)
	cam.set_frustum(upp * frame.y, off, near, far)
	info = { "fovy": fovy, "near": near, "far": far, "aspect": p.y.y / p.x.x, "frame_aspect": float(frame.x) / frame.y,
		"det": v.basis.determinant(), "off_axis": Vector2(p.z.x, p.z.y), "viewport": vp }
	return true

## per frame: the camera, and the overlay's mesh when it is on
func update(frame: Vector2i) -> void:
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
	return "camera: fov %.2f, aspect %.4f, viewport %s in %s, near %.2f, far %.1f, view det %.3f, off-axis %s; Godot's Camera3D against the game: %d points, mean %.3f px, median %.3f, 95%% %.3f, 99%% %.3f, worst %.3f; triangles: %s" % [
		info.fovy, info.aspect, info.viewport, frame, info.near, info.far, info.det, info.off_axis, n,
		total / maxi(n, 1), pct.call(0.5), pct.call(0.95), pct.call(0.99), pct.call(1.0), ", ".join(parts)]
