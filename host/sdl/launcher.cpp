// launcher.cpp: the launcher (launcher.h) - AxisPlay.exe rewritten from its decompiled code, as the Godot build's
// launcher.gd (godot branch; the addresses are AxisPlay.exe's): a 642 x 482 bordered window centred on the screen
// (0x402070) with Launcher\Resource\BackGround\MainBK.bmp and eight buttons whose four pictures (normal, lit, pressed,
// grey: 0x402730) and the window's icon and cursor are read from the user's own AxisPlay.exe; the pointer over a button
// lights it with Launcher\lsound\mmove.wav (0x403e20), a press plays mclick.wav, shows it pressed and acts at once
// (0x404280, 0x404700), the release shows it normal again (0x404500). Installed (MathFunc.tbl there, 0x4054d0): Install
// Game grey, the rest live; otherwise only Install Game, Help, Install DirectX and Quit. Play Game starts the game in
// this program. The dialogs: on Windows the original's own (its dialog templates, from AxisPlay.exe, run by Windows);
// elsewhere message boxes with the same choices. Nothing of the game is in this program: the pictures, sounds, texts
// and movies are the user's files.
#include "launcher.h"
#include <SDL3/SDL.h>
#include <cstdint>
#include <cstring>
#include <vector>

#include "../../standalone/avimovie.h"   // (the movies' reader and decoder, in the game library)

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
extern "C" {   // (the settings' store of the library: src/plat/posix/registry.c - the game's own, in this process)
int plat_regOpen(uint32_t root, const char *path, uint32_t *key);
int plat_regCreate(uint32_t root, const char *path, uint32_t *key, uint32_t *disposition);
int plat_regQuery(uint32_t key, const char *name, uint32_t *type, void *data, uint32_t *size);
int plat_regSet(uint32_t key, const char *name, uint32_t type, const void *data, uint32_t size);
uint32_t plat_regClose(uint32_t key);
}
#endif

namespace {

const int W = 642, H = 482;
const SDL_Rect RECTS[8] = { { 150, 16, 191, 44 }, { 78, 65, 191, 44 }, { 34, 114, 191, 44 }, { 11, 163, 191, 44 },
	{ 439, 260, 191, 44 }, { 419, 309, 191, 44 }, { 378, 358, 191, 44 }, { 300, 407, 191, 44 } };   // (0x402660)
const int BITMAPS[8][4] = { { 325, 327, 326, 394 }, { 329, 328, 330, 398 }, { 332, 331, 333, 395 }, { 335, 334, 336, 392 },
	{ 338, 337, 339, 391 }, { 341, 340, 342, 393 }, { 344, 343, 345, 396 }, { 374, 375, 373, 399 } };
enum { INSTALL, PLAY, CINEMATICS, HELP, SERVER, DIRECTX, VIDEO, QUIT };
enum { NORMAL, LIT, PRESSED, GREY };
const char *LAUNCHER_KEY = "SOFTWARE\\AxisArena\\Launcher";
const char *SERVER_KEY = "SOFTWARE\\AxisArena\\SelectServer";

std::string g_dir;
bool g_korean;
SDL_Window *g_win;
SDL_Renderer *g_ren;

// ---- texts (AxisPlay.exe's English and Korean)
struct Text { const char *en, *ko; };
const Text T_RENDER = { "Select Render Mode in Video Setup", "Video Setup\xec\x97\x90\xec\x84\x9c Render Mode\xeb\xa5\xbc \xec\x84\xa0\xed\x83\x9d\xed\x95\x98\xec\x97\xac \xec\xa3\xbc\xec\x8b\xad\xec\x8b\x9c\xec\x98\xa4" };
const Text T_INSTALL = { " Please Install Axis", "Axis\xeb\xa5\xbc \xec\x9d\xb8\xec\x8a\xa4\xed\x86\xa8 \xed\x95\x98\xec\x97\xac \xec\xa3\xbc\xec\x8b\xad\xec\x8b\x9c\xec\x98\xa4." };
const Text T_NOLIST = { "Can't read ServerList.dat. Server list update", "ServerList.dat\xeb\xa5\xbc \xec\x9d\xbd\xec\x96\xb4 \xeb\x93\xa4\xec\x9d\xb4\xec\xa7\x80 \xeb\xaa\xbb\xed\x96\x88\xec\x8a\xb5\xeb\x8b\x88\xeb\x8b\xa4. Server List\xeb\xa5\xbc Update\xed\x95\x98\xec\x97\xac \xec\xa3\xbc\xec\x8b\xad\xec\x8b\x9c\xec\x98\xa4" };
const Text T_PICK = { "Under of ListBox to Server Select", "\xec\x95\x84\xeb\x9e\x98 \xeb\xa6\xac\xec\x8a\xa4\xed\x8a\xb8\xec\x97\x90\xec\x84\x9c \xec\x84\x9c\xeb\xb2\x84\xec\x9d\x84 \xec\x84\xa0\xed\x83\x9d\xed\x95\x98\xec\x97\xac \xec\xa3\xbc\xec\x8b\xad\xec\x8b\x9c\xec\x98\xa4" };
const Text T_NOTEPAD = { "Can't find 'notepad.exe'", "notepad.exe\xeb\xa5\xbc \xec\xb0\xbe\xec\x9d\x84 \xec\x88\x98 \xec\x97\x86\xec\x8a\xb5\xeb\x8b\x88\xeb\x8b\xa4" };
const Text T_BROWSER = { "Can't find primary webbrowser", "\xea\xb8\xb0\xeb\xb3\xb8 \xeb\xb8\x8c\xeb\x9d\xbc\xec\x9a\xb0\xec\xa0\xb8\xec\x9d\x84 \xec\xb0\xbe\xec\x9d\x84 \xec\x88\x98 \xec\x97\x86\xec\x8a\xb5\xeb\x8b\x88\xeb\x8b\xa4" };
const Text T_DIRECTX = { "DirectX 7.0 or higher is already installed. Would you like to re-install?",
	"\xec\x9d\xb4\xeb\xaf\xb8 DirectX 7.0\xec\x9d\xb4\xec\x83\x81 \xeb\xb2\x84\xec\xa0\xbc\xec\x9d\xb4 \xec\x84\xa4\xec\xb9\x98\xeb\x90\x98\xec\x96\xb4 \xec\x9e\x88\xec\x8a\xb5\xeb\x8b\x88\xeb\x8b\xa4. \xea\xb7\xb8\xeb\x9e\x98\xeb\x8f\x84 \xec\x84\xa4\xec\xb9\x98 \xed\x95\x98\xec\x8b\x9c\xea\xb2\xa0\xec\x8a\xb5\xeb\x8b\x88\xea\xb9\x8c?" };
const char *text(const Text &t) { return g_korean ? t.ko : t.en; }
void alert(const Text &t, const char *title) { SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title, text(t), g_win); }

