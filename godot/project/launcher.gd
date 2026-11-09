extends Control
## The launcher: AxisPlay.exe rewritten in Godot from its decompiled code (Ghidra; addresses below are AxisPlay.exe's).
## A 642 x 482 bordered window centred on the screen (0x402070) with Launcher\Resource\BackGround\MainBK.bmp and eight
## buttons (192 x 45 pictures from AxisPlay.exe's resources: normal, lit, pressed, grey - 0x402730; their places
## 0x402660). The pointer over a button lights it with Launcher\lsound\mmove.wav (0x403e20); a press plays mclick.wav,
## shows it pressed and acts at once (0x404280, 0x404700); the release shows it normal again (0x404500). Installed (the
## game folder has MathFunc.tbl, 0x4054d0): Install Game grey, the rest live; otherwise only Install Game, Help,
## Install DirectX and Quit. "Play Game" starts the game in this program (game.tscn) instead of AxisGL.exe.
## The pictures, sounds, texts and movies are the user's own files - nothing of the game is in this project.
## Command line (after --): --game-dir <folder> (AxisFiles); --play: straight into the game (a graphics change's
## restart, as the original game started AxisGL.exe itself).

const W := 642
const H := 482
# the buttons' places in the window's client area (0x402660: SetRect left, top, right, bottom)
const RECTS := [Rect2i(150, 16, 191, 44), Rect2i(78, 65, 191, 44), Rect2i(34, 114, 191, 44), Rect2i(11, 163, 191, 44),
		Rect2i(439, 260, 191, 44), Rect2i(419, 309, 191, 44), Rect2i(378, 358, 191, 44), Rect2i(300, 407, 191, 44)]
# their pictures (bitmap resources): normal, lit, pressed, grey
const BITMAPS := [[325, 327, 326, 394], [329, 328, 330, 398], [332, 331, 333, 395], [335, 334, 336, 392],
		[338, 337, 339, 391], [341, 340, 342, 393], [344, 343, 345, 396], [374, 375, 373, 399]]
enum { INSTALL, PLAY, CINEMATICS, HELP, SERVER, DIRECTX, VIDEO, QUIT }
enum { NORMAL, LIT, PRESSED, GREY }
const LAUNCHER_KEY := "SOFTWARE\\AxisArena\\Launcher"
const SERVER_KEY := "SOFTWARE\\AxisArena\\SelectServer"
# the messages (AxisPlay.exe's English and Korean texts; Korean when the system's language is)
const TEXT := {
	"select_render": ["Select Render Mode in Video Setup", "Video Setup에서 Render Mode를 선택하여 주십시오"],
	"install": [" Please Install Axis", "Axis를 인스톨 하여 주십시오."],
	"no_list": ["Can't read ServerList.dat. Server list update", "ServerList.dat를 읽어 들이지 못했습니다. Server List를 Update하여 주십시오"],
	"pick_server": ["Under of ListBox to Server Select", "아래 리스트에서 서버을 선택하여 주십시오"],
	"no_notepad": ["Can't find 'notepad.exe'", "notepad.exe를 찾을 수 없습니다"],
	"no_browser": ["Can't find primary webbrowser", "기본 브라우져을 찾을 수 없습니다"],
	"directx": ["DirectX 7.0 or higher is already installed. Would you like to re-install?",
			"이미 DirectX 7.0이상 버젼이 설치되어 있습니다. 그래도 설치 하시겠습니까?"],
}

var sys := AxisLauncher.new()
var res := PeResources.new()
var korean := false
var installed := false
var pictures := []     # per button: [normal, lit, pressed, grey] textures
var buttons := []      # per button: its TextureRect
var lit := []          # per button: lit by the pointer (0x41fc60 ..)
var client: Control    # the client area (inside the 1-pixel border)
var sound: AudioStreamPlayer
var sounds := {}
var modal: LauncherDialog = null
var busy := false      # (a movie or the game starting: no clicks)

func _ready() -> void:
	if OS.get_cmdline_user_args().has("--play"):
		_to_game.call_deferred()
		return
	korean = sys.system_korean()
	theme = LauncherUI.theme()
	_window()
	var exe := AxisFiles.resolve("AxisPlay.exe")
	if exe == "" or not res.open(exe):
		OS.alert("AxisPlay.exe is needed in the game's folder (%s): the launcher's pictures are read from it." % AxisFiles.game_dir(), "Axis Launcher")
		get_tree().quit(1)
		return
	installed = AxisFiles.resolve("MathFunc.tbl") != ""
	if installed:
		_defaults()
	_build()

