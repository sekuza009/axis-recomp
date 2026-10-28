/* fog.c: the scene's OpenGL fog. */
#include "../game.h"

/* 0x472900 (hud_472900): linear fog: keeps colour (four floats), start, end and density in the scene and hands
   them to OpenGL (density too, though linear fog ignores it); all passed on bit for bit */
void THISCALL (hud_472900)(Scene *scene, const u32 colour[4], u32 start, u32 end, u32 density)
{
	for (int i = 0; i < 4; i++)
		scene->glFogColour[i] = colour[i];
	scene->glFogStart = start;
	scene->glFogEnd = end;
	scene->glFogDensity = density;
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR, scene->glFogColour);
	glFogf_stored(GL_FOG_DENSITY, scene->glFogDensity);
	glHint(GL_FOG_HINT, GL_DONT_CARE);
	glFogf_stored(GL_FOG_START, scene->glFogStart);
	glFogf_stored(GL_FOG_END, scene->glFogEnd);
}