// ---- the game's files by their own (Windows, case-free) names: each part matched without regard to case
std::string resolve(const std::string &rel) {
	std::string path = g_dir.substr(0, g_dir.size() - 1);
	size_t at = 0;
	while (at <= rel.size()) {
		size_t end = rel.find_first_of("\\/", at);
		if (end == std::string::npos) end = rel.size();
		std::string part = rel.substr(at, end - at);
		at = end + 1;
		if (part.empty() || part == ".") continue;
		std::string exact = path + "/" + part;
		if (SDL_GetPathInfo(exact.c_str(), nullptr)) { path = exact; continue; }
		struct Find { const char *want; std::string found; } f = { part.c_str(), "" };
		SDL_EnumerateDirectory(path.c_str(), [](void *u, const char *, const char *name) -> SDL_EnumerationResult {
			Find *f = (Find *)u;
			if (SDL_strcasecmp(name, f->want) == 0) { f->found = name; return SDL_ENUM_SUCCESS; }
			return SDL_ENUM_CONTINUE;
		}, &f);
		if (f.found.empty()) return "";
		path += "/" + f.found;
	}
	return path;
}
std::vector<uint8_t> read_file(const std::string &path) {
	size_t n = 0;
	void *d = path.empty() ? nullptr : SDL_LoadFile(path.c_str(), &n);
	std::vector<uint8_t> v;
	if (d) { v.assign((uint8_t *)d, (uint8_t *)d + n); SDL_free(d); }
	return v;
}

// ---- settings: HKEY_CURRENT_USER\SOFTWARE\AxisArena (the registry on Windows; the library's store elsewhere)
#ifdef _WIN32
int reg_create(const char *key) {
	HKEY k; DWORD disp = 0;
	if (RegCreateKeyExA(HKEY_CURRENT_USER, key, 0, nullptr, 0, KEY_ALL_ACCESS, nullptr, &k, &disp) != ERROR_SUCCESS) return 0;
	RegCloseKey(k);
	return (int)disp;
}
bool reg_get(const char *key, const char *name, DWORD *type, uint8_t *data, DWORD *size) {
	HKEY k;
	if (RegOpenKeyExA(HKEY_CURRENT_USER, key, 0, KEY_ALL_ACCESS, &k) != ERROR_SUCCESS) return false;
	bool ok = RegQueryValueExA(k, name, nullptr, type, data, size) == ERROR_SUCCESS;
	RegCloseKey(k);
	return ok;
}
bool reg_set(const char *key, const char *name, DWORD type, const void *data, DWORD size) {
	HKEY k;
	if (RegOpenKeyExA(HKEY_CURRENT_USER, key, 0, KEY_ALL_ACCESS, &k) != ERROR_SUCCESS) return false;
	bool ok = RegSetValueExA(k, name, 0, type, (const BYTE *)data, size) == ERROR_SUCCESS;
	RegCloseKey(k);
	return ok;
}
#else
typedef uint32_t DWORD;
int reg_create(const char *key) {
	uint32_t k, disp = 0;
	if (plat_regCreate(0x80000001u, key, &k, &disp) != 0) return 0;
	plat_regClose(k);
	return (int)disp;
}
bool reg_get(const char *key, const char *name, DWORD *type, uint8_t *data, DWORD *size) {
	uint32_t k;
	if (plat_regOpen(0x80000001u, key, &k) != 0) return false;
	bool ok = plat_regQuery(k, name, type, data, size) == 0;
	plat_regClose(k);
	return ok;
}
bool reg_set(const char *key, const char *name, DWORD type, const void *data, DWORD size) {
	uint32_t k;
	if (plat_regOpen(0x80000001u, key, &k) != 0) return false;
	bool ok = plat_regSet(k, name, type, data, size) == 0;
	plat_regClose(k);
	return ok;
}
#endif
bool get_int(const char *key, const char *name, int *out) {
	DWORD type = 0, size = 4;
	uint8_t d[4];
	if (!reg_get(key, name, &type, d, &size) || type != 4) return false;
	memcpy(out, d, 4);
	return true;
}
bool get_string(const char *key, const char *name, std::string *out) {
	DWORD type = 0, size = 255;
	uint8_t d[256] = {};
	if (!reg_get(key, name, &type, d, &size) || type != 1) return false;
	*out = (const char *)d;
	return true;
}
void set_int(const char *key, const char *name, int v) { reg_set(key, name, 4, &v, 4); }
void set_string(const char *key, const char *name, const std::string &s, int size) {   // (AxisPlay writes fixed sizes)
	std::vector<char> b((size_t)size, 0);
	memcpy(b.data(), s.c_str(), s.size() < (size_t)size ? s.size() : (size_t)size - 1);
	reg_set(key, name, 1, b.data(), (DWORD)size);
}

