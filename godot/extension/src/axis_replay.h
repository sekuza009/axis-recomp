// axis_replay.h: AxisReplay, a node that plays a recorded stream of the game's drawing (an AXGLREC1 file from
// standalone/glrec.c, AXIS_GLREC_DUMP) in Godot: gl_emu turns each frame into clears and draw batches, which are
// executed with Godot's RenderingDevice into a texture (get_texture(), a Texture2DRD) of the recorded frame size.
#pragma once
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/rendering_device.hpp>
#include <godot_cpp/classes/texture2drd.hpp>
#include <godot_cpp/variant/projection.hpp>
#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/classes/compositor_effect.hpp>
#include <godot_cpp/classes/shader.hpp>
#include <godot_cpp/classes/shader_material.hpp>
#include <godot_cpp/variant/transform3d.hpp>

#include <mutex>
#include <unordered_map>
#include <vector>

#include "gl_emu.h"

namespace godot {

class AxisReplay : public Node {
	GDCLASS(AxisReplay, Node)

public:
	AxisReplay();
	~AxisReplay();
	bool open(const String &p_path);
	int get_frame_count() const;
	int get_frame() const { return current; }
	Vector2i get_frame_size() const;
	void set_playing(bool p_playing) { playing = p_playing; }
	bool is_playing() const { return playing; }
	void set_fps(double p_fps) { fps = p_fps; }
	double get_fps() const { return fps; }
	Ref<Texture2DRD> get_texture() const { return texture; }

	// the remaster's look: effects on the finished 3D world (drawn with a perspective projection), before the HUD and
	// menus are drawn over it - those stay exactly the original's. Off: the original's picture, unchanged.
	struct Look {
		bool enabled = false;
		float bloom = 0.0f, bloomThreshold = 0.75f, bloomRadius = 1.0f;
		float exposure = 1.0f, contrast = 1.0f, saturation = 1.0f, warmth = 0.0f;
		float vignette = 0.0f, sharpen = 0.0f;
	};
	Look look;
	// the remaster's view of the frame (src/render/draw_tags.h): tag_view tints each part by what it is; the camera
	// of the frame (the world's view volume) as Godot's types; the world's points of chosen kinds (1 << tag each)
	bool tagView = false, overlay = false;
	void set_tag_view(bool v) { tagView = v; }
	bool get_tag_view() const { return tagView; }
	void set_overlay(bool v) { overlay = v; }
	bool get_overlay() const { return overlay; }
	bool has_camera() const { return emu.hasCamera; }

	// the picture (step 3): 0 the original - the game's own drawing; 1 the original lighting - the map drawn by Godot
	// (remaster_view.gd's viewport, the game's camera) with the game's vertex colours; 2 the remaster - the map lit by
	// Godot's lights (the game's lighting kept as a base: original_light). In 1 and 2 the game's map batches (ground,
	// map objects) are left out and Godot's map put in their place - its colour and depth, so the game's actors, effects
	// and HUD are drawn into it as before (AxisMapEffect, during that viewport's render)
	int pictureMode = 0;
	bool mapViewport = false;   // (remaster_view.gd's viewport and its effect are there)
	float originalLight = 0.6f;
	bool vertexLighting = true;   // (the map lit as the game lights it, per vertex, with Godot's shadows: k_game_light)
	float shadowStrength = 0.5f;
	float lightCap = 1.0f;   // (the lit map surfaces' lights summed no higher than this: k_map_light)
	// what Godot draws in picture modes 1 and 2, by kind (1 << tag, src/render/draw_tags.h): the ground, map objects,
	// actors and items by default (the actors' view pass, over a cleared depth buffer, and the effects stay the game's)
	int godotKinds = (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7) | (1 << 8);
	int weaponMesh = -1;   // (build_map_meshes: the mesh of the actors' view pass - the first-person weapon - or -1)
	int get_weapon_mesh_index() const { return weaponMesh; }
	bool frame_effects() const;   // (picture mode 2 and no sky in the frame: Godot draws the see-through and additive parts too)
	void set_godot_kinds(int v) { godotKinds = v; }
	int get_godot_kinds() const { return godotKinds; }
	void set_picture_mode(int v) { pictureMode = v < 0 ? 0 : v > 2 ? 2 : v; }
	int get_picture_mode() const { return pictureMode; }
	void set_map_viewport(bool v) { mapViewport = v; }
	bool get_map_viewport() const { return mapViewport; }
	void set_original_light(float v);
	float get_original_light() const { return originalLight; }
	void set_vertex_lighting(bool on) { vertexLighting = on; }   // (the next frame's meshes take it: materials by key)
	bool get_vertex_lighting() const { return vertexLighting; }
	void set_shadow_strength(float v);
	float get_shadow_strength() const { return shadowStrength; }
	void set_light_cap(float v);
	float get_light_cap() const { return lightCap; }
	// this frame's world of the kinds Godot draws, in the world's space: meshes of at most 256 surfaces each (Godot's
	// limit; the effects are a surface per run, to keep the game's order)
	TypedArray<ArrayMesh> build_map_meshes();
	// the sky (picture mode 2): its triangles in the game's camera space, whichever viewpoint of its own each part was
	// drawn from (sky.c) - the same on screen - in the game's order, for remaster_view.gd's sky viewport
	TypedArray<ArrayMesh> build_sky_meshes();
	Color get_clear_colour() const;
	void redraw() { submit(emu.width(), emu.height()); }
	String dump_batches() const;   // (a check: the frame's batches - texture size, mode, colours)   // (the frame again: after a picture mode's change)   // the frame's first colour clear (what shows through a see-through sky)
	bool sky_in_godot() const { return pictureMode == 2 && mapViewport; }
	void draw_deferred(const RID &p_color, const RID &p_depth, const Vector2i &p_size);   // (AxisMapEffect, render thread)
	Projection get_camera_projection() const;
	Transform3D get_camera_view() const;
	Rect2i get_camera_viewport() const;
	Array get_lights(bool points = true) const;   // the stage's lights this frame: {pool, kind, colour, position, direction, radius}       // the world's viewport (framebuffer pixels, top-left origin)
	PackedInt32Array get_tag_stats() const;   // triangles drawn this frame by tag
	PackedVector3Array get_world_triangles(int mask) const;   // the 3D batches of those tags, in the world's space
	Array get_world_samples(int mask, int count) const;        // [world points, where the game drew them (pixels)]
#define AXIS_LOOK_PROP(name, field) \
	void set_##name(float v) { look.field = v; } \
	float get_##name() const { return look.field; }
	void set_look_enabled(bool v) { look.enabled = v; }
	bool get_look_enabled() const { return look.enabled; }
	AXIS_LOOK_PROP(bloom, bloom)
	AXIS_LOOK_PROP(bloom_threshold, bloomThreshold)
	AXIS_LOOK_PROP(bloom_radius, bloomRadius)
	AXIS_LOOK_PROP(exposure, exposure)
	AXIS_LOOK_PROP(contrast, contrast)
	AXIS_LOOK_PROP(saturation, saturation)
	AXIS_LOOK_PROP(warmth, warmth)
	AXIS_LOOK_PROP(vignette, vignette)
	AXIS_LOOK_PROP(sharpen, sharpen)
#undef AXIS_LOOK_PROP
	bool step();   // the next frame (false at the end)
	String get_status() const;
	void _process(double p_delta) override;

protected:
	static void _bind_methods();
	void submit(int w, int h);   // emu's current frame to the render thread

