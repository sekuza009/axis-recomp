class_name LauncherUI
extends RefCounted
## The launcher's dialogs as AxisPlay.exe's (its dialog templates 382, 383, 385, 387): plain Windows dialogs - a caption,
## the grey face, bevelled push buttons, a list box - laid out in dialog units (the System font's: 2 pixels a unit
## across and down) and opened at the launcher's top left, modal (the launcher takes no clicks while one is open).

const FACE := Color8(212, 208, 200)
const LIGHT := Color8(255, 255, 255)
const SHADOW := Color8(128, 128, 128)
const DARK := Color8(64, 64, 64)
const CAPTION := 20
const FRAME := 3

static var _theme: Theme

## a bevel as a 6 x 6 nine-patch: the outer ring's top-left and bottom-right colours, the inner ring's, the face
static func _bevel(otl: Color, obr: Color, itl: Color, ibr: Color, face: Color) -> StyleBoxTexture:
	var img := Image.create_empty(6, 6, false, Image.FORMAT_RGBA8)
	img.fill(face)
	for i in 6:
		img.set_pixel(i, 0, otl)
		img.set_pixel(0, i, otl)
		img.set_pixel(i, 5, obr)
		img.set_pixel(5, i, obr)
	for i in range(1, 5):
		img.set_pixel(i, 1, itl)
		img.set_pixel(1, i, itl)
		img.set_pixel(i, 4, ibr)
		img.set_pixel(4, i, ibr)
	img.set_pixel(5, 0, obr)
	img.set_pixel(0, 5, obr)
	var s := StyleBoxTexture.new()
	s.texture = ImageTexture.create_from_image(img)
	s.set_texture_margin_all(2)
	s.set_content_margin_all(3)
	return s

static func theme() -> Theme:
	if _theme:
		return _theme
	var t := Theme.new()
	var font := SystemFont.new()
	font.font_names = PackedStringArray(["MS Sans Serif", "Microsoft Sans Serif", "Tahoma", "Arial", "DejaVu Sans"])
	font.font_weight = 700   # (the System font is a bold one)
	font.antialiasing = TextServer.FONT_ANTIALIASING_GRAY
	t.default_font = font
	t.default_font_size = 15
	var raised := _bevel(LIGHT, DARK, FACE, SHADOW, FACE)
	var sunk := _bevel(DARK, LIGHT, SHADOW, FACE, FACE)
	for st in ["normal", "hover", "disabled", "hover_pressed"]:
		t.set_stylebox(st, "Button", raised)
	t.set_stylebox("pressed", "Button", sunk)
	t.set_stylebox("focus", "Button", StyleBoxEmpty.new())
	for c in ["font_color", "font_hover_color", "font_pressed_color", "font_focus_color", "font_hover_pressed_color"]:
		t.set_color(c, "Button", Color.BLACK)
	t.set_color("font_disabled_color", "Button", SHADOW)
	var field := _bevel(SHADOW, LIGHT, DARK, FACE, Color.WHITE)
	t.set_stylebox("panel", "ItemList", field)
	t.set_stylebox("focus", "ItemList", StyleBoxEmpty.new())
	var sel := StyleBoxFlat.new()
	sel.bg_color = Color8(10, 36, 106)
	t.set_stylebox("selected", "ItemList", sel)
	t.set_stylebox("selected_focus", "ItemList", sel)
	t.set_stylebox("hovered", "ItemList", StyleBoxEmpty.new())
	t.set_stylebox("hovered_selected", "ItemList", sel)
	t.set_stylebox("hovered_selected_focus", "ItemList", sel)
	t.set_stylebox("cursor", "ItemList", StyleBoxEmpty.new())
	t.set_stylebox("cursor_unfocused", "ItemList", StyleBoxEmpty.new())
	t.set_color("font_color", "ItemList", Color.BLACK)
	t.set_color("font_hovered_color", "ItemList", Color.BLACK)
	t.set_color("font_selected_color", "ItemList", Color.WHITE)
	t.set_color("font_hovered_selected_color", "ItemList", Color.WHITE)
	t.set_constant("v_separation", "ItemList", 0)
	t.set_color("font_color", "Label", Color.BLACK)
	t.set_stylebox("panel", "Panel", _bevel(FACE, DARK, LIGHT, SHADOW, FACE))
	_theme = t
	return t

## a modal dialog of the given client size (dialog units) at the launcher's top left (LauncherDialog: its controls go
## in .client; close(value) frees it and fires "closed" with the value)
static func dialog(owner: Control, title: String, w: int, h: int) -> LauncherDialog:
	var d := LauncherDialog.new()
	d.build(owner, title, w * 2, h * 2)
	return d

## a push button at (x, y), w x h dialog units
static func button(d: LauncherDialog, text: String, x: int, y: int, w: int, h: int) -> Button:
	var b := Button.new()
	b.text = text
	b.focus_mode = Control.FOCUS_NONE
	b.position = Vector2(x * 2, y * 2)
	b.size = Vector2(w * 2, h * 2)
	d.client.add_child(b)
	return b