bool korean() {
#ifdef _WIN32
	return PRIMARYLANGID(GetSystemDefaultLangID()) == LANG_KOREAN;
#else
	const char *v = SDL_getenv("LC_ALL");
	if (!v || !*v) v = SDL_getenv("LC_MESSAGES");
	if (!v || !*v) v = SDL_getenv("LANG");
	if (v && *v) return SDL_strncasecmp(v, "ko", 2) == 0;
	int n = 0;
	SDL_Locale **l = SDL_GetPreferredLocales(&n);   // (macOS from the Finder: the system's languages)
	bool k = l && n > 0 && l[0]->language && SDL_strcasecmp(l[0]->language, "ko") == 0;
	SDL_free(l);
	return k;
#endif
}

// ---- AxisPlay.exe's resources: bitmaps, the icon, the cursor
struct Pe {
	std::vector<uint8_t> d;
	uint32_t rsrc = 0;
	struct Sec { uint32_t va, vs, off, sz; };
	std::vector<Sec> secs;
	uint32_t u16(size_t o) const { return o + 2 <= d.size() ? d[o] | d[o + 1] << 8 : 0; }
	uint32_t u32(size_t o) const { return o + 4 <= d.size() ? d[o] | d[o + 1] << 8 | d[o + 2] << 16 | (uint32_t)d[o + 3] << 24 : 0; }
	bool open(const std::string &path) {
		d = read_file(path);
		if (d.size() < 0x40 || u16(0) != 0x5a4d) return false;
		uint32_t pe = u32(0x3c);
		if (u32(pe) != 0x4550) return false;
		uint32_t nsec = u16(pe + 6), optsize = u16(pe + 20), opt = pe + 24;
		rsrc = u32(opt + (u16(opt) == 0x10b ? 96 : 112) + 16);
		for (uint32_t i = 0; i < nsec; i++) {
			uint32_t s = opt + optsize + i * 40;
			secs.push_back({ u32(s + 12), u32(s + 8), u32(s + 20), u32(s + 16) });
		}
		return rsrc != 0;
	}
	long offset(uint32_t rva) const {
		for (const Sec &s : secs)
			if (rva >= s.va && rva < s.va + (s.vs > s.sz ? s.vs : s.sz)) return (long)(s.off + rva - s.va);
		return -1;
	}
	long entry(long root, long dir, int id, const char *name, bool wantDir) const {
		uint32_t n = u16(dir + 12) + u16(dir + 14);
		for (uint32_t i = 0; i < n; i++) {
			long e = dir + 16 + i * 8;
			uint32_t nm = u32(e), off = u32(e + 4);
			bool hit = false;
			if (nm & 0x80000000u) {
				if (name) {
					long p = root + (nm & 0x7fffffff);
					uint32_t len = u16(p);
					std::string s;
					for (uint32_t k = 0; k < len; k++) s += (char)u16(p + 2 + k * 2);
					hit = SDL_strcasecmp(s.c_str(), name) == 0;
				}
			} else if (!name)
				hit = (int)nm == id;
			if (hit && ((off & 0x80000000u) != 0) == wantDir) return root + (off & 0x7fffffff);
		}
		return -1;
	}
	std::vector<uint8_t> find(int type, int id, const char *name = nullptr) const {
		long root = offset(rsrc);
		if (root < 0) return {};
		long t = entry(root, root, type, nullptr, true);
		if (t < 0) return {};
		long n = entry(root, t, id, name, true);
		if (n < 0 || u16(n + 12) + u16(n + 14) == 0) return {};
		long leaf = root + (u32(n + 20) & 0x7fffffff);
		long off = offset(u32(leaf));
		uint32_t size = u32(leaf + 4);
		if (off < 0 || (size_t)off + size > d.size()) return {};
		return std::vector<uint8_t>(d.begin() + off, d.begin() + off + size);
	}
};
Pe g_pe;

