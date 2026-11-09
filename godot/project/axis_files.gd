class_name AxisFiles
extends RefCounted
## The game's folder and its files, for the launcher and the game scene: the folder is --game-dir's (after "--"), else
## for an exported game the exe's folder when it holds initdata, else the one above it; in the editor the default below.
## resolve() finds a file by the game's own (Windows, case-free) name on any system.

const EDITOR_DEFAULT := "C:/Users/Alexander/Desktop/Axis"

static func game_dir() -> String:
	var args := OS.get_cmdline_user_args()
	var i := args.find("--game-dir")
	if i >= 0 and i + 1 < args.size():
		return args[i + 1]
	if OS.has_feature("template"):
		var here := OS.get_executable_path().get_base_dir()
		return here if DirAccess.dir_exists_absolute(here.path_join("initdata")) else here.get_base_dir()
	return EDITOR_DEFAULT

## a path under the game's folder from the game's own spelling (".\\Launcher\\lsound\\mmove.wav"): each part matched
## without regard to case (Linux's file names keep the case the files were copied with). "" when it is not there.
static func resolve(rel: String) -> String:
	var path := game_dir()
	for part in rel.replace("\\", "/").split("/", false):
		if part == ".":
			continue
		var exact := path.path_join(part)
		if FileAccess.file_exists(exact) or DirAccess.dir_exists_absolute(exact):
			path = exact
			continue
		var found := ""
		var d := DirAccess.open(path)
		if d == null:
			return ""
		for name in d.get_files() + d.get_directories():
			if name.to_lower() == part.to_lower():
				found = name
				break
		if found == "":
			return ""
		path = path.path_join(found)
	return path
