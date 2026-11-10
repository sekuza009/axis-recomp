// axis_replay.cpp: see axis_replay.h.
#include "axis_replay.h"

#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/rd_pipeline_color_blend_state.hpp>
#include <godot_cpp/classes/rd_pipeline_color_blend_state_attachment.hpp>
#include <godot_cpp/classes/rd_pipeline_depth_stencil_state.hpp>
#include <godot_cpp/classes/rd_pipeline_multisample_state.hpp>
#include <godot_cpp/classes/rd_pipeline_rasterization_state.hpp>
#include <godot_cpp/classes/rd_sampler_state.hpp>
#include <godot_cpp/classes/rd_shader_source.hpp>
#include <godot_cpp/classes/rd_shader_spirv.hpp>
#include <godot_cpp/classes/rd_texture_format.hpp>
#include <godot_cpp/classes/rd_texture_view.hpp>
#include <godot_cpp/classes/rd_uniform.hpp>
#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/render_data.hpp>
#include <godot_cpp/classes/render_scene_buffers_rd.hpp>

#include <cstring>
#include <cstdlib>

using namespace godot;

namespace {

// the fixed-function pipeline: texture x colour by the texture environment, then fog
const char *k_vertex = R"(#version 450
struct V { vec4 pos; vec4 col; vec4 uvf; };
layout(set = 0, binding = 0, std430) restrict readonly buffer Verts { V v[]; } verts;
layout(push_constant, std430) uniform PC { uint base; uint flags; uint env; uint pad; vec4 fog_color; } pc;
layout(location = 0) out vec4 v_col;
layout(location = 1) out vec2 v_uv;
layout(location = 2) out float v_fog;
void main() {
	V x = verts.v[pc.base + uint(gl_VertexIndex)];
	gl_Position = x.pos;
	gl_PointSize = 1.0;
	v_col = x.col;
	v_uv = x.uvf.xy;
	v_fog = x.uvf.z;
}
)";
const char *k_fragment = R"(#version 450
layout(push_constant, std430) uniform PC { uint base; uint flags; uint env; uint pad; vec4 fog_color; } pc;
layout(set = 1, binding = 0) uniform sampler2D tex;
layout(set = 2, binding = 0) uniform sampler2D godot_map;   // (the remaster: Godot's picture of the map, linear light)
layout(location = 0) in vec4 v_col;
layout(location = 1) in vec2 v_uv;
layout(location = 2) in float v_fog;
layout(location = 0) out vec4 frag;
// the tag view's colours (src/render/draw_tags.h): other, sky, ground, objects, actors, the actors' view pass, bullets,
// particles, items, markers, HUD
const vec3 k_tags[11] = vec3[](vec3(0.5), vec3(0.3, 0.5, 1.0), vec3(0.2, 0.9, 0.2), vec3(1.0, 0.9, 0.1), vec3(1.0, 0.2, 0.2),
	vec3(1.0, 0.4, 0.8), vec3(1.0, 0.6, 0.0), vec3(0.0, 1.0, 1.0), vec3(0.8, 0.3, 1.0), vec3(1.0), vec3(0.6, 0.6, 0.6));
void main() {
	if ((pc.flags & 8u) != 0u) {   // a map surface: Godot's colour where the game's map is seen (its own depth test, as before)
		frag = vec4(pow(clamp(texelFetch(godot_map, ivec2(gl_FragCoord.xy), 0).rgb, 0.0, 1.0), vec3(1.0 / 2.2)), 1.0);
		return;
	}
	vec4 c = v_col;
	if ((pc.flags & 1u) != 0u) {
		vec4 t = texture(tex, v_uv);
		if (pc.env == 0x1E01u) c = t;                                  // GL_REPLACE
		else if (pc.env == 0x2101u) c.rgb = mix(c.rgb, t.rgb, t.a);    // GL_DECAL
		else c *= t;                                                   // GL_MODULATE
	}
	if ((pc.flags & 2u) != 0u)
		c.rgb = mix(pc.fog_color.rgb, c.rgb, v_fog);
	if ((pc.flags & 4u) != 0u) {   // the tag view
		vec3 t = k_tags[min(pc.pad, 10u)];
		c.rgb = mix(vec3(dot(c.rgb, vec3(0.3, 0.59, 0.11))), t, 0.65);
	}
	frag = c;
}
)";

struct Push { uint32_t base, flags, env, pad; float fog[4]; };

// ---- the remaster's look (compute) ----
// bloom: mode 0 the bright pass (the world's copy -> the chain's first, half size), 1 down (a 13-tap filter of the
// level above), 2 up (the level below, a 9-tap tent, added to this one)
const char *k_bloom = R"(#version 450
layout(local_size_x = 8, local_size_y = 8) in;
layout(set = 0, binding = 0) uniform sampler2D src;
layout(set = 0, binding = 1, rgba16f) uniform image2D dst;
layout(push_constant, std430) uniform PC { vec4 a; vec4 b; vec4 c; ivec4 d; } pc;   // a: threshold, knee, -, radius
void main() {
	ivec2 p = ivec2(gl_GlobalInvocationID.xy);
	if (p.x >= pc.d.y || p.y >= pc.d.z) return;
	vec2 size = vec2(pc.d.yz);
	vec2 uv = (vec2(p) + 0.5) / size;
	vec2 t = 1.0 / vec2(textureSize(src, 0));
	if (pc.d.x == 2) {   // up
		vec2 r = t * pc.a.w;
		vec3 s = texture(src, uv).rgb * 4.0;
		s += (texture(src, uv + vec2(-r.x, 0)).rgb + texture(src, uv + vec2(r.x, 0)).rgb +
		      texture(src, uv + vec2(0, -r.y)).rgb + texture(src, uv + vec2(0, r.y)).rgb) * 2.0;
		s += texture(src, uv + vec2(-r.x, -r.y)).rgb + texture(src, uv + vec2(r.x, -r.y)).rgb +
		     texture(src, uv + vec2(-r.x, r.y)).rgb + texture(src, uv + vec2(r.x, r.y)).rgb;
		imageStore(dst, p, vec4(imageLoad(dst, p).rgb + s / 16.0, 1.0));
		return;
	}
	// down (the bright pass too): 13 taps (the "Call of Duty" filter: no flicker from single bright pixels)
	vec3 A = texture(src, uv + t * vec2(-2, -2)).rgb, B = texture(src, uv + t * vec2(0, -2)).rgb, C = texture(src, uv + t * vec2(2, -2)).rgb;
	vec3 D = texture(src, uv + t * vec2(-1, -1)).rgb, E = texture(src, uv + t * vec2(1, -1)).rgb;
	vec3 F = texture(src, uv + t * vec2(-2, 0)).rgb, G = texture(src, uv).rgb, H = texture(src, uv + t * vec2(2, 0)).rgb;
	vec3 I = texture(src, uv + t * vec2(-1, 1)).rgb, J = texture(src, uv + t * vec2(1, 1)).rgb;
	vec3 K = texture(src, uv + t * vec2(-2, 2)).rgb, L = texture(src, uv + t * vec2(0, 2)).rgb, M = texture(src, uv + t * vec2(2, 2)).rgb;
	vec3 s = (D + E + I + J) * 0.125 + (A + C + K + M) * 0.03125 + (B + F + H + L) * 0.0625 + G * 0.125;
	if (pc.d.x == 0) {   // the bright pass: a soft knee above the threshold
		float l = max(s.r, max(s.g, s.b));
		float sat = l > 0.0 ? 1.0 - min(s.r, min(s.g, s.b)) / l : 0.0;
		l *= 0.85 + 0.3 * sat;   // (a pale floor as bright as a lamp glows less: the game has no light levels above white)
		float knee = pc.a.y, th = pc.a.x;
		float soft = clamp(l - th + knee, 0.0, 2.0 * knee);
		soft = soft * soft / (4.0 * knee + 1e-4);
		s *= max(soft, l - th) / max(l, 1e-4);
	}
	imageStore(dst, p, vec4(s, 1.0));
}
)";
// the composite: the world (sharpened), its bloom added, graded, vignetted - written back into the frame
const char *k_composite = R"(#version 450
layout(local_size_x = 8, local_size_y = 8) in;
layout(set = 0, binding = 0) uniform sampler2D scene;
layout(set = 0, binding = 1) uniform sampler2D bloom;
layout(set = 0, binding = 2, rgba8) uniform restrict writeonly image2D frame;
layout(push_constant, std430) uniform PC { vec4 a; vec4 b; vec4 c; ivec4 d; } pc;
// a: -, -, bloom, -   b: exposure, contrast, saturation, warmth   c: vignette, sharpen
void main() {
	ivec2 p = ivec2(gl_GlobalInvocationID.xy);
	if (p.x >= pc.d.y || p.y >= pc.d.z) return;
	ivec2 hi = pc.d.yz - 1;
	vec3 c = texelFetch(scene, p, 0).rgb;
	if (pc.c.y > 0.0) {   // sharpen: the centre against its four neighbours, limited so edges do not ring
		vec3 n = texelFetch(scene, clamp(p + ivec2(0, -1), ivec2(0), hi), 0).rgb;
		vec3 s = texelFetch(scene, clamp(p + ivec2(0, 1), ivec2(0), hi), 0).rgb;
		vec3 w = texelFetch(scene, clamp(p + ivec2(-1, 0), ivec2(0), hi), 0).rgb;
		vec3 e = texelFetch(scene, clamp(p + ivec2(1, 0), ivec2(0), hi), 0).rgb;
		vec3 lo = min(c, min(min(n, s), min(w, e))), up = max(c, max(max(n, s), max(w, e)));
		c = clamp(c + (4.0 * c - n - s - w - e) * 0.25 * pc.c.y, lo, up);
	}
	vec2 uv = (vec2(p) + 0.5) / vec2(pc.d.yz);
	c += texture(bloom, uv).rgb * pc.a.z;
	c *= pc.b.x;                                                   // exposure
	c = (c - 0.5) * pc.b.y + 0.5;                                  // contrast
	float l = dot(c, vec3(0.2126, 0.7152, 0.0722));
	c = mix(vec3(l), c, pc.b.z);                                   // saturation
	c *= vec3(1.0 + 0.12 * pc.b.w, 1.0 + 0.02 * pc.b.w, 1.0 - 0.12 * pc.b.w);   // warmth
	if (pc.c.x > 0.0) {                                            // vignette (by the frame's aspect)
		vec2 q = (uv - 0.5) * vec2(float(pc.d.y) / float(pc.d.z), 1.0);
		c *= 1.0 - pc.c.x * smoothstep(0.35, 0.95, length(q));
	}
	// highlights rolled off above 0.9 instead of clipping (below it the colours are as graded)
	vec3 over = max(c - 0.9, 0.0);
	c = min(c, 0.9) + 0.1 * (1.0 - exp(-over / 0.1));
	imageStore(frame, p, vec4(clamp(c, 0.0, 1.0), 1.0));
}
)";
struct PostPush { float a[4], b[4], c[4]; int32_t d[4]; };

