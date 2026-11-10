// axis_map_effect.h: AxisMapEffect, the compositor effect on remaster_view.gd's map camera: once Godot has drawn the
// map (after its transparent pass), the game's frame is drawn by its AxisReplay into Godot's map - the map's colour and
// depth put in where the game's own map would be, then the game's actors, effects and HUD over it (AxisReplay's
// draw_deferred). Godot's buffers come from the render's own scene buffers, so the map and the game's frame are of the
// same moment.
#pragma once
#include <godot_cpp/classes/compositor_effect.hpp>
#include <godot_cpp/classes/render_data.hpp>
#include <godot_cpp/core/object_id.hpp>

namespace godot {

class AxisMapEffect : public CompositorEffect {
	GDCLASS(AxisMapEffect, CompositorEffect)

public:
	AxisMapEffect();
	void set_replay(Object *p_replay);
	void _render_callback(int32_t p_effect_callback_type, RenderData *p_render_data) override;

protected:
	static void _bind_methods();

private:
	ObjectID replay;
};

} // namespace godot
