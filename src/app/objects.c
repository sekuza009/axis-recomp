/* objects.c: the C++ destructors the compiler made for the game's classes: the "deleting" destructor (the one in
   the vtable) runs the plain one and frees the object when bit 0 of flags is set. */
#include "../game.h"

/* 0x483fb0: a ViewVolume's destructor: its own vtable back, then its vertex buffer freed (gfx_initVertexArrayExt,
   which also looks the GL_EXT_vertex_array entry points up again) */
int THISCALL (ViewVolume_dtor)(void *view)
{
	*(u32 *)view = 0x4aa24c;
	return gfx_initVertexArrayExt(view);
}

/* 0x463430, 0x460c20, 0x463830: the deleting destructors of ViewVolume, Console and Stage (they return the object) */
void *THISCALL (ViewVolume_deletingDtor)(void *view, int flags)
{
	ViewVolume_dtor(view);
	if (flags & 1)
		operator_delete(view);
	return view;
}

void *THISCALL (Console_deletingDtor)(void *console, int flags)
{
	Console_dtor(console);
	if (flags & 1)
		operator_delete(console);
	return console;
}

void *THISCALL (Stage_deletingDtor)(Stage *stage, int flags)
{
	Stage_dtor(stage);
	if (flags & 1)
		operator_delete(stage);
	return stage;
}

/* 0x401290 (load_401290): the compiler's array constructor: construct (thiscall) on count objects of size bytes
   from first (stdcall) */
void STDCALL (load_401290)(u8 *first, int size, int count, void (THISCALL *construct)(void *))
{
	for (int i = 0; i < count; i++, first += size)
		construct(first);
}
