class_name LauncherDialog
extends Control
## One of the launcher's modal dialogs (LauncherUI.dialog): a full-size layer that takes the launcher's clicks, the
## dialog's frame with its caption and close box at the launcher's top left, and the client area for its controls.
## Esc and the close box close it with null (Windows' IDCANCEL / WM_CLOSE).

signal closed(result)

var client: Control
var _done := false

func build(owner: Control, title: String, w: int, h: int) -> void:
	theme = LauncherUI.theme()
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST   # (the bevels' pixels kept sharp)
	set_anchors_preset(Control.PRESET_FULL_RECT)
	mouse_filter = Control.MOUSE_FILTER_STOP   # (modal: the launcher behind takes nothing)
	var frame := Panel.new()
	frame.position = Vector2.ZERO
	frame.size = Vector2(w + LauncherUI.FRAME * 2, h + LauncherUI.CAPTION + LauncherUI.FRAME * 2 + 1)
	add_child(frame)
	var cap := TextureRect.new()
	var grad := Gradient.new()
	grad.set_color(0, Color8(10, 36, 106))
	grad.set_color(1, Color8(166, 202, 240))
	var gt := GradientTexture2D.new()
	gt.gradient = grad
	gt.width = 64
	gt.height = 4
	cap.texture = gt
	cap.stretch_mode = TextureRect.STRETCH_SCALE
	cap.expand_mode = TextureRect.EXPAND_IGNORE_SIZE
	cap.position = Vector2(LauncherUI.FRAME, LauncherUI.FRAME)
	cap.size = Vector2(w, LauncherUI.CAPTION)
	frame.add_child(cap)
	var label := Label.new()
	label.text = title
	label.add_theme_color_override("font_color", Color.WHITE)
	label.add_theme_font_size_override("font_size", 13)
	label.position = Vector2(LauncherUI.FRAME + 3, LauncherUI.FRAME)
	label.size = Vector2(w - 24, LauncherUI.CAPTION)
	label.vertical_alignment = VERTICAL_ALIGNMENT_CENTER
	frame.add_child(label)
	var x := Button.new()   # (the system menu's close box)
	x.text = "x"
	x.focus_mode = Control.FOCUS_NONE
	x.add_theme_font_size_override("font_size", 11)
	x.position = Vector2(LauncherUI.FRAME + w - 18, LauncherUI.FRAME + 3)
	x.size = Vector2(16, 14)
	x.pressed.connect(close.bind(null))
	frame.add_child(x)
	client = Control.new()
	client.position = Vector2(LauncherUI.FRAME, LauncherUI.FRAME + LauncherUI.CAPTION + 1)
	client.size = Vector2(w, h)
	frame.add_child(client)
	owner.add_child(self)

func _unhandled_key_input(e: InputEvent) -> void:
	if e is InputEventKey and e.pressed and e.keycode == KEY_ESCAPE:
		get_viewport().set_input_as_handled()
		close(null)

func close(result) -> void:
	if _done:
		return
	_done = true
	closed.emit(result)
	queue_free()
