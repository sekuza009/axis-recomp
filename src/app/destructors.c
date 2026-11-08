/* destructors.c: C++ object plumbing the compiler made for the game's classes: the "deleting" destructors (the ones
   in the vtables: the plain destructor run, the object freed when bit 0 of flags is set) and plain destructors of the
   view volume and the game object, the array constructor (crt_vectorConstructorIterator), and a view volume's
   matrices captured (ViewVolume_captureMatrices). */
#include "../game.h"

/* 0x483fb0: a ViewVolume's destructor: its own vtable back, then released (ViewVolume_release: its owned block
   freed, its lists cleared, and the GL_EXT_vertex_array entry points looked up again) */
int THISCALL (ViewVolume_dtor)(void *view)
{
	*(u32 *)view = STR(0x4aa24c, "04F");
	return ViewVolume_release(view);
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

/* 0x401290 (crt_vectorConstructorIterator): the compiler's array constructor: construct (thiscall) on count objects of size bytes
   from first (stdcall) */
void STDCALL (crt_vectorConstructorIterator)(u8 *first, int size, int count, void (THISCALL *construct)(void *))
{
	for (int i = 0; i < count; i++, first += size)
		construct(first);
}

/* 0x460c40: the game's class Console's destructor (the Console is our Scene, the game object): its vtable back (0x4aa238), then its members
   destroyed: the stage (+0x1f36c8), the view volume (view) and the time sync (timer). The caller ignores the eax it
   leaves */
void THISCALL (Console_dtor)(u8 *self)
{
	Scene *sc = (Scene *)self;
	GAME_VAR(u32, self) = VT(Console);
	Stage_dtor(SCENE_STAGE(self));
	ViewVolume_dtor(&sc->view);
	TimeSync_dtor((u8 *)&sc->timer);
}

/* 0x4841f0 (thiscall on a view volume): its projection (projection) and view (modelview) matrices copied from those
   given, or each read from OpenGL when none is given, and their product kept (clip) */
void THISCALL (ViewVolume_captureMatrices)(u8 *view, const float *projection, const float *modelview)
{
	ViewVolume *vw = (ViewVolume *)view;
	float *p = vw->projection, *m = vw->modelview;
	if (projection)
		Mat4_copy(p, projection);
	else
		glGetFloatv(0xba7, p);   /* GL_PROJECTION_MATRIX */
	if (modelview)
		Mat4_copy(m, modelview);
	else
		glGetFloatv(0xba6, m);   /* GL_MODELVIEW_MATRIX */
	Mat4_multiply(vw->clip, p, m);
}
