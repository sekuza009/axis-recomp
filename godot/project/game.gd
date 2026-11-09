extends Control
## The game itself, running in Godot (AxisGame: axis.dll in-process, drawn by Godot, Godot's input).
## Command line (after --): --game-dir <the Axis folder> [--library <axis.dll>] [--shot frame:file.png ...]
##   [--quit-after N]   (frames: the game's own, counted from its first)

var game: AxisGame
var shots := {}
var quit_after := -1

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
		elif a == "--quit-after":
			i += 1
			quit_after = int(args[i])
		i += 1
	game = $Game
	$View.texture = game.get_texture()
	if not game.start(dir, lib):
		$Status.text = game.get_status()

func _process(_delta: float) -> void:
	if game == null or not game.is_running():
		return
	var f := game.get_game_frames()
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
