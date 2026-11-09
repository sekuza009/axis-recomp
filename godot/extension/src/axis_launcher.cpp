// axis_launcher.cpp: AxisLauncher (axis_launcher.h).
#include "axis_launcher.h"
#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <string.h>
#include <vector>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <stdint.h>
extern "C" {   // src/plat/posix/registry.c (built into this extension: project SConstruct)
int plat_regOpen(uint32_t root, const char *path, uint32_t *key);
int plat_regCreate(uint32_t root, const char *path, uint32_t *key, uint32_t *disposition);
int plat_regQuery(uint32_t key, const char *name, uint32_t *type, void *data, uint32_t *size);
int plat_regSet(uint32_t key, const char *name, uint32_t type, const void *data, uint32_t size);
uint32_t plat_regClose(uint32_t key);
}
#endif

using namespace godot;

// (the game's texts are the system's ANSI code page on Windows - as the game writes them; UTF-8 elsewhere)
static std::vector<char> to_native(const String &s) {
	std::vector<char> out;
#ifdef _WIN32
	const Char16String w = s.utf16();
	const int n = WideCharToMultiByte(CP_ACP, 0, (LPCWCH)w.get_data(), -1, nullptr, 0, nullptr, nullptr);
	out.resize(n > 0 ? n : 1, 0);
	if (n > 0)
		WideCharToMultiByte(CP_ACP, 0, (LPCWCH)w.get_data(), -1, out.data(), n, nullptr, nullptr);
#else
	const CharString u = s.utf8();
	out.assign(u.get_data(), u.get_data() + u.length() + 1);
#endif
	return out;
}
static String from_native(const char *p, size_t n) {
	size_t len = 0;
	while (len < n && p[len])
		len++;
#ifdef _WIN32
	const int w = MultiByteToWideChar(CP_ACP, 0, p, (int)len, nullptr, 0);
	std::vector<wchar_t> buf(w > 0 ? w : 0);
	if (w > 0)
		MultiByteToWideChar(CP_ACP, 0, p, (int)len, buf.data(), w);
	return String::utf16((const char16_t *)buf.data(), w > 0 ? w : 0);
#else
	return String::utf8(p, (int)len);
#endif
}

#ifdef _WIN32
typedef HKEY RegKey;
static bool open_key(const String &k, RegKey *out) {
	return RegOpenKeyExA(HKEY_CURRENT_USER, to_native(k).data(), 0, KEY_ALL_ACCESS, out) == ERROR_SUCCESS;
}
static void close_key(RegKey k) { RegCloseKey(k); }
static bool reg_read(RegKey k, const char *name, DWORD *type, void *data, DWORD *size) {
	return RegQueryValueExA(k, name, nullptr, type, (LPBYTE)data, size) == ERROR_SUCCESS;
}
static bool reg_write(RegKey k, const char *name, DWORD type, const void *data, DWORD size) {
	return RegSetValueExA(k, name, 0, type, (const BYTE *)data, size) == ERROR_SUCCESS;
}
#else
typedef uint32_t RegKey;
static bool open_key(const String &k, RegKey *out) { return plat_regOpen(0x80000001u, to_native(k).data(), out) == 0; }
static void close_key(RegKey k) { plat_regClose(k); }
static bool reg_read(RegKey k, const char *name, uint32_t *type, void *data, uint32_t *size) {
	return plat_regQuery(k, name, type, data, size) == 0;
}
static bool reg_write(RegKey k, const char *name, uint32_t type, const void *data, uint32_t size) {
	return plat_regSet(k, name, type, data, size) == 0;
}
typedef uint32_t DWORD;
#endif

Variant AxisLauncher::reg_get(const String &p_key, const String &p_name) {
	RegKey k;
	if (!open_key(p_key, &k))
		return Variant();
	char data[1024];
	DWORD type = 0, size = sizeof data;
	Variant r;
	if (reg_read(k, to_native(p_name).data(), &type, data, &size)) {
		if (type == 4 && size >= 4) {   // REG_DWORD
			int v;
			memcpy(&v, data, 4);
			r = v;
		} else if (type == 1 || type == 2)   // REG_SZ, REG_EXPAND_SZ
			r = from_native(data, size);
	}
	close_key(k);
	return r;
}

int AxisLauncher::reg_create(const String &p_key) {
#ifdef _WIN32
	HKEY k;
	DWORD disposition = 0;
	if (RegCreateKeyExA(HKEY_CURRENT_USER, to_native(p_key).data(), 0, nullptr, 0, KEY_ALL_ACCESS, nullptr, &k,
				&disposition) != ERROR_SUCCESS)
		return 0;
	RegCloseKey(k);
	return (int)disposition;
#else
	uint32_t k, disposition = 0;
	if (plat_regCreate(0x80000001u, to_native(p_key).data(), &k, &disposition) != 0)
		return 0;
	plat_regClose(k);
	return (int)disposition;
#endif
}

bool AxisLauncher::reg_set_string(const String &p_key, const String &p_name, const String &p_value, int p_size) {
	RegKey k;
	if (!open_key(p_key, &k))
		return false;
	std::vector<char> v = to_native(p_value);
	if (p_size > 0)
		v.resize((size_t)p_size, 0);
	const bool ok = reg_write(k, to_native(p_name).data(), 1, v.data(), (DWORD)v.size());
	close_key(k);
	return ok;
}

bool AxisLauncher::reg_set_int(const String &p_key, const String &p_name, int p_value) {
	RegKey k;
	if (!open_key(p_key, &k))
		return false;
	const bool ok = reg_write(k, to_native(p_name).data(), 4, &p_value, 4);
	close_key(k);
	return ok;
}

bool AxisLauncher::system_korean() {
#ifdef _WIN32
	return PRIMARYLANGID(GetSystemDefaultLangID()) == LANG_KOREAN;
#else
	return OS::get_singleton()->get_locale_language() == "ko";
#endif
}

void AxisLauncher::_bind_methods() {
	ClassDB::bind_method(D_METHOD("reg_get", "key", "name"), &AxisLauncher::reg_get);
	ClassDB::bind_method(D_METHOD("reg_create", "key"), &AxisLauncher::reg_create);
	ClassDB::bind_method(D_METHOD("reg_set_string", "key", "name", "value", "size"), &AxisLauncher::reg_set_string);
	ClassDB::bind_method(D_METHOD("reg_set_int", "key", "name", "value"), &AxisLauncher::reg_set_int);
	ClassDB::bind_method(D_METHOD("system_korean"), &AxisLauncher::system_korean);
}