	GLEmu emu;
	bool loaded = false, playing = false;
	double fps = 60, accumulated = 0;
	int current = 0;
	Ref<Texture2DRD> texture;
	std::unordered_map<uint32_t, uint32_t> sentVersions;   // the texture versions already handed to the render thread

	// a frame handed to the render thread
	struct Pending {
		std::vector<EmuVertex> verts;
		std::vector<EmuCmd> cmds;
		std::vector<std::pair<uint32_t, EmuTexture>> textures;
		int w = 0, h = 0;
		bool ready = false;
		Look look;
		bool tagView = false;
		bool composite = false;   // drawn later, into Godot's map (draw_deferred)
		int kinds = 0;            // (godotKinds then)
		bool effects = false;     // (frame_effects() then)
	};
	std::mutex mutex;
	Pending pending;

	// the render thread's resources
	RenderingDevice *rd = nullptr;
	RID shader, color, depthTex, framebuffer, vbuf, set0, white, whiteSampler, whiteSet;
	int64_t fbFormat = -1;
	int fbW = 0, fbH = 0;
	uint32_t vbufBytes = 0;
	struct GTex { RID tex; uint32_t version = 0; std::unordered_map<uint64_t, RID> sets; };   // (a set per sampling)
	std::unordered_map<uint32_t, GTex> gtex;
	std::unordered_map<uint64_t, RID> pipelines, samplers;
	String status;

	void _render();
	void draw_cmds(const Pending &p, const RID &gColor, const RID &gDepth);
	Pending deferred;
	bool haveDeferred = false;
	// Godot's picture of the map as the shader's third set (the map's solid surfaces coloured from it)
	RID whiteSet2;
	std::unordered_map<uint64_t, RID> godotSets;
	RID godot_map_set(const RID &p_color);
	// the game's textures as Godot's (Texture2DRD over the same RD textures) and the map's materials
	std::mutex texMutex;
	std::unordered_map<uint32_t, RID> texRids;   // (render thread -> main thread)
	std::unordered_map<uint32_t, Ref<Texture2DRD>> texShown;
	std::unordered_map<uint64_t, Ref<ShaderMaterial>> mapMaterials;
	Ref<Shader> mapShaders[2][5][4][2][2];   // [original lighting / remaster][the class: godot_class()][the culling][weapon][per vertex]
	Ref<ShaderMaterial> map_material(uint32_t texture, uint32_t env, int blendClass, int cull, int priority = 0, bool weapon = false);
	Ref<Shader> skyShaders[4];   // [no blending / alpha / additive (source alpha) / additive (one)]
	std::unordered_map<uint64_t, Ref<ShaderMaterial>> skyMaterials;
	Ref<ShaderMaterial> sky_material(const EmuBatch &b, int priority);
	// the look's passes (compute): the world copied, bloom (a bright pass, a chain of half sizes down, blurred back
	// up), then the composite written back into the frame
	RID postBloomShader, postCompShader, postSampler, postScene;
	std::vector<RID> postBloom;          // the bloom chain, half size each
	std::vector<std::pair<int, int>> postSizes;
	std::vector<RID> postSets;           // (made with the chain: the bloom passes' sets, then the composite's)
	RID postBloomPipe, postCompPipe;
	int postW = 0, postH = 0;
	bool ensure_post(int w, int h);
	void run_post(const Look &l);
	void _set_texture_rid(const RID &p_rid);
	RID newColor;   // (a frame texture made on the render thread, not yet attached: apply_texture)
	bool newColorSet = false;
public:
	void apply_texture();
protected:
	bool ensure_shader();
	void ensure_framebuffer(int w, int h);
	RID sampler_for(int minF, int magF, int wrapS, int wrapT);
	RID set_for(GTex &g, const EmuBatch &b);
	RID pipeline_for(const EmuPipe &p);
	void upload_texture(uint32_t key, const EmuTexture &t);
	void free_all();
};

} // namespace godot