SDL_Surface *bmp_surface(const std::vector<uint8_t> &bytes, bool dibOnly) {
	if (bytes.size() < 40) return nullptr;
	std::vector<uint8_t> b;
	if (dibOnly) {   // (the file header put in front of the resource's DIB)
		uint32_t hsize = bytes[0] | bytes[1] << 8, bpp = bytes[14] | bytes[15] << 8;
		uint32_t colors = bytes[32] | bytes[33] << 8;
		if (!colors && bpp <= 8) colors = 1u << bpp;
		uint32_t total = 14 + (uint32_t)bytes.size(), off = 14 + hsize + colors * 4;
		uint8_t h[14] = { 'B', 'M', (uint8_t)total, (uint8_t)(total >> 8), (uint8_t)(total >> 16), (uint8_t)(total >> 24), 0, 0, 0, 0,
			(uint8_t)off, (uint8_t)(off >> 8), (uint8_t)(off >> 16), (uint8_t)(off >> 24) };
		b.assign(h, h + 14);
	}
	b.insert(b.end(), bytes.begin(), bytes.end());
	return SDL_LoadBMP_IO(SDL_IOFromConstMem(b.data(), b.size()), true);
}
// an icon's or cursor's picture: a DIB of twice the height (the colours, then the AND mask) -> RGBA
SDL_Surface *icon_surface(const std::vector<uint8_t> &dib) {
	auto u32 = [&](size_t o) { return o + 4 <= dib.size() ? (uint32_t)(dib[o] | dib[o + 1] << 8 | dib[o + 2] << 16 | dib[o + 3] << 24) : 0u; };
	if (dib.size() < 40) return nullptr;
	uint32_t hsize = u32(0);
	int w = (int)u32(4), h = (int)u32(8) / 2, bpp = dib[14] | dib[15] << 8;
	uint32_t colors = u32(32);
	if (!colors && bpp <= 8) colors = 1u << bpp;
	size_t pal = hsize, px = hsize + colors * 4, stride = (size_t)((w * bpp + 31) / 32) * 4, mask = px + stride * h,
	       mstride = (size_t)((w + 31) / 32) * 4;
	if (w <= 0 || h <= 0 || px + stride * h > dib.size()) return nullptr;
	SDL_Surface *s = SDL_CreateSurface(w, h, SDL_PIXELFORMAT_RGBA32);
	for (int y = 0; y < h; y++) {
		size_t row = px + (size_t)(h - 1 - y) * stride, mrow = mask + (size_t)(h - 1 - y) * mstride;
		uint8_t *o = (uint8_t *)s->pixels + (size_t)y * s->pitch;
		for (int x = 0; x < w; x++, o += 4) {
			uint8_t r, g, b, a = 255;
			if (bpp <= 8) {
				int bit = x * bpp, v = (dib[row + bit / 8] >> (8 - bpp - bit % 8)) & ((1 << bpp) - 1);
				b = dib[pal + v * 4]; g = dib[pal + v * 4 + 1]; r = dib[pal + v * 4 + 2];
			} else {
				size_t e = row + (size_t)x * (bpp / 8);
				b = dib[e]; g = dib[e + 1]; r = dib[e + 2];
				if (bpp == 32) a = dib[e + 3];
			}
			if (bpp != 32 && mask + mstride * h <= dib.size() && ((dib[mrow + x / 8] >> (7 - x % 8)) & 1)) a = 0;
			o[0] = r; o[1] = g; o[2] = b; o[3] = a;
		}
	}
	return s;
}
// the best picture of an icon (14) or cursor (12) group; a cursor's hot spot
SDL_Surface *group_picture(int groupType, int id, const char *name, int *hx, int *hy) {
	std::vector<uint8_t> g = g_pe.find(groupType, id, name);
	if (g.size() < 6) return nullptr;
	int best = -1, score = -1, count = g[4] | g[5] << 8;
	for (int i = 0; i < count; i++) {
		size_t e = 6 + (size_t)i * 14;
		if (e + 14 > g.size()) break;
		int bits = g[e + 6] | g[e + 7] << 8, wd = groupType == 14 ? (g[e] ? g[e] : 256) : (g[e] | g[e + 1] << 8);
		if (bits * 1000 + wd > score) { score = bits * 1000 + wd; best = g[e + 12] | g[e + 13] << 8; }
	}
	std::vector<uint8_t> d = g_pe.find(groupType == 14 ? 3 : 1, best);
	if (groupType == 12) {
		if (d.size() < 44) return nullptr;
		*hx = d[0] | d[1] << 8;
		*hy = d[2] | d[3] << 8;
		d.erase(d.begin(), d.begin() + 4);
	}
	return icon_surface(d);
}

// ---- sounds (sndPlaySound: asynchronous, a new one stops the last)
struct Sound { SDL_AudioStream *stream = nullptr; Uint8 *buf = nullptr; Uint32 len = 0; };
Sound g_snd[2];
void sound_load(Sound &s, const char *rel) {
	std::string p = resolve(rel);
	SDL_AudioSpec spec;
	if (p.empty() || !SDL_LoadWAV(p.c_str(), &spec, &s.buf, &s.len)) return;
	s.stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, nullptr, nullptr);
	if (s.stream) SDL_ResumeAudioStreamDevice(s.stream);
}
void sound_play(int i) {
	for (Sound &s : g_snd) if (s.stream) SDL_ClearAudioStream(s.stream);
	if (g_snd[i].stream) SDL_PutAudioStreamData(g_snd[i].stream, g_snd[i].buf, (int)g_snd[i].len);
}

// ---- the window's state
SDL_Texture *g_back, *g_pics[8][4];
int g_state[8];
bool g_lit[8], g_installed;
bool live(int i) {
#ifndef _WIN32
	if (i == DIRECTX) return false;   // (DirectX 7's installer: Windows only)
#endif
	return g_installed ? i != INSTALL : (i == INSTALL || i == HELP || i == DIRECTX || i == QUIT);
}
void draw() {
	SDL_SetRenderDrawColor(g_ren, 0, 0, 0, 255);   // (WS_BORDER)
	SDL_RenderClear(g_ren);
	SDL_FRect bk = { 1, 1, (float)(W - 2), (float)(H - 2) };
	if (g_back) SDL_RenderTexture(g_ren, g_back, nullptr, &bk);
	for (int i = 0; i < 8; i++) {
		SDL_Texture *t = g_pics[i][live(i) ? g_state[i] : GREY];
		if (!t) continue;
		float tw, th;
		SDL_GetTextureSize(t, &tw, &th);
		SDL_FRect r = { (float)RECTS[i].x + 1, (float)RECTS[i].y + 1, tw, th };
		SDL_RenderTexture(g_ren, t, nullptr, &r);
	}
	SDL_RenderPresent(g_ren);
}
int hit(float x, float y) {
	x -= 1; y -= 1;   // (the client area: inside the border)
	for (int i = 0; i < 8; i++)
		if (x >= RECTS[i].x && y >= RECTS[i].y && x < RECTS[i].x + RECTS[i].w && y < RECTS[i].y + RECTS[i].h) return i;
	return -1;
}

