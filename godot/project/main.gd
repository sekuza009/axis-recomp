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
		elif a == "--quit-after":
			i += 1
			quit_after = int(args[i])
		else:
			path = a
		i += 1
	replay = $Replay
	if not replay.open(path):
		$Status.text = replay.get_status()
		return
	$View.texture = replay.get_texture()
	replay.playing = true

func _process(_delta: float) -> void:
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
