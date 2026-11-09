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
	void _set_texture_rid(const RID &p_rid);
	bool ensure_shader();
	void ensure_framebuffer(int w, int h);
	RID sampler_for(int minF, int magF, int wrapS, int wrapT);
	RID set_for(GTex &g, const EmuBatch &b);
	RID pipeline_for(const EmuPipe &p);
	void upload_texture(uint32_t key, const EmuTexture &t);
	void free_all();
};

} // namespace godot
