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
		var here := _program_dir()
		return here if DirAccess.dir_exists_absolute(here.path_join("initdata")) else here.get_base_dir()
	return EDITOR_DEFAULT

## the folder the exported program is in - on macOS the one holding its .app bundle (AxisGodot.app/Contents/MacOS/...)
static func _program_dir() -> String:
	var here := OS.get_executable_path().get_base_dir()
	if OS.get_name() == "macOS" and here.ends_with(".app/Contents/MacOS"):
		return here.get_base_dir().get_base_dir().get_base_dir()
	return here

## the game library of this system and processor: axis64.dll / axis.dll (Windows, 64- / 32-bit), libaxis64.so (Linux),
## libaxis64.dylib (macOS, universal); res://bin/ in the editor, beside the program when exported (on macOS the app's
## Contents/Frameworks - axis.gdextension's dependencies put it there)
static func library_path() -> String:
	var name := "axis64.dll" if OS.has_feature("x86_64") else "axis.dll"
	if OS.get_name() == "Linux":
		name = "libaxis64.so"
	elif OS.get_name() == "macOS":
		name = "libaxis64.dylib"
	if not OS.has_feature("template"):
		return "res://bin/" + name
	var here := OS.get_executable_path().get_base_dir()
	if OS.get_name() == "macOS":
		return here.get_base_dir().path_join("Frameworks").path_join(name)
	return here.path_join(name)

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