## the window: AxisPlay's popup (642 x 482, a 1-pixel border, centred) at the screen's scale, drawn at 642 x 482
func _window() -> void:
	var win := get_window()
	var screen := win.current_screen
	var dpi_scale := maxf(1.0, DisplayServer.screen_get_dpi(screen) / 96.0)
	win.borderless = true
	win.content_scale_size = Vector2i(W, H)
	win.content_scale_mode = Window.CONTENT_SCALE_MODE_CANVAS_ITEMS
	win.content_scale_aspect = Window.CONTENT_SCALE_ASPECT_KEEP
	win.size = Vector2i(roundi(W * dpi_scale), roundi(H * dpi_scale))
	var area := DisplayServer.screen_get_usable_rect(screen)
	win.position = area.position + (area.size - win.size) / 2
	win.title = "Axis Launcher"

## the settings AxisPlay writes at its start when installed (WM_CREATE: 0x4020e0, 0x402190, 0x4022b0): new keys get
## their defaults - the render mode 1 (none: Video Setup asks), no server chosen - and StartMode is 0 again
func _defaults() -> void:
	if sys.reg_create(LAUNCHER_KEY) == 1:
		sys.reg_set_int(LAUNCHER_KEY, "EndMode", 0)
		sys.reg_set_int(LAUNCHER_KEY, "RenderMode", 1)
		sys.reg_set_int(LAUNCHER_KEY, "StartMode", 0)
	if sys.reg_create(SERVER_KEY) == 1:
		sys.reg_set_string(SERVER_KEY, "TcpDNS", "10", 0x32)
		sys.reg_set_string(SERVER_KEY, "LadderDNS", "10", 0x32)
		sys.reg_set_int(SERVER_KEY, "TcpPort", 0)
		sys.reg_set_int(SERVER_KEY, "LadderPort", 0)
	sys.reg_set_int(LAUNCHER_KEY, "StartMode", 0)

func _build() -> void:
	var icon := res.icon(377)   # (IDI_LAUNCHER)
	if icon:
		DisplayServer.set_icon(icon)
	var cur := res.cursor("CURSOR2")
	if cur.size() == 2:
		Input.set_custom_mouse_cursor(ImageTexture.create_from_image(cur[0]), Input.CURSOR_ARROW, cur[1])
	var border := ColorRect.new()   # (WS_BORDER)
	border.color = Color.BLACK
	border.size = Vector2(W, H)
	add_child(border)
	client = Control.new()
	client.position = Vector2(1, 1)
	client.size = Vector2(W - 2, H - 2)
	client.mouse_filter = Control.MOUSE_FILTER_IGNORE
	add_child(client)
	var bk := AxisFiles.resolve("Launcher\\Resource\\BackGround\\MainBK.bmp")
	var bimg := PeResources.bmp_image(FileAccess.get_file_as_bytes(bk), false) if bk != "" else null
	if bimg:
		var back := TextureRect.new()
		back.texture = ImageTexture.create_from_image(bimg)
		back.mouse_filter = Control.MOUSE_FILTER_IGNORE
		client.add_child(back)
	for i in RECTS.size():
		var pics := []
		for id in BITMAPS[i]:
			var img := res.bitmap(id)
			pics.append(ImageTexture.create_from_image(img) if img else null)
		pictures.append(pics)
		var b := TextureRect.new()
		b.position = Vector2(RECTS[i].position)
		b.mouse_filter = Control.MOUSE_FILTER_IGNORE
		client.add_child(b)
		buttons.append(b)
		lit.append(false)
		_show(i, NORMAL)
	sound = AudioStreamPlayer.new()
	add_child(sound)
	for k in ["mmove", "mclick"]:
		var p := AxisFiles.resolve("Launcher\\lsound\\%s.wav" % k)
		if p != "":
			sounds[k] = AudioStreamWAV.load_from_file(p)

func _text(key: String) -> String:
	return TEXT[key][1 if korean else 0]

## whether a button takes the pointer and clicks: by the install state (0x403e20 / 0x404280); Install DirectX only on
## Windows (it runs DirectX 7's installer)
func _live(i: int) -> bool:
	if i == DIRECTX and OS.get_name() != "Windows":
		return false
	if installed:
		return i != INSTALL
	return i in [INSTALL, HELP, DIRECTX, QUIT]

func _show(i: int, state: int) -> void:
	buttons[i].texture = pictures[i][state if _live(i) else GREY]

func _play(k: String) -> void:   # (sndPlaySound, asynchronous: a new sound stops the last)
	if sounds.has(k) and sounds[k]:
		sound.stream = sounds[k]
		sound.play()

