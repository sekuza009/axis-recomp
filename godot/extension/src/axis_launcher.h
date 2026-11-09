// axis_launcher.h: what the launcher scene (project/launcher.gd, the rewrite of AxisPlay.exe) needs from the system -
// the game's settings under HKEY_CURRENT_USER\SOFTWARE\AxisArena (the registry on Windows; elsewhere the library's
// stand-in, src/plat/posix/registry.c, so the launcher and the game share them) and the system's language.
#pragma once
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/variant.hpp>

namespace godot {

class AxisLauncher : public RefCounted {
	GDCLASS(AxisLauncher, RefCounted)

public:
	// a value of HKCU\<key>: an int (REG_DWORD), a String (REG_SZ, up to its first NUL), or null when it is missing
	Variant reg_get(const String &p_key, const String &p_name);
	// HKCU\<key> created when missing: 1 created now, 2 it was there, 0 failed (AxisPlay writes its defaults on 1)
	int reg_create(const String &p_key);
	// a REG_SZ of 'size' bytes (the text, then zeros; AxisPlay writes fixed sizes) - size <= 0: the text and its NUL
	bool reg_set_string(const String &p_key, const String &p_name, const String &p_value, int p_size);
	bool reg_set_int(const String &p_key, const String &p_name, int p_value);
	// the system's language is Korean (AxisPlay's GetSystemDefaultLangID check: the Korean texts and readme)
	bool system_korean();

protected:
	static void _bind_methods();
};

} // namespace godot
