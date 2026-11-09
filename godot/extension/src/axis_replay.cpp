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

#include <cstring>

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
layout(location = 0) in vec4 v_col;
layout(location = 1) in vec2 v_uv;
layout(location = 2) in float v_fog;
layout(location = 0) out vec4 frag;
void main() {
	vec4 c = v_col;
	if ((pc.flags & 1u) != 0u) {
		vec4 t = texture(tex, v_uv);
		if (pc.env == 0x1E01u) c = t;                                  // GL_REPLACE
		else if (pc.env == 0x2101u) c.rgb = mix(c.rgb, t.rgb, t.a);    // GL_DECAL
		else c *= t;                                                   // GL_MODULATE
	}
	if ((pc.flags & 2u) != 0u)
		c.rgb = mix(pc.fog_color.rgb, c.rgb, v_fog);
	frag = c;
}
)";

struct Push { uint32_t base, flags, env, pad; float fog[4]; };

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
	f->set_usage_bits(RenderingDevice::TEXTURE_USAGE_COLOR_ATTACHMENT_BIT | RenderingDevice::TEXTURE_USAGE_SAMPLING_BIT | RenderingDevice::TEXTURE_USAGE_CAN_COPY_FROM_BIT);
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
	fbW = w;
	fbH = h;
	for (auto &kv : pipelines) rd->free_rid(kv.second);
	pipelines.clear();
	callable_mp(this, &AxisReplay::_set_texture_rid).call_deferred(color);
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
	// (the y flip in gl_emu turns GL's counter-clockwise front faces clockwise)
	ras->set_front_face(p.frontFace == 0x901 ? RenderingDevice::POLYGON_FRONT_FACE_CLOCKWISE : RenderingDevice::POLYGON_FRONT_FACE_COUNTER_CLOCKWISE);
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
	// the commands, in order: a clear starts a draw list that clears, batches draw into the current one
	int64_t dl = -1;
	for (const EmuCmd &c : p.cmds) {
		if (c.kind == EmuCmd::CLEAR) {
			if (dl >= 0) rd->draw_list_end();
			BitField<RenderingDevice::DrawFlags> flags = 0;
			if (c.clearMask & 0x4000) flags.set_flag(RenderingDevice::DRAW_CLEAR_COLOR_0);
			if (c.clearMask & 0x100) flags.set_flag(RenderingDevice::DRAW_CLEAR_DEPTH);
			PackedColorArray colors;
			colors.push_back(Color(c.clearColor[0], c.clearColor[1], c.clearColor[2], c.clearColor[3]));
			dl = rd->draw_list_begin(framebuffer, flags, colors, c.clearDepth);
			continue;
		}
		const EmuBatch &b = c.batch;
		if (b.count == 0 || b.scissor[2] <= 0 || b.scissor[3] <= 0) continue;
		if (dl < 0) dl = rd->draw_list_begin(framebuffer);
		rd->draw_list_bind_render_pipeline(dl, pipeline_for(b.pipe));
		rd->draw_list_bind_uniform_set(dl, set0, 0);
		RID set = whiteSet;
		bool textured = false;
		if (b.texture) {
			auto it = gtex.find(b.texture - 1);
			if (it != gtex.end() && it->second.tex.is_valid()) { set = set_for(it->second, b); textured = true; }
		}
		rd->draw_list_bind_uniform_set(dl, set, 1);
		rd->draw_list_enable_scissor(dl, Rect2(b.scissor[0], b.scissor[1], b.scissor[2], b.scissor[3]));
		Push push = { b.first, (textured ? 1u : 0u) | (b.fog ? 2u : 0u), b.env, 0, { b.fogColor[0], b.fogColor[1], b.fogColor[2], b.fogColor[3] } };
		rd->draw_list_set_push_constant(dl, bytes(&push, sizeof push), sizeof push);
		rd->draw_list_draw(dl, false, 1, b.count);
	}
	if (dl >= 0) rd->draw_list_end();
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
