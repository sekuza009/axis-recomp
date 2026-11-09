extends Control
## Plays a recorded stream of the game's drawing (standalone/glrec.c, AXIS_GLREC_DUMP) with AxisReplay.
## Command line (after --): <file.glrec> [--fps N] [--shot frame:path ...] [--quit-after N]
##   --shot 300:C:/x.png  saves the replay's image once 300 frames are played (the game's frame 300, counted from 1,
##   as AXIS_GLREC_DUMP_SHOTS); --quit-after N quits once N frames are played.

var replay: AxisReplay
var shots := {}        # frame -> path
var quit_after := -1
var shot_path := ""    # a shot being taken: playing paused while the render thread catches up
var shot_wait := 0

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
	$Status.visible = OS.get_cmdline_user_args().find("--no-status") < 0
	replay.playing = true

func _process(_delta: float) -> void:
	if replay != null:
		fit_view(replay.get_frame_size())
	if replay == null:
		return
	var f := replay.get_frame()
	$Status.text = "frame %d / %d   %s" % [f, replay.get_frame_count(), replay.get_frame_size()]
	if shot_path != "":
		shot_wait -= 1
		if shot_wait <= 0:
			var img := replay.get_texture().get_image()
			if img:
				img.save_png(shot_path)
				print("AxisReplay: frame ", f, " saved to ", shot_path)
			# (and what the window shows: Godot's display of the texture - colour handling, scaling)
			var view := get_viewport().get_texture().get_image()
			if view:
				view.save_png(shot_path.get_basename() + "_view.png")
			shot_path = ""
			replay.playing = true
		return
	if shots.has(f):
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
