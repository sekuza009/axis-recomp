extends Control
## Plays a recorded stream of the game's drawing (standalone/glrec.c, AXIS_GLREC_DUMP) with AxisReplay.
## Command line (after --): <file.glrec> [--fps N] [--shot frame:path ...] [--quit-after N] [--look]
##   --shot 300:C:/x.png  saves the replay's image once 300 frames are played (the game's frame 300, counted from 1,
##   as AXIS_GLREC_DUMP_SHOTS); --quit-after N quits once N frames are played.

var replay: AxisReplay
var shots := {}        # frame -> path
var quit_after := -1
var shot_path := ""    # a shot being taken: playing paused while the render thread catches up
var shot_wait := 0
var remaster: RemasterView
var camera_report: FileAccess

func _ready() -> void:
	var args := OS.get_cmdline_user_args()
	var path := "res://capture.glrec"
	var i := 0
	while i < args.size():
		var a: String = args[i]
		if a == "--fps":
			i += 1
			$Replay.fps = float(args[i])
		elif a == "--shot":
			i += 1
			var parts: PackedStringArray = args[i].split(":", true, 1)
			shots[int(parts[0])] = parts[1]
		elif a == "--picture":   # the picture: 0 the original, 1 the original lighting, 2 the remaster
			i += 1
			$Replay.picture_mode = int(args[i])
		elif a == "--tags":   # the tag view
			$Replay.tag_view = true
		elif a == "--overlay":   # the camera check's overlay
			$Replay.overlay = true
		elif a == "--camera-report":   # the camera check's numbers at each --shot frame into a file
			i += 1
			camera_report = FileAccess.open(args[i], FileAccess.WRITE)
		elif a == "--look":   # the remaster look on (main.tscn holds its settings)
			$Replay.look_enabled = true
		elif a == "--no-status":
			pass
		elif a == "--windowed":
			pass
		elif a == "--quit-after":
			i += 1
			quit_after = int(args[i])
		else:
			path = a
		i += 1
	if args.find("--windowed") < 0:
		DisplayServer.window_set_mode(DisplayServer.WINDOW_MODE_FULLSCREEN)
	replay = $Replay
	if not replay.open(path):
		$Status.text = replay.get_status()
		return
	$View.texture = replay.get_texture()
	remaster = RemasterView.new()
	add_child(remaster)
	remaster.setup(replay, $View)
	$Status.visible = OS.get_cmdline_user_args().find("--no-status") < 0
	replay.playing = true

func _process(_delta: float) -> void:
	if replay != null:
		fit_view(replay.get_frame_size())
	if replay == null:
		return
	var f := replay.get_frame()
	if shot_path == "":
		remaster.update(replay.get_frame_size())
	$Status.text = "frame %d / %d   %s" % [f, replay.get_frame_count(), replay.get_frame_size()]
	if shot_path != "":
		shot_wait -= 1
		if shot_wait <= 0:
			var img := replay.get_texture().get_image()
			if img:
				img.save_png(shot_path)
				print("AxisReplay: frame ", f, " saved to ", shot_path)
			# (and what the window shows: Godot's display of the texture - colour handling, scaling)
			if OS.get_environment("AXIS_DUMP_BATCHES") != "":   # (a check: the frame's batches)
				var df := FileAccess.open(shot_path.get_basename() + "_batches.txt", FileAccess.WRITE)
				df.store_string(replay.dump_batches())
			if remaster and remaster.map_sub.render_target_update_mode == SubViewport.UPDATE_ALWAYS:   # (Godot's map alone)
				var mi := remaster.map_sub.get_texture().get_image()
				if mi:
					mi.save_png(shot_path.get_basename() + "_map.png")
				print("map mesh surfaces: ", remaster.map_mesh.mesh.get_surface_count() if remaster.map_mesh.mesh else -1)
				if remaster.sky_back.visible:
					var si := remaster.sky_sub.get_texture().get_image()
					if si:
						si.save_png(shot_path.get_basename() + "_sky.png")
				if OS.get_environment("AXIS_LIGHT_LIST") != "":
					for l in replay.get_lights():
						print("light ", l)
					print("camera at ", replay.get_camera_view().affine_inverse().origin)
			var view := get_viewport().get_texture().get_image()
			if view:
				view.save_png(shot_path.get_basename() + "_view.png")
			shot_path = ""
			replay.playing = true
		return
	if shots.has(f):
		if camera_report:
			camera_report.store_line("frame %d: %s" % [f, remaster.report(replay.get_frame_size())])
			camera_report.flush()
		replay.playing = false
		shot_path = shots[f]
		shot_wait = 3
		shots.erase(f)
		return
	if quit_after >= 0 and f >= quit_after:
		get_tree().quit()

## the frame shown as the original shows it: when the window is the game's size (full screen at the desktop's size,
## the game's own setting) pixel for pixel, the game window's one extra row above the screen (it starts at y -1);
## otherwise scaled to fit, smoothed
func fit_view(frame: Vector2i) -> void:
	var win := get_viewport().get_visible_rect().size
	var view: TextureRect = $View
	if frame.x == int(win.x) and (frame.y == int(win.y) or frame.y == int(win.y) + 1):
		view.set_anchors_preset(Control.PRESET_TOP_LEFT)
		view.stretch_mode = TextureRect.STRETCH_KEEP
		view.position = Vector2(0, win.y - frame.y)
		view.size = Vector2(frame)
		view.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	else:
		view.set_anchors_preset(Control.PRESET_FULL_RECT)
		view.stretch_mode = TextureRect.STRETCH_KEEP_ASPECT_CENTERED
		view.texture_filter = CanvasItem.TEXTURE_FILTER_LINEAR