// ---- the dialogs
#ifdef _WIN32
// the original's dialog templates (382 Cinematics, 383 Video Setup, 385 Help, 387 Select Server List), from
// AxisPlay.exe loaded as data, run by Windows with these procedures
HMODULE g_res;
struct DlgState { int ending; std::vector<std::string> *servers; bool getlist; int picked; };
INT_PTR CALLBACK dlg_proc(HWND d, UINT m, WPARAM wp, LPARAM lp) {
	DlgState *s = (DlgState *)GetWindowLongPtrA(d, DWLP_USER);
	switch (m) {
	case WM_INITDIALOG: {
		SetWindowLongPtrA(d, DWLP_USER, lp);
		s = (DlgState *)lp;
		HWND owner = GetWindow(d, GW_OWNER);   // (at the launcher's top left, as the original's dialogs opened)
		if (owner) {
			POINT o = { 0, 0 };
			ClientToScreen(owner, &o);
			SetWindowPos(d, nullptr, o.x, o.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
		}
	}
		if (GetDlgItem(d, 1079)) EnableWindow(GetDlgItem(d, 1079), s->ending);   // (Ending Cinema: once EndMode is set)
		if (GetDlgItem(d, 1083)) {   // (Video Setup: one renderer here - OpenGL; Direct3D, Savage, GLSetup grey)
			EnableWindow(GetDlgItem(d, 1083), FALSE);
			EnableWindow(GetDlgItem(d, 1084), FALSE);
			EnableWindow(GetDlgItem(d, 1096), FALSE);
		}
		if (GetDlgItem(d, 1089) && s->servers) {   // (Select Server List)
			SetDlgItemTextA(d, 1090, text(T_PICK));
			for (const std::string &n : *s->servers) SendDlgItemMessageA(d, 1089, LB_ADDSTRING, 0, (LPARAM)n.c_str());
			EnableWindow(GetDlgItem(d, IDOK), FALSE);
			EnableWindow(GetDlgItem(d, 1094), s->getlist);
		}
		return TRUE;
	case WM_COMMAND: {
		int id = LOWORD(wp);
		if (id == 1089 && HIWORD(wp) == LBN_SELCHANGE) {
			EnableWindow(GetDlgItem(d, IDOK), TRUE);
			return TRUE;
		}
		if (id == IDOK && s) s->picked = (int)SendDlgItemMessageA(d, 1089, LB_GETCURSEL, 0, 0);
		if (id == IDCANCEL || id == IDOK || (id >= 1078 && id <= 1096)) {
			EndDialog(d, id);
			return TRUE;
		}
		return FALSE;
	}
	case WM_CLOSE:
		EndDialog(d, IDCANCEL);
		return TRUE;
	}
	return FALSE;
}
int dialog(int templ, DlgState *s) {
	HWND owner = (HWND)SDL_GetPointerProperty(SDL_GetWindowProperties(g_win), SDL_PROP_WINDOW_WIN32_HWND_POINTER, nullptr);
	return (int)DialogBoxParamA(g_res, MAKEINTRESOURCEA(templ), owner, dlg_proc, (LPARAM)s);
}
#endif
// elsewhere: a message box with the choices (buttons: their ids)
int choose(const char *title, const char *message, const std::vector<std::pair<int, const char *>> &buttons) {
	std::vector<SDL_MessageBoxButtonData> b;
	for (const auto &p : buttons) b.push_back({ 0, p.first, p.second });
	SDL_MessageBoxData d = { SDL_MESSAGEBOX_INFORMATION, g_win, title, message, (int)b.size(), b.data(), nullptr };
	int id = -1;
	if (!SDL_ShowMessageBox(&d, &id)) return -1;
	return id;
}

// ---- the movies: full screen, the shape kept, the pointer hidden; a new press of Esc ends one (0x401000, 0x401230)
void movie(const char *rel) {
	std::string p = resolve(rel);
	AviMovie *m = p.empty() ? nullptr : avimovie_open(p.c_str());
	if (!m) return;
	const AviMovieInfo *in = avimovie_info(m);
	SDL_SetWindowFullscreen(g_win, true);
	SDL_SetRenderLogicalPresentation(g_ren, 0, 0, SDL_LOGICAL_PRESENTATION_DISABLED);
	SDL_HideCursor();
	SDL_Texture *tex = SDL_CreateTexture(g_ren, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, in->width, in->height);
	SDL_AudioStream *audio = nullptr;
	double length = (double)in->frames * in->scale / in->rate;
	if (in->pcm) {
		const uint8_t *w = in->waveFormat;
		SDL_AudioSpec spec = { (w[14] == 8) ? SDL_AUDIO_U8 : SDL_AUDIO_S16LE, w[2], (int)(w[4] | w[5] << 8 | w[6] << 16 | (uint32_t)w[7] << 24) };
		audio = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, nullptr, nullptr);
		if (audio) {
			SDL_PutAudioStreamData(audio, in->pcm, (int)in->pcmBytes);
			SDL_ResumeAudioStreamDevice(audio);
		}
	}
	Uint64 start = SDL_GetTicks();
	bool done = false;
	while (!done) {
		SDL_Event e;
		while (SDL_PollEvent(&e))
			if ((e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE && !e.key.repeat) || e.type == SDL_EVENT_QUIT) done = true;
		double t = (SDL_GetTicks() - start) / 1000.0;
		if (avimovie_decode_to(m, (int)(t * in->rate / in->scale) + 1))
			SDL_UpdateTexture(tex, nullptr, avimovie_rgb(m), in->width * 3);
		int ow, oh;
		SDL_GetRenderOutputSize(g_ren, &ow, &oh);
		float s = (float)ow / in->width < (float)oh / in->height ? (float)ow / in->width : (float)oh / in->height;
		SDL_FRect r = { (ow - in->width * s) / 2, (oh - in->height * s) / 2, in->width * s, in->height * s };
		SDL_SetRenderDrawColor(g_ren, 0, 0, 0, 255);
		SDL_RenderClear(g_ren);
		SDL_RenderTexture(g_ren, tex, nullptr, &r);
		SDL_RenderPresent(g_ren);
		if (t >= length) done = true;
	}
	if (audio) SDL_DestroyAudioStream(audio);
	SDL_DestroyTexture(tex);
	avimovie_close(m);
	SDL_ShowCursor();
	SDL_SetWindowFullscreen(g_win, false);
	SDL_SetRenderLogicalPresentation(g_ren, W, H, SDL_LOGICAL_PRESENTATION_LETTERBOX);
}