func _hit(p: Vector2) -> int:
	for i in RECTS.size():
		var r: Rect2i = RECTS[i]
		if p.x >= r.position.x and p.y >= r.position.y and p.x < r.end.x and p.y < r.end.y:   # (PtInRect)
			return i
	return -1

func _input(e: InputEvent) -> void:
	if client == null or modal != null or busy:
		return
	if e is InputEventMouseMotion:
		var p: Vector2 = e.position - client.position
		for i in RECTS.size():
			if not _live(i):
				continue
			var inside := _hit(p) == i
			if inside and not lit[i]:
				_play("mmove")
				_show(i, LIT)
				lit[i] = true
			elif not inside and lit[i]:
				_show(i, NORMAL)
				lit[i] = false
	elif e is InputEventMouseButton and e.button_index == MOUSE_BUTTON_LEFT:
		var i := _hit(e.position - client.position)
		if i < 0 or not _live(i):
			return
		if e.pressed:
			_play("mclick")
			_show(i, PRESSED)
			_act(i)
		else:
			_show(i, NORMAL)

## a button's action (0x404700)
func _act(i: int) -> void:
	match i:
		INSTALL:
			_run_and_quit("Launcher\\AxisInstall\\Setup.exe", _text("install"))
		PLAY:
			_play_game()
		CINEMATICS:
			_cinematics()
		HELP:
			_help()
		SERVER:
			_change_server()
		DIRECTX:
			_install_directx()
		VIDEO:
			_video_setup()
		QUIT:
			get_tree().quit()

## Play Game: a server chosen first (the server dialog when none is), a render mode chosen (Video Setup), StartMode 1,
## then the game - here the game scene in this program
func _play_game() -> void:
	var chosen = sys.reg_get(SERVER_KEY, "")
	if not (chosen is String and chosen != ""):
		if not await _change_server():
			return
	var mode = sys.reg_get(LAUNCHER_KEY, "RenderMode")
	if not (mode in [100, 200, 300]):
		OS.alert(_text("select_render"), "Messsage")
		return
	sys.reg_set_int(LAUNCHER_KEY, "StartMode", 1)
	_to_game()

func _to_game() -> void:
	busy = true
	Input.set_custom_mouse_cursor(null)
	var win := get_window()
	win.content_scale_mode = Window.CONTENT_SCALE_MODE_DISABLED
	win.borderless = false
	win.size = Vector2i(1280, 720)
	var area := DisplayServer.screen_get_usable_rect(win.current_screen)
	win.position = area.position + (area.size - win.size) / 2
	get_tree().change_scene_to_file("res://game.tscn")

## a program of the game's folder run, then the launcher closed (Install Game, Install DirectX); missing: the message
func _run_and_quit(rel: String, missing: String) -> void:
	var p := AxisFiles.resolve(rel)
	if p == "" or OS.get_name() != "Windows":
		OS.alert(missing, "Alert")
		return
	OS.create_process(p, [])
	get_tree().quit()

## Install DirectX: DirectX 7 is always there on today's Windows, so (as the original then) it asks first
func _install_directx() -> void:
	var yes = await _question(_text("directx"), "Messsage")
	if yes:
		_run_and_quit("Launcher\\DirectX\\dx7akor.exe" if korean else "Launcher\\DirectX\\dx7aEng.exe", "DirectX")

## a Yes / No message box: true for Yes
func _question(text: String, title: String) -> bool:
	var font_w := 7
	var w := clampi(text.length() * font_w / 2 + 20, 120, 300)
	var d := LauncherUI.dialog(self, title, w, 62)
	modal = d
	var l := Label.new()
	l.text = text
	l.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	l.position = Vector2(14, 10)
	l.size = Vector2(w * 2 - 28, 70)
	d.client.add_child(l)
	LauncherUI.button(d, "Yes", w / 2 - 54, 44, 50, 14).pressed.connect(d.close.bind(true))
	LauncherUI.button(d, "No", w / 2 + 4, 44, 50, 14).pressed.connect(d.close.bind(false))
	var r = await d.closed
	modal = null
	return r == true

## Cinematics (dialog 382): Opening Cinema (interface.sra), Ending Cinema (battle.sra; only once the game has been
## finished - EndMode, which the game sets), Quit
func _cinematics() -> void:
	var d := LauncherUI.dialog(self, "Cinematics Dialog", 138, 73)
	modal = d
	LauncherUI.button(d, "Opening Cinema", 7, 7, 124, 14).pressed.connect(d.close.bind("InitData\\interface.sra"))
	var ending := LauncherUI.button(d, "Ending Cinema", 7, 29, 124, 14)
	ending.pressed.connect(d.close.bind("InitData\\battle.sra"))
	ending.disabled = sys.reg_get(LAUNCHER_KEY, "EndMode") in [null, 0]
	LauncherUI.button(d, "Quit", 7, 52, 124, 14).pressed.connect(d.close.bind(null))
	var movie = await d.closed
	modal = null
	if movie:
		await _movie(movie)

