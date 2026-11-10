extends Control
## The game itself, running in Godot (AxisGame: the game library in-process, drawn by Godot, Godot's input).
## Command line (after --): --game-dir <the Axis folder> [--library <axis64.dll>] [--shot frame:file.png ...]
##   [--quit-after N]   (frames: the game's own, counted from its first)

var game: AxisGame
var remaster: RemasterView   # the remaster's camera and its check (remaster_view.gd)
var record_path := ""
var camera_report: FileAccess
var next_report := 0
var shots := {}
var quit_after := -1
var audio_log: FileAccess = null   # (--audio-log <file>: the sound status every 3 s, flushed each line)
var audio_t := 0.0
var input_log: FileAccess = null   # (--input-log <file>: what the mouse did, every second)
var input_t := 0.0
var frame_log: FileAccess = null   # (--frame-log <file>: game steps that took long)
var scene_motion := 0   # (motion events the scene itself saw: a check apart from AxisGame)
var scene_rel := Vector2()
var no_game := false

func _ready() -> void:
	var args := OS.get_cmdline_user_args()
	var dir := AxisFiles.game_dir()   # (--game-dir is read again below, for the other arguments' sake)
	var lib := AxisFiles.library_path()
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
		elif a == "--frame-log":
			i += 1
			frame_log = FileAccess.open(args[i], FileAccess.WRITE)
		elif a == "--raw-mouse":
			pass
		elif a == "--music-near-end":   # (a check: each track started that many seconds before its end)
			i += 1
			$Game.set_music_near_end(float(args[i]))
		elif a == "--step-shots":
			i += 1
		elif a == "--gl":
			pass
		elif a == "--record":   # the game's drawing to a file (main.tscn replays it)
			i += 1
			record_path = args[i]
		elif a == "--tags":   # the tag view on (Ctrl+F9 toggles it)
			$Game.tag_view = true
		elif a == "--overlay":   # the camera check's overlay on (Ctrl+F10 toggles it)
			$Game.overlay = true
		elif a == "--camera-report":   # the camera check's numbers every 300 frames into a file
			i += 1
			camera_report = FileAccess.open(args[i], FileAccess.WRITE)
		elif a == "--no-look":   # the original picture (the remaster look off; Ctrl+F11 toggles it in game)
			$Game.look_enabled = false
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
	elif get_window().borderless:   # (started directly: the project's window is the launcher's, 642 x 482 without a frame)
		get_window().borderless = false
		get_window().size = Vector2i(1280, 720)
		get_window().move_to_center()
	$Status.visible = args.find("--status") >= 0
	game = $Game
	$View.texture = game.get_texture()
	if args.find("--no-refit") < 0:
		game.game_size_changed.connect(refit_now)   # (the view laid out as soon as the game's size is known, mid-step too)
	if args.find("--step-shots") >= 0:   # (a check: what Godot shows of a step's frames, frames 5 / 20 / 35)
		game.step_frame_shown.connect(func(fr: int) -> void:
			if fr == 5 or fr == 20 or fr == 35:
				var img := get_viewport().get_texture().get_image()
				if img:
					img.resize(img.get_width() / 4, img.get_height() / 4)
					img.save_png(args[args.find("--step-shots") + 1] + "/step_%d.png" % fr)
				var own: Image = game.get_texture().get_image()   # (the game's own frame, before display)
				if own:
					own.resize(own.get_width() / 8, own.get_height() / 8)
					own.save_png(args[args.find("--step-shots") + 1] + "/game_%d.png" % fr))
	# the game's start-up screen (logo and progress bar) is drawn in its first step: Godot's window shown first
	for _f in 3:
		await get_tree().process_frame
	if no_game:   # (a check: only the mouse captured, no game)
		Input.mouse_mode = Input.MOUSE_MODE_VISIBLE if args.find("--visible") >= 0 else Input.MOUSE_MODE_CAPTURED
	elif game.start(dir, lib, args.find("--gl") >= 0, args.find("--raw-mouse") >= 0):
		if record_path != "":
			game.start_recording(record_path)
		remaster = RemasterView.new()
		add_child(remaster)
		remaster.setup(game, $View)
	else:   # (--raw-mouse: the device's counts, unscaled)   # (--gl: the game draws with OpenGL too, as before)
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
	if remaster:
		remaster.update(game.get_game_size())
		if camera_report and f >= next_report:
			next_report = f + 300
			camera_report.store_line("frame %d: %s" % [f, remaster.report(game.get_game_size())])
			camera_report.flush()
	if frame_log:
		var ev: String = game.take_frame_events()
		if ev != "":
			frame_log.store_string(ev)
			frame_log.flush()
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
		game.stop_recording()
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

## the game's size changed (during a game step too: the start-up screen): the view laid out and its drawing replaced
## at once - a TextureRect redraws only when the step has returned (its redraw is deferred), and a step's frames are
## shown before that
func refit_now(frame: Vector2i) -> void:
	fit_view(frame)
	var view: TextureRect = $View
	var r := Rect2(Vector2.ZERO, view.size)
	if view.stretch_mode == TextureRect.STRETCH_KEEP_ASPECT_CENTERED and frame.x > 0 and frame.y > 0:
		var s := minf(view.size.x / frame.x, view.size.y / frame.y)
		var sz := Vector2(frame) * s
		r = Rect2((view.size - sz) / 2, sz)
	var ci := view.get_canvas_item()
	RenderingServer.canvas_item_clear(ci)
	RenderingServer.canvas_item_add_texture_rect(ci, r, view.texture.get_rid())
