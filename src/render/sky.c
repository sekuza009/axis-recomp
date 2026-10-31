/* sky.c: the stage's sky, drawn first each frame around a camera that only turns: the sky sphere, the cloud layers,
   the side walls and the animated floor under the fog. Each part is a set of triangle strips through a grid of
   vertices kept in the stage; the sphere and the layers are scaled up 10000 times. */
#include "../game.h"

#define GL_TRIANGLE_STRIP 5
#define GL_CULL_FACE 0x0b44
#define GL_DEPTH_TEST 0x0b71
#define GL_MODELVIEW_MATRIX 0x0ba6

static void bind(int texture)
{
	tex_bind(g_textures->managers[texture / 512], texture % 512);
}

/* a vertex of the grids scaled up, each coordinate rounded to a float */
static void scaled(float out[3], const float v[3], float k)
{
	for (int i = 0; i < 3; i++)
		out[i] = f32((long double)v[i] * k);
}

/* the sphere's texture coordinate along a face: the edges pulled in by 0.01 so the faces do not bleed */
static float inset(int i)
{
	return i == 0 ? 0.01f : i == 6 ? -0.01f : 0.0f;
}

/* the sky sphere: six faces (one texture each) of 6 x 6 cells. skyMode 1 draws only the upper half (the top
   two rows of the first five faces) and stretches the side faces' rows double height; 2 draws it all evenly */
static void sky_sphere(Stage *stage)
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	for (int face = 0; face < 6; face++) {
		bind(stage->skyTextures[face]);
		for (int row = 0; row < 6; row++) {
			glBegin(GL_TRIANGLE_STRIP);
			float rowT = f32((long double)row * (1.0f / 6));
			/* the top edge of the first row is pulled in; the bottom one only "for row 6", which never comes */
			float topInset = row == 0 ? 0.01f : 0.0f, bottomInset = row == 6 ? -0.01f : 0.0f;
			for (int col = 0; col <= 6; col++) {
				float v[3];
				float s = f32((long double)col * (1.0f / 6) + inset(col));
				glTexCoord2f(s, (float)((long double)rowT + topInset));
				scaled(v, stage->skySphere[face][row][col], 10000.0f);
				glVertex3fv(v);
				float rowHeight = stage->skyMode == 2 || face == 0 ? 1.0f / 6 : 1.0f / 3;
				scaled(v, stage->skySphere[face][row + 1][col], 10000.0f);
				glTexCoord2f(s, (float)((long double)(row + 1) * rowHeight + bottomInset));
				glVertex3fv(v);
			}
			glEnd();
			if (row == 1 && stage->skyMode == 1)
				break;
		}
		if (face == 4 && stage->skyMode == 1)
			break;
	}
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
}

/* a cloud layer: 6 x 6 cells over the layer grid, the texture repeating once a cell and scrolled by
   stage->layerScroll; the second layer (layerMode 2) sits at 0.9 of the size and scrolls twice as fast */
static void sky_layer(Stage *stage, int second)
{
	bind(stage->layerTextures[second]);
	for (int row = 0; row < 6; row++) {
		glBegin(GL_TRIANGLE_STRIP);
		float top = (float)row, bottom = (float)(row + 1);
		for (int col = 0; col <= 6; col++) {
			float colS = (float)col;
			for (int k = 0; k < 2; k++) {
				const float *p = stage->layer[row + k][col];
				float v[3], t = k == 0 ? top : bottom;
				if (!second) {
					scaled(v, p, 10000.0f);
					glTexCoord2f((float)((long double)colS + stage->layerScroll[0]),
					             (float)((long double)t + stage->layerScroll[1]));
				} else {
					/* x goes on unrounded, y and z are rounded to floats before the 0.9 */
					v[0] = (float)((long double)p[0] * 10000.0f * 0.9f);
					v[1] = (float)((long double)f32((long double)p[1] * 10000.0f) * 0.9f);
					v[2] = (float)((long double)f32((long double)p[2] * 10000.0f) * 0.9f);
					long double su = stage->layerScroll[0], sv = stage->layerScroll[1];
					glTexCoord2f((float)(su + su + colS), (float)(sv + sv + t));
				}
				glVertex3fv(v);
			}
		}
		glEnd();
	}
}