## Help (dialog 385): the readme (Launcher\ReadmeEng.txt / ReadmeHan.txt, in Notepad on Windows), the web site
func _help() -> void:
	var d := LauncherUI.dialog(self, "Help Dialog", 144, 74)
	modal = d
	LauncherUI.button(d, "Read me ", 7, 7, 130, 14).pressed.connect(d.close.bind("readme"))
	LauncherUI.button(d, "www.AxisArena.net", 7, 30, 130, 14).pressed.connect(d.close.bind("web"))
	LauncherUI.button(d, "Cancel", 7, 53, 130, 14).pressed.connect(d.close.bind(null))
	var what = await d.closed
	modal = null
	if what == "readme":
		var p := AxisFiles.resolve("Launcher\\ReadmeHan.txt" if korean else "Launcher\\ReadmeEng.txt")
		var ok := p != ""
		if ok:
			if OS.get_name() == "Windows":
				ok = OS.create_process("notepad.exe", [p.replace("/", "\\")]) > 0
			else:
				ok = OS.shell_open(p) == OK
		if not ok:
			OS.alert(_text("no_notepad"), "Warning Message")
	elif what == "web":
		if OS.shell_open("http://www.axisarena.net") != OK:
			OS.alert(_text("no_browser"), "Warning Message")

## Launcher\ServerList.dat (0x4060e0): the count, then five lines a server - "#DNS <name>", "#TCPIP <address>",
## "#TCPPORT <port>", "#LADDERIP <address>", "#LADDERPORT <port>"
func _server_list() -> Array:
	var p := AxisFiles.resolve("Launcher\\ServerList.dat")
	if p == "":
		return []
	var lines := FileAccess.get_file_as_string(p).replace("\r", "").split("\n")
	if lines.is_empty():
		return []
	var count := lines[0].to_int()
	var list := []
	var at := 1
	for n in count:
		var s := {"name": "", "tcp": "", "tcpport": 0, "ladder": "", "ladderport": 0}
		for k in 5:
			if at >= lines.size():
				break
			var line := lines[at].strip_edges()
			at += 1
			var sp := line.find(" ")
			var key := line if sp < 0 else line.substr(0, sp)
			var value := "" if sp < 0 else line.substr(sp + 1).strip_edges()
			match key:
				"#DNS": s.name = value
				"#TCPIP": s.tcp = value
				"#TCPPORT": s.tcpport = value.to_int()
				"#LADDERIP": s.ladder = value
				"#LADDERPORT": s.ladderport = value.to_int()
		list.append(s)
	return list

## Change Server (dialog 387): the servers of ServerList.dat; OK (live once one is picked) writes it to
## HKCU\SOFTWARE\AxisArena\SelectServer (0x405f70) - the game's server list and ladder servers. List Update runs
## Launcher\GetList.exe (the original's list download). True when OK was pressed.
func _change_server() -> bool:
	var d := LauncherUI.dialog(self, "Select Server List", 151, 181)
	modal = d
	var info := Label.new()
	info.text = _text("pick_server")
	info.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	info.position = Vector2(14, 14)
	info.size = Vector2(274, 56)
	d.client.add_child(info)
	var box := ItemList.new()
	box.position = Vector2(14, 92)
	box.size = Vector2(274, 212)
	box.focus_mode = Control.FOCUS_NONE
	d.client.add_child(box)
	var ok := LauncherUI.button(d, "OK", 57, 160, 43, 14)
	ok.disabled = true
	ok.pressed.connect(func() -> void: d.close(box.get_selected_items()[0] if box.is_anything_selected() else null))
	LauncherUI.button(d, "Cancel", 104, 160, 40, 14).pressed.connect(d.close.bind(null))
	var update := LauncherUI.button(d, "List Update", 7, 160, 46, 14)
	update.disabled = OS.get_name() != "Windows" or AxisFiles.resolve("Launcher\\GetList.exe") == ""
	update.pressed.connect(d.close.bind("update"))
	box.item_selected.connect(func(_i: int) -> void: ok.disabled = false)
	var list := _server_list()
	for s in list:
		box.set_item_tooltip_enabled(box.add_item(s.name), false)
	if list.is_empty():
		OS.alert(_text("no_list"), "Alert")
	var r = await d.closed
	modal = null
	if r is int and r < list.size():
		var s: Dictionary = list[r]
		sys.reg_set_string(SERVER_KEY, "", "10", 10)
		sys.reg_set_string(SERVER_KEY, "TcpDNS", s.tcp, 0x32)
		sys.reg_set_string(SERVER_KEY, "LadderDNS", s.ladder, 0x32)
		sys.reg_set_int(SERVER_KEY, "TcpPort", s.tcpport)
		sys.reg_set_int(SERVER_KEY, "LadderPort", s.ladderport)
		return true
	if r == "update":   # (the window minimised while the program runs, as the original did)
		var win := get_window()
		win.mode = Window.MODE_MINIMIZED
		OS.execute(AxisFiles.resolve("Launcher\\GetList.exe"), [])
		win.mode = Window.MODE_WINDOWED
	return false

