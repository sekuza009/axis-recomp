/* fog.c: the stage's OpenGL fog. */
#include "../game.h"

/* 0x472900 (stage_setFog): linear fog: keeps colour (four floats), start, end and density in the stage and hands
   them to OpenGL (density too, though linear fog ignores it); all passed on bit for bit */
void THISCALL (stage_setFog)(Stage *stage, const u32 colour[4], u32 start, u32 end, u32 density)
{
	for (int i = 0; i < 4; i++)
		BITS(stage->glFogColour[i]) = colour[i];
	BITS(stage->glFogStart) = start;
	BITS(stage->glFogEnd) = end;
	BITS(stage->glFogDensity) = density;
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR, stage->glFogColour);
	glFogf_stored(GL_FOG_DENSITY, BITS(stage->glFogDensity));
	glHint(GL_FOG_HINT, GL_DONT_CARE);
	glFogf_stored(GL_FOG_START, BITS(stage->glFogStart));
	glFogf_stored(GL_FOG_END, BITS(stage->glFogEnd));
}