// how Godot draws a batch, or -1 for the game's own: 0 a solid surface, 1 a cutout (an alpha-blended solid mesh), then
// the effects (with effects only: picture mode 2, no sky in the frame) - 2 alpha-blended, 3 additive (source alpha), 4
// additive (one). Solid surfaces are the chosen kinds' meshes drawn in perspective; effects are those kinds' blended
// batches, also the see-through ones drawn already projected (depth-sorted triangles, billboards)
int godot_class(const EmuBatch &b, int kinds, bool effects) {
	if (b.pipe.prim != 0 || b.scissor[2] <= 0 || b.count < 3 || !(kinds & (1 << b.tag))) return -1;
	const bool mix = b.pipe.src == 0x302 && b.pipe.dst == 0x303;
	if (b.persp && (!b.pipe.blend || mix)) return b.pipe.blend ? 1 : 0;
	if (!effects || !b.pipe.blend) return -1;
	if (mix) return 2;
	if (b.pipe.dst == 1) return b.pipe.src == 0x302 ? 3 : b.pipe.src == 1 ? 4 : -1;
	return -1;
}

// the map's materials (Godot spatial shaders): the game's texture environment (0 modulate, 1 replace, 2 decal), its
// colours in the game's gamma (2.2) taken to Godot's linear light
const char *k_map_common = R"(
uniform sampler2D tex : filter_linear_mipmap, repeat_enable;
uniform bool textured = true;
uniform int env = 0;
uniform float original_light = 0.6;
vec4 game_colour(vec4 c, vec2 uv) {
	vec4 t = textured ? texture(tex, uv) : vec4(1.0);
	return env == 1 ? t : env == 2 ? vec4(mix(c.rgb, t.rgb, t.a), c.a) : c * t;
}
vec4 texture_only(vec2 uv) { return textured ? texture(tex, uv) : vec4(1.0); }
)";

RenderingDevice::BlendFactor blend_factor(uint32_t gl) {
	switch (gl) {
	case 0: return RenderingDevice::BLEND_FACTOR_ZERO;
	case 1: return RenderingDevice::BLEND_FACTOR_ONE;
	case 0x300: return RenderingDevice::BLEND_FACTOR_SRC_COLOR;
	case 0x301: return RenderingDevice::BLEND_FACTOR_ONE_MINUS_SRC_COLOR;
	case 0x302: return RenderingDevice::BLEND_FACTOR_SRC_ALPHA;
	case 0x303: return RenderingDevice::BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	case 0x304: return RenderingDevice::BLEND_FACTOR_DST_ALPHA;
	case 0x305: return RenderingDevice::BLEND_FACTOR_ONE_MINUS_DST_ALPHA;
	case 0x306: return RenderingDevice::BLEND_FACTOR_DST_COLOR;
	case 0x307: return RenderingDevice::BLEND_FACTOR_ONE_MINUS_DST_COLOR;
	case 0x308: return RenderingDevice::BLEND_FACTOR_SRC_ALPHA_SATURATE;
	}
	return RenderingDevice::BLEND_FACTOR_ONE;
}

PackedByteArray bytes(const void *p, size_t n) {
	PackedByteArray b;
	b.resize((int64_t)n);
	if (n) memcpy(b.ptrw(), p, n);
	return b;
}

} // namespace

void AxisReplay::_bind_methods() {
	ClassDB::bind_method(D_METHOD("open", "path"), &AxisReplay::open);
	ClassDB::bind_method(D_METHOD("get_frame_count"), &AxisReplay::get_frame_count);
	ClassDB::bind_method(D_METHOD("get_frame"), &AxisReplay::get_frame);
	ClassDB::bind_method(D_METHOD("get_frame_size"), &AxisReplay::get_frame_size);
	ClassDB::bind_method(D_METHOD("set_playing", "playing"), &AxisReplay::set_playing);
	ClassDB::bind_method(D_METHOD("is_playing"), &AxisReplay::is_playing);
	ClassDB::bind_method(D_METHOD("set_fps", "fps"), &AxisReplay::set_fps);
	ClassDB::bind_method(D_METHOD("get_fps"), &AxisReplay::get_fps);
	ClassDB::bind_method(D_METHOD("get_texture"), &AxisReplay::get_texture);
	ClassDB::bind_method(D_METHOD("step"), &AxisReplay::step);
	ClassDB::bind_method(D_METHOD("get_status"), &AxisReplay::get_status);
	ClassDB::bind_method(D_METHOD("_render"), &AxisReplay::_render);
	ClassDB::bind_method(D_METHOD("_set_texture_rid", "rid"), &AxisReplay::_set_texture_rid);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "playing"), "set_playing", "is_playing");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "fps"), "set_fps", "get_fps");
	// the remaster's look (the 3D world only; the HUD and menus stay the original's)
	ClassDB::bind_method(D_METHOD("set_look_enabled", "enabled"), &AxisReplay::set_look_enabled);
	ClassDB::bind_method(D_METHOD("get_look_enabled"), &AxisReplay::get_look_enabled);
	ClassDB::bind_method(D_METHOD("set_tag_view", "on"), &AxisReplay::set_tag_view);
	ClassDB::bind_method(D_METHOD("get_tag_view"), &AxisReplay::get_tag_view);
	ClassDB::bind_method(D_METHOD("set_overlay", "on"), &AxisReplay::set_overlay);
	ClassDB::bind_method(D_METHOD("get_overlay"), &AxisReplay::get_overlay);
	ClassDB::bind_method(D_METHOD("has_camera"), &AxisReplay::has_camera);
	ClassDB::bind_method(D_METHOD("get_camera_projection"), &AxisReplay::get_camera_projection);
	ClassDB::bind_method(D_METHOD("get_camera_view"), &AxisReplay::get_camera_view);
	ClassDB::bind_method(D_METHOD("get_tag_stats"), &AxisReplay::get_tag_stats);
	ClassDB::bind_method(D_METHOD("get_camera_viewport"), &AxisReplay::get_camera_viewport);
	ClassDB::bind_method(D_METHOD("get_lights"), &AxisReplay::get_lights);
	ClassDB::bind_method(D_METHOD("get_world_triangles", "mask"), &AxisReplay::get_world_triangles);
	ClassDB::bind_method(D_METHOD("get_world_samples", "mask", "count"), &AxisReplay::get_world_samples);
	ClassDB::bind_method(D_METHOD("set_picture_mode", "mode"), &AxisReplay::set_picture_mode);
	ClassDB::bind_method(D_METHOD("get_picture_mode"), &AxisReplay::get_picture_mode);
	ClassDB::bind_method(D_METHOD("set_map_viewport", "on"), &AxisReplay::set_map_viewport);
	ClassDB::bind_method(D_METHOD("get_map_viewport"), &AxisReplay::get_map_viewport);
	ClassDB::bind_method(D_METHOD("set_original_light", "amount"), &AxisReplay::set_original_light);
	ClassDB::bind_method(D_METHOD("get_original_light"), &AxisReplay::get_original_light);
	ClassDB::bind_method(D_METHOD("build_map_meshes"), &AxisReplay::build_map_meshes);
	ClassDB::bind_method(D_METHOD("set_godot_kinds", "mask"), &AxisReplay::set_godot_kinds);
	ClassDB::bind_method(D_METHOD("get_godot_kinds"), &AxisReplay::get_godot_kinds);
	ADD_GROUP("Remaster picture", "");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "picture_mode", PROPERTY_HINT_ENUM, "Original,Original lighting,Remaster"), "set_picture_mode", "get_picture_mode");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "original_light", PROPERTY_HINT_RANGE, "0,1.5,0.01"), "set_original_light", "get_original_light");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "godot_kinds", PROPERTY_HINT_FLAGS, "Other,Sky,Ground,Map objects,Actors,Actor view,Bullets,Particles,Items,Markers,HUD"), "set_godot_kinds", "get_godot_kinds");
	ADD_GROUP("Remaster view", "");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "tag_view"), "set_tag_view", "get_tag_view");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "overlay"), "set_overlay", "get_overlay");
	ADD_GROUP("Remaster look", "");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "look_enabled"), "set_look_enabled", "get_look_enabled");