static void sky_layers(Stage *stage)
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	sky_layer(stage, 0);
	if (stage->layerMode == 2)
		sky_layer(stage, 1);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
}

/* the side walls: six strips of three cells (one texture each) standing on the ground, the first four points of
   each side's eight scaled 8000 times; sideMode 1 makes them half as high */
static void sky_sides(Stage *stage)
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	float height = stage->sideMode == 1 ? 2094.395263671875f : 4188.79052734375f;
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	for (int side = 0; side < 6; side++) {
		bind(stage->sideTextures[side]);
		glBegin(GL_TRIANGLE_STRIP);
		for (int col = 0; col <= 3; col++) {
			const float *p = stage->sides[side][col];
			float s = f32((long double)col * (1.0f / 3));
			float v[3] = { f32((long double)p[0] * 8000.0f), height, f32((long double)p[2] * 8000.0f) };
			glTexCoord2f(s, 0.0f);
			glVertex3fv(v);
			v[1] = 0.0f;
			glTexCoord2f(s, 1.0f);
			glVertex3fv(v);
		}
		glEnd();
	}
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
}

/* the floor: 10 x 10 cells of the floor grid times scale, under the stage's fog, textured with the current frame
   of its animation; the texture lies still on the ground (its coordinates follow the camera position) */
static void sky_floor(Stage *stage, float scale)
{
	stage_setFog(stage, stage->glFogColour, stage->glFogStart, stage->glFogEnd, stage->glFogDensity);
	glEnable(GL_FOG);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	bind(stage->floorTextures[stage->floorFrame]);
	for (int row = 0; row < 10; row++) {
		glBegin(GL_TRIANGLE_STRIP);
		for (int col = 0; col < 11; col++) {
			for (int k = 0; k < 2; k++) {
				float v[3];
				for (int i = 0; i < 3; i++)
					v[i] = f32((long double)scale * stage->floor[row + k][col][i]);
				glTexCoord2f((float)(((long double)v[0] + stage->cameraPos[0]) * 0.0001f),
				             (float)(((long double)v[2] + stage->cameraPos[2]) * 0.0001f));
				glVertex3fv(v);
			}
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_FOG);
}

/* 0x496f20 (sky_draw): the sky, with the modelview saved and restored around it. The sphere and the layers are
   seen from the origin looking along the camera's direction; the side walls from the camera's height (scaled by
   10000 / scale); the floor from the camera's height */
void THISCALL (sky_draw)(Stage *stage, float scale)
{
	float saved[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, saved);
	const float *dir = stage->viewDir, *up = stage->viewUp;
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 0.0, dir[0], dir[1], dir[2], up[0], up[1], up[2]);
	if (stage->skyMode != 0)
		sky_sphere(stage);
	if (stage->layerMode != 0)
		sky_layers(stage);

	float k = f32((long double)10000.0f / scale);
	float height = stage->cameraPos[1];
	glLoadIdentity();
	gluLookAt(0.0, (double)((long double)k * height), 0.0,
	          (double)((long double)k * dir[0]), (double)(((long double)height + dir[1]) * k), (double)((long double)k * dir[2]),
	          (double)((long double)k * up[0]), (double)((long double)k * up[1]), (double)((long double)k * up[2]));
	if (stage->sideMode != 0)
		sky_sides(stage);

	glLoadIdentity();
	gluLookAt(0.0, height, 0.0, dir[0], (double)((long double)height + dir[1]), dir[2], up[0], up[1], up[2]);
	if (stage->floorOn != 0)
		sky_floor(stage, scale);
	glLoadMatrixf(saved);
}
