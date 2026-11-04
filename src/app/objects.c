/* objects.c: the C++ destructors the compiler made for the game's classes: the "deleting" destructor (the one in
   the vtable) runs the plain one and frees the object when bit 0 of flags is set. */
#include "../game.h"

/* 0x483fb0: a ViewVolume's destructor: its own vtable back, then its vertex buffer freed (gfx_initVertexArrayExt,
   which also looks the GL_EXT_vertex_array entry points up again) */
int THISCALL (ViewVolume_dtor)(void *view)
{
	*(u32 *)view = STR(0x4aa24c, "04F");
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

/* 0x401290 (crt_arrayConstruct): the compiler's array constructor: construct (thiscall) on count objects of size bytes
   from first (stdcall) */
void STDCALL (crt_arrayConstruct)(u8 *first, int size, int count, void (THISCALL *construct)(void *))
{
	for (int i = 0; i < count; i++, first += size)
		construct(first);
}

/* 0x460c40 (named Console_ctor; by use the Console's destructor): its vtable back (0x4aa238), then its members
   destroyed: the stage (+0x1f36c8), the view volume (+0x74) and the time sync (+0xc). The caller ignores the eax it
   leaves */
void THISCALL (Console_ctor)(u8 *self)
{
	GAME_VAR(u32, self) = VT(Console, 0x4aa238);
	Stage_dtor(SCENE_STAGE(self));
	ViewVolume_dtor(((Scene *)self)->view);
	TimeSync_dtor((u8 *)&((Scene *)self)->timer);
}

/* 0x4841f0 (thiscall on a view volume): its projection (+0x90b0) and view (+0x90f0) matrices copied from those
   given, or each read from OpenGL when none is given, and their product kept (+0x9130) */
void THISCALL (ViewVolume_captureMatrices)(u8 *view, const float *projection, const float *modelview)
{
	float *p = ((ViewVolume *)view)->projection, *m = ((ViewVolume *)view)->modelview;
	if (projection)
		Mat4_copy(p, projection);
	else
		glGetFloatv(0xba7, p);   /* GL_PROJECTION_MATRIX */
	if (modelview)
		Mat4_copy(m, modelview);
	else
		glGetFloatv(0xba6, m);   /* GL_MODELVIEW_MATRIX */
	Mat4_multiply(((ViewVolume *)view)->clip, p, m);
}
