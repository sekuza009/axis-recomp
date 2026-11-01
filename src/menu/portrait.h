/* portrait.h: a pilot's portrait, a cell of the 3 x 3 portrait atlas (texture 0x4dfa00, 86 texels a cell of 256),
   drawn size square at (x, y) on the bound texture */
static void portrait(int face, int x, int y, int size)
{
	const float *cell = (const float *)IMG(0x4a95ec), *texel = (const float *)IMG(0x4a957c), *last = (const float *)IMG(0x4a95e8);
	int col = face % 3, row = face / 3;
	glBegin(GL_QUADS);
	long double rt = fmul_m((long double)row, cell), ct = fmul_m((long double)col, cell);
	float row_t = f32(rt), col_t = f32(ct);
	float t0 = f32(fmul_m(rt, texel)), s0 = f32(fmul_m(ct, texel));
	glTexCoord2f(s0, t0);
	menu_vertex(x, y);
	float s1 = f32(fmul_m(fadd_m(col_t, last), texel));
	glTexCoord2f(s1, t0);
	menu_vertex(x + size, y);
	float t1 = f32(fmul_m(fadd_m(row_t, last), texel));
	glTexCoord2f(s1, t1);
	menu_vertex(x + size, y + size);
	glTexCoord2f(s0, t1);
	menu_vertex(x, y + size);
	glEnd();
}