// ---- a program of the game folder run (Windows): wait - List Update - or not
bool run(const char *rel, bool wait) {
#ifdef _WIN32
	std::string p = resolve(rel);
	if (p.empty()) return false;
	const char *argv[] = { p.c_str(), nullptr };
	SDL_Process *pr = SDL_CreateProcess(argv, false);
	if (!pr) return false;
	if (wait) SDL_WaitProcess(pr, true, nullptr);
	SDL_DestroyProcess(pr);
	return true;
#else
	(void)rel; (void)wait;
	return false;
#endif
}

// ---- the actions (0x404700)
struct Server { std::string name, tcp, ladder; int tcpport = 0, ladderport = 0; };
std::vector<Server> server_list() {   // Launcher\ServerList.dat (0x4060e0): the count, then five lines a server
	std::vector<uint8_t> b = read_file(resolve("Launcher\\ServerList.dat"));
	std::vector<std::string> lines;
	std::string cur;
	for (uint8_t c : b) {
		if (c == '\n') { lines.push_back(cur); cur.clear(); }
		else if (c != '\r' && c) cur += (char)c;
	}
	if (!cur.empty()) lines.push_back(cur);
	std::vector<Server> list;
	if (lines.empty()) return list;
	int count = SDL_atoi(lines[0].c_str());
	size_t at = 1;
	for (int n = 0; n < count && at < lines.size(); n++) {
		Server s;
		for (int k = 0; k < 5 && at < lines.size(); k++) {
			std::string line = lines[at++];
			size_t a = line.find_first_not_of(" \t");
			line = a == std::string::npos ? "" : line.substr(a);
			size_t sp = line.find(' ');
			std::string key = line.substr(0, sp), value = sp == std::string::npos ? "" : line.substr(sp + 1);
			size_t e = value.find_last_not_of(" \t");
			value = e == std::string::npos ? "" : value.substr(0, e + 1);
			if (key == "#DNS") s.name = value;
			else if (key == "#TCPIP") s.tcp = value;
			else if (key == "#TCPPORT") s.tcpport = SDL_atoi(value.c_str());
			else if (key == "#LADDERIP") s.ladder = value;
			else if (key == "#LADDERPORT") s.ladderport = SDL_atoi(value.c_str());
		}
		list.push_back(s);
	}
	return list;
}
// Change Server (dialog 387): the chosen server into SelectServer (0x405f70); true when one was chosen
bool change_server() {
	std::vector<Server> list = server_list();
	if (list.empty()) alert(T_NOLIST, "Alert");
	int picked = -1;
#ifdef _WIN32
	std::vector<std::string> names;
	for (const Server &s : list) names.push_back(s.name);
	DlgState st = { 0, &names, !resolve("Launcher\\GetList.exe").empty(), -1 };
	int r = dialog(387, &st);
	if (r == 1094) {   // (List Update: GetList.exe, the launcher minimised while it runs)
		SDL_MinimizeWindow(g_win);
		run("Launcher\\GetList.exe", true);
		SDL_RestoreWindow(g_win);
		return false;
	}
	if (r == IDOK) picked = st.picked;
#else
	std::vector<std::pair<int, const char *>> b;
	for (size_t i = 0; i < list.size() && i < 8; i++) b.push_back({ (int)i, list[i].name.c_str() });
	b.push_back({ -1, "Cancel" });
	picked = choose("Select Server List", text(T_PICK), b);
#endif
	if (picked < 0 || picked >= (int)list.size()) return false;
	const Server &s = list[(size_t)picked];
	set_string(SERVER_KEY, "", "10", 10);
	set_string(SERVER_KEY, "TcpDNS", s.tcp, 0x32);
	set_string(SERVER_KEY, "LadderDNS", s.ladder, 0x32);
	set_int(SERVER_KEY, "TcpPort", s.tcpport);
	set_int(SERVER_KEY, "LadderPort", s.ladderport);
	return true;
}
// Play Game: a server chosen first, a render mode chosen, StartMode 1 - true: the game starts
bool play_game() {
	std::string chosen;
	if (!get_string(SERVER_KEY, "", &chosen) || chosen.empty())
		if (!change_server()) return false;
	int mode = 0;
	if (!get_int(LAUNCHER_KEY, "RenderMode", &mode) || (mode != 100 && mode != 200 && mode != 300)) {
		alert(T_RENDER, "Messsage");
		return false;
	}
	set_int(LAUNCHER_KEY, "StartMode", 1);
	return true;
}
void cinematics() {
	int end = 0;
	get_int(LAUNCHER_KEY, "EndMode", &end);
#ifdef _WIN32
	DlgState st = { end != 0, nullptr, false, -1 };
	int r = dialog(382, &st);
	if (r == 1078) movie("InitData\\interface.sra");
	else if (r == 1079) movie("InitData\\battle.sra");
#else
	std::vector<std::pair<int, const char *>> b = { { 1, "Opening Cinema" } };
	if (end) b.push_back({ 2, "Ending Cinema" });
	b.push_back({ 0, "Quit" });
	int r = choose("Cinematics Dialog", "", b);
	if (r == 1) movie("InitData\\interface.sra");
	else if (r == 2) movie("InitData\\battle.sra");
#endif
}
void help() {
	int r;
#ifdef _WIN32
	DlgState st = { 0, nullptr, false, -1 };
	r = dialog(385, &st);
	r = r == 1081 ? 1 : r == 1082 ? 2 : 0;
#else
	r = choose("Help Dialog", "", { { 1, "Read me" }, { 2, "www.AxisArena.net" }, { 0, "Cancel" } });
#endif
	if (r == 1) {
		std::string p = resolve(g_korean ? "Launcher\\ReadmeHan.txt" : "Launcher\\ReadmeEng.txt");
		bool ok = !p.empty();
#ifdef _WIN32
		if (ok) {
			for (char &c : p) if (c == '/') c = '\\';
			const char *argv[] = { "notepad.exe", p.c_str(), nullptr };
			SDL_Process *pr = SDL_CreateProcess(argv, false);
			ok = pr != nullptr;
			if (pr) SDL_DestroyProcess(pr);
		}
#else
		if (ok) ok = SDL_OpenURL(("file://" + p).c_str());
#endif
		if (!ok) alert(T_NOTEPAD, "Warning Message");
	} else if (r == 2 && !SDL_OpenURL("http://www.axisarena.net"))
		alert(T_BROWSER, "Warning Message");
}
void video_setup() {
	int r;
#ifdef _WIN32
	DlgState st = { 0, nullptr, false, -1 };
	r = dialog(383, &st) == 1085 ? 200 : 0;
#else
	r = choose("Video Setup Dialog", "", { { 200, "Select OpenGL Render" }, { 0, "Quit" } });
#endif
	if (r == 200) set_int(LAUNCHER_KEY, "RenderMode", 200);   // (0x4057c0)
}
// Install DirectX / Install Game: the program run, then the launcher closed; true: quit
bool install_directx() {
	int r = choose("Messsage", text(T_DIRECTX), { { 1, "Yes" }, { 0, "No" } });
	return r == 1 && run(g_korean ? "Launcher\\DirectX\\dx7akor.exe" : "Launcher\\DirectX\\dx7aEng.exe", false);
}
bool install_game() {
	if (run("Launcher\\AxisInstall\\Setup.exe", false)) return true;
	alert(T_INSTALL, "Alert");
	return false;
}

