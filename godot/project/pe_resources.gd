class_name PeResources
extends RefCounted
## The resources of a Windows program (AxisPlay.exe: the launcher's button pictures, its icon and cursor), read from the
## user's own copy - nothing of it is shipped. Bitmaps, icons and cursors come back as Images.

var data := PackedByteArray()
var rsrc_rva := 0
var sections := []   # [virtual address, virtual size, file offset, file size]

const RT_CURSOR := 1
const RT_BITMAP := 2
const RT_ICON := 3
const RT_GROUP_CURSOR := 12
const RT_GROUP_ICON := 14

func open(path: String) -> bool:
	data = FileAccess.get_file_as_bytes(path)
	if data.size() < 0x40 or data.decode_u16(0) != 0x5a4d:   # "MZ"
		return false
	var pe := data.decode_u32(0x3c)
	if pe + 24 > data.size() or data.decode_u32(pe) != 0x4550:   # "PE\0\0"
		return false
	var nsec := data.decode_u16(pe + 6)
	var optsize := data.decode_u16(pe + 20)
	var opt := pe + 24
	var dirs := opt + (96 if data.decode_u16(opt) == 0x10b else 112)
	rsrc_rva = data.decode_u32(dirs + 2 * 8)   # (data directory 2: the resources)
	for i in nsec:
		var s := opt + optsize + i * 40
		sections.append([data.decode_u32(s + 12), data.decode_u32(s + 8), data.decode_u32(s + 20), data.decode_u32(s + 16)])
	return rsrc_rva != 0

func _offset(rva: int) -> int:
	for s in sections:
		if rva >= s[0] and rva < s[0] + maxi(s[1], s[3]):
			return s[2] + rva - s[0]
	return -1

## a directory's entry for an id (int) or a name (String): the subdirectory's offset, or the leaf's (negative: -1 none)
func _entry(root: int, dir: int, key, want_dir: bool) -> int:
	var count := data.decode_u16(dir + 12) + data.decode_u16(dir + 14)
	for i in count:
		var e := dir + 16 + i * 8
		var name := data.decode_u32(e)
		var off := data.decode_u32(e + 4)
		var hit := false
		if name & 0x80000000:
			if key is String:
				var p := root + (name & 0x7fffffff)
				var n := data.decode_u16(p)
				hit = data.slice(p + 2, p + 2 + n * 2).get_string_from_utf16().to_upper() == key.to_upper()
		elif key is int:
			hit = name == key
		if hit and ((off & 0x80000000) != 0) == want_dir:
			return root + (off & 0x7fffffff)
	return -1

## a resource's bytes (its first language)
func find(type: int, name) -> PackedByteArray:
	if rsrc_rva == 0:
		return PackedByteArray()
	var root := _offset(rsrc_rva)
	var t := _entry(root, root, type, true)
	if t < 0:
		return PackedByteArray()
	var n := _entry(root, t, name, true)
	if n < 0 or data.decode_u16(n + 12) + data.decode_u16(n + 14) == 0:
		return PackedByteArray()
	var leaf := root + (data.decode_u32(n + 16 + 4) & 0x7fffffff)
	var off := _offset(data.decode_u32(leaf))
	return data.slice(off, off + data.decode_u32(leaf + 4)) if off >= 0 else PackedByteArray()

## a bitmap resource (a DIB: the file header put in front of it)
func bitmap(id: int) -> Image:
	var dib := find(RT_BITMAP, id)
	if dib.is_empty():
		return null
	return bmp_image(dib, true)

## a .bmp file's bytes, or a resource's DIB (without the file header) as an Image
static func bmp_image(bytes: PackedByteArray, dib_only: bool) -> Image:
	var b := bytes
	if dib_only:
		var hsize := b.decode_u32(0)
		var bpp := b.decode_u16(14)
		var colors := b.decode_u32(32)
		if colors == 0 and bpp <= 8:
			colors = 1 << bpp
		var head := PackedByteArray()
		head.resize(14)
		head.encode_u16(0, 0x4d42)
		head.encode_u32(2, 14 + b.size())
		head.encode_u32(10, 14 + hsize + colors * 4)
		b = head + b
	var img := Image.new()
	return img if img.load_bmp_from_buffer(b) == OK else null

## an icon or cursor picture (a DIB of twice the height: the colours, then the AND mask), with its transparency
static func icon_image(dib: PackedByteArray) -> Image:
	var hsize := dib.decode_u32(0)
	var w := dib.decode_s32(4)
	var h := dib.decode_s32(8) / 2
	var bpp := dib.decode_u16(14)
	var colors := dib.decode_u32(32)
	if colors == 0 and bpp <= 8:
		colors = 1 << bpp
	var pal := hsize
	var px := hsize + colors * 4
	var stride := ((w * bpp + 31) / 32) * 4
	var mask := px + stride * h
	var mstride := ((w + 31) / 32) * 4
	var img := Image.create_empty(w, h, false, Image.FORMAT_RGBA8)
	for y in h:
		var row := px + (h - 1 - y) * stride
		var mrow := mask + (h - 1 - y) * mstride
		for x in w:
			var r := 0
			var g := 0
			var bl := 0
			var a := 255
			if bpp <= 8:
				var bit := x * bpp
				var v := (dib[row + bit / 8] >> (8 - bpp - bit % 8)) & ((1 << bpp) - 1)
				bl = dib[pal + v * 4]
				g = dib[pal + v * 4 + 1]
				r = dib[pal + v * 4 + 2]
			else:
				var o := row + x * (bpp / 8)
				bl = dib[o]
				g = dib[o + 1]
				r = dib[o + 2]
				if bpp == 32:
					a = dib[o + 3]
			if bpp != 32 and mask + mstride * h <= dib.size():
				if (dib[mrow + x / 8] >> (7 - x % 8)) & 1:
					a = 0
			img.set_pixel(x, y, Color8(r, g, bl, a))
	return img

## the best picture of an icon group (the most colours, then the biggest)
func icon(group) -> Image:
	var g := find(RT_GROUP_ICON, group)
	if g.size() < 6:
		return null
	var best := -1
	var score := -1
	for i in g.decode_u16(4):
		var e := 6 + i * 14
		var w := g[e] if g[e] != 0 else 256
		var s := g.decode_u16(e + 6) * 1000 + w
		if s > score:
			score = s
			best = g.decode_u16(e + 12)
	var dib := find(RT_ICON, best)
	return icon_image(dib) if not dib.is_empty() else null

## the best picture of a cursor group and its hot spot: [Image, Vector2i]
func cursor(group) -> Array:
	var g := find(RT_GROUP_CURSOR, group)
	if g.size() < 6:
		return []
	var best := -1
	var score := -1
	for i in g.decode_u16(4):
		var e := 6 + i * 14
		var s := g.decode_u16(e + 6) * 1000 + g.decode_u16(e)
		if s > score:
			score = s
			best = g.decode_u16(e + 12)
	var c := find(RT_CURSOR, best)
	if c.size() < 44:
		return []
	return [icon_image(c.slice(4)), Vector2i(c.decode_u16(0), c.decode_u16(2))]
