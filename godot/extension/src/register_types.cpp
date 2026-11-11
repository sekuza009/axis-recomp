// register_types.cpp: the extension's entry - registers AxisReplay (axis_replay.h).
#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "axis_replay.h"
#include "axis_game.h"
#include "axis_launcher.h"
#include "axis_movie.h"
#include "axis_map_effect.h"

#ifndef _WIN32
#include <dlfcn.h>
#endif

using namespace godot;

extern "C" void axis_crash_report_install(void);   // crash_report.c

static void initialize(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
		return;
#if defined(DEBUG_ENABLED) && defined(_WIN32)
	axis_crash_report_install();   // (debug builds on Windows: a crash reported with its place)
#endif
	GDREGISTER_CLASS(AxisReplay);
	GDREGISTER_CLASS(AxisGame);
	GDREGISTER_CLASS(AxisLauncher);
	GDREGISTER_CLASS(AxisMovie);
	GDREGISTER_CLASS(AxisMapEffect);
}

static void uninitialize(ModuleInitializationLevel p_level) {
	(void)p_level;
}

extern "C" GDExtensionBool GDE_EXPORT axis_godot_init(GDExtensionInterfaceGetProcAddress p_get_proc_address,
		const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
#ifndef _WIN32
	{	// (the extension kept mapped to the process's end: Godot unloads it before exit, and an exit handler registered
		// from it (its C++ statics) then jumped into unmapped memory - a crash on every quit on Linux)
		Dl_info self;
		if (dladdr((void *)&axis_godot_init, &self) && self.dli_fname)
			dlopen(self.dli_fname, RTLD_NOW | RTLD_NOLOAD | RTLD_NODELETE);
	}
#endif
	GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
	init_obj.register_initializer(initialize);
	init_obj.register_terminator(uninitialize);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);
	return init_obj.init();
}