// the settings AxisPlay writes at its start when installed (0x4020e0, 0x402190, 0x4022b0)
void defaults() {
	if (reg_create(LAUNCHER_KEY) == 1) {
		set_int(LAUNCHER_KEY, "EndMode", 0);
		set_int(LAUNCHER_KEY, "RenderMode", 1);
		set_int(LAUNCHER_KEY, "StartMode", 0);
	}
	if (reg_create(SERVER_KEY) == 1) {
		set_string(SERVER_KEY, "TcpDNS", "10", 0x32);
		set_string(SERVER_KEY, "LadderDNS", "10", 0x32);
		set_int(SERVER_KEY, "TcpPort", 0);
		set_int(SERVER_KEY, "LadderPort", 0);
	}
	set_int(LAUNCHER_KEY, "StartMode", 0);
}

}   // namespace

bool launcher_run(const std::string &gameDir) {
	g_dir = gameDir;
	g_korean = korean();
	std::string exe = resolve("AxisPlay.exe");
	if (exe.empty() || !g_pe.open(exe)) {
		std::string msg = "AxisPlay.exe is needed in the game's folder (" + g_dir + "): the launcher's pictures are read from it.";
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Axis Launcher", msg.c_str(), nullptr);
		return false;
	}
#ifdef _WIN32
	g_res = LoadLibraryExA(exe.c_str(), nullptr, LOAD_LIBRARY_AS_DATAFILE | LOAD_LIBRARY_AS_IMAGE_RESOURCE);
#endif
	g_installed = !resolve("MathFunc.tbl").empty();
	if (g_installed) defaults();
	// the window: AxisPlay's popup (642 x 482 with a 1-pixel border, centred) at the screen's scale - on the main display
	// (AXISSDL_DISPLAY=<n>: the n-th display instead, as SDL lists them - a check on a machine with several)
	SDL_DisplayID display = SDL_GetPrimaryDisplay();
	{
		int n = 0;
		SDL_DisplayID *all = SDL_GetDisplays(&n);
		for (int i = 0; i < n; i++) {
			SDL_Rect b;
			SDL_GetDisplayBounds(all[i], &b);
			SDL_Log("launcher: display %d '%s' at %d,%d %dx%d%s", i, SDL_GetDisplayName(all[i]), b.x, b.y, b.w, b.h,
			        all[i] == display ? " (main)" : "");
		}
		const char *want = SDL_getenv("AXISSDL_DISPLAY");
		if (want && SDL_atoi(want) >= 0 && SDL_atoi(want) < n) display = all[SDL_atoi(want)];
		SDL_free(all);
	}
	float scale = SDL_GetDisplayContentScale(display);
	if (scale < 1) scale = 1;
	g_win = SDL_CreateWindow("Axis Launcher", (int)(W * scale + 0.5f), (int)(H * scale + 0.5f), SDL_WINDOW_BORDERLESS | SDL_WINDOW_HIGH_PIXEL_DENSITY);
	g_ren = g_win ? SDL_CreateRenderer(g_win, nullptr) : nullptr;
	if (!g_ren) return false;
	SDL_SetWindowPosition(g_win, SDL_WINDOWPOS_CENTERED_DISPLAY(display), SDL_WINDOWPOS_CENTERED_DISPLAY(display));
	SDL_SetRenderLogicalPresentation(g_ren, W, H, SDL_LOGICAL_PRESENTATION_LETTERBOX);
	int hx = 0, hy = 0;
	if (SDL_Surface *ic = group_picture(14, 377, nullptr, &hx, &hy)) { SDL_SetWindowIcon(g_win, ic); SDL_DestroySurface(ic); }   // IDI_LAUNCHER
	SDL_Cursor *cursor = nullptr;
	if (SDL_Surface *cs = group_picture(12, 0, "CURSOR2", &hx, &hy)) {
		cursor = SDL_CreateColorCursor(cs, hx, hy);
		SDL_DestroySurface(cs);
		if (cursor) SDL_SetCursor(cursor);
	}
	if (SDL_Surface *bk = bmp_surface(read_file(resolve("Launcher\\Resource\\BackGround\\MainBK.bmp")), false)) {
		g_back = SDL_CreateTextureFromSurface(g_ren, bk);
		SDL_DestroySurface(bk);
	}
	for (int i = 0; i < 8; i++)
		for (int k = 0; k < 4; k++)
			if (SDL_Surface *s = bmp_surface(g_pe.find(2, BITMAPS[i][k]), true)) {
				g_pics[i][k] = SDL_CreateTextureFromSurface(g_ren, s);
				SDL_DestroySurface(s);
			}
	sound_load(g_snd[0], "Launcher\\lsound\\mmove.wav");
	sound_load(g_snd[1], "Launcher\\lsound\\mclick.wav");
	bool play = false, running = true;
	// a button's action (0x404700)
	auto act = [&](int i) {
		switch (i) {
		case INSTALL: if (install_game()) running = false; break;
		case PLAY: if (play_game()) { play = true; running = false; } break;
		case CINEMATICS: cinematics(); break;
		case HELP: help(); break;
		case SERVER: change_server(); break;
		case DIRECTX: if (install_directx()) running = false; break;
		case VIDEO: video_setup(); break;
		case QUIT: running = false; break;
		}
	};
	// (a check: AXISSDL_LAUNCHER_TEST=install|play|cinematics|help|server|directx|video|quit - that button pressed once the
	// window is up, its dialog then answered by hand)
	static const char *const names[8] = { "install", "play", "cinematics", "help", "server", "directx", "video", "quit" };
	int test = -1;
	if (const char *tst = SDL_getenv("AXISSDL_LAUNCHER_TEST"))
		for (int i = 0; i < 8; i++) if (!SDL_strcasecmp(tst, names[i])) test = i;
	draw();
	while (running) {
		if (test >= 0) {
			SDL_Delay(500);
			SDL_Log("launcher test: the %s button", names[test]);
			const int i = test;
			test = -1;
			g_state[i] = PRESSED;
			draw();
			act(i);
			SDL_Log("launcher test: %s done (play %d, running %d)", names[i], play, running);
			g_state[i] = NORMAL;
			draw();
			continue;
		}
		SDL_Event e;
		if (!SDL_WaitEventTimeout(&e, 100)) continue;
		SDL_ConvertEventToRenderCoordinates(g_ren, &e);
		switch (e.type) {
		case SDL_EVENT_QUIT: running = false; break;
		case SDL_EVENT_MOUSE_MOTION:
			for (int i = 0; i < 8; i++) {
				if (!live(i)) continue;
				bool inside = hit(e.motion.x, e.motion.y) == i;
				if (inside && !g_lit[i]) { sound_play(0); g_state[i] = LIT; g_lit[i] = true; }
				else if (!inside && g_lit[i]) { g_state[i] = NORMAL; g_lit[i] = false; }
			}
			break;
		case SDL_EVENT_MOUSE_BUTTON_DOWN: case SDL_EVENT_MOUSE_BUTTON_UP: {
			if (e.button.button != SDL_BUTTON_LEFT) break;
			int i = hit(e.button.x, e.button.y);
			if (i < 0 || !live(i)) break;
			if (!e.button.down) { g_state[i] = NORMAL; break; }
			sound_play(1);
			g_state[i] = PRESSED;
			draw();
			act(i);
			break;
		}
		default: break;
		}
		draw();
	}
	for (Sound &s : g_snd) { if (s.stream) SDL_DestroyAudioStream(s.stream); SDL_free(s.buf); s = Sound(); }
	for (auto &row : g_pics) for (SDL_Texture *&t : row) { if (t) SDL_DestroyTexture(t); t = nullptr; }
	if (g_back) SDL_DestroyTexture(g_back);
	g_back = nullptr;
	SDL_DestroyRenderer(g_ren);
	SDL_DestroyWindow(g_win);
	if (cursor) { SDL_SetCursor(SDL_GetDefaultCursor()); SDL_DestroyCursor(cursor); }
#ifdef _WIN32
	if (g_res) FreeLibrary(g_res);
#endif
	return play;
}
