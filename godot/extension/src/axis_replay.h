// axis_replay.h: AxisReplay, a node that plays a recorded stream of the game's drawing (an AXGLREC1 file from
// standalone/glrec.c, AXIS_GLREC_DUMP) in Godot: gl_emu turns each frame into clears and draw batches, which are
// executed with Godot's RenderingDevice into a texture (get_texture(), a Texture2DRD) of the recorded frame size.
#pragma once
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/rendering_device.hpp>
#include <godot_cpp/classes/texture2drd.hpp>

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