## Video Setup (dialog 383): the render mode the game was started with (RenderMode: 100 Direct3D, 200 OpenGL, 300
## OpenGL for Savage cards). This version has one renderer (Godot's), so only "Select OpenGL Render" is live;
## Direct3D, Savage and the 2000 GLSetup driver installer stay grey.
func _video_setup() -> void:
	var d := LauncherUI.dialog(self, "Video Setup Dialog", 172, 115)
	modal = d
	LauncherUI.button(d, "GLSetup.exe Install", 7, 7, 158, 14).disabled = true
	LauncherUI.button(d, "Select Direct3D Render", 7, 30, 158, 14).disabled = true
	LauncherUI.button(d, "Select OpenGL Render", 7, 52, 158, 14).pressed.connect(d.close.bind(200))
	LauncherUI.button(d, "Select OpenGL Render for Savage", 7, 73, 158, 14).disabled = true
	LauncherUI.button(d, "Quit", 7, 94, 158, 14).pressed.connect(d.close.bind(null))
	var r = await d.closed
	modal = null
	if r is int:
		sys.reg_set_int(LAUNCHER_KEY, "RenderMode", r)   # (0x4057c0)

## a movie full screen, its shape kept, the pointer hidden; Esc (pressed during it) ends it (0x401000, 0x401230)
func _movie(rel: String) -> void:
	var p := AxisFiles.resolve(rel)
	var m := AxisMovie.new()
	if p == "" or not m.open(p):
		return
	busy = true
	var win := get_window()
	var saved := [win.size, win.position]
	win.content_scale_mode = Window.CONTENT_SCALE_MODE_DISABLED
	win.mode = Window.MODE_FULLSCREEN
	Input.mouse_mode = Input.MOUSE_MODE_HIDDEN
	var layer := CanvasLayer.new()
	layer.layer = 10
	add_child(layer)
	var black := ColorRect.new()
	black.color = Color.BLACK
	black.set_anchors_preset(Control.PRESET_FULL_RECT)
	layer.add_child(black)
	var view := TextureRect.new()
	view.set_anchors_preset(Control.PRESET_FULL_RECT)
	view.expand_mode = TextureRect.EXPAND_IGNORE_SIZE
	view.stretch_mode = TextureRect.STRETCH_KEEP_ASPECT_CENTERED
	m.decode_to(1)
	var tex := ImageTexture.create_from_image(m.get_image())
	view.texture = tex
	layer.add_child(view)
	var player := AudioStreamPlayer.new()
	add_child(player)
	var pcm := m.get_audio()
	var length := m.get_frame_count() / m.get_fps()
	if not pcm.is_empty():
		var wav := AudioStreamWAV.new()
		wav.format = AudioStreamWAV.FORMAT_8_BITS if m.get_audio_bits() == 8 else AudioStreamWAV.FORMAT_16_BITS
		wav.stereo = m.get_audio_channels() == 2
		wav.mix_rate = m.get_audio_rate()
		wav.data = pcm
		player.stream = wav
		length = maxf(length, wav.get_length())
		player.play()
	var start := Time.get_ticks_msec()
	var esc_up := false
	while true:
		await get_tree().process_frame
		var t := (Time.get_ticks_msec() - start) / 1000.0
		if Input.is_physical_key_pressed(KEY_ESCAPE):
			if esc_up:
				break
		else:
			esc_up = true
		if m.decode_to(int(t * m.get_fps()) + 1):
			tex.update(m.get_image())
		if t >= length:
			break
	player.stop()
	player.queue_free()
	layer.queue_free()
	m.close()
	Input.mouse_mode = Input.MOUSE_MODE_VISIBLE
	win.mode = Window.MODE_WINDOWED
	win.borderless = true
	win.content_scale_mode = Window.CONTENT_SCALE_MODE_CANVAS_ITEMS
	win.size = saved[0]
	win.position = saved[1]
	busy = false