#define AXIS_LOOK_BIND(name, range) \
	ClassDB::bind_method(D_METHOD("set_" #name, "value"), &AxisReplay::set_##name); \
	ClassDB::bind_method(D_METHOD("get_" #name), &AxisReplay::get_##name); \
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, #name, PROPERTY_HINT_RANGE, range), "set_" #name, "get_" #name);
	AXIS_LOOK_BIND(bloom, "0,3,0.01")
	AXIS_LOOK_BIND(bloom_threshold, "0,1,0.01")
	AXIS_LOOK_BIND(bloom_radius, "0.25,3,0.01")
	AXIS_LOOK_BIND(exposure, "0.25,3,0.01")
	AXIS_LOOK_BIND(contrast, "0.5,2,0.01")
	AXIS_LOOK_BIND(saturation, "0,2,0.01")
	AXIS_LOOK_BIND(warmth, "-1,1,0.01")
	AXIS_LOOK_BIND(vignette, "0,1,0.01")
	AXIS_LOOK_BIND(sharpen, "0,1,0.01")
#undef AXIS_LOOK_BIND
}

AxisReplay::AxisReplay() {
	texture.instantiate();
}

AxisReplay::~AxisReplay() {
	// (the GPU resources are the render thread's; they go with the rendering device at exit - free_all() is for a
	// later reopen)
}

bool AxisReplay::open(const String &p_path) {
	std::string err;
	const String global = ProjectSettings::get_singleton()->globalize_path(p_path);
	loaded = emu.load(global.utf8().get_data(), err);
	current = 0;
	sentVersions.clear();
	status = loaded ? String("opened ") + global + ": " + String::num_int64(emu.frame_count()) + " frames" : String("cannot open: ") + err.c_str();
	UtilityFunctions::print("AxisReplay: ", status);
	return loaded;
}

int AxisReplay::get_frame_count() const { return loaded ? emu.frame_count() : 0; }

Vector2i AxisReplay::get_frame_size() const {
	if (!loaded) return Vector2i();
	int w, h;
	emu.frame_size(current > 0 ? current - 1 : 0, w, h);
	return Vector2i(w, h);
}

String AxisReplay::get_status() const { return status; }

void AxisReplay::_process(double p_delta) {
	if (!playing || !loaded) return;
	accumulated += p_delta;
	const double each = fps > 0 ? 1.0 / fps : 0;
	if (accumulated >= each) {   // (one frame per process at most: the render thread takes one at a time)
		accumulated = each > 0 ? fmod(accumulated, each) : 0;
		if (!step()) playing = false;
	}
}

bool AxisReplay::step() {
	if (!loaded || current >= emu.frame_count()) return false;
	emu.run_frame(current);
	int w, h;
	emu.frame_size(current, w, h);
	submit(w, h);
	current++;
	return true;
}

void AxisReplay::submit(int w, int h) {
	Pending p;
	p.verts = emu.verts;
	p.cmds = emu.cmds;
	p.w = w;
	p.h = h;
	p.look = look;
	p.tagView = tagView;
	p.composite = pictureMode > 0 && mapViewport && emu.hasCamera;
	p.kinds = godotKinds;
	p.effects = frame_effects();
	for (const auto &kv : emu.textures) {   // (only the textures changed since last handed over)
		auto it = sentVersions.find(kv.first);
		if (it == sentVersions.end() || it->second != kv.second.version) {
			p.textures.push_back(kv);
			sentVersions[kv.first] = kv.second.version;
		}
	}
	p.ready = true;
	{
		std::lock_guard<std::mutex> lock(mutex);
		if (pending.ready)   // (an unrendered frame's texture changes are kept)
			for (auto &t : pending.textures) {
				bool newer = false;
				for (auto &u : p.textures) newer |= u.first == t.first;
				if (!newer) p.textures.push_back(std::move(t));
			}
		pending = std::move(p);
	}
	RenderingServer::get_singleton()->call_on_render_thread(callable_mp(this, &AxisReplay::_render));
}

void AxisReplay::_set_texture_rid(const RID &p_rid) {
	texture->set_texture_rd_rid(p_rid);
}

// the frame texture made on the render thread attached to the shown texture - from the main thread, as soon as it
// can: within a game step too (AxisGame shows a step's frames before it returns; a deferred call would wait for it)
void AxisReplay::apply_texture() {
	RID r;
	{
		std::lock_guard<std::mutex> lock(mutex);
		if (!newColorSet) return;
		r = newColor;
		newColorSet = false;
	}
	texture->set_texture_rd_rid(r);
}

// ---- the render thread ----

bool AxisReplay::ensure_shader() {
	if (shader.is_valid()) return true;
	Ref<RDShaderSource> src;
	src.instantiate();
	src->set_language(RenderingDevice::SHADER_LANGUAGE_GLSL);
	src->set_stage_source(RenderingDevice::SHADER_STAGE_VERTEX, k_vertex);
	src->set_stage_source(RenderingDevice::SHADER_STAGE_FRAGMENT, k_fragment);
	Ref<RDShaderSPIRV> spirv = rd->shader_compile_spirv_from_source(src);
	const String ev = spirv->get_stage_compile_error(RenderingDevice::SHADER_STAGE_VERTEX), ef = spirv->get_stage_compile_error(RenderingDevice::SHADER_STAGE_FRAGMENT);
	if (!ev.is_empty() || !ef.is_empty()) {
		UtilityFunctions::printerr("AxisReplay shader: ", ev, ef);
		return false;
	}
	shader = rd->shader_create_from_spirv(spirv, "AxisReplay");
	// the white texture for untextured batches (the set must still be bound)
	Ref<RDTextureFormat> f;
	f.instantiate();
	f->set_format(RenderingDevice::DATA_FORMAT_R8G8B8A8_UNORM);
	f->set_width(1);
	f->set_height(1);
	f->set_usage_bits(RenderingDevice::TEXTURE_USAGE_SAMPLING_BIT | RenderingDevice::TEXTURE_USAGE_CAN_UPDATE_BIT);
	Ref<RDTextureView> v;
	v.instantiate();
	const uint8_t px[4] = { 255, 255, 255, 255 };
	TypedArray<PackedByteArray> data;
	data.push_back(bytes(px, 4));
	white = rd->texture_create(f, v, data);
	whiteSampler = sampler_for(0x2601, 0x2601, 0x2901, 0x2901);
	Ref<RDUniform> u;
	u.instantiate();
	u->set_uniform_type(RenderingDevice::UNIFORM_TYPE_SAMPLER_WITH_TEXTURE);
	u->set_binding(0);
	u->add_id(whiteSampler);
	u->add_id(white);
	TypedArray<RDUniform> us;
	us.push_back(u);
	whiteSet = rd->uniform_set_create(us, shader, 1);
	whiteSet2 = rd->uniform_set_create(us, shader, 2);   // (the third set when there is no Godot map)
	return shader.is_valid();
}

void AxisReplay::ensure_framebuffer(int w, int h) {
	if (framebuffer.is_valid() && w == fbW && h == fbH) return;
	if (framebuffer.is_valid()) { rd->free_rid(framebuffer); rd->free_rid(color); rd->free_rid(depthTex); }
	Ref<RDTextureFormat> f;
	f.instantiate();
	f->set_format(RenderingDevice::DATA_FORMAT_R8G8B8A8_UNORM);
	f->set_width(w);
	f->set_height(h);
	f->set_usage_bits(RenderingDevice::TEXTURE_USAGE_COLOR_ATTACHMENT_BIT | RenderingDevice::TEXTURE_USAGE_SAMPLING_BIT | RenderingDevice::TEXTURE_USAGE_CAN_COPY_FROM_BIT |
	                  RenderingDevice::TEXTURE_USAGE_STORAGE_BIT);   // (the look's composite writes it)
	Ref<RDTextureView> v;
	v.instantiate();
	color = rd->texture_create(f, v);
	Ref<RDTextureFormat> d;
	d.instantiate();
	d->set_format(RenderingDevice::DATA_FORMAT_D32_SFLOAT);
	d->set_width(w);
	d->set_height(h);
	d->set_usage_bits(RenderingDevice::TEXTURE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT);
	depthTex = rd->texture_create(d, v);
	TypedArray<RID> atts;
	atts.push_back(color);
	atts.push_back(depthTex);
	framebuffer = rd->framebuffer_create(atts);
	fbFormat = rd->framebuffer_get_format(framebuffer);
	{	// (cleared once, opaque black: alpha stays 1 from here on)
		PackedColorArray black;
		black.push_back(Color(0, 0, 0, 1));
		rd->draw_list_begin(framebuffer, RenderingDevice::DRAW_CLEAR_COLOR_0 | RenderingDevice::DRAW_CLEAR_DEPTH, black, 1.0);
		rd->draw_list_end();
	}
	fbW = w;
	fbH = h;
	for (auto &kv : pipelines) rd->free_rid(kv.second);
	pipelines.clear();
	{	// (the new frame texture attached by the main thread: apply_texture, or the deferred call when idle)
		std::lock_guard<std::mutex> lock(mutex);
		newColor = color;
		newColorSet = true;
	}
	callable_mp(this, &AxisReplay::apply_texture).call_deferred();
}

RID AxisReplay::sampler_for(int minF, int magF, int wrapS, int wrapT) {
	const uint64_t key = (uint64_t)(minF & 0xffff) | (uint64_t)(magF & 0xffff) << 16 | (uint64_t)(wrapS & 0xffff) << 32 | (uint64_t)(wrapT & 0xffff) << 48;
	auto it = samplers.find(key);
	if (it != samplers.end()) return it->second;
	Ref<RDSamplerState> s;
	s.instantiate();
	const bool minLinear = minF == 0x2601 || minF == 0x2701 || minF == 0x2703, mipLinear = minF == 0x2702 || minF == 0x2703;
	const bool mip = minF >= 0x2700 && minF <= 0x2703;
	s->set_min_filter(minLinear ? RenderingDevice::SAMPLER_FILTER_LINEAR : RenderingDevice::SAMPLER_FILTER_NEAREST);
	s->set_mag_filter(magF == 0x2601 ? RenderingDevice::SAMPLER_FILTER_LINEAR : RenderingDevice::SAMPLER_FILTER_NEAREST);
	s->set_mip_filter(mipLinear ? RenderingDevice::SAMPLER_FILTER_LINEAR : RenderingDevice::SAMPLER_FILTER_NEAREST);
	if (!mip) s->set_max_lod(0);   // (no mipmapping: the base level only, as GL)
	s->set_repeat_u(wrapS == 0x2901 ? RenderingDevice::SAMPLER_REPEAT_MODE_REPEAT : RenderingDevice::SAMPLER_REPEAT_MODE_CLAMP_TO_EDGE);
	s->set_repeat_v(wrapT == 0x2901 ? RenderingDevice::SAMPLER_REPEAT_MODE_REPEAT : RenderingDevice::SAMPLER_REPEAT_MODE_CLAMP_TO_EDGE);
	RID r = rd->sampler_create(s);
	samplers[key] = r;
	return r;
}

void AxisReplay::upload_texture(uint32_t key, const EmuTexture &t) {
	GTex &g = gtex[key];
	if (g.tex.is_valid()) { rd->free_rid(g.tex); g.tex = RID(); g.sets.clear(); }   // (its uniform sets go with it)
	g.version = t.version;
	{
		std::lock_guard<std::mutex> lock(texMutex);
		texRids.erase(key);
	}
	if (!t.complete()) return;
	const int levels = t.mipped ? (int)t.levels.size() : 1;
	Ref<RDTextureFormat> f;
	f.instantiate();
	f->set_format(RenderingDevice::DATA_FORMAT_R8G8B8A8_UNORM);
	f->set_width(t.sizes[0].first);
	f->set_height(t.sizes[0].second);
	f->set_mipmaps(levels);
	f->set_usage_bits(RenderingDevice::TEXTURE_USAGE_SAMPLING_BIT | RenderingDevice::TEXTURE_USAGE_CAN_UPDATE_BIT);
	std::vector<uint8_t> all;
	for (int i = 0; i < levels; i++) all.insert(all.end(), t.levels[i].begin(), t.levels[i].end());
	TypedArray<PackedByteArray> data;
	data.push_back(bytes(all.data(), all.size()));
	Ref<RDTextureView> v;
	v.instantiate();
	g.tex = rd->texture_create(f, v, data);
	std::lock_guard<std::mutex> lock(texMutex);
	texRids[key] = g.tex;
}

// the texture's uniform set for a batch's sampling (made once per filter / wrap combination)
RID AxisReplay::set_for(GTex &g, const EmuBatch &b) {
	const uint64_t key = (uint64_t)(b.minFilter & 0xffff) | (uint64_t)(b.magFilter & 0xffff) << 16 | (uint64_t)(b.wrapS & 0xffff) << 32 | (uint64_t)(b.wrapT & 0xffff) << 48;
	auto it = g.sets.find(key);
	if (it != g.sets.end()) return it->second;
	Ref<RDUniform> u;
	u.instantiate();
	u->set_uniform_type(RenderingDevice::UNIFORM_TYPE_SAMPLER_WITH_TEXTURE);
	u->set_binding(0);
	u->add_id(sampler_for(b.minFilter, b.magFilter, b.wrapS, b.wrapT));
	u->add_id(g.tex);
	TypedArray<RDUniform> us;
	us.push_back(u);
	RID set = rd->uniform_set_create(us, shader, 1);
	g.sets[key] = set;
	return set;
}

RID AxisReplay::pipeline_for(const EmuPipe &p) {
	const uint64_t key = p.hash();
	auto it = pipelines.find(key);
	if (it != pipelines.end()) return it->second;
	Ref<RDPipelineRasterizationState> ras;
	ras.instantiate();
	// (gl_emu keeps the image the way up GL draws it, and Vulkan's winding is taken as seen on screen: GL's
	// counter-clockwise front faces stay counter-clockwise)
	ras->set_front_face(p.frontFace == 0x901 ? RenderingDevice::POLYGON_FRONT_FACE_COUNTER_CLOCKWISE : RenderingDevice::POLYGON_FRONT_FACE_CLOCKWISE);
	ras->set_cull_mode(!p.cull ? RenderingDevice::POLYGON_CULL_DISABLED : p.cullFace == 0x404 ? RenderingDevice::POLYGON_CULL_FRONT : p.cullFace == 0x405 ? RenderingDevice::POLYGON_CULL_BACK : RenderingDevice::POLYGON_CULL_DISABLED);
	if (p.offset) {
		ras->set_depth_bias_enabled(true);
		ras->set_depth_bias_constant_factor(p.offsetUnits);
		ras->set_depth_bias_slope_factor(p.offsetFactor);
	}
	Ref<RDPipelineMultisampleState> ms;
	ms.instantiate();
	Ref<RDPipelineDepthStencilState> ds;
	ds.instantiate();
	ds->set_enable_depth_test(p.depthTest);
	ds->set_enable_depth_write(p.depthTest);
	ds->set_depth_compare_operator((RenderingDevice::CompareOperator)((p.depthFunc - 0x200) & 7));
	Ref<RDPipelineColorBlendStateAttachment> a;
	a.instantiate();
	a->set_enable_blend(p.blend);
	a->set_src_color_blend_factor(blend_factor(p.src));
	a->set_dst_color_blend_factor(blend_factor(p.dst));
	a->set_src_alpha_blend_factor(blend_factor(p.src));
	a->set_dst_alpha_blend_factor(blend_factor(p.dst));
	// (alpha left at 1: the game's window ignores it - drawn as it is, a frame with the game's blended alphas came out
	// darker over Godot's background, its glows and particles near black)
	a->set_write_a(false);
	Ref<RDPipelineColorBlendState> bs;
	bs.instantiate();
	TypedArray<RDPipelineColorBlendStateAttachment> as;
	as.push_back(a);
	bs->set_attachments(as);
	const RenderingDevice::RenderPrimitive prim = p.prim == 0 ? RenderingDevice::RENDER_PRIMITIVE_TRIANGLES : p.prim == 1 ? RenderingDevice::RENDER_PRIMITIVE_LINES : RenderingDevice::RENDER_PRIMITIVE_POINTS;
	RID r = rd->render_pipeline_create(shader, fbFormat, RenderingDevice::INVALID_FORMAT_ID, prim, ras, ms, ds, bs);
	pipelines[key] = r;
	return r;
}

void AxisReplay::_render() {
	Pending p;
	{
		std::lock_guard<std::mutex> lock(mutex);
		if (!pending.ready) return;
		p = std::move(pending);
		pending = Pending();
	}
	rd = RenderingServer::get_singleton()->get_rendering_device();
	if (!rd || !ensure_shader() || p.w <= 0 || p.h <= 0) return;
	ensure_framebuffer(p.w, p.h);
	for (const auto &t : p.textures) upload_texture(t.first, t.second);
	// the vertices
	const uint32_t need = (uint32_t)(p.verts.size() * sizeof(EmuVertex));
	if (need > vbufBytes || !vbuf.is_valid()) {
		if (vbuf.is_valid()) rd->free_rid(vbuf);
		vbufBytes = need * 2 > (1u << 20) ? need * 2 : (1u << 20);
		vbuf = rd->storage_buffer_create(vbufBytes);
		Ref<RDUniform> u;
		u.instantiate();
		u->set_uniform_type(RenderingDevice::UNIFORM_TYPE_STORAGE_BUFFER);
		u->set_binding(0);
		u->add_id(vbuf);
		TypedArray<RDUniform> us;
		us.push_back(u);
		set0 = rd->uniform_set_create(us, shader, 0);
	}
	if (need) rd->buffer_update(vbuf, 0, need, bytes(p.verts.data(), need));
	haveDeferred = false;   // (a frame left for Godot's map that never came: dropped - its vertices are gone now)
	if (p.composite) {      // drawn during the map viewport's render (draw_deferred), into Godot's map
		deferred = std::move(p);
		haveDeferred = true;
		return;
	}
	draw_cmds(p, RID(), RID());
}

RID AxisReplay::godot_map_set(const RID &p_color) {
	auto it = godotSets.find(p_color.get_id());
	if (it != godotSets.end() && rd->uniform_set_is_valid(it->second)) return it->second;
	Ref<RDUniform> u;
	u.instantiate();
	u->set_uniform_type(RenderingDevice::UNIFORM_TYPE_SAMPLER_WITH_TEXTURE);
	u->set_binding(0);
	u->add_id(whiteSampler);
	u->add_id(p_color);
	TypedArray<RDUniform> us;
	us.push_back(u);
	const RID s = rd->uniform_set_create(us, shader, 2);
	godotSets[p_color.get_id()] = s;
	return s;
}

void AxisReplay::draw_deferred(const RID &p_color, const RID &p_depth, const Vector2i &p_size) {
	if (!haveDeferred || !rd) return;
	haveDeferred = false;
	const bool fits = p_size.x == fbW && p_size.y == fbH;   // (Godot's buffers the frame's size: else drawn as the original)
	draw_cmds(deferred, fits ? p_color : RID(), fits ? p_depth : RID());
}

void AxisReplay::draw_cmds(const Pending &p, const RID &gColor, const RID &gDepth) {
	// with Godot's map: the game's solid map surfaces drawn as they are (their depth, their depth test) but coloured from
	// Godot's picture of the map at each pixel - Godot's map seen exactly where the game's would be
	const bool comp = gColor.is_valid();
	(void)gDepth;   // (Godot's depth is not needed: the game's own map surfaces give it)
	const RID mapSet = comp ? godot_map_set(gColor) : whiteSet2;
	// the look: after the frame's last 3D batch (the world done, the HUD and menus still to come) the effects run on
	// what is drawn so far; a frame without 3D (the menus) is left as it is
	size_t split = (size_t)-1;
	if (p.look.enabled)
		for (size_t i = p.cmds.size(); i-- > 0;)
			if (p.cmds[i].kind == EmuCmd::BATCH && p.cmds[i].batch.persp && p.cmds[i].batch.count) { split = i + 1; break; }
	// the commands, in order: a clear starts a draw list that clears, batches draw into the current one
	int64_t dl = -1;
	for (size_t ci = 0; ci < p.cmds.size(); ci++) {
		if (ci == split) {
			if (dl >= 0) { rd->draw_list_end(); dl = -1; }
			run_post(p.look);
		}
		const EmuCmd &c = p.cmds[ci];
		// the map's solid surfaces (the view volume's meshes, drawn in perspective): Godot's colour now, the game's depth.
		// Its see-through parts (queued as triangles, depth-sorted and drawn already projected: glows, beams) stay the
		// game's own - over the sky they need what is behind them
		const bool fromGodot = comp && c.kind == EmuCmd::BATCH && godot_class(c.batch, p.kinds, p.effects) >= 0;
		if (c.kind == EmuCmd::CLEAR) {
			if (dl >= 0) rd->draw_list_end();
			BitField<RenderingDevice::DrawFlags> flags = 0;
			if (c.clearMask & 0x4000) flags.set_flag(RenderingDevice::DRAW_CLEAR_COLOR_0);
			if (c.clearMask & 0x100) flags.set_flag(RenderingDevice::DRAW_CLEAR_DEPTH);
			PackedColorArray colors;
			colors.push_back(Color(c.clearColor[0], c.clearColor[1], c.clearColor[2], 1.0));   // (opaque: see pipeline_for)
			dl = rd->draw_list_begin(framebuffer, flags, colors, c.clearDepth);
			continue;
		}
		const EmuBatch &b = c.batch;
		if (b.count == 0 || b.scissor[2] <= 0 || b.scissor[3] <= 0) continue;
		if (dl < 0) dl = rd->draw_list_begin(framebuffer);
		if (fromGodot) {   // (unblended: Godot's colour replaces - its picture has the blending done already)
			EmuPipe gp = b.pipe;
			gp.blend = 0;
			rd->draw_list_bind_render_pipeline(dl, pipeline_for(gp));
		} else
			rd->draw_list_bind_render_pipeline(dl, pipeline_for(b.pipe));
		rd->draw_list_bind_uniform_set(dl, mapSet, 2);
		rd->draw_list_bind_uniform_set(dl, set0, 0);
		RID set = whiteSet;
		bool textured = false;
		if (b.texture) {
			auto it = gtex.find(b.texture - 1);
			if (it != gtex.end() && it->second.tex.is_valid()) { set = set_for(it->second, b); textured = true; }
		}
		rd->draw_list_bind_uniform_set(dl, set, 1);
		rd->draw_list_enable_scissor(dl, Rect2(b.scissor[0], b.scissor[1], b.scissor[2], b.scissor[3]));
		Push push = { b.first, (textured ? 1u : 0u) | (b.fog ? 2u : 0u) | (p.tagView ? 4u : 0u) | (fromGodot ? 8u : 0u), b.env, b.tag,
		              { b.fogColor[0], b.fogColor[1], b.fogColor[2], b.fogColor[3] } };
		rd->draw_list_set_push_constant(dl, bytes(&push, sizeof push), sizeof push);
		rd->draw_list_draw(dl, false, 1, b.count);
	}
	if (dl >= 0) rd->draw_list_end();
	if (split == p.cmds.size()) run_post(p.look);   // (nothing after the world)
}


// the look's resources for a w x h frame: the shaders, the world's copy, the bloom chain and their uniform sets
bool AxisReplay::ensure_post(int w, int h) {
	if (!postBloomShader.is_valid()) {
		for (int k = 0; k < 2; k++) {
			Ref<RDShaderSource> src;
			src.instantiate();
			src->set_language(RenderingDevice::SHADER_LANGUAGE_GLSL);
			src->set_stage_source(RenderingDevice::SHADER_STAGE_COMPUTE, k ? k_composite : k_bloom);
			Ref<RDShaderSPIRV> spirv = rd->shader_compile_spirv_from_source(src);
			const String e = spirv->get_stage_compile_error(RenderingDevice::SHADER_STAGE_COMPUTE);
			if (!e.is_empty()) { UtilityFunctions::printerr("AxisReplay look shader: ", e); return false; }
			RID s = rd->shader_create_from_spirv(spirv, k ? "AxisLookComposite" : "AxisLookBloom");
			(k ? postCompShader : postBloomShader) = s;
			(k ? postCompPipe : postBloomPipe) = rd->compute_pipeline_create(s);
		}
		Ref<RDSamplerState> s;
		s.instantiate();
		s->set_min_filter(RenderingDevice::SAMPLER_FILTER_LINEAR);
		s->set_mag_filter(RenderingDevice::SAMPLER_FILTER_LINEAR);
		s->set_repeat_u(RenderingDevice::SAMPLER_REPEAT_MODE_CLAMP_TO_EDGE);
		s->set_repeat_v(RenderingDevice::SAMPLER_REPEAT_MODE_CLAMP_TO_EDGE);
		postSampler = rd->sampler_create(s);
	}
	if (postScene.is_valid() && w == postW && h == postH) return true;
	for (RID r : postSets) if (rd->uniform_set_is_valid(r)) rd->free_rid(r);
	for (RID r : postBloom) rd->free_rid(r);
	if (postScene.is_valid()) rd->free_rid(postScene);
	postSets.clear(); postBloom.clear(); postSizes.clear();
	Ref<RDTextureView> v;
	v.instantiate();
	Ref<RDTextureFormat> f;
	f.instantiate();
	f->set_format(RenderingDevice::DATA_FORMAT_R8G8B8A8_UNORM);
	f->set_width(w);
	f->set_height(h);
	f->set_usage_bits(RenderingDevice::TEXTURE_USAGE_SAMPLING_BIT | RenderingDevice::TEXTURE_USAGE_CAN_COPY_TO_BIT);
	postScene = rd->texture_create(f, v);
	for (int bw = w / 2, bh = h / 2; postBloom.size() < 6 && bw >= 4 && bh >= 4; bw /= 2, bh /= 2) {
		Ref<RDTextureFormat> b;
		b.instantiate();
		b->set_format(RenderingDevice::DATA_FORMAT_R16G16B16A16_SFLOAT);
		b->set_width(bw);
		b->set_height(bh);
		b->set_usage_bits(RenderingDevice::TEXTURE_USAGE_SAMPLING_BIT | RenderingDevice::TEXTURE_USAGE_STORAGE_BIT);
		postBloom.push_back(rd->texture_create(b, v));
		postSizes.push_back({ bw, bh });
	}
	auto sampled = [&](int binding, RID tex) {
		Ref<RDUniform> u;
		u.instantiate();
		u->set_uniform_type(RenderingDevice::UNIFORM_TYPE_SAMPLER_WITH_TEXTURE);
		u->set_binding(binding);
		u->add_id(postSampler);
		u->add_id(tex);
		return u;
	};
	auto image = [&](int binding, RID tex) {
		Ref<RDUniform> u;
		u.instantiate();
		u->set_uniform_type(RenderingDevice::UNIFORM_TYPE_IMAGE);
		u->set_binding(binding);
		u->add_id(tex);
		return u;
	};
	// the bloom sets: [0] the world -> chain 0; [i] chain i-1 -> chain i (down); then [n + i] chain i+1 -> chain i (up)
	const size_t n = postBloom.size();
	for (size_t i = 0; i < n; i++) {
		TypedArray<RDUniform> us;
		us.push_back(sampled(0, i ? postBloom[i - 1] : postScene));
		us.push_back(image(1, postBloom[i]));
		postSets.push_back(rd->uniform_set_create(us, postBloomShader, 0));
	}
	for (size_t i = 0; i + 1 < n; i++) {
		TypedArray<RDUniform> us;
		us.push_back(sampled(0, postBloom[i + 1]));
		us.push_back(image(1, postBloom[i]));
		postSets.push_back(rd->uniform_set_create(us, postBloomShader, 0));
	}
	{
		TypedArray<RDUniform> us;
		us.push_back(sampled(0, postScene));
		us.push_back(sampled(1, n ? postBloom[0] : postScene));
		us.push_back(image(2, color));
		postSets.push_back(rd->uniform_set_create(us, postCompShader, 0));
	}
	postW = w;
	postH = h;
	return true;
}

void AxisReplay::run_post(const Look &l) {
	if (!ensure_post(fbW, fbH)) return;
	rd->texture_copy(color, postScene, Vector3(), Vector3(), Vector3(fbW, fbH, 1), 0, 0, 0, 0);
	const size_t n = postBloom.size();
	const bool bloom = l.bloom > 0.0f && n > 0;
	const float strength = bloom ? l.bloom : 0.0f;   // (no chain: nothing added)
	auto pass = [&](RID pipe, RID set, int mode, int w, int h) {
		PostPush pp = { { l.bloomThreshold, 0.5f * l.bloomThreshold + 0.05f, strength, l.bloomRadius },
		                { l.exposure, l.contrast, l.saturation, l.warmth }, { l.vignette, l.sharpen, 0, 0 }, { mode, w, h, 0 } };
		const int64_t cl = rd->compute_list_begin();
		rd->compute_list_bind_compute_pipeline(cl, pipe);
		rd->compute_list_bind_uniform_set(cl, set, 0);
		rd->compute_list_set_push_constant(cl, bytes(&pp, sizeof pp), sizeof pp);
		rd->compute_list_dispatch(cl, (w + 7) / 8, (h + 7) / 8, 1);
		rd->compute_list_end();
	};
	if (bloom) {
		for (size_t i = 0; i < n; i++) pass(postBloomPipe, postSets[i], i ? 1 : 0, postSizes[i].first, postSizes[i].second);
		for (size_t i = n - 1; i-- > 0;) pass(postBloomPipe, postSets[n + i], 2, postSizes[i].first, postSizes[i].second);
	}
	pass(postCompPipe, postSets.back(), 0, fbW, fbH);
}

// ---- the remaster's view of the frame ----

namespace {
Projection gl_matrix(const float *m) {   // (GL's column-major floats: Godot's Projection is columns too)
	return Projection(Vector4(m[0], m[1], m[2], m[3]), Vector4(m[4], m[5], m[6], m[7]), Vector4(m[8], m[9], m[10], m[11]),
	                  Vector4(m[12], m[13], m[14], m[15]));
}
} // namespace

Projection AxisReplay::get_camera_projection() const {
	return emu.hasCamera ? gl_matrix(emu.camProjection) : Projection();
}

// the view matrix (the world into the camera's space, GL's: the camera looking down -z, y up - Godot's convention)
Transform3D AxisReplay::get_camera_view() const {
	if (!emu.hasCamera) return Transform3D();
	const float *m = emu.camView;
	return Transform3D(Basis(Vector3(m[0], m[1], m[2]), Vector3(m[4], m[5], m[6]), Vector3(m[8], m[9], m[10])), Vector3(m[12], m[13], m[14]));   // (Basis from columns)
}

Array AxisReplay::get_lights() const {
	Array out;
	for (const EmuLight &l : emu.lights) {
		Dictionary d;
		d["pool"] = l.pool;
		d["kind"] = l.kind;
		d["colour"] = Color((l.colour & 0xff) / 255.0f, ((l.colour >> 8) & 0xff) / 255.0f, ((l.colour >> 16) & 0xff) / 255.0f, ((l.colour >> 24) & 0xff) / 255.0f);
		d["position"] = Vector3(l.pos[0], l.pos[1], l.pos[2]);
		d["direction"] = Vector3(l.dir[0], l.dir[1], l.dir[2]);
		d["radius"] = l.radius;
		out.push_back(d);
	}
	return out;
}

Rect2i AxisReplay::get_camera_viewport() const {
	for (const EmuCmd &c : emu.cmds)
		if (c.kind == EmuCmd::BATCH && c.batch.persp && c.batch.scissor[2] > 0)
			return Rect2i(c.batch.scissor[0], c.batch.scissor[1], c.batch.scissor[2], c.batch.scissor[3]);
	return Rect2i(0, 0, emu.width(), emu.height());
}

PackedInt32Array AxisReplay::get_tag_stats() const {
	PackedInt32Array out;
	out.resize(16);
	for (const EmuCmd &c : emu.cmds)
		if (c.kind == EmuCmd::BATCH && c.batch.tag < 16)
			out.set(c.batch.tag, out[c.batch.tag] + (c.batch.pipe.prim == 0 ? (int32_t)c.batch.count / 3 : 0));
	return out;
}

// a 3D batch's vertex back into the world: the viewport unfolded from the clip coordinates gl_emu made, then the
// camera's projection x view inverted
namespace {
// a 4 x 4 column-major matrix inverted in doubles (the far plane is a million units out: floats lose the world)
bool invert(const double m[16], double o[16]) {
	double inv[16];
	inv[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
	inv[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
	inv[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
	inv[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];
	inv[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
	inv[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
	inv[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
	inv[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
	inv[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];
	inv[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];
	inv[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];
	inv[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];
	inv[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6];
	inv[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6];
	inv[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5];
	inv[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5];
	const double det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
	if (det == 0) return false;
	for (int i = 0; i < 16; i++) o[i] = inv[i] / det;
	return true;
}
struct Unproject {
	double inv[16];
	double W, H;
	bool ok = false;
	Vector3 world(const EmuVertex &v, const EmuBatch &b, Vector2 *screen) const {
		const double vx = b.scissor[0], vw = b.scissor[2], vh = b.scissor[3], vy = H - b.scissor[1] - vh;
		const double w = v.pos[3];
		const double cx = (v.pos[0] - w * ((2 * vx + vw) / W - 1)) * W / vw;
		const double cy = (-v.pos[1] - w * ((2 * vy + vh) / H - 1)) * H / vh;
		const double cz = 2.0 * v.pos[2] - w;
		const double c[4] = { cx, cy, cz, w };
		double r[4];
		for (int i = 0; i < 4; i++) r[i] = inv[i] * c[0] + inv[4 + i] * c[1] + inv[8 + i] * c[2] + inv[12 + i] * c[3];
		if (screen) *screen = Vector2((real_t)((v.pos[0] / w * 0.5 + 0.5) * W), (real_t)((v.pos[1] / w * 0.5 + 0.5) * H));
		if (r[3] != 0) for (int i = 0; i < 3; i++) r[i] /= r[3];
		return Vector3((real_t)r[0], (real_t)r[1], (real_t)r[2]);
	}
};
Unproject unprojector(const GLEmu &e) {
	Unproject u;
	if (!e.hasCamera) return u;
	double pv[16];
	for (int c = 0; c < 4; c++)
		for (int r = 0; r < 4; r++) {
			double s = 0;
			for (int k = 0; k < 4; k++) s += (double)e.camProjection[k * 4 + r] * (double)e.camView[c * 4 + k];
			pv[c * 4 + r] = s;
		}
	if (!invert(pv, u.inv)) return u;
	u.W = e.width();
	u.H = e.height();
	u.ok = true;
	return u;
}
} // namespace

PackedVector3Array AxisReplay::get_world_triangles(int mask) const {
	PackedVector3Array out;
	const Unproject u = unprojector(emu);
	if (!u.ok) return out;
	for (const EmuCmd &c : emu.cmds) {
		const EmuBatch &b = c.batch;
		if (c.kind != EmuCmd::BATCH || !b.persp || b.pipe.prim != 0 || !(mask & (1 << b.tag)) || b.scissor[2] <= 0) continue;
		for (uint32_t i = 0; i < b.count; i++) out.push_back(u.world(emu.verts[b.first + i], b, nullptr));
	}
	return out;
}

Array AxisReplay::get_world_samples(int mask, int count) const {
	PackedVector3Array world;
	PackedVector2Array screen;
	const Unproject u = unprojector(emu);
	size_t total = 0;
	if (u.ok)
		for (const EmuCmd &c : emu.cmds)
			if (c.kind == EmuCmd::BATCH && c.batch.persp && (mask & (1 << c.batch.tag)) && c.batch.scissor[2] > 0) total += c.batch.count;
	const size_t step = count > 0 && total > (size_t)count ? total / (size_t)count : 1;
	size_t k = 0;
	if (u.ok)
		for (const EmuCmd &c : emu.cmds) {
			const EmuBatch &b = c.batch;
			if (c.kind != EmuCmd::BATCH || !b.persp || !(mask & (1 << b.tag)) || b.scissor[2] <= 0) continue;
			for (uint32_t i = 0; i < b.count; i++, k++) {
				if (k % step) continue;
				const EmuVertex &v = emu.verts[b.first + i];
				if (v.pos[3] <= 0) continue;   // (behind the camera)
				Vector2 s;
				world.push_back(u.world(v, b, &s));
				screen.push_back(s);
			}
		}
	Array out;
	out.push_back(world);
	out.push_back(screen);
	return out;
}

// ---- the map as Godot's mesh (main thread) ----

void AxisReplay::set_original_light(float v) {
	originalLight = v;
	for (auto &kv : mapMaterials)
		if (kv.second.is_valid()) kv.second->set_shader_parameter("original_light", v);
}

bool AxisReplay::frame_effects() const {
	if (pictureMode != 2) return false;
	for (const EmuCmd &c : emu.cmds)
		if (c.kind == EmuCmd::BATCH && c.batch.tag == 1 && c.batch.count) return false;   // (the sky: Godot has none yet)
	return true;
}

Ref<ShaderMaterial> AxisReplay::map_material(uint32_t texture, uint32_t env, int blendClass, int cull, int priority) {
	const int lit = pictureMode == 2 && blendClass < 2 ? 1 : 0;   // (effects are unlit: they give light, not take it)
	const uint64_t key = (uint64_t)texture | (uint64_t)(env & 0xffff) << 32 | (uint64_t)blendClass << 48 | (uint64_t)lit << 51 |
	                     (uint64_t)cull << 52 | (uint64_t)(priority + 128) << 54;
	auto it = mapMaterials.find(key);
	if (it != mapMaterials.end()) return it->second;
	Ref<Shader> &sh = mapShaders[lit][blendClass][cull];
	if (sh.is_null()) {
		static const char *blend[5] = { "", "", ", blend_mix, depth_draw_never", ", blend_add, depth_draw_never", ", blend_add, depth_draw_never" };
		static const char *culls[4] = { "cull_disabled", "cull_back", "cull_front", "cull_disabled" };
		String code = String("shader_type spatial;\nrender_mode ") + culls[cull] + (lit ? "" : ", unshaded") + blend[blendClass] + ";\n" + k_map_common;
		if (blendClass >= 2)   // (an effect: the game's colour as it is, blended by Godot in the game's order)
			code += String("void fragment() {\n\tvec4 o = game_colour(COLOR, UV);\n\tALBEDO = pow(o.rgb, vec3(2.2));\n\tALPHA = ") +
			        (blendClass == 4 ? "1.0" : "o.a") + ";\n}\n";
		else if (!lit)
			code += String("void fragment() {\n\tvec4 o = game_colour(COLOR, UV);\n\tALBEDO = pow(o.rgb, vec3(2.2));\n") + (blendClass ? "\tALPHA = o.a;\n\tALPHA_SCISSOR_THRESHOLD = 0.5;\n" : "") + "}\n";
		else   // (lit by Godot: the texture as the surface, the game's own lighting kept as a glow of original_light)
			code += String("void fragment() {\n\tvec4 t = texture_only(UV);\n\tvec4 o = game_colour(COLOR, UV);\n\tALBEDO = pow(t.rgb, vec3(2.2));\n"
			               "\tEMISSION = pow(o.rgb, vec3(2.2)) * original_light;\n\tROUGHNESS = 0.8;\n") + (blendClass ? "\tALPHA = o.a;\n\tALPHA_SCISSOR_THRESHOLD = 0.5;\n" : "") + "}\n";
		sh.instantiate();
		sh->set_code(code);
	}
	Ref<ShaderMaterial> m;
	m.instantiate();
	m->set_shader(sh);
	m->set_shader_parameter("env", env == 0x1E01 ? 1 : env == 0x2101 ? 2 : 0);
	m->set_shader_parameter("textured", texture != 0);
	m->set_shader_parameter("original_light", originalLight);
	m->set_render_priority(priority);
	if (texture) {
		Ref<Texture2DRD> &t = texShown[texture - 1];
		if (t.is_null()) t.instantiate();
		m->set_shader_parameter("tex", t);
	}
	mapMaterials[key] = m;
	return m;
}

TypedArray<ArrayMesh> AxisReplay::build_map_meshes() {
	TypedArray<ArrayMesh> meshes;
	Ref<ArrayMesh> mesh;
	const Unproject u = unprojector(emu);
	if (!u.ok) return meshes;
	{	// the textures' RD textures as they are now (uploaded on the render thread)
		std::lock_guard<std::mutex> lock(texMutex);
		for (auto &kv : texShown) {
			auto it = texRids.find(kv.first);
			const RID r = it != texRids.end() ? it->second : RID();
			if (r.is_valid() && kv.second->get_texture_rd_rid() != r) kv.second->set_texture_rd_rid(r);
		}
	}
	// the batches of the kinds Godot draws (godotKinds: the ground, map objects, actors, items), by material
	struct Surface { PackedVector3Array v, n; PackedVector2Array uv; PackedColorArray col; uint32_t texture, env; int blend, cull, run; };
	const bool effects = frame_effects();
	int runs = 0;
	uint64_t lastEffect = ~0ull;
	std::unordered_map<uint64_t, Surface> surfaces;
	std::vector<uint64_t> order;
	for (const EmuCmd &c : emu.cmds) {
		const EmuBatch &b = c.batch;
		if (c.kind != EmuCmd::BATCH) continue;
		const int blendClass = godot_class(b, godotKinds, effects);
		if (blendClass < 0) continue;
		// the game's culling: GL's front faces (counter-clockwise unless glFrontFace(GL_CW)) turned to Godot's (clockwise),
		// its culled face kept (0 none, 1 back, 2 front)
		const int cull = !b.pipe.cull ? 0 : b.pipe.cullFace == 0x404 ? 2 : b.pipe.cullFace == 0x405 ? 1 : 3;
		const bool turn = b.pipe.frontFace == 0x901;
		uint64_t key = (uint64_t)b.texture | (uint64_t)(b.env & 0xffff) << 32 | (uint64_t)blendClass << 48 | (uint64_t)cull << 56;
		int run = 0;
		if (blendClass >= 2) {   // (effects: a surface per run of one material, in the game's order - it sorts them back to front)
			if (key != lastEffect) { runs++; lastEffect = key; }
			run = runs;
			key = (uint64_t)run << 40 ^ key ^ (1ull << 63);
		}
		auto it = surfaces.find(key);
		if (it == surfaces.end()) {
			it = surfaces.emplace(key, Surface()).first;
			it->second.texture = b.texture;
			it->second.env = b.env;
			it->second.blend = blendClass;
			it->second.cull = cull;
			it->second.run = run;
			order.push_back(key);
		}
		Surface &s = it->second;
		for (uint32_t i = 0; i + 2 < b.count; i += 3) {
			Vector3 w[3];
			const int idx[3] = { 0, turn ? 2 : 1, turn ? 1 : 2 };
			for (int k = 0; k < 3; k++) w[k] = u.world(emu.verts[b.first + i + idx[k]], b, nullptr);
			Vector3 n = (w[2] - w[0]).cross(w[1] - w[0]);   // (Godot's clockwise front: the normal towards the viewer)
			n = n.length_squared() > 0 ? n.normalized() : Vector3(0, 1, 0);
			for (int k = 0; k < 3; k++) {
				const EmuVertex &v = emu.verts[b.first + i + idx[k]];
				s.v.push_back(w[k]);
				s.n.push_back(n);
				s.uv.push_back(Vector2(v.uv[0], v.uv[1]));
				s.col.push_back(Color(v.col[0], v.col[1], v.col[2], v.col[3]));
			}
		}
	}
	if (getenv("AXIS_MAP_STATS")) {   // (a check: the map's batches and their depth state)
		String st;
		for (const EmuCmd &c : emu.cmds) {
			const EmuBatch &b = c.batch;
			if (c.kind != EmuCmd::BATCH || (b.tag != 2 && b.tag != 3)) continue;
			st += String(" [tex ") + String::num_int64(b.texture) + " n " + String::num_int64(b.count / 3) + " persp " + String::num_int64(b.persp) +
			      " depth " + String::num_int64(b.pipe.depthTest) + "/" + String::num_int64(b.pipe.depthFunc, 16) + " blend " +
			      String::num_int64(b.pipe.blend) + " " + String::num_int64(b.pipe.src, 16) + "/" + String::num_int64(b.pipe.dst, 16) +
			      " cull " + String::num_int64(b.pipe.cull) + " fog " + String::num_int64(b.fog) + "]";
		}
		UtilityFunctions::print("map batches:", st);
	}
	// smooth normals: each vertex's the sum of the faces that share its position and lie within 60 degrees of its own
	// face (the mechs' curved armour shaded smoothly under Godot's lights; a box's edges kept sharp)
	for (uint64_t key : order) {
		Surface &s = surfaces[key];
		if (s.blend >= 2) continue;   // (effects are unlit)
		const int64_t n = s.v.size();
		std::unordered_map<uint64_t, std::vector<int64_t>> at;
		auto cell = [](const Vector3 &p) {
			const int64_t x = (int64_t)Math::round(p.x * 8.0f), y = (int64_t)Math::round(p.y * 8.0f), z = (int64_t)Math::round(p.z * 8.0f);
			return (uint64_t)(x * 73856093) ^ (uint64_t)(y * 19349663) ^ (uint64_t)(z * 83492791);
		};
		for (int64_t i = 0; i < n; i++) at[cell(s.v[i])].push_back(i);
		PackedVector3Array smooth;
		smooth.resize(n);
		for (int64_t i = 0; i < n; i++) {
			const Vector3 f = s.n[i];
			Vector3 sum;
			for (int64_t j : at[cell(s.v[i])])
				if (s.v[j].distance_squared_to(s.v[i]) < 0.02f && s.n[j].dot(f) > 0.5f) sum += s.n[j];
			smooth.set(i, sum.length_squared() > 0 ? sum.normalized() : f);
		}
		s.n = smooth;
	}
	for (uint64_t key : order) {
		Surface &s = surfaces[key];
		Array arrays;
		arrays.resize(Mesh::ARRAY_MAX);
		arrays[Mesh::ARRAY_VERTEX] = s.v;
		arrays[Mesh::ARRAY_NORMAL] = s.n;
		arrays[Mesh::ARRAY_TEX_UV] = s.uv;
		arrays[Mesh::ARRAY_COLOR] = s.col;
		if (mesh.is_null() || mesh->get_surface_count() >= 256) {
			mesh.instantiate();
			meshes.push_back(mesh);
		}
		mesh->add_surface_from_arrays(Mesh::PRIMITIVE_TRIANGLES, arrays);
		// (effects drawn in the game's order: Godot's render priority, -128 .. 127, by run)
		const int priority = s.run <= 0 ? 0 : runs <= 255 ? -128 + s.run : -128 + (int)((int64_t)s.run * 255 / (runs + 1));
		mesh->surface_set_material(mesh->get_surface_count() - 1, map_material(s.texture, s.env, s.blend, s.cull, priority));
	}
	return meshes;
}

void AxisReplay::free_all() {
	if (!rd) return;
	for (auto &kv : pipelines) rd->free_rid(kv.second);
	for (auto &kv : gtex) if (kv.second.tex.is_valid()) rd->free_rid(kv.second.tex);
	for (auto &kv : samplers) rd->free_rid(kv.second);
	if (vbuf.is_valid()) rd->free_rid(vbuf);
	if (white.is_valid()) rd->free_rid(white);
	if (framebuffer.is_valid()) { rd->free_rid(framebuffer); rd->free_rid(color); rd->free_rid(depthTex); }
	if (shader.is_valid()) rd->free_rid(shader);
	pipelines.clear(); gtex.clear(); samplers.clear();
}
