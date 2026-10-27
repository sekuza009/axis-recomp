/* batch 69 (lifted/grp16.c) */
#include "lifted/grp16.c"
/* 0x4729b0 (thiscall) camera_setupView(pos, dir, up, fov, w, h, near, far, dt): keep the previous camera position
   and view matrix, store the new camera (+0x20f3970), its view matrix (gluLookAt read back from GL, +0x20f39a0) and
   projection (gluPerspective, +0x20f3a34) and their product (+0x20f3a74). Unless both mode flags (+0x2149308 /
   +0x214930c) are set, every active object flagged 1 fades in (dt * 4, up to 1) while its position is inside the
   view and the line of sight to it is clear (collision_rayTrace), else fades out. Every live actor (0x8888 apart from
   +0x1cd94c0, count +0x202e8c8) gets its screen position and depth; one other than the camera's own that is in view
   with a clear line of sight also gets its name-tag corners, its direction cosine checked against the cos table, a
   timer for enemies that are alive, and a tag size by the screen width (gfx_getWidth) */
static THISCALL DWORD camera_setupView(char *scene, DWORD pos, DWORD dir, DWORD up, DWORD fov, DWORD w, DWORD h, DWORD nr, DWORD fr, DWORD dt)
{
	DWORD v[9] = { pos, dir, up, fov, w, h, nr, fr, dt };
	return run_lifted(lift_4729b0, (DWORD)scene, 9, v);
}
