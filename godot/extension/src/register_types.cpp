// register_types.cpp: the extension's entry - registers AxisReplay (axis_replay.h).
#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "axis_replay.h"
#include "axis_game.h"

using namespace godot;

static void initialize(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
		return;
	GDREGISTER_CLASS(AxisReplay);
	GDREGISTER_CLASS(AxisGame);
}

static void uninitialize(ModuleInitializationLevel p_level) {
	(void)p_level;
}

extern "C" GDExtensionBool GDE_EXPORT axis_godot_init(GDExtensionInterfaceGetProcAddress p_get_proc_address,
		const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
	init_obj.register_initializer(initialize);
	init_obj.register_terminator(uninitialize);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);
	return init_obj.init();
}
