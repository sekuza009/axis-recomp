extends Control
## The game itself, running in Godot (AxisGame: axis.dll in-process, drawn by Godot, Godot's input).
## Command line (after --): --game-dir <the Axis folder> [--library <axis.dll>] [--shot frame:file.png ...]
##   [--quit-after N]   (frames: the game's own, counted from its first)

var game: AxisGame
var shots := {}
var quit_after := -1
var audio_log: FileAccess = null   # (--audio-log <file>: the sound status every 3 s, flushed each line)
var audio_t := 0.0
var input_log: FileAccess = null   # (--input-log <file>: what the mouse did, every second)
var input_t := 0.0
var scene_motion := 0   # (motion events the scene itself saw: a check apart from AxisGame)
var scene_rel := Vector2()
var no_game := false

func _ready() -> void:
	var args := OS.get_cmdline_user_args()
	var dir := "C:/Users/Alexander/Desktop/Axis"
	var lib := "res://bin/axis.dll"
	var i := 0
	while i < args.size():
		var a: String = args[i]
		if a == "--game-dir":
			i += 1
			dir = args[i]
		elif a == "--library":
			i += 1
			lib = args[i]
		elif a == "--shot":
			i += 1
			var parts: PackedStringArray = args[i].split(":", true, 1)
			shots[int(parts[0])] = parts[1]
		elif a == "--audio-log":
			i += 1
			audio_log = FileAccess.open(args[i], FileAccess.WRITE)
		elif a == "--input-log":
			i += 1
			input_log = FileAccess.open(args[i], FileAccess.WRITE)
		elif a == "--visible":
			pass
		elif a == "--no-game":
			no_game = true
		elif a == "--gl":
			pass
		elif a == "--status":
			pass
		elif a == "--windowed":
			pass
		elif a == "--quit-after":
			i += 1
			quit_after = int(args[i])
		i += 1
	if args.find("--windowed") < 0:
		DisplayServer.window_set_mode(DisplayServer.WINDOW_MODE_FULLSCREEN)
	$Status.visible = args.find("--status") >= 0
	game = $Game
	$View.texture = game.get_texture()
	if no_game:   # (a check: only the mouse captured, no game)
		Input.mouse_mode = Input.MOUSE_MODE_VISIBLE if args.find("--visible") >= 0 else Input.MOUSE_MODE_CAPTURED
	elif not game.start(dir, lib, args.find("--gl") >= 0):   # (--gl: the game draws with OpenGL too, as before)
		$Status.text = game.get_status()

func _input(e: InputEvent) -> void:
	if e is InputEventMouseMotion:
		scene_motion += 1
		scene_rel += e.relative

func _process(_delta: float) -> void:
	if no_game and input_log:
		input_t += _delta
		if input_t >= 1.0:
			input_t = 0.0
			input_log.store_line("no game: mouse mode %d, scene motion events %d, relative %s" % [Input.mouse_mode, scene_motion, scene_rel])
			input_log.flush()
			scene_motion = 0
			scene_rel = Vector2()
	if game != null:
		fit_view(game.get_game_size())
	if game == null or not game.is_running():
		return
	var f := game.get_game_frames()
	if input_log:
		input_t += _delta
		if input_t >= 1.0:
			input_t = 0.0
			input_log.store_line("frame %d: %s; scene saw %d motion events %s" % [f, game.get_input_status(), scene_motion, scene_rel])
			scene_motion = 0
			scene_rel = Vector2()
			input_log.flush()
	if audio_log:
		audio_t += _delta
		if audio_t >= 3.0:
			audio_t = 0.0
			audio_log.store_line("frame %d: %s" % [f, game.get_audio_status()])
			audio_log.flush()
	$Status.text = "frame %d" % f
	for s in shots.keys():
		if f >= s:
			var img := get_viewport().get_texture().get_image()   # (the window as shown: the 4K frame is too big for a 32-bit process to encode)
			if img:
				img.save_png(shots[s])
				print("AxisGame: frame ", f, " saved to ", shots[s])
			shots.erase(s)
	if quit_after >= 0 and f >= quit_after:
		print("AxisGame: quitting after ", f, " frames")
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
