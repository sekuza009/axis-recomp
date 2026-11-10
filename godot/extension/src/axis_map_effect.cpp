// axis_map_effect.cpp: see axis_map_effect.h.
#include "axis_map_effect.h"
#include "axis_replay.h"

#include <godot_cpp/classes/render_scene_buffers_rd.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void AxisMapEffect::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_replay", "replay"), &AxisMapEffect::set_replay);
}

AxisMapEffect::AxisMapEffect() {
	set_effect_callback_type(EFFECT_CALLBACK_TYPE_POST_TRANSPARENT);
}

void AxisMapEffect::set_replay(Object *p_replay) {
	replay = p_replay ? ObjectID(p_replay->get_instance_id()) : ObjectID();
}

void AxisMapEffect::_render_callback(int32_t p_effect_callback_type, RenderData *p_render_data) {
	(void)p_effect_callback_type;
	AxisReplay *r = Object::cast_to<AxisReplay>(ObjectDB::get_instance(replay));
	if (!r || !p_render_data) return;
	Ref<RenderSceneBuffersRD> b = p_render_data->get_render_scene_buffers();
	if (b.is_null()) return;
	r->draw_deferred(b->get_color_layer(0), b->get_depth_layer(0), b->get_internal_size());
}
